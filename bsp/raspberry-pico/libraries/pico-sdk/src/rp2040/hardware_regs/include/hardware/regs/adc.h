/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : ADC
// Version        : 2
// Bus type       : apb
// Description    : Control and data interface to SAR ADC
// =============================================================================
#ifndef HARDWARE_REGS_ADC_DEFINED
#define HARDWARE_REGS_ADC_DEFINED
// =============================================================================
// Register    : ADC_CS
// Description : ADC Control and Status
#define ADC_CS_OFFSET 0x00000000
#define ADC_CS_BITS   0x001f770f
#define ADC_CS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : ADC_CS_RROBIN
// Description : Round-robin sampling. 1 bit per channel. Set all bits to 0 to
//               disable.
//               Otherwise, the ADC will cycle through each enabled channel in a
//               round-robin fashion.
//               The first channel to be sampled will be the one currently
//               indicated by AINSEL.
//               AINSEL will be updated after each conversion with the
//               newly-selected channel.
#define ADC_CS_RROBIN_RESET  0x00
#define ADC_CS_RROBIN_BITS   0x001f0000
#define ADC_CS_RROBIN_MSB    20
#define ADC_CS_RROBIN_LSB    16
#define ADC_CS_RROBIN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_AINSEL
// Description : Select analog mux input. Updated automatically in round-robin
//               mode.
#define ADC_CS_AINSEL_RESET  0x0
#define ADC_CS_AINSEL_BITS   0x00007000
#define ADC_CS_AINSEL_MSB    14
#define ADC_CS_AINSEL_LSB    12
#define ADC_CS_AINSEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_ERR_STICKY
// Description : Some past ADC conversion encountered an error. Write 1 to
//               clear.
#define ADC_CS_ERR_STICKY_RESET  0x0
#define ADC_CS_ERR_STICKY_BITS   0x00000400
#define ADC_CS_ERR_STICKY_MSB    10
#define ADC_CS_ERR_STICKY_LSB    10
#define ADC_CS_ERR_STICKY_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_ERR
// Description : The most recent ADC conversion encountered an error; result is
//               undefined or noisy.
#define ADC_CS_ERR_RESET  0x0
#define ADC_CS_ERR_BITS   0x00000200
#define ADC_CS_ERR_MSB    9
#define ADC_CS_ERR_LSB    9
#define ADC_CS_ERR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_READY
// Description : 1 if the ADC is ready to start a new conversion. Implies any
//               previous conversion has completed.
//               0 whilst conversion in progress.
#define ADC_CS_READY_RESET  0x0
#define ADC_CS_READY_BITS   0x00000100
#define ADC_CS_READY_MSB    8
#define ADC_CS_READY_LSB    8
#define ADC_CS_READY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_START_MANY
// Description : Continuously perform conversions whilst this bit is 1. A new
//               conversion will start immediately after the previous finishes.
#define ADC_CS_START_MANY_RESET  0x0
#define ADC_CS_START_MANY_BITS   0x00000008
#define ADC_CS_START_MANY_MSB    3
#define ADC_CS_START_MANY_LSB    3
#define ADC_CS_START_MANY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_START_ONCE
// Description : Start a single conversion. Self-clearing. Ignored if start_many
//               is asserted.
#define ADC_CS_START_ONCE_RESET  0x0
#define ADC_CS_START_ONCE_BITS   0x00000004
#define ADC_CS_START_ONCE_MSB    2
#define ADC_CS_START_ONCE_LSB    2
#define ADC_CS_START_ONCE_ACCESS "SC"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_TS_EN
// Description : Power on temperature sensor. 1 - enabled. 0 - disabled.
#define ADC_CS_TS_EN_RESET  0x0
#define ADC_CS_TS_EN_BITS   0x00000002
#define ADC_CS_TS_EN_MSB    1
#define ADC_CS_TS_EN_LSB    1
#define ADC_CS_TS_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_EN
// Description : Power on ADC and enable its clock.
//               1 - enabled. 0 - disabled.
#define ADC_CS_EN_RESET  0x0
#define ADC_CS_EN_BITS   0x00000001
#define ADC_CS_EN_MSB    0
#define ADC_CS_EN_LSB    0
#define ADC_CS_EN_ACCESS "RW"
// =============================================================================
// Register    : ADC_RESULT
// Description : Result of most recent ADC conversion
#define ADC_RESULT_OFFSET 0x00000004
#define ADC_RESULT_BITS   0x00000fff
#define ADC_RESULT_RESET  0x00000000
#define ADC_RESULT_MSB    11
#define ADC_RESULT_LSB    0
#define ADC_RESULT_ACCESS "RO"
// =============================================================================
// Register    : ADC_FCS
// Description : FIFO control and status
#define ADC_FCS_OFFSET 0x00000008
#define ADC_FCS_BITS   0x0f0f0f0f
#define ADC_FCS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_THRESH
// Description : DREQ/IRQ asserted when level >= threshold
#define ADC_FCS_THRESH_RESET  0x0
#define ADC_FCS_THRESH_BITS   0x0f000000
#define ADC_FCS_THRESH_MSB    27
#define ADC_FCS_THRESH_LSB    24
#define ADC_FCS_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_LEVEL
// Description : The number of conversion results currently waiting in the FIFO
#define ADC_FCS_LEVEL_RESET  0x0
#define ADC_FCS_LEVEL_BITS   0x000f0000
#define ADC_FCS_LEVEL_MSB    19
#define ADC_FCS_LEVEL_LSB    16
#define ADC_FCS_LEVEL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_OVER
// Description : 1 if the FIFO has been overflowed. Write 1 to clear.
#define ADC_FCS_OVER_RESET  0x0
#define ADC_FCS_OVER_BITS   0x00000800
#define ADC_FCS_OVER_MSB    11
#define ADC_FCS_OVER_LSB    11
#define ADC_FCS_OVER_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_UNDER
// Description : 1 if the FIFO has been underflowed. Write 1 to clear.
#define ADC_FCS_UNDER_RESET  0x0
#define ADC_FCS_UNDER_BITS   0x00000400
#define ADC_FCS_UNDER_MSB    10
#define ADC_FCS_UNDER_LSB    10
#define ADC_FCS_UNDER_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_FULL
// Description : None
#define ADC_FCS_FULL_RESET  0x0
#define ADC_FCS_FULL_BITS   0x00000200
#define ADC_FCS_FULL_MSB    9
#define ADC_FCS_FULL_LSB    9
#define ADC_FCS_FULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_EMPTY
// Description : None
#define ADC_FCS_EMPTY_RESET  0x0
#define ADC_FCS_EMPTY_BITS   0x00000100
#define ADC_FCS_EMPTY_MSB    8
#define ADC_FCS_EMPTY_LSB    8
#define ADC_FCS_EMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_DREQ_EN
// Description : If 1: assert DMA requests when FIFO contains data
#define ADC_FCS_DREQ_EN_RESET  0x0
#define ADC_FCS_DREQ_EN_BITS   0x00000008
#define ADC_FCS_DREQ_EN_MSB    3
#define ADC_FCS_DREQ_EN_LSB    3
#define ADC_FCS_DREQ_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_ERR
// Description : If 1: conversion error bit appears in the FIFO alongside the
//               result
#define ADC_FCS_ERR_RESET  0x0
#define ADC_FCS_ERR_BITS   0x00000004
#define ADC_FCS_ERR_MSB    2
#define ADC_FCS_ERR_LSB    2
#define ADC_FCS_ERR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_SHIFT
// Description : If 1: FIFO results are right-shifted to be one byte in size.
//               Enables DMA to byte buffers.
#define ADC_FCS_SHIFT_RESET  0x0
#define ADC_FCS_SHIFT_BITS   0x00000002
#define ADC_FCS_SHIFT_MSB    1
#define ADC_FCS_SHIFT_LSB    1
#define ADC_FCS_SHIFT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_EN
// Description : If 1: write result to the FIFO after each conversion.
#define ADC_FCS_EN_RESET  0x0
#define ADC_FCS_EN_BITS   0x00000001
#define ADC_FCS_EN_MSB    0
#define ADC_FCS_EN_LSB    0
#define ADC_FCS_EN_ACCESS "RW"
// =============================================================================
// Register    : ADC_FIFO
// Description : Conversion result FIFO
#define ADC_FIFO_OFFSET 0x0000000c
#define ADC_FIFO_BITS   0x00008fff
#define ADC_FIFO_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : ADC_FIFO_ERR
// Description : 1 if this particular sample experienced a conversion error.
//               Remains in the same location if the sample is shifted.
#define ADC_FIFO_ERR_RESET  "-"
#define ADC_FIFO_ERR_BITS   0x00008000
#define ADC_FIFO_ERR_MSB    15
#define ADC_FIFO_ERR_LSB    15
#define ADC_FIFO_ERR_ACCESS "RF"
// -----------------------------------------------------------------------------
// Field       : ADC_FIFO_VAL
// Description : None
#define ADC_FIFO_VAL_RESET  "-"
#define ADC_FIFO_VAL_BITS   0x00000fff
#define ADC_FIFO_VAL_MSB    11
#define ADC_FIFO_VAL_LSB    0
#define ADC_FIFO_VAL_ACCESS "RF"
// =============================================================================
// Register    : ADC_DIV
// Description : Clock divider. If non-zero, CS_START_MANY will start
//               conversions
//               at regular intervals rather than back-to-back.
//               The divider is reset when either of these fields are written.
//               Total period is 1 + INT + FRAC / 256
#define ADC_DIV_OFFSET 0x00000010
#define ADC_DIV_BITS   0x00ffffff
#define ADC_DIV_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : ADC_DIV_INT
// Description : Integer part of clock divisor.
#define ADC_DIV_INT_RESET  0x0000
#define ADC_DIV_INT_BITS   0x00ffff00
#define ADC_DIV_INT_MSB    23
#define ADC_DIV_INT_LSB    8
#define ADC_DIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_DIV_FRAC
// Description : Fractional part of clock divisor. First-order delta-sigma.
#define ADC_DIV_FRAC_RESET  0x00
#define ADC_DIV_FRAC_BITS   0x000000ff
#define ADC_DIV_FRAC_MSB    7
#define ADC_DIV_FRAC_LSB    0
#define ADC_DIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : ADC_INTR
// Description : Raw Interrupts
#define ADC_INTR_OFFSET 0x00000014
#define ADC_INTR_BITS   0x00000001
#define ADC_INTR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : ADC_INTR_FIFO
// Description : Triggered when the sample FIFO reaches a certain level.
//               This level can be programmed via the FCS_THRESH field.
#define ADC_INTR_FIFO_RESET  0x0
#define ADC_INTR_FIFO_BITS   0x00000001
#define ADC_INTR_FIFO_MSB    0
#define ADC_INTR_FIFO_LSB    0
#define ADC_INTR_FIFO_ACCESS "RO"
// =============================================================================
// Register    : ADC_INTE
// Description : Interrupt Enable
#define ADC_INTE_OFFSET 0x00000018
#define ADC_INTE_BITS   0x00000001
#define ADC_INTE_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : ADC_INTE_FIFO
// Description : Triggered when the sample FIFO reaches a certain level.
//               This level can be programmed via the FCS_THRESH field.
#define ADC_INTE_FIFO_RESET  0x0
#define ADC_INTE_FIFO_BITS   0x00000001
#define ADC_INTE_FIFO_MSB    0
#define ADC_INTE_FIFO_LSB    0
#define ADC_INTE_FIFO_ACCESS "RW"
// =============================================================================
// Register    : ADC_INTF
// Description : Interrupt Force
#define ADC_INTF_OFFSET 0x0000001c
#define ADC_INTF_BITS   0x00000001
#define ADC_INTF_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : ADC_INTF_FIFO
// Description : Triggered when the sample FIFO reaches a certain level.
//               This level can be programmed via the FCS_THRESH field.
#define ADC_INTF_FIFO_RESET  0x0
#define ADC_INTF_FIFO_BITS   0x00000001
#define ADC_INTF_FIFO_MSB    0
#define ADC_INTF_FIFO_LSB    0
#define ADC_INTF_FIFO_ACCESS "RW"
// =============================================================================
// Register    : ADC_INTS
// Description : Interrupt status after masking & forcing
#define ADC_INTS_OFFSET 0x00000020
#define ADC_INTS_BITS   0x00000001
#define ADC_INTS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : ADC_INTS_FIFO
// Description : Triggered when the sample FIFO reaches a certain level.
//               This level can be programmed via the FCS_THRESH field.
#define ADC_INTS_FIFO_RESET  0x0
#define ADC_INTS_FIFO_BITS   0x00000001
#define ADC_INTS_FIFO_MSB    0
#define ADC_INTS_FIFO_LSB    0
#define ADC_INTS_FIFO_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_ADC_DEFINED
