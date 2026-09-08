/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#define DBG_TAG "adc.spacemit-pmic"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define __SPACEMIT_ADC_INTERNAL
#include <mfd/spacemit-pmic.h>

#define SPACEMIT_PMIC_ADC_TIMEOUT_MS 1000

struct spacemit_pmic_adc
{
    struct rt_adc_device parent;

    int irq;

    struct spacemit_pmic *pmic;
    const struct spacemit_pmic_adc_data *data;

    struct rt_mutex lock;
    struct rt_completion completion;
};

#define raw_to_spacemit_pmic_adc(raw) rt_container_of(raw, struct spacemit_pmic_adc, parent)

static rt_err_t spacemit_pmic_adc_enabled(struct rt_adc_device *device,
        rt_int8_t channel, rt_bool_t enabled)
{
    struct spacemit_pmic_adc *pmic_adc = raw_to_spacemit_pmic_adc(device);

    if (channel < 0 || channel >= pmic_adc->data->iio_desc_nr)
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t spacemit_pmic_adc_convert(struct rt_adc_device *device,
        rt_int8_t channel, rt_uint32_t *value)
{
    rt_err_t err;
    rt_uint32_t tmp, adc_val_h, adc_val_l;
    struct spacemit_pmic_adc *pmic_adc = raw_to_spacemit_pmic_adc(device);
    struct spacemit_pmic *pmic = pmic_adc->pmic;

    if (!value || channel < 0 || channel >= pmic_adc->data->iio_desc_nr)
    {
        return -RT_EINVAL;
    }

    if ((err = rt_mutex_take(&pmic_adc->lock, RT_WAITING_FOREVER)))
    {
        return err;
    }

    /* Reset the ADC auto register */
    if ((err = spacemit_pmic_update_bits(pmic, SPM8821_ADC_AUTO_REG,
            SPM8821_ADC_AUTO_BIT_MSK, 0)))
    {
        goto _out_lock;
    }

    /* Enable the ADC : ADC_CTRL[0] */
    if ((err = spacemit_pmic_update_bits(pmic, SPM8821_ADC_CTRL_REG,
            SPM8821_ADC_CTRL_BIT_MSK, (1 << SPM8821_ADC_CTRL_EN_BIT_OFFSET))))
    {
        goto _out_lock;
    }

    /* Choose the channel of adc : ADC_CFG[1] */
    if ((err = spacemit_pmic_update_bits(pmic, SPM8821_ADC_CFG1_REG,
            SPM8821_ADC_CFG1_ADC_CHNNL_SEL_BIT_MSK,
            (channel + SPM8821_ADC_EXTERNAL_CHANNEL_OFFSET) <<
                SPM8821_ADC_CFG1_ADC_CHNNL_SEL_BIT_OFFSET)))
    {
        goto _out_lock;
    }

    rt_completion_init(&pmic_adc->completion);

    /* ADC go */
    if ((err = spacemit_pmic_update_bits(pmic, SPM8821_ADC_CTRL_REG,
            SPM8821_ADC_CTRL_BIT_MSK,
            (1 << SPM8821_ADC_CTRL_GO_BIT_OFFSET)  |
                (1 << SPM8821_ADC_CTRL_EN_BIT_OFFSET))))
    {
        goto _out_lock;
    }

    err = rt_completion_wait(&pmic_adc->completion,
            rt_tick_from_millisecond(SPACEMIT_PMIC_ADC_TIMEOUT_MS));

    if (err)
    {
        unsigned long auto_reg, cfg1, cfg2, ctrl;
        unsigned long enable, result_h, result_l, status;

        ctrl = spacemit_pmic_read(pmic, SPM8821_ADC_CTRL_REG);
        cfg1 = spacemit_pmic_read(pmic, SPM8821_ADC_CFG1_REG);
        cfg2 = spacemit_pmic_read(pmic, SPM8821_ADC_CFG2_REG);
        auto_reg = spacemit_pmic_read(pmic, SPM8821_ADC_AUTO_REG);
        status = spacemit_pmic_read(pmic, SPM8821_E_STATUS_REG_BASE + 1);
        enable = spacemit_pmic_read(pmic, SPM8821_E_EN_REG_BASE + 1);
        result_h = spacemit_pmic_read(pmic,
                SPM8821_ADCIN0_RES_H_REG + channel * 2);
        result_l = spacemit_pmic_read(pmic,
                SPM8821_ADCIN0_RES_L_REG + channel * 2);

        LOG_E("ADC channel %d conversion timed out: %s", channel, rt_strerror(err));
        LOG_E("ADC regs: ctrl=%02lx cfg1=%02lx cfg2=%02lx auto=%02lx "
                "status=%02lx enable=%02lx result=%02lx:%02lx",
                ctrl, cfg1, cfg2, auto_reg, status, enable, result_h, result_l);
        goto _out_lock;
    }

    adc_val_h = spacemit_pmic_read(pmic, SPM8821_ADCIN0_RES_H_REG + channel * 2);

    if ((rt_err_t)adc_val_h < 0)
    {
        err = (rt_err_t)adc_val_h;
        goto _out_lock;
    }

    adc_val_l = spacemit_pmic_read(pmic, SPM8821_ADCIN0_RES_L_REG + channel * 2);

    if ((rt_err_t)adc_val_l < 0)
    {
        err = (rt_err_t)adc_val_l;
        goto _out_lock;
    }

    tmp = spacemit_pmic_read(pmic, SPM8821_VERSION_ID_REG);

    if ((rt_err_t)tmp < 0)
    {
        err = (rt_err_t)tmp;
        goto _out_lock;
    }

    *value = (adc_val_h << (__rt_ffs(SPM8821_ADCIN0_REG_L_BIT_MSK) - 1)) |
            ((adc_val_l & SPM8821_ADCIN0_REG_L_BIT_MSK) >>
                (__rt_ffs(SPM8821_ADCIN0_REG_L_BIT_MSK) - 1));

    if (tmp == 0)
    {
        /*
         * if the version of P1 is A, the data read from
         * the register is the inverse of the real data
         * and the conversion accuracy of P1 is 12 bits
         */
        *value = 4095 - *value;
    }

    err = RT_EOK;

_out_lock:
    rt_mutex_release(&pmic_adc->lock);

    return err;
}

static rt_uint8_t spacemit_pmic_adc_get_resolution(struct rt_adc_device *device)
{
    return 12;
}

static rt_int16_t spacemit_pmic_adc_get_vref(struct rt_adc_device *device)
{
    return 3000;
}

static const struct rt_adc_ops spacemit_pmic_adc_ops =
{
    .enabled = spacemit_pmic_adc_enabled,
    .convert = spacemit_pmic_adc_convert,
    .get_resolution = spacemit_pmic_adc_get_resolution,
    .get_vref = spacemit_pmic_adc_get_vref,
};

static void spacemit_pmic_adc_isr(int irq, void *param)
{
    struct spacemit_pmic_adc *pmic_adc = param;

    rt_completion_done(&pmic_adc->completion);
}

static rt_err_t spacemit_pmic_adc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_pmic *pmic = pdev->priv;
    struct spacemit_pmic_adc *pmic_adc = rt_calloc(1, sizeof(*pmic_adc));
    const struct spacemit_pmic_adc_data *data = pdev->id->data;

    if (!pmic_adc)
    {
        return -RT_ENOMEM;
    }

    pmic_adc->pmic = pmic;
    pmic_adc->data = data;

    if ((pmic_adc->irq = rt_dm_dev_get_irq(dev, 0)) < 0)
    {
        err = pmic_adc->irq;
        goto _fail;
    }

    /* Enable chop */
    if ((err = spacemit_pmic_update_bits(pmic,
            SPM8821_ADC_CFG1_REG,
            SPM8821_ADC_CFG1_ADC_CHOP_EN_BIT_MSK,
            1 << SPM8821_ADC_CFG1_ADC_CHOP_EN_BIT_OFFSET)))
    {
        goto _fail;
    }

    /* Set the vref: 3v3 */
    if ((err = spacemit_pmic_update_bits(pmic,
            SPM8821_ADC_CFG2_REG,
            SPM8821_ADC_CFG2_REF_SEL_BIT_MSK,
            SPM8821_ADC_CFG2_3V3_REF << SPM8821_ADC_CFG2_REF_SEL_BIT_OFFSET)))
    {
        goto _fail;
    }

    /* Set adc deb num: 7 */
    if ((err = spacemit_pmic_update_bits(pmic,
            SPM8821_ADC_CFG2_REG,
            SPM8821_ADC_CFG2_DEB_NUM_BIT_MSK,
            SPM8821_ADC_CFG2_7_DEB_NUM << SPM8821_ADC_CFG2_DEB_NUM_BIT_OFFSET)))
    {
        goto _fail;
    }

    dev->user_data = pmic_adc;

    rt_dm_dev_set_name_auto(&pmic_adc->parent.parent, "adc");
    dev_name = rt_dm_dev_get_name(&pmic_adc->parent.parent);

    if ((err = rt_mutex_init(&pmic_adc->lock, dev_name, RT_IPC_FLAG_PRIO)))
    {
        goto _fail;
    }

    rt_completion_init(&pmic_adc->completion);

    if ((err = rt_hw_adc_register(&pmic_adc->parent, dev_name,
            &spacemit_pmic_adc_ops, pmic_adc)))
    {
        rt_mutex_detach(&pmic_adc->lock);
        goto _fail;
    }

    rt_hw_interrupt_install(pmic_adc->irq, spacemit_pmic_adc_isr, pmic_adc, "adc-spacemit-pmic");
    rt_hw_interrupt_umask(pmic_adc->irq);

    rt_dm_dev_bind_fwdata(dev, RT_NULL, pmic_adc);

    return RT_EOK;

_fail:
    rt_free(pmic_adc);

    return err;
}

static rt_err_t spacemit_pmic_adc_remove(struct rt_platform_device *pdev)
{
    struct spacemit_pmic_adc *pmic_adc = pdev->parent.user_data;

    rt_hw_interrupt_mask(pmic_adc->irq);
    rt_pic_detach_irq(pmic_adc->irq, pmic_adc);

    rt_device_unregister(&pmic_adc->parent.parent);
    rt_mutex_detach(&pmic_adc->lock);

    rt_free(pmic_adc);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_pmic_adc_ofw_ids[] =
{
    { .compatible = "pmic,adc,spm8821", .data = &spm8821_adc_data },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_pmic_adc_driver =
{
    .name = "spacemit-pmic-adc",
    .ids = spacemit_pmic_adc_ofw_ids,

    .probe = spacemit_pmic_adc_probe,
    .remove = spacemit_pmic_adc_remove,
};
RT_PLATFORM_DRIVER_EXPORT(spacemit_pmic_adc_driver);
