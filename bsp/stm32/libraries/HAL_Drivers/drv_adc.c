/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-05     zylx         first version
 * 2018-12-12     greedyhao    Porting for stm32f7xx
 * 2019-02-01     yuneizhilin   fix the stm32_adc_init function initialization issue
 */

#include <board.h>

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3)
#include <adc_port.h>
#include "drv_config.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.adc"
#include <drv_log.h>

#ifdef BSP_ADC1_USING_DMA
DMA_HandleTypeDef hdma_adc1;
ADC_ChannelConfTypeDef adc1_sequence[] = ADC1_SEQUENCER;
#endif

#ifdef BSP_ADC2_USING_DMA
DMA_HandleTypeDef hdma_adc2;
ADC_ChannelConfTypeDef adc2_sequence[] = ADC2_SEQUENCER;
#endif

#ifdef BSP_ADC3_USING_DMA
DMA_HandleTypeDef hdma_adc3;
ADC_ChannelConfTypeDef adc3_sequence[] = ADC3_SEQUENCER;
#endif

static ADC_HandleTypeDef adc_config[] =
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

struct stm32_adc
{
    ADC_HandleTypeDef ADC_Handler;
    struct rt_adc_device stm32_adc_device;
};

#if defined(BSP_ADC1_USING_DMA)
void ADC1_DMA_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_adc1);
}
#endif

#if defined(BSP_ADC2_USING_DMA)
void ADC2_DMA_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_adc2);
}
#endif

#if defined(BSP_ADC3_USING_DMA)
void ADC3_DMA_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_adc3);
}
#endif

static struct stm32_adc stm32_adc_obj[sizeof(adc_config) / sizeof(adc_config[0])];

static rt_err_t stm32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    ADC_HandleTypeDef *stm32_adc_handler;
    RT_ASSERT(device != RT_NULL);
    stm32_adc_handler = device->parent.user_data;

    if (enabled)
    {
#if defined(BSP_ADC1_USING_DMA)
        if(stm32_adc_handler->Instance == ADC1)
        {
            HAL_ADC_Start_DMA(stm32_adc_handler, (rt_uint32_t*)device->dma_buf, device->dma_chn_num*device->dma_chn_size);
        }
        else
#elif defined(BSP_ADC2_USING_DMA)
        if(stm32_adc_handler->Instance == ADC2)
        {
            HAL_ADC_Start_DMA(stm32_adc_handler, (rt_uint32_t*)device->dma_buf, device->dma_chn_num*device->dma_chn_size);
        }
        else
#elif defined(BSP_ADC3_USING_DMA)
        if(stm32_adc_handler->Instance == ADC3)
        {
            HAL_ADC_Start_DMA(stm32_adc_handler, (rt_uint32_t*)device->dma_buf, device->dma_chn_num*device->dma_chn_size);
        }
        else
#endif
        {
#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0)
            ADC_Enable(stm32_adc_handler);
#else
            __HAL_ADC_ENABLE(stm32_adc_handler);
#endif
        }
    }
    else
    {
#if defined(BSP_ADC1_USING_DMA)
        if(stm32_adc_handler->Instance == ADC1)
        {
            HAL_ADC_Stop_DMA(stm32_adc_handler);
        }
        else
#elif defined(BSP_ADC2_USING_DMA)
        if(stm32_adc_handler->Instance == ADC2)
        {
            HAL_ADC_Stop_DMA(stm32_adc_handler);
        }
        else
#elif defined(BSP_ADC3_USING_DMA)
        if(stm32_adc_handler->Instance == ADC3)
        {
            HAL_ADC_Stop_DMA(stm32_adc_handler);
        }
        else
#endif
        {
#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0)
            ADC_Disable(stm32_adc_handler);
#else
            __HAL_ADC_DISABLE(stm32_adc_handler);
#endif
        }
    }

    return RT_EOK;
}

static rt_uint32_t stm32_adc_get_channel(rt_uint32_t channel)
{
    rt_uint32_t stm32_channel = 0;

    switch (channel)
    {
    case  0:
        stm32_channel = ADC_CHANNEL_0;
        break;
    case  1:
        stm32_channel = ADC_CHANNEL_1;
        break;
    case  2:
        stm32_channel = ADC_CHANNEL_2;
        break;
    case  3:
        stm32_channel = ADC_CHANNEL_3;
        break;
    case  4:
        stm32_channel = ADC_CHANNEL_4;
        break;
    case  5:
        stm32_channel = ADC_CHANNEL_5;
        break;
    case  6:
        stm32_channel = ADC_CHANNEL_6;
        break;
    case  7:
        stm32_channel = ADC_CHANNEL_7;
        break;
    case  8:
        stm32_channel = ADC_CHANNEL_8;
        break;
    case  9:
        stm32_channel = ADC_CHANNEL_9;
        break;
    case 10:
        stm32_channel = ADC_CHANNEL_10;
        break;
    case 11:
        stm32_channel = ADC_CHANNEL_11;
        break;
    case 12:
        stm32_channel = ADC_CHANNEL_12;
        break;
    case 13:
        stm32_channel = ADC_CHANNEL_13;
        break;
    case 14:
        stm32_channel = ADC_CHANNEL_14;
        break;
    case 15:
        stm32_channel = ADC_CHANNEL_15;
        break;
    case 16:
        stm32_channel = ADC_CHANNEL_16;
        break;
    case 17:
        stm32_channel = ADC_CHANNEL_17;
        break;
#if defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32L4)
    case 18:
        stm32_channel = ADC_CHANNEL_18;
        break;
#endif
    }

    return stm32_channel;
}

