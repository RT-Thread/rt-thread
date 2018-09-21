//*****************************************************************************
//
//  am_reg_pwrctrl.h
//! @file
//!
//! @brief Register macros for the PWRCTRL module
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
#ifndef AM_REG_PWRCTRL_H
#define AM_REG_PWRCTRL_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_PWRCTRL_NUM_MODULES                   1
#define AM_REG_PWRCTRLn(n) \
    (REG_PWRCTRL_BASEADDR + 0x00000000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_PWRCTRL_SUPPLYSRC_O                   0x00000000
#define AM_REG_PWRCTRL_POWERSTATUS_O                 0x00000004
#define AM_REG_PWRCTRL_DEVICEEN_O                    0x00000008
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_O              0x0000000C
#define AM_REG_PWRCTRL_MEMEN_O                       0x00000010
#define AM_REG_PWRCTRL_PWRONSTATUS_O                 0x00000014
#define AM_REG_PWRCTRL_SRAMCTRL_O                    0x00000018
#define AM_REG_PWRCTRL_ADCSTATUS_O                   0x0000001C
#define AM_REG_PWRCTRL_MISCOPT_O                     0x00000020

//*****************************************************************************
//
// PWRCTRL_SUPPLYSRC - Memory and Core Voltage Supply Source Select Register
//
//*****************************************************************************
// Switches the CORE DOMAIN from BUCK mode (if enabled) to LDO when CPU is in
// DEEP SLEEP. If all the devices are off then this does not matter and LDO (low
// power mode) is used
#define AM_REG_PWRCTRL_SUPPLYSRC_SWITCH_LDO_IN_SLEEP_S 2
#define AM_REG_PWRCTRL_SUPPLYSRC_SWITCH_LDO_IN_SLEEP_M 0x00000004
#define AM_REG_PWRCTRL_SUPPLYSRC_SWITCH_LDO_IN_SLEEP(n) (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_PWRCTRL_SUPPLYSRC_SWITCH_LDO_IN_SLEEP_EN 0x00000004

// Enables and Selects the Core Buck as the supply for the low-voltage power
// domain.
#define AM_REG_PWRCTRL_SUPPLYSRC_COREBUCKEN_S        1
#define AM_REG_PWRCTRL_SUPPLYSRC_COREBUCKEN_M        0x00000002
#define AM_REG_PWRCTRL_SUPPLYSRC_COREBUCKEN(n)       (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_PWRCTRL_SUPPLYSRC_COREBUCKEN_EN       0x00000002

// Enables and select the Memory Buck as the supply for the Flash and SRAM power
// domain.
#define AM_REG_PWRCTRL_SUPPLYSRC_MEMBUCKEN_S         0
#define AM_REG_PWRCTRL_SUPPLYSRC_MEMBUCKEN_M         0x00000001
#define AM_REG_PWRCTRL_SUPPLYSRC_MEMBUCKEN(n)        (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_PWRCTRL_SUPPLYSRC_MEMBUCKEN_EN        0x00000001

//*****************************************************************************
//
// PWRCTRL_POWERSTATUS - Power Status Register for MCU supplies and peripherals
//
//*****************************************************************************
// Indicates whether the Core low-voltage domain is supplied from the LDO or the
// Buck.
#define AM_REG_PWRCTRL_POWERSTATUS_COREBUCKON_S      1
#define AM_REG_PWRCTRL_POWERSTATUS_COREBUCKON_M      0x00000002
#define AM_REG_PWRCTRL_POWERSTATUS_COREBUCKON(n)     (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_PWRCTRL_POWERSTATUS_COREBUCKON_LDO    0x00000000
#define AM_REG_PWRCTRL_POWERSTATUS_COREBUCKON_BUCK   0x00000002

// Indicate whether the Memory power domain is supplied from the LDO or the
// Buck.
#define AM_REG_PWRCTRL_POWERSTATUS_MEMBUCKON_S       0
#define AM_REG_PWRCTRL_POWERSTATUS_MEMBUCKON_M       0x00000001
#define AM_REG_PWRCTRL_POWERSTATUS_MEMBUCKON(n)      (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_PWRCTRL_POWERSTATUS_MEMBUCKON_LDO     0x00000000
#define AM_REG_PWRCTRL_POWERSTATUS_MEMBUCKON_BUCK    0x00000001

//*****************************************************************************
//
// PWRCTRL_DEVICEEN - DEVICE ENABLES for SHELBY
//
//*****************************************************************************
// Enable PDM Digital Block
#define AM_REG_PWRCTRL_DEVICEEN_PDM_S                10
#define AM_REG_PWRCTRL_DEVICEEN_PDM_M                0x00000400
#define AM_REG_PWRCTRL_DEVICEEN_PDM(n)               (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_PWRCTRL_DEVICEEN_PDM_EN               0x00000400
#define AM_REG_PWRCTRL_DEVICEEN_PDM_DIS              0x00000000

// Enable ADC Digital Block
#define AM_REG_PWRCTRL_DEVICEEN_ADC_S                9
#define AM_REG_PWRCTRL_DEVICEEN_ADC_M                0x00000200
#define AM_REG_PWRCTRL_DEVICEEN_ADC(n)               (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_PWRCTRL_DEVICEEN_ADC_EN               0x00000200
#define AM_REG_PWRCTRL_DEVICEEN_ADC_DIS              0x00000000

// Enable UART 1
#define AM_REG_PWRCTRL_DEVICEEN_UART1_S              8
#define AM_REG_PWRCTRL_DEVICEEN_UART1_M              0x00000100
#define AM_REG_PWRCTRL_DEVICEEN_UART1(n)             (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_PWRCTRL_DEVICEEN_UART1_EN             0x00000100
#define AM_REG_PWRCTRL_DEVICEEN_UART1_DIS            0x00000000

// Enable UART 0
#define AM_REG_PWRCTRL_DEVICEEN_UART0_S              7
#define AM_REG_PWRCTRL_DEVICEEN_UART0_M              0x00000080
#define AM_REG_PWRCTRL_DEVICEEN_UART0(n)             (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_PWRCTRL_DEVICEEN_UART0_EN             0x00000080
#define AM_REG_PWRCTRL_DEVICEEN_UART0_DIS            0x00000000

// Enable IO MASTER 5
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER5_S         6
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER5_M         0x00000040
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER5(n)        (((uint32_t)(n) << 6) & 0x00000040)
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER5_EN        0x00000040
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER5_DIS       0x00000000

// Enable IO MASTER 4
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER4_S         5
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER4_M         0x00000020
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER4(n)        (((uint32_t)(n) << 5) & 0x00000020)
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER4_EN        0x00000020
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER4_DIS       0x00000000

// Enable IO MASTER 3
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER3_S         4
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER3_M         0x00000010
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER3(n)        (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER3_EN        0x00000010
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER3_DIS       0x00000000

// Enable IO MASTER 2
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER2_S         3
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER2_M         0x00000008
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER2(n)        (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER2_EN        0x00000008
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER2_DIS       0x00000000

// Enable IO MASTER 1
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER1_S         2
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER1_M         0x00000004
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER1(n)        (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER1_EN        0x00000004
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER1_DIS       0x00000000

// Enable IO MASTER 0
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER0_S         1
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER0_M         0x00000002
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER0(n)        (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER0_EN        0x00000002
#define AM_REG_PWRCTRL_DEVICEEN_IO_MASTER0_DIS       0x00000000

// Enable IO SLAVE
#define AM_REG_PWRCTRL_DEVICEEN_IO_SLAVE_S           0
#define AM_REG_PWRCTRL_DEVICEEN_IO_SLAVE_M           0x00000001
#define AM_REG_PWRCTRL_DEVICEEN_IO_SLAVE(n)          (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_PWRCTRL_DEVICEEN_IO_SLAVE_EN          0x00000001
#define AM_REG_PWRCTRL_DEVICEEN_IO_SLAVE_DIS         0x00000000

//*****************************************************************************
//
// PWRCTRL_SRAMPWDINSLEEP - Powerdown an SRAM Banks in Deep Sleep mode
//
//*****************************************************************************
// Enable CACHE BANKS to power down in deep sleep
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_CACHE_PWD_SLP_S 31
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_CACHE_PWD_SLP_M 0x80000000
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_CACHE_PWD_SLP(n) (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_CACHE_PWD_SLP_EN 0x80000000
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_CACHE_PWD_SLP_DIS 0x00000000

// Selects which SRAM banks are powered down in deep sleep mode, causing the
// contents of the bank to be lost.
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_S 0
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_M 0x000007FF
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN(n) (((uint32_t)(n) << 0) & 0x000007FF)
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_NONE 0x00000000
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_GROUP0_SRAM0 0x00000001
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_GROUP0_SRAM1 0x00000002
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_GROUP0_SRAM2 0x00000004
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_GROUP0_SRAM3 0x00000008
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_GROUP1 0x00000010
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_GROUP2 0x00000020
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_GROUP3 0x00000040
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_GROUP4 0x00000080
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_GROUP5 0x00000100
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_GROUP6 0x00000200
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_GROUP7 0x00000400
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_SRAM8K 0x00000001
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_SRAM16K 0x00000003
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_SRAM32K 0x0000000F
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_SRAM64K 0x0000001F
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_SRAM128K 0x0000007F
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_ALLBUTLOWER8K 0x000007FE
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_ALLBUTLOWER16K 0x000007FC
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_ALLBUTLOWER24K 0x000007F8
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_ALLBUTLOWER32K 0x000007F0
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_ALLBUTLOWER64K 0x000007E0
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_ALLBUTLOWER128K 0x00000780
#define AM_REG_PWRCTRL_SRAMPWDINSLEEP_SRAMSLEEPPOWERDOWN_ALL 0x000007FF

//*****************************************************************************
//
// PWRCTRL_MEMEN - Disables individual banks of the MEMORY array
//
//*****************************************************************************
// Enable CACHE BANK 2
#define AM_REG_PWRCTRL_MEMEN_CACHEB2_S               31
#define AM_REG_PWRCTRL_MEMEN_CACHEB2_M               0x80000000
#define AM_REG_PWRCTRL_MEMEN_CACHEB2(n)              (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_PWRCTRL_MEMEN_CACHEB2_EN              0x80000000
#define AM_REG_PWRCTRL_MEMEN_CACHEB2_DIS             0x00000000

// Enable CACHE BANK 0
#define AM_REG_PWRCTRL_MEMEN_CACHEB0_S               29
#define AM_REG_PWRCTRL_MEMEN_CACHEB0_M               0x20000000
#define AM_REG_PWRCTRL_MEMEN_CACHEB0(n)              (((uint32_t)(n) << 29) & 0x20000000)
#define AM_REG_PWRCTRL_MEMEN_CACHEB0_EN              0x20000000
#define AM_REG_PWRCTRL_MEMEN_CACHEB0_DIS             0x00000000

// Enable FLASH1
#define AM_REG_PWRCTRL_MEMEN_FLASH1_S                12
#define AM_REG_PWRCTRL_MEMEN_FLASH1_M                0x00001000
#define AM_REG_PWRCTRL_MEMEN_FLASH1(n)               (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_PWRCTRL_MEMEN_FLASH1_EN               0x00001000
#define AM_REG_PWRCTRL_MEMEN_FLASH1_DIS              0x00000000

// Enable FLASH 0
#define AM_REG_PWRCTRL_MEMEN_FLASH0_S                11
#define AM_REG_PWRCTRL_MEMEN_FLASH0_M                0x00000800
#define AM_REG_PWRCTRL_MEMEN_FLASH0(n)               (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_PWRCTRL_MEMEN_FLASH0_EN               0x00000800
#define AM_REG_PWRCTRL_MEMEN_FLASH0_DIS              0x00000000

// Enables power for selected SRAM banks (else an access to its address space to
// generate a Hard Fault).
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_S                0
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_M                0x000007FF
#define AM_REG_PWRCTRL_MEMEN_SRAMEN(n)               (((uint32_t)(n) << 0) & 0x000007FF)
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_NONE             0x00000000
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP0_SRAM0     0x00000001
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP0_SRAM1     0x00000002
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP0_SRAM2     0x00000004
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP0_SRAM3     0x00000008
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP1           0x00000010
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP2           0x00000020
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP3           0x00000040
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP4           0x00000080
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP5           0x00000100
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP6           0x00000200
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP7           0x00000400
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM8K           0x00000001
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM16K          0x00000003
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM32K          0x0000000F
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM64K          0x0000001F
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM128K         0x0000007F
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM256K         0x000007FF
#define AM_REG_PWRCTRL_MEMEN_SRAMEN_ALL              0x000007FF

//*****************************************************************************
//
// PWRCTRL_PWRONSTATUS - POWER ON Status
//
//*****************************************************************************
// This bit is 1 if power is supplied to CACHE BANK 2
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_CACHEB2_S      21
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_CACHEB2_M      0x00200000
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_CACHEB2(n)     (((uint32_t)(n) << 21) & 0x00200000)

// This bit is 1 if power is supplied to CACHE BANK 0
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_CACHEB0_S      19
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_CACHEB0_M      0x00080000
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_CACHEB0(n)     (((uint32_t)(n) << 19) & 0x00080000)

// This bit is 1 if power is supplied to SRAM domain PD_GRP7
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP7_SRAM_S    18
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP7_SRAM_M    0x00040000
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP7_SRAM(n)   (((uint32_t)(n) << 18) & 0x00040000)

// This bit is 1 if power is supplied to SRAM domain PD_GRP6
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP6_SRAM_S    17
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP6_SRAM_M    0x00020000
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP6_SRAM(n)   (((uint32_t)(n) << 17) & 0x00020000)

// This bit is 1 if power is supplied to SRAM domain PD_GRP5
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP5_SRAM_S    16
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP5_SRAM_M    0x00010000
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP5_SRAM(n)   (((uint32_t)(n) << 16) & 0x00010000)

// This bit is 1 if power is supplied to SRAM domain PD_GRP4
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP4_SRAM_S    15
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP4_SRAM_M    0x00008000
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP4_SRAM(n)   (((uint32_t)(n) << 15) & 0x00008000)

// This bit is 1 if power is supplied to SRAM domain PD_GRP3
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP3_SRAM_S    14
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP3_SRAM_M    0x00004000
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP3_SRAM(n)   (((uint32_t)(n) << 14) & 0x00004000)

// This bit is 1 if power is supplied to SRAM domain PD_GRP2
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP2_SRAM_S    13
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP2_SRAM_M    0x00002000
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP2_SRAM(n)   (((uint32_t)(n) << 13) & 0x00002000)

// This bit is 1 if power is supplied to SRAM domain PD_GRP1
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP1_SRAM_S    12
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP1_SRAM_M    0x00001000
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP1_SRAM(n)   (((uint32_t)(n) << 12) & 0x00001000)

// This bit is 1 if power is supplied to SRAM domain PD_SRAM0_3
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM3_S   11
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM3_M   0x00000800
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM3(n)  (((uint32_t)(n) << 11) & 0x00000800)

// This bit is 1 if power is supplied to SRAM domain PD_SRAM0_2
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM2_S   10
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM2_M   0x00000400
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM2(n)  (((uint32_t)(n) << 10) & 0x00000400)

// This bit is 1 if power is supplied to SRAM domain SRAM0_1
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM1_S   9
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM1_M   0x00000200
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM1(n)  (((uint32_t)(n) << 9) & 0x00000200)

// This bit is 1 if power is supplied to SRAM domain SRAM0_0
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM0_S   8
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM0_M   0x00000100
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM0(n)  (((uint32_t)(n) << 8) & 0x00000100)

// This bit is 1 if power is supplied to domain PD_ADC
#define AM_REG_PWRCTRL_PWRONSTATUS_PDADC_S           7
#define AM_REG_PWRCTRL_PWRONSTATUS_PDADC_M           0x00000080
#define AM_REG_PWRCTRL_PWRONSTATUS_PDADC(n)          (((uint32_t)(n) << 7) & 0x00000080)

// This bit is 1 if power is supplied to domain PD_FLAM1
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_FLAM1_S        6
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_FLAM1_M        0x00000040
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_FLAM1(n)       (((uint32_t)(n) << 6) & 0x00000040)

// This bit is 1 if power is supplied to domain PD_FLAM0
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_FLAM0_S        5
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_FLAM0_M        0x00000020
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_FLAM0(n)       (((uint32_t)(n) << 5) & 0x00000020)

// This bit is 1 if power is supplied to domain PD_PDM
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_PDM_S          4
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_PDM_M          0x00000010
#define AM_REG_PWRCTRL_PWRONSTATUS_PD_PDM(n)         (((uint32_t)(n) << 4) & 0x00000010)

// This bit is 1 if power is supplied to power domain C, which supplies IOM3-5.
#define AM_REG_PWRCTRL_PWRONSTATUS_PDC_S             3
#define AM_REG_PWRCTRL_PWRONSTATUS_PDC_M             0x00000008
#define AM_REG_PWRCTRL_PWRONSTATUS_PDC(n)            (((uint32_t)(n) << 3) & 0x00000008)

// This bit is 1 if power is supplied to power domain B, which supplies IOM0-2.
#define AM_REG_PWRCTRL_PWRONSTATUS_PDB_S             2
#define AM_REG_PWRCTRL_PWRONSTATUS_PDB_M             0x00000004
#define AM_REG_PWRCTRL_PWRONSTATUS_PDB(n)            (((uint32_t)(n) << 2) & 0x00000004)

// This bit is 1 if power is supplied to power domain A, which supplies IOS and
// UART0,1.
#define AM_REG_PWRCTRL_PWRONSTATUS_PDA_S             1
#define AM_REG_PWRCTRL_PWRONSTATUS_PDA_M             0x00000002
#define AM_REG_PWRCTRL_PWRONSTATUS_PDA(n)            (((uint32_t)(n) << 1) & 0x00000002)

//*****************************************************************************
//
// PWRCTRL_SRAMCTRL - SRAM Control register
//
//*****************************************************************************
// Enables top-level clock gating in the SRAM block.  This bit should be enabled
// for lowest power operation.
#define AM_REG_PWRCTRL_SRAMCTRL_SRAM_MASTER_CLKGATE_S 2
#define AM_REG_PWRCTRL_SRAMCTRL_SRAM_MASTER_CLKGATE_M 0x00000004
#define AM_REG_PWRCTRL_SRAMCTRL_SRAM_MASTER_CLKGATE(n) (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_PWRCTRL_SRAMCTRL_SRAM_MASTER_CLKGATE_EN 0x00000004
#define AM_REG_PWRCTRL_SRAMCTRL_SRAM_MASTER_CLKGATE_DIS 0x00000000

// Enables individual per-RAM clock gating in the SRAM block.  This bit should
// be enabled for lowest power operation.
#define AM_REG_PWRCTRL_SRAMCTRL_SRAM_CLKGATE_S       1
#define AM_REG_PWRCTRL_SRAMCTRL_SRAM_CLKGATE_M       0x00000002
#define AM_REG_PWRCTRL_SRAMCTRL_SRAM_CLKGATE(n)      (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_PWRCTRL_SRAMCTRL_SRAM_CLKGATE_EN      0x00000002
#define AM_REG_PWRCTRL_SRAMCTRL_SRAM_CLKGATE_DIS     0x00000000

// Enable LS (light sleep) of cache RAMs.  When this bit is set, the RAMS will
// be put into light sleep mode while inactive.  NOTE:  if the SRAM is actively
// used, this may have an adverse affect on power since entering/exiting LS mode
// may consume more power than would be saved.
#define AM_REG_PWRCTRL_SRAMCTRL_SRAM_LIGHT_SLEEP_S   0
#define AM_REG_PWRCTRL_SRAMCTRL_SRAM_LIGHT_SLEEP_M   0x00000001
#define AM_REG_PWRCTRL_SRAMCTRL_SRAM_LIGHT_SLEEP(n)  (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_PWRCTRL_SRAMCTRL_SRAM_LIGHT_SLEEP_EN  0x00000001
#define AM_REG_PWRCTRL_SRAMCTRL_SRAM_LIGHT_SLEEP_DIS 0x00000000

//*****************************************************************************
//
// PWRCTRL_ADCSTATUS - Power Status Register for ADC Block
//
//*****************************************************************************
// This bit indicates that the ADC REFBUF is powered down
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_REFBUF_PWD_S    5
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_REFBUF_PWD_M    0x00000020
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_REFBUF_PWD(n)   (((uint32_t)(n) << 5) & 0x00000020)

// This bit indicates that the ADC REFKEEP is powered down
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_REFKEEP_PWD_S   4
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_REFKEEP_PWD_M   0x00000010
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_REFKEEP_PWD(n)  (((uint32_t)(n) << 4) & 0x00000010)

// This bit indicates that the ADC VBAT resistor divider is powered down
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_VBAT_PWD_S      3
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_VBAT_PWD_M      0x00000008
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_VBAT_PWD(n)     (((uint32_t)(n) << 3) & 0x00000008)

// This bit indicates that the ADC temperature sensor input buffer is powered
// down
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_VPTAT_PWD_S     2
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_VPTAT_PWD_M     0x00000004
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_VPTAT_PWD(n)    (((uint32_t)(n) << 2) & 0x00000004)

// This bit indicates that the ADC Band Gap is powered down
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_BGT_PWD_S       1
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_BGT_PWD_M       0x00000002
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_BGT_PWD(n)      (((uint32_t)(n) << 1) & 0x00000002)

// This bit indicates that the ADC is powered down
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_PWD_S           0
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_PWD_M           0x00000001
#define AM_REG_PWRCTRL_ADCSTATUS_ADC_PWD(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PWRCTRL_MISCOPT - Power Optimization Control Bits
//
//*****************************************************************************
// Setting this bit will enable the MEM LDO to be in LPMODE during deep sleep
// even when the ctimers or stimers are running
#define AM_REG_PWRCTRL_MISCOPT_DIS_LDOLPMODE_TIMERS_S 2
#define AM_REG_PWRCTRL_MISCOPT_DIS_LDOLPMODE_TIMERS_M 0x00000004
#define AM_REG_PWRCTRL_MISCOPT_DIS_LDOLPMODE_TIMERS(n) (((uint32_t)(n) << 2) & 0x00000004)

#endif // AM_REG_PWRCTRL_H
