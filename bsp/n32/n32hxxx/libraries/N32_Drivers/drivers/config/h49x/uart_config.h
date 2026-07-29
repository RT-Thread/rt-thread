/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-04-07     ox-horse         first version
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG                                 \
    {                                                \
        .name            = "uart1",                  \
        .Instance        = USART1,                   \
        .irq_type        = USART1_IRQn,              \
        .periph          = RCC_APB2_PERIPHEN_USART1, \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk,  \
    }
#endif /* UART1_CONFIG */
#endif /* BSP_USING_UART1 */
#if defined(BSP_UART1_RX_USING_DMA)
#if defined(UART1_RX_DMA)
#ifndef UART1_DMA_RX_CONFIG
#define UART1_DMA_RX_CONFIG              \
    {                                    \
        .DMAy    = UART1_RX_DMA,         \
        .DMAChx  = UART1_RX_DMA_CHType,  \
        .dma_irq = UART1_RX_DMA_IRQ,     \
        .dma_rcc = UART1_RX_DMA_RCC,     \
        .request = UART1_RX_DMA_REQUEST, \
        .channel = UART1_RX_DMA_CHANNEL, \
    }
#endif /* UART1_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART1_RX_DMA */
#endif /* BSP_UART1_RX_USING_DMA */
#if defined(BSP_UART1_TX_USING_DMA)
#if defined(UART1_TX_DMA)
#ifndef UART1_DMA_TX_CONFIG
#define UART1_DMA_TX_CONFIG              \
    {                                    \
        .DMAy    = UART1_TX_DMA,         \
        .DMAChx  = UART1_TX_DMA_CHType,  \
        .dma_irq = UART1_TX_DMA_IRQ,     \
        .dma_rcc = UART1_TX_DMA_RCC,     \
        .request = UART1_TX_DMA_REQUEST, \
        .channel = UART1_TX_DMA_CHANNEL, \
    }
#endif /* UART1_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART1_TX_DMA */
#endif /* BSP_UART1_TX_USING_DMA */

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG                                 \
    {                                                \
        .name            = "uart2",                  \
        .Instance        = USART2,                   \
        .irq_type        = USART2_IRQn,              \
        .periph          = RCC_APB1_PERIPHEN_USART2, \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk,  \
    }
#endif /* UART2_CONFIG */
#endif /* BSP_USING_UART2 */
#if defined(BSP_UART2_RX_USING_DMA)
#if defined(UART2_RX_DMA)
#ifndef UART2_DMA_RX_CONFIG
#define UART2_DMA_RX_CONFIG              \
    {                                    \
        .DMAy    = UART2_RX_DMA,         \
        .DMAChx  = UART2_RX_DMA_CHType,  \
        .dma_irq = UART2_RX_DMA_IRQ,     \
        .dma_rcc = UART2_RX_DMA_RCC,     \
        .request = UART2_RX_DMA_REQUEST, \
        .channel = UART2_RX_DMA_CHANNEL, \
    }
#endif /* UART2_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART2_RX_DMA */
#endif /* BSP_UART2_RX_USING_DMA */
#if defined(BSP_UART2_TX_USING_DMA)
#if defined(UART2_TX_DMA)
#ifndef UART2_DMA_TX_CONFIG
#define UART2_DMA_TX_CONFIG              \
    {                                    \
        .DMAy    = UART2_TX_DMA,         \
        .DMAChx  = UART2_TX_DMA_CHType,  \
        .dma_irq = UART2_TX_DMA_IRQ,     \
        .dma_rcc = UART2_TX_DMA_RCC,     \
        .request = UART2_TX_DMA_REQUEST, \
        .channel = UART2_TX_DMA_CHANNEL, \
    }
#endif /* UART2_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART2_TX_DMA */
#endif /* BSP_UART2_TX_USING_DMA */

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG                                 \
    {                                                \
        .name            = "uart3",                  \
        .Instance        = USART3,                   \
        .irq_type        = USART3_IRQn,              \
        .periph          = RCC_APB1_PERIPHEN_USART3, \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk,  \
    }
#endif /* UART3_CONFIG */
#endif /* BSP_USING_UART3 */
#if defined(BSP_UART3_RX_USING_DMA)
#if defined(UART3_RX_DMA)
#ifndef UART3_DMA_RX_CONFIG
#define UART3_DMA_RX_CONFIG              \
    {                                    \
        .DMAy    = UART3_RX_DMA,         \
        .DMAChx  = UART3_RX_DMA_CHType,  \
        .dma_irq = UART3_RX_DMA_IRQ,     \
        .dma_rcc = UART3_RX_DMA_RCC,     \
        .request = UART3_RX_DMA_REQUEST, \
        .channel = UART3_RX_DMA_CHANNEL, \
    }
