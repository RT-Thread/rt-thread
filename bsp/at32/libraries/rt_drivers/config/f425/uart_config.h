/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-31     shelton      first version
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>
#include "dma_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UART1_IRQHandler      USART1_IRQHandler
#define UART2_IRQHandler      USART2_IRQHandler

#if defined(BSP_USING_UART1)
#define UART1_CONFIG                                                \
    {                                                               \
        .name = "uart1",                                            \
        .uart_x = USART1,                                           \
        .irqn = USART1_IRQn,                                        \
    }

#if defined(BSP_UART1_RX_USING_DMA)
#define UART1_RX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART1_RX_DMA_CHANNEL,                        \
        .dma_clock = UART1_RX_DMA_CLOCK,                            \
        .dma_irqn = UART1_RX_DMA_IRQ,                               \
        .flex_channel = UART1_RX_DMA_FLEX_CHANNEL,                  \
        .request_id = UART1_RX_DMA_REQ_ID,                          \
    }
#endif /* BSP_UART1_RX_USING_DMA */

#if defined(BSP_UART1_TX_USING_DMA)
#define UART1_TX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART1_TX_DMA_CHANNEL,                        \
        .dma_clock = UART1_TX_DMA_CLOCK,                            \
        .dma_irqn = UART1_TX_DMA_IRQ,                               \
        .flex_channel = UART1_TX_DMA_FLEX_CHANNEL,                  \
        .request_id = UART1_TX_DMA_REQ_ID,                          \
    }
#endif /* BSP_UART1_TX_USING_DMA */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#define UART2_CONFIG                                                \
    {                                                               \
        .name = "uart2",                                            \
        .uart_x = USART2,                                           \
        .irqn = USART2_IRQn,                                        \
    }

#if defined(BSP_UART2_RX_USING_DMA)
#define UART2_RX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART2_RX_DMA_CHANNEL,                        \
        .dma_clock = UART2_RX_DMA_CLOCK,                            \
        .dma_irqn = UART2_RX_DMA_IRQ,                               \
        .flex_channel = UART2_RX_DMA_FLEX_CHANNEL,                  \
        .request_id = UART2_RX_DMA_REQ_ID,                          \
    }
#endif /* BSP_UART2_RX_USING_DMA */

#if defined(BSP_UART2_TX_USING_DMA)
#define UART2_TX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART2_TX_DMA_CHANNEL,                        \
        .dma_clock = UART2_TX_DMA_CLOCK,                            \
        .dma_irqn = UART2_TX_DMA_IRQ,                               \
        .flex_channel = UART2_TX_DMA_FLEX_CHANNEL,                  \
        .request_id = UART2_TX_DMA_REQ_ID,                          \
    }
#endif /* BSP_UART2_TX_USING_DMA */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
#define UART3_CONFIG                                                \
    {                                                               \
        .name = "uart3",                                            \
        .uart_x = USART3,                                           \
        .irqn = USART4_3_IRQn,                                      \
    }

#if defined(BSP_UART3_RX_USING_DMA)
#define UART3_RX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART3_RX_DMA_CHANNEL,                        \
        .dma_clock = UART3_RX_DMA_CLOCK,                            \
        .dma_irqn = UART3_RX_DMA_IRQ,                               \
        .flex_channel = UART3_RX_DMA_FLEX_CHANNEL,                  \
        .request_id = UART3_RX_DMA_REQ_ID,                          \
    }
#endif /* BSP_UART3_RX_USING_DMA */

#if defined(BSP_UART3_TX_USING_DMA)
#define UART3_TX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART3_TX_DMA_CHANNEL,                        \
        .dma_clock = UART3_TX_DMA_CLOCK,                            \
        .dma_irqn = UART3_TX_DMA_IRQ,                               \
        .flex_channel = UART3_TX_DMA_FLEX_CHANNEL,                  \
        .request_id = UART3_TX_DMA_REQ_ID,                          \
    }
#endif /* BSP_UART3_TX_USING_DMA */
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
#define UART4_CONFIG                                                \
    {                                                               \
        .name = "uart4",                                            \
        .uart_x = USART4,                                           \
        .irqn = USART4_3_IRQn,                                      \
    }
#endif /* BSP_USING_UART4 */

#ifdef __cplusplus
}
#endif

#endif
