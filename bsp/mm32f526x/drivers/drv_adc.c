/*
 * Copyright (c) 2022-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-22     chasel       first version
 * 2025-02-10     chasel       fix adc calibration did not clear flag bits
 */
#include <rtdevice.h>
#include "board.h"
#include "drv_adc.h"
#include <hal_gpio.h>
#include <hal_adc.h>
#include <hal_rcc.h>
#include <hal_misc.h>

#if defined(BSP_USING_ADC)

struct mm32_adc
{
    struct rt_adc_device mm32_adc_device;
    ADC_TypeDef *adc_x;
    char *name;
};

#if defined(BSP_USING_ADC1)
struct mm32_adc mm32_adc1_config = {
    .adc_x      = ADC1,
    .name       = "adc1",
};
#endif /* BSP_USING_ADC1 */

#if defined(BSP_USING_ADC2)
struct mm32_adc mm32_adc2_config = {
    .adc_x      = ADC2,
    .name       = "adc2",
};
#endif /* BSP_USING_ADC2 */

static void ADCxChannelEnable(ADC_TypeDef* ADCn, rt_uint32_t channel)
{
    ADCn->ADCHS &= ~(1 << channel);
    ADCn->ADCHS |=  (1 << channel);
}

static rt_err_t mm32_adc_init(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    ADC_InitTypeDef  ADC_InitStruct;
    ADC_TypeDef *adc_x;
    RT_ASSERT(device != RT_NULL);
    adc_x = device->parent.user_data;

    if (enabled) {
        mm32_msp_adc_init((void *)adc_x);

        ADC_CalibrationConfig(adc_x, 0x1FE);

        ADC_StructInit(&ADC_InitStruct);
        ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
        ADC_InitStruct.ADC_Prescaler = ADC_Prescaler_16;                     //ADC prescale factor
        ADC_InitStruct.ADC_Mode = ADC_Mode_Scan;                             //Set ADC mode to scan conversion mode
        ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;                      //AD data right-justified
        ADC_Init(adc_x, &ADC_InitStruct);

        ADC_SampleTimeConfig(adc_x, channel, ADC_SampleTime_240_5);

        ADC_ChannelCmd(adc_x, channel, ENABLE);

        ADC_DifferentialConversionConfig(adc_x, ADC_Pseudo_Differential_Conversion_4_5);

        ADC_Cmd(adc_x, ENABLE);
    } else {
        #if defined(BSP_USING_ADC1)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, DISABLE); //disable ADC1 clock
        #endif /* BSP_USING_ADC1 */

        #if defined(BSP_USING_ADC2)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, DISABLE); //disable ADC2 clock
        #endif /* BSP_USING_ADC2 */

        ADC_DeInit(adc_x);
        ADC_Cmd(adc_x, DISABLE);
    }

    return RT_EOK;
}

static rt_err_t mm32_get_adc_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    ADC_TypeDef *adc_x;
    RT_ASSERT(device != RT_NULL);
    adc_x = device->parent.user_data;

    ADC_SoftwareStartConvCmd(adc_x, ENABLE);

    while(ADC_GetFlagStatus(adc_x, ADC_FLAG_EOC) == 0);
    ADC_ClearFlag(adc_x, ADC_FLAG_EOC);

    *value = ADC_GetChannelConvertedValue(adc_x, channel);
    return RT_EOK;
}

static rt_uint8_t mm32_adc_get_resolution(struct rt_adc_device *device)
{
    ADC_TypeDef *adc_x = device->parent.user_data;

    RT_ASSERT(device != RT_NULL);

    switch( ((adc_x->ADCFG)&(0x00000380)) )
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
    if(device == RT_NULL)
        return -RT_ERROR;

    return 3300;
}

static const struct rt_adc_ops mm32_adc_ops =
{
    .enabled = mm32_adc_init,
    .convert = mm32_get_adc_value,
    .get_resolution = mm32_adc_get_resolution,
    .get_vref = mm32_adc_get_vref,
};

int rt_hw_adc_init(void)
{
    #if defined(BSP_USING_ADC1)
    rt_hw_adc_register(&mm32_adc1_config.mm32_adc_device, mm32_adc1_config.name, &mm32_adc_ops, mm32_adc1_config.adc_x);
    #endif /* BSP_USING_ADC1 */

    #if defined(BSP_USING_ADC2)
    rt_hw_adc_register(&mm32_adc2_config.mm32_adc_device, mm32_adc2_config.name, &mm32_adc_ops, mm32_adc2_config.adc_x);
    #endif /* BSP_USING_ADC2 */

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