static rt_err_t stm32_get_adc_dma_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    rt_uint16_t *pdat;
    rt_uint8_t chn_num;
    rt_uint16_t chn_size;
    rt_uint32_t sum = 0;
    int i = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    pdat = device->dma_buf;
    chn_num = device->dma_chn_num;
    chn_size = device->dma_chn_size;

    for(i=0; i<chn_size; i++)
    {
        sum += pdat[chn_num*i+channel];
    }
    *value = (sum+chn_size/2)/chn_size;

    return RT_EOK;
}

static rt_err_t stm32_get_adc_normal_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    ADC_ChannelConfTypeDef ADC_ChanConf;
    ADC_HandleTypeDef *stm32_adc_handler;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    stm32_adc_handler = device->parent.user_data;

    rt_memset(&ADC_ChanConf, 0, sizeof(ADC_ChanConf));

#if defined(SOC_SERIES_STM32F1)
    if (channel <= 17)
#elif defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32F2)  || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) \
        || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0)
    if (channel <= 18)
#endif
    {
        /* set stm32 ADC channel */
        ADC_ChanConf.Channel =  stm32_adc_get_channel(channel);
    }
    else
    {
#if defined(SOC_SERIES_STM32F1)
        LOG_E("ADC channel must be between 0 and 17.");
#elif defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32F2)  || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) \
        || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0)
        LOG_E("ADC channel must be between 0 and 18.");
#endif
        return -RT_ERROR;
    }
    ADC_ChanConf.Rank = 1;
#if defined(SOC_SERIES_STM32F0)
    ADC_ChanConf.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;
#elif defined(SOC_SERIES_STM32F1)
    ADC_ChanConf.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
#elif defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
    ADC_ChanConf.SamplingTime = ADC_SAMPLETIME_112CYCLES;
#elif defined(SOC_SERIES_STM32L4)
    ADC_ChanConf.SamplingTime = ADC_SAMPLETIME_247CYCLES_5;
#endif
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32L4)
    ADC_ChanConf.Offset = 0;
#endif
#ifdef SOC_SERIES_STM32L4
    ADC_ChanConf.OffsetNumber = ADC_OFFSET_NONE;
    ADC_ChanConf.SingleDiff = LL_ADC_SINGLE_ENDED;
#endif
    HAL_ADC_ConfigChannel(stm32_adc_handler, &ADC_ChanConf);

    /* start ADC */
    HAL_ADC_Start(stm32_adc_handler);

    /* Wait for the ADC to convert */
    HAL_ADC_PollForConversion(stm32_adc_handler, 100);

    /* get ADC value */
    *value = (rt_uint32_t)HAL_ADC_GetValue(stm32_adc_handler);

    return RT_EOK;
}

static rt_err_t stm32_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    ADC_HandleTypeDef *stm32_adc_handler;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    stm32_adc_handler = device->parent.user_data;

#if defined(BSP_ADC1_USING_DMA)
    if(stm32_adc_handler->Instance == ADC1)
    {
        return stm32_get_adc_dma_value(device, channel, value);
    }
    else
#elif defined(BSP_ADC2_USING_DMA)
    if(stm32_adc_handler->Instance == ADC2)
    {
        return stm32_get_adc_dma_value(device, channel, value);
    }
    else
#elif defined(BSP_ADC3_USING_DMA)
    if(stm32_adc_handler->Instance == ADC3)
    {
        return stm32_get_adc_dma_value(device, channel, value);
    }
    else
#endif
    {
        return stm32_get_adc_normal_value(device, channel, value);
    }
}

#if defined(BSP_ADC1_USING_DMA) || defined(BSP_ADC2_USING_DMA) || defined(BSP_ADC3_USING_DMA)
static int stm32_adc_sequence_init(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* hseq, int cnt)
{
    int i = 0;
    int result = 0;

    if(hadc->Init.NbrOfConversion != cnt)
    {
        LOG_E("NbrOfConversion of adc is not equal to sizeof sequence list");
    }
    else
    {
        for(i=0; i<cnt; i++)
        {
            if (HAL_ADC_ConfigChannel(hadc, &hseq[i]) != HAL_OK)
            {
                LOG_E("adc init channel sequence[%d] failed", i);
                result = -RT_ERROR;
                break;
            }
        }
    }

    return result;
}
#endif

