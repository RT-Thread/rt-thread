/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-23     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rtdm.ptp"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define NSEC_PER_SEC    1000000000L

static struct rt_dm_ida ptp_ida = RT_DM_IDA_INIT(PTP);

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops _ptp_ops =
{
};
#endif

rt_err_t rt_ptp_clock_register(struct rt_ptp_clock *ptp)
{
    rt_err_t err;
    int device_id;
    const char *dev_name;
    char name[RT_NAME_MAX];

    if (!ptp || !ptp->ops)
    {
        return -RT_EINVAL;
    }

    if ((device_id = rt_dm_ida_alloc(&ptp_ida)) < 0)
    {
        return -RT_EFULL;
    }

    rt_dm_dev_set_name(&ptp->parent, "ptp%u", device_id);
    dev_name = rt_dm_dev_get_name(&ptp->parent);

    if (ptp->pins_nr)
    {
        if (!ptp->pins)
        {
            LOG_E("%s: found %d pin but pins is NULL", dev_name, ptp->pins_nr);
            err = -RT_EINVAL;
            goto _fail;
        }

        if (!ptp->ops->verify)
        {
            LOG_E("%s: found %d pin but verify is not supported", dev_name, ptp->pins_nr);
            err = -RT_EINVAL;
            goto _fail;
        }

        rt_snprintf(name, sizeof(name), "%s-pin", dev_name);
        rt_mutex_init(&ptp->pin_mutex, name, RT_IPC_FLAG_PRIO);
    }

    if ((ptp->perout_nr || ptp->extts_nr) && !ptp->ops->enable)
    {
        LOG_E("%s: perout(%u) or extts(%u) but enable is not supported",
                dev_name, ptp->perout_nr, ptp->extts_nr);
        err = -RT_EINVAL;
        goto _free_mutex;
    }

    if (ptp->ops->adjfreq && ptp->max_freq <= 0)
    {
        LOG_E("%s: adjfreq is supported but max_freq is not set", dev_name);
        err = -RT_EINVAL;
        goto _free_mutex;
    }

    rt_list_init(&ptp->notifier_nodes);
    rt_spin_lock_init(&ptp->nodes_lock);

    /* Just make a search interface */
    ptp->parent.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    ptp->parent.ops = ptp->parent.ops ? : &_ptp_ops;
#endif
    ptp->parent.master_id = ptp_ida.master_id;
    ptp->parent.device_id = device_id;

    if ((err = rt_device_register(&ptp->parent, dev_name, RT_DEVICE_FLAG_DEACTIVATE)))
    {
        goto _free_mutex;
    }

    return RT_EOK;

_free_mutex:
    if (ptp->pins_nr)
    {
        rt_mutex_detach(&ptp->pin_mutex);
    }

_fail:
    rt_dm_ida_free(&ptp_ida, device_id);

    return err;
}

rt_err_t rt_ptp_clock_unregister(struct rt_ptp_clock *ptp)
{
    struct rt_ptp_request_perout perout;
    struct rt_ptp_request_extts extts;

    if (!ptp)
    {
        return -RT_EINVAL;
    }

    if (ptp->parent.ref_count)
    {
        LOG_E("%s: there is %u user",
                rt_dm_dev_get_name(&ptp->parent), ptp->parent.ref_count);
        return -RT_EINVAL;
    }

    if (!rt_list_isempty(&ptp->notifier_nodes))
    {
        LOG_W("%s: notifier not unregister", rt_dm_dev_get_name(&ptp->parent));
    }

    rt_memset(&extts, 0, sizeof(extts));

    for (int i = 0; i < ptp->extts_nr; ++i)
    {
        extts.chan = i;
        rt_ptp_request_extts(ptp, &extts);
    }

    rt_memset(&perout, 0, sizeof(perout));
    perout.flags = PTP_PEROUT_ONE_SHOT;

    for (int i = 0; i < ptp->perout_nr; ++i)
    {
        perout.chan = i;
        rt_ptp_request_perout(ptp, &perout);
    }

    rt_ptp_enable_pps(ptp, RT_FALSE);

    if (ptp->pins_nr)
    {
        rt_mutex_detach(&ptp->pin_mutex);
    }

    rt_dm_ida_free(&ptp_ida, ptp->parent.device_id);

    return rt_device_unregister(&ptp->parent);
}

