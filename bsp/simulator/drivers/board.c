/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

/**
 * @addtogroup simulator on win32
 */

/**
 * This function will initial STM32 board.
 */
void rt_hw_board_init()
{
#if 0
	/* NVIC Configuration */
	NVIC_Configuration();

    /* Configure the SysTick */
    SysTick_Config( SystemCoreClock / RT_TICK_PER_SECOND );
#endif 

#if defined(RT_USING_CONSOLE)
	rt_hw_usart_init();
	rt_hw_serial_init();
	rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

}

/*@}*/
