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
 * 2013-07-12     aozima       update for auto initial.
 */

#include <rthw.h>
#include <rtthread.h>

#include "nds32.h"
#include "bsp_hal.h"
#include "ae210p.h"
#include "debug.h"
//#include "uart/uart.h"
#include "uart_dev.h"

#include "board.h"
#include "rtconfig.h"

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
	/* clean timer device pending*/
	hal_timer_irq_clear(1);

    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/***********************************************************
 * Set timer 1 as system tick by default
 ***********************************************************/

void BSP_Tmr_TickInit(uint32_t tmrId, uint32_t period, uint32_t vecId, void *isr)
{
	/* set tick  period */
	hal_timer_set_period(tmrId, period);

	/* enable timer1 interrupt */
	hal_timer_irq_control(tmrId, 1);

	/******************************
 	 * tick ISR init
 	 ******************************/
	/* init trigger mode */
	/* Set edge trigger, falling edge */
	hal_intc_irq_config(vecId, 1, 0);
	/* clean pending */
	hal_intc_irq_clean(vecId);
	/* enable timer interrupt */
	hal_intc_irq_enable(vecId);

	if (isr)
		OS_CPU_Vector_Table[vecId] = isr;
	else
		DEBUG(1, 1, "Invalid tick handler!!\r\n");

	/* start timer */
	hal_timer_start(tmrId);
}

/*
 * Setup system tick for OS required.
 */
void bsp_init(void)
{
	/* disable interrupt first */
	rt_hw_interrupt_disable();

//	drv_uart_init();
	rt_hw_usart_init();
	rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

	/* System tick init */
	BSP_Tmr_TickInit(0x1, (MB_PCLK / RT_TICK_PER_SECOND), IRQ_SYS_TICK_VECTOR, SysTick_Handler);
}

/*@}*/
