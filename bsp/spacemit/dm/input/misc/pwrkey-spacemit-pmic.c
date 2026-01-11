/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#define __SPACEMIT_PWRKEY_INTERNAL
#include <mfd/spacemit-pmic.h>

struct spacemit_pmic_pwrkey
{
    struct rt_input_device parent;

    int fall_irq, rise_irq;
    int s_key_irq, l_key_irq;
};

static void spacemit_pmic_pwrkey_fall_irq(int irqno, void *param)
{
    struct spacemit_pmic_pwrkey *pwr = param;

    rt_interrupt_enter();

    rt_input_report_key(&pwr->parent, KEY_POWER, 1);
    rt_input_sync(&pwr->parent);

    rt_interrupt_leave();
}

static void spacemit_pmic_pwrkey_rise_irq(int irqno, void *param)
{
    struct spacemit_pmic_pwrkey *pwr = param;

    rt_interrupt_enter();

    rt_input_report_key(&pwr->parent, KEY_POWER, 0);
    rt_input_sync(&pwr->parent);

    rt_interrupt_leave();
}

static void spacemit_pmic_pwrkey_skey_irq(int irqno, void *param)
{
    /* Do nothing by now */
}

static void spacemit_pmic_pwrkey_lkey_irq(int irqno, void *param)
{
    /* Do nothing by now */
}

static rt_err_t spacemit_pmic_pwrkey_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_pmic_pwrkey *pwr = rt_calloc(1, sizeof(*pwr));

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

    if ((pwr->s_key_irq = rt_dm_dev_get_irq(dev, 2)) < 0)
    {
        err = pwr->s_key_irq;
        goto _fail;
    }

    if ((pwr->l_key_irq = rt_dm_dev_get_irq(dev, 3)) < 0)
    {
        err = pwr->l_key_irq;
        goto _fail;
    }

    rt_input_set_capability(&pwr->parent, EV_KEY, KEY_POWER);

    if ((err = rt_input_device_register(&pwr->parent)))
    {
        goto _fail;
    }

    dev->user_data = pwr;

    rt_hw_interrupt_install(pwr->fall_irq, spacemit_pmic_pwrkey_fall_irq, pwr, "pwrkey-pmic-fall");
    rt_hw_interrupt_umask(pwr->fall_irq);

    rt_hw_interrupt_install(pwr->rise_irq, spacemit_pmic_pwrkey_rise_irq, pwr, "pwrkey-pmic-rise");
    rt_hw_interrupt_umask(pwr->rise_irq);

    rt_hw_interrupt_install(pwr->s_key_irq, spacemit_pmic_pwrkey_skey_irq, pwr, "pwrkey-pmic-skey");
    rt_hw_interrupt_umask(pwr->s_key_irq);

    rt_hw_interrupt_install(pwr->l_key_irq, spacemit_pmic_pwrkey_lkey_irq, pwr, "pwrkey-pmic-lkey");
    rt_hw_interrupt_umask(pwr->l_key_irq);

    return RT_EOK;

_fail:
    rt_free(pwr);

    return err;
}

static rt_err_t spacemit_pmic_pwrkey_remove(struct rt_platform_device *pdev)
{
    struct spacemit_pmic_pwrkey *pwr = pdev->parent.user_data;

    rt_hw_interrupt_mask(pwr->fall_irq);
    rt_pic_detach_irq(pwr->fall_irq, pwr);

    rt_hw_interrupt_mask(pwr->rise_irq);
    rt_pic_detach_irq(pwr->rise_irq, pwr);

    rt_hw_interrupt_mask(pwr->s_key_irq);
    rt_pic_detach_irq(pwr->s_key_irq, pwr);

    rt_hw_interrupt_mask(pwr->l_key_irq);
    rt_pic_detach_irq(pwr->l_key_irq, pwr);

    rt_input_device_unregister(&pwr->parent);

    rt_free(pwr);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_pmic_pwrkey_ofw_ids[] =
{
    { .compatible = "pmic,pwrkey,spm8821" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_pmic_pwrkey_driver =
{
    .name = "spacemit-pmic-pwrkey",
    .ids = spacemit_pmic_pwrkey_ofw_ids,

    .probe = spacemit_pmic_pwrkey_probe,
    .remove = spacemit_pmic_pwrkey_remove,
};
RT_PLATFORM_DRIVER_EXPORT(spacemit_pmic_pwrkey_driver);
