/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_XOSC_H
#define _HARDWARE_STRUCTS_XOSC_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/xosc.h"

/// \tag::xosc_hw[]
typedef struct {
    io_rw_32 ctrl;
    io_rw_32 status;
    io_rw_32 dormant;
    io_rw_32 startup;
    io_rw_32 _reserved[3];
    io_rw_32 count;
} xosc_hw_t;

#define xosc_hw ((xosc_hw_t *const)XOSC_BASE)
/// \end::xosc_hw[]

#endif
