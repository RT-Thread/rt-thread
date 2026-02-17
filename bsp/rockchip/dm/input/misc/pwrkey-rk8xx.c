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

struct rk8xx_pwrkey
{
    struct rt_input_device parent;

    int fall_irq, rise_irq;
};

static void rk8xx_pwrkey_fall_isr(int irqno, void *param)
{
    struct rk8xx_pwrkey *pwr = param;

    rt_interrupt_enter();

    rt_input_report_key(&pwr->parent, KEY_POWER, 1);
    rt_input_sync(&pwr->parent);

    rt_interrupt_leave();
}

static void rk8xx_pwrkey_rise_isr(int irqno, void *param)
{
    struct rk8xx_pwrkey *pwr = param;

    rt_interrupt_enter();

    rt_input_report_key(&pwr->parent, KEY_POWER, 0);
    rt_input_sync(&pwr->parent);

    rt_interrupt_leave();
}

static rt_err_t rk8xx_pwrkey_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rk8xx_pwrkey *pwr = rt_calloc(1, sizeof(*pwr));

    if (!pwr)
    {
        return -RT_ENOMEM;
    }

    if ((pwr->fall_irq = rt_dm_dev_get_irq(dev, 0)) < 0)
    {
        err = pwr->fall_irq;
        goto _fail;
    }

    if ((pwr->rise_irq = rt_dm_dev_get_irq(dev, 1)) < 0)
    {
        err = pwr->rise_irq;
        goto _fail;
    }

    rt_input_set_capability(&pwr->parent, EV_KEY, KEY_POWER);

    if ((err = rt_input_device_register(&pwr->parent)))
    {
        goto _fail;
    }

    dev->user_data = pwr;

    rt_hw_interrupt_install(pwr->fall_irq, rk8xx_pwrkey_fall_isr, pwr, "pwrkey-rk8xx-fall");
    rt_hw_interrupt_umask(pwr->fall_irq);

    rt_hw_interrupt_install(pwr->rise_irq, rk8xx_pwrkey_rise_isr, pwr, "pwrkey-rk8xx-rise");
    rt_hw_interrupt_umask(pwr->rise_irq);

    return RT_EOK;

_fail:
    rt_free(pwr);

    return err;
}

static rt_err_t rk8xx_pwrkey_remove(struct rt_platform_device *pdev)
{
    struct rk8xx_pwrkey *pwr = pdev->parent.user_data;

    rt_hw_interrupt_mask(pwr->fall_irq);
    rt_pic_detach_irq(pwr->fall_irq, pwr);

    rt_hw_interrupt_mask(pwr->rise_irq);
    rt_pic_detach_irq(pwr->rise_irq, pwr);

    rt_input_device_unregister(&pwr->parent);

    rt_free(pwr);

    return RT_EOK;
}

static struct rt_platform_driver rk8xx_pwrkey_driver =
{
    .name = "rk8xx-pwrkey",
    .probe = rk8xx_pwrkey_probe,
    .remove = rk8xx_pwrkey_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rk8xx_pwrkey_driver);
