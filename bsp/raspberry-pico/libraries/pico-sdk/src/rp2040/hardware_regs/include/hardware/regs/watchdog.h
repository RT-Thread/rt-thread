/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : WATCHDOG
// Version        : 1
// Bus type       : apb
// Description    : None
// =============================================================================
#ifndef HARDWARE_REGS_WATCHDOG_DEFINED
#define HARDWARE_REGS_WATCHDOG_DEFINED
// =============================================================================
// Register    : WATCHDOG_CTRL
// Description : Watchdog control
//               The rst_wdsel register determines which subsystems are reset
//               when the watchdog is triggered.
//               The watchdog can be triggered in software.
#define WATCHDOG_CTRL_OFFSET 0x00000000
#define WATCHDOG_CTRL_BITS   0xc7ffffff
#define WATCHDOG_CTRL_RESET  0x07000000
// -----------------------------------------------------------------------------
// Field       : WATCHDOG_CTRL_TRIGGER
// Description : Trigger a watchdog reset
#define WATCHDOG_CTRL_TRIGGER_RESET  0x0
#define WATCHDOG_CTRL_TRIGGER_BITS   0x80000000
#define WATCHDOG_CTRL_TRIGGER_MSB    31
#define WATCHDOG_CTRL_TRIGGER_LSB    31
#define WATCHDOG_CTRL_TRIGGER_ACCESS "SC"
// -----------------------------------------------------------------------------
// Field       : WATCHDOG_CTRL_ENABLE
// Description : When not enabled the watchdog timer is paused
#define WATCHDOG_CTRL_ENABLE_RESET  0x0
#define WATCHDOG_CTRL_ENABLE_BITS   0x40000000
#define WATCHDOG_CTRL_ENABLE_MSB    30
#define WATCHDOG_CTRL_ENABLE_LSB    30
#define WATCHDOG_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : WATCHDOG_CTRL_PAUSE_DBG1
// Description : Pause the watchdog timer when processor 1 is in debug mode
#define WATCHDOG_CTRL_PAUSE_DBG1_RESET  0x1
#define WATCHDOG_CTRL_PAUSE_DBG1_BITS   0x04000000
#define WATCHDOG_CTRL_PAUSE_DBG1_MSB    26
#define WATCHDOG_CTRL_PAUSE_DBG1_LSB    26
#define WATCHDOG_CTRL_PAUSE_DBG1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : WATCHDOG_CTRL_PAUSE_DBG0
// Description : Pause the watchdog timer when processor 0 is in debug mode
#define WATCHDOG_CTRL_PAUSE_DBG0_RESET  0x1
#define WATCHDOG_CTRL_PAUSE_DBG0_BITS   0x02000000
#define WATCHDOG_CTRL_PAUSE_DBG0_MSB    25
#define WATCHDOG_CTRL_PAUSE_DBG0_LSB    25
#define WATCHDOG_CTRL_PAUSE_DBG0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : WATCHDOG_CTRL_PAUSE_JTAG
// Description : Pause the watchdog timer when JTAG is accessing the bus fabric
#define WATCHDOG_CTRL_PAUSE_JTAG_RESET  0x1
#define WATCHDOG_CTRL_PAUSE_JTAG_BITS   0x01000000
#define WATCHDOG_CTRL_PAUSE_JTAG_MSB    24
#define WATCHDOG_CTRL_PAUSE_JTAG_LSB    24
#define WATCHDOG_CTRL_PAUSE_JTAG_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : WATCHDOG_CTRL_TIME
// Description : Indicates the number of ticks / 2 (see errata RP2040-E1) before
//               a watchdog reset will be triggered
#define WATCHDOG_CTRL_TIME_RESET  0x000000
#define WATCHDOG_CTRL_TIME_BITS   0x00ffffff
#define WATCHDOG_CTRL_TIME_MSB    23
#define WATCHDOG_CTRL_TIME_LSB    0
#define WATCHDOG_CTRL_TIME_ACCESS "RO"
// =============================================================================
// Register    : WATCHDOG_LOAD
// Description : Load the watchdog timer. The maximum setting is 0xffffff which
//               corresponds to 0xffffff / 2 ticks before triggering a watchdog
//               reset (see errata RP2040-E1).
#define WATCHDOG_LOAD_OFFSET 0x00000004
#define WATCHDOG_LOAD_BITS   0x00ffffff
#define WATCHDOG_LOAD_RESET  0x00000000
#define WATCHDOG_LOAD_MSB    23
#define WATCHDOG_LOAD_LSB    0
#define WATCHDOG_LOAD_ACCESS "WF"
// =============================================================================
// Register    : WATCHDOG_REASON
// Description : Logs the reason for the last reset. Both bits are zero for the
//               case of a hardware reset.
#define WATCHDOG_REASON_OFFSET 0x00000008
#define WATCHDOG_REASON_BITS   0x00000003
#define WATCHDOG_REASON_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : WATCHDOG_REASON_FORCE
// Description : None
#define WATCHDOG_REASON_FORCE_RESET  0x0
#define WATCHDOG_REASON_FORCE_BITS   0x00000002
#define WATCHDOG_REASON_FORCE_MSB    1
#define WATCHDOG_REASON_FORCE_LSB    1
#define WATCHDOG_REASON_FORCE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : WATCHDOG_REASON_TIMER
// Description : None
#define WATCHDOG_REASON_TIMER_RESET  0x0
#define WATCHDOG_REASON_TIMER_BITS   0x00000001
#define WATCHDOG_REASON_TIMER_MSB    0
#define WATCHDOG_REASON_TIMER_LSB    0
#define WATCHDOG_REASON_TIMER_ACCESS "RO"
// =============================================================================
// Register    : WATCHDOG_SCRATCH0
// Description : Scratch register. Information persists through soft reset of
//               the chip.
#define WATCHDOG_SCRATCH0_OFFSET 0x0000000c
#define WATCHDOG_SCRATCH0_BITS   0xffffffff
#define WATCHDOG_SCRATCH0_RESET  0x00000000
#define WATCHDOG_SCRATCH0_MSB    31
#define WATCHDOG_SCRATCH0_LSB    0
#define WATCHDOG_SCRATCH0_ACCESS "RW"
// =============================================================================
// Register    : WATCHDOG_SCRATCH1
// Description : Scratch register. Information persists through soft reset of
//               the chip.
#define WATCHDOG_SCRATCH1_OFFSET 0x00000010
#define WATCHDOG_SCRATCH1_BITS   0xffffffff
#define WATCHDOG_SCRATCH1_RESET  0x00000000
#define WATCHDOG_SCRATCH1_MSB    31
#define WATCHDOG_SCRATCH1_LSB    0
#define WATCHDOG_SCRATCH1_ACCESS "RW"
// =============================================================================
// Register    : WATCHDOG_SCRATCH2
// Description : Scratch register. Information persists through soft reset of
//               the chip.
#define WATCHDOG_SCRATCH2_OFFSET 0x00000014
#define WATCHDOG_SCRATCH2_BITS   0xffffffff
#define WATCHDOG_SCRATCH2_RESET  0x00000000
#define WATCHDOG_SCRATCH2_MSB    31
#define WATCHDOG_SCRATCH2_LSB    0
#define WATCHDOG_SCRATCH2_ACCESS "RW"
// =============================================================================
// Register    : WATCHDOG_SCRATCH3
// Description : Scratch register. Information persists through soft reset of
//               the chip.
#define WATCHDOG_SCRATCH3_OFFSET 0x00000018
#define WATCHDOG_SCRATCH3_BITS   0xffffffff
#define WATCHDOG_SCRATCH3_RESET  0x00000000
#define WATCHDOG_SCRATCH3_MSB    31
#define WATCHDOG_SCRATCH3_LSB    0
#define WATCHDOG_SCRATCH3_ACCESS "RW"
// =============================================================================
// Register    : WATCHDOG_SCRATCH4
// Description : Scratch register. Information persists through soft reset of
//               the chip.
#define WATCHDOG_SCRATCH4_OFFSET 0x0000001c
#define WATCHDOG_SCRATCH4_BITS   0xffffffff
#define WATCHDOG_SCRATCH4_RESET  0x00000000
#define WATCHDOG_SCRATCH4_MSB    31
#define WATCHDOG_SCRATCH4_LSB    0
#define WATCHDOG_SCRATCH4_ACCESS "RW"
// =============================================================================
// Register    : WATCHDOG_SCRATCH5
// Description : Scratch register. Information persists through soft reset of
//               the chip.
#define WATCHDOG_SCRATCH5_OFFSET 0x00000020
#define WATCHDOG_SCRATCH5_BITS   0xffffffff
#define WATCHDOG_SCRATCH5_RESET  0x00000000
#define WATCHDOG_SCRATCH5_MSB    31
#define WATCHDOG_SCRATCH5_LSB    0
#define WATCHDOG_SCRATCH5_ACCESS "RW"
// =============================================================================
// Register    : WATCHDOG_SCRATCH6
// Description : Scratch register. Information persists through soft reset of
//               the chip.
#define WATCHDOG_SCRATCH6_OFFSET 0x00000024
#define WATCHDOG_SCRATCH6_BITS   0xffffffff
#define WATCHDOG_SCRATCH6_RESET  0x00000000
#define WATCHDOG_SCRATCH6_MSB    31
#define WATCHDOG_SCRATCH6_LSB    0
#define WATCHDOG_SCRATCH6_ACCESS "RW"
// =============================================================================
// Register    : WATCHDOG_SCRATCH7
// Description : Scratch register. Information persists through soft reset of
//               the chip.
#define WATCHDOG_SCRATCH7_OFFSET 0x00000028
#define WATCHDOG_SCRATCH7_BITS   0xffffffff
#define WATCHDOG_SCRATCH7_RESET  0x00000000
#define WATCHDOG_SCRATCH7_MSB    31
#define WATCHDOG_SCRATCH7_LSB    0
#define WATCHDOG_SCRATCH7_ACCESS "RW"
// =============================================================================
// Register    : WATCHDOG_TICK
// Description : Controls the tick generator
#define WATCHDOG_TICK_OFFSET 0x0000002c
#define WATCHDOG_TICK_BITS   0x000fffff
#define WATCHDOG_TICK_RESET  0x00000200
// -----------------------------------------------------------------------------
// Field       : WATCHDOG_TICK_COUNT
// Description : Count down timer: the remaining number clk_tick cycles before
//               the next tick is generated.
#define WATCHDOG_TICK_COUNT_RESET  "-"
#define WATCHDOG_TICK_COUNT_BITS   0x000ff800
#define WATCHDOG_TICK_COUNT_MSB    19
#define WATCHDOG_TICK_COUNT_LSB    11
#define WATCHDOG_TICK_COUNT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : WATCHDOG_TICK_RUNNING
// Description : Is the tick generator running?
#define WATCHDOG_TICK_RUNNING_RESET  "-"
#define WATCHDOG_TICK_RUNNING_BITS   0x00000400
#define WATCHDOG_TICK_RUNNING_MSB    10
#define WATCHDOG_TICK_RUNNING_LSB    10
#define WATCHDOG_TICK_RUNNING_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : WATCHDOG_TICK_ENABLE
// Description : start / stop tick generation
#define WATCHDOG_TICK_ENABLE_RESET  0x1
#define WATCHDOG_TICK_ENABLE_BITS   0x00000200
#define WATCHDOG_TICK_ENABLE_MSB    9
#define WATCHDOG_TICK_ENABLE_LSB    9
#define WATCHDOG_TICK_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : WATCHDOG_TICK_CYCLES
// Description : Total number of clk_tick cycles before the next tick.
#define WATCHDOG_TICK_CYCLES_RESET  0x000
#define WATCHDOG_TICK_CYCLES_BITS   0x000001ff
#define WATCHDOG_TICK_CYCLES_MSB    8
#define WATCHDOG_TICK_CYCLES_LSB    0
#define WATCHDOG_TICK_CYCLES_ACCESS "RW"
// =============================================================================
#endif // HARDWARE_REGS_WATCHDOG_DEFINED
