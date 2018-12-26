/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
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

#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG                                       \
    {                                                      \
        .name = "uart1",                                   \
        .Instance = USART1,                                \
        .irq_type = USART1_IRQn,                           \
        .dma.Instance = DMA1_Channel3,                     \
        .dma_rcc = RCC_AHBENR_DMA1EN,                      \
        .dma_irq = DMA1_Ch2_3_DMA2_Ch1_2_IRQn,             \
    }

#define USART1_RX_DMA_ISR                        DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler
#endif /* UART1_CONFIG */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG                                       \
    {                                                      \
        .name = "uart2",                                   \
        .Instance = USART2,                                \
        .irq_type = USART2_IRQn,                           \
        .dma.Instance = DMA1_Channel3,                     \
        .dma_rcc = RCC_AHBENR_DMA1EN,                      \
        .dma_irq = DMA1_Ch2_3_DMA2_Ch1_2_IRQn,             \
    }

#define USART2_RX_DMA_ISR                        DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler
#endif /* UART2_CONFIG */
#endif /* BSP_USING_UART2 */

#endif /* __UART_CONFIG_H__ */
