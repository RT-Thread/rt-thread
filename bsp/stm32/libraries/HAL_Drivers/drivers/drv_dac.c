/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-06-18     thread-liu        the first version
 * 2020-10-09     thread-liu   Porting for stm32h7xx
 */

#include <board.h>

#if defined(BSP_USING_DAC1) || defined(BSP_USING_DAC2)
#include "drv_config.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.dac"
#include <drv_log.h>

static DAC_HandleTypeDef dac_config[] =
{
#ifdef BSP_USING_DAC1
    DAC1_CONFIG,
#endif

#ifdef BSP_USING_DAC2
    DAC2_CONFIG,
#endif
};

struct stm32_dac
{
    DAC_HandleTypeDef DAC_Handler;
    struct rt_dac_device stm32_dac_device;
};

static struct stm32_dac stm32_dac_obj[sizeof(dac_config) / sizeof(dac_config[0])];

static rt_uint32_t stm32_dac_get_channel(rt_uint32_t channel)
{
    rt_uint32_t stm32_channel = 0;

    switch (channel)
    {
    case  1:
        stm32_channel = DAC_CHANNEL_1;
        break;
    case  2:
        stm32_channel = DAC_CHANNEL_2;
        break;
    default:
        RT_ASSERT(0);
        break;
    }

    return stm32_channel;
}

static rt_err_t stm32_dac_enabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    uint32_t dac_channel;
    DAC_HandleTypeDef *stm32_dac_handler;
    RT_ASSERT(device != RT_NULL);
    stm32_dac_handler = device->parent.user_data;

#if defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F4)
    if ((channel <= 2) && (channel > 0))
    {
        /* set stm32 dac channel */
        dac_channel =  stm32_dac_get_channel(channel);
    }
    else
    {
      LOG_E("dac channel must be 1 or 2.");
      return -RT_ERROR;
    }
    HAL_DAC_Start(stm32_dac_handler, dac_channel);
#endif

    return RT_EOK;
}

static rt_err_t stm32_dac_disabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    uint32_t dac_channel;
    DAC_HandleTypeDef *stm32_dac_handler;
    RT_ASSERT(device != RT_NULL);
    stm32_dac_handler = device->parent.user_data;

#if defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F4)
    if ((channel <= 2) && (channel > 0))
    {
        /* set stm32 dac channel */
        dac_channel =  stm32_dac_get_channel(channel);
    }
    else
    {
      LOG_E("dac channel must be 1 or 2.");
      return -RT_ERROR;
    }
    HAL_DAC_Stop(stm32_dac_handler, dac_channel);
#endif

    return RT_EOK;
}

static rt_uint8_t stm32_dac_get_resolution(struct rt_dac_device *device)
{
    DAC_HandleTypeDef *stm32_dac_handler;

    RT_ASSERT(device != RT_NULL);

    stm32_dac_handler = device->parent.user_data;
    (void)stm32_dac_handler;

    /* Only has supported DAC_ALIGN_12B_R, so it will return 12 bits */
    return 12;
}

static rt_err_t stm32_set_dac_value(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    uint32_t dac_channel;
    DAC_ChannelConfTypeDef DAC_ChanConf;
    DAC_HandleTypeDef *stm32_dac_handler;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    stm32_dac_handler = device->parent.user_data;

    rt_memset(&DAC_ChanConf, 0, sizeof(DAC_ChanConf));

#if defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F4)
    if ((channel <= 2) && (channel > 0))
    {
        /* set stm32 dac channel */
        dac_channel =  stm32_dac_get_channel(channel);
    }
    else
    {
      LOG_E("dac channel must be 1 or 2.");
      return -RT_ERROR;
    }
#endif

#if defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F4)
    DAC_ChanConf.DAC_Trigger      = DAC_TRIGGER_NONE;
    DAC_ChanConf.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
#endif
    /* config dac out channel*/
    if (HAL_DAC_ConfigChannel(stm32_dac_handler, &DAC_ChanConf, dac_channel) != HAL_OK)
    {
        LOG_D("Config dac out channel Error!\n");
        return -RT_ERROR;
    }
    /* set dac channel out value*/
    if (HAL_DAC_SetValue(stm32_dac_handler, dac_channel, DAC_ALIGN_12B_R, *value) != HAL_OK)
    {
        LOG_D("Setting dac channel out value Error!\n");
        return -RT_ERROR;
    }
    /* start dac */
    if (HAL_DAC_Start(stm32_dac_handler, dac_channel) != HAL_OK)
    {
        LOG_D("Start dac Error!\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static const struct rt_dac_ops stm_dac_ops =
{
    .disabled = stm32_dac_disabled,
    .enabled  = stm32_dac_enabled,
    .convert  = stm32_set_dac_value,
    .get_resolution = stm32_dac_get_resolution,
};

static int stm32_dac_init(void)
{
    int result = RT_EOK;
    /* save dac name */
    char name_buf[5] = {'d', 'a', 'c', '0', 0};
    int i = 0;

    for (i = 0; i < sizeof(dac_config) / sizeof(dac_config[0]); i++)
    {
        /* dac init */
        name_buf[3] = '0';
        stm32_dac_obj[i].DAC_Handler = dac_config[i];
#if defined(DAC1)
        if (stm32_dac_obj[i].DAC_Handler.Instance == DAC1)
        {
            name_buf[3] = '1';
        }
#endif
#if defined(DAC2)
        if (stm32_dac_obj[i].dac_Handler.Instance == DAC2)
        {
            name_buf[3] = '2';
        }
#endif
        if (HAL_DAC_Init(&stm32_dac_obj[i].DAC_Handler) != HAL_OK)
        {
            LOG_E("%s init failed", name_buf);
            result = -RT_ERROR;
        }
        else
        {
            /* register dac device */
            if (rt_hw_dac_register(&stm32_dac_obj[i].stm32_dac_device, name_buf, &stm_dac_ops, &stm32_dac_obj[i].DAC_Handler) == RT_EOK)
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
INIT_DEVICE_EXPORT(stm32_dac_init);

#endif /* BSP_USING_DAC */
