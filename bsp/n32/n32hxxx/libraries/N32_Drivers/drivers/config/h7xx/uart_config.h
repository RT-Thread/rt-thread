/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
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
        .periph   = RCC_APB1_PERIPHEN_M7_USART1,                    \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk3,                \
    }
#endif /* UART1_CONFIG */
#endif /* BSP_USING_UART1 */
#if defined(BSP_UART1_RX_USING_DMA)
#if defined(UART1_RX_DMA_INSTANCE)
#ifndef UART1_DMA_RX_CONFIG
#define UART1_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance       = UART1_RX_DMA_INSTANCE,                    \
        .dma_irq        = UART1_RX_DMA_IRQ,                         \
        .HsInterface    = UART1_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART1_RX_DMA_DMA_RCC,                     \
        .dma_channel    = UART1_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART1_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART1_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART1_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART1_RX_DMA_INSTANCE */
#endif /* BSP_UART1_RX_USING_DMA */
#if defined(BSP_UART1_TX_USING_DMA)
#if defined(UART1_TX_DMA_INSTANCE)
#ifndef UART1_DMA_TX_CONFIG
#define UART1_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance       = UART1_TX_DMA_INSTANCE,                    \
        .dma_irq        = UART1_TX_DMA_IRQ,                         \
        .HsInterface    = UART1_TX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART1_TX_DMA_DMA_RCC,                     \
        .dma_channel    = UART1_TX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART1_TX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART1_TX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART1_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART1_TX_DMA_INSTANCE */
#endif /* BSP_UART1_TX_USING_DMA */


#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG                                                \
    {                                                               \
        .name = "uart2",                                            \
        .Instance = USART2,                                         \
        .irq_type = USART2_IRQn,                                    \
        .periph   = RCC_APB1_PERIPHEN_M7_USART2,                    \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk3,                \
    }
#endif /* UART2_CONFIG */
#endif /* BSP_USING_UART2 */
#if defined(BSP_UART2_RX_USING_DMA)
#if defined(UART2_RX_DMA_INSTANCE)
#ifndef UART2_DMA_RX_CONFIG
#define UART2_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance       = UART2_RX_DMA_INSTANCE,                    \
        .dma_irq        = UART2_RX_DMA_IRQ,                         \
        .HsInterface    = UART2_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART2_RX_DMA_DMA_RCC,                     \
        .dma_channel    = UART2_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART2_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART2_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART2_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART2_RX_DMA_INSTANCE */
#endif /* BSP_UART2_RX_USING_DMA */
#if defined(BSP_UART2_TX_USING_DMA)
#if defined(UART2_TX_DMA_INSTANCE)
#ifndef UART2_DMA_TX_CONFIG
#define UART2_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance       = UART2_TX_DMA_INSTANCE,                    \
        .dma_irq        = UART2_TX_DMA_IRQ,                         \
        .HsInterface    = UART2_TX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART2_TX_DMA_DMA_RCC,                     \
        .dma_channel    = UART2_TX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART2_TX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART2_TX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART2_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART2_TX_DMA_INSTANCE */
#endif /* BSP_UART2_TX_USING_DMA */


#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG                                                \
    {                                                               \
        .name = "uart3",                                            \
        .Instance = USART3,                                         \
        .irq_type = USART3_IRQn,                                    \
        .periph   = RCC_APB1_PERIPHEN_M7_USART3,                    \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk3,                \
    }
#endif /* UART3_CONFIG */
#endif /* BSP_USING_UART3 */
#if defined(BSP_UART3_RX_USING_DMA)
#if defined(UART3_RX_DMA_INSTANCE)
#ifndef UART3_DMA_RX_CONFIG
#define UART3_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance       = UART3_RX_DMA_INSTANCE,                    \
        .dma_irq        = UART3_RX_DMA_IRQ,                         \
        .HsInterface    = UART3_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART3_RX_DMA_DMA_RCC,                     \
        .dma_channel    = UART3_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART3_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART3_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART3_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART3_RX_DMA_INSTANCE */
