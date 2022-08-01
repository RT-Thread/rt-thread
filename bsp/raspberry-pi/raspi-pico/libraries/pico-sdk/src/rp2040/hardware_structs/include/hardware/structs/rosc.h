/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_ROSC_H
#define _HARDWARE_STRUCTS_ROSC_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/rosc.h"

typedef struct {
    io_rw_32 ctrl;
    io_rw_32 freqa;
    io_rw_32 freqb;
    io_rw_32 dormant;
    io_rw_32 div;
    io_rw_32 phase;
    io_rw_32 status;
    io_rw_32 randombit;
    io_rw_32 count;
    io_rw_32 dftx;
} rosc_hw_t;

#define rosc_hw ((rosc_hw_t *const)ROSC_BASE)

#endif
