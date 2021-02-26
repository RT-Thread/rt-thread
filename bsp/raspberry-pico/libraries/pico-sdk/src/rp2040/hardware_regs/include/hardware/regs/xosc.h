/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : XOSC
// Version        : 1
// Bus type       : apb
// Description    : Controls the crystal oscillator
// =============================================================================
#ifndef HARDWARE_REGS_XOSC_DEFINED
#define HARDWARE_REGS_XOSC_DEFINED
// =============================================================================
// Register    : XOSC_CTRL
// Description : Crystal Oscillator Control
#define XOSC_CTRL_OFFSET 0x00000000
#define XOSC_CTRL_BITS   0x00ffffff
#define XOSC_CTRL_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : XOSC_CTRL_ENABLE
// Description : On power-up this field is initialised to DISABLE and the chip
//               runs from the ROSC.
//               If the chip has subsequently been programmed to run from the
//               XOSC then setting this field to DISABLE may lock-up the chip.
//               If this is a concern then run the clk_ref from the ROSC and
//               enable the clk_sys RESUS feature.
//               The 12-bit code is intended to give some protection against
//               accidental writes. An invalid setting will enable the
//               oscillator.
//               0xd1e -> DISABLE
//               0xfab -> ENABLE
#define XOSC_CTRL_ENABLE_RESET         "-"
#define XOSC_CTRL_ENABLE_BITS          0x00fff000
#define XOSC_CTRL_ENABLE_MSB           23
#define XOSC_CTRL_ENABLE_LSB           12
#define XOSC_CTRL_ENABLE_ACCESS        "RW"
#define XOSC_CTRL_ENABLE_VALUE_DISABLE 0xd1e
#define XOSC_CTRL_ENABLE_VALUE_ENABLE  0xfab
// -----------------------------------------------------------------------------
// Field       : XOSC_CTRL_FREQ_RANGE
// Description : Frequency range. This resets to 0xAA0 and cannot be changed.
//               0xaa0 -> 1_15MHZ
//               0xaa1 -> RESERVED_1
//               0xaa2 -> RESERVED_2
//               0xaa3 -> RESERVED_3
#define XOSC_CTRL_FREQ_RANGE_RESET            "-"
#define XOSC_CTRL_FREQ_RANGE_BITS             0x00000fff
#define XOSC_CTRL_FREQ_RANGE_MSB              11
#define XOSC_CTRL_FREQ_RANGE_LSB              0
#define XOSC_CTRL_FREQ_RANGE_ACCESS           "RW"
#define XOSC_CTRL_FREQ_RANGE_VALUE_1_15MHZ    0xaa0
#define XOSC_CTRL_FREQ_RANGE_VALUE_RESERVED_1 0xaa1
#define XOSC_CTRL_FREQ_RANGE_VALUE_RESERVED_2 0xaa2
#define XOSC_CTRL_FREQ_RANGE_VALUE_RESERVED_3 0xaa3
// =============================================================================
// Register    : XOSC_STATUS
// Description : Crystal Oscillator Status
#define XOSC_STATUS_OFFSET 0x00000004
#define XOSC_STATUS_BITS   0x81001003
#define XOSC_STATUS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : XOSC_STATUS_STABLE
// Description : Oscillator is running and stable
#define XOSC_STATUS_STABLE_RESET  0x0
#define XOSC_STATUS_STABLE_BITS   0x80000000
#define XOSC_STATUS_STABLE_MSB    31
#define XOSC_STATUS_STABLE_LSB    31
#define XOSC_STATUS_STABLE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : XOSC_STATUS_BADWRITE
// Description : An invalid value has been written to CTRL_ENABLE or
//               CTRL_FREQ_RANGE or DORMANT
#define XOSC_STATUS_BADWRITE_RESET  0x0
#define XOSC_STATUS_BADWRITE_BITS   0x01000000
#define XOSC_STATUS_BADWRITE_MSB    24
#define XOSC_STATUS_BADWRITE_LSB    24
#define XOSC_STATUS_BADWRITE_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : XOSC_STATUS_ENABLED
// Description : Oscillator is enabled but not necessarily running and stable,
//               resets to 0
#define XOSC_STATUS_ENABLED_RESET  "-"
#define XOSC_STATUS_ENABLED_BITS   0x00001000
#define XOSC_STATUS_ENABLED_MSB    12
#define XOSC_STATUS_ENABLED_LSB    12
#define XOSC_STATUS_ENABLED_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : XOSC_STATUS_FREQ_RANGE
// Description : The current frequency range setting, always reads 0
//               0x0 -> 1_15MHZ
//               0x1 -> RESERVED_1
//               0x2 -> RESERVED_2
//               0x3 -> RESERVED_3
#define XOSC_STATUS_FREQ_RANGE_RESET            "-"
#define XOSC_STATUS_FREQ_RANGE_BITS             0x00000003
#define XOSC_STATUS_FREQ_RANGE_MSB              1
#define XOSC_STATUS_FREQ_RANGE_LSB              0
#define XOSC_STATUS_FREQ_RANGE_ACCESS           "RO"
#define XOSC_STATUS_FREQ_RANGE_VALUE_1_15MHZ    0x0
#define XOSC_STATUS_FREQ_RANGE_VALUE_RESERVED_1 0x1
#define XOSC_STATUS_FREQ_RANGE_VALUE_RESERVED_2 0x2
#define XOSC_STATUS_FREQ_RANGE_VALUE_RESERVED_3 0x3
// =============================================================================
// Register    : XOSC_DORMANT
// Description : Crystal Oscillator pause control
//               This is used to save power by pausing the XOSC
//               On power-up this field is initialised to WAKE
//               An invalid write will also select WAKE
//               WARNING: stop the PLLs before selecting dormant mode
//               WARNING: setup the irq before selecting dormant mode
//               0x636f6d61 -> DORMANT
//               0x77616b65 -> WAKE
#define XOSC_DORMANT_OFFSET        0x00000008
#define XOSC_DORMANT_BITS          0xffffffff
#define XOSC_DORMANT_RESET         "-"
#define XOSC_DORMANT_MSB           31
#define XOSC_DORMANT_LSB           0
#define XOSC_DORMANT_ACCESS        "RW"
#define XOSC_DORMANT_VALUE_DORMANT 0x636f6d61
#define XOSC_DORMANT_VALUE_WAKE    0x77616b65
// =============================================================================
// Register    : XOSC_STARTUP
// Description : Controls the startup delay
#define XOSC_STARTUP_OFFSET 0x0000000c
#define XOSC_STARTUP_BITS   0x00103fff
#define XOSC_STARTUP_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : XOSC_STARTUP_X4
// Description : Multiplies the startup_delay by 4. This is of little value to
//               the user given that the delay can be programmed directly
#define XOSC_STARTUP_X4_RESET  "-"
#define XOSC_STARTUP_X4_BITS   0x00100000
#define XOSC_STARTUP_X4_MSB    20
#define XOSC_STARTUP_X4_LSB    20
#define XOSC_STARTUP_X4_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : XOSC_STARTUP_DELAY
// Description : in multiples of 256*xtal_period
#define XOSC_STARTUP_DELAY_RESET  "-"
#define XOSC_STARTUP_DELAY_BITS   0x00003fff
#define XOSC_STARTUP_DELAY_MSB    13
#define XOSC_STARTUP_DELAY_LSB    0
#define XOSC_STARTUP_DELAY_ACCESS "RW"
// =============================================================================
// Register    : XOSC_COUNT
// Description : A down counter running at the xosc frequency which counts to
//               zero and stops.
//               To start the counter write a non-zero value.
//               Can be used for short software pauses when setting up time
//               sensitive hardware.
#define XOSC_COUNT_OFFSET 0x0000001c
#define XOSC_COUNT_BITS   0x000000ff
#define XOSC_COUNT_RESET  0x00000000
#define XOSC_COUNT_MSB    7
#define XOSC_COUNT_LSB    0
#define XOSC_COUNT_ACCESS "RW"
// =============================================================================
#endif // HARDWARE_REGS_XOSC_DEFINED
