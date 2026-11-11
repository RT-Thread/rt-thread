/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-30     SummerGift   first version
 * 2019-01-03     zylx         modify dma support
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
        UART1_RX_DMA_CHANNEL,                  \
        0U,                                    \
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
        UART1_TX_DMA_CHANNEL,          \
        0U,                            \
        UART1_TX_DMA_PRIORITY,         \
        UART1_TX_DMA_PREEMPT_PRIORITY, \
        UART1_TX_DMA_SUB_PRIORITY)
#endif /* UART1_DMA_TX_CONFIG */
#endif /* BSP_UART1_TX_USING_DMA */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG             \
    {                            \
        .name = "uart2",         \
        .Instance = USART2,      \
        .irq_type = USART2_IRQn, \
    }
#endif /* UART2_CONFIG */

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
        UART2_RX_DMA_CHANNEL,                  \
        0U,                                    \
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
        UART2_TX_DMA_CHANNEL,          \
        0U,                            \
        UART2_TX_DMA_PRIORITY,         \
        UART2_TX_DMA_PREEMPT_PRIORITY, \
        UART2_TX_DMA_SUB_PRIORITY)
#endif /* UART2_DMA_TX_CONFIG */
#endif /* BSP_UART2_TX_USING_DMA */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG             \
    {                            \
        .name = "uart3",         \
        .Instance = USART3,      \
        .irq_type = USART3_IRQn, \
    }
#endif /* UART3_CONFIG */

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
        UART3_RX_DMA_CHANNEL,                  \
        0U,                                    \
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
        UART3_TX_DMA_CHANNEL,          \
        0U,                            \
        UART3_TX_DMA_PRIORITY,         \
        UART3_TX_DMA_PREEMPT_PRIORITY, \
        UART3_TX_DMA_SUB_PRIORITY)
#endif /* UART3_DMA_TX_CONFIG */
#endif /* BSP_UART3_TX_USING_DMA */
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
#ifndef UART4_CONFIG
#define UART4_CONFIG            \
    {                           \
        .name = "uart4",        \
        .Instance = UART4,      \
        .irq_type = UART4_IRQn, \
    }
#endif /* UART4_CONFIG */

#if defined(BSP_UART4_RX_USING_DMA)
#ifndef UART4_RX_DMA_PRIORITY
#define UART4_RX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART4_RX_DMA_PRIORITY */

#ifndef UART4_RX_DMA_PREEMPT_PRIORITY
#define UART4_RX_DMA_PREEMPT_PRIORITY         0
#endif /* UART4_RX_DMA_PREEMPT_PRIORITY */

#ifndef UART4_RX_DMA_SUB_PRIORITY
#define UART4_RX_DMA_SUB_PRIORITY             0
#endif /* UART4_RX_DMA_SUB_PRIORITY */

#ifndef UART4_DMA_RX_CONFIG
#define UART4_DMA_RX_CONFIG                    \
    STM32_DMA_RX_BYTE_CIRCULAR_CONFIG_INIT_EX( \
        UART4_RX_DMA_INSTANCE,                 \
        UART4_RX_DMA_RCC,                      \
        UART4_RX_DMA_IRQ,                      \
        UART4_RX_DMA_CHANNEL,                  \
        0U,                                    \
        UART4_RX_DMA_PRIORITY,                 \
        UART4_RX_DMA_PREEMPT_PRIORITY,         \
        UART4_RX_DMA_SUB_PRIORITY)
#endif /* UART4_DMA_RX_CONFIG */
#endif /* BSP_UART4_RX_USING_DMA */

#if defined(BSP_UART4_TX_USING_DMA)
#ifndef UART4_TX_DMA_PRIORITY
#define UART4_TX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART4_TX_DMA_PRIORITY */

#ifndef UART4_TX_DMA_PREEMPT_PRIORITY
#define UART4_TX_DMA_PREEMPT_PRIORITY         0
#endif /* UART4_TX_DMA_PREEMPT_PRIORITY */

#ifndef UART4_TX_DMA_SUB_PRIORITY
#define UART4_TX_DMA_SUB_PRIORITY             0
#endif /* UART4_TX_DMA_SUB_PRIORITY */

