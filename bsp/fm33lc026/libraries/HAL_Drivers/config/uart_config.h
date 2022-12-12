/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-27     Jiao         first version
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_UART0)
#ifndef UART0_CONFIG
#define UART0_CONFIG                                                \
    {                                                               \
        .name = "uart0",                                            \
        .InitTypeDef = UART0,                                       \
        .irq_type = UART0_IRQn,                                    \
        .clockSrc = FL_RCC_UART0_CLK_SOURCE_APB1CLK,                \
    }
#endif /* UART0_CONFIG */
#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG                                                \
    {                                                               \
        .name = "uart1",                                            \
        .InitTypeDef = UART1,                                       \
        .irq_type = UART1_IRQn,                                    \
        .clockSrc = FL_RCC_UART1_CLK_SOURCE_APB1CLK,               \
    }
#endif /* UART1_CONFIG */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART4)
#ifndef UART4_CONFIG
#define UART4_CONFIG                                                \
    {                                                               \
        .name = "uart4",                                            \
        .InitTypeDef = UART4,                                         \
        .irq_type = UART4_IRQn,                                    \
    }
#endif /* UART4_CONFIG */
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
#ifndef UART5_CONFIG
#define UART5_CONFIG                                                \
    {                                                               \
        .name = "uart5",                                            \
        .Instance = UART5,                                         \
        .irq_type = UART5_IRQn,                                    \
    }
#endif /* UART5_CONFIG */
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_LPUART0)
#ifndef LPUART0_CONFIG
#define LPUART0_CONFIG                                                \
    {                                                               \
        .name = "lpuart0",                                            \
        .Instance = LPUART0,                                         \
        .irq_type = LPUART0_IRQn,                                    \
    }
#endif /* LPUART0_CONFIG */
#endif /* BSP_USING_LPUART0 */

#if defined(BSP_USING_LPUART1)
#ifndef LPUART1_CONFIG
#define LPUART1_CONFIG                                                \
    {                                                               \
        .name = "lpuart1",                                            \
        .Instance = LPUART1,                                         \
        .irq_type = LPUART1_IRQn,                                    \
    }
#endif /* LPUART0_CONFIG */
#endif /* BSP_USING_LPUART0 */

#ifdef __cplusplus
}
#endif

#endif /* __UART_CONFIG_H__ */
