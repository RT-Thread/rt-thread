/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-08     Rbb666       first version
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>
#include "board.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef BSP_USING_UART0
    /* UART0 device driver structure */
    cy_stc_sysint_t UART0_SCB_IRQ_cfg =
        {
            .intrSrc = (IRQn_Type)scb_0_interrupt_IRQn,
            .intrPriority = (7u),
    };
#endif
#ifdef BSP_USING_UART1
    /* UART1 device driver structure */
    cy_stc_sysint_t UART1_SCB_IRQ_cfg =
        {
            .intrSrc = (IRQn_Type)scb_1_interrupt_IRQn,
            .intrPriority = (7u),
    };
#endif
#ifdef BSP_USING_UART2
    /* UART2 device driver structure */
    cy_stc_sysint_t UART2_SCB_IRQ_cfg =
        {
            .intrSrc = (IRQn_Type)scb_2_interrupt_IRQn,
            .intrPriority = (7u),
    };
#endif
#ifdef BSP_USING_UART3
    /* UART3 device driver structure */
    cy_stc_sysint_t UART3_SCB_IRQ_cfg =
        {
            .intrSrc = (IRQn_Type)scb_3_interrupt_IRQn,
            .intrPriority = (7u),
    };
#endif
#ifdef BSP_USING_UART4
    /* UART4 device driver structure */
    cy_stc_sysint_t UART4_SCB_IRQ_cfg =
        {
            .intrSrc = (IRQn_Type)scb_4_interrupt_IRQn,
            .intrPriority = (7u),
    };
#endif
#ifdef BSP_USING_UART5
    /* UART5 device driver structure */
    cy_stc_sysint_t UART5_SCB_IRQ_cfg =
        {
            .intrSrc = (IRQn_Type)scb_5_interrupt_IRQn,
            .intrPriority = (7u),
    };
#endif

#if defined(BSP_USING_UART0)
#ifndef UART0_CONFIG
#define UART0_CONFIG                            \
    {                                           \
        .name = "uart0",                        \
        .tx_pin = P0_3,                         \
        .rx_pin = P0_2,                         \
        .usart_x = SCB0,                        \
        .intrSrc = scb_0_interrupt_IRQn,        \
        .userIsr = uart_isr_callback(uart0),    \
        .UART_SCB_IRQ_cfg = &UART0_SCB_IRQ_cfg, \
    }
    void uart0_isr_callback(void);
#endif /* UART0_CONFIG */
#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG                            \
    {                                           \
        .name = "uart1",                        \
        .tx_pin = P10_1,                        \
        .rx_pin = P10_0,                        \
        .usart_x = SCB1,                        \
        .intrSrc = scb_1_interrupt_IRQn,        \
        .userIsr = uart_isr_callback(uart1),    \
        .UART_SCB_IRQ_cfg = &UART1_SCB_IRQ_cfg, \
    }
    void uart1_isr_callback(void);
#endif /* UART1_CONFIG */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#if defined(SOC_CY8C6244LQI_S4D92)
#define UART2_CONFIG                            \
    {                                           \
        .name = "uart2",                        \
        .tx_pin = P3_1,                         \
        .rx_pin = P3_0,                         \
        .usart_x = SCB2,                        \
        .intrSrc = scb_2_interrupt_IRQn,        \
        .userIsr = uart_isr_callback(uart2),    \
        .UART_SCB_IRQ_cfg = &UART2_SCB_IRQ_cfg, \
    }
#else
#define UART2_CONFIG                            \
    {                                           \
        .name = "uart2",                        \
        .tx_pin = P9_1,                         \
        .rx_pin = P9_0,                         \
        .usart_x = SCB2,                        \
        .intrSrc = scb_2_interrupt_IRQn,        \
        .userIsr = uart_isr_callback(uart2),    \
        .UART_SCB_IRQ_cfg = &UART2_SCB_IRQ_cfg, \
    }
#endif /* SOC_CY8C6244LQI_S4D92 */
    void uart2_isr_callback(void);
#endif /* UART2_CONFIG */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG                            \
    {                                           \
        .name = "uart3",                        \
        .tx_pin = P6_1,                         \
        .rx_pin = P6_0,                         \
        .usart_x = SCB3,                        \
        .intrSrc = scb_3_interrupt_IRQn,        \
        .userIsr = uart_isr_callback(uart3),    \
        .UART_SCB_IRQ_cfg = &UART3_SCB_IRQ_cfg, \
    }
    void uart3_isr_callback(void);
#endif /* UART3_CONFIG */
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
#ifndef UART4_CONFIG
#define UART4_CONFIG                            \
    {                                           \
        .name = "uart4",                        \
        .tx_pin = P7_1,                         \
        .rx_pin = P7_0,                         \
        .usart_x = SCB4,                        \
        .intrSrc = scb_4_interrupt_IRQn,        \
        .userIsr = uart_isr_callback(uart4),    \
        .UART_SCB_IRQ_cfg = &UART4_SCB_IRQ_cfg, \
    }
    void uart4_isr_callback(void);
#endif /* UART4_CONFIG */
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
#ifndef UART5_CONFIG
#define UART5_CONFIG                            \
    {                                           \
        .name = "uart5",                        \
        .tx_pin = P5_1,                         \
        .rx_pin = P5_0,                         \
        .usart_x = SCB5,                        \
        .intrSrc = scb_5_interrupt_IRQn,        \
        .userIsr = uart_isr_callback(uart5),    \
        .UART_SCB_IRQ_cfg = &UART5_SCB_IRQ_cfg, \
    }
    void uart5_isr_callback(void);
#endif /* UART5_CONFIG */
#endif /* BSP_USING_UART5 */

#ifdef __cplusplus
}
#endif

#endif
