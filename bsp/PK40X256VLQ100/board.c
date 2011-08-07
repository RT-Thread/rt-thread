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
 * 2011-08-06     Magicoe      PK40X256VLQ100 version
 */

#include <rtthread.h>
#include <rthw.h>

#include "board.h"
#include "uart.h"

#include "PK40X256VLQ100.h"
#include "core_cm4.h"

#include "SLCD_Driver.h"

/**
 * @addtogroup PK40X256VLQ100
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
	rt_uint8_t *dispchar = {"RTINIT"};
	/* Get Core Clock Frequency */
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency */
	/* init systick */
	SysTick_Config( SystemCoreClock/1000 );       /* Generate interrupt each 1 ms    */
	
	SLCD_Configuration();
	SLCD_SegmentsAllOff ();
	SLCD_PrintString(dispchar, 0);

	/* set pend exception priority */
//	NVIC_SetPriority(PendSV_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
#ifdef RT_USING_UART
	/* init hardware UART device */
	rt_hw_uart_init();
#endif
#ifdef RT_USING_CONSOLE
	/* set console device */
	rt_console_set_device("uart0");
#endif
	SLCD_PrintString(dispchar, 0);
}
/*@}*/
