/*
 * Copyright (c) 2019-2020, Xim
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

void rt_hw_uart_start_rx_thread();
int rt_hw_uart_init(void);
void drv_uart_puts(char *str); // for syscall

#endif /* __DRV_UART_H__ */
