#include "stdbool.h"
#include "stdint.h"

#ifndef _UART_EIF_H_
#define _UART_EIF_H_

void eif_uart_read(uint8_t *bufptr, uint32_t size, void (*callback) (void*, uint8_t), void* dummy);
void eif_uart_write(uint8_t *bufptr, uint32_t size, void (*callback) (void*, uint8_t), void* dummy);
void eif_uart_flow_on(void);
bool eif_uart_flow_off(void);

void eif_uart_recv_bytes(uint8_t *data ,uint16_t len);
void eif_uart_send_bytes(uint8_t *src , uint16_t );
void eif_uart_recv_irq_handler(void);
void eif_uart_recv_irq_enable(uint8_t enable);
void eif_uart_init(uint32_t bps);

#endif //_UART_EIF_H_
