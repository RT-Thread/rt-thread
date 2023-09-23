//*****************************************************************************
//
// hw_sysctl.h - Macros used when accessing the system control hardware.
//
// Copyright (c) 2005-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

#ifndef __HW_SYSCTL_H__
#define __HW_SYSCTL_H__

//*****************************************************************************
//
// The following are defines for the System Control register addresses.
//
//*****************************************************************************
#define SYSCTL_DID0             0x400FE000  // Device Identification 0
#define SYSCTL_DID1             0x400FE004  // Device Identification 1
#define SYSCTL_PTBOCTL          0x400FE038  // Power-Temp Brown Out Control
#define SYSCTL_RIS              0x400FE050  // Raw Interrupt Status
#define SYSCTL_IMC              0x400FE054  // Interrupt Mask Control
#define SYSCTL_MISC             0x400FE058  // Masked Interrupt Status and
// Clear
#define SYSCTL_RESC             0x400FE05C  // Reset Cause
#define SYSCTL_PWRTC            0x400FE060  // Power-Temperature Cause
#define SYSCTL_NMIC             0x400FE064  // NMI Cause Register
#define SYSCTL_MOSCCTL          0x400FE07C  // Main Oscillator Control
#define SYSCTL_RSCLKCFG         0x400FE0B0  // Run and Sleep Mode Configuration
// Register
#define SYSCTL_MEMTIM0          0x400FE0C0  // Memory Timing Parameter Register
// 0 for Main Flash and EEPROM
#define SYSCTL_ALTCLKCFG        0x400FE138  // Alternate Clock Configuration
#define SYSCTL_DSLPCLKCFG       0x400FE144  // Deep Sleep Clock Configuration
#define SYSCTL_DSCLKCFG         0x400FE144  // Deep Sleep Clock Configuration
// Register
#define SYSCTL_DIVSCLK          0x400FE148  // Divisor and Source Clock
// Configuration
#define SYSCTL_SYSPROP          0x400FE14C  // System Properties
#define SYSCTL_PIOSCCAL         0x400FE150  // Precision Internal Oscillator
// Calibration
#define SYSCTL_PIOSCSTAT        0x400FE154  // Precision Internal Oscillator
// Statistics
#define SYSCTL_PLLFREQ0         0x400FE160  // PLL Frequency 0
#define SYSCTL_PLLFREQ1         0x400FE164  // PLL Frequency 1
#define SYSCTL_PLLSTAT          0x400FE168  // PLL Status
#define SYSCTL_SLPPWRCFG        0x400FE188  // Sleep Power Configuration
#define SYSCTL_DSLPPWRCFG       0x400FE18C  // Deep-Sleep Power Configuration
#define SYSCTL_DC9              0x400FE190  // Device Capabilities 9
#define SYSCTL_NVMSTAT          0x400FE1A0  // Non-Volatile Memory Information
#define SYSCTL_LDOSPCTL         0x400FE1B4  // LDO Sleep Power Control
#define SYSCTL_LDODPCTL         0x400FE1BC  // LDO Deep-Sleep Power Control
#define SYSCTL_RESBEHAVCTL      0x400FE1D8  // Reset Behavior Control Register
#define SYSCTL_HSSR             0x400FE1F4  // Hardware System Service Request
#define SYSCTL_USBPDS           0x400FE280  // USB Power Domain Status
#define SYSCTL_USBMPC           0x400FE284  // USB Memory Power Control
#define SYSCTL_EMACPDS          0x400FE288  // Ethernet MAC Power Domain Status
#define SYSCTL_EMACMPC          0x400FE28C  // Ethernet MAC Memory Power
// Control
#define SYSCTL_LCDMPC           0x400FE294  // LCD Memory Power Control
#define SYSCTL_PPWD             0x400FE300  // Watchdog Timer Peripheral
// Present
#define SYSCTL_PPTIMER          0x400FE304  // 16/32-Bit General-Purpose Timer
// Peripheral Present
#define SYSCTL_PPGPIO           0x400FE308  // General-Purpose Input/Output
// Peripheral Present
#define SYSCTL_PPDMA            0x400FE30C  // Micro Direct Memory Access
// Peripheral Present
#define SYSCTL_PPEPI            0x400FE310  // EPI Peripheral Present
#define SYSCTL_PPHIB            0x400FE314  // Hibernation Peripheral Present
#define SYSCTL_PPUART           0x400FE318  // Universal Asynchronous
// Receiver/Transmitter Peripheral
// Present
#define SYSCTL_PPSSI            0x400FE31C  // Synchronous Serial Interface
// Peripheral Present
#define SYSCTL_PPI2C            0x400FE320  // Inter-Integrated Circuit
// Peripheral Present
#define SYSCTL_PPUSB            0x400FE328  // Universal Serial Bus Peripheral
// Present
#define SYSCTL_PPEPHY           0x400FE330  // Ethernet PHY Peripheral Present
#define SYSCTL_PPCAN            0x400FE334  // Controller Area Network
// Peripheral Present
#define SYSCTL_PPADC            0x400FE338  // Analog-to-Digital Converter
// Peripheral Present
#define SYSCTL_PPACMP           0x400FE33C  // Analog Comparator Peripheral
// Present
#define SYSCTL_PPPWM            0x400FE340  // Pulse Width Modulator Peripheral
// Present
#define SYSCTL_PPQEI            0x400FE344  // Quadrature Encoder Interface
// Peripheral Present
#define SYSCTL_PPEEPROM         0x400FE358  // EEPROM Peripheral Present
#define SYSCTL_PPCCM            0x400FE374  // CRC and Cryptographic Modules
// Peripheral Present
#define SYSCTL_PPLCD            0x400FE390  // LCD Peripheral Present
#define SYSCTL_PPOWIRE          0x400FE398  // 1-Wire Peripheral Present
#define SYSCTL_PPEMAC           0x400FE39C  // Ethernet MAC Peripheral Present
#define SYSCTL_SRWD             0x400FE500  // Watchdog Timer Software Reset
#define SYSCTL_SRTIMER          0x400FE504  // 16/32-Bit General-Purpose Timer
// Software Reset
#define SYSCTL_SRGPIO           0x400FE508  // General-Purpose Input/Output
// Software Reset
#define SYSCTL_SRDMA            0x400FE50C  // Micro Direct Memory Access
// Software Reset
#define SYSCTL_SREPI            0x400FE510  // EPI Software Reset
#define SYSCTL_SRHIB            0x400FE514  // Hibernation Software Reset
#define SYSCTL_SRUART           0x400FE518  // Universal Asynchronous
// Receiver/Transmitter Software
// Reset
#define SYSCTL_SRSSI            0x400FE51C  // Synchronous Serial Interface
// Software Reset
#define SYSCTL_SRI2C            0x400FE520  // Inter-Integrated Circuit
// Software Reset
#define SYSCTL_SRUSB            0x400FE528  // Universal Serial Bus Software
// Reset
#define SYSCTL_SREPHY           0x400FE530  // Ethernet PHY Software Reset
#define SYSCTL_SRCAN            0x400FE534  // Controller Area Network Software
// Reset
#define SYSCTL_SRADC            0x400FE538  // Analog-to-Digital Converter
// Software Reset
#define SYSCTL_SRACMP           0x400FE53C  // Analog Comparator Software Reset
#define SYSCTL_SRPWM            0x400FE540  // Pulse Width Modulator Software
// Reset
#define SYSCTL_SRQEI            0x400FE544  // Quadrature Encoder Interface
// Software Reset
#define SYSCTL_SREEPROM         0x400FE558  // EEPROM Software Reset
#define SYSCTL_SRCCM            0x400FE574  // CRC and Cryptographic Modules
// Software Reset
#define SYSCTL_SRLCD            0x400FE590  // LCD Controller Software Reset
#define SYSCTL_SROWIRE          0x400FE598  // 1-Wire Software Reset
#define SYSCTL_SREMAC           0x400FE59C  // Ethernet MAC Software Reset
#define SYSCTL_RCGCWD           0x400FE600  // Watchdog Timer Run Mode Clock
// Gating Control
#define SYSCTL_RCGCTIMER        0x400FE604  // 16/32-Bit General-Purpose Timer
// Run Mode Clock Gating Control
#define SYSCTL_RCGCGPIO         0x400FE608  // General-Purpose Input/Output Run
// Mode Clock Gating Control
#define SYSCTL_RCGCDMA          0x400FE60C  // Micro Direct Memory Access Run
// Mode Clock Gating Control
#define SYSCTL_RCGCEPI          0x400FE610  // EPI Run Mode Clock Gating
// Control
#define SYSCTL_RCGCHIB          0x400FE614  // Hibernation Run Mode Clock
// Gating Control
#define SYSCTL_RCGCUART         0x400FE618  // Universal Asynchronous
// Receiver/Transmitter Run Mode
// Clock Gating Control
#define SYSCTL_RCGCSSI          0x400FE61C  // Synchronous Serial Interface Run
// Mode Clock Gating Control
#define SYSCTL_RCGCI2C          0x400FE620  // Inter-Integrated Circuit Run
// Mode Clock Gating Control
#define SYSCTL_RCGCUSB          0x400FE628  // Universal Serial Bus Run Mode
// Clock Gating Control
#define SYSCTL_RCGCEPHY         0x400FE630  // Ethernet PHY Run Mode Clock
// Gating Control
#define SYSCTL_RCGCCAN          0x400FE634  // Controller Area Network Run Mode
// Clock Gating Control
#define SYSCTL_RCGCADC          0x400FE638  // Analog-to-Digital Converter Run
// Mode Clock Gating Control
#define SYSCTL_RCGCACMP         0x400FE63C  // Analog Comparator Run Mode Clock
// Gating Control
#define SYSCTL_RCGCPWM          0x400FE640  // Pulse Width Modulator Run Mode
// Clock Gating Control
#define SYSCTL_RCGCQEI          0x400FE644  // Quadrature Encoder Interface Run
// Mode Clock Gating Control
#define SYSCTL_RCGCEEPROM       0x400FE658  // EEPROM Run Mode Clock Gating
// Control
#define SYSCTL_RCGCCCM          0x400FE674  // CRC and Cryptographic Modules
// Run Mode Clock Gating Control
#define SYSCTL_RCGCLCD          0x400FE690  // LCD Controller Run Mode Clock
// Gating Control
#define SYSCTL_RCGCOWIRE        0x400FE698  // 1-Wire Run Mode Clock Gating
// Control
#define SYSCTL_RCGCEMAC         0x400FE69C  // Ethernet MAC Run Mode Clock
// Gating Control
#define SYSCTL_SCGCWD           0x400FE700  // Watchdog Timer Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCTIMER        0x400FE704  // 16/32-Bit General-Purpose Timer
// Sleep Mode Clock Gating Control
#define SYSCTL_SCGCGPIO         0x400FE708  // General-Purpose Input/Output
// Sleep Mode Clock Gating Control
#define SYSCTL_SCGCDMA          0x400FE70C  // Micro Direct Memory Access Sleep
// Mode Clock Gating Control
#define SYSCTL_SCGCEPI          0x400FE710  // EPI Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCHIB          0x400FE714  // Hibernation Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCUART         0x400FE718  // Universal Asynchronous
// Receiver/Transmitter Sleep Mode
// Clock Gating Control
#define SYSCTL_SCGCSSI          0x400FE71C  // Synchronous Serial Interface
// Sleep Mode Clock Gating Control
#define SYSCTL_SCGCI2C          0x400FE720  // Inter-Integrated Circuit Sleep
// Mode Clock Gating Control
#define SYSCTL_SCGCUSB          0x400FE728  // Universal Serial Bus Sleep Mode
// Clock Gating Control
#define SYSCTL_SCGCEPHY         0x400FE730  // Ethernet PHY Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCCAN          0x400FE734  // Controller Area Network Sleep
// Mode Clock Gating Control
#define SYSCTL_SCGCADC          0x400FE738  // Analog-to-Digital Converter
// Sleep Mode Clock Gating Control
#define SYSCTL_SCGCACMP         0x400FE73C  // Analog Comparator Sleep Mode
// Clock Gating Control
#define SYSCTL_SCGCPWM          0x400FE740  // Pulse Width Modulator Sleep Mode
// Clock Gating Control
#define SYSCTL_SCGCQEI          0x400FE744  // Quadrature Encoder Interface
// Sleep Mode Clock Gating Control
#define SYSCTL_SCGCEEPROM       0x400FE758  // EEPROM Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCCCM          0x400FE774  // CRC and Cryptographic Modules
// Sleep Mode Clock Gating Control
#define SYSCTL_SCGCLCD          0x400FE790  // LCD Controller Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCOWIRE        0x400FE798  // 1-Wire Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCEMAC         0x400FE79C  // Ethernet MAC Sleep Mode Clock
// Gating Control
#define SYSCTL_DCGCWD           0x400FE800  // Watchdog Timer Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCTIMER        0x400FE804  // 16/32-Bit General-Purpose Timer
// Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCGPIO         0x400FE808  // General-Purpose Input/Output
// Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCDMA          0x400FE80C  // Micro Direct Memory Access
// Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCEPI          0x400FE810  // EPI Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCHIB          0x400FE814  // Hibernation Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCUART         0x400FE818  // Universal Asynchronous
// Receiver/Transmitter Deep-Sleep
// Mode Clock Gating Control
#define SYSCTL_DCGCSSI          0x400FE81C  // Synchronous Serial Interface
// Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCI2C          0x400FE820  // Inter-Integrated Circuit
// Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCUSB          0x400FE828  // Universal Serial Bus Deep-Sleep
// Mode Clock Gating Control
#define SYSCTL_DCGCEPHY         0x400FE830  // Ethernet PHY Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCCAN          0x400FE834  // Controller Area Network
// Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCADC          0x400FE838  // Analog-to-Digital Converter
// Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCACMP         0x400FE83C  // Analog Comparator Deep-Sleep
// Mode Clock Gating Control
#define SYSCTL_DCGCPWM          0x400FE840  // Pulse Width Modulator Deep-Sleep
// Mode Clock Gating Control
#define SYSCTL_DCGCQEI          0x400FE844  // Quadrature Encoder Interface
// Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCEEPROM       0x400FE858  // EEPROM Deep-Sleep Mode Clock
// Gating Control
#define SYSCTL_DCGCCCM          0x400FE874  // CRC and Cryptographic Modules
// Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCLCD          0x400FE890  // LCD Controller Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCOWIRE        0x400FE898  // 1-Wire Deep-Sleep Mode Clock
// Gating Control
#define SYSCTL_DCGCEMAC         0x400FE89C  // Ethernet MAC Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_PCWD             0x400FE900  // Watchdog Timer Power Control
#define SYSCTL_PCTIMER          0x400FE904  // 16/32-Bit General-Purpose Timer
// Power Control
#define SYSCTL_PCGPIO           0x400FE908  // General-Purpose Input/Output
// Power Control
#define SYSCTL_PCDMA            0x400FE90C  // Micro Direct Memory Access Power
// Control
#define SYSCTL_PCEPI            0x400FE910  // External Peripheral Interface
// Power Control
#define SYSCTL_PCHIB            0x400FE914  // Hibernation Power Control
#define SYSCTL_PCUART           0x400FE918  // Universal Asynchronous
// Receiver/Transmitter Power
// Control
#define SYSCTL_PCSSI            0x400FE91C  // Synchronous Serial Interface
// Power Control
#define SYSCTL_PCI2C            0x400FE920  // Inter-Integrated Circuit Power
// Control
#define SYSCTL_PCUSB            0x400FE928  // Universal Serial Bus Power
// Control
#define SYSCTL_PCEPHY           0x400FE930  // Ethernet PHY Power Control
#define SYSCTL_PCCAN            0x400FE934  // Controller Area Network Power
// Control
#define SYSCTL_PCADC            0x400FE938  // Analog-to-Digital Converter
// Power Control
#define SYSCTL_PCACMP           0x400FE93C  // Analog Comparator Power Control
#define SYSCTL_PCPWM            0x400FE940  // Pulse Width Modulator Power
// Control
#define SYSCTL_PCQEI            0x400FE944  // Quadrature Encoder Interface
// Power Control
#define SYSCTL_PCEEPROM         0x400FE958  // EEPROM Power Control
#define SYSCTL_PCCCM            0x400FE974  // CRC and Cryptographic Modules
// Power Control
#define SYSCTL_PCLCD            0x400FE990  // LCD Controller Power Control
#define SYSCTL_PCOWIRE          0x400FE998  // 1-Wire Power Control
#define SYSCTL_PCEMAC           0x400FE99C  // Ethernet MAC Power Control
#define SYSCTL_PRWD             0x400FEA00  // Watchdog Timer Peripheral Ready
#define SYSCTL_PRTIMER          0x400FEA04  // 16/32-Bit General-Purpose Timer
// Peripheral Ready
#define SYSCTL_PRGPIO           0x400FEA08  // General-Purpose Input/Output
// Peripheral Ready
#define SYSCTL_PRDMA            0x400FEA0C  // Micro Direct Memory Access
// Peripheral Ready
#define SYSCTL_PREPI            0x400FEA10  // EPI Peripheral Ready
#define SYSCTL_PRHIB            0x400FEA14  // Hibernation Peripheral Ready
#define SYSCTL_PRUART           0x400FEA18  // Universal Asynchronous
// Receiver/Transmitter Peripheral
// Ready
#define SYSCTL_PRSSI            0x400FEA1C  // Synchronous Serial Interface
// Peripheral Ready
#define SYSCTL_PRI2C            0x400FEA20  // Inter-Integrated Circuit
// Peripheral Ready
#define SYSCTL_PRUSB            0x400FEA28  // Universal Serial Bus Peripheral
// Ready
#define SYSCTL_PREPHY           0x400FEA30  // Ethernet PHY Peripheral Ready
#define SYSCTL_PRCAN            0x400FEA34  // Controller Area Network
// Peripheral Ready
#define SYSCTL_PRADC            0x400FEA38  // Analog-to-Digital Converter
// Peripheral Ready
#define SYSCTL_PRACMP           0x400FEA3C  // Analog Comparator Peripheral
// Ready
#define SYSCTL_PRPWM            0x400FEA40  // Pulse Width Modulator Peripheral
// Ready
#define SYSCTL_PRQEI            0x400FEA44  // Quadrature Encoder Interface
// Peripheral Ready
#define SYSCTL_PREEPROM         0x400FEA58  // EEPROM Peripheral Ready
#define SYSCTL_PRCCM            0x400FEA74  // CRC and Cryptographic Modules
// Peripheral Ready
#define SYSCTL_PRLCD            0x400FEA90  // LCD Controller Peripheral Ready
#define SYSCTL_PROWIRE          0x400FEA98  // 1-Wire Peripheral Ready
#define SYSCTL_PREMAC           0x400FEA9C  // Ethernet MAC Peripheral Ready
#define SYSCTL_UNIQUEID0        0x400FEF20  // Unique ID 0
#define SYSCTL_UNIQUEID1        0x400FEF24  // Unique ID 1
#define SYSCTL_UNIQUEID2        0x400FEF28  // Unique ID 2
#define SYSCTL_UNIQUEID3        0x400FEF2C  // Unique ID 3
// #define SYSCTL_CCMCGREQ         0x44030204  // Cryptographic Modules Clock
//                                             // Gating Request

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DID0 register.
//
//*****************************************************************************
#define SYSCTL_DID0_VER_M       0x70000000  // DID0 Version
#define SYSCTL_DID0_VER_1       0x10000000  // Second version of the DID0
// register format.
#define SYSCTL_DID0_CLASS_M     0x00FF0000  // Device Class
#define SYSCTL_DID0_CLASS_MSP432E4                                            \
                                0x000C0000  // MSP432E4 microcontrollers
