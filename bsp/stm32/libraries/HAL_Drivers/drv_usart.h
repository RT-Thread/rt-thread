/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
<<<<<<< HEAD
 * 2018.10.30     SummerGift   change to new framework
=======
 * 2018.10.30     SummerGift   first version
 * 2019.03.05     whj4674672   add stm32h7 
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
<<<<<<< HEAD

int rt_hw_usart_init(void);


#if defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4)
#define DMA_INSTANCE_TYPE              DMA_Channel_TypeDef
#elif defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
#define DMA_INSTANCE_TYPE              DMA_Stream_TypeDef
#endif /*  defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4) */

#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F4)
#define UART_INSTANCE_CLEAR_FUNCTION    __HAL_UART_CLEAR_FLAG
#elif defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32F0)
=======
#include "drv_dma.h"

int rt_hw_usart_init(void);

#if defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4) \
    || defined(SOC_SERIES_STM32L0) || defined(SOC_SERIES_STM32G0)
#define DMA_INSTANCE_TYPE              DMA_Channel_TypeDef
#elif defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32H7)
#define DMA_INSTANCE_TYPE              DMA_Stream_TypeDef
#endif /*  defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4) */

#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F4) \
    || defined(SOC_SERIES_STM32L0) || defined(SOC_SERIES_STM32G0)
#define UART_INSTANCE_CLEAR_FUNCTION    __HAL_UART_CLEAR_FLAG
#elif defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#define UART_INSTANCE_CLEAR_FUNCTION    __HAL_UART_CLEAR_IT
#endif

/* stm32 config class */
struct stm32_uart_config
{
    const char *name;
    USART_TypeDef *Instance;
    IRQn_Type irq_type;
<<<<<<< HEAD

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
=======
    struct dma_config *dma_rx;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
};

/* stm32 uart dirver class */
struct stm32_uart
{
    UART_HandleTypeDef handle;
<<<<<<< HEAD
    const struct stm32_uart_config *config;
    

=======
    struct stm32_uart_config *config;
    
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#ifdef RT_SERIAL_USING_DMA
    struct
    {
        DMA_HandleTypeDef handle;
        rt_size_t last_index;
    } dma;
#endif
<<<<<<< HEAD

=======
    rt_uint8_t uart_dma_flag;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
    struct rt_serial_device serial;
};

#endif  /* __DRV_USART_H__ */
