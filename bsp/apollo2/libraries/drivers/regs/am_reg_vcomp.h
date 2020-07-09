//*****************************************************************************
//
//  am_reg_vcomp.h
//! @file
//!
//! @brief Register macros for the VCOMP module
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
#ifndef AM_REG_VCOMP_H
#define AM_REG_VCOMP_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_VCOMP_NUM_MODULES                     1
#define AM_REG_VCOMPn(n) \
    (REG_VCOMP_BASEADDR + 0x00000000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_VCOMP_CFG_O                           0x00000000
#define AM_REG_VCOMP_STAT_O                          0x00000004
#define AM_REG_VCOMP_PWDKEY_O                        0x00000008
#define AM_REG_VCOMP_INTEN_O                         0x00000200
#define AM_REG_VCOMP_INTSTAT_O                       0x00000204
#define AM_REG_VCOMP_INTCLR_O                        0x00000208
#define AM_REG_VCOMP_INTSET_O                        0x0000020C

//*****************************************************************************
//
// Key values.
//
//*****************************************************************************
#define AM_REG_VCOMP_PWDKEY_KEYVAL                   0x00000037

//*****************************************************************************
//
// VCOMP_INTEN - Voltage Comparator Interrupt registers: Enable
//
//*****************************************************************************
// This bit is the vcompout high interrupt.
#define AM_REG_VCOMP_INTEN_OUTHI_S                   1
#define AM_REG_VCOMP_INTEN_OUTHI_M                   0x00000002
#define AM_REG_VCOMP_INTEN_OUTHI(n)                  (((uint32_t)(n) << 1) & 0x00000002)

// This bit is the vcompout low interrupt.
#define AM_REG_VCOMP_INTEN_OUTLOW_S                  0
#define AM_REG_VCOMP_INTEN_OUTLOW_M                  0x00000001
#define AM_REG_VCOMP_INTEN_OUTLOW(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// VCOMP_INTSTAT - Voltage Comparator Interrupt registers: Status
//
//*****************************************************************************
// This bit is the vcompout high interrupt.
#define AM_REG_VCOMP_INTSTAT_OUTHI_S                 1
#define AM_REG_VCOMP_INTSTAT_OUTHI_M                 0x00000002
#define AM_REG_VCOMP_INTSTAT_OUTHI(n)                (((uint32_t)(n) << 1) & 0x00000002)

// This bit is the vcompout low interrupt.
#define AM_REG_VCOMP_INTSTAT_OUTLOW_S                0
#define AM_REG_VCOMP_INTSTAT_OUTLOW_M                0x00000001
#define AM_REG_VCOMP_INTSTAT_OUTLOW(n)               (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// VCOMP_INTCLR - Voltage Comparator Interrupt registers: Clear
//
//*****************************************************************************
// This bit is the vcompout high interrupt.
#define AM_REG_VCOMP_INTCLR_OUTHI_S                  1
#define AM_REG_VCOMP_INTCLR_OUTHI_M                  0x00000002
#define AM_REG_VCOMP_INTCLR_OUTHI(n)                 (((uint32_t)(n) << 1) & 0x00000002)

// This bit is the vcompout low interrupt.
#define AM_REG_VCOMP_INTCLR_OUTLOW_S                 0
#define AM_REG_VCOMP_INTCLR_OUTLOW_M                 0x00000001
#define AM_REG_VCOMP_INTCLR_OUTLOW(n)                (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// VCOMP_INTSET - Voltage Comparator Interrupt registers: Set
//
//*****************************************************************************
// This bit is the vcompout high interrupt.
#define AM_REG_VCOMP_INTSET_OUTHI_S                  1
#define AM_REG_VCOMP_INTSET_OUTHI_M                  0x00000002
#define AM_REG_VCOMP_INTSET_OUTHI(n)                 (((uint32_t)(n) << 1) & 0x00000002)

// This bit is the vcompout low interrupt.
#define AM_REG_VCOMP_INTSET_OUTLOW_S                 0
#define AM_REG_VCOMP_INTSET_OUTLOW_M                 0x00000001
#define AM_REG_VCOMP_INTSET_OUTLOW(n)                (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// VCOMP_CFG - Configuration Register
//
//*****************************************************************************
// When the reference input NSEL is set to NSEL_DAC, this bitfield selects the
// voltage level for the negative input to the comparator.
#define AM_REG_VCOMP_CFG_LVLSEL_S                    16
#define AM_REG_VCOMP_CFG_LVLSEL_M                    0x000F0000
#define AM_REG_VCOMP_CFG_LVLSEL(n)                   (((uint32_t)(n) << 16) & 0x000F0000)
#define AM_REG_VCOMP_CFG_LVLSEL_0P58V                0x00000000
#define AM_REG_VCOMP_CFG_LVLSEL_0P77V                0x00010000
#define AM_REG_VCOMP_CFG_LVLSEL_0P97V                0x00020000
#define AM_REG_VCOMP_CFG_LVLSEL_1P16V                0x00030000
#define AM_REG_VCOMP_CFG_LVLSEL_1P35V                0x00040000
#define AM_REG_VCOMP_CFG_LVLSEL_1P55V                0x00050000
#define AM_REG_VCOMP_CFG_LVLSEL_1P74V                0x00060000
#define AM_REG_VCOMP_CFG_LVLSEL_1P93V                0x00070000
#define AM_REG_VCOMP_CFG_LVLSEL_2P13V                0x00080000
#define AM_REG_VCOMP_CFG_LVLSEL_2P32V                0x00090000
#define AM_REG_VCOMP_CFG_LVLSEL_2P51V                0x000A0000
#define AM_REG_VCOMP_CFG_LVLSEL_2P71V                0x000B0000
#define AM_REG_VCOMP_CFG_LVLSEL_2P90V                0x000C0000
#define AM_REG_VCOMP_CFG_LVLSEL_3P09V                0x000D0000
#define AM_REG_VCOMP_CFG_LVLSEL_3P29V                0x000E0000
#define AM_REG_VCOMP_CFG_LVLSEL_3P48V                0x000F0000

// This bitfield selects the negative input to the comparator.
#define AM_REG_VCOMP_CFG_NSEL_S                      8
#define AM_REG_VCOMP_CFG_NSEL_M                      0x00000300
#define AM_REG_VCOMP_CFG_NSEL(n)                     (((uint32_t)(n) << 8) & 0x00000300)
#define AM_REG_VCOMP_CFG_NSEL_VREFEXT1               0x00000000
#define AM_REG_VCOMP_CFG_NSEL_VREFEXT2               0x00000100
#define AM_REG_VCOMP_CFG_NSEL_VREFEXT3               0x00000200
#define AM_REG_VCOMP_CFG_NSEL_DAC                    0x00000300

// This bitfield selects the positive input to the comparator.
#define AM_REG_VCOMP_CFG_PSEL_S                      0
#define AM_REG_VCOMP_CFG_PSEL_M                      0x00000003
#define AM_REG_VCOMP_CFG_PSEL(n)                     (((uint32_t)(n) << 0) & 0x00000003)
#define AM_REG_VCOMP_CFG_PSEL_VDDADJ                 0x00000000
#define AM_REG_VCOMP_CFG_PSEL_VTEMP                  0x00000001
#define AM_REG_VCOMP_CFG_PSEL_VEXT1                  0x00000002
#define AM_REG_VCOMP_CFG_PSEL_VEXT2                  0x00000003

//*****************************************************************************
//
// VCOMP_STAT - Status Register
//
//*****************************************************************************
// This bit indicates the power down state of the voltage comparator.
#define AM_REG_VCOMP_STAT_PWDSTAT_S                  1
#define AM_REG_VCOMP_STAT_PWDSTAT_M                  0x00000002
#define AM_REG_VCOMP_STAT_PWDSTAT(n)                 (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_VCOMP_STAT_PWDSTAT_POWERED_DOWN       0x00000002

// This bit is 1 if the positive input of the comparator is greater than the
// negative input.
#define AM_REG_VCOMP_STAT_CMPOUT_S                   0
#define AM_REG_VCOMP_STAT_CMPOUT_M                   0x00000001
#define AM_REG_VCOMP_STAT_CMPOUT(n)                  (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_VCOMP_STAT_CMPOUT_VOUT_LOW            0x00000000
#define AM_REG_VCOMP_STAT_CMPOUT_VOUT_HIGH           0x00000001

#endif // AM_REG_VCOMP_H