#endif /* UART3_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART3_RX_DMA */
#endif /* BSP_UART3_RX_USING_DMA */
#if defined(BSP_UART3_TX_USING_DMA)
#if defined(UART3_TX_DMA)
#ifndef UART3_DMA_TX_CONFIG
#define UART3_DMA_TX_CONFIG              \
    {                                    \
        .DMAy    = UART3_TX_DMA,         \
        .DMAChx  = UART3_TX_DMA_CHType,  \
        .dma_irq = UART3_TX_DMA_IRQ,     \
        .dma_rcc = UART3_TX_DMA_RCC,     \
        .request = UART3_TX_DMA_REQUEST, \
        .channel = UART3_TX_DMA_CHANNEL, \
    }
#endif /* UART3_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART3_TX_DMA */
#endif /* BSP_UART3_TX_USING_DMA */

#if defined(BSP_USING_UART4)
#ifndef UART4_CONFIG
#define UART4_CONFIG                                 \
    {                                                \
        .name            = "uart4",                  \
        .Instance        = USART4,                   \
        .irq_type        = USART4_IRQn,              \
        .periph          = RCC_APB2_PERIPHEN_USART4, \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk,  \
    }
#endif /* UART4_CONFIG */
#endif /* BSP_USING_UART4 */
#if defined(BSP_UART4_RX_USING_DMA)
#if defined(UART4_RX_DMA)
#ifndef UART4_DMA_RX_CONFIG
#define UART4_DMA_RX_CONFIG              \
    {                                    \
        .DMAy    = UART4_RX_DMA,         \
        .DMAChx  = UART4_RX_DMA_CHType,  \
        .dma_irq = UART4_RX_DMA_IRQ,     \
        .dma_rcc = UART4_RX_DMA_RCC,     \
        .request = UART4_RX_DMA_REQUEST, \
        .channel = UART4_RX_DMA_CHANNEL, \
    }
#endif /* UART4_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART4_RX_DMA */
#endif /* BSP_UART4_RX_USING_DMA */
#if defined(BSP_UART4_TX_USING_DMA)
#if defined(UART4_TX_DMA)
#ifndef UART4_DMA_TX_CONFIG
#define UART4_DMA_TX_CONFIG              \
    {                                    \
        .DMAy    = UART4_TX_DMA,         \
        .DMAChx  = UART4_TX_DMA_CHType,  \
        .dma_irq = UART4_TX_DMA_IRQ,     \
        .dma_rcc = UART4_TX_DMA_RCC,     \
        .request = UART4_TX_DMA_REQUEST, \
        .channel = UART4_TX_DMA_CHANNEL, \
    }
#endif /* UART4_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART4_TX_DMA */
#endif /* BSP_UART4_TX_USING_DMA */

#if defined(BSP_USING_UART5)
#ifndef UART5_CONFIG
#define UART5_CONFIG                                \
    {                                               \
        .name            = "uart5",                 \
        .Instance        = UART5,                   \
        .irq_type        = UART5_IRQn,              \
        .periph          = RCC_APB1_PERIPHEN_UART5, \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk, \
    }
#endif /* UART5_CONFIG */
#endif /* BSP_USING_UART5 */
#if defined(BSP_UART5_RX_USING_DMA)
#if defined(UART5_RX_DMA)
#ifndef UART5_DMA_RX_CONFIG
#define UART5_DMA_RX_CONFIG              \
    {                                    \
        .DMAy    = UART5_RX_DMA,         \
        .DMAChx  = UART5_RX_DMA_CHType,  \
        .dma_irq = UART5_RX_DMA_IRQ,     \
        .dma_rcc = UART5_RX_DMA_RCC,     \
        .request = UART5_RX_DMA_REQUEST, \
        .channel = UART5_RX_DMA_CHANNEL, \
    }
#endif /* UART5_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART5_RX_DMA */
#endif /* BSP_UART5_RX_USING_DMA */
#if defined(BSP_UART5_TX_USING_DMA)
#if defined(UART5_TX_DMA)
#ifndef UART5_DMA_TX_CONFIG
#define UART5_DMA_TX_CONFIG              \
    {                                    \
        .DMAy    = UART5_TX_DMA,         \
        .DMAChx  = UART5_TX_DMA_CHType,  \
        .dma_irq = UART5_TX_DMA_IRQ,     \
        .dma_rcc = UART5_TX_DMA_RCC,     \
        .request = UART5_TX_DMA_REQUEST, \
        .channel = UART5_TX_DMA_CHANNEL, \
    }
#endif /* UART5_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART5_TX_DMA */
#endif /* BSP_UART5_TX_USING_DMA */