#define SYSCTL_DID0_MAJ_M       0x0000FF00  // Major Revision
#define SYSCTL_DID0_MAJ_REVA    0x00000000  // Revision A (initial device)
#define SYSCTL_DID0_MAJ_REVB    0x00000100  // Revision B (first base layer
// revision)
#define SYSCTL_DID0_MAJ_REVC    0x00000200  // Revision C (second base layer
// revision)
#define SYSCTL_DID0_MIN_M       0x000000FF  // Minor Revision
#define SYSCTL_DID0_MIN_0       0x00000000  // Initial device, or a major
// revision update
#define SYSCTL_DID0_MIN_1       0x00000001  // First metal layer change
#define SYSCTL_DID0_MIN_2       0x00000002  // Second metal layer change

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DID1 register.
//
//*****************************************************************************
#define SYSCTL_DID1_VER_M       0xF0000000  // DID1 Version
#define SYSCTL_DID1_FAM_M       0x0F000000  // Family
#define SYSCTL_DID1_FAM_MSP432E4                                              \
                                0x00000000  // MSP432E4 family of
// microcontollers
#define SYSCTL_DID1_PRTNO_M     0x00FF0000  // Part Number
#define SYSCTL_DID1_PRTNO_MSP432E401Y                                         \
                                0x002D0000  // MSP432E401Y
#define SYSCTL_DID1_PRTNO_MSP432E411Y                                         \
                                0x00320000  // MSP432E411Y
#define SYSCTL_DID1_PINCNT_M    0x0000E000  // Package Pin Count
#define SYSCTL_DID1_PINCNT_128  0x0000C000  // 128-pin TQFP package
#define SYSCTL_DID1_PINCNT_212  0x0000E000  // 212-pin BGA package
#define SYSCTL_DID1_TEMP_M      0x000000E0  // Temperature Range
#define SYSCTL_DID1_TEMP_C      0x00000000  // Commercial temperature range
#define SYSCTL_DID1_TEMP_I      0x00000020  // Industrial temperature range
#define SYSCTL_DID1_TEMP_E      0x00000040  // Extended temperature range
#define SYSCTL_DID1_TEMP_IE     0x00000060  // Available in both industrial
// temperature range (-40C to 85C)
// and extended temperature range
// (-40C to 105C) devices. See
#define SYSCTL_DID1_PKG_M       0x00000018  // Package Type
#define SYSCTL_DID1_PKG_QFP     0x00000008  // QFP package
#define SYSCTL_DID1_PKG_BGA     0x00000010  // BGA package
#define SYSCTL_DID1_ROHS        0x00000004  // RoHS-Compliance
#define SYSCTL_DID1_QUAL_M      0x00000003  // Qualification Status
#define SYSCTL_DID1_QUAL_ES     0x00000000  // Engineering Sample (unqualified)
#define SYSCTL_DID1_QUAL_PP     0x00000001  // Pilot Production (unqualified)
#define SYSCTL_DID1_QUAL_FQ     0x00000002  // Fully Qualified

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PTBOCTL register.
//
//*****************************************************************************
#define SYSCTL_PTBOCTL_VDDA_UBOR_M                                            \
                                0x00000300  // VDDA under BOR Event Action
#define SYSCTL_PTBOCTL_VDDA_UBOR_NONE                                         \
                                0x00000000  // No Action
#define SYSCTL_PTBOCTL_VDDA_UBOR_SYSINT                                       \
                                0x00000100  // System control interrupt
#define SYSCTL_PTBOCTL_VDDA_UBOR_NMI                                          \
                                0x00000200  // NMI
#define SYSCTL_PTBOCTL_VDDA_UBOR_RST                                          \
                                0x00000300  // Reset
#define SYSCTL_PTBOCTL_VDD_UBOR_M                                             \
                                0x00000003  // VDD (VDDS) under BOR Event
// Action
#define SYSCTL_PTBOCTL_VDD_UBOR_NONE                                          \
                                0x00000000  // No Action
