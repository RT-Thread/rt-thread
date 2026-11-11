/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 * 2026-04-13     wdfk-prog    Unify DMA config descriptors
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_LPUART1)
#ifndef LPUART1_CONFIG
#define LPUART1_CONFIG            \
    {                             \
        .name = "lpuart1",        \
        .Instance = LPUART1,      \
        .irq_type = LPUART1_IRQn, \
    }
#endif /* LPUART1_CONFIG */
#if defined(BSP_LPUART1_RX_USING_DMA)
#ifndef LPUART1_DMA_PRIORITY
#define LPUART1_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* LPUART1_DMA_PRIORITY */

#ifndef LPUART1_DMA_PREEMPT_PRIORITY
#define LPUART1_DMA_PREEMPT_PRIORITY         0
#endif /* LPUART1_DMA_PREEMPT_PRIORITY */

#ifndef LPUART1_DMA_SUB_PRIORITY
#define LPUART1_DMA_SUB_PRIORITY             0
#endif /* LPUART1_DMA_SUB_PRIORITY */

#ifndef LPUART1_DMA_CONFIG
#define LPUART1_DMA_CONFIG                     \
    STM32_DMA_RX_BYTE_CIRCULAR_CONFIG_INIT_EX( \
        LPUART1_RX_DMA_INSTANCE,               \
        LPUART1_RX_DMA_RCC,                    \
        LPUART1_RX_DMA_IRQ,                    \
        0U,                                    \
        LPUART1_RX_DMA_REQUEST,                \
        LPUART1_DMA_PRIORITY,                  \
        LPUART1_DMA_PREEMPT_PRIORITY,          \
        LPUART1_DMA_SUB_PRIORITY)
#endif /* LPUART1_DMA_CONFIG */
#endif /* BSP_LPUART1_RX_USING_DMA */
#endif /* BSP_USING_LPUART1 */

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
        UART1_RX_DMA_REQUEST,                  \
        UART1_RX_DMA_PRIORITY,                 \
        UART1_RX_DMA_PREEMPT_PRIORITY,         \
        UART1_RX_DMA_SUB_PRIORITY)
#endif /* UART1_DMA_RX_CONFIG */
#endif /* BSP_UART1_RX_USING_DMA */

#if defined(BSP_UART1_TX_USING_DMA)
#ifndef UART1_TX_DMA_PRIORITY
#define UART1_TX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART1_TX_DMA_PRIORITY */

#ifndef UART1_TX_DMA_PREEMPT_PRIORITY
#define UART1_TX_DMA_PREEMPT_PRIORITY         0
#endif /* UART1_TX_DMA_PREEMPT_PRIORITY */

#ifndef UART1_TX_DMA_SUB_PRIORITY
#define UART1_TX_DMA_SUB_PRIORITY             0
#endif /* UART1_TX_DMA_SUB_PRIORITY */

#ifndef UART1_DMA_TX_CONFIG
#define UART1_DMA_TX_CONFIG            \
    STM32_DMA_TX_BYTE_CONFIG_INIT_EX(  \
        UART1_TX_DMA_INSTANCE,         \
        UART1_TX_DMA_RCC,              \
        UART1_TX_DMA_IRQ,              \
        0U,                            \
        UART1_TX_DMA_REQUEST,          \
        UART1_TX_DMA_PRIORITY,         \
        UART1_TX_DMA_PREEMPT_PRIORITY, \
        UART1_TX_DMA_SUB_PRIORITY)
#endif /* UART1_DMA_TX_CONFIG */
#endif /* BSP_UART1_TX_USING_DMA */

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
        UART2_RX_DMA_REQUEST,                  \
        UART2_RX_DMA_PRIORITY,                 \
        UART2_RX_DMA_PREEMPT_PRIORITY,         \
        UART2_RX_DMA_SUB_PRIORITY)
#endif /* UART2_DMA_RX_CONFIG */
#endif /* BSP_UART2_RX_USING_DMA */

#if defined(BSP_UART2_TX_USING_DMA)
#ifndef UART2_TX_DMA_PRIORITY
#define UART2_TX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART2_TX_DMA_PRIORITY */

