/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_PADSBANK0_H
#define _HARDWARE_STRUCTS_PADSBANK0_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/pads_bank0.h"

typedef struct {
    io_rw_32 voltage_select;
    io_rw_32 io[30];
} padsbank0_hw_t;

#define padsbank0_hw ((padsbank0_hw_t *)PADS_BANK0_BASE)

#endif
