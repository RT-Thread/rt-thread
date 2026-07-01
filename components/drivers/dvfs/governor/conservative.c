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

#define DBG_TAG "dvfs.governor.conservative"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* Default parameters (Linux-like) */
#define CONSERVATIVE_DEFAULT_SAMPLING_RATE_MS       1000
#define CONSERVATIVE_DEFAULT_UP_THRESHOLD           80
#define CONSERVATIVE_DEFAULT_DOWN_DIFFERENTIAL      20
#define CONSERVATIVE_DEFAULT_FREQ_STEP              5
#define CONSERVATIVE_DEFAULT_SAMPLING_DOWN_FACTOR   1

struct governor_conservative_data
{
    struct rt_work monitor_work;
    rt_bool_t running;
};

static rt_bool_t governor_conservative_active(struct rt_dvfs_scaling *dvfs)
{
    struct governor_conservative_data *data;

    if (!dvfs || !dvfs->gov ||
            dvfs->gov->type != RT_DVFS_GOVERNOR_TYPE_CONSERVATIVE)
    {
        return RT_FALSE;
    }

    data = dvfs->gov_data;

    return data && data->running;
}

static void governor_conservative_monitor(struct rt_work *work, void *work_data)
{
    struct rt_dvfs_scaling *dvfs = (struct rt_dvfs_scaling *)work_data;
    struct governor_conservative_data *data;
    struct rt_dvfs_opp *opp;
    rt_ubase_t target_freq;
    rt_uint32_t load;

    if (!governor_conservative_active(dvfs))
    {
        return;
    }

    data = dvfs->gov_data;

    /* Update CPU load statistics */
    rt_dvfs_load_update(dvfs);
    load = rt_dvfs_cpu_load_get(&dvfs->cpu_load);

    target_freq = dvfs->cur_freq;

    /* Determine target frequency based on load */
    if (load >= dvfs->gov_params.up_threshold)
    {
        /* High load: step up frequency */
        rt_ubase_t step_freq = (dvfs->max_freq * dvfs->gov_params.freq_step) / 100;
        target_freq = dvfs->cur_freq + step_freq;

        /* Find ceil OPP */
        opp = rt_dvfs_scaling_find_ceil_opp(dvfs, target_freq);
        if (opp && opp->available && opp->freq > dvfs->cur_freq)
        {
            target_freq = opp->freq;
        }
        else
        {
            target_freq = dvfs->max_freq;
        }

        LOG_D("%s: load=%u%% >= up_threshold=%u%%, step up to %lu Hz",
              rt_dm_dev_get_name(dvfs->dev), load,
              dvfs->gov_params.up_threshold, target_freq);
    }
    else if (load < dvfs->gov_params.down_differential)
    {
        /* Low load: step down frequency */
        rt_ubase_t step_freq = (dvfs->max_freq * dvfs->gov_params.freq_step) / 100;
        target_freq = (dvfs->cur_freq > step_freq) ? (dvfs->cur_freq - step_freq) : dvfs->min_freq;

        /* Find floor OPP */
        opp = rt_dvfs_scaling_find_floor_opp(dvfs, target_freq);
        if (opp && opp->available && opp->freq < dvfs->cur_freq)
        {
            target_freq = opp->freq;
        }
        else
        {
            target_freq = dvfs->min_freq;
        }

        LOG_D("%s: load=%u%% < down_threshold=%u%%, step down to %lu Hz",
              rt_dm_dev_get_name(dvfs->dev), load,
              dvfs->gov_params.down_differential, target_freq);
    }
    else
    {
        /* Medium load: keep current frequency */
        LOG_D("%s: load=%u%% in range, keep freq %lu Hz",
              rt_dm_dev_get_name(dvfs->dev), load, dvfs->cur_freq);
    }

    /* Set target frequency if different */
    if (target_freq != dvfs->cur_freq && governor_conservative_active(dvfs))
    {
        rt_err_t err = rt_dvfs_scaling_set_frequency(dvfs, target_freq);
        if (err)
        {
            LOG_W("%s: set frequency %lu failed: %s",
                  rt_dm_dev_get_name(dvfs->dev), target_freq, rt_strerror(err));
        }
    }

    /* Reschedule monitoring work */
    if (governor_conservative_active(dvfs))
    {
        rt_work_submit(&data->monitor_work,
                       rt_tick_from_millisecond(dvfs->gov_params.sampling_rate_ms));
    }
}

static rt_err_t governor_conservative_start(struct rt_dvfs_scaling *dvfs)
{
    struct governor_conservative_data *data;

    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    /* Initialize default parameters if not set */
    if (dvfs->gov_params.sampling_rate_ms == 0)
    {
        dvfs->gov_params.sampling_rate_ms = CONSERVATIVE_DEFAULT_SAMPLING_RATE_MS;
    }
    if (dvfs->gov_params.up_threshold == 0)
    {
        dvfs->gov_params.up_threshold = CONSERVATIVE_DEFAULT_UP_THRESHOLD;
    }
    if (dvfs->gov_params.down_differential == 0)
    {
        dvfs->gov_params.down_differential = CONSERVATIVE_DEFAULT_DOWN_DIFFERENTIAL;
    }
    if (dvfs->gov_params.freq_step == 0)
    {
        dvfs->gov_params.freq_step = CONSERVATIVE_DEFAULT_FREQ_STEP;
    }
    if (dvfs->gov_params.sampling_down_factor == 0)
    {
        dvfs->gov_params.sampling_down_factor = CONSERVATIVE_DEFAULT_SAMPLING_DOWN_FACTOR;
    }

    /* Allocate governor data */
    data = rt_calloc(1, sizeof(*data));
    if (!data)
    {
        LOG_E("%s: no memory for conservative data", rt_dm_dev_get_name(dvfs->dev));
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
    rt_work_init(&data->monitor_work, governor_conservative_monitor, dvfs);

    /* Submit first monitoring work */
    rt_work_submit(&data->monitor_work,
                   rt_tick_from_millisecond(dvfs->gov_params.sampling_rate_ms));

    LOG_D("%s: conservative governor started (sampling=%ums, up_threshold=%u%%, down_threshold=%u%%, freq_step=%u%%)",
          rt_dm_dev_get_name(dvfs->dev),
          dvfs->gov_params.sampling_rate_ms,
          dvfs->gov_params.up_threshold,
          dvfs->gov_params.down_differential,
          dvfs->gov_params.freq_step);

    return RT_EOK;
}

static rt_err_t governor_conservative_stop(struct rt_dvfs_scaling *dvfs)
{
    struct governor_conservative_data *data;

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

    LOG_D("%s: conservative governor stopped", rt_dm_dev_get_name(dvfs->dev));

    return RT_EOK;
}

static rt_err_t governor_conservative_suspend(struct rt_dvfs_scaling *dvfs)
{
    struct governor_conservative_data *data;

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

static rt_err_t governor_conservative_resume(struct rt_dvfs_scaling *dvfs)
{
    struct governor_conservative_data *data;

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

static rt_err_t governor_conservative_set_interval(struct rt_dvfs_scaling *dvfs, rt_uint32_t interval_ms)
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

    LOG_D("%s: conservative sampling interval set to %ums",
          rt_dm_dev_get_name(dvfs->dev), interval_ms);

    return RT_EOK;
}

static rt_err_t governor_conservative_set_frequency(struct rt_dvfs_scaling *dvfs, rt_ubase_t *out_freq)
{
    if (!dvfs || !out_freq)
    {
        return -RT_EINVAL;
    }

    /* Conservative sets frequency based on load, not requested frequency */
    /* Return current frequency */
    *out_freq = dvfs->cur_freq;

    return RT_EOK;
}

static struct rt_dvfs_governor governor_conservative =
{
    .name = "conservative",
    .type = RT_DVFS_GOVERNOR_TYPE_CONSERVATIVE,

    .start = governor_conservative_start,
    .stop = governor_conservative_stop,
    .suspend = governor_conservative_suspend,
    .resume = governor_conservative_resume,
    .set_interval = governor_conservative_set_interval,
    .set_frequency = governor_conservative_set_frequency,
};

static int governor_conservative_init(void)
{
    rt_dvfs_governor_register(&governor_conservative);

    return 0;
}
INIT_CORE_EXPORT(governor_conservative_init);
