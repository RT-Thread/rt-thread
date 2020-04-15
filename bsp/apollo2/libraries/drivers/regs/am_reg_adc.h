//*****************************************************************************
//
//  am_reg_adc.h
//! @file
//!
//! @brief Register macros for the ADC module
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
#ifndef AM_REG_ADC_H
#define AM_REG_ADC_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_ADC_NUM_MODULES                       1
#define AM_REG_ADCn(n) \
    (REG_ADC_BASEADDR + 0x00000000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_ADC_CFG_O                             0x00000000
#define AM_REG_ADC_STAT_O                            0x00000004
#define AM_REG_ADC_SWT_O                             0x00000008
#define AM_REG_ADC_SL0CFG_O                          0x0000000C
#define AM_REG_ADC_SL1CFG_O                          0x00000010
#define AM_REG_ADC_SL2CFG_O                          0x00000014
#define AM_REG_ADC_SL3CFG_O                          0x00000018
#define AM_REG_ADC_SL4CFG_O                          0x0000001C
#define AM_REG_ADC_SL5CFG_O                          0x00000020
#define AM_REG_ADC_SL6CFG_O                          0x00000024
#define AM_REG_ADC_SL7CFG_O                          0x00000028
#define AM_REG_ADC_WULIM_O                           0x0000002C
#define AM_REG_ADC_WLLIM_O                           0x00000030
#define AM_REG_ADC_FIFO_O                            0x00000038
#define AM_REG_ADC_INTEN_O                           0x00000200
#define AM_REG_ADC_INTSTAT_O                         0x00000204
#define AM_REG_ADC_INTCLR_O                          0x00000208
#define AM_REG_ADC_INTSET_O                          0x0000020C

//*****************************************************************************
//
// ADC_INTEN - ADC Interrupt registers: Enable
//
//*****************************************************************************
// Window comparator voltage incursion interrupt.
#define AM_REG_ADC_INTEN_WCINC_S                     5
#define AM_REG_ADC_INTEN_WCINC_M                     0x00000020
#define AM_REG_ADC_INTEN_WCINC(n)                    (((uint32_t)(n) << 5) & 0x00000020)
#define AM_REG_ADC_INTEN_WCINC_WCINCINT              0x00000020

// Window comparator voltage excursion interrupt.
#define AM_REG_ADC_INTEN_WCEXC_S                     4
#define AM_REG_ADC_INTEN_WCEXC_M                     0x00000010
#define AM_REG_ADC_INTEN_WCEXC(n)                    (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_ADC_INTEN_WCEXC_WCEXCINT              0x00000010

// FIFO 100 percent full interrupt.
#define AM_REG_ADC_INTEN_FIFOOVR2_S                  3
#define AM_REG_ADC_INTEN_FIFOOVR2_M                  0x00000008
#define AM_REG_ADC_INTEN_FIFOOVR2(n)                 (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_ADC_INTEN_FIFOOVR2_FIFOFULLINT        0x00000008

// FIFO 75 percent full interrupt.
#define AM_REG_ADC_INTEN_FIFOOVR1_S                  2
#define AM_REG_ADC_INTEN_FIFOOVR1_M                  0x00000004
#define AM_REG_ADC_INTEN_FIFOOVR1(n)                 (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_ADC_INTEN_FIFOOVR1_FIFO75INT          0x00000004

// ADC scan complete interrupt.
#define AM_REG_ADC_INTEN_SCNCMP_S                    1
#define AM_REG_ADC_INTEN_SCNCMP_M                    0x00000002
#define AM_REG_ADC_INTEN_SCNCMP(n)                   (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_ADC_INTEN_SCNCMP_SCNCMPINT            0x00000002

// ADC conversion complete interrupt.
#define AM_REG_ADC_INTEN_CNVCMP_S                    0
#define AM_REG_ADC_INTEN_CNVCMP_M                    0x00000001
#define AM_REG_ADC_INTEN_CNVCMP(n)                   (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_ADC_INTEN_CNVCMP_CNVCMPINT            0x00000001

//*****************************************************************************
//
// ADC_INTSTAT - ADC Interrupt registers: Status
//
//*****************************************************************************
// Window comparator voltage incursion interrupt.
#define AM_REG_ADC_INTSTAT_WCINC_S                   5
#define AM_REG_ADC_INTSTAT_WCINC_M                   0x00000020
#define AM_REG_ADC_INTSTAT_WCINC(n)                  (((uint32_t)(n) << 5) & 0x00000020)
#define AM_REG_ADC_INTSTAT_WCINC_WCINCINT            0x00000020

// Window comparator voltage excursion interrupt.
#define AM_REG_ADC_INTSTAT_WCEXC_S                   4
#define AM_REG_ADC_INTSTAT_WCEXC_M                   0x00000010
#define AM_REG_ADC_INTSTAT_WCEXC(n)                  (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_ADC_INTSTAT_WCEXC_WCEXCINT            0x00000010

// FIFO 100 percent full interrupt.
#define AM_REG_ADC_INTSTAT_FIFOOVR2_S                3
#define AM_REG_ADC_INTSTAT_FIFOOVR2_M                0x00000008
#define AM_REG_ADC_INTSTAT_FIFOOVR2(n)               (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_ADC_INTSTAT_FIFOOVR2_FIFOFULLINT      0x00000008

// FIFO 75 percent full interrupt.
#define AM_REG_ADC_INTSTAT_FIFOOVR1_S                2
#define AM_REG_ADC_INTSTAT_FIFOOVR1_M                0x00000004
#define AM_REG_ADC_INTSTAT_FIFOOVR1(n)               (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_ADC_INTSTAT_FIFOOVR1_FIFO75INT        0x00000004

// ADC scan complete interrupt.
#define AM_REG_ADC_INTSTAT_SCNCMP_S                  1
#define AM_REG_ADC_INTSTAT_SCNCMP_M                  0x00000002
#define AM_REG_ADC_INTSTAT_SCNCMP(n)                 (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_ADC_INTSTAT_SCNCMP_SCNCMPINT          0x00000002

// ADC conversion complete interrupt.
#define AM_REG_ADC_INTSTAT_CNVCMP_S                  0
#define AM_REG_ADC_INTSTAT_CNVCMP_M                  0x00000001
#define AM_REG_ADC_INTSTAT_CNVCMP(n)                 (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_ADC_INTSTAT_CNVCMP_CNVCMPINT          0x00000001

//*****************************************************************************
//
// ADC_INTCLR - ADC Interrupt registers: Clear
//
//*****************************************************************************
// Window comparator voltage incursion interrupt.
#define AM_REG_ADC_INTCLR_WCINC_S                    5
#define AM_REG_ADC_INTCLR_WCINC_M                    0x00000020
#define AM_REG_ADC_INTCLR_WCINC(n)                   (((uint32_t)(n) << 5) & 0x00000020)
#define AM_REG_ADC_INTCLR_WCINC_WCINCINT             0x00000020

// Window comparator voltage excursion interrupt.
#define AM_REG_ADC_INTCLR_WCEXC_S                    4
#define AM_REG_ADC_INTCLR_WCEXC_M                    0x00000010
#define AM_REG_ADC_INTCLR_WCEXC(n)                   (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_ADC_INTCLR_WCEXC_WCEXCINT             0x00000010

// FIFO 100 percent full interrupt.
#define AM_REG_ADC_INTCLR_FIFOOVR2_S                 3
#define AM_REG_ADC_INTCLR_FIFOOVR2_M                 0x00000008
#define AM_REG_ADC_INTCLR_FIFOOVR2(n)                (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_ADC_INTCLR_FIFOOVR2_FIFOFULLINT       0x00000008

// FIFO 75 percent full interrupt.
#define AM_REG_ADC_INTCLR_FIFOOVR1_S                 2
#define AM_REG_ADC_INTCLR_FIFOOVR1_M                 0x00000004
#define AM_REG_ADC_INTCLR_FIFOOVR1(n)                (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_ADC_INTCLR_FIFOOVR1_FIFO75INT         0x00000004

// ADC scan complete interrupt.
#define AM_REG_ADC_INTCLR_SCNCMP_S                   1
#define AM_REG_ADC_INTCLR_SCNCMP_M                   0x00000002
#define AM_REG_ADC_INTCLR_SCNCMP(n)                  (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_ADC_INTCLR_SCNCMP_SCNCMPINT           0x00000002

// ADC conversion complete interrupt.
#define AM_REG_ADC_INTCLR_CNVCMP_S                   0
#define AM_REG_ADC_INTCLR_CNVCMP_M                   0x00000001
#define AM_REG_ADC_INTCLR_CNVCMP(n)                  (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_ADC_INTCLR_CNVCMP_CNVCMPINT           0x00000001

//*****************************************************************************
//
// ADC_INTSET - ADC Interrupt registers: Set
//
//*****************************************************************************
// Window comparator voltage incursion interrupt.
#define AM_REG_ADC_INTSET_WCINC_S                    5
#define AM_REG_ADC_INTSET_WCINC_M                    0x00000020
#define AM_REG_ADC_INTSET_WCINC(n)                   (((uint32_t)(n) << 5) & 0x00000020)
#define AM_REG_ADC_INTSET_WCINC_WCINCINT             0x00000020

// Window comparator voltage excursion interrupt.
#define AM_REG_ADC_INTSET_WCEXC_S                    4
#define AM_REG_ADC_INTSET_WCEXC_M                    0x00000010
#define AM_REG_ADC_INTSET_WCEXC(n)                   (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_ADC_INTSET_WCEXC_WCEXCINT             0x00000010

// FIFO 100 percent full interrupt.
#define AM_REG_ADC_INTSET_FIFOOVR2_S                 3
#define AM_REG_ADC_INTSET_FIFOOVR2_M                 0x00000008
#define AM_REG_ADC_INTSET_FIFOOVR2(n)                (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_ADC_INTSET_FIFOOVR2_FIFOFULLINT       0x00000008

// FIFO 75 percent full interrupt.
#define AM_REG_ADC_INTSET_FIFOOVR1_S                 2
#define AM_REG_ADC_INTSET_FIFOOVR1_M                 0x00000004
#define AM_REG_ADC_INTSET_FIFOOVR1(n)                (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_ADC_INTSET_FIFOOVR1_FIFO75INT         0x00000004

// ADC scan complete interrupt.
#define AM_REG_ADC_INTSET_SCNCMP_S                   1
#define AM_REG_ADC_INTSET_SCNCMP_M                   0x00000002
#define AM_REG_ADC_INTSET_SCNCMP(n)                  (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_ADC_INTSET_SCNCMP_SCNCMPINT           0x00000002

// ADC conversion complete interrupt.
#define AM_REG_ADC_INTSET_CNVCMP_S                   0
#define AM_REG_ADC_INTSET_CNVCMP_M                   0x00000001
#define AM_REG_ADC_INTSET_CNVCMP(n)                  (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_ADC_INTSET_CNVCMP_CNVCMPINT           0x00000001

//*****************************************************************************
//
// ADC_CFG - Configuration Register
//
//*****************************************************************************
// Select the source and frequency for the ADC clock.  All values not enumerated
// below are undefined.
#define AM_REG_ADC_CFG_CLKSEL_S                      24
#define AM_REG_ADC_CFG_CLKSEL_M                      0x03000000
#define AM_REG_ADC_CFG_CLKSEL(n)                     (((uint32_t)(n) << 24) & 0x03000000)
#define AM_REG_ADC_CFG_CLKSEL_OFF                    0x00000000
#define AM_REG_ADC_CFG_CLKSEL_HFRC                   0x01000000
#define AM_REG_ADC_CFG_CLKSEL_HFRC_DIV2              0x02000000

// This bit selects the ADC trigger polarity for external off chip triggers.
#define AM_REG_ADC_CFG_TRIGPOL_S                     19
#define AM_REG_ADC_CFG_TRIGPOL_M                     0x00080000
#define AM_REG_ADC_CFG_TRIGPOL(n)                    (((uint32_t)(n) << 19) & 0x00080000)
#define AM_REG_ADC_CFG_TRIGPOL_RISING_EDGE           0x00000000
#define AM_REG_ADC_CFG_TRIGPOL_FALLING_EDGE          0x00080000

// Select the ADC trigger source.
#define AM_REG_ADC_CFG_TRIGSEL_S                     16
#define AM_REG_ADC_CFG_TRIGSEL_M                     0x00070000
#define AM_REG_ADC_CFG_TRIGSEL(n)                    (((uint32_t)(n) << 16) & 0x00070000)
#define AM_REG_ADC_CFG_TRIGSEL_EXT0                  0x00000000
#define AM_REG_ADC_CFG_TRIGSEL_EXT1                  0x00010000
#define AM_REG_ADC_CFG_TRIGSEL_EXT2                  0x00020000
#define AM_REG_ADC_CFG_TRIGSEL_EXT3                  0x00030000
#define AM_REG_ADC_CFG_TRIGSEL_VCOMP                 0x00040000
#define AM_REG_ADC_CFG_TRIGSEL_SWT                   0x00070000

// Select the ADC reference voltage.
#define AM_REG_ADC_CFG_REFSEL_S                      8
#define AM_REG_ADC_CFG_REFSEL_M                      0x00000300
#define AM_REG_ADC_CFG_REFSEL(n)                     (((uint32_t)(n) << 8) & 0x00000300)
#define AM_REG_ADC_CFG_REFSEL_INT2P0                 0x00000000
#define AM_REG_ADC_CFG_REFSEL_INT1P5                 0x00000100
#define AM_REG_ADC_CFG_REFSEL_EXT2P0                 0x00000200
#define AM_REG_ADC_CFG_REFSEL_EXT1P5                 0x00000300

// Clock mode register
#define AM_REG_ADC_CFG_CKMODE_S                      4
#define AM_REG_ADC_CFG_CKMODE_M                      0x00000010
#define AM_REG_ADC_CFG_CKMODE(n)                     (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_ADC_CFG_CKMODE_LPCKMODE               0x00000000
#define AM_REG_ADC_CFG_CKMODE_LLCKMODE               0x00000010

// Select power mode to enter between active scans.
#define AM_REG_ADC_CFG_LPMODE_S                      3
#define AM_REG_ADC_CFG_LPMODE_M                      0x00000008
#define AM_REG_ADC_CFG_LPMODE(n)                     (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_ADC_CFG_LPMODE_MODE0                  0x00000000
#define AM_REG_ADC_CFG_LPMODE_MODE1                  0x00000008

// This bit enables Repeating Scan Mode.
#define AM_REG_ADC_CFG_RPTEN_S                       2
#define AM_REG_ADC_CFG_RPTEN_M                       0x00000004
#define AM_REG_ADC_CFG_RPTEN(n)                      (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_ADC_CFG_RPTEN_SINGLE_SCAN             0x00000000
#define AM_REG_ADC_CFG_RPTEN_REPEATING_SCAN          0x00000004

// This bit enables the ADC module. While the ADC is enabled, the ADCCFG and
// SLOT Configuration regsiter settings must remain stable and unchanged. All
// configuration register settings, slot configuration settings and window
// comparison settings should be written prior to setting the ADCEN bit to '1'.
#define AM_REG_ADC_CFG_ADCEN_S                       0
#define AM_REG_ADC_CFG_ADCEN_M                       0x00000001
#define AM_REG_ADC_CFG_ADCEN(n)                      (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_ADC_CFG_ADCEN_DIS                     0x00000000
#define AM_REG_ADC_CFG_ADCEN_EN                      0x00000001

//*****************************************************************************
//
// ADC_STAT - ADC Power Status
//
//*****************************************************************************
// Indicates the power-status of the ADC.
#define AM_REG_ADC_STAT_PWDSTAT_S                    0
#define AM_REG_ADC_STAT_PWDSTAT_M                    0x00000001
#define AM_REG_ADC_STAT_PWDSTAT(n)                   (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_ADC_STAT_PWDSTAT_ON                   0x00000000
#define AM_REG_ADC_STAT_PWDSTAT_POWERED_DOWN         0x00000001

//*****************************************************************************
//
// ADC_SWT - Software trigger
//
//*****************************************************************************
// Writing 0x37 to this register generates a software trigger.
#define AM_REG_ADC_SWT_SWT_S                         0
#define AM_REG_ADC_SWT_SWT_M                         0x000000FF
#define AM_REG_ADC_SWT_SWT(n)                        (((uint32_t)(n) << 0) & 0x000000FF)
#define AM_REG_ADC_SWT_SWT_GEN_SW_TRIGGER            0x00000037

//*****************************************************************************
//
// ADC_SL0CFG - Slot 0 Configuration Register
//
//*****************************************************************************
// Select the number of measurements to average in the accumulate divide module
// for this slot.
#define AM_REG_ADC_SL0CFG_ADSEL0_S                   24
#define AM_REG_ADC_SL0CFG_ADSEL0_M                   0x07000000
#define AM_REG_ADC_SL0CFG_ADSEL0(n)                  (((uint32_t)(n) << 24) & 0x07000000)
#define AM_REG_ADC_SL0CFG_ADSEL0_AVG_1_MSRMT         0x00000000
#define AM_REG_ADC_SL0CFG_ADSEL0_AVG_2_MSRMTS        0x01000000
#define AM_REG_ADC_SL0CFG_ADSEL0_AVG_4_MSRMTS        0x02000000
#define AM_REG_ADC_SL0CFG_ADSEL0_AVG_8_MSRMT         0x03000000
#define AM_REG_ADC_SL0CFG_ADSEL0_AVG_16_MSRMTS       0x04000000
#define AM_REG_ADC_SL0CFG_ADSEL0_AVG_32_MSRMTS       0x05000000
#define AM_REG_ADC_SL0CFG_ADSEL0_AVG_64_MSRMTS       0x06000000
#define AM_REG_ADC_SL0CFG_ADSEL0_AVG_128_MSRMTS      0x07000000

// Set the Precision Mode For Slot.
#define AM_REG_ADC_SL0CFG_PRMODE0_S                  16
#define AM_REG_ADC_SL0CFG_PRMODE0_M                  0x00030000
#define AM_REG_ADC_SL0CFG_PRMODE0(n)                 (((uint32_t)(n) << 16) & 0x00030000)
#define AM_REG_ADC_SL0CFG_PRMODE0_P14B               0x00000000
#define AM_REG_ADC_SL0CFG_PRMODE0_P12B               0x00010000
#define AM_REG_ADC_SL0CFG_PRMODE0_P10B               0x00020000
#define AM_REG_ADC_SL0CFG_PRMODE0_P8B                0x00030000

// Select one of the 14 channel inputs for this slot.
#define AM_REG_ADC_SL0CFG_CHSEL0_S                   8
#define AM_REG_ADC_SL0CFG_CHSEL0_M                   0x00000F00
#define AM_REG_ADC_SL0CFG_CHSEL0(n)                  (((uint32_t)(n) << 8) & 0x00000F00)
#define AM_REG_ADC_SL0CFG_CHSEL0_SE0                 0x00000000
#define AM_REG_ADC_SL0CFG_CHSEL0_SE1                 0x00000100
#define AM_REG_ADC_SL0CFG_CHSEL0_SE2                 0x00000200
#define AM_REG_ADC_SL0CFG_CHSEL0_SE3                 0x00000300
#define AM_REG_ADC_SL0CFG_CHSEL0_SE4                 0x00000400
#define AM_REG_ADC_SL0CFG_CHSEL0_SE5                 0x00000500
#define AM_REG_ADC_SL0CFG_CHSEL0_SE6                 0x00000600
#define AM_REG_ADC_SL0CFG_CHSEL0_SE7                 0x00000700
#define AM_REG_ADC_SL0CFG_CHSEL0_SE8                 0x00000800
#define AM_REG_ADC_SL0CFG_CHSEL0_SE9                 0x00000900
#define AM_REG_ADC_SL0CFG_CHSEL0_DF0                 0x00000A00
#define AM_REG_ADC_SL0CFG_CHSEL0_DF1                 0x00000B00
#define AM_REG_ADC_SL0CFG_CHSEL0_TEMP                0x00000C00
#define AM_REG_ADC_SL0CFG_CHSEL0_BATT                0x00000D00
#define AM_REG_ADC_SL0CFG_CHSEL0_VSS                 0x00000E00

// This bit enables the window compare function for slot 0.
#define AM_REG_ADC_SL0CFG_WCEN0_S                    1
#define AM_REG_ADC_SL0CFG_WCEN0_M                    0x00000002
#define AM_REG_ADC_SL0CFG_WCEN0(n)                   (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_ADC_SL0CFG_WCEN0_WCEN                 0x00000002

// This bit enables slot 0 for ADC conversions.
#define AM_REG_ADC_SL0CFG_SLEN0_S                    0
#define AM_REG_ADC_SL0CFG_SLEN0_M                    0x00000001
#define AM_REG_ADC_SL0CFG_SLEN0(n)                   (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_ADC_SL0CFG_SLEN0_SLEN                 0x00000001

//*****************************************************************************
//
// ADC_SL1CFG - Slot 1 Configuration Register
//
//*****************************************************************************
// Select the number of measurements to average in the accumulate divide module
// for this slot.
#define AM_REG_ADC_SL1CFG_ADSEL1_S                   24
#define AM_REG_ADC_SL1CFG_ADSEL1_M                   0x07000000
#define AM_REG_ADC_SL1CFG_ADSEL1(n)                  (((uint32_t)(n) << 24) & 0x07000000)
#define AM_REG_ADC_SL1CFG_ADSEL1_AVG_1_MSRMT         0x00000000
#define AM_REG_ADC_SL1CFG_ADSEL1_AVG_2_MSRMTS        0x01000000
#define AM_REG_ADC_SL1CFG_ADSEL1_AVG_4_MSRMTS        0x02000000
#define AM_REG_ADC_SL1CFG_ADSEL1_AVG_8_MSRMT         0x03000000
#define AM_REG_ADC_SL1CFG_ADSEL1_AVG_16_MSRMTS       0x04000000
#define AM_REG_ADC_SL1CFG_ADSEL1_AVG_32_MSRMTS       0x05000000
#define AM_REG_ADC_SL1CFG_ADSEL1_AVG_64_MSRMTS       0x06000000
#define AM_REG_ADC_SL1CFG_ADSEL1_AVG_128_MSRMTS      0x07000000

// Set the Precision Mode For Slot.
#define AM_REG_ADC_SL1CFG_PRMODE1_S                  16
#define AM_REG_ADC_SL1CFG_PRMODE1_M                  0x00030000
#define AM_REG_ADC_SL1CFG_PRMODE1(n)                 (((uint32_t)(n) << 16) & 0x00030000)
#define AM_REG_ADC_SL1CFG_PRMODE1_P14B               0x00000000
#define AM_REG_ADC_SL1CFG_PRMODE1_P12B               0x00010000
#define AM_REG_ADC_SL1CFG_PRMODE1_P10B               0x00020000
#define AM_REG_ADC_SL1CFG_PRMODE1_P8B                0x00030000

// Select one of the 14 channel inputs for this slot.
#define AM_REG_ADC_SL1CFG_CHSEL1_S                   8
#define AM_REG_ADC_SL1CFG_CHSEL1_M                   0x00000F00
#define AM_REG_ADC_SL1CFG_CHSEL1(n)                  (((uint32_t)(n) << 8) & 0x00000F00)
#define AM_REG_ADC_SL1CFG_CHSEL1_SE0                 0x00000000
#define AM_REG_ADC_SL1CFG_CHSEL1_SE1                 0x00000100
#define AM_REG_ADC_SL1CFG_CHSEL1_SE2                 0x00000200
#define AM_REG_ADC_SL1CFG_CHSEL1_SE3                 0x00000300
#define AM_REG_ADC_SL1CFG_CHSEL1_SE4                 0x00000400
#define AM_REG_ADC_SL1CFG_CHSEL1_SE5                 0x00000500
#define AM_REG_ADC_SL1CFG_CHSEL1_SE6                 0x00000600
#define AM_REG_ADC_SL1CFG_CHSEL1_SE7                 0x00000700
#define AM_REG_ADC_SL1CFG_CHSEL1_SE8                 0x00000800
#define AM_REG_ADC_SL1CFG_CHSEL1_SE9                 0x00000900
#define AM_REG_ADC_SL1CFG_CHSEL1_DF0                 0x00000A00
#define AM_REG_ADC_SL1CFG_CHSEL1_DF1                 0x00000B00
#define AM_REG_ADC_SL1CFG_CHSEL1_TEMP                0x00000C00
#define AM_REG_ADC_SL1CFG_CHSEL1_BATT                0x00000D00
#define AM_REG_ADC_SL1CFG_CHSEL1_VSS                 0x00000E00

// This bit enables the window compare function for slot 1.
#define AM_REG_ADC_SL1CFG_WCEN1_S                    1
#define AM_REG_ADC_SL1CFG_WCEN1_M                    0x00000002
#define AM_REG_ADC_SL1CFG_WCEN1(n)                   (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_ADC_SL1CFG_WCEN1_WCEN                 0x00000002

// This bit enables slot 1 for ADC conversions.
#define AM_REG_ADC_SL1CFG_SLEN1_S                    0
#define AM_REG_ADC_SL1CFG_SLEN1_M                    0x00000001
#define AM_REG_ADC_SL1CFG_SLEN1(n)                   (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_ADC_SL1CFG_SLEN1_SLEN                 0x00000001

//*****************************************************************************
//
// ADC_SL2CFG - Slot 2 Configuration Register
//
//*****************************************************************************
// Select the number of measurements to average in the accumulate divide module
// for this slot.
#define AM_REG_ADC_SL2CFG_ADSEL2_S                   24
#define AM_REG_ADC_SL2CFG_ADSEL2_M                   0x07000000
#define AM_REG_ADC_SL2CFG_ADSEL2(n)                  (((uint32_t)(n) << 24) & 0x07000000)
#define AM_REG_ADC_SL2CFG_ADSEL2_AVG_1_MSRMT         0x00000000
#define AM_REG_ADC_SL2CFG_ADSEL2_AVG_2_MSRMTS        0x01000000
#define AM_REG_ADC_SL2CFG_ADSEL2_AVG_4_MSRMTS        0x02000000
#define AM_REG_ADC_SL2CFG_ADSEL2_AVG_8_MSRMT         0x03000000
#define AM_REG_ADC_SL2CFG_ADSEL2_AVG_16_MSRMTS       0x04000000
#define AM_REG_ADC_SL2CFG_ADSEL2_AVG_32_MSRMTS       0x05000000
#define AM_REG_ADC_SL2CFG_ADSEL2_AVG_64_MSRMTS       0x06000000
#define AM_REG_ADC_SL2CFG_ADSEL2_AVG_128_MSRMTS      0x07000000

// Set the Precision Mode For Slot.
#define AM_REG_ADC_SL2CFG_PRMODE2_S                  16
#define AM_REG_ADC_SL2CFG_PRMODE2_M                  0x00030000
#define AM_REG_ADC_SL2CFG_PRMODE2(n)                 (((uint32_t)(n) << 16) & 0x00030000)
#define AM_REG_ADC_SL2CFG_PRMODE2_P14B               0x00000000
#define AM_REG_ADC_SL2CFG_PRMODE2_P12B               0x00010000
#define AM_REG_ADC_SL2CFG_PRMODE2_P10B               0x00020000
#define AM_REG_ADC_SL2CFG_PRMODE2_P8B                0x00030000

// Select one of the 14 channel inputs for this slot.
#define AM_REG_ADC_SL2CFG_CHSEL2_S                   8
#define AM_REG_ADC_SL2CFG_CHSEL2_M                   0x00000F00
#define AM_REG_ADC_SL2CFG_CHSEL2(n)                  (((uint32_t)(n) << 8) & 0x00000F00)
#define AM_REG_ADC_SL2CFG_CHSEL2_SE0                 0x00000000
#define AM_REG_ADC_SL2CFG_CHSEL2_SE1                 0x00000100
#define AM_REG_ADC_SL2CFG_CHSEL2_SE2                 0x00000200
#define AM_REG_ADC_SL2CFG_CHSEL2_SE3                 0x00000300
#define AM_REG_ADC_SL2CFG_CHSEL2_SE4                 0x00000400
#define AM_REG_ADC_SL2CFG_CHSEL2_SE5                 0x00000500
#define AM_REG_ADC_SL2CFG_CHSEL2_SE6                 0x00000600
#define AM_REG_ADC_SL2CFG_CHSEL2_SE7                 0x00000700
#define AM_REG_ADC_SL2CFG_CHSEL2_SE8                 0x00000800
#define AM_REG_ADC_SL2CFG_CHSEL2_SE9                 0x00000900
#define AM_REG_ADC_SL2CFG_CHSEL2_DF0                 0x00000A00
#define AM_REG_ADC_SL2CFG_CHSEL2_DF1                 0x00000B00
#define AM_REG_ADC_SL2CFG_CHSEL2_TEMP                0x00000C00
#define AM_REG_ADC_SL2CFG_CHSEL2_BATT                0x00000D00
#define AM_REG_ADC_SL2CFG_CHSEL2_VSS                 0x00000E00

// This bit enables the window compare function for slot 2.
#define AM_REG_ADC_SL2CFG_WCEN2_S                    1
#define AM_REG_ADC_SL2CFG_WCEN2_M                    0x00000002
#define AM_REG_ADC_SL2CFG_WCEN2(n)                   (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_ADC_SL2CFG_WCEN2_WCEN                 0x00000002

// This bit enables slot 2 for ADC conversions.
#define AM_REG_ADC_SL2CFG_SLEN2_S                    0
#define AM_REG_ADC_SL2CFG_SLEN2_M                    0x00000001
#define AM_REG_ADC_SL2CFG_SLEN2(n)                   (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_ADC_SL2CFG_SLEN2_SLEN                 0x00000001

//*****************************************************************************
//
// ADC_SL3CFG - Slot 3 Configuration Register
//
//*****************************************************************************
// Select the number of measurements to average in the accumulate divide module
// for this slot.
#define AM_REG_ADC_SL3CFG_ADSEL3_S                   24
#define AM_REG_ADC_SL3CFG_ADSEL3_M                   0x07000000
#define AM_REG_ADC_SL3CFG_ADSEL3(n)                  (((uint32_t)(n) << 24) & 0x07000000)
#define AM_REG_ADC_SL3CFG_ADSEL3_AVG_1_MSRMT         0x00000000
#define AM_REG_ADC_SL3CFG_ADSEL3_AVG_2_MSRMTS        0x01000000
#define AM_REG_ADC_SL3CFG_ADSEL3_AVG_4_MSRMTS        0x02000000
#define AM_REG_ADC_SL3CFG_ADSEL3_AVG_8_MSRMT         0x03000000
#define AM_REG_ADC_SL3CFG_ADSEL3_AVG_16_MSRMTS       0x04000000
#define AM_REG_ADC_SL3CFG_ADSEL3_AVG_32_MSRMTS       0x05000000
#define AM_REG_ADC_SL3CFG_ADSEL3_AVG_64_MSRMTS       0x06000000
#define AM_REG_ADC_SL3CFG_ADSEL3_AVG_128_MSRMTS      0x07000000

// Set the Precision Mode For Slot.
#define AM_REG_ADC_SL3CFG_PRMODE3_S                  16
#define AM_REG_ADC_SL3CFG_PRMODE3_M                  0x00030000
#define AM_REG_ADC_SL3CFG_PRMODE3(n)                 (((uint32_t)(n) << 16) & 0x00030000)
#define AM_REG_ADC_SL3CFG_PRMODE3_P14B               0x00000000
#define AM_REG_ADC_SL3CFG_PRMODE3_P12B               0x00010000
#define AM_REG_ADC_SL3CFG_PRMODE3_P10B               0x00020000
#define AM_REG_ADC_SL3CFG_PRMODE3_P8B                0x00030000

// Select one of the 14 channel inputs for this slot.
#define AM_REG_ADC_SL3CFG_CHSEL3_S                   8
#define AM_REG_ADC_SL3CFG_CHSEL3_M                   0x00000F00
#define AM_REG_ADC_SL3CFG_CHSEL3(n)                  (((uint32_t)(n) << 8) & 0x00000F00)
#define AM_REG_ADC_SL3CFG_CHSEL3_SE0                 0x00000000
#define AM_REG_ADC_SL3CFG_CHSEL3_SE1                 0x00000100
#define AM_REG_ADC_SL3CFG_CHSEL3_SE2                 0x00000200
#define AM_REG_ADC_SL3CFG_CHSEL3_SE3                 0x00000300
#define AM_REG_ADC_SL3CFG_CHSEL3_SE4                 0x00000400
#define AM_REG_ADC_SL3CFG_CHSEL3_SE5                 0x00000500
#define AM_REG_ADC_SL3CFG_CHSEL3_SE6                 0x00000600
#define AM_REG_ADC_SL3CFG_CHSEL3_SE7                 0x00000700
#define AM_REG_ADC_SL3CFG_CHSEL3_SE8                 0x00000800
#define AM_REG_ADC_SL3CFG_CHSEL3_SE9                 0x00000900
#define AM_REG_ADC_SL3CFG_CHSEL3_DF0                 0x00000A00
#define AM_REG_ADC_SL3CFG_CHSEL3_DF1                 0x00000B00
#define AM_REG_ADC_SL3CFG_CHSEL3_TEMP                0x00000C00
#define AM_REG_ADC_SL3CFG_CHSEL3_BATT                0x00000D00
#define AM_REG_ADC_SL3CFG_CHSEL3_VSS                 0x00000E00

// This bit enables the window compare function for slot 3.
#define AM_REG_ADC_SL3CFG_WCEN3_S                    1
#define AM_REG_ADC_SL3CFG_WCEN3_M                    0x00000002
#define AM_REG_ADC_SL3CFG_WCEN3(n)                   (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_ADC_SL3CFG_WCEN3_WCEN                 0x00000002

// This bit enables slot 3 for ADC conversions.
#define AM_REG_ADC_SL3CFG_SLEN3_S                    0
#define AM_REG_ADC_SL3CFG_SLEN3_M                    0x00000001
#define AM_REG_ADC_SL3CFG_SLEN3(n)                   (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_ADC_SL3CFG_SLEN3_SLEN                 0x00000001

//*****************************************************************************
//
// ADC_SL4CFG - Slot 4 Configuration Register
//
//*****************************************************************************
// Select the number of measurements to average in the accumulate divide module
// for this slot.
#define AM_REG_ADC_SL4CFG_ADSEL4_S                   24
#define AM_REG_ADC_SL4CFG_ADSEL4_M                   0x07000000
#define AM_REG_ADC_SL4CFG_ADSEL4(n)                  (((uint32_t)(n) << 24) & 0x07000000)
#define AM_REG_ADC_SL4CFG_ADSEL4_AVG_1_MSRMT         0x00000000
#define AM_REG_ADC_SL4CFG_ADSEL4_AVG_2_MSRMTS        0x01000000
#define AM_REG_ADC_SL4CFG_ADSEL4_AVG_4_MSRMTS        0x02000000
#define AM_REG_ADC_SL4CFG_ADSEL4_AVG_8_MSRMT         0x03000000
#define AM_REG_ADC_SL4CFG_ADSEL4_AVG_16_MSRMTS       0x04000000
#define AM_REG_ADC_SL4CFG_ADSEL4_AVG_32_MSRMTS       0x05000000
#define AM_REG_ADC_SL4CFG_ADSEL4_AVG_64_MSRMTS       0x06000000
#define AM_REG_ADC_SL4CFG_ADSEL4_AVG_128_MSRMTS      0x07000000

// Set the Precision Mode For Slot.
#define AM_REG_ADC_SL4CFG_PRMODE4_S                  16
#define AM_REG_ADC_SL4CFG_PRMODE4_M                  0x00030000
#define AM_REG_ADC_SL4CFG_PRMODE4(n)                 (((uint32_t)(n) << 16) & 0x00030000)
#define AM_REG_ADC_SL4CFG_PRMODE4_P14B               0x00000000
#define AM_REG_ADC_SL4CFG_PRMODE4_P12B               0x00010000
#define AM_REG_ADC_SL4CFG_PRMODE4_P10B               0x00020000
#define AM_REG_ADC_SL4CFG_PRMODE4_P8B                0x00030000

// Select one of the 14 channel inputs for this slot.
#define AM_REG_ADC_SL4CFG_CHSEL4_S                   8
#define AM_REG_ADC_SL4CFG_CHSEL4_M                   0x00000F00
#define AM_REG_ADC_SL4CFG_CHSEL4(n)                  (((uint32_t)(n) << 8) & 0x00000F00)
#define AM_REG_ADC_SL4CFG_CHSEL4_SE0                 0x00000000
#define AM_REG_ADC_SL4CFG_CHSEL4_SE1                 0x00000100
#define AM_REG_ADC_SL4CFG_CHSEL4_SE2                 0x00000200
#define AM_REG_ADC_SL4CFG_CHSEL4_SE3                 0x00000300
#define AM_REG_ADC_SL4CFG_CHSEL4_SE4                 0x00000400
#define AM_REG_ADC_SL4CFG_CHSEL4_SE5                 0x00000500
#define AM_REG_ADC_SL4CFG_CHSEL4_SE6                 0x00000600
#define AM_REG_ADC_SL4CFG_CHSEL4_SE7                 0x00000700
#define AM_REG_ADC_SL4CFG_CHSEL4_SE8                 0x00000800
#define AM_REG_ADC_SL4CFG_CHSEL4_SE9                 0x00000900
#define AM_REG_ADC_SL4CFG_CHSEL4_DF0                 0x00000A00
#define AM_REG_ADC_SL4CFG_CHSEL4_DF1                 0x00000B00
#define AM_REG_ADC_SL4CFG_CHSEL4_TEMP                0x00000C00
#define AM_REG_ADC_SL4CFG_CHSEL4_BATT                0x00000D00
#define AM_REG_ADC_SL4CFG_CHSEL4_VSS                 0x00000E00

// This bit enables the window compare function for slot 4.
#define AM_REG_ADC_SL4CFG_WCEN4_S                    1
#define AM_REG_ADC_SL4CFG_WCEN4_M                    0x00000002
#define AM_REG_ADC_SL4CFG_WCEN4(n)                   (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_ADC_SL4CFG_WCEN4_WCEN                 0x00000002

// This bit enables slot 4 for ADC conversions.
#define AM_REG_ADC_SL4CFG_SLEN4_S                    0
#define AM_REG_ADC_SL4CFG_SLEN4_M                    0x00000001
#define AM_REG_ADC_SL4CFG_SLEN4(n)                   (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_ADC_SL4CFG_SLEN4_SLEN                 0x00000001

//*****************************************************************************
//
// ADC_SL5CFG - Slot 5 Configuration Register
//
//*****************************************************************************
// Select number of measurements to average in the accumulate divide module for
// this slot.
#define AM_REG_ADC_SL5CFG_ADSEL5_S                   24
#define AM_REG_ADC_SL5CFG_ADSEL5_M                   0x07000000
#define AM_REG_ADC_SL5CFG_ADSEL5(n)                  (((uint32_t)(n) << 24) & 0x07000000)
#define AM_REG_ADC_SL5CFG_ADSEL5_AVG_1_MSRMT         0x00000000
#define AM_REG_ADC_SL5CFG_ADSEL5_AVG_2_MSRMTS        0x01000000
#define AM_REG_ADC_SL5CFG_ADSEL5_AVG_4_MSRMTS        0x02000000
#define AM_REG_ADC_SL5CFG_ADSEL5_AVG_8_MSRMT         0x03000000
#define AM_REG_ADC_SL5CFG_ADSEL5_AVG_16_MSRMTS       0x04000000
#define AM_REG_ADC_SL5CFG_ADSEL5_AVG_32_MSRMTS       0x05000000
#define AM_REG_ADC_SL5CFG_ADSEL5_AVG_64_MSRMTS       0x06000000
#define AM_REG_ADC_SL5CFG_ADSEL5_AVG_128_MSRMTS      0x07000000

// Set the Precision Mode For Slot.
#define AM_REG_ADC_SL5CFG_PRMODE5_S                  16
#define AM_REG_ADC_SL5CFG_PRMODE5_M                  0x00030000
#define AM_REG_ADC_SL5CFG_PRMODE5(n)                 (((uint32_t)(n) << 16) & 0x00030000)
#define AM_REG_ADC_SL5CFG_PRMODE5_P14B               0x00000000
#define AM_REG_ADC_SL5CFG_PRMODE5_P12B               0x00010000
#define AM_REG_ADC_SL5CFG_PRMODE5_P10B               0x00020000
#define AM_REG_ADC_SL5CFG_PRMODE5_P8B                0x00030000

// Select one of the 14 channel inputs for this slot.
#define AM_REG_ADC_SL5CFG_CHSEL5_S                   8
#define AM_REG_ADC_SL5CFG_CHSEL5_M                   0x00000F00
#define AM_REG_ADC_SL5CFG_CHSEL5(n)                  (((uint32_t)(n) << 8) & 0x00000F00)
#define AM_REG_ADC_SL5CFG_CHSEL5_SE0                 0x00000000
#define AM_REG_ADC_SL5CFG_CHSEL5_SE1                 0x00000100
#define AM_REG_ADC_SL5CFG_CHSEL5_SE2                 0x00000200
#define AM_REG_ADC_SL5CFG_CHSEL5_SE3                 0x00000300
#define AM_REG_ADC_SL5CFG_CHSEL5_SE4                 0x00000400
#define AM_REG_ADC_SL5CFG_CHSEL5_SE5                 0x00000500
#define AM_REG_ADC_SL5CFG_CHSEL5_SE6                 0x00000600
#define AM_REG_ADC_SL5CFG_CHSEL5_SE7                 0x00000700
#define AM_REG_ADC_SL5CFG_CHSEL5_SE8                 0x00000800
#define AM_REG_ADC_SL5CFG_CHSEL5_SE9                 0x00000900
#define AM_REG_ADC_SL5CFG_CHSEL5_DF0                 0x00000A00
#define AM_REG_ADC_SL5CFG_CHSEL5_DF1                 0x00000B00
#define AM_REG_ADC_SL5CFG_CHSEL5_TEMP                0x00000C00
#define AM_REG_ADC_SL5CFG_CHSEL5_BATT                0x00000D00
#define AM_REG_ADC_SL5CFG_CHSEL5_VSS                 0x00000E00

// This bit enables the window compare function for slot 5.
#define AM_REG_ADC_SL5CFG_WCEN5_S                    1
#define AM_REG_ADC_SL5CFG_WCEN5_M                    0x00000002
#define AM_REG_ADC_SL5CFG_WCEN5(n)                   (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_ADC_SL5CFG_WCEN5_WCEN                 0x00000002

// This bit enables slot 5 for ADC conversions.
#define AM_REG_ADC_SL5CFG_SLEN5_S                    0
#define AM_REG_ADC_SL5CFG_SLEN5_M                    0x00000001
#define AM_REG_ADC_SL5CFG_SLEN5(n)                   (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_ADC_SL5CFG_SLEN5_SLEN                 0x00000001

//*****************************************************************************
//
// ADC_SL6CFG - Slot 6 Configuration Register
//
//*****************************************************************************
// Select the number of measurements to average in the accumulate divide module
// for this slot.
#define AM_REG_ADC_SL6CFG_ADSEL6_S                   24
#define AM_REG_ADC_SL6CFG_ADSEL6_M                   0x07000000
#define AM_REG_ADC_SL6CFG_ADSEL6(n)                  (((uint32_t)(n) << 24) & 0x07000000)
#define AM_REG_ADC_SL6CFG_ADSEL6_AVG_1_MSRMT         0x00000000
#define AM_REG_ADC_SL6CFG_ADSEL6_AVG_2_MSRMTS        0x01000000
#define AM_REG_ADC_SL6CFG_ADSEL6_AVG_4_MSRMTS        0x02000000
#define AM_REG_ADC_SL6CFG_ADSEL6_AVG_8_MSRMT         0x03000000
#define AM_REG_ADC_SL6CFG_ADSEL6_AVG_16_MSRMTS       0x04000000
#define AM_REG_ADC_SL6CFG_ADSEL6_AVG_32_MSRMTS       0x05000000
#define AM_REG_ADC_SL6CFG_ADSEL6_AVG_64_MSRMTS       0x06000000
#define AM_REG_ADC_SL6CFG_ADSEL6_AVG_128_MSRMTS      0x07000000

// Set the Precision Mode For Slot.
#define AM_REG_ADC_SL6CFG_PRMODE6_S                  16
#define AM_REG_ADC_SL6CFG_PRMODE6_M                  0x00030000
#define AM_REG_ADC_SL6CFG_PRMODE6(n)                 (((uint32_t)(n) << 16) & 0x00030000)
#define AM_REG_ADC_SL6CFG_PRMODE6_P14B               0x00000000
#define AM_REG_ADC_SL6CFG_PRMODE6_P12B               0x00010000
#define AM_REG_ADC_SL6CFG_PRMODE6_P10B               0x00020000
#define AM_REG_ADC_SL6CFG_PRMODE6_P8B                0x00030000

// Select one of the 14 channel inputs for this slot.
#define AM_REG_ADC_SL6CFG_CHSEL6_S                   8
#define AM_REG_ADC_SL6CFG_CHSEL6_M                   0x00000F00
#define AM_REG_ADC_SL6CFG_CHSEL6(n)                  (((uint32_t)(n) << 8) & 0x00000F00)
#define AM_REG_ADC_SL6CFG_CHSEL6_SE0                 0x00000000
#define AM_REG_ADC_SL6CFG_CHSEL6_SE1                 0x00000100
#define AM_REG_ADC_SL6CFG_CHSEL6_SE2                 0x00000200
#define AM_REG_ADC_SL6CFG_CHSEL6_SE3                 0x00000300
#define AM_REG_ADC_SL6CFG_CHSEL6_SE4                 0x00000400
#define AM_REG_ADC_SL6CFG_CHSEL6_SE5                 0x00000500
#define AM_REG_ADC_SL6CFG_CHSEL6_SE6                 0x00000600
#define AM_REG_ADC_SL6CFG_CHSEL6_SE7                 0x00000700
#define AM_REG_ADC_SL6CFG_CHSEL6_SE8                 0x00000800
#define AM_REG_ADC_SL6CFG_CHSEL6_SE9                 0x00000900
#define AM_REG_ADC_SL6CFG_CHSEL6_DF0                 0x00000A00
#define AM_REG_ADC_SL6CFG_CHSEL6_DF1                 0x00000B00
#define AM_REG_ADC_SL6CFG_CHSEL6_TEMP                0x00000C00
#define AM_REG_ADC_SL6CFG_CHSEL6_BATT                0x00000D00
#define AM_REG_ADC_SL6CFG_CHSEL6_VSS                 0x00000E00

// This bit enables the window compare function for slot 6.
#define AM_REG_ADC_SL6CFG_WCEN6_S                    1
#define AM_REG_ADC_SL6CFG_WCEN6_M                    0x00000002
#define AM_REG_ADC_SL6CFG_WCEN6(n)                   (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_ADC_SL6CFG_WCEN6_WCEN                 0x00000002

// This bit enables slot 6 for ADC conversions.
#define AM_REG_ADC_SL6CFG_SLEN6_S                    0
#define AM_REG_ADC_SL6CFG_SLEN6_M                    0x00000001
#define AM_REG_ADC_SL6CFG_SLEN6(n)                   (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_ADC_SL6CFG_SLEN6_SLEN                 0x00000001

//*****************************************************************************
//
// ADC_SL7CFG - Slot 7 Configuration Register
//
//*****************************************************************************
// Select the number of measurements to average in the accumulate divide module
// for this slot.
#define AM_REG_ADC_SL7CFG_ADSEL7_S                   24
#define AM_REG_ADC_SL7CFG_ADSEL7_M                   0x07000000
#define AM_REG_ADC_SL7CFG_ADSEL7(n)                  (((uint32_t)(n) << 24) & 0x07000000)
#define AM_REG_ADC_SL7CFG_ADSEL7_AVG_1_MSRMT         0x00000000
#define AM_REG_ADC_SL7CFG_ADSEL7_AVG_2_MSRMTS        0x01000000
#define AM_REG_ADC_SL7CFG_ADSEL7_AVG_4_MSRMTS        0x02000000
#define AM_REG_ADC_SL7CFG_ADSEL7_AVG_8_MSRMT         0x03000000
#define AM_REG_ADC_SL7CFG_ADSEL7_AVG_16_MSRMTS       0x04000000
#define AM_REG_ADC_SL7CFG_ADSEL7_AVG_32_MSRMTS       0x05000000
#define AM_REG_ADC_SL7CFG_ADSEL7_AVG_64_MSRMTS       0x06000000
#define AM_REG_ADC_SL7CFG_ADSEL7_AVG_128_MSRMTS      0x07000000

// Set the Precision Mode For Slot.
#define AM_REG_ADC_SL7CFG_PRMODE7_S                  16
#define AM_REG_ADC_SL7CFG_PRMODE7_M                  0x00030000
#define AM_REG_ADC_SL7CFG_PRMODE7(n)                 (((uint32_t)(n) << 16) & 0x00030000)
#define AM_REG_ADC_SL7CFG_PRMODE7_P14B               0x00000000
#define AM_REG_ADC_SL7CFG_PRMODE7_P12B               0x00010000
#define AM_REG_ADC_SL7CFG_PRMODE7_P10B               0x00020000
#define AM_REG_ADC_SL7CFG_PRMODE7_P8B                0x00030000

// Select one of the 14 channel inputs for this slot.
#define AM_REG_ADC_SL7CFG_CHSEL7_S                   8
#define AM_REG_ADC_SL7CFG_CHSEL7_M                   0x00000F00
#define AM_REG_ADC_SL7CFG_CHSEL7(n)                  (((uint32_t)(n) << 8) & 0x00000F00)
#define AM_REG_ADC_SL7CFG_CHSEL7_SE0                 0x00000000
#define AM_REG_ADC_SL7CFG_CHSEL7_SE1                 0x00000100
#define AM_REG_ADC_SL7CFG_CHSEL7_SE2                 0x00000200
#define AM_REG_ADC_SL7CFG_CHSEL7_SE3                 0x00000300
#define AM_REG_ADC_SL7CFG_CHSEL7_SE4                 0x00000400
#define AM_REG_ADC_SL7CFG_CHSEL7_SE5                 0x00000500
#define AM_REG_ADC_SL7CFG_CHSEL7_SE6                 0x00000600
#define AM_REG_ADC_SL7CFG_CHSEL7_SE7                 0x00000700
#define AM_REG_ADC_SL7CFG_CHSEL7_SE8                 0x00000800
#define AM_REG_ADC_SL7CFG_CHSEL7_SE9                 0x00000900
#define AM_REG_ADC_SL7CFG_CHSEL7_DF0                 0x00000A00
#define AM_REG_ADC_SL7CFG_CHSEL7_DF1                 0x00000B00
#define AM_REG_ADC_SL7CFG_CHSEL7_TEMP                0x00000C00
#define AM_REG_ADC_SL7CFG_CHSEL7_BATT                0x00000D00
#define AM_REG_ADC_SL7CFG_CHSEL7_VSS                 0x00000E00

// This bit enables the window compare function for slot 7.
#define AM_REG_ADC_SL7CFG_WCEN7_S                    1
#define AM_REG_ADC_SL7CFG_WCEN7_M                    0x00000002
#define AM_REG_ADC_SL7CFG_WCEN7(n)                   (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_ADC_SL7CFG_WCEN7_WCEN                 0x00000002

// This bit enables slot 7 for ADC conversions.
#define AM_REG_ADC_SL7CFG_SLEN7_S                    0
#define AM_REG_ADC_SL7CFG_SLEN7_M                    0x00000001
#define AM_REG_ADC_SL7CFG_SLEN7(n)                   (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_ADC_SL7CFG_SLEN7_SLEN                 0x00000001

//*****************************************************************************
//
// ADC_WULIM - Window Comparator Upper Limits Register
//
//*****************************************************************************
// Sets the upper limit for the wondow comparator.
#define AM_REG_ADC_WULIM_ULIM_S                      0
#define AM_REG_ADC_WULIM_ULIM_M                      0x000FFFFF
#define AM_REG_ADC_WULIM_ULIM(n)                     (((uint32_t)(n) << 0) & 0x000FFFFF)

//*****************************************************************************
//
// ADC_WLLIM - Window Comparator Lower Limits Register
//
//*****************************************************************************
// Sets the lower limit for the wondow comparator.
#define AM_REG_ADC_WLLIM_LLIM_S                      0
#define AM_REG_ADC_WLLIM_LLIM_M                      0x000FFFFF
#define AM_REG_ADC_WLLIM_LLIM(n)                     (((uint32_t)(n) << 0) & 0x000FFFFF)

//*****************************************************************************
//
// ADC_FIFO - FIFO Data and Valid Count Register
//
//*****************************************************************************
// RESERVED.
#define AM_REG_ADC_FIFO_RSVD_S                       31
#define AM_REG_ADC_FIFO_RSVD_M                       0x80000000
#define AM_REG_ADC_FIFO_RSVD(n)                      (((uint32_t)(n) << 31) & 0x80000000)

// Slot number associated with this FIFO data.
#define AM_REG_ADC_FIFO_SLOTNUM_S                    28
#define AM_REG_ADC_FIFO_SLOTNUM_M                    0x70000000
#define AM_REG_ADC_FIFO_SLOTNUM(n)                   (((uint32_t)(n) << 28) & 0x70000000)

// Number of valid entries in the ADC FIFO.
#define AM_REG_ADC_FIFO_COUNT_S                      20
#define AM_REG_ADC_FIFO_COUNT_M                      0x0FF00000
#define AM_REG_ADC_FIFO_COUNT(n)                     (((uint32_t)(n) << 20) & 0x0FF00000)

// Oldest data in the FIFO.
#define AM_REG_ADC_FIFO_DATA_S                       0
#define AM_REG_ADC_FIFO_DATA_M                       0x000FFFFF
#define AM_REG_ADC_FIFO_DATA(n)                      (((uint32_t)(n) << 0) & 0x000FFFFF)

#endif // AM_REG_ADC_H
