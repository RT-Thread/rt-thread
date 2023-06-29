/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/06/25     flyingcys    first version
 */
#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>

#define UART_REG_SHIFT      0x2  /* Register Shift*/
#define UART_INPUT_CLK      25000000

#define UART0_BASE          0x04140000
#define UART1_BASE          0x04150000
#define UART2_BASE          0x04160000
#define UART3_BASE          0x04170000
#define UART4_BASE          0x041C0000

#define UART_IRQ_BASE       (44)
#define UART0_IRQ           (UART_IRQ_BASE + 0)
#define UART1_IRQ           (UART_IRQ_BASE + 1)
#define UART2_IRQ           (UART_IRQ_BASE + 2)
#define UART3_IRQ           (UART_IRQ_BASE + 3)
#define UART4_IRQ           (UART_IRQ_BASE + 4)

int rt_hw_uart_init(void);

#endif  /* __DRV_USART_H__ */
