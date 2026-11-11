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

#define DBG_TAG "dvfs.governor.schedutil"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* Default parameters */
#define SCHEDUTIL_DEFAULT_SAMPLING_RATE_MS    500
#define SCHEDUTIL_UP_THRESHOLD                85
#define SCHEDUTIL_DOWN_DIFFERENTIAL           20

struct governor_schedutil_data
{
    struct rt_work monitor_work;
    rt_bool_t running;
};

static rt_bool_t governor_schedutil_active(struct rt_dvfs_scaling *dvfs)
{
    struct governor_schedutil_data *data;

    if (!dvfs || !dvfs->gov ||
            dvfs->gov->type != RT_DVFS_GOVERNOR_TYPE_SCHEDUTIL)
    {
        return RT_FALSE;
    }

    data = dvfs->gov_data;

    return data && data->running;
}

static void governor_schedutil_monitor(struct rt_work *work, void *work_data)
{
    struct rt_dvfs_scaling *dvfs = (struct rt_dvfs_scaling *)work_data;
    struct governor_schedutil_data *data;
    struct rt_dvfs_opp *opp;
    rt_ubase_t target_freq;
    rt_uint32_t load;

    if (!governor_schedutil_active(dvfs))
    {
        return;
    }

    data = dvfs->gov_data;

    /* Update CPU load statistics */
    rt_dvfs_load_update(dvfs);
    load = rt_dvfs_cpu_load_get(&dvfs->cpu_load);

    /*
     * Schedutil uses scheduler's utilization estimate.
     * For RT-Thread, we use CPU load as approximation.
     * In a full implementation, this would hook into the scheduler
     * to get actual utilization metrics.
     */
    if (load >= SCHEDUTIL_UP_THRESHOLD)
    {
        /* High utilization: use max frequency */
        target_freq = dvfs->max_freq;
    }
    else
    {
        /* Scale frequency proportionally to load */
        target_freq = dvfs->max_freq * load / 100;

        /* Find floor OPP */
        opp = rt_dvfs_scaling_find_floor_opp(dvfs, target_freq);
        if (opp && opp->available)
        {
            target_freq = opp->freq;
        }
        else
        {
            target_freq = dvfs->min_freq;
        }
    }

    LOG_D("%s: schedutil load=%u%%, target_freq=%lu Hz",
          rt_dm_dev_get_name(dvfs->dev), load, target_freq);

    /* Set target frequency if different */
    if (target_freq != dvfs->cur_freq && governor_schedutil_active(dvfs))
    {
        rt_err_t err = rt_dvfs_scaling_set_frequency(dvfs, target_freq);
        if (err)
        {
            LOG_W("%s: set frequency %lu failed: %s",
                  rt_dm_dev_get_name(dvfs->dev), target_freq, rt_strerror(err));
        }
    }

    /* Reschedule monitoring work */
    if (governor_schedutil_active(dvfs))
    {
        rt_work_submit(&data->monitor_work,
                       rt_tick_from_millisecond(dvfs->gov_params.sampling_rate_ms));
    }
}

static rt_err_t governor_schedutil_start(struct rt_dvfs_scaling *dvfs)
{
    struct governor_schedutil_data *data;

    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    /* Initialize default parameters if not set */
    if (dvfs->gov_params.sampling_rate_ms == 0)
    {
        dvfs->gov_params.sampling_rate_ms = SCHEDUTIL_DEFAULT_SAMPLING_RATE_MS;
    }

    /* Allocate governor data */
    data = rt_calloc(1, sizeof(*data));
    if (!data)
    {
        LOG_E("%s: no memory for schedutil data", rt_dm_dev_get_name(dvfs->dev));
        return -RT_ENOMEM;
    }

    dvfs->gov_data = data;
    data->running = RT_TRUE;

    /* Initialize CPU load */
    dvfs->cpu_load.last_update = rt_tick_get();
    dvfs->cpu_load.total_tick = 0;
    dvfs->cpu_load.idle_tick = 0;
    dvfs->cpu_load.load_percentage = 0;

    /* Initialize monitoring work */
    rt_work_init(&data->monitor_work, governor_schedutil_monitor, dvfs);

    /* Submit first monitoring work */
    rt_work_submit(&data->monitor_work,
                   rt_tick_from_millisecond(dvfs->gov_params.sampling_rate_ms));

    LOG_D("%s: schedutil governor started (sampling=%ums)",
          rt_dm_dev_get_name(dvfs->dev), dvfs->gov_params.sampling_rate_ms);

    return RT_EOK;
}

static rt_err_t governor_schedutil_stop(struct rt_dvfs_scaling *dvfs)
{
    struct governor_schedutil_data *data;

    if (!dvfs || !dvfs->gov)
    {
        return -RT_EINVAL;
    }

    data = dvfs->gov_data;
    if (data)
    {
        data->running = RT_FALSE;
        rt_work_cancel(&data->monitor_work);

        /* Wait for work to complete */
        rt_thread_mdelay(10);

        rt_free(data);
        dvfs->gov_data = RT_NULL;
    }

    LOG_D("%s: schedutil governor stopped", rt_dm_dev_get_name(dvfs->dev));

    return RT_EOK;
}

static rt_err_t governor_schedutil_suspend(struct rt_dvfs_scaling *dvfs)
{
    struct governor_schedutil_data *data;

    if (!dvfs || !dvfs->gov)
    {
        return -RT_EINVAL;
    }

    /* Stop monitoring */
    data = dvfs->gov_data;
    if (data)
    {
        data->running = RT_FALSE;
        rt_work_cancel(&data->monitor_work);
    }

    return RT_EOK;
}

static rt_err_t governor_schedutil_resume(struct rt_dvfs_scaling *dvfs)
{
    struct governor_schedutil_data *data;

    if (!dvfs || !dvfs->gov)
    {
        return -RT_EINVAL;
    }

    /* Resume monitoring */
    data = dvfs->gov_data;
    if (data)
    {
        /* Reset CPU load statistics */
        dvfs->cpu_load.last_update = rt_tick_get();
        dvfs->cpu_load.total_tick = 0;
        dvfs->cpu_load.idle_tick = 0;

        data->running = RT_TRUE;
        rt_work_submit(&data->monitor_work,
                       rt_tick_from_millisecond(dvfs->gov_params.sampling_rate_ms));
    }

    return RT_EOK;
}

static rt_err_t governor_schedutil_set_interval(struct rt_dvfs_scaling *dvfs, rt_uint32_t interval_ms)
{
    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    /* Minimum sampling interval: 10ms */
    if (interval_ms < 10)
    {
        interval_ms = 10;
    }

    dvfs->gov_params.sampling_rate_ms = interval_ms;

    LOG_D("%s: schedutil sampling interval set to %ums",
          rt_dm_dev_get_name(dvfs->dev), interval_ms);

    return RT_EOK;
}

static rt_err_t governor_schedutil_set_frequency(struct rt_dvfs_scaling *dvfs, rt_ubase_t *out_freq)
{
    if (!dvfs || !out_freq)
    {
        return -RT_EINVAL;
    }

    /* Schedutil sets frequency based on scheduler utilization */
    /* Return current frequency */
    *out_freq = dvfs->cur_freq;

    return RT_EOK;
}

static struct rt_dvfs_governor governor_schedutil =
{
    .name = "schedutil",
    .type = RT_DVFS_GOVERNOR_TYPE_SCHEDUTIL,

    .start = governor_schedutil_start,
    .stop = governor_schedutil_stop,
    .suspend = governor_schedutil_suspend,
    .resume = governor_schedutil_resume,
    .set_interval = governor_schedutil_set_interval,
    .set_frequency = governor_schedutil_set_frequency,
};

static int governor_schedutil_init(void)
{
    rt_dvfs_governor_register(&governor_schedutil);

    return 0;
}
INIT_CORE_EXPORT(governor_schedutil_init);
