/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_UART_H
#define _HARDWARE_STRUCTS_UART_H

#include "hardware/address_mapped.h"
#include "hardware/regs/uart.h"

typedef struct {
    io_rw_32 dr;
    io_rw_32 rsr;
    uint32_t _pad0[4];
    io_rw_32 fr;
    uint32_t _pad1;
    io_rw_32 ilpr;
    io_rw_32 ibrd;
    io_rw_32 fbrd;
    io_rw_32 lcr_h;
    io_rw_32 cr;
    io_rw_32 ifls;
    io_rw_32 imsc;
    io_rw_32 ris;
    io_rw_32 mis;
    io_rw_32 icr;
    io_rw_32 dmacr;
} uart_hw_t;

#define uart0_hw ((uart_hw_t *const)UART0_BASE)
#define uart1_hw ((uart_hw_t *const)UART1_BASE)

#endif
