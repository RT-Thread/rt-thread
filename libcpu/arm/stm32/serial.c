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
 * 2009-02-05     Bernard      first version
 */

#include "serial.h"
#include <stm32f10x_dma.h>

static void rt_serial_enable_dma(DMA_Channel_TypeDef* dma_channel, 
	rt_uint32_t address, rt_uint32_t size);

/**
 * @addtogroup STM32
 */
/*@{*/

/**
 * This function read a character from serial without interrupt enable mode
 *
 * @return the read char
 */
int rt_serial_getc(struct stm32_serial_device* uart)
{
	rt_base_t level;
	int ch = -1;
	
	/* disable interrupt */
	level = rt_hw_interrupt_disable();
	
	if (uart->int_rx->read_index != uart->int_rx->save_index)
	{
		ch = uart->int_rx->rx_buffer[uart->int_rx->read_index];

		uart->int_rx->read_index ++;
		if (uart->int_rx->read_index >= UART_RX_BUFFER_SIZE)
			uart->int_rx->read_index = 0;
	}
	
	/* enable interrupt */
	rt_hw_interrupt_enable(level);
	
	return ch;
}

/* save a char to serial buffer */
void rt_serial_savechar(struct stm32_serial_device* uart, char ch)
{
	rt_base_t level;
	
	/* disable interrupt */
	level = rt_hw_interrupt_disable();

	uart->int_rx->rx_buffer[uart->int_rx->save_index] = ch;
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

/**
 * This function will write a character to serial without interrupt enable mode
 *
 * @param c the char to write
 */
void rt_serial_putc(rt_device_t device, const char c)
{
	struct stm32_serial_device* uart = (struct stm32_serial_device*) device->private;

	/*
	 * to be polite with serial console add a line feed
	 * to the carriage return character
	 */
	if (c=='\n' && (device->flag & RT_DEVICE_FLAG_STREAM))
		rt_serial_putc(device, '\r');

	while (!(uart->uart_device->SR & USART_FLAG_TXE));
	uart->uart_device->DR = (c & 0x1FF);
}

/* RT-Thread Device Interface */
static rt_err_t rt_serial_init (rt_device_t dev)
{
	struct stm32_serial_device* uart = (struct stm32_serial_device*) dev->private;

	if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
	{
		if (dev->flag & RT_DEVICE_FLAG_INT_RX)
		{
			rt_memset(uart->int_rx->rx_buffer, 0, 
				sizeof(uart->int_rx->rx_buffer));
			uart->int_rx->read_index = 0;
			uart->int_rx->save_index = 0;
		}
		
		if (dev->flag & RT_DEVICE_FLAG_DMA_RX)
		{
			RT_ASSERT(uart->dma_rx->dma_channel != RT_NULL);
			uart->dma_rx->read_index = uart->dma_rx->read_descriptor = 0;
			uart->dma_rx->is_full = RT_FALSE;
		}
		
		if (dev->flag & RT_DEVICE_FLAG_INT_TX)
		{
			rt_memset(uart->int_tx->tx_buffer, 0, 
				sizeof(uart->int_tx->tx_buffer));
			uart->int_tx->write_index = uart->int_tx->save_index = 0;
		}
		
		if (dev->flag & RT_DEVICE_FLAG_DMA_TX)
		{
			RT_ASSERT(uart->dma_rx->dma_channel != RT_NULL);
			uart->dma_tx->list_head = uart->dma_tx->list_tail = RT_NULL;
		}

		/* Enable USART */
		USART_Cmd(uart->uart_device, ENABLE);

		dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
	}

	return RT_EOK;
}

static rt_err_t rt_serial_open(rt_device_t dev, rt_uint16_t oflag)
{
	struct stm32_serial_device* uart;
	
	RT_ASSERT(dev != RT_NULL);
	
	uart = (struct stm32_serial_device*)dev->private;

	if (dev->flag & RT_DEVICE_FLAG_DMA_RX)
	{
		/* enable Rx DMA */
		rt_serial_enable_dma(uart->dma_rx->dma_channel, 
			(rt_uint32_t)&(uart->dma_rx->rx_buffer[uart->dma_rx->save_descriptor][0]),
			UART_DMA_RX_BUFFER_SIZE);
	}
	
	return RT_EOK;
}

static rt_err_t rt_serial_close(rt_device_t dev)
{
	struct stm32_serial_device* uart;
	
	RT_ASSERT(dev != RT_NULL);
	
	uart = (struct stm32_serial_device*)dev->private;

	if (dev->flag & RT_DEVICE_FLAG_DMA_RX)
	{
		/* disable DMA */
		DMA_Cmd(uart->dma_rx->dma_channel, DISABLE);
	}
	return RT_EOK;
}

static rt_size_t rt_serial_read (rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_uint8_t* ptr;
	rt_err_t err_code;
	struct stm32_serial_device* uart;
	
	ptr = buffer;
	err_code = RT_EOK;
	uart = (struct stm32_serial_device*)dev->private;

	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		rt_int32_t ch;

		/* interrupt mode Rx */
		while (size)
		{
			/* get a character */
			ch = rt_serial_getc(uart);
			if (ch < 0)
			{
				/* set error code */
				err_code = -RT_EEMPTY;
			}
			else
			{
				*ptr++ = ch;
				size --;
			}
		}
	}
	else if (dev->flag & RT_DEVICE_FLAG_DMA_RX)
	{
		/* check queue empty */
		if ((uart->dma_rx->read_descriptor == uart->dma_rx->save_descriptor))
		{
			/* set error code */
			err_code = -RT_EEMPTY;
		}
		else 
		{
			/* read data */
			while ((rt_uint32_t)ptr - (rt_uint32_t)buffer < size)
			{
				/* read buffer */
				*ptr ++ = uart->dma_rx->
					rx_buffer[uart->dma_rx->read_descriptor][uart->dma_rx->read_index];
				
				/* move to next position */
				uart->dma_rx->read_index ++;
				
				/* wrap read index */
				if (uart->dma_rx->read_index >= UART_DMA_RX_BUFFER_SIZE)
				{
					/* wrap read index */
					uart->dma_rx->read_index  = 0;
					
					/* move to next read descriptor */
					uart->dma_rx->read_descriptor ++;
					/* wrap read descriptor */
					if (uart->dma_rx->read_descriptor >= UART_DMA_RX_DESCRIPTOR)
						uart->dma_rx->read_descriptor = 0;

					if (uart->dma_rx->is_full == RT_TRUE)
					{
						rt_uint32_t level;

						level = rt_hw_interrupt_disable();
						uart->dma_rx->save_descriptor ++;
						if (uart->dma_rx->save_descriptor >= UART_DMA_RX_DESCRIPTOR)
							uart->dma_rx->save_descriptor = 0;
						rt_hw_interrupt_enable(level);

						/* re-enable DMA to receive */
						rt_serial_enable_dma(uart->dma_rx->dma_channel, 
							(rt_uint32_t)&(uart->dma_rx->rx_buffer[uart->dma_rx->save_descriptor][0]),
							UART_DMA_RX_BUFFER_SIZE);
					}

					/* check queue empty */
					if ((uart->dma_rx->read_descriptor == uart->dma_rx->save_descriptor))
					{
						/* set error code */
						err_code = -RT_EEMPTY;
						break;
					}
				}
			}
		}
	}
	else
	{
		/* polling mode */
		while ((rt_uint32_t)ptr - (rt_uint32_t)buffer < size)
		{
			while (uart->uart_device->SR & USART_FLAG_RXNE)
			{
				*ptr = uart->uart_device->DR & 0xff;
				ptr ++;
			}
		}
	}

	/* set error code */
	rt_set_errno(err_code);
	return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static void rt_serial_enable_dma(DMA_Channel_TypeDef* dma_channel, 
	rt_uint32_t address, rt_uint32_t size)
{
	RT_ASSERT(dma_channel != RT_NULL);
	
	/* disable DMA */
	DMA_Cmd(dma_channel, DISABLE);

	/* set buffer address */
	dma_channel->CMAR = address;
	/* set size */
	dma_channel->CNDTR = size;
	
	/* enable DMA */
	DMA_Cmd(dma_channel, ENABLE);
}

static rt_size_t rt_serial_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_uint8_t* ptr;
	rt_err_t err_code;
	struct stm32_serial_device* uart;
	
	err_code = RT_EOK;
	ptr = (rt_uint8_t*)buffer;
	uart = (struct stm32_serial_device*)dev->private;

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
	else if (dev->flag & RT_DEVICE_FLAG_DMA_TX)
	{
		/* DMA mode Tx */
		
		/* allocate a data node */
		struct stm32_serial_data_node* data_node = 
			(struct stm32_serial_data_node*) rt_malloc (sizeof(struct stm32_serial_data_node));
		if (data_node == RT_NULL)
		{
			/* set error code */
			err_code = -RT_ENOMEM;
		}
		else
		{
			rt_uint32_t level;
			
			/* fill data node */
			data_node->data_ptr 	= ptr;
			data_node->data_size 	= size;
			
			/* insert to data link */
			data_node->next = RT_NULL;
			
			/* disable interrupt */
			level = rt_hw_interrupt_disable();

			data_node->prev = uart->dma_tx->list_tail;
			if (uart->dma_tx->list_tail != RT_NULL)
				uart->dma_tx->list_tail->next = data_node;
			uart->dma_tx->list_tail = data_node;
			
			if (uart->dma_tx->list_head == RT_NULL)
			{
				/* start DMA to transmit data */
				uart->dma_tx->list_head = data_node;
				
				/* Enable DMA Channel */
				rt_serial_enable_dma(uart->dma_tx->dma_channel, 
					(rt_uint32_t)uart->dma_tx->list_head->data_ptr, 
					uart->dma_tx->list_head->data_size);
			}

			/* enable interrupt */
			rt_hw_interrupt_enable(level);
		}
	}
	else
	{
		/* polling mode */
		while (size)
		{
			rt_serial_putc(dev, *ptr);
			++ptr; --size;
		}
	}	

	/* set error code */
	rt_set_errno(err_code);
	
	return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static rt_err_t rt_serial_control (rt_device_t dev, rt_uint8_t cmd, void *args)
{
	struct stm32_serial_device* uart;
	
	RT_ASSERT(dev != RT_NULL);

	uart = (struct stm32_serial_device*)dev->private;
	switch (cmd)
	{
	case RT_DEVICE_CTRL_SUSPEND:
		/* suspend device */
		dev->flag |= RT_DEVICE_FLAG_SUSPENDED;
		USART_Cmd(uart->uart_device, DISABLE);
		break;
	
	case RT_DEVICE_CTRL_RESUME:
		/* resume device */
		dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;
		USART_Cmd(uart->uart_device, ENABLE);
		break;
	}
	
	return RT_EOK;
}

/*
 * serial register for STM32 
 * support STM32F103VB and STM32F103ZE
 */
rt_err_t rt_hw_serial_register(rt_device_t device, const char* name, rt_uint32_t flag, struct stm32_serial_device *serial)
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
	device->private		= serial;

	/* register a character device */
	return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR | flag);
}

