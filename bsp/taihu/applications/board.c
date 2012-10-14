/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-04-16         first version
 */

#include <rtthread.h>
#include <rthw.h>

#include "board.h"

void rt_hw_board_init()
{
	rt_hw_serial_init();
	rt_console_set_device("uart1");
}
