#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include "mss_uart.h"
void uart_rx_handler(mss_uart_instance_t *this_uart);

void uart0_rx_handler(mss_uart_instance_t * this_uart);
void uart1_rx_handler(mss_uart_instance_t * this_uart);
int rt_hw_uart_init(void);

#endif