rt_err_t rt_ptp_clock_notifier_register(struct rt_ptp_clock *ptp,
        struct rt_ptp_clock_notifier *notifier)
{
    if (!ptp || !notifier)
    {
        return -RT_EINVAL;
    }

    if (!notifier->event_mask)
    {
        LOG_E("%s: clock notifier event mask is empty, try to set 0~%u",
                rt_dm_dev_get_name(&ptp->parent), PTP_CLOCK_EV_MAX - 1);
        return -RT_EINVAL;
    }

    notifier->ptp = ptp;
    rt_list_init(&notifier->list);

    rt_spin_lock(&ptp->nodes_lock);
    rt_list_insert_after(&ptp->notifier_nodes, &notifier->list);
    rt_spin_unlock(&ptp->nodes_lock);

    return RT_EOK;
}

rt_err_t rt_ptp_clock_notifier_unregister(struct rt_ptp_clock *ptp,
        struct rt_ptp_clock_notifier *notifier)
{
    if (!ptp || !notifier)
    {
        return -RT_EINVAL;
    }

    rt_spin_lock(&ptp->nodes_lock);
    rt_list_remove(&notifier->list);
    rt_spin_unlock(&ptp->nodes_lock);

    return RT_EOK;
}

void rt_ptp_clock_event(struct rt_ptp_clock *ptp, struct rt_ptp_clock_event *ev)
{
    struct rt_ptp_clock_notifier *notifier, *next_notifier;

    RT_ASSERT(ptp != RT_NULL);
    RT_ASSERT(ev->type < PTP_CLOCK_EV_MAX);

    rt_spin_lock(&ptp->nodes_lock);

    rt_list_for_each_entry_safe(notifier, next_notifier, &ptp->notifier_nodes, list)
    {
        if (notifier->event_mask & RT_BIT(ev->type))
        {
            rt_spin_unlock(&ptp->nodes_lock);

            notifier->callback(notifier, ev);

            rt_spin_lock(&ptp->nodes_lock);
        }
    }

    rt_spin_unlock(&ptp->nodes_lock);
}

rt_err_t rt_ptp_adjfreq(struct rt_ptp_clock *ptp, rt_base_t freq)
{
    if (!ptp)
    {
        return -RT_EINVAL;
    }

    if (!ptp->ops->adjfreq)
    {
        return -RT_ENOSYS;
    }

    if (ptp->max_freq <= 0)
    {
        if (freq != 0)
        {
            return -RT_EINVAL;
        }

        return RT_EOK;
    }

    if (freq > ptp->max_freq || freq < -ptp->max_freq)
    {
        return -RT_EINVAL;
    }

    return ptp->ops->adjfreq(ptp, freq);
}

rt_err_t rt_ptp_adjphase(struct rt_ptp_clock *ptp, rt_int32_t phase)
{
    rt_err_t err;
    rt_int32_t maxphase;

    if (!ptp)
    {
        return -RT_EINVAL;
    }

    if (!ptp->ops->adjphase)
    {
        return -RT_ENOSYS;
    }

    if ((err = rt_ptp_getmaxphase(ptp, &maxphase)))
    {
        return err;
    }

    if (phase > maxphase || phase < -maxphase)
    {
        return -RT_EINVAL;
    }

    return ptp->ops->adjphase(ptp, phase);
}

rt_err_t rt_ptp_getmaxphase(struct rt_ptp_clock *ptp, rt_int32_t *out_maxphase)
{
    if (!ptp || !out_maxphase)
    {
        return -RT_EINVAL;
    }

    if (!ptp->ops->getmaxphase)
    {
        return -RT_ENOSYS;
    }

    return ptp->ops->getmaxphase(ptp, out_maxphase);
}

rt_err_t rt_ptp_adjtime(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts)
{
    rt_int64_t delta;

    if (!ptp || !ts)
    {
        return -RT_EINVAL;
    }

    if (!ptp->ops->adjtime)
    {
        return -RT_ENOSYS;
    }

    if (ts->nsec < 0 || (rt_int64_t)ts->nsec >= NSEC_PER_SEC)
    {
        return -RT_EINVAL;
    }

    delta = ts->sec * NSEC_PER_SEC + (rt_int64_t)ts->nsec;

    return ptp->ops->adjtime(ptp, delta);
}

