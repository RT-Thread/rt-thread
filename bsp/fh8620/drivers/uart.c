/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#include <board.h>
#include <rtdevice.h>
#include "fh_arch.h"
#include "libraries/inc/fh_uart.h"


void rt_fh_uart_handler(int vector, void *param)
{
	int status;
	unsigned int ret;
	struct fh_uart *uart;
	unsigned int reg_status;
	rt_device_t dev = (rt_device_t)param;
	uart = (struct fh_uart *)dev->user_data;
	status = uart_get_iir_status(uart->uart_port);
	if (status & UART_IIR_NOINT)
	{
		return;
	}
	if(status & UART_IIR_THREMPTY){
		//first close tx isr
		uart_disable_irq(uart->uart_port,UART_IER_ETBEI);

		rt_hw_serial_isr((struct rt_serial_device *)dev, RT_SERIAL_EVENT_TX_DONE);
	}
	else if((status & UART_IIR_CHRTOUT)==UART_IIR_CHRTOUT){
		//bug....
		//if no data in rx fifo
		reg_status = uart_get_status(uart->uart_port);
		if((reg_status & 1<<3) == 0)
			ret = uart_getc(uart->uart_port);
	}
	else{
		rt_interrupt_enter();
		rt_hw_serial_isr((struct rt_serial_device *)dev, RT_SERIAL_EVENT_RX_IND);
		rt_interrupt_leave();
	}
}

/**
* UART device in RT-Thread
*/
static rt_err_t fh_uart_configure(struct rt_serial_device *serial,
                                struct serial_configure *cfg)
{
	int div;
	enum data_bits data_mode;
	enum stop_bits stop_mode;
	enum parity parity_mode;
	struct fh_uart *uart;

	RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
	uart = (struct fh_uart *)serial->parent.user_data;

	switch (cfg->data_bits)
	{
	case DATA_BITS_8:
		data_mode = UART_DATA_BIT8;
		break;
	case DATA_BITS_7:
		data_mode = UART_DATA_BIT7;
		break;
	case DATA_BITS_6:
		data_mode = UART_DATA_BIT6;
		break;
	case DATA_BITS_5:
		data_mode = UART_DATA_BIT5;
		break;
	default:
		data_mode = UART_DATA_BIT8;
		break;
	}

	switch (cfg->stop_bits)
	{
	case STOP_BITS_2:
		stop_mode = UART_STOP_BIT2;
		break;
	case STOP_BITS_1:
	default:
		stop_mode = UART_STOP_BIT1;
		break;
	}

	switch (cfg->parity)
	{
	case PARITY_ODD:
		parity_mode = UART_PARITY_ODD;
		break;
	case PARITY_EVEN:
		parity_mode = UART_PARITY_EVEN;
		break;
	case PARITY_NONE:
	default:
		parity_mode = UART_PARITY_NONE;
		break;
	}

    uart_disable_irq(uart->uart_port, UART_IER_ERBFI);

	uart_configure(uart->uart_port, data_mode,
					stop_mode, parity_mode,
					cfg->baud_rate, UART_CLOCK_FREQ);

	uart_enable_irq(uart->uart_port, UART_IER_ERBFI);

    return RT_EOK;
}

static rt_err_t fh_uart_control(struct rt_serial_device *serial,
                              int cmd, void *arg)
{
    struct fh_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct fh_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
		rt_hw_interrupt_mask(uart->irq);
		uart_disable_irq(uart->uart_port,UART_IER_ERBFI);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
		rt_hw_interrupt_umask(uart->irq);
		uart_enable_irq(uart->uart_port,UART_IER_ERBFI);
        break;
    }

    return RT_EOK;
}

static int fh_uart_putc(struct rt_serial_device *serial, char c)
{
	struct fh_uart *uart = serial->parent.user_data;
	unsigned int ret;
	ret = uart_get_status(uart->uart_port);
	if(serial->parent.open_flag & RT_DEVICE_FLAG_INT_TX){
		//RT_DEVICE_FLAG_INT_TX

		if(c == '\n'){
			fh_uart_putc(serial,'\r');
		}
		if(ret & UART_USR_TFNF){
			uart_putc(uart->uart_port, c);
			return 1;
		}
		//open tx isr here..
		uart_enable_irq(uart->uart_port,UART_IER_ETBEI);
	    return -1;
	}
	//poll mode
	else{

		while(!(uart_get_status(uart->uart_port) & UART_USR_TFNF))
			;
		uart_putc(uart->uart_port, c);
		return 1;


	}



}

static int fh_uart_getc(struct rt_serial_device *serial)
{
    int result;
	struct fh_uart *uart = serial->parent.user_data;

	if (uart_is_rx_ready(uart->uart_port))
	{
		result = uart_getc(uart->uart_port);
	}
	else
	{
		result = -1;
	}

    return result;
}

static const struct rt_uart_ops fh_uart_ops =
{
    fh_uart_configure,
    fh_uart_control,
    fh_uart_putc,
    fh_uart_getc,
};


#if defined(RT_USING_UART0)
static struct rt_serial_device serial0;
struct fh_uart uart0 = {
	(uart *)UART0_REG_BASE,
	UART0_IRQn
};

#endif

#if defined(RT_USING_UART1)
static struct rt_serial_device serial1;
struct fh_uart uart1 = {
	(uart *)UART1_REG_BASE,
	UART1_IRQn
};

#endif




/**
 * This function will handle init uart
 */
void rt_hw_uart_init(void)
{
	struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#if defined(RT_USING_UART0)
#if(0)
	serial0.ops = &fh_uart_ops;
	serial0.config = config;

	/* register vcom device */
	rt_hw_serial_register(&serial0, "uart0",
			RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_STANDALONE,
			&uart0);
	rt_hw_interrupt_install(uart0.irq, rt_fh_uart_handler,
			(void *)&(serial0.parent), "UART0");
	rt_hw_interrupt_umask(uart0.irq);
#endif
	serial0.ops = &fh_uart_ops;
	serial0.config = config;

	/* register vcom device */
	rt_hw_serial_register(&serial0, "uart0",
			RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM ,
			&uart0);
	rt_hw_interrupt_install(uart0.irq, rt_fh_uart_handler,
			(void *)&(serial0.parent), "UART0");
	rt_hw_interrupt_umask(uart0.irq);

#endif

#if defined(RT_USING_UART1)
	serial1.ops = &fh_uart_ops;
	serial1.config = config;

	/* register vcom device */
	rt_hw_serial_register(&serial1, "uart1",
			RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM ,
			&uart1);
	rt_hw_interrupt_install(uart1.irq, rt_fh_uart_handler,
			(void *)&(serial1.parent), "UART1");
	rt_hw_interrupt_umask(uart1.irq);

#endif

}


