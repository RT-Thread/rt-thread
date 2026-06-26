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

#define DBG_TAG "dvfs.idle"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static RT_DEFINE_SPINLOCK(_dvfs_idle_lock);

/* Idle prediction data */
static rt_uint32_t _last_idle_duration_us = 0;
static rt_uint32_t _predicted_idle_us = 0;

rt_inline void dvfs_idle_lock(void)
{
    rt_spin_lock(&_dvfs_idle_lock);
}

rt_inline void dvfs_idle_unlock(void)
{
    rt_spin_unlock(&_dvfs_idle_lock);
}

/* Predict next idle duration based on history */
static rt_uint32_t dvfs_predict_idle_duration(void)
{
    /*
     * Simple prediction: exponentially weighted moving average
     * predicted = 0.7 * last_actual + 0.3 * previous_predicted
     */
    rt_uint32_t predicted = (_last_idle_duration_us * 7 + _predicted_idle_us * 3) / 10;

    /* Clamp to reasonable range */
    if (predicted < 100)
    {
        predicted = 100; /* Minimum 100us */
    }

    _predicted_idle_us = predicted;

    return predicted;
}

/* Update prediction with actual idle duration */
static void dvfs_update_idle_prediction(rt_uint32_t actual_duration_us)
{
    _last_idle_duration_us = actual_duration_us;
}

rt_err_t rt_dvfs_idle_register(struct rt_dvfs_idle *idle)
{
    if (!idle || !idle->dev || !idle->ops)
    {
        return -RT_EINVAL;
    }

    rt_dm_dev_bind_fwdata(idle->dev, RT_NULL, idle);

    return RT_EOK;
}

rt_err_t rt_dvfs_idle_unregister(struct rt_dvfs_idle *idle)
{
    rt_err_t err = RT_EOK;

    if (!idle)
    {
        return -RT_EINVAL;
    }

    dvfs_idle_lock();

    if (idle->ref_count != 0 || idle->entry_count != 0)
    {
        err = -RT_EBUSY;
        goto _unlock;
    }

    rt_dm_dev_unbind_fwdata(idle->dev, RT_NULL);

_unlock:
    dvfs_idle_unlock();

    return err;
}

rt_err_t rt_dvfs_idle_add_status(struct rt_dvfs_idle *idle, struct rt_dvfs_idle_status *status)
{
    if (!idle || !status)
    {
        return -RT_EINVAL;
    }

    if (!idle->status_table)
    {
        if (!(idle->status_table = rt_calloc(1, sizeof(*idle->status_table))))
        {
            return -RT_ENOMEM;
        }

        rt_list_init(&idle->status_table->status_nodes);
    }

    rt_list_init(&status->list);

    dvfs_idle_lock();
    rt_list_insert_before(&idle->status_table->status_nodes, &status->list);
    dvfs_idle_unlock();

    return RT_EOK;
}

void rt_dvfs_idle_remove_status(struct rt_dvfs_idle *idle, struct rt_dvfs_idle_status *status)
{
    if (!idle || !status)
    {
        return;
    }

    RT_ASSERT(idle->status_table != RT_NULL);

    dvfs_idle_lock();
    rt_list_remove(&status->list);
    dvfs_idle_unlock();
}

void rt_dvfs_idle_remove_status_all(struct rt_dvfs_idle *idle,
        void (*release)(struct rt_dvfs_idle *, struct rt_dvfs_idle_status *))
{
    struct rt_dvfs_idle_status_table *status_table;
    struct rt_dvfs_idle_status *status, *status_next;

    if (!idle)
    {
        return;
    }

    RT_ASSERT(idle->status_table != RT_NULL);
    status_table = idle->status_table;

    dvfs_idle_lock();

    rt_list_for_each_entry_safe(status, status_next, &status_table->status_nodes, list)
    {
        rt_list_remove(&status->list);

        dvfs_idle_unlock();

        if (release)
        {
            release(idle, status);
        }

        dvfs_idle_lock();
    }

    dvfs_idle_unlock();
}

