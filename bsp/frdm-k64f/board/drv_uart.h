/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */

#ifndef DRV_UART_H
#define DRV_UART_H

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <MK64F12.h>

#include <drivers/dev_serial.h>

void rt_hw_uart_init(void);

//for kernel debug when console not registered
void rt_hw_console_output(const char *str);

#endif /* end of include guard: DRV_UART_H */
