/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_PADS_QSPI_H
#define _HARDWARE_STRUCTS_PADS_QSPI_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/pads_qspi.h"

typedef struct {
    io_rw_32 voltage_select;
    io_rw_32 io[6];
} pads_qspi_hw_t;

#define pads_qspi_hw ((pads_qspi_hw_t *const)PADS_QSPI_BASE)

#endif
