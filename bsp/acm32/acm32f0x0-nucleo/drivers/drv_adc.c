/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-23     AisinoChip   first implementation
 */

#include <board.h>
#include <rtdevice.h>

#define     ADC_NAME        "adc"

#if defined(RT_USING_ADC)
#if defined(BSP_USING_ADC)

struct acm32_adc
{
    ADC_HandleTypeDef       handle;
    struct rt_adc_device    acm32_adc_device;
};

static struct acm32_adc acm32_adc_obj = {0};

static rt_err_t _adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    struct acm32_adc *adcObj = RT_NULL;

    RT_ASSERT(device != RT_NULL);

    adcObj = rt_container_of(device, struct acm32_adc, acm32_adc_device);

    if (enabled)
    {
        /* channel enabled */
        if (0 != (adcObj->handle.Init.ChannelEn & (1 << channel)))
        {
            return RT_EOK;
        }

        adcObj->handle.Instance = ADC;
        adcObj->handle.Init.ClockDiv = ADC_CLOCK_DIV8;
        adcObj->handle.Init.ConConvMode = ADC_CONCONVMODE_DISABLE;
        adcObj->handle.Init.JChannelMode = ADC_JCHANNELMODE_DISABLE;
        adcObj->handle.Init.DiffMode = ADC_DIFFMODE_DISABLE;
        adcObj->handle.Init.DMAMode = ADC_DMAMODE_DISABLE;
        adcObj->handle.Init.OverMode = ADC_OVERMODE_DISABLE;
        adcObj->handle.Init.OverSampMode = ADC_OVERSAMPMODE_DISABLE;
        adcObj->handle.Init.AnalogWDGEn = ADC_ANALOGWDGEN_DISABLE;
        adcObj->handle.Init.ExTrigMode.ExTrigSel = ADC_SOFTWARE_START;
        adcObj->handle.Init.ChannelEn |= 1 << channel;

        HAL_ADC_Init(&adcObj->handle);

        adcObj->handle.ChannelNum ++;
    }
    else
    {
        /* channel disabled */
        if (0 == (adcObj->handle.Init.ChannelEn & (1 << channel)))
        {
            return RT_EOK;
        }
        adcObj->handle.Init.ChannelEn &= ~(1 << channel);
        adcObj->handle.ChannelNum --;
    }

    return RT_EOK;
}

static rt_err_t _get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    struct acm32_adc *adcObj = RT_NULL;
    ADC_ChannelConfTypeDef channelConf = {0};

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);
    if (channel > ADC_CHANNEL_15)
    {
        return -RT_ERROR;
    }
    *value = RT_UINT32_MAX;
    adcObj = rt_container_of(device, struct acm32_adc, acm32_adc_device);

    /* channel disabled */
    if (0 == (adcObj->handle.Init.ChannelEn & (1 << channel)))
    {
        return -RT_ERROR;
    }

    channelConf.Channel = channel;
    channelConf.RjMode = 0;
    channelConf.Sq = ADC_SEQUENCE_SQ1;
    channelConf.Smp = ADC_SMP_CLOCK_320;
    HAL_ADC_ConfigChannel(&adcObj->handle, &channelConf);

    if (HAL_OK != HAL_ADC_Polling(&adcObj->handle, (uint32_t *)value, 1, 100))
    {
        return -RT_ERROR;
    }
    *value &= ~(HAL_ADC_EOC_FLAG);

    return RT_EOK;
}

static const struct rt_adc_ops acm_adc_ops =
{
    .enabled = _adc_enabled,
    .convert = _get_adc_value,
};

static int rt_hw_adc_init(void)
{
    return rt_hw_adc_register(&acm32_adc_obj.acm32_adc_device,
                              ADC_NAME,
                              &acm_adc_ops,
                              RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
#endif /* RT_USING_ADC */

