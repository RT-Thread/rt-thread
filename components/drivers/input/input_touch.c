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

#define DBG_TAG "input.touch"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct input_touch_device
{
    struct rt_touch_device parent;
    struct rt_input_handler handler;

    rt_bool_t enabled;
    rt_uint16_t slot;
    rt_uint16_t down;
    struct rt_touch_data points[];
};

struct input_touch_properties
{
    rt_uint32_t max_x;
    rt_uint32_t max_y;
    rt_bool_t invert_x;
    rt_bool_t invert_y;
    rt_bool_t swap_x_y;

    rt_uint16_t track_id;
    rt_uint32_t num_slots;
    struct input_touch_device *touch_dev;
};

static rt_size_t input_touch_readpoint(struct rt_touch_device *touch,
        void *buf, rt_size_t touch_num)
{
    struct input_touch_device *touch_dev;

    touch_dev = rt_container_of(touch, struct input_touch_device, parent);

    rt_memcpy(buf, &touch_dev->points[touch_dev->slot], sizeof(struct rt_touch_data));

    return 1;
}

static rt_err_t input_touch_control(struct rt_touch_device *touch, int cmd, void *arg)
{
    rt_err_t err = RT_EOK;
    struct input_touch_device *touch_dev;

    if (!arg)
    {
        return -RT_EINVAL;
    }

    touch_dev = rt_container_of(touch, struct input_touch_device, parent);

    switch (cmd)
    {
    case RT_TOUCH_CTRL_GET_ID:
        *(int *)arg = 0;
        break;

    case RT_TOUCH_CTRL_GET_INFO:
        rt_memcpy(arg, &touch_dev->parent.info, sizeof(touch_dev->parent.info));
        break;

    case RT_TOUCH_CTRL_SET_X_RANGE:
        touch_dev->parent.info.range_x = *(rt_uint16_t *)arg;
        break;

    case RT_TOUCH_CTRL_SET_Y_RANGE:
        touch_dev->parent.info.range_y = *(rt_uint16_t *)arg;
        break;

    case RT_TOUCH_CTRL_SET_X_TO_Y:
        break;

    case RT_TOUCH_CTRL_DISABLE_INT:
    case RT_TOUCH_CTRL_POWER_ON:
        touch_dev->enabled = RT_FALSE;
        break;

    case RT_TOUCH_CTRL_ENABLE_INT:
    case RT_TOUCH_CTRL_POWER_OFF:
        touch_dev->enabled = RT_TRUE;
        break;

    case RT_TOUCH_CTRL_GET_STATUS:
        *(int *)arg = touch_dev->enabled;
        break;

    default:
        err = -RT_ENOSYS;
        break;
    }

    return err;
}

const static struct rt_touch_ops input_touch_ops =
{
    .touch_readpoint = input_touch_readpoint,
    .touch_control = input_touch_control,
};

static rt_bool_t input_touch_cb(struct rt_input_handler *handler,
        struct rt_input_event *ev)
{
    struct input_touch_device *touch_dev;

    touch_dev = rt_container_of(handler, struct input_touch_device, handler);

    if (touch_dev->enabled)
    {
        struct rt_touch_data *point = &touch_dev->points[touch_dev->slot];

        if (ev->type == EV_ABS)
        {
            struct rt_input_device *idev = handler->idev;
            struct rt_input_absinfo *absinfo = &idev->absinfo[touch_dev->slot];

            switch (ev->code)
            {
            case ABS_MT_SLOT:
                touch_dev->slot = ev->value;
                break;

            case ABS_MT_TRACKING_ID:
                point->timestamp = ev->tick;

                if (ev->value == (typeof(ev->code))-1)
                {
                    point->event = RT_TOUCH_EVENT_UP;

                    touch_dev->down = 0;
                    rt_hw_touch_isr(&touch_dev->parent);

                    break;
                }

                point->track_id = ev->value;
                point->event = touch_dev->down ? RT_TOUCH_EVENT_MOVE : RT_TOUCH_EVENT_DOWN;

                ++touch_dev->down;
                break;

            case ABS_MT_POSITION_X:
            case ABS_X:
                point->x_coordinate = (ev->value * touch_dev->parent.info.range_x) /
                        (absinfo->maximum - absinfo->minimum);
                break;

            case ABS_MT_POSITION_Y:
            case ABS_Y:
                point->y_coordinate = (ev->value * touch_dev->parent.info.range_y) /
                        (absinfo->maximum - absinfo->minimum);
                break;
            }
        }
        else if (ev->type == EV_SYN && ev->code == SYN_REPORT && ev->value == 0)
        {
            rt_hw_touch_isr(&touch_dev->parent);
        }
    }

