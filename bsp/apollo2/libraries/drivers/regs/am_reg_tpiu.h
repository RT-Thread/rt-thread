//*****************************************************************************
//
//  am_reg_tpiu.h
//! @file
//!
//! @brief Register macros for the TPIU module
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
#ifndef AM_REG_TPIU_H
#define AM_REG_TPIU_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_TPIU_NUM_MODULES                      1
#define AM_REG_TPIUn(n) \
    (REG_TPIU_BASEADDR + 0x00000000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_TPIU_SSPSR_O                          0xE0040000
#define AM_REG_TPIU_CSPSR_O                          0xE0040004
#define AM_REG_TPIU_ACPR_O                           0xE0040010
#define AM_REG_TPIU_SPPR_O                           0xE00400F0
#define AM_REG_TPIU_FFCR_O                           0xE0040304
#define AM_REG_TPIU_ITCTRL_O                         0xE0040F00
#define AM_REG_TPIU_TYPE_O                           0xE0040FC8

//*****************************************************************************
//
// TPIU_SSPSR - Supported Parallel Port Sizes.
//
//*****************************************************************************
// Parallel Port Width 1 supported
#define AM_REG_TPIU_SSPSR_SWIDTH0_S                  0
#define AM_REG_TPIU_SSPSR_SWIDTH0_M                  0x00000001
#define AM_REG_TPIU_SSPSR_SWIDTH0(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// TPIU_CSPSR - Current Parallel Port Size.
//
//*****************************************************************************
// One-hot representation of the current port width.
#define AM_REG_TPIU_CSPSR_CWIDTH_S                   0
#define AM_REG_TPIU_CSPSR_CWIDTH_M                   0xFFFFFFFF
#define AM_REG_TPIU_CSPSR_CWIDTH(n)                  (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_TPIU_CSPSR_CWIDTH_1BIT                0x00000001

//*****************************************************************************
//
// TPIU_ACPR - Asynchronous Clock Prescaler.
//
//*****************************************************************************
// Prescaler value for the baudrate of SWO.
#define AM_REG_TPIU_ACPR_SWOSCALER_S                 0
#define AM_REG_TPIU_ACPR_SWOSCALER_M                 0x0000FFFF
#define AM_REG_TPIU_ACPR_SWOSCALER(n)                (((uint32_t)(n) << 0) & 0x0000FFFF)
#define AM_REG_TPIU_ACPR_SWOSCALER_115200            0x00000033

//*****************************************************************************
//
// TPIU_SPPR - Selected Pin Protocol.
//
//*****************************************************************************
// Selects the protocol used for trace output.
#define AM_REG_TPIU_SPPR_TXMODE_S                    0
#define AM_REG_TPIU_SPPR_TXMODE_M                    0x00000003
#define AM_REG_TPIU_SPPR_TXMODE(n)                   (((uint32_t)(n) << 0) & 0x00000003)
#define AM_REG_TPIU_SPPR_TXMODE_PARALLEL             0x00000000
#define AM_REG_TPIU_SPPR_TXMODE_MANCHESTER           0x00000001
#define AM_REG_TPIU_SPPR_TXMODE_NRZ                  0x00000002
#define AM_REG_TPIU_SPPR_TXMODE_UART                 0x00000002

//*****************************************************************************
//
// TPIU_FFCR - Formatter and Flush Control Register.
//
//*****************************************************************************
// Enable continuous formatting.
#define AM_REG_TPIU_FFCR_ENFCONT_S                   1
#define AM_REG_TPIU_FFCR_ENFCONT_M                   0x00000002
#define AM_REG_TPIU_FFCR_ENFCONT(n)                  (((uint32_t)(n) << 1) & 0x00000002)

//*****************************************************************************
//
// TPIU_ITCTRL - Specifies normal or integration mode for the TPIU.
//
//*****************************************************************************
// Specifies the current mode for the TPIU.
#define AM_REG_TPIU_ITCTRL_MODE_S                    0
#define AM_REG_TPIU_ITCTRL_MODE_M                    0x00000003
#define AM_REG_TPIU_ITCTRL_MODE(n)                   (((uint32_t)(n) << 0) & 0x00000003)
#define AM_REG_TPIU_ITCTRL_MODE_NORMAL               0x00000000
#define AM_REG_TPIU_ITCTRL_MODE_TEST                 0x00000001
#define AM_REG_TPIU_ITCTRL_MODE_DATA_TEST            0x00000002

//*****************************************************************************
//
// TPIU_TYPE - TPIU Type.
//
//*****************************************************************************
// 1 Indicates UART/NRZ support.
#define AM_REG_TPIU_TYPE_NRZVALID_S                  11
#define AM_REG_TPIU_TYPE_NRZVALID_M                  0x00000800
#define AM_REG_TPIU_TYPE_NRZVALID(n)                 (((uint32_t)(n) << 11) & 0x00000800)

// 1 Indicates Manchester support.
#define AM_REG_TPIU_TYPE_MANCVALID_S                 10
#define AM_REG_TPIU_TYPE_MANCVALID_M                 0x00000400
#define AM_REG_TPIU_TYPE_MANCVALID(n)                (((uint32_t)(n) << 10) & 0x00000400)

// 0 Indicates Parallel Trace support.
#define AM_REG_TPIU_TYPE_PTINVALID_S                 9
#define AM_REG_TPIU_TYPE_PTINVALID_M                 0x00000200
#define AM_REG_TPIU_TYPE_PTINVALID(n)                (((uint32_t)(n) << 9) & 0x00000200)

// FIFO Size reported as a power of two. For instance, 0x3 indicates a FIFO size
// of 8 bytes.
#define AM_REG_TPIU_TYPE_FIFOSZ_S                    6
#define AM_REG_TPIU_TYPE_FIFOSZ_M                    0x000001C0
#define AM_REG_TPIU_TYPE_FIFOSZ(n)                   (((uint32_t)(n) << 6) & 0x000001C0)

#endif // AM_REG_TPIU_H
