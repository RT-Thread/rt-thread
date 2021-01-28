/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _HARDWARE_STRUCTS_SCB_H
#define _HARDWARE_STRUCTS_SCB_H

#include "hardware/address_mapped.h"
#include "hardware/regs/m0plus.h"

// SCB == System Control Block
typedef struct {
    io_ro_32 cpuid;
    io_rw_32 icsr;
    io_rw_32 vtor;
    io_rw_32 aircr;
    io_rw_32 scr;
    // ...
} armv6m_scb_t;

#define scb_hw ((armv6m_scb_t *const)(PPB_BASE + M0PLUS_CPUID_OFFSET))

#endif
