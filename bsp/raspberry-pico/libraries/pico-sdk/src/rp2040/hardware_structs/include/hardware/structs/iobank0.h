/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_IOBANK0_H
#define _HARDWARE_STRUCTS_IOBANK0_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/io_bank0.h"

typedef struct {
    io_rw_32 inte[4];
    io_rw_32 intf[4];
    io_rw_32 ints[4];
} io_irq_ctrl_hw_t;

/// \tag::iobank0_hw[]
typedef struct {
    struct {
        io_rw_32 status;
        io_rw_32 ctrl;
    } io[30];
    io_rw_32 intr[4];
    io_irq_ctrl_hw_t proc0_irq_ctrl;
    io_irq_ctrl_hw_t proc1_irq_ctrl;
    io_irq_ctrl_hw_t dormant_wake_irq_ctrl;
} iobank0_hw_t;
/// \end::iobank0_hw[]

#define iobank0_hw ((iobank0_hw_t *const)IO_BANK0_BASE)

#endif
