/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __BACKLIGHT_H__
#define __BACKLIGHT_H__

#include <rthw.h>
#include <rtdef.h>

struct rt_backlight_ops;

enum rt_backlight_power
{
    RT_BACKLIGHT_POWER_UNBLANK,
    RT_BACKLIGHT_POWER_NORMAL,
    RT_BACKLIGHT_POWER_SUSPEND,
    RT_BACKLIGHT_POWER_POWERDOWN,

    RT_BACKLIGHT_POWER_NR,
};

struct rt_backlight_properties
{
    rt_uint32_t brightness;
    rt_uint32_t max_brightness;

    enum rt_backlight_power power;
};

struct rt_backlight_device
{
    struct rt_device parent;

    struct rt_backlight_properties props;

    const struct rt_backlight_ops *ops;

    struct rt_mutex lock;
    void *priv;
};

struct rt_backlight_ops
{
    rt_err_t (*update_status)(struct rt_backlight_device *);
    rt_err_t (*get_brightness)(struct rt_backlight_device *, rt_uint32_t *out_brightness);
};

rt_err_t rt_backlight_register(struct rt_backlight_device *bl);
rt_err_t rt_backlight_unregister(struct rt_backlight_device *bl);

rt_err_t rt_backlight_set_power(struct rt_backlight_device *bl, enum rt_backlight_power power);
rt_err_t rt_backlight_get_power(struct rt_backlight_device *bl, enum rt_backlight_power *out_power);
rt_err_t rt_backlight_set_brightness(struct rt_backlight_device *bl, rt_uint32_t brightness);
rt_err_t rt_backlight_get_brightness(struct rt_backlight_device *bl, rt_uint32_t *out_brightness);

rt_inline rt_uint32_t rt_backlight_power_brightness(struct rt_backlight_device *bl)
{
    if (bl->props.power != RT_BACKLIGHT_POWER_UNBLANK)
    {
        return 0;
    }

    return bl->props.brightness;
}

#endif /* __BACKLIGHT_H__ */
