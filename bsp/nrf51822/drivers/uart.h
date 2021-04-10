/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef __UART_H__
#define __UART_H__



#define RX_PIN_NUMBER          25
#define TX_PIN_NUMBER          24
#define CTS_PIN_NUMBER         26
#define RTS_PIN_NUMBER         27
#define HWFC                   false


void rt_hw_uart_init(void);

#endif
