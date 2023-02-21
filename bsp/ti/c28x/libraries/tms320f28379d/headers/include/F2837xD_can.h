//###########################################################################
//
// FILE:    F2837xD_can.h
//
// TITLE:   CAN Register Definitions.
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

#ifndef __F2837xD_CAN_H__
#define __F2837xD_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// CAN Individual Register Bit Definitions:

struct CAN_CTL_BITS {                  // bits description
    bp_16 Init:1;                      // 0 Initialization
    bp_16 IE0:1;                       // 1 Interrupt line 0 Enable
    bp_16 SIE:1;                       // 2 Status Change Interrupt Enable
    bp_16 EIE:1;                       // 3 Error Interrupt Enable
    bp_16 rsvd1:1;                     // 4 Reserved
    bp_16 DAR:1;                       // 5 Disable Automatic Retransmission
    bp_16 CCE:1;                       // 6 Configuration Change Enable
    bp_16 Test:1;                      // 7 Test Mode Enable
    bp_16 IDS:1;                       // 8 Interruption Debug Support Enable
    bp_16 ABO:1;                       // 9 Auto-Bus-On Enable
    bp_16 PMD:4;                       // 13:10 Parity on/off
    bp_16 rsvd2:1;                     // 14 Reserved
    bp_16 SWR:1;                       // 15 SW Reset Enable
    bp_32 INITDBG:1;                   // 16 Debug Mode Status
    bp_32 IE1:1;                       // 17 Interrupt line 1 Enable Disabled
    bp_32 rsvd3:1;                     // 18 Reserved
    bp_32 rsvd4:1;                     // 19 Reserved
    bp_32 rsvd5:1;                     // 20 Reserved
    bp_32 rsvd6:3;                     // 23:21 Reserved
    bp_32 rsvd7:1;                     // 24 Reserved
    bp_32 rsvd8:1;                     // 25 Reserved
    bp_32 rsvd9:6;                     // 31:26 Reserved
};

union CAN_CTL_REG {
    bp_32  all;
    struct  CAN_CTL_BITS  bit;
};

struct CAN_ES_BITS {                   // bits description
    bp_16 LEC:3;                       // 2:0 Last Error Code
    bp_16 TxOk:1;                      // 3 Transmission status
    bp_16 RxOk:1;                      // 4 Reception status
    bp_16 EPass:1;                     // 5 Error Passive State
    bp_16 EWarn:1;                     // 6 Warning State
    bp_16 BOff:1;                      // 7 Bus-Off State
    bp_16 PER:1;                       // 8 Parity Error Detected
    bp_16 rsvd1:1;                     // 9 Reserved
    bp_16 rsvd2:1;                     // 10 Reserved
    bp_16 rsvd3:5;                     // 15:11 Reserved
    bp_32 rsvd4:16;                    // 31:16 Reserved
};

union CAN_ES_REG {
    bp_32  all;
    struct  CAN_ES_BITS  bit;
};

struct CAN_ERRC_BITS {                 // bits description
    bp_16 TEC:8;                       // 7:0 Transmit Error Counter
    bp_16 REC:7;                       // 14:8 Receive Error Counter
    bp_16 RP:1;                        // 15 Receive Error Passive
    bp_32 rsvd1:16;                    // 31:16 Reserved
};

union CAN_ERRC_REG {
    bp_32  all;
    struct  CAN_ERRC_BITS  bit;
};

struct CAN_BTR_BITS {                  // bits description
    bp_16 BRP:6;                       // 5:0 Baud Rate Prescaler
    bp_16 SJW:2;                       // 7:6 Synchronization Jump Width
    bp_16 TSEG1:4;                     // 11:8 Time segment
    bp_16 TSEG2:3;                     // 14:12 Time segment
    bp_16 rsvd1:1;                     // 15 Reserved
    bp_32 BRPE:4;                      // 19:16 Baud Rate Prescaler Extension
    bp_32 rsvd2:12;                    // 31:20 Reserved
};

