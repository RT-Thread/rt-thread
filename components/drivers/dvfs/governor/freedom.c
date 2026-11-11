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

#define DBG_TAG "dvfs.governor.freedom"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* Freedom governor: user-controlled frequency, no automatic adjustment */
static rt_err_t governor_freedom_start(struct rt_dvfs_scaling *dvfs)
{
    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    /* Keep current frequency, no automatic adjustment */
    LOG_D("%s: freedom governor started at %lu Hz",
          rt_dm_dev_get_name(dvfs->dev), dvfs->cur_freq);

    return RT_EOK;
}

static rt_err_t governor_freedom_stop(struct rt_dvfs_scaling *dvfs)
{
    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    LOG_D("%s: freedom governor stopped", rt_dm_dev_get_name(dvfs->dev));

    return RT_EOK;
}

static rt_err_t governor_freedom_suspend(struct rt_dvfs_scaling *dvfs)
{
    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    /* Nothing special for suspend */
    return RT_EOK;
}

static rt_err_t governor_freedom_resume(struct rt_dvfs_scaling *dvfs)
{
    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    /* Restore to current frequency */
    return rt_dvfs_scaling_set_frequency(dvfs, dvfs->cur_freq);
}

static rt_err_t governor_freedom_set_interval(struct rt_dvfs_scaling *dvfs, rt_uint32_t interval_ms)
{
    /* Freedom governor doesn't use sampling interval */
    return -RT_ENOSYS;
}

static rt_err_t governor_freedom_set_frequency(struct rt_dvfs_scaling *dvfs, rt_ubase_t *out_freq)
{
    if (!dvfs || !out_freq)
    {
        return -RT_EINVAL;
    }

    /* Return current frequency (user-controlled) */
    *out_freq = dvfs->cur_freq;

    return RT_EOK;
}

static struct rt_dvfs_governor governor_freedom =
{
    .name = "freedom",
    .type = RT_DVFS_GOVERNOR_TYPE_FREEDOM,

    .start = governor_freedom_start,
    .stop = governor_freedom_stop,
    .suspend = governor_freedom_suspend,
    .resume = governor_freedom_resume,
    .set_interval = governor_freedom_set_interval,
    .set_frequency = governor_freedom_set_frequency,
};

static int governor_freedom_init(void)
{
    rt_dvfs_governor_register(&governor_freedom);

    return 0;
}
INIT_CORE_EXPORT(governor_freedom_init);
