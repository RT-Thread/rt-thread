/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Vijai Kumar K <vijai@behindbytes.com>
 */

#ifndef __SERIAL_SHAKTI_UART_H__
#define __SERIAL_SHAKTI_UART_H__

#include <sbi/sbi_types.h>

int shakti_uart_init(unsigned long base, u32 in_freq, u32 baudrate);

#endif
