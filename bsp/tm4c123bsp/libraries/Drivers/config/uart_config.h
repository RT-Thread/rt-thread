/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     AHTYDHD      the first version
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_UART0)
#ifndef UART0_CONFIG
#define UART0_CONFIG                                                \
    {                                                               \
        .name = "uart0",                                            \
        .uartbase = UART0_BASE,                                     \
        .baudrate = 115200,                                         \
        .mode     = UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |     \
                             UART_CONFIG_PAR_NONE                   \
    }
#endif /* UART1_CONFIG */
#endif /* BSP_USING_UART1*/

#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG                                                \
    {                                                               \
        .name = "uart1",                                            \
        .uartbase = UART1_BASE,                                     \
        .baudrate = 115200,                                         \
        .mode     = UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |     \
                             UART_CONFIG_PAR_NONE                   \
    }
#endif /* UART1_CONFIG */
#endif /* BSP_USING_UART1*/

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG                                                \
    {                                                               \
        .name = "uart2",                                            \
        .uartbase = UART2_BASE,                                     \
        .baudrate = 115200,                                         \
        .mode     = UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |     \
                             UART_CONFIG_PAR_NONE                   \
    }
#endif /* UART2_CONFIG */
#endif /* BSP_USING_UART2*/

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG                                                \
    {                                                               \
        .name = "uart3",                                            \
        .uartbase = UART3_BASE,                                     \
        .baudrate = 115200,                                         \
        .mode     = UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |     \
                             UART_CONFIG_PAR_NONE                   \
    }
#endif /* UART3_CONFIG */
#endif /* BSP_USING_UART3*/

#ifdef __cplusplus
}
#endif

#endif /* __UART_CONFIG_H__ */

/************************** end of file ******************/