#ifndef UART4_DMA_TX_CONFIG
#define UART4_DMA_TX_CONFIG            \
    STM32_DMA_TX_BYTE_CONFIG_INIT_EX(  \
        UART4_TX_DMA_INSTANCE,         \
        UART4_TX_DMA_RCC,              \
        UART4_TX_DMA_IRQ,              \
        UART4_TX_DMA_CHANNEL,          \
        0U,                            \
        UART4_TX_DMA_PRIORITY,         \
        UART4_TX_DMA_PREEMPT_PRIORITY, \
        UART4_TX_DMA_SUB_PRIORITY)
#endif /* UART4_DMA_TX_CONFIG */
#endif /* BSP_UART4_TX_USING_DMA */
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
#ifndef UART5_CONFIG
#define UART5_CONFIG            \
    {                           \
        .name = "uart5",        \
        .Instance = UART5,      \
        .irq_type = UART5_IRQn, \
    }
#endif /* UART5_CONFIG */

#if defined(BSP_UART5_RX_USING_DMA)
#ifndef UART5_RX_DMA_PRIORITY
#define UART5_RX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART5_RX_DMA_PRIORITY */

#ifndef UART5_RX_DMA_PREEMPT_PRIORITY
#define UART5_RX_DMA_PREEMPT_PRIORITY         0
#endif /* UART5_RX_DMA_PREEMPT_PRIORITY */

#ifndef UART5_RX_DMA_SUB_PRIORITY
#define UART5_RX_DMA_SUB_PRIORITY             0
#endif /* UART5_RX_DMA_SUB_PRIORITY */

#ifndef UART5_DMA_RX_CONFIG
#define UART5_DMA_RX_CONFIG                    \
    STM32_DMA_RX_BYTE_CIRCULAR_CONFIG_INIT_EX( \
        UART5_RX_DMA_INSTANCE,                 \
        UART5_RX_DMA_RCC,                      \
        UART5_RX_DMA_IRQ,                      \
        UART5_RX_DMA_CHANNEL,                  \
        0U,                                    \
        UART5_RX_DMA_PRIORITY,                 \
        UART5_RX_DMA_PREEMPT_PRIORITY,         \
        UART5_RX_DMA_SUB_PRIORITY)
#endif /* UART5_DMA_RX_CONFIG */
#endif /* BSP_UART5_RX_USING_DMA */

#if defined(BSP_UART5_TX_USING_DMA)
#ifndef UART5_TX_DMA_PRIORITY
#define UART5_TX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART5_TX_DMA_PRIORITY */

#ifndef UART5_TX_DMA_PREEMPT_PRIORITY
#define UART5_TX_DMA_PREEMPT_PRIORITY         0
#endif /* UART5_TX_DMA_PREEMPT_PRIORITY */

#ifndef UART5_TX_DMA_SUB_PRIORITY
#define UART5_TX_DMA_SUB_PRIORITY             0
#endif /* UART5_TX_DMA_SUB_PRIORITY */

#ifndef UART5_DMA_TX_CONFIG
#define UART5_DMA_TX_CONFIG            \
    STM32_DMA_TX_BYTE_CONFIG_INIT_EX(  \
        UART5_TX_DMA_INSTANCE,         \
        UART5_TX_DMA_RCC,              \
        UART5_TX_DMA_IRQ,              \
        UART5_TX_DMA_CHANNEL,          \
        0U,                            \
        UART5_TX_DMA_PRIORITY,         \
        UART5_TX_DMA_PREEMPT_PRIORITY, \
        UART5_TX_DMA_SUB_PRIORITY)
#endif /* UART5_DMA_TX_CONFIG */
#endif /* BSP_UART5_TX_USING_DMA */
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
#ifndef UART6_CONFIG
#define UART6_CONFIG             \
    {                            \
        .name = "uart6",         \
        .Instance = USART6,      \
        .irq_type = USART6_IRQn, \
    }
#endif /* UART6_CONFIG */

#if defined(BSP_UART6_RX_USING_DMA)
#ifndef UART6_RX_DMA_PRIORITY
#define UART6_RX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART6_RX_DMA_PRIORITY */

#ifndef UART6_RX_DMA_PREEMPT_PRIORITY
#define UART6_RX_DMA_PREEMPT_PRIORITY         0
#endif /* UART6_RX_DMA_PREEMPT_PRIORITY */

