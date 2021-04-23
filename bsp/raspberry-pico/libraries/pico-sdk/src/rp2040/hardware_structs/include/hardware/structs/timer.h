/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_TIMER_H
#define _HARDWARE_STRUCTS_TIMER_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/timer.h"

#define NUM_TIMERS 4

typedef struct {
    io_wo_32 timehw;
    io_wo_32 timelw;
    io_ro_32 timehr;
    io_ro_32 timelr;
    io_rw_32 alarm[NUM_TIMERS];
    io_rw_32 armed;
    io_ro_32 timerawh;
    io_ro_32 timerawl;
    io_rw_32 dbgpause;
    io_rw_32 pause;
    io_rw_32 intr;
    io_rw_32 inte;
    io_rw_32 intf;
    io_ro_32 ints;
} timer_hw_t;

#define timer_hw ((timer_hw_t *const)TIMER_BASE)

#endif
