/*
 * File      : serial.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first version
 */
#ifndef __RT_HW_SERIAL_H__
#define __RT_HW_SERIAL_H__

#include <rthw.h>
#include <rtthread.h>

/* STM32F10x library definitions */
#include <stm32f10x.h>

#define UART_DMA_RX_DESCRIPTOR 	2
#define UART_DMA_RX_BUFFER_SIZE	16

#define UART_RX_BUFFER_SIZE		64
#define UART_TX_BUFFER_SIZE		64

struct stm32_serial_dma_rx
{
	DMA_Channel_TypeDef* dma_channel;
	rt_uint8_t  rx_buffer[UART_DMA_RX_DESCRIPTOR][UART_RX_BUFFER_SIZE];
	rt_uint32_t save_descriptor;
	rt_uint32_t read_index, read_descriptor;
	rt_bool_t is_full;
};

/* data node for Tx Mode */
struct stm32_serial_data_node
{
	rt_uint8_t *data_ptr;
	rt_size_t  data_size;
	struct stm32_serial_data_node *next, *prev;
};
struct stm32_serial_dma_tx
{
	DMA_Channel_TypeDef* dma_channel;
	struct stm32_serial_data_node *list_head, *list_tail;
};

struct stm32_serial_int_rx
{
	rt_uint8_t  rx_buffer[UART_RX_BUFFER_SIZE];
	rt_uint32_t read_index, save_index;
};

struct stm32_serial_int_tx
{
	rt_uint8_t  tx_buffer[UART_TX_BUFFER_SIZE];
	rt_uint32_t write_index, save_index;
};

struct stm32_serial_device
{
	USART_TypeDef* uart_device;

	/* rx structure */
	struct stm32_serial_int_rx* int_rx;
	struct stm32_serial_dma_rx* dma_rx;

	/* tx structure */
	struct stm32_serial_int_tx* int_tx;
	struct stm32_serial_dma_tx* dma_tx;
};

rt_err_t rt_hw_serial_register(rt_device_t device, const char* name, rt_uint32_t flag, struct stm32_serial_device *serial);

void rt_hw_serial_isr(rt_device_t device);
void rt_hw_serial_dma_rx_isr(rt_device_t device);
void rt_hw_serial_dma_tx_isr(rt_device_t device);

#endif
