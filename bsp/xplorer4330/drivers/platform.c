/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-12-13     lgnq         first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "cmsis.h"

#ifdef RT_USING_SERIAL
#include "usart.h"
#endif

/**
 * @addtogroup LPC4330
 */

/*@{*/

/**
 * This is the timer interrupt service routine.
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This function will initialize the LPC4330 Xplorer board.
 */
void rt_hw_board_init(void)
{
    Board_Init();

    /* Configure the SysTick - Generate interrupt @ 100 Hz*/
    SysTick_Config(Chip_Clock_GetRate(CLK_MX_MXCORE) / 100);

#ifdef RT_USING_SERIAL
    rt_hw_serial_init();

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
#endif
}

/*@}*/
