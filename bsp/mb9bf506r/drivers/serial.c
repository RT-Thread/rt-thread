/*
 * File      : serial.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-13     Bernard      first version
 * 2011-05-15     lgnq         modified according bernard's implementation.
 */

#include <rtthread.h>

#include "serial.h"

/**
 * @addtogroup FM3 MB9B500
 */

/*@{*/

/* RT-Thread Device Interface */

/**
 * This function initializes serial
 */
static rt_err_t rt_serial_init(rt_device_t dev)
{
	struct serial_device *uart = (struct serial_device*)dev->user_data;

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

/* save a char to serial buffer */
static void rt_serial_savechar(struct serial_device *uart, char ch)
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

static rt_err_t rt_serial_open(rt_device_t dev, rt_uint16_t oflag)
{
	struct serial_device *uart;
	
	RT_ASSERT(dev != RT_NULL);
	uart = (struct serial_device*)dev->user_data;

	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* enable interrupt */
		UART_ENABLE_IRQ(uart->rx_irq);
	}

	return RT_EOK;
}

static rt_err_t rt_serial_close(rt_device_t dev)
{	
	struct serial_device *uart;
	
	RT_ASSERT(dev != RT_NULL);
	uart = (struct serial_device*)dev->user_data;

	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* disable interrupt */
		UART_DISABLE_IRQ(uart->rx_irq);
	}

	return RT_EOK;
}

static rt_size_t rt_serial_read(rt_device_t dev, rt_off_t pos, void *buffer, 
                                 rt_size_t size)
{
	rt_uint8_t *ptr;
	rt_err_t err_code;
	struct serial_device *uart;
	
	ptr = buffer;
	err_code = RT_EOK;
	uart = (struct serial_device*)dev->user_data;

	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		rt_base_t level;

		/* interrupt mode Rx */
		while (size)
		{
			if (uart->int_rx->read_index != uart->int_rx->save_index)
			{
				*ptr++ = uart->int_rx->rx_buffer[uart->int_rx->read_index];
				size --;

				/* disable interrupt */
				level = rt_hw_interrupt_disable();

				uart->int_rx->read_index ++;
				if (uart->int_rx->read_index >= UART_RX_BUFFER_SIZE)
					uart->int_rx->read_index = 0;

				/* enable interrupt */
				rt_hw_interrupt_enable(level);
			}
			else
			{
				/* set error code */
				err_code = -RT_EEMPTY;
				break;
			}
		}
	}
	else
	{
		/* polling mode */
		while ((rt_uint32_t)ptr - (rt_uint32_t)buffer < size)
		{
			while (uart->uart_device->SSR & SSR_RDRF)
			{
				*ptr = uart->uart_device->RDR & 0xff;
				ptr ++;
			}
		}
	}

	/* set error code */
	rt_set_errno(err_code);
	
	return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static rt_size_t rt_serial_write(rt_device_t dev, rt_off_t pos, 
                                 const void *buffer, rt_size_t size)
{
	rt_uint8_t *ptr;
	rt_err_t err_code;
	struct serial_device *uart;
	
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
				while (!(uart->uart_device->SSR & SSR_TDRE));
				uart->uart_device->TDR = '\r';
			}

			while (!(uart->uart_device->SSR & SSR_TDRE));
			uart->uart_device->TDR = (*ptr & 0x1FF);

			++ptr;
			--size;
		}
	}	

	/* set error code */
	rt_set_errno(err_code);
	
	return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static rt_err_t rt_serial_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	RT_ASSERT(dev != RT_NULL);

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
 * serial register
 */
rt_err_t rt_hw_serial_register(rt_device_t device, const char *name, 
                               rt_uint32_t flag, struct serial_device *serial)
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
	return rt_device_register(device, name, flag);
}

