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
#include <mmu.h>
#include <cache.h>

#ifdef RT_USING_SMP
rt_weak int riscv_master_cpu_id rt_align(L1_CACHE_BYTES) = 0;
#endif

rt_ubase_t boot_cpu_hartid;

static rt_bool_t hartid_equ_cpuid = RT_TRUE;
rt_ubase_t cpu_id_to_hartid_map[RT_CPUS_NR] rt_align(L1_CACHE_BYTES) =
{
#if defined(RT_USING_SMP) && !defined(RT_USING_DM)
#include "hartid.map"
#endif
};

#if defined(RT_USING_SMP) && defined(ARCH_MM_MMU)
static rt_ubase_t *percpu_hartid rt_align(L1_CACHE_BYTES);

void percpu_hartid_init(rt_ubase_t *percpu_ptr, rt_ubase_t hartid)
{
    rt_ubase_t *percpu_hartid_paddr;
    int cpu_id = riscv_hartid_to_cpu_id(hartid);
    rt_size_t percpu_size = (rt_size_t)(&__percpu_end - &__percpu_start);

    percpu_hartid_paddr = percpu_ptr;
    percpu_hartid = (void *)((rt_ubase_t)percpu_ptr - rt_kmem_pvoff());

    /* Save to the real area */
    *(rt_ubase_t *)((void *)percpu_hartid_paddr + cpu_id * percpu_size) = hartid;
}

/* This is the current CPU stack, but it is not used in this call. */
void percpu_write(rt_ubase_t offset, const void *data, rt_size_t size)
{
    rt_memcpy(percpu_hartid + 1 + offset, data, size);
}

void percpu_read(rt_ubase_t offset, void *data, rt_size_t size)
{
    rt_memcpy(data, percpu_hartid + 1 + offset, size);
}
#endif /* RT_USING_SMP && ARCH_MM_MMU */

rt_ubase_t riscv_cpu_id_to_hartid(int cpu_id)
{
    RT_ASSERT(cpu_id < RT_CPUS_NR);

    return cpu_id_to_hartid_map[cpu_id];
}

int riscv_hartid_to_cpu_id(rt_ubase_t hartid)
{
    int cpu_id;

    if (hartid_equ_cpuid)
    {
        return hartid;
    }

    for (cpu_id = 0; cpu_id < RT_CPUS_NR; ++cpu_id)
    {
        if (hartid == cpu_id_to_hartid_map[cpu_id])
        {
            break;
        }
    }

    return cpu_id;
}

void riscv_hartid_remap_cpu_id(rt_ubase_t hartid, int cpu_id)
{
    RT_ASSERT(cpu_id < RT_CPUS_NR);

    if (cpu_id != hartid)
    {
        hartid_equ_cpuid = RT_FALSE;
    }

    cpu_id_to_hartid_map[cpu_id] = hartid;
    rt_hw_wmb();
}

int rt_hw_cpu_id(void)
{
#ifdef RT_USING_SMP
#if !defined(ARCH_RISCV_M_MODE) && defined(ARCH_MM_MMU)
    if (ARCH_VADDR_WIDTH)
    {
        return riscv_hartid_to_cpu_id(*percpu_hartid);
    }
    else
#endif /* !ARCH_RISCV_M_MODE && ARCH_MM_MMU */
    {
        int cpu_id;

        __asm__ volatile ("mv %0, tp":"=r"(cpu_id));

        return cpu_id;
    }
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
