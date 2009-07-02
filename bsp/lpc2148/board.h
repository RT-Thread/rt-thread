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
 * 2009-02-16     Bernard      add board.h to this bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__
#include <rtthread.h>

#define CCLK	60000000	/* Fosc = 12MHz, M = 5 */
#define PCLK	15000000	/* CCLK/4, use default */

void rt_hw_board_init(void);

#ifdef RT_USING_FINSH
void rt_hw_finsh_init(void);
#endif

#endif
