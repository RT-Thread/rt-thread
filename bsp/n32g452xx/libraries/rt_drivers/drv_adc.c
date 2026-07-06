/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     breo.com     first version
 */

#include <board.h>
#include "drv_adc.h"

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3)
#define DRV_DEBUG
#define LOG_TAG             "drv.adc"
#include <drv_log.h>

struct n32_adc
{
    struct rt_adc_device n32_adc_device;
    ADC_Module *ADC_Handler;
    char *name;
};

static struct n32_adc n32_adc_obj[] =
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

static rt_uint32_t n32_adc_get_channel(rt_uint32_t channel)
{
    rt_uint32_t n32_channel = 0;

    switch (channel)
    {
    case  0:
        n32_channel = ADC_CH_0;
        break;
    case  1:
        n32_channel = ADC_CH_1;
        break;
    case  2:
        n32_channel = ADC_CH_2;
        break;
    case  3:
        n32_channel = ADC_CH_3;
        break;
    case  4:
        n32_channel = ADC_CH_4;
        break;
    case  5:
        n32_channel = ADC_CH_5;
        break;
    case  6:
        n32_channel = ADC_CH_6;
        break;
    case  7:
        n32_channel = ADC_CH_7;
        break;
    case  8:
        n32_channel = ADC_CH_8;
        break;
    case  9:
        n32_channel = ADC_CH_9;
        break;
    case 10:
        n32_channel = ADC_CH_10;
        break;
    case 11:
        n32_channel = ADC_CH_11;
        break;
    case 12:
        n32_channel = ADC_CH_12;
        break;
    case 13:
        n32_channel = ADC_CH_13;
        break;
    case 14:
        n32_channel = ADC_CH_14;
        break;
    case 15:
        n32_channel = ADC_CH_15;
        break;
    case 16:
        n32_channel = ADC_CH_16;
        break;
    case 17:
        n32_channel = ADC_CH_17;
        break;
    case 18:
        n32_channel = ADC_CH_18;
        break;
    }

    return n32_channel;
}

static rt_err_t n32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    ADC_Module *n32_adc_handler;
    ADC_InitType ADC_InitStructure;
    RT_ASSERT(device != RT_NULL);
    n32_adc_handler = device->parent.user_data;

    n32_msp_adc_init(n32_adc_handler);

    ADC_InitStruct(&ADC_InitStructure);
    ADC_InitStructure.WorkMode              = ADC_WORKMODE_INDEPENDENT;
    ADC_InitStructure.MultiChEn             = DISABLE;
    ADC_InitStructure.ContinueConvEn        = DISABLE;
    ADC_InitStructure.ExtTrigSelect         = ADC_EXT_TRIGCONV_NONE;
    ADC_InitStructure.DatAlign              = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber             = 1;
    ADC_Init(n32_adc_handler, &ADC_InitStructure);

    if (((n32_adc_handler == ADC1) || (n32_adc_handler == ADC2))
        && ((n32_adc_get_channel(channel) == ADC_CH_16)
            || (n32_adc_get_channel(channel) == ADC_CH_18)))
    {
        ADC_EnableTempSensorVrefint(ENABLE);
    }

    if (enabled)
    {
        /* Enable ADC1 */
        ADC_Enable(n32_adc_handler, ENABLE);
        /*Check ADC Ready*/
        while (ADC_GetFlagStatusNew(n32_adc_handler, ADC_FLAG_RDY) == RESET);
        /* Start ADCx calibration */
        ADC_StartCalibration(n32_adc_handler);
        /* Check the end of ADCx calibration */
        while (ADC_GetCalibrationStatus(n32_adc_handler));
    }
    else
    {
        /* Enable ADCx */
        ADC_Enable(n32_adc_handler, DISABLE);
    }

    return RT_EOK;
}

static rt_err_t n32_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    ADC_Module *n32_adc_handler;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    n32_adc_handler = device->parent.user_data;

    /* ADCx regular channels configuration */
    ADC_ConfigRegularChannel(n32_adc_handler, n32_adc_get_channel(channel), 1, ADC_SAMP_TIME_28CYCLES5);

    /* Start ADCx Software Conversion */
    ADC_EnableSoftwareStartConv(n32_adc_handler, ENABLE);

    /* Wait for the ADC to convert */
    while (ADC_GetFlagStatus(n32_adc_handler, ADC_FLAG_ENDC) == RESET);

    ADC_ClearFlag(n32_adc_handler, ADC_FLAG_ENDC);

    /* get ADC value */
    *value = ADC_GetDat(n32_adc_handler);

    return RT_EOK;
}

static const struct rt_adc_ops at_adc_ops =
{
    .enabled = n32_adc_enabled,
    .convert = n32_get_adc_value,
};

static int rt_hw_adc_init(void)
{
    int result = RT_EOK;
    int i = 0;

    for (i = 0; i < sizeof(n32_adc_obj) / sizeof(n32_adc_obj[0]); i++)
    {
        /* register ADC device */
        if (rt_hw_adc_register(&n32_adc_obj[i].n32_adc_device,
                               n32_adc_obj[i].name, &at_adc_ops,
                               n32_adc_obj[i].ADC_Handler) == RT_EOK)
        {
            LOG_D("%s register success", n32_adc_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", n32_adc_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */

