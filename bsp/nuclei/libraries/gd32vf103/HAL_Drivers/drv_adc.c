/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-03     hqfang       the first version.
 *
 */
#include "drv_adc.h"

#ifdef BSP_USING_ADC

#if !defined(BSP_USING_ADC0) && !defined(BSP_USING_ADC1)
    #error "Please define at least one BSP_USING_ADCx"
    /* this driver can be disabled at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable ADC */
#endif


static struct gd32_adc_config adc_config[] =
{
#ifdef BSP_USING_ADC0
    {
        "adc0",
        ADC0,
    },
#endif
#ifdef BSP_USING_ADC1
    {
        "adc1",
        ADC1,
    },
#endif
};

static struct gd32_adc adc_obj[sizeof(adc_config) / sizeof(adc_config[0])] = {0};

static void gd32_adc_init(struct gd32_adc_config *config)
{
    RT_ASSERT(config != RT_NULL);
    adc_deinit(config->adc_periph);

    ADC_CTL0(config->adc_periph) &= ~(ADC_CTL0_SYNCM);
    ADC_CTL0(config->adc_periph) |= ADC_MODE_FREE;

    ADC_CTL1(config->adc_periph) |= ADC_CTL1_TSVREN;

    adc_resolution_config(config->adc_periph, ADC_RESOLUTION_12B);
    /* ADC contineous function enable */
    adc_special_function_config(config->adc_periph, ADC_SCAN_MODE, ENABLE);
    /* ADC data alignment config */
    adc_data_alignment_config(config->adc_periph, ADC_DATAALIGN_RIGHT);
    /* ADC channel length config */
    adc_channel_length_config(config->adc_periph, ADC_REGULAR_CHANNEL, 1);
    adc_external_trigger_source_config(config->adc_periph, ADC_REGULAR_CHANNEL, ADC0_1_EXTTRIG_REGULAR_NONE);

    /* ADC enable */
    adc_external_trigger_config(config->adc_periph, ADC_REGULAR_CHANNEL, ENABLE);
    adc_enable(config->adc_periph);

    adc_calibration_enable(config->adc_periph);
}

static rt_err_t gd32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    if (channel > ADC_CHANNEL_17)
    {
        return RT_EINVAL;
    }
    return RT_EOK;
}

static rt_err_t gd32_adc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    struct gd32_adc_config *config;
    RT_ASSERT(device != RT_NULL);

    if (channel > ADC_CHANNEL_17)
    {
        return RT_EINVAL;
    }
    config = (struct gd32_adc_config *)(device->parent.user_data);

    if (channel > ADC_CHANNEL_15)
    {
        adc_regular_channel_config(config->adc_periph, 0, channel, ADC_SAMPLETIME_239POINT5);
    }
    else
    {
        adc_regular_channel_config(config->adc_periph, 0, channel, ADC_SAMPLETIME_55POINT5);
    }
    adc_software_trigger_enable(config->adc_periph, ADC_REGULAR_CHANNEL);

    while (SET != adc_flag_get(config->adc_periph, ADC_FLAG_EOC));
    adc_flag_clear(config->adc_periph, ADC_FLAG_EOC);

    *value = ADC_RDATA(config->adc_periph);

    return RT_EOK;
}

static struct rt_adc_ops gd32_adc_ops =
{
    .enabled = gd32_adc_enabled,
    .convert = gd32_adc_convert,
};

int rt_hw_adc_init(void)
{
    int i = 0;
    int result = RT_EOK;

#if defined(BSP_USING_ADC0)
    rcu_periph_clock_enable(RCU_ADC0);
#endif
#if defined(BSP_USING_ADC1)
    rcu_periph_clock_enable(RCU_ADC1);
#endif

    rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV8);

    for (i = 0; i < sizeof(adc_obj) / sizeof(adc_obj[0]); i++)
    {
        adc_obj[i].config = &adc_config[i];
        gd32_adc_init(&adc_config[i]);
        rt_hw_adc_register(&adc_obj[i].adc_device, \
                           adc_obj[i].config->name, &gd32_adc_ops, adc_obj[i].config);
    }

    return result;
}

INIT_DEVICE_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */

