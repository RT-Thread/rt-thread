/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : RTC
// Version        : 1
// Bus type       : apb
// Description    : Register block to control RTC
// =============================================================================
#ifndef HARDWARE_REGS_RTC_DEFINED
#define HARDWARE_REGS_RTC_DEFINED
// =============================================================================
// Register    : RTC_CLKDIV_M1
// Description : Divider minus 1 for the 1 second counter. Safe to change the
//               value when RTC is not enabled.
#define RTC_CLKDIV_M1_OFFSET 0x00000000
#define RTC_CLKDIV_M1_BITS   0x0000ffff
#define RTC_CLKDIV_M1_RESET  0x00000000
#define RTC_CLKDIV_M1_MSB    15
#define RTC_CLKDIV_M1_LSB    0
#define RTC_CLKDIV_M1_ACCESS "RW"
// =============================================================================
// Register    : RTC_SETUP_0
// Description : RTC setup register 0
#define RTC_SETUP_0_OFFSET 0x00000004
#define RTC_SETUP_0_BITS   0x00ffff1f
#define RTC_SETUP_0_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : RTC_SETUP_0_YEAR
// Description : Year
#define RTC_SETUP_0_YEAR_RESET  0x000
#define RTC_SETUP_0_YEAR_BITS   0x00fff000
#define RTC_SETUP_0_YEAR_MSB    23
#define RTC_SETUP_0_YEAR_LSB    12
#define RTC_SETUP_0_YEAR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_SETUP_0_MONTH
// Description : Month (1..12)
#define RTC_SETUP_0_MONTH_RESET  0x0
#define RTC_SETUP_0_MONTH_BITS   0x00000f00
#define RTC_SETUP_0_MONTH_MSB    11
#define RTC_SETUP_0_MONTH_LSB    8
#define RTC_SETUP_0_MONTH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_SETUP_0_DAY
// Description : Day of the month (1..31)
#define RTC_SETUP_0_DAY_RESET  0x00
#define RTC_SETUP_0_DAY_BITS   0x0000001f
#define RTC_SETUP_0_DAY_MSB    4
#define RTC_SETUP_0_DAY_LSB    0
#define RTC_SETUP_0_DAY_ACCESS "RW"
// =============================================================================
// Register    : RTC_SETUP_1
// Description : RTC setup register 1
#define RTC_SETUP_1_OFFSET 0x00000008
#define RTC_SETUP_1_BITS   0x071f3f3f
#define RTC_SETUP_1_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : RTC_SETUP_1_DOTW
// Description : Day of the week: 1-Monday...0-Sunday ISO 8601 mod 7
#define RTC_SETUP_1_DOTW_RESET  0x0
#define RTC_SETUP_1_DOTW_BITS   0x07000000
#define RTC_SETUP_1_DOTW_MSB    26
#define RTC_SETUP_1_DOTW_LSB    24
#define RTC_SETUP_1_DOTW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_SETUP_1_HOUR
// Description : Hours
#define RTC_SETUP_1_HOUR_RESET  0x00
#define RTC_SETUP_1_HOUR_BITS   0x001f0000
#define RTC_SETUP_1_HOUR_MSB    20
#define RTC_SETUP_1_HOUR_LSB    16
#define RTC_SETUP_1_HOUR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_SETUP_1_MIN
// Description : Minutes
#define RTC_SETUP_1_MIN_RESET  0x00
#define RTC_SETUP_1_MIN_BITS   0x00003f00
#define RTC_SETUP_1_MIN_MSB    13
#define RTC_SETUP_1_MIN_LSB    8
#define RTC_SETUP_1_MIN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_SETUP_1_SEC
// Description : Seconds
#define RTC_SETUP_1_SEC_RESET  0x00
#define RTC_SETUP_1_SEC_BITS   0x0000003f
#define RTC_SETUP_1_SEC_MSB    5
#define RTC_SETUP_1_SEC_LSB    0
#define RTC_SETUP_1_SEC_ACCESS "RW"
// =============================================================================
// Register    : RTC_CTRL
// Description : RTC Control and status
#define RTC_CTRL_OFFSET 0x0000000c
#define RTC_CTRL_BITS   0x00000113
#define RTC_CTRL_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : RTC_CTRL_FORCE_NOTLEAPYEAR
// Description : If set, leapyear is forced off.
//               Useful for years divisible by 100 but not by 400
#define RTC_CTRL_FORCE_NOTLEAPYEAR_RESET  0x0
#define RTC_CTRL_FORCE_NOTLEAPYEAR_BITS   0x00000100
#define RTC_CTRL_FORCE_NOTLEAPYEAR_MSB    8
#define RTC_CTRL_FORCE_NOTLEAPYEAR_LSB    8
#define RTC_CTRL_FORCE_NOTLEAPYEAR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_CTRL_LOAD
// Description : Load RTC
#define RTC_CTRL_LOAD_RESET  0x0
#define RTC_CTRL_LOAD_BITS   0x00000010
#define RTC_CTRL_LOAD_MSB    4
#define RTC_CTRL_LOAD_LSB    4
#define RTC_CTRL_LOAD_ACCESS "SC"
// -----------------------------------------------------------------------------
// Field       : RTC_CTRL_RTC_ACTIVE
// Description : RTC enabled (running)
#define RTC_CTRL_RTC_ACTIVE_RESET  "-"
#define RTC_CTRL_RTC_ACTIVE_BITS   0x00000002
#define RTC_CTRL_RTC_ACTIVE_MSB    1
#define RTC_CTRL_RTC_ACTIVE_LSB    1
#define RTC_CTRL_RTC_ACTIVE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : RTC_CTRL_RTC_ENABLE
// Description : Enable RTC
#define RTC_CTRL_RTC_ENABLE_RESET  0x0
#define RTC_CTRL_RTC_ENABLE_BITS   0x00000001
#define RTC_CTRL_RTC_ENABLE_MSB    0
#define RTC_CTRL_RTC_ENABLE_LSB    0
#define RTC_CTRL_RTC_ENABLE_ACCESS "RW"
// =============================================================================
// Register    : RTC_IRQ_SETUP_0
// Description : Interrupt setup register 0
#define RTC_IRQ_SETUP_0_OFFSET 0x00000010
#define RTC_IRQ_SETUP_0_BITS   0x37ffff1f
#define RTC_IRQ_SETUP_0_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_0_MATCH_ACTIVE
// Description : None
#define RTC_IRQ_SETUP_0_MATCH_ACTIVE_RESET  "-"
#define RTC_IRQ_SETUP_0_MATCH_ACTIVE_BITS   0x20000000
#define RTC_IRQ_SETUP_0_MATCH_ACTIVE_MSB    29
#define RTC_IRQ_SETUP_0_MATCH_ACTIVE_LSB    29
#define RTC_IRQ_SETUP_0_MATCH_ACTIVE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_0_MATCH_ENA
// Description : Global match enable. Don't change any other value while this
//               one is enabled
#define RTC_IRQ_SETUP_0_MATCH_ENA_RESET  0x0
#define RTC_IRQ_SETUP_0_MATCH_ENA_BITS   0x10000000
#define RTC_IRQ_SETUP_0_MATCH_ENA_MSB    28
#define RTC_IRQ_SETUP_0_MATCH_ENA_LSB    28
#define RTC_IRQ_SETUP_0_MATCH_ENA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_0_YEAR_ENA
// Description : Enable year matching
#define RTC_IRQ_SETUP_0_YEAR_ENA_RESET  0x0
#define RTC_IRQ_SETUP_0_YEAR_ENA_BITS   0x04000000
#define RTC_IRQ_SETUP_0_YEAR_ENA_MSB    26
#define RTC_IRQ_SETUP_0_YEAR_ENA_LSB    26
#define RTC_IRQ_SETUP_0_YEAR_ENA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_0_MONTH_ENA
// Description : Enable month matching
#define RTC_IRQ_SETUP_0_MONTH_ENA_RESET  0x0
#define RTC_IRQ_SETUP_0_MONTH_ENA_BITS   0x02000000
#define RTC_IRQ_SETUP_0_MONTH_ENA_MSB    25
#define RTC_IRQ_SETUP_0_MONTH_ENA_LSB    25
#define RTC_IRQ_SETUP_0_MONTH_ENA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_0_DAY_ENA
// Description : Enable day matching
#define RTC_IRQ_SETUP_0_DAY_ENA_RESET  0x0
#define RTC_IRQ_SETUP_0_DAY_ENA_BITS   0x01000000
#define RTC_IRQ_SETUP_0_DAY_ENA_MSB    24
#define RTC_IRQ_SETUP_0_DAY_ENA_LSB    24
#define RTC_IRQ_SETUP_0_DAY_ENA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_0_YEAR
// Description : Year
#define RTC_IRQ_SETUP_0_YEAR_RESET  0x000
#define RTC_IRQ_SETUP_0_YEAR_BITS   0x00fff000
#define RTC_IRQ_SETUP_0_YEAR_MSB    23
#define RTC_IRQ_SETUP_0_YEAR_LSB    12
#define RTC_IRQ_SETUP_0_YEAR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_0_MONTH
// Description : Month (1..12)
#define RTC_IRQ_SETUP_0_MONTH_RESET  0x0
#define RTC_IRQ_SETUP_0_MONTH_BITS   0x00000f00
#define RTC_IRQ_SETUP_0_MONTH_MSB    11
#define RTC_IRQ_SETUP_0_MONTH_LSB    8
#define RTC_IRQ_SETUP_0_MONTH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_0_DAY
// Description : Day of the month (1..31)
#define RTC_IRQ_SETUP_0_DAY_RESET  0x00
#define RTC_IRQ_SETUP_0_DAY_BITS   0x0000001f
#define RTC_IRQ_SETUP_0_DAY_MSB    4
#define RTC_IRQ_SETUP_0_DAY_LSB    0
#define RTC_IRQ_SETUP_0_DAY_ACCESS "RW"
// =============================================================================
// Register    : RTC_IRQ_SETUP_1
// Description : Interrupt setup register 1
#define RTC_IRQ_SETUP_1_OFFSET 0x00000014
#define RTC_IRQ_SETUP_1_BITS   0xf71f3f3f
#define RTC_IRQ_SETUP_1_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_1_DOTW_ENA
// Description : Enable day of the week matching
#define RTC_IRQ_SETUP_1_DOTW_ENA_RESET  0x0
#define RTC_IRQ_SETUP_1_DOTW_ENA_BITS   0x80000000
#define RTC_IRQ_SETUP_1_DOTW_ENA_MSB    31
#define RTC_IRQ_SETUP_1_DOTW_ENA_LSB    31
#define RTC_IRQ_SETUP_1_DOTW_ENA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_1_HOUR_ENA
// Description : Enable hour matching
#define RTC_IRQ_SETUP_1_HOUR_ENA_RESET  0x0
#define RTC_IRQ_SETUP_1_HOUR_ENA_BITS   0x40000000
#define RTC_IRQ_SETUP_1_HOUR_ENA_MSB    30
#define RTC_IRQ_SETUP_1_HOUR_ENA_LSB    30
#define RTC_IRQ_SETUP_1_HOUR_ENA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_1_MIN_ENA
// Description : Enable minute matching
#define RTC_IRQ_SETUP_1_MIN_ENA_RESET  0x0
#define RTC_IRQ_SETUP_1_MIN_ENA_BITS   0x20000000
#define RTC_IRQ_SETUP_1_MIN_ENA_MSB    29
#define RTC_IRQ_SETUP_1_MIN_ENA_LSB    29
#define RTC_IRQ_SETUP_1_MIN_ENA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_1_SEC_ENA
// Description : Enable second matching
#define RTC_IRQ_SETUP_1_SEC_ENA_RESET  0x0
#define RTC_IRQ_SETUP_1_SEC_ENA_BITS   0x10000000
#define RTC_IRQ_SETUP_1_SEC_ENA_MSB    28
#define RTC_IRQ_SETUP_1_SEC_ENA_LSB    28
#define RTC_IRQ_SETUP_1_SEC_ENA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_1_DOTW
// Description : Day of the week
#define RTC_IRQ_SETUP_1_DOTW_RESET  0x0
#define RTC_IRQ_SETUP_1_DOTW_BITS   0x07000000
#define RTC_IRQ_SETUP_1_DOTW_MSB    26
#define RTC_IRQ_SETUP_1_DOTW_LSB    24
#define RTC_IRQ_SETUP_1_DOTW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_1_HOUR
// Description : Hours
#define RTC_IRQ_SETUP_1_HOUR_RESET  0x00
#define RTC_IRQ_SETUP_1_HOUR_BITS   0x001f0000
#define RTC_IRQ_SETUP_1_HOUR_MSB    20
#define RTC_IRQ_SETUP_1_HOUR_LSB    16
#define RTC_IRQ_SETUP_1_HOUR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_1_MIN
// Description : Minutes
#define RTC_IRQ_SETUP_1_MIN_RESET  0x00
#define RTC_IRQ_SETUP_1_MIN_BITS   0x00003f00
#define RTC_IRQ_SETUP_1_MIN_MSB    13
#define RTC_IRQ_SETUP_1_MIN_LSB    8
#define RTC_IRQ_SETUP_1_MIN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : RTC_IRQ_SETUP_1_SEC
// Description : Seconds
#define RTC_IRQ_SETUP_1_SEC_RESET  0x00
#define RTC_IRQ_SETUP_1_SEC_BITS   0x0000003f
#define RTC_IRQ_SETUP_1_SEC_MSB    5
#define RTC_IRQ_SETUP_1_SEC_LSB    0
#define RTC_IRQ_SETUP_1_SEC_ACCESS "RW"
// =============================================================================
// Register    : RTC_RTC_1
// Description : RTC register 1.
#define RTC_RTC_1_OFFSET 0x00000018
#define RTC_RTC_1_BITS   0x00ffff1f
#define RTC_RTC_1_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : RTC_RTC_1_YEAR
// Description : Year
#define RTC_RTC_1_YEAR_RESET  "-"
#define RTC_RTC_1_YEAR_BITS   0x00fff000
#define RTC_RTC_1_YEAR_MSB    23
#define RTC_RTC_1_YEAR_LSB    12
#define RTC_RTC_1_YEAR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : RTC_RTC_1_MONTH
// Description : Month (1..12)
#define RTC_RTC_1_MONTH_RESET  "-"
#define RTC_RTC_1_MONTH_BITS   0x00000f00
#define RTC_RTC_1_MONTH_MSB    11
#define RTC_RTC_1_MONTH_LSB    8
#define RTC_RTC_1_MONTH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : RTC_RTC_1_DAY
// Description : Day of the month (1..31)
#define RTC_RTC_1_DAY_RESET  "-"
#define RTC_RTC_1_DAY_BITS   0x0000001f
#define RTC_RTC_1_DAY_MSB    4
#define RTC_RTC_1_DAY_LSB    0
#define RTC_RTC_1_DAY_ACCESS "RO"
// =============================================================================
// Register    : RTC_RTC_0
// Description : RTC register 0
//               Read this before RTC 1!
#define RTC_RTC_0_OFFSET 0x0000001c
#define RTC_RTC_0_BITS   0x071f3f3f
#define RTC_RTC_0_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : RTC_RTC_0_DOTW
// Description : Day of the week
#define RTC_RTC_0_DOTW_RESET  "-"
#define RTC_RTC_0_DOTW_BITS   0x07000000
#define RTC_RTC_0_DOTW_MSB    26
#define RTC_RTC_0_DOTW_LSB    24
#define RTC_RTC_0_DOTW_ACCESS "RF"
// -----------------------------------------------------------------------------
// Field       : RTC_RTC_0_HOUR
// Description : Hours
#define RTC_RTC_0_HOUR_RESET  "-"
#define RTC_RTC_0_HOUR_BITS   0x001f0000
#define RTC_RTC_0_HOUR_MSB    20
#define RTC_RTC_0_HOUR_LSB    16
#define RTC_RTC_0_HOUR_ACCESS "RF"
// -----------------------------------------------------------------------------
// Field       : RTC_RTC_0_MIN
// Description : Minutes
#define RTC_RTC_0_MIN_RESET  "-"
#define RTC_RTC_0_MIN_BITS   0x00003f00
#define RTC_RTC_0_MIN_MSB    13
#define RTC_RTC_0_MIN_LSB    8
#define RTC_RTC_0_MIN_ACCESS "RF"
// -----------------------------------------------------------------------------
// Field       : RTC_RTC_0_SEC
// Description : Seconds
#define RTC_RTC_0_SEC_RESET  "-"
#define RTC_RTC_0_SEC_BITS   0x0000003f
#define RTC_RTC_0_SEC_MSB    5
#define RTC_RTC_0_SEC_LSB    0
#define RTC_RTC_0_SEC_ACCESS "RF"
// =============================================================================
// Register    : RTC_INTR
// Description : Raw Interrupts
#define RTC_INTR_OFFSET 0x00000020
#define RTC_INTR_BITS   0x00000001
#define RTC_INTR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : RTC_INTR_RTC
// Description : None
#define RTC_INTR_RTC_RESET  0x0
#define RTC_INTR_RTC_BITS   0x00000001
#define RTC_INTR_RTC_MSB    0
#define RTC_INTR_RTC_LSB    0
#define RTC_INTR_RTC_ACCESS "RO"
// =============================================================================
// Register    : RTC_INTE
// Description : Interrupt Enable
#define RTC_INTE_OFFSET 0x00000024
#define RTC_INTE_BITS   0x00000001
#define RTC_INTE_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : RTC_INTE_RTC
// Description : None
#define RTC_INTE_RTC_RESET  0x0
#define RTC_INTE_RTC_BITS   0x00000001
#define RTC_INTE_RTC_MSB    0
#define RTC_INTE_RTC_LSB    0
#define RTC_INTE_RTC_ACCESS "RW"
// =============================================================================
// Register    : RTC_INTF
// Description : Interrupt Force
#define RTC_INTF_OFFSET 0x00000028
#define RTC_INTF_BITS   0x00000001
#define RTC_INTF_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : RTC_INTF_RTC
// Description : None
#define RTC_INTF_RTC_RESET  0x0
#define RTC_INTF_RTC_BITS   0x00000001
#define RTC_INTF_RTC_MSB    0
#define RTC_INTF_RTC_LSB    0
#define RTC_INTF_RTC_ACCESS "RW"
// =============================================================================
// Register    : RTC_INTS
// Description : Interrupt status after masking & forcing
#define RTC_INTS_OFFSET 0x0000002c
#define RTC_INTS_BITS   0x00000001
#define RTC_INTS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : RTC_INTS_RTC
// Description : None
#define RTC_INTS_RTC_RESET  0x0
#define RTC_INTS_RTC_BITS   0x00000001
#define RTC_INTS_RTC_MSB    0
#define RTC_INTS_RTC_LSB    0
#define RTC_INTS_RTC_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_RTC_DEFINED
