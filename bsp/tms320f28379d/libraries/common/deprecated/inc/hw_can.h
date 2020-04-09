//###########################################################################
//
// FILE:    hw_can.h
//
// TITLE:   Definitions for the C28x CAN registers.
//
//###########################################################################
// $TI Release: F2837xD Support Library v3.05.00.00 $
// $Release Date: Tue Jun 26 03:15:23 CDT 2018 $
// $Copyright:
// Copyright (C) 2013-2018 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
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
// $
//###########################################################################

#ifndef __HW_CAN_H__
#define __HW_CAN_H__

//*****************************************************************************
//
// The following are defines for the CAN register offsets
//
//*****************************************************************************
#define CAN_O_CTL                 0x0         // CAN Control Register
#define CAN_O_ES                  0x4         // Error and Status Register
#define CAN_O_ERRC                0x8         // Error Counter Register
#define CAN_O_BTR                 0xC         // Bit Timing Register
#define CAN_O_INT                 0x10        // Interrupt Register
#define CAN_O_TEST                0x14        // Test Register
#define CAN_O_PERR                0x1C        // CAN Parity Error Code Register
#define CAN_O_REL                 0x20        // CAN Core Release Register
#define CAN_O_RAM_INIT            0x40        // CAN RAM Initialization Register
#define CAN_O_GLB_INT_EN          0x50        // CAN Global Interrupt Enable
                                              // Register
#define CAN_O_GLB_INT_FLG         0x54        // CAN Global Interrupt Flag
                                              // Register
#define CAN_O_GLB_INT_CLR         0x58        // CAN Global Interrupt Clear
                                              // Register
#define CAN_O_ABOTR               0x80        // Auto-Bus-On Time Register
#define CAN_O_TXRQ_X              0x84        // CAN Transmission Request X
                                              // Register
#define CAN_O_TXRQ_21             0x88        // CAN Transmission Request 2_1
                                              // Register
#define CAN_O_NDAT_X              0x98        // CAN New Data X Register
#define CAN_O_NDAT_21             0x9C        // CAN New Data 2_1 Register
#define CAN_O_IPEN_X              0xAC        // CAN Interrupt Pending X
                                              // Register
#define CAN_O_IPEN_21             0xB0        // CAN Interrupt Pending 2_1
                                              // Register
#define CAN_O_MVAL_X              0xC0        // CAN Message Valid X Register
#define CAN_O_MVAL_21             0xC4        // CAN Message Valid 2_1 Register
#define CAN_O_IP_MUX21            0xD8        // CAN Interrupt Multiplexer 2_1
                                              // Register
#define CAN_O_IF1CMD              0x100       // IF1 Command Register
#define CAN_O_IF1MSK              0x104       // IF1 Mask Register
#define CAN_O_IF1ARB              0x108       // IF1 Arbitration Register
#define CAN_O_IF1MCTL             0x10C       // IF1 Message Control Register
#define CAN_O_IF1DATA             0x110       // IF1 Data A Register
#define CAN_O_IF1DATB             0x114       // IF1 Data B Register
#define CAN_O_IF2CMD              0x120       // IF2 Command Register
#define CAN_O_IF2MSK              0x124       // IF2 Mask Register
#define CAN_O_IF2ARB              0x128       // IF2 Arbitration Register
#define CAN_O_IF2MCTL             0x12C       // IF2 Message Control Register
#define CAN_O_IF2DATA             0x130       // IF2 Data A Register
#define CAN_O_IF2DATB             0x134       // IF2 Data B Register
#define CAN_O_IF3OBS              0x140       // IF3 Observation Register
#define CAN_O_IF3MSK              0x144       // IF3 Mask Register
#define CAN_O_IF3ARB              0x148       // IF3 Arbitration Register
#define CAN_O_IF3MCTL             0x14C       // IF3 Message Control Register
#define CAN_O_IF3DATA             0x150       // IF3 Data A Register
#define CAN_O_IF3DATB             0x154       // IF3 Data B Register
#define CAN_O_IF3UPD              0x160       // IF3 Update Enable Register

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_CTL register
//
//*****************************************************************************
#define CAN_CTL_INIT              0x1         // Initialization
#define CAN_CTL_IE0               0x2         // Interrupt line 0 Enable
                                              // Disabled
