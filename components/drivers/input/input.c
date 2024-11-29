/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rtdm.input"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct rt_spinlock input_device_lock = {};
static rt_list_t input_device_nodes = RT_LIST_OBJECT_INIT(input_device_nodes);

static struct rt_dm_ida input_ida = RT_DM_IDA_INIT(INPUT);

#ifdef RT_INPUT_TOUCHSCREEN
void input_touch_register(struct rt_input_device *idev);
void input_touch_unregister(struct rt_input_device *idev);
#endif

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops _input_ops =
{
};
#endif

static void input_remove_poll(struct rt_input_device *idev)
{
    if (idev->poller)
    {
        rt_timer_stop(&idev->poller->timer);
        rt_timer_detach(&idev->poller->timer);

        rt_free(idev->poller);
        idev->poller = RT_NULL;
    }
}

rt_err_t rt_input_device_register(struct rt_input_device *idev)
{
    rt_err_t err;
    int device_id;
    const char *dev_name;

    if (!idev)
    {
        return -RT_EINVAL;
    }

    if ((device_id = rt_dm_ida_alloc(&input_ida)) < 0)
    {
        return -RT_EFULL;
    }

    rt_dm_dev_set_name(&idev->parent, "input%u", device_id);
    dev_name = rt_dm_dev_get_name(&idev->parent);

    rt_list_init(&idev->list);
    rt_list_init(&idev->handler_nodes);
    rt_spin_lock_init(&idev->lock);

    /* Just make a search interface */
    idev->parent.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    idev->parent.ops = idev->parent.ops ? : &_input_ops;
#endif
    idev->parent.master_id = input_ida.master_id;
    idev->parent.device_id = device_id;

    if ((err = rt_device_register(&idev->parent, dev_name, RT_DEVICE_FLAG_DEACTIVATE)))
    {
        goto _fail;
    }

    rt_spin_lock(&input_device_lock);
    rt_list_insert_before(&input_device_nodes, &idev->list);
    rt_spin_unlock(&input_device_lock);

#ifdef RT_INPUT_TOUCHSCREEN
    /* MUST be registered after the list is inserted */
    input_touch_register(idev);
#endif

    if (idev->poller)
    {
        rt_timer_start(&idev->poller->timer);
    }

    return RT_EOK;

_fail:
    rt_dm_ida_free(&input_ida, device_id);

    input_remove_poll(idev);

    return err;
}

rt_err_t rt_input_device_unregister(struct rt_input_device *idev)
{
    const char *dev_name;

    if (!idev)
    {
        return -RT_EINVAL;
    }

    dev_name = rt_dm_dev_get_name(&idev->parent);

    if (idev->parent.ref_count)
    {
        LOG_E("%s: there is %u user", dev_name, idev->parent.ref_count);
        return -RT_EINVAL;
    }

#ifdef RT_INPUT_TOUCHSCREEN
    input_touch_unregister(idev);
#endif
    input_remove_poll(idev);
    idev->absinfo = RT_NULL;

    rt_dm_ida_free(&input_ida, idev->parent.device_id);

    rt_device_unregister(&idev->parent);

    rt_spin_lock(&input_device_lock);
    rt_list_remove(&idev->list);
    rt_spin_unlock(&input_device_lock);

    return RT_EOK;
}

rt_err_t rt_input_set_capability(struct rt_input_device *idev,
        rt_uint16_t type, rt_uint16_t code)
{
    if (!idev)
    {
        return -RT_EINVAL;
    }

    switch (type)
    {
    case EV_KEY:
        rt_bitmap_set_bit(idev->key_map, code);
        break;

    case EV_REL:
        rt_bitmap_set_bit(idev->rel_map, code);
        break;

    case EV_ABS:
        if (!idev->absinfo)
        {
            idev->absinfo = rt_calloc(ABS_CNT, sizeof(*idev->absinfo));

            if (!idev->absinfo)
            {
                return -RT_ENOMEM;
            }
        }
        rt_bitmap_set_bit(idev->abs_map, code);
        break;

    case EV_MSC:
    case EV_SW:
    case EV_LED:
    case EV_SND:
    case EV_REP:
    case EV_FF:
    case EV_PWR:
    case EV_FF_STATUS:
        return -RT_ENOSYS;

    default:
        return -RT_EINVAL;
    }

    rt_bitmap_set_bit(idev->cap, type);

    return RT_EOK;
}

rt_err_t rt_input_set_absinfo(struct rt_input_device *idev, rt_uint32_t axis,
        rt_int32_t min, rt_int32_t max, rt_int32_t fuzz, rt_int32_t flat)
{
    struct rt_input_absinfo *absinfo;

    if (!idev || !idev->absinfo)
    {
        return -RT_EINVAL;
    }

    rt_bitmap_set_bit(idev->abs_map, axis);

    absinfo = &idev->absinfo[axis];
    absinfo->minimum = min;
    absinfo->maximum = max;
    absinfo->fuzz = fuzz;
    absinfo->flat = flat;

    return RT_EOK;
}

static void input_poll(void *param)
{
    struct rt_input_device *idev = param;

    idev->poller->poll(idev);
}

rt_err_t rt_input_setup_polling(struct rt_input_device *idev,
        void (*poll)(struct rt_input_device *idev))
{
    const char *dev_name;

    if (!idev || !poll)
    {
        return -RT_EINVAL;
    }

    dev_name = rt_dm_dev_get_name(&idev->parent);

    idev->poller = rt_malloc(sizeof(*idev->poller));

    if (!idev->poller)
    {
        return -RT_ENOMEM;
    }

    idev->poller->poll = poll;

    rt_timer_init(&idev->poller->timer, dev_name, input_poll, idev,
            rt_tick_from_millisecond(RT_INPUT_POLL_INTERVAL_DEFAULT),
            RT_TIMER_FLAG_PERIODIC);

    return RT_EOK;
}

rt_err_t rt_input_set_poll_interval(struct rt_input_device *idev,
        rt_uint32_t interval_ms)
{
    rt_tick_t tick;

    if (!idev || !idev->poller)
    {
        return -RT_EINVAL;
    }

    tick = rt_tick_from_millisecond(interval_ms);

    return rt_timer_control(&idev->poller->timer, RT_TIMER_CTRL_SET_TIME, &tick);
}

rt_err_t rt_input_trigger(struct rt_input_device *idev,
        rt_uint16_t type, rt_uint16_t code, rt_int32_t value)
{
    RT_ASSERT(idev != RT_NULL);

    if (idev->trigger)
    {
        return idev->trigger(idev, type, code, value);
    }

    return -RT_ENOSYS;
}

void rt_input_event(struct rt_input_device *idev,
        rt_uint16_t type, rt_uint16_t code, rt_int32_t value)
{
    struct rt_input_event event;
    struct rt_input_handler *handler, *handler_next;

    RT_ASSERT(idev != RT_NULL);
    RT_ASSERT(type < EV_MAX);

    event.tick = rt_tick_get();
    event.type = type;
    event.code = code;
    event.value = value;

    rt_spin_lock(&idev->lock);

    rt_list_for_each_entry_safe(handler, handler_next, &idev->handler_nodes, list)
    {
        if (handler->callback(handler, &event))
        {
            break;
        }
    }

    rt_spin_unlock(&idev->lock);
}

rt_err_t rt_input_add_handler(struct rt_input_handler *handler)
{
    struct rt_input_device *idev = RT_NULL, *idev_tmp;

    if (!handler && !handler->callback)
    {
        return -RT_EINVAL;
    }

    if (!handler->idev && !handler->identify)
    {
        return -RT_EINVAL;
    }

    rt_spin_lock(&input_device_lock);

    rt_list_for_each_entry(idev_tmp, &input_device_nodes, list)
    {
        if (handler->idev)
        {
            if (handler->idev == idev_tmp)
            {
                idev = idev_tmp;
                break;
            }
        }
        else if (handler->identify(handler, idev_tmp))
        {
            idev = idev_tmp;
            break;
        }
    }

    rt_spin_unlock(&input_device_lock);

    if (!idev)
    {
        return -RT_ENOSYS;
    }

    handler->idev = idev;
    rt_list_init(&handler->list);

    rt_spin_lock(&idev->lock);
    rt_list_insert_before(&idev->handler_nodes, &handler->list);
    rt_spin_unlock(&idev->lock);

    return RT_EOK;
}

rt_err_t rt_input_del_handler(struct rt_input_handler *handler)
{
    struct rt_input_device *idev;

    if (!handler)
    {
        return -RT_EINVAL;
    }

    idev = handler->idev;

    rt_spin_lock(&idev->lock);
    rt_list_remove(&handler->list);
    rt_spin_unlock(&idev->lock);

    return RT_EOK;
}
