/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : CLOCKS
// Version        : 1
// Bus type       : apb
// Description    : None
// =============================================================================
#ifndef HARDWARE_REGS_CLOCKS_DEFINED
#define HARDWARE_REGS_CLOCKS_DEFINED
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT0_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_GPOUT0_CTRL_OFFSET 0x00000000
#define CLOCKS_CLK_GPOUT0_CTRL_BITS   0x00131de0
#define CLOCKS_CLK_GPOUT0_CTRL_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_CTRL_NUDGE
// Description : An edge on this signal shifts the phase of the output by 1
//               cycle of the input clock
//               This can be done at any time
#define CLOCKS_CLK_GPOUT0_CTRL_NUDGE_RESET  0x0
#define CLOCKS_CLK_GPOUT0_CTRL_NUDGE_BITS   0x00100000
#define CLOCKS_CLK_GPOUT0_CTRL_NUDGE_MSB    20
#define CLOCKS_CLK_GPOUT0_CTRL_NUDGE_LSB    20
#define CLOCKS_CLK_GPOUT0_CTRL_NUDGE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_CTRL_PHASE
// Description : This delays the enable signal by up to 3 cycles of the input
//               clock
//               This must be set before the clock is enabled to have any effect
#define CLOCKS_CLK_GPOUT0_CTRL_PHASE_RESET  0x0
#define CLOCKS_CLK_GPOUT0_CTRL_PHASE_BITS   0x00030000
#define CLOCKS_CLK_GPOUT0_CTRL_PHASE_MSB    17
#define CLOCKS_CLK_GPOUT0_CTRL_PHASE_LSB    16
#define CLOCKS_CLK_GPOUT0_CTRL_PHASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_CTRL_DC50
// Description : Enables duty cycle correction for odd divisors
#define CLOCKS_CLK_GPOUT0_CTRL_DC50_RESET  0x0
#define CLOCKS_CLK_GPOUT0_CTRL_DC50_BITS   0x00001000
#define CLOCKS_CLK_GPOUT0_CTRL_DC50_MSB    12
#define CLOCKS_CLK_GPOUT0_CTRL_DC50_LSB    12
#define CLOCKS_CLK_GPOUT0_CTRL_DC50_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_GPOUT0_CTRL_ENABLE_RESET  0x0
#define CLOCKS_CLK_GPOUT0_CTRL_ENABLE_BITS   0x00000800
#define CLOCKS_CLK_GPOUT0_CTRL_ENABLE_MSB    11
#define CLOCKS_CLK_GPOUT0_CTRL_ENABLE_LSB    11
#define CLOCKS_CLK_GPOUT0_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_GPOUT0_CTRL_KILL_RESET  0x0
#define CLOCKS_CLK_GPOUT0_CTRL_KILL_BITS   0x00000400
#define CLOCKS_CLK_GPOUT0_CTRL_KILL_MSB    10
#define CLOCKS_CLK_GPOUT0_CTRL_KILL_LSB    10
#define CLOCKS_CLK_GPOUT0_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_sys
//               0x1 -> clksrc_gpin0
//               0x2 -> clksrc_gpin1
//               0x3 -> clksrc_pll_usb
//               0x4 -> rosc_clksrc
//               0x5 -> xosc_clksrc
//               0x6 -> clk_sys
//               0x7 -> clk_usb
//               0x8 -> clk_adc
//               0x9 -> clk_rtc
//               0xa -> clk_ref
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_RESET                0x0
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_BITS                 0x000001e0
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_MSB                  8
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_LSB                  5
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS 0x0
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   0x1
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   0x2
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB 0x3
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_ROSC_CLKSRC    0x4
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    0x5
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_SYS        0x6
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_USB        0x7
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_ADC        0x8
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_RTC        0x9
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_REF        0xa
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT0_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_GPOUT0_DIV_OFFSET 0x00000004
#define CLOCKS_CLK_GPOUT0_DIV_BITS   0xffffffff
#define CLOCKS_CLK_GPOUT0_DIV_RESET  0x00000100
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_GPOUT0_DIV_INT_RESET  0x000001
#define CLOCKS_CLK_GPOUT0_DIV_INT_BITS   0xffffff00
#define CLOCKS_CLK_GPOUT0_DIV_INT_MSB    31
#define CLOCKS_CLK_GPOUT0_DIV_INT_LSB    8
#define CLOCKS_CLK_GPOUT0_DIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_DIV_FRAC
// Description : Fractional component of the divisor
#define CLOCKS_CLK_GPOUT0_DIV_FRAC_RESET  0x00
#define CLOCKS_CLK_GPOUT0_DIV_FRAC_BITS   0x000000ff
#define CLOCKS_CLK_GPOUT0_DIV_FRAC_MSB    7
#define CLOCKS_CLK_GPOUT0_DIV_FRAC_LSB    0
#define CLOCKS_CLK_GPOUT0_DIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT0_SELECTED
// Description : Indicates which src is currently selected (one-hot)
#define CLOCKS_CLK_GPOUT0_SELECTED_OFFSET 0x00000008
#define CLOCKS_CLK_GPOUT0_SELECTED_BITS   0xffffffff
#define CLOCKS_CLK_GPOUT0_SELECTED_RESET  0x00000001
#define CLOCKS_CLK_GPOUT0_SELECTED_MSB    31
#define CLOCKS_CLK_GPOUT0_SELECTED_LSB    0
#define CLOCKS_CLK_GPOUT0_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT1_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_GPOUT1_CTRL_OFFSET 0x0000000c
#define CLOCKS_CLK_GPOUT1_CTRL_BITS   0x00131de0
#define CLOCKS_CLK_GPOUT1_CTRL_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_CTRL_NUDGE
// Description : An edge on this signal shifts the phase of the output by 1
//               cycle of the input clock
//               This can be done at any time
#define CLOCKS_CLK_GPOUT1_CTRL_NUDGE_RESET  0x0
#define CLOCKS_CLK_GPOUT1_CTRL_NUDGE_BITS   0x00100000
#define CLOCKS_CLK_GPOUT1_CTRL_NUDGE_MSB    20
#define CLOCKS_CLK_GPOUT1_CTRL_NUDGE_LSB    20
#define CLOCKS_CLK_GPOUT1_CTRL_NUDGE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_CTRL_PHASE
// Description : This delays the enable signal by up to 3 cycles of the input
//               clock
//               This must be set before the clock is enabled to have any effect
#define CLOCKS_CLK_GPOUT1_CTRL_PHASE_RESET  0x0
#define CLOCKS_CLK_GPOUT1_CTRL_PHASE_BITS   0x00030000
#define CLOCKS_CLK_GPOUT1_CTRL_PHASE_MSB    17
#define CLOCKS_CLK_GPOUT1_CTRL_PHASE_LSB    16
#define CLOCKS_CLK_GPOUT1_CTRL_PHASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_CTRL_DC50
// Description : Enables duty cycle correction for odd divisors
#define CLOCKS_CLK_GPOUT1_CTRL_DC50_RESET  0x0
#define CLOCKS_CLK_GPOUT1_CTRL_DC50_BITS   0x00001000
#define CLOCKS_CLK_GPOUT1_CTRL_DC50_MSB    12
#define CLOCKS_CLK_GPOUT1_CTRL_DC50_LSB    12
#define CLOCKS_CLK_GPOUT1_CTRL_DC50_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_GPOUT1_CTRL_ENABLE_RESET  0x0
#define CLOCKS_CLK_GPOUT1_CTRL_ENABLE_BITS   0x00000800
#define CLOCKS_CLK_GPOUT1_CTRL_ENABLE_MSB    11
#define CLOCKS_CLK_GPOUT1_CTRL_ENABLE_LSB    11
#define CLOCKS_CLK_GPOUT1_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_GPOUT1_CTRL_KILL_RESET  0x0
#define CLOCKS_CLK_GPOUT1_CTRL_KILL_BITS   0x00000400
#define CLOCKS_CLK_GPOUT1_CTRL_KILL_MSB    10
#define CLOCKS_CLK_GPOUT1_CTRL_KILL_LSB    10
#define CLOCKS_CLK_GPOUT1_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_sys
//               0x1 -> clksrc_gpin0
//               0x2 -> clksrc_gpin1
//               0x3 -> clksrc_pll_usb
//               0x4 -> rosc_clksrc
//               0x5 -> xosc_clksrc
//               0x6 -> clk_sys
//               0x7 -> clk_usb
//               0x8 -> clk_adc
//               0x9 -> clk_rtc
//               0xa -> clk_ref
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_RESET                0x0
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_BITS                 0x000001e0
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_MSB                  8
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_LSB                  5
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS 0x0
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   0x1
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   0x2
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB 0x3
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_ROSC_CLKSRC    0x4
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    0x5
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLK_SYS        0x6
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLK_USB        0x7
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLK_ADC        0x8
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLK_RTC        0x9
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLK_REF        0xa
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT1_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_GPOUT1_DIV_OFFSET 0x00000010
#define CLOCKS_CLK_GPOUT1_DIV_BITS   0xffffffff
#define CLOCKS_CLK_GPOUT1_DIV_RESET  0x00000100
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_GPOUT1_DIV_INT_RESET  0x000001
#define CLOCKS_CLK_GPOUT1_DIV_INT_BITS   0xffffff00
#define CLOCKS_CLK_GPOUT1_DIV_INT_MSB    31
#define CLOCKS_CLK_GPOUT1_DIV_INT_LSB    8
#define CLOCKS_CLK_GPOUT1_DIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_DIV_FRAC
// Description : Fractional component of the divisor
#define CLOCKS_CLK_GPOUT1_DIV_FRAC_RESET  0x00
#define CLOCKS_CLK_GPOUT1_DIV_FRAC_BITS   0x000000ff
#define CLOCKS_CLK_GPOUT1_DIV_FRAC_MSB    7
#define CLOCKS_CLK_GPOUT1_DIV_FRAC_LSB    0
#define CLOCKS_CLK_GPOUT1_DIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT1_SELECTED
// Description : Indicates which src is currently selected (one-hot)
#define CLOCKS_CLK_GPOUT1_SELECTED_OFFSET 0x00000014
#define CLOCKS_CLK_GPOUT1_SELECTED_BITS   0xffffffff
#define CLOCKS_CLK_GPOUT1_SELECTED_RESET  0x00000001
#define CLOCKS_CLK_GPOUT1_SELECTED_MSB    31
#define CLOCKS_CLK_GPOUT1_SELECTED_LSB    0
#define CLOCKS_CLK_GPOUT1_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT2_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_GPOUT2_CTRL_OFFSET 0x00000018
#define CLOCKS_CLK_GPOUT2_CTRL_BITS   0x00131de0
#define CLOCKS_CLK_GPOUT2_CTRL_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_CTRL_NUDGE
// Description : An edge on this signal shifts the phase of the output by 1
//               cycle of the input clock
//               This can be done at any time
#define CLOCKS_CLK_GPOUT2_CTRL_NUDGE_RESET  0x0
#define CLOCKS_CLK_GPOUT2_CTRL_NUDGE_BITS   0x00100000
#define CLOCKS_CLK_GPOUT2_CTRL_NUDGE_MSB    20
#define CLOCKS_CLK_GPOUT2_CTRL_NUDGE_LSB    20
#define CLOCKS_CLK_GPOUT2_CTRL_NUDGE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_CTRL_PHASE
// Description : This delays the enable signal by up to 3 cycles of the input
//               clock
//               This must be set before the clock is enabled to have any effect
#define CLOCKS_CLK_GPOUT2_CTRL_PHASE_RESET  0x0
#define CLOCKS_CLK_GPOUT2_CTRL_PHASE_BITS   0x00030000
#define CLOCKS_CLK_GPOUT2_CTRL_PHASE_MSB    17
#define CLOCKS_CLK_GPOUT2_CTRL_PHASE_LSB    16
#define CLOCKS_CLK_GPOUT2_CTRL_PHASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_CTRL_DC50
// Description : Enables duty cycle correction for odd divisors
#define CLOCKS_CLK_GPOUT2_CTRL_DC50_RESET  0x0
#define CLOCKS_CLK_GPOUT2_CTRL_DC50_BITS   0x00001000
#define CLOCKS_CLK_GPOUT2_CTRL_DC50_MSB    12
#define CLOCKS_CLK_GPOUT2_CTRL_DC50_LSB    12
#define CLOCKS_CLK_GPOUT2_CTRL_DC50_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_GPOUT2_CTRL_ENABLE_RESET  0x0
#define CLOCKS_CLK_GPOUT2_CTRL_ENABLE_BITS   0x00000800
#define CLOCKS_CLK_GPOUT2_CTRL_ENABLE_MSB    11
#define CLOCKS_CLK_GPOUT2_CTRL_ENABLE_LSB    11
#define CLOCKS_CLK_GPOUT2_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_GPOUT2_CTRL_KILL_RESET  0x0
#define CLOCKS_CLK_GPOUT2_CTRL_KILL_BITS   0x00000400
#define CLOCKS_CLK_GPOUT2_CTRL_KILL_MSB    10
#define CLOCKS_CLK_GPOUT2_CTRL_KILL_LSB    10
#define CLOCKS_CLK_GPOUT2_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_sys
//               0x1 -> clksrc_gpin0
//               0x2 -> clksrc_gpin1
//               0x3 -> clksrc_pll_usb
//               0x4 -> rosc_clksrc_ph
//               0x5 -> xosc_clksrc
//               0x6 -> clk_sys
//               0x7 -> clk_usb
//               0x8 -> clk_adc
//               0x9 -> clk_rtc
//               0xa -> clk_ref
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_RESET                0x0
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_BITS                 0x000001e0
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_MSB                  8
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_LSB                  5
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS 0x0
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   0x1
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   0x2
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB 0x3
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH 0x4
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    0x5
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLK_SYS        0x6
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLK_USB        0x7
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLK_ADC        0x8
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLK_RTC        0x9
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLK_REF        0xa
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT2_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_GPOUT2_DIV_OFFSET 0x0000001c
#define CLOCKS_CLK_GPOUT2_DIV_BITS   0xffffffff
#define CLOCKS_CLK_GPOUT2_DIV_RESET  0x00000100
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_GPOUT2_DIV_INT_RESET  0x000001
#define CLOCKS_CLK_GPOUT2_DIV_INT_BITS   0xffffff00
#define CLOCKS_CLK_GPOUT2_DIV_INT_MSB    31
#define CLOCKS_CLK_GPOUT2_DIV_INT_LSB    8
#define CLOCKS_CLK_GPOUT2_DIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_DIV_FRAC
// Description : Fractional component of the divisor
#define CLOCKS_CLK_GPOUT2_DIV_FRAC_RESET  0x00
#define CLOCKS_CLK_GPOUT2_DIV_FRAC_BITS   0x000000ff
#define CLOCKS_CLK_GPOUT2_DIV_FRAC_MSB    7
#define CLOCKS_CLK_GPOUT2_DIV_FRAC_LSB    0
#define CLOCKS_CLK_GPOUT2_DIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT2_SELECTED
// Description : Indicates which src is currently selected (one-hot)
#define CLOCKS_CLK_GPOUT2_SELECTED_OFFSET 0x00000020
#define CLOCKS_CLK_GPOUT2_SELECTED_BITS   0xffffffff
#define CLOCKS_CLK_GPOUT2_SELECTED_RESET  0x00000001
#define CLOCKS_CLK_GPOUT2_SELECTED_MSB    31
#define CLOCKS_CLK_GPOUT2_SELECTED_LSB    0
#define CLOCKS_CLK_GPOUT2_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT3_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_GPOUT3_CTRL_OFFSET 0x00000024
#define CLOCKS_CLK_GPOUT3_CTRL_BITS   0x00131de0
#define CLOCKS_CLK_GPOUT3_CTRL_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_CTRL_NUDGE
// Description : An edge on this signal shifts the phase of the output by 1
//               cycle of the input clock
//               This can be done at any time
#define CLOCKS_CLK_GPOUT3_CTRL_NUDGE_RESET  0x0
#define CLOCKS_CLK_GPOUT3_CTRL_NUDGE_BITS   0x00100000
#define CLOCKS_CLK_GPOUT3_CTRL_NUDGE_MSB    20
#define CLOCKS_CLK_GPOUT3_CTRL_NUDGE_LSB    20
#define CLOCKS_CLK_GPOUT3_CTRL_NUDGE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_CTRL_PHASE
// Description : This delays the enable signal by up to 3 cycles of the input
//               clock
//               This must be set before the clock is enabled to have any effect
#define CLOCKS_CLK_GPOUT3_CTRL_PHASE_RESET  0x0
#define CLOCKS_CLK_GPOUT3_CTRL_PHASE_BITS   0x00030000
#define CLOCKS_CLK_GPOUT3_CTRL_PHASE_MSB    17
#define CLOCKS_CLK_GPOUT3_CTRL_PHASE_LSB    16
#define CLOCKS_CLK_GPOUT3_CTRL_PHASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_CTRL_DC50
// Description : Enables duty cycle correction for odd divisors
#define CLOCKS_CLK_GPOUT3_CTRL_DC50_RESET  0x0
#define CLOCKS_CLK_GPOUT3_CTRL_DC50_BITS   0x00001000
#define CLOCKS_CLK_GPOUT3_CTRL_DC50_MSB    12
#define CLOCKS_CLK_GPOUT3_CTRL_DC50_LSB    12
#define CLOCKS_CLK_GPOUT3_CTRL_DC50_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_GPOUT3_CTRL_ENABLE_RESET  0x0
#define CLOCKS_CLK_GPOUT3_CTRL_ENABLE_BITS   0x00000800
#define CLOCKS_CLK_GPOUT3_CTRL_ENABLE_MSB    11
#define CLOCKS_CLK_GPOUT3_CTRL_ENABLE_LSB    11
#define CLOCKS_CLK_GPOUT3_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_GPOUT3_CTRL_KILL_RESET  0x0
#define CLOCKS_CLK_GPOUT3_CTRL_KILL_BITS   0x00000400
#define CLOCKS_CLK_GPOUT3_CTRL_KILL_MSB    10
#define CLOCKS_CLK_GPOUT3_CTRL_KILL_LSB    10
#define CLOCKS_CLK_GPOUT3_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_sys
//               0x1 -> clksrc_gpin0
//               0x2 -> clksrc_gpin1
//               0x3 -> clksrc_pll_usb
//               0x4 -> rosc_clksrc_ph
//               0x5 -> xosc_clksrc
//               0x6 -> clk_sys
//               0x7 -> clk_usb
//               0x8 -> clk_adc
//               0x9 -> clk_rtc
//               0xa -> clk_ref
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_RESET                0x0
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_BITS                 0x000001e0
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_MSB                  8
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_LSB                  5
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS 0x0
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   0x1
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   0x2
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB 0x3
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH 0x4
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    0x5
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLK_SYS        0x6
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLK_USB        0x7
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLK_ADC        0x8
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLK_RTC        0x9
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLK_REF        0xa
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT3_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_GPOUT3_DIV_OFFSET 0x00000028
#define CLOCKS_CLK_GPOUT3_DIV_BITS   0xffffffff
#define CLOCKS_CLK_GPOUT3_DIV_RESET  0x00000100
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_GPOUT3_DIV_INT_RESET  0x000001
#define CLOCKS_CLK_GPOUT3_DIV_INT_BITS   0xffffff00
#define CLOCKS_CLK_GPOUT3_DIV_INT_MSB    31
#define CLOCKS_CLK_GPOUT3_DIV_INT_LSB    8
#define CLOCKS_CLK_GPOUT3_DIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_DIV_FRAC
// Description : Fractional component of the divisor
#define CLOCKS_CLK_GPOUT3_DIV_FRAC_RESET  0x00
#define CLOCKS_CLK_GPOUT3_DIV_FRAC_BITS   0x000000ff
#define CLOCKS_CLK_GPOUT3_DIV_FRAC_MSB    7
#define CLOCKS_CLK_GPOUT3_DIV_FRAC_LSB    0
#define CLOCKS_CLK_GPOUT3_DIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT3_SELECTED
// Description : Indicates which src is currently selected (one-hot)
#define CLOCKS_CLK_GPOUT3_SELECTED_OFFSET 0x0000002c
#define CLOCKS_CLK_GPOUT3_SELECTED_BITS   0xffffffff
#define CLOCKS_CLK_GPOUT3_SELECTED_RESET  0x00000001
#define CLOCKS_CLK_GPOUT3_SELECTED_MSB    31
#define CLOCKS_CLK_GPOUT3_SELECTED_LSB    0
#define CLOCKS_CLK_GPOUT3_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_REF_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_REF_CTRL_OFFSET 0x00000030
#define CLOCKS_CLK_REF_CTRL_BITS   0x00000063
#define CLOCKS_CLK_REF_CTRL_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_REF_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_usb
//               0x1 -> clksrc_gpin0
//               0x2 -> clksrc_gpin1
#define CLOCKS_CLK_REF_CTRL_AUXSRC_RESET                0x0
#define CLOCKS_CLK_REF_CTRL_AUXSRC_BITS                 0x00000060
#define CLOCKS_CLK_REF_CTRL_AUXSRC_MSB                  6
#define CLOCKS_CLK_REF_CTRL_AUXSRC_LSB                  5
#define CLOCKS_CLK_REF_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_REF_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB 0x0
#define CLOCKS_CLK_REF_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   0x1
#define CLOCKS_CLK_REF_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   0x2
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_REF_CTRL_SRC
// Description : Selects the clock source glitchlessly, can be changed
//               on-the-fly
//               0x0 -> rosc_clksrc_ph
//               0x1 -> clksrc_clk_ref_aux
//               0x2 -> xosc_clksrc
#define CLOCKS_CLK_REF_CTRL_SRC_RESET                    "-"
#define CLOCKS_CLK_REF_CTRL_SRC_BITS                     0x00000003
#define CLOCKS_CLK_REF_CTRL_SRC_MSB                      1
#define CLOCKS_CLK_REF_CTRL_SRC_LSB                      0
#define CLOCKS_CLK_REF_CTRL_SRC_ACCESS                   "RW"
#define CLOCKS_CLK_REF_CTRL_SRC_VALUE_ROSC_CLKSRC_PH     0x0
#define CLOCKS_CLK_REF_CTRL_SRC_VALUE_CLKSRC_CLK_REF_AUX 0x1
#define CLOCKS_CLK_REF_CTRL_SRC_VALUE_XOSC_CLKSRC        0x2
// =============================================================================
// Register    : CLOCKS_CLK_REF_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_REF_DIV_OFFSET 0x00000034
#define CLOCKS_CLK_REF_DIV_BITS   0x00000300
#define CLOCKS_CLK_REF_DIV_RESET  0x00000100
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_REF_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_REF_DIV_INT_RESET  0x1
#define CLOCKS_CLK_REF_DIV_INT_BITS   0x00000300
#define CLOCKS_CLK_REF_DIV_INT_MSB    9
#define CLOCKS_CLK_REF_DIV_INT_LSB    8
#define CLOCKS_CLK_REF_DIV_INT_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_REF_SELECTED
// Description : Indicates which src is currently selected (one-hot)
#define CLOCKS_CLK_REF_SELECTED_OFFSET 0x00000038
#define CLOCKS_CLK_REF_SELECTED_BITS   0xffffffff
#define CLOCKS_CLK_REF_SELECTED_RESET  0x00000001
#define CLOCKS_CLK_REF_SELECTED_MSB    31
#define CLOCKS_CLK_REF_SELECTED_LSB    0
#define CLOCKS_CLK_REF_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_SYS_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_SYS_CTRL_OFFSET 0x0000003c
#define CLOCKS_CLK_SYS_CTRL_BITS   0x000000e1
#define CLOCKS_CLK_SYS_CTRL_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_sys
//               0x1 -> clksrc_pll_usb
//               0x2 -> rosc_clksrc
//               0x3 -> xosc_clksrc
//               0x4 -> clksrc_gpin0
//               0x5 -> clksrc_gpin1
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_RESET                0x0
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_BITS                 0x000000e0
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_MSB                  7
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_LSB                  5
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS 0x0
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB 0x1
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_ROSC_CLKSRC    0x2
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    0x3
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   0x4
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   0x5
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_CTRL_SRC
// Description : Selects the clock source glitchlessly, can be changed
//               on-the-fly
//               0x0 -> clk_ref
//               0x1 -> clksrc_clk_sys_aux
#define CLOCKS_CLK_SYS_CTRL_SRC_RESET                    0x0
#define CLOCKS_CLK_SYS_CTRL_SRC_BITS                     0x00000001
#define CLOCKS_CLK_SYS_CTRL_SRC_MSB                      0
#define CLOCKS_CLK_SYS_CTRL_SRC_LSB                      0
#define CLOCKS_CLK_SYS_CTRL_SRC_ACCESS                   "RW"
#define CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLK_REF            0x0
#define CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX 0x1
// =============================================================================
// Register    : CLOCKS_CLK_SYS_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_SYS_DIV_OFFSET 0x00000040
#define CLOCKS_CLK_SYS_DIV_BITS   0xffffffff
#define CLOCKS_CLK_SYS_DIV_RESET  0x00000100
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_SYS_DIV_INT_RESET  0x000001
#define CLOCKS_CLK_SYS_DIV_INT_BITS   0xffffff00
#define CLOCKS_CLK_SYS_DIV_INT_MSB    31
#define CLOCKS_CLK_SYS_DIV_INT_LSB    8
#define CLOCKS_CLK_SYS_DIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_DIV_FRAC
// Description : Fractional component of the divisor
#define CLOCKS_CLK_SYS_DIV_FRAC_RESET  0x00
#define CLOCKS_CLK_SYS_DIV_FRAC_BITS   0x000000ff
#define CLOCKS_CLK_SYS_DIV_FRAC_MSB    7
#define CLOCKS_CLK_SYS_DIV_FRAC_LSB    0
#define CLOCKS_CLK_SYS_DIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_SYS_SELECTED
// Description : Indicates which src is currently selected (one-hot)
#define CLOCKS_CLK_SYS_SELECTED_OFFSET 0x00000044
#define CLOCKS_CLK_SYS_SELECTED_BITS   0xffffffff
#define CLOCKS_CLK_SYS_SELECTED_RESET  0x00000001
#define CLOCKS_CLK_SYS_SELECTED_MSB    31
#define CLOCKS_CLK_SYS_SELECTED_LSB    0
#define CLOCKS_CLK_SYS_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_PERI_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_PERI_CTRL_OFFSET 0x00000048
#define CLOCKS_CLK_PERI_CTRL_BITS   0x00000ce0
#define CLOCKS_CLK_PERI_CTRL_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_PERI_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_PERI_CTRL_ENABLE_RESET  0x0
#define CLOCKS_CLK_PERI_CTRL_ENABLE_BITS   0x00000800
#define CLOCKS_CLK_PERI_CTRL_ENABLE_MSB    11
#define CLOCKS_CLK_PERI_CTRL_ENABLE_LSB    11
#define CLOCKS_CLK_PERI_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_PERI_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_PERI_CTRL_KILL_RESET  0x0
#define CLOCKS_CLK_PERI_CTRL_KILL_BITS   0x00000400
#define CLOCKS_CLK_PERI_CTRL_KILL_MSB    10
#define CLOCKS_CLK_PERI_CTRL_KILL_LSB    10
#define CLOCKS_CLK_PERI_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_PERI_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clk_sys
//               0x1 -> clksrc_pll_sys
//               0x2 -> clksrc_pll_usb
//               0x3 -> rosc_clksrc_ph
//               0x4 -> xosc_clksrc
//               0x5 -> clksrc_gpin0
//               0x6 -> clksrc_gpin1
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_RESET                0x0
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_BITS                 0x000000e0
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_MSB                  7
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_LSB                  5
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS        0x0
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS 0x1
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB 0x2
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH 0x3
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    0x4
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   0x5
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   0x6
// =============================================================================
// Register    : CLOCKS_CLK_PERI_SELECTED
// Description : Indicates which src is currently selected (one-hot)
#define CLOCKS_CLK_PERI_SELECTED_OFFSET 0x00000050
#define CLOCKS_CLK_PERI_SELECTED_BITS   0xffffffff
#define CLOCKS_CLK_PERI_SELECTED_RESET  0x00000001
#define CLOCKS_CLK_PERI_SELECTED_MSB    31
#define CLOCKS_CLK_PERI_SELECTED_LSB    0
#define CLOCKS_CLK_PERI_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_USB_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_USB_CTRL_OFFSET 0x00000054
#define CLOCKS_CLK_USB_CTRL_BITS   0x00130ce0
#define CLOCKS_CLK_USB_CTRL_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_USB_CTRL_NUDGE
// Description : An edge on this signal shifts the phase of the output by 1
//               cycle of the input clock
//               This can be done at any time
#define CLOCKS_CLK_USB_CTRL_NUDGE_RESET  0x0
#define CLOCKS_CLK_USB_CTRL_NUDGE_BITS   0x00100000
#define CLOCKS_CLK_USB_CTRL_NUDGE_MSB    20
#define CLOCKS_CLK_USB_CTRL_NUDGE_LSB    20
#define CLOCKS_CLK_USB_CTRL_NUDGE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_USB_CTRL_PHASE
// Description : This delays the enable signal by up to 3 cycles of the input
//               clock
//               This must be set before the clock is enabled to have any effect
#define CLOCKS_CLK_USB_CTRL_PHASE_RESET  0x0
#define CLOCKS_CLK_USB_CTRL_PHASE_BITS   0x00030000
#define CLOCKS_CLK_USB_CTRL_PHASE_MSB    17
#define CLOCKS_CLK_USB_CTRL_PHASE_LSB    16
#define CLOCKS_CLK_USB_CTRL_PHASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_USB_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_USB_CTRL_ENABLE_RESET  0x0
#define CLOCKS_CLK_USB_CTRL_ENABLE_BITS   0x00000800
#define CLOCKS_CLK_USB_CTRL_ENABLE_MSB    11
#define CLOCKS_CLK_USB_CTRL_ENABLE_LSB    11
#define CLOCKS_CLK_USB_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_USB_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_USB_CTRL_KILL_RESET  0x0
#define CLOCKS_CLK_USB_CTRL_KILL_BITS   0x00000400
#define CLOCKS_CLK_USB_CTRL_KILL_MSB    10
#define CLOCKS_CLK_USB_CTRL_KILL_LSB    10
#define CLOCKS_CLK_USB_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_USB_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_usb
//               0x1 -> clksrc_pll_sys
//               0x2 -> rosc_clksrc_ph
//               0x3 -> xosc_clksrc
//               0x4 -> clksrc_gpin0
//               0x5 -> clksrc_gpin1
#define CLOCKS_CLK_USB_CTRL_AUXSRC_RESET                0x0
#define CLOCKS_CLK_USB_CTRL_AUXSRC_BITS                 0x000000e0
#define CLOCKS_CLK_USB_CTRL_AUXSRC_MSB                  7
#define CLOCKS_CLK_USB_CTRL_AUXSRC_LSB                  5
#define CLOCKS_CLK_USB_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB 0x0
#define CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS 0x1
#define CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH 0x2
#define CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    0x3
#define CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   0x4
#define CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   0x5
// =============================================================================
// Register    : CLOCKS_CLK_USB_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_USB_DIV_OFFSET 0x00000058
#define CLOCKS_CLK_USB_DIV_BITS   0x00000300
#define CLOCKS_CLK_USB_DIV_RESET  0x00000100
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_USB_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_USB_DIV_INT_RESET  0x1
#define CLOCKS_CLK_USB_DIV_INT_BITS   0x00000300
#define CLOCKS_CLK_USB_DIV_INT_MSB    9
#define CLOCKS_CLK_USB_DIV_INT_LSB    8
#define CLOCKS_CLK_USB_DIV_INT_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_USB_SELECTED
// Description : Indicates which src is currently selected (one-hot)
#define CLOCKS_CLK_USB_SELECTED_OFFSET 0x0000005c
#define CLOCKS_CLK_USB_SELECTED_BITS   0xffffffff
#define CLOCKS_CLK_USB_SELECTED_RESET  0x00000001
#define CLOCKS_CLK_USB_SELECTED_MSB    31
#define CLOCKS_CLK_USB_SELECTED_LSB    0
#define CLOCKS_CLK_USB_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_ADC_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_ADC_CTRL_OFFSET 0x00000060
#define CLOCKS_CLK_ADC_CTRL_BITS   0x00130ce0
#define CLOCKS_CLK_ADC_CTRL_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_ADC_CTRL_NUDGE
// Description : An edge on this signal shifts the phase of the output by 1
//               cycle of the input clock
//               This can be done at any time
#define CLOCKS_CLK_ADC_CTRL_NUDGE_RESET  0x0
#define CLOCKS_CLK_ADC_CTRL_NUDGE_BITS   0x00100000
#define CLOCKS_CLK_ADC_CTRL_NUDGE_MSB    20
#define CLOCKS_CLK_ADC_CTRL_NUDGE_LSB    20
#define CLOCKS_CLK_ADC_CTRL_NUDGE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_ADC_CTRL_PHASE
// Description : This delays the enable signal by up to 3 cycles of the input
//               clock
//               This must be set before the clock is enabled to have any effect
#define CLOCKS_CLK_ADC_CTRL_PHASE_RESET  0x0
#define CLOCKS_CLK_ADC_CTRL_PHASE_BITS   0x00030000
#define CLOCKS_CLK_ADC_CTRL_PHASE_MSB    17
#define CLOCKS_CLK_ADC_CTRL_PHASE_LSB    16
#define CLOCKS_CLK_ADC_CTRL_PHASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_ADC_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_ADC_CTRL_ENABLE_RESET  0x0
#define CLOCKS_CLK_ADC_CTRL_ENABLE_BITS   0x00000800
#define CLOCKS_CLK_ADC_CTRL_ENABLE_MSB    11
#define CLOCKS_CLK_ADC_CTRL_ENABLE_LSB    11
#define CLOCKS_CLK_ADC_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_ADC_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_ADC_CTRL_KILL_RESET  0x0
#define CLOCKS_CLK_ADC_CTRL_KILL_BITS   0x00000400
#define CLOCKS_CLK_ADC_CTRL_KILL_MSB    10
#define CLOCKS_CLK_ADC_CTRL_KILL_LSB    10
#define CLOCKS_CLK_ADC_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_ADC_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_usb
//               0x1 -> clksrc_pll_sys
//               0x2 -> rosc_clksrc_ph
//               0x3 -> xosc_clksrc
//               0x4 -> clksrc_gpin0
//               0x5 -> clksrc_gpin1
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_RESET                0x0
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_BITS                 0x000000e0
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_MSB                  7
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_LSB                  5
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB 0x0
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS 0x1
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH 0x2
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    0x3
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   0x4
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   0x5
// =============================================================================
// Register    : CLOCKS_CLK_ADC_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_ADC_DIV_OFFSET 0x00000064
#define CLOCKS_CLK_ADC_DIV_BITS   0x00000300
#define CLOCKS_CLK_ADC_DIV_RESET  0x00000100
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_ADC_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_ADC_DIV_INT_RESET  0x1
#define CLOCKS_CLK_ADC_DIV_INT_BITS   0x00000300
#define CLOCKS_CLK_ADC_DIV_INT_MSB    9
#define CLOCKS_CLK_ADC_DIV_INT_LSB    8
#define CLOCKS_CLK_ADC_DIV_INT_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_ADC_SELECTED
// Description : Indicates which src is currently selected (one-hot)
#define CLOCKS_CLK_ADC_SELECTED_OFFSET 0x00000068
#define CLOCKS_CLK_ADC_SELECTED_BITS   0xffffffff
#define CLOCKS_CLK_ADC_SELECTED_RESET  0x00000001
#define CLOCKS_CLK_ADC_SELECTED_MSB    31
#define CLOCKS_CLK_ADC_SELECTED_LSB    0
#define CLOCKS_CLK_ADC_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_RTC_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_RTC_CTRL_OFFSET 0x0000006c
#define CLOCKS_CLK_RTC_CTRL_BITS   0x00130ce0
#define CLOCKS_CLK_RTC_CTRL_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_RTC_CTRL_NUDGE
// Description : An edge on this signal shifts the phase of the output by 1
//               cycle of the input clock
//               This can be done at any time
#define CLOCKS_CLK_RTC_CTRL_NUDGE_RESET  0x0
#define CLOCKS_CLK_RTC_CTRL_NUDGE_BITS   0x00100000
#define CLOCKS_CLK_RTC_CTRL_NUDGE_MSB    20
#define CLOCKS_CLK_RTC_CTRL_NUDGE_LSB    20
#define CLOCKS_CLK_RTC_CTRL_NUDGE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_RTC_CTRL_PHASE
// Description : This delays the enable signal by up to 3 cycles of the input
//               clock
//               This must be set before the clock is enabled to have any effect
#define CLOCKS_CLK_RTC_CTRL_PHASE_RESET  0x0
#define CLOCKS_CLK_RTC_CTRL_PHASE_BITS   0x00030000
#define CLOCKS_CLK_RTC_CTRL_PHASE_MSB    17
#define CLOCKS_CLK_RTC_CTRL_PHASE_LSB    16
#define CLOCKS_CLK_RTC_CTRL_PHASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_RTC_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_RTC_CTRL_ENABLE_RESET  0x0
#define CLOCKS_CLK_RTC_CTRL_ENABLE_BITS   0x00000800
#define CLOCKS_CLK_RTC_CTRL_ENABLE_MSB    11
#define CLOCKS_CLK_RTC_CTRL_ENABLE_LSB    11
#define CLOCKS_CLK_RTC_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_RTC_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_RTC_CTRL_KILL_RESET  0x0
#define CLOCKS_CLK_RTC_CTRL_KILL_BITS   0x00000400
#define CLOCKS_CLK_RTC_CTRL_KILL_MSB    10
#define CLOCKS_CLK_RTC_CTRL_KILL_LSB    10
#define CLOCKS_CLK_RTC_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_RTC_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_usb
//               0x1 -> clksrc_pll_sys
//               0x2 -> rosc_clksrc_ph
//               0x3 -> xosc_clksrc
//               0x4 -> clksrc_gpin0
//               0x5 -> clksrc_gpin1
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_RESET                0x0
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_BITS                 0x000000e0
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_MSB                  7
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_LSB                  5
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB 0x0
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS 0x1
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH 0x2
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    0x3
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   0x4
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   0x5
// =============================================================================
// Register    : CLOCKS_CLK_RTC_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_RTC_DIV_OFFSET 0x00000070
#define CLOCKS_CLK_RTC_DIV_BITS   0xffffffff
#define CLOCKS_CLK_RTC_DIV_RESET  0x00000100
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_RTC_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_RTC_DIV_INT_RESET  0x000001
#define CLOCKS_CLK_RTC_DIV_INT_BITS   0xffffff00
#define CLOCKS_CLK_RTC_DIV_INT_MSB    31
#define CLOCKS_CLK_RTC_DIV_INT_LSB    8
#define CLOCKS_CLK_RTC_DIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_RTC_DIV_FRAC
// Description : Fractional component of the divisor
#define CLOCKS_CLK_RTC_DIV_FRAC_RESET  0x00
#define CLOCKS_CLK_RTC_DIV_FRAC_BITS   0x000000ff
#define CLOCKS_CLK_RTC_DIV_FRAC_MSB    7
#define CLOCKS_CLK_RTC_DIV_FRAC_LSB    0
#define CLOCKS_CLK_RTC_DIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_RTC_SELECTED
// Description : Indicates which src is currently selected (one-hot)
#define CLOCKS_CLK_RTC_SELECTED_OFFSET 0x00000074
#define CLOCKS_CLK_RTC_SELECTED_BITS   0xffffffff
#define CLOCKS_CLK_RTC_SELECTED_RESET  0x00000001
#define CLOCKS_CLK_RTC_SELECTED_MSB    31
#define CLOCKS_CLK_RTC_SELECTED_LSB    0
#define CLOCKS_CLK_RTC_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_SYS_RESUS_CTRL
// Description : None
#define CLOCKS_CLK_SYS_RESUS_CTRL_OFFSET 0x00000078
#define CLOCKS_CLK_SYS_RESUS_CTRL_BITS   0x000111ff
#define CLOCKS_CLK_SYS_RESUS_CTRL_RESET  0x000000ff
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_RESUS_CTRL_CLEAR
// Description : For clearing the resus after the fault that triggered it has
//               been corrected
#define CLOCKS_CLK_SYS_RESUS_CTRL_CLEAR_RESET  0x0
#define CLOCKS_CLK_SYS_RESUS_CTRL_CLEAR_BITS   0x00010000
#define CLOCKS_CLK_SYS_RESUS_CTRL_CLEAR_MSB    16
#define CLOCKS_CLK_SYS_RESUS_CTRL_CLEAR_LSB    16
#define CLOCKS_CLK_SYS_RESUS_CTRL_CLEAR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_RESUS_CTRL_FRCE
// Description : Force a resus, for test purposes only
#define CLOCKS_CLK_SYS_RESUS_CTRL_FRCE_RESET  0x0
#define CLOCKS_CLK_SYS_RESUS_CTRL_FRCE_BITS   0x00001000
#define CLOCKS_CLK_SYS_RESUS_CTRL_FRCE_MSB    12
#define CLOCKS_CLK_SYS_RESUS_CTRL_FRCE_LSB    12
#define CLOCKS_CLK_SYS_RESUS_CTRL_FRCE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_RESUS_CTRL_ENABLE
// Description : Enable resus
#define CLOCKS_CLK_SYS_RESUS_CTRL_ENABLE_RESET  0x0
#define CLOCKS_CLK_SYS_RESUS_CTRL_ENABLE_BITS   0x00000100
#define CLOCKS_CLK_SYS_RESUS_CTRL_ENABLE_MSB    8
#define CLOCKS_CLK_SYS_RESUS_CTRL_ENABLE_LSB    8
#define CLOCKS_CLK_SYS_RESUS_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_RESUS_CTRL_TIMEOUT
// Description : This is expressed as a number of clk_ref cycles
//               and must be >= 2x clk_ref_freq/min_clk_tst_freq
#define CLOCKS_CLK_SYS_RESUS_CTRL_TIMEOUT_RESET  0xff
#define CLOCKS_CLK_SYS_RESUS_CTRL_TIMEOUT_BITS   0x000000ff
#define CLOCKS_CLK_SYS_RESUS_CTRL_TIMEOUT_MSB    7
#define CLOCKS_CLK_SYS_RESUS_CTRL_TIMEOUT_LSB    0
#define CLOCKS_CLK_SYS_RESUS_CTRL_TIMEOUT_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_SYS_RESUS_STATUS
// Description : None
#define CLOCKS_CLK_SYS_RESUS_STATUS_OFFSET 0x0000007c
#define CLOCKS_CLK_SYS_RESUS_STATUS_BITS   0x00000001
#define CLOCKS_CLK_SYS_RESUS_STATUS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_RESUS_STATUS_RESUSSED
// Description : Clock has been resuscitated, correct the error then send
//               ctrl_clear=1
#define CLOCKS_CLK_SYS_RESUS_STATUS_RESUSSED_RESET  0x0
#define CLOCKS_CLK_SYS_RESUS_STATUS_RESUSSED_BITS   0x00000001
#define CLOCKS_CLK_SYS_RESUS_STATUS_RESUSSED_MSB    0
#define CLOCKS_CLK_SYS_RESUS_STATUS_RESUSSED_LSB    0
#define CLOCKS_CLK_SYS_RESUS_STATUS_RESUSSED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_FC0_REF_KHZ
// Description : Reference clock frequency in kHz
#define CLOCKS_FC0_REF_KHZ_OFFSET 0x00000080
#define CLOCKS_FC0_REF_KHZ_BITS   0x000fffff
#define CLOCKS_FC0_REF_KHZ_RESET  0x00000000
#define CLOCKS_FC0_REF_KHZ_MSB    19
#define CLOCKS_FC0_REF_KHZ_LSB    0
#define CLOCKS_FC0_REF_KHZ_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_FC0_MIN_KHZ
// Description : Minimum pass frequency in kHz. This is optional. Set to 0 if
//               you are not using the pass/fail flags
#define CLOCKS_FC0_MIN_KHZ_OFFSET 0x00000084
#define CLOCKS_FC0_MIN_KHZ_BITS   0x01ffffff
#define CLOCKS_FC0_MIN_KHZ_RESET  0x00000000
#define CLOCKS_FC0_MIN_KHZ_MSB    24
#define CLOCKS_FC0_MIN_KHZ_LSB    0
#define CLOCKS_FC0_MIN_KHZ_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_FC0_MAX_KHZ
// Description : Maximum pass frequency in kHz. This is optional. Set to
//               0x1ffffff if you are not using the pass/fail flags
#define CLOCKS_FC0_MAX_KHZ_OFFSET 0x00000088
#define CLOCKS_FC0_MAX_KHZ_BITS   0x01ffffff
#define CLOCKS_FC0_MAX_KHZ_RESET  0x01ffffff
#define CLOCKS_FC0_MAX_KHZ_MSB    24
#define CLOCKS_FC0_MAX_KHZ_LSB    0
#define CLOCKS_FC0_MAX_KHZ_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_FC0_DELAY
// Description : Delays the start of frequency counting to allow the mux to
//               settle
//               Delay is measured in multiples of the reference clock period
#define CLOCKS_FC0_DELAY_OFFSET 0x0000008c
#define CLOCKS_FC0_DELAY_BITS   0x00000007
#define CLOCKS_FC0_DELAY_RESET  0x00000001
#define CLOCKS_FC0_DELAY_MSB    2
#define CLOCKS_FC0_DELAY_LSB    0
#define CLOCKS_FC0_DELAY_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_FC0_INTERVAL
// Description : The test interval is 0.98us * 2**interval, but let's call it
//               1us * 2**interval
//               The default gives a test interval of 250us
#define CLOCKS_FC0_INTERVAL_OFFSET 0x00000090
#define CLOCKS_FC0_INTERVAL_BITS   0x0000000f
#define CLOCKS_FC0_INTERVAL_RESET  0x00000008
#define CLOCKS_FC0_INTERVAL_MSB    3
#define CLOCKS_FC0_INTERVAL_LSB    0
#define CLOCKS_FC0_INTERVAL_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_FC0_SRC
// Description : Clock sent to frequency counter, set to 0 when not required
//               Writing to this register initiates the frequency count
//               0x00 -> NULL
//               0x01 -> pll_sys_clksrc_primary
//               0x02 -> pll_usb_clksrc_primary
//               0x03 -> rosc_clksrc
//               0x04 -> rosc_clksrc_ph
//               0x05 -> xosc_clksrc
//               0x06 -> clksrc_gpin0
//               0x07 -> clksrc_gpin1
//               0x08 -> clk_ref
//               0x09 -> clk_sys
//               0x0a -> clk_peri
//               0x0b -> clk_usb
//               0x0c -> clk_adc
//               0x0d -> clk_rtc
#define CLOCKS_FC0_SRC_OFFSET                       0x00000094
#define CLOCKS_FC0_SRC_BITS                         0x000000ff
#define CLOCKS_FC0_SRC_RESET                        0x00000000
#define CLOCKS_FC0_SRC_MSB                          7
#define CLOCKS_FC0_SRC_LSB                          0
#define CLOCKS_FC0_SRC_ACCESS                       "RW"
#define CLOCKS_FC0_SRC_VALUE_NULL                   0x00
#define CLOCKS_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY 0x01
#define CLOCKS_FC0_SRC_VALUE_PLL_USB_CLKSRC_PRIMARY 0x02
#define CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC            0x03
#define CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC_PH         0x04
#define CLOCKS_FC0_SRC_VALUE_XOSC_CLKSRC            0x05
#define CLOCKS_FC0_SRC_VALUE_CLKSRC_GPIN0           0x06
#define CLOCKS_FC0_SRC_VALUE_CLKSRC_GPIN1           0x07
#define CLOCKS_FC0_SRC_VALUE_CLK_REF                0x08
#define CLOCKS_FC0_SRC_VALUE_CLK_SYS                0x09
#define CLOCKS_FC0_SRC_VALUE_CLK_PERI               0x0a
#define CLOCKS_FC0_SRC_VALUE_CLK_USB                0x0b
#define CLOCKS_FC0_SRC_VALUE_CLK_ADC                0x0c
#define CLOCKS_FC0_SRC_VALUE_CLK_RTC                0x0d
// =============================================================================
// Register    : CLOCKS_FC0_STATUS
// Description : Frequency counter status
#define CLOCKS_FC0_STATUS_OFFSET 0x00000098
#define CLOCKS_FC0_STATUS_BITS   0x11111111
#define CLOCKS_FC0_STATUS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_DIED
// Description : Test clock stopped during test
#define CLOCKS_FC0_STATUS_DIED_RESET  0x0
#define CLOCKS_FC0_STATUS_DIED_BITS   0x10000000
#define CLOCKS_FC0_STATUS_DIED_MSB    28
#define CLOCKS_FC0_STATUS_DIED_LSB    28
#define CLOCKS_FC0_STATUS_DIED_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_FAST
// Description : Test clock faster than expected, only valid when status_done=1
#define CLOCKS_FC0_STATUS_FAST_RESET  0x0
#define CLOCKS_FC0_STATUS_FAST_BITS   0x01000000
#define CLOCKS_FC0_STATUS_FAST_MSB    24
#define CLOCKS_FC0_STATUS_FAST_LSB    24
#define CLOCKS_FC0_STATUS_FAST_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_SLOW
// Description : Test clock slower than expected, only valid when status_done=1
#define CLOCKS_FC0_STATUS_SLOW_RESET  0x0
#define CLOCKS_FC0_STATUS_SLOW_BITS   0x00100000
#define CLOCKS_FC0_STATUS_SLOW_MSB    20
#define CLOCKS_FC0_STATUS_SLOW_LSB    20
#define CLOCKS_FC0_STATUS_SLOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_FAIL
// Description : Test failed
#define CLOCKS_FC0_STATUS_FAIL_RESET  0x0
#define CLOCKS_FC0_STATUS_FAIL_BITS   0x00010000
#define CLOCKS_FC0_STATUS_FAIL_MSB    16
#define CLOCKS_FC0_STATUS_FAIL_LSB    16
#define CLOCKS_FC0_STATUS_FAIL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_WAITING
// Description : Waiting for test clock to start
#define CLOCKS_FC0_STATUS_WAITING_RESET  0x0
#define CLOCKS_FC0_STATUS_WAITING_BITS   0x00001000
#define CLOCKS_FC0_STATUS_WAITING_MSB    12
#define CLOCKS_FC0_STATUS_WAITING_LSB    12
#define CLOCKS_FC0_STATUS_WAITING_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_RUNNING
// Description : Test running
#define CLOCKS_FC0_STATUS_RUNNING_RESET  0x0
#define CLOCKS_FC0_STATUS_RUNNING_BITS   0x00000100
#define CLOCKS_FC0_STATUS_RUNNING_MSB    8
#define CLOCKS_FC0_STATUS_RUNNING_LSB    8
#define CLOCKS_FC0_STATUS_RUNNING_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_DONE
// Description : Test complete
#define CLOCKS_FC0_STATUS_DONE_RESET  0x0
#define CLOCKS_FC0_STATUS_DONE_BITS   0x00000010
#define CLOCKS_FC0_STATUS_DONE_MSB    4
#define CLOCKS_FC0_STATUS_DONE_LSB    4
#define CLOCKS_FC0_STATUS_DONE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_PASS
// Description : Test passed
#define CLOCKS_FC0_STATUS_PASS_RESET  0x0
#define CLOCKS_FC0_STATUS_PASS_BITS   0x00000001
#define CLOCKS_FC0_STATUS_PASS_MSB    0
#define CLOCKS_FC0_STATUS_PASS_LSB    0
#define CLOCKS_FC0_STATUS_PASS_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_FC0_RESULT
// Description : Result of frequency measurement, only valid when status_done=1
#define CLOCKS_FC0_RESULT_OFFSET 0x0000009c
#define CLOCKS_FC0_RESULT_BITS   0x3fffffff
#define CLOCKS_FC0_RESULT_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_RESULT_KHZ
// Description : None
#define CLOCKS_FC0_RESULT_KHZ_RESET  0x0000000
#define CLOCKS_FC0_RESULT_KHZ_BITS   0x3fffffe0
#define CLOCKS_FC0_RESULT_KHZ_MSB    29
#define CLOCKS_FC0_RESULT_KHZ_LSB    5
#define CLOCKS_FC0_RESULT_KHZ_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_RESULT_FRAC
// Description : None
#define CLOCKS_FC0_RESULT_FRAC_RESET  0x00
#define CLOCKS_FC0_RESULT_FRAC_BITS   0x0000001f
#define CLOCKS_FC0_RESULT_FRAC_MSB    4
#define CLOCKS_FC0_RESULT_FRAC_LSB    0
#define CLOCKS_FC0_RESULT_FRAC_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_WAKE_EN0
// Description : enable clock in wake mode
#define CLOCKS_WAKE_EN0_OFFSET 0x000000a0
#define CLOCKS_WAKE_EN0_BITS   0xffffffff
#define CLOCKS_WAKE_EN0_RESET  0xffffffff
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_SRAM3
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM3_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM3_BITS   0x80000000
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM3_MSB    31
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM3_LSB    31
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_SRAM2
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM2_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM2_BITS   0x40000000
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM2_MSB    30
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM2_LSB    30
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_SRAM1
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM1_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM1_BITS   0x20000000
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM1_MSB    29
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM1_LSB    29
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_SRAM0
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM0_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM0_BITS   0x10000000
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM0_MSB    28
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM0_LSB    28
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_SPI1
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI1_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI1_BITS   0x08000000
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI1_MSB    27
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI1_LSB    27
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_PERI_SPI1
// Description : None
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI1_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI1_BITS   0x04000000
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI1_MSB    26
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI1_LSB    26
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_SPI0
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI0_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI0_BITS   0x02000000
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI0_MSB    25
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI0_LSB    25
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_PERI_SPI0
// Description : None
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI0_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI0_BITS   0x01000000
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI0_MSB    24
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI0_LSB    24
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_SIO
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_SIO_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_SIO_BITS   0x00800000
#define CLOCKS_WAKE_EN0_CLK_SYS_SIO_MSB    23
#define CLOCKS_WAKE_EN0_CLK_SYS_SIO_LSB    23
#define CLOCKS_WAKE_EN0_CLK_SYS_SIO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_RTC
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_RTC_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_RTC_BITS   0x00400000
#define CLOCKS_WAKE_EN0_CLK_SYS_RTC_MSB    22
#define CLOCKS_WAKE_EN0_CLK_SYS_RTC_LSB    22
#define CLOCKS_WAKE_EN0_CLK_SYS_RTC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_RTC_RTC
// Description : None
#define CLOCKS_WAKE_EN0_CLK_RTC_RTC_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_RTC_RTC_BITS   0x00200000
#define CLOCKS_WAKE_EN0_CLK_RTC_RTC_MSB    21
#define CLOCKS_WAKE_EN0_CLK_RTC_RTC_LSB    21
#define CLOCKS_WAKE_EN0_CLK_RTC_RTC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_ROSC
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_ROSC_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_ROSC_BITS   0x00100000
#define CLOCKS_WAKE_EN0_CLK_SYS_ROSC_MSB    20
#define CLOCKS_WAKE_EN0_CLK_SYS_ROSC_LSB    20
#define CLOCKS_WAKE_EN0_CLK_SYS_ROSC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_ROM
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_ROM_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_ROM_BITS   0x00080000
#define CLOCKS_WAKE_EN0_CLK_SYS_ROM_MSB    19
#define CLOCKS_WAKE_EN0_CLK_SYS_ROM_LSB    19
#define CLOCKS_WAKE_EN0_CLK_SYS_ROM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_RESETS
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_RESETS_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_RESETS_BITS   0x00040000
#define CLOCKS_WAKE_EN0_CLK_SYS_RESETS_MSB    18
#define CLOCKS_WAKE_EN0_CLK_SYS_RESETS_LSB    18
#define CLOCKS_WAKE_EN0_CLK_SYS_RESETS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_PWM
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_PWM_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_PWM_BITS   0x00020000
#define CLOCKS_WAKE_EN0_CLK_SYS_PWM_MSB    17
#define CLOCKS_WAKE_EN0_CLK_SYS_PWM_LSB    17
#define CLOCKS_WAKE_EN0_CLK_SYS_PWM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_PSM
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_PSM_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_PSM_BITS   0x00010000
#define CLOCKS_WAKE_EN0_CLK_SYS_PSM_MSB    16
#define CLOCKS_WAKE_EN0_CLK_SYS_PSM_LSB    16
#define CLOCKS_WAKE_EN0_CLK_SYS_PSM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_PLL_USB
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_USB_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_USB_BITS   0x00008000
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_USB_MSB    15
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_USB_LSB    15
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_USB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_PLL_SYS
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_SYS_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_SYS_BITS   0x00004000
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_SYS_MSB    14
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_SYS_LSB    14
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_SYS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_PIO1
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO1_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO1_BITS   0x00002000
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO1_MSB    13
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO1_LSB    13
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_PIO0
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO0_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO0_BITS   0x00001000
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO0_MSB    12
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO0_LSB    12
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_PADS
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_PADS_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_PADS_BITS   0x00000800
#define CLOCKS_WAKE_EN0_CLK_SYS_PADS_MSB    11
#define CLOCKS_WAKE_EN0_CLK_SYS_PADS_LSB    11
#define CLOCKS_WAKE_EN0_CLK_SYS_PADS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_VREG_AND_CHIP_RESET
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_VREG_AND_CHIP_RESET_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_VREG_AND_CHIP_RESET_BITS   0x00000400
#define CLOCKS_WAKE_EN0_CLK_SYS_VREG_AND_CHIP_RESET_MSB    10
#define CLOCKS_WAKE_EN0_CLK_SYS_VREG_AND_CHIP_RESET_LSB    10
#define CLOCKS_WAKE_EN0_CLK_SYS_VREG_AND_CHIP_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_JTAG
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_JTAG_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_JTAG_BITS   0x00000200
#define CLOCKS_WAKE_EN0_CLK_SYS_JTAG_MSB    9
#define CLOCKS_WAKE_EN0_CLK_SYS_JTAG_LSB    9
#define CLOCKS_WAKE_EN0_CLK_SYS_JTAG_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_IO
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_IO_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_IO_BITS   0x00000100
#define CLOCKS_WAKE_EN0_CLK_SYS_IO_MSB    8
#define CLOCKS_WAKE_EN0_CLK_SYS_IO_LSB    8
#define CLOCKS_WAKE_EN0_CLK_SYS_IO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_I2C1
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C1_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C1_BITS   0x00000080
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C1_MSB    7
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C1_LSB    7
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_I2C0
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C0_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C0_BITS   0x00000040
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C0_MSB    6
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C0_LSB    6
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_DMA
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_DMA_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_DMA_BITS   0x00000020
#define CLOCKS_WAKE_EN0_CLK_SYS_DMA_MSB    5
#define CLOCKS_WAKE_EN0_CLK_SYS_DMA_LSB    5
#define CLOCKS_WAKE_EN0_CLK_SYS_DMA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_BUSFABRIC
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSFABRIC_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSFABRIC_BITS   0x00000010
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSFABRIC_MSB    4
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSFABRIC_LSB    4
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSFABRIC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_BUSCTRL
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSCTRL_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSCTRL_BITS   0x00000008
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSCTRL_MSB    3
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSCTRL_LSB    3
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSCTRL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_ADC
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_ADC_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_ADC_BITS   0x00000004
#define CLOCKS_WAKE_EN0_CLK_SYS_ADC_MSB    2
#define CLOCKS_WAKE_EN0_CLK_SYS_ADC_LSB    2
#define CLOCKS_WAKE_EN0_CLK_SYS_ADC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_ADC_ADC
// Description : None
#define CLOCKS_WAKE_EN0_CLK_ADC_ADC_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_ADC_ADC_BITS   0x00000002
#define CLOCKS_WAKE_EN0_CLK_ADC_ADC_MSB    1
#define CLOCKS_WAKE_EN0_CLK_ADC_ADC_LSB    1
#define CLOCKS_WAKE_EN0_CLK_ADC_ADC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_CLOCKS
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_CLOCKS_RESET  0x1
#define CLOCKS_WAKE_EN0_CLK_SYS_CLOCKS_BITS   0x00000001
#define CLOCKS_WAKE_EN0_CLK_SYS_CLOCKS_MSB    0
#define CLOCKS_WAKE_EN0_CLK_SYS_CLOCKS_LSB    0
#define CLOCKS_WAKE_EN0_CLK_SYS_CLOCKS_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_WAKE_EN1
// Description : enable clock in wake mode
#define CLOCKS_WAKE_EN1_OFFSET 0x000000a4
#define CLOCKS_WAKE_EN1_BITS   0x00007fff
#define CLOCKS_WAKE_EN1_RESET  0x00007fff
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_XOSC
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_XOSC_RESET  0x1
#define CLOCKS_WAKE_EN1_CLK_SYS_XOSC_BITS   0x00004000
#define CLOCKS_WAKE_EN1_CLK_SYS_XOSC_MSB    14
#define CLOCKS_WAKE_EN1_CLK_SYS_XOSC_LSB    14
#define CLOCKS_WAKE_EN1_CLK_SYS_XOSC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_XIP
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_XIP_RESET  0x1
#define CLOCKS_WAKE_EN1_CLK_SYS_XIP_BITS   0x00002000
#define CLOCKS_WAKE_EN1_CLK_SYS_XIP_MSB    13
#define CLOCKS_WAKE_EN1_CLK_SYS_XIP_LSB    13
#define CLOCKS_WAKE_EN1_CLK_SYS_XIP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_WATCHDOG
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_WATCHDOG_RESET  0x1
#define CLOCKS_WAKE_EN1_CLK_SYS_WATCHDOG_BITS   0x00001000
#define CLOCKS_WAKE_EN1_CLK_SYS_WATCHDOG_MSB    12
#define CLOCKS_WAKE_EN1_CLK_SYS_WATCHDOG_LSB    12
#define CLOCKS_WAKE_EN1_CLK_SYS_WATCHDOG_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_USB_USBCTRL
// Description : None
#define CLOCKS_WAKE_EN1_CLK_USB_USBCTRL_RESET  0x1
#define CLOCKS_WAKE_EN1_CLK_USB_USBCTRL_BITS   0x00000800
#define CLOCKS_WAKE_EN1_CLK_USB_USBCTRL_MSB    11
#define CLOCKS_WAKE_EN1_CLK_USB_USBCTRL_LSB    11
#define CLOCKS_WAKE_EN1_CLK_USB_USBCTRL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_USBCTRL
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_USBCTRL_RESET  0x1
#define CLOCKS_WAKE_EN1_CLK_SYS_USBCTRL_BITS   0x00000400
#define CLOCKS_WAKE_EN1_CLK_SYS_USBCTRL_MSB    10
#define CLOCKS_WAKE_EN1_CLK_SYS_USBCTRL_LSB    10
#define CLOCKS_WAKE_EN1_CLK_SYS_USBCTRL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_UART1
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_UART1_RESET  0x1
#define CLOCKS_WAKE_EN1_CLK_SYS_UART1_BITS   0x00000200
#define CLOCKS_WAKE_EN1_CLK_SYS_UART1_MSB    9
#define CLOCKS_WAKE_EN1_CLK_SYS_UART1_LSB    9
#define CLOCKS_WAKE_EN1_CLK_SYS_UART1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_PERI_UART1
// Description : None
#define CLOCKS_WAKE_EN1_CLK_PERI_UART1_RESET  0x1
#define CLOCKS_WAKE_EN1_CLK_PERI_UART1_BITS   0x00000100
#define CLOCKS_WAKE_EN1_CLK_PERI_UART1_MSB    8
#define CLOCKS_WAKE_EN1_CLK_PERI_UART1_LSB    8
#define CLOCKS_WAKE_EN1_CLK_PERI_UART1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_UART0
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_UART0_RESET  0x1
#define CLOCKS_WAKE_EN1_CLK_SYS_UART0_BITS   0x00000080
#define CLOCKS_WAKE_EN1_CLK_SYS_UART0_MSB    7
#define CLOCKS_WAKE_EN1_CLK_SYS_UART0_LSB    7
#define CLOCKS_WAKE_EN1_CLK_SYS_UART0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_PERI_UART0
// Description : None
#define CLOCKS_WAKE_EN1_CLK_PERI_UART0_RESET  0x1
#define CLOCKS_WAKE_EN1_CLK_PERI_UART0_BITS   0x00000040
#define CLOCKS_WAKE_EN1_CLK_PERI_UART0_MSB    6
#define CLOCKS_WAKE_EN1_CLK_PERI_UART0_LSB    6
#define CLOCKS_WAKE_EN1_CLK_PERI_UART0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_TIMER
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_TIMER_RESET  0x1
#define CLOCKS_WAKE_EN1_CLK_SYS_TIMER_BITS   0x00000020
#define CLOCKS_WAKE_EN1_CLK_SYS_TIMER_MSB    5
#define CLOCKS_WAKE_EN1_CLK_SYS_TIMER_LSB    5
#define CLOCKS_WAKE_EN1_CLK_SYS_TIMER_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_TBMAN
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_TBMAN_RESET  0x1
#define CLOCKS_WAKE_EN1_CLK_SYS_TBMAN_BITS   0x00000010
#define CLOCKS_WAKE_EN1_CLK_SYS_TBMAN_MSB    4
#define CLOCKS_WAKE_EN1_CLK_SYS_TBMAN_LSB    4
#define CLOCKS_WAKE_EN1_CLK_SYS_TBMAN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_SYSINFO
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSINFO_RESET  0x1
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSINFO_BITS   0x00000008
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSINFO_MSB    3
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSINFO_LSB    3
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSINFO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_SYSCFG
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSCFG_RESET  0x1
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSCFG_BITS   0x00000004
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSCFG_MSB    2
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSCFG_LSB    2
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSCFG_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_SRAM5
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM5_RESET  0x1
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM5_BITS   0x00000002
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM5_MSB    1
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM5_LSB    1
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM5_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_SRAM4
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM4_RESET  0x1
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM4_BITS   0x00000001
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM4_MSB    0
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM4_LSB    0
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM4_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_SLEEP_EN0
// Description : enable clock in sleep mode
#define CLOCKS_SLEEP_EN0_OFFSET 0x000000a8
#define CLOCKS_SLEEP_EN0_BITS   0xffffffff
#define CLOCKS_SLEEP_EN0_RESET  0xffffffff
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_SRAM3
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM3_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM3_BITS   0x80000000
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM3_MSB    31
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM3_LSB    31
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_SRAM2
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM2_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM2_BITS   0x40000000
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM2_MSB    30
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM2_LSB    30
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_SRAM1
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM1_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM1_BITS   0x20000000
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM1_MSB    29
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM1_LSB    29
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_SRAM0
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM0_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM0_BITS   0x10000000
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM0_MSB    28
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM0_LSB    28
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_SPI1
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI1_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI1_BITS   0x08000000
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI1_MSB    27
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI1_LSB    27
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_PERI_SPI1
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI1_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI1_BITS   0x04000000
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI1_MSB    26
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI1_LSB    26
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_SPI0
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI0_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI0_BITS   0x02000000
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI0_MSB    25
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI0_LSB    25
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_PERI_SPI0
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI0_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI0_BITS   0x01000000
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI0_MSB    24
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI0_LSB    24
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_SIO
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_SIO_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_SIO_BITS   0x00800000
#define CLOCKS_SLEEP_EN0_CLK_SYS_SIO_MSB    23
#define CLOCKS_SLEEP_EN0_CLK_SYS_SIO_LSB    23
#define CLOCKS_SLEEP_EN0_CLK_SYS_SIO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_RTC
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_RTC_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_RTC_BITS   0x00400000
#define CLOCKS_SLEEP_EN0_CLK_SYS_RTC_MSB    22
#define CLOCKS_SLEEP_EN0_CLK_SYS_RTC_LSB    22
#define CLOCKS_SLEEP_EN0_CLK_SYS_RTC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_RTC_RTC
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_RTC_RTC_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_RTC_RTC_BITS   0x00200000
#define CLOCKS_SLEEP_EN0_CLK_RTC_RTC_MSB    21
#define CLOCKS_SLEEP_EN0_CLK_RTC_RTC_LSB    21
#define CLOCKS_SLEEP_EN0_CLK_RTC_RTC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_ROSC
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROSC_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROSC_BITS   0x00100000
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROSC_MSB    20
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROSC_LSB    20
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROSC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_ROM
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROM_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROM_BITS   0x00080000
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROM_MSB    19
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROM_LSB    19
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_RESETS
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_RESETS_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_RESETS_BITS   0x00040000
#define CLOCKS_SLEEP_EN0_CLK_SYS_RESETS_MSB    18
#define CLOCKS_SLEEP_EN0_CLK_SYS_RESETS_LSB    18
#define CLOCKS_SLEEP_EN0_CLK_SYS_RESETS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_PWM
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_PWM_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_PWM_BITS   0x00020000
#define CLOCKS_SLEEP_EN0_CLK_SYS_PWM_MSB    17
#define CLOCKS_SLEEP_EN0_CLK_SYS_PWM_LSB    17
#define CLOCKS_SLEEP_EN0_CLK_SYS_PWM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_PSM
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_PSM_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_PSM_BITS   0x00010000
#define CLOCKS_SLEEP_EN0_CLK_SYS_PSM_MSB    16
#define CLOCKS_SLEEP_EN0_CLK_SYS_PSM_LSB    16
#define CLOCKS_SLEEP_EN0_CLK_SYS_PSM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_PLL_USB
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_USB_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_USB_BITS   0x00008000
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_USB_MSB    15
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_USB_LSB    15
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_USB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_PLL_SYS
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_SYS_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_SYS_BITS   0x00004000
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_SYS_MSB    14
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_SYS_LSB    14
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_SYS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_PIO1
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO1_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO1_BITS   0x00002000
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO1_MSB    13
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO1_LSB    13
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_PIO0
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO0_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO0_BITS   0x00001000
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO0_MSB    12
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO0_LSB    12
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_PADS
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_PADS_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_PADS_BITS   0x00000800
#define CLOCKS_SLEEP_EN0_CLK_SYS_PADS_MSB    11
#define CLOCKS_SLEEP_EN0_CLK_SYS_PADS_LSB    11
#define CLOCKS_SLEEP_EN0_CLK_SYS_PADS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_VREG_AND_CHIP_RESET
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_VREG_AND_CHIP_RESET_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_VREG_AND_CHIP_RESET_BITS   0x00000400
#define CLOCKS_SLEEP_EN0_CLK_SYS_VREG_AND_CHIP_RESET_MSB    10
#define CLOCKS_SLEEP_EN0_CLK_SYS_VREG_AND_CHIP_RESET_LSB    10
#define CLOCKS_SLEEP_EN0_CLK_SYS_VREG_AND_CHIP_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_JTAG
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_JTAG_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_JTAG_BITS   0x00000200
#define CLOCKS_SLEEP_EN0_CLK_SYS_JTAG_MSB    9
#define CLOCKS_SLEEP_EN0_CLK_SYS_JTAG_LSB    9
#define CLOCKS_SLEEP_EN0_CLK_SYS_JTAG_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_IO
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_IO_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_IO_BITS   0x00000100
#define CLOCKS_SLEEP_EN0_CLK_SYS_IO_MSB    8
#define CLOCKS_SLEEP_EN0_CLK_SYS_IO_LSB    8
#define CLOCKS_SLEEP_EN0_CLK_SYS_IO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_I2C1
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C1_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C1_BITS   0x00000080
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C1_MSB    7
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C1_LSB    7
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_I2C0
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C0_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C0_BITS   0x00000040
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C0_MSB    6
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C0_LSB    6
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_DMA
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_DMA_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_DMA_BITS   0x00000020
#define CLOCKS_SLEEP_EN0_CLK_SYS_DMA_MSB    5
#define CLOCKS_SLEEP_EN0_CLK_SYS_DMA_LSB    5
#define CLOCKS_SLEEP_EN0_CLK_SYS_DMA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_BUSFABRIC
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSFABRIC_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSFABRIC_BITS   0x00000010
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSFABRIC_MSB    4
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSFABRIC_LSB    4
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSFABRIC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_BUSCTRL
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSCTRL_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSCTRL_BITS   0x00000008
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSCTRL_MSB    3
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSCTRL_LSB    3
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSCTRL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_ADC
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_ADC_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_ADC_BITS   0x00000004
#define CLOCKS_SLEEP_EN0_CLK_SYS_ADC_MSB    2
#define CLOCKS_SLEEP_EN0_CLK_SYS_ADC_LSB    2
#define CLOCKS_SLEEP_EN0_CLK_SYS_ADC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_ADC_ADC
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_ADC_ADC_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_ADC_ADC_BITS   0x00000002
#define CLOCKS_SLEEP_EN0_CLK_ADC_ADC_MSB    1
#define CLOCKS_SLEEP_EN0_CLK_ADC_ADC_LSB    1
#define CLOCKS_SLEEP_EN0_CLK_ADC_ADC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_CLOCKS
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_CLOCKS_RESET  0x1
#define CLOCKS_SLEEP_EN0_CLK_SYS_CLOCKS_BITS   0x00000001
#define CLOCKS_SLEEP_EN0_CLK_SYS_CLOCKS_MSB    0
#define CLOCKS_SLEEP_EN0_CLK_SYS_CLOCKS_LSB    0
#define CLOCKS_SLEEP_EN0_CLK_SYS_CLOCKS_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_SLEEP_EN1
// Description : enable clock in sleep mode
#define CLOCKS_SLEEP_EN1_OFFSET 0x000000ac
#define CLOCKS_SLEEP_EN1_BITS   0x00007fff
#define CLOCKS_SLEEP_EN1_RESET  0x00007fff
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_XOSC
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_XOSC_RESET  0x1
#define CLOCKS_SLEEP_EN1_CLK_SYS_XOSC_BITS   0x00004000
#define CLOCKS_SLEEP_EN1_CLK_SYS_XOSC_MSB    14
#define CLOCKS_SLEEP_EN1_CLK_SYS_XOSC_LSB    14
#define CLOCKS_SLEEP_EN1_CLK_SYS_XOSC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_XIP
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_XIP_RESET  0x1
#define CLOCKS_SLEEP_EN1_CLK_SYS_XIP_BITS   0x00002000
#define CLOCKS_SLEEP_EN1_CLK_SYS_XIP_MSB    13
#define CLOCKS_SLEEP_EN1_CLK_SYS_XIP_LSB    13
#define CLOCKS_SLEEP_EN1_CLK_SYS_XIP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_WATCHDOG
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_WATCHDOG_RESET  0x1
#define CLOCKS_SLEEP_EN1_CLK_SYS_WATCHDOG_BITS   0x00001000
#define CLOCKS_SLEEP_EN1_CLK_SYS_WATCHDOG_MSB    12
#define CLOCKS_SLEEP_EN1_CLK_SYS_WATCHDOG_LSB    12
#define CLOCKS_SLEEP_EN1_CLK_SYS_WATCHDOG_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_USB_USBCTRL
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_USB_USBCTRL_RESET  0x1
#define CLOCKS_SLEEP_EN1_CLK_USB_USBCTRL_BITS   0x00000800
#define CLOCKS_SLEEP_EN1_CLK_USB_USBCTRL_MSB    11
#define CLOCKS_SLEEP_EN1_CLK_USB_USBCTRL_LSB    11
#define CLOCKS_SLEEP_EN1_CLK_USB_USBCTRL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_USBCTRL
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_USBCTRL_RESET  0x1
#define CLOCKS_SLEEP_EN1_CLK_SYS_USBCTRL_BITS   0x00000400
#define CLOCKS_SLEEP_EN1_CLK_SYS_USBCTRL_MSB    10
#define CLOCKS_SLEEP_EN1_CLK_SYS_USBCTRL_LSB    10
#define CLOCKS_SLEEP_EN1_CLK_SYS_USBCTRL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_UART1
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART1_RESET  0x1
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART1_BITS   0x00000200
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART1_MSB    9
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART1_LSB    9
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_PERI_UART1
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART1_RESET  0x1
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART1_BITS   0x00000100
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART1_MSB    8
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART1_LSB    8
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_UART0
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART0_RESET  0x1
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART0_BITS   0x00000080
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART0_MSB    7
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART0_LSB    7
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_PERI_UART0
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART0_RESET  0x1
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART0_BITS   0x00000040
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART0_MSB    6
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART0_LSB    6
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_TIMER
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_TIMER_RESET  0x1
#define CLOCKS_SLEEP_EN1_CLK_SYS_TIMER_BITS   0x00000020
#define CLOCKS_SLEEP_EN1_CLK_SYS_TIMER_MSB    5
#define CLOCKS_SLEEP_EN1_CLK_SYS_TIMER_LSB    5
#define CLOCKS_SLEEP_EN1_CLK_SYS_TIMER_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_TBMAN
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_TBMAN_RESET  0x1
#define CLOCKS_SLEEP_EN1_CLK_SYS_TBMAN_BITS   0x00000010
#define CLOCKS_SLEEP_EN1_CLK_SYS_TBMAN_MSB    4
#define CLOCKS_SLEEP_EN1_CLK_SYS_TBMAN_LSB    4
#define CLOCKS_SLEEP_EN1_CLK_SYS_TBMAN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_SYSINFO
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSINFO_RESET  0x1
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSINFO_BITS   0x00000008
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSINFO_MSB    3
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSINFO_LSB    3
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSINFO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_SYSCFG
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSCFG_RESET  0x1
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSCFG_BITS   0x00000004
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSCFG_MSB    2
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSCFG_LSB    2
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSCFG_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_SRAM5
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM5_RESET  0x1
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM5_BITS   0x00000002
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM5_MSB    1
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM5_LSB    1
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM5_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_SRAM4
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM4_RESET  0x1
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM4_BITS   0x00000001
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM4_MSB    0
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM4_LSB    0
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM4_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_ENABLED0
// Description : indicates the state of the clock enable
#define CLOCKS_ENABLED0_OFFSET 0x000000b0
#define CLOCKS_ENABLED0_BITS   0xffffffff
#define CLOCKS_ENABLED0_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_SRAM3
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_SRAM3_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_SRAM3_BITS   0x80000000
#define CLOCKS_ENABLED0_CLK_SYS_SRAM3_MSB    31
#define CLOCKS_ENABLED0_CLK_SYS_SRAM3_LSB    31
#define CLOCKS_ENABLED0_CLK_SYS_SRAM3_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_SRAM2
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_SRAM2_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_SRAM2_BITS   0x40000000
#define CLOCKS_ENABLED0_CLK_SYS_SRAM2_MSB    30
#define CLOCKS_ENABLED0_CLK_SYS_SRAM2_LSB    30
#define CLOCKS_ENABLED0_CLK_SYS_SRAM2_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_SRAM1
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_SRAM1_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_SRAM1_BITS   0x20000000
#define CLOCKS_ENABLED0_CLK_SYS_SRAM1_MSB    29
#define CLOCKS_ENABLED0_CLK_SYS_SRAM1_LSB    29
#define CLOCKS_ENABLED0_CLK_SYS_SRAM1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_SRAM0
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_SRAM0_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_SRAM0_BITS   0x10000000
#define CLOCKS_ENABLED0_CLK_SYS_SRAM0_MSB    28
#define CLOCKS_ENABLED0_CLK_SYS_SRAM0_LSB    28
#define CLOCKS_ENABLED0_CLK_SYS_SRAM0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_SPI1
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_SPI1_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_SPI1_BITS   0x08000000
#define CLOCKS_ENABLED0_CLK_SYS_SPI1_MSB    27
#define CLOCKS_ENABLED0_CLK_SYS_SPI1_LSB    27
#define CLOCKS_ENABLED0_CLK_SYS_SPI1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_PERI_SPI1
// Description : None
#define CLOCKS_ENABLED0_CLK_PERI_SPI1_RESET  0x0
#define CLOCKS_ENABLED0_CLK_PERI_SPI1_BITS   0x04000000
#define CLOCKS_ENABLED0_CLK_PERI_SPI1_MSB    26
#define CLOCKS_ENABLED0_CLK_PERI_SPI1_LSB    26
#define CLOCKS_ENABLED0_CLK_PERI_SPI1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_SPI0
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_SPI0_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_SPI0_BITS   0x02000000
#define CLOCKS_ENABLED0_CLK_SYS_SPI0_MSB    25
#define CLOCKS_ENABLED0_CLK_SYS_SPI0_LSB    25
#define CLOCKS_ENABLED0_CLK_SYS_SPI0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_PERI_SPI0
// Description : None
#define CLOCKS_ENABLED0_CLK_PERI_SPI0_RESET  0x0
#define CLOCKS_ENABLED0_CLK_PERI_SPI0_BITS   0x01000000
#define CLOCKS_ENABLED0_CLK_PERI_SPI0_MSB    24
#define CLOCKS_ENABLED0_CLK_PERI_SPI0_LSB    24
#define CLOCKS_ENABLED0_CLK_PERI_SPI0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_SIO
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_SIO_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_SIO_BITS   0x00800000
#define CLOCKS_ENABLED0_CLK_SYS_SIO_MSB    23
#define CLOCKS_ENABLED0_CLK_SYS_SIO_LSB    23
#define CLOCKS_ENABLED0_CLK_SYS_SIO_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_RTC
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_RTC_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_RTC_BITS   0x00400000
#define CLOCKS_ENABLED0_CLK_SYS_RTC_MSB    22
#define CLOCKS_ENABLED0_CLK_SYS_RTC_LSB    22
#define CLOCKS_ENABLED0_CLK_SYS_RTC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_RTC_RTC
// Description : None
#define CLOCKS_ENABLED0_CLK_RTC_RTC_RESET  0x0
#define CLOCKS_ENABLED0_CLK_RTC_RTC_BITS   0x00200000
#define CLOCKS_ENABLED0_CLK_RTC_RTC_MSB    21
#define CLOCKS_ENABLED0_CLK_RTC_RTC_LSB    21
#define CLOCKS_ENABLED0_CLK_RTC_RTC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_ROSC
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_ROSC_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_ROSC_BITS   0x00100000
#define CLOCKS_ENABLED0_CLK_SYS_ROSC_MSB    20
#define CLOCKS_ENABLED0_CLK_SYS_ROSC_LSB    20
#define CLOCKS_ENABLED0_CLK_SYS_ROSC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_ROM
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_ROM_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_ROM_BITS   0x00080000
#define CLOCKS_ENABLED0_CLK_SYS_ROM_MSB    19
#define CLOCKS_ENABLED0_CLK_SYS_ROM_LSB    19
#define CLOCKS_ENABLED0_CLK_SYS_ROM_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_RESETS
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_RESETS_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_RESETS_BITS   0x00040000
#define CLOCKS_ENABLED0_CLK_SYS_RESETS_MSB    18
#define CLOCKS_ENABLED0_CLK_SYS_RESETS_LSB    18
#define CLOCKS_ENABLED0_CLK_SYS_RESETS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_PWM
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_PWM_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_PWM_BITS   0x00020000
#define CLOCKS_ENABLED0_CLK_SYS_PWM_MSB    17
#define CLOCKS_ENABLED0_CLK_SYS_PWM_LSB    17
#define CLOCKS_ENABLED0_CLK_SYS_PWM_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_PSM
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_PSM_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_PSM_BITS   0x00010000
#define CLOCKS_ENABLED0_CLK_SYS_PSM_MSB    16
#define CLOCKS_ENABLED0_CLK_SYS_PSM_LSB    16
#define CLOCKS_ENABLED0_CLK_SYS_PSM_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_PLL_USB
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_PLL_USB_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_PLL_USB_BITS   0x00008000
#define CLOCKS_ENABLED0_CLK_SYS_PLL_USB_MSB    15
#define CLOCKS_ENABLED0_CLK_SYS_PLL_USB_LSB    15
#define CLOCKS_ENABLED0_CLK_SYS_PLL_USB_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_PLL_SYS
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_PLL_SYS_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_PLL_SYS_BITS   0x00004000
#define CLOCKS_ENABLED0_CLK_SYS_PLL_SYS_MSB    14
#define CLOCKS_ENABLED0_CLK_SYS_PLL_SYS_LSB    14
#define CLOCKS_ENABLED0_CLK_SYS_PLL_SYS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_PIO1
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_PIO1_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_PIO1_BITS   0x00002000
#define CLOCKS_ENABLED0_CLK_SYS_PIO1_MSB    13
#define CLOCKS_ENABLED0_CLK_SYS_PIO1_LSB    13
#define CLOCKS_ENABLED0_CLK_SYS_PIO1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_PIO0
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_PIO0_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_PIO0_BITS   0x00001000
#define CLOCKS_ENABLED0_CLK_SYS_PIO0_MSB    12
#define CLOCKS_ENABLED0_CLK_SYS_PIO0_LSB    12
#define CLOCKS_ENABLED0_CLK_SYS_PIO0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_PADS
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_PADS_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_PADS_BITS   0x00000800
#define CLOCKS_ENABLED0_CLK_SYS_PADS_MSB    11
#define CLOCKS_ENABLED0_CLK_SYS_PADS_LSB    11
#define CLOCKS_ENABLED0_CLK_SYS_PADS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_VREG_AND_CHIP_RESET
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_VREG_AND_CHIP_RESET_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_VREG_AND_CHIP_RESET_BITS   0x00000400
#define CLOCKS_ENABLED0_CLK_SYS_VREG_AND_CHIP_RESET_MSB    10
#define CLOCKS_ENABLED0_CLK_SYS_VREG_AND_CHIP_RESET_LSB    10
#define CLOCKS_ENABLED0_CLK_SYS_VREG_AND_CHIP_RESET_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_JTAG
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_JTAG_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_JTAG_BITS   0x00000200
#define CLOCKS_ENABLED0_CLK_SYS_JTAG_MSB    9
#define CLOCKS_ENABLED0_CLK_SYS_JTAG_LSB    9
#define CLOCKS_ENABLED0_CLK_SYS_JTAG_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_IO
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_IO_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_IO_BITS   0x00000100
#define CLOCKS_ENABLED0_CLK_SYS_IO_MSB    8
#define CLOCKS_ENABLED0_CLK_SYS_IO_LSB    8
#define CLOCKS_ENABLED0_CLK_SYS_IO_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_I2C1
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_I2C1_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_I2C1_BITS   0x00000080
#define CLOCKS_ENABLED0_CLK_SYS_I2C1_MSB    7
#define CLOCKS_ENABLED0_CLK_SYS_I2C1_LSB    7
#define CLOCKS_ENABLED0_CLK_SYS_I2C1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_I2C0
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_I2C0_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_I2C0_BITS   0x00000040
#define CLOCKS_ENABLED0_CLK_SYS_I2C0_MSB    6
#define CLOCKS_ENABLED0_CLK_SYS_I2C0_LSB    6
#define CLOCKS_ENABLED0_CLK_SYS_I2C0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_DMA
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_DMA_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_DMA_BITS   0x00000020
#define CLOCKS_ENABLED0_CLK_SYS_DMA_MSB    5
#define CLOCKS_ENABLED0_CLK_SYS_DMA_LSB    5
#define CLOCKS_ENABLED0_CLK_SYS_DMA_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_BUSFABRIC
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_BUSFABRIC_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_BUSFABRIC_BITS   0x00000010
#define CLOCKS_ENABLED0_CLK_SYS_BUSFABRIC_MSB    4
#define CLOCKS_ENABLED0_CLK_SYS_BUSFABRIC_LSB    4
#define CLOCKS_ENABLED0_CLK_SYS_BUSFABRIC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_BUSCTRL
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_BUSCTRL_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_BUSCTRL_BITS   0x00000008
#define CLOCKS_ENABLED0_CLK_SYS_BUSCTRL_MSB    3
#define CLOCKS_ENABLED0_CLK_SYS_BUSCTRL_LSB    3
#define CLOCKS_ENABLED0_CLK_SYS_BUSCTRL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_ADC
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_ADC_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_ADC_BITS   0x00000004
#define CLOCKS_ENABLED0_CLK_SYS_ADC_MSB    2
#define CLOCKS_ENABLED0_CLK_SYS_ADC_LSB    2
#define CLOCKS_ENABLED0_CLK_SYS_ADC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_ADC_ADC
// Description : None
#define CLOCKS_ENABLED0_CLK_ADC_ADC_RESET  0x0
#define CLOCKS_ENABLED0_CLK_ADC_ADC_BITS   0x00000002
#define CLOCKS_ENABLED0_CLK_ADC_ADC_MSB    1
#define CLOCKS_ENABLED0_CLK_ADC_ADC_LSB    1
#define CLOCKS_ENABLED0_CLK_ADC_ADC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_CLOCKS
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_CLOCKS_RESET  0x0
#define CLOCKS_ENABLED0_CLK_SYS_CLOCKS_BITS   0x00000001
#define CLOCKS_ENABLED0_CLK_SYS_CLOCKS_MSB    0
#define CLOCKS_ENABLED0_CLK_SYS_CLOCKS_LSB    0
#define CLOCKS_ENABLED0_CLK_SYS_CLOCKS_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_ENABLED1
// Description : indicates the state of the clock enable
#define CLOCKS_ENABLED1_OFFSET 0x000000b4
#define CLOCKS_ENABLED1_BITS   0x00007fff
#define CLOCKS_ENABLED1_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_XOSC
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_XOSC_RESET  0x0
#define CLOCKS_ENABLED1_CLK_SYS_XOSC_BITS   0x00004000
#define CLOCKS_ENABLED1_CLK_SYS_XOSC_MSB    14
#define CLOCKS_ENABLED1_CLK_SYS_XOSC_LSB    14
#define CLOCKS_ENABLED1_CLK_SYS_XOSC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_XIP
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_XIP_RESET  0x0
#define CLOCKS_ENABLED1_CLK_SYS_XIP_BITS   0x00002000
#define CLOCKS_ENABLED1_CLK_SYS_XIP_MSB    13
#define CLOCKS_ENABLED1_CLK_SYS_XIP_LSB    13
#define CLOCKS_ENABLED1_CLK_SYS_XIP_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_WATCHDOG
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_WATCHDOG_RESET  0x0
#define CLOCKS_ENABLED1_CLK_SYS_WATCHDOG_BITS   0x00001000
#define CLOCKS_ENABLED1_CLK_SYS_WATCHDOG_MSB    12
#define CLOCKS_ENABLED1_CLK_SYS_WATCHDOG_LSB    12
#define CLOCKS_ENABLED1_CLK_SYS_WATCHDOG_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_USB_USBCTRL
// Description : None
#define CLOCKS_ENABLED1_CLK_USB_USBCTRL_RESET  0x0
#define CLOCKS_ENABLED1_CLK_USB_USBCTRL_BITS   0x00000800
#define CLOCKS_ENABLED1_CLK_USB_USBCTRL_MSB    11
#define CLOCKS_ENABLED1_CLK_USB_USBCTRL_LSB    11
#define CLOCKS_ENABLED1_CLK_USB_USBCTRL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_USBCTRL
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_USBCTRL_RESET  0x0
#define CLOCKS_ENABLED1_CLK_SYS_USBCTRL_BITS   0x00000400
#define CLOCKS_ENABLED1_CLK_SYS_USBCTRL_MSB    10
#define CLOCKS_ENABLED1_CLK_SYS_USBCTRL_LSB    10
#define CLOCKS_ENABLED1_CLK_SYS_USBCTRL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_UART1
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_UART1_RESET  0x0
#define CLOCKS_ENABLED1_CLK_SYS_UART1_BITS   0x00000200
#define CLOCKS_ENABLED1_CLK_SYS_UART1_MSB    9
#define CLOCKS_ENABLED1_CLK_SYS_UART1_LSB    9
#define CLOCKS_ENABLED1_CLK_SYS_UART1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_PERI_UART1
// Description : None
#define CLOCKS_ENABLED1_CLK_PERI_UART1_RESET  0x0
#define CLOCKS_ENABLED1_CLK_PERI_UART1_BITS   0x00000100
#define CLOCKS_ENABLED1_CLK_PERI_UART1_MSB    8
#define CLOCKS_ENABLED1_CLK_PERI_UART1_LSB    8
#define CLOCKS_ENABLED1_CLK_PERI_UART1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_UART0
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_UART0_RESET  0x0
#define CLOCKS_ENABLED1_CLK_SYS_UART0_BITS   0x00000080
#define CLOCKS_ENABLED1_CLK_SYS_UART0_MSB    7
#define CLOCKS_ENABLED1_CLK_SYS_UART0_LSB    7
#define CLOCKS_ENABLED1_CLK_SYS_UART0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_PERI_UART0
// Description : None
#define CLOCKS_ENABLED1_CLK_PERI_UART0_RESET  0x0
#define CLOCKS_ENABLED1_CLK_PERI_UART0_BITS   0x00000040
#define CLOCKS_ENABLED1_CLK_PERI_UART0_MSB    6
#define CLOCKS_ENABLED1_CLK_PERI_UART0_LSB    6
#define CLOCKS_ENABLED1_CLK_PERI_UART0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_TIMER
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_TIMER_RESET  0x0
#define CLOCKS_ENABLED1_CLK_SYS_TIMER_BITS   0x00000020
#define CLOCKS_ENABLED1_CLK_SYS_TIMER_MSB    5
#define CLOCKS_ENABLED1_CLK_SYS_TIMER_LSB    5
#define CLOCKS_ENABLED1_CLK_SYS_TIMER_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_TBMAN
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_TBMAN_RESET  0x0
#define CLOCKS_ENABLED1_CLK_SYS_TBMAN_BITS   0x00000010
#define CLOCKS_ENABLED1_CLK_SYS_TBMAN_MSB    4
#define CLOCKS_ENABLED1_CLK_SYS_TBMAN_LSB    4
#define CLOCKS_ENABLED1_CLK_SYS_TBMAN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_SYSINFO
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_SYSINFO_RESET  0x0
#define CLOCKS_ENABLED1_CLK_SYS_SYSINFO_BITS   0x00000008
#define CLOCKS_ENABLED1_CLK_SYS_SYSINFO_MSB    3
#define CLOCKS_ENABLED1_CLK_SYS_SYSINFO_LSB    3
#define CLOCKS_ENABLED1_CLK_SYS_SYSINFO_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_SYSCFG
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_SYSCFG_RESET  0x0
#define CLOCKS_ENABLED1_CLK_SYS_SYSCFG_BITS   0x00000004
#define CLOCKS_ENABLED1_CLK_SYS_SYSCFG_MSB    2
#define CLOCKS_ENABLED1_CLK_SYS_SYSCFG_LSB    2
#define CLOCKS_ENABLED1_CLK_SYS_SYSCFG_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_SRAM5
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_SRAM5_RESET  0x0
#define CLOCKS_ENABLED1_CLK_SYS_SRAM5_BITS   0x00000002
#define CLOCKS_ENABLED1_CLK_SYS_SRAM5_MSB    1
#define CLOCKS_ENABLED1_CLK_SYS_SRAM5_LSB    1
#define CLOCKS_ENABLED1_CLK_SYS_SRAM5_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_SRAM4
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_SRAM4_RESET  0x0
#define CLOCKS_ENABLED1_CLK_SYS_SRAM4_BITS   0x00000001
#define CLOCKS_ENABLED1_CLK_SYS_SRAM4_MSB    0
#define CLOCKS_ENABLED1_CLK_SYS_SRAM4_LSB    0
#define CLOCKS_ENABLED1_CLK_SYS_SRAM4_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_INTR
// Description : Raw Interrupts
#define CLOCKS_INTR_OFFSET 0x000000b8
#define CLOCKS_INTR_BITS   0x00000001
#define CLOCKS_INTR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_INTR_CLK_SYS_RESUS
// Description : None
#define CLOCKS_INTR_CLK_SYS_RESUS_RESET  0x0
#define CLOCKS_INTR_CLK_SYS_RESUS_BITS   0x00000001
#define CLOCKS_INTR_CLK_SYS_RESUS_MSB    0
#define CLOCKS_INTR_CLK_SYS_RESUS_LSB    0
#define CLOCKS_INTR_CLK_SYS_RESUS_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_INTE
// Description : Interrupt Enable
#define CLOCKS_INTE_OFFSET 0x000000bc
#define CLOCKS_INTE_BITS   0x00000001
#define CLOCKS_INTE_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_INTE_CLK_SYS_RESUS
// Description : None
#define CLOCKS_INTE_CLK_SYS_RESUS_RESET  0x0
#define CLOCKS_INTE_CLK_SYS_RESUS_BITS   0x00000001
#define CLOCKS_INTE_CLK_SYS_RESUS_MSB    0
#define CLOCKS_INTE_CLK_SYS_RESUS_LSB    0
#define CLOCKS_INTE_CLK_SYS_RESUS_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_INTF
// Description : Interrupt Force
#define CLOCKS_INTF_OFFSET 0x000000c0
#define CLOCKS_INTF_BITS   0x00000001
#define CLOCKS_INTF_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_INTF_CLK_SYS_RESUS
// Description : None
#define CLOCKS_INTF_CLK_SYS_RESUS_RESET  0x0
#define CLOCKS_INTF_CLK_SYS_RESUS_BITS   0x00000001
#define CLOCKS_INTF_CLK_SYS_RESUS_MSB    0
#define CLOCKS_INTF_CLK_SYS_RESUS_LSB    0
#define CLOCKS_INTF_CLK_SYS_RESUS_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_INTS
// Description : Interrupt status after masking & forcing
#define CLOCKS_INTS_OFFSET 0x000000c4
#define CLOCKS_INTS_BITS   0x00000001
#define CLOCKS_INTS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : CLOCKS_INTS_CLK_SYS_RESUS
// Description : None
#define CLOCKS_INTS_CLK_SYS_RESUS_RESET  0x0
#define CLOCKS_INTS_CLK_SYS_RESUS_BITS   0x00000001
#define CLOCKS_INTS_CLK_SYS_RESUS_MSB    0
#define CLOCKS_INTS_CLK_SYS_RESUS_LSB    0
#define CLOCKS_INTS_CLK_SYS_RESUS_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_CLOCKS_DEFINED
