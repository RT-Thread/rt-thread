/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-23     AisinoChip   the first version
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>
#include "board.h"


#ifdef __cplusplus
extern "C" {
#endif

#if defined(RT_USING_SERIAL)

#if defined(BSP_USING_UART1)

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_UART1_RX_USING_DMA)
#ifndef UART1_DMA_RX_CONFIG
#define UART1_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance = UART1_RX_DMA_INSTANCE,                          \
        .dma_rcc  = UART1_RX_DMA_RCC,                               \
        .dma_irq  = UART1_RX_DMA_IRQ,                               \
        .channel  = UART1_RX_DMA_CHANNEL,                           \
        .request  = UART1_RX_DMA_REQUEST,                           \
    }
#endif /* UART1_DMA_RX_CONFIG */
#endif /* BSP_UART1_RX_USING_DMA */

#if defined(BSP_UART1_TX_USING_DMA)
#ifndef UART1_DMA_TX_CONFIG
#define UART1_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance = UART1_TX_DMA_INSTANCE,                          \
        .dma_rcc  = UART1_TX_DMA_RCC,                               \
        .dma_irq  = UART1_TX_DMA_IRQ,                               \
        .channel  = UART1_RX_DMA_CHANNEL,                           \
        .request  = UART1_RX_DMA_REQUEST,                           \
    }
#endif /* UART1_DMA_TX_CONFIG */
#endif /* BSP_UART1_TX_USING_DMA */
#endif /* RT_SERIAL_USING_DMA */

#ifndef UART1_CONFIG
#define UART1_CONFIG                                                \
    {                                                               \
        .name = "uart1",                                            \
        .Instance = UART1,                                          \
        .irq_type = UART1_IRQn,                                     \
        .enable_id = EN_UART1,                                      \
        .tx_port  = UART1_TX_PORT,                                  \
        .rx_port  = UART1_RX_PORT,                                  \
        .tx_pin   = UART1_TX_PIN,                                   \
        .rx_pin   = UART1_RX_PIN,                                   \
    }
#endif /* UART1_CONFIG */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_UART2_RX_USING_DMA)
#ifndef UART2_DMA_RX_CONFIG
#define UART2_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance = UART2_RX_DMA_INSTANCE,                          \
        .dma_rcc  = UART2_RX_DMA_RCC,                               \
        .dma_irq  = UART2_RX_DMA_IRQ,                               \
        .channel  = UART2_RX_DMA_CHANNEL,                           \
        .request  = UART2_RX_DMA_REQUEST,                           \
    }
#endif /* UART2_DMA_RX_CONFIG */
#endif /* BSP_UART2_RX_USING_DMA */

#if defined(BSP_UART2_TX_USING_DMA)
#ifndef UART2_DMA_TX_CONFIG
#define UART2_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance = UART2_TX_DMA_INSTANCE,                          \
        .dma_rcc  = UART2_TX_DMA_RCC,                               \
        .dma_irq  = UART2_TX_DMA_IRQ,                               \
        .channel  = UART2_TX_DMA_CHANNEL,                           \
        .request  = UART2_TX_DMA_REQUEST,                           \
    }
#endif /* UART2_DMA_TX_CONFIG */
#endif /* BSP_UART2_TX_USING_DMA */
#endif /* RT_SERIAL_USING_DMA */

#ifndef UART2_CONFIG
#define UART2_CONFIG                                                \
    {                                                               \
        .name = "uart2",                                            \
        .Instance = UART2,                                          \
        .irq_type = UART2_IRQn,                                     \
        .enable_id = EN_UART2,                                      \
        .tx_port  = UART2_TX_PORT,                                  \
        .rx_port  = UART2_RX_PORT,                                  \
        .tx_pin   = UART2_TX_PIN,                                   \
        .rx_pin   = UART2_RX_PIN,                                   \
    }
#endif /* UART2_CONFIG */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_UART3_RX_USING_DMA)
#ifndef UART3_DMA_RX_CONFIG
#define UART3_DMA_RX_CONFIG                                         \
    {                                                               \
        .Instance = UART3_RX_DMA_INSTANCE,                          \
        .dma_rcc  = UART3_RX_DMA_RCC,                               \
        .dma_irq  = UART3_RX_DMA_IRQ,                               \
        .channel  = UART3_RX_DMA_CHANNEL,                           \
        .request  = UART3_RX_DMA_REQUEST,                           \
    }
#endif /* UART3_DMA_RX_CONFIG */
#endif /* BSP_UART3_RX_USING_DMA */

#if defined(BSP_UART3_TX_USING_DMA)
#ifndef UART3_DMA_TX_CONFIG
#define UART3_DMA_TX_CONFIG                                         \
    {                                                               \
        .Instance = UART3_TX_DMA_INSTANCE,                          \
        .dma_rcc  = UART3_TX_DMA_RCC,                               \
        .dma_irq  = UART3_TX_DMA_IRQ,                               \
        .channel  = UART3_TX_DMA_CHANNEL,                           \
        .request  = UART3_TX_DMA_REQUEST,                           \
    }
#endif /* UART3_DMA_TX_CONFIG */
#endif /* BSP_UART3_TX_USING_DMA */
#endif /* RT_SERIAL_USING_DMA */

#ifndef UART3_CONFIG
#define UART3_CONFIG                                                \
    {                                                               \
        .name = "uart3",                                            \
        .Instance = UART3,                                          \
        .irq_type = UART3_IRQn,                                     \
        .enable_id = EN_UART3,                                      \
        .tx_port  = UART3_TX_PORT,                                  \
        .rx_port  = UART3_RX_PORT,                                  \
        .tx_pin   = UART3_TX_PIN,                                   \
        .rx_pin   = UART3_RX_PIN,                                   \
    }
#endif /* UART3_CONFIG */
#endif /* BSP_USING_UART3 */

#ifdef __cplusplus
}
#endif

#endif /* RT_USING_SERIAL */

#endif /* __UART_CONFIG_H__ */
