/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _HARDWARE_STRUCTS_RESETS_H
#define _HARDWARE_STRUCTS_RESETS_H

#include "hardware/address_mapped.h"
#include "hardware/regs/resets.h"

/// \tag::resets_hw[]
typedef struct {
    io_rw_32 reset;
    io_rw_32 wdsel;
    io_rw_32 reset_done;
} resets_hw_t;

#define resets_hw ((resets_hw_t *const)RESETS_BASE)
/// \end::resets_hw[]

#endif
