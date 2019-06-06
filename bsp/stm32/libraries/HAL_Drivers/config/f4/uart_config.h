/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
<<<<<<< HEAD
 * 2018-10-30     SummerGift   change to new framework
=======
 * 2018-10-30     SummerGift   first version
 * 2019-01-03     zylx         modify dma support
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
 */
 
#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>

<<<<<<< HEAD
#if defined(BSP_USING_UART1)
#define UART1_CONFIG                                       \
    {                                                      \
        .name = "uart1",                                   \
        .Instance = USART1,                                \
        .irq_type = USART1_IRQn,                           \
        .dma.stream_channel.Instance = DMA2_Stream5,       \
        .dma.stream_channel.channel = DMA_CHANNEL_4,       \
        .dma_rcc = RCC_AHB1ENR_DMA2EN,                     \
        .dma_irq = DMA2_Stream5_IRQn,                      \
    }

#define USART1_RX_DMA_ISR                        DMA2_Stream5_IRQHandler
#endif

#if defined(BSP_USING_UART2)
#define UART2_CONFIG                                       \
    {                                                      \
        .name = "uart2",                                   \
        .Instance = USART2,                                \
        .irq_type = USART2_IRQn,                           \
        .dma.stream_channel.Instance = DMA1_Stream5,       \
        .dma.stream_channel.channel = DMA_CHANNEL_4,       \
        .dma_rcc = RCC_AHB1ENR_DMA1EN,                     \
        .dma_irq = DMA1_Stream5_IRQn,                      \
    }

#define USART2_RX_DMA_ISR                        DMA1_Stream5_IRQHandler
#endif

#if defined(BSP_USING_UART3)
#define UART3_CONFIG                                       \
    {                                                      \
        .name = "uart3",                                   \
        .Instance = USART3,                                \
        .irq_type = USART3_IRQn,                           \
        .dma.stream_channel.Instance = DMA1_Stream1,       \
        .dma.stream_channel.channel = DMA_CHANNEL_4,       \
        .dma_rcc = RCC_AHB1ENR_DMA1EN,                     \
        .dma_irq = DMA1_Stream1_IRQn,                      \
    }

#define USART3_RX_DMA_ISR                        DMA1_Stream1_IRQHandler
#endif

#if defined(BSP_USING_UART4)
#define UART4_CONFIG                                       \
    {                                                      \
        .name = "uart4",                                   \
        .Instance = UART4,                                 \
        .irq_type = UART4_IRQn,                            \
        .dma.stream_channel.Instance = DMA1_Stream2,       \
        .dma.stream_channel.channel = DMA_CHANNEL_4,       \
        .dma_rcc = RCC_AHB1ENR_DMA1EN,                     \
        .dma_irq = DMA1_Stream2_IRQn,                      \
    }

#define USART4_RX_DMA_ISR                        DMA1_Stream2_IRQHandler
#endif

#if defined(BSP_USING_UART5)
#define UART5_CONFIG                                       \
    {                                                      \
        .name = "uart5",                                   \
        .Instance = UART5,                                 \
        .irq_type = UART5_IRQn,                            \
        .dma.stream_channel.Instance = DMA1_Stream0,       \
        .dma.stream_channel.channel = DMA_CHANNEL_4,       \
        .dma_rcc = RCC_AHB1ENR_DMA1EN,                     \
        .dma_irq = DMA1_Stream0_IRQn,                      \
    }

#define USART5_RX_DMA_ISR                        DMA1_Stream0_IRQHandler
=======
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
        .Instance = UART1_RX_DMA_INSTANCE,                          \
        .channel = UART1_RX_DMA_CHANNEL,                            \
        .dma_rcc = UART1_RX_DMA_RCC,                                \
        .dma_irq = UART1_RX_DMA_IRQ,                                \
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
        .Instance = UART2_RX_DMA_INSTANCE,                          \
        .channel = UART2_RX_DMA_CHANNEL,                            \
        .dma_rcc = UART2_RX_DMA_RCC,                                \
        .dma_irq = UART2_RX_DMA_IRQ,                                \
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
        .Instance = UART3_RX_DMA_INSTANCE,                          \
        .channel = UART3_RX_DMA_CHANNEL,                            \
        .dma_rcc = UART3_RX_DMA_RCC,                                \
        .dma_irq = UART3_RX_DMA_IRQ,                                \
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
        .Instance = UART4_RX_DMA_INSTANCE,                          \
        .channel = UART4_RX_DMA_CHANNEL,                            \
        .dma_rcc = UART4_RX_DMA_RCC,                                \
        .dma_irq = UART4_RX_DMA_IRQ,                                \
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
        .Instance = UART5_RX_DMA_INSTANCE,                          \
        .channel = UART5_RX_DMA_CHANNEL,                            \
        .dma_rcc = UART5_RX_DMA_RCC,                                \
        .dma_irq = UART5_RX_DMA_IRQ,                                \
    }
#endif /* UART5_DMA_CONFIG */
#endif /* BSP_UART5_RX_USING_DMA */

#if defined(BSP_USING_UART6)
#ifndef UART6_CONFIG
#define UART6_CONFIG                                                \
    {                                                               \
        .name = "uart6",                                            \
        .Instance = USART6,                                         \
        .irq_type = USART6_IRQn,                                    \
    }
#endif /* UART6_CONFIG */
#endif /* BSP_USING_UART6 */

#if defined(BSP_UART6_RX_USING_DMA)
#ifndef UART6_DMA_CONFIG
#define UART6_DMA_CONFIG                                            \
    {                                                               \
        .Instance = UART6_RX_DMA_INSTANCE,                          \
        .channel = UART6_RX_DMA_CHANNEL,                            \
        .dma_rcc = UART6_RX_DMA_RCC,                                \
        .dma_irq = UART6_RX_DMA_IRQ,                                \
    }
#endif /* UART6_DMA_CONFIG */
#endif /* BSP_UART6_RX_USING_DMA */

#ifdef __cplusplus
}
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#endif

#endif
