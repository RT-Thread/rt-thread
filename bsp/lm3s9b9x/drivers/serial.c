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
 * 2009-06-11     Bernard      first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <inc/hw_uart.h>
#include <inc/hw_ints.h>
#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>
#include <driverlib/interrupt.h>

#include <driverlib/uart.h>
#include "board.h"

extern void rt_hw_interrupt_thread_switch(void);

#define RT_UART_RX_BUFFER_SIZE 64

/* LM3S serial device */
struct rt_lm3s_serial
{
	/* inherit from device */
	struct rt_device parent;

	rt_uint32_t hw_base;
	rt_uint32_t baudrate;

	/* reception field */
	rt_uint16_t save_index, read_index;
	rt_uint8_t  rx_buffer[RT_UART_RX_BUFFER_SIZE];
};

#ifdef RT_USING_UART1
struct rt_lm3s_serial serial1;
#endif
#ifdef RT_USING_UART2
struct rt_lm3s_serial serial2;
#endif

void rt_hw_serial_init(void);

void rt_hw_uart_isr(struct rt_lm3s_serial* serial)
{
    rt_device_t device;
    rt_uint32_t status;

    device = (struct rt_device*)serial;
    status = UARTIntStatus(serial->hw_base, true);

    /* clear interrupt status */
    UARTIntClear(serial->hw_base, status);

    if (device->flag & RT_DEVICE_FLAG_INT_RX)
    {
        char ch;
		rt_base_t level;

        while (UARTCharsAvail(serial->hw_base))
        {
            ch = UARTCharGetNonBlocking(serial->hw_base);

            /* disable interrupt */
			level = rt_hw_interrupt_disable();

			/* read character */
			serial->rx_buffer[serial->save_index] = ch;
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
        }

		/* invoke callback */
		if(device->rx_indicate != RT_NULL)
		{
		    rt_int32_t length;

		    length = serial->save_index - serial->read_index;
		    if (length < 0) length += RT_UART_RX_BUFFER_SIZE;
            device->rx_indicate(device, length);
		}
    }
}

#ifdef RT_USING_UART1
void rt_hw_uart_isr_1(int irqno)
{
	/* enter interrupt */
	rt_interrupt_enter();

	/* get serial device */
	rt_hw_uart_isr(&serial1);

	/* leave interrupt */
	rt_interrupt_leave();
	rt_hw_interrupt_thread_switch();
}
#endif

#ifdef RT_USING_UART2
void rt_hw_uart_isr_2(int irqno)
{
	/* enter interrupt */
	rt_interrupt_enter();

	/* get serial device */
	rt_hw_uart_isr(&serial2);

	/* leave interrupt */
	rt_interrupt_leave();
	rt_hw_interrupt_thread_switch();
}
#endif

/**
 * @addtogroup LM3S
 */
/*@{*/

static rt_err_t rt_serial_init (rt_device_t dev)
{
	return RT_EOK;
}

static rt_err_t rt_serial_open(rt_device_t dev, rt_uint16_t oflag)
{
	struct rt_lm3s_serial* serial;
	serial = (struct rt_lm3s_serial*) dev;

	RT_ASSERT(serial != RT_NULL);

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* enable interrupt */
        if (serial->hw_base == UART0_BASE)
            IntEnable(INT_UART0);
        else if (serial->hw_base == UART1_BASE)
            IntEnable(INT_UART1);

        UARTIntEnable(serial->hw_base, UART_INT_RX | UART_INT_RT);
    }

	return RT_EOK;
}

static rt_err_t rt_serial_close(rt_device_t dev)
{
	struct rt_lm3s_serial* serial;
	serial = (struct rt_lm3s_serial*) dev;

	RT_ASSERT(serial != RT_NULL);

	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* disable UART rx interrupt */
		UARTIntDisable(serial->hw_base, UART_INT_RX | UART_INT_RT);
	}

	return RT_EOK;
}

static rt_err_t rt_serial_control(rt_device_t dev, int cmd, void *args)
{
	return RT_EOK;
}

static rt_ssize_t rt_serial_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_uint8_t* ptr;
	struct rt_lm3s_serial *serial = (struct rt_lm3s_serial*)dev;
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

			ptr ++; size --;
		}

		return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
	}
	else if (dev->flag & RT_DEVICE_FLAG_DMA_RX)
	{
		/* not support right now */
		RT_ASSERT(0);
	}

	/* polling mode */
	while (size)
	{
	    *ptr = UARTCharGetNonBlocking(serial->hw_base);

	    ptr ++; size --;
	}

	return (rt_size_t)ptr - (rt_size_t)buffer;
}

static rt_ssize_t rt_serial_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	struct rt_lm3s_serial* serial;
	char *ptr;

	serial = (struct rt_lm3s_serial*) dev;
	if (dev->flag & RT_DEVICE_FLAG_INT_TX)
	{
		/* not support */
		RT_ASSERT(0);
	}
	else if (dev->flag & RT_DEVICE_FLAG_DMA_TX)
	{
		/* not support */
		RT_ASSERT(0);
	}

	/* polling write */
	ptr = (char *)buffer;

	if (dev->flag & RT_DEVICE_FLAG_STREAM)
	{
		/* stream mode */
		while (size)
		{
			if (*ptr == '\n')
				while (UARTCharPutNonBlocking(serial->hw_base, '\r') == false);

			while (UARTCharPutNonBlocking(serial->hw_base, *ptr) == false);

			ptr ++;
			size --;
		}
	}
	else
	{
		while (size)
		{
			while (UARTCharPutNonBlocking(serial->hw_base, *ptr) == false);

			ptr ++;
			size --;
		}
	}

	return (rt_size_t) ptr - (rt_size_t) buffer;
}

void rt_hw_serial_init(void)
{
	struct rt_lm3s_serial* serial;

#ifdef RT_USING_UART1
	serial = &serial1;

	serial->parent.type = RT_Device_Class_Char;

	serial->hw_base = UART0_BASE;
	serial->baudrate = 115200;

	rt_memset(serial->rx_buffer, 0, sizeof(serial->rx_buffer));
	serial->read_index = serial->save_index = 0;

	/* enable UART0 clock */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	/* set UART0 pinmux */
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	/* Configure the UART for 115,200, 8-N-1 operation. */
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), serial->baudrate,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));

	serial->parent.init 	= rt_serial_init;
	serial->parent.open 	= rt_serial_open;
	serial->parent.close    = rt_serial_close;
	serial->parent.read 	= rt_serial_read;
	serial->parent.write    = rt_serial_write;
	serial->parent.control  = rt_serial_control;
	serial->parent.user_data  = RT_NULL;

	rt_device_register(&serial->parent,
		"uart1", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
#endif

#ifdef RT_USING_UART2
	serial = &serial2;

	serial->parent.type = RT_Device_Class_Char;

	serial->hw_base = 0xE0010000;
	serial->baudrate = 115200;

	rt_memset(serial->rx_buffer, 0, sizeof(serial->rx_buffer));
	serial->read_index = serial->save_index = 0;

	serial->parent.init 	= rt_serial_init;
	serial->parent.open 	= rt_serial_open;
	serial->parent.close    = rt_serial_close;
	serial->parent.read 	= rt_serial_read;
	serial->parent.write    = rt_serial_write;
	serial->parent.control  = rt_serial_control;
	serial->parent.user_data  = RT_NULL;

	rt_device_register(&serial->parent,
		"uart2", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
#endif
}

/*@}*/
