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

struct e3x0_button
{
    struct rt_input_device parent;

    int press_irq, release_irq;
};

static void e3x0_button_press_isr(int irqno, void *param)
{
    struct e3x0_button *btn = param;

    rt_input_report_key(&btn->parent, KEY_POWER, 1);
    rt_input_sync(&btn->parent);
}

static void e3x0_button_release_isr(int irqno, void *param)
{
    struct e3x0_button *btn = param;

    rt_input_report_key(&btn->parent, KEY_POWER, 0);
    rt_input_sync(&btn->parent);
}

static rt_err_t e3x0_button_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct e3x0_button *btn = rt_calloc(1, sizeof(*btn));

    if (!btn)
    {
        return -RT_ENOMEM;
    }

    if ((btn->press_irq = rt_dm_dev_get_irq_by_name(dev, "press")) < 0)
    {
        err = btn->press_irq;
        goto _fail;
    }

    if ((btn->release_irq = rt_dm_dev_get_irq_by_name(dev, "release")) < 0)
    {
        err = btn->release_irq;
        goto _fail;
    }

    rt_input_set_capability(&btn->parent, EV_KEY, KEY_POWER);

    if ((err = rt_input_device_register(&btn->parent)))
    {
        goto _fail;
    }

    dev->user_data = btn;

    rt_hw_interrupt_install(btn->press_irq, e3x0_button_press_isr, btn, "button-e3x0-press");
    rt_hw_interrupt_umask(btn->press_irq);

    rt_hw_interrupt_install(btn->release_irq, e3x0_button_release_isr, btn, "button-e3x0-release");
    rt_hw_interrupt_umask(btn->release_irq);

    return RT_EOK;

_fail:
    rt_free(btn);

    return err;
}

static rt_err_t e3x0_button_remove(struct rt_platform_device *pdev)
{
    struct e3x0_button *btn = pdev->parent.user_data;

    rt_hw_interrupt_mask(btn->press_irq);
    rt_pic_detach_irq(btn->press_irq, btn);

    rt_hw_interrupt_mask(btn->release_irq);
    rt_pic_detach_irq(btn->release_irq, btn);

    rt_input_device_unregister(&btn->parent);

    rt_free(btn);

    return RT_EOK;
}

static const struct rt_ofw_node_id e3x0_button_ofw_ids[] =
{
    { .compatible = "ettus,e3x0-button" },
    { /* sentinel */ }
};

static struct rt_platform_driver e3x0_button_driver =
{
    .name = "e3x0-button",
    .ids = e3x0_button_ofw_ids,

    .probe = e3x0_button_probe,
    .remove = e3x0_button_remove,
};
RT_PLATFORM_DRIVER_EXPORT(e3x0_button_driver);
