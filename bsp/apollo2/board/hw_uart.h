/*
 * File      : hw_uart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-14     Haley        the first version
 */
 
#ifndef __HW_UART_H_
#define __HW_UART_H_

#include <rtthread.h>

void rt_hw_uart_init(void);
void rt_hw_uart_send_string(char *pcString);

#endif // __HW_UART_H_
