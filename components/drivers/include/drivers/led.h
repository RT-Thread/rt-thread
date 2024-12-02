/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __LED_H__
#define __LED_H__

#include <rthw.h>
#include <rtdef.h>

struct rt_led_ops;

enum rt_led_state
{
    RT_LED_S_OFF,
    RT_LED_S_ON,
    RT_LED_S_TOGGLE,
    RT_LED_S_BLINK,

    RT_LED_STATE_NR,
};

struct rt_led_device
{
    struct rt_device parent;

    const struct rt_led_ops *ops;

    struct rt_spinlock spinlock;

    void *sysdata;
    void *priv;
};

struct rt_led_ops
{
    rt_err_t (*set_state)(struct rt_led_device *led, enum rt_led_state state);
    rt_err_t (*get_state)(struct rt_led_device *led, enum rt_led_state *out_state);
    rt_err_t (*set_period)(struct rt_led_device *led, rt_uint32_t period_ms);
    rt_err_t (*set_brightness)(struct rt_led_device *led, rt_uint32_t brightness);
};

rt_err_t rt_hw_led_register(struct rt_led_device *led);
rt_err_t rt_hw_led_unregister(struct rt_led_device *led);

rt_err_t rt_led_set_state(struct rt_led_device *led, enum rt_led_state state);
rt_err_t rt_led_get_state(struct rt_led_device *led, enum rt_led_state *out_state);
rt_err_t rt_led_set_period(struct rt_led_device *led, rt_uint32_t period_ms);
rt_err_t rt_led_set_brightness(struct rt_led_device *led, rt_uint32_t brightness);

#endif /* __LED_H__ */
