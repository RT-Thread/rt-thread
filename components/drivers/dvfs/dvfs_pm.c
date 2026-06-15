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

#define DBG_TAG "dvfs.pm"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

rt_err_t rt_dvfs_scaling_pm_suspend(struct rt_device_pm *device_pm, rt_uint8_t mode)
{
    struct rt_dvfs_scaling *dvfs = device_pm->device->dvfs_scaling;

    if (!dvfs)
    {
        return RT_EOK;
    }

    return rt_dvfs_scaling_suspend(dvfs);
}

rt_err_t rt_dvfs_scaling_pm_resume(struct rt_device_pm *device_pm, rt_uint8_t mode)
{
    struct rt_dvfs_scaling *dvfs = device_pm->device->dvfs_scaling;

    if (!dvfs)
    {
        return RT_EOK;
    }

    return rt_dvfs_scaling_resume(dvfs);
}

rt_err_t rt_dvfs_scaling_pm_frequency_change(struct rt_device_pm *device_pm, rt_uint8_t mode)
{
    rt_uint32_t governor_type = RT_DVFS_GOVERNOR_TYPE_ONDEMAND;
    struct rt_dvfs_scaling *dvfs = device_pm->device->dvfs_scaling;

    if (!dvfs)
    {
        return RT_EOK;
    }

    rt_dvfs_scaling_enter(dvfs);

    if (dvfs->gov)
    {
        governor_type = dvfs->gov->type;
    }

    rt_dvfs_scaling_leave(dvfs);

    if (governor_type == RT_DVFS_GOVERNOR_TYPE_FREEDOM)
    {
        switch (mode)
        {
        case PM_RUN_MODE_HIGH_SPEED:
            return rt_dvfs_scaling_set_frequency(dvfs, dvfs->max_freq);

        case PM_RUN_MODE_NORMAL_SPEED:
            /*
             * It's not a good idea, but the OPP doesn't seem to have defaults.
             */
            return rt_dvfs_scaling_set_frequency(dvfs, (dvfs->max_freq + dvfs->min_freq) / 2);

        case PM_RUN_MODE_MEDIUM_SPEED:
            return rt_dvfs_scaling_set_frequency(dvfs, dvfs->suspend_freq);

        case PM_RUN_MODE_LOW_SPEED:
            return rt_dvfs_scaling_set_frequency(dvfs, dvfs->min_freq);

        default:
            break;
        }
    }
    else
    {
        switch (mode)
        {
        case PM_RUN_MODE_HIGH_SPEED:
            return rt_dvfs_scaling_set_governor(dvfs, RT_DVFS_GOVERNOR_TYPE_PERFORMANCE);

        case PM_RUN_MODE_NORMAL_SPEED:
            return rt_dvfs_scaling_set_governor(dvfs, RT_DVFS_GOVERNOR_TYPE_ONDEMAND);

        case PM_RUN_MODE_MEDIUM_SPEED:
            return rt_dvfs_scaling_set_governor(dvfs, RT_DVFS_GOVERNOR_TYPE_CONSERVATIVE);

        case PM_RUN_MODE_LOW_SPEED:
            return rt_dvfs_scaling_set_governor(dvfs, RT_DVFS_GOVERNOR_TYPE_POWERSAVE);

        default:
            break;
        }
    }

    return -RT_EINVAL;
}
