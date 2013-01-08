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
 * 2010-01-25     Bernard      first version
 */

#include <rtthread.h>
#include <rthw.h>

#include "board.h"
#include "uart.h"

#include "CMSIS/CM0/NUC1xx.h"
#include "CMSIS/CM0/core_cm0.h"

/**
 * @addtogroup NUC100
 */
/*@{*/

/**
 * This is the timer interrupt service routine.
 */
void rt_hw_timer_handler()
{
	/* enter interrupt */
	rt_interrupt_enter();

	rt_tick_increase();

	/* leave interrupt */
	rt_interrupt_leave();
}

/**
 * This function will initial sam7s64 board.
 */
void rt_hw_board_init()
{
	SystemInit();

	/* init systick */
	SysTick_Config(SystemFrequency/RT_TICK_PER_SECOND - 1);

	/* set pend exception priority */
	NVIC_SetPriority(PendSV_IRQn, (1<<__NVIC_PRIO_BITS) - 1);

#ifdef RT_USING_UART
	/* init hardware UART device */
	rt_hw_uart_init();
#endif
#ifdef RT_USING_CONSOLE
	/* set console device */
	rt_console_set_device("uart1");
#endif
}
/*@}*/
