/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-10-08     Bernard      add board.h to this bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rthw.h>
#include <rtthread.h>


#define MCK		48054857
#define BR    	115200			/* Baud Rate */
#define BRD  	(MCK/16/BR)		/* Baud Rate Divisor */

#define RT_UART_RX_BUFFER_SIZE	128

void rt_hw_board_led_on(int n);
void rt_hw_board_led_off(int n);
void rt_hw_board_init(void);

#endif