#define SYSCTL_PTBOCTL_VDD_UBOR_SYSINT                                        \
                                0x00000001  // System control interrupt
#define SYSCTL_PTBOCTL_VDD_UBOR_NMI                                           \
                                0x00000002  // NMI
#define SYSCTL_PTBOCTL_VDD_UBOR_RST                                           \
                                0x00000003  // Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RIS register.
//
//*****************************************************************************
#define SYSCTL_RIS_MOSCPUPRIS   0x00000100  // MOSC Power Up Raw Interrupt
// Status
#define SYSCTL_RIS_PLLLRIS      0x00000040  // PLL Lock Raw Interrupt Status
#define SYSCTL_RIS_MOFRIS       0x00000008  // Main Oscillator Failure Raw
// Interrupt Status
#define SYSCTL_RIS_BORRIS       0x00000002  // Brown-Out Reset Raw Interrupt
// Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_IMC register.
//
//*****************************************************************************
#define SYSCTL_IMC_MOSCPUPIM    0x00000100  // MOSC Power Up Interrupt Mask
#define SYSCTL_IMC_PLLLIM       0x00000040  // PLL Lock Interrupt Mask
#define SYSCTL_IMC_MOFIM        0x00000008  // Main Oscillator Failure
// Interrupt Mask
#define SYSCTL_IMC_BORIM        0x00000002  // Brown-Out Reset Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_MISC register.
//
//*****************************************************************************
#define SYSCTL_MISC_MOSCPUPMIS  0x00000100  // MOSC Power Up Masked Interrupt
// Status
#define SYSCTL_MISC_PLLLMIS     0x00000040  // PLL Lock Masked Interrupt Status
#define SYSCTL_MISC_MOFMIS      0x00000008  // Main Oscillator Failure Masked
// Interrupt Status
#define SYSCTL_MISC_BORMIS      0x00000002  // BOR Masked Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RESC register.
//
//*****************************************************************************
#define SYSCTL_RESC_MOSCFAIL    0x00010000  // MOSC Failure Reset
#define SYSCTL_RESC_HSSR        0x00001000  // HSSR Reset
#define SYSCTL_RESC_WDT1        0x00000020  // Watchdog Timer 1 Reset
#define SYSCTL_RESC_SW          0x00000010  // Software Reset
#define SYSCTL_RESC_WDT0        0x00000008  // Watchdog Timer 0 Reset
#define SYSCTL_RESC_BOR         0x00000004  // Brown-Out Reset
#define SYSCTL_RESC_POR         0x00000002  // Power-On Reset
#define SYSCTL_RESC_EXT         0x00000001  // External Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PWRTC register.
//
//*****************************************************************************
#define SYSCTL_PWRTC_VDDA_UBOR  0x00000010  // VDDA Under BOR Status
#define SYSCTL_PWRTC_VDD_UBOR   0x00000001  // VDD Under BOR Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_NMIC register.
//
//*****************************************************************************
#define SYSCTL_NMIC_MOSCFAIL    0x00010000  // MOSC Failure NMI
#define SYSCTL_NMIC_TAMPER      0x00000200  // Tamper Event NMI
#define SYSCTL_NMIC_WDT1        0x00000020  // Watch Dog Timer (WDT) 1 NMI
#define SYSCTL_NMIC_WDT0        0x00000008  // Watch Dog Timer (WDT) 0 NMI
#define SYSCTL_NMIC_POWER       0x00000004  // Power/Brown Out Event NMI
#define SYSCTL_NMIC_EXTERNAL    0x00000001  // External Pin NMI

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_MOSCCTL register.
//
//*****************************************************************************
#define SYSCTL_MOSCCTL_OSCRNG   0x00000010  // Oscillator Range
#define SYSCTL_MOSCCTL_PWRDN    0x00000008  // Power Down
#define SYSCTL_MOSCCTL_NOXTAL   0x00000004  // No Crystal Connected
#define SYSCTL_MOSCCTL_MOSCIM   0x00000002  // MOSC Failure Action
#define SYSCTL_MOSCCTL_CVAL     0x00000001  // Clock Validation for MOSC

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RSCLKCFG
// register.
//
//*****************************************************************************
#define SYSCTL_RSCLKCFG_MEMTIMU 0x80000000  // Memory Timing Register Update
#define SYSCTL_RSCLKCFG_NEWFREQ 0x40000000  // New PLLFREQ Accept
#define SYSCTL_RSCLKCFG_ACG     0x20000000  // Auto Clock Gating
#define SYSCTL_RSCLKCFG_USEPLL  0x10000000  // Use PLL
#define SYSCTL_RSCLKCFG_PLLSRC_M                                              \
                                0x0F000000  // PLL Source
#define SYSCTL_RSCLKCFG_PLLSRC_PIOSC                                          \
                                0x00000000  // PIOSC is PLL input clock source
#define SYSCTL_RSCLKCFG_PLLSRC_MOSC                                           \
                                0x03000000  // MOSC is the PLL input clock
// source
#define SYSCTL_RSCLKCFG_OSCSRC_M                                              \
                                0x00F00000  // Oscillator Source
#define SYSCTL_RSCLKCFG_OSCSRC_PIOSC                                          \
                                0x00000000  // PIOSC is oscillator source
#define SYSCTL_RSCLKCFG_OSCSRC_LFIOSC                                         \
                                0x00200000  // LFIOSC is oscillator source
#define SYSCTL_RSCLKCFG_OSCSRC_MOSC                                           \
                                0x00300000  // MOSC is oscillator source
#define SYSCTL_RSCLKCFG_OSCSRC_RTC                                            \
                                0x00400000  // Hibernation Module RTC
// Oscillator (RTCOSC)
#define SYSCTL_RSCLKCFG_OSYSDIV_M                                             \
                                0x000FFC00  // Oscillator System Clock Divisor
#define SYSCTL_RSCLKCFG_PSYSDIV_M                                             \
                                0x000003FF  // PLL System Clock Divisor
#define SYSCTL_RSCLKCFG_OSYSDIV_S                                             \
                                10
#define SYSCTL_RSCLKCFG_PSYSDIV_S                                             \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_MEMTIM0 register.
//
//*****************************************************************************
#define SYSCTL_MEMTIM0_EBCHT_M  0x03C00000  // EEPROM Clock High Time
#define SYSCTL_MEMTIM0_EBCHT_0_5                                              \
                                0x00000000  // 1/2 system clock period
#define SYSCTL_MEMTIM0_EBCHT_1  0x00400000  // 1 system clock period
#define SYSCTL_MEMTIM0_EBCHT_1_5                                              \
                                0x00800000  // 1.5 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_2  0x00C00000  // 2 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_2_5                                              \
                                0x01000000  // 2.5 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_3  0x01400000  // 3 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_3_5                                              \
                                0x01800000  // 3.5 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_4  0x01C00000  // 4 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_4_5                                              \
                                0x02000000  // 4.5 system clock periods
#define SYSCTL_MEMTIM0_EBCE     0x00200000  // EEPROM Bank Clock Edge
#define SYSCTL_MEMTIM0_MB1      0x00100010  // Must be one
#define SYSCTL_MEMTIM0_EWS_M    0x000F0000  // EEPROM Wait States
#define SYSCTL_MEMTIM0_FBCHT_M  0x000003C0  // Flash Bank Clock High Time
#define SYSCTL_MEMTIM0_FBCHT_0_5                                              \
                                0x00000000  // 1/2 system clock period
#define SYSCTL_MEMTIM0_FBCHT_1  0x00000040  // 1 system clock period
#define SYSCTL_MEMTIM0_FBCHT_1_5                                              \
                                0x00000080  // 1.5 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_2  0x000000C0  // 2 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_2_5                                              \
                                0x00000100  // 2.5 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_3  0x00000140  // 3 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_3_5                                              \
                                0x00000180  // 3.5 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_4  0x000001C0  // 4 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_4_5                                              \
                                0x00000200  // 4.5 system clock periods
#define SYSCTL_MEMTIM0_FBCE     0x00000020  // Flash Bank Clock Edge
#define SYSCTL_MEMTIM0_FWS_M    0x0000000F  // Flash Wait State
#define SYSCTL_MEMTIM0_EWS_S    16
#define SYSCTL_MEMTIM0_FWS_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_ALTCLKCFG
// register.
//
//*****************************************************************************
#define SYSCTL_ALTCLKCFG_ALTCLK_M                                             \
                                0x0000000F  // Alternate Clock Source
#define SYSCTL_ALTCLKCFG_ALTCLK_PIOSC                                         \
                                0x00000000  // PIOSC
#define SYSCTL_ALTCLKCFG_ALTCLK_RTCOSC                                        \
                                0x00000003  // Hibernation Module Real-time
// clock output (RTCOSC)
#define SYSCTL_ALTCLKCFG_ALTCLK_LFIOSC                                        \
                                0x00000004  // Low-frequency internal
// oscillator (LFIOSC)

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DSCLKCFG
// register.
//
//*****************************************************************************
#define SYSCTL_DSCLKCFG_PIOSCPD 0x80000000  // PIOSC Power Down
#define SYSCTL_DSCLKCFG_MOSCDPD 0x40000000  // MOSC Disable Power Down
#define SYSCTL_DSCLKCFG_DSOSCSRC_M                                            \
                                0x00F00000  // Deep Sleep Oscillator Source
#define SYSCTL_DSCLKCFG_DSOSCSRC_PIOSC                                        \
                                0x00000000  // PIOSC
#define SYSCTL_DSCLKCFG_DSOSCSRC_LFIOSC                                       \
                                0x00200000  // LFIOSC
#define SYSCTL_DSCLKCFG_DSOSCSRC_MOSC                                         \
                                0x00300000  // MOSC
#define SYSCTL_DSCLKCFG_DSOSCSRC_RTC                                          \
                                0x00400000  // Hibernation Module RTCOSC
#define SYSCTL_DSCLKCFG_DSSYSDIV_M                                            \
                                0x000003FF  // Deep Sleep Clock Divisor
#define SYSCTL_DSCLKCFG_DSSYSDIV_S                                            \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DIVSCLK register.
//
//*****************************************************************************
#define SYSCTL_DIVSCLK_EN       0x80000000  // DIVSCLK Enable
#define SYSCTL_DIVSCLK_SRC_M    0x00030000  // Clock Source
#define SYSCTL_DIVSCLK_SRC_SYSCLK                                             \
                                0x00000000  // System Clock
#define SYSCTL_DIVSCLK_SRC_PIOSC                                              \
                                0x00010000  // PIOSC
