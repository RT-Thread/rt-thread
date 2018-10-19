/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __UART_H__
#define __UART_H__



#define RX_PIN_NUMBER          23
#define TX_PIN_NUMBER          24
#define CTS_PIN_NUMBER         25
#define RTS_PIN_NUMBER         22
#define HWFC                   false


void rt_hw_uart_init(void);

#endif