union CAN_BTR_REG {
    bp_32  all;
    struct  CAN_BTR_BITS  bit;
};

struct CAN_INT_BITS {                  // bits description
    bp_16 INT0ID:16;                   // 15:0 Interrupt Identifier
    bp_32 INT1ID:8;                    // 23:16 Interrupt 1 Identifier
    bp_32 rsvd1:8;                     // 31:24 Reserved
};

union CAN_INT_REG {
    bp_32  all;
    struct  CAN_INT_BITS  bit;
};

struct CAN_TEST_BITS {                 // bits description
    bp_16 rsvd1:3;                     // 2:0 Reserved
    bp_16 SILENT:1;                    // 3 Silent Mode
    bp_16 LBACK:1;                     // 4 Loopback Mode
    bp_16 TX:2;                        // 6:5 CANTX Pin Control
    bp_16 RX:1;                        // 7 CANRX Pin Status
    bp_16 EXL:1;                       // 8 External Loopback Mode
    bp_16 RDA:1;                       // 9 RAM Direct Access Enable:
    bp_16 rsvd2:6;                     // 15:10 Reserved
    bp_32 rsvd3:16;                    // 31:16 Reserved
};

union CAN_TEST_REG {
    bp_32  all;
    struct  CAN_TEST_BITS  bit;
};

struct CAN_PERR_BITS {                 // bits description
    bp_16 MSG_NUM:8;                   // 7:0 Message Number
    bp_16 WORD_NUM:3;                  // 10:8 Word Number
    bp_16 rsvd1:5;                     // 15:11 Reserved
    bp_32 rsvd2:16;                    // 31:16 Reserved
};

union CAN_PERR_REG {
    bp_32  all;
    struct  CAN_PERR_BITS  bit;
};

struct CAN_RAM_INIT_BITS {             // bits description
    bp_16 KEY0:1;                      // 0 KEY0
    bp_16 KEY1:1;                      // 1 KEY1
    bp_16 KEY2:1;                      // 2 KEY2
    bp_16 KEY3:1;                      // 3 KEY3
    bp_16 CAN_RAM_INIT:1;              // 4 Initialize CAN Mailbox RAM
    bp_16 RAM_INIT_DONE:1;             // 5 CAN RAM initialization complete
    bp_16 rsvd1:10;                    // 15:6 Reserved
    bp_32 rsvd2:16;                    // 31:16 Reserved
};

union CAN_RAM_INIT_REG {
    bp_32  all;
    struct  CAN_RAM_INIT_BITS  bit;
};

struct CAN_GLB_INT_EN_BITS {           // bits description
    bp_16 GLBINT0_EN:1;                // 0 Global Interrupt Enable for  CAN INT0
    bp_16 GLBINT1_EN:1;                // 1 Global Interrupt Enable for  CAN INT1
    bp_16 rsvd1:14;                    // 15:2 Reserved
    bp_32 rsvd2:16;                    // 31:16 Reserved
};

union CAN_GLB_INT_EN_REG {
    bp_32  all;
    struct  CAN_GLB_INT_EN_BITS  bit;
};

struct CAN_GLB_INT_FLG_BITS {          // bits description
    bp_16 INT0_FLG:1;                  // 0 Global Interrupt Flag for CAN INT0
    bp_16 INT1_FLG:1;                  // 1 Global Interrupt Flag for CAN INT1
    bp_16 rsvd1:14;                    // 15:2 Reserved
    bp_32 rsvd2:16;                    // 31:16 Reserved
};

union CAN_GLB_INT_FLG_REG {
    bp_32  all;
    struct  CAN_GLB_INT_FLG_BITS  bit;
};

struct CAN_GLB_INT_CLR_BITS {          // bits description
    bp_16 INT0_FLG_CLR:1;              // 0 Global Interrupt flag clear for CAN INT0
    bp_16 INT1_FLG_CLR:1;              // 1 Global Interrupt flag  clear for CAN INT1
    bp_16 rsvd1:14;                    // 15:2 Reserved
    bp_32 rsvd2:16;                    // 31:16 Reserved
};

