/****************************************************************************
 *   $Id:: uart.c 3736 2010-06-24 02:07:03Z usb00423                        $
 *   Project: NXP LPC122x UART example
 *
 *   Description:
 *     This file contains UART code example which include UART 
 *     initialization, UART interrupt handler, and related APIs for 
 *     UART access.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include <rthw.h>
#include <rtthread.h>
#include <CMSIS/LPC122x.h>

#include "uart.h"

#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80

/**
 * @addtogroup LPC11xx
 */

/*@{*/
#if defined(RT_USING_UART) && defined(RT_USING_DEVICE)

#define UART_BAUDRATE   115200

struct rt_uart_lpc
{
	struct rt_device parent;

	/* buffer for reception */
	rt_uint8_t read_index, save_index;
	rt_uint8_t rx_buffer[RT_UART_RX_BUFFER_SIZE];
}uart_device;

void UART0_IRQHandler(void)
{
	rt_ubase_t level, iir;
	struct rt_uart_lpc* uart = &uart_device;

	/* read IIR and clear it */
	iir = LPC_UART0->IIR;

	iir >>= 0x01;		/* skip pending bit in IIR */
	iir  &= 0x07;		/* check bit 1~3, interrupt identification */

	if (iir == IIR_RDA)	/* Receive Line Status */
	{
		/* If no error on RLS, normal ready, save into the data buffer. */
		/* Note: read RBR will clear the interrupt */
		uart->rx_buffer[uart->save_index] = LPC_UART0->RBR;
		level = rt_hw_interrupt_disable();
		uart->save_index ++;
		if (uart->save_index >= RT_UART_RX_BUFFER_SIZE)
	   		uart->save_index = 0;
		rt_hw_interrupt_enable(level);
		/* invoke callback */
		if(uart->parent.rx_indicate != RT_NULL)
		{
		    rt_size_t length;
		    if (uart->read_index > uart->save_index)
	            length = RT_UART_RX_BUFFER_SIZE - uart->read_index + uart->save_index;
	        else
	            length = uart->save_index - uart->read_index;
	
	        uart->parent.rx_indicate(&uart->parent, length);
		}
	}
	return;
}

/*****************************************************************************
** Function name:		rt_uart_init
** Descriptions:		
** parameters:			dev
** Returned value:		None
*****************************************************************************/
static rt_err_t rt_uart_init(rt_device_t dev)
{
	rt_uint32_t Fdiv;
	rt_uint32_t regVal;

	NVIC_DisableIRQ(UART0_IRQn);
	
	/* Init UART Hardware */
	LPC_IOCON->PIO0_1  &= ~0x07;		/* UART I/O config */
	LPC_IOCON->PIO0_1  |=  0x02;		/* UART RXD */
	LPC_IOCON->PIO0_2  &= ~0x07;	
	LPC_IOCON->PIO0_2  |=  0x02;		/* UART TXD */
	
	/* Enable UART clock */
	LPC_SYSCON->PRESETCTRL    |= (0x1<<2);
	LPC_SYSCON->SYSAHBCLKCTRL |= (0x1<<12);
	LPC_SYSCON->UART0CLKDIV    =  0x1;	/* divided by 1 */
	
	LPC_UART0->LCR = 0x83;				/* 8 bits, no Parity, 1 Stop bit */
	regVal = LPC_SYSCON->UART0CLKDIV;
	Fdiv = ((SystemAHBFrequency/regVal)/16)/UART_BAUDRATE ;	/*baud rate */
	
	LPC_UART0->DLM = Fdiv / 256;							
	LPC_UART0->DLL = Fdiv % 256;
	LPC_UART0->LCR = 0x03;				/* DLAB = 0 */
	LPC_UART0->FCR = 0x07;				/* Enable and reset TX and RX FIFO. */
	
	/* Read to clear the line status. */
	regVal = LPC_UART0->LSR;
	
	/* Ensure a clean start, no data in either TX or RX FIFO. */
	while ( LPC_UART0->LSR & (LSR_THRE|LSR_TEMT) != (LSR_THRE|LSR_TEMT) );
	while ( LPC_UART0->LSR & LSR_RDR )
	{
		regVal = LPC_UART0->RBR;		/* Dump data from RX FIFO */
	}
 
	/* Enable the UART Interrupt */
	NVIC_EnableIRQ(UART0_IRQn);
	
	LPC_UART0->IER = IER_RBR | IER_THRE | IER_RLS;	/* Enable UART interrupt */

	return RT_EOK;
}

