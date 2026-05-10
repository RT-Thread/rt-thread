/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-30     SummerGift   first version
 * 2019-01-05     zylx         modify dma support
 * 2020-05-02     whj4674672   support stm32h7 uart dma
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
        UART1_RX_DMA_REQUEST,                  \
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

#if defined(BSP_USING_UART4)
#ifndef UART4_CONFIG
#define UART4_CONFIG            \
    {                           \
        .name = "uart4",        \
        .Instance = UART4,      \
        .irq_type = UART4_IRQn, \
    }
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
#define UART5_CONFIG            \
    {                           \
        .name = "uart5",        \
        .Instance = UART5,      \
        .irq_type = UART5_IRQn, \
    }
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

#if defined(BSP_USING_LPUART1)
#ifndef LPUART1_CONFIG
#define LPUART1_CONFIG            \
    {                             \
        .name = "hlpuart1",       \
        .Instance = LPUART1,      \
        .irq_type = LPUART1_IRQn, \
    }
#endif /* LPUART1_CONFIG */
#endif /* BSP_USING_LPUART1 */

#ifdef __cplusplus
}
#endif

#endif
