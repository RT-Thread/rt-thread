/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_adc.h"

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2)

//#define DRV_DEBUG
#define LOG_TAG              "drv.adc"
#include <drv_log.h>

static ADC_HandleTypeDef adc_config[] =
{
#ifdef BSP_USING_ADC1
    {                                                                  \
        .Instance                       = ADC1,                        \
        .Init.ADC_Mode                  = ADC_Mode_Independent,        \
        .Init.ADC_ScanConvMode          = DISABLE,                     \
        .Init.ADC_ContinuousConvMode    = DISABLE,                     \
        .Init.ADC_ExternalTrigConv      = ADC_ExternalTrigConv_None,   \
        .Init.ADC_DataAlign             = ADC_DataAlign_Right,         \
        .Init.ADC_NbrOfChannel          = 1,                           \
    },
#endif

#ifdef BSP_USING_ADC2
    {                                                                  \
        .Instance                       = ADC2,                        \
        .Init.ADC_Mode                  = ADC_Mode_Independent,        \
        .Init.ADC_ScanConvMode          = DISABLE,                     \
        .Init.ADC_ContinuousConvMode    = DISABLE,                     \
        .Init.ADC_ExternalTrigConv      = ADC_ExternalTrigConv_None,   \
        .Init.ADC_DataAlign             = ADC_DataAlign_Right,         \
        .Init.ADC_NbrOfChannel          = 1,                           \
    }
#endif
};

struct air32_adc
{
    ADC_HandleTypeDef      ADC_Handler;
    struct rt_adc_device   air32_adc_device;
};

static struct air32_adc air32_adc_obj[sizeof(adc_config) / sizeof(adc_config[0])];

static rt_uint8_t air32_adc_get_resolution(struct rt_adc_device *device)
{
    //the resolution  which can not be changed is just 12bit;
    return 12;
}

static rt_int16_t air32_adc_get_vref (struct rt_adc_device *device)
{
    RT_ASSERT(device);
    return 3300;
}

static rt_err_t air32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    ADC_HandleTypeDef *air32_adc_handler;
    RT_ASSERT(device != RT_NULL);
    air32_adc_handler = device->parent.user_data;

    if (enabled)
    {
        ADC_Cmd(air32_adc_handler->Instance, ENABLE);
    }
    else
    {
        ADC_Cmd(air32_adc_handler->Instance, DISABLE);
    }

    return RT_EOK;
}

static rt_uint32_t air32_adc_get_channel(rt_uint32_t channel)
{
    rt_uint32_t air32_channel = 0;

    switch (channel)
    {
    case  0:
        air32_channel = ADC_Channel_0;
        break;
    case  1:
        air32_channel = ADC_Channel_1;
        break;
    case  2:
        air32_channel = ADC_Channel_2;
        break;
    case  3:
        air32_channel = ADC_Channel_3;
        break;
    case  4:
        air32_channel = ADC_Channel_4;
        break;
    case  5:
        air32_channel = ADC_Channel_5;
        break;
    case  6:
        air32_channel = ADC_Channel_6;
        break;
    case  7:
        air32_channel = ADC_Channel_7;
        break;
    case  8:
        air32_channel = ADC_Channel_8;
        break;
    case  9:
        air32_channel = ADC_Channel_9;
        break;
    case 10:
        air32_channel = ADC_Channel_10;
        break;
    case 11:
        air32_channel = ADC_Channel_11;
        break;
    case 12:
        air32_channel = ADC_Channel_12;
        break;
    case 13:
        air32_channel = ADC_Channel_13;
        break;
    case 14:
        air32_channel = ADC_Channel_14;
        break;
    case 15:
        air32_channel = ADC_Channel_15;
        break;
#ifdef ADC_CHANNEL_16
    case 16:
        air32_channel = ADC_Channel_16;
        break;
#endif /* ADC_CHANNEL_16 */
#ifdef ADC_CHANNEL_17
    case 17:
        air32_channel = ADC_Channel_17;
        break;
#endif /* ADC_CHANNEL_17 */
#ifdef ADC_CHANNEL_18
    case 18:
        air32_channel = ADC_Channel_18;
        break;
#endif /* ADC_CHANNEL_18 */
#ifdef ADC_CHANNEL_19
    case 19:
        air32_channel = ADC_Channel_19;
        break;
#endif /* ADC_CHANNEL_19 */
    }

    return air32_channel;
}

