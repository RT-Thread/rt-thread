/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_RTC_H
#define _HARDWARE_STRUCTS_RTC_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/rtc.h"

typedef struct {
    io_rw_32 clkdiv_m1;
    io_rw_32 setup_0;
    io_rw_32 setup_1;
    io_rw_32 ctrl;
    io_rw_32 irq_setup_0;
    io_rw_32 irq_setup_1;
    io_rw_32 rtc_1;
    io_rw_32 rtc_0;
    io_rw_32 intr;
    io_rw_32 inte;
    io_rw_32 intf;
    io_rw_32 ints;
} rtc_hw_t;

#define rtc_hw ((rtc_hw_t *const)RTC_BASE)

#endif
