/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : IO_QSPI
// Version        : 1
// Bus type       : apb
// Description    : None
// =============================================================================
#ifndef HARDWARE_REGS_IO_QSPI_DEFINED
#define HARDWARE_REGS_IO_QSPI_DEFINED
// =============================================================================
// Register    : IO_QSPI_GPIO_QSPI_SCLK_STATUS
// Description : GPIO status
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OFFSET 0x00000000
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_BITS   0x050a3300
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SCLK_STATUS_IRQTOPROC
// Description : interrupt to processors, after override is applied
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_IRQTOPROC_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_IRQTOPROC_BITS   0x04000000
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_IRQTOPROC_MSB    26
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_IRQTOPROC_LSB    26
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_IRQTOPROC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SCLK_STATUS_IRQFROMPAD
// Description : interrupt from pad before override is applied
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_IRQFROMPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_IRQFROMPAD_BITS   0x01000000
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_IRQFROMPAD_MSB    24
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_IRQFROMPAD_LSB    24
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_IRQFROMPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SCLK_STATUS_INTOPERI
// Description : input signal to peripheral, after override is applied
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_INTOPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_INTOPERI_BITS   0x00080000
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_INTOPERI_MSB    19
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_INTOPERI_LSB    19
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_INTOPERI_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SCLK_STATUS_INFROMPAD
// Description : input signal from pad, before override is applied
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_INFROMPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_INFROMPAD_BITS   0x00020000
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_INFROMPAD_MSB    17
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_INFROMPAD_LSB    17
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_INFROMPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SCLK_STATUS_OETOPAD
// Description : output enable to pad after register override is applied
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OETOPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OETOPAD_BITS   0x00002000
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OETOPAD_MSB    13
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OETOPAD_LSB    13
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OETOPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SCLK_STATUS_OEFROMPERI
// Description : output enable from selected peripheral, before register
//               override is applied
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OEFROMPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OEFROMPERI_BITS   0x00001000
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OEFROMPERI_MSB    12
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OEFROMPERI_LSB    12
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OEFROMPERI_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SCLK_STATUS_OUTTOPAD
// Description : output signal to pad after register override is applied
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OUTTOPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OUTTOPAD_BITS   0x00000200
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OUTTOPAD_MSB    9
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OUTTOPAD_LSB    9
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OUTTOPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SCLK_STATUS_OUTFROMPERI
// Description : output signal from selected peripheral, before register
//               override is applied
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OUTFROMPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OUTFROMPERI_BITS   0x00000100
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OUTFROMPERI_MSB    8
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OUTFROMPERI_LSB    8
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OUTFROMPERI_ACCESS "RO"
// =============================================================================
// Register    : IO_QSPI_GPIO_QSPI_SCLK_CTRL
// Description : GPIO control including function select and overrides.
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OFFSET 0x00000004
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_BITS   0x3003331f
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_RESET  0x0000001f
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER
// Description : 0x0 -> don't invert the interrupt
//               0x1 -> invert the interrupt
//               0x2 -> drive interrupt low
//               0x3 -> drive interrupt high
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER_BITS         0x30000000
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER_MSB          29
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER_LSB          28
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER
// Description : 0x0 -> don't invert the peri input
//               0x1 -> invert the peri input
//               0x2 -> drive peri input low
//               0x3 -> drive peri input high
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER_BITS         0x00030000
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER_MSB          17
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER_LSB          16
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER
// Description : 0x0 -> drive output enable from peripheral signal selected by
//               funcsel
//               0x1 -> drive output enable from inverse of peripheral signal
//               selected by funcsel
//               0x2 -> disable output
//               0x3 -> enable output
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER_RESET         0x0
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER_BITS          0x00003000
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER_MSB           13
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER_LSB           12
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER_ACCESS        "RW"
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER_VALUE_NORMAL  0x0
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER_VALUE_INVERT  0x1
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER_VALUE_DISABLE 0x2
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER_VALUE_ENABLE  0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER
// Description : 0x0 -> drive output from peripheral signal selected by funcsel
//               0x1 -> drive output from inverse of peripheral signal selected
//               by funcsel
//               0x2 -> drive output low
//               0x3 -> drive output high
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER_BITS         0x00000300
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER_MSB          9
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER_LSB          8
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SCLK_CTRL_FUNCSEL
// Description : 0-31 -> selects pin function according to the gpio table
//               31 == NULL
//               0x00 -> xip_sclk
//               0x05 -> sio_30
//               0x1f -> null
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_FUNCSEL_RESET          0x1f
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_FUNCSEL_BITS           0x0000001f
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_FUNCSEL_MSB            4
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_FUNCSEL_LSB            0
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_FUNCSEL_ACCESS         "RW"
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_FUNCSEL_VALUE_XIP_SCLK 0x00
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_FUNCSEL_VALUE_SIO_30   0x05
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_FUNCSEL_VALUE_NULL     0x1f
// =============================================================================
// Register    : IO_QSPI_GPIO_QSPI_SS_STATUS
// Description : GPIO status
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OFFSET 0x00000008
#define IO_QSPI_GPIO_QSPI_SS_STATUS_BITS   0x050a3300
#define IO_QSPI_GPIO_QSPI_SS_STATUS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SS_STATUS_IRQTOPROC
// Description : interrupt to processors, after override is applied
#define IO_QSPI_GPIO_QSPI_SS_STATUS_IRQTOPROC_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SS_STATUS_IRQTOPROC_BITS   0x04000000
#define IO_QSPI_GPIO_QSPI_SS_STATUS_IRQTOPROC_MSB    26
#define IO_QSPI_GPIO_QSPI_SS_STATUS_IRQTOPROC_LSB    26
#define IO_QSPI_GPIO_QSPI_SS_STATUS_IRQTOPROC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SS_STATUS_IRQFROMPAD
// Description : interrupt from pad before override is applied
#define IO_QSPI_GPIO_QSPI_SS_STATUS_IRQFROMPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SS_STATUS_IRQFROMPAD_BITS   0x01000000
#define IO_QSPI_GPIO_QSPI_SS_STATUS_IRQFROMPAD_MSB    24
#define IO_QSPI_GPIO_QSPI_SS_STATUS_IRQFROMPAD_LSB    24
#define IO_QSPI_GPIO_QSPI_SS_STATUS_IRQFROMPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SS_STATUS_INTOPERI
// Description : input signal to peripheral, after override is applied
#define IO_QSPI_GPIO_QSPI_SS_STATUS_INTOPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SS_STATUS_INTOPERI_BITS   0x00080000
#define IO_QSPI_GPIO_QSPI_SS_STATUS_INTOPERI_MSB    19
#define IO_QSPI_GPIO_QSPI_SS_STATUS_INTOPERI_LSB    19
#define IO_QSPI_GPIO_QSPI_SS_STATUS_INTOPERI_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SS_STATUS_INFROMPAD
// Description : input signal from pad, before override is applied
#define IO_QSPI_GPIO_QSPI_SS_STATUS_INFROMPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SS_STATUS_INFROMPAD_BITS   0x00020000
#define IO_QSPI_GPIO_QSPI_SS_STATUS_INFROMPAD_MSB    17
#define IO_QSPI_GPIO_QSPI_SS_STATUS_INFROMPAD_LSB    17
#define IO_QSPI_GPIO_QSPI_SS_STATUS_INFROMPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SS_STATUS_OETOPAD
// Description : output enable to pad after register override is applied
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OETOPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OETOPAD_BITS   0x00002000
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OETOPAD_MSB    13
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OETOPAD_LSB    13
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OETOPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SS_STATUS_OEFROMPERI
// Description : output enable from selected peripheral, before register
//               override is applied
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OEFROMPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OEFROMPERI_BITS   0x00001000
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OEFROMPERI_MSB    12
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OEFROMPERI_LSB    12
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OEFROMPERI_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SS_STATUS_OUTTOPAD
// Description : output signal to pad after register override is applied
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OUTTOPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OUTTOPAD_BITS   0x00000200
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OUTTOPAD_MSB    9
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OUTTOPAD_LSB    9
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OUTTOPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SS_STATUS_OUTFROMPERI
// Description : output signal from selected peripheral, before register
//               override is applied
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OUTFROMPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OUTFROMPERI_BITS   0x00000100
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OUTFROMPERI_MSB    8
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OUTFROMPERI_LSB    8
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OUTFROMPERI_ACCESS "RO"
// =============================================================================
// Register    : IO_QSPI_GPIO_QSPI_SS_CTRL
// Description : GPIO control including function select and overrides.
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OFFSET 0x0000000c
#define IO_QSPI_GPIO_QSPI_SS_CTRL_BITS   0x3003331f
#define IO_QSPI_GPIO_QSPI_SS_CTRL_RESET  0x0000001f
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER
// Description : 0x0 -> don't invert the interrupt
//               0x1 -> invert the interrupt
//               0x2 -> drive interrupt low
//               0x3 -> drive interrupt high
#define IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER_BITS         0x30000000
#define IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER_MSB          29
#define IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER_LSB          28
#define IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER
// Description : 0x0 -> don't invert the peri input
//               0x1 -> invert the peri input
//               0x2 -> drive peri input low
//               0x3 -> drive peri input high
#define IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER_BITS         0x00030000
#define IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER_MSB          17
#define IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER_LSB          16
#define IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER
// Description : 0x0 -> drive output enable from peripheral signal selected by
//               funcsel
//               0x1 -> drive output enable from inverse of peripheral signal
//               selected by funcsel
//               0x2 -> disable output
//               0x3 -> enable output
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_RESET         0x0
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_BITS          0x00003000
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_MSB           13
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_LSB           12
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_ACCESS        "RW"
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_VALUE_NORMAL  0x0
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_VALUE_INVERT  0x1
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_VALUE_DISABLE 0x2
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_VALUE_ENABLE  0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER
// Description : 0x0 -> drive output from peripheral signal selected by funcsel
//               0x1 -> drive output from inverse of peripheral signal selected
//               by funcsel
//               0x2 -> drive output low
//               0x3 -> drive output high
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_BITS         0x00000300
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_MSB          9
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_LSB          8
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SS_CTRL_FUNCSEL
// Description : 0-31 -> selects pin function according to the gpio table
//               31 == NULL
//               0x00 -> xip_ss_n
//               0x05 -> sio_31
//               0x1f -> null
#define IO_QSPI_GPIO_QSPI_SS_CTRL_FUNCSEL_RESET          0x1f
#define IO_QSPI_GPIO_QSPI_SS_CTRL_FUNCSEL_BITS           0x0000001f
#define IO_QSPI_GPIO_QSPI_SS_CTRL_FUNCSEL_MSB            4
#define IO_QSPI_GPIO_QSPI_SS_CTRL_FUNCSEL_LSB            0
#define IO_QSPI_GPIO_QSPI_SS_CTRL_FUNCSEL_ACCESS         "RW"
#define IO_QSPI_GPIO_QSPI_SS_CTRL_FUNCSEL_VALUE_XIP_SS_N 0x00
#define IO_QSPI_GPIO_QSPI_SS_CTRL_FUNCSEL_VALUE_SIO_31   0x05
#define IO_QSPI_GPIO_QSPI_SS_CTRL_FUNCSEL_VALUE_NULL     0x1f
// =============================================================================
// Register    : IO_QSPI_GPIO_QSPI_SD0_STATUS
// Description : GPIO status
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OFFSET 0x00000010
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_BITS   0x050a3300
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD0_STATUS_IRQTOPROC
// Description : interrupt to processors, after override is applied
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_IRQTOPROC_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_IRQTOPROC_BITS   0x04000000
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_IRQTOPROC_MSB    26
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_IRQTOPROC_LSB    26
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_IRQTOPROC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD0_STATUS_IRQFROMPAD
// Description : interrupt from pad before override is applied
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_IRQFROMPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_IRQFROMPAD_BITS   0x01000000
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_IRQFROMPAD_MSB    24
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_IRQFROMPAD_LSB    24
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_IRQFROMPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD0_STATUS_INTOPERI
// Description : input signal to peripheral, after override is applied
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_INTOPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_INTOPERI_BITS   0x00080000
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_INTOPERI_MSB    19
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_INTOPERI_LSB    19
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_INTOPERI_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD0_STATUS_INFROMPAD
// Description : input signal from pad, before override is applied
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_INFROMPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_INFROMPAD_BITS   0x00020000
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_INFROMPAD_MSB    17
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_INFROMPAD_LSB    17
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_INFROMPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD0_STATUS_OETOPAD
// Description : output enable to pad after register override is applied
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OETOPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OETOPAD_BITS   0x00002000
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OETOPAD_MSB    13
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OETOPAD_LSB    13
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OETOPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD0_STATUS_OEFROMPERI
// Description : output enable from selected peripheral, before register
//               override is applied
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OEFROMPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OEFROMPERI_BITS   0x00001000
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OEFROMPERI_MSB    12
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OEFROMPERI_LSB    12
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OEFROMPERI_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD0_STATUS_OUTTOPAD
// Description : output signal to pad after register override is applied
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OUTTOPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OUTTOPAD_BITS   0x00000200
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OUTTOPAD_MSB    9
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OUTTOPAD_LSB    9
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OUTTOPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD0_STATUS_OUTFROMPERI
// Description : output signal from selected peripheral, before register
//               override is applied
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OUTFROMPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OUTFROMPERI_BITS   0x00000100
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OUTFROMPERI_MSB    8
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OUTFROMPERI_LSB    8
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OUTFROMPERI_ACCESS "RO"
// =============================================================================
// Register    : IO_QSPI_GPIO_QSPI_SD0_CTRL
// Description : GPIO control including function select and overrides.
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OFFSET 0x00000014
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_BITS   0x3003331f
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_RESET  0x0000001f
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER
// Description : 0x0 -> don't invert the interrupt
//               0x1 -> invert the interrupt
//               0x2 -> drive interrupt low
//               0x3 -> drive interrupt high
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER_BITS         0x30000000
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER_MSB          29
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER_LSB          28
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER
// Description : 0x0 -> don't invert the peri input
//               0x1 -> invert the peri input
//               0x2 -> drive peri input low
//               0x3 -> drive peri input high
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER_BITS         0x00030000
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER_MSB          17
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER_LSB          16
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER
// Description : 0x0 -> drive output enable from peripheral signal selected by
//               funcsel
//               0x1 -> drive output enable from inverse of peripheral signal
//               selected by funcsel
//               0x2 -> disable output
//               0x3 -> enable output
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER_RESET         0x0
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER_BITS          0x00003000
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER_MSB           13
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER_LSB           12
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER_ACCESS        "RW"
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER_VALUE_NORMAL  0x0
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER_VALUE_INVERT  0x1
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER_VALUE_DISABLE 0x2
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER_VALUE_ENABLE  0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER
// Description : 0x0 -> drive output from peripheral signal selected by funcsel
//               0x1 -> drive output from inverse of peripheral signal selected
//               by funcsel
//               0x2 -> drive output low
//               0x3 -> drive output high
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER_BITS         0x00000300
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER_MSB          9
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER_LSB          8
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD0_CTRL_FUNCSEL
// Description : 0-31 -> selects pin function according to the gpio table
//               31 == NULL
//               0x00 -> xip_sd0
//               0x05 -> sio_32
//               0x1f -> null
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_FUNCSEL_RESET         0x1f
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_FUNCSEL_BITS          0x0000001f
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_FUNCSEL_MSB           4
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_FUNCSEL_LSB           0
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_FUNCSEL_ACCESS        "RW"
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_FUNCSEL_VALUE_XIP_SD0 0x00
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_FUNCSEL_VALUE_SIO_32  0x05
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_FUNCSEL_VALUE_NULL    0x1f
// =============================================================================
// Register    : IO_QSPI_GPIO_QSPI_SD1_STATUS
// Description : GPIO status
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OFFSET 0x00000018
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_BITS   0x050a3300
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD1_STATUS_IRQTOPROC
// Description : interrupt to processors, after override is applied
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_IRQTOPROC_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_IRQTOPROC_BITS   0x04000000
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_IRQTOPROC_MSB    26
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_IRQTOPROC_LSB    26
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_IRQTOPROC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD1_STATUS_IRQFROMPAD
// Description : interrupt from pad before override is applied
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_IRQFROMPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_IRQFROMPAD_BITS   0x01000000
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_IRQFROMPAD_MSB    24
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_IRQFROMPAD_LSB    24
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_IRQFROMPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD1_STATUS_INTOPERI
// Description : input signal to peripheral, after override is applied
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_INTOPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_INTOPERI_BITS   0x00080000
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_INTOPERI_MSB    19
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_INTOPERI_LSB    19
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_INTOPERI_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD1_STATUS_INFROMPAD
// Description : input signal from pad, before override is applied
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_INFROMPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_INFROMPAD_BITS   0x00020000
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_INFROMPAD_MSB    17
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_INFROMPAD_LSB    17
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_INFROMPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD1_STATUS_OETOPAD
// Description : output enable to pad after register override is applied
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OETOPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OETOPAD_BITS   0x00002000
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OETOPAD_MSB    13
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OETOPAD_LSB    13
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OETOPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD1_STATUS_OEFROMPERI
// Description : output enable from selected peripheral, before register
//               override is applied
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OEFROMPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OEFROMPERI_BITS   0x00001000
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OEFROMPERI_MSB    12
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OEFROMPERI_LSB    12
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OEFROMPERI_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD1_STATUS_OUTTOPAD
// Description : output signal to pad after register override is applied
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OUTTOPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OUTTOPAD_BITS   0x00000200
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OUTTOPAD_MSB    9
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OUTTOPAD_LSB    9
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OUTTOPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD1_STATUS_OUTFROMPERI
// Description : output signal from selected peripheral, before register
//               override is applied
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OUTFROMPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OUTFROMPERI_BITS   0x00000100
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OUTFROMPERI_MSB    8
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OUTFROMPERI_LSB    8
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OUTFROMPERI_ACCESS "RO"
// =============================================================================
// Register    : IO_QSPI_GPIO_QSPI_SD1_CTRL
// Description : GPIO control including function select and overrides.
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OFFSET 0x0000001c
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_BITS   0x3003331f
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_RESET  0x0000001f
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER
// Description : 0x0 -> don't invert the interrupt
//               0x1 -> invert the interrupt
//               0x2 -> drive interrupt low
//               0x3 -> drive interrupt high
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER_BITS         0x30000000
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER_MSB          29
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER_LSB          28
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER
// Description : 0x0 -> don't invert the peri input
//               0x1 -> invert the peri input
//               0x2 -> drive peri input low
//               0x3 -> drive peri input high
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_BITS         0x00030000
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_MSB          17
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_LSB          16
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER
// Description : 0x0 -> drive output enable from peripheral signal selected by
//               funcsel
//               0x1 -> drive output enable from inverse of peripheral signal
//               selected by funcsel
//               0x2 -> disable output
//               0x3 -> enable output
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER_RESET         0x0
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER_BITS          0x00003000
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER_MSB           13
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER_LSB           12
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER_ACCESS        "RW"
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER_VALUE_NORMAL  0x0
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER_VALUE_INVERT  0x1
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER_VALUE_DISABLE 0x2
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER_VALUE_ENABLE  0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER
// Description : 0x0 -> drive output from peripheral signal selected by funcsel
//               0x1 -> drive output from inverse of peripheral signal selected
//               by funcsel
//               0x2 -> drive output low
//               0x3 -> drive output high
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER_BITS         0x00000300
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER_MSB          9
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER_LSB          8
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD1_CTRL_FUNCSEL
// Description : 0-31 -> selects pin function according to the gpio table
//               31 == NULL
//               0x00 -> xip_sd1
//               0x05 -> sio_33
//               0x1f -> null
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_FUNCSEL_RESET         0x1f
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_FUNCSEL_BITS          0x0000001f
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_FUNCSEL_MSB           4
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_FUNCSEL_LSB           0
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_FUNCSEL_ACCESS        "RW"
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_FUNCSEL_VALUE_XIP_SD1 0x00
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_FUNCSEL_VALUE_SIO_33  0x05
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_FUNCSEL_VALUE_NULL    0x1f
// =============================================================================
// Register    : IO_QSPI_GPIO_QSPI_SD2_STATUS
// Description : GPIO status
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OFFSET 0x00000020
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_BITS   0x050a3300
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD2_STATUS_IRQTOPROC
// Description : interrupt to processors, after override is applied
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_IRQTOPROC_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_IRQTOPROC_BITS   0x04000000
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_IRQTOPROC_MSB    26
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_IRQTOPROC_LSB    26
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_IRQTOPROC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD2_STATUS_IRQFROMPAD
// Description : interrupt from pad before override is applied
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_IRQFROMPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_IRQFROMPAD_BITS   0x01000000
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_IRQFROMPAD_MSB    24
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_IRQFROMPAD_LSB    24
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_IRQFROMPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD2_STATUS_INTOPERI
// Description : input signal to peripheral, after override is applied
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_INTOPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_INTOPERI_BITS   0x00080000
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_INTOPERI_MSB    19
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_INTOPERI_LSB    19
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_INTOPERI_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD2_STATUS_INFROMPAD
// Description : input signal from pad, before override is applied
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_INFROMPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_INFROMPAD_BITS   0x00020000
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_INFROMPAD_MSB    17
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_INFROMPAD_LSB    17
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_INFROMPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD2_STATUS_OETOPAD
// Description : output enable to pad after register override is applied
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OETOPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OETOPAD_BITS   0x00002000
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OETOPAD_MSB    13
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OETOPAD_LSB    13
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OETOPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD2_STATUS_OEFROMPERI
// Description : output enable from selected peripheral, before register
//               override is applied
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OEFROMPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OEFROMPERI_BITS   0x00001000
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OEFROMPERI_MSB    12
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OEFROMPERI_LSB    12
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OEFROMPERI_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD2_STATUS_OUTTOPAD
// Description : output signal to pad after register override is applied
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OUTTOPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OUTTOPAD_BITS   0x00000200
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OUTTOPAD_MSB    9
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OUTTOPAD_LSB    9
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OUTTOPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD2_STATUS_OUTFROMPERI
// Description : output signal from selected peripheral, before register
//               override is applied
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OUTFROMPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OUTFROMPERI_BITS   0x00000100
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OUTFROMPERI_MSB    8
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OUTFROMPERI_LSB    8
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OUTFROMPERI_ACCESS "RO"
// =============================================================================
// Register    : IO_QSPI_GPIO_QSPI_SD2_CTRL
// Description : GPIO control including function select and overrides.
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OFFSET 0x00000024
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_BITS   0x3003331f
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_RESET  0x0000001f
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER
// Description : 0x0 -> don't invert the interrupt
//               0x1 -> invert the interrupt
//               0x2 -> drive interrupt low
//               0x3 -> drive interrupt high
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER_BITS         0x30000000
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER_MSB          29
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER_LSB          28
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER
// Description : 0x0 -> don't invert the peri input
//               0x1 -> invert the peri input
//               0x2 -> drive peri input low
//               0x3 -> drive peri input high
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER_BITS         0x00030000
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER_MSB          17
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER_LSB          16
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER
// Description : 0x0 -> drive output enable from peripheral signal selected by
//               funcsel
//               0x1 -> drive output enable from inverse of peripheral signal
//               selected by funcsel
//               0x2 -> disable output
//               0x3 -> enable output
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER_RESET         0x0
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER_BITS          0x00003000
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER_MSB           13
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER_LSB           12
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER_ACCESS        "RW"
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER_VALUE_NORMAL  0x0
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER_VALUE_INVERT  0x1
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER_VALUE_DISABLE 0x2
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER_VALUE_ENABLE  0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER
// Description : 0x0 -> drive output from peripheral signal selected by funcsel
//               0x1 -> drive output from inverse of peripheral signal selected
//               by funcsel
//               0x2 -> drive output low
//               0x3 -> drive output high
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER_BITS         0x00000300
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER_MSB          9
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER_LSB          8
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD2_CTRL_FUNCSEL
// Description : 0-31 -> selects pin function according to the gpio table
//               31 == NULL
//               0x00 -> xip_sd2
//               0x05 -> sio_34
//               0x1f -> null
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_FUNCSEL_RESET         0x1f
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_FUNCSEL_BITS          0x0000001f
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_FUNCSEL_MSB           4
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_FUNCSEL_LSB           0
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_FUNCSEL_ACCESS        "RW"
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_FUNCSEL_VALUE_XIP_SD2 0x00
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_FUNCSEL_VALUE_SIO_34  0x05
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_FUNCSEL_VALUE_NULL    0x1f
// =============================================================================
// Register    : IO_QSPI_GPIO_QSPI_SD3_STATUS
// Description : GPIO status
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OFFSET 0x00000028
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_BITS   0x050a3300
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD3_STATUS_IRQTOPROC
// Description : interrupt to processors, after override is applied
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_IRQTOPROC_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_IRQTOPROC_BITS   0x04000000
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_IRQTOPROC_MSB    26
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_IRQTOPROC_LSB    26
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_IRQTOPROC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD3_STATUS_IRQFROMPAD
// Description : interrupt from pad before override is applied
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_IRQFROMPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_IRQFROMPAD_BITS   0x01000000
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_IRQFROMPAD_MSB    24
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_IRQFROMPAD_LSB    24
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_IRQFROMPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD3_STATUS_INTOPERI
// Description : input signal to peripheral, after override is applied
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_INTOPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_INTOPERI_BITS   0x00080000
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_INTOPERI_MSB    19
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_INTOPERI_LSB    19
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_INTOPERI_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD3_STATUS_INFROMPAD
// Description : input signal from pad, before override is applied
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_INFROMPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_INFROMPAD_BITS   0x00020000
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_INFROMPAD_MSB    17
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_INFROMPAD_LSB    17
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_INFROMPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD3_STATUS_OETOPAD
// Description : output enable to pad after register override is applied
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OETOPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OETOPAD_BITS   0x00002000
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OETOPAD_MSB    13
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OETOPAD_LSB    13
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OETOPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD3_STATUS_OEFROMPERI
// Description : output enable from selected peripheral, before register
//               override is applied
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OEFROMPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OEFROMPERI_BITS   0x00001000
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OEFROMPERI_MSB    12
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OEFROMPERI_LSB    12
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OEFROMPERI_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD3_STATUS_OUTTOPAD
// Description : output signal to pad after register override is applied
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OUTTOPAD_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OUTTOPAD_BITS   0x00000200
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OUTTOPAD_MSB    9
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OUTTOPAD_LSB    9
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OUTTOPAD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD3_STATUS_OUTFROMPERI
// Description : output signal from selected peripheral, before register
//               override is applied
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OUTFROMPERI_RESET  0x0
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OUTFROMPERI_BITS   0x00000100
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OUTFROMPERI_MSB    8
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OUTFROMPERI_LSB    8
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OUTFROMPERI_ACCESS "RO"
// =============================================================================
// Register    : IO_QSPI_GPIO_QSPI_SD3_CTRL
// Description : GPIO control including function select and overrides.
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OFFSET 0x0000002c
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_BITS   0x3003331f
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_RESET  0x0000001f
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER
// Description : 0x0 -> don't invert the interrupt
//               0x1 -> invert the interrupt
//               0x2 -> drive interrupt low
//               0x3 -> drive interrupt high
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER_BITS         0x30000000
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER_MSB          29
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER_LSB          28
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER
// Description : 0x0 -> don't invert the peri input
//               0x1 -> invert the peri input
//               0x2 -> drive peri input low
//               0x3 -> drive peri input high
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER_BITS         0x00030000
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER_MSB          17
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER_LSB          16
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER
// Description : 0x0 -> drive output enable from peripheral signal selected by
//               funcsel
//               0x1 -> drive output enable from inverse of peripheral signal
//               selected by funcsel
//               0x2 -> disable output
//               0x3 -> enable output
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER_RESET         0x0
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER_BITS          0x00003000
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER_MSB           13
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER_LSB           12
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER_ACCESS        "RW"
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER_VALUE_NORMAL  0x0
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER_VALUE_INVERT  0x1
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER_VALUE_DISABLE 0x2
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER_VALUE_ENABLE  0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER
// Description : 0x0 -> drive output from peripheral signal selected by funcsel
//               0x1 -> drive output from inverse of peripheral signal selected
//               by funcsel
//               0x2 -> drive output low
//               0x3 -> drive output high
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER_RESET        0x0
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER_BITS         0x00000300
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER_MSB          9
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER_LSB          8
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER_ACCESS       "RW"
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER_VALUE_NORMAL 0x0
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER_VALUE_INVERT 0x1
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER_VALUE_LOW    0x2
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER_VALUE_HIGH   0x3
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_GPIO_QSPI_SD3_CTRL_FUNCSEL
// Description : 0-31 -> selects pin function according to the gpio table
//               31 == NULL
//               0x00 -> xip_sd3
//               0x05 -> sio_35
//               0x1f -> null
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_FUNCSEL_RESET         0x1f
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_FUNCSEL_BITS          0x0000001f
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_FUNCSEL_MSB           4
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_FUNCSEL_LSB           0
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_FUNCSEL_ACCESS        "RW"
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_FUNCSEL_VALUE_XIP_SD3 0x00
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_FUNCSEL_VALUE_SIO_35  0x05
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_FUNCSEL_VALUE_NULL    0x1f
// =============================================================================
// Register    : IO_QSPI_INTR
// Description : Raw Interrupts
#define IO_QSPI_INTR_OFFSET 0x00000030
#define IO_QSPI_INTR_BITS   0x00ffffff
#define IO_QSPI_INTR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD3_EDGE_HIGH
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD3_EDGE_HIGH_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD3_EDGE_HIGH_BITS   0x00800000
#define IO_QSPI_INTR_GPIO_QSPI_SD3_EDGE_HIGH_MSB    23
#define IO_QSPI_INTR_GPIO_QSPI_SD3_EDGE_HIGH_LSB    23
#define IO_QSPI_INTR_GPIO_QSPI_SD3_EDGE_HIGH_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD3_EDGE_LOW
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD3_EDGE_LOW_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD3_EDGE_LOW_BITS   0x00400000
#define IO_QSPI_INTR_GPIO_QSPI_SD3_EDGE_LOW_MSB    22
#define IO_QSPI_INTR_GPIO_QSPI_SD3_EDGE_LOW_LSB    22
#define IO_QSPI_INTR_GPIO_QSPI_SD3_EDGE_LOW_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD3_LEVEL_HIGH
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD3_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD3_LEVEL_HIGH_BITS   0x00200000
#define IO_QSPI_INTR_GPIO_QSPI_SD3_LEVEL_HIGH_MSB    21
#define IO_QSPI_INTR_GPIO_QSPI_SD3_LEVEL_HIGH_LSB    21
#define IO_QSPI_INTR_GPIO_QSPI_SD3_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD3_LEVEL_LOW
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD3_LEVEL_LOW_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD3_LEVEL_LOW_BITS   0x00100000
#define IO_QSPI_INTR_GPIO_QSPI_SD3_LEVEL_LOW_MSB    20
#define IO_QSPI_INTR_GPIO_QSPI_SD3_LEVEL_LOW_LSB    20
#define IO_QSPI_INTR_GPIO_QSPI_SD3_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD2_EDGE_HIGH
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD2_EDGE_HIGH_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD2_EDGE_HIGH_BITS   0x00080000
#define IO_QSPI_INTR_GPIO_QSPI_SD2_EDGE_HIGH_MSB    19
#define IO_QSPI_INTR_GPIO_QSPI_SD2_EDGE_HIGH_LSB    19
#define IO_QSPI_INTR_GPIO_QSPI_SD2_EDGE_HIGH_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD2_EDGE_LOW
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD2_EDGE_LOW_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD2_EDGE_LOW_BITS   0x00040000
#define IO_QSPI_INTR_GPIO_QSPI_SD2_EDGE_LOW_MSB    18
#define IO_QSPI_INTR_GPIO_QSPI_SD2_EDGE_LOW_LSB    18
#define IO_QSPI_INTR_GPIO_QSPI_SD2_EDGE_LOW_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD2_LEVEL_HIGH
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD2_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD2_LEVEL_HIGH_BITS   0x00020000
#define IO_QSPI_INTR_GPIO_QSPI_SD2_LEVEL_HIGH_MSB    17
#define IO_QSPI_INTR_GPIO_QSPI_SD2_LEVEL_HIGH_LSB    17
#define IO_QSPI_INTR_GPIO_QSPI_SD2_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD2_LEVEL_LOW
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD2_LEVEL_LOW_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD2_LEVEL_LOW_BITS   0x00010000
#define IO_QSPI_INTR_GPIO_QSPI_SD2_LEVEL_LOW_MSB    16
#define IO_QSPI_INTR_GPIO_QSPI_SD2_LEVEL_LOW_LSB    16
#define IO_QSPI_INTR_GPIO_QSPI_SD2_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD1_EDGE_HIGH
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD1_EDGE_HIGH_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD1_EDGE_HIGH_BITS   0x00008000
#define IO_QSPI_INTR_GPIO_QSPI_SD1_EDGE_HIGH_MSB    15
#define IO_QSPI_INTR_GPIO_QSPI_SD1_EDGE_HIGH_LSB    15
#define IO_QSPI_INTR_GPIO_QSPI_SD1_EDGE_HIGH_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD1_EDGE_LOW
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD1_EDGE_LOW_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD1_EDGE_LOW_BITS   0x00004000
#define IO_QSPI_INTR_GPIO_QSPI_SD1_EDGE_LOW_MSB    14
#define IO_QSPI_INTR_GPIO_QSPI_SD1_EDGE_LOW_LSB    14
#define IO_QSPI_INTR_GPIO_QSPI_SD1_EDGE_LOW_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD1_LEVEL_HIGH
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD1_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD1_LEVEL_HIGH_BITS   0x00002000
#define IO_QSPI_INTR_GPIO_QSPI_SD1_LEVEL_HIGH_MSB    13
#define IO_QSPI_INTR_GPIO_QSPI_SD1_LEVEL_HIGH_LSB    13
#define IO_QSPI_INTR_GPIO_QSPI_SD1_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD1_LEVEL_LOW
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD1_LEVEL_LOW_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD1_LEVEL_LOW_BITS   0x00001000
#define IO_QSPI_INTR_GPIO_QSPI_SD1_LEVEL_LOW_MSB    12
#define IO_QSPI_INTR_GPIO_QSPI_SD1_LEVEL_LOW_LSB    12
#define IO_QSPI_INTR_GPIO_QSPI_SD1_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD0_EDGE_HIGH
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD0_EDGE_HIGH_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD0_EDGE_HIGH_BITS   0x00000800
#define IO_QSPI_INTR_GPIO_QSPI_SD0_EDGE_HIGH_MSB    11
#define IO_QSPI_INTR_GPIO_QSPI_SD0_EDGE_HIGH_LSB    11
#define IO_QSPI_INTR_GPIO_QSPI_SD0_EDGE_HIGH_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD0_EDGE_LOW
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD0_EDGE_LOW_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD0_EDGE_LOW_BITS   0x00000400
#define IO_QSPI_INTR_GPIO_QSPI_SD0_EDGE_LOW_MSB    10
#define IO_QSPI_INTR_GPIO_QSPI_SD0_EDGE_LOW_LSB    10
#define IO_QSPI_INTR_GPIO_QSPI_SD0_EDGE_LOW_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD0_LEVEL_HIGH
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD0_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD0_LEVEL_HIGH_BITS   0x00000200
#define IO_QSPI_INTR_GPIO_QSPI_SD0_LEVEL_HIGH_MSB    9
#define IO_QSPI_INTR_GPIO_QSPI_SD0_LEVEL_HIGH_LSB    9
#define IO_QSPI_INTR_GPIO_QSPI_SD0_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SD0_LEVEL_LOW
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SD0_LEVEL_LOW_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SD0_LEVEL_LOW_BITS   0x00000100
#define IO_QSPI_INTR_GPIO_QSPI_SD0_LEVEL_LOW_MSB    8
#define IO_QSPI_INTR_GPIO_QSPI_SD0_LEVEL_LOW_LSB    8
#define IO_QSPI_INTR_GPIO_QSPI_SD0_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SS_EDGE_HIGH
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SS_EDGE_HIGH_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SS_EDGE_HIGH_BITS   0x00000080
#define IO_QSPI_INTR_GPIO_QSPI_SS_EDGE_HIGH_MSB    7
#define IO_QSPI_INTR_GPIO_QSPI_SS_EDGE_HIGH_LSB    7
#define IO_QSPI_INTR_GPIO_QSPI_SS_EDGE_HIGH_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SS_EDGE_LOW
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SS_EDGE_LOW_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SS_EDGE_LOW_BITS   0x00000040
#define IO_QSPI_INTR_GPIO_QSPI_SS_EDGE_LOW_MSB    6
#define IO_QSPI_INTR_GPIO_QSPI_SS_EDGE_LOW_LSB    6
#define IO_QSPI_INTR_GPIO_QSPI_SS_EDGE_LOW_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SS_LEVEL_HIGH
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SS_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SS_LEVEL_HIGH_BITS   0x00000020
#define IO_QSPI_INTR_GPIO_QSPI_SS_LEVEL_HIGH_MSB    5
#define IO_QSPI_INTR_GPIO_QSPI_SS_LEVEL_HIGH_LSB    5
#define IO_QSPI_INTR_GPIO_QSPI_SS_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SS_LEVEL_LOW
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SS_LEVEL_LOW_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SS_LEVEL_LOW_BITS   0x00000010
#define IO_QSPI_INTR_GPIO_QSPI_SS_LEVEL_LOW_MSB    4
#define IO_QSPI_INTR_GPIO_QSPI_SS_LEVEL_LOW_LSB    4
#define IO_QSPI_INTR_GPIO_QSPI_SS_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SCLK_EDGE_HIGH
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_EDGE_HIGH_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_EDGE_HIGH_BITS   0x00000008
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_EDGE_HIGH_MSB    3
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_EDGE_HIGH_LSB    3
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_EDGE_HIGH_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SCLK_EDGE_LOW
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_EDGE_LOW_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_EDGE_LOW_BITS   0x00000004
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_EDGE_LOW_MSB    2
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_EDGE_LOW_LSB    2
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_EDGE_LOW_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SCLK_LEVEL_HIGH
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_LEVEL_HIGH_BITS   0x00000002
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_LEVEL_HIGH_MSB    1
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_LEVEL_HIGH_LSB    1
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_INTR_GPIO_QSPI_SCLK_LEVEL_LOW
// Description : None
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_LEVEL_LOW_RESET  0x0
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_LEVEL_LOW_BITS   0x00000001
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_LEVEL_LOW_MSB    0
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_LEVEL_LOW_LSB    0
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_LEVEL_LOW_ACCESS "RO"
// =============================================================================
// Register    : IO_QSPI_PROC0_INTE
// Description : Interrupt Enable for proc0
#define IO_QSPI_PROC0_INTE_OFFSET 0x00000034
#define IO_QSPI_PROC0_INTE_BITS   0x00ffffff
#define IO_QSPI_PROC0_INTE_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_EDGE_HIGH_BITS   0x00800000
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_EDGE_HIGH_MSB    23
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_EDGE_HIGH_LSB    23
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_EDGE_LOW_BITS   0x00400000
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_EDGE_LOW_MSB    22
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_EDGE_LOW_LSB    22
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_LEVEL_HIGH_BITS   0x00200000
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_LEVEL_HIGH_MSB    21
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_LEVEL_HIGH_LSB    21
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_LEVEL_LOW_BITS   0x00100000
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_LEVEL_LOW_MSB    20
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_LEVEL_LOW_LSB    20
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_EDGE_HIGH_BITS   0x00080000
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_EDGE_HIGH_MSB    19
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_EDGE_HIGH_LSB    19
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_EDGE_LOW_BITS   0x00040000
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_EDGE_LOW_MSB    18
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_EDGE_LOW_LSB    18
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_LEVEL_HIGH_BITS   0x00020000
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_LEVEL_HIGH_MSB    17
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_LEVEL_HIGH_LSB    17
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_LEVEL_LOW_BITS   0x00010000
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_LEVEL_LOW_MSB    16
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_LEVEL_LOW_LSB    16
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_EDGE_HIGH_BITS   0x00008000
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_EDGE_HIGH_MSB    15
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_EDGE_HIGH_LSB    15
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_EDGE_LOW_BITS   0x00004000
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_EDGE_LOW_MSB    14
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_EDGE_LOW_LSB    14
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_LEVEL_HIGH_BITS   0x00002000
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_LEVEL_HIGH_MSB    13
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_LEVEL_HIGH_LSB    13
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_LEVEL_LOW_BITS   0x00001000
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_LEVEL_LOW_MSB    12
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_LEVEL_LOW_LSB    12
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_EDGE_HIGH_BITS   0x00000800
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_EDGE_HIGH_MSB    11
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_EDGE_HIGH_LSB    11
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_EDGE_LOW_BITS   0x00000400
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_EDGE_LOW_MSB    10
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_EDGE_LOW_LSB    10
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_LEVEL_HIGH_BITS   0x00000200
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_LEVEL_HIGH_MSB    9
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_LEVEL_HIGH_LSB    9
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_LEVEL_LOW_BITS   0x00000100
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_LEVEL_LOW_MSB    8
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_LEVEL_LOW_LSB    8
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_EDGE_HIGH_BITS   0x00000080
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_EDGE_HIGH_MSB    7
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_EDGE_HIGH_LSB    7
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_EDGE_LOW_BITS   0x00000040
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_EDGE_LOW_MSB    6
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_EDGE_LOW_LSB    6
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_LEVEL_HIGH_BITS   0x00000020
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_LEVEL_HIGH_MSB    5
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_LEVEL_HIGH_LSB    5
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_LEVEL_LOW_BITS   0x00000010
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_LEVEL_LOW_MSB    4
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_LEVEL_LOW_LSB    4
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_EDGE_HIGH_BITS   0x00000008
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_EDGE_HIGH_MSB    3
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_EDGE_HIGH_LSB    3
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_EDGE_LOW_BITS   0x00000004
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_EDGE_LOW_MSB    2
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_EDGE_LOW_LSB    2
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH_BITS   0x00000002
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH_MSB    1
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH_LSB    1
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_LEVEL_LOW_BITS   0x00000001
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_LEVEL_LOW_MSB    0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_LEVEL_LOW_LSB    0
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_LEVEL_LOW_ACCESS "RW"
// =============================================================================
// Register    : IO_QSPI_PROC0_INTF
// Description : Interrupt Force for proc0
#define IO_QSPI_PROC0_INTF_OFFSET 0x00000038
#define IO_QSPI_PROC0_INTF_BITS   0x00ffffff
#define IO_QSPI_PROC0_INTF_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_EDGE_HIGH_BITS   0x00800000
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_EDGE_HIGH_MSB    23
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_EDGE_HIGH_LSB    23
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_EDGE_LOW_BITS   0x00400000
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_EDGE_LOW_MSB    22
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_EDGE_LOW_LSB    22
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_LEVEL_HIGH_BITS   0x00200000
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_LEVEL_HIGH_MSB    21
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_LEVEL_HIGH_LSB    21
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_LEVEL_LOW_BITS   0x00100000
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_LEVEL_LOW_MSB    20
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_LEVEL_LOW_LSB    20
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_EDGE_HIGH_BITS   0x00080000
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_EDGE_HIGH_MSB    19
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_EDGE_HIGH_LSB    19
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_EDGE_LOW_BITS   0x00040000
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_EDGE_LOW_MSB    18
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_EDGE_LOW_LSB    18
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_LEVEL_HIGH_BITS   0x00020000
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_LEVEL_HIGH_MSB    17
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_LEVEL_HIGH_LSB    17
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_LEVEL_LOW_BITS   0x00010000
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_LEVEL_LOW_MSB    16
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_LEVEL_LOW_LSB    16
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_EDGE_HIGH_BITS   0x00008000
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_EDGE_HIGH_MSB    15
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_EDGE_HIGH_LSB    15
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_EDGE_LOW_BITS   0x00004000
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_EDGE_LOW_MSB    14
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_EDGE_LOW_LSB    14
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_LEVEL_HIGH_BITS   0x00002000
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_LEVEL_HIGH_MSB    13
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_LEVEL_HIGH_LSB    13
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_LEVEL_LOW_BITS   0x00001000
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_LEVEL_LOW_MSB    12
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_LEVEL_LOW_LSB    12
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_EDGE_HIGH_BITS   0x00000800
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_EDGE_HIGH_MSB    11
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_EDGE_HIGH_LSB    11
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_EDGE_LOW_BITS   0x00000400
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_EDGE_LOW_MSB    10
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_EDGE_LOW_LSB    10
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_LEVEL_HIGH_BITS   0x00000200
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_LEVEL_HIGH_MSB    9
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_LEVEL_HIGH_LSB    9
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_LEVEL_LOW_BITS   0x00000100
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_LEVEL_LOW_MSB    8
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_LEVEL_LOW_LSB    8
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_EDGE_HIGH_BITS   0x00000080
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_EDGE_HIGH_MSB    7
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_EDGE_HIGH_LSB    7
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_EDGE_LOW_BITS   0x00000040
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_EDGE_LOW_MSB    6
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_EDGE_LOW_LSB    6
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_LEVEL_HIGH_BITS   0x00000020
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_LEVEL_HIGH_MSB    5
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_LEVEL_HIGH_LSB    5
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_LEVEL_LOW_BITS   0x00000010
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_LEVEL_LOW_MSB    4
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_LEVEL_LOW_LSB    4
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_EDGE_HIGH_BITS   0x00000008
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_EDGE_HIGH_MSB    3
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_EDGE_HIGH_LSB    3
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_EDGE_LOW_BITS   0x00000004
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_EDGE_LOW_MSB    2
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_EDGE_LOW_LSB    2
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH_BITS   0x00000002
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH_MSB    1
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH_LSB    1
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_LEVEL_LOW_BITS   0x00000001
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_LEVEL_LOW_MSB    0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_LEVEL_LOW_LSB    0
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_LEVEL_LOW_ACCESS "RW"
// =============================================================================
// Register    : IO_QSPI_PROC0_INTS
// Description : Interrupt status after masking & forcing for proc0
#define IO_QSPI_PROC0_INTS_OFFSET 0x0000003c
#define IO_QSPI_PROC0_INTS_BITS   0x00ffffff
#define IO_QSPI_PROC0_INTS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_EDGE_HIGH_BITS   0x00800000
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_EDGE_HIGH_MSB    23
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_EDGE_HIGH_LSB    23
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_EDGE_LOW_BITS   0x00400000
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_EDGE_LOW_MSB    22
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_EDGE_LOW_LSB    22
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_LEVEL_HIGH_BITS   0x00200000
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_LEVEL_HIGH_MSB    21
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_LEVEL_HIGH_LSB    21
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_LEVEL_LOW_BITS   0x00100000
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_LEVEL_LOW_MSB    20
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_LEVEL_LOW_LSB    20
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_EDGE_HIGH_BITS   0x00080000
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_EDGE_HIGH_MSB    19
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_EDGE_HIGH_LSB    19
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_EDGE_LOW_BITS   0x00040000
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_EDGE_LOW_MSB    18
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_EDGE_LOW_LSB    18
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_LEVEL_HIGH_BITS   0x00020000
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_LEVEL_HIGH_MSB    17
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_LEVEL_HIGH_LSB    17
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_LEVEL_LOW_BITS   0x00010000
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_LEVEL_LOW_MSB    16
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_LEVEL_LOW_LSB    16
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_EDGE_HIGH_BITS   0x00008000
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_EDGE_HIGH_MSB    15
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_EDGE_HIGH_LSB    15
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_EDGE_LOW_BITS   0x00004000
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_EDGE_LOW_MSB    14
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_EDGE_LOW_LSB    14
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_LEVEL_HIGH_BITS   0x00002000
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_LEVEL_HIGH_MSB    13
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_LEVEL_HIGH_LSB    13
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_LEVEL_LOW_BITS   0x00001000
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_LEVEL_LOW_MSB    12
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_LEVEL_LOW_LSB    12
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_EDGE_HIGH_BITS   0x00000800
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_EDGE_HIGH_MSB    11
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_EDGE_HIGH_LSB    11
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_EDGE_LOW_BITS   0x00000400
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_EDGE_LOW_MSB    10
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_EDGE_LOW_LSB    10
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_LEVEL_HIGH_BITS   0x00000200
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_LEVEL_HIGH_MSB    9
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_LEVEL_HIGH_LSB    9
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_LEVEL_LOW_BITS   0x00000100
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_LEVEL_LOW_MSB    8
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_LEVEL_LOW_LSB    8
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_EDGE_HIGH_BITS   0x00000080
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_EDGE_HIGH_MSB    7
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_EDGE_HIGH_LSB    7
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_EDGE_LOW_BITS   0x00000040
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_EDGE_LOW_MSB    6
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_EDGE_LOW_LSB    6
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_LEVEL_HIGH_BITS   0x00000020
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_LEVEL_HIGH_MSB    5
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_LEVEL_HIGH_LSB    5
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_LEVEL_LOW_BITS   0x00000010
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_LEVEL_LOW_MSB    4
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_LEVEL_LOW_LSB    4
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_EDGE_HIGH_BITS   0x00000008
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_EDGE_HIGH_MSB    3
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_EDGE_HIGH_LSB    3
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_EDGE_LOW
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_EDGE_LOW_BITS   0x00000004
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_EDGE_LOW_MSB    2
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_EDGE_LOW_LSB    2
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH_BITS   0x00000002
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH_MSB    1
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH_LSB    1
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_LEVEL_LOW_BITS   0x00000001
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_LEVEL_LOW_MSB    0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_LEVEL_LOW_LSB    0
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_LEVEL_LOW_ACCESS "RO"
// =============================================================================
// Register    : IO_QSPI_PROC1_INTE
// Description : Interrupt Enable for proc1
#define IO_QSPI_PROC1_INTE_OFFSET 0x00000040
#define IO_QSPI_PROC1_INTE_BITS   0x00ffffff
#define IO_QSPI_PROC1_INTE_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_EDGE_HIGH_BITS   0x00800000
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_EDGE_HIGH_MSB    23
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_EDGE_HIGH_LSB    23
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_EDGE_LOW_BITS   0x00400000
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_EDGE_LOW_MSB    22
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_EDGE_LOW_LSB    22
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_LEVEL_HIGH_BITS   0x00200000
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_LEVEL_HIGH_MSB    21
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_LEVEL_HIGH_LSB    21
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_LEVEL_LOW_BITS   0x00100000
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_LEVEL_LOW_MSB    20
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_LEVEL_LOW_LSB    20
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_EDGE_HIGH_BITS   0x00080000
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_EDGE_HIGH_MSB    19
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_EDGE_HIGH_LSB    19
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_EDGE_LOW_BITS   0x00040000
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_EDGE_LOW_MSB    18
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_EDGE_LOW_LSB    18
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_LEVEL_HIGH_BITS   0x00020000
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_LEVEL_HIGH_MSB    17
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_LEVEL_HIGH_LSB    17
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_LEVEL_LOW_BITS   0x00010000
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_LEVEL_LOW_MSB    16
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_LEVEL_LOW_LSB    16
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_EDGE_HIGH_BITS   0x00008000
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_EDGE_HIGH_MSB    15
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_EDGE_HIGH_LSB    15
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_EDGE_LOW_BITS   0x00004000
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_EDGE_LOW_MSB    14
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_EDGE_LOW_LSB    14
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_LEVEL_HIGH_BITS   0x00002000
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_LEVEL_HIGH_MSB    13
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_LEVEL_HIGH_LSB    13
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_LEVEL_LOW_BITS   0x00001000
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_LEVEL_LOW_MSB    12
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_LEVEL_LOW_LSB    12
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_EDGE_HIGH_BITS   0x00000800
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_EDGE_HIGH_MSB    11
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_EDGE_HIGH_LSB    11
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_EDGE_LOW_BITS   0x00000400
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_EDGE_LOW_MSB    10
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_EDGE_LOW_LSB    10
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_LEVEL_HIGH_BITS   0x00000200
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_LEVEL_HIGH_MSB    9
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_LEVEL_HIGH_LSB    9
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_LEVEL_LOW_BITS   0x00000100
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_LEVEL_LOW_MSB    8
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_LEVEL_LOW_LSB    8
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_EDGE_HIGH_BITS   0x00000080
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_EDGE_HIGH_MSB    7
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_EDGE_HIGH_LSB    7
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_EDGE_LOW_BITS   0x00000040
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_EDGE_LOW_MSB    6
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_EDGE_LOW_LSB    6
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_LEVEL_HIGH_BITS   0x00000020
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_LEVEL_HIGH_MSB    5
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_LEVEL_HIGH_LSB    5
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_LEVEL_LOW_BITS   0x00000010
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_LEVEL_LOW_MSB    4
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_LEVEL_LOW_LSB    4
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_EDGE_HIGH_BITS   0x00000008
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_EDGE_HIGH_MSB    3
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_EDGE_HIGH_LSB    3
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_EDGE_LOW_BITS   0x00000004
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_EDGE_LOW_MSB    2
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_EDGE_LOW_LSB    2
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH_BITS   0x00000002
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH_MSB    1
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH_LSB    1
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_LEVEL_LOW_BITS   0x00000001
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_LEVEL_LOW_MSB    0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_LEVEL_LOW_LSB    0
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_LEVEL_LOW_ACCESS "RW"
// =============================================================================
// Register    : IO_QSPI_PROC1_INTF
// Description : Interrupt Force for proc1
#define IO_QSPI_PROC1_INTF_OFFSET 0x00000044
#define IO_QSPI_PROC1_INTF_BITS   0x00ffffff
#define IO_QSPI_PROC1_INTF_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_EDGE_HIGH_BITS   0x00800000
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_EDGE_HIGH_MSB    23
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_EDGE_HIGH_LSB    23
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_EDGE_LOW_BITS   0x00400000
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_EDGE_LOW_MSB    22
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_EDGE_LOW_LSB    22
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_LEVEL_HIGH_BITS   0x00200000
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_LEVEL_HIGH_MSB    21
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_LEVEL_HIGH_LSB    21
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_LEVEL_LOW_BITS   0x00100000
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_LEVEL_LOW_MSB    20
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_LEVEL_LOW_LSB    20
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_EDGE_HIGH_BITS   0x00080000
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_EDGE_HIGH_MSB    19
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_EDGE_HIGH_LSB    19
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_EDGE_LOW_BITS   0x00040000
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_EDGE_LOW_MSB    18
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_EDGE_LOW_LSB    18
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_LEVEL_HIGH_BITS   0x00020000
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_LEVEL_HIGH_MSB    17
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_LEVEL_HIGH_LSB    17
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_LEVEL_LOW_BITS   0x00010000
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_LEVEL_LOW_MSB    16
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_LEVEL_LOW_LSB    16
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_EDGE_HIGH_BITS   0x00008000
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_EDGE_HIGH_MSB    15
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_EDGE_HIGH_LSB    15
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_EDGE_LOW_BITS   0x00004000
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_EDGE_LOW_MSB    14
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_EDGE_LOW_LSB    14
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_LEVEL_HIGH_BITS   0x00002000
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_LEVEL_HIGH_MSB    13
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_LEVEL_HIGH_LSB    13
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_LEVEL_LOW_BITS   0x00001000
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_LEVEL_LOW_MSB    12
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_LEVEL_LOW_LSB    12
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_EDGE_HIGH_BITS   0x00000800
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_EDGE_HIGH_MSB    11
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_EDGE_HIGH_LSB    11
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_EDGE_LOW_BITS   0x00000400
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_EDGE_LOW_MSB    10
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_EDGE_LOW_LSB    10
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_LEVEL_HIGH_BITS   0x00000200
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_LEVEL_HIGH_MSB    9
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_LEVEL_HIGH_LSB    9
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_LEVEL_LOW_BITS   0x00000100
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_LEVEL_LOW_MSB    8
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_LEVEL_LOW_LSB    8
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_EDGE_HIGH_BITS   0x00000080
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_EDGE_HIGH_MSB    7
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_EDGE_HIGH_LSB    7
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_EDGE_LOW_BITS   0x00000040
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_EDGE_LOW_MSB    6
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_EDGE_LOW_LSB    6
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_LEVEL_HIGH_BITS   0x00000020
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_LEVEL_HIGH_MSB    5
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_LEVEL_HIGH_LSB    5
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_LEVEL_LOW_BITS   0x00000010
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_LEVEL_LOW_MSB    4
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_LEVEL_LOW_LSB    4
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_EDGE_HIGH_BITS   0x00000008
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_EDGE_HIGH_MSB    3
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_EDGE_HIGH_LSB    3
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_EDGE_LOW_BITS   0x00000004
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_EDGE_LOW_MSB    2
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_EDGE_LOW_LSB    2
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH_BITS   0x00000002
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH_MSB    1
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH_LSB    1
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_LEVEL_LOW_BITS   0x00000001
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_LEVEL_LOW_MSB    0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_LEVEL_LOW_LSB    0
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_LEVEL_LOW_ACCESS "RW"
// =============================================================================
// Register    : IO_QSPI_PROC1_INTS
// Description : Interrupt status after masking & forcing for proc1
#define IO_QSPI_PROC1_INTS_OFFSET 0x00000048
#define IO_QSPI_PROC1_INTS_BITS   0x00ffffff
#define IO_QSPI_PROC1_INTS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_EDGE_HIGH_BITS   0x00800000
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_EDGE_HIGH_MSB    23
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_EDGE_HIGH_LSB    23
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_EDGE_LOW_BITS   0x00400000
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_EDGE_LOW_MSB    22
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_EDGE_LOW_LSB    22
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_LEVEL_HIGH_BITS   0x00200000
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_LEVEL_HIGH_MSB    21
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_LEVEL_HIGH_LSB    21
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_LEVEL_LOW_BITS   0x00100000
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_LEVEL_LOW_MSB    20
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_LEVEL_LOW_LSB    20
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_EDGE_HIGH_BITS   0x00080000
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_EDGE_HIGH_MSB    19
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_EDGE_HIGH_LSB    19
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_EDGE_LOW_BITS   0x00040000
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_EDGE_LOW_MSB    18
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_EDGE_LOW_LSB    18
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_LEVEL_HIGH_BITS   0x00020000
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_LEVEL_HIGH_MSB    17
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_LEVEL_HIGH_LSB    17
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_LEVEL_LOW_BITS   0x00010000
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_LEVEL_LOW_MSB    16
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_LEVEL_LOW_LSB    16
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_EDGE_HIGH_BITS   0x00008000
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_EDGE_HIGH_MSB    15
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_EDGE_HIGH_LSB    15
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_EDGE_LOW_BITS   0x00004000
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_EDGE_LOW_MSB    14
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_EDGE_LOW_LSB    14
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_LEVEL_HIGH_BITS   0x00002000
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_LEVEL_HIGH_MSB    13
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_LEVEL_HIGH_LSB    13
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_LEVEL_LOW_BITS   0x00001000
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_LEVEL_LOW_MSB    12
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_LEVEL_LOW_LSB    12
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_EDGE_HIGH_BITS   0x00000800
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_EDGE_HIGH_MSB    11
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_EDGE_HIGH_LSB    11
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_EDGE_LOW_BITS   0x00000400
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_EDGE_LOW_MSB    10
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_EDGE_LOW_LSB    10
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_LEVEL_HIGH_BITS   0x00000200
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_LEVEL_HIGH_MSB    9
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_LEVEL_HIGH_LSB    9
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_LEVEL_LOW_BITS   0x00000100
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_LEVEL_LOW_MSB    8
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_LEVEL_LOW_LSB    8
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_EDGE_HIGH_BITS   0x00000080
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_EDGE_HIGH_MSB    7
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_EDGE_HIGH_LSB    7
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_EDGE_LOW_BITS   0x00000040
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_EDGE_LOW_MSB    6
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_EDGE_LOW_LSB    6
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_LEVEL_HIGH_BITS   0x00000020
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_LEVEL_HIGH_MSB    5
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_LEVEL_HIGH_LSB    5
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_LEVEL_LOW_BITS   0x00000010
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_LEVEL_LOW_MSB    4
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_LEVEL_LOW_LSB    4
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_EDGE_HIGH
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_EDGE_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_EDGE_HIGH_BITS   0x00000008
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_EDGE_HIGH_MSB    3
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_EDGE_HIGH_LSB    3
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_EDGE_LOW
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_EDGE_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_EDGE_LOW_BITS   0x00000004
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_EDGE_LOW_MSB    2
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_EDGE_LOW_LSB    2
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH_BITS   0x00000002
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH_MSB    1
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH_LSB    1
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_LEVEL_LOW
// Description : None
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_LEVEL_LOW_RESET  0x0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_LEVEL_LOW_BITS   0x00000001
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_LEVEL_LOW_MSB    0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_LEVEL_LOW_LSB    0
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_LEVEL_LOW_ACCESS "RO"
// =============================================================================
// Register    : IO_QSPI_DORMANT_WAKE_INTE
// Description : Interrupt Enable for dormant_wake
#define IO_QSPI_DORMANT_WAKE_INTE_OFFSET 0x0000004c
#define IO_QSPI_DORMANT_WAKE_INTE_BITS   0x00ffffff
#define IO_QSPI_DORMANT_WAKE_INTE_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_EDGE_HIGH_BITS   0x00800000
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_EDGE_HIGH_MSB    23
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_EDGE_HIGH_LSB    23
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_EDGE_LOW_BITS   0x00400000
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_EDGE_LOW_MSB    22
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_EDGE_LOW_LSB    22
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_LEVEL_HIGH_BITS   0x00200000
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_LEVEL_HIGH_MSB    21
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_LEVEL_HIGH_LSB    21
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_LEVEL_LOW_BITS   0x00100000
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_LEVEL_LOW_MSB    20
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_LEVEL_LOW_LSB    20
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_EDGE_HIGH_BITS   0x00080000
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_EDGE_HIGH_MSB    19
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_EDGE_HIGH_LSB    19
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_EDGE_LOW_BITS   0x00040000
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_EDGE_LOW_MSB    18
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_EDGE_LOW_LSB    18
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_LEVEL_HIGH_BITS   0x00020000
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_LEVEL_HIGH_MSB    17
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_LEVEL_HIGH_LSB    17
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_LEVEL_LOW_BITS   0x00010000
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_LEVEL_LOW_MSB    16
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_LEVEL_LOW_LSB    16
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_EDGE_HIGH_BITS   0x00008000
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_EDGE_HIGH_MSB    15
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_EDGE_HIGH_LSB    15
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_EDGE_LOW_BITS   0x00004000
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_EDGE_LOW_MSB    14
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_EDGE_LOW_LSB    14
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_LEVEL_HIGH_BITS   0x00002000
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_LEVEL_HIGH_MSB    13
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_LEVEL_HIGH_LSB    13
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_LEVEL_LOW_BITS   0x00001000
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_LEVEL_LOW_MSB    12
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_LEVEL_LOW_LSB    12
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_EDGE_HIGH_BITS   0x00000800
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_EDGE_HIGH_MSB    11
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_EDGE_HIGH_LSB    11
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_EDGE_LOW_BITS   0x00000400
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_EDGE_LOW_MSB    10
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_EDGE_LOW_LSB    10
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_LEVEL_HIGH_BITS   0x00000200
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_LEVEL_HIGH_MSB    9
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_LEVEL_HIGH_LSB    9
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_LEVEL_LOW_BITS   0x00000100
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_LEVEL_LOW_MSB    8
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_LEVEL_LOW_LSB    8
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_EDGE_HIGH_BITS   0x00000080
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_EDGE_HIGH_MSB    7
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_EDGE_HIGH_LSB    7
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_EDGE_LOW_BITS   0x00000040
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_EDGE_LOW_MSB    6
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_EDGE_LOW_LSB    6
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_LEVEL_HIGH_BITS   0x00000020
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_LEVEL_HIGH_MSB    5
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_LEVEL_HIGH_LSB    5
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_LEVEL_LOW_BITS   0x00000010
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_LEVEL_LOW_MSB    4
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_LEVEL_LOW_LSB    4
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_EDGE_HIGH_BITS   0x00000008
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_EDGE_HIGH_MSB    3
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_EDGE_HIGH_LSB    3
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_EDGE_LOW_BITS   0x00000004
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_EDGE_LOW_MSB    2
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_EDGE_LOW_LSB    2
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH_BITS   0x00000002
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH_MSB    1
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH_LSB    1
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_LEVEL_LOW_BITS   0x00000001
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_LEVEL_LOW_MSB    0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_LEVEL_LOW_LSB    0
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_LEVEL_LOW_ACCESS "RW"
// =============================================================================
// Register    : IO_QSPI_DORMANT_WAKE_INTF
// Description : Interrupt Force for dormant_wake
#define IO_QSPI_DORMANT_WAKE_INTF_OFFSET 0x00000050
#define IO_QSPI_DORMANT_WAKE_INTF_BITS   0x00ffffff
#define IO_QSPI_DORMANT_WAKE_INTF_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_EDGE_HIGH_BITS   0x00800000
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_EDGE_HIGH_MSB    23
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_EDGE_HIGH_LSB    23
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_EDGE_LOW_BITS   0x00400000
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_EDGE_LOW_MSB    22
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_EDGE_LOW_LSB    22
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_LEVEL_HIGH_BITS   0x00200000
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_LEVEL_HIGH_MSB    21
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_LEVEL_HIGH_LSB    21
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_LEVEL_LOW_BITS   0x00100000
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_LEVEL_LOW_MSB    20
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_LEVEL_LOW_LSB    20
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_EDGE_HIGH_BITS   0x00080000
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_EDGE_HIGH_MSB    19
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_EDGE_HIGH_LSB    19
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_EDGE_LOW_BITS   0x00040000
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_EDGE_LOW_MSB    18
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_EDGE_LOW_LSB    18
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_LEVEL_HIGH_BITS   0x00020000
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_LEVEL_HIGH_MSB    17
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_LEVEL_HIGH_LSB    17
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_LEVEL_LOW_BITS   0x00010000
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_LEVEL_LOW_MSB    16
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_LEVEL_LOW_LSB    16
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_EDGE_HIGH_BITS   0x00008000
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_EDGE_HIGH_MSB    15
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_EDGE_HIGH_LSB    15
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_EDGE_LOW_BITS   0x00004000
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_EDGE_LOW_MSB    14
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_EDGE_LOW_LSB    14
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_LEVEL_HIGH_BITS   0x00002000
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_LEVEL_HIGH_MSB    13
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_LEVEL_HIGH_LSB    13
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_LEVEL_LOW_BITS   0x00001000
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_LEVEL_LOW_MSB    12
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_LEVEL_LOW_LSB    12
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_EDGE_HIGH_BITS   0x00000800
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_EDGE_HIGH_MSB    11
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_EDGE_HIGH_LSB    11
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_EDGE_LOW_BITS   0x00000400
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_EDGE_LOW_MSB    10
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_EDGE_LOW_LSB    10
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_LEVEL_HIGH_BITS   0x00000200
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_LEVEL_HIGH_MSB    9
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_LEVEL_HIGH_LSB    9
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_LEVEL_LOW_BITS   0x00000100
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_LEVEL_LOW_MSB    8
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_LEVEL_LOW_LSB    8
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_EDGE_HIGH_BITS   0x00000080
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_EDGE_HIGH_MSB    7
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_EDGE_HIGH_LSB    7
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_EDGE_LOW_BITS   0x00000040
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_EDGE_LOW_MSB    6
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_EDGE_LOW_LSB    6
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_LEVEL_HIGH_BITS   0x00000020
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_LEVEL_HIGH_MSB    5
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_LEVEL_HIGH_LSB    5
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_LEVEL_LOW_BITS   0x00000010
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_LEVEL_LOW_MSB    4
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_LEVEL_LOW_LSB    4
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_LEVEL_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_EDGE_HIGH_BITS   0x00000008
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_EDGE_HIGH_MSB    3
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_EDGE_HIGH_LSB    3
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_EDGE_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_EDGE_LOW_BITS   0x00000004
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_EDGE_LOW_MSB    2
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_EDGE_LOW_LSB    2
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_EDGE_LOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH_BITS   0x00000002
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH_MSB    1
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH_LSB    1
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_LEVEL_LOW_BITS   0x00000001
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_LEVEL_LOW_MSB    0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_LEVEL_LOW_LSB    0
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_LEVEL_LOW_ACCESS "RW"
// =============================================================================
// Register    : IO_QSPI_DORMANT_WAKE_INTS
// Description : Interrupt status after masking & forcing for dormant_wake
#define IO_QSPI_DORMANT_WAKE_INTS_OFFSET 0x00000054
#define IO_QSPI_DORMANT_WAKE_INTS_BITS   0x00ffffff
#define IO_QSPI_DORMANT_WAKE_INTS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_EDGE_HIGH_BITS   0x00800000
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_EDGE_HIGH_MSB    23
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_EDGE_HIGH_LSB    23
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_EDGE_LOW_BITS   0x00400000
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_EDGE_LOW_MSB    22
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_EDGE_LOW_LSB    22
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_LEVEL_HIGH_BITS   0x00200000
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_LEVEL_HIGH_MSB    21
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_LEVEL_HIGH_LSB    21
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_LEVEL_LOW_BITS   0x00100000
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_LEVEL_LOW_MSB    20
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_LEVEL_LOW_LSB    20
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_EDGE_HIGH_BITS   0x00080000
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_EDGE_HIGH_MSB    19
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_EDGE_HIGH_LSB    19
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_EDGE_LOW_BITS   0x00040000
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_EDGE_LOW_MSB    18
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_EDGE_LOW_LSB    18
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_LEVEL_HIGH_BITS   0x00020000
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_LEVEL_HIGH_MSB    17
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_LEVEL_HIGH_LSB    17
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_LEVEL_LOW_BITS   0x00010000
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_LEVEL_LOW_MSB    16
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_LEVEL_LOW_LSB    16
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_EDGE_HIGH_BITS   0x00008000
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_EDGE_HIGH_MSB    15
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_EDGE_HIGH_LSB    15
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_EDGE_LOW_BITS   0x00004000
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_EDGE_LOW_MSB    14
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_EDGE_LOW_LSB    14
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_LEVEL_HIGH_BITS   0x00002000
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_LEVEL_HIGH_MSB    13
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_LEVEL_HIGH_LSB    13
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_LEVEL_LOW_BITS   0x00001000
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_LEVEL_LOW_MSB    12
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_LEVEL_LOW_LSB    12
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_EDGE_HIGH_BITS   0x00000800
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_EDGE_HIGH_MSB    11
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_EDGE_HIGH_LSB    11
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_EDGE_LOW_BITS   0x00000400
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_EDGE_LOW_MSB    10
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_EDGE_LOW_LSB    10
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_LEVEL_HIGH_BITS   0x00000200
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_LEVEL_HIGH_MSB    9
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_LEVEL_HIGH_LSB    9
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_LEVEL_LOW_BITS   0x00000100
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_LEVEL_LOW_MSB    8
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_LEVEL_LOW_LSB    8
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_EDGE_HIGH_BITS   0x00000080
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_EDGE_HIGH_MSB    7
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_EDGE_HIGH_LSB    7
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_EDGE_LOW_BITS   0x00000040
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_EDGE_LOW_MSB    6
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_EDGE_LOW_LSB    6
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_LEVEL_HIGH_BITS   0x00000020
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_LEVEL_HIGH_MSB    5
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_LEVEL_HIGH_LSB    5
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_LEVEL_LOW_BITS   0x00000010
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_LEVEL_LOW_MSB    4
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_LEVEL_LOW_LSB    4
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_LEVEL_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_EDGE_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_EDGE_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_EDGE_HIGH_BITS   0x00000008
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_EDGE_HIGH_MSB    3
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_EDGE_HIGH_LSB    3
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_EDGE_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_EDGE_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_EDGE_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_EDGE_LOW_BITS   0x00000004
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_EDGE_LOW_MSB    2
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_EDGE_LOW_LSB    2
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_EDGE_LOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH_BITS   0x00000002
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH_MSB    1
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH_LSB    1
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_LEVEL_LOW
// Description : None
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_LEVEL_LOW_RESET  0x0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_LEVEL_LOW_BITS   0x00000001
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_LEVEL_LOW_MSB    0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_LEVEL_LOW_LSB    0
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_LEVEL_LOW_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_IO_QSPI_DEFINED
