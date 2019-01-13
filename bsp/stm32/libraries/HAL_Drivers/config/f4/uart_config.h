/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
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
#endif /* BSP_USING_UART1 */

#if defined(BSP_UART1_RX_USING_DMA)
#ifndef UART1_DMA_CONFIG
#define UART1_DMA_CONFIG                                            \
    {                                                               \
        .Instance = USART1_RX_DMA_INSTANCE,                         \
        .channel = USART1_RX_DMA_CHANNEL,                           \
        .dma_rcc = USART1_RX_DMA_RCC,                               \
        .dma_irq = USART1_RX_DMA_IRQ,                               \
    }
#endif /* UART1_DMA_CONFIG */
#endif /* BSP_UART1_RX_USING_DMA */

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG                                                \
    {                                                               \
        .name = "uart2",                                            \
        .Instance = USART2,                                         \
        .irq_type = USART2_IRQn,                                    \
    }
#endif /* UART2_CONFIG */
#endif /* BSP_USING_UART2 */

#if defined(BSP_UART2_RX_USING_DMA)
#ifndef UART2_DMA_CONFIG
#define UART2_DMA_CONFIG                                            \
    {                                                               \
        .Instance = USART2_RX_DMA_INSTANCE,                         \
        .channel = USART2_RX_DMA_CHANNEL,                           \
        .dma_rcc = USART2_RX_DMA_RCC,                               \
        .dma_irq = USART2_RX_DMA_IRQ,                               \
    }
#endif /* UART2_DMA_CONFIG */
#endif /* BSP_UART2_RX_USING_DMA */

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG                                                \
    {                                                               \
        .name = "uart3",                                            \
        .Instance = USART3,                                         \
        .irq_type = USART3_IRQn,                                    \
    }
#endif /* UART3_CONFIG */
#endif /* BSP_USING_UART3 */

#if defined(BSP_UART3_RX_USING_DMA)
#ifndef UART3_DMA_CONFIG
#define UART3_DMA_CONFIG                                            \
    {                                                               \
        .Instance = USART3_RX_DMA_INSTANCE,                         \
        .channel = USART3_RX_DMA_CHANNEL,                           \
        .dma_rcc = USART3_RX_DMA_RCC,                               \
        .dma_irq = USART3_RX_DMA_IRQ,                               \
    }
#endif /* UART3_DMA_CONFIG */
#endif /* BSP_UART3_RX_USING_DMA */

#if defined(BSP_USING_UART4)
#ifndef UART4_CONFIG
#define UART4_CONFIG                                                \
    {                                                               \
        .name = "uart4",                                            \
        .Instance = UART4,                                          \
        .irq_type = UART4_IRQn,                                     \
    }
#endif /* UART4_CONFIG */
#endif /* BSP_USING_UART4 */

#if defined(BSP_UART4_RX_USING_DMA)
#ifndef UART4_DMA_CONFIG
#define UART4_DMA_CONFIG                                            \
    {                                                               \
        .Instance = USART4_RX_DMA_INSTANCE,                         \
        .channel = USART4_RX_DMA_CHANNEL,                           \
        .dma_rcc = USART4_RX_DMA_RCC,                               \
        .dma_irq = USART4_RX_DMA_IRQ,                               \
    }
#endif /* UART4_DMA_CONFIG */
#endif /* BSP_UART4_RX_USING_DMA */

#if defined(BSP_USING_UART5)
#ifndef UART5_CONFIG
#define UART5_CONFIG                                                \
    {                                                               \
        .name = "uart5",                                            \
        .Instance = UART5,                                          \
        .irq_type = UART5_IRQn,                                     \
    }
#endif /* UART5_CONFIG */
#endif /* BSP_USING_UART5 */

#if defined(BSP_UART5_RX_USING_DMA)
#ifndef UART5_DMA_CONFIG
#define UART5_DMA_CONFIG                                            \
    {                                                               \
        .Instance = USART5_RX_DMA_INSTANCE,                         \
        .channel = USART5_RX_DMA_CHANNEL,                           \
        .dma_rcc = USART5_RX_DMA_RCC,                               \
        .dma_irq = USART5_RX_DMA_IRQ,                               \
    }
#endif /* UART5_DMA_CONFIG */
#endif /* BSP_UART5_RX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif
