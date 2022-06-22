/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_SYSTICK_H
#define _HARDWARE_STRUCTS_SYSTICK_H

#include "hardware/address_mapped.h"
#include "hardware/regs/m0plus.h"

typedef struct {
    io_rw_32 csr;
    io_rw_32 rvr;
    io_ro_32 cvr;
    io_ro_32 calib;
} systick_hw_t;

#define mpu_hw ((systick_hw_t *const)(PPB_BASE + M0PLUS_SYST_CSR_OFFSET))

#endif