#ifndef UART2_TX_DMA_PREEMPT_PRIORITY
#define UART2_TX_DMA_PREEMPT_PRIORITY         0
#endif /* UART2_TX_DMA_PREEMPT_PRIORITY */

#ifndef UART2_TX_DMA_SUB_PRIORITY
#define UART2_TX_DMA_SUB_PRIORITY             0
#endif /* UART2_TX_DMA_SUB_PRIORITY */

#ifndef UART2_DMA_TX_CONFIG
#define UART2_DMA_TX_CONFIG            \
    STM32_DMA_TX_BYTE_CONFIG_INIT_EX(  \
        UART2_TX_DMA_INSTANCE,         \
        UART2_TX_DMA_RCC,              \
        UART2_TX_DMA_IRQ,              \
        0U,                            \
        UART2_TX_DMA_REQUEST,          \
        UART2_TX_DMA_PRIORITY,         \
        UART2_TX_DMA_PREEMPT_PRIORITY, \
        UART2_TX_DMA_SUB_PRIORITY)
#endif /* UART2_DMA_TX_CONFIG */
#endif /* BSP_UART2_TX_USING_DMA */

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG             \
    {                            \
        .name = "uart3",         \
        .Instance = USART3,      \
        .irq_type = USART3_IRQn, \
    }
#endif /* UART3_CONFIG */
#endif /* BSP_USING_UART3 */

#if defined(BSP_UART3_RX_USING_DMA)
#ifndef UART3_RX_DMA_PRIORITY
#define UART3_RX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART3_RX_DMA_PRIORITY */

#ifndef UART3_RX_DMA_PREEMPT_PRIORITY
#define UART3_RX_DMA_PREEMPT_PRIORITY         0
#endif /* UART3_RX_DMA_PREEMPT_PRIORITY */

#ifndef UART3_RX_DMA_SUB_PRIORITY
#define UART3_RX_DMA_SUB_PRIORITY             0
#endif /* UART3_RX_DMA_SUB_PRIORITY */

#ifndef UART3_DMA_RX_CONFIG
#define UART3_DMA_RX_CONFIG                    \
    STM32_DMA_RX_BYTE_CIRCULAR_CONFIG_INIT_EX( \
        UART3_RX_DMA_INSTANCE,                 \
        UART3_RX_DMA_RCC,                      \
        UART3_RX_DMA_IRQ,                      \
        0U,                                    \
        UART3_RX_DMA_REQUEST,                  \
        UART3_RX_DMA_PRIORITY,                 \
        UART3_RX_DMA_PREEMPT_PRIORITY,         \
        UART3_RX_DMA_SUB_PRIORITY)
#endif /* UART3_DMA_RX_CONFIG */
#endif /* BSP_UART3_RX_USING_DMA */

#if defined(BSP_UART3_TX_USING_DMA)
#ifndef UART3_TX_DMA_PRIORITY
#define UART3_TX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART3_TX_DMA_PRIORITY */

#ifndef UART3_TX_DMA_PREEMPT_PRIORITY
#define UART3_TX_DMA_PREEMPT_PRIORITY         0
#endif /* UART3_TX_DMA_PREEMPT_PRIORITY */

#ifndef UART3_TX_DMA_SUB_PRIORITY
#define UART3_TX_DMA_SUB_PRIORITY             0
#endif /* UART3_TX_DMA_SUB_PRIORITY */

#ifndef UART3_DMA_TX_CONFIG
#define UART3_DMA_TX_CONFIG            \
    STM32_DMA_TX_BYTE_CONFIG_INIT_EX(  \
        UART3_TX_DMA_INSTANCE,         \
        UART3_TX_DMA_RCC,              \
        UART3_TX_DMA_IRQ,              \
        0U,                            \
        UART3_TX_DMA_REQUEST,          \
        UART3_TX_DMA_PRIORITY,         \
        UART3_TX_DMA_PREEMPT_PRIORITY, \
        UART3_TX_DMA_SUB_PRIORITY)
#endif /* UART3_DMA_TX_CONFIG */
#endif /* BSP_UART3_TX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif
