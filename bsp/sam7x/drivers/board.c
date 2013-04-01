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
 * 2006-08-23     Bernard      first implementation
 * 2010-03-09     ljt8015      Fix a bug in rt_hw_console_init()
 */

#include <rtthread.h>
#include <rthw.h>

#include <AT91SAM7X256.h>
#include "board.h"

static void rt_hw_board_led_init(void);

/**
 * @addtogroup sam7s
 */
/*@{*/

/* Periodic Interval Value */
#define PIV  (((MCK/16)/1000)*(1000/RT_TICK_PER_SECOND))

/**
 * This is the timer interrupt service routine.
 * @param vector the irq number for timer
 */
void rt_hw_timer_handler(int vector, void* param)
{
	if (AT91C_BASE_PITC->PITC_PISR & 0x01)
	{
		/* increase a tick */
		rt_tick_increase();

		/* ack interrupt */
		AT91C_BASE_AIC->AIC_EOICR = AT91C_BASE_PITC->PITC_PIVR;
	}
	else
	{
		/* end of interrupt */
		AT91C_BASE_AIC->AIC_EOICR = 0;
	}
}
						/* PIO   Flash    PA    PB   PIN */
#define LED1 (1 << 19)	/* PA0 / PGMEN0 & PWM0 TIOA0  48 */
#define LED2 (1 << 20)	/* PA1 / PGMEN1 & PWM1 TIOB0  47 */
#define LED3 (1 << 21)	/* PA2          & PWM2 SCK0   44 */
#define LED4 (1 << 22)	/* PA3          & TWD  NPCS3  43 */
#define LED_MASK		(LED1|LED2|LED3|LED4)

int leds[] = {LED1, LED2, LED3, LED4};

/** 
 * This function will init led on the board
 */
static void rt_hw_board_led_init()
{
	/* enable the clock of the PIO A, PIO B */
	AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_PIOA | 1 << AT91C_ID_PIOB;

	/* configure PIO as output for led */
	AT91C_BASE_PIOB->PIO_PER = LED_MASK;
	AT91C_BASE_PIOB->PIO_OER = LED_MASK;
}

/**
 * This function will take the led on board on.
 *
 * @param n the number nth led
 */
void rt_hw_board_led_on(int n)
{
	if (n >= 0 && n < 4)
	{
		AT91C_BASE_PIOB->PIO_CODR = leds[n];
	}
}

/**
 * This function will take the led on board off.
 *
 * @param n the number nth led
 */
void rt_hw_board_led_off(int n)
{
	if (n >= 0 && n < 4)
	{
		AT91C_BASE_PIOB->PIO_SODR = leds[n];
	}
}

/*
 * RT-Thread Console Interface, used by rt_kprintf
 */
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
		if (*str == '\n')
		{
			while (!(AT91C_BASE_US0->US_CSR & AT91C_US_TXRDY));
			AT91C_BASE_US0->US_THR = '\r';
		}
		
		/* Wait for Empty Tx Buffer */
		while (!(AT91C_BASE_US0->US_CSR & AT91C_US_TXRDY));
		/* Transmit Character */
		AT91C_BASE_US0->US_THR = *str;
		
		str ++;
	}
}

static void rt_hw_console_init()
{
	/* Enable Clock for USART0 */
	AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_US0;
	/* Enable RxD0 and TxD0 Pin */
	//AT91C_BASE_PIOA->PIO_PDR = (1 << 5) | (1 << 6);
	AT91C_BASE_PIOA->PIO_PDR = 1 | (1 << 1);//fix bug 2010-3-9

	AT91C_BASE_US0->US_CR = AT91C_US_RSTRX	|		/* Reset Receiver      */
				AT91C_US_RSTTX		|		/* Reset Transmitter   */
				AT91C_US_RXDIS		|		/* Receiver Disable    */
				AT91C_US_TXDIS;				/* Transmitter Disable */

	AT91C_BASE_US0->US_MR = AT91C_US_USMODE_NORMAL |		/* Normal Mode */
				AT91C_US_CLKS_CLOCK		|		/* Clock = MCK */
				AT91C_US_CHRL_8_BITS	|		/* 8-bit Data  */
				AT91C_US_PAR_NONE		|		/* No Parity   */
				AT91C_US_NBSTOP_1_BIT;			/* 1 Stop Bit  */

	/* set baud rate divisor */
	AT91C_BASE_US0->US_BRGR = BRD;

	AT91C_BASE_US0->US_CR = AT91C_US_RXEN |	/* Receiver Enable     */
				AT91C_US_TXEN;	/* Transmitter Enable  */
}

/**
 * This function will initial sam7x board.
 */
void rt_hw_board_init(void)
{
	extern void rt_serial_init(void);
	
	/* init hardware console */
	rt_hw_console_init();

	/* init led */
	rt_hw_board_led_init();

	/* init PITC */
	AT91C_BASE_PITC->PITC_PIMR = (1 << 25) | (1 << 24) | PIV;

	/* install timer handler */
	rt_hw_interrupt_install(AT91C_ID_SYS, rt_hw_timer_handler, RT_NULL, "tick");
	AT91C_BASE_AIC->AIC_SMR[AT91C_ID_SYS] = 0;
	rt_hw_interrupt_umask(AT91C_ID_SYS);	
}
/*@}*/
