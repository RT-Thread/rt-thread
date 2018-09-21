//*****************************************************************************
//
//  am_reg_clkgen.h
//! @file
//!
//! @brief Register macros for the CLKGEN module
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
#ifndef AM_REG_CLKGEN_H
#define AM_REG_CLKGEN_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_CLKGEN_NUM_MODULES                    1
#define AM_REG_CLKGENn(n) \
    (REG_CLKGEN_BASEADDR + 0x00000000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_CLKGEN_CALXT_O                        0x00000000
#define AM_REG_CLKGEN_CALRC_O                        0x00000004
#define AM_REG_CLKGEN_ACALCTR_O                      0x00000008
#define AM_REG_CLKGEN_OCTRL_O                        0x0000000C
#define AM_REG_CLKGEN_CLKOUT_O                       0x00000010
#define AM_REG_CLKGEN_CCTRL_O                        0x00000018
#define AM_REG_CLKGEN_STATUS_O                       0x0000001C
#define AM_REG_CLKGEN_HFADJ_O                        0x00000020
#define AM_REG_CLKGEN_CLOCKEN_O                      0x00000028
#define AM_REG_CLKGEN_CLOCKEN2_O                     0x0000002C
#define AM_REG_CLKGEN_CLOCKEN3_O                     0x00000030
#define AM_REG_CLKGEN_UARTEN_O                       0x00000034
#define AM_REG_CLKGEN_CLKKEY_O                       0x00000014
#define AM_REG_CLKGEN_INTEN_O                        0x00000100
#define AM_REG_CLKGEN_INTSTAT_O                      0x00000104
#define AM_REG_CLKGEN_INTCLR_O                       0x00000108
#define AM_REG_CLKGEN_INTSET_O                       0x0000010C

//*****************************************************************************
//
// Key values.
//
//*****************************************************************************
#define AM_REG_CLKGEN_CLKKEY_KEYVAL                  0x00000047

//*****************************************************************************
//
// CLKGEN_INTEN - CLKGEN Interrupt Register: Enable
//
//*****************************************************************************
// RTC Alarm interrupt
#define AM_REG_CLKGEN_INTEN_ALM_S                    3
#define AM_REG_CLKGEN_INTEN_ALM_M                    0x00000008
#define AM_REG_CLKGEN_INTEN_ALM(n)                   (((uint32_t)(n) << 3) & 0x00000008)

// XT Oscillator Fail interrupt
#define AM_REG_CLKGEN_INTEN_OF_S                     2
#define AM_REG_CLKGEN_INTEN_OF_M                     0x00000004
#define AM_REG_CLKGEN_INTEN_OF(n)                    (((uint32_t)(n) << 2) & 0x00000004)

// Autocalibration Complete interrupt
#define AM_REG_CLKGEN_INTEN_ACC_S                    1
#define AM_REG_CLKGEN_INTEN_ACC_M                    0x00000002
#define AM_REG_CLKGEN_INTEN_ACC(n)                   (((uint32_t)(n) << 1) & 0x00000002)

// Autocalibration Fail interrupt
#define AM_REG_CLKGEN_INTEN_ACF_S                    0
#define AM_REG_CLKGEN_INTEN_ACF_M                    0x00000001
#define AM_REG_CLKGEN_INTEN_ACF(n)                   (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CLKGEN_INTSTAT - CLKGEN Interrupt Register: Status
//
//*****************************************************************************
// RTC Alarm interrupt
#define AM_REG_CLKGEN_INTSTAT_ALM_S                  3
#define AM_REG_CLKGEN_INTSTAT_ALM_M                  0x00000008
#define AM_REG_CLKGEN_INTSTAT_ALM(n)                 (((uint32_t)(n) << 3) & 0x00000008)

// XT Oscillator Fail interrupt
#define AM_REG_CLKGEN_INTSTAT_OF_S                   2
#define AM_REG_CLKGEN_INTSTAT_OF_M                   0x00000004
#define AM_REG_CLKGEN_INTSTAT_OF(n)                  (((uint32_t)(n) << 2) & 0x00000004)

// Autocalibration Complete interrupt
#define AM_REG_CLKGEN_INTSTAT_ACC_S                  1
#define AM_REG_CLKGEN_INTSTAT_ACC_M                  0x00000002
#define AM_REG_CLKGEN_INTSTAT_ACC(n)                 (((uint32_t)(n) << 1) & 0x00000002)

// Autocalibration Fail interrupt
#define AM_REG_CLKGEN_INTSTAT_ACF_S                  0
#define AM_REG_CLKGEN_INTSTAT_ACF_M                  0x00000001
#define AM_REG_CLKGEN_INTSTAT_ACF(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CLKGEN_INTCLR - CLKGEN Interrupt Register: Clear
//
//*****************************************************************************
// RTC Alarm interrupt
#define AM_REG_CLKGEN_INTCLR_ALM_S                   3
#define AM_REG_CLKGEN_INTCLR_ALM_M                   0x00000008
#define AM_REG_CLKGEN_INTCLR_ALM(n)                  (((uint32_t)(n) << 3) & 0x00000008)

// XT Oscillator Fail interrupt
#define AM_REG_CLKGEN_INTCLR_OF_S                    2
#define AM_REG_CLKGEN_INTCLR_OF_M                    0x00000004
#define AM_REG_CLKGEN_INTCLR_OF(n)                   (((uint32_t)(n) << 2) & 0x00000004)

// Autocalibration Complete interrupt
#define AM_REG_CLKGEN_INTCLR_ACC_S                   1
#define AM_REG_CLKGEN_INTCLR_ACC_M                   0x00000002
#define AM_REG_CLKGEN_INTCLR_ACC(n)                  (((uint32_t)(n) << 1) & 0x00000002)

// Autocalibration Fail interrupt
#define AM_REG_CLKGEN_INTCLR_ACF_S                   0
#define AM_REG_CLKGEN_INTCLR_ACF_M                   0x00000001
#define AM_REG_CLKGEN_INTCLR_ACF(n)                  (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CLKGEN_INTSET - CLKGEN Interrupt Register: Set
//
//*****************************************************************************
// RTC Alarm interrupt
#define AM_REG_CLKGEN_INTSET_ALM_S                   3
#define AM_REG_CLKGEN_INTSET_ALM_M                   0x00000008
#define AM_REG_CLKGEN_INTSET_ALM(n)                  (((uint32_t)(n) << 3) & 0x00000008)

// XT Oscillator Fail interrupt
#define AM_REG_CLKGEN_INTSET_OF_S                    2
#define AM_REG_CLKGEN_INTSET_OF_M                    0x00000004
#define AM_REG_CLKGEN_INTSET_OF(n)                   (((uint32_t)(n) << 2) & 0x00000004)

// Autocalibration Complete interrupt
#define AM_REG_CLKGEN_INTSET_ACC_S                   1
#define AM_REG_CLKGEN_INTSET_ACC_M                   0x00000002
#define AM_REG_CLKGEN_INTSET_ACC(n)                  (((uint32_t)(n) << 1) & 0x00000002)

// Autocalibration Fail interrupt
#define AM_REG_CLKGEN_INTSET_ACF_S                   0
#define AM_REG_CLKGEN_INTSET_ACF_M                   0x00000001
#define AM_REG_CLKGEN_INTSET_ACF(n)                  (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CLKGEN_CALXT - XT Oscillator Control
//
//*****************************************************************************
// XT Oscillator calibration value
#define AM_REG_CLKGEN_CALXT_CALXT_S                  0
#define AM_REG_CLKGEN_CALXT_CALXT_M                  0x000007FF
#define AM_REG_CLKGEN_CALXT_CALXT(n)                 (((uint32_t)(n) << 0) & 0x000007FF)

//*****************************************************************************
//
// CLKGEN_CALRC - RC Oscillator Control
//
//*****************************************************************************
// LFRC Oscillator calibration value
#define AM_REG_CLKGEN_CALRC_CALRC_S                  0
#define AM_REG_CLKGEN_CALRC_CALRC_M                  0x0003FFFF
#define AM_REG_CLKGEN_CALRC_CALRC(n)                 (((uint32_t)(n) << 0) & 0x0003FFFF)

//*****************************************************************************
//
// CLKGEN_ACALCTR - Autocalibration Counter
//
//*****************************************************************************
// Autocalibration Counter result.
#define AM_REG_CLKGEN_ACALCTR_ACALCTR_S              0
#define AM_REG_CLKGEN_ACALCTR_ACALCTR_M              0x00FFFFFF
#define AM_REG_CLKGEN_ACALCTR_ACALCTR(n)             (((uint32_t)(n) << 0) & 0x00FFFFFF)

//*****************************************************************************
//
// CLKGEN_OCTRL - Oscillator Control
//
//*****************************************************************************
// Autocalibration control
#define AM_REG_CLKGEN_OCTRL_ACAL_S                   8
#define AM_REG_CLKGEN_OCTRL_ACAL_M                   0x00000700
#define AM_REG_CLKGEN_OCTRL_ACAL(n)                  (((uint32_t)(n) << 8) & 0x00000700)
#define AM_REG_CLKGEN_OCTRL_ACAL_DIS                 0x00000000
#define AM_REG_CLKGEN_OCTRL_ACAL_1024SEC             0x00000200
#define AM_REG_CLKGEN_OCTRL_ACAL_512SEC              0x00000300
#define AM_REG_CLKGEN_OCTRL_ACAL_XTFREQ              0x00000600
#define AM_REG_CLKGEN_OCTRL_ACAL_EXTFREQ             0x00000700

// Selects the RTC oscillator (1 => LFRC, 0 => XT)
#define AM_REG_CLKGEN_OCTRL_OSEL_S                   7
#define AM_REG_CLKGEN_OCTRL_OSEL_M                   0x00000080
#define AM_REG_CLKGEN_OCTRL_OSEL(n)                  (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_CLKGEN_OCTRL_OSEL_RTC_XT              0x00000000
#define AM_REG_CLKGEN_OCTRL_OSEL_RTC_LFRC            0x00000080

// Oscillator switch on failure function
#define AM_REG_CLKGEN_OCTRL_FOS_S                    6
#define AM_REG_CLKGEN_OCTRL_FOS_M                    0x00000040
#define AM_REG_CLKGEN_OCTRL_FOS(n)                   (((uint32_t)(n) << 6) & 0x00000040)
#define AM_REG_CLKGEN_OCTRL_FOS_DIS                  0x00000000
#define AM_REG_CLKGEN_OCTRL_FOS_EN                   0x00000040

// Stop the LFRC Oscillator to the RTC
#define AM_REG_CLKGEN_OCTRL_STOPRC_S                 1
#define AM_REG_CLKGEN_OCTRL_STOPRC_M                 0x00000002
#define AM_REG_CLKGEN_OCTRL_STOPRC(n)                (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_CLKGEN_OCTRL_STOPRC_EN                0x00000000
#define AM_REG_CLKGEN_OCTRL_STOPRC_STOP              0x00000002

// Stop the XT Oscillator to the RTC
#define AM_REG_CLKGEN_OCTRL_STOPXT_S                 0
#define AM_REG_CLKGEN_OCTRL_STOPXT_M                 0x00000001
#define AM_REG_CLKGEN_OCTRL_STOPXT(n)                (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CLKGEN_OCTRL_STOPXT_EN                0x00000000
#define AM_REG_CLKGEN_OCTRL_STOPXT_STOP              0x00000001

//*****************************************************************************
//
// CLKGEN_CLKOUT - CLKOUT Frequency Select
//
//*****************************************************************************
// Enable the CLKOUT signal
#define AM_REG_CLKGEN_CLKOUT_CKEN_S                  7
#define AM_REG_CLKGEN_CLKOUT_CKEN_M                  0x00000080
#define AM_REG_CLKGEN_CLKOUT_CKEN(n)                 (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_CLKGEN_CLKOUT_CKEN_DIS                0x00000000
#define AM_REG_CLKGEN_CLKOUT_CKEN_EN                 0x00000080

// CLKOUT signal select.  Note that HIGH_DRIVE should be selected if any high
// frequencies (such as from HFRC) are selected for CLKOUT.
#define AM_REG_CLKGEN_CLKOUT_CKSEL_S                 0
#define AM_REG_CLKGEN_CLKOUT_CKSEL_M                 0x0000003F
#define AM_REG_CLKGEN_CLKOUT_CKSEL(n)                (((uint32_t)(n) << 0) & 0x0000003F)
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC              0x00000000
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV2           0x00000001
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV4           0x00000002
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV8           0x00000003
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV16          0x00000004
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV32          0x00000005
#define AM_REG_CLKGEN_CLKOUT_CKSEL_RTC_1Hz           0x00000010
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV2M          0x00000016
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT                0x00000017
#define AM_REG_CLKGEN_CLKOUT_CKSEL_CG_100Hz          0x00000018
#define AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC              0x00000019
#define AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV4         0x0000001A
#define AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV8         0x0000001B
#define AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV16        0x0000001C
#define AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV64        0x0000001D
#define AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV128       0x0000001E
#define AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV256       0x0000001F
#define AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV512       0x00000020
#define AM_REG_CLKGEN_CLKOUT_CKSEL_FLASH_CLK         0x00000022
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC_DIV2         0x00000023
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC_DIV32        0x00000024
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC_DIV512       0x00000025
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC_DIV32K       0x00000026
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV256         0x00000027
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV8K          0x00000028
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV64K         0x00000029
#define AM_REG_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV16       0x0000002A
#define AM_REG_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV128      0x0000002B
#define AM_REG_CLKGEN_CLKOUT_CKSEL_ULFRC_1Hz         0x0000002C
#define AM_REG_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV4K       0x0000002D
#define AM_REG_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV1M       0x0000002E
#define AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV64K       0x0000002F
#define AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV16M       0x00000030
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC_DIV2M        0x00000031
#define AM_REG_CLKGEN_CLKOUT_CKSEL_HFRCNE            0x00000032
#define AM_REG_CLKGEN_CLKOUT_CKSEL_HFRCNE_DIV8       0x00000033
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XTNE              0x00000035
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XTNE_DIV16        0x00000036
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRCNE_DIV32      0x00000037
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRCNE            0x00000039

//*****************************************************************************
//
// CLKGEN_CCTRL - HFRC Clock Control
//
//*****************************************************************************
// Core Clock divisor
#define AM_REG_CLKGEN_CCTRL_CORESEL_S                0
#define AM_REG_CLKGEN_CCTRL_CORESEL_M                0x00000001
#define AM_REG_CLKGEN_CCTRL_CORESEL(n)               (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CLKGEN_CCTRL_CORESEL_HFRC             0x00000000
#define AM_REG_CLKGEN_CCTRL_CORESEL_HFRC_DIV2        0x00000001

//*****************************************************************************
//
// CLKGEN_STATUS - Clock Generator Status
//
//*****************************************************************************
// XT Oscillator is enabled but not oscillating
#define AM_REG_CLKGEN_STATUS_OSCF_S                  1
#define AM_REG_CLKGEN_STATUS_OSCF_M                  0x00000002
#define AM_REG_CLKGEN_STATUS_OSCF(n)                 (((uint32_t)(n) << 1) & 0x00000002)

// Current RTC oscillator (1 => LFRC, 0 => XT)
#define AM_REG_CLKGEN_STATUS_OMODE_S                 0
#define AM_REG_CLKGEN_STATUS_OMODE_M                 0x00000001
#define AM_REG_CLKGEN_STATUS_OMODE(n)                (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CLKGEN_HFADJ - HFRC Adjustment
//
//*****************************************************************************
// Gain control for HFRC adjustment
#define AM_REG_CLKGEN_HFADJ_HFADJ_GAIN_S             21
#define AM_REG_CLKGEN_HFADJ_HFADJ_GAIN_M             0x00E00000
#define AM_REG_CLKGEN_HFADJ_HFADJ_GAIN(n)            (((uint32_t)(n) << 21) & 0x00E00000)
#define AM_REG_CLKGEN_HFADJ_HFADJ_GAIN_Gain_of_1     0x00000000
#define AM_REG_CLKGEN_HFADJ_HFADJ_GAIN_Gain_of_1_in_2 0x00200000
#define AM_REG_CLKGEN_HFADJ_HFADJ_GAIN_Gain_of_1_in_4 0x00400000
#define AM_REG_CLKGEN_HFADJ_HFADJ_GAIN_Gain_of_1_in_8 0x00600000
#define AM_REG_CLKGEN_HFADJ_HFADJ_GAIN_Gain_of_1_in_16 0x00800000
#define AM_REG_CLKGEN_HFADJ_HFADJ_GAIN_Gain_of_1_in_32 0x00A00000

// XT warmup period for HFRC adjustment
#define AM_REG_CLKGEN_HFADJ_HFWARMUP_S               20
#define AM_REG_CLKGEN_HFADJ_HFWARMUP_M               0x00100000
#define AM_REG_CLKGEN_HFADJ_HFWARMUP(n)              (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_CLKGEN_HFADJ_HFWARMUP_1SEC            0x00000000
#define AM_REG_CLKGEN_HFADJ_HFWARMUP_2SEC            0x00100000

// Target HFRC adjustment value.
#define AM_REG_CLKGEN_HFADJ_HFXTADJ_S                8
#define AM_REG_CLKGEN_HFADJ_HFXTADJ_M                0x000FFF00
#define AM_REG_CLKGEN_HFADJ_HFXTADJ(n)               (((uint32_t)(n) << 8) & 0x000FFF00)

// Repeat period for HFRC adjustment
#define AM_REG_CLKGEN_HFADJ_HFADJCK_S                1
#define AM_REG_CLKGEN_HFADJ_HFADJCK_M                0x0000000E
#define AM_REG_CLKGEN_HFADJ_HFADJCK(n)               (((uint32_t)(n) << 1) & 0x0000000E)
#define AM_REG_CLKGEN_HFADJ_HFADJCK_4SEC             0x00000000
#define AM_REG_CLKGEN_HFADJ_HFADJCK_16SEC            0x00000002
#define AM_REG_CLKGEN_HFADJ_HFADJCK_32SEC            0x00000004
#define AM_REG_CLKGEN_HFADJ_HFADJCK_64SEC            0x00000006
#define AM_REG_CLKGEN_HFADJ_HFADJCK_128SEC           0x00000008
#define AM_REG_CLKGEN_HFADJ_HFADJCK_256SEC           0x0000000A
#define AM_REG_CLKGEN_HFADJ_HFADJCK_512SEC           0x0000000C
#define AM_REG_CLKGEN_HFADJ_HFADJCK_1024SEC          0x0000000E

// HFRC adjustment control
#define AM_REG_CLKGEN_HFADJ_HFADJEN_S                0
#define AM_REG_CLKGEN_HFADJ_HFADJEN_M                0x00000001
#define AM_REG_CLKGEN_HFADJ_HFADJEN(n)               (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CLKGEN_HFADJ_HFADJEN_DIS              0x00000000
#define AM_REG_CLKGEN_HFADJ_HFADJEN_EN               0x00000001

//*****************************************************************************
//
// CLKGEN_CLOCKEN - Clock Enable Status
//
//*****************************************************************************
// Clock enable status
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_S              0
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_M              0xFFFFFFFF
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN(n)             (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_ADC_CLKEN      0x00000001
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_CTIMER_CLKEN   0x00000002
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_CTIMER0A_CLKEN 0x00000004
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_CTIMER0B_CLKEN 0x00000008
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_CTIMER1A_CLKEN 0x00000010
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_CTIMER1B_CLKEN 0x00000020
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_CTIMER2A_CLKEN 0x00000040
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_CTIMER2B_CLKEN 0x00000080
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_CTIMER3A_CLKEN 0x00000100
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_CTIMER3B_CLKEN 0x00000200
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_IOMSTR0_CLKEN  0x00000400
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_IOMSTR1_CLKEN  0x00000800
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_IOMSTR2_CLKEN  0x00001000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_IOMSTR3_CLKEN  0x00002000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_IOMSTR4_CLKEN  0x00004000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_IOMSTR5_CLKEN  0x00008000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_IOMSTRIFC0_CLKEN 0x00010000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_IOMSTRIFC1_CLKEN 0x00020000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_IOMSTRIFC2_CLKEN 0x00040000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_IOMSTRIFC3_CLKEN 0x00080000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_IOMSTRIFC4_CLKEN 0x00100000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_IOMSTRIFC5_CLKEN 0x00200000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_IOSLAVE_CLKEN  0x00400000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_PDM_CLKEN      0x00800000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_PDMIFC_CLKEN   0x01000000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_RSTGEN_CLKEN   0x02000000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_SRAM_WIPE_CLKEN 0x04000000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_STIMER_CLKEN   0x08000000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_STIMER_CNT_CLKEN 0x10000000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_TPIU_CLKEN     0x20000000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_UART0_HCLK_CLKEN 0x40000000
#define AM_REG_CLKGEN_CLOCKEN_CLOCKEN_UART0HF_CLKEN  0x80000000

//*****************************************************************************
//
// CLKGEN_CLOCKEN2 - Clock Enable Status
//
//*****************************************************************************
// Clock enable status 2
#define AM_REG_CLKGEN_CLOCKEN2_CLOCKEN2_S            0
#define AM_REG_CLKGEN_CLOCKEN2_CLOCKEN2_M            0xFFFFFFFF
#define AM_REG_CLKGEN_CLOCKEN2_CLOCKEN2(n)           (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_CLKGEN_CLOCKEN2_CLOCKEN2_UART1_HCLK_CLKEN 0x00000001
#define AM_REG_CLKGEN_CLOCKEN2_CLOCKEN2_UART1HF_CLKEN 0x00000002
#define AM_REG_CLKGEN_CLOCKEN2_CLOCKEN2_WDT_CLKEN    0x00000004
#define AM_REG_CLKGEN_CLOCKEN2_CLOCKEN2_XT_32KHz_EN  0x40000000
#define AM_REG_CLKGEN_CLOCKEN2_CLOCKEN2_FRCHFRC      0x80000000

//*****************************************************************************
//
// CLKGEN_CLOCKEN3 - Clock Enable Status
//
//*****************************************************************************
// Clock enable status 3
#define AM_REG_CLKGEN_CLOCKEN3_CLOCKEN3_S            0
#define AM_REG_CLKGEN_CLOCKEN3_CLOCKEN3_M            0xFFFFFFFF
#define AM_REG_CLKGEN_CLOCKEN3_CLOCKEN3(n)           (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_CLKGEN_CLOCKEN3_CLOCKEN3_periph_all_xtal_en 0x01000000
#define AM_REG_CLKGEN_CLOCKEN3_CLOCKEN3_periph_all_hfrc_en 0x02000000
#define AM_REG_CLKGEN_CLOCKEN3_CLOCKEN3_HFADJEN      0x04000000
#define AM_REG_CLKGEN_CLOCKEN3_CLOCKEN3_HFRC_en_out  0x08000000
#define AM_REG_CLKGEN_CLOCKEN3_CLOCKEN3_RTC_SOURCE   0x10000000
#define AM_REG_CLKGEN_CLOCKEN3_CLOCKEN3_XTAL_EN      0x20000000
#define AM_REG_CLKGEN_CLOCKEN3_CLOCKEN3_HFRC_EN      0x40000000
#define AM_REG_CLKGEN_CLOCKEN3_CLOCKEN3_FLASHCLK_EN  0x80000000

//*****************************************************************************
//
// CLKGEN_UARTEN - UART Enable
//
//*****************************************************************************
// UART1 system clock control
#define AM_REG_CLKGEN_UARTEN_UART1EN_S               8
#define AM_REG_CLKGEN_UARTEN_UART1EN_M               0x00000300
#define AM_REG_CLKGEN_UARTEN_UART1EN(n)              (((uint32_t)(n) << 8) & 0x00000300)
#define AM_REG_CLKGEN_UARTEN_UART1EN_DIS             0x00000000
#define AM_REG_CLKGEN_UARTEN_UART1EN_EN              0x00000100
#define AM_REG_CLKGEN_UARTEN_UART1EN_REDUCE_FREQ     0x00000200
#define AM_REG_CLKGEN_UARTEN_UART1EN_EN_POWER_SAV    0x00000300

// UART0 system clock control
#define AM_REG_CLKGEN_UARTEN_UART0EN_S               0
#define AM_REG_CLKGEN_UARTEN_UART0EN_M               0x00000003
#define AM_REG_CLKGEN_UARTEN_UART0EN(n)              (((uint32_t)(n) << 0) & 0x00000003)
#define AM_REG_CLKGEN_UARTEN_UART0EN_DIS             0x00000000
#define AM_REG_CLKGEN_UARTEN_UART0EN_EN              0x00000001
#define AM_REG_CLKGEN_UARTEN_UART0EN_REDUCE_FREQ     0x00000002
#define AM_REG_CLKGEN_UARTEN_UART0EN_EN_POWER_SAV    0x00000003

#endif // AM_REG_CLKGEN_H
