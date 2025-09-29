/*
 * COPYRIGHT (C) 2025, Real-Thread Information Technology Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-12     BruceOu      the first 
 * 2025-08-10     Siwei Xu     Fix compile errors
 * 2025-09-15     Siwei Xu     Add LPUART driver
 */

#ifndef __UART_H__
#define __UART_H__

#include <board.h>

int rt_hw_uart_init(void);

void rt_hw_earlycon_ioremap(void);
void rt_hw_earlycon_putc(char c);
void rt_hw_earlycon_puts(const char *str);
void rt_hw_earlycon_print_hex(const char *str, rt_base_t hex);

void rt_hw_console_putc(char c);
void rt_hw_console_output(const char *str);

#endif


