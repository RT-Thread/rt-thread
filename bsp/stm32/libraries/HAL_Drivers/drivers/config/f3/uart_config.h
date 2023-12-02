/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-30     SummerGift   first version
 * 2019-01-03     zylx         modify dma support
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG                                                \
    {                                                               \
        .name = "uart1",                                            \
        .Instance = USART1,                                         \
        .irq_type = USART1_IRQn,                                    \
    }
#endif /* UART1_CONFIG */

#if defined(BSP_UART1_RX_USING_DMA)
#ifndef UART1_DMA_RX_CONFIG
#define UART1_DMA_RX_CONFIG                                        \
    {                                                              \
        .Instance = UART1_RX_DMA_INSTANCE,                         \
        .channel = UART1_RX_DMA_CHANNEL,                           \
        .dma_rcc = UART1_RX_DMA_RCC,                               \
        .dma_irq = UART1_RX_DMA_IRQ,                               \
    }
#endif /* UART1_DMA_RX_CONFIG */
#endif /* BSP_UART1_RX_USING_DMA */

#if defined(BSP_UART1_TX_USING_DMA)
#ifndef UART1_DMA_TX_CONFIG
#define UART1_DMA_TX_CONFIG                                        \
    {                                                              \
        .Instance = UART1_TX_DMA_INSTANCE,                         \
        .channel = UART1_TX_DMA_CHANNEL,                           \
        .dma_rcc = UART1_TX_DMA_RCC,                               \
        .dma_irq = UART1_TX_DMA_IRQ,                               \
    }
#endif /* UART1_DMA_TX_CONFIG */
#endif /* BSP_UART1_TX_USING_DMA */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG                                                \
    {                                                               \
        .name = "uart2",                                            \
        .Instance = USART2,                                         \
        .irq_type = USART2_IRQn,                                    \
    }
#endif /* UART2_CONFIG */

#if defined(BSP_UART2_RX_USING_DMA)
#ifndef UART2_DMA_RX_CONFIG
#define UART2_DMA_RX_CONFIG                                        \
    {                                                              \
        .Instance = UART2_RX_DMA_INSTANCE,                         \
        .channel = UART2_RX_DMA_CHANNEL,                           \
        .dma_rcc = UART2_RX_DMA_RCC,                               \
        .dma_irq = UART2_RX_DMA_IRQ,                               \
    }
#endif /* UART2_DMA_RX_CONFIG */
#endif /* BSP_UART2_RX_USING_DMA */

#if defined(BSP_UART2_TX_USING_DMA)
#ifndef UART2_DMA_TX_CONFIG
#define UART2_DMA_TX_CONFIG                                        \
    {                                                              \
        .Instance = UART2_TX_DMA_INSTANCE,                         \
        .channel = UART2_TX_DMA_CHANNEL,                           \
        .dma_rcc = UART2_TX_DMA_RCC,                               \
        .dma_irq = UART2_TX_DMA_IRQ,                               \
    }
#endif /* UART2_DMA_TX_CONFIG */
#endif /* BSP_UART2_TX_USING_DMA */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG                                                \
    {                                                               \
        .name = "uart3",                                            \
        .Instance = USART3,                                         \
        .irq_type = USART3_IRQn,                                    \
    }
#endif /* UART3_CONFIG */

#if defined(BSP_UART3_RX_USING_DMA)
#ifndef UART3_DMA_RX_CONFIG
#define UART3_DMA_RX_CONFIG                                        \
    {                                                              \
        .Instance = UART3_RX_DMA_INSTANCE,                         \
        .channel = UART3_RX_DMA_CHANNEL,                           \
        .dma_rcc = UART3_RX_DMA_RCC,                               \
        .dma_irq = UART3_RX_DMA_IRQ,                               \
    }
#endif /* UART3_DMA_RX_CONFIG */
#endif /* BSP_UART3_RX_USING_DMA */

#if defined(BSP_UART3_TX_USING_DMA)
#ifndef UART3_DMA_TX_CONFIG
#define UART3_DMA_TX_CONFIG                                        \
    {                                                              \
        .Instance = UART3_TX_DMA_INSTANCE,                         \
        .channel = UART3_TX_DMA_CHANNEL,                           \
        .dma_rcc = UART3_TX_DMA_RCC,                               \
        .dma_irq = UART3_TX_DMA_IRQ,                               \
    }
#endif /* UART3_DMA_TX_CONFIG */
#endif /* BSP_UART3_TX_USING_DMA */
#endif /* BSP_USING_UART3 */

#ifdef __cplusplus
}
#endif

#endif
