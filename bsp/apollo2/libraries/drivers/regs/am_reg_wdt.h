//*****************************************************************************
//
//  am_reg_wdt.h
//! @file
//!
//! @brief Register macros for the WDT module
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
#ifndef AM_REG_WDT_H
#define AM_REG_WDT_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_WDT_NUM_MODULES                       1
#define AM_REG_WDTn(n) \
    (REG_WDT_BASEADDR + 0x00000000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_WDT_CFG_O                             0x00000000
#define AM_REG_WDT_RSTRT_O                           0x00000004
#define AM_REG_WDT_LOCK_O                            0x00000008
#define AM_REG_WDT_COUNT_O                           0x0000000C
#define AM_REG_WDT_INTEN_O                           0x00000200
#define AM_REG_WDT_INTSTAT_O                         0x00000204
#define AM_REG_WDT_INTCLR_O                          0x00000208
#define AM_REG_WDT_INTSET_O                          0x0000020C

//*****************************************************************************
//
// WDT_INTEN - WDT Interrupt register: Enable
//
//*****************************************************************************
// Watchdog Timer Interrupt.
#define AM_REG_WDT_INTEN_WDT_S                       0
#define AM_REG_WDT_INTEN_WDT_M                       0x00000001
#define AM_REG_WDT_INTEN_WDT(n)                      (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// WDT_INTSTAT - WDT Interrupt register: Status
//
//*****************************************************************************
// Watchdog Timer Interrupt.
#define AM_REG_WDT_INTSTAT_WDT_S                     0
#define AM_REG_WDT_INTSTAT_WDT_M                     0x00000001
#define AM_REG_WDT_INTSTAT_WDT(n)                    (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// WDT_INTCLR - WDT Interrupt register: Clear
//
//*****************************************************************************
// Watchdog Timer Interrupt.
#define AM_REG_WDT_INTCLR_WDT_S                      0
#define AM_REG_WDT_INTCLR_WDT_M                      0x00000001
#define AM_REG_WDT_INTCLR_WDT(n)                     (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// WDT_INTSET - WDT Interrupt register: Set
//
//*****************************************************************************
// Watchdog Timer Interrupt.
#define AM_REG_WDT_INTSET_WDT_S                      0
#define AM_REG_WDT_INTSET_WDT_M                      0x00000001
#define AM_REG_WDT_INTSET_WDT(n)                     (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// WDT_CFG - Configuration Register
//
//*****************************************************************************
// Select the frequency for the WDT.  All values not enumerated below are
// undefined.
#define AM_REG_WDT_CFG_CLKSEL_S                      24
#define AM_REG_WDT_CFG_CLKSEL_M                      0x07000000
#define AM_REG_WDT_CFG_CLKSEL(n)                     (((uint32_t)(n) << 24) & 0x07000000)
#define AM_REG_WDT_CFG_CLKSEL_OFF                    0x00000000
#define AM_REG_WDT_CFG_CLKSEL_128HZ                  0x01000000
#define AM_REG_WDT_CFG_CLKSEL_16HZ                   0x02000000
#define AM_REG_WDT_CFG_CLKSEL_1HZ                    0x03000000
#define AM_REG_WDT_CFG_CLKSEL_1_16HZ                 0x04000000

// This bitfield is the compare value for counter bits 7:0 to generate a
// watchdog interrupt.
#define AM_REG_WDT_CFG_INTVAL_S                      16
#define AM_REG_WDT_CFG_INTVAL_M                      0x00FF0000
#define AM_REG_WDT_CFG_INTVAL(n)                     (((uint32_t)(n) << 16) & 0x00FF0000)

// This bitfield is the compare value for counter bits 7:0 to generate a
// watchdog reset.
#define AM_REG_WDT_CFG_RESVAL_S                      8
#define AM_REG_WDT_CFG_RESVAL_M                      0x0000FF00
#define AM_REG_WDT_CFG_RESVAL(n)                     (((uint32_t)(n) << 8) & 0x0000FF00)

// This bitfield enables the WDT reset.
#define AM_REG_WDT_CFG_RESEN_S                       2
#define AM_REG_WDT_CFG_RESEN_M                       0x00000004
#define AM_REG_WDT_CFG_RESEN(n)                      (((uint32_t)(n) << 2) & 0x00000004)

// This bitfield enables the WDT interrupt. Note : This bit must be set before
// the interrupt status bit will reflect a watchdog timer expiration.  The IER
// interrupt register must also be enabled for a WDT interrupt to be sent to the
// NVIC.
#define AM_REG_WDT_CFG_INTEN_S                       1
#define AM_REG_WDT_CFG_INTEN_M                       0x00000002
#define AM_REG_WDT_CFG_INTEN(n)                      (((uint32_t)(n) << 1) & 0x00000002)

// This bitfield enables the WDT.
#define AM_REG_WDT_CFG_WDTEN_S                       0
#define AM_REG_WDT_CFG_WDTEN_M                       0x00000001
#define AM_REG_WDT_CFG_WDTEN(n)                      (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// WDT_RSTRT - Restart the watchdog timer
//
//*****************************************************************************
// Writing 0xB2 to WDTRSTRT restarts the watchdog timer.
#define AM_REG_WDT_RSTRT_RSTRT_S                     0
#define AM_REG_WDT_RSTRT_RSTRT_M                     0x000000FF
#define AM_REG_WDT_RSTRT_RSTRT(n)                    (((uint32_t)(n) << 0) & 0x000000FF)
#define AM_REG_WDT_RSTRT_RSTRT_KEYVALUE              0x000000B2

//*****************************************************************************
//
// WDT_LOCK - Locks the WDT
//
//*****************************************************************************
// Writing 0x3A locks the watchdog timer. Once locked, the WDTCFG reg cannot be
// written and WDTEN is set.
#define AM_REG_WDT_LOCK_LOCK_S                       0
#define AM_REG_WDT_LOCK_LOCK_M                       0x000000FF
#define AM_REG_WDT_LOCK_LOCK(n)                      (((uint32_t)(n) << 0) & 0x000000FF)
#define AM_REG_WDT_LOCK_LOCK_KEYVALUE                0x0000003A

//*****************************************************************************
//
// WDT_COUNT - Current Counter Value for WDT
//
//*****************************************************************************
// Read-Only current value of the WDT counter
#define AM_REG_WDT_COUNT_COUNT_S                     0
#define AM_REG_WDT_COUNT_COUNT_M                     0x000000FF
#define AM_REG_WDT_COUNT_COUNT(n)                    (((uint32_t)(n) << 0) & 0x000000FF)

#endif // AM_REG_WDT_H