#define SYSCTL_DIVSCLK_SRC_MOSC 0x00020000  // MOSC
#define SYSCTL_DIVSCLK_DIV_M    0x000000FF  // Divisor Value
#define SYSCTL_DIVSCLK_DIV_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SYSPROP register.
//
//*****************************************************************************
#define SYSCTL_SYSPROP_FPU      0x00000001  // FPU Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PIOSCCAL
// register.
//
//*****************************************************************************
#define SYSCTL_PIOSCCAL_UTEN    0x80000000  // Use User Trim Value
#define SYSCTL_PIOSCCAL_CAL     0x00000200  // Start Calibration
#define SYSCTL_PIOSCCAL_UPDATE  0x00000100  // Update Trim
#define SYSCTL_PIOSCCAL_UT_M    0x0000007F  // User Trim Value
#define SYSCTL_PIOSCCAL_UT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PIOSCSTAT
// register.
//
//*****************************************************************************
#define SYSCTL_PIOSCSTAT_DT_M   0x007F0000  // Default Trim Value
#define SYSCTL_PIOSCSTAT_CR_M   0x00000300  // Calibration Result
#define SYSCTL_PIOSCSTAT_CRNONE 0x00000000  // Calibration has not been
// attempted
#define SYSCTL_PIOSCSTAT_CRPASS 0x00000100  // The last calibration operation
// completed to meet 1% accuracy
#define SYSCTL_PIOSCSTAT_CRFAIL 0x00000200  // The last calibration operation
// failed to meet 1% accuracy
#define SYSCTL_PIOSCSTAT_CT_M   0x0000007F  // Calibration Trim Value
#define SYSCTL_PIOSCSTAT_DT_S   16
#define SYSCTL_PIOSCSTAT_CT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PLLFREQ0
// register.
//
//*****************************************************************************
#define SYSCTL_PLLFREQ0_PLLPWR  0x00800000  // PLL Power
#define SYSCTL_PLLFREQ0_MFRAC_M 0x000FFC00  // PLL M Fractional Value
#define SYSCTL_PLLFREQ0_MINT_M  0x000003FF  // PLL M Integer Value
#define SYSCTL_PLLFREQ0_MFRAC_S 10
#define SYSCTL_PLLFREQ0_MINT_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PLLFREQ1
// register.
//
//*****************************************************************************
#define SYSCTL_PLLFREQ1_Q_M     0x00001F00  // PLL Q Value
#define SYSCTL_PLLFREQ1_N_M     0x0000001F  // PLL N Value
#define SYSCTL_PLLFREQ1_Q_S     8
#define SYSCTL_PLLFREQ1_N_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PLLSTAT register.
//
//*****************************************************************************
#define SYSCTL_PLLSTAT_LOCK     0x00000001  // PLL Lock

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SLPPWRCFG
// register.
//
//*****************************************************************************
#define SYSCTL_SLPPWRCFG_FLASHPM_M                                            \
                                0x00000030  // Flash Power Modes
#define SYSCTL_SLPPWRCFG_FLASHPM_NRM                                          \
                                0x00000000  // Active Mode
#define SYSCTL_SLPPWRCFG_FLASHPM_SLP                                          \
                                0x00000020  // Low Power Mode
#define SYSCTL_SLPPWRCFG_SRAMPM_M                                             \
                                0x00000003  // SRAM Power Modes
#define SYSCTL_SLPPWRCFG_SRAMPM_NRM                                           \
                                0x00000000  // Active Mode
#define SYSCTL_SLPPWRCFG_SRAMPM_SBY                                           \
                                0x00000001  // Standby Mode
#define SYSCTL_SLPPWRCFG_SRAMPM_LP                                            \
                                0x00000003  // Low Power Mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DSLPPWRCFG
// register.
//
//*****************************************************************************
#define SYSCTL_DSLPPWRCFG_LDOSM 0x00000200  // LDO Sleep Mode
#define SYSCTL_DSLPPWRCFG_TSPD  0x00000100  // Temperature Sense Power Down
#define SYSCTL_DSLPPWRCFG_FLASHPM_M                                           \
                                0x00000030  // Flash Power Modes
#define SYSCTL_DSLPPWRCFG_FLASHPM_NRM                                         \
                                0x00000000  // Active Mode
#define SYSCTL_DSLPPWRCFG_FLASHPM_SLP                                         \
                                0x00000020  // Low Power Mode
#define SYSCTL_DSLPPWRCFG_SRAMPM_M                                            \
                                0x00000003  // SRAM Power Modes
#define SYSCTL_DSLPPWRCFG_SRAMPM_NRM                                          \
                                0x00000000  // Active Mode
#define SYSCTL_DSLPPWRCFG_SRAMPM_SBY                                          \
                                0x00000001  // Standby Mode
#define SYSCTL_DSLPPWRCFG_SRAMPM_LP                                           \
                                0x00000003  // Low Power Mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_NVMSTAT register.
//
//*****************************************************************************
#define SYSCTL_NVMSTAT_FWB      0x00000001  // 32 Word Flash Write Buffer
// Available

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_LDOSPCTL
// register.
//
//*****************************************************************************
#define SYSCTL_LDOSPCTL_VADJEN  0x80000000  // Voltage Adjust Enable
#define SYSCTL_LDOSPCTL_VLDO_M  0x000000FF  // LDO Output Voltage
#define SYSCTL_LDOSPCTL_VLDO_0_90V                                            \
                                0x00000012  // 0.90 V
#define SYSCTL_LDOSPCTL_VLDO_0_95V                                            \
                                0x00000013  // 0.95 V
#define SYSCTL_LDOSPCTL_VLDO_1_00V                                            \
                                0x00000014  // 1.00 V
#define SYSCTL_LDOSPCTL_VLDO_1_05V                                            \
                                0x00000015  // 1.05 V
#define SYSCTL_LDOSPCTL_VLDO_1_10V                                            \
                                0x00000016  // 1.10 V
#define SYSCTL_LDOSPCTL_VLDO_1_15V                                            \
                                0x00000017  // 1.15 V
#define SYSCTL_LDOSPCTL_VLDO_1_20V                                            \
                                0x00000018  // 1.20 V

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_LDODPCTL
// register.
//
//*****************************************************************************
#define SYSCTL_LDODPCTL_VADJEN  0x80000000  // Voltage Adjust Enable
#define SYSCTL_LDODPCTL_VLDO_M  0x000000FF  // LDO Output Voltage
#define SYSCTL_LDODPCTL_VLDO_0_90V                                            \
                                0x00000012  // 0.90 V
#define SYSCTL_LDODPCTL_VLDO_0_95V                                            \
                                0x00000013  // 0.95 V
#define SYSCTL_LDODPCTL_VLDO_1_00V                                            \
                                0x00000014  // 1.00 V
#define SYSCTL_LDODPCTL_VLDO_1_05V                                            \
                                0x00000015  // 1.05 V
#define SYSCTL_LDODPCTL_VLDO_1_10V                                            \
                                0x00000016  // 1.10 V
#define SYSCTL_LDODPCTL_VLDO_1_15V                                            \
                                0x00000017  // 1.15 V
#define SYSCTL_LDODPCTL_VLDO_1_20V                                            \
                                0x00000018  // 1.20 V

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RESBEHAVCTL
// register.
//
//*****************************************************************************
#define SYSCTL_RESBEHAVCTL_WDOG1_M                                            \
                                0x000000C0  // Watchdog 1 Reset Operation
#define SYSCTL_RESBEHAVCTL_WDOG1_SYSRST                                       \
                                0x00000080  // Watchdog 1 issues a system
// reset. The application starts
// within 10 us
#define SYSCTL_RESBEHAVCTL_WDOG1_POR                                          \
                                0x000000C0  // Watchdog 1 issues a simulated
// POR sequence. Application starts
// less than 500 us after
// deassertion (Default)
#define SYSCTL_RESBEHAVCTL_WDOG0_M                                            \
                                0x00000030  // Watchdog 0 Reset Operation
#define SYSCTL_RESBEHAVCTL_WDOG0_SYSRST                                       \
                                0x00000020  // Watchdog 0 issues a system
// reset. The application starts
// within 10 us
#define SYSCTL_RESBEHAVCTL_WDOG0_POR                                          \
                                0x00000030  // Watchdog 0 issues a simulated
// POR sequence. Application starts
// less than 500 us after
// deassertion (Default)
#define SYSCTL_RESBEHAVCTL_BOR_M                                              \
                                0x0000000C  // BOR Reset operation
#define SYSCTL_RESBEHAVCTL_BOR_SYSRST                                         \
                                0x00000008  // Brown Out Reset issues system
// reset. The application starts
// within 10 us
#define SYSCTL_RESBEHAVCTL_BOR_POR                                            \
                                0x0000000C  // Brown Out Reset issues a
// simulated POR sequence. The
// application starts less than 500
// us after deassertion (Default)
#define SYSCTL_RESBEHAVCTL_EXTRES_M                                           \
                                0x00000003  // External RST Pin Operation
#define SYSCTL_RESBEHAVCTL_EXTRES_SYSRST                                      \
                                0x00000002  // External RST assertion issues a
// system reset. The application
// starts within 10 us
#define SYSCTL_RESBEHAVCTL_EXTRES_POR                                         \
                                0x00000003  // External RST assertion issues a
// simulated POR sequence.
// Application starts less than 500
// us after deassertion (Default)

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_HSSR register.
//
//*****************************************************************************
#define SYSCTL_HSSR_KEY_M       0xFF000000  // Write Key
#define SYSCTL_HSSR_CDOFF_M     0x00FFFFFF  // Command Descriptor Pointer
#define SYSCTL_HSSR_KEY_S       24
#define SYSCTL_HSSR_CDOFF_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_USBPDS register.
//
//*****************************************************************************
#define SYSCTL_USBPDS_MEMSTAT_M 0x0000000C  // Memory Array Power Status
#define SYSCTL_USBPDS_MEMSTAT_OFF                                             \
                                0x00000000  // Array OFF
#define SYSCTL_USBPDS_MEMSTAT_RETAIN                                          \
                                0x00000004  // SRAM Retention
#define SYSCTL_USBPDS_MEMSTAT_ON                                              \
                                0x0000000C  // Array On
#define SYSCTL_USBPDS_PWRSTAT_M 0x00000003  // Power Domain Status
#define SYSCTL_USBPDS_PWRSTAT_OFF                                             \
                                0x00000000  // OFF
#define SYSCTL_USBPDS_PWRSTAT_ON                                              \
                                0x00000003  // ON

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_USBMPC register.
//
//*****************************************************************************
#define SYSCTL_USBMPC_PWRCTL_M  0x00000003  // Memory Array Power Control
#define SYSCTL_USBMPC_PWRCTL_OFF                                              \
                                0x00000000  // Array OFF
#define SYSCTL_USBMPC_PWRCTL_RETAIN                                           \
                                0x00000001  // SRAM Retention
#define SYSCTL_USBMPC_PWRCTL_ON 0x00000003  // Array On

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_EMACPDS register.
//
//*****************************************************************************
#define SYSCTL_EMACPDS_MEMSTAT_M                                              \
                                0x0000000C  // Memory Array Power Status
#define SYSCTL_EMACPDS_MEMSTAT_OFF                                            \
                                0x00000000  // Array OFF
#define SYSCTL_EMACPDS_MEMSTAT_ON                                             \
                                0x0000000C  // Array On
#define SYSCTL_EMACPDS_PWRSTAT_M                                              \
                                0x00000003  // Power Domain Status
#define SYSCTL_EMACPDS_PWRSTAT_OFF                                            \
                                0x00000000  // OFF
#define SYSCTL_EMACPDS_PWRSTAT_ON                                             \
                                0x00000003  // ON

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_EMACMPC register.
//
//*****************************************************************************
#define SYSCTL_EMACMPC_PWRCTL_M 0x00000003  // Memory Array Power Control
#define SYSCTL_EMACMPC_PWRCTL_OFF                                             \
                                0x00000000  // Array OFF
#define SYSCTL_EMACMPC_PWRCTL_ON                                              \
                                0x00000003  // Array On

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_LCDMPC register.
//
//*****************************************************************************
#define SYSCTL_LCDMPC_PWRCTL_M  0x00000003  // Memory Array Power Control
#define SYSCTL_LCDMPC_PWRCTL_OFF                                              \
                                0x00000000  // Array OFF
