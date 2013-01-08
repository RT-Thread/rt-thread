/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-05-16     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>
#include <board.h>

#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <inc/hw_uart.h>
#include <driverlib/uart.h>
#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>
#include <driverlib/systick.h>
#include <driverlib/interrupt.h>


static void rt_hw_console_init(void);

/**
 * @addtogroup LM3S
 */

/*@{*/

extern void rt_hw_interrupt_thread_switch(void);
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
	rt_hw_interrupt_thread_switch();
}

/**
 * This is the ethernet interrupt service routine.
 *
 */
void rt_hw_eth_handler(void)
{
#ifdef RT_USING_LWIP
    extern void luminaryif_isr(void);

    /* enter interrupt */
    rt_interrupt_enter();

    /* luminary ethernet interface */
    luminaryif_isr();

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}

/**
 * This function will initial LM3S board.
 */
void rt_hw_board_init()
{
	// set sysclock to 80M
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	/* init systick */
	SysTickDisable();
	SysTickPeriodSet(SysCtlClockGet()/RT_TICK_PER_SECOND);
	SysTickIntEnable();
	SysTickEnable();

	/* enable ssio */
	//SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);

#if LM3S_EXT_SRAM == 1
	/* init SDRAM */
	rt_hw_sdram_init();
#endif
	/* init console */
	rt_hw_console_init();

	/* enable interrupt */
	IntMasterEnable();
}

/* init console to support rt_kprintf */
static void rt_hw_console_init()
{
	/* Enable the UART0 peripherals */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	/* Set GPIO A0 and A1 as UART pins. */
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	/* Configure the UART for 115,200, 8-N-1 operation. */
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
	                    (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
	                     UART_CONFIG_PAR_NONE));
}

/* write one character to serial, must not trigger interrupt */
static void rt_hw_console_putc(const char c)
{
	if (c == '\n')
		while(UARTCharPutNonBlocking(UART0_BASE, '\r') == false);

	while(UARTCharPutNonBlocking(UART0_BASE, c) == false);
}

/**
 * This function is used by rt_kprintf to display a string on console.
 *
 * @param str the displayed string
 */
void rt_hw_console_output(const char* str)
{
	while (*str)
	{
		rt_hw_console_putc (*str++);
	}
}

/*@}*/
