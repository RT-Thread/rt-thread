/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-21     GuEe-GUI     first version
 */

#include <rtthread.h>

#define DBG_TAG "cpu.aa64"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>
#include <smp_call.h>
#include <cpu.h>
#include <mmu.h>
#include <cpuport.h>
#include <interrupt.h>
#include <gtimer.h>
#include <setup.h>
#include <stdlib.h>
#include <ioremap.h>
#include <rtdevice.h>
#include <gic.h>
#include <gicv3.h>
#include <mm_memblock.h>

#define SIZE_KB  1024
#define SIZE_MB (1024 * SIZE_KB)
#define SIZE_GB (1024 * SIZE_MB)

extern rt_ubase_t _start, _end;
extern void _secondary_cpu_entry(void);
extern size_t MMUTable[];
extern void *system_vectors;

static void *fdt_ptr = RT_NULL;
static rt_size_t fdt_size = 0;
static rt_uint64_t initrd_ranges[3] = { };

#ifdef RT_USING_SMP
extern struct cpu_ops_t cpu_psci_ops;
extern struct cpu_ops_t cpu_spin_table_ops;
#else
extern int rt_hw_cpu_id(void);
#endif

rt_uint64_t rt_cpu_mpidr_table[] =
{
    [RT_CPUS_NR] = 0,
};

static struct cpu_ops_t *cpu_ops[] =
{
#ifdef RT_USING_SMP
    &cpu_psci_ops,
    &cpu_spin_table_ops,
#endif
};

static struct rt_ofw_node *cpu_np[RT_CPUS_NR] = { };

void rt_hw_fdt_install_early(void *fdt)
{
    if (fdt != RT_NULL && !fdt_check_header(fdt))
    {
        fdt_ptr = fdt;
        fdt_size = fdt_totalsize(fdt);
    }
}

#ifdef RT_USING_HWTIMER
static rt_ubase_t loops_per_tick[RT_CPUS_NR];

static rt_ubase_t cpu_get_cycles(void)
{
    rt_ubase_t cycles;

    rt_hw_sysreg_read(cntpct_el0, cycles);

    return cycles;
}

static void cpu_loops_per_tick_init(void)
{
    rt_ubase_t offset;
    volatile rt_ubase_t freq, step, cycles_end1, cycles_end2;
    volatile rt_uint32_t cycles_count1 = 0, cycles_count2 = 0;

    rt_hw_sysreg_read(cntfrq_el0, freq);
    step = freq / RT_TICK_PER_SECOND;

    cycles_end1 = cpu_get_cycles() + step;

    while (cpu_get_cycles() < cycles_end1)
    {
        __asm__ volatile ("nop");
        __asm__ volatile ("add %0, %0, #1":"=r"(cycles_count1));
    }

    cycles_end2 = cpu_get_cycles() + step;

    while (cpu_get_cycles() < cycles_end2)
    {
        __asm__ volatile ("add %0, %0, #1":"=r"(cycles_count2));
    }

    if ((rt_int32_t)(cycles_count2 - cycles_count1) > 0)
    {
        offset = cycles_count2 - cycles_count1;
    }
    else
    {
        /* Impossible, but prepared for any eventualities */
        offset = cycles_count2 / 4;
    }

    loops_per_tick[rt_hw_cpu_id()] = offset;
}

static void cpu_us_delay(rt_uint32_t us)
{
    volatile rt_base_t start = cpu_get_cycles(), cycles;

    cycles = ((us * 0x10c7UL) * loops_per_tick[rt_hw_cpu_id()] * RT_TICK_PER_SECOND) >> 32;

    while ((cpu_get_cycles() - start) < cycles)
    {
        rt_hw_cpu_relax();
    }
}
#endif /* RT_USING_HWTIMER */

rt_weak void rt_hw_idle_wfi(void)
{
    __asm__ volatile ("wfi");
}

static void system_vectors_init(void)
{
    rt_hw_set_current_vbar((rt_ubase_t)&system_vectors);
}

rt_inline void cpu_info_init(void)
{
    int i = 0;
    rt_uint64_t mpidr;
    struct rt_ofw_node *np;

    /* get boot cpu info */
    rt_hw_sysreg_read(mpidr_el1, mpidr);

    rt_ofw_foreach_cpu_node(np)
    {
        rt_uint64_t hwid = rt_ofw_get_cpu_hwid(np, 0);

        if ((mpidr & MPIDR_AFFINITY_MASK) != hwid)
        {
            /* Only save affinity and res make smp boot can check */
            hwid |= 1ULL << 31;
        }
        else
        {
            hwid = mpidr;
        }

        cpu_np[i] = np;
        rt_cpu_mpidr_table[i] = hwid;

        rt_ofw_data(np) = (void *)hwid;

        for (int idx = 0; idx < RT_ARRAY_SIZE(cpu_ops); ++idx)
        {
            struct cpu_ops_t *ops = cpu_ops[idx];

            if (ops->cpu_init)
            {
                ops->cpu_init(i, np);
            }
        }

        if (++i >= RT_CPUS_NR)
        {
            break;
        }
    }

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, rt_cpu_mpidr_table, sizeof(rt_cpu_mpidr_table));

#ifdef RT_USING_HWTIMER
    cpu_loops_per_tick_init();

    if (!rt_device_hwtimer_us_delay)
    {
        rt_device_hwtimer_us_delay = &cpu_us_delay;
    }
#endif /* RT_USING_HWTIMER */
}

void rt_hw_common_setup(void)
{
    rt_size_t kernel_start, kernel_end;
    rt_size_t heap_start, heap_end;
    rt_size_t init_page_start, init_page_end;
    rt_size_t fdt_start, fdt_end;
    rt_region_t init_page_region = { 0 };
    rt_region_t platform_mem_region = { 0 };
    static struct mem_desc platform_mem_desc;
    const rt_ubase_t pv_off = PV_OFFSET;

    system_vectors_init();

#ifdef RT_USING_SMART
    rt_hw_mmu_map_init(&rt_kernel_space, (void*)0xfffffffff0000000, 0x10000000, MMUTable, pv_off);
#else
    rt_hw_mmu_map_init(&rt_kernel_space, (void*)0xffffd0000000, 0x10000000, MMUTable, 0);
#endif

    kernel_start    = RT_ALIGN_DOWN((rt_size_t)rt_kmem_v2p((void *)&_start) - 64, ARCH_PAGE_SIZE);
    kernel_end      = RT_ALIGN((rt_size_t)rt_kmem_v2p((void *)&_end), ARCH_PAGE_SIZE);
    heap_start      = kernel_end;
    heap_end        = RT_ALIGN(heap_start + ARCH_HEAP_SIZE, ARCH_PAGE_SIZE);
    init_page_start = heap_end;
    init_page_end   = RT_ALIGN(init_page_start + ARCH_INIT_PAGE_SIZE, ARCH_PAGE_SIZE);
    fdt_start       = init_page_end;
    fdt_end         = RT_ALIGN(fdt_start + fdt_size, ARCH_PAGE_SIZE);

    platform_mem_region.start = kernel_start;
    platform_mem_region.end   = fdt_end;

    rt_memblock_reserve_memory("kernel", kernel_start, kernel_end, MEMBLOCK_NONE);
    rt_memblock_reserve_memory("memheap", heap_start, heap_end, MEMBLOCK_NONE);
    rt_memblock_reserve_memory("init-page", init_page_start, init_page_end, MEMBLOCK_NONE);
    rt_memblock_reserve_memory("fdt", fdt_start, fdt_end, MEMBLOCK_NONE);

    /* To virtual address */
    fdt_ptr = (void *)(fdt_ptr - pv_off);
#ifdef KERNEL_VADDR_START
    if ((rt_ubase_t)fdt_ptr + fdt_size - KERNEL_VADDR_START > SIZE_GB)
    {
        fdt_ptr = rt_ioremap_early(fdt_ptr + pv_off, fdt_size);

        RT_ASSERT(fdt_ptr != RT_NULL);
    }
#endif
    rt_memmove((void *)(fdt_start - pv_off), fdt_ptr, fdt_size);
    fdt_ptr = (void *)fdt_start - pv_off;

    rt_system_heap_init((void *)(heap_start - pv_off), (void *)(heap_end - pv_off));

    init_page_region.start = init_page_start - pv_off;
    init_page_region.end = init_page_end - pv_off;
    rt_page_init(init_page_region);

    /* create MMU mapping of kernel memory */
    platform_mem_region.start = RT_ALIGN_DOWN(platform_mem_region.start, ARCH_PAGE_SIZE);
    platform_mem_region.end   = RT_ALIGN(platform_mem_region.end, ARCH_PAGE_SIZE);

    platform_mem_desc.paddr_start = platform_mem_region.start;
    platform_mem_desc.vaddr_start = platform_mem_region.start - pv_off;
    platform_mem_desc.vaddr_end = platform_mem_region.end - pv_off - 1;
    platform_mem_desc.attr = NORMAL_MEM;

    rt_hw_mmu_setup(&rt_kernel_space, &platform_mem_desc, 1);

    if (rt_fdt_prefetch(fdt_ptr))
    {
        /* Platform cannot be initialized */
        RT_ASSERT(0);
    }

    rt_fdt_scan_chosen_stdout();

    rt_fdt_scan_initrd(initrd_ranges);

    rt_fdt_scan_memory();

    rt_memblock_setup_memory_environment();

    rt_fdt_earlycon_kick(FDT_EARLYCON_KICK_UPDATE);

    rt_fdt_unflatten();

    cpu_info_init();

#ifdef RT_USING_PIC
    rt_pic_init();
    rt_pic_irq_init();
#else
    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    /* initialize uart */
    rt_hw_uart_init();
#endif

#ifndef RT_HWTIMER_ARM_ARCH
    /* initialize timer for os tick */
    rt_hw_gtimer_init();
#endif /* !RT_HWTIMER_ARM_ARCH */

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_ofw_console_setup();
#endif

    rt_thread_idle_sethook(rt_hw_idle_wfi);

#ifdef RT_USING_SMP
    rt_smp_call_init();
    /* Install the IPI handle */
    rt_hw_ipi_handler_install(RT_SCHEDULE_IPI, rt_scheduler_ipi_handler);
    rt_hw_ipi_handler_install(RT_STOP_IPI, rt_scheduler_ipi_handler);
    rt_hw_ipi_handler_install(RT_SMP_CALL_IPI, rt_smp_call_ipi_handler);
    rt_hw_interrupt_umask(RT_SCHEDULE_IPI);
    rt_hw_interrupt_umask(RT_STOP_IPI);
    rt_hw_interrupt_umask(RT_SMP_CALL_IPI);
#endif
}