#define CAN_CTL_SIE               0x4         // Status Change Interrupt Enable
                                              // Disabled
#define CAN_CTL_EIE               0x8         // Error Interrupt Enable Disabled
#define CAN_CTL_DAR               0x20        // Disable Automatic
                                              // Retransmission
#define CAN_CTL_CCE               0x40        // Configuration Change Enable
#define CAN_CTL_TEST              0x80        // Test Mode Enable
#define CAN_CTL_IDS               0x100       // Interruption Debug Support
                                              // Enable
#define CAN_CTL_ABO               0x200       // Auto-Bus-On Enable
#define CAN_CTL_PMD_S             10
#define CAN_CTL_PMD_M             0x3C00      // Parity on/off
#define CAN_CTL_SWR               0x8000      // SW Reset Enable
#define CAN_CTL_INITDBG           0x10000     // Debug Mode Status
#define CAN_CTL_IE1               0x20000     // Interrupt line 1 Enable
                                              // Disabled
#define CAN_CTL_PDR               0x1000000   // Power Down Request Mode
#define CAN_CTL_WUBA              0x2000000   // Wake Up on Bus Activity

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_ES register
//
//*****************************************************************************
#define CAN_ES_LEC_S              0
#define CAN_ES_LEC_M              0x7         // Last Error Code
#define CAN_ES_TXOK               0x8         // Transmission status
#define CAN_ES_RXOK               0x10        // Reception status
#define CAN_ES_EPASS              0x20        // Error Passive State
#define CAN_ES_EWARN              0x40        // Warning State
#define CAN_ES_BOFF               0x80        // Bus-Off State
#define CAN_ES_PER                0x100       // Parity Error Detected
#define CAN_ES_WAKEUPPND          0x200       // Wake Up Pending
#define CAN_ES_PDA                0x400       // Power down mode acknowledge

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_ERRC register
//
//*****************************************************************************
#define CAN_ERRC_TEC_S            0
#define CAN_ERRC_TEC_M            0xFF        // Transmit Error Counter
#define CAN_ERRC_REC_S            8
#define CAN_ERRC_REC_M            0x7F00      // Receive Error Counter
#define CAN_ERRC_RP               0x8000      // Receive Error Passive

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_BTR register
//
//*****************************************************************************
#define CAN_BTR_BRP_S             0
#define CAN_BTR_BRP_M             0x3F       // Baud Rate Prescaler
#define CAN_BTR_SJW_S             6
#define CAN_BTR_SJW_M             0xC0        // Synchronization Jump Width
#define CAN_BTR_TSEG1_S           8
#define CAN_BTR_TSEG1_M           0xF00       // Time segment
#define CAN_BTR_TSEG2_S           12
#define CAN_BTR_TSEG2_M           0x7000      // Time segment
#define CAN_BTR_BRPE_S            16
#define CAN_BTR_BRPE_M            0xF0000     // Baud Rate Prescaler Extension

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_INT register
//
//*****************************************************************************
#define CAN_INT_INT0ID_S          0
#define CAN_INT_INT0ID_M          0xFFFF      // Interrupt Identifier
#define CAN_INT_INT1ID_S          16
#define CAN_INT_INT1ID_M          0xFF0000    // Interrupt 1 Identifier

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_TEST register
//
//*****************************************************************************
#define CAN_TEST_SILENT           0x8         // Silent Mode
#define CAN_TEST_LBACK            0x10        // Loopback Mode
#define CAN_TEST_TX_S             5
#define CAN_TEST_TX_M             0x60        // CANTX Pin Control
#define CAN_TEST_RX               0x80        // CANRX Pin Status
#define CAN_TEST_EXL              0x100       // External Loopback Mode
#define CAN_TEST_RDA              0x200       // RAM Direct Access Enable:

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_PERR register
//
//*****************************************************************************
#define CAN_PERR_MSG_NUM_S        0
#define CAN_PERR_MSG_NUM_M        0xFF        // Message Number
#define CAN_PERR_WORD_NUM_S       8
#define CAN_PERR_WORD_NUM_M       0x700       // Word Number

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_REL register
//
//*****************************************************************************
#define CAN_REL_DAY_S             0
#define CAN_REL_DAY_M             0xFF        // Day
#define CAN_REL_MON_S             8
#define CAN_REL_MON_M             0xFF00      // Month
#define CAN_REL_YEAR_S            16
#define CAN_REL_YEAR_M            0xF0000     // Year
#define CAN_REL_SUBSTEP_S         20
#define CAN_REL_SUBSTEP_M         0xF00000    // Substep
#define CAN_REL_STEP_S            24
#define CAN_REL_STEP_M            0xF000000   // Step
#define CAN_REL_REL_S             28
#define CAN_REL_REL_M             0xF0000000  // Release

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_RAM_INIT register
//
//*****************************************************************************
#define CAN_RAM_INIT_KEY0         0x1         // KEY0
#define CAN_RAM_INIT_KEY1         0x2         // KEY1
#define CAN_RAM_INIT_KEY2         0x4         // KEY2
#define CAN_RAM_INIT_KEY3         0x8         // KEY3
#define CAN_RAM_INIT_CAN_RAM_INIT  0x10        // Initialize CAN Mailbox RAM
#define CAN_RAM_INIT_RAM_INIT_DONE  0x20        // CAN RAM initialization complete

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_GLB_INT_EN register
//
//*****************************************************************************
#define CAN_GLB_INT_CANINT0  0x1         // Global Interrupt Enable for CAN INT0
#define CAN_GLB_INT_CANINT1  0x2         // Global Interrupt Enable for CAN INT1

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_GLB_INT_FLG register
//
//*****************************************************************************
#define CAN_GLB_INT_FLG_NAME      0x1         // Global Interrupt Flag for CAN
                                              // INT0
