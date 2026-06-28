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

#define DBG_TAG "rtdm.dvfs"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static RT_DEFINE_SPINLOCK(_dvfs_scaling_lock);

#ifdef RT_USING_OFW
static rt_err_t dvfs_ofw_parse_opp(struct rt_dvfs_scaling *dvfs)
{
    struct rt_dvfs_opp *opp;
    struct rt_ofw_node *opp_np, *opp_child_np;

    if (!dvfs->dev->ofw_node)
    {
        return RT_EOK;
    }

    opp_np = rt_ofw_parse_phandle(dvfs->dev->ofw_node, "operating-points-v2", 0);

    if (!opp_np)
    {
        return RT_EOK;
    }

    rt_ofw_foreach_child_node(opp_np, opp_child_np)
    {
        rt_uint64_t hz = 0;
        rt_uint32_t uvolt[3] = {0}, uvolt_nr = 0;

        if (rt_ofw_prop_read_u64(opp_child_np, "opp-hz", &hz))
        {
            continue;
        }

        uvolt_nr = rt_ofw_prop_read_u32_array_index(opp_child_np,
                "opp-microvolt", 0, RT_ARRAY_SIZE(uvolt), uvolt);

        if ((int)uvolt_nr < 0)
        {
            /* If previous voltage is unknown, assume 0 to ensure a voltage ramp-up */
            uvolt[0] = 0;
        }

        if (!(opp = rt_dvfs_scaling_add_opp(dvfs, (rt_ubase_t)hz, (rt_ubase_t)uvolt[0])))
        {
            continue;
        }

        if (dvfs->ops && dvfs->ops->parse_opp)
        {
            rt_err_t err = dvfs->ops->parse_opp(dvfs, opp, (void *)opp_child_np);

            if (err)
            {
                LOG_W("%s: Parse OPP %s error = %s", rt_dm_dev_get_name(dvfs->dev),
                        rt_ofw_node_full_name(opp_child_np), rt_strerror(err));
            }
        }
    }

    dvfs->opp_table->share = rt_ofw_prop_read_bool(opp_np, "opp-shared");
    dvfs->opp_table->priv = dvfs->opp_table->priv ? : opp_np; /* Default value, DVFS unused */

    return RT_EOK;
}
#endif /* RT_USING_OFW */

static void dvfs_gov_params_init_default(struct rt_dvfs_governor_params *params)
{
    params->sampling_rate_ms = 1000;
    params->up_threshold = 80;
    params->down_differential = 20;
    params->sampling_down_factor = 1;
    params->freq_step = 5;
    params->ignore_nice_load = RT_FALSE;
    params->powersave_bias = 0;
}

static rt_err_t dvfs_scaling_init_frequency(struct rt_dvfs_scaling *dvfs)
{
    struct rt_dvfs_opp *opp;

    if (!dvfs->opp_table || rt_list_isempty(&dvfs->opp_table->opp_nodes))
    {
        return RT_EOK;
    }

    if (dvfs->suspend_freq &&
        (opp = rt_dvfs_scaling_find_opp(dvfs, dvfs->suspend_freq)))
    {
        return rt_dvfs_scaling_apply_opp(dvfs, opp);
    }

    opp = rt_dvfs_scaling_find_ceil_opp(dvfs, dvfs->max_freq);
    if (!opp)
    {
        opp = rt_list_entry(dvfs->opp_table->opp_nodes.next, struct rt_dvfs_opp, list);
    }

    return rt_dvfs_scaling_apply_opp(dvfs, opp);
}

rt_err_t rt_dvfs_scaling_register(struct rt_dvfs_scaling *dvfs)
{
    rt_err_t err = RT_EOK;

    if (!dvfs || !dvfs->dev || !dvfs->ops)
    {
        return -RT_EINVAL;
    }

    RT_ASSERT(dvfs->ops->set_opp != RT_NULL);

    if (!dvfs->gov_params.sampling_rate_ms)
    {
        dvfs_gov_params_init_default(&dvfs->gov_params);
    }

#ifdef RT_USING_OFW
    if ((err = dvfs_ofw_parse_opp(dvfs)))
    {
        return err;
    }
#endif /* RT_USING_OFW */

    if (dvfs->opp_table && !dvfs->cur_freq)
    {
        err = dvfs_scaling_init_frequency(dvfs);
        if (err)
        {
            LOG_W("%s: init frequency error = %s",
                    rt_dm_dev_get_name(dvfs->dev), rt_strerror(err));
        }
    }

    rt_dm_dev_bind_fwdata(dvfs->dev, RT_NULL, dvfs);
    dvfs->dev->dvfs_scaling = dvfs;

    return RT_EOK;
}

