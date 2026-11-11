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

#define DBG_TAG "input.power"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct input_event_cap
{
    rt_uint16_t code;
    rt_int32_t value;
    rt_int32_t current;
};

static rt_bool_t power_input_identify(struct rt_input_handler *handler,
        struct rt_input_device *idev)
{
    struct input_event_cap *cap = handler->priv;

    if (rt_bitmap_test_bit(idev->key_map, cap->code))
    {
        if (cap->value == cap->current)
        {
            return RT_TRUE;
        }

        ++cap->current;
    }

    return RT_FALSE;
}

static rt_bool_t power_input_callback(struct rt_input_handler *handler,
        struct rt_input_event *ev)
{
    if (ev->code == KEY_POWER)
    {
        if (ev->value == 0)
        {
            rt_hw_cpu_shutdown();
        }

        return RT_TRUE;
    }
    else if (ev->code == KEY_RESTART)
    {
        if (ev->value == 0)
        {
            rt_hw_cpu_reset();
        }

        return RT_TRUE;
    }

    return RT_FALSE;
}

static rt_bool_t power_test_cap(struct rt_input_handler *handler,
        struct rt_input_device *idev)
{
    struct input_event_cap *cap = handler->priv;

    if (rt_bitmap_test_bit(idev->key_map, cap->code))
    {
        ++cap->value;
    }

    return RT_FALSE;
}

static void power_handler_install(rt_uint16_t code)
{
    rt_uint32_t idev_count;
    struct input_event_cap cap;
    struct rt_input_handler tmp_handler, *handlers;

    cap.code = code;
    cap.value = 0;
    tmp_handler.idev = RT_NULL;
    tmp_handler.identify = &power_test_cap;
    tmp_handler.callback = &power_input_callback;
    tmp_handler.priv = &cap;
    rt_input_add_handler(&tmp_handler); /* Just test */

    if (!(idev_count = cap.value))
    {
        return;
    }

    handlers = rt_calloc(idev_count, sizeof(*handlers));

    if (!handlers)
    {
        LOG_E("No memory to install power handler");
        return;
    }

    for (int i = 0; i < idev_count; ++i, ++handlers)
    {
        cap.value = i;
        cap.current = 0;

        handlers->identify = &power_input_identify;
        handlers->callback = &power_input_callback;
        handlers->priv = &cap;

        rt_input_add_handler(handlers);
        handlers->priv = RT_NULL;
    }
}

static int input_event_power_init(void)
{
    power_handler_install(KEY_POWER);
    power_handler_install(KEY_RESTART);

    return 0;
}
INIT_ENV_EXPORT(input_event_power_init);
