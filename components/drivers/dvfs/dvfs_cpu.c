/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "dvfs.cpu"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

rt_err_t rt_dvfs_cpufreq_register(struct rt_dvfs_cpufreq *cpufreq)
{
    rt_err_t err;

    if (!cpufreq)
    {
        return -RT_EINVAL;
    }

    err = rt_dvfs_devfreq_register(rt_dvfs_cpufreq_to_devfreq(cpufreq));
    if (err)
    {
        return err;
    }

    LOG_D("CPUfreq registered for device %s",
          rt_dm_dev_get_name(rt_dvfs_cpufreq_to_scaling(cpufreq)->dev));

    return RT_EOK;
}

rt_err_t rt_dvfs_cpufreq_unregister(struct rt_dvfs_cpufreq *cpufreq)
{
    if (!cpufreq)
    {
        return -RT_EINVAL;
    }

    return rt_dvfs_devfreq_unregister(rt_dvfs_cpufreq_to_devfreq(cpufreq));
}