#endif /* BSP_UART3_RX_USING_DMA */
#if defined(BSP_UART3_TX_USING_DMA)
#if defined(UART3_TX_DMA_INSTANCE)
#ifndef UART3_DMA_TX_CONFIG
#define UART3_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance       = UART3_TX_DMA_INSTANCE,                    \
        .dma_irq        = UART3_TX_DMA_IRQ,                         \
        .HsInterface    = UART3_TX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART3_TX_DMA_DMA_RCC,                     \
        .dma_channel    = UART3_TX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART3_TX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART3_TX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART3_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART3_TX_DMA_INSTANCE */
#endif /* BSP_UART3_TX_USING_DMA */


#if defined(BSP_USING_UART4)
#ifndef UART4_CONFIG
#define UART4_CONFIG                                                \
    {                                                               \
        .name = "uart4",                                            \
        .Instance = USART4,                                         \
        .irq_type = USART4_IRQn,                                    \
        .periph   = RCC_APB1_PERIPHEN_M7_USART4,                    \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk3,                \
    }
#endif /* UART4_CONFIG */
#endif /* BSP_USING_UART4 */
#if defined(BSP_UART4_RX_USING_DMA)
#if defined(UART4_RX_DMA_INSTANCE)
#ifndef UART4_DMA_RX_CONFIG
#define UART4_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance       = UART4_RX_DMA_INSTANCE,                    \
        .dma_irq        = UART4_RX_DMA_IRQ,                         \
        .HsInterface    = UART4_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART4_RX_DMA_DMA_RCC,                     \
        .dma_channel    = UART4_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART4_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART4_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART4_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART4_RX_DMA_INSTANCE */
#endif /* BSP_UART4_RX_USING_DMA */
#if defined(BSP_UART4_TX_USING_DMA)
#if defined(UART4_TX_DMA_INSTANCE)
#ifndef UART4_DMA_TX_CONFIG
#define UART4_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance       = UART4_TX_DMA_INSTANCE,                    \
        .dma_irq        = UART4_TX_DMA_IRQ,                         \
        .HsInterface    = UART4_TX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART4_TX_DMA_DMA_RCC,                     \
        .dma_channel    = UART4_TX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART4_TX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART4_TX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART4_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART4_TX_DMA_INSTANCE */
#endif /* BSP_UART4_TX_USING_DMA */


#if defined(BSP_USING_UART5)
#ifndef UART5_CONFIG
#define UART5_CONFIG                                                \
    {                                                               \
        .name = "uart5",                                            \
        .Instance = USART5,                                         \
        .irq_type = USART5_IRQn,                                    \
        .periph   = RCC_APB2_PERIPHEN_M7_USART5,                    \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk3,                \
    }
#endif /* UART5_CONFIG */
#endif /* BSP_USING_UART5 */
#if defined(BSP_UART5_RX_USING_DMA)
#if defined(UART5_RX_DMA_INSTANCE)
#ifndef UART5_DMA_RX_CONFIG
#define UART5_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance       = UART5_RX_DMA_INSTANCE,                    \
        .dma_irq        = UART5_RX_DMA_IRQ,                         \
        .HsInterface    = UART5_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART5_RX_DMA_DMA_RCC,                     \
        .dma_channel    = UART5_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART5_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART5_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART5_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART5_RX_DMA_INSTANCE */
#endif /* BSP_UART5_RX_USING_DMA */
#if defined(BSP_UART5_TX_USING_DMA)
#if defined(UART5_TX_DMA_INSTANCE)
#ifndef UART5_DMA_TX_CONFIG
#define UART5_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance       = UART5_TX_DMA_INSTANCE,                    \
        .dma_irq        = UART5_TX_DMA_IRQ,                         \
        .HsInterface    = UART5_TX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART5_TX_DMA_DMA_RCC,                     \
        .dma_channel    = UART5_TX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART5_TX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART5_TX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART5_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART5_TX_DMA_INSTANCE */
