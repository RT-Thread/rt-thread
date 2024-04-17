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

#include <cpu.h>
#include <mmu.h>
#include <cpuport.h>
#include <interrupt.h>
#include <gtimer.h>
#include <setup.h>
#include <stdlib.h>
#include <ioremap.h>
#include <rtdevice.h>

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

rt_inline rt_bool_t is_kernel_aspace(const char *name)
{
    static char * const names[] =
    {
        "kernel",
        "memheap",
    };

    if (!name)
    {
        return RT_FALSE;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(names); ++i)
    {
        if (!rt_strcmp(names[i], name))
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

void rt_hw_common_setup(void)
{
    rt_size_t mem_region_nr;
    rt_region_t *mem_region;
    rt_size_t page_best_start;
    rt_region_t platform_mem_region;
    static struct mem_desc platform_mem_desc;
    void *kernel_start, *kernel_end, *memheap_start = RT_NULL, *memheap_end = RT_NULL;

    system_vectors_init();

#ifdef RT_USING_SMART
    rt_hw_mmu_map_init(&rt_kernel_space, (void*)0xfffffffff0000000, 0x10000000, MMUTable, PV_OFFSET);
#else
    rt_hw_mmu_map_init(&rt_kernel_space, (void*)0xffffd0000000, 0x10000000, MMUTable, 0);
#endif

    kernel_start = rt_kmem_v2p((void *)&_start) - 64;
    kernel_end   = rt_kmem_v2p((void *)&_end);

    if (!rt_fdt_commit_memregion_request(&mem_region, &mem_region_nr, RT_TRUE))
    {
        const char *name = "memheap";

        while (mem_region_nr --> 0)
        {
            if (mem_region->name == name || !rt_strcmp(mem_region->name, name))
            {
                memheap_start = (void *)mem_region->start;
                memheap_end = (void *)mem_region->end;

                break;
            }
            mem_region++;
        }
    }

    page_best_start = (rt_size_t)(memheap_end ? : kernel_end);

    if (memheap_end && fdt_ptr > kernel_start)
    {
        rt_memmove(memheap_end - PV_OFFSET, fdt_ptr - PV_OFFSET, fdt_size);

        fdt_ptr = memheap_end;

        page_best_start = (rt_size_t)fdt_ptr + fdt_size;
    }

    rt_fdt_commit_memregion_early(&(rt_region_t)
    {
        .name = "fdt",
        .start = (rt_size_t)fdt_ptr,
        .end = (rt_size_t)(fdt_ptr + fdt_size),
    }, RT_TRUE);

    fdt_ptr -= PV_OFFSET;

    rt_fdt_commit_memregion_early(&(rt_region_t)
    {
        .name = "kernel",
        .start = (rt_size_t)kernel_start,
        .end = (rt_size_t)kernel_end,
    }, RT_TRUE);

    if (rt_fdt_prefetch(fdt_ptr))
    {
        /* Platform cannot be initialized */
        RT_ASSERT(0);
    }

    rt_fdt_scan_chosen_stdout();

    rt_fdt_scan_initrd(initrd_ranges);

    rt_fdt_scan_memory();

    if (memheap_start && memheap_end)
    {
        rt_system_heap_init(memheap_start - PV_OFFSET, memheap_end - PV_OFFSET);
    }

    platform_mem_region.start = ~0UL;
    platform_mem_region.end = 0;

    if (!rt_fdt_commit_memregion_request(&mem_region, &mem_region_nr, RT_TRUE))
    {
        LOG_I("Reserved memory:");

        while (mem_region_nr --> 0)
        {
            if (is_kernel_aspace(mem_region->name))
            {
                if (platform_mem_region.start > mem_region->start)
                {
                    platform_mem_region.start = mem_region->start;
                }

                if (platform_mem_region.end < mem_region->end)
                {
                    platform_mem_region.end = mem_region->end;
                }
            }

            LOG_I("  %-*.s [%p, %p]", RT_NAME_MAX, mem_region->name, mem_region->start, mem_region->end);

            ++mem_region;
        }
    }

    if (!rt_fdt_commit_memregion_request(&mem_region, &mem_region_nr, RT_FALSE))
    {
        rt_ubase_t best_offset = ~0UL;
        rt_region_t *usable_mem_region = mem_region, *page_region = RT_NULL, init_page_region = { 0 };

        LOG_I("Usable memory:");

        for (int i = 0; i < mem_region_nr; ++i, ++mem_region)
        {
            if (!mem_region->name)
            {
                continue;
            }

            if (platform_mem_region.start > mem_region->start)
            {
                platform_mem_region.start = mem_region->start;
            }

            if (platform_mem_region.end < mem_region->end)
            {
                platform_mem_region.end = mem_region->end;
            }

            if (mem_region->start >= page_best_start &&
                mem_region->start - page_best_start < best_offset &&
                /* MUST >= 1MB */
                mem_region->end - mem_region->start >= SIZE_MB)
            {
                page_region = mem_region;

                best_offset = page_region->start - page_best_start;
            }

            LOG_I("  %-*.s [%p, %p]", RT_NAME_MAX, mem_region->name, mem_region->start, mem_region->end);

        }

        RT_ASSERT(page_region != RT_NULL);

        init_page_region.start = page_region->start - PV_OFFSET;
        init_page_region.end = page_region->end - PV_OFFSET;

        rt_page_init(init_page_region);

        platform_mem_region.start = RT_ALIGN(platform_mem_region.start, ARCH_PAGE_SIZE);
        platform_mem_region.end = RT_ALIGN_DOWN(platform_mem_region.end, ARCH_PAGE_SIZE);
        RT_ASSERT(platform_mem_region.end - platform_mem_region.start != 0);

        platform_mem_desc.paddr_start = platform_mem_region.start;
        platform_mem_desc.vaddr_start = platform_mem_region.start - PV_OFFSET;
        platform_mem_desc.vaddr_end = platform_mem_region.end - PV_OFFSET - 1;
        platform_mem_desc.attr = NORMAL_MEM;

        rt_hw_mmu_setup(&rt_kernel_space, &platform_mem_desc, 1);

        rt_fdt_earlycon_kick(FDT_EARLYCON_KICK_UPDATE);

        mem_region = usable_mem_region;

        for (int i = 0; i < mem_region_nr; ++i, ++mem_region)
        {
            if (mem_region != page_region && mem_region->name)
            {
                mem_region->start -= PV_OFFSET;
                mem_region->end -= PV_OFFSET;
                rt_page_install(*mem_region);
            }
        }
    }

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

    /* initialize timer for os tick */
    rt_hw_gtimer_init();
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_ofw_console_setup();
#endif

    rt_thread_idle_sethook(rt_hw_idle_wfi);

#ifdef RT_USING_SMP
    /* Install the IPI handle */
    rt_hw_ipi_handler_install(RT_SCHEDULE_IPI, rt_scheduler_ipi_handler);
    rt_hw_ipi_handler_install(RT_STOP_IPI, rt_scheduler_ipi_handler);
    rt_hw_interrupt_umask(RT_SCHEDULE_IPI);
    rt_hw_interrupt_umask(RT_STOP_IPI);
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
    rt_hw_interrupt_init();
#endif

    rt_dm_secondary_cpu_init();

    rt_hw_interrupt_umask(RT_SCHEDULE_IPI);
    rt_hw_interrupt_umask(RT_STOP_IPI);

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
