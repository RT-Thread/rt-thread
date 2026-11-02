/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-20     GuEe-GUI     The first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtcompiler.h>

#include <csr.h>
#include <cpu.h>
#include <cpuport.h>
#ifdef ARCH_MM_MMU
#include <mmu.h>
#endif
#include <cache.h>

#define RISCV_HARTID_INVALID   (~(rt_ubase_t)0)

rt_ubase_t boot_cpu_hartid;

static rt_bool_t hartid_equ_cpuid = RT_FALSE;
static int mapped_cpus_nr;
rt_ubase_t cpu_id_to_hartid_map[RT_CPUS_NR] rt_align(L1_CACHE_BYTES);

static void riscv_hartid_map_clear(void)
{
    for (int i = 0; i < RT_CPUS_NR; ++i)
    {
        cpu_id_to_hartid_map[i] = RISCV_HARTID_INVALID;
    }

    mapped_cpus_nr = 0;
    hartid_equ_cpuid = RT_FALSE;
}

static void riscv_hartid_map_refresh_fastpath(void)
{
    hartid_equ_cpuid = RT_TRUE;

    for (int i = 0; i < mapped_cpus_nr; ++i)
    {
        if (cpu_id_to_hartid_map[i] != (rt_ubase_t)i)
        {
            hartid_equ_cpuid = RT_FALSE;
            break;
        }
    }
}

#if defined(RT_USING_SMP) && defined(ARCH_MM_MMU)
extern char __percpu_hartid;

static rt_ubase_t *percpu_hartid rt_align(L1_CACHE_BYTES);

static rt_bool_t percpu_hartid_ptr_valid(rt_ubase_t *ptr)
{
    rt_ubase_t addr = (rt_ubase_t)ptr;
    rt_ubase_t start = (rt_ubase_t)&__percpu_start;
    rt_ubase_t end = (rt_ubase_t)&__percpu_end;

    return addr >= start && addr + sizeof(*ptr) <= end;
}

static rt_ubase_t *percpu_hartid_ptr(void)
{
    rt_ubase_t *ptr = percpu_hartid;

    if (!percpu_hartid_ptr_valid(ptr))
    {
        ptr = (rt_ubase_t *)&__percpu_hartid;
    }

    return percpu_hartid_ptr_valid(ptr) ? ptr : RT_NULL;
}

void percpu_hartid_init(rt_ubase_t *percpu_ptr, rt_ubase_t hartid)
{
    rt_ubase_t *percpu_hartid_paddr;
    int cpu_id = riscv_hartid_to_cpu_id(hartid);
    rt_size_t percpu_size = (rt_size_t)(&__percpu_end - &__percpu_start);

    RT_ASSERT(cpu_id >= 0);
    RT_ASSERT(cpu_id < RT_CPUS_NR);
    if (cpu_id < 0 || cpu_id >= RT_CPUS_NR)
    {
        return;
    }

    percpu_hartid_paddr = percpu_ptr;
    percpu_hartid = (void *)((rt_ubase_t)percpu_ptr - rt_kmem_pvoff());

    /* Save to the real area */
    *(rt_ubase_t *)((void *)percpu_hartid_paddr + cpu_id * percpu_size) = hartid;
}

/* This is the current CPU stack, but it is not used in this call. */
void percpu_write(rt_ubase_t offset, const void *data, rt_size_t size)
{
    rt_ubase_t *ptr = percpu_hartid_ptr();

    if (ptr)
    {
        rt_memcpy((void *)((rt_ubase_t)(ptr + 1) + offset), data, size);
    }
}

void percpu_read(rt_ubase_t offset, void *data, rt_size_t size)
{
    rt_ubase_t *ptr = percpu_hartid_ptr();

    if (ptr)
    {
        rt_memcpy(data, (void *)((rt_ubase_t)(ptr + 1) + offset), size);
    }
}
#endif /* RT_USING_SMP && ARCH_MM_MMU */

rt_ubase_t riscv_cpu_id_to_hartid(int cpu_id)
{
    RT_ASSERT(cpu_id >= 0);
    RT_ASSERT(cpu_id < RT_CPUS_NR);
    RT_ASSERT(cpu_id_to_hartid_map[cpu_id] != RISCV_HARTID_INVALID);

    return cpu_id_to_hartid_map[cpu_id];
}

