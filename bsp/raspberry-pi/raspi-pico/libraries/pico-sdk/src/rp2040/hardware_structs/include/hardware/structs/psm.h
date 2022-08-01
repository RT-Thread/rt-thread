/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_PSM_H
#define _HARDWARE_STRUCTS_PSM_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/psm.h"

typedef struct {
    io_rw_32 frce_on;
    io_rw_32 frce_off;
    io_rw_32 wdsel;
    io_rw_32 done;
} psm_hw_t;

#define psm_hw ((psm_hw_t *const)PSM_BASE)

#endif
