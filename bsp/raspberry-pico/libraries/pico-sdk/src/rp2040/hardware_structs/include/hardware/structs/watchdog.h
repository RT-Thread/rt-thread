/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_WATCHDOG_H
#define _HARDWARE_STRUCTS_WATCHDOG_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/watchdog.h"

typedef struct {
    io_rw_32 ctrl;
    io_wo_32 load;
    io_ro_32 reason;
    io_rw_32 scratch[8];
    io_rw_32 tick;
} watchdog_hw_t;

#define watchdog_hw ((watchdog_hw_t *const)WATCHDOG_BASE)

#endif
