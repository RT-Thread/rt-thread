//*****************************************************************************
//
//  am_reg_pdm.h
//! @file
//!
//! @brief Register macros for the PDM module
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
#ifndef AM_REG_PDM_H
#define AM_REG_PDM_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_PDM_NUM_MODULES                       1
#define AM_REG_PDMn(n) \
    (REG_PDM_BASEADDR + 0x00000000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_PDM_PCFG_O                            0x00000000
#define AM_REG_PDM_VCFG_O                            0x00000004
#define AM_REG_PDM_FR_O                              0x00000008
#define AM_REG_PDM_FRD_O                             0x0000000C
#define AM_REG_PDM_FLUSH_O                           0x00000010
#define AM_REG_PDM_FTHR_O                            0x00000014
#define AM_REG_PDM_INTEN_O                           0x00000200
#define AM_REG_PDM_INTSTAT_O                         0x00000204
#define AM_REG_PDM_INTCLR_O                          0x00000208
#define AM_REG_PDM_INTSET_O                          0x0000020C

//*****************************************************************************
//
// PDM_INTEN - IO Master Interrupts: Enable
//
//*****************************************************************************
// This is the FIFO underflow interrupt.
#define AM_REG_PDM_INTEN_UNDFL_S                     2
#define AM_REG_PDM_INTEN_UNDFL_M                     0x00000004
#define AM_REG_PDM_INTEN_UNDFL(n)                    (((uint32_t)(n) << 2) & 0x00000004)

// This is the FIFO overflow interrupt.
#define AM_REG_PDM_INTEN_OVF_S                       1
#define AM_REG_PDM_INTEN_OVF_M                       0x00000002
#define AM_REG_PDM_INTEN_OVF(n)                      (((uint32_t)(n) << 1) & 0x00000002)

// This is the FIFO threshold interrupt.
#define AM_REG_PDM_INTEN_THR_S                       0
#define AM_REG_PDM_INTEN_THR_M                       0x00000001
#define AM_REG_PDM_INTEN_THR(n)                      (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PDM_INTSTAT - IO Master Interrupts: Status
//
//*****************************************************************************
// This is the FIFO underflow interrupt.
#define AM_REG_PDM_INTSTAT_UNDFL_S                   2
#define AM_REG_PDM_INTSTAT_UNDFL_M                   0x00000004
#define AM_REG_PDM_INTSTAT_UNDFL(n)                  (((uint32_t)(n) << 2) & 0x00000004)

// This is the FIFO overflow interrupt.
#define AM_REG_PDM_INTSTAT_OVF_S                     1
#define AM_REG_PDM_INTSTAT_OVF_M                     0x00000002
#define AM_REG_PDM_INTSTAT_OVF(n)                    (((uint32_t)(n) << 1) & 0x00000002)

// This is the FIFO threshold interrupt.
#define AM_REG_PDM_INTSTAT_THR_S                     0
#define AM_REG_PDM_INTSTAT_THR_M                     0x00000001
#define AM_REG_PDM_INTSTAT_THR(n)                    (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PDM_INTCLR - IO Master Interrupts: Clear
//
//*****************************************************************************
// This is the FIFO underflow interrupt.
#define AM_REG_PDM_INTCLR_UNDFL_S                    2
#define AM_REG_PDM_INTCLR_UNDFL_M                    0x00000004
#define AM_REG_PDM_INTCLR_UNDFL(n)                   (((uint32_t)(n) << 2) & 0x00000004)

// This is the FIFO overflow interrupt.
#define AM_REG_PDM_INTCLR_OVF_S                      1
#define AM_REG_PDM_INTCLR_OVF_M                      0x00000002
#define AM_REG_PDM_INTCLR_OVF(n)                     (((uint32_t)(n) << 1) & 0x00000002)

// This is the FIFO threshold interrupt.
#define AM_REG_PDM_INTCLR_THR_S                      0
#define AM_REG_PDM_INTCLR_THR_M                      0x00000001
#define AM_REG_PDM_INTCLR_THR(n)                     (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PDM_INTSET - IO Master Interrupts: Set
//
//*****************************************************************************
// This is the FIFO underflow interrupt.
#define AM_REG_PDM_INTSET_UNDFL_S                    2
#define AM_REG_PDM_INTSET_UNDFL_M                    0x00000004
#define AM_REG_PDM_INTSET_UNDFL(n)                   (((uint32_t)(n) << 2) & 0x00000004)

// This is the FIFO overflow interrupt.
#define AM_REG_PDM_INTSET_OVF_S                      1
#define AM_REG_PDM_INTSET_OVF_M                      0x00000002
#define AM_REG_PDM_INTSET_OVF(n)                     (((uint32_t)(n) << 1) & 0x00000002)

// This is the FIFO threshold interrupt.
#define AM_REG_PDM_INTSET_THR_S                      0
#define AM_REG_PDM_INTSET_THR_M                      0x00000001
#define AM_REG_PDM_INTSET_THR(n)                     (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PDM_PCFG - PDM Configuration Register
//
//*****************************************************************************
// Left/right channel swap.
#define AM_REG_PDM_PCFG_LRSWAP_S                     31
#define AM_REG_PDM_PCFG_LRSWAP_M                     0x80000000
#define AM_REG_PDM_PCFG_LRSWAP(n)                    (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_PDM_PCFG_LRSWAP_EN                    0x80000000
#define AM_REG_PDM_PCFG_LRSWAP_NOSWAP                0x00000000

// Right channel PGA gain.
#define AM_REG_PDM_PCFG_PGARIGHT_S                   27
#define AM_REG_PDM_PCFG_PGARIGHT_M                   0x78000000
#define AM_REG_PDM_PCFG_PGARIGHT(n)                  (((uint32_t)(n) << 27) & 0x78000000)
#define AM_REG_PDM_PCFG_PGARIGHT_M15DB               0x78000000
#define AM_REG_PDM_PCFG_PGARIGHT_M300DB              0x70000000
#define AM_REG_PDM_PCFG_PGARIGHT_M45DB               0x68000000
#define AM_REG_PDM_PCFG_PGARIGHT_M60DB               0x60000000
#define AM_REG_PDM_PCFG_PGARIGHT_M75DB               0x58000000
#define AM_REG_PDM_PCFG_PGARIGHT_M90DB               0x50000000
#define AM_REG_PDM_PCFG_PGARIGHT_M105DB              0x48000000
#define AM_REG_PDM_PCFG_PGARIGHT_M120DB              0x40000000
#define AM_REG_PDM_PCFG_PGARIGHT_P105DB              0x38000000
#define AM_REG_PDM_PCFG_PGARIGHT_P90DB               0x30000000
#define AM_REG_PDM_PCFG_PGARIGHT_P75DB               0x28000000
#define AM_REG_PDM_PCFG_PGARIGHT_P60DB               0x20000000
#define AM_REG_PDM_PCFG_PGARIGHT_P45DB               0x18000000
#define AM_REG_PDM_PCFG_PGARIGHT_P30DB               0x10000000
#define AM_REG_PDM_PCFG_PGARIGHT_P15DB               0x08000000
#define AM_REG_PDM_PCFG_PGARIGHT_0DB                 0x00000000

// Left channel PGA gain.
#define AM_REG_PDM_PCFG_PGALEFT_S                    23
#define AM_REG_PDM_PCFG_PGALEFT_M                    0x07800000
#define AM_REG_PDM_PCFG_PGALEFT(n)                   (((uint32_t)(n) << 23) & 0x07800000)
#define AM_REG_PDM_PCFG_PGALEFT_M15DB                0x07800000
#define AM_REG_PDM_PCFG_PGALEFT_M300DB               0x07000000
#define AM_REG_PDM_PCFG_PGALEFT_M45DB                0x06800000
#define AM_REG_PDM_PCFG_PGALEFT_M60DB                0x06000000
#define AM_REG_PDM_PCFG_PGALEFT_M75DB                0x05800000
#define AM_REG_PDM_PCFG_PGALEFT_M90DB                0x05000000
#define AM_REG_PDM_PCFG_PGALEFT_M105DB               0x04800000
#define AM_REG_PDM_PCFG_PGALEFT_M120DB               0x04000000
#define AM_REG_PDM_PCFG_PGALEFT_P105DB               0x03800000
#define AM_REG_PDM_PCFG_PGALEFT_P90DB                0x03000000
#define AM_REG_PDM_PCFG_PGALEFT_P75DB                0x02800000
#define AM_REG_PDM_PCFG_PGALEFT_P60DB                0x02000000
#define AM_REG_PDM_PCFG_PGALEFT_P45DB                0x01800000
#define AM_REG_PDM_PCFG_PGALEFT_P30DB                0x01000000
#define AM_REG_PDM_PCFG_PGALEFT_P15DB                0x00800000
#define AM_REG_PDM_PCFG_PGALEFT_0DB                  0x00000000

// PDM_CLK frequency divisor.
#define AM_REG_PDM_PCFG_MCLKDIV_S                    17
#define AM_REG_PDM_PCFG_MCLKDIV_M                    0x00060000
#define AM_REG_PDM_PCFG_MCLKDIV(n)                   (((uint32_t)(n) << 17) & 0x00060000)
#define AM_REG_PDM_PCFG_MCLKDIV_MCKDIV4              0x00060000
#define AM_REG_PDM_PCFG_MCLKDIV_MCKDIV3              0x00040000
#define AM_REG_PDM_PCFG_MCLKDIV_MCKDIV2              0x00020000
#define AM_REG_PDM_PCFG_MCLKDIV_MCKDIV1              0x00000000

// SINC decimation rate.
#define AM_REG_PDM_PCFG_SINCRATE_S                   10
#define AM_REG_PDM_PCFG_SINCRATE_M                   0x0001FC00
#define AM_REG_PDM_PCFG_SINCRATE(n)                  (((uint32_t)(n) << 10) & 0x0001FC00)

// High pass filter control.
#define AM_REG_PDM_PCFG_ADCHPD_S                     9
#define AM_REG_PDM_PCFG_ADCHPD_M                     0x00000200
#define AM_REG_PDM_PCFG_ADCHPD(n)                    (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_PDM_PCFG_ADCHPD_EN                    0x00000200
#define AM_REG_PDM_PCFG_ADCHPD_DIS                   0x00000000

// High pass filter coefficients.
#define AM_REG_PDM_PCFG_HPCUTOFF_S                   5
#define AM_REG_PDM_PCFG_HPCUTOFF_M                   0x000001E0
#define AM_REG_PDM_PCFG_HPCUTOFF(n)                  (((uint32_t)(n) << 5) & 0x000001E0)

// Number of clocks during gain-setting changes.
#define AM_REG_PDM_PCFG_CYCLES_S                     2
#define AM_REG_PDM_PCFG_CYCLES_M                     0x0000001C
#define AM_REG_PDM_PCFG_CYCLES(n)                    (((uint32_t)(n) << 2) & 0x0000001C)

// Soft mute control.
#define AM_REG_PDM_PCFG_SOFTMUTE_S                   1
#define AM_REG_PDM_PCFG_SOFTMUTE_M                   0x00000002
#define AM_REG_PDM_PCFG_SOFTMUTE(n)                  (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_PDM_PCFG_SOFTMUTE_EN                  0x00000002
#define AM_REG_PDM_PCFG_SOFTMUTE_DIS                 0x00000000

// Data Streaming Control.
#define AM_REG_PDM_PCFG_PDMCORE_S                    0
#define AM_REG_PDM_PCFG_PDMCORE_M                    0x00000001
#define AM_REG_PDM_PCFG_PDMCORE(n)                   (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_PDM_PCFG_PDMCORE_EN                   0x00000001
#define AM_REG_PDM_PCFG_PDMCORE_DIS                  0x00000000

//*****************************************************************************
//
// PDM_VCFG - Voice Configuration Register
//
//*****************************************************************************
// Enable the IO clock.
#define AM_REG_PDM_VCFG_IOCLKEN_S                    31
#define AM_REG_PDM_VCFG_IOCLKEN_M                    0x80000000
#define AM_REG_PDM_VCFG_IOCLKEN(n)                   (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_PDM_VCFG_IOCLKEN_DIS                  0x00000000
#define AM_REG_PDM_VCFG_IOCLKEN_EN                   0x80000000

// Reset the IP core.
#define AM_REG_PDM_VCFG_RSTB_S                       30
#define AM_REG_PDM_VCFG_RSTB_M                       0x40000000
#define AM_REG_PDM_VCFG_RSTB(n)                      (((uint32_t)(n) << 30) & 0x40000000)
#define AM_REG_PDM_VCFG_RSTB_RESET                   0x00000000
#define AM_REG_PDM_VCFG_RSTB_NORM                    0x40000000

// Select the PDM input clock.
#define AM_REG_PDM_VCFG_PDMCLKSEL_S                  27
#define AM_REG_PDM_VCFG_PDMCLKSEL_M                  0x38000000
#define AM_REG_PDM_VCFG_PDMCLKSEL(n)                 (((uint32_t)(n) << 27) & 0x38000000)
#define AM_REG_PDM_VCFG_PDMCLKSEL_DISABLE            0x00000000
#define AM_REG_PDM_VCFG_PDMCLKSEL_12MHz              0x08000000
#define AM_REG_PDM_VCFG_PDMCLKSEL_6MHz               0x10000000
#define AM_REG_PDM_VCFG_PDMCLKSEL_3MHz               0x18000000
#define AM_REG_PDM_VCFG_PDMCLKSEL_1_5MHz             0x20000000
#define AM_REG_PDM_VCFG_PDMCLKSEL_750KHz             0x28000000
#define AM_REG_PDM_VCFG_PDMCLKSEL_375KHz             0x30000000
#define AM_REG_PDM_VCFG_PDMCLKSEL_187KHz             0x38000000

// Enable the serial clock.
#define AM_REG_PDM_VCFG_PDMCLK_S                     26
#define AM_REG_PDM_VCFG_PDMCLK_M                     0x04000000
#define AM_REG_PDM_VCFG_PDMCLK(n)                    (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_PDM_VCFG_PDMCLK_DIS                   0x00000000
#define AM_REG_PDM_VCFG_PDMCLK_EN                    0x04000000

// I2S interface enable.
#define AM_REG_PDM_VCFG_I2SMODE_S                    20
#define AM_REG_PDM_VCFG_I2SMODE_M                    0x00100000
#define AM_REG_PDM_VCFG_I2SMODE(n)                   (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_PDM_VCFG_I2SMODE_DIS                  0x00000000
#define AM_REG_PDM_VCFG_I2SMODE_EN                   0x00100000

// I2S BCLK input inversion.
#define AM_REG_PDM_VCFG_BCLKINV_S                    19
#define AM_REG_PDM_VCFG_BCLKINV_M                    0x00080000
#define AM_REG_PDM_VCFG_BCLKINV(n)                   (((uint32_t)(n) << 19) & 0x00080000)
#define AM_REG_PDM_VCFG_BCLKINV_INV                  0x00000000
#define AM_REG_PDM_VCFG_BCLKINV_NORM                 0x00080000

// PDM clock sampling delay.
#define AM_REG_PDM_VCFG_DMICKDEL_S                   17
#define AM_REG_PDM_VCFG_DMICKDEL_M                   0x00020000
#define AM_REG_PDM_VCFG_DMICKDEL(n)                  (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_PDM_VCFG_DMICKDEL_0CYC                0x00000000
#define AM_REG_PDM_VCFG_DMICKDEL_1CYC                0x00020000

// Select PDM input clock source.
#define AM_REG_PDM_VCFG_SELAP_S                      16
#define AM_REG_PDM_VCFG_SELAP_M                      0x00010000
#define AM_REG_PDM_VCFG_SELAP(n)                     (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_PDM_VCFG_SELAP_I2S                    0x00010000
#define AM_REG_PDM_VCFG_SELAP_INTERNAL               0x00000000

// PCM data packing enable.
#define AM_REG_PDM_VCFG_PCMPACK_S                    8
#define AM_REG_PDM_VCFG_PCMPACK_M                    0x00000100
#define AM_REG_PDM_VCFG_PCMPACK(n)                   (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_PDM_VCFG_PCMPACK_DIS                  0x00000000
#define AM_REG_PDM_VCFG_PCMPACK_EN                   0x00000100

// Set PCM channels.
#define AM_REG_PDM_VCFG_CHSET_S                      3
#define AM_REG_PDM_VCFG_CHSET_M                      0x00000018
#define AM_REG_PDM_VCFG_CHSET(n)                     (((uint32_t)(n) << 3) & 0x00000018)
#define AM_REG_PDM_VCFG_CHSET_DIS                    0x00000000
#define AM_REG_PDM_VCFG_CHSET_LEFT                   0x00000008
#define AM_REG_PDM_VCFG_CHSET_RIGHT                  0x00000010
#define AM_REG_PDM_VCFG_CHSET_STEREO                 0x00000018

//*****************************************************************************
//
// PDM_FR - Voice Status Register
//
//*****************************************************************************
// Valid 32-bit entries currently in the FIFO.
#define AM_REG_PDM_FR_FIFOCNT_S                      0
#define AM_REG_PDM_FR_FIFOCNT_M                      0x000001FF
#define AM_REG_PDM_FR_FIFOCNT(n)                     (((uint32_t)(n) << 0) & 0x000001FF)

//*****************************************************************************
//
// PDM_FRD - FIFO Read
//
//*****************************************************************************
// FIFO read data.
#define AM_REG_PDM_FRD_FIFOREAD_S                    0
#define AM_REG_PDM_FRD_FIFOREAD_M                    0xFFFFFFFF
#define AM_REG_PDM_FRD_FIFOREAD(n)                   (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// PDM_FLUSH - FIFO Flush
//
//*****************************************************************************
// FIFO FLUSH.
#define AM_REG_PDM_FLUSH_FIFOFLUSH_S                 0
#define AM_REG_PDM_FLUSH_FIFOFLUSH_M                 0x00000001
#define AM_REG_PDM_FLUSH_FIFOFLUSH(n)                (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PDM_FTHR - FIFO Threshold
//
//*****************************************************************************
// FIFO interrupt threshold.
#define AM_REG_PDM_FTHR_FIFOTHR_S                    0
#define AM_REG_PDM_FTHR_FIFOTHR_M                    0x000000FF
#define AM_REG_PDM_FTHR_FIFOTHR(n)                   (((uint32_t)(n) << 0) & 0x000000FF)

#endif // AM_REG_PDM_H