rt_bool_t riscv_cpu_id_available(int cpu_id)
{
    if (cpu_id < 0 || cpu_id >= RT_CPUS_NR)
    {
        return RT_FALSE;
    }

    return cpu_id_to_hartid_map[cpu_id] != RISCV_HARTID_INVALID;
}

int riscv_hartid_to_cpu_id(rt_ubase_t hartid)
{
    int cpu_id;

    if (hartid_equ_cpuid && hartid < (rt_ubase_t)mapped_cpus_nr)
    {
        return hartid;
    }

    for (cpu_id = 0; cpu_id < mapped_cpus_nr; ++cpu_id)
    {
        if (hartid == cpu_id_to_hartid_map[cpu_id])
        {
            return cpu_id;
        }
    }

    return -1;
}

int riscv_hartid_register(rt_ubase_t hartid)
{
    int cpu_id = riscv_hartid_to_cpu_id(hartid);

    if (cpu_id >= 0)
    {
        return cpu_id;
    }

    if (mapped_cpus_nr >= RT_CPUS_NR)
    {
        RT_ASSERT(0);
        return -RT_EFULL;
    }

    cpu_id = mapped_cpus_nr;
    cpu_id_to_hartid_map[cpu_id] = hartid;
    rt_hw_wmb();
    mapped_cpus_nr = cpu_id + 1;
    riscv_hartid_map_refresh_fastpath();
    rt_hw_wmb();

    return cpu_id;
}

void riscv_cpu_id_set(int cpu_id)
{
#ifdef RT_USING_SMP
    RT_ASSERT(cpu_id >= 0 && cpu_id < RT_CPUS_NR);
    if (cpu_id < 0 || cpu_id >= RT_CPUS_NR)
    {
        return;
    }

    __asm__ volatile ("mv tp, %0" :: "r"(cpu_id) : "memory");
#else
    RT_UNUSED(cpu_id);
#endif
}

#if defined(RT_USING_SMP) && !defined(RT_USING_DM)
rt_weak rt_size_t riscv_hartid_list_get(rt_ubase_t *hartids, rt_size_t max_harts)
{
    rt_size_t hart_count = max_harts;

    if (hart_count > RT_CPUS_NR)
    {
        hart_count = RT_CPUS_NR;
    }

    for (rt_size_t i = 0; i < hart_count; ++i)
    {
        hartids[i] = i;
    }

    return hart_count;
}
#endif

void riscv_boot_hart_init(rt_ubase_t hartid)
{
#if defined(RT_USING_SMP) && !defined(RT_USING_DM)
    rt_ubase_t hartids[RT_CPUS_NR];
    rt_size_t hart_count = riscv_hartid_list_get(hartids, RT_CPUS_NR);
#endif

    boot_cpu_hartid = hartid;
    riscv_hartid_map_clear();
    riscv_hartid_register(hartid);
    riscv_cpu_id_set(0);

#if defined(RT_USING_SMP) && !defined(RT_USING_DM)
    RT_ASSERT(hart_count <= RT_CPUS_NR);
    if (hart_count > RT_CPUS_NR)
    {
        hart_count = RT_CPUS_NR;
    }

    for (rt_size_t i = 0; i < hart_count; ++i)
    {
        if (hartids[i] != hartid)
        {
            riscv_hartid_register(hartids[i]);
        }
    }
#endif
}

int rt_hw_cpu_id(void)
{
#ifdef RT_USING_SMP
    int cpu_id;

#if !defined(ARCH_RISCV_M_MODE) && defined(ARCH_MM_MMU)
    if (ARCH_VADDR_WIDTH)
    {
        rt_ubase_t *ptr = percpu_hartid_ptr();

        if (ptr)
        {
            cpu_id = riscv_hartid_to_cpu_id(*ptr);
            if (cpu_id >= 0 && cpu_id < RT_CPUS_NR)
            {
                return cpu_id;
            }
        }
    }
#endif /* !ARCH_RISCV_M_MODE && ARCH_MM_MMU */
    {
        __asm__ volatile ("mv %0, tp":"=r"(cpu_id));

        if (cpu_id >= 0 && cpu_id < RT_CPUS_NR)
        {
            return cpu_id;
        }
    }

    return 0;
#else
    return 0;
#endif
}

const char *rt_hw_cpu_arch(void)
{
#if __riscv_xlen == 128
    return "riscv128";
#elif __riscv_xlen == 64
    return "riscv64";
#elif __riscv_xlen == 32
    return "riscv32";
#else
#error "Unexpected __riscv_xlen"
#endif
}
