/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __RT_HW_SERIAL_H__
#define __RT_HW_SERIAL_H__

#include <rthw.h>
#include <rtthread.h>

#include "s3c24x0.h"

#define	USTAT_RCV_READY		0x01   	/* receive data ready */ 
#define	USTAT_TXB_EMPTY		0x02   	/* tx buffer empty */
#define BPS					115200	/* serial baudrate */

#define UART_RX_BUFFER_SIZE		64
#define UART_TX_BUFFER_SIZE		64

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
	volatile rt_uint32_t ulcon;
	volatile rt_uint32_t ucon;
	volatile rt_uint32_t ufcon;
	volatile rt_uint32_t umcon;
	volatile rt_uint32_t ustat;
	volatile rt_uint32_t urxb;
	volatile rt_uint32_t ufstat;
	volatile rt_uint32_t umstat;
	volatile rt_uint32_t utxh;	
	volatile rt_uint32_t urxh;	
	volatile rt_uint32_t ubrd;
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