rt_err_t rt_dvfs_scaling_unregister(struct rt_dvfs_scaling *dvfs)
{
    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    if (dvfs->gov)
    {
        if (dvfs->gov->stop)
        {
            dvfs->gov->stop(dvfs);
        }

        rt_dvfs_governor_put(dvfs->gov);
        dvfs->gov = RT_NULL;
    }

    dvfs->gov_data = RT_NULL;
    dvfs->load_update = RT_NULL;

    dvfs->dev->dvfs_scaling = RT_NULL;
    rt_dm_dev_unbind_fwdata(dvfs->dev, RT_NULL);

    /* Free the OPP by Drivers */

    return RT_EOK;
}

void rt_dvfs_scaling_enter(struct rt_dvfs_scaling *dvfs)
{
    if (dvfs)
    {
        rt_spin_lock(&_dvfs_scaling_lock);
    }
}

void rt_dvfs_scaling_leave(struct rt_dvfs_scaling *dvfs)
{
    if (dvfs)
    {
        rt_spin_unlock(&_dvfs_scaling_lock);
    }
}

void rt_dvfs_ns_sleep(rt_uint32_t ns)
{
    rt_uint32_t us;

    if (!ns)
    {
        return;
    }

    us = (ns + 999) / 1000;

    if (us < 1000 || rt_hw_interrupt_is_disabled())
    {
        rt_hw_us_delay(us);
    }
    else
    {
        rt_thread_mdelay(us / 1000);
    }
}

rt_err_t rt_dvfs_scaling_suspend(struct rt_dvfs_scaling *dvfs)
{
    rt_err_t err = RT_EOK;

    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    if (dvfs->gov && dvfs->gov->suspend)
    {
        if ((err = dvfs->gov->suspend(dvfs)))
        {
            LOG_W("%s: governor suspend error = %s",
                    rt_dm_dev_get_name(dvfs->dev), rt_strerror(err));
        }
    }

    if (dvfs->suspend_freq)
    {
        if ((err = rt_dvfs_scaling_set_frequency(dvfs, dvfs->suspend_freq)))
        {
            LOG_W("%s: set suspend frequency(%lu) error = %s",
                    rt_dm_dev_get_name(dvfs->dev), dvfs->suspend_freq, rt_strerror(err));
        }
    }

    if (dvfs->ops && dvfs->ops->suspend)
    {
        rt_dvfs_scaling_enter(dvfs);
        err = dvfs->ops->suspend(dvfs);
        rt_dvfs_scaling_leave(dvfs);
    }

    return err;
}

rt_err_t rt_dvfs_scaling_resume(struct rt_dvfs_scaling *dvfs)
{
    rt_err_t err = RT_EOK;

    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    if (dvfs->ops && dvfs->ops->resume)
    {
        rt_dvfs_scaling_enter(dvfs);
        err = dvfs->ops->resume(dvfs);
        rt_dvfs_scaling_leave(dvfs);
    }

    if (dvfs->gov && dvfs->gov->resume)
    {
        rt_err_t gov_err = dvfs->gov->resume(dvfs);

        if (gov_err && !err)
        {
            err = gov_err;
        }
    }

    return err;
}

rt_err_t rt_dvfs_scaling_set_governor(struct rt_dvfs_scaling *dvfs, rt_uint32_t governor)
{
    rt_err_t err = RT_EOK;
    struct rt_dvfs_governor *gov;

    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    if (!(gov = rt_dvfs_governor_get(governor)))
    {
        return -RT_ENOSYS;
    }

    if (dvfs->gov)
    {
        if (dvfs->gov->stop)
        {
            if ((err = dvfs->gov->stop(dvfs)))
            {
                rt_dvfs_governor_put(gov);
                return err;
            }
        }

        rt_dvfs_governor_put(dvfs->gov);
    }

    dvfs->gov = gov;

    if (dvfs->gov->start)
    {
        if ((err = dvfs->gov->start(dvfs)))
        {
            rt_dvfs_governor_put(dvfs->gov);
            dvfs->gov = RT_NULL;
        }
    }

    return err;
}