union CAN_GLB_INT_CLR_REG {
    bp_32  all;
    struct  CAN_GLB_INT_CLR_BITS  bit;
};

struct CAN_TXRQ_X_BITS {               // bits description
    bp_16 TxRqstReg1:2;                // 1:0 Transmit Request Register 1
    bp_16 TxRqstReg2:2;                // 3:2 Transmit Request Register 2
    bp_16 rsvd1:12;                    // 15:4 Reserved
    bp_32 rsvd2:16;                    // 31:16 Reserved
};

union CAN_TXRQ_X_REG {
    bp_32  all;
    struct  CAN_TXRQ_X_BITS  bit;
};

struct CAN_NDAT_X_BITS {               // bits description
    bp_16 NewDatReg1:2;                // 1:0 New Data Register 1
    bp_16 NewDatReg2:2;                // 3:2 New Data Register 2
    bp_16 rsvd1:12;                    // 15:4 Reserved
    bp_32 rsvd2:16;                    // 31:16 Reserved
};

union CAN_NDAT_X_REG {
    bp_32  all;
    struct  CAN_NDAT_X_BITS  bit;
};

struct CAN_IPEN_X_BITS {               // bits description
    bp_16 IntPndReg1:2;                // 1:0 Interrupt Pending Register 1
    bp_16 IntPndReg2:2;                // 3:2 Interrupt Pending Register 2
    bp_16 rsvd1:12;                    // 15:4 Reserved
    bp_32 rsvd2:16;                    // 31:16 Reserved
};

union CAN_IPEN_X_REG {
    bp_32  all;
    struct  CAN_IPEN_X_BITS  bit;
};

struct CAN_MVAL_X_BITS {               // bits description
    bp_16 MsgValReg1:2;                // 1:0 Message Valid Register 1
    bp_16 MsgValReg2:2;                // 3:2 Message Valid Register 2
    bp_16 rsvd1:12;                    // 15:4 Reserved
    bp_32 rsvd2:16;                    // 31:16 Reserved
};

union CAN_MVAL_X_REG {
    bp_32  all;
    struct  CAN_MVAL_X_BITS  bit;
};

struct CAN_IF1CMD_BITS {               // bits description
    bp_16 MSG_NUM:8;                   // 7:0 Message Number
    bp_16 rsvd1:6;                     // 13:8 Reserved
    bp_16 rsvd2:1;                     // 14 Reserved
    bp_16 Busy:1;                      // 15 Busy Flag
    bp_32 DATA_B:1;                    // 16 Access Data Bytes 4-7
    bp_32 DATA_A:1;                    // 17 Access Data Bytes 0-3
    bp_32 TXRQST:1;                    // 18 Access Transmission Request Bit
    bp_32 ClrIntPnd:1;                 // 19 Clear Interrupt Pending Bit
    bp_32 Control:1;                   // 20 Access Control Bits
    bp_32 Arb:1;                       // 21 Access Arbitration Bits
    bp_32 Mask:1;                      // 22 Access Mask Bits
    bp_32 DIR:1;                       // 23 Write/Read Direction
    bp_32 rsvd3:8;                     // 31:24 Reserved
};

union CAN_IF1CMD_REG {
    bp_32  all;
    struct  CAN_IF1CMD_BITS  bit;
};

struct CAN_IF1MSK_BITS {               // bits description
    bp_32 Msk:29;                      // 28:0 Identifier Mask
    bp_32 rsvd1:1;                     // 29 Reserved
    bp_32 MDir:1;                      // 30 Mask Message Direction
    bp_32 MXtd:1;                      // 31 Mask Extended Identifier
};

union CAN_IF1MSK_REG {
    bp_32  all;
    struct  CAN_IF1MSK_BITS  bit;
};

