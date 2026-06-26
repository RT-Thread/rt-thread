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

#define DBG_TAG "dvfs.governor.performance"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_err_t governor_performance_start(struct rt_dvfs_scaling *dvfs)
{
    rt_err_t err;

    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    /* Set frequency to maximum */
    err = rt_dvfs_scaling_set_frequency(dvfs, dvfs->max_freq);
    if (err)
    {
        LOG_E("%s: set max frequency failed: %s",
              rt_dm_dev_get_name(dvfs->dev), rt_strerror(err));
        return err;
    }

    LOG_D("%s: performance governor started at %lu Hz",
          rt_dm_dev_get_name(dvfs->dev), dvfs->cur_freq);

    return RT_EOK;
}

static rt_err_t governor_performance_stop(struct rt_dvfs_scaling *dvfs)
{
    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    LOG_D("%s: performance governor stopped", rt_dm_dev_get_name(dvfs->dev));

    return RT_EOK;
}

static rt_err_t governor_performance_suspend(struct rt_dvfs_scaling *dvfs)
{
    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    /* Nothing special for suspend */
    return RT_EOK;
}

static rt_err_t governor_performance_resume(struct rt_dvfs_scaling *dvfs)
{
    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    /* Restore to max frequency */
    return rt_dvfs_scaling_set_frequency(dvfs, dvfs->max_freq);
}

static rt_err_t governor_performance_set_interval(struct rt_dvfs_scaling *dvfs, rt_uint32_t interval_ms)
{
    /* Performance governor doesn't use sampling interval */
    return -RT_ENOSYS;
}

static rt_err_t governor_performance_set_frequency(struct rt_dvfs_scaling *dvfs, rt_ubase_t *out_freq)
{
    if (!dvfs || !out_freq)
    {
        return -RT_EINVAL;
    }

    /* Always return max frequency */
    *out_freq = dvfs->max_freq;

    return RT_EOK;
}

static struct rt_dvfs_governor governor_performance =
{
    .name = "performance",
    .type = RT_DVFS_GOVERNOR_TYPE_PERFORMANCE,

    .start = governor_performance_start,
    .stop = governor_performance_stop,
    .suspend = governor_performance_suspend,
    .resume = governor_performance_resume,
    .set_interval = governor_performance_set_interval,
    .set_frequency = governor_performance_set_frequency,
};

static int governor_performance_init(void)
{
    rt_dvfs_governor_register(&governor_performance);

    return 0;
}
INIT_CORE_EXPORT(governor_performance_init);
