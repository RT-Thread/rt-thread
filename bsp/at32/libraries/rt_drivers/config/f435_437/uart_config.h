/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-09     shelton      first version
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>
#include "dma_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG                                                \
    {                                                               \
        .name = "uart1",                                            \
        .uart_x = USART1,                                           \
        .irqn = USART1_IRQn,                                        \
    }
#endif /* UART1_CONFIG */

#if defined(BSP_UART1_RX_USING_DMA)
#ifndef UART1_RX_DMA_CONFIG
#define UART1_RX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART1_RX_DMA_CHANNEL,                        \
        .dma_clock = UART1_RX_DMA_CLOCK,                            \
        .dma_irqn = UART1_RX_DMA_IRQ,                               \
        .dmamux_channel = UART1_RX_DMA_MUX_CHANNEL,                 \
        .request_id = UART1_RX_DMA_REQ_ID,                          \
    }
#endif /* UART1_RX_DMA_CONFIG */
#endif /* BSP_UART1_RX_USING_DMA */

#if defined(BSP_UART1_TX_USING_DMA)
#ifndef UART1_TX_DMA_CONFIG
#define UART1_TX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART1_TX_DMA_CHANNEL,                        \
        .dma_clock = UART1_TX_DMA_CLOCK,                            \
        .dma_irqn = UART1_TX_DMA_IRQ,                               \
        .dmamux_channel = UART1_TX_DMA_MUX_CHANNEL,                 \
        .request_id = UART1_TX_DMA_REQ_ID,                          \
    }
#endif /* UART1_TX_DMA_CONFIG */
#endif /* BSP_UART1_TX_USING_DMA */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG                                                \
    {                                                               \
        .name = "uart2",                                            \
        .uart_x = USART2,                                           \
        .irqn = USART2_IRQn,                                        \
    }
#endif /* UART2_CONFIG */

#if defined(BSP_UART2_RX_USING_DMA)
#ifndef UART2_RX_DMA_CONFIG
#define UART2_RX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART2_RX_DMA_CHANNEL,                        \
        .dma_clock = UART2_RX_DMA_CLOCK,                            \
        .dma_irqn = UART2_RX_DMA_IRQ,                               \
        .dmamux_channel = UART2_RX_DMA_MUX_CHANNEL,                 \
        .request_id = UART2_RX_DMA_REQ_ID,                          \
    }
#endif /* UART2_RX_DMA_CONFIG */
#endif /* BSP_UART2_RX_USING_DMA */

#if defined(BSP_UART2_TX_USING_DMA)
#ifndef UART2_TX_DMA_CONFIG
#define UART2_TX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART2_TX_DMA_CHANNEL,                        \
        .dma_clock = UART2_TX_DMA_CLOCK,                            \
        .dma_irqn = UART2_TX_DMA_IRQ,                               \
        .dmamux_channel = UART2_TX_DMA_MUX_CHANNEL,                 \
        .request_id = UART2_TX_DMA_REQ_ID,                          \
    }
#endif /* UART2_TX_DMA_CONFIG */
#endif /* BSP_UART2_TX_USING_DMA */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG                                                \
    {                                                               \
        .name = "uart3",                                            \
        .uart_x = USART3,                                           \
        .irqn = USART3_IRQn,                                        \
    }
#endif /* UART3_CONFIG */

#if defined(BSP_UART3_RX_USING_DMA)
#ifndef UART3_RX_DMA_CONFIG
#define UART3_RX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART3_RX_DMA_CHANNEL,                        \
        .dma_clock = UART3_RX_DMA_CLOCK,                            \
        .dma_irqn = UART3_RX_DMA_IRQ,                               \
        .dmamux_channel = UART3_RX_DMA_MUX_CHANNEL,                 \
        .request_id = UART3_RX_DMA_REQ_ID,                          \
    }
#endif /* UART3_RX_DMA_CONFIG */
#endif /* BSP_UART3_RX_USING_DMA */

#if defined(BSP_UART3_TX_USING_DMA)
#ifndef UART3_TX_DMA_CONFIG
#define UART3_TX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART3_TX_DMA_CHANNEL,                        \
        .dma_clock = UART3_TX_DMA_CLOCK,                            \
        .dma_irqn = UART3_TX_DMA_IRQ,                               \
        .dmamux_channel = UART3_TX_DMA_MUX_CHANNEL,                 \
        .request_id = UART3_TX_DMA_REQ_ID,                          \
    }
#endif /* UART3_TX_DMA_CONFIG */
#endif /* BSP_UART3_TX_USING_DMA */
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
#ifndef UART4_CONFIG
#define UART4_CONFIG                                                \
    {                                                               \
        .name = "uart4",                                            \
        .uart_x = UART4,                                            \
        .irqn = UART4_IRQn,                                         \
    }
#endif /* UART4_CONFIG */

#if defined(BSP_UART4_RX_USING_DMA)
#ifndef UART4_RX_DMA_CONFIG
#define UART4_RX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART4_RX_DMA_CHANNEL,                        \
        .dma_clock = UART4_RX_DMA_CLOCK,                            \
        .dma_irqn = UART4_RX_DMA_IRQ,                               \
        .dmamux_channel = UART4_RX_DMA_MUX_CHANNEL,                 \
        .request_id = UART4_RX_DMA_REQ_ID,                          \
    }
#endif /* UART4_RX_DMA_CONFIG */
#endif /* BSP_UART4_RX_USING_DMA */