struct CAN_IF1ARB_BITS {               // bits description
    bp_32 ID:29;                       // 28:0 `
    bp_32 Dir:1;                       // 29 Message Direction
    bp_32 Xtd:1;                       // 30 Extended Identifier
    bp_32 MsgVal:1;                    // 31 Message Valid
};

union CAN_IF1ARB_REG {
    bp_32  all;
    struct  CAN_IF1ARB_BITS  bit;
};

struct CAN_IF1MCTL_BITS {              // bits description
    bp_16 DLC:4;                       // 3:0 Data length code
    bp_16 rsvd1:3;                     // 6:4 Reserved
    bp_16 EoB:1;                       // 7 End of Block
    bp_16 TxRqst:1;                    // 8 Transmit Request
    bp_16 RmtEn:1;                     // 9 Remote Enable
    bp_16 RxIE:1;                      // 10 Receive Interrupt Enable
    bp_16 TxIE:1;                      // 11 Transmit Interrupt Enable
    bp_16 UMask:1;                     // 12 Use Acceptance Mask
    bp_16 IntPnd:1;                    // 13 Interrupt Pending
    bp_16 MsgLst:1;                    // 14 Message Lost
    bp_16 NewDat:1;                    // 15 New Data
    bp_32 rsvd2:16;                    // 31:16 Reserved
};

union CAN_IF1MCTL_REG {
    bp_32  all;
    struct  CAN_IF1MCTL_BITS  bit;
};

struct CAN_IF1DATA_BITS {              // bits description
    bp_16 Data_0:8;                    // 7:0 Data Byte 0
    bp_16 Data_1:8;                    // 15:8 Data Byte 1
    bp_32 Data_2:8;                    // 23:16 Data Byte 2
    bp_32 Data_3:8;                    // 31:24 Data Byte 3
};

union CAN_IF1DATA_REG {
    bp_32  all;
    struct  CAN_IF1DATA_BITS  bit;
};

struct CAN_IF1DATB_BITS {              // bits description
    bp_16 Data_4:8;                    // 7:0 Data Byte 4
    bp_16 Data_5:8;                    // 15:8 Data Byte 5
    bp_32 Data_6:8;                    // 23:16 Data Byte 6
    bp_32 Data_7:8;                    // 31:24 Data Byte 7
};

union CAN_IF1DATB_REG {
    bp_32  all;
    struct  CAN_IF1DATB_BITS  bit;
};

struct CAN_IF2CMD_BITS {               // bits description
    bp_16 MSG_NUM:8;                   // 7:0 Message Number
    bp_16 rsvd1:6;                     // 13:8 Reserved
    bp_16 rsvd2:1;                     // 14 Reserved
    bp_16 Busy:1;                      // 15 Busy Flag
    bp_32 DATA_B:1;                    // 16 Access Data Bytes 4-7
    bp_32 DATA_A:1;                    // 17 Access Data Bytes 0-3
    bp_32 TxRqst:1;                    // 18 Access Transmission Request Bit
    bp_32 ClrIntPnd:1;                 // 19 Clear Interrupt Pending Bit
    bp_32 Control:1;                   // 20 Access Control Bits
    bp_32 Arb:1;                       // 21 Access Arbitration Bits
    bp_32 Mask:1;                      // 22 Access Mask Bits
    bp_32 DIR:1;                       // 23 Write/Read Direction
    bp_32 rsvd3:8;                     // 31:24 Reserved
};

union CAN_IF2CMD_REG {
    bp_32  all;
    struct  CAN_IF2CMD_BITS  bit;
};

struct CAN_IF2MSK_BITS {               // bits description
    bp_32 Msk:29;                      // 28:0 Identifier Mask
    bp_32 rsvd1:1;                     // 29 Reserved
    bp_32 MDir:1;                      // 30 Mask Message Direction
    bp_32 MXtd:1;                      // 31 Mask Extended Identifier
};

union CAN_IF2MSK_REG {
    bp_32  all;
    struct  CAN_IF2MSK_BITS  bit;
};

