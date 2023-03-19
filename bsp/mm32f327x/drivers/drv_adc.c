/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-17     letian       first version
 */
#include <HAL_device.h>
#include <rtdevice.h>
#include "drv_adc.h"
#include <hal_gpio.h>
#include <hal_adc.h>
#include <hal_rcc.h>
#include <hal_misc.h>

#if defined(BSP_USING_ADC)

#define ADC_CONFIG_GPIORCC     RCC_AHBENR_GPIOA
#define ADC_CONFIG_GPIOX       GPIOA
#define ADC_CONFIG_IOX         GPIO_Pin_5 | GPIO_Pin_4

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

static void ADCxChannelEnable(ADC_TypeDef* ADCn, ADCCHANNEL_TypeDef channel)
{
    ADCn->CHSR &= ~(1 << channel);
    ADCn->CHSR |=  (1 << channel);
}

static rt_err_t mm32_adc_init(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    ADC_InitTypeDef  ADC_InitStruct;
    ADC_TypeDef *adc_x;
    RT_ASSERT(device != RT_NULL);
    adc_x = device->parent.user_data;

    #if defined(BSP_USING_ADC1)
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC1, ENABLE); //Enable ADC1 clock
    #endif /* BSP_USING_ADC1 */

    #if defined(BSP_USING_ADC2)
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC2, ENABLE); //Enable ADC2 clock
    #endif /* BSP_USING_ADC2 */

    ADC_StructInit(&ADC_InitStruct);
    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStruct.ADC_PRESCARE = ADC_PCLK2_PRESCARE_16;                     //ADC prescale factor
    ADC_InitStruct.ADC_Mode = ADC_Mode_Continue;                             //Set ADC mode to continuous conversion mode
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;                      //AD data right-justified
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    ADC_Init(adc_x, &ADC_InitStruct);

    ADC_RegularChannelConfig(adc_x, channel, 0, ADC_Samctl_239_5);
    ADC_Cmd(adc_x, ENABLE);
    ADCxChannelEnable(adc_x, channel);

    //config gpio
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct);

    RCC_AHBPeriphClockCmd(ADC_CONFIG_GPIORCC, ENABLE);
    GPIO_InitStruct.GPIO_Pin  = ADC_CONFIG_IOX;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(ADC_CONFIG_GPIOX, &GPIO_InitStruct);

    return RT_EOK;
}

static rt_err_t mm32_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    ADC_TypeDef *adc_x;
    RT_ASSERT(device != RT_NULL);
    adc_x = device->parent.user_data;

    ADC_SoftwareStartConvCmd(adc_x, ENABLE);
    while(ADC_GetFlagStatus(adc_x, ADC_IT_EOC) == 0);
    ADC_ClearFlag(adc_x, ADC_IT_EOC);
    *value = ADC_GetConversionValue(adc_x);
    return RT_EOK;
}

static rt_uint8_t mm32_adc_get_resolution(struct rt_adc_device *device)
{
    ADC_TypeDef *adc_x = device->parent.user_data;

    RT_ASSERT(device != RT_NULL);

    switch( ((adc_x->CFGR)&(0x00000380)) )
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
            return 0;
    }
}

static rt_int16_t mm32_adc_get_vref(struct rt_adc_device *device)
{
    if(device == RT_NULL)
        return RT_ERROR;

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
