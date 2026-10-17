/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <drivers/dvfs.h>

#define DBG_TAG "dvfs.f101-cpu"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct rt_device sun252i_f101_cpufreq_dev;
static struct rt_dvfs_cpufreq sun252i_f101_cpufreq;

static int sun252i_f101_cpufreq_init(void)
{
    rt_err_t err;
    struct rt_clk *clk;
    struct rt_dvfs_scaling *scaling;
    struct rt_ofw_node *cpu_np;

    cpu_np = rt_ofw_get_next_cpu_node(RT_NULL);
    if (!cpu_np)
    {
        return 0;
    }

    sun252i_f101_cpufreq_dev.ofw_node = cpu_np;
    if ((err = rt_device_register(&sun252i_f101_cpufreq_dev, "cpufreq0",
            RT_DEVICE_FLAG_DEACTIVATE)))
    {
        LOG_W("register cpufreq device failed: %s", rt_strerror(err));
        rt_ofw_node_put(cpu_np);
        sun252i_f101_cpufreq_dev.ofw_node = RT_NULL;
        return 0;
    }

    if (rt_is_err_or_null(clk = rt_clk_get_by_index(&sun252i_f101_cpufreq_dev, 0)))
    {
        LOG_W("CPU clock is unavailable");
        rt_device_unregister(&sun252i_f101_cpufreq_dev);
        rt_ofw_node_put(cpu_np);
        sun252i_f101_cpufreq_dev.ofw_node = RT_NULL;
        return 0;
    }

    scaling = rt_dvfs_cpufreq_to_scaling(&sun252i_f101_cpufreq);
    scaling->dev = &sun252i_f101_cpufreq_dev;
    scaling->clk = clk;
    scaling->ops = &rt_dvfs_devfreq_ops;
    scaling->transition_latency = 100000;
    sun252i_f101_cpufreq.master_cpu = 0;
    rt_bitmap_set_bit(sun252i_f101_cpufreq.cpus_map, 0);

    /* Keep the bootloader-selected OPP until a governor makes a decision. */
    scaling->cur_freq = rt_clk_get_rate(clk);

    if ((err = rt_dvfs_cpufreq_register(&sun252i_f101_cpufreq)))
    {
        LOG_W("register cpufreq failed: %s", rt_strerror(err));
        rt_clk_put(clk);
        rt_device_unregister(&sun252i_f101_cpufreq_dev);
        rt_ofw_node_put(cpu_np);
        sun252i_f101_cpufreq_dev.ofw_node = RT_NULL;
        return 0;
    }

    if ((err = rt_dvfs_scaling_set_governor(scaling,
            RT_DVFS_GOVERNOR_TYPE_ONDEMAND)))
    {
        LOG_W("set ondemand governor failed: %s", rt_strerror(err));
        rt_dvfs_scaling_set_governor(scaling, RT_DVFS_GOVERNOR_TYPE_PERFORMANCE);
    }

    LOG_D("C907 CPUfreq ready: %lu Hz", scaling->cur_freq);
    return 0;
}
INIT_APP_EXPORT(sun252i_f101_cpufreq_init);
