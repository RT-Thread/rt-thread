/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-30     zylx         first version
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
#ifndef UART1_DMA_RX_CONFIG
#define UART1_DMA_RX_CONFIG                                            \
    {                                                               \
        .Instance = UART1_RX_DMA_INSTANCE,                          \
        .dma_rcc  = UART1_RX_DMA_RCC,                               \
        .dma_irq  = UART1_RX_DMA_IRQ,                               \
    }
#endif /* UART1_DMA_RX_CONFIG */
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
#ifndef UART2_DMA_RX_CONFIG
#define UART2_DMA_RX_CONFIG                                            \
    {                                                               \
        .Instance = UART2_RX_DMA_INSTANCE,                          \
        .dma_rcc  = UART2_RX_DMA_RCC,                               \
        .dma_irq  = UART2_RX_DMA_IRQ,                               \
    }
#endif /* UART2_DMA_RX_CONFIG */
#endif /* BSP_UART2_RX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /* __UART_CONFIG_H__ */
