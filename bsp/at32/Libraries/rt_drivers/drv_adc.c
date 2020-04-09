/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-15     Leo         first version
 */

#include <board.h>
#include "drv_adc.h"

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3)
#define DRV_DEBUG
#define LOG_TAG             "drv.adc"
#include <drv_log.h>

struct at32_adc
{  
    struct rt_adc_device at32_adc_device;
    ADC_Type *ADC_Handler;
    char *name;
};

static struct at32_adc at32_adc_obj[] =
{
#ifdef BSP_USING_ADC1
    ADC1_CONFIG,
#endif

#ifdef BSP_USING_ADC2
    ADC2_CONFIG,
#endif

#ifdef BSP_USING_ADC3
    ADC3_CONFIG,
#endif
};

static rt_uint32_t at32_adc_get_channel(rt_uint32_t channel)
{
    rt_uint32_t at32_channel = 0;

    switch (channel)
    {
    case  0:
        at32_channel = ADC_Channel_0;
        break;
    case  1:
        at32_channel = ADC_Channel_1;
        break;
    case  2:
        at32_channel = ADC_Channel_2;
        break;
    case  3:
        at32_channel = ADC_Channel_3;
        break;
    case  4:
        at32_channel = ADC_Channel_4;
        break;
    case  5:
        at32_channel = ADC_Channel_5;
        break;
    case  6:
        at32_channel = ADC_Channel_6;
        break;
    case  7:
        at32_channel = ADC_Channel_7;
        break;
    case  8:
        at32_channel = ADC_Channel_8;
        break;
    case  9:
        at32_channel = ADC_Channel_9;
        break;
    case 10:
        at32_channel = ADC_Channel_10;
        break;
    case 11:
        at32_channel = ADC_Channel_11;
        break;
    case 12:
        at32_channel = ADC_Channel_12;
        break;
    case 13:
        at32_channel = ADC_Channel_13;
        break;
    case 14:
        at32_channel = ADC_Channel_14;
        break;
    case 15:
        at32_channel = ADC_Channel_15;
        break;
    case 16:
        at32_channel = ADC_Channel_16;
        break;
    case 17:
        at32_channel = ADC_Channel_17;
        break;
    }

    return at32_channel;
}

static rt_err_t at32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    ADC_Type *at32_adc_handler;
    ADC_InitType ADC_InitStructure;
    RT_ASSERT(device != RT_NULL);
    at32_adc_handler = device->parent.user_data;
  
    at32_msp_adc_init(at32_adc_handler);
  
    /* ADCx configuration ------------------------------------------------------*/
    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.ADC_Mode              = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanMode          = DISABLE;
    ADC_InitStructure.ADC_ContinuousMode    = DISABLE;
    ADC_InitStructure.ADC_ExternalTrig      = ADC_ExternalTrig_None;
    ADC_InitStructure.ADC_DataAlign         = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NumOfChannel      = 1;
    ADC_Init(at32_adc_handler, &ADC_InitStructure);
  
    /* ADCx regular channels configuration */ 
    ADC_RegularChannelConfig(at32_adc_handler, at32_adc_get_channel(channel), 1, ADC_SampleTime_28_5); 
    
    /* Enable ADCx */
    ADC_Ctrl(at32_adc_handler, ENABLE);
  
    /* Enable ADCx reset calibration register */   
    ADC_RstCalibration(at32_adc_handler);
    /* Check the end of ADCx reset calibration register */
    while(ADC_GetResetCalibrationStatus(at32_adc_handler));

    /* Start ADCx calibration */
    ADC_StartCalibration(at32_adc_handler);
    /* Check the end of ADCx calibration */
    while(ADC_GetCalibrationStatus(at32_adc_handler));

    if (enabled)
    {
      /* Enable ADC1 */
      ADC_Ctrl(at32_adc_handler, ENABLE);
    }
    else
    {
      /* Enable ADCx */
      ADC_Ctrl(at32_adc_handler, DISABLE);
    }

    return RT_EOK;
}

static rt_err_t at32_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    ADC_Type *at32_adc_handler;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    at32_adc_handler = device->parent.user_data;

    /* Start ADCx Software Conversion */ 
    ADC_SoftwareStartConvCtrl(at32_adc_handler, ENABLE);

    /* Wait for the ADC to convert */
    while(ADC_GetFlagStatus(at32_adc_handler, ADC_FLAG_EC) == RESET);

    /* get ADC value */
    *value = ADC_GetConversionValue(at32_adc_handler);

    return RT_EOK;
}

static const struct rt_adc_ops at_adc_ops =
{
    .enabled = at32_adc_enabled,
    .convert = at32_get_adc_value,
};

static int rt_hw_adc_init(void)
{
    int result = RT_EOK;
    int i = 0;

    for (i = 0; i < sizeof(at32_adc_obj) / sizeof(at32_adc_obj[0]); i++)
    {
        /* register ADC device */
        if (rt_hw_adc_register(&at32_adc_obj[i].at32_adc_device, at32_adc_obj[i].name, &at_adc_ops, at32_adc_obj[i].ADC_Handler) == RT_EOK)
        {
            LOG_D("%s register success", at32_adc_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", at32_adc_obj[i].name);
            result = -RT_ERROR;
        }

    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
