/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *
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
        .Instance = UART1,                                         \
        .rx_irq_type = UART1_RX_IRQn,                                    \
        .tx_irq_type = UART1_TX_IRQn,                                    \
        .irq_handler = UART1_IRQHandler,                                     \
    }
#endif /* UART1_CONFIG */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG                                                \
    {                                                               \
        .name = "uart2",                                            \
        .Instance = UART2,                                         \
        .rx_irq_type = UART2_RX_IRQn,                                    \
        .tx_irq_type = UART2_TX_IRQn,                                    \
        .irq_handler = UART2_IRQHandler,                          \
    }
#endif /* UART2_CONFIG */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG                                                \
    {                                                               \
        .name = "uart3",                                            \
        .Instance = UART3,                                         \
        .rx_irq_type = UART3_RX_IRQn,                                    \
        .tx_irq_type = UART3_TX_IRQn,                                    \
        .irq_handler = UART3_IRQHandler,                                     \
    }
#endif /* UART3_CONFIG */
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
#ifndef UART4_CONFIG
#define UART4_CONFIG                                                \
    {                                                               \
        .name = "uart4",                                            \
        .Instance = UART4,                                         \
        .rx_irq_type = UART4_RX_IRQn,                                    \
        .tx_irq_type = UART4_TX_IRQn,                                    \
        .irq_handler = UART4_IRQHandler,                                     \
    }
#endif /* UART4_CONFIG */
#endif /* BSP_USING_UART4 */

#ifdef __cplusplus
}
#endif

#endif

