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
#include "core_cm3.h"

extern const uint32_t SystemFrequency;

#define UART0	FM3_MFS0_UART
struct serial_int_rx uart0_int_rx;
struct serial_device uart0 =
{
	UART0,
	&uart0_int_rx,
	RT_NULL
};
struct rt_device uart0_device;

#define UART2	FM3_MFS2_UART
struct serial_int_rx uart2_int_rx;
struct serial_device uart2 =
{
	UART2,
	&uart2_int_rx,
	RT_NULL
};
struct rt_device uart2_device;

/**
 * @addtogroup FM3
 */

/*@{*/

/**
 * This is the timer interrupt service routine.
 *
 */
void rt_hw_timer_handler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();

	rt_tick_increase();

	/* leave interrupt */
	rt_interrupt_leave();
}

void rt_hw_uart2_rx_handler(void)
{
#ifdef RT_USING_UART2
    extern struct rt_device uart2_device;
	extern void rt_hw_serial_isr(struct rt_device *device);

    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_serial_isr(&uart2_device);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}

/**
 * This function will handle init uart
 */
static void rt_hw_uart_init(void)
{
    /* Set Uart Ch2 Port, SIN2_1, SOT2_1 */
    FM3_GPIO->PFR2 = FM3_GPIO->PFR2 | 0x0030;
    FM3_GPIO->EPFR07 = FM3_GPIO->EPFR07 | 0x000a0000;
    
uart2.uart_device->SMR = SMR_MD_UART | SMR_SOE;;
uart2.uart_device->BGR = (40000000UL + (BPS/2))/BPS - 1;
uart2.uart_device->ESCR = ESCR_DATABITS_8;
uart2.uart_device->SCR = SCR_RXE | SCR_TXE | SCR_RIE;

UART_ENABLE_IRQ(MFS2RX_IRQn);
UART_ENABLE_IRQ(MFS2TX_IRQn);
}

/**
* This function will initial FM3 Easy Kit board.
 */
void rt_hw_board_init()
{
    /* init systick */
    SysTick_Config(SystemFrequency/RT_TICK_PER_SECOND - 1);
    rt_hw_uart_init();
}

/*@}*/
