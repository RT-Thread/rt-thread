/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-30     zylx         first version
 * 2026-04-13     wdfk-prog    Unify DMA config descriptors
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG             \
    {                            \
        .name = "uart1",         \
        .Instance = USART1,      \
        .irq_type = USART1_IRQn, \
    }
#endif /* UART1_CONFIG */
#endif /* BSP_USING_UART1 */

#if defined(BSP_UART1_RX_USING_DMA)
#ifndef UART1_RX_DMA_PRIORITY
#define UART1_RX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART1_RX_DMA_PRIORITY */

#ifndef UART1_RX_DMA_PREEMPT_PRIORITY
#define UART1_RX_DMA_PREEMPT_PRIORITY         0
#endif /* UART1_RX_DMA_PREEMPT_PRIORITY */

#ifndef UART1_RX_DMA_SUB_PRIORITY
#define UART1_RX_DMA_SUB_PRIORITY             0
#endif /* UART1_RX_DMA_SUB_PRIORITY */

#ifndef UART1_DMA_RX_CONFIG
#define UART1_DMA_RX_CONFIG                    \
    STM32_DMA_RX_BYTE_CIRCULAR_CONFIG_INIT_EX( \
        UART1_RX_DMA_INSTANCE,                 \
        UART1_RX_DMA_RCC,                      \
        UART1_RX_DMA_IRQ,                      \
        0U,                                    \
        0U,                                    \
        UART1_RX_DMA_PRIORITY,                 \
        UART1_RX_DMA_PREEMPT_PRIORITY,         \
        UART1_RX_DMA_SUB_PRIORITY)
#endif /* UART1_DMA_RX_CONFIG */
#endif /* BSP_UART1_RX_USING_DMA */

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG             \
    {                            \
        .name = "uart2",         \
        .Instance = USART2,      \
        .irq_type = USART2_IRQn, \
    }
#endif /* UART2_CONFIG */
#endif /* BSP_USING_UART2 */

#if defined(BSP_UART2_RX_USING_DMA)
#ifndef UART2_RX_DMA_PRIORITY
#define UART2_RX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART2_RX_DMA_PRIORITY */

#ifndef UART2_RX_DMA_PREEMPT_PRIORITY
#define UART2_RX_DMA_PREEMPT_PRIORITY         0
#endif /* UART2_RX_DMA_PREEMPT_PRIORITY */

#ifndef UART2_RX_DMA_SUB_PRIORITY
#define UART2_RX_DMA_SUB_PRIORITY             0
#endif /* UART2_RX_DMA_SUB_PRIORITY */

#ifndef UART2_DMA_RX_CONFIG
#define UART2_DMA_RX_CONFIG                    \
    STM32_DMA_RX_BYTE_CIRCULAR_CONFIG_INIT_EX( \
        UART2_RX_DMA_INSTANCE,                 \
        UART2_RX_DMA_RCC,                      \
        UART2_RX_DMA_IRQ,                      \
        0U,                                    \
        0U,                                    \
        UART2_RX_DMA_PRIORITY,                 \
        UART2_RX_DMA_PREEMPT_PRIORITY,         \
        UART2_RX_DMA_SUB_PRIORITY)
#endif /* UART2_DMA_RX_CONFIG */
#endif /* BSP_UART2_RX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /* __UART_CONFIG_H__ */
