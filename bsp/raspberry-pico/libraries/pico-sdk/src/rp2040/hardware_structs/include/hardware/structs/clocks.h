/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_CLOCKS_H
#define _HARDWARE_STRUCTS_CLOCKS_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/clocks.h"

/*! \brief Enumeration identifying a hardware clock
 *  \ingroup hardware_clocks
 */
/// \tag::clkenum[]
enum clock_index {
    clk_gpout0 = 0,     ///< GPIO Muxing 0
    clk_gpout1,         ///< GPIO Muxing 1
    clk_gpout2,         ///< GPIO Muxing 2
    clk_gpout3,         ///< GPIO Muxing 3
    clk_ref,            ///< Watchdog and timers reference clock
    clk_sys,            ///< Processors, bus fabric, memory, memory mapped registers
    clk_peri,           ///< Peripheral clock for UART and SPI
    clk_usb,            ///< USB clock
    clk_adc,            ///< ADC clock
    clk_rtc,            ///< Real time clock
    CLK_COUNT
};
/// \end::clkenum[]

/// \tag::clock_hw[]
typedef struct {
    io_rw_32 ctrl;
    io_rw_32 div;
    io_rw_32 selected;
} clock_hw_t;
/// \end::clock_hw[]

typedef struct {
    io_rw_32 ref_khz;
    io_rw_32 min_khz;
    io_rw_32 max_khz;
    io_rw_32 delay;
    io_rw_32 interval;
    io_rw_32 src;
    io_ro_32 status;
    io_ro_32 result;
} fc_hw_t;

typedef struct {
    clock_hw_t clk[CLK_COUNT];
    struct {
        io_rw_32 ctrl;
        io_rw_32 status;
    } resus;
    fc_hw_t fc0;
    io_rw_32 wake_en0;
    io_rw_32 wake_en1;
    io_rw_32 sleep_en0;
    io_rw_32 sleep_en1;
    io_rw_32 enabled0;
    io_rw_32 enabled1;
    io_rw_32 intr;
    io_rw_32 inte;
    io_rw_32 intf;
    io_rw_32 ints;
} clocks_hw_t;

#define clocks_hw ((clocks_hw_t *const)CLOCKS_BASE)
#endif
