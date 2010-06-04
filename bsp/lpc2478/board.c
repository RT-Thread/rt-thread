/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-12-11     xuxinming    first version
 */

#include <rtthread.h>
#include <rthw.h>

#include <LPC24xx.h>
#include "board.h"

/* #define RT_BOARD_DEBUG */

#define DATA_COUNT 14400000/RT_TICK_PER_SECOND	/* T0MR0 = delayInMs * (Fpclk / 1000); */

/**
 * @addtogroup LPC2478
 */
/*@{*/

void rt_timer_handler(int vector)
{
#ifdef BOARD_DEBUG
	rt_kprintf("timer handler, increase a tick\n");
#endif

	T0IR |= 0x01;			/* clear interrupt flag */
	rt_tick_increase();
	VICVectAddr = 0;		/* Acknowledge Interrupt */
}


/**
 * This function is used to display a string on console, normally, it's
 * invoked by rt_kprintf
 *
 * @param str the displayed string
 */
void rt_hw_console_output(const char* str)
{
	while (*str)
	{
		if (*str=='\n')
		{
			while (!(U0LSR & 0x20));
			U0THR = '\r';
		}
	
		while (!(U0LSR & 0x20));
		U0THR = *str;
		
		str ++;
	}
}

#define BAUD_RATE	115200
#define U0PINS		0x50
void rt_hw_console_init()
{
	rt_uint32_t fdiv;

	/* Enable RxD and TxD pins */
  	PINSEL0 = U0PINS;

	/* 8 bits, no Parity, 1 Stop bit */
	U0LCR = 0x83;

	/* Setup Baudrate */
	fdiv = ( PCLK / 16 ) / BAUD_RATE ;	/*baud rate */
	U0DLM = fdiv / 256;							
	U0DLL = fdiv % 256;
	U0FCR = 0x00;		/* Enable and reset TX and RX FIFO. */
	U0LCR = 0x03;		/* DLAB = 0 */

	/* DLAB = 0 */
	U0LCR = 0x03;
}

/**
 * This function will init LPC2478 board
 */
void rt_hw_board_init()
{
	/* init console for rt_kprintf function */
	rt_hw_console_init();
	
	T0IR 	= 0xff; 
	T0TC 	= 0;
	T0MCR 	= 0x03; 
	T0MR0 	= (DATA_COUNT);

	rt_hw_interrupt_install(TIMER0_INT, rt_timer_handler, RT_NULL);	
	rt_hw_interrupt_umask(TIMER0_INT);

	T0TCR = 0x01; //enable timer0 counter
}

/*@}*/
