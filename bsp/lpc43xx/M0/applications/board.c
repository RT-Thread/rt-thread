/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2014 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2014-06-20     xiaonong     ported to LPC43xx
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"


/** M0 does not have SysTick so we have to use RIT timer for it... */
void RIT_OR_WWDT_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This function will initial LPC43xx board.
 */
void rt_hw_board_init()
{
    /* set pend exception priority */
    NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

    /* init uart device */
    rt_hw_uart_init();

    /* setup the console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
}

