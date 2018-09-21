//*****************************************************************************
//
//  am_reg_mcuctrl.h
//! @file
//!
//! @brief Register macros for the MCUCTRL module
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
#ifndef AM_REG_MCUCTRL_H
#define AM_REG_MCUCTRL_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_MCUCTRL_NUM_MODULES                   1
#define AM_REG_MCUCTRLn(n) \
    (REG_MCUCTRL_BASEADDR + 0x00000000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_MCUCTRL_CHIP_INFO_O                   0x00000000
#define AM_REG_MCUCTRL_CHIPID0_O                     0x00000004
#define AM_REG_MCUCTRL_CHIPID1_O                     0x00000008
#define AM_REG_MCUCTRL_CHIPREV_O                     0x0000000C
#define AM_REG_MCUCTRL_VENDORID_O                    0x00000010
#define AM_REG_MCUCTRL_DEBUGGER_O                    0x00000014
#define AM_REG_MCUCTRL_BUCK_O                        0x00000060
#define AM_REG_MCUCTRL_BUCK3_O                       0x00000068
#define AM_REG_MCUCTRL_LDOREG1_O                     0x00000080
#define AM_REG_MCUCTRL_LDOREG3_O                     0x00000088
#define AM_REG_MCUCTRL_BODPORCTRL_O                  0x00000100
#define AM_REG_MCUCTRL_ADCPWRDLY_O                   0x00000104
#define AM_REG_MCUCTRL_ADCCAL_O                      0x0000010C
#define AM_REG_MCUCTRL_ADCBATTLOAD_O                 0x00000110
#define AM_REG_MCUCTRL_BUCKTRIM_O                    0x00000114
#define AM_REG_MCUCTRL_BOOTLOADERLOW_O               0x000001A0
#define AM_REG_MCUCTRL_SHADOWVALID_O                 0x000001A4
#define AM_REG_MCUCTRL_ICODEFAULTADDR_O              0x000001C0
#define AM_REG_MCUCTRL_DCODEFAULTADDR_O              0x000001C4
#define AM_REG_MCUCTRL_SYSFAULTADDR_O                0x000001C8
#define AM_REG_MCUCTRL_FAULTSTATUS_O                 0x000001CC
#define AM_REG_MCUCTRL_FAULTCAPTUREEN_O              0x000001D0
#define AM_REG_MCUCTRL_DBGR1_O                       0x00000200
#define AM_REG_MCUCTRL_DBGR2_O                       0x00000204
#define AM_REG_MCUCTRL_PMUENABLE_O                   0x00000220
#define AM_REG_MCUCTRL_TPIUCTRL_O                    0x00000250

//*****************************************************************************
//
// Key values.
//
//*****************************************************************************

//*****************************************************************************
//
// MCUCTRL_CHIP_INFO - Chip Information Register
//
//*****************************************************************************
// BCD part number.
#define AM_REG_MCUCTRL_CHIP_INFO_PARTNUM_S           0
#define AM_REG_MCUCTRL_CHIP_INFO_PARTNUM_M           0xFFFFFFFF
#define AM_REG_MCUCTRL_CHIP_INFO_PARTNUM(n)          (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_MCUCTRL_CHIP_INFO_PARTNUM_APOLLO2     0x03000000
#define AM_REG_MCUCTRL_CHIP_INFO_PARTNUM_APOLLO      0x01000000
#define AM_REG_MCUCTRL_CHIP_INFO_PARTNUM_PN_M        0xFF000000

//*****************************************************************************
//
// MCUCTRL_CHIPID0 - Unique Chip ID 0
//
//*****************************************************************************
// Unique chip ID 0.
#define AM_REG_MCUCTRL_CHIPID0_VALUE_S               0
#define AM_REG_MCUCTRL_CHIPID0_VALUE_M               0xFFFFFFFF
#define AM_REG_MCUCTRL_CHIPID0_VALUE(n)              (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_MCUCTRL_CHIPID0_VALUE_APOLLO2         0x00000000

//*****************************************************************************
//
// MCUCTRL_CHIPID1 - Unique Chip ID 1
//
//*****************************************************************************
// Unique chip ID 1.
#define AM_REG_MCUCTRL_CHIPID1_VALUE_S               0
#define AM_REG_MCUCTRL_CHIPID1_VALUE_M               0xFFFFFFFF
#define AM_REG_MCUCTRL_CHIPID1_VALUE(n)              (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_MCUCTRL_CHIPID1_VALUE_APOLLO2         0x00000000

//*****************************************************************************
//
// MCUCTRL_CHIPREV - Chip Revision
//
//*****************************************************************************
// Major Revision ID.
#define AM_REG_MCUCTRL_CHIPREV_REVMAJ_S              4
#define AM_REG_MCUCTRL_CHIPREV_REVMAJ_M              0x000000F0
#define AM_REG_MCUCTRL_CHIPREV_REVMAJ(n)             (((uint32_t)(n) << 4) & 0x000000F0)
#define AM_REG_MCUCTRL_CHIPREV_REVMAJ_B              0x00000020
#define AM_REG_MCUCTRL_CHIPREV_REVMAJ_A              0x00000010

// Minor Revision ID.
#define AM_REG_MCUCTRL_CHIPREV_REVMIN_S              0
#define AM_REG_MCUCTRL_CHIPREV_REVMIN_M              0x0000000F
#define AM_REG_MCUCTRL_CHIPREV_REVMIN(n)             (((uint32_t)(n) << 0) & 0x0000000F)
#define AM_REG_MCUCTRL_CHIPREV_REVMIN_REV0           0x00000000
#define AM_REG_MCUCTRL_CHIPREV_REVMIN_REV2           0x00000002

//*****************************************************************************
//
// MCUCTRL_VENDORID - Unique Vendor ID
//
//*****************************************************************************
// Unique Vendor ID
#define AM_REG_MCUCTRL_VENDORID_VALUE_S              0
#define AM_REG_MCUCTRL_VENDORID_VALUE_M              0xFFFFFFFF
#define AM_REG_MCUCTRL_VENDORID_VALUE(n)             (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_MCUCTRL_VENDORID_VALUE_AMBIQ          0x414D4251

//*****************************************************************************
//
// MCUCTRL_DEBUGGER - Debugger Access Control
//
//*****************************************************************************
// Lockout of debugger (SWD).
#define AM_REG_MCUCTRL_DEBUGGER_LOCKOUT_S            0
#define AM_REG_MCUCTRL_DEBUGGER_LOCKOUT_M            0x00000001
#define AM_REG_MCUCTRL_DEBUGGER_LOCKOUT(n)           (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MCUCTRL_BUCK - Analog Buck Control
//
//*****************************************************************************
// Reset control override for Mem Buck; 0=enabled, 1=reset; Value is propagated
// only when the BUCKSWE bit is active, otherwise contrl is from the power
// control module.
#define AM_REG_MCUCTRL_BUCK_MEMBUCKRST_S             7
#define AM_REG_MCUCTRL_BUCK_MEMBUCKRST_M             0x00000080
#define AM_REG_MCUCTRL_BUCK_MEMBUCKRST(n)            (((uint32_t)(n) << 7) & 0x00000080)

// Reset control override for Core Buck; 0=enabled, 1=reset; Value is propagated
// only when the BUCKSWE bit is active, otherwise control is from the power
// control module.
#define AM_REG_MCUCTRL_BUCK_COREBUCKRST_S            6
#define AM_REG_MCUCTRL_BUCK_COREBUCKRST_M            0x00000040
#define AM_REG_MCUCTRL_BUCK_COREBUCKRST(n)           (((uint32_t)(n) << 6) & 0x00000040)

// Not used.  Additional control of buck is available in the power control
// module
#define AM_REG_MCUCTRL_BUCK_BYPBUCKMEM_S             5
#define AM_REG_MCUCTRL_BUCK_BYPBUCKMEM_M             0x00000020
#define AM_REG_MCUCTRL_BUCK_BYPBUCKMEM(n)            (((uint32_t)(n) << 5) & 0x00000020)

// Memory buck power down override. 1=Powered Down; 0=Enabled; Value is
// propagated only when the BUCKSWE bit is active, otherwise control is from the
// power control module.
#define AM_REG_MCUCTRL_BUCK_MEMBUCKPWD_S             4
#define AM_REG_MCUCTRL_BUCK_MEMBUCKPWD_M             0x00000010
#define AM_REG_MCUCTRL_BUCK_MEMBUCKPWD(n)            (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_MCUCTRL_BUCK_MEMBUCKPWD_EN            0x00000000

// HFRC clkgen bit 0 override. When set, this will override to 0 bit 0 of the
// hfrc_freq_clkgen internal bus (see internal Shelby-1473)
#define AM_REG_MCUCTRL_BUCK_SLEEPBUCKANA_S           3
#define AM_REG_MCUCTRL_BUCK_SLEEPBUCKANA_M           0x00000008
#define AM_REG_MCUCTRL_BUCK_SLEEPBUCKANA(n)          (((uint32_t)(n) << 3) & 0x00000008)

// Core buck power down override. 1=Powered Down; 0=Enabled; Value is propagated
// only when the BUCKSWE bit is active, otherwise control is from the power
// control module.
#define AM_REG_MCUCTRL_BUCK_COREBUCKPWD_S            2
#define AM_REG_MCUCTRL_BUCK_COREBUCKPWD_M            0x00000004
#define AM_REG_MCUCTRL_BUCK_COREBUCKPWD(n)           (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_MCUCTRL_BUCK_COREBUCKPWD_EN           0x00000000

// Not used.  Additional control of buck is available in the power control
// module
#define AM_REG_MCUCTRL_BUCK_BYPBUCKCORE_S            1
#define AM_REG_MCUCTRL_BUCK_BYPBUCKCORE_M            0x00000002
#define AM_REG_MCUCTRL_BUCK_BYPBUCKCORE(n)           (((uint32_t)(n) << 1) & 0x00000002)

// Buck Register Software Override Enable.  This will enable the override values
// for MEMBUCKPWD, COREBUCKPWD, COREBUCKRST, MEMBUCKRST, all to be propagated to
// the control logic, instead of the normal power control module signal.  Note -
// Must take care to have correct value for ALL the register bits when this SWE
// is enabled.
#define AM_REG_MCUCTRL_BUCK_BUCKSWE_S                0
#define AM_REG_MCUCTRL_BUCK_BUCKSWE_M                0x00000001
#define AM_REG_MCUCTRL_BUCK_BUCKSWE(n)               (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_BUCK_BUCKSWE_OVERRIDE_DIS     0x00000000
#define AM_REG_MCUCTRL_BUCK_BUCKSWE_OVERRIDE_EN      0x00000001

//*****************************************************************************
//
// MCUCTRL_BUCK3 - Buck control reg 3
//
//*****************************************************************************
// MEM Buck low TON trim value
#define AM_REG_MCUCTRL_BUCK3_MEMBUCKLOTON_S          18
#define AM_REG_MCUCTRL_BUCK3_MEMBUCKLOTON_M          0x003C0000
#define AM_REG_MCUCTRL_BUCK3_MEMBUCKLOTON(n)         (((uint32_t)(n) << 18) & 0x003C0000)

// MEM Buck burst enable 0=disable, 0=disabled, 1=enable.
#define AM_REG_MCUCTRL_BUCK3_MEMBUCKBURSTEN_S        17
#define AM_REG_MCUCTRL_BUCK3_MEMBUCKBURSTEN_M        0x00020000
#define AM_REG_MCUCTRL_BUCK3_MEMBUCKBURSTEN(n)       (((uint32_t)(n) << 17) & 0x00020000)

// Memory buck zero crossing trim value
#define AM_REG_MCUCTRL_BUCK3_MEMBUCKZXTRIM_S         13
#define AM_REG_MCUCTRL_BUCK3_MEMBUCKZXTRIM_M         0x0001E000
#define AM_REG_MCUCTRL_BUCK3_MEMBUCKZXTRIM(n)        (((uint32_t)(n) << 13) & 0x0001E000)

// Hysterisis trim for mem buck
#define AM_REG_MCUCTRL_BUCK3_MEMBUCKHYSTTRIM_S       11
#define AM_REG_MCUCTRL_BUCK3_MEMBUCKHYSTTRIM_M       0x00001800
#define AM_REG_MCUCTRL_BUCK3_MEMBUCKHYSTTRIM(n)      (((uint32_t)(n) << 11) & 0x00001800)

// Core Buck low TON trim value
#define AM_REG_MCUCTRL_BUCK3_COREBUCKLOTON_S         7
#define AM_REG_MCUCTRL_BUCK3_COREBUCKLOTON_M         0x00000780
#define AM_REG_MCUCTRL_BUCK3_COREBUCKLOTON(n)        (((uint32_t)(n) << 7) & 0x00000780)

// Core Buck burst enable. 0=disabled, 1=enabled
#define AM_REG_MCUCTRL_BUCK3_COREBUCKBURSTEN_S       6
#define AM_REG_MCUCTRL_BUCK3_COREBUCKBURSTEN_M       0x00000040
#define AM_REG_MCUCTRL_BUCK3_COREBUCKBURSTEN(n)      (((uint32_t)(n) << 6) & 0x00000040)

// Core buck  zero crossing trim value
#define AM_REG_MCUCTRL_BUCK3_COREBUCKZXTRIM_S        2
#define AM_REG_MCUCTRL_BUCK3_COREBUCKZXTRIM_M        0x0000003C
#define AM_REG_MCUCTRL_BUCK3_COREBUCKZXTRIM(n)       (((uint32_t)(n) << 2) & 0x0000003C)

// Hysterisis trim for core buck
#define AM_REG_MCUCTRL_BUCK3_COREBUCKHYSTTRIM_S      0
#define AM_REG_MCUCTRL_BUCK3_COREBUCKHYSTTRIM_M      0x00000003
#define AM_REG_MCUCTRL_BUCK3_COREBUCKHYSTTRIM(n)     (((uint32_t)(n) << 0) & 0x00000003)

//*****************************************************************************
//
// MCUCTRL_LDOREG1 - Analog LDO Reg 1
//
//*****************************************************************************
// CORE LDO IBIAS Trim
#define AM_REG_MCUCTRL_LDOREG1_CORELDOIBSTRM_S       20
#define AM_REG_MCUCTRL_LDOREG1_CORELDOIBSTRM_M       0x00100000
#define AM_REG_MCUCTRL_LDOREG1_CORELDOIBSTRM(n)      (((uint32_t)(n) << 20) & 0x00100000)

// CORE LDO Low Power Trim
#define AM_REG_MCUCTRL_LDOREG1_CORELDOLPTRIM_S       14
#define AM_REG_MCUCTRL_LDOREG1_CORELDOLPTRIM_M       0x000FC000
#define AM_REG_MCUCTRL_LDOREG1_CORELDOLPTRIM(n)      (((uint32_t)(n) << 14) & 0x000FC000)

// CORE LDO tempco trim (R3).
#define AM_REG_MCUCTRL_LDOREG1_TRIMCORELDOR3_S       10
#define AM_REG_MCUCTRL_LDOREG1_TRIMCORELDOR3_M       0x00003C00
#define AM_REG_MCUCTRL_LDOREG1_TRIMCORELDOR3(n)      (((uint32_t)(n) << 10) & 0x00003C00)

// CORE LDO Active mode ouput trim (R1).
#define AM_REG_MCUCTRL_LDOREG1_TRIMCORELDOR1_S       0
#define AM_REG_MCUCTRL_LDOREG1_TRIMCORELDOR1_M       0x000003FF
#define AM_REG_MCUCTRL_LDOREG1_TRIMCORELDOR1(n)      (((uint32_t)(n) << 0) & 0x000003FF)

//*****************************************************************************
//
// MCUCTRL_LDOREG3 - LDO Control Register 3
//
//*****************************************************************************
// MEM LDO active mode trim (R1).
#define AM_REG_MCUCTRL_LDOREG3_TRIMMEMLDOR1_S        12
#define AM_REG_MCUCTRL_LDOREG3_TRIMMEMLDOR1_M        0x0003F000
#define AM_REG_MCUCTRL_LDOREG3_TRIMMEMLDOR1(n)       (((uint32_t)(n) << 12) & 0x0003F000)

// MEM LDO TRIM for low power mode with ADC active
#define AM_REG_MCUCTRL_LDOREG3_MEMLDOLPALTTRIM_S     6
#define AM_REG_MCUCTRL_LDOREG3_MEMLDOLPALTTRIM_M     0x00000FC0
#define AM_REG_MCUCTRL_LDOREG3_MEMLDOLPALTTRIM(n)    (((uint32_t)(n) << 6) & 0x00000FC0)

// MEM LDO TRIM for low power mode with ADC inactive
#define AM_REG_MCUCTRL_LDOREG3_MEMLDOLPTRIM_S        0
#define AM_REG_MCUCTRL_LDOREG3_MEMLDOLPTRIM_M        0x0000003F
#define AM_REG_MCUCTRL_LDOREG3_MEMLDOLPTRIM(n)       (((uint32_t)(n) << 0) & 0x0000003F)

//*****************************************************************************
//
// MCUCTRL_BODPORCTRL - BOD and PDR control Register
//
//*****************************************************************************
// BOD External Reference Select.
#define AM_REG_MCUCTRL_BODPORCTRL_BODEXTREFSEL_S     3
#define AM_REG_MCUCTRL_BODPORCTRL_BODEXTREFSEL_M     0x00000008
#define AM_REG_MCUCTRL_BODPORCTRL_BODEXTREFSEL(n)    (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_MCUCTRL_BODPORCTRL_BODEXTREFSEL_SELECT 0x00000008

// PDR External Reference Select.
#define AM_REG_MCUCTRL_BODPORCTRL_PDREXTREFSEL_S     2
#define AM_REG_MCUCTRL_BODPORCTRL_PDREXTREFSEL_M     0x00000004
#define AM_REG_MCUCTRL_BODPORCTRL_PDREXTREFSEL(n)    (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_MCUCTRL_BODPORCTRL_PDREXTREFSEL_SELECT 0x00000004

// BOD Power Down.
#define AM_REG_MCUCTRL_BODPORCTRL_PWDBOD_S           1
#define AM_REG_MCUCTRL_BODPORCTRL_PWDBOD_M           0x00000002
#define AM_REG_MCUCTRL_BODPORCTRL_PWDBOD(n)          (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_MCUCTRL_BODPORCTRL_PWDBOD_PWR_DN      0x00000002

// PDR Power Down.
#define AM_REG_MCUCTRL_BODPORCTRL_PWDPDR_S           0
#define AM_REG_MCUCTRL_BODPORCTRL_PWDPDR_M           0x00000001
#define AM_REG_MCUCTRL_BODPORCTRL_PWDPDR(n)          (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_BODPORCTRL_PWDPDR_PWR_DN      0x00000001

//*****************************************************************************
//
// MCUCTRL_ADCPWRDLY - ADC Power Up Delay Control
//
//*****************************************************************************
// ADC Reference Keeper enable delay in 16 ADC CLK increments for ADC_CLKSEL =
// 0x1, 8 ADC CLOCK increments for ADC_CLKSEL = 0x2.
#define AM_REG_MCUCTRL_ADCPWRDLY_ADCPWR1_S           8
#define AM_REG_MCUCTRL_ADCPWRDLY_ADCPWR1_M           0x0000FF00
#define AM_REG_MCUCTRL_ADCPWRDLY_ADCPWR1(n)          (((uint32_t)(n) << 8) & 0x0000FF00)

// ADC Reference Buffer Power Enable delay in 64 ADC CLK increments for
// ADC_CLKSEL = 0x1, 32 ADC CLOCK increments for ADC_CLKSEL = 0x2.
#define AM_REG_MCUCTRL_ADCPWRDLY_ADCPWR0_S           0
#define AM_REG_MCUCTRL_ADCPWRDLY_ADCPWR0_M           0x000000FF
#define AM_REG_MCUCTRL_ADCPWRDLY_ADCPWR0(n)          (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// MCUCTRL_ADCCAL - ADC Calibration Control
//
//*****************************************************************************
// Status for ADC Calibration
#define AM_REG_MCUCTRL_ADCCAL_ADCCALIBRATED_S        1
#define AM_REG_MCUCTRL_ADCCAL_ADCCALIBRATED_M        0x00000002
#define AM_REG_MCUCTRL_ADCCAL_ADCCALIBRATED(n)       (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_MCUCTRL_ADCCAL_ADCCALIBRATED_FALSE    0x00000000
#define AM_REG_MCUCTRL_ADCCAL_ADCCALIBRATED_TRUE     0x00000002

// Run ADC Calibration on initial power up sequence
#define AM_REG_MCUCTRL_ADCCAL_CALONPWRUP_S           0
#define AM_REG_MCUCTRL_ADCCAL_CALONPWRUP_M           0x00000001
#define AM_REG_MCUCTRL_ADCCAL_CALONPWRUP(n)          (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_ADCCAL_CALONPWRUP_DIS         0x00000000
#define AM_REG_MCUCTRL_ADCCAL_CALONPWRUP_EN          0x00000001

//*****************************************************************************
//
// MCUCTRL_ADCBATTLOAD - ADC Battery Load Enable
//
//*****************************************************************************
// Enable the ADC battery load resistor
#define AM_REG_MCUCTRL_ADCBATTLOAD_BATTLOAD_S        0
#define AM_REG_MCUCTRL_ADCBATTLOAD_BATTLOAD_M        0x00000001
#define AM_REG_MCUCTRL_ADCBATTLOAD_BATTLOAD(n)       (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_ADCBATTLOAD_BATTLOAD_DIS      0x00000000
#define AM_REG_MCUCTRL_ADCBATTLOAD_BATTLOAD_EN       0x00000001

//*****************************************************************************
//
// MCUCTRL_BUCKTRIM - Trim settings for Core and Mem buck modules
//
//*****************************************************************************
// RESERVED.
#define AM_REG_MCUCTRL_BUCKTRIM_RSVD2_S              24
#define AM_REG_MCUCTRL_BUCKTRIM_RSVD2_M              0x3F000000
#define AM_REG_MCUCTRL_BUCKTRIM_RSVD2(n)             (((uint32_t)(n) << 24) & 0x3F000000)

// Core Buck voltage output trim bits[9:6]. Concatenate with field COREBUCKR1_LO
// for the full trim value.
#define AM_REG_MCUCTRL_BUCKTRIM_COREBUCKR1_HI_S      16
#define AM_REG_MCUCTRL_BUCKTRIM_COREBUCKR1_HI_M      0x000F0000
#define AM_REG_MCUCTRL_BUCKTRIM_COREBUCKR1_HI(n)     (((uint32_t)(n) << 16) & 0x000F0000)

// Core Buck voltage output trim bits[5:0], Concatenate with field COREBUCKR1_HI
// for the full trim value.
#define AM_REG_MCUCTRL_BUCKTRIM_COREBUCKR1_LO_S      8
#define AM_REG_MCUCTRL_BUCKTRIM_COREBUCKR1_LO_M      0x00003F00
#define AM_REG_MCUCTRL_BUCKTRIM_COREBUCKR1_LO(n)     (((uint32_t)(n) << 8) & 0x00003F00)

// Trim values for BUCK regulator.
#define AM_REG_MCUCTRL_BUCKTRIM_MEMBUCKR1_S          0
#define AM_REG_MCUCTRL_BUCKTRIM_MEMBUCKR1_M          0x0000003F
#define AM_REG_MCUCTRL_BUCKTRIM_MEMBUCKR1(n)         (((uint32_t)(n) << 0) & 0x0000003F)

//*****************************************************************************
//
// MCUCTRL_BOOTLOADERLOW - Determines whether the bootloader code is visible at
// address 0x00000000
//
//*****************************************************************************
// Determines whether the bootloader code is visible at address 0x00000000 or
// not.
#define AM_REG_MCUCTRL_BOOTLOADERLOW_VALUE_S         0
#define AM_REG_MCUCTRL_BOOTLOADERLOW_VALUE_M         0x00000001
#define AM_REG_MCUCTRL_BOOTLOADERLOW_VALUE(n)        (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_BOOTLOADERLOW_VALUE_ADDR0     0x00000001

//*****************************************************************************
//
// MCUCTRL_SHADOWVALID - Register to indicate whether the shadow registers have
// been successfully loaded from the Flash Information Space.
//
//*****************************************************************************
// Indicates whether the bootloader should sleep or deep sleep if no image
// loaded.
#define AM_REG_MCUCTRL_SHADOWVALID_BL_DSLEEP_S       1
#define AM_REG_MCUCTRL_SHADOWVALID_BL_DSLEEP_M       0x00000002
#define AM_REG_MCUCTRL_SHADOWVALID_BL_DSLEEP(n)      (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_MCUCTRL_SHADOWVALID_BL_DSLEEP_DEEPSLEEP 0x00000002

// Indicates whether the shadow registers contain valid data from the Flash
// Information Space.
#define AM_REG_MCUCTRL_SHADOWVALID_VALID_S           0
#define AM_REG_MCUCTRL_SHADOWVALID_VALID_M           0x00000001
#define AM_REG_MCUCTRL_SHADOWVALID_VALID(n)          (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_SHADOWVALID_VALID_VALID       0x00000001

//*****************************************************************************
//
// MCUCTRL_ICODEFAULTADDR - ICODE bus address which was present when a bus fault
// occurred.
//
//*****************************************************************************
// The ICODE bus address observed when a Bus Fault occurred. Once an address is
// captured in this field, it is held until the corresponding Fault Observed bit
// is cleared in the FAULTSTATUS register.
#define AM_REG_MCUCTRL_ICODEFAULTADDR_ADDR_S         0
#define AM_REG_MCUCTRL_ICODEFAULTADDR_ADDR_M         0xFFFFFFFF
#define AM_REG_MCUCTRL_ICODEFAULTADDR_ADDR(n)        (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_DCODEFAULTADDR - DCODE bus address which was present when a bus fault
// occurred.
//
//*****************************************************************************
// The DCODE bus address observed when a Bus Fault occurred. Once an address is
// captured in this field, it is held until the corresponding Fault Observed bit
// is cleared in the FAULTSTATUS register.
#define AM_REG_MCUCTRL_DCODEFAULTADDR_ADDR_S         0
#define AM_REG_MCUCTRL_DCODEFAULTADDR_ADDR_M         0xFFFFFFFF
#define AM_REG_MCUCTRL_DCODEFAULTADDR_ADDR(n)        (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_SYSFAULTADDR - System bus address which was present when a bus fault
// occurred.
//
//*****************************************************************************
// SYS bus address observed when a Bus Fault occurred. Once an address is
// captured in this field, it is held until the corresponding Fault Observed bit
// is cleared in the FAULTSTATUS register.
#define AM_REG_MCUCTRL_SYSFAULTADDR_ADDR_S           0
#define AM_REG_MCUCTRL_SYSFAULTADDR_ADDR_M           0xFFFFFFFF
#define AM_REG_MCUCTRL_SYSFAULTADDR_ADDR(n)          (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_FAULTSTATUS - Reflects the status of the bus decoders' fault
// detection. Any write to this register will clear all of the status bits
// within the register.
//
//*****************************************************************************
// SYS Bus Decoder Fault Detected bit. When set, a fault has been detected, and
// the SYSFAULTADDR register will contain the bus address which generated the
// fault.
#define AM_REG_MCUCTRL_FAULTSTATUS_SYS_S             2
#define AM_REG_MCUCTRL_FAULTSTATUS_SYS_M             0x00000004
#define AM_REG_MCUCTRL_FAULTSTATUS_SYS(n)            (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_MCUCTRL_FAULTSTATUS_SYS_NOFAULT       0x00000000
#define AM_REG_MCUCTRL_FAULTSTATUS_SYS_FAULT         0x00000004

// DCODE Bus Decoder Fault Detected bit. When set, a fault has been detected,
// and the DCODEFAULTADDR register will contain the bus address which generated
// the fault.
#define AM_REG_MCUCTRL_FAULTSTATUS_DCODE_S           1
#define AM_REG_MCUCTRL_FAULTSTATUS_DCODE_M           0x00000002
#define AM_REG_MCUCTRL_FAULTSTATUS_DCODE(n)          (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_MCUCTRL_FAULTSTATUS_DCODE_NOFAULT     0x00000000
#define AM_REG_MCUCTRL_FAULTSTATUS_DCODE_FAULT       0x00000002

// The ICODE Bus Decoder Fault Detected bit. When set, a fault has been
// detected, and the ICODEFAULTADDR register will contain the bus address which
// generated the fault.
#define AM_REG_MCUCTRL_FAULTSTATUS_ICODE_S           0
#define AM_REG_MCUCTRL_FAULTSTATUS_ICODE_M           0x00000001
#define AM_REG_MCUCTRL_FAULTSTATUS_ICODE(n)          (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_FAULTSTATUS_ICODE_NOFAULT     0x00000000
#define AM_REG_MCUCTRL_FAULTSTATUS_ICODE_FAULT       0x00000001

//*****************************************************************************
//
// MCUCTRL_FAULTCAPTUREEN - Enable the fault capture registers
//
//*****************************************************************************
// Fault Capture Enable field. When set, the Fault Capture monitors are enabled
// and addresses which generate a hard fault are captured into the FAULTADDR
// registers.
#define AM_REG_MCUCTRL_FAULTCAPTUREEN_ENABLE_S       0
#define AM_REG_MCUCTRL_FAULTCAPTUREEN_ENABLE_M       0x00000001
#define AM_REG_MCUCTRL_FAULTCAPTUREEN_ENABLE(n)      (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_FAULTCAPTUREEN_ENABLE_DIS     0x00000000
#define AM_REG_MCUCTRL_FAULTCAPTUREEN_ENABLE_EN      0x00000001

//*****************************************************************************
//
// MCUCTRL_DBGR1 - Read-only debug register 1
//
//*****************************************************************************
// Read-only register for communication validation
#define AM_REG_MCUCTRL_DBGR1_ONETO8_S                0
#define AM_REG_MCUCTRL_DBGR1_ONETO8_M                0xFFFFFFFF
#define AM_REG_MCUCTRL_DBGR1_ONETO8(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_DBGR2 - Read-only debug register 2
//
//*****************************************************************************
// Read-only register for communication validation
#define AM_REG_MCUCTRL_DBGR2_COOLCODE_S              0
#define AM_REG_MCUCTRL_DBGR2_COOLCODE_M              0xFFFFFFFF
#define AM_REG_MCUCTRL_DBGR2_COOLCODE(n)             (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_PMUENABLE - Control bit to enable/disable the PMU
//
//*****************************************************************************
// PMU Enable Control bit. When set, the MCU's PMU will place the MCU into the
// lowest power consuming Deep Sleep mode upon execution of a WFI instruction
// (dependent on the setting of the SLEEPDEEP bit in the ARM SCR register). When
// cleared, regardless of the requested sleep mode, the PMU will not enter the
// lowest power Deep Sleep mode, instead entering the Sleep mode.
#define AM_REG_MCUCTRL_PMUENABLE_ENABLE_S            0
#define AM_REG_MCUCTRL_PMUENABLE_ENABLE_M            0x00000001
#define AM_REG_MCUCTRL_PMUENABLE_ENABLE(n)           (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_PMUENABLE_ENABLE_DIS          0x00000000
#define AM_REG_MCUCTRL_PMUENABLE_ENABLE_EN           0x00000001

//*****************************************************************************
//
// MCUCTRL_TPIUCTRL - TPIU Control Register. Determines the clock enable and
// frequency for the M4's TPIU interface.
//
//*****************************************************************************
// This field selects the frequency of the ARM M4 TPIU port.
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL_S             8
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL_M             0x00000700
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL(n)            (((uint32_t)(n) << 8) & 0x00000700)
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL_LOW_PWR       0x00000000
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL_0MHz          0x00000000
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL_HFRC_DIV_2    0x00000100
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL_HFRC_DIV_8    0x00000200
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL_HFRC_DIV_16   0x00000300
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL_HFRC_DIV_32   0x00000400

// TPIU Enable field. When set, the ARM M4 TPIU is enabled and data can be
// streamed out of the MCU's SWO port using the ARM ITM and TPIU modules.
#define AM_REG_MCUCTRL_TPIUCTRL_ENABLE_S             0
#define AM_REG_MCUCTRL_TPIUCTRL_ENABLE_M             0x00000001
#define AM_REG_MCUCTRL_TPIUCTRL_ENABLE(n)            (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_TPIUCTRL_ENABLE_DIS           0x00000000
#define AM_REG_MCUCTRL_TPIUCTRL_ENABLE_EN            0x00000001

#endif // AM_REG_MCUCTRL_H