    return RT_FALSE;
}

void input_touch_register(struct rt_input_device *idev)
{
    const char *dev_name;
    struct rt_touch_device *tdev;
    struct input_touch_device *touch_dev;
    struct input_touch_properties *prop = idev->touch;

    /* Only register rt_touch_device */
    if (!prop || !prop->touch_dev)
    {
        return;
    }
    touch_dev = prop->touch_dev;
    tdev = &touch_dev->parent;

    tdev->ops = &input_touch_ops;

    rt_dm_dev_set_name_auto(&tdev->parent, "touch");
    dev_name = rt_dm_dev_get_name(&tdev->parent);

    rt_hw_touch_register(tdev, dev_name, RT_DEVICE_FLAG_INT_RX, prop);

    touch_dev->enabled = RT_TRUE;
    touch_dev->handler.idev = idev;
    touch_dev->handler.callback = &input_touch_cb;
    rt_input_add_handler(&touch_dev->handler);
}

void input_touch_unregister(struct rt_input_device *idev)
{
    struct rt_touch_device *tdev;
    struct input_touch_device *touch_dev;
    struct input_touch_properties *prop = idev->touch;

    if (!prop)
    {
        return;
    }

    if (prop->touch_dev)
    {
        goto _end;
    }

    touch_dev = prop->touch_dev;
    tdev = &touch_dev->parent;

    rt_input_del_handler(&touch_dev->handler);
    rt_device_unregister(&tdev->parent);

_end:
    rt_free(idev->touch);
    idev->touch = RT_NULL;
}

static void input_touch_parse(struct rt_input_device *idev,
        rt_bool_t multitouch, struct input_touch_properties *prop)
{
    rt_bool_t present = RT_TRUE;
    rt_uint32_t axis, axis_x, axis_y;
    rt_uint32_t minimum, maximum, fuzz;
    struct rt_device *dev = &idev->parent;
    struct rt_input_absinfo *absinfo = idev->absinfo;

    axis_x = multitouch ? ABS_MT_POSITION_X : ABS_X;
    axis_y = multitouch ? ABS_MT_POSITION_Y : ABS_Y;

    if ((present = rt_dm_dev_prop_read_u32(dev, "touchscreen-min-x", &minimum)))
    {
        minimum = absinfo[axis_x].minimum;
    }

    if ((present |= rt_dm_dev_prop_read_u32(dev, "touchscreen-size-x", &maximum)))
    {
        maximum = absinfo[axis_x].maximum + 1;
    }

    if ((present |= rt_dm_dev_prop_read_u32(dev, "touchscreen-fuzz-x", &fuzz)))
    {
        fuzz = absinfo[axis_x].fuzz;
    }

    if (present)
    {
        rt_input_set_absinfo(idev, axis_x, minimum, maximum - 1, fuzz, 0);
    }

    if ((present = rt_dm_dev_prop_read_u32(dev, "touchscreen-min-y", &minimum)))
    {
        minimum = absinfo[axis_y].minimum;
    }

    if ((present |= rt_dm_dev_prop_read_u32(dev, "touchscreen-size-y", &maximum)))
    {
        maximum = absinfo[axis_y].maximum + 1;
    }

    if ((present |= rt_dm_dev_prop_read_u32(dev, "touchscreen-fuzz-y", &fuzz)))
    {
        fuzz = absinfo[axis_y].fuzz;
    }

    if (present)
    {
        rt_input_set_absinfo(idev, axis_y, minimum, maximum - 1, fuzz, 0);
    }

    axis = multitouch ? ABS_MT_PRESSURE : ABS_PRESSURE;

    if ((present = rt_dm_dev_prop_read_u32(dev, "touchscreen-max-pressure", &maximum)))
    {
        maximum = absinfo[axis].maximum;
    }

    if ((present |= rt_dm_dev_prop_read_u32(dev, "touchscreen-fuzz-pressure", &fuzz)))
    {
        fuzz = absinfo[axis].fuzz;
    }

    if (present)
    {
        rt_input_set_absinfo(idev, axis, 0, maximum, fuzz, 0);
    }

    prop->max_x = absinfo[axis_x].maximum;
    prop->max_y = absinfo[axis_y].maximum;

    prop->invert_x = rt_dm_dev_prop_read_bool(dev, "touchscreen-inverted-x");

    if (prop->invert_x)
    {
        absinfo[axis_x].maximum -= absinfo[axis_x].minimum;
        absinfo[axis_x].minimum = 0;
    }

    prop->invert_y = rt_dm_dev_prop_read_bool(dev, "touchscreen-inverted-y");

    if (prop->invert_y)
    {
        absinfo[axis_y].maximum -= absinfo[axis_y].minimum;
        absinfo[axis_y].minimum = 0;
    }

    prop->swap_x_y = rt_dm_dev_prop_read_bool(dev, "touchscreen-swapped-x-y");

    if (prop->swap_x_y)
    {
        struct rt_input_absinfo swap_absinfo;

        rt_memcpy(&swap_absinfo, &idev->absinfo[axis_x], sizeof(swap_absinfo));
        rt_memcpy(&idev->absinfo[axis_x], &idev->absinfo[axis_y], sizeof(swap_absinfo));
        rt_memcpy(&idev->absinfo[axis_y], &swap_absinfo, sizeof(swap_absinfo));
    }
}

