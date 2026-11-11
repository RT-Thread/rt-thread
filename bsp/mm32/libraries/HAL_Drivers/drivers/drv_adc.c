/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtdevice.h>
#include "board.h"
#include "drv_adc.h"
#include <hal_gpio.h>
#include <hal_adc.h>
#include <hal_rcc.h>
#include <hal_misc.h>

#if defined(BSP_USING_ADC)

#define LOG_TAG             "drv.adc"
#include <rtdbg.h>

#if defined(SOC_SERIES_MM32F327)
#define ADC_CONFIG_GPIORCC     RCC_AHBENR_GPIOA
#define ADC_CONFIG_GPIOX       GPIOA
#define ADC_CONFIG_IOX         (GPIO_Pin_5 | GPIO_Pin_4)
#endif

struct mm32_adc
{
    struct rt_adc_device device;
    ADC_TypeDef *instance;
    const char *name;
};

static struct mm32_adc adc_obj[] =
{
#if defined(BSP_USING_ADC1)
    {
        .instance = ADC1,
        .name = "adc1",
    },
#endif
#if defined(BSP_USING_ADC2)
    {
        .instance = ADC2,
        .name = "adc2",
    },
#endif
};

static void mm32_adc_channel_enable(ADC_TypeDef *adc, rt_uint32_t channel)
{
#if defined(SOC_SERIES_MM32F526)
    adc->ADCHS &= ~(1UL << channel);
    adc->ADCHS |= (1UL << channel);
#elif defined(SOC_SERIES_MM32F327)
    adc->CHSR &= ~(1UL << channel);
    adc->CHSR |= (1UL << channel);
#else
#error "Unsupported MM32 ADC series"
#endif
}

static void mm32_adc_clock_enable(ADC_TypeDef *adc, rt_bool_t enabled)
{
#if defined(SOC_SERIES_MM32F526)
    if (adc == ADC1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, enabled ? ENABLE : DISABLE);
    }
#ifdef ADC2
    else if (adc == ADC2)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, enabled ? ENABLE : DISABLE);
    }
#endif
#elif defined(SOC_SERIES_MM32F327)
    if (adc == ADC1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC1, enabled ? ENABLE : DISABLE);
    }
#ifdef ADC2
    else if (adc == ADC2)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC2, enabled ? ENABLE : DISABLE);
    }
#endif
#endif
}

static void mm32_adc_hw_config(ADC_TypeDef *adc, rt_uint32_t channel)
{
    ADC_InitTypeDef init;
#if defined(SOC_SERIES_MM32F327)
    GPIO_InitTypeDef gpio_init;
#endif

#if defined(SOC_SERIES_MM32F526)
    mm32_msp_adc_init((void *)adc);
    ADC_CalibrationConfig(adc, 0x1FE);
#else
    mm32_adc_clock_enable(adc, RT_TRUE);
#endif

    ADC_StructInit(&init);
    init.ADC_Resolution = ADC_Resolution_12b;
    init.ADC_DataAlign = ADC_DataAlign_Right;

#if defined(SOC_SERIES_MM32F526)
    init.ADC_Prescaler = ADC_Prescaler_16;
    init.ADC_Mode = ADC_Mode_Scan;
    ADC_Init(adc, &init);
    ADC_SampleTimeConfig(adc, channel, ADC_SampleTime_240_5);
    ADC_ChannelCmd(adc, channel, ENABLE);
    ADC_DifferentialConversionConfig(adc, ADC_Pseudo_Differential_Conversion_4_5);
#elif defined(SOC_SERIES_MM32F327)
    init.ADC_PRESCARE = ADC_PCLK2_PRESCARE_16;
    init.ADC_Mode = ADC_Mode_Continue;
    init.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    ADC_Init(adc, &init);
    ADC_RegularChannelConfig(adc, channel, 0, ADC_Samctl_239_5);

    GPIO_StructInit(&gpio_init);
    RCC_AHBPeriphClockCmd(ADC_CONFIG_GPIORCC, ENABLE);
    gpio_init.GPIO_Pin = ADC_CONFIG_IOX;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(ADC_CONFIG_GPIOX, &gpio_init);
#endif

    ADC_Cmd(adc, ENABLE);
    mm32_adc_channel_enable(adc, channel);
}

static rt_err_t mm32_adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    ADC_TypeDef *adc;

    RT_ASSERT(device != RT_NULL);
    adc = device->parent.user_data;

    if (enabled)
    {
        mm32_adc_hw_config(adc, (rt_uint32_t)channel);
    }
    else
    {
        ADC_DeInit(adc);
        ADC_Cmd(adc, DISABLE);
        mm32_adc_clock_enable(adc, RT_FALSE);
    }

    return RT_EOK;
}

static rt_err_t mm32_adc_get_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    ADC_TypeDef *adc;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);
    adc = device->parent.user_data;

    ADC_SoftwareStartConvCmd(adc, ENABLE);

#if defined(SOC_SERIES_MM32F526)
    while (ADC_GetFlagStatus(adc, ADC_FLAG_EOC) == 0)
    {
    }
    ADC_ClearFlag(adc, ADC_FLAG_EOC);
    *value = ADC_GetChannelConvertedValue(adc, channel);
#elif defined(SOC_SERIES_MM32F327)
    while (ADC_GetFlagStatus(adc, ADC_IT_EOC) == 0)
    {
    }
    ADC_ClearFlag(adc, ADC_IT_EOC);
    *value = ADC_GetConversionValue(adc);
#endif

    return RT_EOK;
}

static rt_uint8_t mm32_adc_get_resolution(struct rt_adc_device *device)
{
    ADC_TypeDef *adc;
    rt_uint32_t resolution;

    RT_ASSERT(device != RT_NULL);
    adc = device->parent.user_data;

#if defined(SOC_SERIES_MM32F526)
    resolution = adc->ADCFG & 0x00000380;
#else
    resolution = adc->CFGR & 0x00000380;
#endif

    switch (resolution)
    {
    case ADC_Resolution_12b:
        return 12;
    case ADC_Resolution_11b:
        return 11;
    case ADC_Resolution_10b:
        return 10;
    case ADC_Resolution_9b:
        return 9;
    case ADC_Resolution_8b:
        return 8;
    default:
        return 12;
    }
}

static rt_int16_t mm32_adc_get_vref(struct rt_adc_device *device)
{
    if (device == RT_NULL)
    {
        return -RT_ERROR;
    }

    return 3300;
}

static const struct rt_adc_ops mm32_adc_ops =
{
    .enabled = mm32_adc_enabled,
    .convert = mm32_adc_get_value,
    .get_resolution = mm32_adc_get_resolution,
    .get_vref = mm32_adc_get_vref,
};

int rt_hw_adc_init(void)
{
    rt_size_t i;

    for (i = 0; i < sizeof(adc_obj) / sizeof(adc_obj[0]); i++)
    {
        if (rt_hw_adc_register(&adc_obj[i].device, adc_obj[i].name, &mm32_adc_ops, adc_obj[i].instance) != RT_EOK)
        {
            LOG_E("%s register failed", adc_obj[i].name);
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
