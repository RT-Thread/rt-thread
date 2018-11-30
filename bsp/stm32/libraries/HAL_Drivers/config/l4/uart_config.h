/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   change to new framework
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>

#if defined(BSP_USING_UART1)

#define UART1_CONFIG                                       \
    {                                                      \
        .name = "uart1",                                   \
        .Instance = USART1,                                \
        .irq_type = USART1_IRQn,                           \
        .dma.channel_request.Instance = DMA2_Channel7,     \
        .dma.channel_request.request = DMA_REQUEST_2,      \
        .dma_rcc = RCC_AHB1ENR_DMA2EN,                     \
        .dma_irq = DMA2_Channel7_IRQn,                     \
    }

#define USART1_RX_DMA_ISR                        DMA2_Channel7_IRQHandler
#endif

#if defined(BSP_USING_UART2)

#define UART2_CONFIG                                       \
    {                                                      \
        .name = "uart2",                                   \
        .Instance = USART2,                                \
        .irq_type = USART2_IRQn,                           \
        .dma.channel_request.Instance = DMA1_Channel6,     \
        .dma.channel_request.request = DMA_REQUEST_2,      \
        .dma_rcc = RCC_AHB1SMENR_DMA1SMEN,                 \
        .dma_irq = DMA1_Channel6_IRQn,                     \
    }

#define USART2_RX_DMA_ISR                        DMA1_Channel6_IRQHandler
#endif

#endif
