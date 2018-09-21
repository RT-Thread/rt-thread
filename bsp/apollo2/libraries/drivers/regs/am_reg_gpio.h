//*****************************************************************************
//
//  am_reg_gpio.h
//! @file
//!
//! @brief Register macros for the GPIO module
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
#ifndef AM_REG_GPIO_H
#define AM_REG_GPIO_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_GPIO_NUM_MODULES                      1
#define AM_REG_GPIOn(n) \
    (REG_GPIO_BASEADDR + 0x00000000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_GPIO_PADREGA_O                        0x00000000
#define AM_REG_GPIO_PADREGB_O                        0x00000004
#define AM_REG_GPIO_PADREGC_O                        0x00000008
#define AM_REG_GPIO_PADREGD_O                        0x0000000C
#define AM_REG_GPIO_PADREGE_O                        0x00000010
#define AM_REG_GPIO_PADREGF_O                        0x00000014
#define AM_REG_GPIO_PADREGG_O                        0x00000018
#define AM_REG_GPIO_PADREGH_O                        0x0000001C
#define AM_REG_GPIO_PADREGI_O                        0x00000020
#define AM_REG_GPIO_PADREGJ_O                        0x00000024
#define AM_REG_GPIO_PADREGK_O                        0x00000028
#define AM_REG_GPIO_PADREGL_O                        0x0000002C
#define AM_REG_GPIO_PADREGM_O                        0x00000030
#define AM_REG_GPIO_CFGA_O                           0x00000040
#define AM_REG_GPIO_CFGB_O                           0x00000044
#define AM_REG_GPIO_CFGC_O                           0x00000048
#define AM_REG_GPIO_CFGD_O                           0x0000004C
#define AM_REG_GPIO_CFGE_O                           0x00000050
#define AM_REG_GPIO_CFGF_O                           0x00000054
#define AM_REG_GPIO_CFGG_O                           0x00000058
#define AM_REG_GPIO_RDA_O                            0x00000080
#define AM_REG_GPIO_RDB_O                            0x00000084
#define AM_REG_GPIO_WTA_O                            0x00000088
#define AM_REG_GPIO_WTB_O                            0x0000008C
#define AM_REG_GPIO_WTSA_O                           0x00000090
#define AM_REG_GPIO_WTSB_O                           0x00000094
#define AM_REG_GPIO_WTCA_O                           0x00000098
#define AM_REG_GPIO_WTCB_O                           0x0000009C
#define AM_REG_GPIO_ENA_O                            0x000000A0
#define AM_REG_GPIO_ENB_O                            0x000000A4
#define AM_REG_GPIO_ENSA_O                           0x000000A8
#define AM_REG_GPIO_ENSB_O                           0x000000AC
#define AM_REG_GPIO_ENCA_O                           0x000000B4
#define AM_REG_GPIO_ENCB_O                           0x000000B8
#define AM_REG_GPIO_STMRCAP_O                        0x000000BC
#define AM_REG_GPIO_IOM0IRQ_O                        0x000000C0
#define AM_REG_GPIO_IOM1IRQ_O                        0x000000C4
#define AM_REG_GPIO_IOM2IRQ_O                        0x000000C8
#define AM_REG_GPIO_IOM3IRQ_O                        0x000000CC
#define AM_REG_GPIO_IOM4IRQ_O                        0x000000D0
#define AM_REG_GPIO_IOM5IRQ_O                        0x000000D4
#define AM_REG_GPIO_LOOPBACK_O                       0x000000D8
#define AM_REG_GPIO_GPIOOBS_O                        0x000000DC
#define AM_REG_GPIO_ALTPADCFGA_O                     0x000000E0
#define AM_REG_GPIO_ALTPADCFGB_O                     0x000000E4
#define AM_REG_GPIO_ALTPADCFGC_O                     0x000000E8
#define AM_REG_GPIO_ALTPADCFGD_O                     0x000000EC
#define AM_REG_GPIO_ALTPADCFGE_O                     0x000000F0
#define AM_REG_GPIO_ALTPADCFGF_O                     0x000000F4
#define AM_REG_GPIO_ALTPADCFGG_O                     0x000000F8
#define AM_REG_GPIO_ALTPADCFGH_O                     0x000000FC
#define AM_REG_GPIO_ALTPADCFGI_O                     0x00000100
#define AM_REG_GPIO_ALTPADCFGJ_O                     0x00000104
#define AM_REG_GPIO_ALTPADCFGK_O                     0x00000108
#define AM_REG_GPIO_ALTPADCFGL_O                     0x0000010C
#define AM_REG_GPIO_ALTPADCFGM_O                     0x00000110
#define AM_REG_GPIO_PADKEY_O                         0x00000060
#define AM_REG_GPIO_INT0EN_O                         0x00000200
#define AM_REG_GPIO_INT0STAT_O                       0x00000204
#define AM_REG_GPIO_INT0CLR_O                        0x00000208
#define AM_REG_GPIO_INT0SET_O                        0x0000020C
#define AM_REG_GPIO_INT1EN_O                         0x00000210
#define AM_REG_GPIO_INT1STAT_O                       0x00000214
#define AM_REG_GPIO_INT1CLR_O                        0x00000218
#define AM_REG_GPIO_INT1SET_O                        0x0000021C

//*****************************************************************************
//
// Key values.
//
//*****************************************************************************
#define AM_REG_GPIO_PADKEY_KEYVAL                    0x00000073

//*****************************************************************************
//
// GPIO_INT0EN - GPIO Interrupt Registers 31-0: Enable
//
//*****************************************************************************
// GPIO31 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO31_S                  31
#define AM_REG_GPIO_INT0EN_GPIO31_M                  0x80000000
#define AM_REG_GPIO_INT0EN_GPIO31(n)                 (((uint32_t)(n) << 31) & 0x80000000)

// GPIO30 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO30_S                  30
#define AM_REG_GPIO_INT0EN_GPIO30_M                  0x40000000
#define AM_REG_GPIO_INT0EN_GPIO30(n)                 (((uint32_t)(n) << 30) & 0x40000000)

// GPIO29 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO29_S                  29
#define AM_REG_GPIO_INT0EN_GPIO29_M                  0x20000000
#define AM_REG_GPIO_INT0EN_GPIO29(n)                 (((uint32_t)(n) << 29) & 0x20000000)

// GPIO28 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO28_S                  28
#define AM_REG_GPIO_INT0EN_GPIO28_M                  0x10000000
#define AM_REG_GPIO_INT0EN_GPIO28(n)                 (((uint32_t)(n) << 28) & 0x10000000)

// GPIO27 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO27_S                  27
#define AM_REG_GPIO_INT0EN_GPIO27_M                  0x08000000
#define AM_REG_GPIO_INT0EN_GPIO27(n)                 (((uint32_t)(n) << 27) & 0x08000000)

// GPIO26 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO26_S                  26
#define AM_REG_GPIO_INT0EN_GPIO26_M                  0x04000000
#define AM_REG_GPIO_INT0EN_GPIO26(n)                 (((uint32_t)(n) << 26) & 0x04000000)

// GPIO25 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO25_S                  25
#define AM_REG_GPIO_INT0EN_GPIO25_M                  0x02000000
#define AM_REG_GPIO_INT0EN_GPIO25(n)                 (((uint32_t)(n) << 25) & 0x02000000)

// GPIO24 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO24_S                  24
#define AM_REG_GPIO_INT0EN_GPIO24_M                  0x01000000
#define AM_REG_GPIO_INT0EN_GPIO24(n)                 (((uint32_t)(n) << 24) & 0x01000000)

// GPIO23 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO23_S                  23
#define AM_REG_GPIO_INT0EN_GPIO23_M                  0x00800000
#define AM_REG_GPIO_INT0EN_GPIO23(n)                 (((uint32_t)(n) << 23) & 0x00800000)

// GPIO22 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO22_S                  22
#define AM_REG_GPIO_INT0EN_GPIO22_M                  0x00400000
#define AM_REG_GPIO_INT0EN_GPIO22(n)                 (((uint32_t)(n) << 22) & 0x00400000)

// GPIO21 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO21_S                  21
#define AM_REG_GPIO_INT0EN_GPIO21_M                  0x00200000
#define AM_REG_GPIO_INT0EN_GPIO21(n)                 (((uint32_t)(n) << 21) & 0x00200000)

// GPIO20 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO20_S                  20
#define AM_REG_GPIO_INT0EN_GPIO20_M                  0x00100000
#define AM_REG_GPIO_INT0EN_GPIO20(n)                 (((uint32_t)(n) << 20) & 0x00100000)

// GPIO19 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO19_S                  19
#define AM_REG_GPIO_INT0EN_GPIO19_M                  0x00080000
#define AM_REG_GPIO_INT0EN_GPIO19(n)                 (((uint32_t)(n) << 19) & 0x00080000)

// GPIO18interrupt.
#define AM_REG_GPIO_INT0EN_GPIO18_S                  18
#define AM_REG_GPIO_INT0EN_GPIO18_M                  0x00040000
#define AM_REG_GPIO_INT0EN_GPIO18(n)                 (((uint32_t)(n) << 18) & 0x00040000)

// GPIO17 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO17_S                  17
#define AM_REG_GPIO_INT0EN_GPIO17_M                  0x00020000
#define AM_REG_GPIO_INT0EN_GPIO17(n)                 (((uint32_t)(n) << 17) & 0x00020000)

// GPIO16 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO16_S                  16
#define AM_REG_GPIO_INT0EN_GPIO16_M                  0x00010000
#define AM_REG_GPIO_INT0EN_GPIO16(n)                 (((uint32_t)(n) << 16) & 0x00010000)

// GPIO15 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO15_S                  15
#define AM_REG_GPIO_INT0EN_GPIO15_M                  0x00008000
#define AM_REG_GPIO_INT0EN_GPIO15(n)                 (((uint32_t)(n) << 15) & 0x00008000)

// GPIO14 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO14_S                  14
#define AM_REG_GPIO_INT0EN_GPIO14_M                  0x00004000
#define AM_REG_GPIO_INT0EN_GPIO14(n)                 (((uint32_t)(n) << 14) & 0x00004000)

// GPIO13 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO13_S                  13
#define AM_REG_GPIO_INT0EN_GPIO13_M                  0x00002000
#define AM_REG_GPIO_INT0EN_GPIO13(n)                 (((uint32_t)(n) << 13) & 0x00002000)

// GPIO12 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO12_S                  12
#define AM_REG_GPIO_INT0EN_GPIO12_M                  0x00001000
#define AM_REG_GPIO_INT0EN_GPIO12(n)                 (((uint32_t)(n) << 12) & 0x00001000)

// GPIO11 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO11_S                  11
#define AM_REG_GPIO_INT0EN_GPIO11_M                  0x00000800
#define AM_REG_GPIO_INT0EN_GPIO11(n)                 (((uint32_t)(n) << 11) & 0x00000800)

// GPIO10 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO10_S                  10
#define AM_REG_GPIO_INT0EN_GPIO10_M                  0x00000400
#define AM_REG_GPIO_INT0EN_GPIO10(n)                 (((uint32_t)(n) << 10) & 0x00000400)

// GPIO9 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO9_S                   9
#define AM_REG_GPIO_INT0EN_GPIO9_M                   0x00000200
#define AM_REG_GPIO_INT0EN_GPIO9(n)                  (((uint32_t)(n) << 9) & 0x00000200)

// GPIO8 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO8_S                   8
#define AM_REG_GPIO_INT0EN_GPIO8_M                   0x00000100
#define AM_REG_GPIO_INT0EN_GPIO8(n)                  (((uint32_t)(n) << 8) & 0x00000100)

// GPIO7 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO7_S                   7
#define AM_REG_GPIO_INT0EN_GPIO7_M                   0x00000080
#define AM_REG_GPIO_INT0EN_GPIO7(n)                  (((uint32_t)(n) << 7) & 0x00000080)

// GPIO6 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO6_S                   6
#define AM_REG_GPIO_INT0EN_GPIO6_M                   0x00000040
#define AM_REG_GPIO_INT0EN_GPIO6(n)                  (((uint32_t)(n) << 6) & 0x00000040)

// GPIO5 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO5_S                   5
#define AM_REG_GPIO_INT0EN_GPIO5_M                   0x00000020
#define AM_REG_GPIO_INT0EN_GPIO5(n)                  (((uint32_t)(n) << 5) & 0x00000020)

// GPIO4 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO4_S                   4
#define AM_REG_GPIO_INT0EN_GPIO4_M                   0x00000010
#define AM_REG_GPIO_INT0EN_GPIO4(n)                  (((uint32_t)(n) << 4) & 0x00000010)

// GPIO3 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO3_S                   3
#define AM_REG_GPIO_INT0EN_GPIO3_M                   0x00000008
#define AM_REG_GPIO_INT0EN_GPIO3(n)                  (((uint32_t)(n) << 3) & 0x00000008)

// GPIO2 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO2_S                   2
#define AM_REG_GPIO_INT0EN_GPIO2_M                   0x00000004
#define AM_REG_GPIO_INT0EN_GPIO2(n)                  (((uint32_t)(n) << 2) & 0x00000004)

// GPIO1 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO1_S                   1
#define AM_REG_GPIO_INT0EN_GPIO1_M                   0x00000002
#define AM_REG_GPIO_INT0EN_GPIO1(n)                  (((uint32_t)(n) << 1) & 0x00000002)

// GPIO0 interrupt.
#define AM_REG_GPIO_INT0EN_GPIO0_S                   0
#define AM_REG_GPIO_INT0EN_GPIO0_M                   0x00000001
#define AM_REG_GPIO_INT0EN_GPIO0(n)                  (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_INT0STAT - GPIO Interrupt Registers 31-0: Status
//
//*****************************************************************************
// GPIO31 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO31_S                31
#define AM_REG_GPIO_INT0STAT_GPIO31_M                0x80000000
#define AM_REG_GPIO_INT0STAT_GPIO31(n)               (((uint32_t)(n) << 31) & 0x80000000)

// GPIO30 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO30_S                30
#define AM_REG_GPIO_INT0STAT_GPIO30_M                0x40000000
#define AM_REG_GPIO_INT0STAT_GPIO30(n)               (((uint32_t)(n) << 30) & 0x40000000)

// GPIO29 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO29_S                29
#define AM_REG_GPIO_INT0STAT_GPIO29_M                0x20000000
#define AM_REG_GPIO_INT0STAT_GPIO29(n)               (((uint32_t)(n) << 29) & 0x20000000)

// GPIO28 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO28_S                28
#define AM_REG_GPIO_INT0STAT_GPIO28_M                0x10000000
#define AM_REG_GPIO_INT0STAT_GPIO28(n)               (((uint32_t)(n) << 28) & 0x10000000)

// GPIO27 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO27_S                27
#define AM_REG_GPIO_INT0STAT_GPIO27_M                0x08000000
#define AM_REG_GPIO_INT0STAT_GPIO27(n)               (((uint32_t)(n) << 27) & 0x08000000)

// GPIO26 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO26_S                26
#define AM_REG_GPIO_INT0STAT_GPIO26_M                0x04000000
#define AM_REG_GPIO_INT0STAT_GPIO26(n)               (((uint32_t)(n) << 26) & 0x04000000)

// GPIO25 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO25_S                25
#define AM_REG_GPIO_INT0STAT_GPIO25_M                0x02000000
#define AM_REG_GPIO_INT0STAT_GPIO25(n)               (((uint32_t)(n) << 25) & 0x02000000)

// GPIO24 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO24_S                24
#define AM_REG_GPIO_INT0STAT_GPIO24_M                0x01000000
#define AM_REG_GPIO_INT0STAT_GPIO24(n)               (((uint32_t)(n) << 24) & 0x01000000)

// GPIO23 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO23_S                23
#define AM_REG_GPIO_INT0STAT_GPIO23_M                0x00800000
#define AM_REG_GPIO_INT0STAT_GPIO23(n)               (((uint32_t)(n) << 23) & 0x00800000)

// GPIO22 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO22_S                22
#define AM_REG_GPIO_INT0STAT_GPIO22_M                0x00400000
#define AM_REG_GPIO_INT0STAT_GPIO22(n)               (((uint32_t)(n) << 22) & 0x00400000)

// GPIO21 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO21_S                21
#define AM_REG_GPIO_INT0STAT_GPIO21_M                0x00200000
#define AM_REG_GPIO_INT0STAT_GPIO21(n)               (((uint32_t)(n) << 21) & 0x00200000)

// GPIO20 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO20_S                20
#define AM_REG_GPIO_INT0STAT_GPIO20_M                0x00100000
#define AM_REG_GPIO_INT0STAT_GPIO20(n)               (((uint32_t)(n) << 20) & 0x00100000)

// GPIO19 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO19_S                19
#define AM_REG_GPIO_INT0STAT_GPIO19_M                0x00080000
#define AM_REG_GPIO_INT0STAT_GPIO19(n)               (((uint32_t)(n) << 19) & 0x00080000)

// GPIO18interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO18_S                18
#define AM_REG_GPIO_INT0STAT_GPIO18_M                0x00040000
#define AM_REG_GPIO_INT0STAT_GPIO18(n)               (((uint32_t)(n) << 18) & 0x00040000)

// GPIO17 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO17_S                17
#define AM_REG_GPIO_INT0STAT_GPIO17_M                0x00020000
#define AM_REG_GPIO_INT0STAT_GPIO17(n)               (((uint32_t)(n) << 17) & 0x00020000)

// GPIO16 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO16_S                16
#define AM_REG_GPIO_INT0STAT_GPIO16_M                0x00010000
#define AM_REG_GPIO_INT0STAT_GPIO16(n)               (((uint32_t)(n) << 16) & 0x00010000)

// GPIO15 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO15_S                15
#define AM_REG_GPIO_INT0STAT_GPIO15_M                0x00008000
#define AM_REG_GPIO_INT0STAT_GPIO15(n)               (((uint32_t)(n) << 15) & 0x00008000)

// GPIO14 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO14_S                14
#define AM_REG_GPIO_INT0STAT_GPIO14_M                0x00004000
#define AM_REG_GPIO_INT0STAT_GPIO14(n)               (((uint32_t)(n) << 14) & 0x00004000)

// GPIO13 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO13_S                13
#define AM_REG_GPIO_INT0STAT_GPIO13_M                0x00002000
#define AM_REG_GPIO_INT0STAT_GPIO13(n)               (((uint32_t)(n) << 13) & 0x00002000)

// GPIO12 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO12_S                12
#define AM_REG_GPIO_INT0STAT_GPIO12_M                0x00001000
#define AM_REG_GPIO_INT0STAT_GPIO12(n)               (((uint32_t)(n) << 12) & 0x00001000)

// GPIO11 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO11_S                11
#define AM_REG_GPIO_INT0STAT_GPIO11_M                0x00000800
#define AM_REG_GPIO_INT0STAT_GPIO11(n)               (((uint32_t)(n) << 11) & 0x00000800)

// GPIO10 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO10_S                10
#define AM_REG_GPIO_INT0STAT_GPIO10_M                0x00000400
#define AM_REG_GPIO_INT0STAT_GPIO10(n)               (((uint32_t)(n) << 10) & 0x00000400)

// GPIO9 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO9_S                 9
#define AM_REG_GPIO_INT0STAT_GPIO9_M                 0x00000200
#define AM_REG_GPIO_INT0STAT_GPIO9(n)                (((uint32_t)(n) << 9) & 0x00000200)

// GPIO8 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO8_S                 8
#define AM_REG_GPIO_INT0STAT_GPIO8_M                 0x00000100
#define AM_REG_GPIO_INT0STAT_GPIO8(n)                (((uint32_t)(n) << 8) & 0x00000100)

// GPIO7 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO7_S                 7
#define AM_REG_GPIO_INT0STAT_GPIO7_M                 0x00000080
#define AM_REG_GPIO_INT0STAT_GPIO7(n)                (((uint32_t)(n) << 7) & 0x00000080)

// GPIO6 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO6_S                 6
#define AM_REG_GPIO_INT0STAT_GPIO6_M                 0x00000040
#define AM_REG_GPIO_INT0STAT_GPIO6(n)                (((uint32_t)(n) << 6) & 0x00000040)

// GPIO5 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO5_S                 5
#define AM_REG_GPIO_INT0STAT_GPIO5_M                 0x00000020
#define AM_REG_GPIO_INT0STAT_GPIO5(n)                (((uint32_t)(n) << 5) & 0x00000020)

// GPIO4 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO4_S                 4
#define AM_REG_GPIO_INT0STAT_GPIO4_M                 0x00000010
#define AM_REG_GPIO_INT0STAT_GPIO4(n)                (((uint32_t)(n) << 4) & 0x00000010)

// GPIO3 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO3_S                 3
#define AM_REG_GPIO_INT0STAT_GPIO3_M                 0x00000008
#define AM_REG_GPIO_INT0STAT_GPIO3(n)                (((uint32_t)(n) << 3) & 0x00000008)

// GPIO2 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO2_S                 2
#define AM_REG_GPIO_INT0STAT_GPIO2_M                 0x00000004
#define AM_REG_GPIO_INT0STAT_GPIO2(n)                (((uint32_t)(n) << 2) & 0x00000004)

// GPIO1 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO1_S                 1
#define AM_REG_GPIO_INT0STAT_GPIO1_M                 0x00000002
#define AM_REG_GPIO_INT0STAT_GPIO1(n)                (((uint32_t)(n) << 1) & 0x00000002)

// GPIO0 interrupt.
#define AM_REG_GPIO_INT0STAT_GPIO0_S                 0
#define AM_REG_GPIO_INT0STAT_GPIO0_M                 0x00000001
#define AM_REG_GPIO_INT0STAT_GPIO0(n)                (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_INT0CLR - GPIO Interrupt Registers 31-0: Clear
//
//*****************************************************************************
// GPIO31 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO31_S                 31
#define AM_REG_GPIO_INT0CLR_GPIO31_M                 0x80000000
#define AM_REG_GPIO_INT0CLR_GPIO31(n)                (((uint32_t)(n) << 31) & 0x80000000)

// GPIO30 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO30_S                 30
#define AM_REG_GPIO_INT0CLR_GPIO30_M                 0x40000000
#define AM_REG_GPIO_INT0CLR_GPIO30(n)                (((uint32_t)(n) << 30) & 0x40000000)

// GPIO29 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO29_S                 29
#define AM_REG_GPIO_INT0CLR_GPIO29_M                 0x20000000
#define AM_REG_GPIO_INT0CLR_GPIO29(n)                (((uint32_t)(n) << 29) & 0x20000000)

// GPIO28 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO28_S                 28
#define AM_REG_GPIO_INT0CLR_GPIO28_M                 0x10000000
#define AM_REG_GPIO_INT0CLR_GPIO28(n)                (((uint32_t)(n) << 28) & 0x10000000)

// GPIO27 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO27_S                 27
#define AM_REG_GPIO_INT0CLR_GPIO27_M                 0x08000000
#define AM_REG_GPIO_INT0CLR_GPIO27(n)                (((uint32_t)(n) << 27) & 0x08000000)

// GPIO26 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO26_S                 26
#define AM_REG_GPIO_INT0CLR_GPIO26_M                 0x04000000
#define AM_REG_GPIO_INT0CLR_GPIO26(n)                (((uint32_t)(n) << 26) & 0x04000000)

// GPIO25 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO25_S                 25
#define AM_REG_GPIO_INT0CLR_GPIO25_M                 0x02000000
#define AM_REG_GPIO_INT0CLR_GPIO25(n)                (((uint32_t)(n) << 25) & 0x02000000)

// GPIO24 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO24_S                 24
#define AM_REG_GPIO_INT0CLR_GPIO24_M                 0x01000000
#define AM_REG_GPIO_INT0CLR_GPIO24(n)                (((uint32_t)(n) << 24) & 0x01000000)

// GPIO23 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO23_S                 23
#define AM_REG_GPIO_INT0CLR_GPIO23_M                 0x00800000
#define AM_REG_GPIO_INT0CLR_GPIO23(n)                (((uint32_t)(n) << 23) & 0x00800000)

// GPIO22 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO22_S                 22
#define AM_REG_GPIO_INT0CLR_GPIO22_M                 0x00400000
#define AM_REG_GPIO_INT0CLR_GPIO22(n)                (((uint32_t)(n) << 22) & 0x00400000)

// GPIO21 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO21_S                 21
#define AM_REG_GPIO_INT0CLR_GPIO21_M                 0x00200000
#define AM_REG_GPIO_INT0CLR_GPIO21(n)                (((uint32_t)(n) << 21) & 0x00200000)

// GPIO20 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO20_S                 20
#define AM_REG_GPIO_INT0CLR_GPIO20_M                 0x00100000
#define AM_REG_GPIO_INT0CLR_GPIO20(n)                (((uint32_t)(n) << 20) & 0x00100000)

// GPIO19 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO19_S                 19
#define AM_REG_GPIO_INT0CLR_GPIO19_M                 0x00080000
#define AM_REG_GPIO_INT0CLR_GPIO19(n)                (((uint32_t)(n) << 19) & 0x00080000)

// GPIO18interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO18_S                 18
#define AM_REG_GPIO_INT0CLR_GPIO18_M                 0x00040000
#define AM_REG_GPIO_INT0CLR_GPIO18(n)                (((uint32_t)(n) << 18) & 0x00040000)

// GPIO17 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO17_S                 17
#define AM_REG_GPIO_INT0CLR_GPIO17_M                 0x00020000
#define AM_REG_GPIO_INT0CLR_GPIO17(n)                (((uint32_t)(n) << 17) & 0x00020000)

// GPIO16 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO16_S                 16
#define AM_REG_GPIO_INT0CLR_GPIO16_M                 0x00010000
#define AM_REG_GPIO_INT0CLR_GPIO16(n)                (((uint32_t)(n) << 16) & 0x00010000)

// GPIO15 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO15_S                 15
#define AM_REG_GPIO_INT0CLR_GPIO15_M                 0x00008000
#define AM_REG_GPIO_INT0CLR_GPIO15(n)                (((uint32_t)(n) << 15) & 0x00008000)

// GPIO14 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO14_S                 14
#define AM_REG_GPIO_INT0CLR_GPIO14_M                 0x00004000
#define AM_REG_GPIO_INT0CLR_GPIO14(n)                (((uint32_t)(n) << 14) & 0x00004000)

// GPIO13 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO13_S                 13
#define AM_REG_GPIO_INT0CLR_GPIO13_M                 0x00002000
#define AM_REG_GPIO_INT0CLR_GPIO13(n)                (((uint32_t)(n) << 13) & 0x00002000)

// GPIO12 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO12_S                 12
#define AM_REG_GPIO_INT0CLR_GPIO12_M                 0x00001000
#define AM_REG_GPIO_INT0CLR_GPIO12(n)                (((uint32_t)(n) << 12) & 0x00001000)

// GPIO11 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO11_S                 11
#define AM_REG_GPIO_INT0CLR_GPIO11_M                 0x00000800
#define AM_REG_GPIO_INT0CLR_GPIO11(n)                (((uint32_t)(n) << 11) & 0x00000800)

// GPIO10 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO10_S                 10
#define AM_REG_GPIO_INT0CLR_GPIO10_M                 0x00000400
#define AM_REG_GPIO_INT0CLR_GPIO10(n)                (((uint32_t)(n) << 10) & 0x00000400)

// GPIO9 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO9_S                  9
#define AM_REG_GPIO_INT0CLR_GPIO9_M                  0x00000200
#define AM_REG_GPIO_INT0CLR_GPIO9(n)                 (((uint32_t)(n) << 9) & 0x00000200)

// GPIO8 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO8_S                  8
#define AM_REG_GPIO_INT0CLR_GPIO8_M                  0x00000100
#define AM_REG_GPIO_INT0CLR_GPIO8(n)                 (((uint32_t)(n) << 8) & 0x00000100)

// GPIO7 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO7_S                  7
#define AM_REG_GPIO_INT0CLR_GPIO7_M                  0x00000080
#define AM_REG_GPIO_INT0CLR_GPIO7(n)                 (((uint32_t)(n) << 7) & 0x00000080)

// GPIO6 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO6_S                  6
#define AM_REG_GPIO_INT0CLR_GPIO6_M                  0x00000040
#define AM_REG_GPIO_INT0CLR_GPIO6(n)                 (((uint32_t)(n) << 6) & 0x00000040)

// GPIO5 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO5_S                  5
#define AM_REG_GPIO_INT0CLR_GPIO5_M                  0x00000020
#define AM_REG_GPIO_INT0CLR_GPIO5(n)                 (((uint32_t)(n) << 5) & 0x00000020)

// GPIO4 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO4_S                  4
#define AM_REG_GPIO_INT0CLR_GPIO4_M                  0x00000010
#define AM_REG_GPIO_INT0CLR_GPIO4(n)                 (((uint32_t)(n) << 4) & 0x00000010)

// GPIO3 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO3_S                  3
#define AM_REG_GPIO_INT0CLR_GPIO3_M                  0x00000008
#define AM_REG_GPIO_INT0CLR_GPIO3(n)                 (((uint32_t)(n) << 3) & 0x00000008)

// GPIO2 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO2_S                  2
#define AM_REG_GPIO_INT0CLR_GPIO2_M                  0x00000004
#define AM_REG_GPIO_INT0CLR_GPIO2(n)                 (((uint32_t)(n) << 2) & 0x00000004)

// GPIO1 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO1_S                  1
#define AM_REG_GPIO_INT0CLR_GPIO1_M                  0x00000002
#define AM_REG_GPIO_INT0CLR_GPIO1(n)                 (((uint32_t)(n) << 1) & 0x00000002)

// GPIO0 interrupt.
#define AM_REG_GPIO_INT0CLR_GPIO0_S                  0
#define AM_REG_GPIO_INT0CLR_GPIO0_M                  0x00000001
#define AM_REG_GPIO_INT0CLR_GPIO0(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_INT0SET - GPIO Interrupt Registers 31-0: Set
//
//*****************************************************************************
// GPIO31 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO31_S                 31
#define AM_REG_GPIO_INT0SET_GPIO31_M                 0x80000000
#define AM_REG_GPIO_INT0SET_GPIO31(n)                (((uint32_t)(n) << 31) & 0x80000000)

// GPIO30 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO30_S                 30
#define AM_REG_GPIO_INT0SET_GPIO30_M                 0x40000000
#define AM_REG_GPIO_INT0SET_GPIO30(n)                (((uint32_t)(n) << 30) & 0x40000000)

// GPIO29 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO29_S                 29
#define AM_REG_GPIO_INT0SET_GPIO29_M                 0x20000000
#define AM_REG_GPIO_INT0SET_GPIO29(n)                (((uint32_t)(n) << 29) & 0x20000000)

// GPIO28 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO28_S                 28
#define AM_REG_GPIO_INT0SET_GPIO28_M                 0x10000000
#define AM_REG_GPIO_INT0SET_GPIO28(n)                (((uint32_t)(n) << 28) & 0x10000000)

// GPIO27 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO27_S                 27
#define AM_REG_GPIO_INT0SET_GPIO27_M                 0x08000000
#define AM_REG_GPIO_INT0SET_GPIO27(n)                (((uint32_t)(n) << 27) & 0x08000000)

// GPIO26 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO26_S                 26
#define AM_REG_GPIO_INT0SET_GPIO26_M                 0x04000000
#define AM_REG_GPIO_INT0SET_GPIO26(n)                (((uint32_t)(n) << 26) & 0x04000000)

// GPIO25 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO25_S                 25
#define AM_REG_GPIO_INT0SET_GPIO25_M                 0x02000000
#define AM_REG_GPIO_INT0SET_GPIO25(n)                (((uint32_t)(n) << 25) & 0x02000000)

// GPIO24 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO24_S                 24
#define AM_REG_GPIO_INT0SET_GPIO24_M                 0x01000000
#define AM_REG_GPIO_INT0SET_GPIO24(n)                (((uint32_t)(n) << 24) & 0x01000000)

// GPIO23 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO23_S                 23
#define AM_REG_GPIO_INT0SET_GPIO23_M                 0x00800000
#define AM_REG_GPIO_INT0SET_GPIO23(n)                (((uint32_t)(n) << 23) & 0x00800000)

// GPIO22 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO22_S                 22
#define AM_REG_GPIO_INT0SET_GPIO22_M                 0x00400000
#define AM_REG_GPIO_INT0SET_GPIO22(n)                (((uint32_t)(n) << 22) & 0x00400000)

// GPIO21 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO21_S                 21
#define AM_REG_GPIO_INT0SET_GPIO21_M                 0x00200000
#define AM_REG_GPIO_INT0SET_GPIO21(n)                (((uint32_t)(n) << 21) & 0x00200000)

// GPIO20 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO20_S                 20
#define AM_REG_GPIO_INT0SET_GPIO20_M                 0x00100000
#define AM_REG_GPIO_INT0SET_GPIO20(n)                (((uint32_t)(n) << 20) & 0x00100000)

// GPIO19 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO19_S                 19
#define AM_REG_GPIO_INT0SET_GPIO19_M                 0x00080000
#define AM_REG_GPIO_INT0SET_GPIO19(n)                (((uint32_t)(n) << 19) & 0x00080000)

// GPIO18interrupt.
#define AM_REG_GPIO_INT0SET_GPIO18_S                 18
#define AM_REG_GPIO_INT0SET_GPIO18_M                 0x00040000
#define AM_REG_GPIO_INT0SET_GPIO18(n)                (((uint32_t)(n) << 18) & 0x00040000)

// GPIO17 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO17_S                 17
#define AM_REG_GPIO_INT0SET_GPIO17_M                 0x00020000
#define AM_REG_GPIO_INT0SET_GPIO17(n)                (((uint32_t)(n) << 17) & 0x00020000)

// GPIO16 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO16_S                 16
#define AM_REG_GPIO_INT0SET_GPIO16_M                 0x00010000
#define AM_REG_GPIO_INT0SET_GPIO16(n)                (((uint32_t)(n) << 16) & 0x00010000)

// GPIO15 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO15_S                 15
#define AM_REG_GPIO_INT0SET_GPIO15_M                 0x00008000
#define AM_REG_GPIO_INT0SET_GPIO15(n)                (((uint32_t)(n) << 15) & 0x00008000)

// GPIO14 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO14_S                 14
#define AM_REG_GPIO_INT0SET_GPIO14_M                 0x00004000
#define AM_REG_GPIO_INT0SET_GPIO14(n)                (((uint32_t)(n) << 14) & 0x00004000)

// GPIO13 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO13_S                 13
#define AM_REG_GPIO_INT0SET_GPIO13_M                 0x00002000
#define AM_REG_GPIO_INT0SET_GPIO13(n)                (((uint32_t)(n) << 13) & 0x00002000)

// GPIO12 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO12_S                 12
#define AM_REG_GPIO_INT0SET_GPIO12_M                 0x00001000
#define AM_REG_GPIO_INT0SET_GPIO12(n)                (((uint32_t)(n) << 12) & 0x00001000)

// GPIO11 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO11_S                 11
#define AM_REG_GPIO_INT0SET_GPIO11_M                 0x00000800
#define AM_REG_GPIO_INT0SET_GPIO11(n)                (((uint32_t)(n) << 11) & 0x00000800)

// GPIO10 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO10_S                 10
#define AM_REG_GPIO_INT0SET_GPIO10_M                 0x00000400
#define AM_REG_GPIO_INT0SET_GPIO10(n)                (((uint32_t)(n) << 10) & 0x00000400)

// GPIO9 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO9_S                  9
#define AM_REG_GPIO_INT0SET_GPIO9_M                  0x00000200
#define AM_REG_GPIO_INT0SET_GPIO9(n)                 (((uint32_t)(n) << 9) & 0x00000200)

// GPIO8 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO8_S                  8
#define AM_REG_GPIO_INT0SET_GPIO8_M                  0x00000100
#define AM_REG_GPIO_INT0SET_GPIO8(n)                 (((uint32_t)(n) << 8) & 0x00000100)

// GPIO7 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO7_S                  7
#define AM_REG_GPIO_INT0SET_GPIO7_M                  0x00000080
#define AM_REG_GPIO_INT0SET_GPIO7(n)                 (((uint32_t)(n) << 7) & 0x00000080)

// GPIO6 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO6_S                  6
#define AM_REG_GPIO_INT0SET_GPIO6_M                  0x00000040
#define AM_REG_GPIO_INT0SET_GPIO6(n)                 (((uint32_t)(n) << 6) & 0x00000040)

// GPIO5 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO5_S                  5
#define AM_REG_GPIO_INT0SET_GPIO5_M                  0x00000020
#define AM_REG_GPIO_INT0SET_GPIO5(n)                 (((uint32_t)(n) << 5) & 0x00000020)

// GPIO4 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO4_S                  4
#define AM_REG_GPIO_INT0SET_GPIO4_M                  0x00000010
#define AM_REG_GPIO_INT0SET_GPIO4(n)                 (((uint32_t)(n) << 4) & 0x00000010)

// GPIO3 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO3_S                  3
#define AM_REG_GPIO_INT0SET_GPIO3_M                  0x00000008
#define AM_REG_GPIO_INT0SET_GPIO3(n)                 (((uint32_t)(n) << 3) & 0x00000008)

// GPIO2 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO2_S                  2
#define AM_REG_GPIO_INT0SET_GPIO2_M                  0x00000004
#define AM_REG_GPIO_INT0SET_GPIO2(n)                 (((uint32_t)(n) << 2) & 0x00000004)

// GPIO1 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO1_S                  1
#define AM_REG_GPIO_INT0SET_GPIO1_M                  0x00000002
#define AM_REG_GPIO_INT0SET_GPIO1(n)                 (((uint32_t)(n) << 1) & 0x00000002)

// GPIO0 interrupt.
#define AM_REG_GPIO_INT0SET_GPIO0_S                  0
#define AM_REG_GPIO_INT0SET_GPIO0_M                  0x00000001
#define AM_REG_GPIO_INT0SET_GPIO0(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_INT1EN - GPIO Interrupt Registers 49-32: Enable
//
//*****************************************************************************
// GPIO49 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO49_S                  17
#define AM_REG_GPIO_INT1EN_GPIO49_M                  0x00020000
#define AM_REG_GPIO_INT1EN_GPIO49(n)                 (((uint32_t)(n) << 17) & 0x00020000)

// GPIO48 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO48_S                  16
#define AM_REG_GPIO_INT1EN_GPIO48_M                  0x00010000
#define AM_REG_GPIO_INT1EN_GPIO48(n)                 (((uint32_t)(n) << 16) & 0x00010000)

// GPIO47 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO47_S                  15
#define AM_REG_GPIO_INT1EN_GPIO47_M                  0x00008000
#define AM_REG_GPIO_INT1EN_GPIO47(n)                 (((uint32_t)(n) << 15) & 0x00008000)

// GPIO46 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO46_S                  14
#define AM_REG_GPIO_INT1EN_GPIO46_M                  0x00004000
#define AM_REG_GPIO_INT1EN_GPIO46(n)                 (((uint32_t)(n) << 14) & 0x00004000)

// GPIO45 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO45_S                  13
#define AM_REG_GPIO_INT1EN_GPIO45_M                  0x00002000
#define AM_REG_GPIO_INT1EN_GPIO45(n)                 (((uint32_t)(n) << 13) & 0x00002000)

// GPIO44 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO44_S                  12
#define AM_REG_GPIO_INT1EN_GPIO44_M                  0x00001000
#define AM_REG_GPIO_INT1EN_GPIO44(n)                 (((uint32_t)(n) << 12) & 0x00001000)

// GPIO43 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO43_S                  11
#define AM_REG_GPIO_INT1EN_GPIO43_M                  0x00000800
#define AM_REG_GPIO_INT1EN_GPIO43(n)                 (((uint32_t)(n) << 11) & 0x00000800)

// GPIO42 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO42_S                  10
#define AM_REG_GPIO_INT1EN_GPIO42_M                  0x00000400
#define AM_REG_GPIO_INT1EN_GPIO42(n)                 (((uint32_t)(n) << 10) & 0x00000400)

// GPIO41 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO41_S                  9
#define AM_REG_GPIO_INT1EN_GPIO41_M                  0x00000200
#define AM_REG_GPIO_INT1EN_GPIO41(n)                 (((uint32_t)(n) << 9) & 0x00000200)

// GPIO40 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO40_S                  8
#define AM_REG_GPIO_INT1EN_GPIO40_M                  0x00000100
#define AM_REG_GPIO_INT1EN_GPIO40(n)                 (((uint32_t)(n) << 8) & 0x00000100)

// GPIO39 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO39_S                  7
#define AM_REG_GPIO_INT1EN_GPIO39_M                  0x00000080
#define AM_REG_GPIO_INT1EN_GPIO39(n)                 (((uint32_t)(n) << 7) & 0x00000080)

// GPIO38 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO38_S                  6
#define AM_REG_GPIO_INT1EN_GPIO38_M                  0x00000040
#define AM_REG_GPIO_INT1EN_GPIO38(n)                 (((uint32_t)(n) << 6) & 0x00000040)

// GPIO37 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO37_S                  5
#define AM_REG_GPIO_INT1EN_GPIO37_M                  0x00000020
#define AM_REG_GPIO_INT1EN_GPIO37(n)                 (((uint32_t)(n) << 5) & 0x00000020)

// GPIO36 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO36_S                  4
#define AM_REG_GPIO_INT1EN_GPIO36_M                  0x00000010
#define AM_REG_GPIO_INT1EN_GPIO36(n)                 (((uint32_t)(n) << 4) & 0x00000010)

// GPIO35 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO35_S                  3
#define AM_REG_GPIO_INT1EN_GPIO35_M                  0x00000008
#define AM_REG_GPIO_INT1EN_GPIO35(n)                 (((uint32_t)(n) << 3) & 0x00000008)

// GPIO34 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO34_S                  2
#define AM_REG_GPIO_INT1EN_GPIO34_M                  0x00000004
#define AM_REG_GPIO_INT1EN_GPIO34(n)                 (((uint32_t)(n) << 2) & 0x00000004)

// GPIO33 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO33_S                  1
#define AM_REG_GPIO_INT1EN_GPIO33_M                  0x00000002
#define AM_REG_GPIO_INT1EN_GPIO33(n)                 (((uint32_t)(n) << 1) & 0x00000002)

// GPIO32 interrupt.
#define AM_REG_GPIO_INT1EN_GPIO32_S                  0
#define AM_REG_GPIO_INT1EN_GPIO32_M                  0x00000001
#define AM_REG_GPIO_INT1EN_GPIO32(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_INT1STAT - GPIO Interrupt Registers 49-32: Status
//
//*****************************************************************************
// GPIO49 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO49_S                17
#define AM_REG_GPIO_INT1STAT_GPIO49_M                0x00020000
#define AM_REG_GPIO_INT1STAT_GPIO49(n)               (((uint32_t)(n) << 17) & 0x00020000)

// GPIO48 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO48_S                16
#define AM_REG_GPIO_INT1STAT_GPIO48_M                0x00010000
#define AM_REG_GPIO_INT1STAT_GPIO48(n)               (((uint32_t)(n) << 16) & 0x00010000)

// GPIO47 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO47_S                15
#define AM_REG_GPIO_INT1STAT_GPIO47_M                0x00008000
#define AM_REG_GPIO_INT1STAT_GPIO47(n)               (((uint32_t)(n) << 15) & 0x00008000)

// GPIO46 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO46_S                14
#define AM_REG_GPIO_INT1STAT_GPIO46_M                0x00004000
#define AM_REG_GPIO_INT1STAT_GPIO46(n)               (((uint32_t)(n) << 14) & 0x00004000)

// GPIO45 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO45_S                13
#define AM_REG_GPIO_INT1STAT_GPIO45_M                0x00002000
#define AM_REG_GPIO_INT1STAT_GPIO45(n)               (((uint32_t)(n) << 13) & 0x00002000)

// GPIO44 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO44_S                12
#define AM_REG_GPIO_INT1STAT_GPIO44_M                0x00001000
#define AM_REG_GPIO_INT1STAT_GPIO44(n)               (((uint32_t)(n) << 12) & 0x00001000)

// GPIO43 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO43_S                11
#define AM_REG_GPIO_INT1STAT_GPIO43_M                0x00000800
#define AM_REG_GPIO_INT1STAT_GPIO43(n)               (((uint32_t)(n) << 11) & 0x00000800)

// GPIO42 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO42_S                10
#define AM_REG_GPIO_INT1STAT_GPIO42_M                0x00000400
#define AM_REG_GPIO_INT1STAT_GPIO42(n)               (((uint32_t)(n) << 10) & 0x00000400)

// GPIO41 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO41_S                9
#define AM_REG_GPIO_INT1STAT_GPIO41_M                0x00000200
#define AM_REG_GPIO_INT1STAT_GPIO41(n)               (((uint32_t)(n) << 9) & 0x00000200)

// GPIO40 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO40_S                8
#define AM_REG_GPIO_INT1STAT_GPIO40_M                0x00000100
#define AM_REG_GPIO_INT1STAT_GPIO40(n)               (((uint32_t)(n) << 8) & 0x00000100)

// GPIO39 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO39_S                7
#define AM_REG_GPIO_INT1STAT_GPIO39_M                0x00000080
#define AM_REG_GPIO_INT1STAT_GPIO39(n)               (((uint32_t)(n) << 7) & 0x00000080)

// GPIO38 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO38_S                6
#define AM_REG_GPIO_INT1STAT_GPIO38_M                0x00000040
#define AM_REG_GPIO_INT1STAT_GPIO38(n)               (((uint32_t)(n) << 6) & 0x00000040)

// GPIO37 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO37_S                5
#define AM_REG_GPIO_INT1STAT_GPIO37_M                0x00000020
#define AM_REG_GPIO_INT1STAT_GPIO37(n)               (((uint32_t)(n) << 5) & 0x00000020)

// GPIO36 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO36_S                4
#define AM_REG_GPIO_INT1STAT_GPIO36_M                0x00000010
#define AM_REG_GPIO_INT1STAT_GPIO36(n)               (((uint32_t)(n) << 4) & 0x00000010)

// GPIO35 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO35_S                3
#define AM_REG_GPIO_INT1STAT_GPIO35_M                0x00000008
#define AM_REG_GPIO_INT1STAT_GPIO35(n)               (((uint32_t)(n) << 3) & 0x00000008)

// GPIO34 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO34_S                2
#define AM_REG_GPIO_INT1STAT_GPIO34_M                0x00000004
#define AM_REG_GPIO_INT1STAT_GPIO34(n)               (((uint32_t)(n) << 2) & 0x00000004)

// GPIO33 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO33_S                1
#define AM_REG_GPIO_INT1STAT_GPIO33_M                0x00000002
#define AM_REG_GPIO_INT1STAT_GPIO33(n)               (((uint32_t)(n) << 1) & 0x00000002)

// GPIO32 interrupt.
#define AM_REG_GPIO_INT1STAT_GPIO32_S                0
#define AM_REG_GPIO_INT1STAT_GPIO32_M                0x00000001
#define AM_REG_GPIO_INT1STAT_GPIO32(n)               (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_INT1CLR - GPIO Interrupt Registers 49-32: Clear
//
//*****************************************************************************
// GPIO49 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO49_S                 17
#define AM_REG_GPIO_INT1CLR_GPIO49_M                 0x00020000
#define AM_REG_GPIO_INT1CLR_GPIO49(n)                (((uint32_t)(n) << 17) & 0x00020000)

// GPIO48 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO48_S                 16
#define AM_REG_GPIO_INT1CLR_GPIO48_M                 0x00010000
#define AM_REG_GPIO_INT1CLR_GPIO48(n)                (((uint32_t)(n) << 16) & 0x00010000)

// GPIO47 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO47_S                 15
#define AM_REG_GPIO_INT1CLR_GPIO47_M                 0x00008000
#define AM_REG_GPIO_INT1CLR_GPIO47(n)                (((uint32_t)(n) << 15) & 0x00008000)

// GPIO46 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO46_S                 14
#define AM_REG_GPIO_INT1CLR_GPIO46_M                 0x00004000
#define AM_REG_GPIO_INT1CLR_GPIO46(n)                (((uint32_t)(n) << 14) & 0x00004000)

// GPIO45 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO45_S                 13
#define AM_REG_GPIO_INT1CLR_GPIO45_M                 0x00002000
#define AM_REG_GPIO_INT1CLR_GPIO45(n)                (((uint32_t)(n) << 13) & 0x00002000)

// GPIO44 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO44_S                 12
#define AM_REG_GPIO_INT1CLR_GPIO44_M                 0x00001000
#define AM_REG_GPIO_INT1CLR_GPIO44(n)                (((uint32_t)(n) << 12) & 0x00001000)

// GPIO43 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO43_S                 11
#define AM_REG_GPIO_INT1CLR_GPIO43_M                 0x00000800
#define AM_REG_GPIO_INT1CLR_GPIO43(n)                (((uint32_t)(n) << 11) & 0x00000800)

// GPIO42 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO42_S                 10
#define AM_REG_GPIO_INT1CLR_GPIO42_M                 0x00000400
#define AM_REG_GPIO_INT1CLR_GPIO42(n)                (((uint32_t)(n) << 10) & 0x00000400)

// GPIO41 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO41_S                 9
#define AM_REG_GPIO_INT1CLR_GPIO41_M                 0x00000200
#define AM_REG_GPIO_INT1CLR_GPIO41(n)                (((uint32_t)(n) << 9) & 0x00000200)

// GPIO40 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO40_S                 8
#define AM_REG_GPIO_INT1CLR_GPIO40_M                 0x00000100
#define AM_REG_GPIO_INT1CLR_GPIO40(n)                (((uint32_t)(n) << 8) & 0x00000100)

// GPIO39 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO39_S                 7
#define AM_REG_GPIO_INT1CLR_GPIO39_M                 0x00000080
#define AM_REG_GPIO_INT1CLR_GPIO39(n)                (((uint32_t)(n) << 7) & 0x00000080)

// GPIO38 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO38_S                 6
#define AM_REG_GPIO_INT1CLR_GPIO38_M                 0x00000040
#define AM_REG_GPIO_INT1CLR_GPIO38(n)                (((uint32_t)(n) << 6) & 0x00000040)

// GPIO37 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO37_S                 5
#define AM_REG_GPIO_INT1CLR_GPIO37_M                 0x00000020
#define AM_REG_GPIO_INT1CLR_GPIO37(n)                (((uint32_t)(n) << 5) & 0x00000020)

// GPIO36 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO36_S                 4
#define AM_REG_GPIO_INT1CLR_GPIO36_M                 0x00000010
#define AM_REG_GPIO_INT1CLR_GPIO36(n)                (((uint32_t)(n) << 4) & 0x00000010)

// GPIO35 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO35_S                 3
#define AM_REG_GPIO_INT1CLR_GPIO35_M                 0x00000008
#define AM_REG_GPIO_INT1CLR_GPIO35(n)                (((uint32_t)(n) << 3) & 0x00000008)

// GPIO34 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO34_S                 2
#define AM_REG_GPIO_INT1CLR_GPIO34_M                 0x00000004
#define AM_REG_GPIO_INT1CLR_GPIO34(n)                (((uint32_t)(n) << 2) & 0x00000004)

// GPIO33 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO33_S                 1
#define AM_REG_GPIO_INT1CLR_GPIO33_M                 0x00000002
#define AM_REG_GPIO_INT1CLR_GPIO33(n)                (((uint32_t)(n) << 1) & 0x00000002)

// GPIO32 interrupt.
#define AM_REG_GPIO_INT1CLR_GPIO32_S                 0
#define AM_REG_GPIO_INT1CLR_GPIO32_M                 0x00000001
#define AM_REG_GPIO_INT1CLR_GPIO32(n)                (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_INT1SET - GPIO Interrupt Registers 49-32: Set
//
//*****************************************************************************
// GPIO49 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO49_S                 17
#define AM_REG_GPIO_INT1SET_GPIO49_M                 0x00020000
#define AM_REG_GPIO_INT1SET_GPIO49(n)                (((uint32_t)(n) << 17) & 0x00020000)

// GPIO48 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO48_S                 16
#define AM_REG_GPIO_INT1SET_GPIO48_M                 0x00010000
#define AM_REG_GPIO_INT1SET_GPIO48(n)                (((uint32_t)(n) << 16) & 0x00010000)

// GPIO47 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO47_S                 15
#define AM_REG_GPIO_INT1SET_GPIO47_M                 0x00008000
#define AM_REG_GPIO_INT1SET_GPIO47(n)                (((uint32_t)(n) << 15) & 0x00008000)

// GPIO46 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO46_S                 14
#define AM_REG_GPIO_INT1SET_GPIO46_M                 0x00004000
#define AM_REG_GPIO_INT1SET_GPIO46(n)                (((uint32_t)(n) << 14) & 0x00004000)

// GPIO45 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO45_S                 13
#define AM_REG_GPIO_INT1SET_GPIO45_M                 0x00002000
#define AM_REG_GPIO_INT1SET_GPIO45(n)                (((uint32_t)(n) << 13) & 0x00002000)

// GPIO44 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO44_S                 12
#define AM_REG_GPIO_INT1SET_GPIO44_M                 0x00001000
#define AM_REG_GPIO_INT1SET_GPIO44(n)                (((uint32_t)(n) << 12) & 0x00001000)

// GPIO43 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO43_S                 11
#define AM_REG_GPIO_INT1SET_GPIO43_M                 0x00000800
#define AM_REG_GPIO_INT1SET_GPIO43(n)                (((uint32_t)(n) << 11) & 0x00000800)

// GPIO42 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO42_S                 10
#define AM_REG_GPIO_INT1SET_GPIO42_M                 0x00000400
#define AM_REG_GPIO_INT1SET_GPIO42(n)                (((uint32_t)(n) << 10) & 0x00000400)

// GPIO41 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO41_S                 9
#define AM_REG_GPIO_INT1SET_GPIO41_M                 0x00000200
#define AM_REG_GPIO_INT1SET_GPIO41(n)                (((uint32_t)(n) << 9) & 0x00000200)

// GPIO40 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO40_S                 8
#define AM_REG_GPIO_INT1SET_GPIO40_M                 0x00000100
#define AM_REG_GPIO_INT1SET_GPIO40(n)                (((uint32_t)(n) << 8) & 0x00000100)

// GPIO39 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO39_S                 7
#define AM_REG_GPIO_INT1SET_GPIO39_M                 0x00000080
#define AM_REG_GPIO_INT1SET_GPIO39(n)                (((uint32_t)(n) << 7) & 0x00000080)

// GPIO38 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO38_S                 6
#define AM_REG_GPIO_INT1SET_GPIO38_M                 0x00000040
#define AM_REG_GPIO_INT1SET_GPIO38(n)                (((uint32_t)(n) << 6) & 0x00000040)

// GPIO37 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO37_S                 5
#define AM_REG_GPIO_INT1SET_GPIO37_M                 0x00000020
#define AM_REG_GPIO_INT1SET_GPIO37(n)                (((uint32_t)(n) << 5) & 0x00000020)

// GPIO36 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO36_S                 4
#define AM_REG_GPIO_INT1SET_GPIO36_M                 0x00000010
#define AM_REG_GPIO_INT1SET_GPIO36(n)                (((uint32_t)(n) << 4) & 0x00000010)

// GPIO35 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO35_S                 3
#define AM_REG_GPIO_INT1SET_GPIO35_M                 0x00000008
#define AM_REG_GPIO_INT1SET_GPIO35(n)                (((uint32_t)(n) << 3) & 0x00000008)

// GPIO34 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO34_S                 2
#define AM_REG_GPIO_INT1SET_GPIO34_M                 0x00000004
#define AM_REG_GPIO_INT1SET_GPIO34(n)                (((uint32_t)(n) << 2) & 0x00000004)

// GPIO33 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO33_S                 1
#define AM_REG_GPIO_INT1SET_GPIO33_M                 0x00000002
#define AM_REG_GPIO_INT1SET_GPIO33(n)                (((uint32_t)(n) << 1) & 0x00000002)

// GPIO32 interrupt.
#define AM_REG_GPIO_INT1SET_GPIO32_S                 0
#define AM_REG_GPIO_INT1SET_GPIO32_M                 0x00000001
#define AM_REG_GPIO_INT1SET_GPIO32(n)                (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_PADREGA - Pad Configuration Register A
//
//*****************************************************************************
// Pad 3 function select
#define AM_REG_GPIO_PADREGA_PAD3FNCSEL_S             27
#define AM_REG_GPIO_PADREGA_PAD3FNCSEL_M             0x38000000
#define AM_REG_GPIO_PADREGA_PAD3FNCSEL(n)            (((uint32_t)(n) << 27) & 0x38000000)
#define AM_REG_GPIO_PADREGA_PAD3FNCSEL_UA0RTS        0x00000000
#define AM_REG_GPIO_PADREGA_PAD3FNCSEL_SLnCE         0x08000000
#define AM_REG_GPIO_PADREGA_PAD3FNCSEL_M1nCE4        0x10000000
#define AM_REG_GPIO_PADREGA_PAD3FNCSEL_GPIO3         0x18000000
#define AM_REG_GPIO_PADREGA_PAD3FNCSEL_MxnCELB       0x20000000
#define AM_REG_GPIO_PADREGA_PAD3FNCSEL_M2nCE0        0x28000000
#define AM_REG_GPIO_PADREGA_PAD3FNCSEL_TRIG1         0x30000000
#define AM_REG_GPIO_PADREGA_PAD3FNCSEL_I2S_WCLK      0x38000000

// Pad 3 drive strength.
#define AM_REG_GPIO_PADREGA_PAD3STRNG_S              26
#define AM_REG_GPIO_PADREGA_PAD3STRNG_M              0x04000000
#define AM_REG_GPIO_PADREGA_PAD3STRNG(n)             (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_GPIO_PADREGA_PAD3STRNG_LOW            0x00000000
#define AM_REG_GPIO_PADREGA_PAD3STRNG_HIGH           0x04000000

// Pad 3 input enable.
#define AM_REG_GPIO_PADREGA_PAD3INPEN_S              25
#define AM_REG_GPIO_PADREGA_PAD3INPEN_M              0x02000000
#define AM_REG_GPIO_PADREGA_PAD3INPEN(n)             (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_GPIO_PADREGA_PAD3INPEN_DIS            0x00000000
#define AM_REG_GPIO_PADREGA_PAD3INPEN_EN             0x02000000

// Pad 3 pullup enable
#define AM_REG_GPIO_PADREGA_PAD3PULL_S               24
#define AM_REG_GPIO_PADREGA_PAD3PULL_M               0x01000000
#define AM_REG_GPIO_PADREGA_PAD3PULL(n)              (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_PADREGA_PAD3PULL_DIS             0x00000000
#define AM_REG_GPIO_PADREGA_PAD3PULL_EN              0x01000000

// Pad 2 function select
#define AM_REG_GPIO_PADREGA_PAD2FNCSEL_S             19
#define AM_REG_GPIO_PADREGA_PAD2FNCSEL_M             0x00380000
#define AM_REG_GPIO_PADREGA_PAD2FNCSEL(n)            (((uint32_t)(n) << 19) & 0x00380000)
#define AM_REG_GPIO_PADREGA_PAD2FNCSEL_SLWIR3        0x00000000
#define AM_REG_GPIO_PADREGA_PAD2FNCSEL_SLMOSI        0x00080000
#define AM_REG_GPIO_PADREGA_PAD2FNCSEL_UART0RX       0x00100000
#define AM_REG_GPIO_PADREGA_PAD2FNCSEL_GPIO2         0x00180000
#define AM_REG_GPIO_PADREGA_PAD2FNCSEL_MxMOSILB      0x00200000
#define AM_REG_GPIO_PADREGA_PAD2FNCSEL_M2MOSI        0x00280000
#define AM_REG_GPIO_PADREGA_PAD2FNCSEL_MxWIR3LB      0x00300000
#define AM_REG_GPIO_PADREGA_PAD2FNCSEL_M2WIR3        0x00380000

// Pad 2 drive strength
#define AM_REG_GPIO_PADREGA_PAD2STRNG_S              18
#define AM_REG_GPIO_PADREGA_PAD2STRNG_M              0x00040000
#define AM_REG_GPIO_PADREGA_PAD2STRNG(n)             (((uint32_t)(n) << 18) & 0x00040000)
#define AM_REG_GPIO_PADREGA_PAD2STRNG_LOW            0x00000000
#define AM_REG_GPIO_PADREGA_PAD2STRNG_HIGH           0x00040000

// Pad 2 input enable
#define AM_REG_GPIO_PADREGA_PAD2INPEN_S              17
#define AM_REG_GPIO_PADREGA_PAD2INPEN_M              0x00020000
#define AM_REG_GPIO_PADREGA_PAD2INPEN(n)             (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_GPIO_PADREGA_PAD2INPEN_DIS            0x00000000
#define AM_REG_GPIO_PADREGA_PAD2INPEN_EN             0x00020000

// Pad 2 pullup enable
#define AM_REG_GPIO_PADREGA_PAD2PULL_S               16
#define AM_REG_GPIO_PADREGA_PAD2PULL_M               0x00010000
#define AM_REG_GPIO_PADREGA_PAD2PULL(n)              (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_PADREGA_PAD2PULL_DIS             0x00000000
#define AM_REG_GPIO_PADREGA_PAD2PULL_EN              0x00010000

// Pad 1 pullup resistor selection.
#define AM_REG_GPIO_PADREGA_PAD1RSEL_S               14
#define AM_REG_GPIO_PADREGA_PAD1RSEL_M               0x0000C000
#define AM_REG_GPIO_PADREGA_PAD1RSEL(n)              (((uint32_t)(n) << 14) & 0x0000C000)
#define AM_REG_GPIO_PADREGA_PAD1RSEL_PULL1_5K        0x00000000
#define AM_REG_GPIO_PADREGA_PAD1RSEL_PULL6K          0x00004000
#define AM_REG_GPIO_PADREGA_PAD1RSEL_PULL12K         0x00008000
#define AM_REG_GPIO_PADREGA_PAD1RSEL_PULL24K         0x0000C000

// Pad 1 function select
#define AM_REG_GPIO_PADREGA_PAD1FNCSEL_S             11
#define AM_REG_GPIO_PADREGA_PAD1FNCSEL_M             0x00003800
#define AM_REG_GPIO_PADREGA_PAD1FNCSEL(n)            (((uint32_t)(n) << 11) & 0x00003800)
#define AM_REG_GPIO_PADREGA_PAD1FNCSEL_SLSDA         0x00000000
#define AM_REG_GPIO_PADREGA_PAD1FNCSEL_SLMISO        0x00000800
#define AM_REG_GPIO_PADREGA_PAD1FNCSEL_UART0TX       0x00001000
#define AM_REG_GPIO_PADREGA_PAD1FNCSEL_GPIO1         0x00001800
#define AM_REG_GPIO_PADREGA_PAD1FNCSEL_MxMISOLB      0x00002000
#define AM_REG_GPIO_PADREGA_PAD1FNCSEL_M2MISO        0x00002800
#define AM_REG_GPIO_PADREGA_PAD1FNCSEL_MxSDALB       0x00003000
#define AM_REG_GPIO_PADREGA_PAD1FNCSEL_M2SDA         0x00003800

// Pad 1 drive strength
#define AM_REG_GPIO_PADREGA_PAD1STRNG_S              10
#define AM_REG_GPIO_PADREGA_PAD1STRNG_M              0x00000400
#define AM_REG_GPIO_PADREGA_PAD1STRNG(n)             (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_GPIO_PADREGA_PAD1STRNG_LOW            0x00000000
#define AM_REG_GPIO_PADREGA_PAD1STRNG_HIGH           0x00000400

// Pad 1 input enable
#define AM_REG_GPIO_PADREGA_PAD1INPEN_S              9
#define AM_REG_GPIO_PADREGA_PAD1INPEN_M              0x00000200
#define AM_REG_GPIO_PADREGA_PAD1INPEN(n)             (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_GPIO_PADREGA_PAD1INPEN_DIS            0x00000000
#define AM_REG_GPIO_PADREGA_PAD1INPEN_EN             0x00000200

// Pad 1 pullup enable
#define AM_REG_GPIO_PADREGA_PAD1PULL_S               8
#define AM_REG_GPIO_PADREGA_PAD1PULL_M               0x00000100
#define AM_REG_GPIO_PADREGA_PAD1PULL(n)              (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_PADREGA_PAD1PULL_DIS             0x00000000
#define AM_REG_GPIO_PADREGA_PAD1PULL_EN              0x00000100

// Pad 0 pullup resistor selection.
#define AM_REG_GPIO_PADREGA_PAD0RSEL_S               6
#define AM_REG_GPIO_PADREGA_PAD0RSEL_M               0x000000C0
#define AM_REG_GPIO_PADREGA_PAD0RSEL(n)              (((uint32_t)(n) << 6) & 0x000000C0)
#define AM_REG_GPIO_PADREGA_PAD0RSEL_PULL1_5K        0x00000000
#define AM_REG_GPIO_PADREGA_PAD0RSEL_PULL6K          0x00000040
#define AM_REG_GPIO_PADREGA_PAD0RSEL_PULL12K         0x00000080
#define AM_REG_GPIO_PADREGA_PAD0RSEL_PULL24K         0x000000C0

// Pad 0 function select
#define AM_REG_GPIO_PADREGA_PAD0FNCSEL_S             3
#define AM_REG_GPIO_PADREGA_PAD0FNCSEL_M             0x00000038
#define AM_REG_GPIO_PADREGA_PAD0FNCSEL(n)            (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_GPIO_PADREGA_PAD0FNCSEL_SLSCL         0x00000000
#define AM_REG_GPIO_PADREGA_PAD0FNCSEL_SLSCK         0x00000008
#define AM_REG_GPIO_PADREGA_PAD0FNCSEL_CLKOUT        0x00000010
#define AM_REG_GPIO_PADREGA_PAD0FNCSEL_GPIO0         0x00000018
#define AM_REG_GPIO_PADREGA_PAD0FNCSEL_MxSCKLB       0x00000020
#define AM_REG_GPIO_PADREGA_PAD0FNCSEL_M2SCK         0x00000028
#define AM_REG_GPIO_PADREGA_PAD0FNCSEL_MxSCLLB       0x00000030
#define AM_REG_GPIO_PADREGA_PAD0FNCSEL_M2SCL         0x00000038

// Pad 0 drive strength
#define AM_REG_GPIO_PADREGA_PAD0STRNG_S              2
#define AM_REG_GPIO_PADREGA_PAD0STRNG_M              0x00000004
#define AM_REG_GPIO_PADREGA_PAD0STRNG(n)             (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_GPIO_PADREGA_PAD0STRNG_LOW            0x00000000
#define AM_REG_GPIO_PADREGA_PAD0STRNG_HIGH           0x00000004

// Pad 0 input enable
#define AM_REG_GPIO_PADREGA_PAD0INPEN_S              1
#define AM_REG_GPIO_PADREGA_PAD0INPEN_M              0x00000002
#define AM_REG_GPIO_PADREGA_PAD0INPEN(n)             (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_GPIO_PADREGA_PAD0INPEN_DIS            0x00000000
#define AM_REG_GPIO_PADREGA_PAD0INPEN_EN             0x00000002

// Pad 0 pullup enable
#define AM_REG_GPIO_PADREGA_PAD0PULL_S               0
#define AM_REG_GPIO_PADREGA_PAD0PULL_M               0x00000001
#define AM_REG_GPIO_PADREGA_PAD0PULL(n)              (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_PADREGA_PAD0PULL_DIS             0x00000000
#define AM_REG_GPIO_PADREGA_PAD0PULL_EN              0x00000001

//*****************************************************************************
//
// GPIO_PADREGB - Pad Configuration Register B
//
//*****************************************************************************
// Pad 7 function select
#define AM_REG_GPIO_PADREGB_PAD7FNCSEL_S             27
#define AM_REG_GPIO_PADREGB_PAD7FNCSEL_M             0x38000000
#define AM_REG_GPIO_PADREGB_PAD7FNCSEL(n)            (((uint32_t)(n) << 27) & 0x38000000)
#define AM_REG_GPIO_PADREGB_PAD7FNCSEL_M0WIR3        0x00000000
#define AM_REG_GPIO_PADREGB_PAD7FNCSEL_M0MOSI        0x08000000
#define AM_REG_GPIO_PADREGB_PAD7FNCSEL_CLKOUT        0x10000000
#define AM_REG_GPIO_PADREGB_PAD7FNCSEL_GPIO7         0x18000000
#define AM_REG_GPIO_PADREGB_PAD7FNCSEL_TRIG0         0x20000000
#define AM_REG_GPIO_PADREGB_PAD7FNCSEL_UART0TX       0x28000000
#define AM_REG_GPIO_PADREGB_PAD7FNCSEL_SLWIR3LB      0x30000000
#define AM_REG_GPIO_PADREGB_PAD7FNCSEL_M1nCE1        0x38000000

// Pad 7 drive strength
#define AM_REG_GPIO_PADREGB_PAD7STRNG_S              26
#define AM_REG_GPIO_PADREGB_PAD7STRNG_M              0x04000000
#define AM_REG_GPIO_PADREGB_PAD7STRNG(n)             (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_GPIO_PADREGB_PAD7STRNG_LOW            0x00000000
#define AM_REG_GPIO_PADREGB_PAD7STRNG_HIGH           0x04000000

// Pad 7 input enable
#define AM_REG_GPIO_PADREGB_PAD7INPEN_S              25
#define AM_REG_GPIO_PADREGB_PAD7INPEN_M              0x02000000
#define AM_REG_GPIO_PADREGB_PAD7INPEN(n)             (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_GPIO_PADREGB_PAD7INPEN_DIS            0x00000000
#define AM_REG_GPIO_PADREGB_PAD7INPEN_EN             0x02000000

// Pad 7 pullup enable
#define AM_REG_GPIO_PADREGB_PAD7PULL_S               24
#define AM_REG_GPIO_PADREGB_PAD7PULL_M               0x01000000
#define AM_REG_GPIO_PADREGB_PAD7PULL(n)              (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_PADREGB_PAD7PULL_DIS             0x00000000
#define AM_REG_GPIO_PADREGB_PAD7PULL_EN              0x01000000

// Pad 6 pullup resistor selection.
#define AM_REG_GPIO_PADREGB_PAD6RSEL_S               22
#define AM_REG_GPIO_PADREGB_PAD6RSEL_M               0x00C00000
#define AM_REG_GPIO_PADREGB_PAD6RSEL(n)              (((uint32_t)(n) << 22) & 0x00C00000)
#define AM_REG_GPIO_PADREGB_PAD6RSEL_PULL1_5K        0x00000000
#define AM_REG_GPIO_PADREGB_PAD6RSEL_PULL6K          0x00400000
#define AM_REG_GPIO_PADREGB_PAD6RSEL_PULL12K         0x00800000
#define AM_REG_GPIO_PADREGB_PAD6RSEL_PULL24K         0x00C00000

// Pad 6 function select
#define AM_REG_GPIO_PADREGB_PAD6FNCSEL_S             19
#define AM_REG_GPIO_PADREGB_PAD6FNCSEL_M             0x00380000
#define AM_REG_GPIO_PADREGB_PAD6FNCSEL(n)            (((uint32_t)(n) << 19) & 0x00380000)
#define AM_REG_GPIO_PADREGB_PAD6FNCSEL_M0SDA         0x00000000
#define AM_REG_GPIO_PADREGB_PAD6FNCSEL_M0MISO        0x00080000
#define AM_REG_GPIO_PADREGB_PAD6FNCSEL_UA0CTS        0x00100000
#define AM_REG_GPIO_PADREGB_PAD6FNCSEL_GPIO6         0x00180000
#define AM_REG_GPIO_PADREGB_PAD6FNCSEL_SLMISOLB      0x00200000
#define AM_REG_GPIO_PADREGB_PAD6FNCSEL_M1nCE0        0x00280000
#define AM_REG_GPIO_PADREGB_PAD6FNCSEL_SLSDALB       0x00300000
#define AM_REG_GPIO_PADREGB_PAD6FNCSEL_I2S_DAT       0x00380000

// Pad 6 drive strength
#define AM_REG_GPIO_PADREGB_PAD6STRNG_S              18
#define AM_REG_GPIO_PADREGB_PAD6STRNG_M              0x00040000
#define AM_REG_GPIO_PADREGB_PAD6STRNG(n)             (((uint32_t)(n) << 18) & 0x00040000)
#define AM_REG_GPIO_PADREGB_PAD6STRNG_LOW            0x00000000
#define AM_REG_GPIO_PADREGB_PAD6STRNG_HIGH           0x00040000

// Pad 6 input enable
#define AM_REG_GPIO_PADREGB_PAD6INPEN_S              17
#define AM_REG_GPIO_PADREGB_PAD6INPEN_M              0x00020000
#define AM_REG_GPIO_PADREGB_PAD6INPEN(n)             (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_GPIO_PADREGB_PAD6INPEN_DIS            0x00000000
#define AM_REG_GPIO_PADREGB_PAD6INPEN_EN             0x00020000

// Pad 6 pullup enable
#define AM_REG_GPIO_PADREGB_PAD6PULL_S               16
#define AM_REG_GPIO_PADREGB_PAD6PULL_M               0x00010000
#define AM_REG_GPIO_PADREGB_PAD6PULL(n)              (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_PADREGB_PAD6PULL_DIS             0x00000000
#define AM_REG_GPIO_PADREGB_PAD6PULL_EN              0x00010000

// Pad 5 pullup resistor selection.
#define AM_REG_GPIO_PADREGB_PAD5RSEL_S               14
#define AM_REG_GPIO_PADREGB_PAD5RSEL_M               0x0000C000
#define AM_REG_GPIO_PADREGB_PAD5RSEL(n)              (((uint32_t)(n) << 14) & 0x0000C000)
#define AM_REG_GPIO_PADREGB_PAD5RSEL_PULL1_5K        0x00000000
#define AM_REG_GPIO_PADREGB_PAD5RSEL_PULL6K          0x00004000
#define AM_REG_GPIO_PADREGB_PAD5RSEL_PULL12K         0x00008000
#define AM_REG_GPIO_PADREGB_PAD5RSEL_PULL24K         0x0000C000

// Pad 5 function select
#define AM_REG_GPIO_PADREGB_PAD5FNCSEL_S             11
#define AM_REG_GPIO_PADREGB_PAD5FNCSEL_M             0x00003800
#define AM_REG_GPIO_PADREGB_PAD5FNCSEL(n)            (((uint32_t)(n) << 11) & 0x00003800)
#define AM_REG_GPIO_PADREGB_PAD5FNCSEL_M0SCL         0x00000000
#define AM_REG_GPIO_PADREGB_PAD5FNCSEL_M0SCK         0x00000800
#define AM_REG_GPIO_PADREGB_PAD5FNCSEL_UA0RTS        0x00001000
#define AM_REG_GPIO_PADREGB_PAD5FNCSEL_GPIO5         0x00001800
#define AM_REG_GPIO_PADREGB_PAD5FNCSEL_M0SCKLB       0x00002000
#define AM_REG_GPIO_PADREGB_PAD5FNCSEL_EXTHFA        0x00002800
#define AM_REG_GPIO_PADREGB_PAD5FNCSEL_M0SCLLB       0x00003000
#define AM_REG_GPIO_PADREGB_PAD5FNCSEL_M1nCE2        0x00003800

// Pad 5 drive strength
#define AM_REG_GPIO_PADREGB_PAD5STRNG_S              10
#define AM_REG_GPIO_PADREGB_PAD5STRNG_M              0x00000400
#define AM_REG_GPIO_PADREGB_PAD5STRNG(n)             (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_GPIO_PADREGB_PAD5STRNG_LOW            0x00000000
#define AM_REG_GPIO_PADREGB_PAD5STRNG_HIGH           0x00000400

// Pad 5 input enable
#define AM_REG_GPIO_PADREGB_PAD5INPEN_S              9
#define AM_REG_GPIO_PADREGB_PAD5INPEN_M              0x00000200
#define AM_REG_GPIO_PADREGB_PAD5INPEN(n)             (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_GPIO_PADREGB_PAD5INPEN_DIS            0x00000000
#define AM_REG_GPIO_PADREGB_PAD5INPEN_EN             0x00000200

// Pad 5 pullup enable
#define AM_REG_GPIO_PADREGB_PAD5PULL_S               8
#define AM_REG_GPIO_PADREGB_PAD5PULL_M               0x00000100
#define AM_REG_GPIO_PADREGB_PAD5PULL(n)              (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_PADREGB_PAD5PULL_DIS             0x00000000
#define AM_REG_GPIO_PADREGB_PAD5PULL_EN              0x00000100

// Pad 4 VSS power switch enable
#define AM_REG_GPIO_PADREGB_PAD4PWRDN_S              7
#define AM_REG_GPIO_PADREGB_PAD4PWRDN_M              0x00000080
#define AM_REG_GPIO_PADREGB_PAD4PWRDN(n)             (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_GPIO_PADREGB_PAD4PWRDN_DIS            0x00000000
#define AM_REG_GPIO_PADREGB_PAD4PWRDN_EN             0x00000080

// Pad 4 function select
#define AM_REG_GPIO_PADREGB_PAD4FNCSEL_S             3
#define AM_REG_GPIO_PADREGB_PAD4FNCSEL_M             0x00000038
#define AM_REG_GPIO_PADREGB_PAD4FNCSEL(n)            (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_GPIO_PADREGB_PAD4FNCSEL_UA0CTS        0x00000000
#define AM_REG_GPIO_PADREGB_PAD4FNCSEL_SLINT         0x00000008
#define AM_REG_GPIO_PADREGB_PAD4FNCSEL_M0nCE5        0x00000010
#define AM_REG_GPIO_PADREGB_PAD4FNCSEL_GPIO4         0x00000018
#define AM_REG_GPIO_PADREGB_PAD4FNCSEL_SLINTGP       0x00000020
#define AM_REG_GPIO_PADREGB_PAD4FNCSEL_M2nCE5        0x00000028
#define AM_REG_GPIO_PADREGB_PAD4FNCSEL_CLKOUT        0x00000030
#define AM_REG_GPIO_PADREGB_PAD4FNCSEL_32khz_XT      0x00000038

// Pad 4 drive strength
#define AM_REG_GPIO_PADREGB_PAD4STRNG_S              2
#define AM_REG_GPIO_PADREGB_PAD4STRNG_M              0x00000004
#define AM_REG_GPIO_PADREGB_PAD4STRNG(n)             (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_GPIO_PADREGB_PAD4STRNG_LOW            0x00000000
#define AM_REG_GPIO_PADREGB_PAD4STRNG_HIGH           0x00000004

// Pad 4 input enable
#define AM_REG_GPIO_PADREGB_PAD4INPEN_S              1
#define AM_REG_GPIO_PADREGB_PAD4INPEN_M              0x00000002
#define AM_REG_GPIO_PADREGB_PAD4INPEN(n)             (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_GPIO_PADREGB_PAD4INPEN_DIS            0x00000000
#define AM_REG_GPIO_PADREGB_PAD4INPEN_EN             0x00000002

// Pad 4 pullup enable
#define AM_REG_GPIO_PADREGB_PAD4PULL_S               0
#define AM_REG_GPIO_PADREGB_PAD4PULL_M               0x00000001
#define AM_REG_GPIO_PADREGB_PAD4PULL(n)              (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_PADREGB_PAD4PULL_DIS             0x00000000
#define AM_REG_GPIO_PADREGB_PAD4PULL_EN              0x00000001

//*****************************************************************************
//
// GPIO_PADREGC - Pad Configuration Register C
//
//*****************************************************************************
// Pad 11 function select
#define AM_REG_GPIO_PADREGC_PAD11FNCSEL_S            27
#define AM_REG_GPIO_PADREGC_PAD11FNCSEL_M            0x38000000
#define AM_REG_GPIO_PADREGC_PAD11FNCSEL(n)           (((uint32_t)(n) << 27) & 0x38000000)
#define AM_REG_GPIO_PADREGC_PAD11FNCSEL_ADCSE2       0x00000000
#define AM_REG_GPIO_PADREGC_PAD11FNCSEL_M0nCE0       0x08000000
#define AM_REG_GPIO_PADREGC_PAD11FNCSEL_CLKOUT       0x10000000
#define AM_REG_GPIO_PADREGC_PAD11FNCSEL_GPIO11       0x18000000
#define AM_REG_GPIO_PADREGC_PAD11FNCSEL_M2nCE7       0x20000000
#define AM_REG_GPIO_PADREGC_PAD11FNCSEL_UA1CTS       0x28000000
#define AM_REG_GPIO_PADREGC_PAD11FNCSEL_UART0RX      0x30000000
#define AM_REG_GPIO_PADREGC_PAD11FNCSEL_PDM_DATA     0x38000000

// Pad 11 drive strength
#define AM_REG_GPIO_PADREGC_PAD11STRNG_S             26
#define AM_REG_GPIO_PADREGC_PAD11STRNG_M             0x04000000
#define AM_REG_GPIO_PADREGC_PAD11STRNG(n)            (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_GPIO_PADREGC_PAD11STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGC_PAD11STRNG_HIGH          0x04000000

// Pad 11 input enable
#define AM_REG_GPIO_PADREGC_PAD11INPEN_S             25
#define AM_REG_GPIO_PADREGC_PAD11INPEN_M             0x02000000
#define AM_REG_GPIO_PADREGC_PAD11INPEN(n)            (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_GPIO_PADREGC_PAD11INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGC_PAD11INPEN_EN            0x02000000

// Pad 11 pullup enable
#define AM_REG_GPIO_PADREGC_PAD11PULL_S              24
#define AM_REG_GPIO_PADREGC_PAD11PULL_M              0x01000000
#define AM_REG_GPIO_PADREGC_PAD11PULL(n)             (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_PADREGC_PAD11PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGC_PAD11PULL_EN             0x01000000

// Pad 10 function select
#define AM_REG_GPIO_PADREGC_PAD10FNCSEL_S            19
#define AM_REG_GPIO_PADREGC_PAD10FNCSEL_M            0x00380000
#define AM_REG_GPIO_PADREGC_PAD10FNCSEL(n)           (((uint32_t)(n) << 19) & 0x00380000)
#define AM_REG_GPIO_PADREGC_PAD10FNCSEL_M1WIR3       0x00000000
#define AM_REG_GPIO_PADREGC_PAD10FNCSEL_M1MOSI       0x00080000
#define AM_REG_GPIO_PADREGC_PAD10FNCSEL_M0nCE6       0x00100000
#define AM_REG_GPIO_PADREGC_PAD10FNCSEL_GPIO10       0x00180000
#define AM_REG_GPIO_PADREGC_PAD10FNCSEL_M2nCE6       0x00200000
#define AM_REG_GPIO_PADREGC_PAD10FNCSEL_UA1RTS       0x00280000
#define AM_REG_GPIO_PADREGC_PAD10FNCSEL_M4nCE4       0x00300000
#define AM_REG_GPIO_PADREGC_PAD10FNCSEL_SLWIR3LB     0x00380000

// Pad 10 drive strength
#define AM_REG_GPIO_PADREGC_PAD10STRNG_S             18
#define AM_REG_GPIO_PADREGC_PAD10STRNG_M             0x00040000
#define AM_REG_GPIO_PADREGC_PAD10STRNG(n)            (((uint32_t)(n) << 18) & 0x00040000)
#define AM_REG_GPIO_PADREGC_PAD10STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGC_PAD10STRNG_HIGH          0x00040000

// Pad 10 input enable
#define AM_REG_GPIO_PADREGC_PAD10INPEN_S             17
#define AM_REG_GPIO_PADREGC_PAD10INPEN_M             0x00020000
#define AM_REG_GPIO_PADREGC_PAD10INPEN(n)            (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_GPIO_PADREGC_PAD10INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGC_PAD10INPEN_EN            0x00020000

// Pad 10 pullup enable
#define AM_REG_GPIO_PADREGC_PAD10PULL_S              16
#define AM_REG_GPIO_PADREGC_PAD10PULL_M              0x00010000
#define AM_REG_GPIO_PADREGC_PAD10PULL(n)             (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_PADREGC_PAD10PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGC_PAD10PULL_EN             0x00010000

// Pad 9 pullup resistor selection
#define AM_REG_GPIO_PADREGC_PAD9RSEL_S               14
#define AM_REG_GPIO_PADREGC_PAD9RSEL_M               0x0000C000
#define AM_REG_GPIO_PADREGC_PAD9RSEL(n)              (((uint32_t)(n) << 14) & 0x0000C000)
#define AM_REG_GPIO_PADREGC_PAD9RSEL_PULL1_5K        0x00000000
#define AM_REG_GPIO_PADREGC_PAD9RSEL_PULL6K          0x00004000
#define AM_REG_GPIO_PADREGC_PAD9RSEL_PULL12K         0x00008000
#define AM_REG_GPIO_PADREGC_PAD9RSEL_PULL24K         0x0000C000

// Pad 9 function select
#define AM_REG_GPIO_PADREGC_PAD9FNCSEL_S             11
#define AM_REG_GPIO_PADREGC_PAD9FNCSEL_M             0x00003800
#define AM_REG_GPIO_PADREGC_PAD9FNCSEL(n)            (((uint32_t)(n) << 11) & 0x00003800)
#define AM_REG_GPIO_PADREGC_PAD9FNCSEL_M1SDA         0x00000000
#define AM_REG_GPIO_PADREGC_PAD9FNCSEL_M1MISO        0x00000800
#define AM_REG_GPIO_PADREGC_PAD9FNCSEL_M0nCE5        0x00001000
#define AM_REG_GPIO_PADREGC_PAD9FNCSEL_GPIO9         0x00001800
#define AM_REG_GPIO_PADREGC_PAD9FNCSEL_M4nCE5        0x00002000
#define AM_REG_GPIO_PADREGC_PAD9FNCSEL_SLMISOLB      0x00002800
#define AM_REG_GPIO_PADREGC_PAD9FNCSEL_UART1RX       0x00003000
#define AM_REG_GPIO_PADREGC_PAD9FNCSEL_SLSDALB       0x00003800

// Pad 9 drive strength
#define AM_REG_GPIO_PADREGC_PAD9STRNG_S              10
#define AM_REG_GPIO_PADREGC_PAD9STRNG_M              0x00000400
#define AM_REG_GPIO_PADREGC_PAD9STRNG(n)             (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_GPIO_PADREGC_PAD9STRNG_LOW            0x00000000
#define AM_REG_GPIO_PADREGC_PAD9STRNG_HIGH           0x00000400

// Pad 9 input enable
#define AM_REG_GPIO_PADREGC_PAD9INPEN_S              9
#define AM_REG_GPIO_PADREGC_PAD9INPEN_M              0x00000200
#define AM_REG_GPIO_PADREGC_PAD9INPEN(n)             (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_GPIO_PADREGC_PAD9INPEN_DIS            0x00000000
#define AM_REG_GPIO_PADREGC_PAD9INPEN_EN             0x00000200

// Pad 9 pullup enable
#define AM_REG_GPIO_PADREGC_PAD9PULL_S               8
#define AM_REG_GPIO_PADREGC_PAD9PULL_M               0x00000100
#define AM_REG_GPIO_PADREGC_PAD9PULL(n)              (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_PADREGC_PAD9PULL_DIS             0x00000000
#define AM_REG_GPIO_PADREGC_PAD9PULL_EN              0x00000100

// Pad 8 pullup resistor selection.
#define AM_REG_GPIO_PADREGC_PAD8RSEL_S               6
#define AM_REG_GPIO_PADREGC_PAD8RSEL_M               0x000000C0
#define AM_REG_GPIO_PADREGC_PAD8RSEL(n)              (((uint32_t)(n) << 6) & 0x000000C0)
#define AM_REG_GPIO_PADREGC_PAD8RSEL_PULL1_5K        0x00000000
#define AM_REG_GPIO_PADREGC_PAD8RSEL_PULL6K          0x00000040
#define AM_REG_GPIO_PADREGC_PAD8RSEL_PULL12K         0x00000080
#define AM_REG_GPIO_PADREGC_PAD8RSEL_PULL24K         0x000000C0

// Pad 8 function select
#define AM_REG_GPIO_PADREGC_PAD8FNCSEL_S             3
#define AM_REG_GPIO_PADREGC_PAD8FNCSEL_M             0x00000038
#define AM_REG_GPIO_PADREGC_PAD8FNCSEL(n)            (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_GPIO_PADREGC_PAD8FNCSEL_M1SCL         0x00000000
#define AM_REG_GPIO_PADREGC_PAD8FNCSEL_M1SCK         0x00000008
#define AM_REG_GPIO_PADREGC_PAD8FNCSEL_M0nCE4        0x00000010
#define AM_REG_GPIO_PADREGC_PAD8FNCSEL_GPIO8         0x00000018
#define AM_REG_GPIO_PADREGC_PAD8FNCSEL_M2nCE4        0x00000020
#define AM_REG_GPIO_PADREGC_PAD8FNCSEL_M1SCKLB       0x00000028
#define AM_REG_GPIO_PADREGC_PAD8FNCSEL_UART1TX       0x00000030
#define AM_REG_GPIO_PADREGC_PAD8FNCSEL_M1SCLLB       0x00000038

// Pad 8 drive strength
#define AM_REG_GPIO_PADREGC_PAD8STRNG_S              2
#define AM_REG_GPIO_PADREGC_PAD8STRNG_M              0x00000004
#define AM_REG_GPIO_PADREGC_PAD8STRNG(n)             (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_GPIO_PADREGC_PAD8STRNG_LOW            0x00000000
#define AM_REG_GPIO_PADREGC_PAD8STRNG_HIGH           0x00000004

// Pad 8 input enable
#define AM_REG_GPIO_PADREGC_PAD8INPEN_S              1
#define AM_REG_GPIO_PADREGC_PAD8INPEN_M              0x00000002
#define AM_REG_GPIO_PADREGC_PAD8INPEN(n)             (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_GPIO_PADREGC_PAD8INPEN_DIS            0x00000000
#define AM_REG_GPIO_PADREGC_PAD8INPEN_EN             0x00000002

// Pad 8 pullup enable
#define AM_REG_GPIO_PADREGC_PAD8PULL_S               0
#define AM_REG_GPIO_PADREGC_PAD8PULL_M               0x00000001
#define AM_REG_GPIO_PADREGC_PAD8PULL(n)              (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_PADREGC_PAD8PULL_DIS             0x00000000
#define AM_REG_GPIO_PADREGC_PAD8PULL_EN              0x00000001

//*****************************************************************************
//
// GPIO_PADREGD - Pad Configuration Register D
//
//*****************************************************************************
// Pad 15 function select
#define AM_REG_GPIO_PADREGD_PAD15FNCSEL_S            27
#define AM_REG_GPIO_PADREGD_PAD15FNCSEL_M            0x38000000
#define AM_REG_GPIO_PADREGD_PAD15FNCSEL(n)           (((uint32_t)(n) << 27) & 0x38000000)
#define AM_REG_GPIO_PADREGD_PAD15FNCSEL_ADCD1N       0x00000000
#define AM_REG_GPIO_PADREGD_PAD15FNCSEL_M1nCE3       0x08000000
#define AM_REG_GPIO_PADREGD_PAD15FNCSEL_UART1RX      0x10000000
#define AM_REG_GPIO_PADREGD_PAD15FNCSEL_GPIO15       0x18000000
#define AM_REG_GPIO_PADREGD_PAD15FNCSEL_M2nCE2       0x20000000
#define AM_REG_GPIO_PADREGD_PAD15FNCSEL_EXTXT        0x28000000
#define AM_REG_GPIO_PADREGD_PAD15FNCSEL_SWDIO        0x30000000
#define AM_REG_GPIO_PADREGD_PAD15FNCSEL_SWO          0x38000000

// Pad 15 drive strength
#define AM_REG_GPIO_PADREGD_PAD15STRNG_S             26
#define AM_REG_GPIO_PADREGD_PAD15STRNG_M             0x04000000
#define AM_REG_GPIO_PADREGD_PAD15STRNG(n)            (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_GPIO_PADREGD_PAD15STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGD_PAD15STRNG_HIGH          0x04000000

// Pad 15 input enable
#define AM_REG_GPIO_PADREGD_PAD15INPEN_S             25
#define AM_REG_GPIO_PADREGD_PAD15INPEN_M             0x02000000
#define AM_REG_GPIO_PADREGD_PAD15INPEN(n)            (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_GPIO_PADREGD_PAD15INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGD_PAD15INPEN_EN            0x02000000

// Pad 15 pullup enable
#define AM_REG_GPIO_PADREGD_PAD15PULL_S              24
#define AM_REG_GPIO_PADREGD_PAD15PULL_M              0x01000000
#define AM_REG_GPIO_PADREGD_PAD15PULL(n)             (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_PADREGD_PAD15PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGD_PAD15PULL_EN             0x01000000

// Pad 14 function select
#define AM_REG_GPIO_PADREGD_PAD14FNCSEL_S            19
#define AM_REG_GPIO_PADREGD_PAD14FNCSEL_M            0x00380000
#define AM_REG_GPIO_PADREGD_PAD14FNCSEL(n)           (((uint32_t)(n) << 19) & 0x00380000)
#define AM_REG_GPIO_PADREGD_PAD14FNCSEL_ADCD1P       0x00000000
#define AM_REG_GPIO_PADREGD_PAD14FNCSEL_M1nCE2       0x00080000
#define AM_REG_GPIO_PADREGD_PAD14FNCSEL_UART1TX      0x00100000
#define AM_REG_GPIO_PADREGD_PAD14FNCSEL_GPIO14       0x00180000
#define AM_REG_GPIO_PADREGD_PAD14FNCSEL_M2nCE1       0x00200000
#define AM_REG_GPIO_PADREGD_PAD14FNCSEL_EXTHFS       0x00280000
#define AM_REG_GPIO_PADREGD_PAD14FNCSEL_SWDCK        0x00300000
#define AM_REG_GPIO_PADREGD_PAD14FNCSEL_32khz_XT     0x00380000

// Pad 14 drive strength
#define AM_REG_GPIO_PADREGD_PAD14STRNG_S             18
#define AM_REG_GPIO_PADREGD_PAD14STRNG_M             0x00040000
#define AM_REG_GPIO_PADREGD_PAD14STRNG(n)            (((uint32_t)(n) << 18) & 0x00040000)
#define AM_REG_GPIO_PADREGD_PAD14STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGD_PAD14STRNG_HIGH          0x00040000

// Pad 14 input enable
#define AM_REG_GPIO_PADREGD_PAD14INPEN_S             17
#define AM_REG_GPIO_PADREGD_PAD14INPEN_M             0x00020000
#define AM_REG_GPIO_PADREGD_PAD14INPEN(n)            (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_GPIO_PADREGD_PAD14INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGD_PAD14INPEN_EN            0x00020000

// Pad 14 pullup enable
#define AM_REG_GPIO_PADREGD_PAD14PULL_S              16
#define AM_REG_GPIO_PADREGD_PAD14PULL_M              0x00010000
#define AM_REG_GPIO_PADREGD_PAD14PULL(n)             (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_PADREGD_PAD14PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGD_PAD14PULL_EN             0x00010000

// Pad 13 function select
#define AM_REG_GPIO_PADREGD_PAD13FNCSEL_S            11
#define AM_REG_GPIO_PADREGD_PAD13FNCSEL_M            0x00003800
#define AM_REG_GPIO_PADREGD_PAD13FNCSEL(n)           (((uint32_t)(n) << 11) & 0x00003800)
#define AM_REG_GPIO_PADREGD_PAD13FNCSEL_ADCD0PSE8    0x00000000
#define AM_REG_GPIO_PADREGD_PAD13FNCSEL_M1nCE1       0x00000800
#define AM_REG_GPIO_PADREGD_PAD13FNCSEL_TCTB0        0x00001000
#define AM_REG_GPIO_PADREGD_PAD13FNCSEL_GPIO13       0x00001800
#define AM_REG_GPIO_PADREGD_PAD13FNCSEL_M2nCE3       0x00002000
#define AM_REG_GPIO_PADREGD_PAD13FNCSEL_EXTHFB       0x00002800
#define AM_REG_GPIO_PADREGD_PAD13FNCSEL_UA0RTS       0x00003000
#define AM_REG_GPIO_PADREGD_PAD13FNCSEL_UART1RX      0x00003800

// Pad 13 drive strength
#define AM_REG_GPIO_PADREGD_PAD13STRNG_S             10
#define AM_REG_GPIO_PADREGD_PAD13STRNG_M             0x00000400
#define AM_REG_GPIO_PADREGD_PAD13STRNG(n)            (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_GPIO_PADREGD_PAD13STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGD_PAD13STRNG_HIGH          0x00000400

// Pad 13 input enable
#define AM_REG_GPIO_PADREGD_PAD13INPEN_S             9
#define AM_REG_GPIO_PADREGD_PAD13INPEN_M             0x00000200
#define AM_REG_GPIO_PADREGD_PAD13INPEN(n)            (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_GPIO_PADREGD_PAD13INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGD_PAD13INPEN_EN            0x00000200

// Pad 13 pullup enable
#define AM_REG_GPIO_PADREGD_PAD13PULL_S              8
#define AM_REG_GPIO_PADREGD_PAD13PULL_M              0x00000100
#define AM_REG_GPIO_PADREGD_PAD13PULL(n)             (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_PADREGD_PAD13PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGD_PAD13PULL_EN             0x00000100

// Pad 12 function select
#define AM_REG_GPIO_PADREGD_PAD12FNCSEL_S            3
#define AM_REG_GPIO_PADREGD_PAD12FNCSEL_M            0x00000038
#define AM_REG_GPIO_PADREGD_PAD12FNCSEL(n)           (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_GPIO_PADREGD_PAD12FNCSEL_ADCD0NSE9    0x00000000
#define AM_REG_GPIO_PADREGD_PAD12FNCSEL_M1nCE0       0x00000008
#define AM_REG_GPIO_PADREGD_PAD12FNCSEL_TCTA0        0x00000010
#define AM_REG_GPIO_PADREGD_PAD12FNCSEL_GPIO12       0x00000018
#define AM_REG_GPIO_PADREGD_PAD12FNCSEL_CLKOUT       0x00000020
#define AM_REG_GPIO_PADREGD_PAD12FNCSEL_PDM_CLK      0x00000028
#define AM_REG_GPIO_PADREGD_PAD12FNCSEL_UA0CTS       0x00000030
#define AM_REG_GPIO_PADREGD_PAD12FNCSEL_UART1TX      0x00000038

// Pad 12 drive strength
#define AM_REG_GPIO_PADREGD_PAD12STRNG_S             2
#define AM_REG_GPIO_PADREGD_PAD12STRNG_M             0x00000004
#define AM_REG_GPIO_PADREGD_PAD12STRNG(n)            (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_GPIO_PADREGD_PAD12STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGD_PAD12STRNG_HIGH          0x00000004

// Pad 12 input enable
#define AM_REG_GPIO_PADREGD_PAD12INPEN_S             1
#define AM_REG_GPIO_PADREGD_PAD12INPEN_M             0x00000002
#define AM_REG_GPIO_PADREGD_PAD12INPEN(n)            (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_GPIO_PADREGD_PAD12INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGD_PAD12INPEN_EN            0x00000002

// Pad 12 pullup enable
#define AM_REG_GPIO_PADREGD_PAD12PULL_S              0
#define AM_REG_GPIO_PADREGD_PAD12PULL_M              0x00000001
#define AM_REG_GPIO_PADREGD_PAD12PULL(n)             (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_PADREGD_PAD12PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGD_PAD12PULL_EN             0x00000001

//*****************************************************************************
//
// GPIO_PADREGE - Pad Configuration Register E
//
//*****************************************************************************
// Pad 19 function select
#define AM_REG_GPIO_PADREGE_PAD19FNCSEL_S            27
#define AM_REG_GPIO_PADREGE_PAD19FNCSEL_M            0x38000000
#define AM_REG_GPIO_PADREGE_PAD19FNCSEL(n)           (((uint32_t)(n) << 27) & 0x38000000)
#define AM_REG_GPIO_PADREGE_PAD19FNCSEL_CMPRF0       0x00000000
#define AM_REG_GPIO_PADREGE_PAD19FNCSEL_M0nCE3       0x08000000
#define AM_REG_GPIO_PADREGE_PAD19FNCSEL_TCTB1        0x10000000
#define AM_REG_GPIO_PADREGE_PAD19FNCSEL_GPIO19       0x18000000
#define AM_REG_GPIO_PADREGE_PAD19FNCSEL_TCTA1        0x20000000
#define AM_REG_GPIO_PADREGE_PAD19FNCSEL_ANATEST1     0x28000000
#define AM_REG_GPIO_PADREGE_PAD19FNCSEL_UART1RX      0x30000000
#define AM_REG_GPIO_PADREGE_PAD19FNCSEL_I2S_BCLK     0x38000000

// Pad 19 drive strength
#define AM_REG_GPIO_PADREGE_PAD19STRNG_S             26
#define AM_REG_GPIO_PADREGE_PAD19STRNG_M             0x04000000
#define AM_REG_GPIO_PADREGE_PAD19STRNG(n)            (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_GPIO_PADREGE_PAD19STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGE_PAD19STRNG_HIGH          0x04000000

// Pad 19 input enable
#define AM_REG_GPIO_PADREGE_PAD19INPEN_S             25
#define AM_REG_GPIO_PADREGE_PAD19INPEN_M             0x02000000
#define AM_REG_GPIO_PADREGE_PAD19INPEN(n)            (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_GPIO_PADREGE_PAD19INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGE_PAD19INPEN_EN            0x02000000

// Pad 19 pullup enable
#define AM_REG_GPIO_PADREGE_PAD19PULL_S              24
#define AM_REG_GPIO_PADREGE_PAD19PULL_M              0x01000000
#define AM_REG_GPIO_PADREGE_PAD19PULL(n)             (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_PADREGE_PAD19PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGE_PAD19PULL_EN             0x01000000

// Pad 18 function select
#define AM_REG_GPIO_PADREGE_PAD18FNCSEL_S            19
#define AM_REG_GPIO_PADREGE_PAD18FNCSEL_M            0x00380000
#define AM_REG_GPIO_PADREGE_PAD18FNCSEL(n)           (((uint32_t)(n) << 19) & 0x00380000)
#define AM_REG_GPIO_PADREGE_PAD18FNCSEL_CMPIN1       0x00000000
#define AM_REG_GPIO_PADREGE_PAD18FNCSEL_M0nCE2       0x00080000
#define AM_REG_GPIO_PADREGE_PAD18FNCSEL_TCTA1        0x00100000
#define AM_REG_GPIO_PADREGE_PAD18FNCSEL_GPIO18       0x00180000
#define AM_REG_GPIO_PADREGE_PAD18FNCSEL_M4nCE1       0x00200000
#define AM_REG_GPIO_PADREGE_PAD18FNCSEL_ANATEST2     0x00280000
#define AM_REG_GPIO_PADREGE_PAD18FNCSEL_UART1TX      0x00300000
#define AM_REG_GPIO_PADREGE_PAD18FNCSEL_32khz_XT     0x00380000

// Pad 18 drive strength
#define AM_REG_GPIO_PADREGE_PAD18STRNG_S             18
#define AM_REG_GPIO_PADREGE_PAD18STRNG_M             0x00040000
#define AM_REG_GPIO_PADREGE_PAD18STRNG(n)            (((uint32_t)(n) << 18) & 0x00040000)
#define AM_REG_GPIO_PADREGE_PAD18STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGE_PAD18STRNG_HIGH          0x00040000

// Pad 18 input enable
#define AM_REG_GPIO_PADREGE_PAD18INPEN_S             17
#define AM_REG_GPIO_PADREGE_PAD18INPEN_M             0x00020000
#define AM_REG_GPIO_PADREGE_PAD18INPEN(n)            (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_GPIO_PADREGE_PAD18INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGE_PAD18INPEN_EN            0x00020000

// Pad 18 pullup enable
#define AM_REG_GPIO_PADREGE_PAD18PULL_S              16
#define AM_REG_GPIO_PADREGE_PAD18PULL_M              0x00010000
#define AM_REG_GPIO_PADREGE_PAD18PULL(n)             (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_PADREGE_PAD18PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGE_PAD18PULL_EN             0x00010000

// Pad 17 function select
#define AM_REG_GPIO_PADREGE_PAD17FNCSEL_S            11
#define AM_REG_GPIO_PADREGE_PAD17FNCSEL_M            0x00003800
#define AM_REG_GPIO_PADREGE_PAD17FNCSEL(n)           (((uint32_t)(n) << 11) & 0x00003800)
#define AM_REG_GPIO_PADREGE_PAD17FNCSEL_CMPRF1       0x00000000
#define AM_REG_GPIO_PADREGE_PAD17FNCSEL_M0nCE1       0x00000800
#define AM_REG_GPIO_PADREGE_PAD17FNCSEL_TRIG1        0x00001000
#define AM_REG_GPIO_PADREGE_PAD17FNCSEL_GPIO17       0x00001800
#define AM_REG_GPIO_PADREGE_PAD17FNCSEL_M4nCE3       0x00002000
#define AM_REG_GPIO_PADREGE_PAD17FNCSEL_EXTLF        0x00002800
#define AM_REG_GPIO_PADREGE_PAD17FNCSEL_UART0RX      0x00003000
#define AM_REG_GPIO_PADREGE_PAD17FNCSEL_UA1CTS       0x00003800

// Pad 17 drive strength
#define AM_REG_GPIO_PADREGE_PAD17STRNG_S             10
#define AM_REG_GPIO_PADREGE_PAD17STRNG_M             0x00000400
#define AM_REG_GPIO_PADREGE_PAD17STRNG(n)            (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_GPIO_PADREGE_PAD17STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGE_PAD17STRNG_HIGH          0x00000400

// Pad 17 input enable
#define AM_REG_GPIO_PADREGE_PAD17INPEN_S             9
#define AM_REG_GPIO_PADREGE_PAD17INPEN_M             0x00000200
#define AM_REG_GPIO_PADREGE_PAD17INPEN(n)            (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_GPIO_PADREGE_PAD17INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGE_PAD17INPEN_EN            0x00000200

// Pad 17 pullup enable
#define AM_REG_GPIO_PADREGE_PAD17PULL_S              8
#define AM_REG_GPIO_PADREGE_PAD17PULL_M              0x00000100
#define AM_REG_GPIO_PADREGE_PAD17PULL(n)             (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_PADREGE_PAD17PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGE_PAD17PULL_EN             0x00000100

// Pad 16 function select
#define AM_REG_GPIO_PADREGE_PAD16FNCSEL_S            3
#define AM_REG_GPIO_PADREGE_PAD16FNCSEL_M            0x00000038
#define AM_REG_GPIO_PADREGE_PAD16FNCSEL(n)           (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_GPIO_PADREGE_PAD16FNCSEL_ADCSE0       0x00000000
#define AM_REG_GPIO_PADREGE_PAD16FNCSEL_M0nCE4       0x00000008
#define AM_REG_GPIO_PADREGE_PAD16FNCSEL_TRIG0        0x00000010
#define AM_REG_GPIO_PADREGE_PAD16FNCSEL_GPIO16       0x00000018
#define AM_REG_GPIO_PADREGE_PAD16FNCSEL_M2nCE3       0x00000020
#define AM_REG_GPIO_PADREGE_PAD16FNCSEL_CMPIN0       0x00000028
#define AM_REG_GPIO_PADREGE_PAD16FNCSEL_UART0TX      0x00000030
#define AM_REG_GPIO_PADREGE_PAD16FNCSEL_UA1RTS       0x00000038

// Pad 16 drive strength
#define AM_REG_GPIO_PADREGE_PAD16STRNG_S             2
#define AM_REG_GPIO_PADREGE_PAD16STRNG_M             0x00000004
#define AM_REG_GPIO_PADREGE_PAD16STRNG(n)            (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_GPIO_PADREGE_PAD16STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGE_PAD16STRNG_HIGH          0x00000004

// Pad 16 input enable
#define AM_REG_GPIO_PADREGE_PAD16INPEN_S             1
#define AM_REG_GPIO_PADREGE_PAD16INPEN_M             0x00000002
#define AM_REG_GPIO_PADREGE_PAD16INPEN(n)            (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_GPIO_PADREGE_PAD16INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGE_PAD16INPEN_EN            0x00000002

// Pad 16 pullup enable
#define AM_REG_GPIO_PADREGE_PAD16PULL_S              0
#define AM_REG_GPIO_PADREGE_PAD16PULL_M              0x00000001
#define AM_REG_GPIO_PADREGE_PAD16PULL(n)             (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_PADREGE_PAD16PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGE_PAD16PULL_EN             0x00000001

//*****************************************************************************
//
// GPIO_PADREGF - Pad Configuration Register F
//
//*****************************************************************************
// Pad 23 function select
#define AM_REG_GPIO_PADREGF_PAD23FNCSEL_S            27
#define AM_REG_GPIO_PADREGF_PAD23FNCSEL_M            0x38000000
#define AM_REG_GPIO_PADREGF_PAD23FNCSEL(n)           (((uint32_t)(n) << 27) & 0x38000000)
#define AM_REG_GPIO_PADREGF_PAD23FNCSEL_UART0RX      0x00000000
#define AM_REG_GPIO_PADREGF_PAD23FNCSEL_M0nCE0       0x08000000
#define AM_REG_GPIO_PADREGF_PAD23FNCSEL_TCTB3        0x10000000
#define AM_REG_GPIO_PADREGF_PAD23FNCSEL_GPIO23       0x18000000
#define AM_REG_GPIO_PADREGF_PAD23FNCSEL_PDM_DATA     0x20000000
#define AM_REG_GPIO_PADREGF_PAD23FNCSEL_CMPOUT       0x28000000
#define AM_REG_GPIO_PADREGF_PAD23FNCSEL_TCTB1        0x30000000
#define AM_REG_GPIO_PADREGF_PAD23FNCSEL_UNDEF7       0x38000000

// Pad 23 drive strength
#define AM_REG_GPIO_PADREGF_PAD23STRNG_S             26
#define AM_REG_GPIO_PADREGF_PAD23STRNG_M             0x04000000
#define AM_REG_GPIO_PADREGF_PAD23STRNG(n)            (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_GPIO_PADREGF_PAD23STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGF_PAD23STRNG_HIGH          0x04000000

// Pad 23 input enable
#define AM_REG_GPIO_PADREGF_PAD23INPEN_S             25
#define AM_REG_GPIO_PADREGF_PAD23INPEN_M             0x02000000
#define AM_REG_GPIO_PADREGF_PAD23INPEN(n)            (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_GPIO_PADREGF_PAD23INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGF_PAD23INPEN_EN            0x02000000

// Pad 23 pullup enable
#define AM_REG_GPIO_PADREGF_PAD23PULL_S              24
#define AM_REG_GPIO_PADREGF_PAD23PULL_M              0x01000000
#define AM_REG_GPIO_PADREGF_PAD23PULL(n)             (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_PADREGF_PAD23PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGF_PAD23PULL_EN             0x01000000

// Pad 22  upper power switch enable
#define AM_REG_GPIO_PADREGF_PAD22PWRUP_S             23
#define AM_REG_GPIO_PADREGF_PAD22PWRUP_M             0x00800000
#define AM_REG_GPIO_PADREGF_PAD22PWRUP(n)            (((uint32_t)(n) << 23) & 0x00800000)
#define AM_REG_GPIO_PADREGF_PAD22PWRUP_DIS           0x00000000
#define AM_REG_GPIO_PADREGF_PAD22PWRUP_EN            0x00800000

// Pad 22 function select
#define AM_REG_GPIO_PADREGF_PAD22FNCSEL_S            19
#define AM_REG_GPIO_PADREGF_PAD22FNCSEL_M            0x00380000
#define AM_REG_GPIO_PADREGF_PAD22FNCSEL(n)           (((uint32_t)(n) << 19) & 0x00380000)
#define AM_REG_GPIO_PADREGF_PAD22FNCSEL_UART0TX      0x00000000
#define AM_REG_GPIO_PADREGF_PAD22FNCSEL_M1nCE7       0x00080000
#define AM_REG_GPIO_PADREGF_PAD22FNCSEL_TCTA3        0x00100000
#define AM_REG_GPIO_PADREGF_PAD22FNCSEL_GPIO22       0x00180000
#define AM_REG_GPIO_PADREGF_PAD22FNCSEL_PDM_CLK      0x00200000
#define AM_REG_GPIO_PADREGF_PAD22FNCSEL_UNDEF5       0x00280000
#define AM_REG_GPIO_PADREGF_PAD22FNCSEL_TCTB1        0x00300000
#define AM_REG_GPIO_PADREGF_PAD22FNCSEL_SWO          0x00380000

// Pad 22 drive strength
#define AM_REG_GPIO_PADREGF_PAD22STRNG_S             18
#define AM_REG_GPIO_PADREGF_PAD22STRNG_M             0x00040000
#define AM_REG_GPIO_PADREGF_PAD22STRNG(n)            (((uint32_t)(n) << 18) & 0x00040000)
#define AM_REG_GPIO_PADREGF_PAD22STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGF_PAD22STRNG_HIGH          0x00040000

// Pad 22 input enable
#define AM_REG_GPIO_PADREGF_PAD22INPEN_S             17
#define AM_REG_GPIO_PADREGF_PAD22INPEN_M             0x00020000
#define AM_REG_GPIO_PADREGF_PAD22INPEN(n)            (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_GPIO_PADREGF_PAD22INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGF_PAD22INPEN_EN            0x00020000

// Pad 22 pullup enable
#define AM_REG_GPIO_PADREGF_PAD22PULL_S              16
#define AM_REG_GPIO_PADREGF_PAD22PULL_M              0x00010000
#define AM_REG_GPIO_PADREGF_PAD22PULL(n)             (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_PADREGF_PAD22PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGF_PAD22PULL_EN             0x00010000

// Pad 21 function select
#define AM_REG_GPIO_PADREGF_PAD21FNCSEL_S            11
#define AM_REG_GPIO_PADREGF_PAD21FNCSEL_M            0x00003800
#define AM_REG_GPIO_PADREGF_PAD21FNCSEL(n)           (((uint32_t)(n) << 11) & 0x00003800)
#define AM_REG_GPIO_PADREGF_PAD21FNCSEL_SWDIO        0x00000000
#define AM_REG_GPIO_PADREGF_PAD21FNCSEL_M1nCE6       0x00000800
#define AM_REG_GPIO_PADREGF_PAD21FNCSEL_TCTB2        0x00001000
#define AM_REG_GPIO_PADREGF_PAD21FNCSEL_GPIO21       0x00001800
#define AM_REG_GPIO_PADREGF_PAD21FNCSEL_UART0RX      0x00002000
#define AM_REG_GPIO_PADREGF_PAD21FNCSEL_UART1RX      0x00002800
#define AM_REG_GPIO_PADREGF_PAD21FNCSEL_UNDEF6       0x00003000
#define AM_REG_GPIO_PADREGF_PAD21FNCSEL_UNDEF7       0x00003800

// Pad 21 drive strength
#define AM_REG_GPIO_PADREGF_PAD21STRNG_S             10
#define AM_REG_GPIO_PADREGF_PAD21STRNG_M             0x00000400
#define AM_REG_GPIO_PADREGF_PAD21STRNG(n)            (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_GPIO_PADREGF_PAD21STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGF_PAD21STRNG_HIGH          0x00000400

// Pad 21 input enable
#define AM_REG_GPIO_PADREGF_PAD21INPEN_S             9
#define AM_REG_GPIO_PADREGF_PAD21INPEN_M             0x00000200
#define AM_REG_GPIO_PADREGF_PAD21INPEN(n)            (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_GPIO_PADREGF_PAD21INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGF_PAD21INPEN_EN            0x00000200

// Pad 21 pullup enable
#define AM_REG_GPIO_PADREGF_PAD21PULL_S              8
#define AM_REG_GPIO_PADREGF_PAD21PULL_M              0x00000100
#define AM_REG_GPIO_PADREGF_PAD21PULL(n)             (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_PADREGF_PAD21PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGF_PAD21PULL_EN             0x00000100

// Pad 20 function select
#define AM_REG_GPIO_PADREGF_PAD20FNCSEL_S            3
#define AM_REG_GPIO_PADREGF_PAD20FNCSEL_M            0x00000038
#define AM_REG_GPIO_PADREGF_PAD20FNCSEL(n)           (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_GPIO_PADREGF_PAD20FNCSEL_SWDCK        0x00000000
#define AM_REG_GPIO_PADREGF_PAD20FNCSEL_M1nCE5       0x00000008
#define AM_REG_GPIO_PADREGF_PAD20FNCSEL_TCTA2        0x00000010
#define AM_REG_GPIO_PADREGF_PAD20FNCSEL_GPIO20       0x00000018
#define AM_REG_GPIO_PADREGF_PAD20FNCSEL_UART0TX      0x00000020
#define AM_REG_GPIO_PADREGF_PAD20FNCSEL_UART1TX      0x00000028
#define AM_REG_GPIO_PADREGF_PAD20FNCSEL_UNDEF6       0x00000030
#define AM_REG_GPIO_PADREGF_PAD20FNCSEL_UNDEF7       0x00000038

// Pad 20 drive strength
#define AM_REG_GPIO_PADREGF_PAD20STRNG_S             2
#define AM_REG_GPIO_PADREGF_PAD20STRNG_M             0x00000004
#define AM_REG_GPIO_PADREGF_PAD20STRNG(n)            (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_GPIO_PADREGF_PAD20STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGF_PAD20STRNG_HIGH          0x00000004

// Pad 20 input enable
#define AM_REG_GPIO_PADREGF_PAD20INPEN_S             1
#define AM_REG_GPIO_PADREGF_PAD20INPEN_M             0x00000002
#define AM_REG_GPIO_PADREGF_PAD20INPEN(n)            (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_GPIO_PADREGF_PAD20INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGF_PAD20INPEN_EN            0x00000002

// Pad 20 pulldown enable
#define AM_REG_GPIO_PADREGF_PAD20PULL_S              0
#define AM_REG_GPIO_PADREGF_PAD20PULL_M              0x00000001
#define AM_REG_GPIO_PADREGF_PAD20PULL(n)             (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_PADREGF_PAD20PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGF_PAD20PULL_EN             0x00000001

//*****************************************************************************
//
// GPIO_PADREGG - Pad Configuration Register G
//
//*****************************************************************************
// Pad 27 pullup resistor selection.
#define AM_REG_GPIO_PADREGG_PAD27RSEL_S              30
#define AM_REG_GPIO_PADREGG_PAD27RSEL_M              0xC0000000
#define AM_REG_GPIO_PADREGG_PAD27RSEL(n)             (((uint32_t)(n) << 30) & 0xC0000000)
#define AM_REG_GPIO_PADREGG_PAD27RSEL_PULL1_5K       0x00000000
#define AM_REG_GPIO_PADREGG_PAD27RSEL_PULL6K         0x40000000
#define AM_REG_GPIO_PADREGG_PAD27RSEL_PULL12K        0x80000000
#define AM_REG_GPIO_PADREGG_PAD27RSEL_PULL24K        0xC0000000

// Pad 27 function select
#define AM_REG_GPIO_PADREGG_PAD27FNCSEL_S            27
#define AM_REG_GPIO_PADREGG_PAD27FNCSEL_M            0x38000000
#define AM_REG_GPIO_PADREGG_PAD27FNCSEL(n)           (((uint32_t)(n) << 27) & 0x38000000)
#define AM_REG_GPIO_PADREGG_PAD27FNCSEL_EXTHF        0x00000000
#define AM_REG_GPIO_PADREGG_PAD27FNCSEL_M1nCE4       0x08000000
#define AM_REG_GPIO_PADREGG_PAD27FNCSEL_TCTA1        0x10000000
#define AM_REG_GPIO_PADREGG_PAD27FNCSEL_GPIO27       0x18000000
#define AM_REG_GPIO_PADREGG_PAD27FNCSEL_M2SCL        0x20000000
#define AM_REG_GPIO_PADREGG_PAD27FNCSEL_M2SCK        0x28000000
#define AM_REG_GPIO_PADREGG_PAD27FNCSEL_M2SCKLB      0x30000000
#define AM_REG_GPIO_PADREGG_PAD27FNCSEL_M2SCLLB      0x38000000

// Pad 27 drive strength
#define AM_REG_GPIO_PADREGG_PAD27STRNG_S             26
#define AM_REG_GPIO_PADREGG_PAD27STRNG_M             0x04000000
#define AM_REG_GPIO_PADREGG_PAD27STRNG(n)            (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_GPIO_PADREGG_PAD27STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGG_PAD27STRNG_HIGH          0x04000000

// Pad 27 input enable
#define AM_REG_GPIO_PADREGG_PAD27INPEN_S             25
#define AM_REG_GPIO_PADREGG_PAD27INPEN_M             0x02000000
#define AM_REG_GPIO_PADREGG_PAD27INPEN(n)            (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_GPIO_PADREGG_PAD27INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGG_PAD27INPEN_EN            0x02000000

// Pad 27 pullup enable
#define AM_REG_GPIO_PADREGG_PAD27PULL_S              24
#define AM_REG_GPIO_PADREGG_PAD27PULL_M              0x01000000
#define AM_REG_GPIO_PADREGG_PAD27PULL(n)             (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_PADREGG_PAD27PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGG_PAD27PULL_EN             0x01000000

// Pad 26 function select
#define AM_REG_GPIO_PADREGG_PAD26FNCSEL_S            19
#define AM_REG_GPIO_PADREGG_PAD26FNCSEL_M            0x00380000
#define AM_REG_GPIO_PADREGG_PAD26FNCSEL(n)           (((uint32_t)(n) << 19) & 0x00380000)
#define AM_REG_GPIO_PADREGG_PAD26FNCSEL_EXTLF        0x00000000
#define AM_REG_GPIO_PADREGG_PAD26FNCSEL_M0nCE3       0x00080000
#define AM_REG_GPIO_PADREGG_PAD26FNCSEL_TCTB0        0x00100000
#define AM_REG_GPIO_PADREGG_PAD26FNCSEL_GPIO26       0x00180000
#define AM_REG_GPIO_PADREGG_PAD26FNCSEL_M2nCE0       0x00200000
#define AM_REG_GPIO_PADREGG_PAD26FNCSEL_TCTA1        0x00280000
#define AM_REG_GPIO_PADREGG_PAD26FNCSEL_M5nCE1       0x00300000
#define AM_REG_GPIO_PADREGG_PAD26FNCSEL_M3nCE0       0x00380000

// Pad 26 drive strength
#define AM_REG_GPIO_PADREGG_PAD26STRNG_S             18
#define AM_REG_GPIO_PADREGG_PAD26STRNG_M             0x00040000
#define AM_REG_GPIO_PADREGG_PAD26STRNG(n)            (((uint32_t)(n) << 18) & 0x00040000)
#define AM_REG_GPIO_PADREGG_PAD26STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGG_PAD26STRNG_HIGH          0x00040000

// Pad 26 input enable
#define AM_REG_GPIO_PADREGG_PAD26INPEN_S             17
#define AM_REG_GPIO_PADREGG_PAD26INPEN_M             0x00020000
#define AM_REG_GPIO_PADREGG_PAD26INPEN(n)            (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_GPIO_PADREGG_PAD26INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGG_PAD26INPEN_EN            0x00020000

// Pad 26 pullup enable
#define AM_REG_GPIO_PADREGG_PAD26PULL_S              16
#define AM_REG_GPIO_PADREGG_PAD26PULL_M              0x00010000
#define AM_REG_GPIO_PADREGG_PAD26PULL(n)             (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_PADREGG_PAD26PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGG_PAD26PULL_EN             0x00010000

// Pad 25 pullup resistor selection.
#define AM_REG_GPIO_PADREGG_PAD25RSEL_S              14
#define AM_REG_GPIO_PADREGG_PAD25RSEL_M              0x0000C000
#define AM_REG_GPIO_PADREGG_PAD25RSEL(n)             (((uint32_t)(n) << 14) & 0x0000C000)
#define AM_REG_GPIO_PADREGG_PAD25RSEL_PULL1_5K       0x00000000
#define AM_REG_GPIO_PADREGG_PAD25RSEL_PULL6K         0x00004000
#define AM_REG_GPIO_PADREGG_PAD25RSEL_PULL12K        0x00008000
#define AM_REG_GPIO_PADREGG_PAD25RSEL_PULL24K        0x0000C000

// Pad 25 function select
#define AM_REG_GPIO_PADREGG_PAD25FNCSEL_S            11
#define AM_REG_GPIO_PADREGG_PAD25FNCSEL_M            0x00003800
#define AM_REG_GPIO_PADREGG_PAD25FNCSEL(n)           (((uint32_t)(n) << 11) & 0x00003800)
#define AM_REG_GPIO_PADREGG_PAD25FNCSEL_EXTXT        0x00000000
#define AM_REG_GPIO_PADREGG_PAD25FNCSEL_M0nCE2       0x00000800
#define AM_REG_GPIO_PADREGG_PAD25FNCSEL_TCTA0        0x00001000
#define AM_REG_GPIO_PADREGG_PAD25FNCSEL_GPIO25       0x00001800
#define AM_REG_GPIO_PADREGG_PAD25FNCSEL_M2SDA        0x00002000
#define AM_REG_GPIO_PADREGG_PAD25FNCSEL_M2MISO       0x00002800
#define AM_REG_GPIO_PADREGG_PAD25FNCSEL_SLMISOLB     0x00003000
#define AM_REG_GPIO_PADREGG_PAD25FNCSEL_SLSDALB      0x00003800

// Pad 25 drive strength
#define AM_REG_GPIO_PADREGG_PAD25STRNG_S             10
#define AM_REG_GPIO_PADREGG_PAD25STRNG_M             0x00000400
#define AM_REG_GPIO_PADREGG_PAD25STRNG(n)            (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_GPIO_PADREGG_PAD25STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGG_PAD25STRNG_HIGH          0x00000400

// Pad 25 input enable
#define AM_REG_GPIO_PADREGG_PAD25INPEN_S             9
#define AM_REG_GPIO_PADREGG_PAD25INPEN_M             0x00000200
#define AM_REG_GPIO_PADREGG_PAD25INPEN(n)            (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_GPIO_PADREGG_PAD25INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGG_PAD25INPEN_EN            0x00000200

// Pad 25 pullup enable
#define AM_REG_GPIO_PADREGG_PAD25PULL_S              8
#define AM_REG_GPIO_PADREGG_PAD25PULL_M              0x00000100
#define AM_REG_GPIO_PADREGG_PAD25PULL(n)             (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_PADREGG_PAD25PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGG_PAD25PULL_EN             0x00000100

// Pad 24 function select
#define AM_REG_GPIO_PADREGG_PAD24FNCSEL_S            3
#define AM_REG_GPIO_PADREGG_PAD24FNCSEL_M            0x00000038
#define AM_REG_GPIO_PADREGG_PAD24FNCSEL(n)           (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_GPIO_PADREGG_PAD24FNCSEL_M2nCE1       0x00000000
#define AM_REG_GPIO_PADREGG_PAD24FNCSEL_M0nCE1       0x00000008
#define AM_REG_GPIO_PADREGG_PAD24FNCSEL_CLKOUT       0x00000010
#define AM_REG_GPIO_PADREGG_PAD24FNCSEL_GPIO24       0x00000018
#define AM_REG_GPIO_PADREGG_PAD24FNCSEL_M5nCE0       0x00000020
#define AM_REG_GPIO_PADREGG_PAD24FNCSEL_TCTA1        0x00000028
#define AM_REG_GPIO_PADREGG_PAD24FNCSEL_I2S_BCLK     0x00000030
#define AM_REG_GPIO_PADREGG_PAD24FNCSEL_SWO          0x00000038

// Pad 24 drive strength
#define AM_REG_GPIO_PADREGG_PAD24STRNG_S             2
#define AM_REG_GPIO_PADREGG_PAD24STRNG_M             0x00000004
#define AM_REG_GPIO_PADREGG_PAD24STRNG(n)            (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_GPIO_PADREGG_PAD24STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGG_PAD24STRNG_HIGH          0x00000004

// Pad 24 input enable
#define AM_REG_GPIO_PADREGG_PAD24INPEN_S             1
#define AM_REG_GPIO_PADREGG_PAD24INPEN_M             0x00000002
#define AM_REG_GPIO_PADREGG_PAD24INPEN(n)            (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_GPIO_PADREGG_PAD24INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGG_PAD24INPEN_EN            0x00000002

// Pad 24 pullup enable
#define AM_REG_GPIO_PADREGG_PAD24PULL_S              0
#define AM_REG_GPIO_PADREGG_PAD24PULL_M              0x00000001
#define AM_REG_GPIO_PADREGG_PAD24PULL(n)             (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_PADREGG_PAD24PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGG_PAD24PULL_EN             0x00000001

//*****************************************************************************
//
// GPIO_PADREGH - Pad Configuration Register H
//
//*****************************************************************************
// Pad 31 function select
#define AM_REG_GPIO_PADREGH_PAD31FNCSEL_S            27
#define AM_REG_GPIO_PADREGH_PAD31FNCSEL_M            0x38000000
#define AM_REG_GPIO_PADREGH_PAD31FNCSEL(n)           (((uint32_t)(n) << 27) & 0x38000000)
#define AM_REG_GPIO_PADREGH_PAD31FNCSEL_ADCSE3       0x00000000
#define AM_REG_GPIO_PADREGH_PAD31FNCSEL_M0nCE4       0x08000000
#define AM_REG_GPIO_PADREGH_PAD31FNCSEL_TCTA3        0x10000000
#define AM_REG_GPIO_PADREGH_PAD31FNCSEL_GPIO31       0x18000000
#define AM_REG_GPIO_PADREGH_PAD31FNCSEL_UART0RX      0x20000000
#define AM_REG_GPIO_PADREGH_PAD31FNCSEL_TCTB1        0x28000000
#define AM_REG_GPIO_PADREGH_PAD31FNCSEL_UNDEF6       0x30000000
#define AM_REG_GPIO_PADREGH_PAD31FNCSEL_UNDEF7       0x38000000

// Pad 31 drive strength
#define AM_REG_GPIO_PADREGH_PAD31STRNG_S             26
#define AM_REG_GPIO_PADREGH_PAD31STRNG_M             0x04000000
#define AM_REG_GPIO_PADREGH_PAD31STRNG(n)            (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_GPIO_PADREGH_PAD31STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGH_PAD31STRNG_HIGH          0x04000000

// Pad 31 input enable
#define AM_REG_GPIO_PADREGH_PAD31INPEN_S             25
#define AM_REG_GPIO_PADREGH_PAD31INPEN_M             0x02000000
#define AM_REG_GPIO_PADREGH_PAD31INPEN(n)            (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_GPIO_PADREGH_PAD31INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGH_PAD31INPEN_EN            0x02000000

// Pad 31 pullup enable
#define AM_REG_GPIO_PADREGH_PAD31PULL_S              24
#define AM_REG_GPIO_PADREGH_PAD31PULL_M              0x01000000
#define AM_REG_GPIO_PADREGH_PAD31PULL(n)             (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_PADREGH_PAD31PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGH_PAD31PULL_EN             0x01000000

// Pad 30 function select
#define AM_REG_GPIO_PADREGH_PAD30FNCSEL_S            19
#define AM_REG_GPIO_PADREGH_PAD30FNCSEL_M            0x00380000
#define AM_REG_GPIO_PADREGH_PAD30FNCSEL(n)           (((uint32_t)(n) << 19) & 0x00380000)
#define AM_REG_GPIO_PADREGH_PAD30FNCSEL_UNDEF0       0x00000000
#define AM_REG_GPIO_PADREGH_PAD30FNCSEL_M1nCE7       0x00080000
#define AM_REG_GPIO_PADREGH_PAD30FNCSEL_TCTB2        0x00100000
#define AM_REG_GPIO_PADREGH_PAD30FNCSEL_GPIO30       0x00180000
#define AM_REG_GPIO_PADREGH_PAD30FNCSEL_UART0TX      0x00200000
#define AM_REG_GPIO_PADREGH_PAD30FNCSEL_UA1RTS       0x00280000
#define AM_REG_GPIO_PADREGH_PAD30FNCSEL_UNDEF6       0x00300000
#define AM_REG_GPIO_PADREGH_PAD30FNCSEL_I2S_DAT      0x00380000

// Pad 30 drive strength
#define AM_REG_GPIO_PADREGH_PAD30STRNG_S             18
#define AM_REG_GPIO_PADREGH_PAD30STRNG_M             0x00040000
#define AM_REG_GPIO_PADREGH_PAD30STRNG(n)            (((uint32_t)(n) << 18) & 0x00040000)
#define AM_REG_GPIO_PADREGH_PAD30STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGH_PAD30STRNG_HIGH          0x00040000

// Pad 30 input enable
#define AM_REG_GPIO_PADREGH_PAD30INPEN_S             17
#define AM_REG_GPIO_PADREGH_PAD30INPEN_M             0x00020000
#define AM_REG_GPIO_PADREGH_PAD30INPEN(n)            (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_GPIO_PADREGH_PAD30INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGH_PAD30INPEN_EN            0x00020000

// Pad 30 pullup enable
#define AM_REG_GPIO_PADREGH_PAD30PULL_S              16
#define AM_REG_GPIO_PADREGH_PAD30PULL_M              0x00010000
#define AM_REG_GPIO_PADREGH_PAD30PULL(n)             (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_PADREGH_PAD30PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGH_PAD30PULL_EN             0x00010000

// Pad 29 function select
#define AM_REG_GPIO_PADREGH_PAD29FNCSEL_S            11
#define AM_REG_GPIO_PADREGH_PAD29FNCSEL_M            0x00003800
#define AM_REG_GPIO_PADREGH_PAD29FNCSEL(n)           (((uint32_t)(n) << 11) & 0x00003800)
#define AM_REG_GPIO_PADREGH_PAD29FNCSEL_ADCSE1       0x00000000
#define AM_REG_GPIO_PADREGH_PAD29FNCSEL_M1nCE6       0x00000800
#define AM_REG_GPIO_PADREGH_PAD29FNCSEL_TCTA2        0x00001000
#define AM_REG_GPIO_PADREGH_PAD29FNCSEL_GPIO29       0x00001800
#define AM_REG_GPIO_PADREGH_PAD29FNCSEL_UA0CTS       0x00002000
#define AM_REG_GPIO_PADREGH_PAD29FNCSEL_UA1CTS       0x00002800
#define AM_REG_GPIO_PADREGH_PAD29FNCSEL_M4nCE0       0x00003000
#define AM_REG_GPIO_PADREGH_PAD29FNCSEL_PDM_DATA     0x00003800

// Pad 29 drive strength
#define AM_REG_GPIO_PADREGH_PAD29STRNG_S             10
#define AM_REG_GPIO_PADREGH_PAD29STRNG_M             0x00000400
#define AM_REG_GPIO_PADREGH_PAD29STRNG(n)            (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_GPIO_PADREGH_PAD29STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGH_PAD29STRNG_HIGH          0x00000400

// Pad 29 input enable
#define AM_REG_GPIO_PADREGH_PAD29INPEN_S             9
#define AM_REG_GPIO_PADREGH_PAD29INPEN_M             0x00000200
#define AM_REG_GPIO_PADREGH_PAD29INPEN(n)            (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_GPIO_PADREGH_PAD29INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGH_PAD29INPEN_EN            0x00000200

// Pad 29 pullup enable
#define AM_REG_GPIO_PADREGH_PAD29PULL_S              8
#define AM_REG_GPIO_PADREGH_PAD29PULL_M              0x00000100
#define AM_REG_GPIO_PADREGH_PAD29PULL(n)             (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_PADREGH_PAD29PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGH_PAD29PULL_EN             0x00000100

// Pad 28 function select
#define AM_REG_GPIO_PADREGH_PAD28FNCSEL_S            3
#define AM_REG_GPIO_PADREGH_PAD28FNCSEL_M            0x00000038
#define AM_REG_GPIO_PADREGH_PAD28FNCSEL(n)           (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_GPIO_PADREGH_PAD28FNCSEL_I2S_WCLK     0x00000000
#define AM_REG_GPIO_PADREGH_PAD28FNCSEL_M1nCE5       0x00000008
#define AM_REG_GPIO_PADREGH_PAD28FNCSEL_TCTB1        0x00000010
#define AM_REG_GPIO_PADREGH_PAD28FNCSEL_GPIO28       0x00000018
#define AM_REG_GPIO_PADREGH_PAD28FNCSEL_M2WIR3       0x00000020
#define AM_REG_GPIO_PADREGH_PAD28FNCSEL_M2MOSI       0x00000028
#define AM_REG_GPIO_PADREGH_PAD28FNCSEL_M5nCE3       0x00000030
#define AM_REG_GPIO_PADREGH_PAD28FNCSEL_SLWIR3LB     0x00000038

// Pad 28 drive strength
#define AM_REG_GPIO_PADREGH_PAD28STRNG_S             2
#define AM_REG_GPIO_PADREGH_PAD28STRNG_M             0x00000004
#define AM_REG_GPIO_PADREGH_PAD28STRNG(n)            (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_GPIO_PADREGH_PAD28STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGH_PAD28STRNG_HIGH          0x00000004

// Pad 28 input enable
#define AM_REG_GPIO_PADREGH_PAD28INPEN_S             1
#define AM_REG_GPIO_PADREGH_PAD28INPEN_M             0x00000002
#define AM_REG_GPIO_PADREGH_PAD28INPEN(n)            (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_GPIO_PADREGH_PAD28INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGH_PAD28INPEN_EN            0x00000002

// Pad 28 pullup enable
#define AM_REG_GPIO_PADREGH_PAD28PULL_S              0
#define AM_REG_GPIO_PADREGH_PAD28PULL_M              0x00000001
#define AM_REG_GPIO_PADREGH_PAD28PULL(n)             (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_PADREGH_PAD28PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGH_PAD28PULL_EN             0x00000001

//*****************************************************************************
//
// GPIO_PADREGI - Pad Configuration Register I
//
//*****************************************************************************
// Pad 35 function select
#define AM_REG_GPIO_PADREGI_PAD35FNCSEL_S            27
#define AM_REG_GPIO_PADREGI_PAD35FNCSEL_M            0x38000000
#define AM_REG_GPIO_PADREGI_PAD35FNCSEL(n)           (((uint32_t)(n) << 27) & 0x38000000)
#define AM_REG_GPIO_PADREGI_PAD35FNCSEL_ADCSE7       0x00000000
#define AM_REG_GPIO_PADREGI_PAD35FNCSEL_M1nCE0       0x08000000
#define AM_REG_GPIO_PADREGI_PAD35FNCSEL_UART1TX      0x10000000
#define AM_REG_GPIO_PADREGI_PAD35FNCSEL_GPIO35       0x18000000
#define AM_REG_GPIO_PADREGI_PAD35FNCSEL_M4nCE6       0x20000000
#define AM_REG_GPIO_PADREGI_PAD35FNCSEL_TCTA1        0x28000000
#define AM_REG_GPIO_PADREGI_PAD35FNCSEL_UA0RTS       0x30000000
#define AM_REG_GPIO_PADREGI_PAD35FNCSEL_M3nCE2       0x38000000

// Pad 35 drive strength
#define AM_REG_GPIO_PADREGI_PAD35STRNG_S             26
#define AM_REG_GPIO_PADREGI_PAD35STRNG_M             0x04000000
#define AM_REG_GPIO_PADREGI_PAD35STRNG(n)            (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_GPIO_PADREGI_PAD35STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGI_PAD35STRNG_HIGH          0x04000000

// Pad 35 input enable
#define AM_REG_GPIO_PADREGI_PAD35INPEN_S             25
#define AM_REG_GPIO_PADREGI_PAD35INPEN_M             0x02000000
#define AM_REG_GPIO_PADREGI_PAD35INPEN(n)            (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_GPIO_PADREGI_PAD35INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGI_PAD35INPEN_EN            0x02000000

// Pad 35 pullup enable
#define AM_REG_GPIO_PADREGI_PAD35PULL_S              24
#define AM_REG_GPIO_PADREGI_PAD35PULL_M              0x01000000
#define AM_REG_GPIO_PADREGI_PAD35PULL(n)             (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_PADREGI_PAD35PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGI_PAD35PULL_EN             0x01000000

// Pad 34 function select
#define AM_REG_GPIO_PADREGI_PAD34FNCSEL_S            19
#define AM_REG_GPIO_PADREGI_PAD34FNCSEL_M            0x00380000
#define AM_REG_GPIO_PADREGI_PAD34FNCSEL(n)           (((uint32_t)(n) << 19) & 0x00380000)
#define AM_REG_GPIO_PADREGI_PAD34FNCSEL_ADCSE6       0x00000000
#define AM_REG_GPIO_PADREGI_PAD34FNCSEL_M0nCE7       0x00080000
#define AM_REG_GPIO_PADREGI_PAD34FNCSEL_M2nCE3       0x00100000
#define AM_REG_GPIO_PADREGI_PAD34FNCSEL_GPIO34       0x00180000
#define AM_REG_GPIO_PADREGI_PAD34FNCSEL_CMPRF2       0x00200000
#define AM_REG_GPIO_PADREGI_PAD34FNCSEL_M3nCE1       0x00280000
#define AM_REG_GPIO_PADREGI_PAD34FNCSEL_M4nCE0       0x00300000
#define AM_REG_GPIO_PADREGI_PAD34FNCSEL_M5nCE2       0x00380000

// Pad 34 drive strength
#define AM_REG_GPIO_PADREGI_PAD34STRNG_S             18
#define AM_REG_GPIO_PADREGI_PAD34STRNG_M             0x00040000
#define AM_REG_GPIO_PADREGI_PAD34STRNG(n)            (((uint32_t)(n) << 18) & 0x00040000)
#define AM_REG_GPIO_PADREGI_PAD34STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGI_PAD34STRNG_HIGH          0x00040000

// Pad 34 input enable
#define AM_REG_GPIO_PADREGI_PAD34INPEN_S             17
#define AM_REG_GPIO_PADREGI_PAD34INPEN_M             0x00020000
#define AM_REG_GPIO_PADREGI_PAD34INPEN(n)            (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_GPIO_PADREGI_PAD34INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGI_PAD34INPEN_EN            0x00020000

// Pad 34 pullup enable
#define AM_REG_GPIO_PADREGI_PAD34PULL_S              16
#define AM_REG_GPIO_PADREGI_PAD34PULL_M              0x00010000
#define AM_REG_GPIO_PADREGI_PAD34PULL(n)             (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_PADREGI_PAD34PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGI_PAD34PULL_EN             0x00010000

// Pad 33 function select
#define AM_REG_GPIO_PADREGI_PAD33FNCSEL_S            11
#define AM_REG_GPIO_PADREGI_PAD33FNCSEL_M            0x00003800
#define AM_REG_GPIO_PADREGI_PAD33FNCSEL(n)           (((uint32_t)(n) << 11) & 0x00003800)
#define AM_REG_GPIO_PADREGI_PAD33FNCSEL_ADCSE5       0x00000000
#define AM_REG_GPIO_PADREGI_PAD33FNCSEL_M0nCE6       0x00000800
#define AM_REG_GPIO_PADREGI_PAD33FNCSEL_32khz_XT     0x00001000
#define AM_REG_GPIO_PADREGI_PAD33FNCSEL_GPIO33       0x00001800
#define AM_REG_GPIO_PADREGI_PAD33FNCSEL_UNDEF4       0x00002000
#define AM_REG_GPIO_PADREGI_PAD33FNCSEL_M3nCE7       0x00002800
#define AM_REG_GPIO_PADREGI_PAD33FNCSEL_TCTB1        0x00003000
#define AM_REG_GPIO_PADREGI_PAD33FNCSEL_SWO          0x00003800

// Pad 33 drive strength
#define AM_REG_GPIO_PADREGI_PAD33STRNG_S             10
#define AM_REG_GPIO_PADREGI_PAD33STRNG_M             0x00000400
#define AM_REG_GPIO_PADREGI_PAD33STRNG(n)            (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_GPIO_PADREGI_PAD33STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGI_PAD33STRNG_HIGH          0x00000400

// Pad 33 input enable
#define AM_REG_GPIO_PADREGI_PAD33INPEN_S             9
#define AM_REG_GPIO_PADREGI_PAD33INPEN_M             0x00000200
#define AM_REG_GPIO_PADREGI_PAD33INPEN(n)            (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_GPIO_PADREGI_PAD33INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGI_PAD33INPEN_EN            0x00000200

// Pad 33 pullup enable
#define AM_REG_GPIO_PADREGI_PAD33PULL_S              8
#define AM_REG_GPIO_PADREGI_PAD33PULL_M              0x00000100
#define AM_REG_GPIO_PADREGI_PAD33PULL(n)             (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_PADREGI_PAD33PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGI_PAD33PULL_EN             0x00000100

// Pad 32 function select
#define AM_REG_GPIO_PADREGI_PAD32FNCSEL_S            3
#define AM_REG_GPIO_PADREGI_PAD32FNCSEL_M            0x00000038
#define AM_REG_GPIO_PADREGI_PAD32FNCSEL(n)           (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_GPIO_PADREGI_PAD32FNCSEL_ADCSE4       0x00000000
#define AM_REG_GPIO_PADREGI_PAD32FNCSEL_M0nCE5       0x00000008
#define AM_REG_GPIO_PADREGI_PAD32FNCSEL_TCTB3        0x00000010
#define AM_REG_GPIO_PADREGI_PAD32FNCSEL_GPIO32       0x00000018
#define AM_REG_GPIO_PADREGI_PAD32FNCSEL_UNDEF4       0x00000020
#define AM_REG_GPIO_PADREGI_PAD32FNCSEL_TCTB1        0x00000028
#define AM_REG_GPIO_PADREGI_PAD32FNCSEL_UNDEF6       0x00000030
#define AM_REG_GPIO_PADREGI_PAD32FNCSEL_UNDEF7       0x00000038

// Pad 32 drive strength
#define AM_REG_GPIO_PADREGI_PAD32STRNG_S             2
#define AM_REG_GPIO_PADREGI_PAD32STRNG_M             0x00000004
#define AM_REG_GPIO_PADREGI_PAD32STRNG(n)            (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_GPIO_PADREGI_PAD32STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGI_PAD32STRNG_HIGH          0x00000004

// Pad 32 input enable
#define AM_REG_GPIO_PADREGI_PAD32INPEN_S             1
#define AM_REG_GPIO_PADREGI_PAD32INPEN_M             0x00000002
#define AM_REG_GPIO_PADREGI_PAD32INPEN(n)            (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_GPIO_PADREGI_PAD32INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGI_PAD32INPEN_EN            0x00000002

// Pad 32 pullup enable
#define AM_REG_GPIO_PADREGI_PAD32PULL_S              0
#define AM_REG_GPIO_PADREGI_PAD32PULL_M              0x00000001
#define AM_REG_GPIO_PADREGI_PAD32PULL(n)             (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_PADREGI_PAD32PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGI_PAD32PULL_EN             0x00000001

//*****************************************************************************
//
// GPIO_PADREGJ - Pad Configuration Register J
//
//*****************************************************************************
// Pad 39 pullup resistor selection.
#define AM_REG_GPIO_PADREGJ_PAD39RSEL_S              30
#define AM_REG_GPIO_PADREGJ_PAD39RSEL_M              0xC0000000
#define AM_REG_GPIO_PADREGJ_PAD39RSEL(n)             (((uint32_t)(n) << 30) & 0xC0000000)
#define AM_REG_GPIO_PADREGJ_PAD39RSEL_PULL1_5K       0x00000000
#define AM_REG_GPIO_PADREGJ_PAD39RSEL_PULL6K         0x40000000
#define AM_REG_GPIO_PADREGJ_PAD39RSEL_PULL12K        0x80000000
#define AM_REG_GPIO_PADREGJ_PAD39RSEL_PULL24K        0xC0000000

// Pad 39 function select
#define AM_REG_GPIO_PADREGJ_PAD39FNCSEL_S            27
#define AM_REG_GPIO_PADREGJ_PAD39FNCSEL_M            0x38000000
#define AM_REG_GPIO_PADREGJ_PAD39FNCSEL(n)           (((uint32_t)(n) << 27) & 0x38000000)
#define AM_REG_GPIO_PADREGJ_PAD39FNCSEL_UART0TX      0x00000000
#define AM_REG_GPIO_PADREGJ_PAD39FNCSEL_UART1TX      0x08000000
#define AM_REG_GPIO_PADREGJ_PAD39FNCSEL_CLKOUT       0x10000000
#define AM_REG_GPIO_PADREGJ_PAD39FNCSEL_GPIO39       0x18000000
#define AM_REG_GPIO_PADREGJ_PAD39FNCSEL_M4SCL        0x20000000
#define AM_REG_GPIO_PADREGJ_PAD39FNCSEL_M4SCK        0x28000000
#define AM_REG_GPIO_PADREGJ_PAD39FNCSEL_M4SCKLB      0x30000000
#define AM_REG_GPIO_PADREGJ_PAD39FNCSEL_M4SCLLB      0x38000000

// Pad 39 drive strength
#define AM_REG_GPIO_PADREGJ_PAD39STRNG_S             26
#define AM_REG_GPIO_PADREGJ_PAD39STRNG_M             0x04000000
#define AM_REG_GPIO_PADREGJ_PAD39STRNG(n)            (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_GPIO_PADREGJ_PAD39STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGJ_PAD39STRNG_HIGH          0x04000000

// Pad 39 input enable
#define AM_REG_GPIO_PADREGJ_PAD39INPEN_S             25
#define AM_REG_GPIO_PADREGJ_PAD39INPEN_M             0x02000000
#define AM_REG_GPIO_PADREGJ_PAD39INPEN(n)            (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_GPIO_PADREGJ_PAD39INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGJ_PAD39INPEN_EN            0x02000000

// Pad 39 pullup enable
#define AM_REG_GPIO_PADREGJ_PAD39PULL_S              24
#define AM_REG_GPIO_PADREGJ_PAD39PULL_M              0x01000000
#define AM_REG_GPIO_PADREGJ_PAD39PULL(n)             (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_PADREGJ_PAD39PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGJ_PAD39PULL_EN             0x01000000

// Pad 38 function select
#define AM_REG_GPIO_PADREGJ_PAD38FNCSEL_S            19
#define AM_REG_GPIO_PADREGJ_PAD38FNCSEL_M            0x00380000
#define AM_REG_GPIO_PADREGJ_PAD38FNCSEL(n)           (((uint32_t)(n) << 19) & 0x00380000)
#define AM_REG_GPIO_PADREGJ_PAD38FNCSEL_TRIG3        0x00000000
#define AM_REG_GPIO_PADREGJ_PAD38FNCSEL_M1nCE3       0x00080000
#define AM_REG_GPIO_PADREGJ_PAD38FNCSEL_UA0CTS       0x00100000
#define AM_REG_GPIO_PADREGJ_PAD38FNCSEL_GPIO38       0x00180000
#define AM_REG_GPIO_PADREGJ_PAD38FNCSEL_M3WIR3       0x00200000
#define AM_REG_GPIO_PADREGJ_PAD38FNCSEL_M3MOSI       0x00280000
#define AM_REG_GPIO_PADREGJ_PAD38FNCSEL_M4nCE7       0x00300000
#define AM_REG_GPIO_PADREGJ_PAD38FNCSEL_SLWIR3LB     0x00380000

// Pad 38 drive strength
#define AM_REG_GPIO_PADREGJ_PAD38STRNG_S             18
#define AM_REG_GPIO_PADREGJ_PAD38STRNG_M             0x00040000
#define AM_REG_GPIO_PADREGJ_PAD38STRNG(n)            (((uint32_t)(n) << 18) & 0x00040000)
#define AM_REG_GPIO_PADREGJ_PAD38STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGJ_PAD38STRNG_HIGH          0x00040000

// Pad 38 input enable
#define AM_REG_GPIO_PADREGJ_PAD38INPEN_S             17
#define AM_REG_GPIO_PADREGJ_PAD38INPEN_M             0x00020000
#define AM_REG_GPIO_PADREGJ_PAD38INPEN(n)            (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_GPIO_PADREGJ_PAD38INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGJ_PAD38INPEN_EN            0x00020000

// Pad 38 pullup enable
#define AM_REG_GPIO_PADREGJ_PAD38PULL_S              16
#define AM_REG_GPIO_PADREGJ_PAD38PULL_M              0x00010000
#define AM_REG_GPIO_PADREGJ_PAD38PULL(n)             (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_PADREGJ_PAD38PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGJ_PAD38PULL_EN             0x00010000

// Pad 37 function select
#define AM_REG_GPIO_PADREGJ_PAD37FNCSEL_S            11
#define AM_REG_GPIO_PADREGJ_PAD37FNCSEL_M            0x00003800
#define AM_REG_GPIO_PADREGJ_PAD37FNCSEL(n)           (((uint32_t)(n) << 11) & 0x00003800)
#define AM_REG_GPIO_PADREGJ_PAD37FNCSEL_TRIG2        0x00000000
#define AM_REG_GPIO_PADREGJ_PAD37FNCSEL_M1nCE2       0x00000800
#define AM_REG_GPIO_PADREGJ_PAD37FNCSEL_UA0RTS       0x00001000
#define AM_REG_GPIO_PADREGJ_PAD37FNCSEL_GPIO37       0x00001800
#define AM_REG_GPIO_PADREGJ_PAD37FNCSEL_M3nCE4       0x00002000
#define AM_REG_GPIO_PADREGJ_PAD37FNCSEL_M4nCE1       0x00002800
#define AM_REG_GPIO_PADREGJ_PAD37FNCSEL_PDM_CLK      0x00003000
#define AM_REG_GPIO_PADREGJ_PAD37FNCSEL_TCTA1        0x00003800

// Pad 37 drive strength
#define AM_REG_GPIO_PADREGJ_PAD37STRNG_S             10
#define AM_REG_GPIO_PADREGJ_PAD37STRNG_M             0x00000400
#define AM_REG_GPIO_PADREGJ_PAD37STRNG(n)            (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_GPIO_PADREGJ_PAD37STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGJ_PAD37STRNG_HIGH          0x00000400

// Pad 37 input enable
#define AM_REG_GPIO_PADREGJ_PAD37INPEN_S             9
#define AM_REG_GPIO_PADREGJ_PAD37INPEN_M             0x00000200
#define AM_REG_GPIO_PADREGJ_PAD37INPEN(n)            (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_GPIO_PADREGJ_PAD37INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGJ_PAD37INPEN_EN            0x00000200

// Pad 37 pullup enable
#define AM_REG_GPIO_PADREGJ_PAD37PULL_S              8
#define AM_REG_GPIO_PADREGJ_PAD37PULL_M              0x00000100
#define AM_REG_GPIO_PADREGJ_PAD37PULL(n)             (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_PADREGJ_PAD37PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGJ_PAD37PULL_EN             0x00000100

// Pad 36 function select
#define AM_REG_GPIO_PADREGJ_PAD36FNCSEL_S            3
#define AM_REG_GPIO_PADREGJ_PAD36FNCSEL_M            0x00000038
#define AM_REG_GPIO_PADREGJ_PAD36FNCSEL(n)           (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_GPIO_PADREGJ_PAD36FNCSEL_TRIG1        0x00000000
#define AM_REG_GPIO_PADREGJ_PAD36FNCSEL_M1nCE1       0x00000008
#define AM_REG_GPIO_PADREGJ_PAD36FNCSEL_UART1RX      0x00000010
#define AM_REG_GPIO_PADREGJ_PAD36FNCSEL_GPIO36       0x00000018
#define AM_REG_GPIO_PADREGJ_PAD36FNCSEL_32khz_XT     0x00000020
#define AM_REG_GPIO_PADREGJ_PAD36FNCSEL_M2nCE0       0x00000028
#define AM_REG_GPIO_PADREGJ_PAD36FNCSEL_UA0CTS       0x00000030
#define AM_REG_GPIO_PADREGJ_PAD36FNCSEL_M3nCE3       0x00000038

// Pad 36 drive strength
#define AM_REG_GPIO_PADREGJ_PAD36STRNG_S             2
#define AM_REG_GPIO_PADREGJ_PAD36STRNG_M             0x00000004
#define AM_REG_GPIO_PADREGJ_PAD36STRNG(n)            (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_GPIO_PADREGJ_PAD36STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGJ_PAD36STRNG_HIGH          0x00000004

// Pad 36 input enable
#define AM_REG_GPIO_PADREGJ_PAD36INPEN_S             1
#define AM_REG_GPIO_PADREGJ_PAD36INPEN_M             0x00000002
#define AM_REG_GPIO_PADREGJ_PAD36INPEN(n)            (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_GPIO_PADREGJ_PAD36INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGJ_PAD36INPEN_EN            0x00000002

// Pad 36 pullup enable
#define AM_REG_GPIO_PADREGJ_PAD36PULL_S              0
#define AM_REG_GPIO_PADREGJ_PAD36PULL_M              0x00000001
#define AM_REG_GPIO_PADREGJ_PAD36PULL(n)             (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_PADREGJ_PAD36PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGJ_PAD36PULL_EN             0x00000001

//*****************************************************************************
//
// GPIO_PADREGK - Pad Configuration Register K
//
//*****************************************************************************
// Pad 43 pullup resistor selection.
#define AM_REG_GPIO_PADREGK_PAD43RSEL_S              30
#define AM_REG_GPIO_PADREGK_PAD43RSEL_M              0xC0000000
#define AM_REG_GPIO_PADREGK_PAD43RSEL(n)             (((uint32_t)(n) << 30) & 0xC0000000)
#define AM_REG_GPIO_PADREGK_PAD43RSEL_PULL1_5K       0x00000000
#define AM_REG_GPIO_PADREGK_PAD43RSEL_PULL6K         0x40000000
#define AM_REG_GPIO_PADREGK_PAD43RSEL_PULL12K        0x80000000
#define AM_REG_GPIO_PADREGK_PAD43RSEL_PULL24K        0xC0000000

// Pad 43 function select
#define AM_REG_GPIO_PADREGK_PAD43FNCSEL_S            27
#define AM_REG_GPIO_PADREGK_PAD43FNCSEL_M            0x38000000
#define AM_REG_GPIO_PADREGK_PAD43FNCSEL(n)           (((uint32_t)(n) << 27) & 0x38000000)
#define AM_REG_GPIO_PADREGK_PAD43FNCSEL_M2nCE4       0x00000000
#define AM_REG_GPIO_PADREGK_PAD43FNCSEL_M0nCE1       0x08000000
#define AM_REG_GPIO_PADREGK_PAD43FNCSEL_TCTB0        0x10000000
#define AM_REG_GPIO_PADREGK_PAD43FNCSEL_GPIO43       0x18000000
#define AM_REG_GPIO_PADREGK_PAD43FNCSEL_M3SDA        0x20000000
#define AM_REG_GPIO_PADREGK_PAD43FNCSEL_M3MISO       0x28000000
#define AM_REG_GPIO_PADREGK_PAD43FNCSEL_SLMISOLB     0x30000000
#define AM_REG_GPIO_PADREGK_PAD43FNCSEL_SLSDALB      0x38000000

// Pad 43 drive strength
#define AM_REG_GPIO_PADREGK_PAD43STRNG_S             26
#define AM_REG_GPIO_PADREGK_PAD43STRNG_M             0x04000000
#define AM_REG_GPIO_PADREGK_PAD43STRNG(n)            (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_GPIO_PADREGK_PAD43STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGK_PAD43STRNG_HIGH          0x04000000

// Pad 43 input enable
#define AM_REG_GPIO_PADREGK_PAD43INPEN_S             25
#define AM_REG_GPIO_PADREGK_PAD43INPEN_M             0x02000000
#define AM_REG_GPIO_PADREGK_PAD43INPEN(n)            (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_GPIO_PADREGK_PAD43INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGK_PAD43INPEN_EN            0x02000000

// Pad 43 pullup enable
#define AM_REG_GPIO_PADREGK_PAD43PULL_S              24
#define AM_REG_GPIO_PADREGK_PAD43PULL_M              0x01000000
#define AM_REG_GPIO_PADREGK_PAD43PULL(n)             (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_PADREGK_PAD43PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGK_PAD43PULL_EN             0x01000000

// Pad 42 pullup resistor selection.
#define AM_REG_GPIO_PADREGK_PAD42RSEL_S              22
#define AM_REG_GPIO_PADREGK_PAD42RSEL_M              0x00C00000
#define AM_REG_GPIO_PADREGK_PAD42RSEL(n)             (((uint32_t)(n) << 22) & 0x00C00000)
#define AM_REG_GPIO_PADREGK_PAD42RSEL_PULL1_5K       0x00000000
#define AM_REG_GPIO_PADREGK_PAD42RSEL_PULL6K         0x00400000
#define AM_REG_GPIO_PADREGK_PAD42RSEL_PULL12K        0x00800000
#define AM_REG_GPIO_PADREGK_PAD42RSEL_PULL24K        0x00C00000

// Pad 42 function select
#define AM_REG_GPIO_PADREGK_PAD42FNCSEL_S            19
#define AM_REG_GPIO_PADREGK_PAD42FNCSEL_M            0x00380000
#define AM_REG_GPIO_PADREGK_PAD42FNCSEL(n)           (((uint32_t)(n) << 19) & 0x00380000)
#define AM_REG_GPIO_PADREGK_PAD42FNCSEL_M2nCE2       0x00000000
#define AM_REG_GPIO_PADREGK_PAD42FNCSEL_M0nCE0       0x00080000
#define AM_REG_GPIO_PADREGK_PAD42FNCSEL_TCTA0        0x00100000
#define AM_REG_GPIO_PADREGK_PAD42FNCSEL_GPIO42       0x00180000
#define AM_REG_GPIO_PADREGK_PAD42FNCSEL_M3SCL        0x00200000
#define AM_REG_GPIO_PADREGK_PAD42FNCSEL_M3SCK        0x00280000
#define AM_REG_GPIO_PADREGK_PAD42FNCSEL_M3SCKLB      0x00300000
#define AM_REG_GPIO_PADREGK_PAD42FNCSEL_M3SCLLB      0x00380000

// Pad 42 drive strength
#define AM_REG_GPIO_PADREGK_PAD42STRNG_S             18
#define AM_REG_GPIO_PADREGK_PAD42STRNG_M             0x00040000
#define AM_REG_GPIO_PADREGK_PAD42STRNG(n)            (((uint32_t)(n) << 18) & 0x00040000)
#define AM_REG_GPIO_PADREGK_PAD42STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGK_PAD42STRNG_HIGH          0x00040000

// Pad 42 input enable
#define AM_REG_GPIO_PADREGK_PAD42INPEN_S             17
#define AM_REG_GPIO_PADREGK_PAD42INPEN_M             0x00020000
#define AM_REG_GPIO_PADREGK_PAD42INPEN(n)            (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_GPIO_PADREGK_PAD42INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGK_PAD42INPEN_EN            0x00020000

// Pad 42 pullup enable
#define AM_REG_GPIO_PADREGK_PAD42PULL_S              16
#define AM_REG_GPIO_PADREGK_PAD42PULL_M              0x00010000
#define AM_REG_GPIO_PADREGK_PAD42PULL(n)             (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_PADREGK_PAD42PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGK_PAD42PULL_EN             0x00010000

// Pad 41 upper power switch enable
#define AM_REG_GPIO_PADREGK_PAD41PWRUP_S             15
#define AM_REG_GPIO_PADREGK_PAD41PWRUP_M             0x00008000
#define AM_REG_GPIO_PADREGK_PAD41PWRUP(n)            (((uint32_t)(n) << 15) & 0x00008000)
#define AM_REG_GPIO_PADREGK_PAD41PWRUP_DIS           0x00000000
#define AM_REG_GPIO_PADREGK_PAD41PWRUP_EN            0x00008000

// Pad 41 function select
#define AM_REG_GPIO_PADREGK_PAD41FNCSEL_S            11
#define AM_REG_GPIO_PADREGK_PAD41FNCSEL_M            0x00003800
#define AM_REG_GPIO_PADREGK_PAD41FNCSEL(n)           (((uint32_t)(n) << 11) & 0x00003800)
#define AM_REG_GPIO_PADREGK_PAD41FNCSEL_M2nCE1       0x00000000
#define AM_REG_GPIO_PADREGK_PAD41FNCSEL_CLKOUT       0x00000800
#define AM_REG_GPIO_PADREGK_PAD41FNCSEL_SWO          0x00001000
#define AM_REG_GPIO_PADREGK_PAD41FNCSEL_GPIO41       0x00001800
#define AM_REG_GPIO_PADREGK_PAD41FNCSEL_M3nCE5       0x00002000
#define AM_REG_GPIO_PADREGK_PAD41FNCSEL_M5nCE7       0x00002800
#define AM_REG_GPIO_PADREGK_PAD41FNCSEL_M4nCE2       0x00003000
#define AM_REG_GPIO_PADREGK_PAD41FNCSEL_UA0RTS       0x00003800

// Pad 41 drive strength
#define AM_REG_GPIO_PADREGK_PAD41STRNG_S             10
#define AM_REG_GPIO_PADREGK_PAD41STRNG_M             0x00000400
#define AM_REG_GPIO_PADREGK_PAD41STRNG(n)            (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_GPIO_PADREGK_PAD41STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGK_PAD41STRNG_HIGH          0x00000400

// Pad 41 input enable
#define AM_REG_GPIO_PADREGK_PAD41INPEN_S             9
#define AM_REG_GPIO_PADREGK_PAD41INPEN_M             0x00000200
#define AM_REG_GPIO_PADREGK_PAD41INPEN(n)            (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_GPIO_PADREGK_PAD41INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGK_PAD41INPEN_EN            0x00000200

// Pad 41 pullup enable
#define AM_REG_GPIO_PADREGK_PAD41PULL_S              8
#define AM_REG_GPIO_PADREGK_PAD41PULL_M              0x00000100
#define AM_REG_GPIO_PADREGK_PAD41PULL(n)             (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_PADREGK_PAD41PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGK_PAD41PULL_EN             0x00000100

// Pad 40 pullup resistor selection.
#define AM_REG_GPIO_PADREGK_PAD40RSEL_S              6
#define AM_REG_GPIO_PADREGK_PAD40RSEL_M              0x000000C0
#define AM_REG_GPIO_PADREGK_PAD40RSEL(n)             (((uint32_t)(n) << 6) & 0x000000C0)
#define AM_REG_GPIO_PADREGK_PAD40RSEL_PULL1_5K       0x00000000
#define AM_REG_GPIO_PADREGK_PAD40RSEL_PULL6K         0x00000040
#define AM_REG_GPIO_PADREGK_PAD40RSEL_PULL12K        0x00000080
#define AM_REG_GPIO_PADREGK_PAD40RSEL_PULL24K        0x000000C0

// Pad 40 function select
#define AM_REG_GPIO_PADREGK_PAD40FNCSEL_S            3
#define AM_REG_GPIO_PADREGK_PAD40FNCSEL_M            0x00000038
#define AM_REG_GPIO_PADREGK_PAD40FNCSEL(n)           (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_GPIO_PADREGK_PAD40FNCSEL_UART0RX      0x00000000
#define AM_REG_GPIO_PADREGK_PAD40FNCSEL_UART1RX      0x00000008
#define AM_REG_GPIO_PADREGK_PAD40FNCSEL_TRIG0        0x00000010
#define AM_REG_GPIO_PADREGK_PAD40FNCSEL_GPIO40       0x00000018
#define AM_REG_GPIO_PADREGK_PAD40FNCSEL_M4SDA        0x00000020
#define AM_REG_GPIO_PADREGK_PAD40FNCSEL_M4MISO       0x00000028
#define AM_REG_GPIO_PADREGK_PAD40FNCSEL_SLMISOLB     0x00000030
#define AM_REG_GPIO_PADREGK_PAD40FNCSEL_SLSDALB      0x00000038

// Pad 40 drive strength
#define AM_REG_GPIO_PADREGK_PAD40STRNG_S             2
#define AM_REG_GPIO_PADREGK_PAD40STRNG_M             0x00000004
#define AM_REG_GPIO_PADREGK_PAD40STRNG(n)            (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_GPIO_PADREGK_PAD40STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGK_PAD40STRNG_HIGH          0x00000004

// Pad 40 input enable
#define AM_REG_GPIO_PADREGK_PAD40INPEN_S             1
#define AM_REG_GPIO_PADREGK_PAD40INPEN_M             0x00000002
#define AM_REG_GPIO_PADREGK_PAD40INPEN(n)            (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_GPIO_PADREGK_PAD40INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGK_PAD40INPEN_EN            0x00000002

// Pad 40 pullup enable
#define AM_REG_GPIO_PADREGK_PAD40PULL_S              0
#define AM_REG_GPIO_PADREGK_PAD40PULL_M              0x00000001
#define AM_REG_GPIO_PADREGK_PAD40PULL(n)             (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_PADREGK_PAD40PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGK_PAD40PULL_EN             0x00000001

//*****************************************************************************
//
// GPIO_PADREGL - Pad Configuration Register L
//
//*****************************************************************************
// Pad 47 function select
#define AM_REG_GPIO_PADREGL_PAD47FNCSEL_S            27
#define AM_REG_GPIO_PADREGL_PAD47FNCSEL_M            0x38000000
#define AM_REG_GPIO_PADREGL_PAD47FNCSEL(n)           (((uint32_t)(n) << 27) & 0x38000000)
#define AM_REG_GPIO_PADREGL_PAD47FNCSEL_M2nCE5       0x00000000
#define AM_REG_GPIO_PADREGL_PAD47FNCSEL_M0nCE5       0x08000000
#define AM_REG_GPIO_PADREGL_PAD47FNCSEL_TCTB2        0x10000000
#define AM_REG_GPIO_PADREGL_PAD47FNCSEL_GPIO47       0x18000000
#define AM_REG_GPIO_PADREGL_PAD47FNCSEL_M5WIR3       0x20000000
#define AM_REG_GPIO_PADREGL_PAD47FNCSEL_M5MOSI       0x28000000
#define AM_REG_GPIO_PADREGL_PAD47FNCSEL_M4nCE5       0x30000000
#define AM_REG_GPIO_PADREGL_PAD47FNCSEL_SLWIR3LB     0x38000000

// Pad 47 drive strength
#define AM_REG_GPIO_PADREGL_PAD47STRNG_S             26
#define AM_REG_GPIO_PADREGL_PAD47STRNG_M             0x04000000
#define AM_REG_GPIO_PADREGL_PAD47STRNG(n)            (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_GPIO_PADREGL_PAD47STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGL_PAD47STRNG_HIGH          0x04000000

// Pad 47 input enable
#define AM_REG_GPIO_PADREGL_PAD47INPEN_S             25
#define AM_REG_GPIO_PADREGL_PAD47INPEN_M             0x02000000
#define AM_REG_GPIO_PADREGL_PAD47INPEN(n)            (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_GPIO_PADREGL_PAD47INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGL_PAD47INPEN_EN            0x02000000

// Pad 47 pullup enable
#define AM_REG_GPIO_PADREGL_PAD47PULL_S              24
#define AM_REG_GPIO_PADREGL_PAD47PULL_M              0x01000000
#define AM_REG_GPIO_PADREGL_PAD47PULL(n)             (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_PADREGL_PAD47PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGL_PAD47PULL_EN             0x01000000

// Pad 46 function select
#define AM_REG_GPIO_PADREGL_PAD46FNCSEL_S            19
#define AM_REG_GPIO_PADREGL_PAD46FNCSEL_M            0x00380000
#define AM_REG_GPIO_PADREGL_PAD46FNCSEL(n)           (((uint32_t)(n) << 19) & 0x00380000)
#define AM_REG_GPIO_PADREGL_PAD46FNCSEL_32khz_XT     0x00000000
#define AM_REG_GPIO_PADREGL_PAD46FNCSEL_M0nCE4       0x00080000
#define AM_REG_GPIO_PADREGL_PAD46FNCSEL_TCTA2        0x00100000
#define AM_REG_GPIO_PADREGL_PAD46FNCSEL_GPIO46       0x00180000
#define AM_REG_GPIO_PADREGL_PAD46FNCSEL_TCTA1        0x00200000
#define AM_REG_GPIO_PADREGL_PAD46FNCSEL_M5nCE4       0x00280000
#define AM_REG_GPIO_PADREGL_PAD46FNCSEL_M4nCE4       0x00300000
#define AM_REG_GPIO_PADREGL_PAD46FNCSEL_SWO          0x00380000

// Pad 46 drive strength
#define AM_REG_GPIO_PADREGL_PAD46STRNG_S             18
#define AM_REG_GPIO_PADREGL_PAD46STRNG_M             0x00040000
#define AM_REG_GPIO_PADREGL_PAD46STRNG(n)            (((uint32_t)(n) << 18) & 0x00040000)
#define AM_REG_GPIO_PADREGL_PAD46STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGL_PAD46STRNG_HIGH          0x00040000

// Pad 46 input enable
#define AM_REG_GPIO_PADREGL_PAD46INPEN_S             17
#define AM_REG_GPIO_PADREGL_PAD46INPEN_M             0x00020000
#define AM_REG_GPIO_PADREGL_PAD46INPEN(n)            (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_GPIO_PADREGL_PAD46INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGL_PAD46INPEN_EN            0x00020000

// Pad 46 pullup enable
#define AM_REG_GPIO_PADREGL_PAD46PULL_S              16
#define AM_REG_GPIO_PADREGL_PAD46PULL_M              0x00010000
#define AM_REG_GPIO_PADREGL_PAD46PULL(n)             (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_PADREGL_PAD46PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGL_PAD46PULL_EN             0x00010000

// Pad 45 function select
#define AM_REG_GPIO_PADREGL_PAD45FNCSEL_S            11
#define AM_REG_GPIO_PADREGL_PAD45FNCSEL_M            0x00003800
#define AM_REG_GPIO_PADREGL_PAD45FNCSEL(n)           (((uint32_t)(n) << 11) & 0x00003800)
#define AM_REG_GPIO_PADREGL_PAD45FNCSEL_UA1CTS       0x00000000
#define AM_REG_GPIO_PADREGL_PAD45FNCSEL_M0nCE3       0x00000800
#define AM_REG_GPIO_PADREGL_PAD45FNCSEL_TCTB1        0x00001000
#define AM_REG_GPIO_PADREGL_PAD45FNCSEL_GPIO45       0x00001800
#define AM_REG_GPIO_PADREGL_PAD45FNCSEL_M4nCE3       0x00002000
#define AM_REG_GPIO_PADREGL_PAD45FNCSEL_M3nCE6       0x00002800
#define AM_REG_GPIO_PADREGL_PAD45FNCSEL_M5nCE5       0x00003000
#define AM_REG_GPIO_PADREGL_PAD45FNCSEL_TCTA1        0x00003800

// Pad 45 drive strength
#define AM_REG_GPIO_PADREGL_PAD45STRNG_S             10
#define AM_REG_GPIO_PADREGL_PAD45STRNG_M             0x00000400
#define AM_REG_GPIO_PADREGL_PAD45STRNG(n)            (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_GPIO_PADREGL_PAD45STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGL_PAD45STRNG_HIGH          0x00000400

// Pad 45 input enable
#define AM_REG_GPIO_PADREGL_PAD45INPEN_S             9
#define AM_REG_GPIO_PADREGL_PAD45INPEN_M             0x00000200
#define AM_REG_GPIO_PADREGL_PAD45INPEN(n)            (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_GPIO_PADREGL_PAD45INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGL_PAD45INPEN_EN            0x00000200

// Pad 45 pullup enable
#define AM_REG_GPIO_PADREGL_PAD45PULL_S              8
#define AM_REG_GPIO_PADREGL_PAD45PULL_M              0x00000100
#define AM_REG_GPIO_PADREGL_PAD45PULL(n)             (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_PADREGL_PAD45PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGL_PAD45PULL_EN             0x00000100

// Pad 44 function select
#define AM_REG_GPIO_PADREGL_PAD44FNCSEL_S            3
#define AM_REG_GPIO_PADREGL_PAD44FNCSEL_M            0x00000038
#define AM_REG_GPIO_PADREGL_PAD44FNCSEL(n)           (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_GPIO_PADREGL_PAD44FNCSEL_UA1RTS       0x00000000
#define AM_REG_GPIO_PADREGL_PAD44FNCSEL_M0nCE2       0x00000008
#define AM_REG_GPIO_PADREGL_PAD44FNCSEL_TCTA1        0x00000010
#define AM_REG_GPIO_PADREGL_PAD44FNCSEL_GPIO44       0x00000018
#define AM_REG_GPIO_PADREGL_PAD44FNCSEL_M4WIR3       0x00000020
#define AM_REG_GPIO_PADREGL_PAD44FNCSEL_M4MOSI       0x00000028
#define AM_REG_GPIO_PADREGL_PAD44FNCSEL_M5nCE6       0x00000030
#define AM_REG_GPIO_PADREGL_PAD44FNCSEL_SLWIR3LB     0x00000038

// Pad 44 drive strength
#define AM_REG_GPIO_PADREGL_PAD44STRNG_S             2
#define AM_REG_GPIO_PADREGL_PAD44STRNG_M             0x00000004
#define AM_REG_GPIO_PADREGL_PAD44STRNG(n)            (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_GPIO_PADREGL_PAD44STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGL_PAD44STRNG_HIGH          0x00000004

// Pad 44 input enable
#define AM_REG_GPIO_PADREGL_PAD44INPEN_S             1
#define AM_REG_GPIO_PADREGL_PAD44INPEN_M             0x00000002
#define AM_REG_GPIO_PADREGL_PAD44INPEN(n)            (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_GPIO_PADREGL_PAD44INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGL_PAD44INPEN_EN            0x00000002

// Pad 44 pullup enable
#define AM_REG_GPIO_PADREGL_PAD44PULL_S              0
#define AM_REG_GPIO_PADREGL_PAD44PULL_M              0x00000001
#define AM_REG_GPIO_PADREGL_PAD44PULL(n)             (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_PADREGL_PAD44PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGL_PAD44PULL_EN             0x00000001

//*****************************************************************************
//
// GPIO_PADREGM - Pad Configuration Register M
//
//*****************************************************************************
// Pad 49 pullup resistor selection.
#define AM_REG_GPIO_PADREGM_PAD49RSEL_S              14
#define AM_REG_GPIO_PADREGM_PAD49RSEL_M              0x0000C000
#define AM_REG_GPIO_PADREGM_PAD49RSEL(n)             (((uint32_t)(n) << 14) & 0x0000C000)
#define AM_REG_GPIO_PADREGM_PAD49RSEL_PULL1_5K       0x00000000
#define AM_REG_GPIO_PADREGM_PAD49RSEL_PULL6K         0x00004000
#define AM_REG_GPIO_PADREGM_PAD49RSEL_PULL12K        0x00008000
#define AM_REG_GPIO_PADREGM_PAD49RSEL_PULL24K        0x0000C000

// Pad 49 function select
#define AM_REG_GPIO_PADREGM_PAD49FNCSEL_S            11
#define AM_REG_GPIO_PADREGM_PAD49FNCSEL_M            0x00003800
#define AM_REG_GPIO_PADREGM_PAD49FNCSEL(n)           (((uint32_t)(n) << 11) & 0x00003800)
#define AM_REG_GPIO_PADREGM_PAD49FNCSEL_M2nCE7       0x00000000
#define AM_REG_GPIO_PADREGM_PAD49FNCSEL_M0nCE7       0x00000800
#define AM_REG_GPIO_PADREGM_PAD49FNCSEL_TCTB3        0x00001000
#define AM_REG_GPIO_PADREGM_PAD49FNCSEL_GPIO49       0x00001800
#define AM_REG_GPIO_PADREGM_PAD49FNCSEL_M5SDA        0x00002000
#define AM_REG_GPIO_PADREGM_PAD49FNCSEL_M5MISO       0x00002800
#define AM_REG_GPIO_PADREGM_PAD49FNCSEL_SLMISOLB     0x00003000
#define AM_REG_GPIO_PADREGM_PAD49FNCSEL_SLSDALB      0x00003800

// Pad 49 drive strength
#define AM_REG_GPIO_PADREGM_PAD49STRNG_S             10
#define AM_REG_GPIO_PADREGM_PAD49STRNG_M             0x00000400
#define AM_REG_GPIO_PADREGM_PAD49STRNG(n)            (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_GPIO_PADREGM_PAD49STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGM_PAD49STRNG_HIGH          0x00000400

// Pad 49 input enable
#define AM_REG_GPIO_PADREGM_PAD49INPEN_S             9
#define AM_REG_GPIO_PADREGM_PAD49INPEN_M             0x00000200
#define AM_REG_GPIO_PADREGM_PAD49INPEN(n)            (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_GPIO_PADREGM_PAD49INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGM_PAD49INPEN_EN            0x00000200

// Pad 49 pullup enable
#define AM_REG_GPIO_PADREGM_PAD49PULL_S              8
#define AM_REG_GPIO_PADREGM_PAD49PULL_M              0x00000100
#define AM_REG_GPIO_PADREGM_PAD49PULL(n)             (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_PADREGM_PAD49PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGM_PAD49PULL_EN             0x00000100

// Pad 48 pullup resistor selection.
#define AM_REG_GPIO_PADREGM_PAD48RSEL_S              6
#define AM_REG_GPIO_PADREGM_PAD48RSEL_M              0x000000C0
#define AM_REG_GPIO_PADREGM_PAD48RSEL(n)             (((uint32_t)(n) << 6) & 0x000000C0)
#define AM_REG_GPIO_PADREGM_PAD48RSEL_PULL1_5K       0x00000000
#define AM_REG_GPIO_PADREGM_PAD48RSEL_PULL6K         0x00000040
#define AM_REG_GPIO_PADREGM_PAD48RSEL_PULL12K        0x00000080
#define AM_REG_GPIO_PADREGM_PAD48RSEL_PULL24K        0x000000C0

// Pad 48 function select
#define AM_REG_GPIO_PADREGM_PAD48FNCSEL_S            3
#define AM_REG_GPIO_PADREGM_PAD48FNCSEL_M            0x00000038
#define AM_REG_GPIO_PADREGM_PAD48FNCSEL(n)           (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_GPIO_PADREGM_PAD48FNCSEL_M2nCE6       0x00000000
#define AM_REG_GPIO_PADREGM_PAD48FNCSEL_M0nCE6       0x00000008
#define AM_REG_GPIO_PADREGM_PAD48FNCSEL_TCTA3        0x00000010
#define AM_REG_GPIO_PADREGM_PAD48FNCSEL_GPIO48       0x00000018
#define AM_REG_GPIO_PADREGM_PAD48FNCSEL_M5SCL        0x00000020
#define AM_REG_GPIO_PADREGM_PAD48FNCSEL_M5SCK        0x00000028
#define AM_REG_GPIO_PADREGM_PAD48FNCSEL_M5SCKLB      0x00000030
#define AM_REG_GPIO_PADREGM_PAD48FNCSEL_M5SCLLB      0x00000038

// Pad 48 drive strength
#define AM_REG_GPIO_PADREGM_PAD48STRNG_S             2
#define AM_REG_GPIO_PADREGM_PAD48STRNG_M             0x00000004
#define AM_REG_GPIO_PADREGM_PAD48STRNG(n)            (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_GPIO_PADREGM_PAD48STRNG_LOW           0x00000000
#define AM_REG_GPIO_PADREGM_PAD48STRNG_HIGH          0x00000004

// Pad 48 input enable
#define AM_REG_GPIO_PADREGM_PAD48INPEN_S             1
#define AM_REG_GPIO_PADREGM_PAD48INPEN_M             0x00000002
#define AM_REG_GPIO_PADREGM_PAD48INPEN(n)            (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_GPIO_PADREGM_PAD48INPEN_DIS           0x00000000
#define AM_REG_GPIO_PADREGM_PAD48INPEN_EN            0x00000002

// Pad 48 pullup enable
#define AM_REG_GPIO_PADREGM_PAD48PULL_S              0
#define AM_REG_GPIO_PADREGM_PAD48PULL_M              0x00000001
#define AM_REG_GPIO_PADREGM_PAD48PULL(n)             (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_PADREGM_PAD48PULL_DIS            0x00000000
#define AM_REG_GPIO_PADREGM_PAD48PULL_EN             0x00000001

//*****************************************************************************
//
// GPIO_CFGA - GPIO Configuration Register A
//
//*****************************************************************************
// GPIO7 interrupt direction.
#define AM_REG_GPIO_CFGA_GPIO7INTD_S                 31
#define AM_REG_GPIO_CFGA_GPIO7INTD_M                 0x80000000
#define AM_REG_GPIO_CFGA_GPIO7INTD(n)                (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_GPIO_CFGA_GPIO7INTD_INTLH             0x00000000
#define AM_REG_GPIO_CFGA_GPIO7INTD_INTHL             0x80000000

// GPIO7 output configuration.
#define AM_REG_GPIO_CFGA_GPIO7OUTCFG_S               29
#define AM_REG_GPIO_CFGA_GPIO7OUTCFG_M               0x60000000
#define AM_REG_GPIO_CFGA_GPIO7OUTCFG(n)              (((uint32_t)(n) << 29) & 0x60000000)
#define AM_REG_GPIO_CFGA_GPIO7OUTCFG_DIS             0x00000000
#define AM_REG_GPIO_CFGA_GPIO7OUTCFG_PUSHPULL        0x20000000
#define AM_REG_GPIO_CFGA_GPIO7OUTCFG_OD              0x40000000
#define AM_REG_GPIO_CFGA_GPIO7OUTCFG_TS              0x60000000

// GPIO7 input enable.
#define AM_REG_GPIO_CFGA_GPIO7INCFG_S                28
#define AM_REG_GPIO_CFGA_GPIO7INCFG_M                0x10000000
#define AM_REG_GPIO_CFGA_GPIO7INCFG(n)               (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_CFGA_GPIO7INCFG_READ             0x00000000
#define AM_REG_GPIO_CFGA_GPIO7INCFG_RDZERO           0x10000000

// GPIO6 interrupt direction.
#define AM_REG_GPIO_CFGA_GPIO6INTD_S                 27
#define AM_REG_GPIO_CFGA_GPIO6INTD_M                 0x08000000
#define AM_REG_GPIO_CFGA_GPIO6INTD(n)                (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_GPIO_CFGA_GPIO6INTD_INTLH             0x00000000
#define AM_REG_GPIO_CFGA_GPIO6INTD_INTHL             0x08000000

// GPIO6 output configuration.
#define AM_REG_GPIO_CFGA_GPIO6OUTCFG_S               25
#define AM_REG_GPIO_CFGA_GPIO6OUTCFG_M               0x06000000
#define AM_REG_GPIO_CFGA_GPIO6OUTCFG(n)              (((uint32_t)(n) << 25) & 0x06000000)
#define AM_REG_GPIO_CFGA_GPIO6OUTCFG_DIS             0x00000000
#define AM_REG_GPIO_CFGA_GPIO6OUTCFG_PUSHPULL        0x02000000
#define AM_REG_GPIO_CFGA_GPIO6OUTCFG_OD              0x04000000
#define AM_REG_GPIO_CFGA_GPIO6OUTCFG_TS              0x06000000

// GPIO6 input enable.
#define AM_REG_GPIO_CFGA_GPIO6INCFG_S                24
#define AM_REG_GPIO_CFGA_GPIO6INCFG_M                0x01000000
#define AM_REG_GPIO_CFGA_GPIO6INCFG(n)               (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_CFGA_GPIO6INCFG_READ             0x00000000
#define AM_REG_GPIO_CFGA_GPIO6INCFG_RDZERO           0x01000000

// GPIO5 interrupt direction.
#define AM_REG_GPIO_CFGA_GPIO5INTD_S                 23
#define AM_REG_GPIO_CFGA_GPIO5INTD_M                 0x00800000
#define AM_REG_GPIO_CFGA_GPIO5INTD(n)                (((uint32_t)(n) << 23) & 0x00800000)
#define AM_REG_GPIO_CFGA_GPIO5INTD_INTLH             0x00000000
#define AM_REG_GPIO_CFGA_GPIO5INTD_INTHL             0x00800000

// GPIO5 output configuration.
#define AM_REG_GPIO_CFGA_GPIO5OUTCFG_S               21
#define AM_REG_GPIO_CFGA_GPIO5OUTCFG_M               0x00600000
#define AM_REG_GPIO_CFGA_GPIO5OUTCFG(n)              (((uint32_t)(n) << 21) & 0x00600000)
#define AM_REG_GPIO_CFGA_GPIO5OUTCFG_DIS             0x00000000
#define AM_REG_GPIO_CFGA_GPIO5OUTCFG_PUSHPULL        0x00200000
#define AM_REG_GPIO_CFGA_GPIO5OUTCFG_OD              0x00400000
#define AM_REG_GPIO_CFGA_GPIO5OUTCFG_TS              0x00600000

// GPIO5 input enable.
#define AM_REG_GPIO_CFGA_GPIO5INCFG_S                20
#define AM_REG_GPIO_CFGA_GPIO5INCFG_M                0x00100000
#define AM_REG_GPIO_CFGA_GPIO5INCFG(n)               (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_CFGA_GPIO5INCFG_READ             0x00000000
#define AM_REG_GPIO_CFGA_GPIO5INCFG_RDZERO           0x00100000

// GPIO4 interrupt direction.
#define AM_REG_GPIO_CFGA_GPIO4INTD_S                 19
#define AM_REG_GPIO_CFGA_GPIO4INTD_M                 0x00080000
#define AM_REG_GPIO_CFGA_GPIO4INTD(n)                (((uint32_t)(n) << 19) & 0x00080000)
#define AM_REG_GPIO_CFGA_GPIO4INTD_INTLH             0x00000000
#define AM_REG_GPIO_CFGA_GPIO4INTD_INTHL             0x00080000

// GPIO4 output configuration.
#define AM_REG_GPIO_CFGA_GPIO4OUTCFG_S               17
#define AM_REG_GPIO_CFGA_GPIO4OUTCFG_M               0x00060000
#define AM_REG_GPIO_CFGA_GPIO4OUTCFG(n)              (((uint32_t)(n) << 17) & 0x00060000)
#define AM_REG_GPIO_CFGA_GPIO4OUTCFG_DIS             0x00000000
#define AM_REG_GPIO_CFGA_GPIO4OUTCFG_PUSHPULL        0x00020000
#define AM_REG_GPIO_CFGA_GPIO4OUTCFG_OD              0x00040000
#define AM_REG_GPIO_CFGA_GPIO4OUTCFG_TS              0x00060000

// GPIO4 input enable.
#define AM_REG_GPIO_CFGA_GPIO4INCFG_S                16
#define AM_REG_GPIO_CFGA_GPIO4INCFG_M                0x00010000
#define AM_REG_GPIO_CFGA_GPIO4INCFG(n)               (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_CFGA_GPIO4INCFG_READ             0x00000000
#define AM_REG_GPIO_CFGA_GPIO4INCFG_RDZERO           0x00010000

// GPIO3 interrupt direction.
#define AM_REG_GPIO_CFGA_GPIO3INTD_S                 15
#define AM_REG_GPIO_CFGA_GPIO3INTD_M                 0x00008000
#define AM_REG_GPIO_CFGA_GPIO3INTD(n)                (((uint32_t)(n) << 15) & 0x00008000)
#define AM_REG_GPIO_CFGA_GPIO3INTD_INTLH             0x00000000
#define AM_REG_GPIO_CFGA_GPIO3INTD_INTHL             0x00008000

// GPIO3 output configuration.
#define AM_REG_GPIO_CFGA_GPIO3OUTCFG_S               13
#define AM_REG_GPIO_CFGA_GPIO3OUTCFG_M               0x00006000
#define AM_REG_GPIO_CFGA_GPIO3OUTCFG(n)              (((uint32_t)(n) << 13) & 0x00006000)
#define AM_REG_GPIO_CFGA_GPIO3OUTCFG_DIS             0x00000000
#define AM_REG_GPIO_CFGA_GPIO3OUTCFG_PUSHPULL        0x00002000
#define AM_REG_GPIO_CFGA_GPIO3OUTCFG_OD              0x00004000
#define AM_REG_GPIO_CFGA_GPIO3OUTCFG_TS              0x00006000

// GPIO3 input enable.
#define AM_REG_GPIO_CFGA_GPIO3INCFG_S                12
#define AM_REG_GPIO_CFGA_GPIO3INCFG_M                0x00001000
#define AM_REG_GPIO_CFGA_GPIO3INCFG(n)               (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_CFGA_GPIO3INCFG_READ             0x00000000
#define AM_REG_GPIO_CFGA_GPIO3INCFG_RDZERO           0x00001000

// GPIO2 interrupt direction.
#define AM_REG_GPIO_CFGA_GPIO2INTD_S                 11
#define AM_REG_GPIO_CFGA_GPIO2INTD_M                 0x00000800
#define AM_REG_GPIO_CFGA_GPIO2INTD(n)                (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_GPIO_CFGA_GPIO2INTD_INTLH             0x00000000
#define AM_REG_GPIO_CFGA_GPIO2INTD_INTHL             0x00000800

// GPIO2 output configuration.
#define AM_REG_GPIO_CFGA_GPIO2OUTCFG_S               9
#define AM_REG_GPIO_CFGA_GPIO2OUTCFG_M               0x00000600
#define AM_REG_GPIO_CFGA_GPIO2OUTCFG(n)              (((uint32_t)(n) << 9) & 0x00000600)
#define AM_REG_GPIO_CFGA_GPIO2OUTCFG_DIS             0x00000000
#define AM_REG_GPIO_CFGA_GPIO2OUTCFG_PUSHPULL        0x00000200
#define AM_REG_GPIO_CFGA_GPIO2OUTCFG_OD              0x00000400
#define AM_REG_GPIO_CFGA_GPIO2OUTCFG_TS              0x00000600

// GPIO2 input enable.
#define AM_REG_GPIO_CFGA_GPIO2INCFG_S                8
#define AM_REG_GPIO_CFGA_GPIO2INCFG_M                0x00000100
#define AM_REG_GPIO_CFGA_GPIO2INCFG(n)               (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_CFGA_GPIO2INCFG_READ             0x00000000
#define AM_REG_GPIO_CFGA_GPIO2INCFG_RDZERO           0x00000100

// GPIO1 interrupt direction.
#define AM_REG_GPIO_CFGA_GPIO1INTD_S                 7
#define AM_REG_GPIO_CFGA_GPIO1INTD_M                 0x00000080
#define AM_REG_GPIO_CFGA_GPIO1INTD(n)                (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_GPIO_CFGA_GPIO1INTD_INTLH             0x00000000
#define AM_REG_GPIO_CFGA_GPIO1INTD_INTHL             0x00000080

// GPIO1 output configuration.
#define AM_REG_GPIO_CFGA_GPIO1OUTCFG_S               5
#define AM_REG_GPIO_CFGA_GPIO1OUTCFG_M               0x00000060
#define AM_REG_GPIO_CFGA_GPIO1OUTCFG(n)              (((uint32_t)(n) << 5) & 0x00000060)
#define AM_REG_GPIO_CFGA_GPIO1OUTCFG_DIS             0x00000000
#define AM_REG_GPIO_CFGA_GPIO1OUTCFG_PUSHPULL        0x00000020
#define AM_REG_GPIO_CFGA_GPIO1OUTCFG_OD              0x00000040
#define AM_REG_GPIO_CFGA_GPIO1OUTCFG_TS              0x00000060

// GPIO1 input enable.
#define AM_REG_GPIO_CFGA_GPIO1INCFG_S                4
#define AM_REG_GPIO_CFGA_GPIO1INCFG_M                0x00000010
#define AM_REG_GPIO_CFGA_GPIO1INCFG(n)               (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_CFGA_GPIO1INCFG_READ             0x00000000
#define AM_REG_GPIO_CFGA_GPIO1INCFG_RDZERO           0x00000010

// GPIO0 interrupt direction.
#define AM_REG_GPIO_CFGA_GPIO0INTD_S                 3
#define AM_REG_GPIO_CFGA_GPIO0INTD_M                 0x00000008
#define AM_REG_GPIO_CFGA_GPIO0INTD(n)                (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_GPIO_CFGA_GPIO0INTD_INTLH             0x00000000
#define AM_REG_GPIO_CFGA_GPIO0INTD_INTHL             0x00000008

// GPIO0 output configuration.
#define AM_REG_GPIO_CFGA_GPIO0OUTCFG_S               1
#define AM_REG_GPIO_CFGA_GPIO0OUTCFG_M               0x00000006
#define AM_REG_GPIO_CFGA_GPIO0OUTCFG(n)              (((uint32_t)(n) << 1) & 0x00000006)
#define AM_REG_GPIO_CFGA_GPIO0OUTCFG_DIS             0x00000000
#define AM_REG_GPIO_CFGA_GPIO0OUTCFG_PUSHPULL        0x00000002
#define AM_REG_GPIO_CFGA_GPIO0OUTCFG_OD              0x00000004
#define AM_REG_GPIO_CFGA_GPIO0OUTCFG_TS              0x00000006

// GPIO0 input enable.
#define AM_REG_GPIO_CFGA_GPIO0INCFG_S                0
#define AM_REG_GPIO_CFGA_GPIO0INCFG_M                0x00000001
#define AM_REG_GPIO_CFGA_GPIO0INCFG(n)               (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_CFGA_GPIO0INCFG_READ             0x00000000
#define AM_REG_GPIO_CFGA_GPIO0INCFG_RDZERO           0x00000001

//*****************************************************************************
//
// GPIO_CFGB - GPIO Configuration Register B
//
//*****************************************************************************
// GPIO15 interrupt direction.
#define AM_REG_GPIO_CFGB_GPIO15INTD_S                31
#define AM_REG_GPIO_CFGB_GPIO15INTD_M                0x80000000
#define AM_REG_GPIO_CFGB_GPIO15INTD(n)               (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_GPIO_CFGB_GPIO15INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGB_GPIO15INTD_INTHL            0x80000000

// GPIO15 output configuration.
#define AM_REG_GPIO_CFGB_GPIO15OUTCFG_S              29
#define AM_REG_GPIO_CFGB_GPIO15OUTCFG_M              0x60000000
#define AM_REG_GPIO_CFGB_GPIO15OUTCFG(n)             (((uint32_t)(n) << 29) & 0x60000000)
#define AM_REG_GPIO_CFGB_GPIO15OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGB_GPIO15OUTCFG_PUSHPULL       0x20000000
#define AM_REG_GPIO_CFGB_GPIO15OUTCFG_OD             0x40000000
#define AM_REG_GPIO_CFGB_GPIO15OUTCFG_TS             0x60000000

// GPIO15 input enable.
#define AM_REG_GPIO_CFGB_GPIO15INCFG_S               28
#define AM_REG_GPIO_CFGB_GPIO15INCFG_M               0x10000000
#define AM_REG_GPIO_CFGB_GPIO15INCFG(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_CFGB_GPIO15INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGB_GPIO15INCFG_RDZERO          0x10000000

// GPIO14 interrupt direction.
#define AM_REG_GPIO_CFGB_GPIO14INTD_S                27
#define AM_REG_GPIO_CFGB_GPIO14INTD_M                0x08000000
#define AM_REG_GPIO_CFGB_GPIO14INTD(n)               (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_GPIO_CFGB_GPIO14INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGB_GPIO14INTD_INTHL            0x08000000

// GPIO14 output configuration.
#define AM_REG_GPIO_CFGB_GPIO14OUTCFG_S              25
#define AM_REG_GPIO_CFGB_GPIO14OUTCFG_M              0x06000000
#define AM_REG_GPIO_CFGB_GPIO14OUTCFG(n)             (((uint32_t)(n) << 25) & 0x06000000)
#define AM_REG_GPIO_CFGB_GPIO14OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGB_GPIO14OUTCFG_PUSHPULL       0x02000000
#define AM_REG_GPIO_CFGB_GPIO14OUTCFG_OD             0x04000000
#define AM_REG_GPIO_CFGB_GPIO14OUTCFG_TS             0x06000000

// GPIO14 input enable.
#define AM_REG_GPIO_CFGB_GPIO14INCFG_S               24
#define AM_REG_GPIO_CFGB_GPIO14INCFG_M               0x01000000
#define AM_REG_GPIO_CFGB_GPIO14INCFG(n)              (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_CFGB_GPIO14INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGB_GPIO14INCFG_RDZERO          0x01000000

// GPIO13 interrupt direction.
#define AM_REG_GPIO_CFGB_GPIO13INTD_S                23
#define AM_REG_GPIO_CFGB_GPIO13INTD_M                0x00800000
#define AM_REG_GPIO_CFGB_GPIO13INTD(n)               (((uint32_t)(n) << 23) & 0x00800000)
#define AM_REG_GPIO_CFGB_GPIO13INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGB_GPIO13INTD_INTHL            0x00800000

// GPIO13 output configuration.
#define AM_REG_GPIO_CFGB_GPIO13OUTCFG_S              21
#define AM_REG_GPIO_CFGB_GPIO13OUTCFG_M              0x00600000
#define AM_REG_GPIO_CFGB_GPIO13OUTCFG(n)             (((uint32_t)(n) << 21) & 0x00600000)
#define AM_REG_GPIO_CFGB_GPIO13OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGB_GPIO13OUTCFG_PUSHPULL       0x00200000
#define AM_REG_GPIO_CFGB_GPIO13OUTCFG_OD             0x00400000
#define AM_REG_GPIO_CFGB_GPIO13OUTCFG_TS             0x00600000

// GPIO13 input enable.
#define AM_REG_GPIO_CFGB_GPIO13INCFG_S               20
#define AM_REG_GPIO_CFGB_GPIO13INCFG_M               0x00100000
#define AM_REG_GPIO_CFGB_GPIO13INCFG(n)              (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_CFGB_GPIO13INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGB_GPIO13INCFG_RDZERO          0x00100000

// GPIO12 interrupt direction.
#define AM_REG_GPIO_CFGB_GPIO12INTD_S                19
#define AM_REG_GPIO_CFGB_GPIO12INTD_M                0x00080000
#define AM_REG_GPIO_CFGB_GPIO12INTD(n)               (((uint32_t)(n) << 19) & 0x00080000)
#define AM_REG_GPIO_CFGB_GPIO12INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGB_GPIO12INTD_INTHL            0x00080000

// GPIO12 output configuration.
#define AM_REG_GPIO_CFGB_GPIO12OUTCFG_S              17
#define AM_REG_GPIO_CFGB_GPIO12OUTCFG_M              0x00060000
#define AM_REG_GPIO_CFGB_GPIO12OUTCFG(n)             (((uint32_t)(n) << 17) & 0x00060000)
#define AM_REG_GPIO_CFGB_GPIO12OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGB_GPIO12OUTCFG_PUSHPULL       0x00020000
#define AM_REG_GPIO_CFGB_GPIO12OUTCFG_OD             0x00040000
#define AM_REG_GPIO_CFGB_GPIO12OUTCFG_TS             0x00060000

// GPIO12 input enable.
#define AM_REG_GPIO_CFGB_GPIO12INCFG_S               16
#define AM_REG_GPIO_CFGB_GPIO12INCFG_M               0x00010000
#define AM_REG_GPIO_CFGB_GPIO12INCFG(n)              (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_CFGB_GPIO12INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGB_GPIO12INCFG_RDZERO          0x00010000

// GPIO11 interrupt direction.
#define AM_REG_GPIO_CFGB_GPIO11INTD_S                15
#define AM_REG_GPIO_CFGB_GPIO11INTD_M                0x00008000
#define AM_REG_GPIO_CFGB_GPIO11INTD(n)               (((uint32_t)(n) << 15) & 0x00008000)
#define AM_REG_GPIO_CFGB_GPIO11INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGB_GPIO11INTD_INTHL            0x00008000

// GPIO11 output configuration.
#define AM_REG_GPIO_CFGB_GPIO11OUTCFG_S              13
#define AM_REG_GPIO_CFGB_GPIO11OUTCFG_M              0x00006000
#define AM_REG_GPIO_CFGB_GPIO11OUTCFG(n)             (((uint32_t)(n) << 13) & 0x00006000)
#define AM_REG_GPIO_CFGB_GPIO11OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGB_GPIO11OUTCFG_PUSHPULL       0x00002000
#define AM_REG_GPIO_CFGB_GPIO11OUTCFG_OD             0x00004000
#define AM_REG_GPIO_CFGB_GPIO11OUTCFG_TS             0x00006000

// GPIO11 input enable.
#define AM_REG_GPIO_CFGB_GPIO11INCFG_S               12
#define AM_REG_GPIO_CFGB_GPIO11INCFG_M               0x00001000
#define AM_REG_GPIO_CFGB_GPIO11INCFG(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_CFGB_GPIO11INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGB_GPIO11INCFG_RDZERO          0x00001000

// GPIO10 interrupt direction.
#define AM_REG_GPIO_CFGB_GPIO10INTD_S                11
#define AM_REG_GPIO_CFGB_GPIO10INTD_M                0x00000800
#define AM_REG_GPIO_CFGB_GPIO10INTD(n)               (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_GPIO_CFGB_GPIO10INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGB_GPIO10INTD_INTHL            0x00000800

// GPIO10 output configuration.
#define AM_REG_GPIO_CFGB_GPIO10OUTCFG_S              9
#define AM_REG_GPIO_CFGB_GPIO10OUTCFG_M              0x00000600
#define AM_REG_GPIO_CFGB_GPIO10OUTCFG(n)             (((uint32_t)(n) << 9) & 0x00000600)
#define AM_REG_GPIO_CFGB_GPIO10OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGB_GPIO10OUTCFG_PUSHPULL       0x00000200
#define AM_REG_GPIO_CFGB_GPIO10OUTCFG_OD             0x00000400
#define AM_REG_GPIO_CFGB_GPIO10OUTCFG_TS             0x00000600

// GPIO10 input enable.
#define AM_REG_GPIO_CFGB_GPIO10INCFG_S               8
#define AM_REG_GPIO_CFGB_GPIO10INCFG_M               0x00000100
#define AM_REG_GPIO_CFGB_GPIO10INCFG(n)              (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_CFGB_GPIO10INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGB_GPIO10INCFG_RDZERO          0x00000100

// GPIO9 interrupt direction.
#define AM_REG_GPIO_CFGB_GPIO9INTD_S                 7
#define AM_REG_GPIO_CFGB_GPIO9INTD_M                 0x00000080
#define AM_REG_GPIO_CFGB_GPIO9INTD(n)                (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_GPIO_CFGB_GPIO9INTD_INTLH             0x00000000
#define AM_REG_GPIO_CFGB_GPIO9INTD_INTHL             0x00000080

// GPIO9 output configuration.
#define AM_REG_GPIO_CFGB_GPIO9OUTCFG_S               5
#define AM_REG_GPIO_CFGB_GPIO9OUTCFG_M               0x00000060
#define AM_REG_GPIO_CFGB_GPIO9OUTCFG(n)              (((uint32_t)(n) << 5) & 0x00000060)
#define AM_REG_GPIO_CFGB_GPIO9OUTCFG_DIS             0x00000000
#define AM_REG_GPIO_CFGB_GPIO9OUTCFG_PUSHPULL        0x00000020
#define AM_REG_GPIO_CFGB_GPIO9OUTCFG_OD              0x00000040
#define AM_REG_GPIO_CFGB_GPIO9OUTCFG_TS              0x00000060

// GPIO9 input enable.
#define AM_REG_GPIO_CFGB_GPIO9INCFG_S                4
#define AM_REG_GPIO_CFGB_GPIO9INCFG_M                0x00000010
#define AM_REG_GPIO_CFGB_GPIO9INCFG(n)               (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_CFGB_GPIO9INCFG_READ             0x00000000
#define AM_REG_GPIO_CFGB_GPIO9INCFG_RDZERO           0x00000010

// GPIO8 interrupt direction.
#define AM_REG_GPIO_CFGB_GPIO8INTD_S                 3
#define AM_REG_GPIO_CFGB_GPIO8INTD_M                 0x00000008
#define AM_REG_GPIO_CFGB_GPIO8INTD(n)                (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_GPIO_CFGB_GPIO8INTD_INTLH             0x00000000
#define AM_REG_GPIO_CFGB_GPIO8INTD_INTHL             0x00000008

// GPIO8 output configuration.
#define AM_REG_GPIO_CFGB_GPIO8OUTCFG_S               1
#define AM_REG_GPIO_CFGB_GPIO8OUTCFG_M               0x00000006
#define AM_REG_GPIO_CFGB_GPIO8OUTCFG(n)              (((uint32_t)(n) << 1) & 0x00000006)
#define AM_REG_GPIO_CFGB_GPIO8OUTCFG_DIS             0x00000000
#define AM_REG_GPIO_CFGB_GPIO8OUTCFG_PUSHPULL        0x00000002
#define AM_REG_GPIO_CFGB_GPIO8OUTCFG_OD              0x00000004
#define AM_REG_GPIO_CFGB_GPIO8OUTCFG_TS              0x00000006

// GPIO8 input enable.
#define AM_REG_GPIO_CFGB_GPIO8INCFG_S                0
#define AM_REG_GPIO_CFGB_GPIO8INCFG_M                0x00000001
#define AM_REG_GPIO_CFGB_GPIO8INCFG(n)               (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_CFGB_GPIO8INCFG_READ             0x00000000
#define AM_REG_GPIO_CFGB_GPIO8INCFG_RDZERO           0x00000001

//*****************************************************************************
//
// GPIO_CFGC - GPIO Configuration Register C
//
//*****************************************************************************
// GPIO23 interrupt direction.
#define AM_REG_GPIO_CFGC_GPIO23INTD_S                31
#define AM_REG_GPIO_CFGC_GPIO23INTD_M                0x80000000
#define AM_REG_GPIO_CFGC_GPIO23INTD(n)               (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_GPIO_CFGC_GPIO23INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGC_GPIO23INTD_INTHL            0x80000000

// GPIO23 output configuration.
#define AM_REG_GPIO_CFGC_GPIO23OUTCFG_S              29
#define AM_REG_GPIO_CFGC_GPIO23OUTCFG_M              0x60000000
#define AM_REG_GPIO_CFGC_GPIO23OUTCFG(n)             (((uint32_t)(n) << 29) & 0x60000000)
#define AM_REG_GPIO_CFGC_GPIO23OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGC_GPIO23OUTCFG_PUSHPULL       0x20000000
#define AM_REG_GPIO_CFGC_GPIO23OUTCFG_OD             0x40000000
#define AM_REG_GPIO_CFGC_GPIO23OUTCFG_TS             0x60000000

// GPIO23 input enable.
#define AM_REG_GPIO_CFGC_GPIO23INCFG_S               28
#define AM_REG_GPIO_CFGC_GPIO23INCFG_M               0x10000000
#define AM_REG_GPIO_CFGC_GPIO23INCFG(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_CFGC_GPIO23INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGC_GPIO23INCFG_RDZERO          0x10000000

// GPIO22 interrupt direction.
#define AM_REG_GPIO_CFGC_GPIO22INTD_S                27
#define AM_REG_GPIO_CFGC_GPIO22INTD_M                0x08000000
#define AM_REG_GPIO_CFGC_GPIO22INTD(n)               (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_GPIO_CFGC_GPIO22INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGC_GPIO22INTD_INTHL            0x08000000

// GPIO22 output configuration.
#define AM_REG_GPIO_CFGC_GPIO22OUTCFG_S              25
#define AM_REG_GPIO_CFGC_GPIO22OUTCFG_M              0x06000000
#define AM_REG_GPIO_CFGC_GPIO22OUTCFG(n)             (((uint32_t)(n) << 25) & 0x06000000)
#define AM_REG_GPIO_CFGC_GPIO22OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGC_GPIO22OUTCFG_PUSHPULL       0x02000000
#define AM_REG_GPIO_CFGC_GPIO22OUTCFG_OD             0x04000000
#define AM_REG_GPIO_CFGC_GPIO22OUTCFG_TS             0x06000000

// GPIO22 input enable.
#define AM_REG_GPIO_CFGC_GPIO22INCFG_S               24
#define AM_REG_GPIO_CFGC_GPIO22INCFG_M               0x01000000
#define AM_REG_GPIO_CFGC_GPIO22INCFG(n)              (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_CFGC_GPIO22INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGC_GPIO22INCFG_RDZERO          0x01000000

// GPIO21 interrupt direction.
#define AM_REG_GPIO_CFGC_GPIO21INTD_S                23
#define AM_REG_GPIO_CFGC_GPIO21INTD_M                0x00800000
#define AM_REG_GPIO_CFGC_GPIO21INTD(n)               (((uint32_t)(n) << 23) & 0x00800000)
#define AM_REG_GPIO_CFGC_GPIO21INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGC_GPIO21INTD_INTHL            0x00800000

// GPIO21 output configuration.
#define AM_REG_GPIO_CFGC_GPIO21OUTCFG_S              21
#define AM_REG_GPIO_CFGC_GPIO21OUTCFG_M              0x00600000
#define AM_REG_GPIO_CFGC_GPIO21OUTCFG(n)             (((uint32_t)(n) << 21) & 0x00600000)
#define AM_REG_GPIO_CFGC_GPIO21OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGC_GPIO21OUTCFG_PUSHPULL       0x00200000
#define AM_REG_GPIO_CFGC_GPIO21OUTCFG_OD             0x00400000
#define AM_REG_GPIO_CFGC_GPIO21OUTCFG_TS             0x00600000

// GPIO21 input enable.
#define AM_REG_GPIO_CFGC_GPIO21INCFG_S               20
#define AM_REG_GPIO_CFGC_GPIO21INCFG_M               0x00100000
#define AM_REG_GPIO_CFGC_GPIO21INCFG(n)              (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_CFGC_GPIO21INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGC_GPIO21INCFG_RDZERO          0x00100000

// GPIO20 interrupt direction.
#define AM_REG_GPIO_CFGC_GPIO20INTD_S                19
#define AM_REG_GPIO_CFGC_GPIO20INTD_M                0x00080000
#define AM_REG_GPIO_CFGC_GPIO20INTD(n)               (((uint32_t)(n) << 19) & 0x00080000)
#define AM_REG_GPIO_CFGC_GPIO20INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGC_GPIO20INTD_INTHL            0x00080000

// GPIO20 output configuration.
#define AM_REG_GPIO_CFGC_GPIO20OUTCFG_S              17
#define AM_REG_GPIO_CFGC_GPIO20OUTCFG_M              0x00060000
#define AM_REG_GPIO_CFGC_GPIO20OUTCFG(n)             (((uint32_t)(n) << 17) & 0x00060000)
#define AM_REG_GPIO_CFGC_GPIO20OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGC_GPIO20OUTCFG_PUSHPULL       0x00020000
#define AM_REG_GPIO_CFGC_GPIO20OUTCFG_OD             0x00040000
#define AM_REG_GPIO_CFGC_GPIO20OUTCFG_TS             0x00060000

// GPIO20 input enable.
#define AM_REG_GPIO_CFGC_GPIO20INCFG_S               16
#define AM_REG_GPIO_CFGC_GPIO20INCFG_M               0x00010000
#define AM_REG_GPIO_CFGC_GPIO20INCFG(n)              (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_CFGC_GPIO20INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGC_GPIO20INCFG_RDZERO          0x00010000

// GPIO19 interrupt direction.
#define AM_REG_GPIO_CFGC_GPIO19INTD_S                15
#define AM_REG_GPIO_CFGC_GPIO19INTD_M                0x00008000
#define AM_REG_GPIO_CFGC_GPIO19INTD(n)               (((uint32_t)(n) << 15) & 0x00008000)
#define AM_REG_GPIO_CFGC_GPIO19INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGC_GPIO19INTD_INTHL            0x00008000

// GPIO19 output configuration.
#define AM_REG_GPIO_CFGC_GPIO19OUTCFG_S              13
#define AM_REG_GPIO_CFGC_GPIO19OUTCFG_M              0x00006000
#define AM_REG_GPIO_CFGC_GPIO19OUTCFG(n)             (((uint32_t)(n) << 13) & 0x00006000)
#define AM_REG_GPIO_CFGC_GPIO19OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGC_GPIO19OUTCFG_PUSHPULL       0x00002000
#define AM_REG_GPIO_CFGC_GPIO19OUTCFG_OD             0x00004000
#define AM_REG_GPIO_CFGC_GPIO19OUTCFG_TS             0x00006000

// GPIO19 input enable.
#define AM_REG_GPIO_CFGC_GPIO19INCFG_S               12
#define AM_REG_GPIO_CFGC_GPIO19INCFG_M               0x00001000
#define AM_REG_GPIO_CFGC_GPIO19INCFG(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_CFGC_GPIO19INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGC_GPIO19INCFG_RDZERO          0x00001000

// GPIO18 interrupt direction.
#define AM_REG_GPIO_CFGC_GPIO18INTD_S                11
#define AM_REG_GPIO_CFGC_GPIO18INTD_M                0x00000800
#define AM_REG_GPIO_CFGC_GPIO18INTD(n)               (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_GPIO_CFGC_GPIO18INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGC_GPIO18INTD_INTHL            0x00000800

// GPIO18 output configuration.
#define AM_REG_GPIO_CFGC_GPIO18OUTCFG_S              9
#define AM_REG_GPIO_CFGC_GPIO18OUTCFG_M              0x00000600
#define AM_REG_GPIO_CFGC_GPIO18OUTCFG(n)             (((uint32_t)(n) << 9) & 0x00000600)
#define AM_REG_GPIO_CFGC_GPIO18OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGC_GPIO18OUTCFG_PUSHPULL       0x00000200
#define AM_REG_GPIO_CFGC_GPIO18OUTCFG_OD             0x00000400
#define AM_REG_GPIO_CFGC_GPIO18OUTCFG_TS             0x00000600

// GPIO18 input enable.
#define AM_REG_GPIO_CFGC_GPIO18INCFG_S               8
#define AM_REG_GPIO_CFGC_GPIO18INCFG_M               0x00000100
#define AM_REG_GPIO_CFGC_GPIO18INCFG(n)              (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_CFGC_GPIO18INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGC_GPIO18INCFG_RDZERO          0x00000100

// GPIO17 interrupt direction.
#define AM_REG_GPIO_CFGC_GPIO17INTD_S                7
#define AM_REG_GPIO_CFGC_GPIO17INTD_M                0x00000080
#define AM_REG_GPIO_CFGC_GPIO17INTD(n)               (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_GPIO_CFGC_GPIO17INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGC_GPIO17INTD_INTHL            0x00000080

// GPIO17 output configuration.
#define AM_REG_GPIO_CFGC_GPIO17OUTCFG_S              5
#define AM_REG_GPIO_CFGC_GPIO17OUTCFG_M              0x00000060
#define AM_REG_GPIO_CFGC_GPIO17OUTCFG(n)             (((uint32_t)(n) << 5) & 0x00000060)
#define AM_REG_GPIO_CFGC_GPIO17OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGC_GPIO17OUTCFG_PUSHPULL       0x00000020
#define AM_REG_GPIO_CFGC_GPIO17OUTCFG_OD             0x00000040
#define AM_REG_GPIO_CFGC_GPIO17OUTCFG_TS             0x00000060

// GPIO17 input enable.
#define AM_REG_GPIO_CFGC_GPIO17INCFG_S               4
#define AM_REG_GPIO_CFGC_GPIO17INCFG_M               0x00000010
#define AM_REG_GPIO_CFGC_GPIO17INCFG(n)              (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_CFGC_GPIO17INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGC_GPIO17INCFG_RDZERO          0x00000010

// GPIO16 interrupt direction.
#define AM_REG_GPIO_CFGC_GPIO16INTD_S                3
#define AM_REG_GPIO_CFGC_GPIO16INTD_M                0x00000008
#define AM_REG_GPIO_CFGC_GPIO16INTD(n)               (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_GPIO_CFGC_GPIO16INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGC_GPIO16INTD_INTHL            0x00000008

// GPIO16 output configuration.
#define AM_REG_GPIO_CFGC_GPIO16OUTCFG_S              1
#define AM_REG_GPIO_CFGC_GPIO16OUTCFG_M              0x00000006
#define AM_REG_GPIO_CFGC_GPIO16OUTCFG(n)             (((uint32_t)(n) << 1) & 0x00000006)
#define AM_REG_GPIO_CFGC_GPIO16OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGC_GPIO16OUTCFG_PUSHPULL       0x00000002
#define AM_REG_GPIO_CFGC_GPIO16OUTCFG_OD             0x00000004
#define AM_REG_GPIO_CFGC_GPIO16OUTCFG_TS             0x00000006

// GPIO16 input enable.
#define AM_REG_GPIO_CFGC_GPIO16INCFG_S               0
#define AM_REG_GPIO_CFGC_GPIO16INCFG_M               0x00000001
#define AM_REG_GPIO_CFGC_GPIO16INCFG(n)              (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_CFGC_GPIO16INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGC_GPIO16INCFG_RDZERO          0x00000001

//*****************************************************************************
//
// GPIO_CFGD - GPIO Configuration Register D
//
//*****************************************************************************
// GPIO31 interrupt direction.
#define AM_REG_GPIO_CFGD_GPIO31INTD_S                31
#define AM_REG_GPIO_CFGD_GPIO31INTD_M                0x80000000
#define AM_REG_GPIO_CFGD_GPIO31INTD(n)               (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_GPIO_CFGD_GPIO31INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGD_GPIO31INTD_INTHL            0x80000000

// GPIO31 output configuration.
#define AM_REG_GPIO_CFGD_GPIO31OUTCFG_S              29
#define AM_REG_GPIO_CFGD_GPIO31OUTCFG_M              0x60000000
#define AM_REG_GPIO_CFGD_GPIO31OUTCFG(n)             (((uint32_t)(n) << 29) & 0x60000000)
#define AM_REG_GPIO_CFGD_GPIO31OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGD_GPIO31OUTCFG_PUSHPULL       0x20000000
#define AM_REG_GPIO_CFGD_GPIO31OUTCFG_OD             0x40000000
#define AM_REG_GPIO_CFGD_GPIO31OUTCFG_TS             0x60000000

// GPIO31 input enable.
#define AM_REG_GPIO_CFGD_GPIO31INCFG_S               28
#define AM_REG_GPIO_CFGD_GPIO31INCFG_M               0x10000000
#define AM_REG_GPIO_CFGD_GPIO31INCFG(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_CFGD_GPIO31INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGD_GPIO31INCFG_RDZERO          0x10000000

// GPIO30 interrupt direction.
#define AM_REG_GPIO_CFGD_GPIO30INTD_S                27
#define AM_REG_GPIO_CFGD_GPIO30INTD_M                0x08000000
#define AM_REG_GPIO_CFGD_GPIO30INTD(n)               (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_GPIO_CFGD_GPIO30INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGD_GPIO30INTD_INTHL            0x08000000

// GPIO30 output configuration.
#define AM_REG_GPIO_CFGD_GPIO30OUTCFG_S              25
#define AM_REG_GPIO_CFGD_GPIO30OUTCFG_M              0x06000000
#define AM_REG_GPIO_CFGD_GPIO30OUTCFG(n)             (((uint32_t)(n) << 25) & 0x06000000)
#define AM_REG_GPIO_CFGD_GPIO30OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGD_GPIO30OUTCFG_PUSHPULL       0x02000000
#define AM_REG_GPIO_CFGD_GPIO30OUTCFG_OD             0x04000000
#define AM_REG_GPIO_CFGD_GPIO30OUTCFG_TS             0x06000000

// GPIO30 input enable.
#define AM_REG_GPIO_CFGD_GPIO30INCFG_S               24
#define AM_REG_GPIO_CFGD_GPIO30INCFG_M               0x01000000
#define AM_REG_GPIO_CFGD_GPIO30INCFG(n)              (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_CFGD_GPIO30INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGD_GPIO30INCFG_RDZERO          0x01000000

// GPIO29 interrupt direction.
#define AM_REG_GPIO_CFGD_GPIO29INTD_S                23
#define AM_REG_GPIO_CFGD_GPIO29INTD_M                0x00800000
#define AM_REG_GPIO_CFGD_GPIO29INTD(n)               (((uint32_t)(n) << 23) & 0x00800000)
#define AM_REG_GPIO_CFGD_GPIO29INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGD_GPIO29INTD_INTHL            0x00800000

// GPIO29 output configuration.
#define AM_REG_GPIO_CFGD_GPIO29OUTCFG_S              21
#define AM_REG_GPIO_CFGD_GPIO29OUTCFG_M              0x00600000
#define AM_REG_GPIO_CFGD_GPIO29OUTCFG(n)             (((uint32_t)(n) << 21) & 0x00600000)
#define AM_REG_GPIO_CFGD_GPIO29OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGD_GPIO29OUTCFG_PUSHPULL       0x00200000
#define AM_REG_GPIO_CFGD_GPIO29OUTCFG_OD             0x00400000
#define AM_REG_GPIO_CFGD_GPIO29OUTCFG_TS             0x00600000

// GPIO29 input enable.
#define AM_REG_GPIO_CFGD_GPIO29INCFG_S               20
#define AM_REG_GPIO_CFGD_GPIO29INCFG_M               0x00100000
#define AM_REG_GPIO_CFGD_GPIO29INCFG(n)              (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_CFGD_GPIO29INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGD_GPIO29INCFG_RDZERO          0x00100000

// GPIO28 interrupt direction.
#define AM_REG_GPIO_CFGD_GPIO28INTD_S                19
#define AM_REG_GPIO_CFGD_GPIO28INTD_M                0x00080000
#define AM_REG_GPIO_CFGD_GPIO28INTD(n)               (((uint32_t)(n) << 19) & 0x00080000)
#define AM_REG_GPIO_CFGD_GPIO28INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGD_GPIO28INTD_INTHL            0x00080000

// GPIO28 output configuration.
#define AM_REG_GPIO_CFGD_GPIO28OUTCFG_S              17
#define AM_REG_GPIO_CFGD_GPIO28OUTCFG_M              0x00060000
#define AM_REG_GPIO_CFGD_GPIO28OUTCFG(n)             (((uint32_t)(n) << 17) & 0x00060000)
#define AM_REG_GPIO_CFGD_GPIO28OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGD_GPIO28OUTCFG_PUSHPULL       0x00020000
#define AM_REG_GPIO_CFGD_GPIO28OUTCFG_OD             0x00040000
#define AM_REG_GPIO_CFGD_GPIO28OUTCFG_TS             0x00060000

// GPIO28 input enable.
#define AM_REG_GPIO_CFGD_GPIO28INCFG_S               16
#define AM_REG_GPIO_CFGD_GPIO28INCFG_M               0x00010000
#define AM_REG_GPIO_CFGD_GPIO28INCFG(n)              (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_CFGD_GPIO28INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGD_GPIO28INCFG_RDZERO          0x00010000

// GPIO27 interrupt direction.
#define AM_REG_GPIO_CFGD_GPIO27INTD_S                15
#define AM_REG_GPIO_CFGD_GPIO27INTD_M                0x00008000
#define AM_REG_GPIO_CFGD_GPIO27INTD(n)               (((uint32_t)(n) << 15) & 0x00008000)
#define AM_REG_GPIO_CFGD_GPIO27INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGD_GPIO27INTD_INTHL            0x00008000

// GPIO27 output configuration.
#define AM_REG_GPIO_CFGD_GPIO27OUTCFG_S              13
#define AM_REG_GPIO_CFGD_GPIO27OUTCFG_M              0x00006000
#define AM_REG_GPIO_CFGD_GPIO27OUTCFG(n)             (((uint32_t)(n) << 13) & 0x00006000)
#define AM_REG_GPIO_CFGD_GPIO27OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGD_GPIO27OUTCFG_PUSHPULL       0x00002000
#define AM_REG_GPIO_CFGD_GPIO27OUTCFG_OD             0x00004000
#define AM_REG_GPIO_CFGD_GPIO27OUTCFG_TS             0x00006000

// GPIO27 input enable.
#define AM_REG_GPIO_CFGD_GPIO27INCFG_S               12
#define AM_REG_GPIO_CFGD_GPIO27INCFG_M               0x00001000
#define AM_REG_GPIO_CFGD_GPIO27INCFG(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_CFGD_GPIO27INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGD_GPIO27INCFG_RDZERO          0x00001000

// GPIO26 interrupt direction.
#define AM_REG_GPIO_CFGD_GPIO26INTD_S                11
#define AM_REG_GPIO_CFGD_GPIO26INTD_M                0x00000800
#define AM_REG_GPIO_CFGD_GPIO26INTD(n)               (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_GPIO_CFGD_GPIO26INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGD_GPIO26INTD_INTHL            0x00000800

// GPIO26 output configuration.
#define AM_REG_GPIO_CFGD_GPIO26OUTCFG_S              9
#define AM_REG_GPIO_CFGD_GPIO26OUTCFG_M              0x00000600
#define AM_REG_GPIO_CFGD_GPIO26OUTCFG(n)             (((uint32_t)(n) << 9) & 0x00000600)
#define AM_REG_GPIO_CFGD_GPIO26OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGD_GPIO26OUTCFG_PUSHPULL       0x00000200
#define AM_REG_GPIO_CFGD_GPIO26OUTCFG_OD             0x00000400
#define AM_REG_GPIO_CFGD_GPIO26OUTCFG_TS             0x00000600

// GPIO26 input enable.
#define AM_REG_GPIO_CFGD_GPIO26INCFG_S               8
#define AM_REG_GPIO_CFGD_GPIO26INCFG_M               0x00000100
#define AM_REG_GPIO_CFGD_GPIO26INCFG(n)              (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_CFGD_GPIO26INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGD_GPIO26INCFG_RDZERO          0x00000100

// GPIO25 interrupt direction.
#define AM_REG_GPIO_CFGD_GPIO25INTD_S                7
#define AM_REG_GPIO_CFGD_GPIO25INTD_M                0x00000080
#define AM_REG_GPIO_CFGD_GPIO25INTD(n)               (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_GPIO_CFGD_GPIO25INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGD_GPIO25INTD_INTHL            0x00000080

// GPIO25 output configuration.
#define AM_REG_GPIO_CFGD_GPIO25OUTCFG_S              5
#define AM_REG_GPIO_CFGD_GPIO25OUTCFG_M              0x00000060
#define AM_REG_GPIO_CFGD_GPIO25OUTCFG(n)             (((uint32_t)(n) << 5) & 0x00000060)
#define AM_REG_GPIO_CFGD_GPIO25OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGD_GPIO25OUTCFG_PUSHPULL       0x00000020
#define AM_REG_GPIO_CFGD_GPIO25OUTCFG_OD             0x00000040
#define AM_REG_GPIO_CFGD_GPIO25OUTCFG_TS             0x00000060

// GPIO25 input enable.
#define AM_REG_GPIO_CFGD_GPIO25INCFG_S               4
#define AM_REG_GPIO_CFGD_GPIO25INCFG_M               0x00000010
#define AM_REG_GPIO_CFGD_GPIO25INCFG(n)              (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_CFGD_GPIO25INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGD_GPIO25INCFG_RDZERO          0x00000010

// GPIO24 interrupt direction.
#define AM_REG_GPIO_CFGD_GPIO24INTD_S                3
#define AM_REG_GPIO_CFGD_GPIO24INTD_M                0x00000008
#define AM_REG_GPIO_CFGD_GPIO24INTD(n)               (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_GPIO_CFGD_GPIO24INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGD_GPIO24INTD_INTHL            0x00000008

// GPIO24 output configuration.
#define AM_REG_GPIO_CFGD_GPIO24OUTCFG_S              1
#define AM_REG_GPIO_CFGD_GPIO24OUTCFG_M              0x00000006
#define AM_REG_GPIO_CFGD_GPIO24OUTCFG(n)             (((uint32_t)(n) << 1) & 0x00000006)
#define AM_REG_GPIO_CFGD_GPIO24OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGD_GPIO24OUTCFG_PUSHPULL       0x00000002
#define AM_REG_GPIO_CFGD_GPIO24OUTCFG_OD             0x00000004
#define AM_REG_GPIO_CFGD_GPIO24OUTCFG_TS             0x00000006

// GPIO24 input enable.
#define AM_REG_GPIO_CFGD_GPIO24INCFG_S               0
#define AM_REG_GPIO_CFGD_GPIO24INCFG_M               0x00000001
#define AM_REG_GPIO_CFGD_GPIO24INCFG(n)              (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_CFGD_GPIO24INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGD_GPIO24INCFG_RDZERO          0x00000001

//*****************************************************************************
//
// GPIO_CFGE - GPIO Configuration Register E
//
//*****************************************************************************
// GPIO39 interrupt direction.
#define AM_REG_GPIO_CFGE_GPIO39INTD_S                31
#define AM_REG_GPIO_CFGE_GPIO39INTD_M                0x80000000
#define AM_REG_GPIO_CFGE_GPIO39INTD(n)               (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_GPIO_CFGE_GPIO39INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGE_GPIO39INTD_INTHL            0x80000000

// GPIO39 output configuration.
#define AM_REG_GPIO_CFGE_GPIO39OUTCFG_S              29
#define AM_REG_GPIO_CFGE_GPIO39OUTCFG_M              0x60000000
#define AM_REG_GPIO_CFGE_GPIO39OUTCFG(n)             (((uint32_t)(n) << 29) & 0x60000000)
#define AM_REG_GPIO_CFGE_GPIO39OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGE_GPIO39OUTCFG_PUSHPULL       0x20000000
#define AM_REG_GPIO_CFGE_GPIO39OUTCFG_OD             0x40000000
#define AM_REG_GPIO_CFGE_GPIO39OUTCFG_TS             0x60000000

// GPIO39 input enable.
#define AM_REG_GPIO_CFGE_GPIO39INCFG_S               28
#define AM_REG_GPIO_CFGE_GPIO39INCFG_M               0x10000000
#define AM_REG_GPIO_CFGE_GPIO39INCFG(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_CFGE_GPIO39INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGE_GPIO39INCFG_RDZERO          0x10000000

// GPIO38 interrupt direction.
#define AM_REG_GPIO_CFGE_GPIO38INTD_S                27
#define AM_REG_GPIO_CFGE_GPIO38INTD_M                0x08000000
#define AM_REG_GPIO_CFGE_GPIO38INTD(n)               (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_GPIO_CFGE_GPIO38INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGE_GPIO38INTD_INTHL            0x08000000

// GPIO38 output configuration.
#define AM_REG_GPIO_CFGE_GPIO38OUTCFG_S              25
#define AM_REG_GPIO_CFGE_GPIO38OUTCFG_M              0x06000000
#define AM_REG_GPIO_CFGE_GPIO38OUTCFG(n)             (((uint32_t)(n) << 25) & 0x06000000)
#define AM_REG_GPIO_CFGE_GPIO38OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGE_GPIO38OUTCFG_PUSHPULL       0x02000000
#define AM_REG_GPIO_CFGE_GPIO38OUTCFG_OD             0x04000000
#define AM_REG_GPIO_CFGE_GPIO38OUTCFG_TS             0x06000000

// GPIO38 input enable.
#define AM_REG_GPIO_CFGE_GPIO38INCFG_S               24
#define AM_REG_GPIO_CFGE_GPIO38INCFG_M               0x01000000
#define AM_REG_GPIO_CFGE_GPIO38INCFG(n)              (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_CFGE_GPIO38INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGE_GPIO38INCFG_RDZERO          0x01000000

// GPIO37 interrupt direction.
#define AM_REG_GPIO_CFGE_GPIO37INTD_S                23
#define AM_REG_GPIO_CFGE_GPIO37INTD_M                0x00800000
#define AM_REG_GPIO_CFGE_GPIO37INTD(n)               (((uint32_t)(n) << 23) & 0x00800000)
#define AM_REG_GPIO_CFGE_GPIO37INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGE_GPIO37INTD_INTHL            0x00800000

// GPIO37 output configuration.
#define AM_REG_GPIO_CFGE_GPIO37OUTCFG_S              21
#define AM_REG_GPIO_CFGE_GPIO37OUTCFG_M              0x00600000
#define AM_REG_GPIO_CFGE_GPIO37OUTCFG(n)             (((uint32_t)(n) << 21) & 0x00600000)
#define AM_REG_GPIO_CFGE_GPIO37OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGE_GPIO37OUTCFG_PUSHPULL       0x00200000
#define AM_REG_GPIO_CFGE_GPIO37OUTCFG_OD             0x00400000
#define AM_REG_GPIO_CFGE_GPIO37OUTCFG_TS             0x00600000

// GPIO37 input enable.
#define AM_REG_GPIO_CFGE_GPIO37INCFG_S               20
#define AM_REG_GPIO_CFGE_GPIO37INCFG_M               0x00100000
#define AM_REG_GPIO_CFGE_GPIO37INCFG(n)              (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_CFGE_GPIO37INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGE_GPIO37INCFG_RDZERO          0x00100000

// GPIO36 interrupt direction.
#define AM_REG_GPIO_CFGE_GPIO36INTD_S                19
#define AM_REG_GPIO_CFGE_GPIO36INTD_M                0x00080000
#define AM_REG_GPIO_CFGE_GPIO36INTD(n)               (((uint32_t)(n) << 19) & 0x00080000)
#define AM_REG_GPIO_CFGE_GPIO36INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGE_GPIO36INTD_INTHL            0x00080000

// GPIO36 output configuration.
#define AM_REG_GPIO_CFGE_GPIO36OUTCFG_S              17
#define AM_REG_GPIO_CFGE_GPIO36OUTCFG_M              0x00060000
#define AM_REG_GPIO_CFGE_GPIO36OUTCFG(n)             (((uint32_t)(n) << 17) & 0x00060000)
#define AM_REG_GPIO_CFGE_GPIO36OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGE_GPIO36OUTCFG_PUSHPULL       0x00020000
#define AM_REG_GPIO_CFGE_GPIO36OUTCFG_OD             0x00040000
#define AM_REG_GPIO_CFGE_GPIO36OUTCFG_TS             0x00060000

// GPIO36 input enable.
#define AM_REG_GPIO_CFGE_GPIO36INCFG_S               16
#define AM_REG_GPIO_CFGE_GPIO36INCFG_M               0x00010000
#define AM_REG_GPIO_CFGE_GPIO36INCFG(n)              (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_CFGE_GPIO36INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGE_GPIO36INCFG_RDZERO          0x00010000

// GPIO35 interrupt direction.
#define AM_REG_GPIO_CFGE_GPIO35INTD_S                15
#define AM_REG_GPIO_CFGE_GPIO35INTD_M                0x00008000
#define AM_REG_GPIO_CFGE_GPIO35INTD(n)               (((uint32_t)(n) << 15) & 0x00008000)
#define AM_REG_GPIO_CFGE_GPIO35INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGE_GPIO35INTD_INTHL            0x00008000

// GPIO35 output configuration.
#define AM_REG_GPIO_CFGE_GPIO35OUTCFG_S              13
#define AM_REG_GPIO_CFGE_GPIO35OUTCFG_M              0x00006000
#define AM_REG_GPIO_CFGE_GPIO35OUTCFG(n)             (((uint32_t)(n) << 13) & 0x00006000)
#define AM_REG_GPIO_CFGE_GPIO35OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGE_GPIO35OUTCFG_PUSHPULL       0x00002000
#define AM_REG_GPIO_CFGE_GPIO35OUTCFG_OD             0x00004000
#define AM_REG_GPIO_CFGE_GPIO35OUTCFG_TS             0x00006000

// GPIO35 input enable.
#define AM_REG_GPIO_CFGE_GPIO35INCFG_S               12
#define AM_REG_GPIO_CFGE_GPIO35INCFG_M               0x00001000
#define AM_REG_GPIO_CFGE_GPIO35INCFG(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_CFGE_GPIO35INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGE_GPIO35INCFG_RDZERO          0x00001000

// GPIO34 interrupt direction.
#define AM_REG_GPIO_CFGE_GPIO34INTD_S                11
#define AM_REG_GPIO_CFGE_GPIO34INTD_M                0x00000800
#define AM_REG_GPIO_CFGE_GPIO34INTD(n)               (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_GPIO_CFGE_GPIO34INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGE_GPIO34INTD_INTHL            0x00000800

// GPIO34 output configuration.
#define AM_REG_GPIO_CFGE_GPIO34OUTCFG_S              9
#define AM_REG_GPIO_CFGE_GPIO34OUTCFG_M              0x00000600
#define AM_REG_GPIO_CFGE_GPIO34OUTCFG(n)             (((uint32_t)(n) << 9) & 0x00000600)
#define AM_REG_GPIO_CFGE_GPIO34OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGE_GPIO34OUTCFG_PUSHPULL       0x00000200
#define AM_REG_GPIO_CFGE_GPIO34OUTCFG_OD             0x00000400
#define AM_REG_GPIO_CFGE_GPIO34OUTCFG_TS             0x00000600

// GPIO34 input enable.
#define AM_REG_GPIO_CFGE_GPIO34INCFG_S               8
#define AM_REG_GPIO_CFGE_GPIO34INCFG_M               0x00000100
#define AM_REG_GPIO_CFGE_GPIO34INCFG(n)              (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_CFGE_GPIO34INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGE_GPIO34INCFG_RDZERO          0x00000100

// GPIO33 interrupt direction.
#define AM_REG_GPIO_CFGE_GPIO33INTD_S                7
#define AM_REG_GPIO_CFGE_GPIO33INTD_M                0x00000080
#define AM_REG_GPIO_CFGE_GPIO33INTD(n)               (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_GPIO_CFGE_GPIO33INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGE_GPIO33INTD_INTHL            0x00000080

// GPIO33 output configuration.
#define AM_REG_GPIO_CFGE_GPIO33OUTCFG_S              5
#define AM_REG_GPIO_CFGE_GPIO33OUTCFG_M              0x00000060
#define AM_REG_GPIO_CFGE_GPIO33OUTCFG(n)             (((uint32_t)(n) << 5) & 0x00000060)
#define AM_REG_GPIO_CFGE_GPIO33OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGE_GPIO33OUTCFG_PUSHPULL       0x00000020
#define AM_REG_GPIO_CFGE_GPIO33OUTCFG_OD             0x00000040
#define AM_REG_GPIO_CFGE_GPIO33OUTCFG_TS             0x00000060

// GPIO33 input enable.
#define AM_REG_GPIO_CFGE_GPIO33INCFG_S               4
#define AM_REG_GPIO_CFGE_GPIO33INCFG_M               0x00000010
#define AM_REG_GPIO_CFGE_GPIO33INCFG(n)              (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_CFGE_GPIO33INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGE_GPIO33INCFG_RDZERO          0x00000010

// GPIO32 interrupt direction.
#define AM_REG_GPIO_CFGE_GPIO32INTD_S                3
#define AM_REG_GPIO_CFGE_GPIO32INTD_M                0x00000008
#define AM_REG_GPIO_CFGE_GPIO32INTD(n)               (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_GPIO_CFGE_GPIO32INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGE_GPIO32INTD_INTHL            0x00000008

// GPIO32 output configuration.
#define AM_REG_GPIO_CFGE_GPIO32OUTCFG_S              1
#define AM_REG_GPIO_CFGE_GPIO32OUTCFG_M              0x00000006
#define AM_REG_GPIO_CFGE_GPIO32OUTCFG(n)             (((uint32_t)(n) << 1) & 0x00000006)
#define AM_REG_GPIO_CFGE_GPIO32OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGE_GPIO32OUTCFG_PUSHPULL       0x00000002
#define AM_REG_GPIO_CFGE_GPIO32OUTCFG_OD             0x00000004
#define AM_REG_GPIO_CFGE_GPIO32OUTCFG_TS             0x00000006

// GPIO32 input enable.
#define AM_REG_GPIO_CFGE_GPIO32INCFG_S               0
#define AM_REG_GPIO_CFGE_GPIO32INCFG_M               0x00000001
#define AM_REG_GPIO_CFGE_GPIO32INCFG(n)              (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_CFGE_GPIO32INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGE_GPIO32INCFG_RDZERO          0x00000001

//*****************************************************************************
//
// GPIO_CFGF - GPIO Configuration Register F
//
//*****************************************************************************
// GPIO47 interrupt direction.
#define AM_REG_GPIO_CFGF_GPIO47INTD_S                31
#define AM_REG_GPIO_CFGF_GPIO47INTD_M                0x80000000
#define AM_REG_GPIO_CFGF_GPIO47INTD(n)               (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_GPIO_CFGF_GPIO47INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGF_GPIO47INTD_INTHL            0x80000000

// GPIO47 output configuration.
#define AM_REG_GPIO_CFGF_GPIO47OUTCFG_S              29
#define AM_REG_GPIO_CFGF_GPIO47OUTCFG_M              0x60000000
#define AM_REG_GPIO_CFGF_GPIO47OUTCFG(n)             (((uint32_t)(n) << 29) & 0x60000000)
#define AM_REG_GPIO_CFGF_GPIO47OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGF_GPIO47OUTCFG_PUSHPULL       0x20000000
#define AM_REG_GPIO_CFGF_GPIO47OUTCFG_OD             0x40000000
#define AM_REG_GPIO_CFGF_GPIO47OUTCFG_TS             0x60000000

// GPIO47 input enable.
#define AM_REG_GPIO_CFGF_GPIO47INCFG_S               28
#define AM_REG_GPIO_CFGF_GPIO47INCFG_M               0x10000000
#define AM_REG_GPIO_CFGF_GPIO47INCFG(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_CFGF_GPIO47INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGF_GPIO47INCFG_RDZERO          0x10000000

// GPIO46 interrupt direction.
#define AM_REG_GPIO_CFGF_GPIO46INTD_S                27
#define AM_REG_GPIO_CFGF_GPIO46INTD_M                0x08000000
#define AM_REG_GPIO_CFGF_GPIO46INTD(n)               (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_GPIO_CFGF_GPIO46INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGF_GPIO46INTD_INTHL            0x08000000

// GPIO46 output configuration.
#define AM_REG_GPIO_CFGF_GPIO46OUTCFG_S              25
#define AM_REG_GPIO_CFGF_GPIO46OUTCFG_M              0x06000000
#define AM_REG_GPIO_CFGF_GPIO46OUTCFG(n)             (((uint32_t)(n) << 25) & 0x06000000)
#define AM_REG_GPIO_CFGF_GPIO46OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGF_GPIO46OUTCFG_PUSHPULL       0x02000000
#define AM_REG_GPIO_CFGF_GPIO46OUTCFG_OD             0x04000000
#define AM_REG_GPIO_CFGF_GPIO46OUTCFG_TS             0x06000000

// GPIO46 input enable.
#define AM_REG_GPIO_CFGF_GPIO46INCFG_S               24
#define AM_REG_GPIO_CFGF_GPIO46INCFG_M               0x01000000
#define AM_REG_GPIO_CFGF_GPIO46INCFG(n)              (((uint32_t)(n) << 24) & 0x01000000)
#define AM_REG_GPIO_CFGF_GPIO46INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGF_GPIO46INCFG_RDZERO          0x01000000

// GPIO45 interrupt direction.
#define AM_REG_GPIO_CFGF_GPIO45INTD_S                23
#define AM_REG_GPIO_CFGF_GPIO45INTD_M                0x00800000
#define AM_REG_GPIO_CFGF_GPIO45INTD(n)               (((uint32_t)(n) << 23) & 0x00800000)
#define AM_REG_GPIO_CFGF_GPIO45INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGF_GPIO45INTD_INTHL            0x00800000

// GPIO45 output configuration.
#define AM_REG_GPIO_CFGF_GPIO45OUTCFG_S              21
#define AM_REG_GPIO_CFGF_GPIO45OUTCFG_M              0x00600000
#define AM_REG_GPIO_CFGF_GPIO45OUTCFG(n)             (((uint32_t)(n) << 21) & 0x00600000)
#define AM_REG_GPIO_CFGF_GPIO45OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGF_GPIO45OUTCFG_PUSHPULL       0x00200000
#define AM_REG_GPIO_CFGF_GPIO45OUTCFG_OD             0x00400000
#define AM_REG_GPIO_CFGF_GPIO45OUTCFG_TS             0x00600000

// GPIO45 input enable.
#define AM_REG_GPIO_CFGF_GPIO45INCFG_S               20
#define AM_REG_GPIO_CFGF_GPIO45INCFG_M               0x00100000
#define AM_REG_GPIO_CFGF_GPIO45INCFG(n)              (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_CFGF_GPIO45INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGF_GPIO45INCFG_RDZERO          0x00100000

// GPIO44 interrupt direction.
#define AM_REG_GPIO_CFGF_GPIO44INTD_S                19
#define AM_REG_GPIO_CFGF_GPIO44INTD_M                0x00080000
#define AM_REG_GPIO_CFGF_GPIO44INTD(n)               (((uint32_t)(n) << 19) & 0x00080000)
#define AM_REG_GPIO_CFGF_GPIO44INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGF_GPIO44INTD_INTHL            0x00080000

// GPIO44 output configuration.
#define AM_REG_GPIO_CFGF_GPIO44OUTCFG_S              17
#define AM_REG_GPIO_CFGF_GPIO44OUTCFG_M              0x00060000
#define AM_REG_GPIO_CFGF_GPIO44OUTCFG(n)             (((uint32_t)(n) << 17) & 0x00060000)
#define AM_REG_GPIO_CFGF_GPIO44OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGF_GPIO44OUTCFG_PUSHPULL       0x00020000
#define AM_REG_GPIO_CFGF_GPIO44OUTCFG_OD             0x00040000
#define AM_REG_GPIO_CFGF_GPIO44OUTCFG_TS             0x00060000

// GPIO44 input enable.
#define AM_REG_GPIO_CFGF_GPIO44INCFG_S               16
#define AM_REG_GPIO_CFGF_GPIO44INCFG_M               0x00010000
#define AM_REG_GPIO_CFGF_GPIO44INCFG(n)              (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_GPIO_CFGF_GPIO44INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGF_GPIO44INCFG_RDZERO          0x00010000

// GPIO43 interrupt direction.
#define AM_REG_GPIO_CFGF_GPIO43INTD_S                15
#define AM_REG_GPIO_CFGF_GPIO43INTD_M                0x00008000
#define AM_REG_GPIO_CFGF_GPIO43INTD(n)               (((uint32_t)(n) << 15) & 0x00008000)
#define AM_REG_GPIO_CFGF_GPIO43INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGF_GPIO43INTD_INTHL            0x00008000

// GPIO43 output configuration.
#define AM_REG_GPIO_CFGF_GPIO43OUTCFG_S              13
#define AM_REG_GPIO_CFGF_GPIO43OUTCFG_M              0x00006000
#define AM_REG_GPIO_CFGF_GPIO43OUTCFG(n)             (((uint32_t)(n) << 13) & 0x00006000)
#define AM_REG_GPIO_CFGF_GPIO43OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGF_GPIO43OUTCFG_PUSHPULL       0x00002000
#define AM_REG_GPIO_CFGF_GPIO43OUTCFG_OD             0x00004000
#define AM_REG_GPIO_CFGF_GPIO43OUTCFG_TS             0x00006000

// GPIO43 input enable.
#define AM_REG_GPIO_CFGF_GPIO43INCFG_S               12
#define AM_REG_GPIO_CFGF_GPIO43INCFG_M               0x00001000
#define AM_REG_GPIO_CFGF_GPIO43INCFG(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_CFGF_GPIO43INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGF_GPIO43INCFG_RDZERO          0x00001000

// GPIO42 interrupt direction.
#define AM_REG_GPIO_CFGF_GPIO42INTD_S                11
#define AM_REG_GPIO_CFGF_GPIO42INTD_M                0x00000800
#define AM_REG_GPIO_CFGF_GPIO42INTD(n)               (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_GPIO_CFGF_GPIO42INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGF_GPIO42INTD_INTHL            0x00000800

// GPIO42 output configuration.
#define AM_REG_GPIO_CFGF_GPIO42OUTCFG_S              9
#define AM_REG_GPIO_CFGF_GPIO42OUTCFG_M              0x00000600
#define AM_REG_GPIO_CFGF_GPIO42OUTCFG(n)             (((uint32_t)(n) << 9) & 0x00000600)
#define AM_REG_GPIO_CFGF_GPIO42OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGF_GPIO42OUTCFG_PUSHPULL       0x00000200
#define AM_REG_GPIO_CFGF_GPIO42OUTCFG_OD             0x00000400
#define AM_REG_GPIO_CFGF_GPIO42OUTCFG_TS             0x00000600

// GPIO42 input enable.
#define AM_REG_GPIO_CFGF_GPIO42INCFG_S               8
#define AM_REG_GPIO_CFGF_GPIO42INCFG_M               0x00000100
#define AM_REG_GPIO_CFGF_GPIO42INCFG(n)              (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_GPIO_CFGF_GPIO42INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGF_GPIO42INCFG_RDZERO          0x00000100

// GPIO41 interrupt direction.
#define AM_REG_GPIO_CFGF_GPIO41INTD_S                7
#define AM_REG_GPIO_CFGF_GPIO41INTD_M                0x00000080
#define AM_REG_GPIO_CFGF_GPIO41INTD(n)               (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_GPIO_CFGF_GPIO41INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGF_GPIO41INTD_INTHL            0x00000080

// GPIO41 output configuration.
#define AM_REG_GPIO_CFGF_GPIO41OUTCFG_S              5
#define AM_REG_GPIO_CFGF_GPIO41OUTCFG_M              0x00000060
#define AM_REG_GPIO_CFGF_GPIO41OUTCFG(n)             (((uint32_t)(n) << 5) & 0x00000060)
#define AM_REG_GPIO_CFGF_GPIO41OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGF_GPIO41OUTCFG_PUSHPULL       0x00000020
#define AM_REG_GPIO_CFGF_GPIO41OUTCFG_OD             0x00000040
#define AM_REG_GPIO_CFGF_GPIO41OUTCFG_TS             0x00000060

// GPIO41 input enable.
#define AM_REG_GPIO_CFGF_GPIO41INCFG_S               4
#define AM_REG_GPIO_CFGF_GPIO41INCFG_M               0x00000010
#define AM_REG_GPIO_CFGF_GPIO41INCFG(n)              (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_CFGF_GPIO41INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGF_GPIO41INCFG_RDZERO          0x00000010

// GPIO40 interrupt direction.
#define AM_REG_GPIO_CFGF_GPIO40INTD_S                3
#define AM_REG_GPIO_CFGF_GPIO40INTD_M                0x00000008
#define AM_REG_GPIO_CFGF_GPIO40INTD(n)               (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_GPIO_CFGF_GPIO40INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGF_GPIO40INTD_INTHL            0x00000008

// GPIO40 output configuration.
#define AM_REG_GPIO_CFGF_GPIO40OUTCFG_S              1
#define AM_REG_GPIO_CFGF_GPIO40OUTCFG_M              0x00000006
#define AM_REG_GPIO_CFGF_GPIO40OUTCFG(n)             (((uint32_t)(n) << 1) & 0x00000006)
#define AM_REG_GPIO_CFGF_GPIO40OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGF_GPIO40OUTCFG_PUSHPULL       0x00000002
#define AM_REG_GPIO_CFGF_GPIO40OUTCFG_OD             0x00000004
#define AM_REG_GPIO_CFGF_GPIO40OUTCFG_TS             0x00000006

// GPIO40 input enable.
#define AM_REG_GPIO_CFGF_GPIO40INCFG_S               0
#define AM_REG_GPIO_CFGF_GPIO40INCFG_M               0x00000001
#define AM_REG_GPIO_CFGF_GPIO40INCFG(n)              (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_CFGF_GPIO40INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGF_GPIO40INCFG_RDZERO          0x00000001

//*****************************************************************************
//
// GPIO_CFGG - GPIO Configuration Register G
//
//*****************************************************************************
// GPIO49 interrupt direction.
#define AM_REG_GPIO_CFGG_GPIO49INTD_S                7
#define AM_REG_GPIO_CFGG_GPIO49INTD_M                0x00000080
#define AM_REG_GPIO_CFGG_GPIO49INTD(n)               (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_GPIO_CFGG_GPIO49INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGG_GPIO49INTD_INTHL            0x00000080

// GPIO49 output configuration.
#define AM_REG_GPIO_CFGG_GPIO49OUTCFG_S              5
#define AM_REG_GPIO_CFGG_GPIO49OUTCFG_M              0x00000060
#define AM_REG_GPIO_CFGG_GPIO49OUTCFG(n)             (((uint32_t)(n) << 5) & 0x00000060)
#define AM_REG_GPIO_CFGG_GPIO49OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGG_GPIO49OUTCFG_PUSHPULL       0x00000020
#define AM_REG_GPIO_CFGG_GPIO49OUTCFG_OD             0x00000040
#define AM_REG_GPIO_CFGG_GPIO49OUTCFG_TS             0x00000060

// GPIO49 input enable.
#define AM_REG_GPIO_CFGG_GPIO49INCFG_S               4
#define AM_REG_GPIO_CFGG_GPIO49INCFG_M               0x00000010
#define AM_REG_GPIO_CFGG_GPIO49INCFG(n)              (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_CFGG_GPIO49INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGG_GPIO49INCFG_RDZERO          0x00000010

// GPIO48 interrupt direction.
#define AM_REG_GPIO_CFGG_GPIO48INTD_S                3
#define AM_REG_GPIO_CFGG_GPIO48INTD_M                0x00000008
#define AM_REG_GPIO_CFGG_GPIO48INTD(n)               (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_GPIO_CFGG_GPIO48INTD_INTLH            0x00000000
#define AM_REG_GPIO_CFGG_GPIO48INTD_INTHL            0x00000008

// GPIO48 output configuration.
#define AM_REG_GPIO_CFGG_GPIO48OUTCFG_S              1
#define AM_REG_GPIO_CFGG_GPIO48OUTCFG_M              0x00000006
#define AM_REG_GPIO_CFGG_GPIO48OUTCFG(n)             (((uint32_t)(n) << 1) & 0x00000006)
#define AM_REG_GPIO_CFGG_GPIO48OUTCFG_DIS            0x00000000
#define AM_REG_GPIO_CFGG_GPIO48OUTCFG_PUSHPULL       0x00000002
#define AM_REG_GPIO_CFGG_GPIO48OUTCFG_OD             0x00000004
#define AM_REG_GPIO_CFGG_GPIO48OUTCFG_TS             0x00000006

// GPIO48 input enable.
#define AM_REG_GPIO_CFGG_GPIO48INCFG_S               0
#define AM_REG_GPIO_CFGG_GPIO48INCFG_M               0x00000001
#define AM_REG_GPIO_CFGG_GPIO48INCFG(n)              (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_GPIO_CFGG_GPIO48INCFG_READ            0x00000000
#define AM_REG_GPIO_CFGG_GPIO48INCFG_RDZERO          0x00000001

//*****************************************************************************
//
// GPIO_RDA - GPIO Input Register A
//
//*****************************************************************************
// GPIO31-0 read data.
#define AM_REG_GPIO_RDA_RDA_S                        0
#define AM_REG_GPIO_RDA_RDA_M                        0xFFFFFFFF
#define AM_REG_GPIO_RDA_RDA(n)                       (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// GPIO_RDB - GPIO Input Register B
//
//*****************************************************************************
// GPIO49-32 read data.
#define AM_REG_GPIO_RDB_RDB_S                        0
#define AM_REG_GPIO_RDB_RDB_M                        0x0003FFFF
#define AM_REG_GPIO_RDB_RDB(n)                       (((uint32_t)(n) << 0) & 0x0003FFFF)

//*****************************************************************************
//
// GPIO_WTA - GPIO Output Register A
//
//*****************************************************************************
// GPIO31-0 write data.
#define AM_REG_GPIO_WTA_WTA_S                        0
#define AM_REG_GPIO_WTA_WTA_M                        0xFFFFFFFF
#define AM_REG_GPIO_WTA_WTA(n)                       (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// GPIO_WTB - GPIO Output Register B
//
//*****************************************************************************
// GPIO49-32 write data.
#define AM_REG_GPIO_WTB_WTB_S                        0
#define AM_REG_GPIO_WTB_WTB_M                        0x0003FFFF
#define AM_REG_GPIO_WTB_WTB(n)                       (((uint32_t)(n) << 0) & 0x0003FFFF)

//*****************************************************************************
//
// GPIO_WTSA - GPIO Output Register A Set
//
//*****************************************************************************
// Set the GPIO31-0 write data.
#define AM_REG_GPIO_WTSA_WTSA_S                      0
#define AM_REG_GPIO_WTSA_WTSA_M                      0xFFFFFFFF
#define AM_REG_GPIO_WTSA_WTSA(n)                     (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// GPIO_WTSB - GPIO Output Register B Set
//
//*****************************************************************************
// Set the GPIO49-32 write data.
#define AM_REG_GPIO_WTSB_WTSB_S                      0
#define AM_REG_GPIO_WTSB_WTSB_M                      0x0003FFFF
#define AM_REG_GPIO_WTSB_WTSB(n)                     (((uint32_t)(n) << 0) & 0x0003FFFF)

//*****************************************************************************
//
// GPIO_WTCA - GPIO Output Register A Clear
//
//*****************************************************************************
// Clear the GPIO31-0 write data.
#define AM_REG_GPIO_WTCA_WTCA_S                      0
#define AM_REG_GPIO_WTCA_WTCA_M                      0xFFFFFFFF
#define AM_REG_GPIO_WTCA_WTCA(n)                     (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// GPIO_WTCB - GPIO Output Register B Clear
//
//*****************************************************************************
// Clear the GPIO49-32 write data.
#define AM_REG_GPIO_WTCB_WTCB_S                      0
#define AM_REG_GPIO_WTCB_WTCB_M                      0x0003FFFF
#define AM_REG_GPIO_WTCB_WTCB(n)                     (((uint32_t)(n) << 0) & 0x0003FFFF)

//*****************************************************************************
//
// GPIO_ENA - GPIO Enable Register A
//
//*****************************************************************************
// GPIO31-0 output enables
#define AM_REG_GPIO_ENA_ENA_S                        0
#define AM_REG_GPIO_ENA_ENA_M                        0xFFFFFFFF
#define AM_REG_GPIO_ENA_ENA(n)                       (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// GPIO_ENB - GPIO Enable Register B
//
//*****************************************************************************
// GPIO49-32 output enables
#define AM_REG_GPIO_ENB_ENB_S                        0
#define AM_REG_GPIO_ENB_ENB_M                        0x0003FFFF
#define AM_REG_GPIO_ENB_ENB(n)                       (((uint32_t)(n) << 0) & 0x0003FFFF)

//*****************************************************************************
//
// GPIO_ENSA - GPIO Enable Register A Set
//
//*****************************************************************************
// Set the GPIO31-0 output enables
#define AM_REG_GPIO_ENSA_ENSA_S                      0
#define AM_REG_GPIO_ENSA_ENSA_M                      0xFFFFFFFF
#define AM_REG_GPIO_ENSA_ENSA(n)                     (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// GPIO_ENSB - GPIO Enable Register B Set
//
//*****************************************************************************
// Set the GPIO49-32 output enables
#define AM_REG_GPIO_ENSB_ENSB_S                      0
#define AM_REG_GPIO_ENSB_ENSB_M                      0x0003FFFF
#define AM_REG_GPIO_ENSB_ENSB(n)                     (((uint32_t)(n) << 0) & 0x0003FFFF)

//*****************************************************************************
//
// GPIO_ENCA - GPIO Enable Register A Clear
//
//*****************************************************************************
// Clear the GPIO31-0 output enables
#define AM_REG_GPIO_ENCA_ENCA_S                      0
#define AM_REG_GPIO_ENCA_ENCA_M                      0xFFFFFFFF
#define AM_REG_GPIO_ENCA_ENCA(n)                     (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// GPIO_ENCB - GPIO Enable Register B Clear
//
//*****************************************************************************
// Clear the GPIO49-32 output enables
#define AM_REG_GPIO_ENCB_ENCB_S                      0
#define AM_REG_GPIO_ENCB_ENCB_M                      0x0003FFFF
#define AM_REG_GPIO_ENCB_ENCB(n)                     (((uint32_t)(n) << 0) & 0x0003FFFF)

//*****************************************************************************
//
// GPIO_STMRCAP - STIMER Capture Control
//
//*****************************************************************************
// STIMER Capture 3 Polarity.
#define AM_REG_GPIO_STMRCAP_STPOL3_S                 30
#define AM_REG_GPIO_STMRCAP_STPOL3_M                 0x40000000
#define AM_REG_GPIO_STMRCAP_STPOL3(n)                (((uint32_t)(n) << 30) & 0x40000000)
#define AM_REG_GPIO_STMRCAP_STPOL3_CAPLH             0x00000000
#define AM_REG_GPIO_STMRCAP_STPOL3_CAPHL             0x40000000

// STIMER Capture 3 Select.
#define AM_REG_GPIO_STMRCAP_STSEL3_S                 24
#define AM_REG_GPIO_STMRCAP_STSEL3_M                 0x3F000000
#define AM_REG_GPIO_STMRCAP_STSEL3(n)                (((uint32_t)(n) << 24) & 0x3F000000)

// STIMER Capture 2 Polarity.
#define AM_REG_GPIO_STMRCAP_STPOL2_S                 22
#define AM_REG_GPIO_STMRCAP_STPOL2_M                 0x00400000
#define AM_REG_GPIO_STMRCAP_STPOL2(n)                (((uint32_t)(n) << 22) & 0x00400000)
#define AM_REG_GPIO_STMRCAP_STPOL2_CAPLH             0x00000000
#define AM_REG_GPIO_STMRCAP_STPOL2_CAPHL             0x00400000

// STIMER Capture 2 Select.
#define AM_REG_GPIO_STMRCAP_STSEL2_S                 16
#define AM_REG_GPIO_STMRCAP_STSEL2_M                 0x003F0000
#define AM_REG_GPIO_STMRCAP_STSEL2(n)                (((uint32_t)(n) << 16) & 0x003F0000)

// STIMER Capture 1 Polarity.
#define AM_REG_GPIO_STMRCAP_STPOL1_S                 14
#define AM_REG_GPIO_STMRCAP_STPOL1_M                 0x00004000
#define AM_REG_GPIO_STMRCAP_STPOL1(n)                (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_GPIO_STMRCAP_STPOL1_CAPLH             0x00000000
#define AM_REG_GPIO_STMRCAP_STPOL1_CAPHL             0x00004000

// STIMER Capture 1 Select.
#define AM_REG_GPIO_STMRCAP_STSEL1_S                 8
#define AM_REG_GPIO_STMRCAP_STSEL1_M                 0x00003F00
#define AM_REG_GPIO_STMRCAP_STSEL1(n)                (((uint32_t)(n) << 8) & 0x00003F00)

// STIMER Capture 0 Polarity.
#define AM_REG_GPIO_STMRCAP_STPOL0_S                 6
#define AM_REG_GPIO_STMRCAP_STPOL0_M                 0x00000040
#define AM_REG_GPIO_STMRCAP_STPOL0(n)                (((uint32_t)(n) << 6) & 0x00000040)
#define AM_REG_GPIO_STMRCAP_STPOL0_CAPLH             0x00000000
#define AM_REG_GPIO_STMRCAP_STPOL0_CAPHL             0x00000040

// STIMER Capture 0 Select.
#define AM_REG_GPIO_STMRCAP_STSEL0_S                 0
#define AM_REG_GPIO_STMRCAP_STSEL0_M                 0x0000003F
#define AM_REG_GPIO_STMRCAP_STSEL0(n)                (((uint32_t)(n) << 0) & 0x0000003F)

//*****************************************************************************
//
// GPIO_IOM0IRQ - IOM0 Flow Control IRQ Select
//
//*****************************************************************************
// IOMSTR0 IRQ pad select.
#define AM_REG_GPIO_IOM0IRQ_IOM0IRQ_S                0
#define AM_REG_GPIO_IOM0IRQ_IOM0IRQ_M                0x0000003F
#define AM_REG_GPIO_IOM0IRQ_IOM0IRQ(n)               (((uint32_t)(n) << 0) & 0x0000003F)

//*****************************************************************************
//
// GPIO_IOM1IRQ - IOM1 Flow Control IRQ Select
//
//*****************************************************************************
// IOMSTR1 IRQ pad select.
#define AM_REG_GPIO_IOM1IRQ_IOM1IRQ_S                0
#define AM_REG_GPIO_IOM1IRQ_IOM1IRQ_M                0x0000003F
#define AM_REG_GPIO_IOM1IRQ_IOM1IRQ(n)               (((uint32_t)(n) << 0) & 0x0000003F)

//*****************************************************************************
//
// GPIO_IOM2IRQ - IOM2 Flow Control IRQ Select
//
//*****************************************************************************
// IOMSTR2 IRQ pad select.
#define AM_REG_GPIO_IOM2IRQ_IOM2IRQ_S                0
#define AM_REG_GPIO_IOM2IRQ_IOM2IRQ_M                0x0000003F
#define AM_REG_GPIO_IOM2IRQ_IOM2IRQ(n)               (((uint32_t)(n) << 0) & 0x0000003F)

//*****************************************************************************
//
// GPIO_IOM3IRQ - IOM3 Flow Control IRQ Select
//
//*****************************************************************************
// IOMSTR3 IRQ pad select.
#define AM_REG_GPIO_IOM3IRQ_IOM3IRQ_S                0
#define AM_REG_GPIO_IOM3IRQ_IOM3IRQ_M                0x0000003F
#define AM_REG_GPIO_IOM3IRQ_IOM3IRQ(n)               (((uint32_t)(n) << 0) & 0x0000003F)

//*****************************************************************************
//
// GPIO_IOM4IRQ - IOM4 Flow Control IRQ Select
//
//*****************************************************************************
// IOMSTR4 IRQ pad select.
#define AM_REG_GPIO_IOM4IRQ_IOM4IRQ_S                0
#define AM_REG_GPIO_IOM4IRQ_IOM4IRQ_M                0x0000003F
#define AM_REG_GPIO_IOM4IRQ_IOM4IRQ(n)               (((uint32_t)(n) << 0) & 0x0000003F)

//*****************************************************************************
//
// GPIO_IOM5IRQ - IOM5 Flow Control IRQ Select
//
//*****************************************************************************
// IOMSTR5 IRQ pad select.
#define AM_REG_GPIO_IOM5IRQ_IOM5IRQ_S                0
#define AM_REG_GPIO_IOM5IRQ_IOM5IRQ_M                0x0000003F
#define AM_REG_GPIO_IOM5IRQ_IOM5IRQ(n)               (((uint32_t)(n) << 0) & 0x0000003F)

//*****************************************************************************
//
// GPIO_LOOPBACK - IOM to IOS Loopback Control
//
//*****************************************************************************
// IOM to IOS loopback control.
#define AM_REG_GPIO_LOOPBACK_LOOPBACK_S              0
#define AM_REG_GPIO_LOOPBACK_LOOPBACK_M              0x00000007
#define AM_REG_GPIO_LOOPBACK_LOOPBACK(n)             (((uint32_t)(n) << 0) & 0x00000007)
#define AM_REG_GPIO_LOOPBACK_LOOPBACK_LOOP0          0x00000000
#define AM_REG_GPIO_LOOPBACK_LOOPBACK_LOOP1          0x00000001
#define AM_REG_GPIO_LOOPBACK_LOOPBACK_LOOP2          0x00000002
#define AM_REG_GPIO_LOOPBACK_LOOPBACK_LOOP3          0x00000003
#define AM_REG_GPIO_LOOPBACK_LOOPBACK_LOOP4          0x00000004
#define AM_REG_GPIO_LOOPBACK_LOOPBACK_LOOP5          0x00000005
#define AM_REG_GPIO_LOOPBACK_LOOPBACK_LOOPNONE       0x00000006

//*****************************************************************************
//
// GPIO_GPIOOBS - GPIO Observation Mode Sample register
//
//*****************************************************************************
// Sample of the data output on the GPIO observation port.  May have async
// sampling issues, as the data is not synronized to the read operation.
// Intended for debug purposes only
#define AM_REG_GPIO_GPIOOBS_OBS_DATA_S               0
#define AM_REG_GPIO_GPIOOBS_OBS_DATA_M               0x0000FFFF
#define AM_REG_GPIO_GPIOOBS_OBS_DATA(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// GPIO_ALTPADCFGA - Alternate Pad Configuration reg0 (Pads 3,2,1,0)
//
//*****************************************************************************
// Pad 3 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGA_PAD3_SR_S             28
#define AM_REG_GPIO_ALTPADCFGA_PAD3_SR_M             0x10000000
#define AM_REG_GPIO_ALTPADCFGA_PAD3_SR(n)            (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_ALTPADCFGA_PAD3_SR_SR_EN         0x10000000

// Pad 3 high order drive strength selection.  Used in conjunction with
// PAD3STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGA_PAD3_DS1_S            24
#define AM_REG_GPIO_ALTPADCFGA_PAD3_DS1_M            0x01000000
#define AM_REG_GPIO_ALTPADCFGA_PAD3_DS1(n)           (((uint32_t)(n) << 24) & 0x01000000)

// Pad 2 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGA_PAD2_SR_S             20
#define AM_REG_GPIO_ALTPADCFGA_PAD2_SR_M             0x00100000
#define AM_REG_GPIO_ALTPADCFGA_PAD2_SR(n)            (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_ALTPADCFGA_PAD2_SR_SR_EN         0x00100000

// Pad 2 high order drive strength selection.  Used in conjunction with
// PAD2STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGA_PAD2_DS1_S            16
#define AM_REG_GPIO_ALTPADCFGA_PAD2_DS1_M            0x00010000
#define AM_REG_GPIO_ALTPADCFGA_PAD2_DS1(n)           (((uint32_t)(n) << 16) & 0x00010000)

// Pad 1 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGA_PAD1_SR_S             12
#define AM_REG_GPIO_ALTPADCFGA_PAD1_SR_M             0x00001000
#define AM_REG_GPIO_ALTPADCFGA_PAD1_SR(n)            (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_ALTPADCFGA_PAD1_SR_SR_EN         0x00001000

// Pad 1 high order drive strength selection.  Used in conjunction with
// PAD1STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGA_PAD1_DS1_S            8
#define AM_REG_GPIO_ALTPADCFGA_PAD1_DS1_M            0x00000100
#define AM_REG_GPIO_ALTPADCFGA_PAD1_DS1(n)           (((uint32_t)(n) << 8) & 0x00000100)

// Pad 0 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGA_PAD0_SR_S             4
#define AM_REG_GPIO_ALTPADCFGA_PAD0_SR_M             0x00000010
#define AM_REG_GPIO_ALTPADCFGA_PAD0_SR(n)            (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_ALTPADCFGA_PAD0_SR_SR_EN         0x00000010

// Pad 0 high order drive strength selection.  Used in conjunction with
// PAD0STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGA_PAD0_DS1_S            0
#define AM_REG_GPIO_ALTPADCFGA_PAD0_DS1_M            0x00000001
#define AM_REG_GPIO_ALTPADCFGA_PAD0_DS1(n)           (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_ALTPADCFGB - Alternate Pad Configuration reg1 (Pads 7,6,5,4)
//
//*****************************************************************************
// Pad 7 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGB_PAD7_SR_S             28
#define AM_REG_GPIO_ALTPADCFGB_PAD7_SR_M             0x10000000
#define AM_REG_GPIO_ALTPADCFGB_PAD7_SR(n)            (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_ALTPADCFGB_PAD7_SR_SR_EN         0x10000000

// Pad 7 high order drive strength selection.  Used in conjunction with
// PAD7STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGB_PAD7_DS1_S            24
#define AM_REG_GPIO_ALTPADCFGB_PAD7_DS1_M            0x01000000
#define AM_REG_GPIO_ALTPADCFGB_PAD7_DS1(n)           (((uint32_t)(n) << 24) & 0x01000000)

// Pad 6 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGB_PAD6_SR_S             20
#define AM_REG_GPIO_ALTPADCFGB_PAD6_SR_M             0x00100000
#define AM_REG_GPIO_ALTPADCFGB_PAD6_SR(n)            (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_ALTPADCFGB_PAD6_SR_SR_EN         0x00100000

// Pad 6 high order drive strength selection.  Used in conjunction with
// PAD6STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGB_PAD6_DS1_S            16
#define AM_REG_GPIO_ALTPADCFGB_PAD6_DS1_M            0x00010000
#define AM_REG_GPIO_ALTPADCFGB_PAD6_DS1(n)           (((uint32_t)(n) << 16) & 0x00010000)

// Pad 5 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGB_PAD5_SR_S             12
#define AM_REG_GPIO_ALTPADCFGB_PAD5_SR_M             0x00001000
#define AM_REG_GPIO_ALTPADCFGB_PAD5_SR(n)            (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_ALTPADCFGB_PAD5_SR_SR_EN         0x00001000

// Pad 5 high order drive strength selection.  Used in conjunction with
// PAD5STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGB_PAD5_DS1_S            8
#define AM_REG_GPIO_ALTPADCFGB_PAD5_DS1_M            0x00000100
#define AM_REG_GPIO_ALTPADCFGB_PAD5_DS1(n)           (((uint32_t)(n) << 8) & 0x00000100)

// Pad 4 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGB_PAD4_SR_S             4
#define AM_REG_GPIO_ALTPADCFGB_PAD4_SR_M             0x00000010
#define AM_REG_GPIO_ALTPADCFGB_PAD4_SR(n)            (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_ALTPADCFGB_PAD4_SR_SR_EN         0x00000010

// Pad 4 high order drive strength selection.  Used in conjunction with
// PAD4STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGB_PAD4_DS1_S            0
#define AM_REG_GPIO_ALTPADCFGB_PAD4_DS1_M            0x00000001
#define AM_REG_GPIO_ALTPADCFGB_PAD4_DS1(n)           (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_ALTPADCFGC - Alternate Pad Configuration reg2 (Pads 11,10,9,8)
//
//*****************************************************************************
// Pad 11 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGC_PAD11_SR_S            28
#define AM_REG_GPIO_ALTPADCFGC_PAD11_SR_M            0x10000000
#define AM_REG_GPIO_ALTPADCFGC_PAD11_SR(n)           (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_ALTPADCFGC_PAD11_SR_SR_EN        0x10000000

// Pad 11 high order drive strength selection.  Used in conjunction with
// PAD11STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGC_PAD11_DS1_S           24
#define AM_REG_GPIO_ALTPADCFGC_PAD11_DS1_M           0x01000000
#define AM_REG_GPIO_ALTPADCFGC_PAD11_DS1(n)          (((uint32_t)(n) << 24) & 0x01000000)

// Pad 10 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGC_PAD10_SR_S            20
#define AM_REG_GPIO_ALTPADCFGC_PAD10_SR_M            0x00100000
#define AM_REG_GPIO_ALTPADCFGC_PAD10_SR(n)           (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_ALTPADCFGC_PAD10_SR_SR_EN        0x00100000

// Pad 10 high order drive strength selection.  Used in conjunction with
// PAD10STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGC_PAD10_DS1_S           16
#define AM_REG_GPIO_ALTPADCFGC_PAD10_DS1_M           0x00010000
#define AM_REG_GPIO_ALTPADCFGC_PAD10_DS1(n)          (((uint32_t)(n) << 16) & 0x00010000)

// Pad 9 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGC_PAD9_SR_S             12
#define AM_REG_GPIO_ALTPADCFGC_PAD9_SR_M             0x00001000
#define AM_REG_GPIO_ALTPADCFGC_PAD9_SR(n)            (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_ALTPADCFGC_PAD9_SR_SR_EN         0x00001000

// Pad 9 high order drive strength selection.  Used in conjunction with
// PAD9STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGC_PAD9_DS1_S            8
#define AM_REG_GPIO_ALTPADCFGC_PAD9_DS1_M            0x00000100
#define AM_REG_GPIO_ALTPADCFGC_PAD9_DS1(n)           (((uint32_t)(n) << 8) & 0x00000100)

// Pad 8 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGC_PAD8_SR_S             4
#define AM_REG_GPIO_ALTPADCFGC_PAD8_SR_M             0x00000010
#define AM_REG_GPIO_ALTPADCFGC_PAD8_SR(n)            (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_ALTPADCFGC_PAD8_SR_SR_EN         0x00000010

// Pad 8 high order drive strength selection.  Used in conjunction with
// PAD8STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGC_PAD8_DS1_S            0
#define AM_REG_GPIO_ALTPADCFGC_PAD8_DS1_M            0x00000001
#define AM_REG_GPIO_ALTPADCFGC_PAD8_DS1(n)           (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_ALTPADCFGD - Alternate Pad Configuration reg3 (Pads 15,14,13,12)
//
//*****************************************************************************
// Pad 15 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGD_PAD15_SR_S            28
#define AM_REG_GPIO_ALTPADCFGD_PAD15_SR_M            0x10000000
#define AM_REG_GPIO_ALTPADCFGD_PAD15_SR(n)           (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_ALTPADCFGD_PAD15_SR_SR_EN        0x10000000

// Pad 15 high order drive strength selection.  Used in conjunction with
// PAD15STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGD_PAD15_DS1_S           24
#define AM_REG_GPIO_ALTPADCFGD_PAD15_DS1_M           0x01000000
#define AM_REG_GPIO_ALTPADCFGD_PAD15_DS1(n)          (((uint32_t)(n) << 24) & 0x01000000)

// Pad 14 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGD_PAD14_SR_S            20
#define AM_REG_GPIO_ALTPADCFGD_PAD14_SR_M            0x00100000
#define AM_REG_GPIO_ALTPADCFGD_PAD14_SR(n)           (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_ALTPADCFGD_PAD14_SR_SR_EN        0x00100000

// Pad 14 high order drive strength selection.  Used in conjunction with
// PAD14STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGD_PAD14_DS1_S           16
#define AM_REG_GPIO_ALTPADCFGD_PAD14_DS1_M           0x00010000
#define AM_REG_GPIO_ALTPADCFGD_PAD14_DS1(n)          (((uint32_t)(n) << 16) & 0x00010000)

// Pad 13 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGD_PAD13_SR_S            12
#define AM_REG_GPIO_ALTPADCFGD_PAD13_SR_M            0x00001000
#define AM_REG_GPIO_ALTPADCFGD_PAD13_SR(n)           (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_ALTPADCFGD_PAD13_SR_SR_EN        0x00001000

// Pad 13 high order drive strength selection.  Used in conjunction with
// PAD13STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGD_PAD13_DS1_S           8
#define AM_REG_GPIO_ALTPADCFGD_PAD13_DS1_M           0x00000100
#define AM_REG_GPIO_ALTPADCFGD_PAD13_DS1(n)          (((uint32_t)(n) << 8) & 0x00000100)

// Pad 12 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGD_PAD12_SR_S            4
#define AM_REG_GPIO_ALTPADCFGD_PAD12_SR_M            0x00000010
#define AM_REG_GPIO_ALTPADCFGD_PAD12_SR(n)           (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_ALTPADCFGD_PAD12_SR_SR_EN        0x00000010

// Pad 12 high order drive strength selection.  Used in conjunction with
// PAD12STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGD_PAD12_DS1_S           0
#define AM_REG_GPIO_ALTPADCFGD_PAD12_DS1_M           0x00000001
#define AM_REG_GPIO_ALTPADCFGD_PAD12_DS1(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_ALTPADCFGE - Alternate Pad Configuration reg4 (Pads 19,18,17,16)
//
//*****************************************************************************
// Pad 19 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGE_PAD19_SR_S            28
#define AM_REG_GPIO_ALTPADCFGE_PAD19_SR_M            0x10000000
#define AM_REG_GPIO_ALTPADCFGE_PAD19_SR(n)           (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_ALTPADCFGE_PAD19_SR_SR_EN        0x10000000

// Pad 19 high order drive strength selection.  Used in conjunction with
// PAD19STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGE_PAD19_DS1_S           24
#define AM_REG_GPIO_ALTPADCFGE_PAD19_DS1_M           0x01000000
#define AM_REG_GPIO_ALTPADCFGE_PAD19_DS1(n)          (((uint32_t)(n) << 24) & 0x01000000)

// Pad 18 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGE_PAD18_SR_S            20
#define AM_REG_GPIO_ALTPADCFGE_PAD18_SR_M            0x00100000
#define AM_REG_GPIO_ALTPADCFGE_PAD18_SR(n)           (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_ALTPADCFGE_PAD18_SR_SR_EN        0x00100000

// Pad 18 high order drive strength selection.  Used in conjunction with
// PAD18STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGE_PAD18_DS1_S           16
#define AM_REG_GPIO_ALTPADCFGE_PAD18_DS1_M           0x00010000
#define AM_REG_GPIO_ALTPADCFGE_PAD18_DS1(n)          (((uint32_t)(n) << 16) & 0x00010000)

// Pad 17 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGE_PAD17_SR_S            12
#define AM_REG_GPIO_ALTPADCFGE_PAD17_SR_M            0x00001000
#define AM_REG_GPIO_ALTPADCFGE_PAD17_SR(n)           (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_ALTPADCFGE_PAD17_SR_SR_EN        0x00001000

// Pad 17 high order drive strength selection.  Used in conjunction with
// PAD17STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGE_PAD17_DS1_S           8
#define AM_REG_GPIO_ALTPADCFGE_PAD17_DS1_M           0x00000100
#define AM_REG_GPIO_ALTPADCFGE_PAD17_DS1(n)          (((uint32_t)(n) << 8) & 0x00000100)

// Pad 16 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGE_PAD16_SR_S            4
#define AM_REG_GPIO_ALTPADCFGE_PAD16_SR_M            0x00000010
#define AM_REG_GPIO_ALTPADCFGE_PAD16_SR(n)           (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_ALTPADCFGE_PAD16_SR_SR_EN        0x00000010

// Pad 16 high order drive strength selection.  Used in conjunction with
// PAD16STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGE_PAD16_DS1_S           0
#define AM_REG_GPIO_ALTPADCFGE_PAD16_DS1_M           0x00000001
#define AM_REG_GPIO_ALTPADCFGE_PAD16_DS1(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_ALTPADCFGF - Alternate Pad Configuration reg5 (Pads 23,22,21,20)
//
//*****************************************************************************
// Pad 23 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGF_PAD23_SR_S            28
#define AM_REG_GPIO_ALTPADCFGF_PAD23_SR_M            0x10000000
#define AM_REG_GPIO_ALTPADCFGF_PAD23_SR(n)           (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_ALTPADCFGF_PAD23_SR_SR_EN        0x10000000

// Pad 23 high order drive strength selection.  Used in conjunction with
// PAD23STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGF_PAD23_DS1_S           24
#define AM_REG_GPIO_ALTPADCFGF_PAD23_DS1_M           0x01000000
#define AM_REG_GPIO_ALTPADCFGF_PAD23_DS1(n)          (((uint32_t)(n) << 24) & 0x01000000)

// Pad 22 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGF_PAD22_SR_S            20
#define AM_REG_GPIO_ALTPADCFGF_PAD22_SR_M            0x00100000
#define AM_REG_GPIO_ALTPADCFGF_PAD22_SR(n)           (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_ALTPADCFGF_PAD22_SR_SR_EN        0x00100000

// Pad 22 high order drive strength selection.  Used in conjunction with
// PAD22STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGF_PAD22_DS1_S           16
#define AM_REG_GPIO_ALTPADCFGF_PAD22_DS1_M           0x00010000
#define AM_REG_GPIO_ALTPADCFGF_PAD22_DS1(n)          (((uint32_t)(n) << 16) & 0x00010000)

// Pad 21 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGF_PAD21_SR_S            12
#define AM_REG_GPIO_ALTPADCFGF_PAD21_SR_M            0x00001000
#define AM_REG_GPIO_ALTPADCFGF_PAD21_SR(n)           (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_ALTPADCFGF_PAD21_SR_SR_EN        0x00001000

// Pad 21 high order drive strength selection.  Used in conjunction with
// PAD21STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGF_PAD21_DS1_S           8
#define AM_REG_GPIO_ALTPADCFGF_PAD21_DS1_M           0x00000100
#define AM_REG_GPIO_ALTPADCFGF_PAD21_DS1(n)          (((uint32_t)(n) << 8) & 0x00000100)

// Pad 20 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGF_PAD20_SR_S            4
#define AM_REG_GPIO_ALTPADCFGF_PAD20_SR_M            0x00000010
#define AM_REG_GPIO_ALTPADCFGF_PAD20_SR(n)           (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_ALTPADCFGF_PAD20_SR_SR_EN        0x00000010

// Pad 20 high order drive strength selection.  Used in conjunction with
// PAD20STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGF_PAD20_DS1_S           0
#define AM_REG_GPIO_ALTPADCFGF_PAD20_DS1_M           0x00000001
#define AM_REG_GPIO_ALTPADCFGF_PAD20_DS1(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_ALTPADCFGG - Alternate Pad Configuration reg6 (Pads 27,26,25,24)
//
//*****************************************************************************
// Pad 27 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGG_PAD27_SR_S            28
#define AM_REG_GPIO_ALTPADCFGG_PAD27_SR_M            0x10000000
#define AM_REG_GPIO_ALTPADCFGG_PAD27_SR(n)           (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_ALTPADCFGG_PAD27_SR_SR_EN        0x10000000

// Pad 27 high order drive strength selection.  Used in conjunction with
// PAD27STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGG_PAD27_DS1_S           24
#define AM_REG_GPIO_ALTPADCFGG_PAD27_DS1_M           0x01000000
#define AM_REG_GPIO_ALTPADCFGG_PAD27_DS1(n)          (((uint32_t)(n) << 24) & 0x01000000)

// Pad 26 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGG_PAD26_SR_S            20
#define AM_REG_GPIO_ALTPADCFGG_PAD26_SR_M            0x00100000
#define AM_REG_GPIO_ALTPADCFGG_PAD26_SR(n)           (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_ALTPADCFGG_PAD26_SR_SR_EN        0x00100000

// Pad 26 high order drive strength selection.  Used in conjunction with
// PAD26STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGG_PAD26_DS1_S           16
#define AM_REG_GPIO_ALTPADCFGG_PAD26_DS1_M           0x00010000
#define AM_REG_GPIO_ALTPADCFGG_PAD26_DS1(n)          (((uint32_t)(n) << 16) & 0x00010000)

// Pad 25 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGG_PAD25_SR_S            12
#define AM_REG_GPIO_ALTPADCFGG_PAD25_SR_M            0x00001000
#define AM_REG_GPIO_ALTPADCFGG_PAD25_SR(n)           (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_ALTPADCFGG_PAD25_SR_SR_EN        0x00001000

// Pad 25 high order drive strength selection.  Used in conjunction with
// PAD25STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGG_PAD25_DS1_S           8
#define AM_REG_GPIO_ALTPADCFGG_PAD25_DS1_M           0x00000100
#define AM_REG_GPIO_ALTPADCFGG_PAD25_DS1(n)          (((uint32_t)(n) << 8) & 0x00000100)

// Pad 24 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGG_PAD24_SR_S            4
#define AM_REG_GPIO_ALTPADCFGG_PAD24_SR_M            0x00000010
#define AM_REG_GPIO_ALTPADCFGG_PAD24_SR(n)           (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_ALTPADCFGG_PAD24_SR_SR_EN        0x00000010

// Pad 24 high order drive strength selection.  Used in conjunction with
// PAD24STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGG_PAD24_DS1_S           0
#define AM_REG_GPIO_ALTPADCFGG_PAD24_DS1_M           0x00000001
#define AM_REG_GPIO_ALTPADCFGG_PAD24_DS1(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_ALTPADCFGH - Alternate Pad Configuration reg7 (Pads 31,30,29,28)
//
//*****************************************************************************
// Pad 31 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGH_PAD31_SR_S            28
#define AM_REG_GPIO_ALTPADCFGH_PAD31_SR_M            0x10000000
#define AM_REG_GPIO_ALTPADCFGH_PAD31_SR(n)           (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_ALTPADCFGH_PAD31_SR_SR_EN        0x10000000

// Pad 31 high order drive strength selection.  Used in conjunction with
// PAD31STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGH_PAD31_DS1_S           24
#define AM_REG_GPIO_ALTPADCFGH_PAD31_DS1_M           0x01000000
#define AM_REG_GPIO_ALTPADCFGH_PAD31_DS1(n)          (((uint32_t)(n) << 24) & 0x01000000)

// Pad 30 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGH_PAD30_SR_S            20
#define AM_REG_GPIO_ALTPADCFGH_PAD30_SR_M            0x00100000
#define AM_REG_GPIO_ALTPADCFGH_PAD30_SR(n)           (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_ALTPADCFGH_PAD30_SR_SR_EN        0x00100000

// Pad 30 high order drive strength selection.  Used in conjunction with
// PAD30STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGH_PAD30_DS1_S           16
#define AM_REG_GPIO_ALTPADCFGH_PAD30_DS1_M           0x00010000
#define AM_REG_GPIO_ALTPADCFGH_PAD30_DS1(n)          (((uint32_t)(n) << 16) & 0x00010000)

// Pad 29 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGH_PAD29_SR_S            12
#define AM_REG_GPIO_ALTPADCFGH_PAD29_SR_M            0x00001000
#define AM_REG_GPIO_ALTPADCFGH_PAD29_SR(n)           (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_ALTPADCFGH_PAD29_SR_SR_EN        0x00001000

// Pad 29 high order drive strength selection.  Used in conjunction with
// PAD29STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGH_PAD29_DS1_S           8
#define AM_REG_GPIO_ALTPADCFGH_PAD29_DS1_M           0x00000100
#define AM_REG_GPIO_ALTPADCFGH_PAD29_DS1(n)          (((uint32_t)(n) << 8) & 0x00000100)

// Pad 28 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGH_PAD28_SR_S            4
#define AM_REG_GPIO_ALTPADCFGH_PAD28_SR_M            0x00000010
#define AM_REG_GPIO_ALTPADCFGH_PAD28_SR(n)           (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_ALTPADCFGH_PAD28_SR_SR_EN        0x00000010

// Pad 28 high order drive strength selection.  Used in conjunction with
// PAD28STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGH_PAD28_DS1_S           0
#define AM_REG_GPIO_ALTPADCFGH_PAD28_DS1_M           0x00000001
#define AM_REG_GPIO_ALTPADCFGH_PAD28_DS1(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_ALTPADCFGI - Alternate Pad Configuration reg8 (Pads 35,34,33,32)
//
//*****************************************************************************
// Pad 35 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGI_PAD35_SR_S            28
#define AM_REG_GPIO_ALTPADCFGI_PAD35_SR_M            0x10000000
#define AM_REG_GPIO_ALTPADCFGI_PAD35_SR(n)           (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_ALTPADCFGI_PAD35_SR_SR_EN        0x10000000

// Pad 35 high order drive strength selection.  Used in conjunction with
// PAD35STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGI_PAD35_DS1_S           24
#define AM_REG_GPIO_ALTPADCFGI_PAD35_DS1_M           0x01000000
#define AM_REG_GPIO_ALTPADCFGI_PAD35_DS1(n)          (((uint32_t)(n) << 24) & 0x01000000)

// Pad 34 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGI_PAD34_SR_S            20
#define AM_REG_GPIO_ALTPADCFGI_PAD34_SR_M            0x00100000
#define AM_REG_GPIO_ALTPADCFGI_PAD34_SR(n)           (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_ALTPADCFGI_PAD34_SR_SR_EN        0x00100000

// Pad 34 high order drive strength selection.  Used in conjunction with
// PAD34STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGI_PAD34_DS1_S           16
#define AM_REG_GPIO_ALTPADCFGI_PAD34_DS1_M           0x00010000
#define AM_REG_GPIO_ALTPADCFGI_PAD34_DS1(n)          (((uint32_t)(n) << 16) & 0x00010000)

// Pad 33 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGI_PAD33_SR_S            12
#define AM_REG_GPIO_ALTPADCFGI_PAD33_SR_M            0x00001000
#define AM_REG_GPIO_ALTPADCFGI_PAD33_SR(n)           (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_ALTPADCFGI_PAD33_SR_SR_EN        0x00001000

// Pad 33 high order drive strength selection.  Used in conjunction with
// PAD33STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGI_PAD33_DS1_S           8
#define AM_REG_GPIO_ALTPADCFGI_PAD33_DS1_M           0x00000100
#define AM_REG_GPIO_ALTPADCFGI_PAD33_DS1(n)          (((uint32_t)(n) << 8) & 0x00000100)

// Pad 32 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGI_PAD32_SR_S            4
#define AM_REG_GPIO_ALTPADCFGI_PAD32_SR_M            0x00000010
#define AM_REG_GPIO_ALTPADCFGI_PAD32_SR(n)           (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_ALTPADCFGI_PAD32_SR_SR_EN        0x00000010

// Pad 32 high order drive strength selection.  Used in conjunction with
// PAD32STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGI_PAD32_DS1_S           0
#define AM_REG_GPIO_ALTPADCFGI_PAD32_DS1_M           0x00000001
#define AM_REG_GPIO_ALTPADCFGI_PAD32_DS1(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_ALTPADCFGJ - Alternate Pad Configuration reg9 (Pads 39,38,37,36)
//
//*****************************************************************************
// Pad 39 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGJ_PAD39_SR_S            28
#define AM_REG_GPIO_ALTPADCFGJ_PAD39_SR_M            0x10000000
#define AM_REG_GPIO_ALTPADCFGJ_PAD39_SR(n)           (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_ALTPADCFGJ_PAD39_SR_SR_EN        0x10000000

// Pad 39 high order drive strength selection.  Used in conjunction with
// PAD39STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGJ_PAD39_DS1_S           24
#define AM_REG_GPIO_ALTPADCFGJ_PAD39_DS1_M           0x01000000
#define AM_REG_GPIO_ALTPADCFGJ_PAD39_DS1(n)          (((uint32_t)(n) << 24) & 0x01000000)

// Pad 38 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGJ_PAD38_SR_S            20
#define AM_REG_GPIO_ALTPADCFGJ_PAD38_SR_M            0x00100000
#define AM_REG_GPIO_ALTPADCFGJ_PAD38_SR(n)           (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_ALTPADCFGJ_PAD38_SR_SR_EN        0x00100000

// Pad 38 high order drive strength selection.  Used in conjunction with
// PAD38STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGJ_PAD38_DS1_S           16
#define AM_REG_GPIO_ALTPADCFGJ_PAD38_DS1_M           0x00010000
#define AM_REG_GPIO_ALTPADCFGJ_PAD38_DS1(n)          (((uint32_t)(n) << 16) & 0x00010000)

// Pad 37 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGJ_PAD37_SR_S            12
#define AM_REG_GPIO_ALTPADCFGJ_PAD37_SR_M            0x00001000
#define AM_REG_GPIO_ALTPADCFGJ_PAD37_SR(n)           (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_ALTPADCFGJ_PAD37_SR_SR_EN        0x00001000

// Pad 37 high order drive strength selection.  Used in conjunction with
// PAD37STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGJ_PAD37_DS1_S           8
#define AM_REG_GPIO_ALTPADCFGJ_PAD37_DS1_M           0x00000100
#define AM_REG_GPIO_ALTPADCFGJ_PAD37_DS1(n)          (((uint32_t)(n) << 8) & 0x00000100)

// Pad 36 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGJ_PAD36_SR_S            4
#define AM_REG_GPIO_ALTPADCFGJ_PAD36_SR_M            0x00000010
#define AM_REG_GPIO_ALTPADCFGJ_PAD36_SR(n)           (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_ALTPADCFGJ_PAD36_SR_SR_EN        0x00000010

// Pad 36 high order drive strength selection.  Used in conjunction with
// PAD36STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGJ_PAD36_DS1_S           0
#define AM_REG_GPIO_ALTPADCFGJ_PAD36_DS1_M           0x00000001
#define AM_REG_GPIO_ALTPADCFGJ_PAD36_DS1(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_ALTPADCFGK - Alternate Pad Configuration reg10 (Pads 43,42,41,40)
//
//*****************************************************************************
// Pad 43 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGK_PAD43_SR_S            28
#define AM_REG_GPIO_ALTPADCFGK_PAD43_SR_M            0x10000000
#define AM_REG_GPIO_ALTPADCFGK_PAD43_SR(n)           (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_ALTPADCFGK_PAD43_SR_SR_EN        0x10000000

// Pad 43 high order drive strength selection.  Used in conjunction with
// PAD43STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGK_PAD43_DS1_S           24
#define AM_REG_GPIO_ALTPADCFGK_PAD43_DS1_M           0x01000000
#define AM_REG_GPIO_ALTPADCFGK_PAD43_DS1(n)          (((uint32_t)(n) << 24) & 0x01000000)

// Pad 42 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGK_PAD42_SR_S            20
#define AM_REG_GPIO_ALTPADCFGK_PAD42_SR_M            0x00100000
#define AM_REG_GPIO_ALTPADCFGK_PAD42_SR(n)           (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_ALTPADCFGK_PAD42_SR_SR_EN        0x00100000

// Pad 42 high order drive strength selection.  Used in conjunction with
// PAD42STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGK_PAD42_DS1_S           16
#define AM_REG_GPIO_ALTPADCFGK_PAD42_DS1_M           0x00010000
#define AM_REG_GPIO_ALTPADCFGK_PAD42_DS1(n)          (((uint32_t)(n) << 16) & 0x00010000)

// Pad 41 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGK_PAD41_SR_S            12
#define AM_REG_GPIO_ALTPADCFGK_PAD41_SR_M            0x00001000
#define AM_REG_GPIO_ALTPADCFGK_PAD41_SR(n)           (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_ALTPADCFGK_PAD41_SR_SR_EN        0x00001000

// Pad 41 high order drive strength selection.  Used in conjunction with
// PAD41STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGK_PAD41_DS1_S           8
#define AM_REG_GPIO_ALTPADCFGK_PAD41_DS1_M           0x00000100
#define AM_REG_GPIO_ALTPADCFGK_PAD41_DS1(n)          (((uint32_t)(n) << 8) & 0x00000100)

// Pad 40 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGK_PAD40_SR_S            4
#define AM_REG_GPIO_ALTPADCFGK_PAD40_SR_M            0x00000010
#define AM_REG_GPIO_ALTPADCFGK_PAD40_SR(n)           (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_ALTPADCFGK_PAD40_SR_SR_EN        0x00000010

// Pad 40 high order drive strength selection.  Used in conjunction with
// PAD40STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGK_PAD40_DS1_S           0
#define AM_REG_GPIO_ALTPADCFGK_PAD40_DS1_M           0x00000001
#define AM_REG_GPIO_ALTPADCFGK_PAD40_DS1(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_ALTPADCFGL - Alternate Pad Configuration reg11 (Pads 47,46,45,44)
//
//*****************************************************************************
// Pad 47 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGL_PAD47_SR_S            28
#define AM_REG_GPIO_ALTPADCFGL_PAD47_SR_M            0x10000000
#define AM_REG_GPIO_ALTPADCFGL_PAD47_SR(n)           (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_GPIO_ALTPADCFGL_PAD47_SR_SR_EN        0x10000000

// Pad 47 high order drive strength selection.  Used in conjunction with
// PAD47STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGL_PAD47_DS1_S           24
#define AM_REG_GPIO_ALTPADCFGL_PAD47_DS1_M           0x01000000
#define AM_REG_GPIO_ALTPADCFGL_PAD47_DS1(n)          (((uint32_t)(n) << 24) & 0x01000000)

// Pad 46 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGL_PAD46_SR_S            20
#define AM_REG_GPIO_ALTPADCFGL_PAD46_SR_M            0x00100000
#define AM_REG_GPIO_ALTPADCFGL_PAD46_SR(n)           (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_GPIO_ALTPADCFGL_PAD46_SR_SR_EN        0x00100000

// Pad 46 high order drive strength selection.  Used in conjunction with
// PAD46STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGL_PAD46_DS1_S           16
#define AM_REG_GPIO_ALTPADCFGL_PAD46_DS1_M           0x00010000
#define AM_REG_GPIO_ALTPADCFGL_PAD46_DS1(n)          (((uint32_t)(n) << 16) & 0x00010000)

// Pad 45 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGL_PAD45_SR_S            12
#define AM_REG_GPIO_ALTPADCFGL_PAD45_SR_M            0x00001000
#define AM_REG_GPIO_ALTPADCFGL_PAD45_SR(n)           (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_ALTPADCFGL_PAD45_SR_SR_EN        0x00001000

// Pad 45 high order drive strength selection.  Used in conjunction with
// PAD45STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGL_PAD45_DS1_S           8
#define AM_REG_GPIO_ALTPADCFGL_PAD45_DS1_M           0x00000100
#define AM_REG_GPIO_ALTPADCFGL_PAD45_DS1(n)          (((uint32_t)(n) << 8) & 0x00000100)

// Pad 44 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGL_PAD44_SR_S            4
#define AM_REG_GPIO_ALTPADCFGL_PAD44_SR_M            0x00000010
#define AM_REG_GPIO_ALTPADCFGL_PAD44_SR(n)           (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_ALTPADCFGL_PAD44_SR_SR_EN        0x00000010

// Pad 44 high order drive strength selection.  Used in conjunction with
// PAD44STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGL_PAD44_DS1_S           0
#define AM_REG_GPIO_ALTPADCFGL_PAD44_DS1_M           0x00000001
#define AM_REG_GPIO_ALTPADCFGL_PAD44_DS1(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// GPIO_ALTPADCFGM - Alternate Pad Configuration reg12 (Pads 49,48)
//
//*****************************************************************************
// Pad 49 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGM_PAD49_SR_S            12
#define AM_REG_GPIO_ALTPADCFGM_PAD49_SR_M            0x00001000
#define AM_REG_GPIO_ALTPADCFGM_PAD49_SR(n)           (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_GPIO_ALTPADCFGM_PAD49_SR_SR_EN        0x00001000

// Pad 49 high order drive strength selection.  Used in conjunction with
// PAD49STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGM_PAD49_DS1_S           8
#define AM_REG_GPIO_ALTPADCFGM_PAD49_DS1_M           0x00000100
#define AM_REG_GPIO_ALTPADCFGM_PAD49_DS1(n)          (((uint32_t)(n) << 8) & 0x00000100)

// Pad 48 slew rate selection.
#define AM_REG_GPIO_ALTPADCFGM_PAD48_SR_S            4
#define AM_REG_GPIO_ALTPADCFGM_PAD48_SR_M            0x00000010
#define AM_REG_GPIO_ALTPADCFGM_PAD48_SR(n)           (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_GPIO_ALTPADCFGM_PAD48_SR_SR_EN        0x00000010

// Pad 48 high order drive strength selection.  Used in conjunction with
// PAD48STRNG field to set the pad drive strength.
#define AM_REG_GPIO_ALTPADCFGM_PAD48_DS1_S           0
#define AM_REG_GPIO_ALTPADCFGM_PAD48_DS1_M           0x00000001
#define AM_REG_GPIO_ALTPADCFGM_PAD48_DS1(n)          (((uint32_t)(n) << 0) & 0x00000001)

#endif // AM_REG_GPIO_H