#define CAN_GLB_INT_FLG_INT1_FLG  0x2         // Global Interrupt Flag for CAN
                                              // INT1

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_GLB_INT_CLR register
//
//*****************************************************************************
#define CAN_GLB_INT_CLR_INT0_FLG_CLR  0x1         // Global Interrupt flag clear for
                                              // CAN INT0
#define CAN_GLB_INT_CLR_INT1_FLG_CLR  0x2         // Global Interrupt flag  clear
                                              // for CAN INT1

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_ABOTR register
//
//*****************************************************************************
#define CAN_ABOTR_ABO_TIME_S      0
#define CAN_ABOTR_ABO_TIME_M      0xFFFFFFFF  // Auto-Bus-On Timer

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_TXRQ_X register
//
//*****************************************************************************
#define CAN_TXRQ_X_TXRQSTREG1_S   0
#define CAN_TXRQ_X_TXRQSTREG1_M   0x3         // Transmit Request Register 1
#define CAN_TXRQ_X_TXRQSTREG2_S   2
#define CAN_TXRQ_X_TXRQSTREG2_M   0xC         // Transmit Request Register 2

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_TXRQ_21 register
//
//*****************************************************************************
#define CAN_TXRQ_21_TXRQST_S      0
#define CAN_TXRQ_21_TXRQST_M      0xFFFFFFFF  // Transmission Request Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_NDAT_X register
//
//*****************************************************************************
#define CAN_NDAT_X_NEWDATREG1_S   0
#define CAN_NDAT_X_NEWDATREG1_M   0x3         // New Data Register 1
#define CAN_NDAT_X_NEWDATREG2_S   2
#define CAN_NDAT_X_NEWDATREG2_M   0xC         // New Data Register 2

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_NDAT_21 register
//
//*****************************************************************************
#define CAN_NDAT_21_NEWDAT_S      0
#define CAN_NDAT_21_NEWDAT_M      0xFFFFFFFF  // New Data Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IPEN_X register
//
//*****************************************************************************
#define CAN_IPEN_X_INTPNDREG1_S   0
#define CAN_IPEN_X_INTPNDREG1_M   0x3         // Interrupt Pending Register 1
#define CAN_IPEN_X_INTPNDREG2_S   2
#define CAN_IPEN_X_INTPNDREG2_M   0xC         // Interrupt Pending Register 2

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IPEN_21 register
//
//*****************************************************************************
#define CAN_IPEN_21_INTPND_S      0
#define CAN_IPEN_21_INTPND_M      0xFFFFFFFF  // Interrupt Pending

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_MVAL_X register
//
//*****************************************************************************
#define CAN_MVAL_X_MSGVALREG1_S   0
#define CAN_MVAL_X_MSGVALREG1_M   0x3         // Message Valid Register 1
#define CAN_MVAL_X_MSGVALREG2_S   2
#define CAN_MVAL_X_MSGVALREG2_M   0xC         // Message Valid Register 2

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_MVAL_21 register
//
//*****************************************************************************
#define CAN_MVAL_21_MSGVALREG_S   0
#define CAN_MVAL_21_MSGVALREG_M   0xFFFFFFFF  // Message Valid Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IP_MUX21 register
//
//*****************************************************************************
#define CAN_IP_MUX21_INTMUX_S     0
#define CAN_IP_MUX21_INTMUX_M     0xFFFFFFFF  // Interrupt Mux

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF1CMD register
//
//*****************************************************************************
#define CAN_IF1CMD_MSG_NUM_S      0
#define CAN_IF1CMD_MSG_NUM_M      0xFF        // Message Number
#define CAN_IF1CMD_BUSY           0x8000      // Busy Flag
#define CAN_IF1CMD_DATA_B         0x10000     // Access Data Bytes 4-7
#define CAN_IF1CMD_DATA_A         0x20000     // Access Data Bytes 0-3
#define CAN_IF1CMD_TXRQST         0x40000     // Access Transmission Request Bit
#define CAN_IF1CMD_CLRINTPND      0x80000     // Clear Interrupt Pending Bit
#define CAN_IF1CMD_CONTROL        0x100000    // Access Control Bits
#define CAN_IF1CMD_ARB            0x200000    // Access Arbitration Bits
#define CAN_IF1CMD_MASK           0x400000    // Access Mask Bits
#define CAN_IF1CMD_DIR            0x800000    // Write/Read Direction

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF1MSK register
//
//*****************************************************************************
#define CAN_IF1MSK_MSK_S          0
#define CAN_IF1MSK_MSK_M          0x1FFFFFFF  // Identifier Mask
#define CAN_IF1MSK_MDIR           0x40000000  // Mask Message Direction
#define CAN_IF1MSK_MXTD           0x80000000  // Mask Extended Identifier

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF1ARB register
//
//*****************************************************************************
#define CAN_IF1ARB_ID_S           0
#define CAN_IF1ARB_ID_M           0x1FFFFFFF  // `
#define CAN_IF1ARB_DIR            0x20000000  // Message Direction
#define CAN_IF1ARB_XTD            0x40000000  // Extended Identifier
#define CAN_IF1ARB_MSGVAL         0x80000000  // Message Valid

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF1MCTL register
//
//*****************************************************************************
#define CAN_IF1MCTL_DLC_S         0
#define CAN_IF1MCTL_DLC_M         0xF         // Data length code
#define CAN_IF1MCTL_EOB           0x80        // End of Block
#define CAN_IF1MCTL_TXRQST        0x100       // Transmit Request
#define CAN_IF1MCTL_RMTEN         0x200       // Remote Enable
#define CAN_IF1MCTL_RXIE          0x400       // Receive Interrupt Enable
#define CAN_IF1MCTL_TXIE          0x800       // Transmit Interrupt Enable
#define CAN_IF1MCTL_UMASK         0x1000      // Use Acceptance Mask
#define CAN_IF1MCTL_INTPND        0x2000      // Interrupt Pending
#define CAN_IF1MCTL_MSGLST        0x4000      // Message Lost
#define CAN_IF1MCTL_NEWDAT        0x8000      // New Data

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF1DATA register
//
//*****************************************************************************
#define CAN_IF1DATA_DATA_0_S      0
#define CAN_IF1DATA_DATA_0_M      0xFF        // Data Byte 0
#define CAN_IF1DATA_DATA_1_S      8
#define CAN_IF1DATA_DATA_1_M      0xFF00      // Data Byte 1
#define CAN_IF1DATA_DATA_2_S      16
#define CAN_IF1DATA_DATA_2_M      0xFF0000    // Data Byte 2
#define CAN_IF1DATA_DATA_3_S      24
#define CAN_IF1DATA_DATA_3_M      0xFF000000  // Data Byte 3

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF1DATB register
//
//*****************************************************************************
#define CAN_IF1DATB_DATA_4_S      0
#define CAN_IF1DATB_DATA_4_M      0xFF        // Data Byte 4
#define CAN_IF1DATB_DATA_5_S      8
#define CAN_IF1DATB_DATA_5_M      0xFF00      // Data Byte 5
#define CAN_IF1DATB_DATA_6_S      16
#define CAN_IF1DATB_DATA_6_M      0xFF0000    // Data Byte 6
#define CAN_IF1DATB_DATA_7_S      24
#define CAN_IF1DATB_DATA_7_M      0xFF000000  // Data Byte 7

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF2CMD register
//
//*****************************************************************************
#define CAN_IF2CMD_MSG_NUM_S      0
#define CAN_IF2CMD_MSG_NUM_M      0xFF        // Message Number
#define CAN_IF2CMD_BUSY           0x8000      // Busy Flag
#define CAN_IF2CMD_DATA_B         0x10000     // Access Data Bytes 4-7
#define CAN_IF2CMD_DATA_A         0x20000     // Access Data Bytes 0-3
#define CAN_IF2CMD_TXRQST         0x40000     // Access Transmission Request Bit
#define CAN_IF2CMD_CLRINTPND      0x80000     // Clear Interrupt Pending Bit
#define CAN_IF2CMD_CONTROL        0x100000    // Access Control Bits
#define CAN_IF2CMD_ARB            0x200000    // Access Arbitration Bits
#define CAN_IF2CMD_MASK           0x400000    // Access Mask Bits
#define CAN_IF2CMD_DIR            0x800000    // Write/Read Direction

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF2MSK register
//
//*****************************************************************************
#define CAN_IF2MSK_MSK_S          0
#define CAN_IF2MSK_MSK_M          0x1FFFFFFF  // Identifier Mask
#define CAN_IF2MSK_MDIR           0x40000000  // Mask Message Direction
#define CAN_IF2MSK_MXTD           0x80000000  // Mask Extended Identifier

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF2ARB register
//
//*****************************************************************************
#define CAN_IF2ARB_ID_S           0
#define CAN_IF2ARB_ID_M           0x1FFFFFFF  // Message  Identifier
#define CAN_IF2ARB_DIR            0x20000000  // Message Direction
#define CAN_IF2ARB_XTD            0x40000000  // Extended Identifier
#define CAN_IF2ARB_MSGVAL         0x80000000  // Message Valid

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF2MCTL register
//
//*****************************************************************************
#define CAN_IF2MCTL_DLC_S         0
#define CAN_IF2MCTL_DLC_M         0xF         // Data length code
#define CAN_IF2MCTL_EOB           0x80        // End of Block
#define CAN_IF2MCTL_TXRQST        0x100       // Transmit Request
#define CAN_IF2MCTL_RMTEN         0x200       // Remote Enable
#define CAN_IF2MCTL_RXIE          0x400       // Receive Interrupt Enable
#define CAN_IF2MCTL_TXIE          0x800       // Transmit Interrupt Enable
#define CAN_IF2MCTL_UMASK         0x1000      // Use Acceptance Mask
#define CAN_IF2MCTL_INTPND        0x2000      // Interrupt Pending
#define CAN_IF2MCTL_MSGLST        0x4000      // Message Lost
#define CAN_IF2MCTL_NEWDAT        0x8000      // New Data

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF2DATA register
//
//*****************************************************************************
#define CAN_IF2DATA_DATA_0_S      0
#define CAN_IF2DATA_DATA_0_M      0xFF        // Data Byte 0
#define CAN_IF2DATA_DATA_1_S      8
#define CAN_IF2DATA_DATA_1_M      0xFF00      // Data Byte 1
#define CAN_IF2DATA_DATA_2_S      16
#define CAN_IF2DATA_DATA_2_M      0xFF0000    // Data Byte 2
#define CAN_IF2DATA_DATA_3_S      24
#define CAN_IF2DATA_DATA_3_M      0xFF000000  // Data Byte 3

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF2DATB register
//
//*****************************************************************************
#define CAN_IF2DATB_DATA_4_S      0
#define CAN_IF2DATB_DATA_4_M      0xFF        // Data Byte 4
#define CAN_IF2DATB_DATA_5_S      8
#define CAN_IF2DATB_DATA_5_M      0xFF00      // Data Byte 5
#define CAN_IF2DATB_DATA_6_S      16
#define CAN_IF2DATB_DATA_6_M      0xFF0000    // Data Byte 6
#define CAN_IF2DATB_DATA_7_S      24
#define CAN_IF2DATB_DATA_7_M      0xFF000000  // Data Byte 7

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF3OBS register
//
//*****************************************************************************
#define CAN_IF3OBS_MASK           0x1         // Mask data read observation
#define CAN_IF3OBS_ARB            0x2         // Arbitration data read
                                              // observation
#define CAN_IF3OBS_CTRL           0x4         // Ctrl read observation
#define CAN_IF3OBS_DATA_A         0x8         // Data A read observation
#define CAN_IF3OBS_DATA_B         0x10        // Data B read observation
#define CAN_IF3OBS_IF3SM          0x100       // IF3 Status of Mask data read
                                              // access
#define CAN_IF3OBS_IF3SA          0x200       // IF3 Status of Arbitration data
                                              // read access
#define CAN_IF3OBS_IF3SC          0x400       // IF3 Status of Control bits read
                                              // access
#define CAN_IF3OBS_IF3SDA         0x800       // IF3 Status of Data A read
                                              // access
#define CAN_IF3OBS_IF3SDB         0x1000      // IF3 Status of Data B read
                                              // access
#define CAN_IF3OBS_IF3UPD         0x8000      // IF3 Update Data

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF3MSK register
//
//*****************************************************************************
#define CAN_IF3MSK_MSK_S          0
#define CAN_IF3MSK_MSK_M          0x1FFFFFFF  // Mask
#define CAN_IF3MSK_MDIR           0x40000000  // Mask Message Direction
#define CAN_IF3MSK_MXTD           0x80000000  // Mask Extended Identifier

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF3ARB register
//
//*****************************************************************************
#define CAN_IF3ARB_ID_S           0
#define CAN_IF3ARB_ID_M           0x1FFFFFFF  // Message  Identifier
#define CAN_IF3ARB_DIR            0x20000000  // Message Direction
#define CAN_IF3ARB_XTD            0x40000000  // Extended Identifier
#define CAN_IF3ARB_MSGVAL         0x80000000  // Message Valid

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF3MCTL register
//
//*****************************************************************************
#define CAN_IF3MCTL_DLC_S         0
#define CAN_IF3MCTL_DLC_M         0xF         // Data length code
#define CAN_IF3MCTL_EOB           0x80        // End of Block
#define CAN_IF3MCTL_TXRQST        0x100       // Transmit Request
#define CAN_IF3MCTL_RMTEN         0x200       // Remote Enable
#define CAN_IF3MCTL_RXIE          0x400       // Receive Interrupt Enable
#define CAN_IF3MCTL_TXIE          0x800       // Transmit Interrupt Enable
#define CAN_IF3MCTL_UMASK         0x1000      // Use Acceptance Mask
#define CAN_IF3MCTL_INTPND        0x2000      // Interrupt Pending
#define CAN_IF3MCTL_MSGLST        0x4000      // Message Lost
#define CAN_IF3MCTL_NEWDAT        0x8000      // New Data

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF3DATA register
//
//*****************************************************************************
#define CAN_IF3DATA_DATA_0_S      0
#define CAN_IF3DATA_DATA_0_M      0xFF        // Data Byte 0
#define CAN_IF3DATA_DATA_1_S      8
#define CAN_IF3DATA_DATA_1_M      0xFF00      // Data Byte 1
#define CAN_IF3DATA_DATA_2_S      16
#define CAN_IF3DATA_DATA_2_M      0xFF0000    // Data Byte 2
#define CAN_IF3DATA_DATA_3_S      24
#define CAN_IF3DATA_DATA_3_M      0xFF000000  // Data Byte 3

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF3DATB register
//
//*****************************************************************************
#define CAN_IF3DATB_DATA_4_S      0
#define CAN_IF3DATB_DATA_4_M      0xFF        // Data Byte 4
#define CAN_IF3DATB_DATA_5_S      8
#define CAN_IF3DATB_DATA_5_M      0xFF00      // Data Byte 5
#define CAN_IF3DATB_DATA_6_S      16
#define CAN_IF3DATB_DATA_6_M      0xFF0000    // Data Byte 6
#define CAN_IF3DATB_DATA_7_S      24
#define CAN_IF3DATB_DATA_7_M      0xFF000000  // Data Byte 7

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IF3UPD register
//
//*****************************************************************************
#define CAN_IF3UPD_IF3UPDEN_S     0
#define CAN_IF3UPD_IF3UPDEN_M     0xFFFFFFFF  // IF3 Update Enabled
#endif
