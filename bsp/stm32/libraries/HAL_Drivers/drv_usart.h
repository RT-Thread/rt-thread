/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018.10.30     SummerGift   change to new framework
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>

int rt_hw_usart_init(void);

#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4)
#define DMA_INSTANCE_TYPE              DMA_Channel_TypeDef
#elif defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
#define DMA_INSTANCE_TYPE              DMA_Stream_TypeDef
#endif /*  defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4) */

/* stm32 config class */
struct stm32_uart_config
{
    const char *name;
    USART_TypeDef *Instance;
    IRQn_Type irq_type;

    union {
        DMA_INSTANCE_TYPE *Instance;

#if defined(SOC_SERIES_STM32F1)
        /* the DMA config has channel only, such as on STM32F1xx */
        struct {
            DMA_INSTANCE_TYPE *Instance;
        } channel;
#endif

#if defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
        /* the DMA config has stream and channel, such as on STM32F4xx */
        struct {
            DMA_INSTANCE_TYPE *Instance;
            rt_uint32_t channel;
        } stream_channel;
#endif

#if defined(SOC_SERIES_STM32L4)
        /* the DMA config has channel and request, such as on STM32L4xx */
        struct {
            DMA_INSTANCE_TYPE *Instance;
            rt_uint32_t request;
        } channel_request;
#endif
    } dma;

    rt_uint32_t dma_rcc;
    IRQn_Type dma_irq;
};

/* stm32 uart dirver class */
struct stm32_uart
{
    UART_HandleTypeDef handle;
    const struct stm32_uart_config *config;
    

#ifdef BSP_UART_USING_DMA_RX
    struct
    {
        DMA_HandleTypeDef handle;
        rt_size_t last_index;
    } dma;
#endif

    struct rt_serial_device serial;
};

#endif  /* __DRV_USART_H__ */
