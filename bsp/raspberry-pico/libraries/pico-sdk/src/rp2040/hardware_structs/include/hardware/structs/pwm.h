/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_PWM_H
#define _HARDWARE_STRUCTS_PWM_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/pwm.h"

typedef struct pwm_slice_hw {
    io_rw_32 csr;
    io_rw_32 div;
    io_rw_32 ctr;
    io_rw_32 cc;
    io_rw_32 top;
} pwm_slice_hw_t;

typedef struct {
    pwm_slice_hw_t slice[NUM_PWM_SLICES];
    io_rw_32 en;
    io_rw_32 intr;
    io_rw_32 inte;
    io_rw_32 intf;
    io_rw_32 ints;
} pwm_hw_t;

#define pwm_hw ((pwm_hw_t *const)PWM_BASE)

#endif
