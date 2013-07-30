/*
 * File      : serial.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
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
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-13     Bernard      first version
 * 2009-04-20     yi.qiu       modified according bernard's stm32 version
 * 2010-10-6      wangmeng     added sep4020 surpport
 * 2013-7-15      Peng Fan     Modified from sep4020
 */

#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <sep6200.h>

#define	USTAT_RCV_READY		0x01   	/* receive data ready */
#define USTAT_OVERRUN		0x02	/* overrun */
#define USTAT_PARITY_ERR	0x04	/* parity error */
#define USTAT_FRAME_ERROR	0x08	/* frame error */
#define USTAT_BREAK		0x10	/* break */
#define	USTAT_TXB_EMPTY		0x40   	/* tx buffer empty */
#define USTAT_RCV_ERR		0x80	/* receive error */

#define BPS					115200	/* serial baudrate */

#define UART_RX_BUFFER_SIZE		64
#define UART_TX_BUFFER_SIZE		64

/*For sep6200's uart have several secondary function*/
/*we use union to decribe it*/

union dlbl_fifo
{
	rt_uint32_t dlbl;
	rt_uint32_t rxfifo;
	rt_uint32_t txfifo;
};

union dlbh_ier
{
	rt_uint32_t dlbh;
	rt_uint32_t ier;
};

union iir_fcr
{
	rt_uint32_t iir;
	rt_uint32_t fcr;
};

struct serial_int_rx
{
	rt_uint8_t  rx_buffer[UART_RX_BUFFER_SIZE];
	rt_uint32_t read_index, save_index;
};

struct serial_int_tx
{
	rt_uint8_t  tx_buffer[UART_TX_BUFFER_SIZE];
	rt_uint32_t write_index, save_index;
};

typedef struct uartport
{
	union dlbl_fifo dlbl_fifo;
	union dlbh_ier	dlbh_ier;
	union iir_fcr	iir_fcr;
	rt_uint32_t lcr;
	rt_uint32_t mcr;
	rt_uint32_t lsr;
	rt_uint32_t msr;
}uartport;

struct serial_device
{
	uartport* uart_device;

	/* rx structure */
	struct serial_int_rx* int_rx;

	/* tx structure */
	struct serial_int_tx* int_tx;
};

rt_err_t rt_hw_serial_register(rt_device_t device, const char* name, rt_uint32_t flag, struct serial_device *serial);

void rt_hw_serial_isr(rt_device_t device);

#endif
