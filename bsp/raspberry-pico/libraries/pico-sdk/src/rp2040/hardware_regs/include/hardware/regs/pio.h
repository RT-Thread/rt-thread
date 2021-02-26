/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : PIO
// Version        : 1
// Bus type       : ahbl
// Description    : Programmable IO block
// =============================================================================
#ifndef HARDWARE_REGS_PIO_DEFINED
#define HARDWARE_REGS_PIO_DEFINED
// =============================================================================
// Register    : PIO_CTRL
// Description : PIO control register
#define PIO_CTRL_OFFSET 0x00000000
#define PIO_CTRL_BITS   0x00000fff
#define PIO_CTRL_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : PIO_CTRL_CLKDIV_RESTART
// Description : Force clock dividers to restart their count and clear
//               fractional
//               accumulators. Restart multiple dividers to synchronise them.
#define PIO_CTRL_CLKDIV_RESTART_RESET  0x0
#define PIO_CTRL_CLKDIV_RESTART_BITS   0x00000f00
#define PIO_CTRL_CLKDIV_RESTART_MSB    11
#define PIO_CTRL_CLKDIV_RESTART_LSB    8
#define PIO_CTRL_CLKDIV_RESTART_ACCESS "SC"
// -----------------------------------------------------------------------------
// Field       : PIO_CTRL_SM_RESTART
// Description : Clear internal SM state which is otherwise difficult to access
//               (e.g. shift counters). Self-clearing.
#define PIO_CTRL_SM_RESTART_RESET  0x0
#define PIO_CTRL_SM_RESTART_BITS   0x000000f0
#define PIO_CTRL_SM_RESTART_MSB    7
#define PIO_CTRL_SM_RESTART_LSB    4
#define PIO_CTRL_SM_RESTART_ACCESS "SC"
// -----------------------------------------------------------------------------
// Field       : PIO_CTRL_SM_ENABLE
// Description : Enable state machine
#define PIO_CTRL_SM_ENABLE_RESET  0x0
#define PIO_CTRL_SM_ENABLE_BITS   0x0000000f
#define PIO_CTRL_SM_ENABLE_MSB    3
#define PIO_CTRL_SM_ENABLE_LSB    0
#define PIO_CTRL_SM_ENABLE_ACCESS "RW"
// =============================================================================
// Register    : PIO_FSTAT
// Description : FIFO status register
#define PIO_FSTAT_OFFSET 0x00000004
#define PIO_FSTAT_BITS   0x0f0f0f0f
#define PIO_FSTAT_RESET  0x0f000f00
// -----------------------------------------------------------------------------
// Field       : PIO_FSTAT_TXEMPTY
// Description : State machine TX FIFO is empty
#define PIO_FSTAT_TXEMPTY_RESET  0xf
#define PIO_FSTAT_TXEMPTY_BITS   0x0f000000
#define PIO_FSTAT_TXEMPTY_MSB    27
#define PIO_FSTAT_TXEMPTY_LSB    24
#define PIO_FSTAT_TXEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FSTAT_TXFULL
// Description : State machine TX FIFO is full
#define PIO_FSTAT_TXFULL_RESET  0x0
#define PIO_FSTAT_TXFULL_BITS   0x000f0000
#define PIO_FSTAT_TXFULL_MSB    19
#define PIO_FSTAT_TXFULL_LSB    16
#define PIO_FSTAT_TXFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FSTAT_RXEMPTY
// Description : State machine RX FIFO is empty
#define PIO_FSTAT_RXEMPTY_RESET  0xf
#define PIO_FSTAT_RXEMPTY_BITS   0x00000f00
#define PIO_FSTAT_RXEMPTY_MSB    11
#define PIO_FSTAT_RXEMPTY_LSB    8
#define PIO_FSTAT_RXEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FSTAT_RXFULL
// Description : State machine RX FIFO is full
#define PIO_FSTAT_RXFULL_RESET  0x0
#define PIO_FSTAT_RXFULL_BITS   0x0000000f
#define PIO_FSTAT_RXFULL_MSB    3
#define PIO_FSTAT_RXFULL_LSB    0
#define PIO_FSTAT_RXFULL_ACCESS "RO"
// =============================================================================
// Register    : PIO_FDEBUG
// Description : FIFO debug register
#define PIO_FDEBUG_OFFSET 0x00000008
#define PIO_FDEBUG_BITS   0x0f0f0f0f
#define PIO_FDEBUG_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : PIO_FDEBUG_TXSTALL
// Description : State machine has stalled on empty TX FIFO. Write 1 to clear.
#define PIO_FDEBUG_TXSTALL_RESET  0x0
#define PIO_FDEBUG_TXSTALL_BITS   0x0f000000
#define PIO_FDEBUG_TXSTALL_MSB    27
#define PIO_FDEBUG_TXSTALL_LSB    24
#define PIO_FDEBUG_TXSTALL_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : PIO_FDEBUG_TXOVER
// Description : TX FIFO overflow has occurred. Write 1 to clear.
#define PIO_FDEBUG_TXOVER_RESET  0x0
#define PIO_FDEBUG_TXOVER_BITS   0x000f0000
#define PIO_FDEBUG_TXOVER_MSB    19
#define PIO_FDEBUG_TXOVER_LSB    16
#define PIO_FDEBUG_TXOVER_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : PIO_FDEBUG_RXUNDER
// Description : RX FIFO underflow has occurred. Write 1 to clear.
#define PIO_FDEBUG_RXUNDER_RESET  0x0
#define PIO_FDEBUG_RXUNDER_BITS   0x00000f00
#define PIO_FDEBUG_RXUNDER_MSB    11
#define PIO_FDEBUG_RXUNDER_LSB    8
#define PIO_FDEBUG_RXUNDER_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : PIO_FDEBUG_RXSTALL
// Description : State machine has stalled on full RX FIFO. Write 1 to clear.
#define PIO_FDEBUG_RXSTALL_RESET  0x0
#define PIO_FDEBUG_RXSTALL_BITS   0x0000000f
#define PIO_FDEBUG_RXSTALL_MSB    3
#define PIO_FDEBUG_RXSTALL_LSB    0
#define PIO_FDEBUG_RXSTALL_ACCESS "WC"
// =============================================================================
// Register    : PIO_FLEVEL
// Description : FIFO levels
#define PIO_FLEVEL_OFFSET 0x0000000c
#define PIO_FLEVEL_BITS   0xffffffff
#define PIO_FLEVEL_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_RX3
// Description : None
#define PIO_FLEVEL_RX3_RESET  0x0
#define PIO_FLEVEL_RX3_BITS   0xf0000000
#define PIO_FLEVEL_RX3_MSB    31
#define PIO_FLEVEL_RX3_LSB    28
#define PIO_FLEVEL_RX3_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_TX3
// Description : None
#define PIO_FLEVEL_TX3_RESET  0x0
#define PIO_FLEVEL_TX3_BITS   0x0f000000
#define PIO_FLEVEL_TX3_MSB    27
#define PIO_FLEVEL_TX3_LSB    24
#define PIO_FLEVEL_TX3_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_RX2
// Description : None
#define PIO_FLEVEL_RX2_RESET  0x0
#define PIO_FLEVEL_RX2_BITS   0x00f00000
#define PIO_FLEVEL_RX2_MSB    23
#define PIO_FLEVEL_RX2_LSB    20
#define PIO_FLEVEL_RX2_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_TX2
// Description : None
#define PIO_FLEVEL_TX2_RESET  0x0
#define PIO_FLEVEL_TX2_BITS   0x000f0000
#define PIO_FLEVEL_TX2_MSB    19
#define PIO_FLEVEL_TX2_LSB    16
#define PIO_FLEVEL_TX2_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_RX1
// Description : None
#define PIO_FLEVEL_RX1_RESET  0x0
#define PIO_FLEVEL_RX1_BITS   0x0000f000
#define PIO_FLEVEL_RX1_MSB    15
#define PIO_FLEVEL_RX1_LSB    12
#define PIO_FLEVEL_RX1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_TX1
// Description : None
#define PIO_FLEVEL_TX1_RESET  0x0
#define PIO_FLEVEL_TX1_BITS   0x00000f00
#define PIO_FLEVEL_TX1_MSB    11
#define PIO_FLEVEL_TX1_LSB    8
#define PIO_FLEVEL_TX1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_RX0
// Description : None
#define PIO_FLEVEL_RX0_RESET  0x0
#define PIO_FLEVEL_RX0_BITS   0x000000f0
#define PIO_FLEVEL_RX0_MSB    7
#define PIO_FLEVEL_RX0_LSB    4
#define PIO_FLEVEL_RX0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_TX0
// Description : None
#define PIO_FLEVEL_TX0_RESET  0x0
#define PIO_FLEVEL_TX0_BITS   0x0000000f
#define PIO_FLEVEL_TX0_MSB    3
#define PIO_FLEVEL_TX0_LSB    0
#define PIO_FLEVEL_TX0_ACCESS "RO"
// =============================================================================
// Register    : PIO_TXF0
// Description : Direct write access to the TX FIFO for this state machine. Each
//               write pushes one word to the FIFO.
#define PIO_TXF0_OFFSET 0x00000010
#define PIO_TXF0_BITS   0xffffffff
#define PIO_TXF0_RESET  0x00000000
#define PIO_TXF0_MSB    31
#define PIO_TXF0_LSB    0
#define PIO_TXF0_ACCESS "WF"
// =============================================================================
// Register    : PIO_TXF1
// Description : Direct write access to the TX FIFO for this state machine. Each
//               write pushes one word to the FIFO.
#define PIO_TXF1_OFFSET 0x00000014
#define PIO_TXF1_BITS   0xffffffff
#define PIO_TXF1_RESET  0x00000000
#define PIO_TXF1_MSB    31
#define PIO_TXF1_LSB    0
#define PIO_TXF1_ACCESS "WF"
// =============================================================================
// Register    : PIO_TXF2
// Description : Direct write access to the TX FIFO for this state machine. Each
//               write pushes one word to the FIFO.
#define PIO_TXF2_OFFSET 0x00000018
#define PIO_TXF2_BITS   0xffffffff
#define PIO_TXF2_RESET  0x00000000
#define PIO_TXF2_MSB    31
#define PIO_TXF2_LSB    0
#define PIO_TXF2_ACCESS "WF"
// =============================================================================
// Register    : PIO_TXF3
// Description : Direct write access to the TX FIFO for this state machine. Each
//               write pushes one word to the FIFO.
#define PIO_TXF3_OFFSET 0x0000001c
#define PIO_TXF3_BITS   0xffffffff
#define PIO_TXF3_RESET  0x00000000
#define PIO_TXF3_MSB    31
#define PIO_TXF3_LSB    0
#define PIO_TXF3_ACCESS "WF"
// =============================================================================
// Register    : PIO_RXF0
// Description : Direct read access to the RX FIFO for this state machine. Each
//               read pops one word from the FIFO.
#define PIO_RXF0_OFFSET 0x00000020
#define PIO_RXF0_BITS   0xffffffff
#define PIO_RXF0_RESET  "-"
#define PIO_RXF0_MSB    31
#define PIO_RXF0_LSB    0
#define PIO_RXF0_ACCESS "RF"
// =============================================================================
// Register    : PIO_RXF1
// Description : Direct read access to the RX FIFO for this state machine. Each
//               read pops one word from the FIFO.
#define PIO_RXF1_OFFSET 0x00000024
#define PIO_RXF1_BITS   0xffffffff
#define PIO_RXF1_RESET  "-"
#define PIO_RXF1_MSB    31
#define PIO_RXF1_LSB    0
#define PIO_RXF1_ACCESS "RF"
// =============================================================================
// Register    : PIO_RXF2
// Description : Direct read access to the RX FIFO for this state machine. Each
//               read pops one word from the FIFO.
#define PIO_RXF2_OFFSET 0x00000028
#define PIO_RXF2_BITS   0xffffffff
#define PIO_RXF2_RESET  "-"
#define PIO_RXF2_MSB    31
#define PIO_RXF2_LSB    0
#define PIO_RXF2_ACCESS "RF"
// =============================================================================
// Register    : PIO_RXF3
// Description : Direct read access to the RX FIFO for this state machine. Each
//               read pops one word from the FIFO.
#define PIO_RXF3_OFFSET 0x0000002c
#define PIO_RXF3_BITS   0xffffffff
#define PIO_RXF3_RESET  "-"
#define PIO_RXF3_MSB    31
#define PIO_RXF3_LSB    0
#define PIO_RXF3_ACCESS "RF"
// =============================================================================
// Register    : PIO_IRQ
// Description : Interrupt request register. Write 1 to clear
#define PIO_IRQ_OFFSET 0x00000030
#define PIO_IRQ_BITS   0x000000ff
#define PIO_IRQ_RESET  0x00000000
#define PIO_IRQ_MSB    7
#define PIO_IRQ_LSB    0
#define PIO_IRQ_ACCESS "WC"
// =============================================================================
// Register    : PIO_IRQ_FORCE
// Description : Writing a 1 to each of these bits will forcibly assert the
//               corresponding IRQ.
//               Note this is different to the INTF register: writing here
//               affects PIO internal
//               state. INTF just asserts the processor-facing IRQ signal for
//               testing ISRs,
//               and is not visible to the state machines.
#define PIO_IRQ_FORCE_OFFSET 0x00000034
#define PIO_IRQ_FORCE_BITS   0x000000ff
#define PIO_IRQ_FORCE_RESET  0x00000000
#define PIO_IRQ_FORCE_MSB    7
#define PIO_IRQ_FORCE_LSB    0
#define PIO_IRQ_FORCE_ACCESS "WF"
// =============================================================================
// Register    : PIO_INPUT_SYNC_BYPASS
// Description : There is a 2-flipflop synchronizer on each GPIO input, which
//               protects
//               PIO logic from metastabilities. This increases input delay, and
//               for fast
//               synchronous IO (e.g. SPI) these synchronizers may need to be
//               bypassed.
//               Each bit in this register corresponds to one GPIO.
//               0 -> input is synchronized (default)
//               1 -> synchronizer is bypassed
//               If in doubt, leave this register as all zeroes.
#define PIO_INPUT_SYNC_BYPASS_OFFSET 0x00000038
#define PIO_INPUT_SYNC_BYPASS_BITS   0xffffffff
#define PIO_INPUT_SYNC_BYPASS_RESET  0x00000000
#define PIO_INPUT_SYNC_BYPASS_MSB    31
#define PIO_INPUT_SYNC_BYPASS_LSB    0
#define PIO_INPUT_SYNC_BYPASS_ACCESS "RW"
// =============================================================================
// Register    : PIO_DBG_PADOUT
// Description : Read to sample the pad output values PIO is currently driving
//               to the GPIOs.
#define PIO_DBG_PADOUT_OFFSET 0x0000003c
#define PIO_DBG_PADOUT_BITS   0xffffffff
#define PIO_DBG_PADOUT_RESET  0x00000000
#define PIO_DBG_PADOUT_MSB    31
#define PIO_DBG_PADOUT_LSB    0
#define PIO_DBG_PADOUT_ACCESS "RO"
// =============================================================================
// Register    : PIO_DBG_PADOE
// Description : Read to sample the pad output enables (direction) PIO is
//               currently driving to the GPIOs.
#define PIO_DBG_PADOE_OFFSET 0x00000040
#define PIO_DBG_PADOE_BITS   0xffffffff
#define PIO_DBG_PADOE_RESET  0x00000000
#define PIO_DBG_PADOE_MSB    31
#define PIO_DBG_PADOE_LSB    0
#define PIO_DBG_PADOE_ACCESS "RO"
// =============================================================================
// Register    : PIO_DBG_CFGINFO
// Description : The PIO hardware has some free parameters that may vary between
//               chip products.
//               These should be provided in the chip datasheet, but are also
//               exposed here.
#define PIO_DBG_CFGINFO_OFFSET 0x00000044
#define PIO_DBG_CFGINFO_BITS   0x003f0f3f
#define PIO_DBG_CFGINFO_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : PIO_DBG_CFGINFO_IMEM_SIZE
// Description : The size of the instruction memory, measured in units of one
//               instruction
#define PIO_DBG_CFGINFO_IMEM_SIZE_RESET  "-"
#define PIO_DBG_CFGINFO_IMEM_SIZE_BITS   0x003f0000
#define PIO_DBG_CFGINFO_IMEM_SIZE_MSB    21
#define PIO_DBG_CFGINFO_IMEM_SIZE_LSB    16
#define PIO_DBG_CFGINFO_IMEM_SIZE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_DBG_CFGINFO_SM_COUNT
// Description : The number of state machines this PIO instance is equipped
//               with.
#define PIO_DBG_CFGINFO_SM_COUNT_RESET  "-"
#define PIO_DBG_CFGINFO_SM_COUNT_BITS   0x00000f00
#define PIO_DBG_CFGINFO_SM_COUNT_MSB    11
#define PIO_DBG_CFGINFO_SM_COUNT_LSB    8
#define PIO_DBG_CFGINFO_SM_COUNT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_DBG_CFGINFO_FIFO_DEPTH
// Description : The depth of the state machine TX/RX FIFOs, measured in words.
//               Joining fifos via SHIFTCTRL_FJOIN gives one FIFO with double
//               this depth.
#define PIO_DBG_CFGINFO_FIFO_DEPTH_RESET  "-"
#define PIO_DBG_CFGINFO_FIFO_DEPTH_BITS   0x0000003f
#define PIO_DBG_CFGINFO_FIFO_DEPTH_MSB    5
#define PIO_DBG_CFGINFO_FIFO_DEPTH_LSB    0
#define PIO_DBG_CFGINFO_FIFO_DEPTH_ACCESS "RO"
// =============================================================================
// Register    : PIO_INSTR_MEM0
// Description : Write-only access to instruction memory location 0
#define PIO_INSTR_MEM0_OFFSET 0x00000048
#define PIO_INSTR_MEM0_BITS   0x0000ffff
#define PIO_INSTR_MEM0_RESET  0x00000000
#define PIO_INSTR_MEM0_MSB    15
#define PIO_INSTR_MEM0_LSB    0
#define PIO_INSTR_MEM0_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM1
// Description : Write-only access to instruction memory location 1
#define PIO_INSTR_MEM1_OFFSET 0x0000004c
#define PIO_INSTR_MEM1_BITS   0x0000ffff
#define PIO_INSTR_MEM1_RESET  0x00000000
#define PIO_INSTR_MEM1_MSB    15
#define PIO_INSTR_MEM1_LSB    0
#define PIO_INSTR_MEM1_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM2
// Description : Write-only access to instruction memory location 2
#define PIO_INSTR_MEM2_OFFSET 0x00000050
#define PIO_INSTR_MEM2_BITS   0x0000ffff
#define PIO_INSTR_MEM2_RESET  0x00000000
#define PIO_INSTR_MEM2_MSB    15
#define PIO_INSTR_MEM2_LSB    0
#define PIO_INSTR_MEM2_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM3
// Description : Write-only access to instruction memory location 3
#define PIO_INSTR_MEM3_OFFSET 0x00000054
#define PIO_INSTR_MEM3_BITS   0x0000ffff
#define PIO_INSTR_MEM3_RESET  0x00000000
#define PIO_INSTR_MEM3_MSB    15
#define PIO_INSTR_MEM3_LSB    0
#define PIO_INSTR_MEM3_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM4
// Description : Write-only access to instruction memory location 4
#define PIO_INSTR_MEM4_OFFSET 0x00000058
#define PIO_INSTR_MEM4_BITS   0x0000ffff
#define PIO_INSTR_MEM4_RESET  0x00000000
#define PIO_INSTR_MEM4_MSB    15
#define PIO_INSTR_MEM4_LSB    0
#define PIO_INSTR_MEM4_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM5
// Description : Write-only access to instruction memory location 5
#define PIO_INSTR_MEM5_OFFSET 0x0000005c
#define PIO_INSTR_MEM5_BITS   0x0000ffff
#define PIO_INSTR_MEM5_RESET  0x00000000
#define PIO_INSTR_MEM5_MSB    15
#define PIO_INSTR_MEM5_LSB    0
#define PIO_INSTR_MEM5_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM6
// Description : Write-only access to instruction memory location 6
#define PIO_INSTR_MEM6_OFFSET 0x00000060
#define PIO_INSTR_MEM6_BITS   0x0000ffff
#define PIO_INSTR_MEM6_RESET  0x00000000
#define PIO_INSTR_MEM6_MSB    15
#define PIO_INSTR_MEM6_LSB    0
#define PIO_INSTR_MEM6_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM7
// Description : Write-only access to instruction memory location 7
#define PIO_INSTR_MEM7_OFFSET 0x00000064
#define PIO_INSTR_MEM7_BITS   0x0000ffff
#define PIO_INSTR_MEM7_RESET  0x00000000
#define PIO_INSTR_MEM7_MSB    15
#define PIO_INSTR_MEM7_LSB    0
#define PIO_INSTR_MEM7_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM8
// Description : Write-only access to instruction memory location 8
#define PIO_INSTR_MEM8_OFFSET 0x00000068
#define PIO_INSTR_MEM8_BITS   0x0000ffff
#define PIO_INSTR_MEM8_RESET  0x00000000
#define PIO_INSTR_MEM8_MSB    15
#define PIO_INSTR_MEM8_LSB    0
#define PIO_INSTR_MEM8_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM9
// Description : Write-only access to instruction memory location 9
#define PIO_INSTR_MEM9_OFFSET 0x0000006c
#define PIO_INSTR_MEM9_BITS   0x0000ffff
#define PIO_INSTR_MEM9_RESET  0x00000000
#define PIO_INSTR_MEM9_MSB    15
#define PIO_INSTR_MEM9_LSB    0
#define PIO_INSTR_MEM9_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM10
// Description : Write-only access to instruction memory location 10
#define PIO_INSTR_MEM10_OFFSET 0x00000070
#define PIO_INSTR_MEM10_BITS   0x0000ffff
#define PIO_INSTR_MEM10_RESET  0x00000000
#define PIO_INSTR_MEM10_MSB    15
#define PIO_INSTR_MEM10_LSB    0
#define PIO_INSTR_MEM10_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM11
// Description : Write-only access to instruction memory location 11
#define PIO_INSTR_MEM11_OFFSET 0x00000074
#define PIO_INSTR_MEM11_BITS   0x0000ffff
#define PIO_INSTR_MEM11_RESET  0x00000000
#define PIO_INSTR_MEM11_MSB    15
#define PIO_INSTR_MEM11_LSB    0
#define PIO_INSTR_MEM11_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM12
// Description : Write-only access to instruction memory location 12
#define PIO_INSTR_MEM12_OFFSET 0x00000078
#define PIO_INSTR_MEM12_BITS   0x0000ffff
#define PIO_INSTR_MEM12_RESET  0x00000000
#define PIO_INSTR_MEM12_MSB    15
#define PIO_INSTR_MEM12_LSB    0
#define PIO_INSTR_MEM12_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM13
// Description : Write-only access to instruction memory location 13
#define PIO_INSTR_MEM13_OFFSET 0x0000007c
#define PIO_INSTR_MEM13_BITS   0x0000ffff
#define PIO_INSTR_MEM13_RESET  0x00000000
#define PIO_INSTR_MEM13_MSB    15
#define PIO_INSTR_MEM13_LSB    0
#define PIO_INSTR_MEM13_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM14
// Description : Write-only access to instruction memory location 14
#define PIO_INSTR_MEM14_OFFSET 0x00000080
#define PIO_INSTR_MEM14_BITS   0x0000ffff
#define PIO_INSTR_MEM14_RESET  0x00000000
#define PIO_INSTR_MEM14_MSB    15
#define PIO_INSTR_MEM14_LSB    0
#define PIO_INSTR_MEM14_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM15
// Description : Write-only access to instruction memory location 15
#define PIO_INSTR_MEM15_OFFSET 0x00000084
#define PIO_INSTR_MEM15_BITS   0x0000ffff
#define PIO_INSTR_MEM15_RESET  0x00000000
#define PIO_INSTR_MEM15_MSB    15
#define PIO_INSTR_MEM15_LSB    0
#define PIO_INSTR_MEM15_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM16
// Description : Write-only access to instruction memory location 16
#define PIO_INSTR_MEM16_OFFSET 0x00000088
#define PIO_INSTR_MEM16_BITS   0x0000ffff
#define PIO_INSTR_MEM16_RESET  0x00000000
#define PIO_INSTR_MEM16_MSB    15
#define PIO_INSTR_MEM16_LSB    0
#define PIO_INSTR_MEM16_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM17
// Description : Write-only access to instruction memory location 17
#define PIO_INSTR_MEM17_OFFSET 0x0000008c
#define PIO_INSTR_MEM17_BITS   0x0000ffff
#define PIO_INSTR_MEM17_RESET  0x00000000
#define PIO_INSTR_MEM17_MSB    15
#define PIO_INSTR_MEM17_LSB    0
#define PIO_INSTR_MEM17_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM18
// Description : Write-only access to instruction memory location 18
#define PIO_INSTR_MEM18_OFFSET 0x00000090
#define PIO_INSTR_MEM18_BITS   0x0000ffff
#define PIO_INSTR_MEM18_RESET  0x00000000
#define PIO_INSTR_MEM18_MSB    15
#define PIO_INSTR_MEM18_LSB    0
#define PIO_INSTR_MEM18_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM19
// Description : Write-only access to instruction memory location 19
#define PIO_INSTR_MEM19_OFFSET 0x00000094
#define PIO_INSTR_MEM19_BITS   0x0000ffff
#define PIO_INSTR_MEM19_RESET  0x00000000
#define PIO_INSTR_MEM19_MSB    15
#define PIO_INSTR_MEM19_LSB    0
#define PIO_INSTR_MEM19_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM20
// Description : Write-only access to instruction memory location 20
#define PIO_INSTR_MEM20_OFFSET 0x00000098
#define PIO_INSTR_MEM20_BITS   0x0000ffff
#define PIO_INSTR_MEM20_RESET  0x00000000
#define PIO_INSTR_MEM20_MSB    15
#define PIO_INSTR_MEM20_LSB    0
#define PIO_INSTR_MEM20_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM21
// Description : Write-only access to instruction memory location 21
#define PIO_INSTR_MEM21_OFFSET 0x0000009c
#define PIO_INSTR_MEM21_BITS   0x0000ffff
#define PIO_INSTR_MEM21_RESET  0x00000000
#define PIO_INSTR_MEM21_MSB    15
#define PIO_INSTR_MEM21_LSB    0
#define PIO_INSTR_MEM21_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM22
// Description : Write-only access to instruction memory location 22
#define PIO_INSTR_MEM22_OFFSET 0x000000a0
#define PIO_INSTR_MEM22_BITS   0x0000ffff
#define PIO_INSTR_MEM22_RESET  0x00000000
#define PIO_INSTR_MEM22_MSB    15
#define PIO_INSTR_MEM22_LSB    0
#define PIO_INSTR_MEM22_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM23
// Description : Write-only access to instruction memory location 23
#define PIO_INSTR_MEM23_OFFSET 0x000000a4
#define PIO_INSTR_MEM23_BITS   0x0000ffff
#define PIO_INSTR_MEM23_RESET  0x00000000
#define PIO_INSTR_MEM23_MSB    15
#define PIO_INSTR_MEM23_LSB    0
#define PIO_INSTR_MEM23_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM24
// Description : Write-only access to instruction memory location 24
#define PIO_INSTR_MEM24_OFFSET 0x000000a8
#define PIO_INSTR_MEM24_BITS   0x0000ffff
#define PIO_INSTR_MEM24_RESET  0x00000000
#define PIO_INSTR_MEM24_MSB    15
#define PIO_INSTR_MEM24_LSB    0
#define PIO_INSTR_MEM24_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM25
// Description : Write-only access to instruction memory location 25
#define PIO_INSTR_MEM25_OFFSET 0x000000ac
#define PIO_INSTR_MEM25_BITS   0x0000ffff
#define PIO_INSTR_MEM25_RESET  0x00000000
#define PIO_INSTR_MEM25_MSB    15
#define PIO_INSTR_MEM25_LSB    0
#define PIO_INSTR_MEM25_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM26
// Description : Write-only access to instruction memory location 26
#define PIO_INSTR_MEM26_OFFSET 0x000000b0
#define PIO_INSTR_MEM26_BITS   0x0000ffff
#define PIO_INSTR_MEM26_RESET  0x00000000
#define PIO_INSTR_MEM26_MSB    15
#define PIO_INSTR_MEM26_LSB    0
#define PIO_INSTR_MEM26_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM27
// Description : Write-only access to instruction memory location 27
#define PIO_INSTR_MEM27_OFFSET 0x000000b4
#define PIO_INSTR_MEM27_BITS   0x0000ffff
#define PIO_INSTR_MEM27_RESET  0x00000000
#define PIO_INSTR_MEM27_MSB    15
#define PIO_INSTR_MEM27_LSB    0
#define PIO_INSTR_MEM27_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM28
// Description : Write-only access to instruction memory location 28
#define PIO_INSTR_MEM28_OFFSET 0x000000b8
#define PIO_INSTR_MEM28_BITS   0x0000ffff
#define PIO_INSTR_MEM28_RESET  0x00000000
#define PIO_INSTR_MEM28_MSB    15
#define PIO_INSTR_MEM28_LSB    0
#define PIO_INSTR_MEM28_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM29
// Description : Write-only access to instruction memory location 29
#define PIO_INSTR_MEM29_OFFSET 0x000000bc
#define PIO_INSTR_MEM29_BITS   0x0000ffff
#define PIO_INSTR_MEM29_RESET  0x00000000
#define PIO_INSTR_MEM29_MSB    15
#define PIO_INSTR_MEM29_LSB    0
#define PIO_INSTR_MEM29_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM30
// Description : Write-only access to instruction memory location 30
#define PIO_INSTR_MEM30_OFFSET 0x000000c0
#define PIO_INSTR_MEM30_BITS   0x0000ffff
#define PIO_INSTR_MEM30_RESET  0x00000000
#define PIO_INSTR_MEM30_MSB    15
#define PIO_INSTR_MEM30_LSB    0
#define PIO_INSTR_MEM30_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM31
// Description : Write-only access to instruction memory location 31
#define PIO_INSTR_MEM31_OFFSET 0x000000c4
#define PIO_INSTR_MEM31_BITS   0x0000ffff
#define PIO_INSTR_MEM31_RESET  0x00000000
#define PIO_INSTR_MEM31_MSB    15
#define PIO_INSTR_MEM31_LSB    0
#define PIO_INSTR_MEM31_ACCESS "WO"
// =============================================================================
// Register    : PIO_SM0_CLKDIV
// Description : Clock divider register for state machine 0
//               Frequency = clock freq / (CLKDIV_INT + CLKDIV_FRAC / 256)
#define PIO_SM0_CLKDIV_OFFSET 0x000000c8
#define PIO_SM0_CLKDIV_BITS   0xffffff00
#define PIO_SM0_CLKDIV_RESET  0x00010000
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_CLKDIV_INT
// Description : Effective frequency is sysclk/int.
//               Value of 0 is interpreted as max possible value
#define PIO_SM0_CLKDIV_INT_RESET  0x0001
#define PIO_SM0_CLKDIV_INT_BITS   0xffff0000
#define PIO_SM0_CLKDIV_INT_MSB    31
#define PIO_SM0_CLKDIV_INT_LSB    16
#define PIO_SM0_CLKDIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_CLKDIV_FRAC
// Description : Fractional part of clock divider
#define PIO_SM0_CLKDIV_FRAC_RESET  0x00
#define PIO_SM0_CLKDIV_FRAC_BITS   0x0000ff00
#define PIO_SM0_CLKDIV_FRAC_MSB    15
#define PIO_SM0_CLKDIV_FRAC_LSB    8
#define PIO_SM0_CLKDIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM0_EXECCTRL
// Description : Execution/behavioural settings for state machine 0
#define PIO_SM0_EXECCTRL_OFFSET 0x000000cc
#define PIO_SM0_EXECCTRL_BITS   0xffffff9f
#define PIO_SM0_EXECCTRL_RESET  0x0001f000
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_EXEC_STALLED
// Description : An instruction written to SMx_INSTR is stalled, and latched by
//               the
//               state machine. Will clear once the instruction completes.
#define PIO_SM0_EXECCTRL_EXEC_STALLED_RESET  0x0
#define PIO_SM0_EXECCTRL_EXEC_STALLED_BITS   0x80000000
#define PIO_SM0_EXECCTRL_EXEC_STALLED_MSB    31
#define PIO_SM0_EXECCTRL_EXEC_STALLED_LSB    31
#define PIO_SM0_EXECCTRL_EXEC_STALLED_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_SIDE_EN
// Description : If 1, the delay MSB is used as side-set enable, rather than a
//               side-set data bit. This allows instructions to perform side-set
//               optionally,
//               rather than on every instruction.
#define PIO_SM0_EXECCTRL_SIDE_EN_RESET  0x0
#define PIO_SM0_EXECCTRL_SIDE_EN_BITS   0x40000000
#define PIO_SM0_EXECCTRL_SIDE_EN_MSB    30
#define PIO_SM0_EXECCTRL_SIDE_EN_LSB    30
#define PIO_SM0_EXECCTRL_SIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_SIDE_PINDIR
// Description : Side-set data is asserted to pin OEs instead of pin values
#define PIO_SM0_EXECCTRL_SIDE_PINDIR_RESET  0x0
#define PIO_SM0_EXECCTRL_SIDE_PINDIR_BITS   0x20000000
#define PIO_SM0_EXECCTRL_SIDE_PINDIR_MSB    29
#define PIO_SM0_EXECCTRL_SIDE_PINDIR_LSB    29
#define PIO_SM0_EXECCTRL_SIDE_PINDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_JMP_PIN
// Description : The GPIO number to use as condition for JMP PIN. Unaffected by
//               input mapping.
#define PIO_SM0_EXECCTRL_JMP_PIN_RESET  0x00
#define PIO_SM0_EXECCTRL_JMP_PIN_BITS   0x1f000000
#define PIO_SM0_EXECCTRL_JMP_PIN_MSB    28
#define PIO_SM0_EXECCTRL_JMP_PIN_LSB    24
#define PIO_SM0_EXECCTRL_JMP_PIN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_OUT_EN_SEL
// Description : Which data bit to use for inline OUT enable
#define PIO_SM0_EXECCTRL_OUT_EN_SEL_RESET  0x00
#define PIO_SM0_EXECCTRL_OUT_EN_SEL_BITS   0x00f80000
#define PIO_SM0_EXECCTRL_OUT_EN_SEL_MSB    23
#define PIO_SM0_EXECCTRL_OUT_EN_SEL_LSB    19
#define PIO_SM0_EXECCTRL_OUT_EN_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_INLINE_OUT_EN
// Description : If 1, use a bit of OUT data as an auxiliary write enable
//               When used in conjunction with OUT_STICKY, writes with an enable
//               of 0 will
//               deassert the latest pin write. This can create useful
//               masking/override behaviour
//               due to the priority ordering of state machine pin writes (SM0 <
//               SM1 < ...)
#define PIO_SM0_EXECCTRL_INLINE_OUT_EN_RESET  0x0
#define PIO_SM0_EXECCTRL_INLINE_OUT_EN_BITS   0x00040000
#define PIO_SM0_EXECCTRL_INLINE_OUT_EN_MSB    18
#define PIO_SM0_EXECCTRL_INLINE_OUT_EN_LSB    18
#define PIO_SM0_EXECCTRL_INLINE_OUT_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_OUT_STICKY
// Description : Continuously assert the most recent OUT/SET to the pins
#define PIO_SM0_EXECCTRL_OUT_STICKY_RESET  0x0
#define PIO_SM0_EXECCTRL_OUT_STICKY_BITS   0x00020000
#define PIO_SM0_EXECCTRL_OUT_STICKY_MSB    17
#define PIO_SM0_EXECCTRL_OUT_STICKY_LSB    17
#define PIO_SM0_EXECCTRL_OUT_STICKY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_WRAP_TOP
// Description : After reaching this address, execution is wrapped to
//               wrap_bottom.
//               If the instruction is a jump, and the jump condition is true,
//               the jump takes priority.
#define PIO_SM0_EXECCTRL_WRAP_TOP_RESET  0x1f
#define PIO_SM0_EXECCTRL_WRAP_TOP_BITS   0x0001f000
#define PIO_SM0_EXECCTRL_WRAP_TOP_MSB    16
#define PIO_SM0_EXECCTRL_WRAP_TOP_LSB    12
#define PIO_SM0_EXECCTRL_WRAP_TOP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_WRAP_BOTTOM
// Description : After reaching wrap_top, execution is wrapped to this address.
#define PIO_SM0_EXECCTRL_WRAP_BOTTOM_RESET  0x00
#define PIO_SM0_EXECCTRL_WRAP_BOTTOM_BITS   0x00000f80
#define PIO_SM0_EXECCTRL_WRAP_BOTTOM_MSB    11
#define PIO_SM0_EXECCTRL_WRAP_BOTTOM_LSB    7
#define PIO_SM0_EXECCTRL_WRAP_BOTTOM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_STATUS_SEL
// Description : Comparison used for the MOV x, STATUS instruction.
//               0x0 -> All-ones if TX FIFO level < N, otherwise all-zeroes
//               0x1 -> All-ones if RX FIFO level < N, otherwise all-zeroes
#define PIO_SM0_EXECCTRL_STATUS_SEL_RESET         0x0
#define PIO_SM0_EXECCTRL_STATUS_SEL_BITS          0x00000010
#define PIO_SM0_EXECCTRL_STATUS_SEL_MSB           4
#define PIO_SM0_EXECCTRL_STATUS_SEL_LSB           4
#define PIO_SM0_EXECCTRL_STATUS_SEL_ACCESS        "RW"
#define PIO_SM0_EXECCTRL_STATUS_SEL_VALUE_TXLEVEL 0x0
#define PIO_SM0_EXECCTRL_STATUS_SEL_VALUE_RXLEVEL 0x1
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_STATUS_N
// Description : Comparison level for the MOV x, STATUS instruction
#define PIO_SM0_EXECCTRL_STATUS_N_RESET  0x0
#define PIO_SM0_EXECCTRL_STATUS_N_BITS   0x0000000f
#define PIO_SM0_EXECCTRL_STATUS_N_MSB    3
#define PIO_SM0_EXECCTRL_STATUS_N_LSB    0
#define PIO_SM0_EXECCTRL_STATUS_N_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM0_SHIFTCTRL
// Description : Control behaviour of the input/output shift registers for state
//               machine 0
#define PIO_SM0_SHIFTCTRL_OFFSET 0x000000d0
#define PIO_SM0_SHIFTCTRL_BITS   0xffff0000
#define PIO_SM0_SHIFTCTRL_RESET  0x000c0000
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_FJOIN_RX
// Description : When 1, RX FIFO steals the TX FIFO's storage, and becomes twice
//               as deep.
//               TX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM0_SHIFTCTRL_FJOIN_RX_RESET  0x0
#define PIO_SM0_SHIFTCTRL_FJOIN_RX_BITS   0x80000000
#define PIO_SM0_SHIFTCTRL_FJOIN_RX_MSB    31
#define PIO_SM0_SHIFTCTRL_FJOIN_RX_LSB    31
#define PIO_SM0_SHIFTCTRL_FJOIN_RX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_FJOIN_TX
// Description : When 1, TX FIFO steals the RX FIFO's storage, and becomes twice
//               as deep.
//               RX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM0_SHIFTCTRL_FJOIN_TX_RESET  0x0
#define PIO_SM0_SHIFTCTRL_FJOIN_TX_BITS   0x40000000
#define PIO_SM0_SHIFTCTRL_FJOIN_TX_MSB    30
#define PIO_SM0_SHIFTCTRL_FJOIN_TX_LSB    30
#define PIO_SM0_SHIFTCTRL_FJOIN_TX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_PULL_THRESH
// Description : Number of bits shifted out of TXSR before autopull or
//               conditional pull.
//               Write 0 for value of 32.
#define PIO_SM0_SHIFTCTRL_PULL_THRESH_RESET  0x00
#define PIO_SM0_SHIFTCTRL_PULL_THRESH_BITS   0x3e000000
#define PIO_SM0_SHIFTCTRL_PULL_THRESH_MSB    29
#define PIO_SM0_SHIFTCTRL_PULL_THRESH_LSB    25
#define PIO_SM0_SHIFTCTRL_PULL_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_PUSH_THRESH
// Description : Number of bits shifted into RXSR before autopush or conditional
//               push.
//               Write 0 for value of 32.
#define PIO_SM0_SHIFTCTRL_PUSH_THRESH_RESET  0x00
#define PIO_SM0_SHIFTCTRL_PUSH_THRESH_BITS   0x01f00000
#define PIO_SM0_SHIFTCTRL_PUSH_THRESH_MSB    24
#define PIO_SM0_SHIFTCTRL_PUSH_THRESH_LSB    20
#define PIO_SM0_SHIFTCTRL_PUSH_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_OUT_SHIFTDIR
// Description : 1 = shift out of output shift register to right. 0 = to left.
#define PIO_SM0_SHIFTCTRL_OUT_SHIFTDIR_RESET  0x1
#define PIO_SM0_SHIFTCTRL_OUT_SHIFTDIR_BITS   0x00080000
#define PIO_SM0_SHIFTCTRL_OUT_SHIFTDIR_MSB    19
#define PIO_SM0_SHIFTCTRL_OUT_SHIFTDIR_LSB    19
#define PIO_SM0_SHIFTCTRL_OUT_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_IN_SHIFTDIR
// Description : 1 = shift input shift register to right (data enters from
//               left). 0 = to left.
#define PIO_SM0_SHIFTCTRL_IN_SHIFTDIR_RESET  0x1
#define PIO_SM0_SHIFTCTRL_IN_SHIFTDIR_BITS   0x00040000
#define PIO_SM0_SHIFTCTRL_IN_SHIFTDIR_MSB    18
#define PIO_SM0_SHIFTCTRL_IN_SHIFTDIR_LSB    18
#define PIO_SM0_SHIFTCTRL_IN_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_AUTOPULL
// Description : Pull automatically when the output shift register is emptied
#define PIO_SM0_SHIFTCTRL_AUTOPULL_RESET  0x0
#define PIO_SM0_SHIFTCTRL_AUTOPULL_BITS   0x00020000
#define PIO_SM0_SHIFTCTRL_AUTOPULL_MSB    17
#define PIO_SM0_SHIFTCTRL_AUTOPULL_LSB    17
#define PIO_SM0_SHIFTCTRL_AUTOPULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_AUTOPUSH
// Description : Push automatically when the input shift register is filled
#define PIO_SM0_SHIFTCTRL_AUTOPUSH_RESET  0x0
#define PIO_SM0_SHIFTCTRL_AUTOPUSH_BITS   0x00010000
#define PIO_SM0_SHIFTCTRL_AUTOPUSH_MSB    16
#define PIO_SM0_SHIFTCTRL_AUTOPUSH_LSB    16
#define PIO_SM0_SHIFTCTRL_AUTOPUSH_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM0_ADDR
// Description : Current instruction address of state machine 0
#define PIO_SM0_ADDR_OFFSET 0x000000d4
#define PIO_SM0_ADDR_BITS   0x0000001f
#define PIO_SM0_ADDR_RESET  0x00000000
#define PIO_SM0_ADDR_MSB    4
#define PIO_SM0_ADDR_LSB    0
#define PIO_SM0_ADDR_ACCESS "RO"
// =============================================================================
// Register    : PIO_SM0_INSTR
// Description : Instruction currently being executed by state machine 0
//               Write to execute an instruction immediately (including jumps)
//               and then resume execution.
#define PIO_SM0_INSTR_OFFSET 0x000000d8
#define PIO_SM0_INSTR_BITS   0x0000ffff
#define PIO_SM0_INSTR_RESET  "-"
#define PIO_SM0_INSTR_MSB    15
#define PIO_SM0_INSTR_LSB    0
#define PIO_SM0_INSTR_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM0_PINCTRL
// Description : State machine pin control
#define PIO_SM0_PINCTRL_OFFSET 0x000000dc
#define PIO_SM0_PINCTRL_BITS   0xffffffff
#define PIO_SM0_PINCTRL_RESET  0x14000000
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_PINCTRL_SIDESET_COUNT
// Description : The number of delay bits co-opted for side-set. Inclusive of
//               the enable bit, if present.
#define PIO_SM0_PINCTRL_SIDESET_COUNT_RESET  0x0
#define PIO_SM0_PINCTRL_SIDESET_COUNT_BITS   0xe0000000
#define PIO_SM0_PINCTRL_SIDESET_COUNT_MSB    31
#define PIO_SM0_PINCTRL_SIDESET_COUNT_LSB    29
#define PIO_SM0_PINCTRL_SIDESET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_PINCTRL_SET_COUNT
// Description : The number of pins asserted by a SET. Max of 5
#define PIO_SM0_PINCTRL_SET_COUNT_RESET  0x5
#define PIO_SM0_PINCTRL_SET_COUNT_BITS   0x1c000000
#define PIO_SM0_PINCTRL_SET_COUNT_MSB    28
#define PIO_SM0_PINCTRL_SET_COUNT_LSB    26
#define PIO_SM0_PINCTRL_SET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_PINCTRL_OUT_COUNT
// Description : The number of pins asserted by an OUT. Value of 0 -> 32 pins
#define PIO_SM0_PINCTRL_OUT_COUNT_RESET  0x00
#define PIO_SM0_PINCTRL_OUT_COUNT_BITS   0x03f00000
#define PIO_SM0_PINCTRL_OUT_COUNT_MSB    25
#define PIO_SM0_PINCTRL_OUT_COUNT_LSB    20
#define PIO_SM0_PINCTRL_OUT_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_PINCTRL_IN_BASE
// Description : The virtual pin corresponding to IN bit 0
#define PIO_SM0_PINCTRL_IN_BASE_RESET  0x00
#define PIO_SM0_PINCTRL_IN_BASE_BITS   0x000f8000
#define PIO_SM0_PINCTRL_IN_BASE_MSB    19
#define PIO_SM0_PINCTRL_IN_BASE_LSB    15
#define PIO_SM0_PINCTRL_IN_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_PINCTRL_SIDESET_BASE
// Description : The virtual pin corresponding to delay field bit 0
#define PIO_SM0_PINCTRL_SIDESET_BASE_RESET  0x00
#define PIO_SM0_PINCTRL_SIDESET_BASE_BITS   0x00007c00
#define PIO_SM0_PINCTRL_SIDESET_BASE_MSB    14
#define PIO_SM0_PINCTRL_SIDESET_BASE_LSB    10
#define PIO_SM0_PINCTRL_SIDESET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_PINCTRL_SET_BASE
// Description : The virtual pin corresponding to SET bit 0
#define PIO_SM0_PINCTRL_SET_BASE_RESET  0x00
#define PIO_SM0_PINCTRL_SET_BASE_BITS   0x000003e0
#define PIO_SM0_PINCTRL_SET_BASE_MSB    9
#define PIO_SM0_PINCTRL_SET_BASE_LSB    5
#define PIO_SM0_PINCTRL_SET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_PINCTRL_OUT_BASE
// Description : The virtual pin corresponding to OUT bit 0
#define PIO_SM0_PINCTRL_OUT_BASE_RESET  0x00
#define PIO_SM0_PINCTRL_OUT_BASE_BITS   0x0000001f
#define PIO_SM0_PINCTRL_OUT_BASE_MSB    4
#define PIO_SM0_PINCTRL_OUT_BASE_LSB    0
#define PIO_SM0_PINCTRL_OUT_BASE_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM1_CLKDIV
// Description : Clock divider register for state machine 1
//               Frequency = clock freq / (CLKDIV_INT + CLKDIV_FRAC / 256)
#define PIO_SM1_CLKDIV_OFFSET 0x000000e0
#define PIO_SM1_CLKDIV_BITS   0xffffff00
#define PIO_SM1_CLKDIV_RESET  0x00010000
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_CLKDIV_INT
// Description : Effective frequency is sysclk/int.
//               Value of 0 is interpreted as max possible value
#define PIO_SM1_CLKDIV_INT_RESET  0x0001
#define PIO_SM1_CLKDIV_INT_BITS   0xffff0000
#define PIO_SM1_CLKDIV_INT_MSB    31
#define PIO_SM1_CLKDIV_INT_LSB    16
#define PIO_SM1_CLKDIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_CLKDIV_FRAC
// Description : Fractional part of clock divider
#define PIO_SM1_CLKDIV_FRAC_RESET  0x00
#define PIO_SM1_CLKDIV_FRAC_BITS   0x0000ff00
#define PIO_SM1_CLKDIV_FRAC_MSB    15
#define PIO_SM1_CLKDIV_FRAC_LSB    8
#define PIO_SM1_CLKDIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM1_EXECCTRL
// Description : Execution/behavioural settings for state machine 1
#define PIO_SM1_EXECCTRL_OFFSET 0x000000e4
#define PIO_SM1_EXECCTRL_BITS   0xffffff9f
#define PIO_SM1_EXECCTRL_RESET  0x0001f000
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_EXEC_STALLED
// Description : An instruction written to SMx_INSTR is stalled, and latched by
//               the
//               state machine. Will clear once the instruction completes.
#define PIO_SM1_EXECCTRL_EXEC_STALLED_RESET  0x0
#define PIO_SM1_EXECCTRL_EXEC_STALLED_BITS   0x80000000
#define PIO_SM1_EXECCTRL_EXEC_STALLED_MSB    31
#define PIO_SM1_EXECCTRL_EXEC_STALLED_LSB    31
#define PIO_SM1_EXECCTRL_EXEC_STALLED_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_SIDE_EN
// Description : If 1, the delay MSB is used as side-set enable, rather than a
//               side-set data bit. This allows instructions to perform side-set
//               optionally,
//               rather than on every instruction.
#define PIO_SM1_EXECCTRL_SIDE_EN_RESET  0x0
#define PIO_SM1_EXECCTRL_SIDE_EN_BITS   0x40000000
#define PIO_SM1_EXECCTRL_SIDE_EN_MSB    30
#define PIO_SM1_EXECCTRL_SIDE_EN_LSB    30
#define PIO_SM1_EXECCTRL_SIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_SIDE_PINDIR
// Description : Side-set data is asserted to pin OEs instead of pin values
#define PIO_SM1_EXECCTRL_SIDE_PINDIR_RESET  0x0
#define PIO_SM1_EXECCTRL_SIDE_PINDIR_BITS   0x20000000
#define PIO_SM1_EXECCTRL_SIDE_PINDIR_MSB    29
#define PIO_SM1_EXECCTRL_SIDE_PINDIR_LSB    29
#define PIO_SM1_EXECCTRL_SIDE_PINDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_JMP_PIN
// Description : The GPIO number to use as condition for JMP PIN. Unaffected by
//               input mapping.
#define PIO_SM1_EXECCTRL_JMP_PIN_RESET  0x00
#define PIO_SM1_EXECCTRL_JMP_PIN_BITS   0x1f000000
#define PIO_SM1_EXECCTRL_JMP_PIN_MSB    28
#define PIO_SM1_EXECCTRL_JMP_PIN_LSB    24
#define PIO_SM1_EXECCTRL_JMP_PIN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_OUT_EN_SEL
// Description : Which data bit to use for inline OUT enable
#define PIO_SM1_EXECCTRL_OUT_EN_SEL_RESET  0x00
#define PIO_SM1_EXECCTRL_OUT_EN_SEL_BITS   0x00f80000
#define PIO_SM1_EXECCTRL_OUT_EN_SEL_MSB    23
#define PIO_SM1_EXECCTRL_OUT_EN_SEL_LSB    19
#define PIO_SM1_EXECCTRL_OUT_EN_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_INLINE_OUT_EN
// Description : If 1, use a bit of OUT data as an auxiliary write enable
//               When used in conjunction with OUT_STICKY, writes with an enable
//               of 0 will
//               deassert the latest pin write. This can create useful
//               masking/override behaviour
//               due to the priority ordering of state machine pin writes (SM0 <
//               SM1 < ...)
#define PIO_SM1_EXECCTRL_INLINE_OUT_EN_RESET  0x0
#define PIO_SM1_EXECCTRL_INLINE_OUT_EN_BITS   0x00040000
#define PIO_SM1_EXECCTRL_INLINE_OUT_EN_MSB    18
#define PIO_SM1_EXECCTRL_INLINE_OUT_EN_LSB    18
#define PIO_SM1_EXECCTRL_INLINE_OUT_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_OUT_STICKY
// Description : Continuously assert the most recent OUT/SET to the pins
#define PIO_SM1_EXECCTRL_OUT_STICKY_RESET  0x0
#define PIO_SM1_EXECCTRL_OUT_STICKY_BITS   0x00020000
#define PIO_SM1_EXECCTRL_OUT_STICKY_MSB    17
#define PIO_SM1_EXECCTRL_OUT_STICKY_LSB    17
#define PIO_SM1_EXECCTRL_OUT_STICKY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_WRAP_TOP
// Description : After reaching this address, execution is wrapped to
//               wrap_bottom.
//               If the instruction is a jump, and the jump condition is true,
//               the jump takes priority.
#define PIO_SM1_EXECCTRL_WRAP_TOP_RESET  0x1f
#define PIO_SM1_EXECCTRL_WRAP_TOP_BITS   0x0001f000
#define PIO_SM1_EXECCTRL_WRAP_TOP_MSB    16
#define PIO_SM1_EXECCTRL_WRAP_TOP_LSB    12
#define PIO_SM1_EXECCTRL_WRAP_TOP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_WRAP_BOTTOM
// Description : After reaching wrap_top, execution is wrapped to this address.
#define PIO_SM1_EXECCTRL_WRAP_BOTTOM_RESET  0x00
#define PIO_SM1_EXECCTRL_WRAP_BOTTOM_BITS   0x00000f80
#define PIO_SM1_EXECCTRL_WRAP_BOTTOM_MSB    11
#define PIO_SM1_EXECCTRL_WRAP_BOTTOM_LSB    7
#define PIO_SM1_EXECCTRL_WRAP_BOTTOM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_STATUS_SEL
// Description : Comparison used for the MOV x, STATUS instruction.
//               0x0 -> All-ones if TX FIFO level < N, otherwise all-zeroes
//               0x1 -> All-ones if RX FIFO level < N, otherwise all-zeroes
#define PIO_SM1_EXECCTRL_STATUS_SEL_RESET         0x0
#define PIO_SM1_EXECCTRL_STATUS_SEL_BITS          0x00000010
#define PIO_SM1_EXECCTRL_STATUS_SEL_MSB           4
#define PIO_SM1_EXECCTRL_STATUS_SEL_LSB           4
#define PIO_SM1_EXECCTRL_STATUS_SEL_ACCESS        "RW"
#define PIO_SM1_EXECCTRL_STATUS_SEL_VALUE_TXLEVEL 0x0
#define PIO_SM1_EXECCTRL_STATUS_SEL_VALUE_RXLEVEL 0x1
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_STATUS_N
// Description : Comparison level for the MOV x, STATUS instruction
#define PIO_SM1_EXECCTRL_STATUS_N_RESET  0x0
#define PIO_SM1_EXECCTRL_STATUS_N_BITS   0x0000000f
#define PIO_SM1_EXECCTRL_STATUS_N_MSB    3
#define PIO_SM1_EXECCTRL_STATUS_N_LSB    0
#define PIO_SM1_EXECCTRL_STATUS_N_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM1_SHIFTCTRL
// Description : Control behaviour of the input/output shift registers for state
//               machine 1
#define PIO_SM1_SHIFTCTRL_OFFSET 0x000000e8
#define PIO_SM1_SHIFTCTRL_BITS   0xffff0000
#define PIO_SM1_SHIFTCTRL_RESET  0x000c0000
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_FJOIN_RX
// Description : When 1, RX FIFO steals the TX FIFO's storage, and becomes twice
//               as deep.
//               TX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM1_SHIFTCTRL_FJOIN_RX_RESET  0x0
#define PIO_SM1_SHIFTCTRL_FJOIN_RX_BITS   0x80000000
#define PIO_SM1_SHIFTCTRL_FJOIN_RX_MSB    31
#define PIO_SM1_SHIFTCTRL_FJOIN_RX_LSB    31
#define PIO_SM1_SHIFTCTRL_FJOIN_RX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_FJOIN_TX
// Description : When 1, TX FIFO steals the RX FIFO's storage, and becomes twice
//               as deep.
//               RX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM1_SHIFTCTRL_FJOIN_TX_RESET  0x0
#define PIO_SM1_SHIFTCTRL_FJOIN_TX_BITS   0x40000000
#define PIO_SM1_SHIFTCTRL_FJOIN_TX_MSB    30
#define PIO_SM1_SHIFTCTRL_FJOIN_TX_LSB    30
#define PIO_SM1_SHIFTCTRL_FJOIN_TX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_PULL_THRESH
// Description : Number of bits shifted out of TXSR before autopull or
//               conditional pull.
//               Write 0 for value of 32.
#define PIO_SM1_SHIFTCTRL_PULL_THRESH_RESET  0x00
#define PIO_SM1_SHIFTCTRL_PULL_THRESH_BITS   0x3e000000
#define PIO_SM1_SHIFTCTRL_PULL_THRESH_MSB    29
#define PIO_SM1_SHIFTCTRL_PULL_THRESH_LSB    25
#define PIO_SM1_SHIFTCTRL_PULL_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_PUSH_THRESH
// Description : Number of bits shifted into RXSR before autopush or conditional
//               push.
//               Write 0 for value of 32.
#define PIO_SM1_SHIFTCTRL_PUSH_THRESH_RESET  0x00
#define PIO_SM1_SHIFTCTRL_PUSH_THRESH_BITS   0x01f00000
#define PIO_SM1_SHIFTCTRL_PUSH_THRESH_MSB    24
#define PIO_SM1_SHIFTCTRL_PUSH_THRESH_LSB    20
#define PIO_SM1_SHIFTCTRL_PUSH_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_OUT_SHIFTDIR
// Description : 1 = shift out of output shift register to right. 0 = to left.
#define PIO_SM1_SHIFTCTRL_OUT_SHIFTDIR_RESET  0x1
#define PIO_SM1_SHIFTCTRL_OUT_SHIFTDIR_BITS   0x00080000
#define PIO_SM1_SHIFTCTRL_OUT_SHIFTDIR_MSB    19
#define PIO_SM1_SHIFTCTRL_OUT_SHIFTDIR_LSB    19
#define PIO_SM1_SHIFTCTRL_OUT_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_IN_SHIFTDIR
// Description : 1 = shift input shift register to right (data enters from
//               left). 0 = to left.
#define PIO_SM1_SHIFTCTRL_IN_SHIFTDIR_RESET  0x1
#define PIO_SM1_SHIFTCTRL_IN_SHIFTDIR_BITS   0x00040000
#define PIO_SM1_SHIFTCTRL_IN_SHIFTDIR_MSB    18
#define PIO_SM1_SHIFTCTRL_IN_SHIFTDIR_LSB    18
#define PIO_SM1_SHIFTCTRL_IN_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_AUTOPULL
// Description : Pull automatically when the output shift register is emptied
#define PIO_SM1_SHIFTCTRL_AUTOPULL_RESET  0x0
#define PIO_SM1_SHIFTCTRL_AUTOPULL_BITS   0x00020000
#define PIO_SM1_SHIFTCTRL_AUTOPULL_MSB    17
#define PIO_SM1_SHIFTCTRL_AUTOPULL_LSB    17
#define PIO_SM1_SHIFTCTRL_AUTOPULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_AUTOPUSH
// Description : Push automatically when the input shift register is filled
#define PIO_SM1_SHIFTCTRL_AUTOPUSH_RESET  0x0
#define PIO_SM1_SHIFTCTRL_AUTOPUSH_BITS   0x00010000
#define PIO_SM1_SHIFTCTRL_AUTOPUSH_MSB    16
#define PIO_SM1_SHIFTCTRL_AUTOPUSH_LSB    16
#define PIO_SM1_SHIFTCTRL_AUTOPUSH_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM1_ADDR
// Description : Current instruction address of state machine 1
#define PIO_SM1_ADDR_OFFSET 0x000000ec
#define PIO_SM1_ADDR_BITS   0x0000001f
#define PIO_SM1_ADDR_RESET  0x00000000
#define PIO_SM1_ADDR_MSB    4
#define PIO_SM1_ADDR_LSB    0
#define PIO_SM1_ADDR_ACCESS "RO"
// =============================================================================
// Register    : PIO_SM1_INSTR
// Description : Instruction currently being executed by state machine 1
//               Write to execute an instruction immediately (including jumps)
//               and then resume execution.
#define PIO_SM1_INSTR_OFFSET 0x000000f0
#define PIO_SM1_INSTR_BITS   0x0000ffff
#define PIO_SM1_INSTR_RESET  "-"
#define PIO_SM1_INSTR_MSB    15
#define PIO_SM1_INSTR_LSB    0
#define PIO_SM1_INSTR_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM1_PINCTRL
// Description : State machine pin control
#define PIO_SM1_PINCTRL_OFFSET 0x000000f4
#define PIO_SM1_PINCTRL_BITS   0xffffffff
#define PIO_SM1_PINCTRL_RESET  0x14000000
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_PINCTRL_SIDESET_COUNT
// Description : The number of delay bits co-opted for side-set. Inclusive of
//               the enable bit, if present.
#define PIO_SM1_PINCTRL_SIDESET_COUNT_RESET  0x0
#define PIO_SM1_PINCTRL_SIDESET_COUNT_BITS   0xe0000000
#define PIO_SM1_PINCTRL_SIDESET_COUNT_MSB    31
#define PIO_SM1_PINCTRL_SIDESET_COUNT_LSB    29
#define PIO_SM1_PINCTRL_SIDESET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_PINCTRL_SET_COUNT
// Description : The number of pins asserted by a SET. Max of 5
#define PIO_SM1_PINCTRL_SET_COUNT_RESET  0x5
#define PIO_SM1_PINCTRL_SET_COUNT_BITS   0x1c000000
#define PIO_SM1_PINCTRL_SET_COUNT_MSB    28
#define PIO_SM1_PINCTRL_SET_COUNT_LSB    26
#define PIO_SM1_PINCTRL_SET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_PINCTRL_OUT_COUNT
// Description : The number of pins asserted by an OUT. Value of 0 -> 32 pins
#define PIO_SM1_PINCTRL_OUT_COUNT_RESET  0x00
#define PIO_SM1_PINCTRL_OUT_COUNT_BITS   0x03f00000
#define PIO_SM1_PINCTRL_OUT_COUNT_MSB    25
#define PIO_SM1_PINCTRL_OUT_COUNT_LSB    20
#define PIO_SM1_PINCTRL_OUT_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_PINCTRL_IN_BASE
// Description : The virtual pin corresponding to IN bit 0
#define PIO_SM1_PINCTRL_IN_BASE_RESET  0x00
#define PIO_SM1_PINCTRL_IN_BASE_BITS   0x000f8000
#define PIO_SM1_PINCTRL_IN_BASE_MSB    19
#define PIO_SM1_PINCTRL_IN_BASE_LSB    15
#define PIO_SM1_PINCTRL_IN_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_PINCTRL_SIDESET_BASE
// Description : The virtual pin corresponding to delay field bit 0
#define PIO_SM1_PINCTRL_SIDESET_BASE_RESET  0x00
#define PIO_SM1_PINCTRL_SIDESET_BASE_BITS   0x00007c00
#define PIO_SM1_PINCTRL_SIDESET_BASE_MSB    14
#define PIO_SM1_PINCTRL_SIDESET_BASE_LSB    10
#define PIO_SM1_PINCTRL_SIDESET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_PINCTRL_SET_BASE
// Description : The virtual pin corresponding to SET bit 0
#define PIO_SM1_PINCTRL_SET_BASE_RESET  0x00
#define PIO_SM1_PINCTRL_SET_BASE_BITS   0x000003e0
#define PIO_SM1_PINCTRL_SET_BASE_MSB    9
#define PIO_SM1_PINCTRL_SET_BASE_LSB    5
#define PIO_SM1_PINCTRL_SET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_PINCTRL_OUT_BASE
// Description : The virtual pin corresponding to OUT bit 0
#define PIO_SM1_PINCTRL_OUT_BASE_RESET  0x00
#define PIO_SM1_PINCTRL_OUT_BASE_BITS   0x0000001f
#define PIO_SM1_PINCTRL_OUT_BASE_MSB    4
#define PIO_SM1_PINCTRL_OUT_BASE_LSB    0
#define PIO_SM1_PINCTRL_OUT_BASE_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM2_CLKDIV
// Description : Clock divider register for state machine 2
//               Frequency = clock freq / (CLKDIV_INT + CLKDIV_FRAC / 256)
#define PIO_SM2_CLKDIV_OFFSET 0x000000f8
#define PIO_SM2_CLKDIV_BITS   0xffffff00
#define PIO_SM2_CLKDIV_RESET  0x00010000
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_CLKDIV_INT
// Description : Effective frequency is sysclk/int.
//               Value of 0 is interpreted as max possible value
#define PIO_SM2_CLKDIV_INT_RESET  0x0001
#define PIO_SM2_CLKDIV_INT_BITS   0xffff0000
#define PIO_SM2_CLKDIV_INT_MSB    31
#define PIO_SM2_CLKDIV_INT_LSB    16
#define PIO_SM2_CLKDIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_CLKDIV_FRAC
// Description : Fractional part of clock divider
#define PIO_SM2_CLKDIV_FRAC_RESET  0x00
#define PIO_SM2_CLKDIV_FRAC_BITS   0x0000ff00
#define PIO_SM2_CLKDIV_FRAC_MSB    15
#define PIO_SM2_CLKDIV_FRAC_LSB    8
#define PIO_SM2_CLKDIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM2_EXECCTRL
// Description : Execution/behavioural settings for state machine 2
#define PIO_SM2_EXECCTRL_OFFSET 0x000000fc
#define PIO_SM2_EXECCTRL_BITS   0xffffff9f
#define PIO_SM2_EXECCTRL_RESET  0x0001f000
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_EXEC_STALLED
// Description : An instruction written to SMx_INSTR is stalled, and latched by
//               the
//               state machine. Will clear once the instruction completes.
#define PIO_SM2_EXECCTRL_EXEC_STALLED_RESET  0x0
#define PIO_SM2_EXECCTRL_EXEC_STALLED_BITS   0x80000000
#define PIO_SM2_EXECCTRL_EXEC_STALLED_MSB    31
#define PIO_SM2_EXECCTRL_EXEC_STALLED_LSB    31
#define PIO_SM2_EXECCTRL_EXEC_STALLED_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_SIDE_EN
// Description : If 1, the delay MSB is used as side-set enable, rather than a
//               side-set data bit. This allows instructions to perform side-set
//               optionally,
//               rather than on every instruction.
#define PIO_SM2_EXECCTRL_SIDE_EN_RESET  0x0
#define PIO_SM2_EXECCTRL_SIDE_EN_BITS   0x40000000
#define PIO_SM2_EXECCTRL_SIDE_EN_MSB    30
#define PIO_SM2_EXECCTRL_SIDE_EN_LSB    30
#define PIO_SM2_EXECCTRL_SIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_SIDE_PINDIR
// Description : Side-set data is asserted to pin OEs instead of pin values
#define PIO_SM2_EXECCTRL_SIDE_PINDIR_RESET  0x0
#define PIO_SM2_EXECCTRL_SIDE_PINDIR_BITS   0x20000000
#define PIO_SM2_EXECCTRL_SIDE_PINDIR_MSB    29
#define PIO_SM2_EXECCTRL_SIDE_PINDIR_LSB    29
#define PIO_SM2_EXECCTRL_SIDE_PINDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_JMP_PIN
// Description : The GPIO number to use as condition for JMP PIN. Unaffected by
//               input mapping.
#define PIO_SM2_EXECCTRL_JMP_PIN_RESET  0x00
#define PIO_SM2_EXECCTRL_JMP_PIN_BITS   0x1f000000
#define PIO_SM2_EXECCTRL_JMP_PIN_MSB    28
#define PIO_SM2_EXECCTRL_JMP_PIN_LSB    24
#define PIO_SM2_EXECCTRL_JMP_PIN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_OUT_EN_SEL
// Description : Which data bit to use for inline OUT enable
#define PIO_SM2_EXECCTRL_OUT_EN_SEL_RESET  0x00
#define PIO_SM2_EXECCTRL_OUT_EN_SEL_BITS   0x00f80000
#define PIO_SM2_EXECCTRL_OUT_EN_SEL_MSB    23
#define PIO_SM2_EXECCTRL_OUT_EN_SEL_LSB    19
#define PIO_SM2_EXECCTRL_OUT_EN_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_INLINE_OUT_EN
// Description : If 1, use a bit of OUT data as an auxiliary write enable
//               When used in conjunction with OUT_STICKY, writes with an enable
//               of 0 will
//               deassert the latest pin write. This can create useful
//               masking/override behaviour
//               due to the priority ordering of state machine pin writes (SM0 <
//               SM1 < ...)
#define PIO_SM2_EXECCTRL_INLINE_OUT_EN_RESET  0x0
#define PIO_SM2_EXECCTRL_INLINE_OUT_EN_BITS   0x00040000
#define PIO_SM2_EXECCTRL_INLINE_OUT_EN_MSB    18
#define PIO_SM2_EXECCTRL_INLINE_OUT_EN_LSB    18
#define PIO_SM2_EXECCTRL_INLINE_OUT_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_OUT_STICKY
// Description : Continuously assert the most recent OUT/SET to the pins
#define PIO_SM2_EXECCTRL_OUT_STICKY_RESET  0x0
#define PIO_SM2_EXECCTRL_OUT_STICKY_BITS   0x00020000
#define PIO_SM2_EXECCTRL_OUT_STICKY_MSB    17
#define PIO_SM2_EXECCTRL_OUT_STICKY_LSB    17
#define PIO_SM2_EXECCTRL_OUT_STICKY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_WRAP_TOP
// Description : After reaching this address, execution is wrapped to
//               wrap_bottom.
//               If the instruction is a jump, and the jump condition is true,
//               the jump takes priority.
#define PIO_SM2_EXECCTRL_WRAP_TOP_RESET  0x1f
#define PIO_SM2_EXECCTRL_WRAP_TOP_BITS   0x0001f000
#define PIO_SM2_EXECCTRL_WRAP_TOP_MSB    16
#define PIO_SM2_EXECCTRL_WRAP_TOP_LSB    12
#define PIO_SM2_EXECCTRL_WRAP_TOP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_WRAP_BOTTOM
// Description : After reaching wrap_top, execution is wrapped to this address.
#define PIO_SM2_EXECCTRL_WRAP_BOTTOM_RESET  0x00
#define PIO_SM2_EXECCTRL_WRAP_BOTTOM_BITS   0x00000f80
#define PIO_SM2_EXECCTRL_WRAP_BOTTOM_MSB    11
#define PIO_SM2_EXECCTRL_WRAP_BOTTOM_LSB    7
#define PIO_SM2_EXECCTRL_WRAP_BOTTOM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_STATUS_SEL
// Description : Comparison used for the MOV x, STATUS instruction.
//               0x0 -> All-ones if TX FIFO level < N, otherwise all-zeroes
//               0x1 -> All-ones if RX FIFO level < N, otherwise all-zeroes
#define PIO_SM2_EXECCTRL_STATUS_SEL_RESET         0x0
#define PIO_SM2_EXECCTRL_STATUS_SEL_BITS          0x00000010
#define PIO_SM2_EXECCTRL_STATUS_SEL_MSB           4
#define PIO_SM2_EXECCTRL_STATUS_SEL_LSB           4
#define PIO_SM2_EXECCTRL_STATUS_SEL_ACCESS        "RW"
#define PIO_SM2_EXECCTRL_STATUS_SEL_VALUE_TXLEVEL 0x0
#define PIO_SM2_EXECCTRL_STATUS_SEL_VALUE_RXLEVEL 0x1
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_STATUS_N
// Description : Comparison level for the MOV x, STATUS instruction
#define PIO_SM2_EXECCTRL_STATUS_N_RESET  0x0
#define PIO_SM2_EXECCTRL_STATUS_N_BITS   0x0000000f
#define PIO_SM2_EXECCTRL_STATUS_N_MSB    3
#define PIO_SM2_EXECCTRL_STATUS_N_LSB    0
#define PIO_SM2_EXECCTRL_STATUS_N_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM2_SHIFTCTRL
// Description : Control behaviour of the input/output shift registers for state
//               machine 2
#define PIO_SM2_SHIFTCTRL_OFFSET 0x00000100
#define PIO_SM2_SHIFTCTRL_BITS   0xffff0000
#define PIO_SM2_SHIFTCTRL_RESET  0x000c0000
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_FJOIN_RX
// Description : When 1, RX FIFO steals the TX FIFO's storage, and becomes twice
//               as deep.
//               TX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM2_SHIFTCTRL_FJOIN_RX_RESET  0x0
#define PIO_SM2_SHIFTCTRL_FJOIN_RX_BITS   0x80000000
#define PIO_SM2_SHIFTCTRL_FJOIN_RX_MSB    31
#define PIO_SM2_SHIFTCTRL_FJOIN_RX_LSB    31
#define PIO_SM2_SHIFTCTRL_FJOIN_RX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_FJOIN_TX
// Description : When 1, TX FIFO steals the RX FIFO's storage, and becomes twice
//               as deep.
//               RX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM2_SHIFTCTRL_FJOIN_TX_RESET  0x0
#define PIO_SM2_SHIFTCTRL_FJOIN_TX_BITS   0x40000000
#define PIO_SM2_SHIFTCTRL_FJOIN_TX_MSB    30
#define PIO_SM2_SHIFTCTRL_FJOIN_TX_LSB    30
#define PIO_SM2_SHIFTCTRL_FJOIN_TX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_PULL_THRESH
// Description : Number of bits shifted out of TXSR before autopull or
//               conditional pull.
//               Write 0 for value of 32.
#define PIO_SM2_SHIFTCTRL_PULL_THRESH_RESET  0x00
#define PIO_SM2_SHIFTCTRL_PULL_THRESH_BITS   0x3e000000
#define PIO_SM2_SHIFTCTRL_PULL_THRESH_MSB    29
#define PIO_SM2_SHIFTCTRL_PULL_THRESH_LSB    25
#define PIO_SM2_SHIFTCTRL_PULL_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_PUSH_THRESH
// Description : Number of bits shifted into RXSR before autopush or conditional
//               push.
//               Write 0 for value of 32.
#define PIO_SM2_SHIFTCTRL_PUSH_THRESH_RESET  0x00
#define PIO_SM2_SHIFTCTRL_PUSH_THRESH_BITS   0x01f00000
#define PIO_SM2_SHIFTCTRL_PUSH_THRESH_MSB    24
#define PIO_SM2_SHIFTCTRL_PUSH_THRESH_LSB    20
#define PIO_SM2_SHIFTCTRL_PUSH_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_OUT_SHIFTDIR
// Description : 1 = shift out of output shift register to right. 0 = to left.
#define PIO_SM2_SHIFTCTRL_OUT_SHIFTDIR_RESET  0x1
#define PIO_SM2_SHIFTCTRL_OUT_SHIFTDIR_BITS   0x00080000
#define PIO_SM2_SHIFTCTRL_OUT_SHIFTDIR_MSB    19
#define PIO_SM2_SHIFTCTRL_OUT_SHIFTDIR_LSB    19
#define PIO_SM2_SHIFTCTRL_OUT_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_IN_SHIFTDIR
// Description : 1 = shift input shift register to right (data enters from
//               left). 0 = to left.
#define PIO_SM2_SHIFTCTRL_IN_SHIFTDIR_RESET  0x1
#define PIO_SM2_SHIFTCTRL_IN_SHIFTDIR_BITS   0x00040000
#define PIO_SM2_SHIFTCTRL_IN_SHIFTDIR_MSB    18
#define PIO_SM2_SHIFTCTRL_IN_SHIFTDIR_LSB    18
#define PIO_SM2_SHIFTCTRL_IN_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_AUTOPULL
// Description : Pull automatically when the output shift register is emptied
#define PIO_SM2_SHIFTCTRL_AUTOPULL_RESET  0x0
#define PIO_SM2_SHIFTCTRL_AUTOPULL_BITS   0x00020000
#define PIO_SM2_SHIFTCTRL_AUTOPULL_MSB    17
#define PIO_SM2_SHIFTCTRL_AUTOPULL_LSB    17
#define PIO_SM2_SHIFTCTRL_AUTOPULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_AUTOPUSH
// Description : Push automatically when the input shift register is filled
#define PIO_SM2_SHIFTCTRL_AUTOPUSH_RESET  0x0
#define PIO_SM2_SHIFTCTRL_AUTOPUSH_BITS   0x00010000
#define PIO_SM2_SHIFTCTRL_AUTOPUSH_MSB    16
#define PIO_SM2_SHIFTCTRL_AUTOPUSH_LSB    16
#define PIO_SM2_SHIFTCTRL_AUTOPUSH_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM2_ADDR
// Description : Current instruction address of state machine 2
#define PIO_SM2_ADDR_OFFSET 0x00000104
#define PIO_SM2_ADDR_BITS   0x0000001f
#define PIO_SM2_ADDR_RESET  0x00000000
#define PIO_SM2_ADDR_MSB    4
#define PIO_SM2_ADDR_LSB    0
#define PIO_SM2_ADDR_ACCESS "RO"
// =============================================================================
// Register    : PIO_SM2_INSTR
// Description : Instruction currently being executed by state machine 2
//               Write to execute an instruction immediately (including jumps)
//               and then resume execution.
#define PIO_SM2_INSTR_OFFSET 0x00000108
#define PIO_SM2_INSTR_BITS   0x0000ffff
#define PIO_SM2_INSTR_RESET  "-"
#define PIO_SM2_INSTR_MSB    15
#define PIO_SM2_INSTR_LSB    0
#define PIO_SM2_INSTR_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM2_PINCTRL
// Description : State machine pin control
#define PIO_SM2_PINCTRL_OFFSET 0x0000010c
#define PIO_SM2_PINCTRL_BITS   0xffffffff
#define PIO_SM2_PINCTRL_RESET  0x14000000
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_PINCTRL_SIDESET_COUNT
// Description : The number of delay bits co-opted for side-set. Inclusive of
//               the enable bit, if present.
#define PIO_SM2_PINCTRL_SIDESET_COUNT_RESET  0x0
#define PIO_SM2_PINCTRL_SIDESET_COUNT_BITS   0xe0000000
#define PIO_SM2_PINCTRL_SIDESET_COUNT_MSB    31
#define PIO_SM2_PINCTRL_SIDESET_COUNT_LSB    29
#define PIO_SM2_PINCTRL_SIDESET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_PINCTRL_SET_COUNT
// Description : The number of pins asserted by a SET. Max of 5
#define PIO_SM2_PINCTRL_SET_COUNT_RESET  0x5
#define PIO_SM2_PINCTRL_SET_COUNT_BITS   0x1c000000
#define PIO_SM2_PINCTRL_SET_COUNT_MSB    28
#define PIO_SM2_PINCTRL_SET_COUNT_LSB    26
#define PIO_SM2_PINCTRL_SET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_PINCTRL_OUT_COUNT
// Description : The number of pins asserted by an OUT. Value of 0 -> 32 pins
#define PIO_SM2_PINCTRL_OUT_COUNT_RESET  0x00
#define PIO_SM2_PINCTRL_OUT_COUNT_BITS   0x03f00000
#define PIO_SM2_PINCTRL_OUT_COUNT_MSB    25
#define PIO_SM2_PINCTRL_OUT_COUNT_LSB    20
#define PIO_SM2_PINCTRL_OUT_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_PINCTRL_IN_BASE
// Description : The virtual pin corresponding to IN bit 0
#define PIO_SM2_PINCTRL_IN_BASE_RESET  0x00
#define PIO_SM2_PINCTRL_IN_BASE_BITS   0x000f8000
#define PIO_SM2_PINCTRL_IN_BASE_MSB    19
#define PIO_SM2_PINCTRL_IN_BASE_LSB    15
#define PIO_SM2_PINCTRL_IN_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_PINCTRL_SIDESET_BASE
// Description : The virtual pin corresponding to delay field bit 0
#define PIO_SM2_PINCTRL_SIDESET_BASE_RESET  0x00
#define PIO_SM2_PINCTRL_SIDESET_BASE_BITS   0x00007c00
#define PIO_SM2_PINCTRL_SIDESET_BASE_MSB    14
#define PIO_SM2_PINCTRL_SIDESET_BASE_LSB    10
#define PIO_SM2_PINCTRL_SIDESET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_PINCTRL_SET_BASE
// Description : The virtual pin corresponding to SET bit 0
#define PIO_SM2_PINCTRL_SET_BASE_RESET  0x00
#define PIO_SM2_PINCTRL_SET_BASE_BITS   0x000003e0
#define PIO_SM2_PINCTRL_SET_BASE_MSB    9
#define PIO_SM2_PINCTRL_SET_BASE_LSB    5
#define PIO_SM2_PINCTRL_SET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_PINCTRL_OUT_BASE
// Description : The virtual pin corresponding to OUT bit 0
#define PIO_SM2_PINCTRL_OUT_BASE_RESET  0x00
#define PIO_SM2_PINCTRL_OUT_BASE_BITS   0x0000001f
#define PIO_SM2_PINCTRL_OUT_BASE_MSB    4
#define PIO_SM2_PINCTRL_OUT_BASE_LSB    0
#define PIO_SM2_PINCTRL_OUT_BASE_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM3_CLKDIV
// Description : Clock divider register for state machine 3
//               Frequency = clock freq / (CLKDIV_INT + CLKDIV_FRAC / 256)
#define PIO_SM3_CLKDIV_OFFSET 0x00000110
#define PIO_SM3_CLKDIV_BITS   0xffffff00
#define PIO_SM3_CLKDIV_RESET  0x00010000
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_CLKDIV_INT
// Description : Effective frequency is sysclk/int.
//               Value of 0 is interpreted as max possible value
#define PIO_SM3_CLKDIV_INT_RESET  0x0001
#define PIO_SM3_CLKDIV_INT_BITS   0xffff0000
#define PIO_SM3_CLKDIV_INT_MSB    31
#define PIO_SM3_CLKDIV_INT_LSB    16
#define PIO_SM3_CLKDIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_CLKDIV_FRAC
// Description : Fractional part of clock divider
#define PIO_SM3_CLKDIV_FRAC_RESET  0x00
#define PIO_SM3_CLKDIV_FRAC_BITS   0x0000ff00
#define PIO_SM3_CLKDIV_FRAC_MSB    15
#define PIO_SM3_CLKDIV_FRAC_LSB    8
#define PIO_SM3_CLKDIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM3_EXECCTRL
// Description : Execution/behavioural settings for state machine 3
#define PIO_SM3_EXECCTRL_OFFSET 0x00000114
#define PIO_SM3_EXECCTRL_BITS   0xffffff9f
#define PIO_SM3_EXECCTRL_RESET  0x0001f000
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_EXEC_STALLED
// Description : An instruction written to SMx_INSTR is stalled, and latched by
//               the
//               state machine. Will clear once the instruction completes.
#define PIO_SM3_EXECCTRL_EXEC_STALLED_RESET  0x0
#define PIO_SM3_EXECCTRL_EXEC_STALLED_BITS   0x80000000
#define PIO_SM3_EXECCTRL_EXEC_STALLED_MSB    31
#define PIO_SM3_EXECCTRL_EXEC_STALLED_LSB    31
#define PIO_SM3_EXECCTRL_EXEC_STALLED_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_SIDE_EN
// Description : If 1, the delay MSB is used as side-set enable, rather than a
//               side-set data bit. This allows instructions to perform side-set
//               optionally,
//               rather than on every instruction.
#define PIO_SM3_EXECCTRL_SIDE_EN_RESET  0x0
#define PIO_SM3_EXECCTRL_SIDE_EN_BITS   0x40000000
#define PIO_SM3_EXECCTRL_SIDE_EN_MSB    30
#define PIO_SM3_EXECCTRL_SIDE_EN_LSB    30
#define PIO_SM3_EXECCTRL_SIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_SIDE_PINDIR
// Description : Side-set data is asserted to pin OEs instead of pin values
#define PIO_SM3_EXECCTRL_SIDE_PINDIR_RESET  0x0
#define PIO_SM3_EXECCTRL_SIDE_PINDIR_BITS   0x20000000
#define PIO_SM3_EXECCTRL_SIDE_PINDIR_MSB    29
#define PIO_SM3_EXECCTRL_SIDE_PINDIR_LSB    29
#define PIO_SM3_EXECCTRL_SIDE_PINDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_JMP_PIN
// Description : The GPIO number to use as condition for JMP PIN. Unaffected by
//               input mapping.
#define PIO_SM3_EXECCTRL_JMP_PIN_RESET  0x00
#define PIO_SM3_EXECCTRL_JMP_PIN_BITS   0x1f000000
#define PIO_SM3_EXECCTRL_JMP_PIN_MSB    28
#define PIO_SM3_EXECCTRL_JMP_PIN_LSB    24
#define PIO_SM3_EXECCTRL_JMP_PIN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_OUT_EN_SEL
// Description : Which data bit to use for inline OUT enable
#define PIO_SM3_EXECCTRL_OUT_EN_SEL_RESET  0x00
#define PIO_SM3_EXECCTRL_OUT_EN_SEL_BITS   0x00f80000
#define PIO_SM3_EXECCTRL_OUT_EN_SEL_MSB    23
#define PIO_SM3_EXECCTRL_OUT_EN_SEL_LSB    19
#define PIO_SM3_EXECCTRL_OUT_EN_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_INLINE_OUT_EN
// Description : If 1, use a bit of OUT data as an auxiliary write enable
//               When used in conjunction with OUT_STICKY, writes with an enable
//               of 0 will
//               deassert the latest pin write. This can create useful
//               masking/override behaviour
//               due to the priority ordering of state machine pin writes (SM0 <
//               SM1 < ...)
#define PIO_SM3_EXECCTRL_INLINE_OUT_EN_RESET  0x0
#define PIO_SM3_EXECCTRL_INLINE_OUT_EN_BITS   0x00040000
#define PIO_SM3_EXECCTRL_INLINE_OUT_EN_MSB    18
#define PIO_SM3_EXECCTRL_INLINE_OUT_EN_LSB    18
#define PIO_SM3_EXECCTRL_INLINE_OUT_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_OUT_STICKY
// Description : Continuously assert the most recent OUT/SET to the pins
#define PIO_SM3_EXECCTRL_OUT_STICKY_RESET  0x0
#define PIO_SM3_EXECCTRL_OUT_STICKY_BITS   0x00020000
#define PIO_SM3_EXECCTRL_OUT_STICKY_MSB    17
#define PIO_SM3_EXECCTRL_OUT_STICKY_LSB    17
#define PIO_SM3_EXECCTRL_OUT_STICKY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_WRAP_TOP
// Description : After reaching this address, execution is wrapped to
//               wrap_bottom.
//               If the instruction is a jump, and the jump condition is true,
//               the jump takes priority.
#define PIO_SM3_EXECCTRL_WRAP_TOP_RESET  0x1f
#define PIO_SM3_EXECCTRL_WRAP_TOP_BITS   0x0001f000
#define PIO_SM3_EXECCTRL_WRAP_TOP_MSB    16
#define PIO_SM3_EXECCTRL_WRAP_TOP_LSB    12
#define PIO_SM3_EXECCTRL_WRAP_TOP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_WRAP_BOTTOM
// Description : After reaching wrap_top, execution is wrapped to this address.
#define PIO_SM3_EXECCTRL_WRAP_BOTTOM_RESET  0x00
#define PIO_SM3_EXECCTRL_WRAP_BOTTOM_BITS   0x00000f80
#define PIO_SM3_EXECCTRL_WRAP_BOTTOM_MSB    11
#define PIO_SM3_EXECCTRL_WRAP_BOTTOM_LSB    7
#define PIO_SM3_EXECCTRL_WRAP_BOTTOM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_STATUS_SEL
// Description : Comparison used for the MOV x, STATUS instruction.
//               0x0 -> All-ones if TX FIFO level < N, otherwise all-zeroes
//               0x1 -> All-ones if RX FIFO level < N, otherwise all-zeroes
#define PIO_SM3_EXECCTRL_STATUS_SEL_RESET         0x0
#define PIO_SM3_EXECCTRL_STATUS_SEL_BITS          0x00000010
#define PIO_SM3_EXECCTRL_STATUS_SEL_MSB           4
#define PIO_SM3_EXECCTRL_STATUS_SEL_LSB           4
#define PIO_SM3_EXECCTRL_STATUS_SEL_ACCESS        "RW"
#define PIO_SM3_EXECCTRL_STATUS_SEL_VALUE_TXLEVEL 0x0
#define PIO_SM3_EXECCTRL_STATUS_SEL_VALUE_RXLEVEL 0x1
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_STATUS_N
// Description : Comparison level for the MOV x, STATUS instruction
#define PIO_SM3_EXECCTRL_STATUS_N_RESET  0x0
#define PIO_SM3_EXECCTRL_STATUS_N_BITS   0x0000000f
#define PIO_SM3_EXECCTRL_STATUS_N_MSB    3
#define PIO_SM3_EXECCTRL_STATUS_N_LSB    0
#define PIO_SM3_EXECCTRL_STATUS_N_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM3_SHIFTCTRL
// Description : Control behaviour of the input/output shift registers for state
//               machine 3
#define PIO_SM3_SHIFTCTRL_OFFSET 0x00000118
#define PIO_SM3_SHIFTCTRL_BITS   0xffff0000
#define PIO_SM3_SHIFTCTRL_RESET  0x000c0000
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_FJOIN_RX
// Description : When 1, RX FIFO steals the TX FIFO's storage, and becomes twice
//               as deep.
//               TX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM3_SHIFTCTRL_FJOIN_RX_RESET  0x0
#define PIO_SM3_SHIFTCTRL_FJOIN_RX_BITS   0x80000000
#define PIO_SM3_SHIFTCTRL_FJOIN_RX_MSB    31
#define PIO_SM3_SHIFTCTRL_FJOIN_RX_LSB    31
#define PIO_SM3_SHIFTCTRL_FJOIN_RX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_FJOIN_TX
// Description : When 1, TX FIFO steals the RX FIFO's storage, and becomes twice
//               as deep.
//               RX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM3_SHIFTCTRL_FJOIN_TX_RESET  0x0
#define PIO_SM3_SHIFTCTRL_FJOIN_TX_BITS   0x40000000
#define PIO_SM3_SHIFTCTRL_FJOIN_TX_MSB    30
#define PIO_SM3_SHIFTCTRL_FJOIN_TX_LSB    30
#define PIO_SM3_SHIFTCTRL_FJOIN_TX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_PULL_THRESH
// Description : Number of bits shifted out of TXSR before autopull or
//               conditional pull.
//               Write 0 for value of 32.
#define PIO_SM3_SHIFTCTRL_PULL_THRESH_RESET  0x00
#define PIO_SM3_SHIFTCTRL_PULL_THRESH_BITS   0x3e000000
#define PIO_SM3_SHIFTCTRL_PULL_THRESH_MSB    29
#define PIO_SM3_SHIFTCTRL_PULL_THRESH_LSB    25
#define PIO_SM3_SHIFTCTRL_PULL_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_PUSH_THRESH
// Description : Number of bits shifted into RXSR before autopush or conditional
//               push.
//               Write 0 for value of 32.
#define PIO_SM3_SHIFTCTRL_PUSH_THRESH_RESET  0x00
#define PIO_SM3_SHIFTCTRL_PUSH_THRESH_BITS   0x01f00000
#define PIO_SM3_SHIFTCTRL_PUSH_THRESH_MSB    24
#define PIO_SM3_SHIFTCTRL_PUSH_THRESH_LSB    20
#define PIO_SM3_SHIFTCTRL_PUSH_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_OUT_SHIFTDIR
// Description : 1 = shift out of output shift register to right. 0 = to left.
#define PIO_SM3_SHIFTCTRL_OUT_SHIFTDIR_RESET  0x1
#define PIO_SM3_SHIFTCTRL_OUT_SHIFTDIR_BITS   0x00080000
#define PIO_SM3_SHIFTCTRL_OUT_SHIFTDIR_MSB    19
#define PIO_SM3_SHIFTCTRL_OUT_SHIFTDIR_LSB    19
#define PIO_SM3_SHIFTCTRL_OUT_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_IN_SHIFTDIR
// Description : 1 = shift input shift register to right (data enters from
//               left). 0 = to left.
#define PIO_SM3_SHIFTCTRL_IN_SHIFTDIR_RESET  0x1
#define PIO_SM3_SHIFTCTRL_IN_SHIFTDIR_BITS   0x00040000
#define PIO_SM3_SHIFTCTRL_IN_SHIFTDIR_MSB    18
#define PIO_SM3_SHIFTCTRL_IN_SHIFTDIR_LSB    18
#define PIO_SM3_SHIFTCTRL_IN_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_AUTOPULL
// Description : Pull automatically when the output shift register is emptied
#define PIO_SM3_SHIFTCTRL_AUTOPULL_RESET  0x0
#define PIO_SM3_SHIFTCTRL_AUTOPULL_BITS   0x00020000
#define PIO_SM3_SHIFTCTRL_AUTOPULL_MSB    17
#define PIO_SM3_SHIFTCTRL_AUTOPULL_LSB    17
#define PIO_SM3_SHIFTCTRL_AUTOPULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_AUTOPUSH
// Description : Push automatically when the input shift register is filled
#define PIO_SM3_SHIFTCTRL_AUTOPUSH_RESET  0x0
#define PIO_SM3_SHIFTCTRL_AUTOPUSH_BITS   0x00010000
#define PIO_SM3_SHIFTCTRL_AUTOPUSH_MSB    16
#define PIO_SM3_SHIFTCTRL_AUTOPUSH_LSB    16
#define PIO_SM3_SHIFTCTRL_AUTOPUSH_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM3_ADDR
// Description : Current instruction address of state machine 3
#define PIO_SM3_ADDR_OFFSET 0x0000011c
#define PIO_SM3_ADDR_BITS   0x0000001f
#define PIO_SM3_ADDR_RESET  0x00000000
#define PIO_SM3_ADDR_MSB    4
#define PIO_SM3_ADDR_LSB    0
#define PIO_SM3_ADDR_ACCESS "RO"
// =============================================================================
// Register    : PIO_SM3_INSTR
// Description : Instruction currently being executed by state machine 3
//               Write to execute an instruction immediately (including jumps)
//               and then resume execution.
#define PIO_SM3_INSTR_OFFSET 0x00000120
#define PIO_SM3_INSTR_BITS   0x0000ffff
#define PIO_SM3_INSTR_RESET  "-"
#define PIO_SM3_INSTR_MSB    15
#define PIO_SM3_INSTR_LSB    0
#define PIO_SM3_INSTR_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM3_PINCTRL
// Description : State machine pin control
#define PIO_SM3_PINCTRL_OFFSET 0x00000124
#define PIO_SM3_PINCTRL_BITS   0xffffffff
#define PIO_SM3_PINCTRL_RESET  0x14000000
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_PINCTRL_SIDESET_COUNT
// Description : The number of delay bits co-opted for side-set. Inclusive of
//               the enable bit, if present.
#define PIO_SM3_PINCTRL_SIDESET_COUNT_RESET  0x0
#define PIO_SM3_PINCTRL_SIDESET_COUNT_BITS   0xe0000000
#define PIO_SM3_PINCTRL_SIDESET_COUNT_MSB    31
#define PIO_SM3_PINCTRL_SIDESET_COUNT_LSB    29
#define PIO_SM3_PINCTRL_SIDESET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_PINCTRL_SET_COUNT
// Description : The number of pins asserted by a SET. Max of 5
#define PIO_SM3_PINCTRL_SET_COUNT_RESET  0x5
#define PIO_SM3_PINCTRL_SET_COUNT_BITS   0x1c000000
#define PIO_SM3_PINCTRL_SET_COUNT_MSB    28
#define PIO_SM3_PINCTRL_SET_COUNT_LSB    26
#define PIO_SM3_PINCTRL_SET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_PINCTRL_OUT_COUNT
// Description : The number of pins asserted by an OUT. Value of 0 -> 32 pins
#define PIO_SM3_PINCTRL_OUT_COUNT_RESET  0x00
#define PIO_SM3_PINCTRL_OUT_COUNT_BITS   0x03f00000
#define PIO_SM3_PINCTRL_OUT_COUNT_MSB    25
#define PIO_SM3_PINCTRL_OUT_COUNT_LSB    20
#define PIO_SM3_PINCTRL_OUT_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_PINCTRL_IN_BASE
// Description : The virtual pin corresponding to IN bit 0
#define PIO_SM3_PINCTRL_IN_BASE_RESET  0x00
#define PIO_SM3_PINCTRL_IN_BASE_BITS   0x000f8000
#define PIO_SM3_PINCTRL_IN_BASE_MSB    19
#define PIO_SM3_PINCTRL_IN_BASE_LSB    15
#define PIO_SM3_PINCTRL_IN_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_PINCTRL_SIDESET_BASE
// Description : The virtual pin corresponding to delay field bit 0
#define PIO_SM3_PINCTRL_SIDESET_BASE_RESET  0x00
#define PIO_SM3_PINCTRL_SIDESET_BASE_BITS   0x00007c00
#define PIO_SM3_PINCTRL_SIDESET_BASE_MSB    14
#define PIO_SM3_PINCTRL_SIDESET_BASE_LSB    10
#define PIO_SM3_PINCTRL_SIDESET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_PINCTRL_SET_BASE
// Description : The virtual pin corresponding to SET bit 0
#define PIO_SM3_PINCTRL_SET_BASE_RESET  0x00
#define PIO_SM3_PINCTRL_SET_BASE_BITS   0x000003e0
#define PIO_SM3_PINCTRL_SET_BASE_MSB    9
#define PIO_SM3_PINCTRL_SET_BASE_LSB    5
#define PIO_SM3_PINCTRL_SET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_PINCTRL_OUT_BASE
// Description : The virtual pin corresponding to OUT bit 0
#define PIO_SM3_PINCTRL_OUT_BASE_RESET  0x00
#define PIO_SM3_PINCTRL_OUT_BASE_BITS   0x0000001f
#define PIO_SM3_PINCTRL_OUT_BASE_MSB    4
#define PIO_SM3_PINCTRL_OUT_BASE_LSB    0
#define PIO_SM3_PINCTRL_OUT_BASE_ACCESS "RW"
// =============================================================================
// Register    : PIO_INTR
// Description : Raw Interrupts
#define PIO_INTR_OFFSET 0x00000128
#define PIO_INTR_BITS   0x00000fff
#define PIO_INTR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM3
// Description : None
#define PIO_INTR_SM3_RESET  0x0
#define PIO_INTR_SM3_BITS   0x00000800
#define PIO_INTR_SM3_MSB    11
#define PIO_INTR_SM3_LSB    11
#define PIO_INTR_SM3_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM2
// Description : None
#define PIO_INTR_SM2_RESET  0x0
#define PIO_INTR_SM2_BITS   0x00000400
#define PIO_INTR_SM2_MSB    10
#define PIO_INTR_SM2_LSB    10
#define PIO_INTR_SM2_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM1
// Description : None
#define PIO_INTR_SM1_RESET  0x0
#define PIO_INTR_SM1_BITS   0x00000200
#define PIO_INTR_SM1_MSB    9
#define PIO_INTR_SM1_LSB    9
#define PIO_INTR_SM1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM0
// Description : None
#define PIO_INTR_SM0_RESET  0x0
#define PIO_INTR_SM0_BITS   0x00000100
#define PIO_INTR_SM0_MSB    8
#define PIO_INTR_SM0_LSB    8
#define PIO_INTR_SM0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM3_TXNFULL
// Description : None
#define PIO_INTR_SM3_TXNFULL_RESET  0x0
#define PIO_INTR_SM3_TXNFULL_BITS   0x00000080
#define PIO_INTR_SM3_TXNFULL_MSB    7
#define PIO_INTR_SM3_TXNFULL_LSB    7
#define PIO_INTR_SM3_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM2_TXNFULL
// Description : None
#define PIO_INTR_SM2_TXNFULL_RESET  0x0
#define PIO_INTR_SM2_TXNFULL_BITS   0x00000040
#define PIO_INTR_SM2_TXNFULL_MSB    6
#define PIO_INTR_SM2_TXNFULL_LSB    6
#define PIO_INTR_SM2_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM1_TXNFULL
// Description : None
#define PIO_INTR_SM1_TXNFULL_RESET  0x0
#define PIO_INTR_SM1_TXNFULL_BITS   0x00000020
#define PIO_INTR_SM1_TXNFULL_MSB    5
#define PIO_INTR_SM1_TXNFULL_LSB    5
#define PIO_INTR_SM1_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM0_TXNFULL
// Description : None
#define PIO_INTR_SM0_TXNFULL_RESET  0x0
#define PIO_INTR_SM0_TXNFULL_BITS   0x00000010
#define PIO_INTR_SM0_TXNFULL_MSB    4
#define PIO_INTR_SM0_TXNFULL_LSB    4
#define PIO_INTR_SM0_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM3_RXNEMPTY
// Description : None
#define PIO_INTR_SM3_RXNEMPTY_RESET  0x0
#define PIO_INTR_SM3_RXNEMPTY_BITS   0x00000008
#define PIO_INTR_SM3_RXNEMPTY_MSB    3
#define PIO_INTR_SM3_RXNEMPTY_LSB    3
#define PIO_INTR_SM3_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM2_RXNEMPTY
// Description : None
#define PIO_INTR_SM2_RXNEMPTY_RESET  0x0
#define PIO_INTR_SM2_RXNEMPTY_BITS   0x00000004
#define PIO_INTR_SM2_RXNEMPTY_MSB    2
#define PIO_INTR_SM2_RXNEMPTY_LSB    2
#define PIO_INTR_SM2_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM1_RXNEMPTY
// Description : None
#define PIO_INTR_SM1_RXNEMPTY_RESET  0x0
#define PIO_INTR_SM1_RXNEMPTY_BITS   0x00000002
#define PIO_INTR_SM1_RXNEMPTY_MSB    1
#define PIO_INTR_SM1_RXNEMPTY_LSB    1
#define PIO_INTR_SM1_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM0_RXNEMPTY
// Description : None
#define PIO_INTR_SM0_RXNEMPTY_RESET  0x0
#define PIO_INTR_SM0_RXNEMPTY_BITS   0x00000001
#define PIO_INTR_SM0_RXNEMPTY_MSB    0
#define PIO_INTR_SM0_RXNEMPTY_LSB    0
#define PIO_INTR_SM0_RXNEMPTY_ACCESS "RO"
// =============================================================================
// Register    : PIO_IRQ0_INTE
// Description : Interrupt Enable for irq0
#define PIO_IRQ0_INTE_OFFSET 0x0000012c
#define PIO_IRQ0_INTE_BITS   0x00000fff
#define PIO_IRQ0_INTE_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM3
// Description : None
#define PIO_IRQ0_INTE_SM3_RESET  0x0
#define PIO_IRQ0_INTE_SM3_BITS   0x00000800
#define PIO_IRQ0_INTE_SM3_MSB    11
#define PIO_IRQ0_INTE_SM3_LSB    11
#define PIO_IRQ0_INTE_SM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM2
// Description : None
#define PIO_IRQ0_INTE_SM2_RESET  0x0
#define PIO_IRQ0_INTE_SM2_BITS   0x00000400
#define PIO_IRQ0_INTE_SM2_MSB    10
#define PIO_IRQ0_INTE_SM2_LSB    10
#define PIO_IRQ0_INTE_SM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM1
// Description : None
#define PIO_IRQ0_INTE_SM1_RESET  0x0
#define PIO_IRQ0_INTE_SM1_BITS   0x00000200
#define PIO_IRQ0_INTE_SM1_MSB    9
#define PIO_IRQ0_INTE_SM1_LSB    9
#define PIO_IRQ0_INTE_SM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM0
// Description : None
#define PIO_IRQ0_INTE_SM0_RESET  0x0
#define PIO_IRQ0_INTE_SM0_BITS   0x00000100
#define PIO_IRQ0_INTE_SM0_MSB    8
#define PIO_IRQ0_INTE_SM0_LSB    8
#define PIO_IRQ0_INTE_SM0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM3_TXNFULL
// Description : None
#define PIO_IRQ0_INTE_SM3_TXNFULL_RESET  0x0
#define PIO_IRQ0_INTE_SM3_TXNFULL_BITS   0x00000080
#define PIO_IRQ0_INTE_SM3_TXNFULL_MSB    7
#define PIO_IRQ0_INTE_SM3_TXNFULL_LSB    7
#define PIO_IRQ0_INTE_SM3_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM2_TXNFULL
// Description : None
#define PIO_IRQ0_INTE_SM2_TXNFULL_RESET  0x0
#define PIO_IRQ0_INTE_SM2_TXNFULL_BITS   0x00000040
#define PIO_IRQ0_INTE_SM2_TXNFULL_MSB    6
#define PIO_IRQ0_INTE_SM2_TXNFULL_LSB    6
#define PIO_IRQ0_INTE_SM2_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM1_TXNFULL
// Description : None
#define PIO_IRQ0_INTE_SM1_TXNFULL_RESET  0x0
#define PIO_IRQ0_INTE_SM1_TXNFULL_BITS   0x00000020
#define PIO_IRQ0_INTE_SM1_TXNFULL_MSB    5
#define PIO_IRQ0_INTE_SM1_TXNFULL_LSB    5
#define PIO_IRQ0_INTE_SM1_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM0_TXNFULL
// Description : None
#define PIO_IRQ0_INTE_SM0_TXNFULL_RESET  0x0
#define PIO_IRQ0_INTE_SM0_TXNFULL_BITS   0x00000010
#define PIO_IRQ0_INTE_SM0_TXNFULL_MSB    4
#define PIO_IRQ0_INTE_SM0_TXNFULL_LSB    4
#define PIO_IRQ0_INTE_SM0_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM3_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTE_SM3_RXNEMPTY_RESET  0x0
#define PIO_IRQ0_INTE_SM3_RXNEMPTY_BITS   0x00000008
#define PIO_IRQ0_INTE_SM3_RXNEMPTY_MSB    3
#define PIO_IRQ0_INTE_SM3_RXNEMPTY_LSB    3
#define PIO_IRQ0_INTE_SM3_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM2_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTE_SM2_RXNEMPTY_RESET  0x0
#define PIO_IRQ0_INTE_SM2_RXNEMPTY_BITS   0x00000004
#define PIO_IRQ0_INTE_SM2_RXNEMPTY_MSB    2
#define PIO_IRQ0_INTE_SM2_RXNEMPTY_LSB    2
#define PIO_IRQ0_INTE_SM2_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM1_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTE_SM1_RXNEMPTY_RESET  0x0
#define PIO_IRQ0_INTE_SM1_RXNEMPTY_BITS   0x00000002
#define PIO_IRQ0_INTE_SM1_RXNEMPTY_MSB    1
#define PIO_IRQ0_INTE_SM1_RXNEMPTY_LSB    1
#define PIO_IRQ0_INTE_SM1_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM0_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTE_SM0_RXNEMPTY_RESET  0x0
#define PIO_IRQ0_INTE_SM0_RXNEMPTY_BITS   0x00000001
#define PIO_IRQ0_INTE_SM0_RXNEMPTY_MSB    0
#define PIO_IRQ0_INTE_SM0_RXNEMPTY_LSB    0
#define PIO_IRQ0_INTE_SM0_RXNEMPTY_ACCESS "RW"
// =============================================================================
// Register    : PIO_IRQ0_INTF
// Description : Interrupt Force for irq0
#define PIO_IRQ0_INTF_OFFSET 0x00000130
#define PIO_IRQ0_INTF_BITS   0x00000fff
#define PIO_IRQ0_INTF_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM3
// Description : None
#define PIO_IRQ0_INTF_SM3_RESET  0x0
#define PIO_IRQ0_INTF_SM3_BITS   0x00000800
#define PIO_IRQ0_INTF_SM3_MSB    11
#define PIO_IRQ0_INTF_SM3_LSB    11
#define PIO_IRQ0_INTF_SM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM2
// Description : None
#define PIO_IRQ0_INTF_SM2_RESET  0x0
#define PIO_IRQ0_INTF_SM2_BITS   0x00000400
#define PIO_IRQ0_INTF_SM2_MSB    10
#define PIO_IRQ0_INTF_SM2_LSB    10
#define PIO_IRQ0_INTF_SM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM1
// Description : None
#define PIO_IRQ0_INTF_SM1_RESET  0x0
#define PIO_IRQ0_INTF_SM1_BITS   0x00000200
#define PIO_IRQ0_INTF_SM1_MSB    9
#define PIO_IRQ0_INTF_SM1_LSB    9
#define PIO_IRQ0_INTF_SM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM0
// Description : None
#define PIO_IRQ0_INTF_SM0_RESET  0x0
#define PIO_IRQ0_INTF_SM0_BITS   0x00000100
#define PIO_IRQ0_INTF_SM0_MSB    8
#define PIO_IRQ0_INTF_SM0_LSB    8
#define PIO_IRQ0_INTF_SM0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM3_TXNFULL
// Description : None
#define PIO_IRQ0_INTF_SM3_TXNFULL_RESET  0x0
#define PIO_IRQ0_INTF_SM3_TXNFULL_BITS   0x00000080
#define PIO_IRQ0_INTF_SM3_TXNFULL_MSB    7
#define PIO_IRQ0_INTF_SM3_TXNFULL_LSB    7
#define PIO_IRQ0_INTF_SM3_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM2_TXNFULL
// Description : None
#define PIO_IRQ0_INTF_SM2_TXNFULL_RESET  0x0
#define PIO_IRQ0_INTF_SM2_TXNFULL_BITS   0x00000040
#define PIO_IRQ0_INTF_SM2_TXNFULL_MSB    6
#define PIO_IRQ0_INTF_SM2_TXNFULL_LSB    6
#define PIO_IRQ0_INTF_SM2_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM1_TXNFULL
// Description : None
#define PIO_IRQ0_INTF_SM1_TXNFULL_RESET  0x0
#define PIO_IRQ0_INTF_SM1_TXNFULL_BITS   0x00000020
#define PIO_IRQ0_INTF_SM1_TXNFULL_MSB    5
#define PIO_IRQ0_INTF_SM1_TXNFULL_LSB    5
#define PIO_IRQ0_INTF_SM1_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM0_TXNFULL
// Description : None
#define PIO_IRQ0_INTF_SM0_TXNFULL_RESET  0x0
#define PIO_IRQ0_INTF_SM0_TXNFULL_BITS   0x00000010
#define PIO_IRQ0_INTF_SM0_TXNFULL_MSB    4
#define PIO_IRQ0_INTF_SM0_TXNFULL_LSB    4
#define PIO_IRQ0_INTF_SM0_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM3_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTF_SM3_RXNEMPTY_RESET  0x0
#define PIO_IRQ0_INTF_SM3_RXNEMPTY_BITS   0x00000008
#define PIO_IRQ0_INTF_SM3_RXNEMPTY_MSB    3
#define PIO_IRQ0_INTF_SM3_RXNEMPTY_LSB    3
#define PIO_IRQ0_INTF_SM3_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM2_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTF_SM2_RXNEMPTY_RESET  0x0
#define PIO_IRQ0_INTF_SM2_RXNEMPTY_BITS   0x00000004
#define PIO_IRQ0_INTF_SM2_RXNEMPTY_MSB    2
#define PIO_IRQ0_INTF_SM2_RXNEMPTY_LSB    2
#define PIO_IRQ0_INTF_SM2_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM1_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTF_SM1_RXNEMPTY_RESET  0x0
#define PIO_IRQ0_INTF_SM1_RXNEMPTY_BITS   0x00000002
#define PIO_IRQ0_INTF_SM1_RXNEMPTY_MSB    1
#define PIO_IRQ0_INTF_SM1_RXNEMPTY_LSB    1
#define PIO_IRQ0_INTF_SM1_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM0_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTF_SM0_RXNEMPTY_RESET  0x0
#define PIO_IRQ0_INTF_SM0_RXNEMPTY_BITS   0x00000001
#define PIO_IRQ0_INTF_SM0_RXNEMPTY_MSB    0
#define PIO_IRQ0_INTF_SM0_RXNEMPTY_LSB    0
#define PIO_IRQ0_INTF_SM0_RXNEMPTY_ACCESS "RW"
// =============================================================================
// Register    : PIO_IRQ0_INTS
// Description : Interrupt status after masking & forcing for irq0
#define PIO_IRQ0_INTS_OFFSET 0x00000134
#define PIO_IRQ0_INTS_BITS   0x00000fff
#define PIO_IRQ0_INTS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM3
// Description : None
#define PIO_IRQ0_INTS_SM3_RESET  0x0
#define PIO_IRQ0_INTS_SM3_BITS   0x00000800
#define PIO_IRQ0_INTS_SM3_MSB    11
#define PIO_IRQ0_INTS_SM3_LSB    11
#define PIO_IRQ0_INTS_SM3_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM2
// Description : None
#define PIO_IRQ0_INTS_SM2_RESET  0x0
#define PIO_IRQ0_INTS_SM2_BITS   0x00000400
#define PIO_IRQ0_INTS_SM2_MSB    10
#define PIO_IRQ0_INTS_SM2_LSB    10
#define PIO_IRQ0_INTS_SM2_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM1
// Description : None
#define PIO_IRQ0_INTS_SM1_RESET  0x0
#define PIO_IRQ0_INTS_SM1_BITS   0x00000200
#define PIO_IRQ0_INTS_SM1_MSB    9
#define PIO_IRQ0_INTS_SM1_LSB    9
#define PIO_IRQ0_INTS_SM1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM0
// Description : None
#define PIO_IRQ0_INTS_SM0_RESET  0x0
#define PIO_IRQ0_INTS_SM0_BITS   0x00000100
#define PIO_IRQ0_INTS_SM0_MSB    8
#define PIO_IRQ0_INTS_SM0_LSB    8
#define PIO_IRQ0_INTS_SM0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM3_TXNFULL
// Description : None
#define PIO_IRQ0_INTS_SM3_TXNFULL_RESET  0x0
#define PIO_IRQ0_INTS_SM3_TXNFULL_BITS   0x00000080
#define PIO_IRQ0_INTS_SM3_TXNFULL_MSB    7
#define PIO_IRQ0_INTS_SM3_TXNFULL_LSB    7
#define PIO_IRQ0_INTS_SM3_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM2_TXNFULL
// Description : None
#define PIO_IRQ0_INTS_SM2_TXNFULL_RESET  0x0
#define PIO_IRQ0_INTS_SM2_TXNFULL_BITS   0x00000040
#define PIO_IRQ0_INTS_SM2_TXNFULL_MSB    6
#define PIO_IRQ0_INTS_SM2_TXNFULL_LSB    6
#define PIO_IRQ0_INTS_SM2_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM1_TXNFULL
// Description : None
#define PIO_IRQ0_INTS_SM1_TXNFULL_RESET  0x0
#define PIO_IRQ0_INTS_SM1_TXNFULL_BITS   0x00000020
#define PIO_IRQ0_INTS_SM1_TXNFULL_MSB    5
#define PIO_IRQ0_INTS_SM1_TXNFULL_LSB    5
#define PIO_IRQ0_INTS_SM1_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM0_TXNFULL
// Description : None
#define PIO_IRQ0_INTS_SM0_TXNFULL_RESET  0x0
#define PIO_IRQ0_INTS_SM0_TXNFULL_BITS   0x00000010
#define PIO_IRQ0_INTS_SM0_TXNFULL_MSB    4
#define PIO_IRQ0_INTS_SM0_TXNFULL_LSB    4
#define PIO_IRQ0_INTS_SM0_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM3_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTS_SM3_RXNEMPTY_RESET  0x0
#define PIO_IRQ0_INTS_SM3_RXNEMPTY_BITS   0x00000008
#define PIO_IRQ0_INTS_SM3_RXNEMPTY_MSB    3
#define PIO_IRQ0_INTS_SM3_RXNEMPTY_LSB    3
#define PIO_IRQ0_INTS_SM3_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM2_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTS_SM2_RXNEMPTY_RESET  0x0
#define PIO_IRQ0_INTS_SM2_RXNEMPTY_BITS   0x00000004
#define PIO_IRQ0_INTS_SM2_RXNEMPTY_MSB    2
#define PIO_IRQ0_INTS_SM2_RXNEMPTY_LSB    2
#define PIO_IRQ0_INTS_SM2_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM1_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTS_SM1_RXNEMPTY_RESET  0x0
#define PIO_IRQ0_INTS_SM1_RXNEMPTY_BITS   0x00000002
#define PIO_IRQ0_INTS_SM1_RXNEMPTY_MSB    1
#define PIO_IRQ0_INTS_SM1_RXNEMPTY_LSB    1
#define PIO_IRQ0_INTS_SM1_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM0_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTS_SM0_RXNEMPTY_RESET  0x0
#define PIO_IRQ0_INTS_SM0_RXNEMPTY_BITS   0x00000001
#define PIO_IRQ0_INTS_SM0_RXNEMPTY_MSB    0
#define PIO_IRQ0_INTS_SM0_RXNEMPTY_LSB    0
#define PIO_IRQ0_INTS_SM0_RXNEMPTY_ACCESS "RO"
// =============================================================================
// Register    : PIO_IRQ1_INTE
// Description : Interrupt Enable for irq1
#define PIO_IRQ1_INTE_OFFSET 0x00000138
#define PIO_IRQ1_INTE_BITS   0x00000fff
#define PIO_IRQ1_INTE_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM3
// Description : None
#define PIO_IRQ1_INTE_SM3_RESET  0x0
#define PIO_IRQ1_INTE_SM3_BITS   0x00000800
#define PIO_IRQ1_INTE_SM3_MSB    11
#define PIO_IRQ1_INTE_SM3_LSB    11
#define PIO_IRQ1_INTE_SM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM2
// Description : None
#define PIO_IRQ1_INTE_SM2_RESET  0x0
#define PIO_IRQ1_INTE_SM2_BITS   0x00000400
#define PIO_IRQ1_INTE_SM2_MSB    10
#define PIO_IRQ1_INTE_SM2_LSB    10
#define PIO_IRQ1_INTE_SM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM1
// Description : None
#define PIO_IRQ1_INTE_SM1_RESET  0x0
#define PIO_IRQ1_INTE_SM1_BITS   0x00000200
#define PIO_IRQ1_INTE_SM1_MSB    9
#define PIO_IRQ1_INTE_SM1_LSB    9
#define PIO_IRQ1_INTE_SM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM0
// Description : None
#define PIO_IRQ1_INTE_SM0_RESET  0x0
#define PIO_IRQ1_INTE_SM0_BITS   0x00000100
#define PIO_IRQ1_INTE_SM0_MSB    8
#define PIO_IRQ1_INTE_SM0_LSB    8
#define PIO_IRQ1_INTE_SM0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM3_TXNFULL
// Description : None
#define PIO_IRQ1_INTE_SM3_TXNFULL_RESET  0x0
#define PIO_IRQ1_INTE_SM3_TXNFULL_BITS   0x00000080
#define PIO_IRQ1_INTE_SM3_TXNFULL_MSB    7
#define PIO_IRQ1_INTE_SM3_TXNFULL_LSB    7
#define PIO_IRQ1_INTE_SM3_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM2_TXNFULL
// Description : None
#define PIO_IRQ1_INTE_SM2_TXNFULL_RESET  0x0
#define PIO_IRQ1_INTE_SM2_TXNFULL_BITS   0x00000040
#define PIO_IRQ1_INTE_SM2_TXNFULL_MSB    6
#define PIO_IRQ1_INTE_SM2_TXNFULL_LSB    6
#define PIO_IRQ1_INTE_SM2_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM1_TXNFULL
// Description : None
#define PIO_IRQ1_INTE_SM1_TXNFULL_RESET  0x0
#define PIO_IRQ1_INTE_SM1_TXNFULL_BITS   0x00000020
#define PIO_IRQ1_INTE_SM1_TXNFULL_MSB    5
#define PIO_IRQ1_INTE_SM1_TXNFULL_LSB    5
#define PIO_IRQ1_INTE_SM1_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM0_TXNFULL
// Description : None
#define PIO_IRQ1_INTE_SM0_TXNFULL_RESET  0x0
#define PIO_IRQ1_INTE_SM0_TXNFULL_BITS   0x00000010
#define PIO_IRQ1_INTE_SM0_TXNFULL_MSB    4
#define PIO_IRQ1_INTE_SM0_TXNFULL_LSB    4
#define PIO_IRQ1_INTE_SM0_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM3_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTE_SM3_RXNEMPTY_RESET  0x0
#define PIO_IRQ1_INTE_SM3_RXNEMPTY_BITS   0x00000008
#define PIO_IRQ1_INTE_SM3_RXNEMPTY_MSB    3
#define PIO_IRQ1_INTE_SM3_RXNEMPTY_LSB    3
#define PIO_IRQ1_INTE_SM3_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM2_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTE_SM2_RXNEMPTY_RESET  0x0
#define PIO_IRQ1_INTE_SM2_RXNEMPTY_BITS   0x00000004
#define PIO_IRQ1_INTE_SM2_RXNEMPTY_MSB    2
#define PIO_IRQ1_INTE_SM2_RXNEMPTY_LSB    2
#define PIO_IRQ1_INTE_SM2_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM1_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTE_SM1_RXNEMPTY_RESET  0x0
#define PIO_IRQ1_INTE_SM1_RXNEMPTY_BITS   0x00000002
#define PIO_IRQ1_INTE_SM1_RXNEMPTY_MSB    1
#define PIO_IRQ1_INTE_SM1_RXNEMPTY_LSB    1
#define PIO_IRQ1_INTE_SM1_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM0_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTE_SM0_RXNEMPTY_RESET  0x0
#define PIO_IRQ1_INTE_SM0_RXNEMPTY_BITS   0x00000001
#define PIO_IRQ1_INTE_SM0_RXNEMPTY_MSB    0
#define PIO_IRQ1_INTE_SM0_RXNEMPTY_LSB    0
#define PIO_IRQ1_INTE_SM0_RXNEMPTY_ACCESS "RW"
// =============================================================================
// Register    : PIO_IRQ1_INTF
// Description : Interrupt Force for irq1
#define PIO_IRQ1_INTF_OFFSET 0x0000013c
#define PIO_IRQ1_INTF_BITS   0x00000fff
#define PIO_IRQ1_INTF_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM3
// Description : None
#define PIO_IRQ1_INTF_SM3_RESET  0x0
#define PIO_IRQ1_INTF_SM3_BITS   0x00000800
#define PIO_IRQ1_INTF_SM3_MSB    11
#define PIO_IRQ1_INTF_SM3_LSB    11
#define PIO_IRQ1_INTF_SM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM2
// Description : None
#define PIO_IRQ1_INTF_SM2_RESET  0x0
#define PIO_IRQ1_INTF_SM2_BITS   0x00000400
#define PIO_IRQ1_INTF_SM2_MSB    10
#define PIO_IRQ1_INTF_SM2_LSB    10
#define PIO_IRQ1_INTF_SM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM1
// Description : None
#define PIO_IRQ1_INTF_SM1_RESET  0x0
#define PIO_IRQ1_INTF_SM1_BITS   0x00000200
#define PIO_IRQ1_INTF_SM1_MSB    9
#define PIO_IRQ1_INTF_SM1_LSB    9
#define PIO_IRQ1_INTF_SM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM0
// Description : None
#define PIO_IRQ1_INTF_SM0_RESET  0x0
#define PIO_IRQ1_INTF_SM0_BITS   0x00000100
#define PIO_IRQ1_INTF_SM0_MSB    8
#define PIO_IRQ1_INTF_SM0_LSB    8
#define PIO_IRQ1_INTF_SM0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM3_TXNFULL
// Description : None
#define PIO_IRQ1_INTF_SM3_TXNFULL_RESET  0x0
#define PIO_IRQ1_INTF_SM3_TXNFULL_BITS   0x00000080
#define PIO_IRQ1_INTF_SM3_TXNFULL_MSB    7
#define PIO_IRQ1_INTF_SM3_TXNFULL_LSB    7
#define PIO_IRQ1_INTF_SM3_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM2_TXNFULL
// Description : None
#define PIO_IRQ1_INTF_SM2_TXNFULL_RESET  0x0
#define PIO_IRQ1_INTF_SM2_TXNFULL_BITS   0x00000040
#define PIO_IRQ1_INTF_SM2_TXNFULL_MSB    6
#define PIO_IRQ1_INTF_SM2_TXNFULL_LSB    6
#define PIO_IRQ1_INTF_SM2_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM1_TXNFULL
// Description : None
#define PIO_IRQ1_INTF_SM1_TXNFULL_RESET  0x0
#define PIO_IRQ1_INTF_SM1_TXNFULL_BITS   0x00000020
#define PIO_IRQ1_INTF_SM1_TXNFULL_MSB    5
#define PIO_IRQ1_INTF_SM1_TXNFULL_LSB    5
#define PIO_IRQ1_INTF_SM1_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM0_TXNFULL
// Description : None
#define PIO_IRQ1_INTF_SM0_TXNFULL_RESET  0x0
#define PIO_IRQ1_INTF_SM0_TXNFULL_BITS   0x00000010
#define PIO_IRQ1_INTF_SM0_TXNFULL_MSB    4
#define PIO_IRQ1_INTF_SM0_TXNFULL_LSB    4
#define PIO_IRQ1_INTF_SM0_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM3_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTF_SM3_RXNEMPTY_RESET  0x0
#define PIO_IRQ1_INTF_SM3_RXNEMPTY_BITS   0x00000008
#define PIO_IRQ1_INTF_SM3_RXNEMPTY_MSB    3
#define PIO_IRQ1_INTF_SM3_RXNEMPTY_LSB    3
#define PIO_IRQ1_INTF_SM3_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM2_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTF_SM2_RXNEMPTY_RESET  0x0
#define PIO_IRQ1_INTF_SM2_RXNEMPTY_BITS   0x00000004
#define PIO_IRQ1_INTF_SM2_RXNEMPTY_MSB    2
#define PIO_IRQ1_INTF_SM2_RXNEMPTY_LSB    2
#define PIO_IRQ1_INTF_SM2_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM1_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTF_SM1_RXNEMPTY_RESET  0x0
#define PIO_IRQ1_INTF_SM1_RXNEMPTY_BITS   0x00000002
#define PIO_IRQ1_INTF_SM1_RXNEMPTY_MSB    1
#define PIO_IRQ1_INTF_SM1_RXNEMPTY_LSB    1
#define PIO_IRQ1_INTF_SM1_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM0_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTF_SM0_RXNEMPTY_RESET  0x0
#define PIO_IRQ1_INTF_SM0_RXNEMPTY_BITS   0x00000001
#define PIO_IRQ1_INTF_SM0_RXNEMPTY_MSB    0
#define PIO_IRQ1_INTF_SM0_RXNEMPTY_LSB    0
#define PIO_IRQ1_INTF_SM0_RXNEMPTY_ACCESS "RW"
// =============================================================================
// Register    : PIO_IRQ1_INTS
// Description : Interrupt status after masking & forcing for irq1
#define PIO_IRQ1_INTS_OFFSET 0x00000140
#define PIO_IRQ1_INTS_BITS   0x00000fff
#define PIO_IRQ1_INTS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM3
// Description : None
#define PIO_IRQ1_INTS_SM3_RESET  0x0
#define PIO_IRQ1_INTS_SM3_BITS   0x00000800
#define PIO_IRQ1_INTS_SM3_MSB    11
#define PIO_IRQ1_INTS_SM3_LSB    11
#define PIO_IRQ1_INTS_SM3_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM2
// Description : None
#define PIO_IRQ1_INTS_SM2_RESET  0x0
#define PIO_IRQ1_INTS_SM2_BITS   0x00000400
#define PIO_IRQ1_INTS_SM2_MSB    10
#define PIO_IRQ1_INTS_SM2_LSB    10
#define PIO_IRQ1_INTS_SM2_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM1
// Description : None
#define PIO_IRQ1_INTS_SM1_RESET  0x0
#define PIO_IRQ1_INTS_SM1_BITS   0x00000200
#define PIO_IRQ1_INTS_SM1_MSB    9
#define PIO_IRQ1_INTS_SM1_LSB    9
#define PIO_IRQ1_INTS_SM1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM0
// Description : None
#define PIO_IRQ1_INTS_SM0_RESET  0x0
#define PIO_IRQ1_INTS_SM0_BITS   0x00000100
#define PIO_IRQ1_INTS_SM0_MSB    8
#define PIO_IRQ1_INTS_SM0_LSB    8
#define PIO_IRQ1_INTS_SM0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM3_TXNFULL
// Description : None
#define PIO_IRQ1_INTS_SM3_TXNFULL_RESET  0x0
#define PIO_IRQ1_INTS_SM3_TXNFULL_BITS   0x00000080
#define PIO_IRQ1_INTS_SM3_TXNFULL_MSB    7
#define PIO_IRQ1_INTS_SM3_TXNFULL_LSB    7
#define PIO_IRQ1_INTS_SM3_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM2_TXNFULL
// Description : None
#define PIO_IRQ1_INTS_SM2_TXNFULL_RESET  0x0
#define PIO_IRQ1_INTS_SM2_TXNFULL_BITS   0x00000040
#define PIO_IRQ1_INTS_SM2_TXNFULL_MSB    6
#define PIO_IRQ1_INTS_SM2_TXNFULL_LSB    6
#define PIO_IRQ1_INTS_SM2_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM1_TXNFULL
// Description : None
#define PIO_IRQ1_INTS_SM1_TXNFULL_RESET  0x0
#define PIO_IRQ1_INTS_SM1_TXNFULL_BITS   0x00000020
#define PIO_IRQ1_INTS_SM1_TXNFULL_MSB    5
#define PIO_IRQ1_INTS_SM1_TXNFULL_LSB    5
#define PIO_IRQ1_INTS_SM1_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM0_TXNFULL
// Description : None
#define PIO_IRQ1_INTS_SM0_TXNFULL_RESET  0x0
#define PIO_IRQ1_INTS_SM0_TXNFULL_BITS   0x00000010
#define PIO_IRQ1_INTS_SM0_TXNFULL_MSB    4
#define PIO_IRQ1_INTS_SM0_TXNFULL_LSB    4
#define PIO_IRQ1_INTS_SM0_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM3_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTS_SM3_RXNEMPTY_RESET  0x0
#define PIO_IRQ1_INTS_SM3_RXNEMPTY_BITS   0x00000008
#define PIO_IRQ1_INTS_SM3_RXNEMPTY_MSB    3
#define PIO_IRQ1_INTS_SM3_RXNEMPTY_LSB    3
#define PIO_IRQ1_INTS_SM3_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM2_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTS_SM2_RXNEMPTY_RESET  0x0
#define PIO_IRQ1_INTS_SM2_RXNEMPTY_BITS   0x00000004
#define PIO_IRQ1_INTS_SM2_RXNEMPTY_MSB    2
#define PIO_IRQ1_INTS_SM2_RXNEMPTY_LSB    2
#define PIO_IRQ1_INTS_SM2_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM1_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTS_SM1_RXNEMPTY_RESET  0x0
#define PIO_IRQ1_INTS_SM1_RXNEMPTY_BITS   0x00000002
#define PIO_IRQ1_INTS_SM1_RXNEMPTY_MSB    1
#define PIO_IRQ1_INTS_SM1_RXNEMPTY_LSB    1
#define PIO_IRQ1_INTS_SM1_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM0_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTS_SM0_RXNEMPTY_RESET  0x0
#define PIO_IRQ1_INTS_SM0_RXNEMPTY_BITS   0x00000001
#define PIO_IRQ1_INTS_SM0_RXNEMPTY_MSB    0
#define PIO_IRQ1_INTS_SM0_RXNEMPTY_LSB    0
#define PIO_IRQ1_INTS_SM0_RXNEMPTY_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_PIO_DEFINED