struct CAN_IF2ARB_BITS {               // bits description
    bp_32 ID:29;                       // 28:0 Message  Identifier
    bp_32 Dir:1;                       // 29 Message Direction
    bp_32 Xtd:1;                       // 30 Extended Identifier
    bp_32 MsgVal:1;                    // 31 Message Valid
};

union CAN_IF2ARB_REG {
    bp_32  all;
    struct  CAN_IF2ARB_BITS  bit;
};

struct CAN_IF2MCTL_BITS {              // bits description
    bp_16 DLC:4;                       // 3:0 Data length code
    bp_16 rsvd1:3;                     // 6:4 Reserved
    bp_16 EoB:1;                       // 7 End of Block
    bp_16 TxRqst:1;                    // 8 Transmit Request
    bp_16 RmtEn:1;                     // 9 Remote Enable
    bp_16 RxIE:1;                      // 10 Receive Interrupt Enable
    bp_16 TxIE:1;                      // 11 Transmit Interrupt Enable
    bp_16 UMask:1;                     // 12 Use Acceptance Mask
    bp_16 IntPnd:1;                    // 13 Interrupt Pending
    bp_16 MsgLst:1;                    // 14 Message Lost
    bp_16 NewDat:1;                    // 15 New Data
    bp_32 rsvd2:16;                    // 31:16 Reserved
};

union CAN_IF2MCTL_REG {
    bp_32  all;
    struct  CAN_IF2MCTL_BITS  bit;
};

struct CAN_IF2DATA_BITS {              // bits description
    bp_16 Data_0:8;                    // 7:0 Data Byte 0
    bp_16 Data_1:8;                    // 15:8 Data Byte 1
    bp_32 Data_2:8;                    // 23:16 Data Byte 2
    bp_32 Data_3:8;                    // 31:24 Data Byte 3
};

union CAN_IF2DATA_REG {
    bp_32  all;
    struct  CAN_IF2DATA_BITS  bit;
};

struct CAN_IF2DATB_BITS {              // bits description
    bp_16 Data_4:8;                    // 7:0 Data Byte 4
    bp_16 Data_5:8;                    // 15:8 Data Byte 5
    bp_32 Data_6:8;                    // 23:16 Data Byte 6
    bp_32 Data_7:8;                    // 31:24 Data Byte 7
};

union CAN_IF2DATB_REG {
    bp_32  all;
    struct  CAN_IF2DATB_BITS  bit;
};

struct CAN_IF3OBS_BITS {               // bits description
    bp_16 Mask:1;                      // 0 Mask data read observation
    bp_16 Arb:1;                       // 1 Arbitration data read observation
    bp_16 Ctrl:1;                      // 2 Ctrl read observation
    bp_16 Data_A:1;                    // 3 Data A read observation
    bp_16 Data_B:1;                    // 4 Data B read observation
    bp_16 rsvd1:3;                     // 7:5 Reserved
    bp_16 IF3SM:1;                     // 8 IF3 Status of Mask data read access
    bp_16 IF3SA:1;                     // 9 IF3 Status of Arbitration data read access
    bp_16 IF3SC:1;                     // 10 IF3 Status of Control bits read access
    bp_16 IF3SDA:1;                    // 11 IF3 Status of Data A read access
    bp_16 IF3SDB:1;                    // 12 IF3 Status of Data B read access
    bp_16 rsvd2:2;                     // 14:13 Reserved
    bp_16 IF3Upd:1;                    // 15 IF3 Update Data
    bp_32 rsvd3:16;                    // 31:16 Reserved
};

union CAN_IF3OBS_REG {
    bp_32  all;
    struct  CAN_IF3OBS_BITS  bit;
};

struct CAN_IF3MSK_BITS {               // bits description
    bp_32 Msk:29;                      // 28:0 Mask
    bp_32 rsvd1:1;                     // 29 Reserved
    bp_32 MDir:1;                      // 30 Mask Message Direction
    bp_32 MXtd:1;                      // 31 Mask Extended Identifier
};