rt_err_t rt_input_setup_touch(struct rt_input_device *idev,
        rt_uint32_t num_slots, struct rt_touch_info *info)
{
    rt_size_t alloc_size;
    rt_bool_t multitouch;
    struct input_touch_device *touch_dev;
    struct input_touch_properties *prop;

    if (!idev || idev->touch)
    {
        return -RT_EINVAL;
    }

    multitouch = !!num_slots;
    alloc_size = sizeof(*prop);

    if (info)
    {
        alloc_size += sizeof(*touch_dev);
        alloc_size += sizeof(*touch_dev->points) * rt_max_t(rt_uint32_t, num_slots, 1);
    }

    if (!(prop = rt_calloc(1, alloc_size)))
    {
        return -RT_ENOMEM;
    }
    idev->touch = prop;

    if ((prop->num_slots = num_slots))
    {
        rt_input_set_absinfo(idev, ABS_MT_SLOT, 0, num_slots - 1, 0, 0);
        rt_input_set_absinfo(idev, ABS_MT_TRACKING_ID, 0, RT_UINT16_MAX, 0, 0);
    }

    input_touch_parse(idev, multitouch, prop);

    if (info)
    {
        rt_size_t points_nr = rt_max_t(rt_uint32_t, num_slots, 1);

        touch_dev = (void *)prop + sizeof(*prop);
        prop->touch_dev = touch_dev;

        for (int i = 0; i < points_nr; ++i)
        {
            touch_dev->points[i].width = 1;
        }

        rt_memcpy(&touch_dev->parent.info, info, sizeof(*info));

        info = &touch_dev->parent.info;
        info->point_num = info->point_num ? : prop->num_slots;
        info->range_x = info->range_x ? : prop->max_x;
        info->range_y = info->range_y ? : prop->max_y;
    }

    return RT_EOK;
}

rt_err_t rt_input_parse_touch_position(struct rt_input_device *idev,
        rt_uint32_t *out_x, rt_uint32_t *out_y)
{
    struct input_touch_properties *prop;

    RT_ASSERT(idev != RT_NULL);
    RT_ASSERT(out_x != RT_NULL);
    RT_ASSERT(out_y != RT_NULL);

    prop = idev->touch;

    if (prop->invert_x)
    {
        *out_x = prop->max_x - *out_x;
    }

    if (prop->invert_y)
    {
        *out_y = prop->max_y - *out_y;
    }

    if (prop->swap_x_y)
    {
        *out_x ^= *out_y;
        *out_y ^= *out_x;
        *out_x ^= *out_y;
    }

    return RT_EOK;
}

rt_bool_t rt_input_report_touch_inactive(struct rt_input_device *idev,
        rt_bool_t active)
{
    struct input_touch_properties *prop;

    RT_ASSERT(idev != RT_NULL);

    prop = idev->touch;

    if (!active)
    {
        rt_input_event(idev, EV_ABS, ABS_MT_TRACKING_ID, -1);

        return RT_FALSE;
    }

    rt_input_event(idev, EV_ABS, ABS_MT_TRACKING_ID, prop->track_id++);

    return RT_TRUE;
}

void rt_input_report_touch_position(struct rt_input_device *idev,
        rt_uint32_t x, rt_uint32_t y, rt_bool_t multitouch)
{
    RT_ASSERT(idev != RT_NULL);

    rt_input_parse_touch_position(idev, &x, &y);
    rt_input_report_abs(idev, multitouch ? ABS_MT_POSITION_X : ABS_X, x);
    rt_input_report_abs(idev, multitouch ? ABS_MT_POSITION_Y : ABS_Y, y);
}
