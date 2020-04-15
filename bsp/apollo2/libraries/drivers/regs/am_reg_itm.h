//*****************************************************************************
//
//  am_reg_itm.h
//! @file
//!
//! @brief Register macros for the ITM module
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************
#ifndef AM_REG_ITM_H
#define AM_REG_ITM_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_ITM_NUM_MODULES                       1
#define AM_REG_ITMn(n) \
    (REG_ITM_BASEADDR + 0x00000000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_ITM_STIM0_O                           0xE0000000
#define AM_REG_ITM_STIM1_O                           0xE0000004
#define AM_REG_ITM_STIM2_O                           0xE0000008
#define AM_REG_ITM_STIM3_O                           0xE000000C
#define AM_REG_ITM_STIM4_O                           0xE0000010
#define AM_REG_ITM_STIM5_O                           0xE0000014
#define AM_REG_ITM_STIM6_O                           0xE0000018
#define AM_REG_ITM_STIM7_O                           0xE000001C
#define AM_REG_ITM_STIM8_O                           0xE0000020
#define AM_REG_ITM_STIM9_O                           0xE0000024
#define AM_REG_ITM_STIM10_O                          0xE0000028
#define AM_REG_ITM_STIM11_O                          0xE000002C
#define AM_REG_ITM_STIM12_O                          0xE0000030
#define AM_REG_ITM_STIM13_O                          0xE0000034
#define AM_REG_ITM_STIM14_O                          0xE0000038
#define AM_REG_ITM_STIM15_O                          0xE000003C
#define AM_REG_ITM_STIM16_O                          0xE0000040
#define AM_REG_ITM_STIM17_O                          0xE0000044
#define AM_REG_ITM_STIM18_O                          0xE0000048
#define AM_REG_ITM_STIM19_O                          0xE000004C
#define AM_REG_ITM_STIM20_O                          0xE0000050
#define AM_REG_ITM_STIM21_O                          0xE0000054
#define AM_REG_ITM_STIM22_O                          0xE0000058
#define AM_REG_ITM_STIM23_O                          0xE000005C
#define AM_REG_ITM_STIM24_O                          0xE0000060
#define AM_REG_ITM_STIM25_O                          0xE0000064
#define AM_REG_ITM_STIM26_O                          0xE0000068
#define AM_REG_ITM_STIM27_O                          0xE000006C
#define AM_REG_ITM_STIM28_O                          0xE0000070
#define AM_REG_ITM_STIM29_O                          0xE0000074
#define AM_REG_ITM_STIM30_O                          0xE0000078
#define AM_REG_ITM_STIM31_O                          0xE000007C
#define AM_REG_ITM_TER_O                             0xE0000E00
#define AM_REG_ITM_TPR_O                             0xE0000E40
#define AM_REG_ITM_TCR_O                             0xE0000E80
#define AM_REG_ITM_LOCKSREG_O                        0xE0000FB4
#define AM_REG_ITM_PID4_O                            0xE0000FD0
#define AM_REG_ITM_PID5_O                            0xE0000FD4
#define AM_REG_ITM_PID6_O                            0xE0000FD8
#define AM_REG_ITM_PID7_O                            0xE0000FDC
#define AM_REG_ITM_PID0_O                            0xE0000FE0
#define AM_REG_ITM_PID1_O                            0xE0000FE4
#define AM_REG_ITM_PID2_O                            0xE0000FE8
#define AM_REG_ITM_PID3_O                            0xE0000FEC
#define AM_REG_ITM_CID0_O                            0xE0000FF0
#define AM_REG_ITM_CID1_O                            0xE0000FF4
#define AM_REG_ITM_CID2_O                            0xE0000FF8
#define AM_REG_ITM_CID3_O                            0xE0000FFC
#define AM_REG_ITM_LOCKAREG_O                        0xE0000FB0

//*****************************************************************************
//
// Key values.
//
//*****************************************************************************
#define AM_REG_ITM_LOCKAREG_KEYVAL                   0xC5ACCE55

//*****************************************************************************
//
// ITM_STIM0 - Stimulus Port Register 0
//
//*****************************************************************************
// Stimulus Port Register 0.
#define AM_REG_ITM_STIM0_STIM0_S                     0
#define AM_REG_ITM_STIM0_STIM0_M                     0xFFFFFFFF
#define AM_REG_ITM_STIM0_STIM0(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM1 - Stimulus Port Register 1
//
//*****************************************************************************
// Stimulus Port Register 1.
#define AM_REG_ITM_STIM1_STIM1_S                     0
#define AM_REG_ITM_STIM1_STIM1_M                     0xFFFFFFFF
#define AM_REG_ITM_STIM1_STIM1(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM2 - Stimulus Port Register 2
//
//*****************************************************************************
// Stimulus Port Register 2.
#define AM_REG_ITM_STIM2_STIM2_S                     0
#define AM_REG_ITM_STIM2_STIM2_M                     0xFFFFFFFF
#define AM_REG_ITM_STIM2_STIM2(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM3 - Stimulus Port Register 3
//
//*****************************************************************************
// Stimulus Port Register 3.
#define AM_REG_ITM_STIM3_STIM3_S                     0
#define AM_REG_ITM_STIM3_STIM3_M                     0xFFFFFFFF
#define AM_REG_ITM_STIM3_STIM3(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM4 - Stimulus Port Register 4
//
//*****************************************************************************
// Stimulus Port Register 4.
#define AM_REG_ITM_STIM4_STIM4_S                     0
#define AM_REG_ITM_STIM4_STIM4_M                     0xFFFFFFFF
#define AM_REG_ITM_STIM4_STIM4(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM5 - Stimulus Port Register 5
//
//*****************************************************************************
// Stimulus Port Register 5.
#define AM_REG_ITM_STIM5_STIM5_S                     0
#define AM_REG_ITM_STIM5_STIM5_M                     0xFFFFFFFF
#define AM_REG_ITM_STIM5_STIM5(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM6 - Stimulus Port Register 6
//
//*****************************************************************************
// Stimulus Port Register 6.
#define AM_REG_ITM_STIM6_STIM6_S                     0
#define AM_REG_ITM_STIM6_STIM6_M                     0xFFFFFFFF
#define AM_REG_ITM_STIM6_STIM6(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM7 - Stimulus Port Register 7
//
//*****************************************************************************
// Stimulus Port Register 7.
#define AM_REG_ITM_STIM7_STIM7_S                     0
#define AM_REG_ITM_STIM7_STIM7_M                     0xFFFFFFFF
#define AM_REG_ITM_STIM7_STIM7(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM8 - Stimulus Port Register 8
//
//*****************************************************************************
// Stimulus Port Register 8.
#define AM_REG_ITM_STIM8_STIM8_S                     0
#define AM_REG_ITM_STIM8_STIM8_M                     0xFFFFFFFF
#define AM_REG_ITM_STIM8_STIM8(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM9 - Stimulus Port Register 9
//
//*****************************************************************************
// Stimulus Port Register 9.
#define AM_REG_ITM_STIM9_STIM9_S                     0
#define AM_REG_ITM_STIM9_STIM9_M                     0xFFFFFFFF
#define AM_REG_ITM_STIM9_STIM9(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM10 - Stimulus Port Register 10
//
//*****************************************************************************
// Stimulus Port Register 10.
#define AM_REG_ITM_STIM10_STIM10_S                   0
#define AM_REG_ITM_STIM10_STIM10_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM10_STIM10(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM11 - Stimulus Port Register 11
//
//*****************************************************************************
// Stimulus Port Register 11.
#define AM_REG_ITM_STIM11_STIM11_S                   0
#define AM_REG_ITM_STIM11_STIM11_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM11_STIM11(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM12 - Stimulus Port Register 12
//
//*****************************************************************************
// Stimulus Port Register 12.
#define AM_REG_ITM_STIM12_STIM12_S                   0
#define AM_REG_ITM_STIM12_STIM12_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM12_STIM12(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM13 - Stimulus Port Register 13
//
//*****************************************************************************
// Stimulus Port Register 13.
#define AM_REG_ITM_STIM13_STIM13_S                   0
#define AM_REG_ITM_STIM13_STIM13_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM13_STIM13(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM14 - Stimulus Port Register 14
//
//*****************************************************************************
// Stimulus Port Register 14.
#define AM_REG_ITM_STIM14_STIM14_S                   0
#define AM_REG_ITM_STIM14_STIM14_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM14_STIM14(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM15 - Stimulus Port Register 15
//
//*****************************************************************************
// Stimulus Port Register 15.
#define AM_REG_ITM_STIM15_STIM15_S                   0
#define AM_REG_ITM_STIM15_STIM15_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM15_STIM15(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM16 - Stimulus Port Register 16
//
//*****************************************************************************
// Stimulus Port Register 16.
#define AM_REG_ITM_STIM16_STIM16_S                   0
#define AM_REG_ITM_STIM16_STIM16_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM16_STIM16(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM17 - Stimulus Port Register 17
//
//*****************************************************************************
// Stimulus Port Register 17.
#define AM_REG_ITM_STIM17_STIM17_S                   0
#define AM_REG_ITM_STIM17_STIM17_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM17_STIM17(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM18 - Stimulus Port Register 18
//
//*****************************************************************************
// Stimulus Port Register 18.
#define AM_REG_ITM_STIM18_STIM18_S                   0
#define AM_REG_ITM_STIM18_STIM18_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM18_STIM18(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM19 - Stimulus Port Register 19
//
//*****************************************************************************
// Stimulus Port Register 19.
#define AM_REG_ITM_STIM19_STIM19_S                   0
#define AM_REG_ITM_STIM19_STIM19_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM19_STIM19(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM20 - Stimulus Port Register 20
//
//*****************************************************************************
// Stimulus Port Register 20.
#define AM_REG_ITM_STIM20_STIM20_S                   0
#define AM_REG_ITM_STIM20_STIM20_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM20_STIM20(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM21 - Stimulus Port Register 21
//
//*****************************************************************************
// Stimulus Port Register 21.
#define AM_REG_ITM_STIM21_STIM21_S                   0
#define AM_REG_ITM_STIM21_STIM21_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM21_STIM21(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM22 - Stimulus Port Register 22
//
//*****************************************************************************
// Stimulus Port Register 22.
#define AM_REG_ITM_STIM22_STIM22_S                   0
#define AM_REG_ITM_STIM22_STIM22_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM22_STIM22(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM23 - Stimulus Port Register 23
//
//*****************************************************************************
// Stimulus Port Register 23.
#define AM_REG_ITM_STIM23_STIM23_S                   0
#define AM_REG_ITM_STIM23_STIM23_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM23_STIM23(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM24 - Stimulus Port Register 24
//
//*****************************************************************************
// Stimulus Port Register 24.
#define AM_REG_ITM_STIM24_STIM24_S                   0
#define AM_REG_ITM_STIM24_STIM24_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM24_STIM24(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM25 - Stimulus Port Register 25
//
//*****************************************************************************
// Stimulus Port Register 25.
#define AM_REG_ITM_STIM25_STIM25_S                   0
#define AM_REG_ITM_STIM25_STIM25_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM25_STIM25(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM26 - Stimulus Port Register 26
//
//*****************************************************************************
// Stimulus Port Register 26.
#define AM_REG_ITM_STIM26_STIM26_S                   0
#define AM_REG_ITM_STIM26_STIM26_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM26_STIM26(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM27 - Stimulus Port Register 27
//
//*****************************************************************************
// Stimulus Port Register 27.
#define AM_REG_ITM_STIM27_STIM27_S                   0
#define AM_REG_ITM_STIM27_STIM27_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM27_STIM27(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM28 - Stimulus Port Register 28
//
//*****************************************************************************
// Stimulus Port Register 28.
#define AM_REG_ITM_STIM28_STIM28_S                   0
#define AM_REG_ITM_STIM28_STIM28_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM28_STIM28(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM29 - Stimulus Port Register 29
//
//*****************************************************************************
// Stimulus Port Register 29.
#define AM_REG_ITM_STIM29_STIM29_S                   0
#define AM_REG_ITM_STIM29_STIM29_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM29_STIM29(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM30 - Stimulus Port Register 30
//
//*****************************************************************************
// Stimulus Port Register 30.
#define AM_REG_ITM_STIM30_STIM30_S                   0
#define AM_REG_ITM_STIM30_STIM30_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM30_STIM30(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_STIM31 - Stimulus Port Register 31
//
//*****************************************************************************
// Stimulus Port Register 31.
#define AM_REG_ITM_STIM31_STIM31_S                   0
#define AM_REG_ITM_STIM31_STIM31_M                   0xFFFFFFFF
#define AM_REG_ITM_STIM31_STIM31(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_TER - Trace Enable Register.
//
//*****************************************************************************
// Bit mask to enable tracing on ITM stimulus ports. One bit per stimulus port..
#define AM_REG_ITM_TER_STIMENA_S                     0
#define AM_REG_ITM_TER_STIMENA_M                     0xFFFFFFFF
#define AM_REG_ITM_TER_STIMENA(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_TPR - Trace Privilege Register.
//
//*****************************************************************************
// Bit mask to enable tracing on ITM stimulus ports. bit[0] = stimulus
// ports[7:0], bit[1] = stimulus ports[15:8], bit[2] = stimulus ports[23:16],
// bit[3] = stimulus ports[31:24].
#define AM_REG_ITM_TPR_PRIVMASK_S                    0
#define AM_REG_ITM_TPR_PRIVMASK_M                    0x0000000F
#define AM_REG_ITM_TPR_PRIVMASK(n)                   (((uint32_t)(n) << 0) & 0x0000000F)

//*****************************************************************************
//
// ITM_TCR - Trace Control Register.
//
//*****************************************************************************
// Set when ITM events present and being drained.
#define AM_REG_ITM_TCR_BUSY_S                        23
#define AM_REG_ITM_TCR_BUSY_M                        0x00800000
#define AM_REG_ITM_TCR_BUSY(n)                       (((uint32_t)(n) << 23) & 0x00800000)

// ATB ID for CoreSight system.
#define AM_REG_ITM_TCR_ATB_ID_S                      16
#define AM_REG_ITM_TCR_ATB_ID_M                      0x007F0000
#define AM_REG_ITM_TCR_ATB_ID(n)                     (((uint32_t)(n) << 16) & 0x007F0000)

// Global Timestamp Frequency.
#define AM_REG_ITM_TCR_TS_FREQ_S                     10
#define AM_REG_ITM_TCR_TS_FREQ_M                     0x00000C00
#define AM_REG_ITM_TCR_TS_FREQ(n)                    (((uint32_t)(n) << 10) & 0x00000C00)

// Timestamp prescaler: 0b00 = no prescaling 0b01 = divide by 4 0b10 = divide by
// 16 0b11 = divide by 64.
#define AM_REG_ITM_TCR_TS_PRESCALE_S                 8
#define AM_REG_ITM_TCR_TS_PRESCALE_M                 0x00000300
#define AM_REG_ITM_TCR_TS_PRESCALE(n)                (((uint32_t)(n) << 8) & 0x00000300)

// Enable SWV behavior – count on TPIUEMIT and TPIUBAUD.
#define AM_REG_ITM_TCR_SWV_ENABLE_S                  4
#define AM_REG_ITM_TCR_SWV_ENABLE_M                  0x00000010
#define AM_REG_ITM_TCR_SWV_ENABLE(n)                 (((uint32_t)(n) << 4) & 0x00000010)

// Enables the DWT stimulus.
#define AM_REG_ITM_TCR_DWT_ENABLE_S                  3
#define AM_REG_ITM_TCR_DWT_ENABLE_M                  0x00000008
#define AM_REG_ITM_TCR_DWT_ENABLE(n)                 (((uint32_t)(n) << 3) & 0x00000008)

// Enables sync packets for TPIU.
#define AM_REG_ITM_TCR_SYNC_ENABLE_S                 2
#define AM_REG_ITM_TCR_SYNC_ENABLE_M                 0x00000004
#define AM_REG_ITM_TCR_SYNC_ENABLE(n)                (((uint32_t)(n) << 2) & 0x00000004)

// Enables differential timestamps. Differential timestamps are emitted when a
// packet is written to the FIFO with a non-zero timestamp counter, and when the
// timestamp counter overflows. Timestamps are emitted during idle times after a
// fixed number of cycles. This provides a time reference for packets and inter-
// packet gaps.
#define AM_REG_ITM_TCR_TS_ENABLE_S                   1
#define AM_REG_ITM_TCR_TS_ENABLE_M                   0x00000002
#define AM_REG_ITM_TCR_TS_ENABLE(n)                  (((uint32_t)(n) << 1) & 0x00000002)

// Enable ITM. This is the master enable, and must be set before ITM Stimulus
// and Trace Enable registers can be written.
#define AM_REG_ITM_TCR_ITM_ENABLE_S                  0
#define AM_REG_ITM_TCR_ITM_ENABLE_M                  0x00000001
#define AM_REG_ITM_TCR_ITM_ENABLE(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// ITM_LOCKSREG - Lock Status Register
//
//*****************************************************************************
// You cannot implement 8-bit lock accesses.
#define AM_REG_ITM_LOCKSREG_BYTEACC_S                2
#define AM_REG_ITM_LOCKSREG_BYTEACC_M                0x00000004
#define AM_REG_ITM_LOCKSREG_BYTEACC(n)               (((uint32_t)(n) << 2) & 0x00000004)

// Write access to component is blocked. All writes are ignored, reads are
// permitted.
#define AM_REG_ITM_LOCKSREG_ACCESS_S                 1
#define AM_REG_ITM_LOCKSREG_ACCESS_M                 0x00000002
#define AM_REG_ITM_LOCKSREG_ACCESS(n)                (((uint32_t)(n) << 1) & 0x00000002)

// Indicates that a lock mechanism exists for this component.
#define AM_REG_ITM_LOCKSREG_PRESENT_S                0
#define AM_REG_ITM_LOCKSREG_PRESENT_M                0x00000001
#define AM_REG_ITM_LOCKSREG_PRESENT(n)               (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// ITM_PID4 - Peripheral Identification Register 4
//
//*****************************************************************************
// Peripheral Identification 4.
#define AM_REG_ITM_PID4_PID4_S                       0
#define AM_REG_ITM_PID4_PID4_M                       0xFFFFFFFF
#define AM_REG_ITM_PID4_PID4(n)                      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_PID5 - Peripheral Identification Register 5
//
//*****************************************************************************
// Peripheral Identification 5.
#define AM_REG_ITM_PID5_PID5_S                       0
#define AM_REG_ITM_PID5_PID5_M                       0xFFFFFFFF
#define AM_REG_ITM_PID5_PID5(n)                      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_PID6 - Peripheral Identification Register 6
//
//*****************************************************************************
// Peripheral Identification 6.
#define AM_REG_ITM_PID6_PID6_S                       0
#define AM_REG_ITM_PID6_PID6_M                       0xFFFFFFFF
#define AM_REG_ITM_PID6_PID6(n)                      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_PID7 - Peripheral Identification Register 7
//
//*****************************************************************************
// Peripheral Identification 7.
#define AM_REG_ITM_PID7_PID7_S                       0
#define AM_REG_ITM_PID7_PID7_M                       0xFFFFFFFF
#define AM_REG_ITM_PID7_PID7(n)                      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_PID0 - Peripheral Identification Register 0
//
//*****************************************************************************
// Peripheral Identification 0.
#define AM_REG_ITM_PID0_PID0_S                       0
#define AM_REG_ITM_PID0_PID0_M                       0xFFFFFFFF
#define AM_REG_ITM_PID0_PID0(n)                      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_PID1 - Peripheral Identification Register 1
//
//*****************************************************************************
// Peripheral Identification 1.
#define AM_REG_ITM_PID1_PID1_S                       0
#define AM_REG_ITM_PID1_PID1_M                       0xFFFFFFFF
#define AM_REG_ITM_PID1_PID1(n)                      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_PID2 - Peripheral Identification Register 2
//
//*****************************************************************************
// Peripheral Identification 2.
#define AM_REG_ITM_PID2_PID2_S                       0
#define AM_REG_ITM_PID2_PID2_M                       0xFFFFFFFF
#define AM_REG_ITM_PID2_PID2(n)                      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_PID3 - Peripheral Identification Register 3
//
//*****************************************************************************
// Peripheral Identification 3.
#define AM_REG_ITM_PID3_PID3_S                       0
#define AM_REG_ITM_PID3_PID3_M                       0xFFFFFFFF
#define AM_REG_ITM_PID3_PID3(n)                      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_CID0 - Component Identification Register 1
//
//*****************************************************************************
// Component Identification 1.
#define AM_REG_ITM_CID0_CID0_S                       0
#define AM_REG_ITM_CID0_CID0_M                       0xFFFFFFFF
#define AM_REG_ITM_CID0_CID0(n)                      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_CID1 - Component Identification Register 1
//
//*****************************************************************************
// Component Identification 1.
#define AM_REG_ITM_CID1_CID1_S                       0
#define AM_REG_ITM_CID1_CID1_M                       0xFFFFFFFF
#define AM_REG_ITM_CID1_CID1(n)                      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_CID2 - Component Identification Register 2
//
//*****************************************************************************
// Component Identification 2.
#define AM_REG_ITM_CID2_CID2_S                       0
#define AM_REG_ITM_CID2_CID2_M                       0xFFFFFFFF
#define AM_REG_ITM_CID2_CID2(n)                      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// ITM_CID3 - Component Identification Register 3
//
//*****************************************************************************
// Component Identification 3.
#define AM_REG_ITM_CID3_CID3_S                       0
#define AM_REG_ITM_CID3_CID3_M                       0xFFFFFFFF
#define AM_REG_ITM_CID3_CID3(n)                      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

#endif // AM_REG_ITM_H
