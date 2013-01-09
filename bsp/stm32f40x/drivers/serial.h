/*
 * File      : serial.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first version
 * 2010-03-29     Bernard      remove interrupt tx and DMA rx mode.
 */
#ifndef __RT_HW_SERIAL_H__
#define __RT_HW_SERIAL_H__

#include <rthw.h>
#include <rtthread.h>

/* STM32F40x library definitions */
#include <stm32f4xx.h>

#define UART_RX_BUFFER_SIZE		64
#define UART_TX_DMA_NODE_SIZE	4

/* data node for Tx Mode */
struct stm32_serial_data_node
{
	rt_uint8_t *data_ptr;
	rt_size_t  data_size;
	struct stm32_serial_data_node *next, *prev;
};
struct stm32_serial_dma_tx
{
	/* DMA Channel */
	DMA_Stream_TypeDef* dma_channel;

	/* data list head and tail */
	struct stm32_serial_data_node *list_head, *list_tail;

	/* data node memory pool */
	struct rt_mempool data_node_mp;
	rt_uint8_t data_node_mem_pool[UART_TX_DMA_NODE_SIZE *
		(sizeof(struct stm32_serial_data_node) + sizeof(void*))];
};

struct stm32_serial_int_rx
{
	rt_uint8_t  rx_buffer[UART_RX_BUFFER_SIZE];
	rt_uint32_t read_index, save_index;
};

struct stm32_serial_device
{
	USART_TypeDef* uart_device;

	/* rx structure */
	struct stm32_serial_int_rx* int_rx;

	/* tx structure */
	struct stm32_serial_dma_tx* dma_tx;
};

rt_err_t rt_hw_serial_register(rt_device_t device, const char* name, rt_uint32_t flag, struct stm32_serial_device *serial);

void rt_hw_serial_isr(rt_device_t device);
void rt_hw_serial_dma_tx_isr(rt_device_t device);

#endif
