/*
 * COPYRIGHT (C) 2025, Real-Thread Information Technology Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-10     Siwei Xu     Add i.MX91 SDK
 * 2025-09-15     Siwei Xu     Fix LPUART driver
 */

#ifndef __UART_H__
#define __UART_H__

#include "board.h"

#include <rtthread.h>

int rt_hw_uart_init(void);

#ifdef BSP_USING_EARLY_CONSOLE
#define USING_EARLY_CONSOLE 1
#else
#define USING_EARLY_CONSOLE 0
#endif

#if USING_EARLY_CONSOLE
void rt_hw_earlycon_ioremap(void);
void rt_hw_earlycon_putc(char c);
void rt_hw_earlycon_puts(const char *str);
void rt_hw_earlycon_print_hex(const char *str, rt_base_t hex);
#else
static inline void rt_hw_earlycon_ioremap(void) {}
static inline void rt_hw_earlycon_putc(char) {}
static inline void rt_hw_earlycon_puts(const char *) {}
static inline void rt_hw_earlycon_print_hex(const char *, rt_base_t) {}
#endif

void rt_hw_console_putc(char c);
void rt_hw_console_output(const char *str);

#endif


