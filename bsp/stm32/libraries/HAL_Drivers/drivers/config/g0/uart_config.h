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

#if defined(BSP_USING_LPUART1)
#ifndef LPUART1_CONFIG
#if defined(STM32G071xx) || defined(STM32G081xx)
#define LPUART1_CONFIG                     \
    {                                      \
        .name = "lpuart1",                 \
        .Instance = LPUART1,               \
        .irq_type = USART3_4_LPUART1_IRQn, \
    }
#elif defined(STM32G0B1xx) || defined(STM32G0C1xx)
#define LPUART1_CONFIG                         \
    {                                          \
        .name = "lpuart1",                     \
        .Instance = LPUART1,                   \
        .irq_type = USART3_4_5_6_LPUART1_IRQn, \
    }
#endif /* defined(STM32G071xx) || defined(STM32G081xx) */
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
#if defined(STM32G0B1xx) || defined(STM32G0C1xx)
#define UART2_CONFIG                      \
    {                                     \
        .name = "uart2",                  \
        .Instance = USART2,               \
        .irq_type = USART2_LPUART2_IRQn , \
    }
#else
#define UART2_CONFIG             \
    {                            \
        .name = "uart2",         \
        .Instance = USART2,      \
        .irq_type = USART2_IRQn, \
    }
#endif /* defined(STM32G0B1xx) || defined(STM32G0C1xx) */
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
#if defined(STM32G0B1xx) || defined(STM32G0C1xx)
#define UART3_CONFIG                           \
    {                                          \
        .name = "uart3",                       \
        .Instance = USART3,                    \
        .irq_type = USART3_4_5_6_LPUART1_IRQn, \
    }
#elif defined(STM32G070xx)
#define UART3_CONFIG               \
    {                              \
        .name = "uart3",           \
        .Instance = USART3,        \
        .irq_type = USART3_4_IRQn, \
    }
#elif defined(STM32G071xx) || defined(STM32G081xx)
#define UART3_CONFIG                       \
    {                                      \
        .name = "uart3",                   \
        .Instance = USART3,                \
        .irq_type = USART3_4_LPUART1_IRQn, \
    }
#elif defined(STM32G0B0xx)
#define UART3_CONFIG                   \
    {                                  \
        .name = "uart3",               \
        .Instance = USART3,            \
        .irq_type = USART3_4_5_6_IRQn, \
    }
#else
#define UART3_CONFIG             \
    {                            \
        .name = "uart3",         \
        .Instance = USART3,      \
        .irq_type = USART3_IRQn, \
    }
#endif /* defined(STM32G0B1xx) || defined(STM32G0C1xx) */
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

#if defined(BSP_USING_UART4)
#ifndef UART4_CONFIG
#if defined(STM32G0B1xx) || defined(STM32G0C1xx)
#define UART4_CONFIG                           \
    {                                          \
        .name = "uart4",                       \
        .Instance = USART4,                    \
        .irq_type = USART3_4_5_6_LPUART1_IRQn, \
    }
#elif defined(STM32G070xx)
#define UART4_CONFIG               \
    {                              \
        .name = "uart4",           \
        .Instance = USART4,        \
        .irq_type = USART3_4_IRQn, \
    }
#elif defined(STM32G071xx) || defined(STM32G081xx)
#define UART4_CONFIG                       \
    {                                      \
        .name = "uart4",                   \
        .Instance = USART4,                \
        .irq_type = USART3_4_LPUART1_IRQn, \
    }
#elif defined(STM32G0B0xx)
#define UART4_CONFIG                   \
    {                                  \
        .name = "uart4",               \
        .Instance = USART4,            \
        .irq_type = USART3_4_5_6_IRQn, \
    }
#else
#define UART4_CONFIG             \
    {                            \
        .name = "uart4",         \
        .Instance = USART4,      \
        .irq_type = USART4_IRQn, \
    }
#endif /* defined(STM32G0B1xx) || defined(STM32G0C1xx) */
#endif /* UART4_CONFIG */
#endif /* BSP_USING_UART4 */

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
        0U,                                    \
        UART4_RX_DMA_REQUEST,                  \
        UART4_RX_DMA_PRIORITY,                 \
        UART4_RX_DMA_PREEMPT_PRIORITY,         \
        UART4_RX_DMA_SUB_PRIORITY)
#endif /* UART4_DMA_RX_CONFIG */
#endif /* BSP_UART4_RX_USING_DMA */

#if defined(BSP_USING_UART5)
#ifndef UART5_CONFIG
#if defined(STM32G0B1xx) || defined(STM32G0C1xx)
#define UART5_CONFIG                           \
    {                                          \
        .name = "uart5",                       \
        .Instance = UART5,                     \
        .irq_type = USART3_4_5_6_LPUART1_IRQn, \
    }
#elif defined(STM32G0B0xx)
#define UART5_CONFIG                   \
    {                                  \
        .name = "uart5",               \
        .Instance = UART5,             \
        .irq_type = USART3_4_5_6_IRQn, \
    }
#else
#define UART5_CONFIG            \
    {                           \
        .name = "uart5",        \
        .Instance = UART5,      \
        .irq_type = UART5_IRQn, \
    }
#endif /* defined(STM32G0B1xx) || defined(STM32G0C1xx) */
#endif /* UART5_CONFIG */
#endif /* BSP_USING_UART5 */

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
        0U,                                    \
        UART5_RX_DMA_REQUEST,                  \
        UART5_RX_DMA_PRIORITY,                 \
        UART5_RX_DMA_PREEMPT_PRIORITY,         \
        UART5_RX_DMA_SUB_PRIORITY)
#endif /* UART5_DMA_RX_CONFIG */
#endif /* BSP_UART5_RX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /* __UART_CONFIG_H__ */
