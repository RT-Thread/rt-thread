/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __INPUT_H__
#define __INPUT_H__

#include <rtthread.h>

#include <bitmap.h>
#include <drivers/touch.h>
#include <dt-bindings/input/event-codes.h>

struct rt_input_poller;
struct rt_input_absinfo;

struct rt_input_event
{
    rt_tick_t tick;

    rt_uint16_t type;
    rt_uint16_t code;
    rt_int32_t value;
};

struct rt_input_device
{
    struct rt_device parent;

    RT_BITMAP_DECLARE(cap, EV_CNT);
    RT_BITMAP_DECLARE(key_map, KEY_CNT);
    RT_BITMAP_DECLARE(rel_map, REL_CNT);
    RT_BITMAP_DECLARE(abs_map, ABS_CNT);

    rt_list_t list;
    rt_list_t handler_nodes;
    struct rt_spinlock lock;

    rt_err_t (*trigger)(struct rt_input_device *idev,
            rt_uint16_t type, rt_uint16_t code, rt_int32_t value);

    struct rt_input_poller *poller;
    struct rt_input_absinfo *absinfo;
#ifdef RT_INPUT_TOUCHSCREEN
    void *touch;
#endif
};

struct rt_input_handler
{
    rt_list_t list;
    struct rt_input_device *idev;

    rt_bool_t (*identify)(struct rt_input_handler *handler, struct rt_input_device *idev);
    rt_bool_t (*callback)(struct rt_input_handler *handler, struct rt_input_event *ev);

    void *priv;
};

struct rt_input_poller
{
#define RT_INPUT_POLL_INTERVAL_DEFAULT  17  /* 60fps */
    rt_uint32_t interval;
    struct rt_timer timer;

    void (*poll)(struct rt_input_device *idev);
};

struct rt_input_absinfo
{
    rt_int32_t value;
    rt_int32_t minimum;
    rt_int32_t maximum;
    rt_int32_t fuzz;
    rt_int32_t flat;
    rt_int32_t resolution;
};

rt_err_t rt_input_device_register(struct rt_input_device *idev);
rt_err_t rt_input_device_unregister(struct rt_input_device *idev);

rt_err_t rt_input_set_capability(struct rt_input_device *idev,
        rt_uint16_t type, rt_uint16_t code);

rt_err_t rt_input_set_absinfo(struct rt_input_device *idev, rt_uint32_t axis,
        rt_int32_t min, rt_int32_t max, rt_int32_t fuzz, rt_int32_t flat);

rt_err_t rt_input_setup_touch(struct rt_input_device *idev,
        rt_uint32_t num_slots, struct rt_touch_info *info);
rt_err_t rt_input_parse_touch_position(struct rt_input_device *idev,
        rt_uint32_t *out_x, rt_uint32_t *out_y);

rt_err_t rt_input_setup_polling(struct rt_input_device *idev,
        void (*work)(struct rt_input_device *idev));
rt_err_t rt_input_set_poll_interval(struct rt_input_device *idev,
        rt_uint32_t interval_ms);

rt_err_t rt_input_trigger(struct rt_input_device *idev,
        rt_uint16_t type, rt_uint16_t code, rt_int32_t value);

void rt_input_event(struct rt_input_device *idev,
        rt_uint16_t type, rt_uint16_t code, rt_int32_t value);

rt_inline void rt_input_report_key(struct rt_input_device *idev,
        rt_uint16_t code, rt_int32_t value)
{
    rt_input_event(idev, EV_KEY, code, !!value);
}

rt_inline void rt_input_report_rel(struct rt_input_device *idev,
        rt_uint16_t code, rt_int32_t value)
{
    rt_input_event(idev, EV_REL, code, value);
}

rt_inline void rt_input_report_abs(struct rt_input_device *idev,
        rt_uint16_t code, rt_int32_t value)
{
    rt_input_event(idev, EV_ABS, code, value);
}

rt_inline void rt_input_report_touch_slot(struct rt_input_device *idev,
        rt_uint32_t slot)
{
    rt_input_event(idev, EV_ABS, ABS_MT_SLOT, slot);
}

rt_bool_t rt_input_report_touch_inactive(struct rt_input_device *idev,
        rt_bool_t active);

void rt_input_report_touch_position(struct rt_input_device *idev,
        rt_uint32_t x, rt_uint32_t y, rt_bool_t multitouch);

rt_inline void rt_input_sync(struct rt_input_device *idev)
{
    rt_input_event(idev, EV_SYN, SYN_REPORT, 0);
}

rt_err_t rt_input_add_handler(struct rt_input_handler *handler);
rt_err_t rt_input_del_handler(struct rt_input_handler *handler);

#endif /* __INPUT_H__ */
