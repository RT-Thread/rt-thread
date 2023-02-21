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
 * 2009-05-14     Bernard      add RT-THread device interface
 * 2010-03-14     MingBai      US_IMR is read-only.
 * 2010-03-16     MingBai      Changed interrupt source mode to level sensitive.
 */

#include <rthw.h>
#include <rtthread.h>

#include "AT91SAM7X.h"
#include "serial.h"

/**
 * @addtogroup AT91SAM7X256
 */
/*@{*/
typedef volatile rt_uint32_t REG32;
struct rt_at91serial_hw
{
	REG32	 US_CR; 	// Control Register
	REG32	 US_MR; 	// Mode Register
	REG32	 US_IER; 	// Interrupt Enable Register
	REG32	 US_IDR; 	// Interrupt Disable Register
	REG32	 US_IMR; 	// Interrupt Mask Register
	REG32	 US_CSR; 	// Channel Status Register
	REG32	 US_RHR; 	// Receiver Holding Register
	REG32	 US_THR; 	// Transmitter Holding Register
	REG32	 US_BRGR; 	// Baud Rate Generator Register
	REG32	 US_RTOR; 	// Receiver Time-out Register
	REG32	 US_TTGR; 	// Transmitter Time-guard Register
	REG32	 Reserved0[5]; 	//
	REG32	 US_FIDI; 	// FI_DI_Ratio Register
	REG32	 US_NER; 	// Nb Errors Register
	REG32	 Reserved1[1]; 	//
	REG32	 US_IF; 	// IRDA_FILTER Register
	REG32	 Reserved2[44]; 	//
	REG32	 US_RPR; 	// Receive Pointer Register
	REG32	 US_RCR; 	// Receive Counter Register
	REG32	 US_TPR; 	// Transmit Pointer Register
	REG32	 US_TCR; 	// Transmit Counter Register
	REG32	 US_RNPR; 	// Receive Next Pointer Register
	REG32	 US_RNCR; 	// Receive Next Counter Register
	REG32	 US_TNPR; 	// Transmit Next Pointer Register
	REG32	 US_TNCR; 	// Transmit Next Counter Register
	REG32	 US_PTCR; 	// PDC Transfer Control Register
	REG32	 US_PTSR; 	// PDC Transfer Status Register
};

struct rt_at91serial
{
	struct rt_device parent;

	struct rt_at91serial_hw* hw_base;
	rt_uint16_t peripheral_id;
	rt_uint32_t baudrate;

	/* reception field */
	rt_uint16_t save_index, read_index;
	rt_uint8_t  rx_buffer[RT_UART_RX_BUFFER_SIZE];
};
#ifdef RT_USING_UART1
struct rt_at91serial serial1;
#endif
#ifdef RT_USING_UART2
struct rt_at91serial serial2;
#endif

static void rt_hw_serial_isr(int irqno, void* param)
{
	rt_base_t level;
	struct rt_device* device;
	struct rt_at91serial* serial = (struct rt_at91serial*)param;

	RT_ASSERT(serial != RT_NULL);

	/* get generic device object */
	device = (rt_device_t)serial;

	/* disable interrupt */
	level = rt_hw_interrupt_disable();

	/* get received character */
	serial->rx_buffer[serial->save_index] = serial->hw_base->US_RHR;

	/* move to next position */
	serial->save_index ++;
	if (serial->save_index >= RT_UART_RX_BUFFER_SIZE)
		serial->save_index = 0;

	/* if the next position is read index, discard this 'read char' */
	if (serial->save_index == serial->read_index)
	{
		serial->read_index ++;
		if (serial->read_index >= RT_UART_RX_BUFFER_SIZE)
			serial->read_index = 0;
	}

	/* enable interrupt */
	rt_hw_interrupt_enable(level);

	/* indicate to upper layer application */
	if (device->rx_indicate != RT_NULL)
		device->rx_indicate(device, 1);

	/* ack interrupt */
	AT91C_AIC_EOICR = 1;
}