rt_err_t rt_ptp_gettime(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts)
{
    if (!ptp || !ts)
    {
        return -RT_EINVAL;
    }

    if (!ptp->ops->gettime)
    {
        return -RT_ENOSYS;
    }

    return ptp->ops->gettime(ptp, ts);
}

rt_err_t rt_ptp_settime(struct rt_ptp_clock *ptp, const struct rt_ptp_clock_time *ts)
{
    if (!ptp || !ts)
    {
        return -RT_EINVAL;
    }

    if (!ptp->ops->settime)
    {
        return -RT_ENOSYS;
    }

    return ptp->ops->settime(ptp, ts);
}

rt_err_t rt_ptp_request_extts(struct rt_ptp_clock *ptp,
        struct rt_ptp_request_extts *extts)
{
    rt_bool_t enable;
    struct rt_ptp_clock_request request;

    if (!ptp || !extts)
    {
        return -RT_EINVAL;
    }

    if (extts->chan >= ptp->extts_nr)
    {
        return -RT_EINVAL;
    }

    if (extts->flags & PTP_STRICT_FLAGS)
    {
        /* Ensure one of the rising/falling edge bits is set */
        if ((extts->flags & PTP_ENABLE_FEATURE) &&
            (extts->flags & PTP_EXTTS_EDGES) == 0)
        {
            return -RT_EINVAL;
        }
    }

    if (!ptp->ops->enable)
    {
        return -RT_ENOSYS;
    }

    request.type = PTP_CLK_REQ_EXTTS;
    rt_memcpy(&request.extts, extts, sizeof(*extts));
    enable = !!(extts->flags & PTP_ENABLE_FEATURE);

    return ptp->ops->enable(ptp, &request, enable);
}

rt_err_t rt_ptp_request_perout(struct rt_ptp_clock *ptp,
        struct rt_ptp_request_perout *perout)
{
    rt_bool_t enable;
    struct rt_ptp_clock_request request;

    if (!ptp || !perout)
    {
        return -RT_EINVAL;
    }

    if (perout->chan >= ptp->perout_nr)
    {
        return -RT_EINVAL;
    }

    if (perout->flags & PTP_STRICT_FLAGS)
    {
        if (perout->flags & PTP_PEROUT_DUTY_CYCLE)
        {
            /* The duty cycle must be subunitary */
            if (perout->on.sec > perout->period.sec ||
                (perout->on.sec == perout->period.sec &&
                    perout->on.nsec > perout->period.nsec))
            {
                return -RT_EINVAL;
            }
        }

        if (perout->flags & PTP_PEROUT_PHASE)
        {
            /*
             * The phase should be specified modulo the period,
             * therefore anything equal or larger than 1 period is invalid
             */
            if (perout->start_phase.sec > perout->period.sec ||
                (perout->start_phase.sec == perout->period.sec &&
                    perout->start_phase.nsec >= perout->period.nsec))
            {
                return -RT_EINVAL;
            }
        }
    }

    if (!ptp->ops->enable)
    {
        return -RT_ENOSYS;
    }

    request.type = PTP_CLK_REQ_PEROUT;
    rt_memcpy(&request.perout, perout, sizeof(*perout));
    enable = perout->period.sec || perout->period.nsec;

    return ptp->ops->enable(ptp, &request, enable);
}

rt_err_t rt_ptp_enable_pps(struct rt_ptp_clock *ptp, rt_bool_t on)
{
    struct rt_ptp_clock_request request;

    if (!ptp)
    {
        return -RT_EINVAL;
    }

    if (!ptp->ops->enable)
    {
        return -RT_ENOSYS;
    }

    request.type = PTP_CLK_REQ_PPS;

    return ptp->ops->enable(ptp, &request, on);
}

rt_err_t rt_ptp_get_pin_func(struct rt_ptp_clock *ptp,
        rt_uint32_t pin, struct rt_ptp_pin *out_pin)
{
    if (!ptp || !out_pin)
    {
        return -RT_EINVAL;
    }

    if (pin >= ptp->pins_nr)
    {
        if (!ptp->pins_nr)
        {
            return -RT_ENOSYS;
        }

        return -RT_EINVAL;
    }

    rt_mutex_take(&ptp->pin_mutex, RT_WAITING_FOREVER);

    rt_memcpy(out_pin, &ptp->pins[pin], sizeof(*out_pin));

    rt_mutex_release(&ptp->pin_mutex);

    return RT_EOK;
}

static rt_err_t ptp_disable_pin_func(struct rt_ptp_clock *ptp,
        rt_uint32_t func, rt_uint32_t chan)
{
    rt_err_t err = RT_EOK;
    struct rt_ptp_request_extts extts;
    struct rt_ptp_request_perout perout;

    switch (func)
    {
    case PTP_PIN_FUNC_NONE:
    case PTP_PIN_FUNC_PHYSYNC:
        break;

    case PTP_PIN_FUNC_EXTTS:
        rt_memset(&extts, 0, sizeof(extts));
        extts.chan = chan;
        err = rt_ptp_request_extts(ptp, &extts);
        break;

    case PTP_PIN_FUNC_PEROUT:
        rt_memset(&perout, 0, sizeof(perout));
        perout.chan = chan;
        err = rt_ptp_request_perout(ptp, &perout);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

static rt_err_t ptp_set_pin_func(struct rt_ptp_clock *ptp,
        rt_uint32_t pin, rt_uint32_t func, rt_uint32_t chan)
{
    int i;
    rt_err_t err;
    struct rt_ptp_pin *pin1 = RT_NULL, *pin2 = &ptp->pins[pin];

    for (i = 0; i < ptp->pins_nr; ++i)
    {
        if (ptp->pins[i].func == func && ptp->pins[i].chan == chan)
        {
            pin1 = &ptp->pins[i];
            break;
        }
    }

    /* Configure already, do nothing */
    if (pin1 && i == pin)
    {
        return RT_EOK;
    }

    switch (func)
    {
    case PTP_PIN_FUNC_NONE:
        break;

    case PTP_PIN_FUNC_EXTTS:
        if (chan >= ptp->extts_nr)
        {
            return -RT_EINVAL;
        }
        break;

    case PTP_PIN_FUNC_PEROUT:
        if (chan >= ptp->perout_nr)
        {
            return -RT_EINVAL;
        }
        break;

    case PTP_PIN_FUNC_PHYSYNC:
        if (chan != 0)
        {
            return -RT_EINVAL;
        }
        break;

    default:
        return -RT_EINVAL;
    }

    if ((err = ptp->ops->verify(ptp, pin, func, chan)))
    {
        LOG_E("%s: pin %u function %u channel %u error = %s",
                rt_dm_dev_get_name(&ptp->parent), pin, func, chan, rt_strerror(err));
        return err;
    }

    /* Disable configure before, update new configure */
    if (pin1)
    {
        ptp_disable_pin_func(ptp, func, chan);
        pin1->func = PTP_PIN_FUNC_NONE;
        pin1->chan = 0;
    }

    ptp_disable_pin_func(ptp, pin2->func, pin2->chan);
    pin2->func = func;
    pin2->chan = chan;

    return RT_EOK;
}

rt_err_t rt_ptp_set_pin_func(struct rt_ptp_clock *ptp,
        rt_uint32_t pin, rt_uint32_t func, rt_uint32_t chan)
{
    rt_err_t err;

    if (!ptp)
    {
        return -RT_EINVAL;
    }

    if (pin >= ptp->pins_nr)
    {
        if (!ptp->pins_nr)
        {
            return -RT_ENOSYS;
        }

        return -RT_EINVAL;
    }

    if (func >= PTP_PIN_FUNC_MAX)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&ptp->pin_mutex, RT_WAITING_FOREVER);

    err = ptp_set_pin_func(ptp, pin, func, chan);

    rt_mutex_release(&ptp->pin_mutex);

    return err;
}

rt_err_t rt_ptp_getsnapshot(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts)
{
    if (!ptp || !ts)
    {
        return -RT_EINVAL;
    }

    if (!ptp->ops->getsnapshot)
    {
        return -RT_ENOSYS;
    }

    return ptp->ops->getsnapshot(ptp, ts);
}