#ifndef UART6_RX_DMA_SUB_PRIORITY
#define UART6_RX_DMA_SUB_PRIORITY             0
#endif /* UART6_RX_DMA_SUB_PRIORITY */

#ifndef UART6_DMA_RX_CONFIG
#define UART6_DMA_RX_CONFIG                    \
    STM32_DMA_RX_BYTE_CIRCULAR_CONFIG_INIT_EX( \
        UART6_RX_DMA_INSTANCE,                 \
        UART6_RX_DMA_RCC,                      \
        UART6_RX_DMA_IRQ,                      \
        UART6_RX_DMA_CHANNEL,                  \
        0U,                                    \
        UART6_RX_DMA_PRIORITY,                 \
        UART6_RX_DMA_PREEMPT_PRIORITY,         \
        UART6_RX_DMA_SUB_PRIORITY)
#endif /* UART6_DMA_RX_CONFIG */
#endif /* BSP_UART6_RX_USING_DMA */

#if defined(BSP_UART6_TX_USING_DMA)
#ifndef UART6_TX_DMA_PRIORITY
#define UART6_TX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART6_TX_DMA_PRIORITY */

#ifndef UART6_TX_DMA_PREEMPT_PRIORITY
#define UART6_TX_DMA_PREEMPT_PRIORITY         0
#endif /* UART6_TX_DMA_PREEMPT_PRIORITY */

#ifndef UART6_TX_DMA_SUB_PRIORITY
#define UART6_TX_DMA_SUB_PRIORITY             0
#endif /* UART6_TX_DMA_SUB_PRIORITY */

#ifndef UART6_DMA_TX_CONFIG
#define UART6_DMA_TX_CONFIG            \
    STM32_DMA_TX_BYTE_CONFIG_INIT_EX(  \
        UART6_TX_DMA_INSTANCE,         \
        UART6_TX_DMA_RCC,              \
        UART6_TX_DMA_IRQ,              \
        UART6_TX_DMA_CHANNEL,          \
        0U,                            \
        UART6_TX_DMA_PRIORITY,         \
        UART6_TX_DMA_PREEMPT_PRIORITY, \
        UART6_TX_DMA_SUB_PRIORITY)
#endif /* UART6_DMA_TX_CONFIG */
#endif /* BSP_UART6_TX_USING_DMA */
#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
#ifndef UART7_CONFIG
#define UART7_CONFIG            \
    {                           \
        .name = "uart7",        \
        .Instance = UART7,      \
        .irq_type = UART7_IRQn, \
    }
#endif /* UART7_CONFIG */

#if defined(BSP_UART7_RX_USING_DMA)
#ifndef UART7_RX_DMA_PRIORITY
#define UART7_RX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART7_RX_DMA_PRIORITY */

#ifndef UART7_RX_DMA_PREEMPT_PRIORITY
#define UART7_RX_DMA_PREEMPT_PRIORITY         0
#endif /* UART7_RX_DMA_PREEMPT_PRIORITY */

#ifndef UART7_RX_DMA_SUB_PRIORITY
#define UART7_RX_DMA_SUB_PRIORITY             0
#endif /* UART7_RX_DMA_SUB_PRIORITY */

#ifndef UART7_DMA_RX_CONFIG
#define UART7_DMA_RX_CONFIG                    \
    STM32_DMA_RX_BYTE_CIRCULAR_CONFIG_INIT_EX( \
        UART7_RX_DMA_INSTANCE,                 \
        UART7_RX_DMA_RCC,                      \
        UART7_RX_DMA_IRQ,                      \
        UART7_RX_DMA_CHANNEL,                  \
        0U,                                    \
        UART7_RX_DMA_PRIORITY,                 \
        UART7_RX_DMA_PREEMPT_PRIORITY,         \
        UART7_RX_DMA_SUB_PRIORITY)
#endif /* UART7_DMA_RX_CONFIG */
#endif /* BSP_UART7_RX_USING_DMA */

#if defined(BSP_UART7_TX_USING_DMA)
#ifndef UART7_TX_DMA_PRIORITY
#define UART7_TX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART7_TX_DMA_PRIORITY */

#ifndef UART7_TX_DMA_PREEMPT_PRIORITY
#define UART7_TX_DMA_PREEMPT_PRIORITY         0
#endif /* UART7_TX_DMA_PREEMPT_PRIORITY */