union CAN_IF3MSK_REG {
    bp_32  all;
    struct  CAN_IF3MSK_BITS  bit;
};

struct CAN_IF3ARB_BITS {               // bits description
    bp_32 ID:29;                       // 28:0 Message  Identifier
    bp_32 Dir:1;                       // 29 Message Direction
    bp_32 Xtd:1;                       // 30 Extended Identifier
    bp_32 MsgVal:1;                    // 31 Message Valid
};

union CAN_IF3ARB_REG {
    bp_32  all;
    struct  CAN_IF3ARB_BITS  bit;
};

struct CAN_IF3MCTL_BITS {              // bits description
    bp_16 DLC:4;                       // 3:0 Data length code
    bp_16 rsvd1:3;                     // 6:4 Reserved
    bp_16 EoB:1;                       // 7 End of Block
    bp_16 TxRqst:1;                    // 8 Transmit Request
    bp_16 RmtEn:1;                     // 9 Remote Enable
    bp_16 RxIE:1;                      // 10 Receive Interrupt Enable
    bp_16 TxIE:1;                      // 11 Transmit Interrupt Enable
    bp_16 UMask:1;                     // 12 Use Acceptance Mask
    bp_16 IntPnd:1;                    // 13 Interrupt Pending
    bp_16 MsgLst:1;                    // 14 Message Lost
    bp_16 NewDat:1;                    // 15 New Data
    bp_32 rsvd2:16;                    // 31:16 Reserved
};

union CAN_IF3MCTL_REG {
    bp_32  all;
    struct  CAN_IF3MCTL_BITS  bit;
};

struct CAN_IF3DATA_BITS {              // bits description
    bp_16 Data_0:8;                    // 7:0 Data Byte 0
    bp_16 Data_1:8;                    // 15:8 Data Byte 1
    bp_32 Data_2:8;                    // 23:16 Data Byte 2
    bp_32 Data_3:8;                    // 31:24 Data Byte 3
};

union CAN_IF3DATA_REG {
    bp_32  all;
    struct  CAN_IF3DATA_BITS  bit;
};

struct CAN_IF3DATB_BITS {              // bits description
    bp_16 Data_4:8;                    // 7:0 Data Byte 4
    bp_16 Data_5:8;                    // 15:8 Data Byte 5
    bp_32 Data_6:8;                    // 23:16 Data Byte 6
    bp_32 Data_7:8;                    // 31:24 Data Byte 7
};

union CAN_IF3DATB_REG {
    bp_32  all;
    struct  CAN_IF3DATB_BITS  bit;
};

