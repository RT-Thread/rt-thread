/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-27     Grissiom     port to RM48x50
 */

#include <rtthread.h>
#include <rthw.h>

#include "sys_common.h"
#include "system.h"
#include "rti.h"

#include "board.h"

#include "drv_uart.h"

#define RTI_INT_VEC 6

void rt_timer_handler(int vector, void* param)
{
    rtiREG1->INTFLAG = 8U; /* clear interrupt flag */
	rt_tick_increase();
}

void rt_hw_board_init(void)
{
    rtiInit();

	rt_hw_interrupt_install(RTI_INT_VEC, rt_timer_handler, RT_NULL, "tick");
    rt_hw_interrupt_umask(RTI_INT_VEC);

    rtiStartCounter(rtiCOUNTER_BLOCK1);
    rtiEnableNotification(rtiNOTIFICATION_COMPARE3);

    rt_hw_uart_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
}