static rt_err_t rt_serial_init (rt_device_t dev)
{
	rt_uint32_t bd;
	struct rt_at91serial* serial = (struct rt_at91serial*) dev;

	RT_ASSERT(serial != RT_NULL);
	/* must be US0 or US1 */
	RT_ASSERT((serial->peripheral_id == AT91C_ID_US0) ||
			  (serial->peripheral_id == AT91C_ID_US1));

	/* Enable Clock for USART */
	AT91C_PMC_PCER = 1 << serial->peripheral_id;

	/* Enable RxD0 and TxDO Pin */
	if (serial->peripheral_id == AT91C_ID_US0)
	{
		/* set pinmux */
		//AT91C_PIO_PDR = (1 << 5) | (1 << 6);
		AT91C_PIO_PDR = 1 | (1 << 1);  //fix bug 2010-3-9
	}
	else if (serial->peripheral_id == AT91C_ID_US1)
	{
		/* set pinmux */
		//AT91C_PIO_PDR = (1 << 21) | (1 << 22);
		AT91C_PIO_PDR = (1 << 5) | (1 << 6);  //fix bug 2010-3-9
	}

	serial->hw_base->US_CR = AT91C_US_RSTRX	    | 	/* Reset Receiver      */
							 AT91C_US_RSTTX		|	/* Reset Transmitter   */
							 AT91C_US_RXDIS		|	/* Receiver Disable    */
							 AT91C_US_TXDIS;		/* Transmitter Disable */

	serial->hw_base->US_MR = AT91C_US_USMODE_NORMAL |	/* Normal Mode */
							 AT91C_US_CLKS_CLOCK	|	/* Clock = MCK */
							 AT91C_US_CHRL_8_BITS	|	/* 8-bit Data  */
							 AT91C_US_PAR_NONE		|	/* No Parity   */
							 AT91C_US_NBSTOP_1_BIT;		/* 1 Stop Bit  */

	/* set baud rate divisor */
	bd =  ((MCK*10)/(serial->baudrate * 16));
	if ((bd % 10) >= 5) bd = (bd / 10) + 1;
	else bd /= 10;

	serial->hw_base->US_BRGR = bd;
	serial->hw_base->US_CR = AT91C_US_RXEN |	/* Receiver Enable     */
							 AT91C_US_TXEN;	    /* Transmitter Enable  */

	/* reset rx index */
	serial->save_index = 0;
	serial->read_index = 0;

	/* reset rx buffer */
	rt_memset(serial->rx_buffer, 0, RT_UART_RX_BUFFER_SIZE);

	return RT_EOK;
}

static rt_err_t rt_serial_open(rt_device_t dev, rt_uint16_t oflag)
{
	struct rt_at91serial *serial = (struct rt_at91serial*)dev;
	RT_ASSERT(serial != RT_NULL);

	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* enable UART rx interrupt */
		serial->hw_base->US_IER = 1 << 0; 		/* RxReady interrupt */
        // US_IMR is a READ-ONLY register!
		//serial->hw_base->US_IMR |= 1 << 0; 		/* umask RxReady interrupt */

		/* install UART handler */
		rt_hw_interrupt_install(serial->peripheral_id, rt_hw_serial_isr, serial, "uart");
		// SAM7X Datasheet 30.5.3:
		// It is notrecommended to use the USART interrupt line in edge sensitive mode
		//AT91C_AIC_SMR(serial->peripheral_id) = 5 | (0x01 << 5);
		AT91C_AIC_SMR(serial->peripheral_id) = 5;
		rt_hw_interrupt_umask(serial->peripheral_id);
	}

	return RT_EOK;
}

static rt_err_t rt_serial_close(rt_device_t dev)
{
	struct rt_at91serial *serial = (struct rt_at91serial*)dev;
	RT_ASSERT(serial != RT_NULL);

	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* disable interrupt */
		serial->hw_base->US_IDR = 1 << 0; 		/* RxReady interrupt */
		//serial->hw_base->US_IMR &= ~(1 << 0); 	/* mask RxReady interrupt */
	}

	serial->hw_base->US_CR = AT91C_US_RSTRX	    | 	/* Reset Receiver      */
							 AT91C_US_RSTTX		|	/* Reset Transmitter   */
							 AT91C_US_RXDIS		|	/* Receiver Disable    */
							 AT91C_US_TXDIS;		/* Transmitter Disable */

	return RT_EOK;
}

static rt_ssize_t rt_serial_read (rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_uint8_t* ptr;
	struct rt_at91serial *serial = (struct rt_at91serial*)dev;
	RT_ASSERT(serial != RT_NULL);

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
			if (serial->read_index != serial->save_index)
			{
				*ptr = serial->rx_buffer[serial->read_index];

				serial->read_index ++;
				if (serial->read_index >= RT_UART_RX_BUFFER_SIZE)
					serial->read_index = 0;
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
	else if (dev->flag & RT_DEVICE_FLAG_DMA_RX)
	{
		/* not support right now */
		RT_ASSERT(0);
	}
	else
	{
		/* poll mode */
		while (size)
		{
			/* Wait for Full Rx Buffer */
			while (!(serial->hw_base->US_CSR & AT91C_US_RXRDY));

			/* Read Character */
			*ptr = serial->hw_base->US_RHR;
			ptr ++;
			size --;
		}

		return (rt_size_t)ptr - (rt_size_t)buffer;
	}

	return 0;
}

static rt_ssize_t rt_serial_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_uint8_t* ptr;
	struct rt_at91serial *serial = (struct rt_at91serial*)dev;
	RT_ASSERT(serial != RT_NULL);

	ptr = (rt_uint8_t*) buffer;
	if (dev->open_flag & RT_DEVICE_OFLAG_WRONLY)
	{
		if (dev->flag & RT_DEVICE_FLAG_STREAM)
		{
			/* it's a stream mode device */
			while (size)
			{
				/* stream mode */
				if (*ptr == '\n')
				{
					while (!(serial->hw_base->US_CSR & AT91C_US_TXRDY));
					serial->hw_base->US_THR = '\r';
				}

				/* Wait for Empty Tx Buffer */
				while (!(serial->hw_base->US_CSR & AT91C_US_TXRDY));

				/* Transmit Character */
				serial->hw_base->US_THR = *ptr;
				ptr ++;
				size --;
			}
		}
		else
		{
			while (size)
			{
				/* Wait for Empty Tx Buffer */
				while (!(serial->hw_base->US_CSR & AT91C_US_TXRDY));

				/* Transmit Character */
				serial->hw_base->US_THR = *ptr;
				ptr ++;
				size --;
			}
		}
	}

	return (rt_size_t)ptr - (rt_size_t)buffer;
}

static rt_err_t rt_serial_control (rt_device_t dev, int cmd, void *args)
{
	return RT_EOK;
}

rt_err_t rt_hw_serial_init()
{
	rt_device_t device;

#ifdef RT_USING_UART1
	device = (rt_device_t) &serial1;

	/* init serial device private data */
	serial1.hw_base 		= (struct rt_at91serial_hw*)AT91C_BASE_US0;
	serial1.peripheral_id 	= AT91C_ID_US0;
	serial1.baudrate		= 115200;

	/* set device virtual interface */
	device->init 	= rt_serial_init;
	device->open 	= rt_serial_open;
	device->close 	= rt_serial_close;
	device->read 	= rt_serial_read;
	device->write 	= rt_serial_write;
	device->control = rt_serial_control;

	/* register uart1 on device subsystem */
	rt_device_register(device, "uart1", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
#endif

#ifdef RT_USING_UART2
	device = (rt_device_t) &serial2;

	serial2.hw_base 		= (struct rt_at91serial_hw*)AT91C_BASE_US1;
	serial2.peripheral_id 	= AT91C_ID_US1;
	serial2.baudrate		= 115200;

	/* set device virtual interface */
	device->init 	= rt_serial_init;
	device->open 	= rt_serial_open;
	device->close 	= rt_serial_close;
	device->read 	= rt_serial_read;
	device->write 	= rt_serial_write;
	device->control = rt_serial_control;

	/* register uart2 on device subsystem */
	rt_device_register(device, "uart2", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
#endif

	return RT_EOK;
}

/*@}*/
