#ifndef __RT_HW_SERIAL_H__
#define __RT_HW_SERIAL_H__

#include <rthw.h>
#include <rtthread.h>

#include "at91sam926x.h"

#define RXRDY			0x01
#define TXRDY			(1 << 1)
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
/* USART register offsets */
	volatile rt_uint32_t USART_CR;
	volatile rt_uint32_t USART_MR;
	volatile rt_uint32_t USART_IER;
	volatile rt_uint32_t USART_IDR;
	volatile rt_uint32_t USART_IMR;
	volatile rt_uint32_t USART_CSR;
	volatile rt_uint32_t USART_RHR;
	volatile rt_uint32_t USART_THR;
	volatile rt_uint32_t USART_BRGR;
	volatile rt_uint32_t USART_RTOR;
	volatile rt_uint32_t USART_TTGR;
	volatile rt_uint32_t reseverd0[5];
	volatile rt_uint32_t USART_FIDI;
	volatile rt_uint32_t USART_NER;
	volatile rt_uint32_t USART_XXR;
	volatile rt_uint32_t USART_IFR;
	volatile rt_uint32_t reserved1[44];
	volatile rt_uint32_t USART_RPR;
	volatile rt_uint32_t USART_RCR;
	volatile rt_uint32_t USART_TPR;
	volatile rt_uint32_t USART_TCR;
	volatile rt_uint32_t USART_RNPR;
	volatile rt_uint32_t USART_RNCR;
	volatile rt_uint32_t USART_TNPR;
	volatile rt_uint32_t USART_TNCR;
	volatile rt_uint32_t USART_PTCR;
	volatile rt_uint32_t USART_PTSR;
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