static rt_err_t air32_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    ADC_ChannelConfTypeDef ADC_ChanConf;
    ADC_HandleTypeDef *air32_adc_handler;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    air32_adc_handler = device->parent.user_data;

    rt_memset(&ADC_ChanConf, 0, sizeof(ADC_ChanConf));

#ifndef ADC_CHANNEL_16
    if (channel == 16)
    {
        LOG_E("ADC channel must not be 16.");
        return -RT_ERROR;
    }
#endif

/* ADC channel number is up to 17 */
#if !defined(ADC_CHANNEL_18)
    if (channel <= 17)
/* ADC channel number is up to 19 */
#elif defined(ADC_CHANNEL_19)
    if (channel <= 19)
/* ADC channel number is up to 18 */
#else
    if (channel <= 18)
#endif
    {
        /* set air32 ADC channel */
        ADC_ChanConf.Channel =  air32_adc_get_channel(channel);
    }
    else
    {
#if !defined(ADC_CHANNEL_18)
        LOG_E("ADC channel must be between 0 and 17.");
#elif defined(ADC_CHANNEL_19)
        LOG_E("ADC channel must be between 0 and 19.");
#else
        LOG_E("ADC channel must be between 0 and 18.");
#endif
        return -RT_ERROR;
    }

    ADC_ChanConf.Rank = 1;
    ADC_ChanConf.SamplingTime = ADC_SampleTime_239Cycles5;
    ADC_RegularChannelConfig(air32_adc_handler->Instance,ADC_ChanConf.Channel , ADC_ChanConf.Rank, ADC_ChanConf.SamplingTime );

    /* start ADC */
    ADC_SoftwareStartConvCmd(air32_adc_handler->Instance, ENABLE);
    /* Wait for the ADC to convert */
    while(!ADC_GetFlagStatus(air32_adc_handler->Instance, ADC_FLAG_EOC ));
    /* get ADC value */
    *value = (rt_uint32_t)ADC_GetConversionValue(air32_adc_handler->Instance);
    ADC_ClearFlag( air32_adc_handler->Instance, ADC_FLAG_EOC);

    return RT_EOK;
}

static const struct rt_adc_ops air32_adc_ops =
{
    .enabled = air32_adc_enabled,
    .convert = air32_get_adc_value,
    .get_resolution = air32_adc_get_resolution,
    .get_vref = air32_adc_get_vref
};

static int air32_adc_init(void)
{
    int result = RT_EOK;
    /* save adc name */
    char name_buf[5] = {'a', 'd', 'c', '0', 0};
    int i = 0;

    for (i = 0; i < sizeof(adc_config) / sizeof(adc_config[0]); i++)
    {
        /* ADC init */
        name_buf[3] = '0';
        air32_adc_obj[i].ADC_Handler = adc_config[i];
#if defined(ADC1)
        if (air32_adc_obj[i].ADC_Handler.Instance == ADC1)
        {
            name_buf[3] = '1';
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );
        }
#endif
#if defined(ADC2)
        if (air32_adc_obj[i].ADC_Handler.Instance == ADC2)
        {
            name_buf[3] = '2';
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE );
        }
#endif
        {
            ADC_Init(air32_adc_obj[i].ADC_Handler.Instance,&air32_adc_obj[i].ADC_Handler.Init );
            /* register ADC device */
            if (rt_hw_adc_register(&air32_adc_obj[i].air32_adc_device, name_buf, &air32_adc_ops, &air32_adc_obj[i].ADC_Handler) == RT_EOK)
            {
                LOG_D("%s init success", name_buf);
            }
            else
            {
                LOG_E("%s register failed", name_buf);
                result = -RT_ERROR;
            }
        }
    }

    return result;
}
INIT_DEVICE_EXPORT(air32_adc_init);

#endif /* BSP_USING_ADC */
