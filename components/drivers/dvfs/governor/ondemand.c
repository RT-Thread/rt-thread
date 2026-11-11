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

#define DBG_TAG "dvfs.governor.ondemand"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* Default parameters (Linux-like) */
#define ONDEMAND_DEFAULT_SAMPLING_RATE_MS    1000
#define ONDEMAND_DEFAULT_UP_THRESHOLD        80
#define ONDEMAND_DEFAULT_DOWN_DIFFERENTIAL   20
#define ONDEMAND_DEFAULT_IGNORE_NICE         RT_FALSE
#define ONDEMAND_DEFAULT_POWERSAVE_BIAS      0

struct governor_ondemand_data
{
    struct rt_work monitor_work;
    rt_bool_t running;
};

static rt_bool_t governor_ondemand_active(struct rt_dvfs_scaling *dvfs)
{
    struct governor_ondemand_data *data;

    if (!dvfs || !dvfs->gov ||
            dvfs->gov->type != RT_DVFS_GOVERNOR_TYPE_ONDEMAND)
    {
        return RT_FALSE;
    }

    data = dvfs->gov_data;

    return data && data->running;
}

static void governor_ondemand_monitor(struct rt_work *work, void *work_data)
{
    struct rt_dvfs_scaling *dvfs = (struct rt_dvfs_scaling *)work_data;
    struct governor_ondemand_data *data;
    struct rt_dvfs_opp *opp;
    rt_ubase_t target_freq;
    rt_uint32_t load;

    if (!governor_ondemand_active(dvfs))
    {
        return;
    }

    data = dvfs->gov_data;

    /* Update CPU load statistics */
    rt_dvfs_load_update(dvfs);
    load = rt_dvfs_cpu_load_get(&dvfs->cpu_load);

    /* Determine target frequency based on load */
    if (load >= dvfs->gov_params.up_threshold)
    {
        /* High load: jump to max frequency */
        target_freq = dvfs->max_freq;
        LOG_D("%s: load=%u%% >= threshold=%u%%, set max freq",
              rt_dm_dev_get_name(dvfs->dev), load,
              dvfs->gov_params.up_threshold);
    }
    else if (load < dvfs->gov_params.down_differential)
    {
        /* Low load: find appropriate frequency */
        rt_ubase_t freq_target = (dvfs->cur_freq * load) / 100;

        /* Apply powersave bias if configured */
        if (dvfs->gov_params.powersave_bias > 0)
        {
            freq_target = freq_target * (100 - dvfs->gov_params.powersave_bias) / 100;
        }

        /* Find floor OPP (next lower or equal frequency) */
        opp = rt_dvfs_scaling_find_floor_opp(dvfs, freq_target);
        if (opp && opp->available)
        {
            target_freq = opp->freq;
        }
        else
        {
            target_freq = dvfs->min_freq;
        }

        LOG_D("%s: load=%u%% < diff=%u%%, target=%lu Hz",
              rt_dm_dev_get_name(dvfs->dev), load,
              dvfs->gov_params.down_differential, target_freq);
    }
    else
    {
        /* Medium load: keep current frequency */
        target_freq = dvfs->cur_freq;
    }

    /* Set target frequency if different */
    if (target_freq != dvfs->cur_freq && governor_ondemand_active(dvfs))
    {
        rt_err_t err = rt_dvfs_scaling_set_frequency(dvfs, target_freq);
        if (err)
        {
            LOG_W("%s: set frequency %lu failed: %s",
                  rt_dm_dev_get_name(dvfs->dev), target_freq, rt_strerror(err));
        }
    }

    /* Reschedule monitoring work */
    if (governor_ondemand_active(dvfs))
    {
        rt_work_submit(&data->monitor_work,
                       rt_tick_from_millisecond(dvfs->gov_params.sampling_rate_ms));
    }
}

static rt_err_t governor_ondemand_start(struct rt_dvfs_scaling *dvfs)
{
    struct governor_ondemand_data *data;

    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    /* Initialize default parameters if not set */
    if (dvfs->gov_params.sampling_rate_ms == 0)
    {
        dvfs->gov_params.sampling_rate_ms = ONDEMAND_DEFAULT_SAMPLING_RATE_MS;
    }
    if (dvfs->gov_params.up_threshold == 0)
    {
        dvfs->gov_params.up_threshold = ONDEMAND_DEFAULT_UP_THRESHOLD;
    }
    if (dvfs->gov_params.down_differential == 0)
    {
        dvfs->gov_params.down_differential = ONDEMAND_DEFAULT_DOWN_DIFFERENTIAL;
    }
    if (dvfs->gov_params.ignore_nice_load == 0)
    {
        dvfs->gov_params.ignore_nice_load = ONDEMAND_DEFAULT_IGNORE_NICE;
    }
    if (dvfs->gov_params.powersave_bias == 0)
    {
        dvfs->gov_params.powersave_bias = ONDEMAND_DEFAULT_POWERSAVE_BIAS;
    }

    /* Allocate governor data */
    data = rt_calloc(1, sizeof(*data));
    if (!data)
    {
        LOG_E("%s: no memory for ondemand data", rt_dm_dev_get_name(dvfs->dev));
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
    rt_work_init(&data->monitor_work, governor_ondemand_monitor, dvfs);

    /* Submit first monitoring work */
    rt_work_submit(&data->monitor_work,
                   rt_tick_from_millisecond(dvfs->gov_params.sampling_rate_ms));

    LOG_D("%s: ondemand governor started (sampling=%ums, up_threshold=%u%%, down_diff=%u%%)",
          rt_dm_dev_get_name(dvfs->dev),
          dvfs->gov_params.sampling_rate_ms,
          dvfs->gov_params.up_threshold,
          dvfs->gov_params.down_differential);

    return RT_EOK;
}

static rt_err_t governor_ondemand_stop(struct rt_dvfs_scaling *dvfs)
{
    struct governor_ondemand_data *data;

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

    LOG_D("%s: ondemand governor stopped", rt_dm_dev_get_name(dvfs->dev));

    return RT_EOK;
}

static rt_err_t governor_ondemand_suspend(struct rt_dvfs_scaling *dvfs)
{
    struct governor_ondemand_data *data;

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

static rt_err_t governor_ondemand_resume(struct rt_dvfs_scaling *dvfs)
{
    struct governor_ondemand_data *data;

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

static rt_err_t governor_ondemand_set_interval(struct rt_dvfs_scaling *dvfs, rt_uint32_t interval_ms)
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

    LOG_D("%s: ondemand sampling interval set to %ums",
          rt_dm_dev_get_name(dvfs->dev), interval_ms);

    return RT_EOK;
}

static rt_err_t governor_ondemand_set_frequency(struct rt_dvfs_scaling *dvfs, rt_ubase_t *out_freq)
{
    if (!dvfs || !out_freq)
    {
        return -RT_EINVAL;
    }

    /* Ondemand sets frequency based on load, not requested frequency */
    /* Return current frequency */
    *out_freq = dvfs->cur_freq;

    return RT_EOK;
}

static struct rt_dvfs_governor governor_ondemand =
{
    .name = "ondemand",
    .type = RT_DVFS_GOVERNOR_TYPE_ONDEMAND,

    .start = governor_ondemand_start,
    .stop = governor_ondemand_stop,
    .suspend = governor_ondemand_suspend,
    .resume = governor_ondemand_resume,
    .set_interval = governor_ondemand_set_interval,
    .set_frequency = governor_ondemand_set_frequency,
};

static int governor_ondemand_init(void)
{
    rt_dvfs_governor_register(&governor_ondemand);

    return 0;
}
INIT_CORE_EXPORT(governor_ondemand_init);
