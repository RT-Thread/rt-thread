/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 * 2020-07-10     lik          rewrite
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include "board.h"

/* swm config class */
struct swm_uart_cfg
{
    const char *name;
    UART_TypeDef *UARTx;
    IRQn_Type irq;
    UART_InitStructure uart_initstruct;
};

/* swm uart dirver class */
struct swm_uart
{
    struct swm_uart_cfg *cfg;
    struct rt_serial_device serial_device;
};

#ifdef BSP_USING_UART0
#ifndef UART0_CFG
#define UART0_CFG                                   \
    {                                               \
        .name = "uart0",                            \
        .UARTx = UART0,                             \
        .irq = UART0_IRQn,                          \
        .uart_initstruct.Baudrate = 115200,         \
        .uart_initstruct.DataBits = UART_DATA_8BIT, \
        .uart_initstruct.Parity = UART_PARITY_NONE, \
        .uart_initstruct.StopBits = UART_STOP_1BIT, \
        .uart_initstruct.RXThreshold = 0,           \
        .uart_initstruct.RXThresholdIEn = 1,        \
        .uart_initstruct.TXThresholdIEn = 0,        \
        .uart_initstruct.TimeoutTime = 10,          \
        .uart_initstruct.TimeoutIEn = 1,            \
    }
#endif /* UART0_CFG */
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
#ifndef UART1_CFG
#define UART1_CFG                                   \
    {                                               \
        .name = "uart1",                            \
        .UARTx = UART1,                             \
        .irq = UART1_IRQn,                          \
        .uart_initstruct.Baudrate = 115200,         \
        .uart_initstruct.DataBits = UART_DATA_8BIT, \
        .uart_initstruct.Parity = UART_PARITY_NONE, \
        .uart_initstruct.StopBits = UART_STOP_1BIT, \
        .uart_initstruct.RXThreshold = 0,           \
        .uart_initstruct.RXThresholdIEn = 1,        \
        .uart_initstruct.TXThresholdIEn = 0,        \
        .uart_initstruct.TimeoutTime = 10,          \
        .uart_initstruct.TimeoutIEn = 1,            \
    }
#endif /* UART1_CFG */
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
#ifndef UART2_CFG
#define UART2_CFG                                   \
    {                                               \
        .name = "uart2",                            \
        .UARTx = UART2,                             \
        .irq = UART2_IRQn,                          \
        .uart_initstruct.Baudrate = 115200,         \
        .uart_initstruct.DataBits = UART_DATA_8BIT, \
        .uart_initstruct.Parity = UART_PARITY_NONE, \
        .uart_initstruct.StopBits = UART_STOP_1BIT, \
        .uart_initstruct.RXThreshold = 0,           \
        .uart_initstruct.RXThresholdIEn = 1,        \
        .uart_initstruct.TXThresholdIEn = 0,        \
        .uart_initstruct.TimeoutTime = 10,          \
        .uart_initstruct.TimeoutIEn = 1,            \
    }
#endif /* UART2_CFG */
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
#ifndef UART3_CFG
#define UART3_CFG                                   \
    {                                               \
        .name = "uart3",                            \
        .UARTx = UART3,                             \
        .irq = UART3_IRQn,                          \
        .uart_initstruct.Baudrate = 115200,         \
        .uart_initstruct.DataBits = UART_DATA_8BIT, \
        .uart_initstruct.Parity = UART_PARITY_NONE, \
        .uart_initstruct.StopBits = UART_STOP_1BIT, \
        .uart_initstruct.RXThreshold = 0,           \
        .uart_initstruct.RXThresholdIEn = 1,        \
        .uart_initstruct.TXThresholdIEn = 0,        \
        .uart_initstruct.TimeoutTime = 10,          \
        .uart_initstruct.TimeoutIEn = 1,            \
    }
#endif /* UART3_CFG */
#endif /* BSP_USING_UART3 */

int rt_hw_serial_init(void);

#endif /* __DRV_UART_H__ */
