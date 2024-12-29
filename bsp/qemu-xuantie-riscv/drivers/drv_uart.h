/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/12/11     flyingcys    The first version
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include "dw_uart_ll.h"

#define DW_UART0_BASE              (0x1900d000UL)
#define DW_UART0_IRQn              (20)             /* uart Interrupt */

int rt_hw_uart_init(void);

#endif /* __DRV_UART_H__ */