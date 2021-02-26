/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : ROSC
// Version        : 1
// Bus type       : apb
// Description    : None
// =============================================================================
#ifndef HARDWARE_REGS_ROSC_DEFINED
#define HARDWARE_REGS_ROSC_DEFINED
// =============================================================================
// Register    : ROSC_CTRL
// Description : Ring Oscillator control
#define ROSC_CTRL_OFFSET 0x00000000
#define ROSC_CTRL_BITS   0x00ffffff
#define ROSC_CTRL_RESET  0x00000aa0
// -----------------------------------------------------------------------------
// Field       : ROSC_CTRL_ENABLE
// Description : On power-up this field is initialised to ENABLE
//               The system clock must be switched to another source before
//               setting this field to DISABLE otherwise the chip will lock up
//               The 12-bit code is intended to give some protection against
//               accidental writes. An invalid setting will enable the
//               oscillator.
//               0xd1e -> DISABLE
//               0xfab -> ENABLE
#define ROSC_CTRL_ENABLE_RESET         "-"
#define ROSC_CTRL_ENABLE_BITS          0x00fff000
#define ROSC_CTRL_ENABLE_MSB           23
#define ROSC_CTRL_ENABLE_LSB           12
#define ROSC_CTRL_ENABLE_ACCESS        "RW"
#define ROSC_CTRL_ENABLE_VALUE_DISABLE 0xd1e
#define ROSC_CTRL_ENABLE_VALUE_ENABLE  0xfab
// -----------------------------------------------------------------------------
// Field       : ROSC_CTRL_FREQ_RANGE
// Description : Controls the number of delay stages in the ROSC ring
//               LOW uses stages 0 to 7
//               MEDIUM uses stages 0 to 5
//               HIGH uses stages 0 to 3
//               TOOHIGH uses stages 0 to 1 and should not be used because its
//               frequency exceeds design specifications
//               The clock output will not glitch when changing the range up one
//               step at a time
//               The clock output will glitch when changing the range down
//               Note: the values here are gray coded which is why HIGH comes
//               before TOOHIGH
//               0xfa4 -> LOW
//               0xfa5 -> MEDIUM
//               0xfa7 -> HIGH
//               0xfa6 -> TOOHIGH
#define ROSC_CTRL_FREQ_RANGE_RESET         0xaa0
#define ROSC_CTRL_FREQ_RANGE_BITS          0x00000fff
#define ROSC_CTRL_FREQ_RANGE_MSB           11
#define ROSC_CTRL_FREQ_RANGE_LSB           0
#define ROSC_CTRL_FREQ_RANGE_ACCESS        "RW"
#define ROSC_CTRL_FREQ_RANGE_VALUE_LOW     0xfa4
#define ROSC_CTRL_FREQ_RANGE_VALUE_MEDIUM  0xfa5
#define ROSC_CTRL_FREQ_RANGE_VALUE_HIGH    0xfa7
#define ROSC_CTRL_FREQ_RANGE_VALUE_TOOHIGH 0xfa6
// =============================================================================
// Register    : ROSC_FREQA
// Description : The FREQA & FREQB registers control the frequency by
//               controlling the drive strength of each stage
//               The drive strength has 4 levels determined by the number of
//               bits set
//               Increasing the number of bits set increases the drive strength
//               and increases the oscillation frequency
//               0 bits set is the default drive strength
//               1 bit set doubles the drive strength
//               2 bits set triples drive strength
//               3 bits set quadruples drive strength
#define ROSC_FREQA_OFFSET 0x00000004
#define ROSC_FREQA_BITS   0xffff7777
#define ROSC_FREQA_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : ROSC_FREQA_PASSWD
// Description : Set to 0x9696 to apply the settings
//               Any other value in this field will set all drive strengths to 0
//               0x9696 -> PASS
#define ROSC_FREQA_PASSWD_RESET      0x0000
#define ROSC_FREQA_PASSWD_BITS       0xffff0000
#define ROSC_FREQA_PASSWD_MSB        31
#define ROSC_FREQA_PASSWD_LSB        16
#define ROSC_FREQA_PASSWD_ACCESS     "RW"
#define ROSC_FREQA_PASSWD_VALUE_PASS 0x9696
// -----------------------------------------------------------------------------
// Field       : ROSC_FREQA_DS3
// Description : Stage 3 drive strength
#define ROSC_FREQA_DS3_RESET  0x0
#define ROSC_FREQA_DS3_BITS   0x00007000
#define ROSC_FREQA_DS3_MSB    14
#define ROSC_FREQA_DS3_LSB    12
#define ROSC_FREQA_DS3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ROSC_FREQA_DS2
// Description : Stage 2 drive strength
#define ROSC_FREQA_DS2_RESET  0x0
#define ROSC_FREQA_DS2_BITS   0x00000700
#define ROSC_FREQA_DS2_MSB    10
#define ROSC_FREQA_DS2_LSB    8
#define ROSC_FREQA_DS2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ROSC_FREQA_DS1
// Description : Stage 1 drive strength
#define ROSC_FREQA_DS1_RESET  0x0
#define ROSC_FREQA_DS1_BITS   0x00000070
#define ROSC_FREQA_DS1_MSB    6
#define ROSC_FREQA_DS1_LSB    4
#define ROSC_FREQA_DS1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ROSC_FREQA_DS0
// Description : Stage 0 drive strength
#define ROSC_FREQA_DS0_RESET  0x0
#define ROSC_FREQA_DS0_BITS   0x00000007
#define ROSC_FREQA_DS0_MSB    2
#define ROSC_FREQA_DS0_LSB    0
#define ROSC_FREQA_DS0_ACCESS "RW"
// =============================================================================
// Register    : ROSC_FREQB
// Description : For a detailed description see freqa register
#define ROSC_FREQB_OFFSET 0x00000008
#define ROSC_FREQB_BITS   0xffff7777
#define ROSC_FREQB_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : ROSC_FREQB_PASSWD
// Description : Set to 0x9696 to apply the settings
//               Any other value in this field will set all drive strengths to 0
//               0x9696 -> PASS
#define ROSC_FREQB_PASSWD_RESET      0x0000
#define ROSC_FREQB_PASSWD_BITS       0xffff0000
#define ROSC_FREQB_PASSWD_MSB        31
#define ROSC_FREQB_PASSWD_LSB        16
#define ROSC_FREQB_PASSWD_ACCESS     "RW"
#define ROSC_FREQB_PASSWD_VALUE_PASS 0x9696
// -----------------------------------------------------------------------------
// Field       : ROSC_FREQB_DS7
// Description : Stage 7 drive strength
#define ROSC_FREQB_DS7_RESET  0x0
#define ROSC_FREQB_DS7_BITS   0x00007000
#define ROSC_FREQB_DS7_MSB    14
#define ROSC_FREQB_DS7_LSB    12
#define ROSC_FREQB_DS7_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ROSC_FREQB_DS6
// Description : Stage 6 drive strength
#define ROSC_FREQB_DS6_RESET  0x0
#define ROSC_FREQB_DS6_BITS   0x00000700
#define ROSC_FREQB_DS6_MSB    10
#define ROSC_FREQB_DS6_LSB    8
#define ROSC_FREQB_DS6_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ROSC_FREQB_DS5
// Description : Stage 5 drive strength
#define ROSC_FREQB_DS5_RESET  0x0
#define ROSC_FREQB_DS5_BITS   0x00000070
#define ROSC_FREQB_DS5_MSB    6
#define ROSC_FREQB_DS5_LSB    4
#define ROSC_FREQB_DS5_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ROSC_FREQB_DS4
// Description : Stage 4 drive strength
#define ROSC_FREQB_DS4_RESET  0x0
#define ROSC_FREQB_DS4_BITS   0x00000007
#define ROSC_FREQB_DS4_MSB    2
#define ROSC_FREQB_DS4_LSB    0
#define ROSC_FREQB_DS4_ACCESS "RW"
// =============================================================================
// Register    : ROSC_DORMANT
// Description : Ring Oscillator pause control
//               This is used to save power by pausing the ROSC
//               On power-up this field is initialised to WAKE
//               An invalid write will also select WAKE
//               Warning: setup the irq before selecting dormant mode
//               0x636f6d61 -> DORMANT
//               0x77616b65 -> WAKE
#define ROSC_DORMANT_OFFSET        0x0000000c
#define ROSC_DORMANT_BITS          0xffffffff
#define ROSC_DORMANT_RESET         "-"
#define ROSC_DORMANT_MSB           31
#define ROSC_DORMANT_LSB           0
#define ROSC_DORMANT_ACCESS        "RW"
#define ROSC_DORMANT_VALUE_DORMANT 0x636f6d61
#define ROSC_DORMANT_VALUE_WAKE    0x77616b65
// =============================================================================
// Register    : ROSC_DIV
// Description : Controls the output divider
//               set to 0xaa0 + div where
//               div = 0 divides by 32
//               div = 1-31 divides by div
//               any other value sets div=0 and therefore divides by 32
//               this register resets to div=16
//               0xaa0 -> PASS
#define ROSC_DIV_OFFSET     0x00000010
#define ROSC_DIV_BITS       0x00000fff
#define ROSC_DIV_RESET      "-"
#define ROSC_DIV_MSB        11
#define ROSC_DIV_LSB        0
#define ROSC_DIV_ACCESS     "RW"
#define ROSC_DIV_VALUE_PASS 0xaa0
// =============================================================================
// Register    : ROSC_PHASE
// Description : Controls the phase shifted output
#define ROSC_PHASE_OFFSET 0x00000014
#define ROSC_PHASE_BITS   0x00000fff
#define ROSC_PHASE_RESET  0x00000008
// -----------------------------------------------------------------------------
// Field       : ROSC_PHASE_PASSWD
// Description : set to 0xaa0
//               any other value enables the output with shift=0
#define ROSC_PHASE_PASSWD_RESET  0x00
#define ROSC_PHASE_PASSWD_BITS   0x00000ff0
#define ROSC_PHASE_PASSWD_MSB    11
#define ROSC_PHASE_PASSWD_LSB    4
#define ROSC_PHASE_PASSWD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ROSC_PHASE_ENABLE
// Description : enable the phase-shifted output
//               this can be changed on-the-fly
#define ROSC_PHASE_ENABLE_RESET  0x1
#define ROSC_PHASE_ENABLE_BITS   0x00000008
#define ROSC_PHASE_ENABLE_MSB    3
#define ROSC_PHASE_ENABLE_LSB    3
#define ROSC_PHASE_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ROSC_PHASE_FLIP
// Description : invert the phase-shifted output
//               this is ignored when div=1
#define ROSC_PHASE_FLIP_RESET  0x0
#define ROSC_PHASE_FLIP_BITS   0x00000004
#define ROSC_PHASE_FLIP_MSB    2
#define ROSC_PHASE_FLIP_LSB    2
#define ROSC_PHASE_FLIP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ROSC_PHASE_SHIFT
// Description : phase shift the phase-shifted output by SHIFT input clocks
//               this can be changed on-the-fly
//               must be set to 0 before setting div=1
#define ROSC_PHASE_SHIFT_RESET  0x0
#define ROSC_PHASE_SHIFT_BITS   0x00000003
#define ROSC_PHASE_SHIFT_MSB    1
#define ROSC_PHASE_SHIFT_LSB    0
#define ROSC_PHASE_SHIFT_ACCESS "RW"
// =============================================================================
// Register    : ROSC_STATUS
// Description : Ring Oscillator Status
#define ROSC_STATUS_OFFSET 0x00000018
#define ROSC_STATUS_BITS   0x81011000
#define ROSC_STATUS_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : ROSC_STATUS_STABLE
// Description : Oscillator is running and stable
#define ROSC_STATUS_STABLE_RESET  0x0
#define ROSC_STATUS_STABLE_BITS   0x80000000
#define ROSC_STATUS_STABLE_MSB    31
#define ROSC_STATUS_STABLE_LSB    31
#define ROSC_STATUS_STABLE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : ROSC_STATUS_BADWRITE
// Description : An invalid value has been written to CTRL_ENABLE or
//               CTRL_FREQ_RANGE or FRFEQA or FREQB or DORMANT
#define ROSC_STATUS_BADWRITE_RESET  0x0
#define ROSC_STATUS_BADWRITE_BITS   0x01000000
#define ROSC_STATUS_BADWRITE_MSB    24
#define ROSC_STATUS_BADWRITE_LSB    24
#define ROSC_STATUS_BADWRITE_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : ROSC_STATUS_DIV_RUNNING
// Description : post-divider is running
//               this resets to 0 but transitions to 1 during chip startup
#define ROSC_STATUS_DIV_RUNNING_RESET  "-"
#define ROSC_STATUS_DIV_RUNNING_BITS   0x00010000
#define ROSC_STATUS_DIV_RUNNING_MSB    16
#define ROSC_STATUS_DIV_RUNNING_LSB    16
#define ROSC_STATUS_DIV_RUNNING_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : ROSC_STATUS_ENABLED
// Description : Oscillator is enabled but not necessarily running and stable
//               this resets to 0 but transitions to 1 during chip startup
#define ROSC_STATUS_ENABLED_RESET  "-"
#define ROSC_STATUS_ENABLED_BITS   0x00001000
#define ROSC_STATUS_ENABLED_MSB    12
#define ROSC_STATUS_ENABLED_LSB    12
#define ROSC_STATUS_ENABLED_ACCESS "RO"
// =============================================================================
// Register    : ROSC_RANDOMBIT
// Description : This just reads the state of the oscillator output so
//               randomness is compromised if the ring oscillator is stopped or
//               run at a harmonic of the bus frequency
#define ROSC_RANDOMBIT_OFFSET 0x0000001c
#define ROSC_RANDOMBIT_BITS   0x00000001
#define ROSC_RANDOMBIT_RESET  0x00000001
#define ROSC_RANDOMBIT_MSB    0
#define ROSC_RANDOMBIT_LSB    0
#define ROSC_RANDOMBIT_ACCESS "RO"
// =============================================================================
// Register    : ROSC_COUNT
// Description : A down counter running at the ROSC frequency which counts to
//               zero and stops.
//               To start the counter write a non-zero value.
//               Can be used for short software pauses when setting up time
//               sensitive hardware.
#define ROSC_COUNT_OFFSET 0x00000020
#define ROSC_COUNT_BITS   0x000000ff
#define ROSC_COUNT_RESET  0x00000000
#define ROSC_COUNT_MSB    7
#define ROSC_COUNT_LSB    0
#define ROSC_COUNT_ACCESS "RW"
// =============================================================================
#endif // HARDWARE_REGS_ROSC_DEFINED
