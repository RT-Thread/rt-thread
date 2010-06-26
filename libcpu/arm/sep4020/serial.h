#ifndef __RT_SERIAL_H__
#define __RT_SERIAL_H__

#include <rthw.h>
#include <rtthread.h>


#define	USTAT_RCV_READY			0x01   	/* receive data ready */ 
#define	USTAT_TXB_EMPTY			0x20   	/* tx buffer empty */
#define BPS						115200	/* serial baudrate */

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

/* serial port registers */
typedef struct uartport
{
	rt_uint32_t dlbl_rxfifo_txfifo;
	rt_uint32_t dlbh_ier;
	rt_uint32_t iir_fcr;
	rt_uint32_t lcr;
	rt_uint32_t mcr;
	rt_uint32_t lsr;
	rt_uint32_t msr;
}uartport;

struct serial_device
{
	/* uart hardware registers */
	uartport* uart_device;
	
	/* rx structure */
	struct serial_int_rx* int_rx;

	/* tx structure */
	struct serial_int_tx* int_tx;
};

rt_err_t rt_hw_serial_register(rt_device_t device, const char* name, rt_uint32_t flag, struct serial_device *serial);

void rt_hw_serial_isr(rt_device_t device);

#endif