#ifdef RT_USING_SMP
rt_weak void rt_hw_secondary_cpu_up(void)
{
    int cpu_id = rt_hw_cpu_id();
    rt_uint64_t entry = (rt_uint64_t)rt_kmem_v2p(_secondary_cpu_entry);

    if (!entry)
    {
        LOG_E("Failed to translate '_secondary_cpu_entry' to physical address");
        RT_ASSERT(0);
    }

    /* Maybe we are no in the first cpu */
    for (int i = 0; i < RT_ARRAY_SIZE(cpu_np); ++i)
    {
        int err;
        const char *enable_method;

        if (!cpu_np[i] || i == cpu_id)
        {
            continue;
        }

        err = rt_ofw_prop_read_string(cpu_np[i], "enable-method", &enable_method);

        for (int idx = 0; !err && idx < RT_ARRAY_SIZE(cpu_ops); ++idx)
        {
            struct cpu_ops_t *ops = cpu_ops[idx];

            if (ops->method && !rt_strcmp(ops->method, enable_method) && ops->cpu_boot)
            {
                err = ops->cpu_boot(i, entry);

                break;
            }
        }

        if (err)
        {
            LOG_W("Call cpu %d on %s", i, "failed");
        }
    }
}

rt_weak void rt_hw_secondary_cpu_bsp_start(void)
{
    int cpu_id = rt_hw_cpu_id();

    system_vectors_init();

    rt_hw_spin_lock(&_cpus_lock);

    /* Save all mpidr */
    rt_hw_sysreg_read(mpidr_el1, rt_cpu_mpidr_table[cpu_id]);

    rt_hw_mmu_ktbl_set((unsigned long)MMUTable);

#ifdef RT_USING_PIC
    rt_pic_irq_init();
#else
    /* initialize vector table */
    rt_hw_vector_init();

    arm_gic_cpu_init(0, 0);
#ifdef BSP_USING_GICV3
    arm_gic_redist_init(0, 0);
#endif /* BSP_USING_GICV3 */
#endif

#ifndef RT_HWTIMER_ARM_ARCH
    /* initialize timer for os tick */
    rt_hw_gtimer_local_enable();
#endif /* !RT_HWTIMER_ARM_ARCH */

    rt_dm_secondary_cpu_init();

    rt_hw_interrupt_umask(RT_SCHEDULE_IPI);
    rt_hw_interrupt_umask(RT_STOP_IPI);
    rt_hw_interrupt_umask(RT_SMP_CALL_IPI);

    LOG_I("Call cpu %d on %s", cpu_id, "success");

#ifdef RT_USING_HWTIMER
    if (rt_device_hwtimer_us_delay == &cpu_us_delay)
    {
        cpu_loops_per_tick_init();
    }
#endif

    rt_system_scheduler_start();
}

rt_weak void rt_hw_secondary_cpu_idle_exec(void)
{
    rt_hw_wfe();
}
#endif

void rt_hw_console_output(const char *str)
{
    rt_fdt_earlycon_output(str);
}
