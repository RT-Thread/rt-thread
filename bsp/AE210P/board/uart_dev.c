/*
 * File      : uart_dev.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2010-03-29     Bernard      remove interrupt Tx and DMA Rx mode
 * 2013-05-13     aozima       update for kehong-lingtai.
 */

#include "uart/uart.h"
#include "uart_dev.h"
#include "ae210p.h"
#include "board.h"
#include "bsp_hal.h"

#include "rtdevice.h"

#include "serial.h"

#define UART_ENABLE_IRQ(n)  hal_intc_irq_enable(n)
#define UART_DISABLE_IRQ(n) hal_intc_irq_disable(n)

struct uart_device
{
	uint32_t uart_base;
	uint32_t irq;
};

static rt_err_t __uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
	struct uart_device *uartDev = RT_NULL;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

	uartDev = (struct uart_device *)serial->parent.user_data;

	__drv_uart_init(uartDev->uart_base, cfg->baud_rate);

	// todo : enable FIFO threshold, enable rx & rx timeout(threshold) interrupt

    return RT_EOK;
}

static rt_err_t __uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
	struct uart_device *uartDev = RT_NULL;

	RT_ASSERT(serial != RT_NULL);
	uartDev = (struct uart_device *)serial->parent.user_data;

	switch (cmd)
	{
	case RT_DEVICE_CTRL_CLR_INT: /* disable rx irq */
		UART_DISABLE_IRQ(uartDev->irq);
		break;

	case RT_DEVICE_CTRL_SET_INT: /* enable rx irq */
		UART_ENABLE_IRQ(uartDev->irq);
		break;

	default:
		break;
	}

	return RT_EOK;
}

static int __uart_putc(struct rt_serial_device *serial, char c)
{
	struct uart_device *uartDev = RT_NULL;

	RT_ASSERT(serial != RT_NULL);

	uartDev = (struct uart_device *)serial->parent.user_data;

	__drv_uart_put_char(uartDev->uart_base, c); // Transmit Data

	return 1;
}

static int __uart_getc(struct rt_serial_device *serial)
{
	int ch = -1;
	struct uart_device *uartDev = RT_NULL;

	RT_ASSERT(serial != RT_NULL);
	uartDev = (struct uart_device *)serial->parent.user_data;

	ch = -1;

	if (__drv_uart_is_kbd_hit(uartDev->uart_base))
	{
		ch = __drv_uart_get_char(uartDev->uart_base) & 0x00FF;
	}

	return ch;
}

static const struct rt_uart_ops __uart_ops =
{
    __uart_configure,
	__uart_control,
	__uart_putc,
	__uart_getc,
	RT_NULL
};

#if RT_USING_UART01
struct uart_device uartDev01 =
{ // UART01 device driver structure
	UART1_BASE,
	IRQ_UART1_VECTOR
};

struct rt_serial_device serial01;

void URT01_IRQHandler(void)
{
	struct uart_device *uartDev = RT_NULL;
	
	uartDev = &uartDev01;

	rt_interrupt_enter(); /* enter interrupt */

//	if (uart->uart_device->Interrupt & ((1 << bsUART_TIMEOUT_INTENAB) | (1 << bsUART_RECEIVE_INTENAB))) // RX
//	{
//		rt_hw_serial_isr(&serial01, RT_SERIAL_EVENT_RX_IND);
//	}
//
//	if (uart->uart_device->Interrupt & (1 << bsUART_TRANSMIT_INTENAB)) // TX
//	{
//		;
//	}
//
//	/* clear all interrupt */
//	uart->uart_device->IntClear = (1 << bsUART_RECEIVE_INTENAB)
//									| (1 << bsUART_TRANSMIT_INTENAB)
//									| (1 << bsUART_TIMEOUT_INTENAB);

	rt_interrupt_leave(); /* leave interrupt */
}
#endif /* RT_USING_UART01 */

#if RT_USING_UART02
struct uart_device uartDev02 =
{ // UART02 device driver structure
	UART2_BASE,
	IRQ_UATR2_VECTOR
};

struct rt_serial_device serial02;

void URT02_IRQHandler(void)
{
	struct uart_device *uartDev = RT_NULL;

	uartDev = &uartDev02;

	rt_interrupt_enter(); /* enter interrupt */

	uartDev = uartDev;

	rt_interrupt_leave(); /* leave interrupt */
}
#endif /* RT_USING_UART02 */

void rt_hw_usart_init(void)
{
	struct uart_device *uartDev = RT_NULL;
	struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#if RT_USING_UART01
	uart = &uartDev01;
	config.baud_rate = BAUD_RATE_38400;

	serial01.ops    = &__uart_ops;
	serial01.config = config;

	// set interrupt priority level
	// disable interrupt

	// register UART01 device
	rt_hw_serial_register(&serial01, "uart01",
							RT_DEVICE_FLAG_RDWR /*| RT_DEVICE_FLAG_INT_RX*/,
							uartDev);
#endif /* RT_USING_UART01 */

#if RT_USING_UART02
	uartDev = &uartDev02;

	config.baud_rate = BAUD_RATE_38400;
	serial02.ops    = &__uart_ops;
	serial02.config = config;

	// set interrupt priority level
	// disable interrupt

	/* register UART02 device */
	rt_hw_serial_register(&serial02, "uart02",
							RT_DEVICE_FLAG_RDWR /*| RT_DEVICE_FLAG_INT_RX*/,
							uartDev);
	#endif /* RT_USING_UART02 */
}

