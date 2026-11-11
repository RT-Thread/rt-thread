/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <rpi-sense.h>

struct rpisense_joystick
{
    struct rt_input_device parent;
    struct rpisense *rpisense;

    rt_base_t pin;
    rt_uint8_t active_val;
    rt_int32_t prev_keys;

    struct rt_thread *keys_task;
};

static rt_uint8_t keymap[5] =
{
    KEY_DOWN, KEY_RIGHT, KEY_UP, KEY_ENTER, KEY_LEFT
};

static void rpisense_keys_task(void *param)
{
    rt_int32_t keys, changes;
    struct rpisense_joystick *rpisense_js = param;

    while (RT_TRUE)
    {
        rt_thread_suspend(rpisense_js->keys_task);
        rt_schedule();

        keys = rpisense_reg_read(rpisense_js->rpisense, RPISENSE_KEYS);
        changes = keys ^ rpisense_js->prev_keys;
        rpisense_js->prev_keys = keys;

        for (int i = 0; i < RT_ARRAY_SIZE(keymap); ++i)
        {
            if (changes & 1)
            {
                rt_input_report_key(&rpisense_js->parent, keymap[i], keys & 1);
            }

            changes >>= 1;
            keys >>= 1;
        }

        rt_input_sync(&rpisense_js->parent);
    }
}

static void rpisense_isr(void *args)
{
    struct rpisense_joystick *rpisense_js = args;

    rt_thread_resume(rpisense_js->keys_task);
}

static rt_err_t rpisense_js_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rpisense *rpisense = pdev->priv;
    struct rpisense_joystick *rpisense_js = rt_calloc(1, sizeof(*rpisense_js));

    if (!rpisense_js)
    {
        return -RT_ENOMEM;
    }

    rpisense_js->rpisense = rpisense;
    rpisense_js->pin = rt_pin_get_named_pin(&rpisense->i2c_client->parent,
            "keys-int", 0, RT_NULL, &rpisense_js->active_val);

    if (rpisense_js->pin < 0)
    {
        err = rpisense_js->pin;
        goto _fail;
    }

    rt_pin_write(rpisense_js->pin, rpisense_js->active_val);
    rt_pin_mode(rpisense_js->pin, PIN_MODE_INPUT);
    rt_pin_attach_irq(rpisense_js->pin, PIN_IRQ_MODE_RISING, rpisense_isr, rpisense_js);
    rt_pin_irq_enable(rpisense_js->pin, RT_TRUE);

    for (int i = 0; i < RT_ARRAY_SIZE(keymap); ++i)
    {
        rt_input_set_capability(&rpisense_js->parent, EV_KEY, keymap[i]);
    }

    if ((err = rt_input_device_register(&rpisense_js->parent)))
    {
        goto _fail;
    }

    rpisense_js->keys_task = rt_thread_create("rpisense-js", &rpisense_keys_task,
            rpisense_js, DM_THREAD_STACK_SIZE, RT_THREAD_PRIORITY_MAX / 2, 10);

    if (!rpisense_js->keys_task)
    {
        rt_input_device_unregister(&rpisense_js->parent);
        goto _fail;
    }

    pdev->parent.user_data = rpisense_js;

    rt_thread_startup(rpisense_js->keys_task);

    return RT_EOK;

_fail:
    if (rpisense_js->pin >= 0)
    {
        rt_pin_detach_irq(rpisense_js->pin);
    }

    rt_free(rpisense_js);

    return err;
}

static rt_err_t rpisense_js_remove(struct rt_platform_device *pdev)
{
    struct rpisense_joystick *rpisense_js = pdev->parent.user_data;

    rt_pin_irq_enable(rpisense_js->pin, RT_FALSE);
    rt_pin_detach_irq(rpisense_js->pin);

    rt_thread_delete(rpisense_js->keys_task);

    rt_input_device_unregister(&rpisense_js->parent);

    rt_free(rpisense_js);

    return RT_EOK;
}

static struct rt_platform_driver rpisense_js_driver =
{
    .name = "rpi-sense-js",

    .probe = rpisense_js_probe,
    .remove = rpisense_js_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rpisense_js_driver);
