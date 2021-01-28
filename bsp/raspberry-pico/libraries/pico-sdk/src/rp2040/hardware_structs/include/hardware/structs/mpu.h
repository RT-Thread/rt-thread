/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_MPU_H
#define _HARDWARE_STRUCTS_MPU_H

#include "hardware/address_mapped.h"
#include "hardware/regs/m0plus.h"

typedef struct {
    io_ro_32 type;
    io_rw_32 ctrl;
    io_rw_32 rnr;
    io_rw_32 rbar;
    io_rw_32 rasr;
} mpu_hw_t;

#define mpu_hw ((mpu_hw_t *const)(PPB_BASE + M0PLUS_MPU_TYPE_OFFSET))

#endif