struct CAN_REGS {
    union   CAN_CTL_REG                      CAN_CTL;                      // CAN Control Register
    union   CAN_ES_REG                       CAN_ES;                       // Error and Status Register
    union   CAN_ERRC_REG                     CAN_ERRC;                     // Error Counter Register
    union   CAN_BTR_REG                      CAN_BTR;                      // Bit Timing Register
    union   CAN_INT_REG                      CAN_INT;                      // Interrupt Register
    union   CAN_TEST_REG                     CAN_TEST;                     // Test Register
    uint32_t                                 rsvd1[2];                     // Reserved
    union   CAN_PERR_REG                     CAN_PERR;                     // CAN Parity Error Code Register
    uint32_t                                 rsvd2[16];                    // Reserved
    union   CAN_RAM_INIT_REG                 CAN_RAM_INIT;                 // CAN RAM Initialization Register
    uint32_t                                 rsvd3[6];                     // Reserved
    union   CAN_GLB_INT_EN_REG               CAN_GLB_INT_EN;               // CAN Global Interrupt Enable Register
    union   CAN_GLB_INT_FLG_REG              CAN_GLB_INT_FLG;              // CAN Global Interrupt Flag Register
    union   CAN_GLB_INT_CLR_REG              CAN_GLB_INT_CLR;              // CAN Global Interrupt Clear Register
    uint32_t                                 rsvd4[18];                    // Reserved
    bp_32                                    CAN_ABOTR;                    // Auto-Bus-On Time Register
    union   CAN_TXRQ_X_REG                   CAN_TXRQ_X;                   // CAN Transmission Request Register
    bp_32                                    CAN_TXRQ_21;                  // CAN Transmission Request 2_1 Register
    uint32_t                                 rsvd5[6];                     // Reserved
    union   CAN_NDAT_X_REG                   CAN_NDAT_X;                   // CAN New Data Register
    bp_32                                    CAN_NDAT_21;                  // CAN New Data 2_1 Register
    uint32_t                                 rsvd6[6];                     // Reserved
    union   CAN_IPEN_X_REG                   CAN_IPEN_X;                   // CAN Interrupt Pending Register
    bp_32                                    CAN_IPEN_21;                  // CAN Interrupt Pending 2_1 Register
    uint32_t                                 rsvd7[6];                     // Reserved
    union   CAN_MVAL_X_REG                   CAN_MVAL_X;                   // CAN Message Valid Register
    bp_32                                    CAN_MVAL_21;                  // CAN Message Valid 2_1 Register
    uint32_t                                 rsvd8[8];                     // Reserved
    bp_32                                    CAN_IP_MUX21;                 // CAN Interrupt Multiplexer 2_1 Register
    uint32_t                                 rsvd9[18];                    // Reserved
    union   CAN_IF1CMD_REG                   CAN_IF1CMD;                   // IF1 Command Register
    union   CAN_IF1MSK_REG                   CAN_IF1MSK;                   // IF1 Mask Register
    union   CAN_IF1ARB_REG                   CAN_IF1ARB;                   // IF1 Arbitration Register
    union   CAN_IF1MCTL_REG                  CAN_IF1MCTL;                  // IF1 Message Control Register
    union   CAN_IF1DATA_REG                  CAN_IF1DATA;                  // IF1 Data A Register
    union   CAN_IF1DATB_REG                  CAN_IF1DATB;                  // IF1 Data B Register
    uint32_t                                 rsvd10[4];                    // Reserved
    union   CAN_IF2CMD_REG                   CAN_IF2CMD;                   // IF2 Command Register
    union   CAN_IF2MSK_REG                   CAN_IF2MSK;                   // IF2 Mask Register
    union   CAN_IF2ARB_REG                   CAN_IF2ARB;                   // IF2 Arbitration Register
    union   CAN_IF2MCTL_REG                  CAN_IF2MCTL;                  // IF2 Message Control Register
    union   CAN_IF2DATA_REG                  CAN_IF2DATA;                  // IF2 Data A Register
    union   CAN_IF2DATB_REG                  CAN_IF2DATB;                  // IF2 Data B Register
    uint32_t                                 rsvd11[4];                    // Reserved
    union   CAN_IF3OBS_REG                   CAN_IF3OBS;                   // IF3 Observation Register
    union   CAN_IF3MSK_REG                   CAN_IF3MSK;                   // IF3 Mask Register
    union   CAN_IF3ARB_REG                   CAN_IF3ARB;                   // IF3 Arbitration Register
    union   CAN_IF3MCTL_REG                  CAN_IF3MCTL;                  // IF3 Message Control Register
    union   CAN_IF3DATA_REG                  CAN_IF3DATA;                  // IF3 Data A Register
    union   CAN_IF3DATB_REG                  CAN_IF3DATB;                  // IF3 Data B Register
    uint32_t                                 rsvd12[4];                    // Reserved
    bp_32                                    CAN_IF3UPD;                   // IF3 Update Enable Register
};

//---------------------------------------------------------------------------
// CAN External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct CAN_REGS CanaRegs;
extern volatile struct CAN_REGS CanbRegs;
#endif
#ifdef CPU2
extern volatile struct CAN_REGS CanaRegs;
extern volatile struct CAN_REGS CanbRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
