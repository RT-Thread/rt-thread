/*
 * File      : serial.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-02-05     Bernard      first version
 * 2009-10-25     Bernard      fix rt_serial_read bug when there is no data
 *                             in the buffer.
 * 2010-03-29     Bernard      cleanup code.
 * 2010-06-14     zchong       for sep4020
 */

#include "serial.h"

/**
 * @addtogroup SEP4020
 */
/*@{*/

/* RT-Thread Device Interface */
static rt_err_t rt_serial_init (rt_device_t dev)
{
	struct serial_device* uart = (struct serial_device*) dev->user_data;

	if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
	{

		if (dev->flag & RT_DEVICE_FLAG_INT_RX)
		{
			rt_memset(uart->int_rx->rx_buffer, 0, 
				sizeof(uart->int_rx->rx_buffer));
			uart->int_rx->read_index = uart->int_rx->save_index = 0;
		}
		
		if (dev->flag & RT_DEVICE_FLAG_INT_TX)
		{
			rt_memset(uart->int_tx->tx_buffer, 0, 
				sizeof(uart->int_tx->tx_buffer));
			uart->int_tx->write_index = uart->int_tx->save_index = 0;
		}

		dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
	}

	return RT_EOK;
}

static rt_err_t rt_serial_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_serial_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_serial_read (rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_uint8_t* ptr;
	rt_err_t err_code;
	struct serial_device* uart;

	ptr = buffer;
	err_code = RT_EOK;
	uart = (struct serial_device*)dev->user_data;

	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* interrupt mode Rx */
		while (size)
		{
			rt_base_t level;

			/* disable interrupt */
			level = rt_hw_interrupt_disable();

			if (uart->int_rx->read_index != uart->int_rx->save_index)
			{
				/* read a character */
				*ptr++ = uart->int_rx->rx_buffer[uart->int_rx->read_index];
				size--;

				/* move to next position */
				uart->int_rx->read_index ++;
				if (uart->int_rx->read_index >= UART_RX_BUFFER_SIZE)
					uart->int_rx->read_index = 0;
			}
			else
			{
				/* set error code */
				err_code = -RT_EEMPTY;

				/* enable interrupt */
				rt_hw_interrupt_enable(level);
				break;
			}

			/* enable interrupt */
			rt_hw_interrupt_enable(level);
		}
	}
	else
	{
		/* polling mode */
		while ((rt_uint32_t)ptr - (rt_uint32_t)buffer < size)
		{
			while (uart->uart_device->lsr & USTAT_RCV_READY)
			{
				*ptr = uart->uart_device->dlbl_rxfifo_txfifo & 0xff;
				ptr ++;
			}
		}
	}

	/* set error code */
	rt_set_errno(err_code);
	return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}


static rt_size_t rt_serial_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_uint8_t* ptr;
	rt_err_t err_code;
	struct serial_device* uart;
	
	err_code = RT_EOK;
	ptr = (rt_uint8_t*)buffer;
	uart = (struct serial_device*)dev->user_data;

	if (dev->flag & RT_DEVICE_FLAG_INT_TX)
	{
		/* interrupt mode Tx */
		while (uart->int_tx->save_index != uart->int_tx->write_index)
		{
			/* save on tx buffer */
			uart->int_tx->tx_buffer[uart->int_tx->save_index] = *ptr++;
			
			-- size;

			/* move to next position */
			uart->int_tx->save_index ++;
			
			/* wrap save index */
			if (uart->int_tx->save_index >= UART_TX_BUFFER_SIZE)
				uart->int_tx->save_index = 0;
		}
		
		/* set error code */
		if (size > 0)
			err_code = -RT_EFULL;
	}
	else
	{
		/* polling mode */
		while (size)
		{
			/*
			 * to be polite with serial console add a line feed
			 * to the carriage return character
			 */
			if (*ptr == '\n' && (dev->flag & RT_DEVICE_FLAG_STREAM))
			{
				while (!(uart->uart_device->lsr & USTAT_TXB_EMPTY));
				uart->uart_device->dlbl_rxfifo_txfifo = '\r';
			}

			while (!(uart->uart_device->lsr & USTAT_TXB_EMPTY));
			uart->uart_device->dlbl_rxfifo_txfifo = (*ptr & 0x1FF);

			++ptr; --size;
		}
	}	

	/* set error code */
	rt_set_errno(err_code);
	
	return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static rt_err_t rt_serial_control (rt_device_t dev, rt_uint8_t cmd, void *args)
{
//	struct serial_device* uart;

	RT_ASSERT(dev != RT_NULL);

//	uart = (struct serial_device*)dev->private;
	switch (cmd)
	{
	case RT_DEVICE_CTRL_SUSPEND:
		/* suspend device */
		dev->flag |= RT_DEVICE_FLAG_SUSPENDED;
		break;

	case RT_DEVICE_CTRL_RESUME:
		/* resume device */
		dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;
		break;
	}

	return RT_EOK;
}

/*
 * serial register for SEP4020
 */
rt_err_t rt_hw_serial_register(rt_device_t device, const char* name, rt_uint32_t flag, struct serial_device *serial)
{
	RT_ASSERT(device != RT_NULL);


	device->type 		= RT_Device_Class_Char;
	device->rx_indicate = RT_NULL;
	device->tx_complete = RT_NULL;
	device->init 		= rt_serial_init;
	device->open		= rt_serial_open;
	device->close		= rt_serial_close;
	device->read 		= rt_serial_read;
	device->write 		= rt_serial_write;
	device->control 	= rt_serial_control;
	device->user_data	= serial;

	/* register a character device */
	return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR | flag);
}

/* ISR for serial interrupt */
void rt_hw_serial_isr(rt_device_t device)
{
	rt_base_t level;
	struct serial_device* uart = (struct serial_device*) device->user_data;
	
	/* interrupt mode receive */	
	RT_ASSERT(device->flag & RT_DEVICE_FLAG_INT_RX);

	/* save on rx buffer */
	while (uart->uart_device->lsr & USTAT_RCV_READY)
	{
		/* disable interrupt */
		level = rt_hw_interrupt_disable();

		uart->int_rx->rx_buffer[uart->int_rx->save_index] = uart->uart_device->dlbl_rxfifo_txfifo & 0xff;
		uart->int_rx->save_index ++;
		if (uart->int_rx->save_index >= UART_RX_BUFFER_SIZE)
			uart->int_rx->save_index = 0;
	
		/* if the next position is read index, discard this 'read char' */
		if (uart->int_rx->save_index == uart->int_rx->read_index)
		{
			uart->int_rx->read_index ++;
			if (uart->int_rx->read_index >= UART_RX_BUFFER_SIZE)
				uart->int_rx->read_index = 0;
		}

		/* enable interrupt */
		rt_hw_interrupt_enable(level);
	}

	/* invoke callback */
	if (device->rx_indicate != RT_NULL)
	{
		rt_size_t rx_length;
		
		/* get rx length */
		rx_length = uart->int_rx->read_index > uart->int_rx->save_index ?
			UART_RX_BUFFER_SIZE - uart->int_rx->read_index + uart->int_rx->save_index :
			uart->int_rx->save_index - uart->int_rx->read_index;

		device->rx_indicate(device, rx_length);
	}	
}


/*@}*/
