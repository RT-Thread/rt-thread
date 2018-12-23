//*****************************************************************************
//
//  am_reg_nvic.h
//! @file
//!
//! @brief Register macros for the NVIC module
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
#ifndef AM_REG_NVIC_H
#define AM_REG_NVIC_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_NVIC_NUM_MODULES                      1
#define AM_REG_NVICn(n) \
    (REG_NVIC_BASEADDR + 0x00000000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_NVIC_ISER0_O                          0xE000E100
#define AM_REG_NVIC_ICER0_O                          0xE000E180
#define AM_REG_NVIC_ISPR0_O                          0xE000E200
#define AM_REG_NVIC_ICPR0_O                          0xE000E280
#define AM_REG_NVIC_IABR0_O                          0xE000E300
#define AM_REG_NVIC_IPR0_O                           0xE000E400
#define AM_REG_NVIC_IPR1_O                           0xE000E404
#define AM_REG_NVIC_IPR2_O                           0xE000E408
#define AM_REG_NVIC_IPR3_O                           0xE000E40C
#define AM_REG_NVIC_IPR4_O                           0xE000E410
#define AM_REG_NVIC_IPR5_O                           0xE000E414
#define AM_REG_NVIC_IPR6_O                           0xE000E418
#define AM_REG_NVIC_IPR7_O                           0xE000E41C

//*****************************************************************************
//
// NVIC_ISER0 - Interrupt Set-Enable Register 0
//
//*****************************************************************************
// NVIC_ISERn[31:0] are the set-enable bits for interrupts 31 through 0.
#define AM_REG_NVIC_ISER0_BITS_S                     0
#define AM_REG_NVIC_ISER0_BITS_M                     0xFFFFFFFF
#define AM_REG_NVIC_ISER0_BITS(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// NVIC_ICER0 - Interrupt Clear-Enable Register 0
//
//*****************************************************************************
// NVIC_ISERn[31:0] are the clear-enable bits for interrupts 31 through 0.
#define AM_REG_NVIC_ICER0_BITS_S                     0
#define AM_REG_NVIC_ICER0_BITS_M                     0xFFFFFFFF
#define AM_REG_NVIC_ICER0_BITS(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// NVIC_ISPR0 - Interrupt Set-Pending Register 0
//
//*****************************************************************************
// NVIC_ISERn[31:0] are the set-pending bits for interrupts 31 through 0.
#define AM_REG_NVIC_ISPR0_BITS_S                     0
#define AM_REG_NVIC_ISPR0_BITS_M                     0xFFFFFFFF
#define AM_REG_NVIC_ISPR0_BITS(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// NVIC_ICPR0 - Interrupt Clear-Pending Register 0
//
//*****************************************************************************
// NVIC_ISERn[31:0] are the clear-pending bits for interrupts 31 through 0.
#define AM_REG_NVIC_ICPR0_BITS_S                     0
#define AM_REG_NVIC_ICPR0_BITS_M                     0xFFFFFFFF
#define AM_REG_NVIC_ICPR0_BITS(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// NVIC_IABR0 - Interrupt Active Bit Register 0
//
//*****************************************************************************
// NVIC_ISERn[31:0] are the interrupt active bits for interrupts 31 through 0.
#define AM_REG_NVIC_IABR0_BITS_S                     0
#define AM_REG_NVIC_IABR0_BITS_M                     0xFFFFFFFF
#define AM_REG_NVIC_IABR0_BITS(n)                    (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// NVIC_IPR0 - Interrupt Priority Register 0
//
//*****************************************************************************
// Priority assignment for interrupt vector 3.
#define AM_REG_NVIC_IPR0_PRI_N3_S                    24
#define AM_REG_NVIC_IPR0_PRI_N3_M                    0xFF000000
#define AM_REG_NVIC_IPR0_PRI_N3(n)                   (((uint32_t)(n) << 24) & 0xFF000000)

// Priority assignment for interrupt vector 2.
#define AM_REG_NVIC_IPR0_PRI_N2_S                    16
#define AM_REG_NVIC_IPR0_PRI_N2_M                    0x00FF0000
#define AM_REG_NVIC_IPR0_PRI_N2(n)                   (((uint32_t)(n) << 16) & 0x00FF0000)

// Priority assignment for interrupt vector 1.
#define AM_REG_NVIC_IPR0_PRI_N1_S                    8
#define AM_REG_NVIC_IPR0_PRI_N1_M                    0x0000FF00
#define AM_REG_NVIC_IPR0_PRI_N1(n)                   (((uint32_t)(n) << 8) & 0x0000FF00)

// Priority assignment for interrupt vector 0.
#define AM_REG_NVIC_IPR0_PRI_N0_S                    0
#define AM_REG_NVIC_IPR0_PRI_N0_M                    0x000000FF
#define AM_REG_NVIC_IPR0_PRI_N0(n)                   (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// NVIC_IPR1 - Interrupt Priority Register 1
//
//*****************************************************************************
// Priority assignment for interrupt vector 7.
#define AM_REG_NVIC_IPR1_PRI_N3_S                    24
#define AM_REG_NVIC_IPR1_PRI_N3_M                    0xFF000000
#define AM_REG_NVIC_IPR1_PRI_N3(n)                   (((uint32_t)(n) << 24) & 0xFF000000)

// Priority assignment for interrupt vector 6.
#define AM_REG_NVIC_IPR1_PRI_N2_S                    16
#define AM_REG_NVIC_IPR1_PRI_N2_M                    0x00FF0000
#define AM_REG_NVIC_IPR1_PRI_N2(n)                   (((uint32_t)(n) << 16) & 0x00FF0000)

// Priority assignment for interrupt vector 5.
#define AM_REG_NVIC_IPR1_PRI_N1_S                    8
#define AM_REG_NVIC_IPR1_PRI_N1_M                    0x0000FF00
#define AM_REG_NVIC_IPR1_PRI_N1(n)                   (((uint32_t)(n) << 8) & 0x0000FF00)

// Priority assignment for interrupt vector 4.
#define AM_REG_NVIC_IPR1_PRI_N0_S                    0
#define AM_REG_NVIC_IPR1_PRI_N0_M                    0x000000FF
#define AM_REG_NVIC_IPR1_PRI_N0(n)                   (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// NVIC_IPR2 - Interrupt Priority Register 2
//
//*****************************************************************************
// Priority assignment for interrupt vector 11.
#define AM_REG_NVIC_IPR2_PRI_N3_S                    24
#define AM_REG_NVIC_IPR2_PRI_N3_M                    0xFF000000
#define AM_REG_NVIC_IPR2_PRI_N3(n)                   (((uint32_t)(n) << 24) & 0xFF000000)

// Priority assignment for interrupt vector 10.
#define AM_REG_NVIC_IPR2_PRI_N2_S                    16
#define AM_REG_NVIC_IPR2_PRI_N2_M                    0x00FF0000
#define AM_REG_NVIC_IPR2_PRI_N2(n)                   (((uint32_t)(n) << 16) & 0x00FF0000)

// Priority assignment for interrupt vector 9.
#define AM_REG_NVIC_IPR2_PRI_N1_S                    8
#define AM_REG_NVIC_IPR2_PRI_N1_M                    0x0000FF00
#define AM_REG_NVIC_IPR2_PRI_N1(n)                   (((uint32_t)(n) << 8) & 0x0000FF00)

// Priority assignment for interrupt vector 8.
#define AM_REG_NVIC_IPR2_PRI_N0_S                    0
#define AM_REG_NVIC_IPR2_PRI_N0_M                    0x000000FF
#define AM_REG_NVIC_IPR2_PRI_N0(n)                   (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// NVIC_IPR3 - Interrupt Priority Register 3
//
//*****************************************************************************
// Priority assignment for interrupt vector 15.
#define AM_REG_NVIC_IPR3_PRI_N3_S                    24
#define AM_REG_NVIC_IPR3_PRI_N3_M                    0xFF000000
#define AM_REG_NVIC_IPR3_PRI_N3(n)                   (((uint32_t)(n) << 24) & 0xFF000000)

// Priority assignment for interrupt vector 14.
#define AM_REG_NVIC_IPR3_PRI_N2_S                    16
#define AM_REG_NVIC_IPR3_PRI_N2_M                    0x00FF0000
#define AM_REG_NVIC_IPR3_PRI_N2(n)                   (((uint32_t)(n) << 16) & 0x00FF0000)

// Priority assignment for interrupt vector 13.
#define AM_REG_NVIC_IPR3_PRI_N1_S                    8
#define AM_REG_NVIC_IPR3_PRI_N1_M                    0x0000FF00
#define AM_REG_NVIC_IPR3_PRI_N1(n)                   (((uint32_t)(n) << 8) & 0x0000FF00)

// Priority assignment for interrupt vector 12.
#define AM_REG_NVIC_IPR3_PRI_N0_S                    0
#define AM_REG_NVIC_IPR3_PRI_N0_M                    0x000000FF
#define AM_REG_NVIC_IPR3_PRI_N0(n)                   (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// NVIC_IPR4 - Interrupt Priority Register 4
//
//*****************************************************************************
// Priority assignment for interrupt vector 19.
#define AM_REG_NVIC_IPR4_PRI_N3_S                    24
#define AM_REG_NVIC_IPR4_PRI_N3_M                    0xFF000000
#define AM_REG_NVIC_IPR4_PRI_N3(n)                   (((uint32_t)(n) << 24) & 0xFF000000)

// Priority assignment for interrupt vector 18.
#define AM_REG_NVIC_IPR4_PRI_N2_S                    16
#define AM_REG_NVIC_IPR4_PRI_N2_M                    0x00FF0000
#define AM_REG_NVIC_IPR4_PRI_N2(n)                   (((uint32_t)(n) << 16) & 0x00FF0000)

// Priority assignment for interrupt vector 17.
#define AM_REG_NVIC_IPR4_PRI_N1_S                    8
#define AM_REG_NVIC_IPR4_PRI_N1_M                    0x0000FF00
#define AM_REG_NVIC_IPR4_PRI_N1(n)                   (((uint32_t)(n) << 8) & 0x0000FF00)

// Priority assignment for interrupt vector 16.
#define AM_REG_NVIC_IPR4_PRI_N0_S                    0
#define AM_REG_NVIC_IPR4_PRI_N0_M                    0x000000FF
#define AM_REG_NVIC_IPR4_PRI_N0(n)                   (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// NVIC_IPR5 - Interrupt Priority Register 5
//
//*****************************************************************************
// Priority assignment for interrupt vector 23.
#define AM_REG_NVIC_IPR5_PRI_N3_S                    24
#define AM_REG_NVIC_IPR5_PRI_N3_M                    0xFF000000
#define AM_REG_NVIC_IPR5_PRI_N3(n)                   (((uint32_t)(n) << 24) & 0xFF000000)

// Priority assignment for interrupt vector 22.
#define AM_REG_NVIC_IPR5_PRI_N2_S                    16
#define AM_REG_NVIC_IPR5_PRI_N2_M                    0x00FF0000
#define AM_REG_NVIC_IPR5_PRI_N2(n)                   (((uint32_t)(n) << 16) & 0x00FF0000)

// Priority assignment for interrupt vector 21.
#define AM_REG_NVIC_IPR5_PRI_N1_S                    8
#define AM_REG_NVIC_IPR5_PRI_N1_M                    0x0000FF00
#define AM_REG_NVIC_IPR5_PRI_N1(n)                   (((uint32_t)(n) << 8) & 0x0000FF00)

// Priority assignment for interrupt vector 20.
#define AM_REG_NVIC_IPR5_PRI_N0_S                    0
#define AM_REG_NVIC_IPR5_PRI_N0_M                    0x000000FF
#define AM_REG_NVIC_IPR5_PRI_N0(n)                   (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// NVIC_IPR6 - Interrupt Priority Register 6
//
//*****************************************************************************
// Priority assignment for interrupt vector 27.
#define AM_REG_NVIC_IPR6_PRI_N3_S                    24
#define AM_REG_NVIC_IPR6_PRI_N3_M                    0xFF000000
#define AM_REG_NVIC_IPR6_PRI_N3(n)                   (((uint32_t)(n) << 24) & 0xFF000000)

// Priority assignment for interrupt vector 26.
#define AM_REG_NVIC_IPR6_PRI_N2_S                    16
#define AM_REG_NVIC_IPR6_PRI_N2_M                    0x00FF0000
#define AM_REG_NVIC_IPR6_PRI_N2(n)                   (((uint32_t)(n) << 16) & 0x00FF0000)

// Priority assignment for interrupt vector 25.
#define AM_REG_NVIC_IPR6_PRI_N1_S                    8
#define AM_REG_NVIC_IPR6_PRI_N1_M                    0x0000FF00
#define AM_REG_NVIC_IPR6_PRI_N1(n)                   (((uint32_t)(n) << 8) & 0x0000FF00)

// Priority assignment for interrupt vector 24.
#define AM_REG_NVIC_IPR6_PRI_N0_S                    0
#define AM_REG_NVIC_IPR6_PRI_N0_M                    0x000000FF
#define AM_REG_NVIC_IPR6_PRI_N0(n)                   (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// NVIC_IPR7 - Interrupt Priority Register 7
//
//*****************************************************************************
// Priority assignment for interrupt vector 31.
#define AM_REG_NVIC_IPR7_PRI_N3_S                    24
#define AM_REG_NVIC_IPR7_PRI_N3_M                    0xFF000000
#define AM_REG_NVIC_IPR7_PRI_N3(n)                   (((uint32_t)(n) << 24) & 0xFF000000)

// Priority assignment for interrupt vector 30.
#define AM_REG_NVIC_IPR7_PRI_N2_S                    16
#define AM_REG_NVIC_IPR7_PRI_N2_M                    0x00FF0000
#define AM_REG_NVIC_IPR7_PRI_N2(n)                   (((uint32_t)(n) << 16) & 0x00FF0000)

// Priority assignment for interrupt vector 29.
#define AM_REG_NVIC_IPR7_PRI_N1_S                    8
#define AM_REG_NVIC_IPR7_PRI_N1_M                    0x0000FF00
#define AM_REG_NVIC_IPR7_PRI_N1(n)                   (((uint32_t)(n) << 8) & 0x0000FF00)

// Priority assignment for interrupt vector 28.
#define AM_REG_NVIC_IPR7_PRI_N0_S                    0
#define AM_REG_NVIC_IPR7_PRI_N0_M                    0x000000FF
#define AM_REG_NVIC_IPR7_PRI_N0(n)                   (((uint32_t)(n) << 0) & 0x000000FF)

#endif // AM_REG_NVIC_H