/* ISR for serial interrupt */
void rt_hw_serial_isr(rt_device_t device)
{
	struct stm32_serial_device* uart = (struct stm32_serial_device*) device->private;
	
	if(USART_GetITStatus(uart->uart_device, USART_IT_RXNE) != RESET)
	{
		/* interrupt mode receive */	
		RT_ASSERT(device->flag & RT_DEVICE_FLAG_INT_RX);

		/* save on rx buffer */
		while (uart->uart_device->SR & USART_FLAG_RXNE)
		{
			rt_serial_savechar(uart, uart->uart_device->DR & 0xff);
		}
		
		/* clear interrupt */
		USART_ClearITPendingBit(uart->uart_device, USART_IT_RXNE);

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
	
	if (USART_GetITStatus(uart->uart_device, USART_IT_TC) != RESET)
	{
		/* interrupt mode transmission */
		RT_ASSERT(device->flag & RT_DEVICE_FLAG_INT_TX);
		
		/* transmission completed */
		uart->int_tx->write_index ++;
		if (uart->int_tx->write_index >= UART_TX_BUFFER_SIZE)
			uart->int_tx->write_index = 0;

		/* clear interrupt */
		USART_ClearITPendingBit(uart->uart_device, USART_IT_RXNE);
		
		/* start next transmission */
		if (uart->int_tx->write_index <
			uart->int_tx->save_index)
		{
			uart->uart_device->DR = uart->int_tx
				->tx_buffer[uart->int_tx->write_index];
		}
	}
}

/* 
 * ISR for DMA mode Rx
 */
void rt_hw_serial_dma_rx_isr(rt_device_t device)
{
	rt_uint32_t next_descriptor;
	struct stm32_serial_device* uart = (struct stm32_serial_device*) device->private;
	
	/* DMA mode receive */	
	RT_ASSERT(device->flag & RT_DEVICE_FLAG_DMA_RX);
	
	/* invoke callback */
	if (device->rx_indicate != RT_NULL)
		device->rx_indicate(device, UART_DMA_RX_BUFFER_SIZE);

	next_descriptor = uart->dma_rx->save_descriptor;
	
	/* move to next descriptor */
	next_descriptor ++;
	if (next_descriptor >= UART_DMA_RX_DESCRIPTOR)
		next_descriptor = 0;
	
	if (next_descriptor != uart->dma_rx->read_descriptor)
	{
		uart->dma_rx->save_descriptor = next_descriptor;
		/* enable next DMA */
		rt_serial_enable_dma(uart->dma_rx->dma_channel, 
			(rt_uint32_t)&(uart->dma_rx->rx_buffer[uart->dma_rx->save_descriptor][0]),
			UART_DMA_RX_BUFFER_SIZE);
	}
	else
	{
		/* no descriptor yet, disable DMA */
		DMA_Cmd(uart->dma_rx->dma_channel, DISABLE);
		uart->dma_rx->is_full = RT_TRUE;
	}
}

/* 
 * ISR for DMA mode Tx
 */
void rt_hw_serial_dma_tx_isr(rt_device_t device)
{
	rt_uint32_t level;
	struct stm32_serial_data_node* data_node;
	struct stm32_serial_device* uart = (struct stm32_serial_device*) device->private;

	/* DMA mode receive */	
	RT_ASSERT(device->flag & RT_DEVICE_FLAG_DMA_TX);
	
	/* get the first data node */
	data_node = uart->dma_tx->list_head;
	RT_ASSERT(data_node != RT_NULL);
	
	/* invoke call to notify tx complete */
	if (device->tx_complete != RT_NULL)
		device->tx_complete(device, data_node->data_ptr);

	/* disable interrupt */
	level = rt_hw_interrupt_disable();
	
	/* remove list tail */
	uart->dma_tx->list_tail = data_node->prev;
	if (uart->dma_tx->list_tail == RT_NULL)
		uart->dma_tx->list_head = RT_NULL;

	/* enable interrupt */
	rt_hw_interrupt_enable(level);
	
	/* free data node memory */
	rt_free(data_node);
	
	if (uart->dma_tx->list_tail != RT_NULL)
	{
		/* transmit next data node */
		rt_serial_enable_dma(uart->dma_tx->dma_channel,
			(rt_uint32_t)uart->dma_tx->list_tail->data_ptr,
			uart->dma_tx->list_tail->data_size);
	}
	else
	{
		/* no data to be transmitted, disable DMA */
		DMA_Cmd(uart->dma_tx->dma_channel, DISABLE);
	}
}

/*@}*/
