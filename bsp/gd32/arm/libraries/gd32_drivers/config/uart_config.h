/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-10-09     WangShun     optimize the serial driver
 * 2025-11-13     kurisaw      general GD driver adaptation
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_UART0)
#ifndef UART0_CONFIG
#define UART0_CONFIG                                               \
    {                                                              \
        .uart_periph = USART0,                                     \
        .irqn = USART0_IRQn,                                       \
        .per_clk = RCU_USART0,                                     \
        .tx_pin_name = BSP_UART0_TX_PIN,                           \
        .rx_pin_name = BSP_UART0_RX_PIN,                           \
        .alternate = BSP_UART0_AFIO,                               \
        .serial = &serial0,                                        \
        .device_name = "uart0",                                    \
    }
#endif /* UART0_CONFIG */
#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG                                               \
    {                                                              \
        .uart_periph = USART1,                                     \
        .irqn = USART1_IRQn,                                       \
        .per_clk = RCU_USART1,                                     \
        .tx_pin_name = BSP_UART1_TX_PIN,                           \
        .rx_pin_name = BSP_UART1_RX_PIN,                           \
        .alternate = BSP_UART1_AFIO,                               \
        .serial = &serial1,                                        \
        .device_name = "uart1",                                    \
    }
#endif /* UART1_CONFIG */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG                                               \
    {                                                              \
        .uart_periph = USART2,                                     \
        .irqn = USART2_IRQn,                                       \
        .per_clk = RCU_USART2,                                     \
        .tx_pin_name = BSP_UART2_TX_PIN,                           \
        .rx_pin_name = BSP_UART2_RX_PIN,                           \
        .alternate = BSP_UART2_AFIO,                               \
        .serial = &serial2,                                        \
        .device_name = "uart2",                                    \
    }
#endif /* UART2_CONFIG */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG                                               \
    {                                                              \
        .uart_periph = UART3,                                      \
        .irqn = UART3_IRQn,                                        \
        .per_clk = RCU_UART3,                                      \
        .tx_pin_name = BSP_UART3_TX_PIN,                           \
        .rx_pin_name = BSP_UART3_RX_PIN,                           \
        .alternate = BSP_UART3_AFIO,                               \
        .serial = &serial3,                                        \
        .device_name = "uart3",                                    \
    }
#endif /* UART3_CONFIG */
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
#ifndef UART4_CONFIG
#define UART4_CONFIG                                               \
    {                                                              \
        .uart_periph = UART4,                                      \
        .irqn = UART4_IRQn,                                        \
        .per_clk = RCU_UART4,                                      \
        .tx_pin_name = BSP_UART4_TX_PIN,                           \
        .rx_pin_name = BSP_UART4_RX_PIN,                           \
        .alternate = BSP_UART4_AFIO,                               \
        .serial = &serial4,                                        \
        .device_name = "uart4",                                    \
    }
#endif /* UART4_CONFIG */
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
#ifndef UART5_CONFIG
#define UART5_CONFIG                                               \
    {                                                              \
        .uart_periph = USART5,                                     \
        .irqn = USART5_IRQn,                                       \
        .per_clk = RCU_USART5,                                     \
        .tx_pin_name = BSP_UART5_TX_PIN,                           \
        .rx_pin_name = BSP_UART5_RX_PIN,                           \
        .alternate = BSP_UART5_AFIO,                               \
        .serial = &serial5,                                        \
        .device_name = "uart5",                                    \
    }
#endif /* UART5_CONFIG */
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
#ifndef UART6_CONFIG
#define UART6_CONFIG                                               \
    {                                                              \
        .uart_periph = UART6,                                      \
        .irqn = UART6_IRQn,                                        \
        .per_clk = RCU_UART6,                                      \
        .tx_pin_name = BSP_UART6_TX_PIN,                           \
        .rx_pin_name = BSP_UART6_RX_PIN,                           \
        .alternate = BSP_UART6_AFIO,                               \
        .serial = &serial6,                                        \
        .device_name = "uart6",                                    \
    }
#endif /* UART6_CONFIG */
#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
#ifndef UART7_CONFIG
#define UART7_CONFIG                                               \
    {                                                              \
        .uart_periph = UART7,                                      \
        .irqn = UART7_IRQn,                                        \
        .per_clk = RCU_UART7,                                      \
        .tx_pin_name = BSP_UART7_TX_PIN,                           \
        .rx_pin_name = BSP_UART7_RX_PIN,                           \
        .alternate = BSP_UART7_AFIO,                               \
        .serial = &serial7,                                        \
        .device_name = "uart7",                                    \
    }
#endif /* UART7_CONFIG */
#endif /* BSP_USING_UART7 */

#ifdef __cplusplus
}
#endif

#endif /* __UART_CONFIG_H__ */

