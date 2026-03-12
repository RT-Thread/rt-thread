/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "backlight.gpio"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct gpio_backlight
{
    struct rt_backlight_device parent;

    rt_base_t pin;
    rt_uint8_t active_val;
};

#define raw_to_gpio_backlight(raw) rt_container_of(raw, struct gpio_backlight, parent)

static rt_err_t gpio_backlight_update_status(struct rt_backlight_device *bl)
{
    rt_uint8_t brightness;
    struct gpio_backlight *gbl = raw_to_gpio_backlight(bl);

    rt_pin_mode(gbl->pin, PIN_MODE_OUTPUT);

    brightness = rt_backlight_power_brightness(bl);

    if (!gbl->active_val)
    {
        brightness = !brightness;
    }

    rt_pin_write(gbl->pin, brightness);

    return RT_EOK;
}

static struct rt_backlight_ops gpio_backlight_ops =
{
    .update_status = gpio_backlight_update_status,
};

static rt_err_t gpio_backlight_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_bool_t def_value;
    struct rt_device *dev = &pdev->parent;
    struct gpio_backlight *gbl = rt_calloc(1, sizeof(*gbl));

    if (!gbl)
    {
        return -RT_ENOMEM;
    }

    def_value = rt_dm_dev_prop_read_bool(dev, "default-on");

    gbl->pin = rt_pin_get_named_pin(dev, RT_NULL, 0, RT_NULL, &gbl->active_val);

    if (gbl->pin < 0)
    {
        err = gbl->pin;

        goto _fail;
    }

    /* Set the initial power state */
    if (!dev->ofw_node || !rt_dm_dev_prop_read_bool(dev, "phandle"))
    {
        gbl->parent.props.power = def_value ?
                RT_BACKLIGHT_POWER_UNBLANK : RT_BACKLIGHT_POWER_POWERDOWN;
    }
    else if (rt_pin_read(gbl->pin) != gbl->active_val)
    {
        gbl->parent.props.power = RT_BACKLIGHT_POWER_POWERDOWN;
    }
    else
    {
        gbl->parent.props.power = RT_BACKLIGHT_POWER_UNBLANK;
    }

    gbl->parent.props.max_brightness = 1;
    gbl->parent.ops = &gpio_backlight_ops;

    if ((err = rt_backlight_register(&gbl->parent)))
    {
        goto _fail;
    }

    rt_pin_mode(gbl->pin, PIN_MODE_OUTPUT);
    rt_backlight_set_brightness(&gbl->parent, 1);

    return RT_EOK;

_fail:
    rt_free(gbl);

    return err;
}

static rt_err_t gpio_backlight_remove(struct rt_platform_device *pdev)
{
    struct gpio_backlight *gbl = pdev->parent.user_data;

    rt_backlight_unregister(&gbl->parent);

    rt_free(gbl);

    return RT_EOK;
}

static const struct rt_ofw_node_id gpio_backlight_ofw_ids[] =
{
    { .compatible = "gpio-backlight" },
    { /* sentinel */ }
};

static struct rt_platform_driver gpio_backlight_driver =
{
    .name = "gpio-backlight",
    .ids = gpio_backlight_ofw_ids,

    .probe = gpio_backlight_probe,
    .remove = gpio_backlight_remove,
};
RT_PLATFORM_DRIVER_EXPORT(gpio_backlight_driver);
