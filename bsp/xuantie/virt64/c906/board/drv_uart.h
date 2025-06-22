/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include "riscv_io.h"

/**
 * uart ns16550a
 * http://byterunner.com/16550.html
 */

/* TRANSMIT AND RECEIVE HOLDING REGISTER */
#define UART_RHR 0
#define UART_THR 0

/* INTERRUPT ENABLE REGISTER */
#define UART_IER 1
#define UART_IER_RX_ENABLE (1 << 0)
#define UART_IER_TX_ENABLE (1 << 1)

/* FIFO CONTROL REGISTER */
#define UART_FCR 2
#define UART_FCR_FIFO_ENABLE (1 << 0)
#define UART_FCR_FIFO_CLEAR (3 << 1)

/* INTERRUPT STATUS REGISTER */
#define UART_ISR 2

/* LINE CONTROL REGISTER */
#define UART_LCR 3
#define UART_LCR_EIGHT_BITS (3 << 0)
// special mode to set baud rate
#define UART_LCR_BAUD_LATCH (1 << 7)

/* LINE STATUS REGISTER */
#define UART_LSR 5
// input is waiting to be read from RHR
#define UART_LSR_RX_READY (1 << 0)
// THR can accept another character to send
#define UART_LSR_TX_IDLE (1 << 5)

#define UART_REFERENCE_CLOCK  1843200
#define UART_DEFAULT_BAUDRATE 115200

extern void *uart0_base;

#define write8_uart0(idx, value) __raw_writeb(((rt_uint8_t)value), (void*)((size_t)uart0_base + (idx)))
#define read8_uart0(idx) __raw_readb((void*)((size_t)uart0_base + (idx)))

void rt_hw_uart_start_rx_thread();
int rt_hw_uart_init(void);
void drv_uart_puts(char *str); // for syscall

#endif /* __DRV_UART_H__ */