#if defined(BSP_UART4_TX_USING_DMA)
#ifndef UART4_TX_DMA_CONFIG
#define UART4_TX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART4_TX_DMA_CHANNEL,                        \
        .dma_clock = UART4_TX_DMA_CLOCK,                            \
        .dma_irqn = UART4_TX_DMA_IRQ,                               \
        .dmamux_channel = UART4_TX_DMA_MUX_CHANNEL,                 \
        .request_id = UART4_TX_DMA_REQ_ID,                          \
    }
#endif /* UART4_TX_DMA_CONFIG */
#endif /* BSP_UART4_TX_USING_DMA */
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
#ifndef UART5_CONFIG
#define UART5_CONFIG                                                \
    {                                                               \
        .name = "uart5",                                            \
        .uart_x = UART5,                                            \
        .irqn = UART5_IRQn,                                         \
    }
#endif /* UART5_CONFIG */

#if defined(BSP_UART5_RX_USING_DMA)
#ifndef UART5_RX_DMA_CONFIG
#define UART5_RX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART5_RX_DMA_CHANNEL,                        \
        .dma_clock = UART5_RX_DMA_CLOCK,                            \
        .dma_irqn = UART5_RX_DMA_IRQ,                               \
        .dmamux_channel = UART5_RX_DMA_MUX_CHANNEL,                 \
        .request_id = UART5_RX_DMA_REQ_ID,                          \
    }
#endif /* UART5_RX_DMA_CONFIG */
#endif /* BSP_UART5_RX_USING_DMA */

#if defined(BSP_UART5_TX_USING_DMA)
#ifndef UART5_TX_DMA_CONFIG
#define UART5_TX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART5_TX_DMA_CHANNEL,                        \
        .dma_clock = UART5_TX_DMA_CLOCK,                            \
        .dma_irqn = UART5_TX_DMA_IRQ,                               \
        .dmamux_channel = UART5_TX_DMA_MUX_CHANNEL,                 \
        .request_id = UART5_TX_DMA_REQ_ID,                          \
    }
#endif /* UART5_TX_DMA_CONFIG */
#endif /* BSP_UART5_TX_USING_DMA */
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
#ifndef UART6_CONFIG
#define UART6_CONFIG                                                \
    {                                                               \
        .name = "usart6",                                           \
        .uart_x = UART6,                                            \
        .irqn = USART6_IRQn,                                        \
    }
#endif /* UART6_CONFIG */

#if defined(BSP_UART6_RX_USING_DMA)
#ifndef UART6_RX_DMA_CONFIG
#define UART6_RX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART6_RX_DMA_CHANNEL,                        \
        .dma_clock = UART6_RX_DMA_CLOCK,                            \
        .dma_irqn = UART6_RX_DMA_IRQ,                               \
        .dmamux_channel = UART6_RX_DMA_MUX_CHANNEL,                 \
        .request_id = UART6_RX_DMA_REQ_ID,                          \
    }
#endif /* UART6_RX_DMA_CONFIG */
#endif /* BSP_UART6_RX_USING_DMA */

#if defined(BSP_UART6_TX_USING_DMA)
#ifndef UART6_TX_DMA_CONFIG
#define UART6_TX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART6_TX_DMA_CHANNEL,                        \
        .dma_clock = UART6_TX_DMA_CLOCK,                            \
        .dma_irqn = UART6_TX_DMA_IRQ,                               \
        .dmamux_channel = UART6_TX_DMA_MUX_CHANNEL,                 \
        .request_id = UART6_TX_DMA_REQ_ID,                          \
    }
#endif /* UART6_TX_DMA_CONFIG */
#endif /* BSP_UART6_TX_USING_DMA */
#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
#ifndef UART7_CONFIG
#define UART7_CONFIG                                                \
    {                                                               \
        .name = "uart7",                                            \
        .uart_x = UART7,                                            \
        .irqn = UART7_IRQn,                                         \
    }
#endif /* UART7_CONFIG */

#if defined(BSP_UART7_RX_USING_DMA)
#ifndef UART7_RX_DMA_CONFIG
#define UART7_RX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART7_RX_DMA_CHANNEL,                        \
        .dma_clock = UART7_RX_DMA_CLOCK,                            \
        .dma_irqn = UART7_RX_DMA_IRQ,                               \
        .dmamux_channel = UART7_RX_DMA_MUX_CHANNEL,                 \
        .request_id = UART7_RX_DMA_REQ_ID,                          \
    }
#endif /* UART7_RX_DMA_CONFIG */
#endif /* BSP_UART7_RX_USING_DMA */

#if defined(BSP_UART7_TX_USING_DMA)
#ifndef UART7_TX_DMA_CONFIG
#define UART7_TX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART7_TX_DMA_CHANNEL,                        \
        .dma_clock = UART7_TX_DMA_CLOCK,                            \
        .dma_irqn = UART7_TX_DMA_IRQ,                               \
        .dmamux_channel = UART7_TX_DMA_MUX_CHANNEL,                 \
        .request_id = UART7_TX_DMA_REQ_ID,                          \
    }
#endif /* UART7_TX_DMA_CONFIG */
#endif /* BSP_UART7_TX_USING_DMA */
#endif /* BSP_USING_UART7 */

#if defined(BSP_USING_UART8)
#ifndef UART8_CONFIG
#define UART8_CONFIG                                                \
    {                                                               \
        .name = "uart8",                                            \
        .uart_x = UART8,                                            \
        .irqn = UART8_IRQn,                                         \
    }
#endif /* UART8_CONFIG */
#endif /* BSP_USING_UART8 */

#ifdef __cplusplus
}
#endif

#endif
