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

#define DBG_TAG "reset.gpio.poweroff"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct gpio_poweroff
{
    rt_ubase_t pin;
    rt_uint8_t active_value;

    rt_uint32_t timeout_ms;
    rt_uint32_t active_delay_ms;
    rt_uint32_t inactive_delay_ms;
};

static rt_err_t gpio_poweroff_do_poweroff(struct rt_device *dev)
{
    struct gpio_poweroff *gp = dev->user_data;

    rt_pin_mode(gp->pin, PIN_MODE_OUTPUT);
    rt_thread_mdelay(gp->active_delay_ms);

    rt_pin_write(gp->pin, !gp->active_value);
    rt_thread_mdelay(gp->inactive_delay_ms);
    rt_pin_write(gp->pin, gp->active_value);

    rt_thread_mdelay(gp->timeout_ms);

    return RT_EOK;
}

static rt_err_t gpio_poweroff_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct gpio_poweroff *gp = rt_calloc(1, sizeof(*gp));

    if (!gp)
    {
        return -RT_ENOMEM;
    }

    gp->pin = rt_pin_get_named_pin(dev, RT_NULL, 0, RT_NULL, &gp->active_value);

    if (gp->pin < 0)
    {
        err = gp->pin;
        goto _fail;
    }

    gp->active_delay_ms = 100;
    gp->inactive_delay_ms = 100;
    gp->timeout_ms = 3000;

    rt_dm_dev_prop_read_u32(dev, "active-delay-ms", &gp->active_delay_ms);
    rt_dm_dev_prop_read_u32(dev, "inactive-delay-ms", &gp->inactive_delay_ms);
    rt_dm_dev_prop_read_u32(dev, "timeout-ms", &gp->timeout_ms);

    dev->user_data = gp;

    if ((err = rt_dm_power_off_handler(dev, RT_DM_POWER_OFF_MODE_SHUTDOWN,
            RT_DM_POWER_OFF_PRIO_DEFAULT, gpio_poweroff_do_poweroff)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_free(gp);

    return err;
}

static const struct rt_ofw_node_id gpio_poweroff_ofw_ids[] =
{
    { .compatible = "gpio-poweroff" },
    { /* sentinel */ }
};

static struct rt_platform_driver gpio_poweroff_driver =
{
    .name = "reset-gpio-poweroff",
    .ids = gpio_poweroff_ofw_ids,

    .probe = gpio_poweroff_probe,
};
RT_PLATFORM_DRIVER_EXPORT(gpio_poweroff_driver);