#endif /* BSP_UART5_TX_USING_DMA */


#if defined(BSP_USING_UART6)
#ifndef UART6_CONFIG
#define UART6_CONFIG                                                \
    {                                                               \
        .name = "uart6",                                            \
        .Instance = USART6,                                         \
        .irq_type = USART6_IRQn,                                    \
        .periph   = RCC_APB2_PERIPHEN_M7_USART6,                    \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk3,                \
    }
#endif /* UART6_CONFIG */
#endif /* BSP_USING_UART6 */
#if defined(BSP_UART6_RX_USING_DMA)
#if defined(UART6_RX_DMA_INSTANCE)
#ifndef UART6_DMA_RX_CONFIG
#define UART6_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance       = UART6_RX_DMA_INSTANCE,                    \
        .dma_irq        = UART6_RX_DMA_IRQ,                         \
        .HsInterface    = UART6_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART6_RX_DMA_DMA_RCC,                     \
        .dma_channel    = UART6_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART6_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART6_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART6_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART6_RX_DMA_INSTANCE */
#endif /* BSP_UART6_RX_USING_DMA */
#if defined(BSP_UART6_TX_USING_DMA)
#if defined(UART6_TX_DMA_INSTANCE)
#ifndef UART6_DMA_TX_CONFIG
#define UART6_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance       = UART6_TX_DMA_INSTANCE,                    \
        .dma_irq        = UART6_TX_DMA_IRQ,                         \
        .HsInterface    = UART6_TX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART6_TX_DMA_DMA_RCC,                     \
        .dma_channel    = UART6_TX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART6_TX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART6_TX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART6_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART6_TX_DMA_INSTANCE */
#endif /* BSP_UART6_TX_USING_DMA */


#if defined(BSP_USING_UART7)
#ifndef UART7_CONFIG
#define UART7_CONFIG                                                \
    {                                                               \
        .name = "uart7",                                            \
        .Instance = USART7,                                         \
        .irq_type = USART7_IRQn,                                    \
        .periph   = RCC_APB2_PERIPHEN_M7_USART7,                    \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk3,                \
    }
#endif /* UART7_CONFIG */
#endif /* BSP_USING_UART7 */
#if defined(BSP_UART7_RX_USING_DMA)
#if defined(UART7_RX_DMA_INSTANCE)
#ifndef UART7_DMA_RX_CONFIG
#define UART7_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance       = UART7_RX_DMA_INSTANCE,                    \
        .dma_irq        = UART7_RX_DMA_IRQ,                         \
        .HsInterface    = UART7_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART7_RX_DMA_DMA_RCC,                     \
        .dma_channel    = UART7_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART7_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART7_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART7_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART7_RX_DMA_INSTANCE */
#endif /* BSP_UART7_RX_USING_DMA */
#if defined(BSP_UART7_TX_USING_DMA)
#if defined(UART7_TX_DMA_INSTANCE)
#ifndef UART7_DMA_TX_CONFIG
#define UART7_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance       = UART7_TX_DMA_INSTANCE,                    \
        .dma_irq        = UART7_TX_DMA_IRQ,                         \
        .HsInterface    = UART7_TX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART7_TX_DMA_DMA_RCC,                     \
        .dma_channel    = UART7_TX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART7_TX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART7_TX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART7_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART7_TX_DMA_INSTANCE */
#endif /* BSP_UART7_TX_USING_DMA */


#if defined(BSP_USING_UART8)
#ifndef UART8_CONFIG
#define UART8_CONFIG                                                \
    {                                                               \
        .name = "uart8",                                            \
        .Instance = USART8,                                         \
        .irq_type = USART8_IRQn,                                    \
        .periph   = RCC_APB2_PERIPHEN_M7_USART8,                    \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk3,                \
    }