rt_err_t rt_dvfs_idle_entry(struct rt_dvfs_idle *idle)
{
    rt_err_t err;
    rt_bool_t can_stop_timer = RT_TRUE;
    struct rt_dvfs_idle_status_table *table;
    struct rt_dvfs_idle_status *it, *best = RT_NULL;
    rt_uint32_t predicted_idle_us;
    rt_tick_t entry_tick;

    if (!idle)
    {
        return -RT_EINVAL;
    }

    if (!(table = idle->status_table))
    {
        return -RT_ENOSYS;
    }

    if (idle->ops->timer_can_stop)
    {
        can_stop_timer = idle->ops->timer_can_stop(idle);
    }

    /* Predict idle duration */
    predicted_idle_us = dvfs_predict_idle_duration();

    /*
     * Select the best idle state based on predicted idle duration:
     * - Choose the deepest sleep state that has:
     *   - entry_latency + exit_latency < predicted_idle
     *   - min_residency <= predicted_idle
     * - This maximizes power savings while ensuring timely wakeup
     */
    rt_list_for_each_entry(it, &table->status_nodes, list)
    {
        rt_uint32_t total_latency = it->entry_latency_us + it->exit_latency_us;

        /* Skip states that require timer stop if timer can't stop */
        if (it->timer_stop && !can_stop_timer)
        {
            continue;
        }

        /* Check if this state is suitable for predicted idle time */
        if (predicted_idle_us >= total_latency && predicted_idle_us >= it->min_residency_us)
        {
            /* Choose the deepest suitable state (highest min_residency) */
            if (!best || it->min_residency_us > best->min_residency_us)
            {
                best = it;
            }
        }
    }

    /* If no suitable state found, try to find a fallback */
    if (!best)
    {
        /* Find shallowest state that doesn't require timer stop */
        rt_list_for_each_entry(it, &table->status_nodes, list)
        {
            if (!it->timer_stop || can_stop_timer)
            {
                if (!best || it->entry_latency_us < best->entry_latency_us)
                {
                    best = it;
                }
            }
        }
    }

    if (!best)
    {
        return -RT_EEMPTY;
    }

    dvfs_idle_lock();

    if (idle->entry_count != 0)
    {
        dvfs_idle_unlock();
        return -RT_EBUSY;
    }

    table->current_status = best;
    ++idle->entry_count;
    entry_tick = rt_tick_get();

    dvfs_idle_unlock();

    LOG_D("%s: enter idle, predicted=%uus, selected state min_residency=%uus",
          rt_dm_dev_get_name(idle->dev), predicted_idle_us, best->min_residency_us);

    if ((err = idle->ops->entry(idle, best)))
    {
        dvfs_idle_lock();
        table->current_status = RT_NULL;
        --idle->entry_count;
        dvfs_idle_unlock();
        return err;
    }

    /* Store entry time for exit calculation */
    idle->priv = (void *)(rt_ubase_t)entry_tick;

    return RT_EOK;
}

rt_err_t rt_dvfs_idle_exit(struct rt_dvfs_idle *idle)
{
    rt_err_t err;
    struct rt_dvfs_idle_status *cur;
    struct rt_dvfs_idle_status_table *table;
    rt_tick_t exit_tick, entry_tick;
    rt_uint32_t actual_idle_us;

    if (!idle)
    {
        return -RT_EINVAL;
    }

    if (!(table = idle->status_table))
    {
        return -RT_ENOSYS;
    }

    dvfs_idle_lock();

    if (idle->entry_count == 0 || table->current_status == RT_NULL)
    {
        dvfs_idle_unlock();
        return -RT_EINVAL;
    }
    cur = table->current_status;
    entry_tick = (rt_tick_t)(rt_ubase_t)idle->priv;

    dvfs_idle_unlock();

    exit_tick = rt_tick_get();

    /* Calculate actual idle duration in microseconds */
    if (exit_tick >= entry_tick)
    {
        actual_idle_us = (exit_tick - entry_tick) * (1000000 / RT_TICK_PER_SECOND);
    }
    else
    {
        /* Tick overflow */
        actual_idle_us = (RT_TICK_MAX - entry_tick + exit_tick + 1) * (1000000 / RT_TICK_PER_SECOND);
    }

    err = idle->ops->exit(idle, cur);

    dvfs_idle_lock();

    if (idle->entry_count > 0)
    {
        --idle->entry_count;
    }
    table->current_status = RT_NULL;
    idle->priv = RT_NULL;

    dvfs_idle_unlock();

    /* Update prediction with actual duration */
    dvfs_update_idle_prediction(actual_idle_us);

    LOG_D("%s: exit idle, actual=%uus", rt_dm_dev_get_name(idle->dev), actual_idle_us);

    return err;
}

struct rt_dvfs_idle *rt_dvfs_idle_get(struct rt_device *dev)
{
    struct rt_dvfs_idle *idle = RT_NULL;

    if (!dev)
    {
        return rt_err_ptr(-RT_EINVAL);
    }

    dvfs_idle_lock();

#ifdef RT_USING_OFW
    if (dev && dev->ofw_node)
    {
        idle = rt_ofw_data(dev->ofw_node);
    }
#endif /* RT_USING_OFW */

    if (!rt_is_err_or_null(idle))
    {
        ++idle->ref_count;
    }

    dvfs_idle_unlock();

    return idle;
}

void rt_dvfs_idle_put(struct rt_dvfs_idle *idle)
{
    if (!idle)
    {
        return;
    }

    dvfs_idle_lock();
    --idle->ref_count;
    dvfs_idle_unlock();
}
