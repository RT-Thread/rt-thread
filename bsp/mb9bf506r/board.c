/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 - 2011 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-24     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "mb9bf506r.h"

#include "serial.h"
#include "nand.h"

extern const uint32_t SystemFrequency;

/**
 * @addtogroup FM3
 */

/*@{*/

/**
 * This is the timer interrupt service routine.
 *
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
* This function will initial FM3 Easy Kit board.
 */
void rt_hw_board_init(void)
{
    /* init systick */
    SysTick_Config(SystemFrequency/RT_TICK_PER_SECOND);
    
	/* initialize UART device */
	rt_hw_serial_init();
	/* set console as UART device */
	rt_console_set_device("uart2");
	
	/* initialize nand flash device */
	rt_hw_nand_init();
}

/*@}*/