#if defined(BSP_USING_UART6)
#ifndef UART6_CONFIG
#define UART6_CONFIG                                \
    {                                               \
        .name            = "uart6",                 \
        .Instance        = UART6,                   \
        .irq_type        = UART6_IRQn,              \
        .periph          = RCC_APB2_PERIPHEN_UART6, \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk, \
    }
#endif /* UART6_CONFIG */
#endif /* BSP_USING_UART6 */
#if defined(BSP_UART6_RX_USING_DMA)
#if defined(UART6_RX_DMA)
#ifndef UART6_DMA_RX_CONFIG
#define UART6_DMA_RX_CONFIG              \
    {                                    \
        .DMAy    = UART6_RX_DMA,         \
        .DMAChx  = UART6_RX_DMA_CHType,  \
        .dma_irq = UART6_RX_DMA_IRQ,     \
        .dma_rcc = UART6_RX_DMA_RCC,     \
        .request = UART6_RX_DMA_REQUEST, \
        .channel = UART6_RX_DMA_CHANNEL, \
    }
#endif /* UART6_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART6_RX_DMA */
#endif /* BSP_UART6_RX_USING_DMA */
#if defined(BSP_UART6_TX_USING_DMA)
#if defined(UART6_TX_DMA)
#ifndef UART6_DMA_TX_CONFIG
#define UART6_DMA_TX_CONFIG              \
    {                                    \
        .DMAy    = UART6_TX_DMA,         \
        .DMAChx  = UART6_TX_DMA_CHType,  \
        .dma_irq = UART6_TX_DMA_IRQ,     \
        .dma_rcc = UART6_TX_DMA_RCC,     \
        .request = UART6_TX_DMA_REQUEST, \
        .channel = UART6_TX_DMA_CHANNEL, \
    }
#endif /* UART6_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART6_TX_DMA */
#endif /* BSP_UART6_TX_USING_DMA */

#if defined(BSP_USING_UART7)
#ifndef UART7_CONFIG
#define UART7_CONFIG                                \
    {                                               \
        .name            = "uart7",                 \
        .Instance        = UART7,                   \
        .irq_type        = UART7_IRQn,              \
        .periph          = RCC_APB2_PERIPHEN_UART7, \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk, \
    }
#endif /* UART7_CONFIG */
#endif /* BSP_USING_UART7 */
#if defined(BSP_UART7_RX_USING_DMA)
#if defined(UART7_RX_DMA)
#ifndef UART7_DMA_RX_CONFIG
#define UART7_DMA_RX_CONFIG              \
    {                                    \
        .DMAy    = UART7_RX_DMA,         \
        .DMAChx  = UART7_RX_DMA_CHType,  \
        .dma_irq = UART7_RX_DMA_IRQ,     \
        .dma_rcc = UART7_RX_DMA_RCC,     \
        .request = UART7_RX_DMA_REQUEST, \
        .channel = UART7_RX_DMA_CHANNEL, \
    }
#endif /* UART7_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART7_RX_DMA */
#endif /* BSP_UART7_RX_USING_DMA */
#if defined(BSP_UART7_TX_USING_DMA)
#if defined(UART7_TX_DMA)
#ifndef UART7_DMA_TX_CONFIG
#define UART7_DMA_TX_CONFIG              \
    {                                    \
        .DMAy    = UART7_TX_DMA,         \
        .DMAChx  = UART7_TX_DMA_CHType,  \
        .dma_irq = UART7_TX_DMA_IRQ,     \
        .dma_rcc = UART7_TX_DMA_RCC,     \
        .request = UART7_TX_DMA_REQUEST, \
        .channel = UART7_TX_DMA_CHANNEL, \
    }
#endif /* UART7_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART7_TX_DMA */
#endif /* BSP_UART7_TX_USING_DMA */

#if defined(BSP_USING_UART8)
#ifndef UART8_CONFIG
#define UART8_CONFIG                                \
    {                                               \
        .name            = "uart8",                 \
        .Instance        = UART8,                   \
        .irq_type        = UART8_IRQn,              \
        .periph          = RCC_APB1_PERIPHEN_UART8, \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk, \
    }
#endif /* UART8_CONFIG */
#endif /* BSP_USING_UART8 */
#if defined(BSP_UART8_RX_USING_DMA)
#if defined(UART8_RX_DMA)
#ifndef UART8_DMA_RX_CONFIG
#define UART8_DMA_RX_CONFIG              \
    {                                    \
        .DMAy    = UART8_RX_DMA,         \
        .DMAChx  = UART8_RX_DMA_CHType,  \
        .dma_irq = UART8_RX_DMA_IRQ,     \
        .dma_rcc = UART8_RX_DMA_RCC,     \
        .request = UART8_RX_DMA_REQUEST, \
        .channel = UART8_RX_DMA_CHANNEL, \
    }
