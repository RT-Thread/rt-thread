/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
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

#if defined(SOC_SERIES_IFX_XMC)
#if defined(UART_CPU_IRQ_Number)
#if (UART_CPU_IRQ_Number == 0)
    #define UART_NvicMuxN_IRQn NvicMux0_IRQn
#elif(UART_CPU_IRQ_Number == 1)
    #define UART_NvicMuxN_IRQn NvicMux1_IRQn
#elif (UART_CPU_IRQ_Number == 2)
    #define UART_NvicMuxN_IRQn NvicMux2_IRQn
#elif (UART_CPU_IRQ_Number == 3)
    #define UART_NvicMuxN_IRQn NvicMux3_IRQn
#elif (UART_CPU_IRQ_Number == 4)
    #define UART_NvicMuxN_IRQn NvicMux4_IRQn
#elif (UART_CPU_IRQ_Number == 5)
    #define UART_NvicMuxN_IRQn NvicMux5_IRQn
#elif (UART_CPU_IRQ_Number == 6)
    #define UART_NvicMuxN_IRQn NvicMux6_IRQn
#elif (UART_CPU_IRQ_Number == 7)
    #define UART_NvicMuxN_IRQn NvicMux7_IRQn
#endif
#endif
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
#if defined(SOC_SERIES_IFX_XMC)
            .intrSrc = ((UART_NvicMuxN_IRQn << 16) | (cy_en_intr_t)scb_3_interrupt_IRQn),
#else
            .intrSrc = (IRQn_Type)scb_3_interrupt_IRQn,
#endif
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
#ifdef BSP_USING_UART6
    /* UART6 device driver structure */
    cy_stc_sysint_t UART6_SCB_IRQ_cfg =
        {
            .intrSrc = (IRQn_Type)scb_6_interrupt_IRQn,
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
#if defined(SOC_XMC7200D_E272K8384AA)
#define UART3_CONFIG                            \
    {                                           \
        .name = "uart3",                        \
        .tx_pin = P13_1,                        \
        .rx_pin = P13_0,                        \
        .usart_x = SCB3,                        \
        .intrSrc = scb_3_interrupt_IRQn,        \
        .userIsr = uart_isr_callback(uart3),    \
        .UART_SCB_IRQ_cfg = &UART3_SCB_IRQ_cfg, \
    }
#else
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
#endif
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

#if defined(BSP_USING_UART6)
#ifndef UART6_CONFIG
#define UART6_CONFIG                            \
    {                                           \
        .name = "uart6",                        \
        .tx_pin = P6_5,                         \
        .rx_pin = P6_4,                         \
        .usart_x = SCB6,                        \
        .intrSrc = scb_6_interrupt_IRQn,        \
        .userIsr = uart_isr_callback(uart6),    \
        .UART_SCB_IRQ_cfg = &UART6_SCB_IRQ_cfg, \
    }
    void uart6_isr_callback(void);
#endif /* UART6_CONFIG */
#endif /* BSP_USING_UART6 */
#ifdef __cplusplus
}
#endif

#endif
