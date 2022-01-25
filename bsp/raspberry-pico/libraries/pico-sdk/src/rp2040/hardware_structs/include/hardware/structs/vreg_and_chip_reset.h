/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_VREG_AND_CHIP_RESET_H
#define _HARDWARE_STRUCTS_VREG_AND_CHIP_RESET_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/vreg_and_chip_reset.h"

typedef struct {
    io_rw_32 vreg;
    io_rw_32 bod;
    io_rw_32 chip_reset;
} vreg_and_chip_reset_hw_t;

#define vreg_and_chip_reset_hw ((vreg_and_chip_reset_hw_t *const)VREG_AND_CHIP_RESET_BASE)

#endif