#endif /* UART8_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART8_RX_DMA */
#endif /* BSP_UART8_RX_USING_DMA */
#if defined(BSP_UART8_TX_USING_DMA)
#if defined(UART8_TX_DMA)
#ifndef UART8_DMA_TX_CONFIG
#define UART8_DMA_TX_CONFIG              \
    {                                    \
        .DMAy    = UART8_TX_DMA,         \
        .DMAChx  = UART8_TX_DMA_CHType,  \
        .dma_irq = UART8_TX_DMA_IRQ,     \
        .dma_rcc = UART8_TX_DMA_RCC,     \
        .request = UART8_TX_DMA_REQUEST, \
        .channel = UART8_TX_DMA_CHANNEL, \
    }
#endif /* UART8_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART8_TX_DMA */
#endif /* BSP_UART8_TX_USING_DMA */

#if defined(BSP_USING_UART9)
#ifndef UART9_CONFIG
#define UART9_CONFIG                                 \
    {                                                \
        .name            = "uart9",                  \
        .Instance        = USART9,                   \
        .irq_type        = USART9_IRQn,              \
        .periph          = RCC_APB2_PERIPHEN_USART9, \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk,  \
    }
#endif /* UART9_CONFIG */
#endif /* BSP_USING_UART9 */
#if defined(BSP_UART9_RX_USING_DMA)
#if defined(UART9_RX_DMA)
#ifndef UART9_DMA_RX_CONFIG
#define UART9_DMA_RX_CONFIG              \
    {                                    \
        .DMAy    = UART9_RX_DMA,         \
        .DMAChx  = UART9_RX_DMA_CHType,  \
        .dma_irq = UART9_RX_DMA_IRQ,     \
        .dma_rcc = UART9_RX_DMA_RCC,     \
        .request = UART9_RX_DMA_REQUEST, \
        .channel = UART9_RX_DMA_CHANNEL, \
    }
#endif /* UART9_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART9_RX_DMA */
#endif /* BSP_UART9_RX_USING_DMA */
#if defined(BSP_UART9_TX_USING_DMA)
#if defined(UART9_TX_DMA)
#ifndef UART9_DMA_TX_CONFIG
#define UART9_DMA_TX_CONFIG              \
    {                                    \
        .DMAy    = UART9_TX_DMA,         \
        .DMAChx  = UART9_TX_DMA_CHType,  \
        .dma_irq = UART9_TX_DMA_IRQ,     \
        .dma_rcc = UART9_TX_DMA_RCC,     \
        .request = UART9_TX_DMA_REQUEST, \
        .channel = UART9_TX_DMA_CHANNEL, \
    }
#endif /* UART9_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART9_TX_DMA */
#endif /* BSP_UART9_TX_USING_DMA */

#if defined(BSP_USING_UART10)
#ifndef UART10_CONFIG
#define UART10_CONFIG                                \
    {                                                \
        .name            = "uart10",                 \
        .Instance        = URT10,                    \
        .irq_type        = UART10_IRQn,              \
        .periph          = RCC_APB2_PERIPHEN_UART10, \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk,  \
    }
#endif /* UART10_CONFIG */
#endif /* BSP_USING_UART10 */
#if defined(BSP_UART10_RX_USING_DMA)
#if defined(UART10_RX_DMA)
#ifndef UART10_DMA_RX_CONFIG
#define UART10_DMA_RX_CONFIG              \
    {                                     \
        .DMAy    = UART10_RX_DMA,         \
        .DMAChx  = UART10_RX_DMA_CHType,  \
        .dma_irq = UART10_RX_DMA_IRQ,     \
        .dma_rcc = UART10_RX_DMA_RCC,     \
        .request = UART10_RX_DMA_REQUEST, \
        .channel = UART10_RX_DMA_CHANNEL, \
    }
#endif /* UART10_DMA_RX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART10_RX_DMA */
#endif /* BSP_UART10_RX_USING_DMA */
#if defined(BSP_UART10_TX_USING_DMA)
#if defined(UART10_TX_DMA)
#ifndef UART10_DMA_TX_CONFIG
#define UART10_DMA_TX_CONFIG              \
    {                                     \
        .DMAy    = UART10_TX_DMA,         \
        .DMAChx  = UART10_TX_DMA_CHType,  \
        .dma_irq = UART10_TX_DMA_IRQ,     \
        .dma_rcc = UART10_TX_DMA_RCC,     \
        .request = UART10_TX_DMA_REQUEST, \
        .channel = UART10_TX_DMA_CHANNEL, \
    }
#endif /* UART10_DMA_TX_CONFIG */
#else
#error "The DMA resource is not available."
#endif /* UART10_TX_DMA */
#endif /* BSP_UART10_TX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /* __UART_CONFIG_H__ */

