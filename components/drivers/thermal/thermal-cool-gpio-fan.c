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

#define DBG_TAG "thermal.cool.gpio-fan"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct gpio_fan_desc
{
    rt_base_t pin;
    rt_uint8_t active_val;
};

struct gpio_fan_speed
{
    rt_uint32_t rpm;
    rt_uint32_t ctrl_val;
};

struct gpio_fan_cool
{
    struct rt_thermal_cooling_device parent;

    rt_size_t pins_nr;
    struct gpio_fan_desc *pins_desc;

    rt_size_t speed_nr;
    rt_size_t speed_cur;
    struct gpio_fan_speed *speed;

    struct rt_mutex lock;
};

#define raw_to_gpio_fan_cool(raw) rt_container_of(raw, struct gpio_fan_cool, parent)

static rt_err_t gpio_fan_cool_set_speed(struct gpio_fan_cool *gf_cool, rt_size_t speed_idx)
{
    rt_uint32_t ctrl_val = gf_cool->speed[speed_idx].ctrl_val;

    for (int i = 0; i < gf_cool->pins_nr; ++i)
    {
        rt_uint8_t value = (ctrl_val >> i) & 1;

        if (gf_cool->pins_desc[i].active_val)
        {
            value = !value;
        }

        rt_pin_mode(gf_cool->pins_desc[i].pin, PIN_MODE_OUTPUT);
        rt_pin_write(gf_cool->pins_desc[i].pin, value);
    }

    gf_cool->speed_cur = speed_idx;

    return RT_EOK;
}

static rt_size_t gpio_fan_cool_get_speed(struct gpio_fan_cool *gf_cool)
{
    rt_uint32_t ctrl_val = 0;

    for (int i = 0; i < gf_cool->pins_nr; ++i)
    {
        rt_uint32_t value;

        rt_pin_mode(gf_cool->pins_desc[i].pin, PIN_MODE_INPUT);
        value = rt_pin_read(gf_cool->pins_desc[i].pin);

        if (gf_cool->pins_desc[i].active_val)
        {
            value = !value;
        }

        ctrl_val |= (value << i);
    }

    for (int i = 0; i < gf_cool->speed_nr; ++i)
    {
        if (gf_cool->speed[i].ctrl_val == ctrl_val)
        {
            return i;
        }
    }

    return 0;
}

static rt_err_t gpio_fan_cool_get_max_level(struct rt_thermal_cooling_device *cdev,
        rt_ubase_t *out_level)
{
    struct gpio_fan_cool *gf_cool = raw_to_gpio_fan_cool(cdev);

    *out_level = gf_cool->speed_nr - 1;

    return RT_EOK;
}

static rt_err_t gpio_fan_cool_get_cur_level(struct rt_thermal_cooling_device *cdev,
        rt_ubase_t *out_level)
{
    struct gpio_fan_cool *gf_cool = raw_to_gpio_fan_cool(cdev);

    *out_level = gf_cool->speed_cur;

    return RT_EOK;
}

static rt_err_t gpio_fan_cool_set_cur_level(struct rt_thermal_cooling_device *cdev,
        rt_ubase_t level)
{
    rt_err_t err;
    struct gpio_fan_cool *gf_cool = raw_to_gpio_fan_cool(cdev);

    if (level >= gf_cool->speed_nr)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&gf_cool->lock, RT_WAITING_FOREVER);

    if (gf_cool->speed_cur == level)
    {
        rt_mutex_release(&gf_cool->lock);

        return RT_EOK;
    }

    err = gpio_fan_cool_set_speed(gf_cool, level);

    rt_mutex_release(&gf_cool->lock);

    return err;
}

const static struct rt_thermal_cooling_device_ops gpio_fan_cool_ops =
{
    .get_max_level = gpio_fan_cool_get_max_level,
    .get_cur_level = gpio_fan_cool_get_cur_level,
    .set_cur_level = gpio_fan_cool_set_cur_level,
};

