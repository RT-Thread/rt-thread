/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-30     BalanceTWK   change to new framework
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
        .dma.channel.Instance = DMA1_Channel5,             \
        .dma_rcc = RCC_AHBENR_DMA1EN,                      \
        .dma_irq = DMA1_Channel5_IRQn,                     \
    }

#define USART1_RX_DMA_ISR                        DMA1_Channel5_IRQHandler
#endif

#if defined(BSP_USING_UART2)

#define UART2_CONFIG                                       \
    {                                                      \
        .name = "uart2",                                   \
        .Instance = USART2,                                \
        .irq_type = USART2_IRQn,                           \
        .dma.channel.Instance = DMA1_Channel6,             \
        .dma_rcc = RCC_AHBENR_DMA1EN,                      \
        .dma_irq = DMA1_Channel6_IRQn,                     \
    }

#define USART2_RX_DMA_ISR                        DMA1_Channel6_IRQHandler
#endif
    
#if defined(BSP_USING_UART3)

#define UART3_CONFIG                                       \
    {                                                      \
        .name = "uart3",                                   \
        .Instance = USART3,                                \
        .irq_type = USART3_IRQn,                           \
        .dma.channel.Instance = DMA1_Channel3,             \
        .dma_rcc = RCC_AHBENR_DMA1EN,                      \
        .dma_irq = DMA1_Channel3_IRQn,                     \
    }

#define USART3_RX_DMA_ISR                        DMA1_Channel3_IRQHandler
#endif

#if defined(BSP_USING_UART4)

#define UART4_CONFIG                                       \
    {                                                      \
        .name = "uart4",                                   \
        .Instance = UART4,                                 \
        .irq_type = UART4_IRQn,                            \
        .dma.channel.Instance = DMA2_Channel3,             \
        .dma_rcc = RCC_AHBENR_DMA2EN,                      \
        .dma_irq = DMA2_Channel3_IRQn,                     \
    }

#define USART4_RX_DMA_ISR                        DMA2_Channel3_IRQHandler
#endif

#if defined(BSP_USING_UART5)

#define UART5_CONFIG                                       \
    {                                                      \
        .name = "uart5",                                   \
        .Instance = UART5,                                 \
        .irq_type = UART5_IRQn,                            \
        .dma.channel.Instance = DMA_NOT_AVAILABLE,         \
    }
#endif
#endif
