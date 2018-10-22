/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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

void rt_hw_board_led_on(int n);
void rt_hw_board_led_off(int n);
void rt_hw_board_init(void);

#endif
