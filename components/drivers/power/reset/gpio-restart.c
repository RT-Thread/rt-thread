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

#define DBG_TAG "reset.gpio.restart"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct gpio_restart
{
    rt_ubase_t pin;
    rt_uint8_t active_value;

    rt_uint32_t wait_delay_ms;
    rt_uint32_t active_delay_ms;
    rt_uint32_t inactive_delay_ms;
};

static rt_err_t gpio_restart_do_restart(struct rt_device *dev)
{
    struct gpio_restart *gr = dev->user_data;

    rt_pin_mode(gr->pin, PIN_MODE_OUTPUT);
    rt_thread_mdelay(gr->active_delay_ms);

    rt_pin_write(gr->pin, !gr->active_value);
    rt_thread_mdelay(gr->inactive_delay_ms);
    rt_pin_write(gr->pin, gr->active_value);

    rt_thread_mdelay(gr->wait_delay_ms);

    return RT_EOK;
}

static rt_err_t gpio_restart_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct gpio_restart *gr = rt_calloc(1, sizeof(*gr));

    if (!gr)
    {
        return -RT_ENOMEM;
    }

    gr->pin = rt_pin_get_named_pin(dev, RT_NULL, 0, RT_NULL, &gr->active_value);

    if (gr->pin < 0)
    {
        err = gr->pin;
        goto _fail;
    }

    gr->active_delay_ms = 100;
    gr->inactive_delay_ms = 100;
    gr->wait_delay_ms = 3000;

    rt_dm_dev_prop_read_u32(dev, "active-delay", &gr->active_delay_ms);
    rt_dm_dev_prop_read_u32(dev, "inactive-delay", &gr->inactive_delay_ms);
    rt_dm_dev_prop_read_u32(dev, "wait-delay", &gr->wait_delay_ms);

    dev->user_data = gr;

    if ((err = rt_dm_power_off_handler(dev, RT_DM_POWER_OFF_MODE_RESET,
            RT_DM_POWER_OFF_PRIO_DEFAULT, gpio_restart_do_restart)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_free(gr);

    return err;
}

static const struct rt_ofw_node_id gpio_restart_ofw_ids[] =
{
    { .compatible = "gpio-restart" },
    { /* sentinel */ }
};

static struct rt_platform_driver gpio_restart_driver =
{
    .name = "reset-gpio-restart",
    .ids = gpio_restart_ofw_ids,

    .probe = gpio_restart_probe,
};
RT_PLATFORM_DRIVER_EXPORT(gpio_restart_driver);
