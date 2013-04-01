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
 * 2010-06-25     Bernard      first version
 */

#include <rtthread.h>
#include <rthw.h>

#include "board.h"
#include "uart.h"
#include <jz4755.h>

/**
 * @addtogroup JZ47xx
 */
/*@{*/

/**
 * This is the timer interrupt service routine.
 */
void rt_hw_timer_handler(int vector, void* param)
{
	/* increase a OS tick */
	rt_tick_increase();

	/* clear flag */
	TCU_TFCR = TCU_TFCR_OSTFLAG;
}

/**
 * This function will initial OS timer
 */
void rt_hw_timer_init(void)
{
	rt_uint32_t val;

	/* disable TCU clock */
	CPM_CLKGR &= ~CPM_CLKGR_TCU;
	TCU_TECR = TCU_TECR_OSTCL;

	/* set */
	OST_DR = RT_TICK_PER_SECOND * 0xcffff;
	/* clear counter */
	OST_CNT = 0;

#ifdef RTC_SRC_EXTAL
	OST_CSR = (val | OST_TCSR_EXT_EN);
#else
	OST_CSR = (val | OST_TCSR_PCLK_EN);
#endif

	TCU_TFCR = TCU_TFCR_OSTFLAG;
	TCU_TMCR = TCU_TMCR_OSTMCL;
	TCU_TESR = TCU_TESR_OSTST;

	rt_hw_interrupt_install(IRQ_TCU0, rt_hw_timer_handler, RT_NULL, "tick");
	rt_hw_interrupt_umask  (IRQ_TCU0);
}

/**
 * This function will initial sam7s64 board.
 */
void rt_hw_board_init()
{
#ifdef RT_USING_UART
	/* init hardware UART device */
	rt_hw_uart_init();
#endif

#ifdef RT_USING_CONSOLE
	/* set console device */
	rt_console_set_device("uart");
#endif

	/* init operating system timer */
	rt_hw_timer_init();
}
/*@}*/
