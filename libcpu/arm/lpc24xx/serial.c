/*
 * File      : serial.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-23     Bernard      first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "lpc214x.h"
#include "board.h"

void rt_serial_init(void);

#define PCLK		18000000
#define BAUD_RATE	115200
#define U0PINS  	0x00000005

/**
 * @addtogroup LPC2100
 */
/*@{*/

/**
 * This function is used to display a string on console, normally, it's
 * invoked by rt_kprintf
 *
 * @param str the displayed string
 */
void rt_console_puts(const char* str)
{
	while (*str)
	{
		rt_serial_putc (*str++);
	}
}

#define UART_RX_BUFFER_SIZE	64
static rt_uint8_t  uart_rx_buffer[UART_RX_BUFFER_SIZE];
static rt_uint32_t uart_read_index, uart_save_index;

/**
 * This function initializes serial
 */
void rt_serial_init()
{
	unsigned long Fdiv;

	PINSEL0 = 0x00000050;       /* RxD0 and TxD0 */

	rt_memset(uart_rx_buffer, 0, sizeof(uart_rx_buffer));
	uart_read_index = uart_save_index = 0;

	U0LCR = 0x83;		/* 8 bits, no Parity, 1 Stop bit */
	/*PCLK select is 00,so /4*/
	Fdiv = ( PCLK / 16 ) / BAUD_RATE ;	/*baud rate */
	U0DLM = Fdiv / 256;							
	U0DLL = Fdiv % 256;
	U0FCR = 0x00;		/* Enable and reset TX and RX FIFO. */
	U0LCR = 0x03;		/* DLAB = 0 */
}

/* save a char to serial buffer */
void rt_serial_savechar(char ch)
{
	rt_base_t level;
	
	/* disable interrupt */
	level = rt_hw_interrupt_disable();

	uart_rx_buffer[uart_save_index] = ch;
	uart_save_index ++;
	if (uart_save_index >= UART_RX_BUFFER_SIZE)
		uart_save_index = 0;
	
	/* if the next position is read index, discard this 'read char' */
	if (uart_save_index == uart_read_index)
	{
		uart_read_index ++;
		if (uart_read_index >= UART_RX_BUFFER_SIZE)
			uart_read_index = 0;
	}

	/* enable interrupt */
	rt_hw_interrupt_enable(level);
}

/**
 * This function read a character from serial without interrupt enable mode
 *
 * @return the read char
 */
char rt_serial_getc()
{
	char ch;
	rt_base_t level;
	
	/* disable interrupt */
	level = rt_hw_interrupt_disable();
	
	if (uart_read_index != uart_save_index)
	{
		ch = uart_rx_buffer[uart_read_index];

		uart_read_index ++;
		if (uart_read_index >= UART_RX_BUFFER_SIZE)
			uart_read_index = 0;
		
		/* enable interrupt */
		rt_hw_interrupt_enable(level);
		
		return ch;
	}

	/* enable interrupt */
	rt_hw_interrupt_enable(level);

	return 0;
}

/**
 * This function will write a character to serial without interrupt enable mode
 *
 * @param c the char to write
 */
void rt_serial_putc(const char c)
{
	/*
		to be polite with serial console add a line feed
		to the carriage return character
	*/
	if (c=='\n')
	{
		while (!(U0LSR & 0x20));
		U0THR = '\r';
	}

	while (!(U0LSR & 0x20));
	U0THR = c;
}

/*@}*/