static rt_err_t rt_uart_open(rt_device_t dev, rt_uint16_t oflag)
{
	RT_ASSERT(dev != RT_NULL);
	if(dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* Enable the UART Interrupt */
		NVIC_EnableIRQ(UART0_IRQn);
	}
	return RT_EOK;
}

static rt_err_t rt_uart_close(rt_device_t dev)
{
	RT_ASSERT(dev != RT_NULL);
	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* Disable the UART Interrupt */
		NVIC_DisableIRQ(UART0_IRQn);
	}

	return RT_EOK;
}
static rt_size_t rt_uart_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_uint8_t* ptr;
	struct rt_uart_lpc *uart = (struct rt_uart_lpc*)dev;
	RT_ASSERT(uart != RT_NULL);

	/* point to buffer */
	ptr = (rt_uint8_t*) buffer;
	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		while (size)
		{
			/* interrupt receive */
			rt_base_t level;

			/* disable interrupt */
			level = rt_hw_interrupt_disable();
			if (uart->read_index != uart->save_index)
			{
				*ptr = uart->rx_buffer[uart->read_index];

				uart->read_index ++;
				if (uart->read_index >= RT_UART_RX_BUFFER_SIZE)
					uart->read_index = 0;
			}
			else
			{
				/* no data in rx buffer */

				/* enable interrupt */
				rt_hw_interrupt_enable(level);
				break;
			}

			/* enable interrupt */
			rt_hw_interrupt_enable(level);

			ptr ++;
			size --;
		}

		return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
	}

	return 0;
}

static rt_size_t rt_uart_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	char *ptr;
	ptr = (char*)buffer;

	if (dev->flag & RT_DEVICE_FLAG_STREAM)
	{
		/* stream mode */
		while (size)
		{
			if (*ptr == '\n')
			{
				/* THRE status, contain valid data */
				while ( !(LPC_UART0->LSR & LSR_THRE) );
				/* write data */
				LPC_UART0->THR = '\r';
			}

			/* THRE status, contain valid data */
			while ( !(LPC_UART0->LSR & LSR_THRE) );	
			/* write data */
			LPC_UART0->THR = *ptr;
			
			ptr ++;
			size --;
		}
	}
	else
	{
	while ( size != 0 )
	{
		/* THRE status, contain valid data */
		while ( !(LPC_UART0->LSR & LSR_THRE) );

		/* write data */
		LPC_UART0->THR = *ptr;

		ptr++;
		size--;
	}
	}

	return (rt_size_t) ptr - (rt_size_t) buffer;
}

void rt_hw_uart_init(void)
{
	struct rt_uart_lpc* uart;

	/* get uart device */
	uart = &uart_device;

	/* device initialization */
	uart->parent.type = RT_Device_Class_Char;
	rt_memset(uart->rx_buffer, 0, sizeof(uart->rx_buffer));
	uart->read_index = uart->save_index = 0;

	/* device interface */
	uart->parent.init 	    = rt_uart_init;
	uart->parent.open 	    = rt_uart_open;
	uart->parent.close      = rt_uart_close;
	uart->parent.read 	    = rt_uart_read;
	uart->parent.write      = rt_uart_write;
	uart->parent.control    = RT_NULL;
	uart->parent.user_data  = RT_NULL;

	rt_device_register(&uart->parent,
		"uart", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_INT_RX);
}

#endif

/******************************************************************************
**                            End Of File
******************************************************************************/
