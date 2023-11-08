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

#include <stdlib.h>
#include <ioremap.h>
#include <drivers/ofw.h>
#include <drivers/ofw_fdt.h>
#include <drivers/ofw_raw.h>
#include <drivers/core/dm.h>

#define rt_sysreg_write(sysreg, val) \
    __asm__ volatile ("msr "RT_STRINGIFY(sysreg)", %0"::"r"((rt_uint64_t)(val)))

#define rt_sysreg_read(sysreg, val) \
    __asm__ volatile ("mrs %0, "RT_STRINGIFY(sysreg)"":"=r"((val)))

extern void _secondary_cpu_entry(void);
extern size_t MMUTable[];
extern void *system_vectors;

static void *fdt_ptr = RT_NULL;
static rt_size_t fdt_size = 0;

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
    void *fdt_vaddr = fdt - PV_OFFSET;

    if (fdt != RT_NULL && !fdt_check_header(fdt_vaddr))
    {
        fdt_ptr = fdt_vaddr;
        fdt_size = fdt_totalsize(fdt_vaddr);
    }
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
    rt_sysreg_read(mpidr_el1, mpidr);

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
}

void rt_hw_common_setup(void)
{
    if (rt_fdt_prefetch(fdt_ptr))
    {
        /* Platform cannot be initialized */
        RT_ASSERT(0);
    }

    rt_fdt_unflatten();

    cpu_info_init();
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
    rt_sysreg_read(mpidr_el1, rt_cpu_mpidr_table[cpu_id]);

    rt_hw_mmu_ktbl_set((unsigned long)MMUTable);

    rt_hw_interrupt_init();

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
