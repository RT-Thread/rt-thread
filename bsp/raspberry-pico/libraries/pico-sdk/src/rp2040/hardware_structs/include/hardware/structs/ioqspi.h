/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_IOQSPI_H
#define _HARDWARE_STRUCTS_IOQSPI_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/io_qspi.h"

typedef struct {
    struct {
        io_rw_32 status;
        io_rw_32 ctrl;
    } io[6];
} ioqspi_hw_t;

#define ioqspi_hw ((ioqspi_hw_t *const)IO_QSPI_BASE)

#endif