#endif /* UART8_CONFIG */
#endif /* BSP_USING_UART8 */
#if defined(BSP_UART8_RX_USING_DMA)
#if defined(UART8_RX_DMA_INSTANCE)
#ifndef UART8_DMA_RX_CONFIG
#define UART8_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance       = UART8_RX_DMA_INSTANCE,                    \
        .dma_irq        = UART8_RX_DMA_IRQ,                         \
        .HsInterface    = UART8_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART8_RX_DMA_DMA_RCC,                     \
        .dma_channel    = UART8_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART8_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART8_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART8_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART8_RX_DMA_INSTANCE */
#endif /* BSP_UART8_RX_USING_DMA */
#if defined(BSP_UART8_TX_USING_DMA)
#if defined(UART8_TX_DMA_INSTANCE)
#ifndef UART8_DMA_TX_CONFIG
#define UART8_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance       = UART8_TX_DMA_INSTANCE,                    \
        .dma_irq        = UART8_TX_DMA_IRQ,                         \
        .HsInterface    = UART8_TX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART8_TX_DMA_DMA_RCC,                     \
        .dma_channel    = UART8_TX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART8_TX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART8_TX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART8_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART8_TX_DMA_INSTANCE */
#endif /* BSP_UART8_TX_USING_DMA */


#if defined(BSP_USING_UART9)
#ifndef UART9_CONFIG
#define UART9_CONFIG                                                \
    {                                                               \
        .name = "uart9",                                            \
        .Instance = UART9,                                          \
        .irq_type = UART9_IRQn,                                     \
        .periph   = RCC_APB1_PERIPHEN_M7_UART9,                     \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk3,                \
    }
#endif /* UART9_CONFIG */
#endif /* BSP_USING_UART9 */
#if defined(BSP_UART9_RX_USING_DMA)
#if defined(UART9_RX_DMA_INSTANCE)
#ifndef UART9_DMA_RX_CONFIG
#define UART9_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance       = UART9_RX_DMA_INSTANCE,                    \
        .dma_irq        = UART9_RX_DMA_IRQ,                         \
        .HsInterface    = UART9_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART9_RX_DMA_DMA_RCC,                     \
        .dma_channel    = UART9_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART9_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART9_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART9_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART9_RX_DMA_INSTANCE */
#endif /* BSP_UART9_RX_USING_DMA */
#if defined(BSP_UART9_TX_USING_DMA)
#if defined(UART9_TX_DMA_INSTANCE)
#ifndef UART9_DMA_TX_CONFIG
#define UART9_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance       = UART9_TX_DMA_INSTANCE,                    \
        .dma_irq        = UART9_TX_DMA_IRQ,                         \
        .HsInterface    = UART9_TX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART9_TX_DMA_DMA_RCC,                     \
        .dma_channel    = UART9_TX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART9_TX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART9_TX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART9_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART9_TX_DMA_INSTANCE */
#endif /* BSP_UART9_TX_USING_DMA */


#if defined(BSP_USING_UART10)
#ifndef UART10_CONFIG
#define UART10_CONFIG                                               \
    {                                                               \
        .name = "uart10",                                           \
        .Instance = UART10,                                         \
        .irq_type = UART10_IRQn,                                    \
        .periph   = RCC_APB1_PERIPHEN_M7_UART10,                    \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk3,                \
    }