/* ISR for serial interrupt */
void rt_hw_serial_isr(rt_device_t device)
{
	struct serial_device *uart = (struct serial_device*)device->user_data;
	
	/* interrupt mode receive */	
	RT_ASSERT(device->flag & RT_DEVICE_FLAG_INT_RX);

	/* save on rx buffer */
	while (uart->uart_device->SSR & SSR_RDRF)
	{
		rt_serial_savechar(uart, uart->uart_device->RDR & 0xff);
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

#if (defined(RT_USING_UART0_0) || defined(RT_USING_UART0_1))
/* UART0 device driver structure */
struct serial_int_rx uart0_int_rx;
struct serial_device uart0 =
{
	FM3_MFS0_UART,
	MFS0RX_IRQn,
	MFS0TX_IRQn,
	&uart0_int_rx,
	RT_NULL
};
struct rt_device uart0_device;

void MFS0RX_IRQHandler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();
	rt_hw_serial_isr(&uart0_device);
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif

#if (defined(RT_USING_UART1_0) || defined(RT_USING_UART1_1))
/* UART1 device driver structure */
struct serial_int_rx uart1_int_rx;
struct serial_device uart1 =
{
	FM3_MFS1_UART,
	MFS1RX_IRQn,
	MFS1TX_IRQn,
	&uart1_int_rx,
	RT_NULL
};
struct rt_device uart1_device;

void MFS1RX_IRQHandler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();
	rt_hw_serial_isr(&uart1_device);
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif

#if (defined(RT_USING_UART2_0) || defined(RT_USING_UART2_1) || defined(RT_USING_UART2_2))
/* UART2 device driver structure */
struct serial_int_rx uart2_int_rx;
struct serial_device uart2 =
{
	FM3_MFS2_UART,
	MFS2RX_IRQn,
	MFS2TX_IRQn,
	&uart2_int_rx,
	RT_NULL
};
struct rt_device uart2_device;

void MFS2RX_IRQHandler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();
	rt_hw_serial_isr(&uart2_device);
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif

#if (defined(RT_USING_UART3_0) || defined(RT_USING_UART3_1) || defined(RT_USING_UART3_2))
/* UART3 device driver structure */
struct serial_int_rx uart3_int_rx;
struct serial_device uart3 =
{
	FM3_MFS3_UART,
	MFS3RX_IRQn,
	MFS3TX_IRQn,
	&uart3_int_rx,
	RT_NULL
};
struct rt_device uart3_device;

void MFS3RX_IRQHandler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();
	rt_hw_serial_isr(&uart3_device);
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif

void uart_pin_setup(void)
{
#if defined(RT_USING_UART0_0)
	/* Set UART Ch0 Port, SIN0_0(P21), SOT0_0(P22) */
	FM3_GPIO->PFR2_f.P1 = 1;
	FM3_GPIO->PFR2_f.P2 = 1;
	FM3_GPIO->EPFR07_f.SIN0S0 = 1;
	FM3_GPIO->EPFR07_f.SIN0S1 = 0;
	FM3_GPIO->EPFR07_f.SOT0B0 = 1;
	FM3_GPIO->EPFR07_f.SOT0B1 = 0;
#elif defined(RT_USING_UART0_1)
	/* Set UART Ch0 Port, SIN0_1(P14), SOT0_1(P15) */
	FM3_GPIO->PFR1_f.P4 = 1;
	FM3_GPIO->PFR1_f.P5 = 1;
	FM3_GPIO->EPFR07_f.SIN0S0 = 0;
	FM3_GPIO->EPFR07_f.SIN0S1 = 1;
	FM3_GPIO->EPFR07_f.SOT0B0 = 0;
	FM3_GPIO->EPFR07_f.SOT0B1 = 1;
#endif

#if defined(RT_USING_UART1_0)
	/* Set UART Ch1 Port, SIN1_0(P56), SOT1_0(P57) */
	FM3_GPIO->PFR5_f.P6 = 1;
	FM3_GPIO->PFR5_f.P7 = 1;
	FM3_GPIO->EPFR07_f.SIN1S0 = 1;
	FM3_GPIO->EPFR07_f.SIN1S1 = 0;
	FM3_GPIO->EPFR07_f.SOT1B0 = 1;
	FM3_GPIO->EPFR07_f.SOT1B1 = 0;
#elif defined(RT_USING_UART1_1)
	/* Set UART Ch1 Port, SIN1_1(P11), SOT1_1(P12) */
	FM3_GPIO->PFR1_f.P1 = 1;
	FM3_GPIO->PFR1_f.P2 = 1;
	FM3_GPIO->EPFR07_f.SIN1S0 = 0;
	FM3_GPIO->EPFR07_f.SIN1S1 = 1;
	FM3_GPIO->EPFR07_f.SOT1B0 = 0;
	FM3_GPIO->EPFR07_f.SOT1B1 = 1;
#endif

#if defined(RT_USING_UART2_0)
	/* Set UART Ch2 Port, SIN2_0(P72), SOT2_0(P73) */
	FM3_GPIO->PFR7_f.P2 = 1;
	FM3_GPIO->PFR7_f.P3 = 1;
	FM3_GPIO->EPFR07_f.SIN2S0 = 1;
	FM3_GPIO->EPFR07_f.SIN2S1 = 0;
	FM3_GPIO->EPFR07_f.SOT2B0 = 1;
	FM3_GPIO->EPFR07_f.SOT2B1 = 0;
#elif defined(RT_USING_UART2_1)
	/* Set UART Ch2 Port, SIN2_1(P24), SOT2_1(P25) */
	FM3_GPIO->PFR2_f.P4 = 1;
	FM3_GPIO->PFR2_f.P5 = 1;
	FM3_GPIO->EPFR07_f.SIN2S0 = 0;
	FM3_GPIO->EPFR07_f.SIN2S1 = 1;
	FM3_GPIO->EPFR07_f.SOT2B0 = 0;
	FM3_GPIO->EPFR07_f.SOT2B1 = 1;
#elif defined(RT_USING_UART2_2)
	/* Set UART Ch2 Port, SIN2_2(P17), SOT2_2(P18) */
	FM3_GPIO->PFR1_f.P7 = 1;
	FM3_GPIO->PFR1_f.P8 = 1;
	FM3_GPIO->EPFR07_f.SIN2S0 = 1;
	FM3_GPIO->EPFR07_f.SIN2S1 = 1;
	FM3_GPIO->EPFR07_f.SOT2B0 = 1;
	FM3_GPIO->EPFR07_f.SOT2B1 = 1;
#endif

#if defined(RT_USING_UART3_0)
	/* Set UART Ch3 Port, SIN3_0(P66), SOT3_0(P67) */
	FM3_GPIO->PFR6_f.P6 = 1;
	FM3_GPIO->PFR6_f.P7 = 1;
	FM3_GPIO->EPFR07_f.SIN3S0 = 1;
	FM3_GPIO->EPFR07_f.SIN3S1 = 0;
	FM3_GPIO->EPFR07_f.SOT3B0 = 1;
	FM3_GPIO->EPFR07_f.SOT3B1 = 0;
#elif defined(RT_USING_UART3_1)
	/* Set UART Ch3 Port, SIN3_1(P50), SOT3_1(P51) */
	FM3_GPIO->PFR5_f.P0 = 1;
	FM3_GPIO->PFR5_f.P1 = 1;
	FM3_GPIO->EPFR07_f.SIN3S0 = 0;
	FM3_GPIO->EPFR07_f.SIN3S1 = 1;
	FM3_GPIO->EPFR07_f.SOT3B0 = 0;
	FM3_GPIO->EPFR07_f.SOT3B1 = 1;
#elif defined(RT_USING_UART3_2)
	/* Set UART Ch3 Port, SIN3_2(P48), SOT3_2(P49) */
	FM3_GPIO->PFR4_f.P8 = 1;
	FM3_GPIO->PFR4_f.P9 = 1;
	FM3_GPIO->EPFR07_f.SIN3S0 = 1;
	FM3_GPIO->EPFR07_f.SIN3S1 = 1;
	FM3_GPIO->EPFR07_f.SOT3B0 = 1;
	FM3_GPIO->EPFR07_f.SOT3B1 = 1;
#endif

#if defined(RT_USING_UART4_0)
	/* Set UART Ch4 Port, SIN4_0(P0A), SOT4_0(P0B), CTS4_0(P0E), RTS4_0(P0D) */
	FM3_GPIO->PFR0_f.PA = 1;
	FM3_GPIO->PFR0_f.PB = 1;
	FM3_GPIO->PFR0_f.PD = 1;
	FM3_GPIO->PFR0_f.PE = 1;
	FM3_GPIO->EPFR08_f.SIN4S0 = 1;
	FM3_GPIO->EPFR08_f.SIN4S1 = 0;
	FM3_GPIO->EPFR08_f.SOT4B0 = 1;
	FM3_GPIO->EPFR08_f.SOT4B1 = 0;
	FM3_GPIO->EPFR08_f.CTS4S0 = 1;
	FM3_GPIO->EPFR08_f.CTS4S1 = 0;
	FM3_GPIO->EPFR08_f.RTS4E0 = 1;
	FM3_GPIO->EPFR08_f.RTS4E1 = 0;
#elif defined(RT_USING_UART4_1)
	/* Set UART Ch4 Port, SIN4_1(P1A), SOT4_1(P1B), CTS4_1(P1D), RTS4_1(P1E) */
	FM3_GPIO->PFR1_f.PA = 1;
	FM3_GPIO->PFR1_f.PB = 1;
	FM3_GPIO->PFR1_f.PD = 1;
	FM3_GPIO->PFR1_f.PE = 1;
	FM3_GPIO->EPFR08_f.SIN4S0 = 0;
	FM3_GPIO->EPFR08_f.SIN4S1 = 1;
	FM3_GPIO->EPFR08_f.SOT4B0 = 0;
	FM3_GPIO->EPFR08_f.SOT4B1 = 1;
	FM3_GPIO->EPFR08_f.CTS4S0 = 0;
	FM3_GPIO->EPFR08_f.CTS4S1 = 1;
	FM3_GPIO->EPFR08_f.RTS4E0 = 0;
	FM3_GPIO->EPFR08_f.RTS4E1 = 1;
#elif defined(RT_USING_UART4_2)
	/* Set UART Ch4 Port, SIN4_2(P05), SOT4_2(P06), CTS4_2(P08), RTS4_2(P09)*/
	FM3_GPIO->PFR0_f.P5 = 1;
	FM3_GPIO->PFR0_f.P6 = 1;
	FM3_GPIO->PFR0_f.P8 = 1;
	FM3_GPIO->PFR0_f.P9 = 1;
	FM3_GPIO->EPFR08_f.SIN4S0 = 1;
	FM3_GPIO->EPFR08_f.SIN4S1 = 1;
	FM3_GPIO->EPFR08_f.SOT4B0 = 1;
	FM3_GPIO->EPFR08_f.SOT4B1 = 1;
	FM3_GPIO->EPFR08_f.CTS4S0 = 1;
	FM3_GPIO->EPFR08_f.CTS4S1 = 1;
	FM3_GPIO->EPFR08_f.RTS4E0 = 1;
	FM3_GPIO->EPFR08_f.RTS4E1 = 1;
#endif

#if defined(RT_USING_UART5_0)
	/* Set UART Ch5 Port, SIN5_0(P60), SOT5_0(P61) */
	FM3_GPIO->PFR6_f.P0 = 1;
	FM3_GPIO->PFR6_f.P1 = 1;
	FM3_GPIO->EPFR08_f.SIN5S0 = 1;
	FM3_GPIO->EPFR08_f.SIN5S1 = 0;
	FM3_GPIO->EPFR08_f.SOT5B0 = 1;
	FM3_GPIO->EPFR08_f.SOT5B1 = 0;
#elif defined(RT_USING_UART5_1)
	/* Set UART Ch5 Port, SIN5_1(P63), SOT5_1(P64) */
	FM3_GPIO->PFR6_f.P3 = 1;
	FM3_GPIO->PFR6_f.P4 = 1;
	FM3_GPIO->EPFR08_f.SIN5S0 = 0;
	FM3_GPIO->EPFR08_f.SIN5S1 = 1;
	FM3_GPIO->EPFR08_f.SOT5B0 = 0;
	FM3_GPIO->EPFR08_f.SOT5B1 = 1;
#elif defined(RT_USING_UART5_2)
	/* Set UART Ch5 Port, SIN5_2(P36), SOT5_2(P37) */
	FM3_GPIO->PFR3_f.P6 = 1;
	FM3_GPIO->PFR3_f.P7 = 1;
	FM3_GPIO->EPFR08_f.SIN5S0 = 1;
	FM3_GPIO->EPFR08_f.SIN5S1 = 1;
	FM3_GPIO->EPFR08_f.SOT5B0 = 1;
	FM3_GPIO->EPFR08_f.SOT5B1 = 1;
#endif

#if defined(RT_USING_UART6_0)
	/* Set UART Ch6 Port, SIN6_0(P53), SOT6_0(P54) */
	FM3_GPIO->PFR5_f.P3 = 1;
	FM3_GPIO->PFR5_f.P4 = 1;
	FM3_GPIO->EPFR08_f.SIN6S0 = 1;
	FM3_GPIO->EPFR08_f.SIN6S1 = 0;
	FM3_GPIO->EPFR08_f.SOT6B0 = 1;
	FM3_GPIO->EPFR08_f.SOT6B1 = 0;
#elif defined(RT_USING_UART6_1)
	/* Set UART Ch6 Port, SIN6_1(P33), SOT6_1(P32) */
	FM3_GPIO->PFR3_f.P2 = 1;
	FM3_GPIO->PFR3_f.P3 = 1;
	FM3_GPIO->EPFR08_f.SIN6S0 = 0;
	FM3_GPIO->EPFR08_f.SIN6S1 = 1;
	FM3_GPIO->EPFR08_f.SOT6B0 = 0;
	FM3_GPIO->EPFR08_f.SOT6B1 = 1;
#endif

#if defined(RT_USING_UART7_0)
	/* Set UART Ch7 Port, SIN7_0(P59), SOT7_0(P5A) */
	FM3_GPIO->PFR5_f.P9 = 1;
	FM3_GPIO->PFR5_f.PA = 1;
	FM3_GPIO->EPFR08_f.SIN7S0 = 1;
	FM3_GPIO->EPFR08_f.SIN7S1 = 0;
	FM3_GPIO->EPFR08_f.SOT7B0 = 1;
	FM3_GPIO->EPFR08_f.SOT7B1 = 0;
#elif defined(RT_USING_UART7_1)
	/* Set UART Ch7 Port, SIN7_1(P4E), SOT7_1(P4D) */
	FM3_GPIO->PFR4_f.PD = 1;
	FM3_GPIO->PFR4_f.PE = 1;
	FM3_GPIO->EPFR08_f.SIN7S0 = 0;
	FM3_GPIO->EPFR08_f.SIN7S1 = 1;
	FM3_GPIO->EPFR08_f.SOT7B0 = 0;
	FM3_GPIO->EPFR08_f.SOT7B1 = 1;
#endif
}

void rt_hw_serial_init(void)
{
	uart_pin_setup();

#if (defined(RT_USING_UART0_0) || defined(RT_USING_UART0_1))
	/* initialize UART0 */
	uart0.uart_device->SMR	= SMR_MD_UART | SMR_SOE;
	uart0.uart_device->BGR	= (40000000UL + (BPS/2))/BPS - 1;
	uart0.uart_device->ESCR	= ESCR_DATABITS_8;
	uart0.uart_device->SCR	= SCR_RXE | SCR_TXE | SCR_RIE;

	/* register UART0 device */
	rt_hw_serial_register(&uart0_device, 
		"uart0", 
		RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
		&uart0);
#endif

#if (defined(RT_USING_UART1_0) || defined(RT_USING_UART1_1))
	/* initialize UART1 */
	uart1.uart_device->SMR	= SMR_MD_UART | SMR_SOE;
	uart1.uart_device->BGR	= (40000000UL + (BPS/2))/BPS - 1;
	uart1.uart_device->ESCR	= ESCR_DATABITS_8;
	uart1.uart_device->SCR	= SCR_RXE | SCR_TXE | SCR_RIE;

	/* register UART1 device */
	rt_hw_serial_register(&uart1_device,
		"uart1",
		RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
		&uart1);
#endif

#if (defined(RT_USING_UART2_0) || defined(RT_USING_UART2_1) || defined(RT_USING_UART2_2))
	/* initialize UART2 */
	uart2.uart_device->SMR = SMR_MD_UART | SMR_SOE;
	uart2.uart_device->BGR = (40000000UL + (BPS/2))/BPS - 1;
	uart2.uart_device->ESCR = ESCR_DATABITS_8;
	uart2.uart_device->SCR = SCR_RXE | SCR_TXE | SCR_RIE;

	/* register UART2 device */
	rt_hw_serial_register(&uart2_device, 
		"uart2", 
		RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
		&uart2);
#endif

#if (defined(RT_USING_UART3_0) || defined(RT_USING_UART3_1) || defined(RT_USING_UART3_2))
	/* initialize UART3 */
	uart3.uart_device->SMR = SMR_MD_UART | SMR_SOE;
	uart3.uart_device->BGR = (40000000UL + (BPS/2))/BPS - 1;
	uart3.uart_device->ESCR = ESCR_DATABITS_8;
	uart3.uart_device->SCR = SCR_RXE | SCR_TXE | SCR_RIE;

	/* register UART3 device */
	rt_hw_serial_register(&uart3_device,
		"uart3",
		RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
		&uart3);
#endif
}

/*@}*/