#define SYSCTL_LCDMPC_PWRCTL_ON 0x00000003  // Array On

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPWD register.
//
//*****************************************************************************
#define SYSCTL_PPWD_P1          0x00000002  // Watchdog Timer 1 Present
#define SYSCTL_PPWD_P0          0x00000001  // Watchdog Timer 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPTIMER register.
//
//*****************************************************************************
#define SYSCTL_PPTIMER_P7       0x00000080  // 16/32-Bit General-Purpose Timer
// 7 Present
#define SYSCTL_PPTIMER_P6       0x00000040  // 16/32-Bit General-Purpose Timer
// 6 Present
#define SYSCTL_PPTIMER_P5       0x00000020  // 16/32-Bit General-Purpose Timer
// 5 Present
#define SYSCTL_PPTIMER_P4       0x00000010  // 16/32-Bit General-Purpose Timer
// 4 Present
#define SYSCTL_PPTIMER_P3       0x00000008  // 16/32-Bit General-Purpose Timer
// 3 Present
#define SYSCTL_PPTIMER_P2       0x00000004  // 16/32-Bit General-Purpose Timer
// 2 Present
#define SYSCTL_PPTIMER_P1       0x00000002  // 16/32-Bit General-Purpose Timer
// 1 Present
#define SYSCTL_PPTIMER_P0       0x00000001  // 16/32-Bit General-Purpose Timer
// 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPGPIO register.
//
//*****************************************************************************
#define SYSCTL_PPGPIO_P17       0x00020000  // GPIO Port T Present
#define SYSCTL_PPGPIO_P16       0x00010000  // GPIO Port S Present
#define SYSCTL_PPGPIO_P15       0x00008000  // GPIO Port R Present
#define SYSCTL_PPGPIO_P14       0x00004000  // GPIO Port Q Present
#define SYSCTL_PPGPIO_P13       0x00002000  // GPIO Port P Present
#define SYSCTL_PPGPIO_P12       0x00001000  // GPIO Port N Present
#define SYSCTL_PPGPIO_P11       0x00000800  // GPIO Port M Present
#define SYSCTL_PPGPIO_P10       0x00000400  // GPIO Port L Present
#define SYSCTL_PPGPIO_P9        0x00000200  // GPIO Port K Present
#define SYSCTL_PPGPIO_P8        0x00000100  // GPIO Port J Present
#define SYSCTL_PPGPIO_P7        0x00000080  // GPIO Port H Present
#define SYSCTL_PPGPIO_P6        0x00000040  // GPIO Port G Present
#define SYSCTL_PPGPIO_P5        0x00000020  // GPIO Port F Present
#define SYSCTL_PPGPIO_P4        0x00000010  // GPIO Port E Present
#define SYSCTL_PPGPIO_P3        0x00000008  // GPIO Port D Present
#define SYSCTL_PPGPIO_P2        0x00000004  // GPIO Port C Present
#define SYSCTL_PPGPIO_P1        0x00000002  // GPIO Port B Present
#define SYSCTL_PPGPIO_P0        0x00000001  // GPIO Port A Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPDMA register.
//
//*****************************************************************************
#define SYSCTL_PPDMA_P0         0x00000001  // uDMA Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPEPI register.
//
//*****************************************************************************
#define SYSCTL_PPEPI_P0         0x00000001  // EPI Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPHIB register.
//
//*****************************************************************************
#define SYSCTL_PPHIB_P0         0x00000001  // Hibernation Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPUART register.
//
//*****************************************************************************
#define SYSCTL_PPUART_P7        0x00000080  // UART Module 7 Present
#define SYSCTL_PPUART_P6        0x00000040  // UART Module 6 Present
#define SYSCTL_PPUART_P5        0x00000020  // UART Module 5 Present
#define SYSCTL_PPUART_P4        0x00000010  // UART Module 4 Present
#define SYSCTL_PPUART_P3        0x00000008  // UART Module 3 Present
#define SYSCTL_PPUART_P2        0x00000004  // UART Module 2 Present
#define SYSCTL_PPUART_P1        0x00000002  // UART Module 1 Present
#define SYSCTL_PPUART_P0        0x00000001  // UART Module 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPSSI register.
//
//*****************************************************************************
#define SYSCTL_PPSSI_P3         0x00000008  // SSI Module 3 Present
#define SYSCTL_PPSSI_P2         0x00000004  // SSI Module 2 Present
#define SYSCTL_PPSSI_P1         0x00000002  // SSI Module 1 Present
#define SYSCTL_PPSSI_P0         0x00000001  // SSI Module 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPI2C register.
//
//*****************************************************************************
#define SYSCTL_PPI2C_P9         0x00000200  // I2C Module 9 Present
#define SYSCTL_PPI2C_P8         0x00000100  // I2C Module 8 Present
#define SYSCTL_PPI2C_P7         0x00000080  // I2C Module 7 Present
#define SYSCTL_PPI2C_P6         0x00000040  // I2C Module 6 Present
#define SYSCTL_PPI2C_P5         0x00000020  // I2C Module 5 Present
#define SYSCTL_PPI2C_P4         0x00000010  // I2C Module 4 Present
#define SYSCTL_PPI2C_P3         0x00000008  // I2C Module 3 Present
#define SYSCTL_PPI2C_P2         0x00000004  // I2C Module 2 Present
#define SYSCTL_PPI2C_P1         0x00000002  // I2C Module 1 Present
#define SYSCTL_PPI2C_P0         0x00000001  // I2C Module 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPUSB register.
//
//*****************************************************************************
#define SYSCTL_PPUSB_P0         0x00000001  // USB Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPEPHY register.
//
//*****************************************************************************
#define SYSCTL_PPEPHY_P0        0x00000001  // Ethernet PHY Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPCAN register.
//
//*****************************************************************************
#define SYSCTL_PPCAN_P1         0x00000002  // CAN Module 1 Present
#define SYSCTL_PPCAN_P0         0x00000001  // CAN Module 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPADC register.
//
//*****************************************************************************
#define SYSCTL_PPADC_P1         0x00000002  // ADC Module 1 Present
#define SYSCTL_PPADC_P0         0x00000001  // ADC Module 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPACMP register.
//
//*****************************************************************************
#define SYSCTL_PPACMP_P0        0x00000001  // Analog Comparator Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPPWM register.
//
//*****************************************************************************
#define SYSCTL_PPPWM_P1         0x00000002  // PWM Module 1 Present
#define SYSCTL_PPPWM_P0         0x00000001  // PWM Module 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPQEI register.
//
//*****************************************************************************
#define SYSCTL_PPQEI_P1         0x00000002  // QEI Module 1 Present
#define SYSCTL_PPQEI_P0         0x00000001  // QEI Module 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPEEPROM
// register.
//
//*****************************************************************************
#define SYSCTL_PPEEPROM_P0      0x00000001  // EEPROM Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPCCM register.
//
//*****************************************************************************
#define SYSCTL_PPCCM_P0         0x00000001  // CRC and Cryptographic Modules
// Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPLCD register.
//
//*****************************************************************************
#define SYSCTL_PPLCD_P0         0x00000001  // LCD Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPOWIRE register.
//
//*****************************************************************************
#define SYSCTL_PPOWIRE_P0       0x00000001  // 1-Wire Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPEMAC register.
//
//*****************************************************************************
#define SYSCTL_PPEMAC_P0        0x00000001  // Ethernet Controller Module
// Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRWD register.
//
//*****************************************************************************
#define SYSCTL_SRWD_R1          0x00000002  // Watchdog Timer 1 Software Reset
#define SYSCTL_SRWD_R0          0x00000001  // Watchdog Timer 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRTIMER register.
//
//*****************************************************************************
#define SYSCTL_SRTIMER_R7       0x00000080  // 16/32-Bit General-Purpose Timer
// 7 Software Reset
#define SYSCTL_SRTIMER_R6       0x00000040  // 16/32-Bit General-Purpose Timer
// 6 Software Reset
#define SYSCTL_SRTIMER_R5       0x00000020  // 16/32-Bit General-Purpose Timer
// 5 Software Reset
#define SYSCTL_SRTIMER_R4       0x00000010  // 16/32-Bit General-Purpose Timer
// 4 Software Reset
#define SYSCTL_SRTIMER_R3       0x00000008  // 16/32-Bit General-Purpose Timer
// 3 Software Reset
#define SYSCTL_SRTIMER_R2       0x00000004  // 16/32-Bit General-Purpose Timer
// 2 Software Reset
#define SYSCTL_SRTIMER_R1       0x00000002  // 16/32-Bit General-Purpose Timer
// 1 Software Reset
#define SYSCTL_SRTIMER_R0       0x00000001  // 16/32-Bit General-Purpose Timer
// 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRGPIO register.
//
//*****************************************************************************
#define SYSCTL_SRGPIO_R17       0x00020000  // GPIO Port T Software Reset
#define SYSCTL_SRGPIO_R16       0x00010000  // GPIO Port S Software Reset
#define SYSCTL_SRGPIO_R15       0x00008000  // GPIO Port R Software Reset
#define SYSCTL_SRGPIO_R14       0x00004000  // GPIO Port Q Software Reset
#define SYSCTL_SRGPIO_R13       0x00002000  // GPIO Port P Software Reset
#define SYSCTL_SRGPIO_R12       0x00001000  // GPIO Port N Software Reset
#define SYSCTL_SRGPIO_R11       0x00000800  // GPIO Port M Software Reset
#define SYSCTL_SRGPIO_R10       0x00000400  // GPIO Port L Software Reset
#define SYSCTL_SRGPIO_R9        0x00000200  // GPIO Port K Software Reset
#define SYSCTL_SRGPIO_R8        0x00000100  // GPIO Port J Software Reset
#define SYSCTL_SRGPIO_R7        0x00000080  // GPIO Port H Software Reset
#define SYSCTL_SRGPIO_R6        0x00000040  // GPIO Port G Software Reset
#define SYSCTL_SRGPIO_R5        0x00000020  // GPIO Port F Software Reset
#define SYSCTL_SRGPIO_R4        0x00000010  // GPIO Port E Software Reset
#define SYSCTL_SRGPIO_R3        0x00000008  // GPIO Port D Software Reset
#define SYSCTL_SRGPIO_R2        0x00000004  // GPIO Port C Software Reset
#define SYSCTL_SRGPIO_R1        0x00000002  // GPIO Port B Software Reset
#define SYSCTL_SRGPIO_R0        0x00000001  // GPIO Port A Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRDMA register.
//
//*****************************************************************************
#define SYSCTL_SRDMA_R0         0x00000001  // uDMA Module Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SREPI register.
//
//*****************************************************************************
#define SYSCTL_SREPI_R0         0x00000001  // EPI Module Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRHIB register.
//
//*****************************************************************************
#define SYSCTL_SRHIB_R0         0x00000001  // Hibernation Module Software
// Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRUART register.
//
//*****************************************************************************
#define SYSCTL_SRUART_R7        0x00000080  // UART Module 7 Software Reset
#define SYSCTL_SRUART_R6        0x00000040  // UART Module 6 Software Reset
#define SYSCTL_SRUART_R5        0x00000020  // UART Module 5 Software Reset
#define SYSCTL_SRUART_R4        0x00000010  // UART Module 4 Software Reset
#define SYSCTL_SRUART_R3        0x00000008  // UART Module 3 Software Reset
#define SYSCTL_SRUART_R2        0x00000004  // UART Module 2 Software Reset
#define SYSCTL_SRUART_R1        0x00000002  // UART Module 1 Software Reset
#define SYSCTL_SRUART_R0        0x00000001  // UART Module 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRSSI register.
//
//*****************************************************************************
#define SYSCTL_SRSSI_R3         0x00000008  // SSI Module 3 Software Reset
#define SYSCTL_SRSSI_R2         0x00000004  // SSI Module 2 Software Reset
#define SYSCTL_SRSSI_R1         0x00000002  // SSI Module 1 Software Reset
#define SYSCTL_SRSSI_R0         0x00000001  // SSI Module 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRI2C register.
//
//*****************************************************************************
#define SYSCTL_SRI2C_R9         0x00000200  // I2C Module 9 Software Reset
#define SYSCTL_SRI2C_R8         0x00000100  // I2C Module 8 Software Reset
#define SYSCTL_SRI2C_R7         0x00000080  // I2C Module 7 Software Reset
#define SYSCTL_SRI2C_R6         0x00000040  // I2C Module 6 Software Reset
#define SYSCTL_SRI2C_R5         0x00000020  // I2C Module 5 Software Reset
#define SYSCTL_SRI2C_R4         0x00000010  // I2C Module 4 Software Reset
#define SYSCTL_SRI2C_R3         0x00000008  // I2C Module 3 Software Reset
#define SYSCTL_SRI2C_R2         0x00000004  // I2C Module 2 Software Reset
#define SYSCTL_SRI2C_R1         0x00000002  // I2C Module 1 Software Reset
#define SYSCTL_SRI2C_R0         0x00000001  // I2C Module 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRUSB register.
//
//*****************************************************************************
#define SYSCTL_SRUSB_R0         0x00000001  // USB Module Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SREPHY register.
//
//*****************************************************************************
#define SYSCTL_SREPHY_R0        0x00000001  // Ethernet PHY Module Software
// Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRCAN register.
//
//*****************************************************************************
#define SYSCTL_SRCAN_R1         0x00000002  // CAN Module 1 Software Reset
#define SYSCTL_SRCAN_R0         0x00000001  // CAN Module 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRADC register.
//
//*****************************************************************************
#define SYSCTL_SRADC_R1         0x00000002  // ADC Module 1 Software Reset
#define SYSCTL_SRADC_R0         0x00000001  // ADC Module 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRACMP register.
//
//*****************************************************************************
#define SYSCTL_SRACMP_R0        0x00000001  // Analog Comparator Module 0
// Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRPWM register.
//
//*****************************************************************************
#define SYSCTL_SRPWM_R1         0x00000002  // PWM Module 1 Software Reset
#define SYSCTL_SRPWM_R0         0x00000001  // PWM Module 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRQEI register.
//
//*****************************************************************************
#define SYSCTL_SRQEI_R1         0x00000002  // QEI Module 1 Software Reset
#define SYSCTL_SRQEI_R0         0x00000001  // QEI Module 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SREEPROM
// register.
//
//*****************************************************************************
#define SYSCTL_SREEPROM_R0      0x00000001  // EEPROM Module Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRCCM register.
//
//*****************************************************************************
#define SYSCTL_SRCCM_R0         0x00000001  // CRC and Cryptographic Modules
// Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRLCD register.
//
//*****************************************************************************
#define SYSCTL_SRLCD_R0         0x00000001  // LCD Module 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SROWIRE register.
//
//*****************************************************************************
#define SYSCTL_SROWIRE_R0       0x00000001  // 1-Wire Module Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SREMAC register.
//
//*****************************************************************************
#define SYSCTL_SREMAC_R0        0x00000001  // Ethernet Controller MAC Module 0
// Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCWD register.
//
//*****************************************************************************
#define SYSCTL_RCGCWD_R1        0x00000002  // Watchdog Timer 1 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCWD_R0        0x00000001  // Watchdog Timer 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCTIMER
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCTIMER_R7     0x00000080  // 16/32-Bit General-Purpose Timer
// 7 Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER_R6     0x00000040  // 16/32-Bit General-Purpose Timer
// 6 Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER_R5     0x00000020  // 16/32-Bit General-Purpose Timer
// 5 Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER_R4     0x00000010  // 16/32-Bit General-Purpose Timer
// 4 Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER_R3     0x00000008  // 16/32-Bit General-Purpose Timer
// 3 Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER_R2     0x00000004  // 16/32-Bit General-Purpose Timer
// 2 Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER_R1     0x00000002  // 16/32-Bit General-Purpose Timer
// 1 Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER_R0     0x00000001  // 16/32-Bit General-Purpose Timer
// 0 Run Mode Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCGPIO
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCGPIO_R17     0x00020000  // GPIO Port T Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R16     0x00010000  // GPIO Port S Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R15     0x00008000  // GPIO Port R Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R14     0x00004000  // GPIO Port Q Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R13     0x00002000  // GPIO Port P Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R12     0x00001000  // GPIO Port N Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R11     0x00000800  // GPIO Port M Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R10     0x00000400  // GPIO Port L Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R9      0x00000200  // GPIO Port K Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R8      0x00000100  // GPIO Port J Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R7      0x00000080  // GPIO Port H Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R6      0x00000040  // GPIO Port G Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R5      0x00000020  // GPIO Port F Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R4      0x00000010  // GPIO Port E Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R3      0x00000008  // GPIO Port D Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R2      0x00000004  // GPIO Port C Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R1      0x00000002  // GPIO Port B Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R0      0x00000001  // GPIO Port A Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCDMA register.
//
//*****************************************************************************
#define SYSCTL_RCGCDMA_R0       0x00000001  // uDMA Module Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCEPI register.
//
//*****************************************************************************
#define SYSCTL_RCGCEPI_R0       0x00000001  // EPI Module Run Mode Clock Gating
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCHIB register.
//
//*****************************************************************************
#define SYSCTL_RCGCHIB_R0       0x00000001  // Hibernation Module Run Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCUART
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCUART_R7      0x00000080  // UART Module 7 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCUART_R6      0x00000040  // UART Module 6 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCUART_R5      0x00000020  // UART Module 5 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCUART_R4      0x00000010  // UART Module 4 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCUART_R3      0x00000008  // UART Module 3 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCUART_R2      0x00000004  // UART Module 2 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCUART_R1      0x00000002  // UART Module 1 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCUART_R0      0x00000001  // UART Module 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCSSI register.
//
//*****************************************************************************
#define SYSCTL_RCGCSSI_R3       0x00000008  // SSI Module 3 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCSSI_R2       0x00000004  // SSI Module 2 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCSSI_R1       0x00000002  // SSI Module 1 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCSSI_R0       0x00000001  // SSI Module 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCI2C register.
//
//*****************************************************************************
#define SYSCTL_RCGCI2C_R9       0x00000200  // I2C Module 9 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R8       0x00000100  // I2C Module 8 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R7       0x00000080  // I2C Module 7 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R6       0x00000040  // I2C Module 6 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R5       0x00000020  // I2C Module 5 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R4       0x00000010  // I2C Module 4 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R3       0x00000008  // I2C Module 3 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R2       0x00000004  // I2C Module 2 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R1       0x00000002  // I2C Module 1 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R0       0x00000001  // I2C Module 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCUSB register.
//
//*****************************************************************************
#define SYSCTL_RCGCUSB_R0       0x00000001  // USB Module Run Mode Clock Gating
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCEPHY
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCEPHY_R0      0x00000001  // Ethernet PHY Module Run Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCCAN register.
//
//*****************************************************************************
#define SYSCTL_RCGCCAN_R1       0x00000002  // CAN Module 1 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCCAN_R0       0x00000001  // CAN Module 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCADC register.
//
//*****************************************************************************
#define SYSCTL_RCGCADC_R1       0x00000002  // ADC Module 1 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCADC_R0       0x00000001  // ADC Module 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCACMP
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCACMP_R0      0x00000001  // Analog Comparator Module 0 Run
// Mode Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCPWM register.
//
//*****************************************************************************
#define SYSCTL_RCGCPWM_R1       0x00000002  // PWM Module 1 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCPWM_R0       0x00000001  // PWM Module 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCQEI register.
//
//*****************************************************************************
#define SYSCTL_RCGCQEI_R1       0x00000002  // QEI Module 1 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCQEI_R0       0x00000001  // QEI Module 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCEEPROM
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCEEPROM_R0    0x00000001  // EEPROM Module Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCCCM register.
//
//*****************************************************************************
#define SYSCTL_RCGCCCM_R0       0x00000001  // CRC and Cryptographic Modules
// Run Mode Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCLCD register.
//
//*****************************************************************************
#define SYSCTL_RCGCLCD_R0       0x00000001  // LCD Controller Module 0 Run Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCOWIRE
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCOWIRE_R0     0x00000001  // 1-Wire Module 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCEMAC
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCEMAC_R0      0x00000001  // Ethernet MAC Module 0 Run Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCWD register.
//
//*****************************************************************************
#define SYSCTL_SCGCWD_S1        0x00000002  // Watchdog Timer 1 Sleep Mode
// Clock Gating Control
#define SYSCTL_SCGCWD_S0        0x00000001  // Watchdog Timer 0 Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCTIMER
// register.
//
//*****************************************************************************
#define SYSCTL_SCGCTIMER_S7     0x00000080  // 16/32-Bit General-Purpose Timer
// 7 Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCTIMER_S6     0x00000040  // 16/32-Bit General-Purpose Timer
// 6 Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCTIMER_S5     0x00000020  // 16/32-Bit General-Purpose Timer
// 5 Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCTIMER_S4     0x00000010  // 16/32-Bit General-Purpose Timer
// 4 Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCTIMER_S3     0x00000008  // 16/32-Bit General-Purpose Timer
// 3 Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCTIMER_S2     0x00000004  // 16/32-Bit General-Purpose Timer
// 2 Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCTIMER_S1     0x00000002  // 16/32-Bit General-Purpose Timer
// 1 Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCTIMER_S0     0x00000001  // 16/32-Bit General-Purpose Timer
// 0 Sleep Mode Clock Gating
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCGPIO
// register.
//
//*****************************************************************************
#define SYSCTL_SCGCGPIO_S17     0x00020000  // GPIO Port T Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S16     0x00010000  // GPIO Port S Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S15     0x00008000  // GPIO Port R Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S14     0x00004000  // GPIO Port Q Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S13     0x00002000  // GPIO Port P Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S12     0x00001000  // GPIO Port N Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S11     0x00000800  // GPIO Port M Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S10     0x00000400  // GPIO Port L Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S9      0x00000200  // GPIO Port K Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S8      0x00000100  // GPIO Port J Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S7      0x00000080  // GPIO Port H Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S6      0x00000040  // GPIO Port G Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S5      0x00000020  // GPIO Port F Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S4      0x00000010  // GPIO Port E Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S3      0x00000008  // GPIO Port D Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S2      0x00000004  // GPIO Port C Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S1      0x00000002  // GPIO Port B Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S0      0x00000001  // GPIO Port A Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCDMA register.
//
//*****************************************************************************
#define SYSCTL_SCGCDMA_S0       0x00000001  // uDMA Module Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCEPI register.
//
//*****************************************************************************
#define SYSCTL_SCGCEPI_S0       0x00000001  // EPI Module Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCHIB register.
//
//*****************************************************************************
#define SYSCTL_SCGCHIB_S0       0x00000001  // Hibernation Module Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCUART
// register.
//
//*****************************************************************************
#define SYSCTL_SCGCUART_S7      0x00000080  // UART Module 7 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCUART_S6      0x00000040  // UART Module 6 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCUART_S5      0x00000020  // UART Module 5 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCUART_S4      0x00000010  // UART Module 4 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCUART_S3      0x00000008  // UART Module 3 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCUART_S2      0x00000004  // UART Module 2 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCUART_S1      0x00000002  // UART Module 1 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCUART_S0      0x00000001  // UART Module 0 Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCSSI register.
//
//*****************************************************************************
#define SYSCTL_SCGCSSI_S3       0x00000008  // SSI Module 3 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCSSI_S2       0x00000004  // SSI Module 2 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCSSI_S1       0x00000002  // SSI Module 1 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCSSI_S0       0x00000001  // SSI Module 0 Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCI2C register.
//
//*****************************************************************************
#define SYSCTL_SCGCI2C_S9       0x00000200  // I2C Module 9 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S8       0x00000100  // I2C Module 8 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S7       0x00000080  // I2C Module 7 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S6       0x00000040  // I2C Module 6 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S5       0x00000020  // I2C Module 5 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S4       0x00000010  // I2C Module 4 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S3       0x00000008  // I2C Module 3 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S2       0x00000004  // I2C Module 2 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S1       0x00000002  // I2C Module 1 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S0       0x00000001  // I2C Module 0 Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCUSB register.
//
//*****************************************************************************
#define SYSCTL_SCGCUSB_S0       0x00000001  // USB Module Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCEPHY
// register.
//
//*****************************************************************************
#define SYSCTL_SCGCEPHY_S0      0x00000001  // PHY Module Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCCAN register.
//
//*****************************************************************************
#define SYSCTL_SCGCCAN_S1       0x00000002  // CAN Module 1 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCCAN_S0       0x00000001  // CAN Module 0 Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCADC register.
//
//*****************************************************************************
#define SYSCTL_SCGCADC_S1       0x00000002  // ADC Module 1 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCADC_S0       0x00000001  // ADC Module 0 Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCACMP
// register.
//
//*****************************************************************************
#define SYSCTL_SCGCACMP_S0      0x00000001  // Analog Comparator Module 0 Sleep
// Mode Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCPWM register.
//
//*****************************************************************************
#define SYSCTL_SCGCPWM_S1       0x00000002  // PWM Module 1 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCPWM_S0       0x00000001  // PWM Module 0 Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCQEI register.
//
//*****************************************************************************
#define SYSCTL_SCGCQEI_S1       0x00000002  // QEI Module 1 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCQEI_S0       0x00000001  // QEI Module 0 Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCEEPROM
// register.
//
//*****************************************************************************
#define SYSCTL_SCGCEEPROM_S0    0x00000001  // EEPROM Module Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCCCM register.
//
//*****************************************************************************
#define SYSCTL_SCGCCCM_S0       0x00000001  // CRC and Cryptographic Modules
// Sleep Mode Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCLCD register.
//
//*****************************************************************************
#define SYSCTL_SCGCLCD_S0       0x00000001  // LCD Controller Module 0 Sleep
// Mode Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCOWIRE
// register.
//
//*****************************************************************************
#define SYSCTL_SCGCOWIRE_S0     0x00000001  // 1-Wire Module 0 Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCEMAC
// register.
//
//*****************************************************************************
#define SYSCTL_SCGCEMAC_S0      0x00000001  // Ethernet MAC Module 0 Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCWD register.
//
//*****************************************************************************
#define SYSCTL_DCGCWD_D1        0x00000002  // Watchdog Timer 1 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCWD_D0        0x00000001  // Watchdog Timer 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCTIMER
// register.
//
//*****************************************************************************
#define SYSCTL_DCGCTIMER_D7     0x00000080  // 16/32-Bit General-Purpose Timer
// 7 Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCTIMER_D6     0x00000040  // 16/32-Bit General-Purpose Timer
// 6 Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCTIMER_D5     0x00000020  // 16/32-Bit General-Purpose Timer
// 5 Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCTIMER_D4     0x00000010  // 16/32-Bit General-Purpose Timer
// 4 Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCTIMER_D3     0x00000008  // 16/32-Bit General-Purpose Timer
// 3 Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCTIMER_D2     0x00000004  // 16/32-Bit General-Purpose Timer
// 2 Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCTIMER_D1     0x00000002  // 16/32-Bit General-Purpose Timer
// 1 Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCTIMER_D0     0x00000001  // 16/32-Bit General-Purpose Timer
// 0 Deep-Sleep Mode Clock Gating
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCGPIO
// register.
//
//*****************************************************************************
#define SYSCTL_DCGCGPIO_D17     0x00020000  // GPIO Port T Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D16     0x00010000  // GPIO Port S Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D15     0x00008000  // GPIO Port R Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D14     0x00004000  // GPIO Port Q Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D13     0x00002000  // GPIO Port P Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D12     0x00001000  // GPIO Port N Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D11     0x00000800  // GPIO Port M Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D10     0x00000400  // GPIO Port L Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D9      0x00000200  // GPIO Port K Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D8      0x00000100  // GPIO Port J Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D7      0x00000080  // GPIO Port H Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D6      0x00000040  // GPIO Port G Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D5      0x00000020  // GPIO Port F Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D4      0x00000010  // GPIO Port E Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D3      0x00000008  // GPIO Port D Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D2      0x00000004  // GPIO Port C Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D1      0x00000002  // GPIO Port B Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D0      0x00000001  // GPIO Port A Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCDMA register.
//
//*****************************************************************************
#define SYSCTL_DCGCDMA_D0       0x00000001  // uDMA Module Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCEPI register.
//
//*****************************************************************************
#define SYSCTL_DCGCEPI_D0       0x00000001  // EPI Module Deep-Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCHIB register.
//
//*****************************************************************************
#define SYSCTL_DCGCHIB_D0       0x00000001  // Hibernation Module Deep-Sleep
// Mode Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCUART
// register.
//
//*****************************************************************************
#define SYSCTL_DCGCUART_D7      0x00000080  // UART Module 7 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCUART_D6      0x00000040  // UART Module 6 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCUART_D5      0x00000020  // UART Module 5 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCUART_D4      0x00000010  // UART Module 4 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCUART_D3      0x00000008  // UART Module 3 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCUART_D2      0x00000004  // UART Module 2 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCUART_D1      0x00000002  // UART Module 1 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCUART_D0      0x00000001  // UART Module 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCSSI register.
//
//*****************************************************************************
#define SYSCTL_DCGCSSI_D3       0x00000008  // SSI Module 3 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCSSI_D2       0x00000004  // SSI Module 2 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCSSI_D1       0x00000002  // SSI Module 1 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCSSI_D0       0x00000001  // SSI Module 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCI2C register.
//
//*****************************************************************************
#define SYSCTL_DCGCI2C_D9       0x00000200  // I2C Module 9 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D8       0x00000100  // I2C Module 8 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D7       0x00000080  // I2C Module 7 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D6       0x00000040  // I2C Module 6 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D5       0x00000020  // I2C Module 5 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D4       0x00000010  // I2C Module 4 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D3       0x00000008  // I2C Module 3 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D2       0x00000004  // I2C Module 2 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D1       0x00000002  // I2C Module 1 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D0       0x00000001  // I2C Module 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCUSB register.
//
//*****************************************************************************
#define SYSCTL_DCGCUSB_D0       0x00000001  // USB Module Deep-Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCEPHY
// register.
//
//*****************************************************************************
#define SYSCTL_DCGCEPHY_D0      0x00000001  // PHY Module Deep-Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCCAN register.
//
//*****************************************************************************
#define SYSCTL_DCGCCAN_D1       0x00000002  // CAN Module 1 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCCAN_D0       0x00000001  // CAN Module 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCADC register.
//
//*****************************************************************************
#define SYSCTL_DCGCADC_D1       0x00000002  // ADC Module 1 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCADC_D0       0x00000001  // ADC Module 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCACMP
// register.
//
//*****************************************************************************
#define SYSCTL_DCGCACMP_D0      0x00000001  // Analog Comparator Module 0
// Deep-Sleep Mode Clock Gating
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCPWM register.
//
//*****************************************************************************
#define SYSCTL_DCGCPWM_D1       0x00000002  // PWM Module 1 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCPWM_D0       0x00000001  // PWM Module 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCQEI register.
//
//*****************************************************************************
#define SYSCTL_DCGCQEI_D1       0x00000002  // QEI Module 1 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCQEI_D0       0x00000001  // QEI Module 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCEEPROM
// register.
//
//*****************************************************************************
#define SYSCTL_DCGCEEPROM_D0    0x00000001  // EEPROM Module Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCCCM register.
//
//*****************************************************************************
#define SYSCTL_DCGCCCM_D0       0x00000001  // CRC and Cryptographic Modules
// Deep-Sleep Mode Clock Gating
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCLCD register.
//
//*****************************************************************************
#define SYSCTL_DCGCLCD_D0       0x00000001  // LCD Controller Module 0
// Deep-Sleep Mode Clock Gating
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCOWIRE
// register.
//
//*****************************************************************************
#define SYSCTL_DCGCOWIRE_D0     0x00000001  // 1-Wire Module 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCEMAC
// register.
//
//*****************************************************************************
#define SYSCTL_DCGCEMAC_D0      0x00000001  // Ethernet MAC Module 0 Deep-Sleep
// Mode Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCWD register.
//
//*****************************************************************************
#define SYSCTL_PCWD_P1          0x00000002  // Watchdog Timer 1 Power Control
#define SYSCTL_PCWD_P0          0x00000001  // Watchdog Timer 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCTIMER register.
//
//*****************************************************************************
#define SYSCTL_PCTIMER_P7       0x00000080  // General-Purpose Timer 7 Power
// Control
#define SYSCTL_PCTIMER_P6       0x00000040  // General-Purpose Timer 6 Power
// Control
#define SYSCTL_PCTIMER_P5       0x00000020  // General-Purpose Timer 5 Power
// Control
#define SYSCTL_PCTIMER_P4       0x00000010  // General-Purpose Timer 4 Power
// Control
#define SYSCTL_PCTIMER_P3       0x00000008  // General-Purpose Timer 3 Power
// Control
#define SYSCTL_PCTIMER_P2       0x00000004  // General-Purpose Timer 2 Power
// Control
#define SYSCTL_PCTIMER_P1       0x00000002  // General-Purpose Timer 1 Power
// Control
#define SYSCTL_PCTIMER_P0       0x00000001  // General-Purpose Timer 0 Power
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCGPIO register.
//
//*****************************************************************************
#define SYSCTL_PCGPIO_P17       0x00020000  // GPIO Port T Power Control
#define SYSCTL_PCGPIO_P16       0x00010000  // GPIO Port S Power Control
#define SYSCTL_PCGPIO_P15       0x00008000  // GPIO Port R Power Control
#define SYSCTL_PCGPIO_P14       0x00004000  // GPIO Port Q Power Control
#define SYSCTL_PCGPIO_P13       0x00002000  // GPIO Port P Power Control
#define SYSCTL_PCGPIO_P12       0x00001000  // GPIO Port N Power Control
#define SYSCTL_PCGPIO_P11       0x00000800  // GPIO Port M Power Control
#define SYSCTL_PCGPIO_P10       0x00000400  // GPIO Port L Power Control
#define SYSCTL_PCGPIO_P9        0x00000200  // GPIO Port K Power Control
#define SYSCTL_PCGPIO_P8        0x00000100  // GPIO Port J Power Control
#define SYSCTL_PCGPIO_P7        0x00000080  // GPIO Port H Power Control
#define SYSCTL_PCGPIO_P6        0x00000040  // GPIO Port G Power Control
#define SYSCTL_PCGPIO_P5        0x00000020  // GPIO Port F Power Control
#define SYSCTL_PCGPIO_P4        0x00000010  // GPIO Port E Power Control
#define SYSCTL_PCGPIO_P3        0x00000008  // GPIO Port D Power Control
#define SYSCTL_PCGPIO_P2        0x00000004  // GPIO Port C Power Control
#define SYSCTL_PCGPIO_P1        0x00000002  // GPIO Port B Power Control
#define SYSCTL_PCGPIO_P0        0x00000001  // GPIO Port A Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCDMA register.
//
//*****************************************************************************
#define SYSCTL_PCDMA_P0         0x00000001  // uDMA Module Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCEPI register.
//
//*****************************************************************************
#define SYSCTL_PCEPI_P0         0x00000001  // EPI Module Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCHIB register.
//
//*****************************************************************************
#define SYSCTL_PCHIB_P0         0x00000001  // Hibernation Module Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCUART register.
//
//*****************************************************************************
#define SYSCTL_PCUART_P7        0x00000080  // UART Module 7 Power Control
#define SYSCTL_PCUART_P6        0x00000040  // UART Module 6 Power Control
#define SYSCTL_PCUART_P5        0x00000020  // UART Module 5 Power Control
#define SYSCTL_PCUART_P4        0x00000010  // UART Module 4 Power Control
#define SYSCTL_PCUART_P3        0x00000008  // UART Module 3 Power Control
#define SYSCTL_PCUART_P2        0x00000004  // UART Module 2 Power Control
#define SYSCTL_PCUART_P1        0x00000002  // UART Module 1 Power Control
#define SYSCTL_PCUART_P0        0x00000001  // UART Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCSSI register.
//
//*****************************************************************************
#define SYSCTL_PCSSI_P3         0x00000008  // SSI Module 3 Power Control
#define SYSCTL_PCSSI_P2         0x00000004  // SSI Module 2 Power Control
#define SYSCTL_PCSSI_P1         0x00000002  // SSI Module 1 Power Control
#define SYSCTL_PCSSI_P0         0x00000001  // SSI Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCI2C register.
//
//*****************************************************************************
#define SYSCTL_PCI2C_P9         0x00000200  // I2C Module 9 Power Control
#define SYSCTL_PCI2C_P8         0x00000100  // I2C Module 8 Power Control
#define SYSCTL_PCI2C_P7         0x00000080  // I2C Module 7 Power Control
#define SYSCTL_PCI2C_P6         0x00000040  // I2C Module 6 Power Control
#define SYSCTL_PCI2C_P5         0x00000020  // I2C Module 5 Power Control
#define SYSCTL_PCI2C_P4         0x00000010  // I2C Module 4 Power Control
#define SYSCTL_PCI2C_P3         0x00000008  // I2C Module 3 Power Control
#define SYSCTL_PCI2C_P2         0x00000004  // I2C Module 2 Power Control
#define SYSCTL_PCI2C_P1         0x00000002  // I2C Module 1 Power Control
#define SYSCTL_PCI2C_P0         0x00000001  // I2C Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCUSB register.
//
//*****************************************************************************
#define SYSCTL_PCUSB_P0         0x00000001  // USB Module Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCEPHY register.
//
//*****************************************************************************
#define SYSCTL_PCEPHY_P0        0x00000001  // Ethernet PHY Module Power
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCCAN register.
//
//*****************************************************************************
#define SYSCTL_PCCAN_P1         0x00000002  // CAN Module 1 Power Control
#define SYSCTL_PCCAN_P0         0x00000001  // CAN Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCADC register.
//
//*****************************************************************************
#define SYSCTL_PCADC_P1         0x00000002  // ADC Module 1 Power Control
#define SYSCTL_PCADC_P0         0x00000001  // ADC Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCACMP register.
//
//*****************************************************************************
#define SYSCTL_PCACMP_P0        0x00000001  // Analog Comparator Module 0 Power
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCPWM register.
//
//*****************************************************************************
#define SYSCTL_PCPWM_P0         0x00000001  // PWM Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCQEI register.
//
//*****************************************************************************
#define SYSCTL_PCQEI_P0         0x00000001  // QEI Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCEEPROM
// register.
//
//*****************************************************************************
#define SYSCTL_PCEEPROM_P0      0x00000001  // EEPROM Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCCCM register.
//
//*****************************************************************************
#define SYSCTL_PCCCM_P0         0x00000001  // CRC and Cryptographic Modules
// Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCLCD register.
//
//*****************************************************************************
#define SYSCTL_PCLCD_P0         0x00000001  // LCD Controller Module 0 Power
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCOWIRE register.
//
//*****************************************************************************
#define SYSCTL_PCOWIRE_P0       0x00000001  // 1-Wire Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCEMAC register.
//
//*****************************************************************************
#define SYSCTL_PCEMAC_P0        0x00000001  // Ethernet MAC Module 0 Power
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRWD register.
//
//*****************************************************************************
#define SYSCTL_PRWD_R1          0x00000002  // Watchdog Timer 1 Peripheral
// Ready
#define SYSCTL_PRWD_R0          0x00000001  // Watchdog Timer 0 Peripheral
// Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRTIMER register.
//
//*****************************************************************************
#define SYSCTL_PRTIMER_R7       0x00000080  // 16/32-Bit General-Purpose Timer
// 7 Peripheral Ready
#define SYSCTL_PRTIMER_R6       0x00000040  // 16/32-Bit General-Purpose Timer
// 6 Peripheral Ready
#define SYSCTL_PRTIMER_R5       0x00000020  // 16/32-Bit General-Purpose Timer
// 5 Peripheral Ready
#define SYSCTL_PRTIMER_R4       0x00000010  // 16/32-Bit General-Purpose Timer
// 4 Peripheral Ready
#define SYSCTL_PRTIMER_R3       0x00000008  // 16/32-Bit General-Purpose Timer
// 3 Peripheral Ready
#define SYSCTL_PRTIMER_R2       0x00000004  // 16/32-Bit General-Purpose Timer
// 2 Peripheral Ready
#define SYSCTL_PRTIMER_R1       0x00000002  // 16/32-Bit General-Purpose Timer
// 1 Peripheral Ready
#define SYSCTL_PRTIMER_R0       0x00000001  // 16/32-Bit General-Purpose Timer
// 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRGPIO register.
//
//*****************************************************************************
#define SYSCTL_PRGPIO_R17       0x00020000  // GPIO Port T Peripheral Ready
#define SYSCTL_PRGPIO_R16       0x00010000  // GPIO Port S Peripheral Ready
#define SYSCTL_PRGPIO_R15       0x00008000  // GPIO Port R Peripheral Ready
#define SYSCTL_PRGPIO_R14       0x00004000  // GPIO Port Q Peripheral Ready
#define SYSCTL_PRGPIO_R13       0x00002000  // GPIO Port P Peripheral Ready
#define SYSCTL_PRGPIO_R12       0x00001000  // GPIO Port N Peripheral Ready
#define SYSCTL_PRGPIO_R11       0x00000800  // GPIO Port M Peripheral Ready
#define SYSCTL_PRGPIO_R10       0x00000400  // GPIO Port L Peripheral Ready
#define SYSCTL_PRGPIO_R9        0x00000200  // GPIO Port K Peripheral Ready
#define SYSCTL_PRGPIO_R8        0x00000100  // GPIO Port J Peripheral Ready
#define SYSCTL_PRGPIO_R7        0x00000080  // GPIO Port H Peripheral Ready
#define SYSCTL_PRGPIO_R6        0x00000040  // GPIO Port G Peripheral Ready
#define SYSCTL_PRGPIO_R5        0x00000020  // GPIO Port F Peripheral Ready
#define SYSCTL_PRGPIO_R4        0x00000010  // GPIO Port E Peripheral Ready
#define SYSCTL_PRGPIO_R3        0x00000008  // GPIO Port D Peripheral Ready
#define SYSCTL_PRGPIO_R2        0x00000004  // GPIO Port C Peripheral Ready
#define SYSCTL_PRGPIO_R1        0x00000002  // GPIO Port B Peripheral Ready
#define SYSCTL_PRGPIO_R0        0x00000001  // GPIO Port A Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRDMA register.
//
//*****************************************************************************
#define SYSCTL_PRDMA_R0         0x00000001  // uDMA Module Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PREPI register.
//
//*****************************************************************************
#define SYSCTL_PREPI_R0         0x00000001  // EPI Module Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRHIB register.
//
//*****************************************************************************
#define SYSCTL_PRHIB_R0         0x00000001  // Hibernation Module Peripheral
// Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRUART register.
//
//*****************************************************************************
#define SYSCTL_PRUART_R7        0x00000080  // UART Module 7 Peripheral Ready
#define SYSCTL_PRUART_R6        0x00000040  // UART Module 6 Peripheral Ready
#define SYSCTL_PRUART_R5        0x00000020  // UART Module 5 Peripheral Ready
#define SYSCTL_PRUART_R4        0x00000010  // UART Module 4 Peripheral Ready
#define SYSCTL_PRUART_R3        0x00000008  // UART Module 3 Peripheral Ready
#define SYSCTL_PRUART_R2        0x00000004  // UART Module 2 Peripheral Ready
#define SYSCTL_PRUART_R1        0x00000002  // UART Module 1 Peripheral Ready
#define SYSCTL_PRUART_R0        0x00000001  // UART Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRSSI register.
//
//*****************************************************************************
#define SYSCTL_PRSSI_R3         0x00000008  // SSI Module 3 Peripheral Ready
#define SYSCTL_PRSSI_R2         0x00000004  // SSI Module 2 Peripheral Ready
#define SYSCTL_PRSSI_R1         0x00000002  // SSI Module 1 Peripheral Ready
#define SYSCTL_PRSSI_R0         0x00000001  // SSI Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRI2C register.
//
//*****************************************************************************
#define SYSCTL_PRI2C_R9         0x00000200  // I2C Module 9 Peripheral Ready
#define SYSCTL_PRI2C_R8         0x00000100  // I2C Module 8 Peripheral Ready
#define SYSCTL_PRI2C_R7         0x00000080  // I2C Module 7 Peripheral Ready
#define SYSCTL_PRI2C_R6         0x00000040  // I2C Module 6 Peripheral Ready
#define SYSCTL_PRI2C_R5         0x00000020  // I2C Module 5 Peripheral Ready
#define SYSCTL_PRI2C_R4         0x00000010  // I2C Module 4 Peripheral Ready
#define SYSCTL_PRI2C_R3         0x00000008  // I2C Module 3 Peripheral Ready
#define SYSCTL_PRI2C_R2         0x00000004  // I2C Module 2 Peripheral Ready
#define SYSCTL_PRI2C_R1         0x00000002  // I2C Module 1 Peripheral Ready
#define SYSCTL_PRI2C_R0         0x00000001  // I2C Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRUSB register.
//
//*****************************************************************************
#define SYSCTL_PRUSB_R0         0x00000001  // USB Module Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PREPHY register.
//
//*****************************************************************************
#define SYSCTL_PREPHY_R0        0x00000001  // Ethernet PHY Module Peripheral
// Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRCAN register.
//
//*****************************************************************************
#define SYSCTL_PRCAN_R1         0x00000002  // CAN Module 1 Peripheral Ready
#define SYSCTL_PRCAN_R0         0x00000001  // CAN Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRADC register.
//
//*****************************************************************************
#define SYSCTL_PRADC_R1         0x00000002  // ADC Module 1 Peripheral Ready
#define SYSCTL_PRADC_R0         0x00000001  // ADC Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRACMP register.
//
//*****************************************************************************
#define SYSCTL_PRACMP_R0        0x00000001  // Analog Comparator Module 0
// Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRPWM register.
//
//*****************************************************************************
#define SYSCTL_PRPWM_R1         0x00000002  // PWM Module 1 Peripheral Ready
#define SYSCTL_PRPWM_R0         0x00000001  // PWM Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRQEI register.
//
//*****************************************************************************
#define SYSCTL_PRQEI_R1         0x00000002  // QEI Module 1 Peripheral Ready
#define SYSCTL_PRQEI_R0         0x00000001  // QEI Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PREEPROM
// register.
//
//*****************************************************************************
#define SYSCTL_PREEPROM_R0      0x00000001  // EEPROM Module Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRCCM register.
//
//*****************************************************************************
#define SYSCTL_PRCCM_R0         0x00000001  // CRC and Cryptographic Modules
// Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRLCD register.
//
//*****************************************************************************
#define SYSCTL_PRLCD_R0         0x00000001  // LCD Controller Module 0
// Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PROWIRE register.
//
//*****************************************************************************
#define SYSCTL_PROWIRE_R0       0x00000001  // 1-Wire Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PREMAC register.
//
//*****************************************************************************
#define SYSCTL_PREMAC_R0        0x00000001  // Ethernet MAC Module 0 Peripheral
// Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_UNIQUEID0
// register.
//
//*****************************************************************************
#define SYSCTL_UNIQUEID0_ID_M   0xFFFFFFFF  // Unique ID
#define SYSCTL_UNIQUEID0_ID_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_UNIQUEID1
// register.
//
//*****************************************************************************
#define SYSCTL_UNIQUEID1_ID_M   0xFFFFFFFF  // Unique ID
#define SYSCTL_UNIQUEID1_ID_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_UNIQUEID2
// register.
//
//*****************************************************************************
#define SYSCTL_UNIQUEID2_ID_M   0xFFFFFFFF  // Unique ID
#define SYSCTL_UNIQUEID2_ID_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_UNIQUEID3
// register.
//
//*****************************************************************************
#define SYSCTL_UNIQUEID3_ID_M   0xFFFFFFFF  // Unique ID
#define SYSCTL_UNIQUEID3_ID_S   0

// //*****************************************************************************
// //
// // The following are defines for the bit fields in the SYSCTL_CCMCGREQ
// // register.
// //
// //*****************************************************************************
// #define SYSCTL_CCMCGREQ_DESCFG  0x00000004  // DES Clock Gating Request
// #define SYSCTL_CCMCGREQ_AESCFG  0x00000002  // AES Clock Gating Request
// #define SYSCTL_CCMCGREQ_SHACFG  0x00000001  // SHA/MD5 Clock Gating Request

#endif // __HW_SYSCTL_H__
