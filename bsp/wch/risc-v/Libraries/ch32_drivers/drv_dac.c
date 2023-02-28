/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WCH          the first version
 * 2022-09-17     hg0720       add some operation function
 */

#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_dac.h"

#if defined BSP_USING_DAC

//#define DRV_DEBUG
#define LOG_TAG              "drv.dac"
#include <drv_log.h>

static DAC_HandleTypeDef dac_config[] =
{
#ifdef BSP_USING_DAC_CHANNEL1
    {                                                                         \
        .Instance                               = DAC,                        \
        .Init.DAC_Trigger                       = DAC_Trigger_None,           \
        .Init.DAC_WaveGeneration                = DAC_WaveGeneration_None,    \
        .Init.DAC_LFSRUnmask_TriangleAmplitude  = DAC_TriangleAmplitude_4095, \
        .Init.DAC_OutputBuffer                  = DAC_OutputBuffer_Enable,    \
        .Channel                                = DAC_Channel_1,
    },
#endif

#ifdef BSP_USING_DAC_CHANNEL2
    {
        .Instance                               = DAC,                        \
        .Init.DAC_Trigger                       = DAC_Trigger_None,           \
        .Init.DAC_WaveGeneration                = DAC_WaveGeneration_None,    \
        .Init.DAC_LFSRUnmask_TriangleAmplitude  = DAC_TriangleAmplitude_4095, \
        .Init.DAC_OutputBuffer                  = DAC_OutputBuffer_Enable,    \
        .Channel                                = DAC_Channel_2,
    }
#endif
};

struct ch32_dac
{
    DAC_HandleTypeDef      DAC_Handler;
    struct rt_dac_device   ch32_dac_device;
};

static struct ch32_dac ch32_dac_obj[sizeof(dac_config) / sizeof(dac_config[0])];

static rt_err_t ch32_dac_enabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    DAC_HandleTypeDef *ch32_dac_handler;
    RT_ASSERT(device != RT_NULL);
    ch32_dac_handler = device->parent.user_data;
    DAC_Cmd(ch32_dac_handler->Channel, ENABLE);
    return RT_EOK;
}

static rt_err_t ch32_dac_disabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    DAC_HandleTypeDef *ch32_dac_handler;
    RT_ASSERT(device != RT_NULL);
    ch32_dac_handler = device->parent.user_data;
    DAC_Cmd(ch32_dac_handler->Channel, DISABLE);
    return RT_EOK;
}

static rt_uint8_t ch32_dac_get_resolution(struct rt_dac_device *device)
{
    DAC_HandleTypeDef *ch32_dac_handler;

    RT_ASSERT(device != RT_NULL);

    ch32_dac_handler = device->parent.user_data;
    (void)ch32_dac_handler;

    /* Only has supported DAC_ALIGN_12B_R, so it will return 12 bits */
    return 12;
}

static rt_uint32_t ch32_dac_get_channel(rt_uint32_t channel)
{
    rt_uint32_t ch32_channel = 0;

    switch (channel)
    {
    case  1:
        ch32_channel = DAC_Channel_1;
        break;
    case  2:
        ch32_channel = DAC_Channel_2;
        break;
    default:
        RT_ASSERT(0);
        break;
    }

    return ch32_channel;
}

static rt_err_t ch32_set_dac_value(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    rt_uint32_t dac_channel;
    DAC_HandleTypeDef *ch32_dac_handler;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    ch32_dac_handler = device->parent.user_data;


    if ((channel <= 2) && (channel > 0))
    {
        /* set ch32 dac channel */
        dac_channel =  ch32_dac_get_channel(channel);
    }
    else
    {
        LOG_E("dac channel must be 1 or 2.");
        return -RT_ERROR;
    }

    if (channel==1)
    {
        DAC_SetChannel1Data(DAC_Align_12b_R, *value);
    }
    else if (channel==2)
    {
        DAC_SetChannel2Data(DAC_Align_12b_R, *value);
    }

    return RT_EOK;
}

static const struct rt_dac_ops ch_dac_ops =
{
    .disabled = ch32_dac_disabled,
    .enabled  = ch32_dac_enabled,
    .convert  = ch32_set_dac_value,
    .get_resolution = ch32_dac_get_resolution,
};

static int ch32_dac_init(void)
{
    int result = RT_EOK;
    /* save dac name */
    char name_buf[6] = {'d', 'a', 'c', 'c','0', 0};
    int i = 0;
    GPIO_InitTypeDef GPIO_InitStructure={0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );
    for (i = 0; i < sizeof(dac_config) / sizeof(dac_config[0]); i++)
    {
        /* dac channel init */
        name_buf[4] = '0';
        ch32_dac_obj[i].DAC_Handler = dac_config[i];

        if (ch32_dac_obj[i].DAC_Handler.Channel==DAC_Channel_1)
        {
            name_buf[4] = '1';
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        if (ch32_dac_obj[i].DAC_Handler.Channel==DAC_Channel_2)
        {
            name_buf[4] = '2';
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        /* init dac channelx */
        DAC_Init(ch32_dac_obj[i].DAC_Handler.Channel,&ch32_dac_obj[i].DAC_Handler.Init);

        /* register dac device */
        if (rt_hw_dac_register(&ch32_dac_obj[i].ch32_dac_device, name_buf, &ch_dac_ops, &ch32_dac_obj[i].DAC_Handler) == RT_EOK)
        {
            LOG_D("%s init success", name_buf);
        }
        else
        {
            LOG_E("%s register failed", name_buf);
            result = -RT_ERROR;
        }
    }

    return result;
}

INIT_DEVICE_EXPORT(ch32_dac_init);

#endif /* BSP_USING_DAC */
