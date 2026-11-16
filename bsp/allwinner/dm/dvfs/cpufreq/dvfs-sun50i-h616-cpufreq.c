/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "dvfs.h616-cpu"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct rt_dvfs_cpufreq *h616_cpufreq;
#ifdef RT_THERMAL_COOL_DVFS
static struct rt_platform_device *h616_cool_pdev;
#endif

static void h616_cpufreq_destroy(struct rt_platform_device *pdev,
                                 struct rt_dvfs_cpufreq *cpufreq)
{
    struct rt_dvfs_scaling *scaling = rt_dvfs_cpufreq_to_scaling(cpufreq);

    if (scaling->opp_table)
    {
        rt_dvfs_scaling_remove_opp_all(scaling);
        rt_free(scaling->opp_table);
    }
    if (scaling->clk)
    {
        rt_clk_put(scaling->clk);
    }
    if (scaling->supply)
    {
        rt_regulator_put(scaling->supply);
    }
    if (pdev)
    {
        if (pdev->parent.ofw_node)
        {
            rt_ofw_node_put(pdev->parent.ofw_node);
        }
        rt_free(pdev);
    }
    rt_free(cpufreq);
}

static void h616_cpufreq_fill_cpu_map(struct rt_dvfs_cpufreq *cpufreq)
{
    struct rt_ofw_node *np = RT_NULL;

    rt_ofw_foreach_cpu_node(np)
    {
        rt_uint32_t cpu;

        if (!rt_ofw_prop_read_u32(np, "reg", &cpu) && cpu < RT_CPUS_NR)
        {
            rt_bitmap_set_bit(cpufreq->cpus_map, cpu);
        }
    }
}

#ifdef RT_THERMAL_COOL_DVFS
static void h616_cpufreq_register_cooling(struct rt_ofw_node *cpu_np,
                                          struct rt_dvfs_scaling *scaling)
{
    struct rt_platform_device *cool;
    rt_err_t err;

    if (!rt_ofw_prop_read_bool(cpu_np, "#cooling-cells"))
    {
        return;
    }
    cool = rt_platform_device_alloc("dvfs-cool");
    if (!cool)
    {
        LOG_W("allocate DVFS cooling device failed");
        return;
    }
    cool->parent.ofw_node = rt_ofw_node_get(cpu_np);
    cool->priv = scaling;
    if ((err = rt_platform_device_register(cool)))
    {
        LOG_W("register DVFS cooling device failed: %s", rt_strerror(err));
        rt_ofw_node_put(cool->parent.ofw_node);
        rt_free(cool);
        return;
    }
    h616_cool_pdev = cool;
}
#endif

static int h616_cpufreq_init(void)
{
    struct rt_platform_device *pdev;
    struct rt_dvfs_scaling *scaling;
    struct rt_ofw_node *cpu_np;
    struct rt_clk *clk;
    rt_err_t err;

    if (h616_cpufreq)
    {
        return 0;
    }
    cpu_np = rt_ofw_get_next_cpu_node(RT_NULL);
    if (!cpu_np)
    {
        LOG_W("no enabled CPU node, skip CPUfreq");
        return 0;
    }
    if (!(pdev = rt_platform_device_alloc("ofw-cpufreq")) ||
        !(h616_cpufreq = rt_calloc(1, sizeof(*h616_cpufreq))))
    {
        if (pdev)
        {
            rt_free(pdev);
        }
        rt_ofw_node_put(cpu_np);
        h616_cpufreq = RT_NULL;
        return 0;
    }

    pdev->priv = h616_cpufreq;
    pdev->parent.ofw_node = cpu_np;
    rt_dm_dev_set_name_auto(&pdev->parent, "cpufreq");
    h616_cpufreq_fill_cpu_map(h616_cpufreq);
    scaling = rt_dvfs_cpufreq_to_scaling(h616_cpufreq);
    scaling->transition_latency = 250000;
    scaling->retry_delay = 100000;

    if ((err = rt_device_register(&pdev->parent,
                                  rt_dm_dev_get_name(&pdev->parent), RT_DEVICE_FLAG_DEACTIVATE)))
    {
        LOG_W("register CPUfreq device failed: %s", rt_strerror(err));
        h616_cpufreq_destroy(pdev, h616_cpufreq);
        h616_cpufreq = RT_NULL;
        return 0;
    }
    clk = rt_clk_get_by_index(&pdev->parent, 0);
    if (rt_is_err_or_null(clk))
    {
        LOG_W("CPU clock is unavailable");
        rt_device_unregister(&pdev->parent);
        h616_cpufreq_destroy(pdev, h616_cpufreq);
        h616_cpufreq = RT_NULL;
        return 0;
    }
    scaling->clk = clk;
    /* Prevent generic OPP setup from changing the U-Boot boot rate. */
    scaling->cur_freq = rt_clk_get_rate(clk);
    if ((err = rt_platform_device_register(pdev)))
    {
        LOG_W("initialize CPUfreq failed: %s", rt_strerror(err));
        rt_device_unregister(&pdev->parent);
        h616_cpufreq_destroy(pdev, h616_cpufreq);
        h616_cpufreq = RT_NULL;
        return 0;
    }
    if (!pdev->parent.drv)
    {
        LOG_W("CPUfreq framework driver is unavailable");
        rt_bus_remove_device(&pdev->parent);
        rt_device_unregister(&pdev->parent);
        h616_cpufreq_destroy(pdev, h616_cpufreq);
        h616_cpufreq = RT_NULL;
        return 0;
    }

    if (scaling->opp_table)
    {
        struct rt_dvfs_opp *opp = rt_dvfs_scaling_find_opp(scaling,
                                                           scaling->cur_freq);

        if (opp)
        {
            scaling->opp_table->current_opp = opp;
        }
        else
        {
            LOG_W("boot CPU rate %lu Hz is outside the OPP table",
                  scaling->cur_freq);
        }
    }
#ifdef RT_THERMAL_COOL_DVFS
    h616_cpufreq_register_cooling(cpu_np, scaling);
#endif

    if ((err = rt_dvfs_scaling_set_governor(scaling,
                                            RT_DVFS_GOVERNOR_TYPE_ONDEMAND)))
    {
        LOG_W("set ondemand governor failed: %s", rt_strerror(err));
        rt_dvfs_scaling_set_governor(scaling, RT_DVFS_GOVERNOR_TYPE_PERFORMANCE);
    }
    LOG_D("CPUfreq ready: %lu Hz, %lu-%lu Hz", scaling->cur_freq,
          scaling->min_freq, scaling->max_freq);
    return 0;
}
INIT_APP_EXPORT(h616_cpufreq_init);
