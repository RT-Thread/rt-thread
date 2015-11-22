/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2015-11-11     Xue Liu		Initial for nRF52
 */

#include <rthw.h>
#include <rtthread.h>

#include <nrf52.h>
#include <nrf52_bitfields.h>

#include "board.h"
#include "uart.h"

/**
 * @addtogroup NRF52832
 */

/** @brief: Function for handling the Systick interrupts.
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
	
	rt_tick_increase();  //This function will notify kernel there is one tick passed
	
	/* leave interrupt */
    rt_interrupt_leave();
}


/**
 * This function will initial NRF52832 board.
 */
void rt_hw_board_init()
{
    /* Configure the SysTick */
	SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

    /* Initial usart deriver, and set console device */
    rt_hw_uart_init();

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}

/*@}*/
