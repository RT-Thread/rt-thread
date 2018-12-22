//*****************************************************************************
//
//  am_reg_rstgen.h
//! @file
//!
//! @brief Register macros for the RSTGEN module
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
#ifndef AM_REG_RSTGEN_H
#define AM_REG_RSTGEN_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_RSTGEN_NUM_MODULES                    1
#define AM_REG_RSTGENn(n) \
    (REG_RSTGEN_BASEADDR + 0x00000000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_RSTGEN_CFG_O                          0x00000000
#define AM_REG_RSTGEN_SWPOI_O                        0x00000004
#define AM_REG_RSTGEN_SWPOR_O                        0x00000008
#define AM_REG_RSTGEN_STAT_O                         0x0000000C
#define AM_REG_RSTGEN_CLRSTAT_O                      0x00000010
#define AM_REG_RSTGEN_TPIU_RST_O                     0x00000014
#define AM_REG_RSTGEN_INTEN_O                        0x00000200
#define AM_REG_RSTGEN_INTSTAT_O                      0x00000204
#define AM_REG_RSTGEN_INTCLR_O                       0x00000208
#define AM_REG_RSTGEN_INTSET_O                       0x0000020C

//*****************************************************************************
//
// RSTGEN_INTEN - Reset Interrupt register: Enable
//
//*****************************************************************************
// Enables an interrupt that triggers when VCC is below BODH level.
#define AM_REG_RSTGEN_INTEN_BODH_S                   0
#define AM_REG_RSTGEN_INTEN_BODH_M                   0x00000001
#define AM_REG_RSTGEN_INTEN_BODH(n)                  (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// RSTGEN_INTSTAT - Reset Interrupt register: Status
//
//*****************************************************************************
// Enables an interrupt that triggers when VCC is below BODH level.
#define AM_REG_RSTGEN_INTSTAT_BODH_S                 0
#define AM_REG_RSTGEN_INTSTAT_BODH_M                 0x00000001
#define AM_REG_RSTGEN_INTSTAT_BODH(n)                (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// RSTGEN_INTCLR - Reset Interrupt register: Clear
//
//*****************************************************************************
// Enables an interrupt that triggers when VCC is below BODH level.
#define AM_REG_RSTGEN_INTCLR_BODH_S                  0
#define AM_REG_RSTGEN_INTCLR_BODH_M                  0x00000001
#define AM_REG_RSTGEN_INTCLR_BODH(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// RSTGEN_INTSET - Reset Interrupt register: Set
//
//*****************************************************************************
// Enables an interrupt that triggers when VCC is below BODH level.
#define AM_REG_RSTGEN_INTSET_BODH_S                  0
#define AM_REG_RSTGEN_INTSET_BODH_M                  0x00000001
#define AM_REG_RSTGEN_INTSET_BODH(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// RSTGEN_CFG - Configuration Register
//
//*****************************************************************************
// Watchdog Timer Reset Enable.  NOTE: The WDT module must also be configured
// for WDT reset.
#define AM_REG_RSTGEN_CFG_WDREN_S                    1
#define AM_REG_RSTGEN_CFG_WDREN_M                    0x00000002
#define AM_REG_RSTGEN_CFG_WDREN(n)                   (((uint32_t)(n) << 1) & 0x00000002)

// Brown out high (2.1v) reset enable.
#define AM_REG_RSTGEN_CFG_BODHREN_S                  0
#define AM_REG_RSTGEN_CFG_BODHREN_M                  0x00000001
#define AM_REG_RSTGEN_CFG_BODHREN(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// RSTGEN_SWPOI - Software POI Reset
//
//*****************************************************************************
// 0x1B generates a software POI reset.
#define AM_REG_RSTGEN_SWPOI_SWPOIKEY_S               0
#define AM_REG_RSTGEN_SWPOI_SWPOIKEY_M               0x000000FF
#define AM_REG_RSTGEN_SWPOI_SWPOIKEY(n)              (((uint32_t)(n) << 0) & 0x000000FF)
#define AM_REG_RSTGEN_SWPOI_SWPOIKEY_KEYVALUE        0x0000001B

//*****************************************************************************
//
// RSTGEN_SWPOR - Software POR Reset
//
//*****************************************************************************
// 0xD4 generates a software POR reset.
#define AM_REG_RSTGEN_SWPOR_SWPORKEY_S               0
#define AM_REG_RSTGEN_SWPOR_SWPORKEY_M               0x000000FF
#define AM_REG_RSTGEN_SWPOR_SWPORKEY(n)              (((uint32_t)(n) << 0) & 0x000000FF)
#define AM_REG_RSTGEN_SWPOR_SWPORKEY_KEYVALUE        0x000000D4

//*****************************************************************************
//
// RSTGEN_STAT - Status Register
//
//*****************************************************************************
// Reset was initiated by a Watchdog Timer Reset.
#define AM_REG_RSTGEN_STAT_WDRSTAT_S                 6
#define AM_REG_RSTGEN_STAT_WDRSTAT_M                 0x00000040
#define AM_REG_RSTGEN_STAT_WDRSTAT(n)                (((uint32_t)(n) << 6) & 0x00000040)

// Reset was a initiated by Debugger Reset.
#define AM_REG_RSTGEN_STAT_DBGRSTAT_S                5
#define AM_REG_RSTGEN_STAT_DBGRSTAT_M                0x00000020
#define AM_REG_RSTGEN_STAT_DBGRSTAT(n)               (((uint32_t)(n) << 5) & 0x00000020)

// Reset was a initiated by Software POI Reset.
#define AM_REG_RSTGEN_STAT_POIRSTAT_S                4
#define AM_REG_RSTGEN_STAT_POIRSTAT_M                0x00000010
#define AM_REG_RSTGEN_STAT_POIRSTAT(n)               (((uint32_t)(n) << 4) & 0x00000010)

// Reset was a initiated by SW POR or AIRCR Reset.
#define AM_REG_RSTGEN_STAT_SWRSTAT_S                 3
#define AM_REG_RSTGEN_STAT_SWRSTAT_M                 0x00000008
#define AM_REG_RSTGEN_STAT_SWRSTAT(n)                (((uint32_t)(n) << 3) & 0x00000008)

// Reset was initiated by a Brown-Out Reset.
#define AM_REG_RSTGEN_STAT_BORSTAT_S                 2
#define AM_REG_RSTGEN_STAT_BORSTAT_M                 0x00000004
#define AM_REG_RSTGEN_STAT_BORSTAT(n)                (((uint32_t)(n) << 2) & 0x00000004)

// Reset was initiated by a Power-On Reset.
#define AM_REG_RSTGEN_STAT_PORSTAT_S                 1
#define AM_REG_RSTGEN_STAT_PORSTAT_M                 0x00000002
#define AM_REG_RSTGEN_STAT_PORSTAT(n)                (((uint32_t)(n) << 1) & 0x00000002)

// Reset was initiated by an External Reset.
#define AM_REG_RSTGEN_STAT_EXRSTAT_S                 0
#define AM_REG_RSTGEN_STAT_EXRSTAT_M                 0x00000001
#define AM_REG_RSTGEN_STAT_EXRSTAT(n)                (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// RSTGEN_CLRSTAT - Clear the status register
//
//*****************************************************************************
// Writing a 1 to this bit clears all bits in the RST_STAT.
#define AM_REG_RSTGEN_CLRSTAT_CLRSTAT_S              0
#define AM_REG_RSTGEN_CLRSTAT_CLRSTAT_M              0x00000001
#define AM_REG_RSTGEN_CLRSTAT_CLRSTAT(n)             (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// RSTGEN_TPIU_RST - TPIU reset
//
//*****************************************************************************
// Static reset for the TPIU. Write to '1' to assert reset to TPIU. Write to '0'
// to clear the reset.
#define AM_REG_RSTGEN_TPIU_RST_TPIURST_S             0
#define AM_REG_RSTGEN_TPIU_RST_TPIURST_M             0x00000001
#define AM_REG_RSTGEN_TPIU_RST_TPIURST(n)            (((uint32_t)(n) << 0) & 0x00000001)

#endif // AM_REG_RSTGEN_H