#endif /* UART10_CONFIG */
#endif /* BSP_USING_UART10 */
#if defined(BSP_UART10_RX_USING_DMA)
#if defined(UART10_RX_DMA_INSTANCE)
#ifndef UART10_DMA_RX_CONFIG
#define UART10_DMA_RX_CONFIG                                         \
    {                                                                \
        .Instance       = UART10_RX_DMA_INSTANCE,                    \
        .dma_irq        = UART10_RX_DMA_IRQ,                         \
        .HsInterface    = UART10_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART10_RX_DMA_DMA_RCC,                     \
        .dma_channel    = UART10_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART10_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART10_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART10_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART10_RX_DMA_INSTANCE */
#endif /* BSP_UART10_RX_USING_DMA */
#if defined(BSP_UART10_TX_USING_DMA)
#if defined(UART10_TX_DMA_INSTANCE)
#ifndef UART10_DMA_TX_CONFIG
#define UART10_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance       = UART10_TX_DMA_INSTANCE,                    \
        .dma_irq        = UART10_TX_DMA_IRQ,                         \
        .HsInterface    = UART10_TX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART10_TX_DMA_DMA_RCC,                     \
        .dma_channel    = UART10_TX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART10_TX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART10_TX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART10_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART10_TX_DMA_INSTANCE */
#endif /* BSP_UART10_TX_USING_DMA */


#if defined(BSP_USING_UART11)
#ifndef UART11_CONFIG
#define UART11_CONFIG                                               \
    {                                                               \
        .name = "uart11",                                           \
        .Instance = UART11,                                         \
        .irq_type = UART11_IRQn,                                    \
        .periph   = RCC_APB1_PERIPHEN_M7_UART11,                    \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk3,                \
    }
#endif /* UART11_CONFIG */
#endif /* BSP_USING_UART11 */
#if defined(BSP_UART11_RX_USING_DMA)
#if defined(UART11_RX_DMA_INSTANCE)
#ifndef UART11_DMA_RX_CONFIG
#define UART11_DMA_RX_CONFIG                                         \
    {                                                                \
        .Instance       = UART11_RX_DMA_INSTANCE,                    \
        .dma_irq        = UART11_RX_DMA_IRQ,                         \
        .HsInterface    = UART11_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART11_RX_DMA_DMA_RCC,                     \
        .dma_channel    = UART11_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART11_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART11_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART11_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART11_RX_DMA_INSTANCE */
#endif /* BSP_UART11_RX_USING_DMA */
#if defined(BSP_UART11_TX_USING_DMA)
#if defined(UART11_TX_DMA_INSTANCE)
#ifndef UART11_DMA_TX_CONFIG
#define UART11_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance       = UART11_TX_DMA_INSTANCE,                    \
        .dma_irq        = UART11_TX_DMA_IRQ,                         \
        .HsInterface    = UART11_TX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART11_TX_DMA_DMA_RCC,                     \
        .dma_channel    = UART11_TX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART11_TX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART11_TX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART11_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART11_TX_DMA_INSTANCE */
#endif /* BSP_UART11_TX_USING_DMA */


#if defined(BSP_USING_UART12)
#ifndef UART12_CONFIG
#define UART12_CONFIG                                               \
    {                                                               \
        .name = "uart12",                                           \
        .Instance = UART12,                                         \
        .irq_type = UART12_IRQn,                                    \
        .periph   = RCC_APB1_PERIPHEN_M7_UART12,                    \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk3,                \
    }
#endif /* UART12_CONFIG */
#endif /* BSP_USING_UART12 */
#if defined(BSP_UART12_RX_USING_DMA)
#if defined(UART12_RX_DMA_INSTANCE)
#ifndef UART12_DMA_RX_CONFIG
#define UART12_DMA_RX_CONFIG                                         \
    {                                                                \
        .Instance       = UART12_RX_DMA_INSTANCE,                    \
        .dma_irq        = UART12_RX_DMA_IRQ,                         \
        .HsInterface    = UART12_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART12_RX_DMA_DMA_RCC,                     \
        .dma_channel    = UART12_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART12_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART12_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART12_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART12_RX_DMA_INSTANCE */
#endif /* BSP_UART12_RX_USING_DMA */
#if defined(BSP_UART12_TX_USING_DMA)
#if defined(UART12_TX_DMA_INSTANCE)
#ifndef UART12_DMA_TX_CONFIG
#define UART12_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance       = UART12_TX_DMA_INSTANCE,                    \
        .dma_irq        = UART12_TX_DMA_IRQ,                         \
        .HsInterface    = UART12_TX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART12_TX_DMA_DMA_RCC,                     \
        .dma_channel    = UART12_TX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART12_TX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART12_TX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART12_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART12_TX_DMA_INSTANCE */
#endif /* BSP_UART12_TX_USING_DMA */


#if defined(BSP_USING_UART13)
#ifndef UART13_CONFIG
#define UART13_CONFIG                                                \
    {                                                               \
        .name = "uart13",                                            \
        .Instance = UART13,                                         \
        .irq_type = UART13_IRQn,                                    \
        .periph   = RCC_APB2_PERIPHEN_M7_UART13,                    \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk3,                \
    }
#endif /* UART13_CONFIG */
#endif /* BSP_USING_UART13 */
#if defined(BSP_UART13_RX_USING_DMA)
#if defined(UART13_RX_DMA_INSTANCE)
#ifndef UART13_DMA_RX_CONFIG
#define UART13_DMA_RX_CONFIG                                         \
    {                                                                \
        .Instance       = UART13_RX_DMA_INSTANCE,                    \
        .dma_irq        = UART13_RX_DMA_IRQ,                         \
        .HsInterface    = UART13_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART13_RX_DMA_DMA_RCC,                     \
        .dma_channel    = UART13_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART13_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART13_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART13_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART13_RX_DMA_INSTANCE */
#endif /* BSP_UART13_RX_USING_DMA */
#if defined(BSP_UART13_TX_USING_DMA)
#if defined(UART13_TX_DMA_INSTANCE)
#ifndef UART13_DMA_TX_CONFIG
#define UART13_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance       = UART13_TX_DMA_INSTANCE,                    \
        .dma_irq        = UART13_TX_DMA_IRQ,                         \
        .HsInterface    = UART13_TX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART13_TX_DMA_DMA_RCC,                     \
        .dma_channel    = UART13_TX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART13_TX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART13_TX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART13_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART13_TX_DMA_INSTANCE */
#endif /* BSP_UART13_TX_USING_DMA */


#if defined(BSP_USING_UART14)
#ifndef UART14_CONFIG
#define UART14_CONFIG                                                \
    {                                                               \
        .name = "uart14",                                            \
        .Instance = UART14,                                         \
        .irq_type = UART14_IRQn,                                    \
        .periph   = RCC_APB2_PERIPHEN_M7_UART14,                    \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk3,                \
    }
#endif /* UART14_CONFIG */
#endif /* BSP_USING_UART14 */
#if defined(BSP_UART14_RX_USING_DMA)
#if defined(UART14_RX_DMA_INSTANCE)
#ifndef UART14_DMA_RX_CONFIG
#define UART14_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance       = UART14_RX_DMA_INSTANCE,                    \
        .dma_irq        = UART14_RX_DMA_IRQ,                         \
        .HsInterface    = UART14_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART14_RX_DMA_DMA_RCC,                     \
        .dma_channel    = UART14_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART14_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART14_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART14_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART14_RX_DMA_INSTANCE */
#endif /* BSP_UART14_RX_USING_DMA */
#if defined(BSP_UART14_TX_USING_DMA)
#if defined(UART14_TX_DMA_INSTANCE)
#ifndef UART14_DMA_TX_CONFIG
#define UART14_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance       = UART14_TX_DMA_INSTANCE,                    \
        .dma_irq        = UART14_TX_DMA_IRQ,                         \
        .HsInterface    = UART14_TX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART14_TX_DMA_DMA_RCC,                     \
        .dma_channel    = UART14_TX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART14_TX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART14_TX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART14_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART14_TX_DMA_INSTANCE */
#endif /* BSP_UART14_TX_USING_DMA */


#if defined(BSP_USING_UART15)
#ifndef UART15_CONFIG
#define UART15_CONFIG                                                \
    {                                                               \
        .name = "uart15",                                            \
        .Instance = UART15,                                         \
        .irq_type = UART15_IRQn,                                    \
        .periph   = RCC_APB2_PERIPHEN_M7_UART15,                    \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk3,                \
    }
#endif /* UART15_CONFIG */
#endif /* BSP_USING_UART15 */
#if defined(BSP_UART15_RX_USING_DMA)
#if defined(UART15_RX_DMA_INSTANCE)
#ifndef UART15_DMA_RX_CONFIG
#define UART15_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance       = UART15_RX_DMA_INSTANCE,                    \
        .dma_irq        = UART15_RX_DMA_IRQ,                         \
        .HsInterface    = UART15_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART15_RX_DMA_DMA_RCC,                     \
        .dma_channel    = UART15_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART15_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART15_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART15_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART15_RX_DMA_INSTANCE */
#endif /* BSP_UART15_RX_USING_DMA */
#if defined(BSP_UART15_TX_USING_DMA)
#if defined(UART15_TX_DMA_INSTANCE)
#ifndef UART15_DMA_TX_CONFIG
#define UART15_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance       = UART15_TX_DMA_INSTANCE,                    \
        .dma_irq        = UART15_TX_DMA_IRQ,                         \
        .HsInterface    = UART15_TX_DMA_HANDSHAK,                    \
        .dma_rcc        = UART15_TX_DMA_DMA_RCC,                     \
        .dma_channel    = UART15_TX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = UART15_TX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = UART15_TX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* UART15_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART15_TX_DMA_INSTANCE */
#endif /* BSP_UART15_TX_USING_DMA */


#if defined(BSP_USING_LPUART1)
#ifndef LPUART1_CONFIG
#define LPUART1_CONFIG                                                \
    {                                                               \
        .name = "lpuart1",                                            \
        .Instance = LPUART1,                                         \
        .irq_type = LPUART1_IRQn,                                    \
        .periph   = RCC_RD_PERIPHEN_M7_LPUART1,                      \
        .EnablePeriphClk = RCC_EnableRDPeriphClk1,                   \
    }
#endif /* LPUART1_CONFIG */
#endif /* BSP_USING_LPUART1 */
#if defined(BSP_LPUART1_RX_USING_DMA)
#ifndef LPUART1_DMA_RX_CONFIG
#define LPUART1_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance       = LPUART1_RX_DMA_INSTANCE,                    \
        .dma_irq        = LPUART1_RX_DMA_IRQ,                         \
        .HsInterface    = LPUART1_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = LPUART1_RX_DMA_DMA_RCC,                     \
        .dma_channel    = LPUART1_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = LPUART1_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = LPUART1_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* LPUART1_DMA_RX_CONFIG */
#endif /* BSP_LPUART1_RX_USING_DMA */


#if defined(BSP_USING_LPUART2)
#ifndef LPUART2_CONFIG
#define LPUART2_CONFIG                                                \
    {                                                               \
        .name = "lpuart2",                                            \
        .Instance = LPUART2,                                         \
        .irq_type = LPUART2_IRQn,                                    \
        .periph   = RCC_RD_PERIPHEN_M7_LPUART2,                      \
        .EnablePeriphClk = RCC_EnableRDPeriphClk1,                   \
    }
#endif /* LPUART2_CONFIG */
#endif /* BSP_USING_LPUART2 */
#if defined(BSP_LPUART2_RX_USING_DMA)
#ifndef LPUART2_DMA_RX_CONFIG
#define LPUART2_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance       = LPUART2_RX_DMA_INSTANCE,                    \
        .dma_irq        = LPUART2_RX_DMA_IRQ,                         \
        .HsInterface    = LPUART2_RX_DMA_HANDSHAK,                    \
        .dma_rcc        = LPUART2_RX_DMA_DMA_RCC,                     \
        .dma_channel    = LPUART2_RX_DMA_DMA_CHANNEL,                 \
        .dmamux_channel = LPUART2_RX_DMA_DMAMUX_CHANNEL,              \
        .dmamux_request = LPUART2_RX_DMA_DMAMUX_REQUEST,              \
    }
#endif /* LPUART2_DMA_RX_CONFIG */
#endif /* BSP_LPUART2_RX_USING_DMA */


#ifdef __cplusplus
}
#endif

#endif /* __UART_CONFIG_H__ */

