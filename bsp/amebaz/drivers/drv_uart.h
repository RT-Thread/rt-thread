/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-05-30     Bernard      the first version
 * 2018-03-15     flyingcys    add amebaz
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#if defined(CONFIG_PLATFORM_8711B)
// 8710B
#define UART_TX PA_23
#define UART_RX PA_18
#else
// 8711AM
#define UART_TX PA_7
#define UART_RX PA_6
//8711AF
//#define UART_TX PA_4
//#define UART_RX PA_0
#endif

int rt_hw_uart_init(void);

#endif /* __DRV_UART_H__ */