static void gpio_fan_cool_free(struct gpio_fan_cool *gf_cool)
{
    if (gf_cool->pins_desc)
    {
        rt_free(gf_cool->pins_desc);

        if (gf_cool->speed)
        {
            rt_free(gf_cool->speed);
        }
    }

    rt_mutex_detach(&gf_cool->lock);

    rt_free(gf_cool);
}

static rt_err_t gpio_fan_cool_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const fdt32_t *cell = RT_NULL;
    rt_uint32_t value = 0;
    struct rt_ofw_prop *prop;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node;
    struct gpio_fan_cool *gf_cool = rt_calloc(1, sizeof(*gf_cool));

    if (!gf_cool)
    {
        return -RT_ENOMEM;
    }

    rt_mutex_init(&gf_cool->lock, rt_dm_dev_get_name(dev), RT_IPC_FLAG_PRIO);

    gf_cool->pins_nr = rt_ofw_get_named_pin_count(np, RT_NULL);

    if (gf_cool->pins_nr <= 0)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    gf_cool->pins_desc = rt_malloc(sizeof(*gf_cool->pins_desc) * gf_cool->pins_nr);

    if (!gf_cool->pins_desc)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    for (int i = 0; i < gf_cool->pins_nr; ++i)
    {
        gf_cool->pins_desc[i].pin = rt_ofw_get_named_pin(np, RT_NULL, i, RT_NULL,
                &gf_cool->pins_desc[i].active_val);

        if (gf_cool->pins_desc[i].pin < 0)
        {
            err = -RT_EINVAL;
            goto _fail;
        }
    }

    prop = rt_ofw_get_prop(np, "gpio-fan,speed-map", (rt_ssize_t *)&gf_cool->speed_nr);

    if (!prop)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    gf_cool->speed_nr /= (sizeof(rt_uint32_t) * 2);

    if (!gf_cool->speed_nr)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    gf_cool->speed = rt_malloc(sizeof(*gf_cool->speed) * gf_cool->speed_nr);

    if (!gf_cool->speed)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    for (int i = 0; i < gf_cool->speed_nr; ++i)
    {
        cell = rt_ofw_prop_next_u32(prop, cell, &value);
        gf_cool->speed[i].rpm = value;

        cell = rt_ofw_prop_next_u32(prop, cell, &value);
        gf_cool->speed[i].ctrl_val = value;
    }

    gf_cool->speed_cur = gpio_fan_cool_get_speed(gf_cool);

    rt_dm_dev_set_name(&gf_cool->parent.parent, "%s", rt_dm_dev_get_name(&pdev->parent));
    gf_cool->parent.parent.ofw_node = dev->ofw_node;
    gf_cool->parent.ops = &gpio_fan_cool_ops;

    if ((err = rt_thermal_cooling_device_register(&gf_cool->parent)))
    {
        goto _fail;
    }

    dev->user_data = gf_cool;

    return RT_EOK;

_fail:
    gpio_fan_cool_free(gf_cool);

    return err;
}

static rt_err_t gpio_fan_cool_remove(struct rt_platform_device *pdev)
{
    struct gpio_fan_cool *gf_cool = pdev->parent.user_data;

    rt_thermal_cooling_device_unregister(&gf_cool->parent);

    gpio_fan_cool_set_speed(gf_cool, 0);
    gpio_fan_cool_free(gf_cool);

    return RT_EOK;
}

static rt_err_t gpio_fan_cool_shutdown(struct rt_platform_device *pdev)
{
    return gpio_fan_cool_remove(pdev);
}

static const struct rt_ofw_node_id gpio_fan_cool_ofw_ids[] =
{
    { .compatible = "gpio-fan" },
    { /* sentinel */ }
};

static struct rt_platform_driver gpio_fan_cool_driver =
{
    .name = "gpio-fan-cool",
    .ids = gpio_fan_cool_ofw_ids,

    .probe = gpio_fan_cool_probe,
    .remove = gpio_fan_cool_remove,
    .shutdown = gpio_fan_cool_shutdown,
};
RT_PLATFORM_DRIVER_EXPORT(gpio_fan_cool_driver);