static const struct rt_adc_ops stm_adc_ops =
{
    .enabled = stm32_adc_enabled,
    .convert = stm32_get_adc_value,
};

static int stm32_adc_init(void)
{
    int result = RT_EOK;
    /* save adc name */
    char name_buf[5] = {'a', 'd', 'c', '0', 0};
    int i = 0;
    rt_uint16_t chn_size = 0;

    for (i = 0; i < sizeof(adc_config) / sizeof(adc_config[0]); i++)
    {
        /* ADC init */
        name_buf[3] = '0';
        stm32_adc_obj[i].ADC_Handler = adc_config[i];
#if defined(ADC1)
        if (stm32_adc_obj[i].ADC_Handler.Instance == ADC1)
        {
            name_buf[3] = '1';
        }
#endif
#if defined(ADC2)
        if (stm32_adc_obj[i].ADC_Handler.Instance == ADC2)
        {
            name_buf[3] = '2';
        }
#endif
#if defined(ADC3)
        if (stm32_adc_obj[i].ADC_Handler.Instance == ADC3)
        {
            name_buf[3] = '3';
        }
#endif
        if (HAL_ADC_Init(&stm32_adc_obj[i].ADC_Handler) != HAL_OK)
        {
            LOG_E("%s init failed", name_buf);
            result = -RT_ERROR;
        }
        else
        {
            /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. */
#if defined(BSP_ADC1_USING_DMA)
            if (stm32_adc_obj[i].ADC_Handler.Instance == ADC1)
            {
                if(stm32_adc_sequence_init(&stm32_adc_obj[i].ADC_Handler, adc1_sequence, sizeof(adc1_sequence)/sizeof(adc1_sequence[0])) != RT_EOK)
                {
                    result = -RT_ERROR;
                    goto err;
                }
            }

            /* DMA controller clock enable */
            __HAL_RCC_DMA2_CLK_ENABLE();

            /* DMA interrupt init */
            /* DMA2_Stream2_IRQn interrupt configuration */
            HAL_NVIC_SetPriority(ADC1_DMA_IRQ, 5, 0);
            HAL_NVIC_EnableIRQ(ADC1_DMA_IRQ);
#endif

#if defined(BSP_ADC2_USING_DMA)
            if (stm32_adc_obj[i].ADC_Handler.Instance == ADC2)
            {
                if(stm32_adc_sequence_init(&stm32_adc_obj[i].ADC_Handler, adc2_sequence, sizeof(adc2_sequence)/sizeof(adc2_sequence[0])) != RT_EOK)
                {
                    result = -RT_ERROR;
                    goto err;
                }
            }
            
            /* DMA controller clock enable */
            __HAL_RCC_DMA2_CLK_ENABLE();

            /* DMA interrupt init */
            /* DMA2_Stream2_IRQn interrupt configuration */
            HAL_NVIC_SetPriority(ADC2_DMA_IRQ, 5, 0);
            HAL_NVIC_EnableIRQ(ADC2_DMA_IRQ);
#endif

#if defined(BSP_ADC3_USING_DMA)
            if (stm32_adc_obj[i].ADC_Handler.Instance == ADC3)
            {
                if(stm32_adc_sequence_init(&stm32_adc_obj[i].ADC_Handler, adc3_sequence, sizeof(adc3_sequence)/sizeof(adc3_sequence[0])) != RT_EOK)
                {
                    result = -RT_ERROR;
                    goto err;
                }
            }
            
            /* DMA controller clock enable */
            __HAL_RCC_DMA2_CLK_ENABLE();

            /* DMA interrupt init */
            /* DMA2_Stream2_IRQn interrupt configuration */
            HAL_NVIC_SetPriority(ADC3_DMA_IRQ, 5, 0);
            HAL_NVIC_EnableIRQ(ADC3_DMA_IRQ);
#endif

#if defined(BSP_ADC1_USING_DMA)
            if (stm32_adc_obj[i].ADC_Handler.Instance == ADC1)
            {
                chn_size = ADC1_CHAN_BUF_SIZE;
            }
            else
#endif
#if defined(BSP_ADC2_USING_DMA)
            if (stm32_adc_obj[i].ADC_Handler.Instance == ADC2)
            {
                chn_size = ADC2_CHAN_BUF_SIZE;
            }
            else
#endif
#if defined(BSP_ADC3_USING_DMA)
            if (stm32_adc_obj[i].ADC_Handler.Instance == ADC3)
            {
                chn_size = ADC3_CHAN_BUF_SIZE;
            }
            else
#endif
            {}
            
            /* register ADC device */
            if (rt_hw_adc_register(&stm32_adc_obj[i].stm32_adc_device, name_buf, &stm_adc_ops, &stm32_adc_obj[i].ADC_Handler, stm32_adc_obj[i].ADC_Handler.Init.NbrOfConversion, chn_size) == RT_EOK)
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

err:
    return result;
}
INIT_BOARD_EXPORT(stm32_adc_init);

#endif /* BSP_USING_ADC */