#ifndef UART7_TX_DMA_SUB_PRIORITY
#define UART7_TX_DMA_SUB_PRIORITY             0
#endif /* UART7_TX_DMA_SUB_PRIORITY */

#ifndef UART7_DMA_TX_CONFIG
#define UART7_DMA_TX_CONFIG            \
    STM32_DMA_TX_BYTE_CONFIG_INIT_EX(  \
        UART7_TX_DMA_INSTANCE,         \
        UART7_TX_DMA_RCC,              \
        UART7_TX_DMA_IRQ,              \
        UART7_TX_DMA_CHANNEL,          \
        0U,                            \
        UART7_TX_DMA_PRIORITY,         \
        UART7_TX_DMA_PREEMPT_PRIORITY, \
        UART7_TX_DMA_SUB_PRIORITY)
#endif /* UART7_DMA_TX_CONFIG */
#endif /* BSP_UART7_TX_USING_DMA */
#endif /* BSP_USING_UART7 */

#if defined(BSP_USING_UART8)
#ifndef UART8_CONFIG
#define UART8_CONFIG            \
    {                           \
        .name = "uart8",        \
        .Instance = UART8,      \
        .irq_type = UART8_IRQn, \
    }
#endif /* UART8_CONFIG */

#if defined(BSP_UART8_RX_USING_DMA)
#ifndef UART8_RX_DMA_PRIORITY
#define UART8_RX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART8_RX_DMA_PRIORITY */

#ifndef UART8_RX_DMA_PREEMPT_PRIORITY
#define UART8_RX_DMA_PREEMPT_PRIORITY         0
#endif /* UART8_RX_DMA_PREEMPT_PRIORITY */

#ifndef UART8_RX_DMA_SUB_PRIORITY
#define UART8_RX_DMA_SUB_PRIORITY             0
#endif /* UART8_RX_DMA_SUB_PRIORITY */

#ifndef UART8_DMA_RX_CONFIG
#define UART8_DMA_RX_CONFIG                    \
    STM32_DMA_RX_BYTE_CIRCULAR_CONFIG_INIT_EX( \
        UART8_RX_DMA_INSTANCE,                 \
        UART8_RX_DMA_RCC,                      \
        UART8_RX_DMA_IRQ,                      \
        UART8_RX_DMA_CHANNEL,                  \
        0U,                                    \
        UART8_RX_DMA_PRIORITY,                 \
        UART8_RX_DMA_PREEMPT_PRIORITY,         \
        UART8_RX_DMA_SUB_PRIORITY)
#endif /* UART8_DMA_RX_CONFIG */
#endif /* BSP_UART8_RX_USING_DMA */

#if defined(BSP_UART8_TX_USING_DMA)
#ifndef UART8_TX_DMA_PRIORITY
#define UART8_TX_DMA_PRIORITY                 DMA_PRIORITY_MEDIUM
#endif /* UART8_TX_DMA_PRIORITY */

#ifndef UART8_TX_DMA_PREEMPT_PRIORITY
#define UART8_TX_DMA_PREEMPT_PRIORITY         0
#endif /* UART8_TX_DMA_PREEMPT_PRIORITY */

#ifndef UART8_TX_DMA_SUB_PRIORITY
#define UART8_TX_DMA_SUB_PRIORITY             0
#endif /* UART8_TX_DMA_SUB_PRIORITY */

#ifndef UART8_DMA_TX_CONFIG
#define UART8_DMA_TX_CONFIG            \
    STM32_DMA_TX_BYTE_CONFIG_INIT_EX(  \
        UART8_TX_DMA_INSTANCE,         \
        UART8_TX_DMA_RCC,              \
        UART8_TX_DMA_IRQ,              \
        UART8_TX_DMA_CHANNEL,          \
        0U,                            \
        UART8_TX_DMA_PRIORITY,         \
        UART8_TX_DMA_PREEMPT_PRIORITY, \
        UART8_TX_DMA_SUB_PRIORITY)
#endif /* UART8_DMA_TX_CONFIG */
#endif /* BSP_UART8_TX_USING_DMA */
#endif /* BSP_USING_UART8 */

#ifdef __cplusplus
}
#endif

#endif