rt_err_t rt_dvfs_scaling_set_frequency(struct rt_dvfs_scaling *dvfs, rt_ubase_t frequency)
{
    rt_err_t err;
    struct rt_dvfs_opp *opp = RT_NULL;

    if (!dvfs || !dvfs->opp_table)
    {
        return -RT_EINVAL;
    }

    if (dvfs->min_freq && frequency < dvfs->min_freq)
    {
        frequency = dvfs->min_freq;
    }
    if (dvfs->max_freq && frequency > dvfs->max_freq)
    {
        frequency = dvfs->max_freq;
    }

    if (!(opp = rt_dvfs_scaling_find_opp(dvfs, frequency)))
    {
        if (!(opp = rt_dvfs_scaling_find_floor_opp(dvfs, frequency)))
        {
            opp = rt_dvfs_scaling_find_ceil_opp(dvfs, frequency);
        }
    }

    if (!opp || !opp->available)
    {
        return -RT_ENOENT;
    }

    err = rt_dvfs_scaling_apply_opp(dvfs, opp);

    return err;
}

static rt_err_t dvfs_regulator_set_voltage_retry(struct rt_regulator *supply,
        rt_ubase_t uvolt, rt_uint32_t retry_ns)
{
    for (int i = 0; i < RT_USING_DVFS_OPP_RETRY_MAX; ++i)
    {
        rt_err_t err = rt_regulator_set_voltage(supply, uvolt, uvolt);

        if (err == -RT_EBUSY)
        {
            rt_dvfs_ns_sleep(retry_ns);
            continue;
        }

        return err;
    }

    return -RT_EBUSY;
}

static rt_err_t dvfs_clk_set_rate_retry(struct rt_clk *clk,
        rt_ubase_t rate, rt_uint32_t retry_ns)
{
    for (int i = 0; i < RT_USING_DVFS_OPP_RETRY_MAX; ++i)
    {
        rt_err_t err = rt_clk_set_rate(clk, rate);

        if (err == -RT_EBUSY)
        {
            rt_dvfs_ns_sleep(retry_ns);
            continue;
        }

        return err;
    }

    return -RT_EBUSY;
}

rt_err_t rt_dvfs_scaling_apply_opp(struct rt_dvfs_scaling *dvfs, struct rt_dvfs_opp *opp)
{
    rt_err_t err;

    if (!dvfs || !opp || !dvfs->ops || !dvfs->ops->set_opp || !dvfs->opp_table)
    {
        return -RT_EINVAL;
    }

    if (!opp->available)
    {
        return -RT_EINVAL;
    }

    if ((dvfs->min_freq && opp->freq < dvfs->min_freq) ||
        (dvfs->max_freq && opp->freq > dvfs->max_freq))
    {
        return -RT_EINVAL;
    }

    if (dvfs->ops->set_opp)
    {
        err = -RT_EBUSY;

        for (int tries = 0; tries < RT_USING_DVFS_OPP_RETRY_MAX; ++tries)
        {
            err = dvfs->ops->set_opp(dvfs, opp);

            if (err != -RT_EBUSY)
            {
                break;
            }

            rt_dvfs_ns_sleep(dvfs->retry_delay);
        }

        if (err)
        {
            return err;
        }

        rt_dvfs_ns_sleep(dvfs->transition_latency);
    }
    else
    {
        rt_uint32_t retry_delay = dvfs->retry_delay;
        rt_ubase_t old_uvolt, old_freq, new_uvolt, new_freq;
        struct rt_dvfs_opp *old = dvfs->opp_table->current_opp;

        /* If previous voltage is unknown, assume 0 to ensure a voltage ramp-up */
        old_uvolt = old ? old->uvolt : 0;
        old_freq = dvfs->cur_freq;

        new_uvolt = opp->uvolt;
        new_freq = opp->freq;

        if (new_freq > old_freq)
        {
            /* Scale up: raise voltage first, then increase frequency */
            if (dvfs->supply && new_uvolt > old_uvolt)
            {
                if ((err = dvfs_regulator_set_voltage_retry(dvfs->supply, new_uvolt, retry_delay)))
                {
                    return err;
                }
            }

            if (dvfs->clk)
            {
                if ((err = dvfs_clk_set_rate_retry(dvfs->clk, new_freq, retry_delay)))
                {
                    return err;
                }
            }
        }
        else if (new_freq < old_freq)
        {
            /* Scale down: lower frequency first, then lower voltage */
            if (dvfs->clk)
            {
                if ((err = dvfs_clk_set_rate_retry(dvfs->clk, new_freq, retry_delay)))
                {
                    return err;
                }
            }

            if (dvfs->supply && new_uvolt < old_uvolt)
            {
                if ((err = dvfs_regulator_set_voltage_retry(dvfs->supply, new_uvolt, retry_delay)))
                {
                    return err;
                }
            }
        }
        else
        {
            /* Frequency unchanged: adjust voltage only if needed */
            if (dvfs->supply && new_uvolt != old_uvolt)
            {
                if ((err = dvfs_regulator_set_voltage_retry(dvfs->supply, new_uvolt, retry_delay)))
                {
                    return err;
                }
            }
        }

        rt_dvfs_ns_sleep(dvfs->transition_latency);
    }

    rt_dvfs_scaling_enter(dvfs);
    dvfs->cur_freq = opp->freq;
    dvfs->opp_table->current_opp = opp;
    rt_dvfs_scaling_leave(dvfs);

    return RT_EOK;
}

/* CPU Load Monitoring */
#ifdef RT_USING_IDLE_HOOK

static rt_uint64_t _idle_tick_total = 0;
static rt_tick_t _idle_start_tick = 0;
static rt_bool_t _in_idle = RT_FALSE;

static void dvfs_idle_hook(void)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();

    if (!_in_idle)
    {
        _in_idle = RT_TRUE;
        _idle_start_tick = rt_tick_get();
    }

    rt_hw_interrupt_enable(level);
}

static int dvfs_load_init(void)
{
    /* Install idle hook */
    rt_thread_idle_sethook(dvfs_idle_hook);

    return 0;
}
INIT_DEVICE_EXPORT(dvfs_load_init);

void rt_dvfs_load_update(struct rt_dvfs_scaling *dvfs)
{
    if (!dvfs)
    {
        return;
    }

    if (dvfs->load_update)
    {
        dvfs->load_update(dvfs);
    }
    else
    {
        rt_dvfs_cpu_load_update(&dvfs->cpu_load);
    }
}

void rt_dvfs_cpu_load_update(struct rt_dvfs_cpu_load *load)
{
    rt_tick_t now;
    rt_base_t level;

    if (!load)
    {
        return;
    }

    level = rt_hw_interrupt_disable();

    now = rt_tick_get();

    /* Exit idle state if in idle */
    if (_in_idle)
    {
        rt_uint64_t idle_ticks = now - _idle_start_tick;
        _idle_tick_total += idle_ticks;
        _in_idle = RT_FALSE;
    }

    if (load->last_update == 0)
    {
        /* First update */
        load->last_update = now;
        load->total_tick = 0;
        load->idle_tick = 0;
        load->load_percentage = 0;
    }
    else
    {
        rt_uint64_t total_elapsed;
        rt_uint64_t idle_elapsed;

        /* Calculate total elapsed ticks */
        total_elapsed = now - load->last_update;

        /* Get idle ticks accumulated since last update */
        idle_elapsed = _idle_tick_total - load->idle_tick;

        /* Update counters */
        load->total_tick = total_elapsed;
        load->idle_tick = _idle_tick_total;
        load->last_update = now;

        /* Calculate load percentage */
        if (total_elapsed > 0)
        {
            rt_uint64_t busy_ticks = (idle_elapsed > total_elapsed) ? 0 : (total_elapsed - idle_elapsed);
            load->load_percentage = (busy_ticks * 100) / total_elapsed;

            /* Clamp to 0-100 range */
            if (load->load_percentage > 100)
            {
                load->load_percentage = 100;
            }
        }
        else
        {
            load->load_percentage = 0;
        }
    }

    rt_hw_interrupt_enable(level);
}

#else /* RT_USING_IDLE_HOOK */

void rt_dvfs_cpu_load_update(struct rt_dvfs_cpu_load *load)
{
    rt_tick_t now;

    if (!load)
    {
        return;
    }

    now = rt_tick_get();

    if (load->last_update == 0)
    {
        load->last_update = now;
        load->total_tick = 0;
        load->idle_tick = 0;
        load->load_percentage = 50; /* Default to medium load */
    }
    else
    {
        /* Without idle hook, use default load estimation */
        load->total_tick = now - load->last_update;
        load->last_update = now;

        /* Estimate load based on scheduler activity */
        /* This is a simple heuristic - actual load depends on scheduler */
        extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
        rt_uint32_t ready_count = 0;
        rt_base_t level;

        level = rt_hw_interrupt_disable();
        for (int i = 0; i < RT_THREAD_PRIORITY_MAX; i++)
        {
            if (!rt_list_isempty(&rt_thread_priority_table[i]))
            {
                ready_count++;
            }
        }
        rt_hw_interrupt_enable(level);

        /* Estimate: 1 ready thread = 50%, more threads = higher load */
        load->load_percentage = (ready_count > 5) ? 90 : (ready_count * 15 + 30);
        if (load->load_percentage > 100)
        {
            load->load_percentage = 100;
        }
    }
}

#endif /* RT_USING_IDLE_HOOK */

rt_uint32_t rt_dvfs_cpu_load_get(struct rt_dvfs_cpu_load *load)
{
    if (!load)
    {
        return 0;
    }

    return load->load_percentage;
}

/* Governor parameter management */
rt_err_t rt_dvfs_governor_set_params(struct rt_dvfs_scaling *dvfs, struct rt_dvfs_governor_params *params)
{
    if (!dvfs || !params)
    {
        return -RT_EINVAL;
    }

    /* Validate parameters */
    if (params->up_threshold > 100 || params->down_differential > 100)
    {
        return -RT_EINVAL;
    }

    if (params->sampling_rate_ms > 0 && params->sampling_rate_ms < 10)
    {
        LOG_W("Sampling rate too small, adjusting to 10ms");
        params->sampling_rate_ms = 10;
    }

    rt_dvfs_scaling_enter(dvfs);
    rt_memcpy(&dvfs->gov_params, params, sizeof(*params));
    rt_dvfs_scaling_leave(dvfs);

    return RT_EOK;
}

rt_err_t rt_dvfs_governor_get_params(struct rt_dvfs_scaling *dvfs, struct rt_dvfs_governor_params *params)
{
    if (!dvfs || !params)
    {
        return -RT_EINVAL;
    }

    rt_dvfs_scaling_enter(dvfs);
    rt_memcpy(params, &dvfs->gov_params, sizeof(*params));
    rt_dvfs_scaling_leave(dvfs);

    return RT_EOK;
}

static rt_err_t dvfs_default_set_opp(struct rt_dvfs_scaling *dvfs, struct rt_dvfs_opp *opp)
{
    rt_err_t err;
    rt_ubase_t old_freq, old_uvolt, new_freq, new_uvolt;
    struct rt_dvfs_opp *old_opp;

    if (!dvfs || !opp)
    {
        return -RT_EINVAL;
    }

    old_opp = dvfs->opp_table ? dvfs->opp_table->current_opp : RT_NULL;
    old_freq = dvfs->cur_freq;
    old_uvolt = old_opp ? old_opp->uvolt : 0;
    new_freq = opp->freq;
    new_uvolt = opp->uvolt;

    if (new_freq > old_freq)
    {
        if (dvfs->supply && new_uvolt > old_uvolt)
        {
            err = rt_regulator_set_voltage(dvfs->supply, new_uvolt, new_uvolt);
            if (err)
            {
                return err;
            }

            if (dvfs->transition_latency)
            {
                rt_dvfs_ns_sleep(dvfs->transition_latency);
            }
        }

        if (dvfs->clk)
        {
            err = rt_clk_set_rate(dvfs->clk, new_freq);
            if (err)
            {
                if (dvfs->supply && new_uvolt > old_uvolt)
                {
                    rt_regulator_set_voltage(dvfs->supply, old_uvolt, old_uvolt);
                }
                return err;
            }
        }
    }
    else if (new_freq < old_freq)
    {
        if (dvfs->clk)
        {
            err = rt_clk_set_rate(dvfs->clk, new_freq);
            if (err)
            {
                return err;
            }
        }

        if (dvfs->supply && new_uvolt < old_uvolt)
        {
            err = rt_regulator_set_voltage(dvfs->supply, new_uvolt, new_uvolt);
            if (err)
            {
                LOG_W("%s: set voltage %lu failed: %s",
                      rt_dm_dev_get_name(dvfs->dev), new_uvolt, rt_strerror(err));
            }
        }
    }
    else if (dvfs->supply && new_uvolt != old_uvolt)
    {
        err = rt_regulator_set_voltage(dvfs->supply, new_uvolt, new_uvolt);
        if (err)
        {
            return err;
        }
    }

    if (dvfs->transition_latency)
    {
        rt_dvfs_ns_sleep(dvfs->transition_latency);
    }

    return RT_EOK;
}

static rt_err_t dvfs_default_parse_opp(struct rt_dvfs_scaling *dvfs,
        struct rt_dvfs_opp *opp, void *fw_np)
{
#ifdef RT_USING_OFW
    struct rt_ofw_node *opp_np = (struct rt_ofw_node *)fw_np;
    rt_uint32_t power = 0;

    if (!opp || !opp_np)
    {
        return -RT_EINVAL;
    }

    if (!rt_ofw_prop_read_u32(opp_np, "opp-microwatt", &power))
    {
        opp->power = power / 1000;
    }

    opp->available = RT_TRUE;

    if (rt_ofw_prop_read_bool(opp_np, "opp-suspend"))
    {
        dvfs->suspend_freq = opp->freq;
    }
#else
    RT_UNUSED(dvfs);
    RT_UNUSED(opp);
    RT_UNUSED(fw_np);
#endif

    return RT_EOK;
}

struct rt_dvfs_scaling_ops rt_dvfs_devfreq_ops =
{
    .set_opp = dvfs_default_set_opp,
    .parse_opp = dvfs_default_parse_opp,
};

static void devfreq_load_from_event(struct rt_dvfs_scaling *scaling)
{
    struct rt_dvfs_devfreq *devfreq = rt_container_of(scaling, struct rt_dvfs_devfreq, parent);
    struct rt_dvfs_event_data evd;
    rt_err_t err;

    if (!devfreq->ev)
    {
        return;
    }

    if ((err = rt_dvfs_event_read(devfreq->ev, &evd)))
    {
        LOG_D("%s: read dvfs event error = %s",
              rt_dm_dev_get_name(scaling->dev), rt_strerror(err));
        return;
    }

    if (evd.total_count)
    {
        scaling->cpu_load.load_percentage = (rt_uint32_t)((evd.load_count * 100) / evd.total_count);

        if (scaling->cpu_load.load_percentage > 100)
        {
            scaling->cpu_load.load_percentage = 100;
        }
    }
    else
    {
        scaling->cpu_load.load_percentage = 0;
    }
}

rt_err_t rt_dvfs_devfreq_register(struct rt_dvfs_devfreq *devfreq)
{
    rt_err_t err;
    struct rt_dvfs_scaling *scaling;

    if (!devfreq)
    {
        return -RT_EINVAL;
    }

    scaling = rt_dvfs_devfreq_to_scaling(devfreq);

    if (!scaling->load_update && devfreq->ev)
    {
        scaling->load_update = devfreq_load_from_event;
    }

    if (devfreq->ev)
    {
        err = rt_dvfs_event_enable(devfreq->ev);
        if (err)
        {
            LOG_W("%s: enable devfreq event error = %s",
                  rt_dm_dev_get_name(scaling->dev), rt_strerror(err));
        }
    }

    err = rt_dvfs_scaling_register(scaling);
    if (err)
    {
        if (devfreq->ev)
        {
            rt_dvfs_event_disable(devfreq->ev);
        }
        return err;
    }

    LOG_D("Devfreq registered for device %s", rt_dm_dev_get_name(scaling->dev));

    return RT_EOK;
}

rt_err_t rt_dvfs_devfreq_unregister(struct rt_dvfs_devfreq *devfreq)
{
    rt_err_t err;

    if (!devfreq)
    {
        return -RT_EINVAL;
    }

    err = rt_dvfs_scaling_unregister(rt_dvfs_devfreq_to_scaling(devfreq));

    if (devfreq->ev)
    {
        rt_dvfs_event_disable(devfreq->ev);
        rt_dvfs_event_put(devfreq->ev);
        devfreq->ev = RT_NULL;
    }

    return err;
}
