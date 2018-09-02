//###########################################################################
//
// FILE:    F2837xD_piectrl.h
//
// TITLE:   PIECTRL Register Definitions.
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

#ifndef __F2837xD_PIECTRL_H__
#define __F2837xD_PIECTRL_H__

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// PIECTRL Individual Register Bit Definitions:

struct PIECTRL_BITS {                   // bits description
    Uint16 ENPIE:1;                     // 0 PIE Enable
    Uint16 PIEVECT:15;                  // 15:1 PIE Vector Address
};

union PIECTRL_REG {
    Uint16  all;
    struct  PIECTRL_BITS  bit;
};

struct PIEACK_BITS {                    // bits description
    Uint16 ACK1:1;                      // 0 Acknowledge PIE Interrupt Group 1
    Uint16 ACK2:1;                      // 1 Acknowledge PIE Interrupt Group 2
    Uint16 ACK3:1;                      // 2 Acknowledge PIE Interrupt Group 3
    Uint16 ACK4:1;                      // 3 Acknowledge PIE Interrupt Group 4
    Uint16 ACK5:1;                      // 4 Acknowledge PIE Interrupt Group 5
    Uint16 ACK6:1;                      // 5 Acknowledge PIE Interrupt Group 6
    Uint16 ACK7:1;                      // 6 Acknowledge PIE Interrupt Group 7
    Uint16 ACK8:1;                      // 7 Acknowledge PIE Interrupt Group 8
    Uint16 ACK9:1;                      // 8 Acknowledge PIE Interrupt Group 9
    Uint16 ACK10:1;                     // 9 Acknowledge PIE Interrupt Group 10
    Uint16 ACK11:1;                     // 10 Acknowledge PIE Interrupt Group 11
    Uint16 ACK12:1;                     // 11 Acknowledge PIE Interrupt Group 12
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union PIEACK_REG {
    Uint16  all;
    struct  PIEACK_BITS  bit;
};

struct PIEIER1_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Enable for Interrupt 1.1
    Uint16 INTx2:1;                     // 1 Enable for Interrupt 1.2
    Uint16 INTx3:1;                     // 2 Enable for Interrupt 1.3
    Uint16 INTx4:1;                     // 3 Enable for Interrupt 1.4
    Uint16 INTx5:1;                     // 4 Enable for Interrupt 1.5
    Uint16 INTx6:1;                     // 5 Enable for Interrupt 1.6
    Uint16 INTx7:1;                     // 6 Enable for Interrupt 1.7
    Uint16 INTx8:1;                     // 7 Enable for Interrupt 1.8
    Uint16 INTx9:1;                     // 8 Enable for Interrupt 1.9
    Uint16 INTx10:1;                    // 9 Enable for Interrupt 1.10
    Uint16 INTx11:1;                    // 10 Enable for Interrupt 1.11
    Uint16 INTx12:1;                    // 11 Enable for Interrupt 1.12
    Uint16 INTx13:1;                    // 12 Enable for Interrupt 1.13
    Uint16 INTx14:1;                    // 13 Enable for Interrupt 1.14
    Uint16 INTx15:1;                    // 14 Enable for Interrupt 1.15
    Uint16 INTx16:1;                    // 15 Enable for Interrupt 1.16
};

union PIEIER1_REG {
    Uint16  all;
    struct  PIEIER1_BITS  bit;
};

struct PIEIFR1_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Flag for Interrupt 1.1
    Uint16 INTx2:1;                     // 1 Flag for Interrupt 1.2
    Uint16 INTx3:1;                     // 2 Flag for Interrupt 1.3
    Uint16 INTx4:1;                     // 3 Flag for Interrupt 1.4
    Uint16 INTx5:1;                     // 4 Flag for Interrupt 1.5
    Uint16 INTx6:1;                     // 5 Flag for Interrupt 1.6
    Uint16 INTx7:1;                     // 6 Flag for Interrupt 1.7
    Uint16 INTx8:1;                     // 7 Flag for Interrupt 1.8
    Uint16 INTx9:1;                     // 8 Flag for Interrupt 1.9
    Uint16 INTx10:1;                    // 9 Flag for Interrupt 1.10
    Uint16 INTx11:1;                    // 10 Flag for Interrupt 1.11
    Uint16 INTx12:1;                    // 11 Flag for Interrupt 1.12
    Uint16 INTx13:1;                    // 12 Flag for Interrupt 1.13
    Uint16 INTx14:1;                    // 13 Flag for Interrupt 1.14
    Uint16 INTx15:1;                    // 14 Flag for Interrupt 1.15
    Uint16 INTx16:1;                    // 15 Flag for Interrupt 1.16
};

union PIEIFR1_REG {
    Uint16  all;
    struct  PIEIFR1_BITS  bit;
};

struct PIEIER2_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Enable for Interrupt 2.1
    Uint16 INTx2:1;                     // 1 Enable for Interrupt 2.2
    Uint16 INTx3:1;                     // 2 Enable for Interrupt 2.3
    Uint16 INTx4:1;                     // 3 Enable for Interrupt 2.4
    Uint16 INTx5:1;                     // 4 Enable for Interrupt 2.5
    Uint16 INTx6:1;                     // 5 Enable for Interrupt 2.6
    Uint16 INTx7:1;                     // 6 Enable for Interrupt 2.7
    Uint16 INTx8:1;                     // 7 Enable for Interrupt 2.8
    Uint16 INTx9:1;                     // 8 Enable for Interrupt 2.9
    Uint16 INTx10:1;                    // 9 Enable for Interrupt 2.10
    Uint16 INTx11:1;                    // 10 Enable for Interrupt 2.11
    Uint16 INTx12:1;                    // 11 Enable for Interrupt 2.12
    Uint16 INTx13:1;                    // 12 Enable for Interrupt 2.13
    Uint16 INTx14:1;                    // 13 Enable for Interrupt 2.14
    Uint16 INTx15:1;                    // 14 Enable for Interrupt 2.15
    Uint16 INTx16:1;                    // 15 Enable for Interrupt 2.16
};

union PIEIER2_REG {
    Uint16  all;
    struct  PIEIER2_BITS  bit;
};

struct PIEIFR2_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Flag for Interrupt 2.1
    Uint16 INTx2:1;                     // 1 Flag for Interrupt 2.2
    Uint16 INTx3:1;                     // 2 Flag for Interrupt 2.3
    Uint16 INTx4:1;                     // 3 Flag for Interrupt 2.4
    Uint16 INTx5:1;                     // 4 Flag for Interrupt 2.5
    Uint16 INTx6:1;                     // 5 Flag for Interrupt 2.6
    Uint16 INTx7:1;                     // 6 Flag for Interrupt 2.7
    Uint16 INTx8:1;                     // 7 Flag for Interrupt 2.8
    Uint16 INTx9:1;                     // 8 Flag for Interrupt 2.9
    Uint16 INTx10:1;                    // 9 Flag for Interrupt 2.10
    Uint16 INTx11:1;                    // 10 Flag for Interrupt 2.11
    Uint16 INTx12:1;                    // 11 Flag for Interrupt 2.12
    Uint16 INTx13:1;                    // 12 Flag for Interrupt 2.13
    Uint16 INTx14:1;                    // 13 Flag for Interrupt 2.14
    Uint16 INTx15:1;                    // 14 Flag for Interrupt 2.15
    Uint16 INTx16:1;                    // 15 Flag for Interrupt 2.16
};

union PIEIFR2_REG {
    Uint16  all;
    struct  PIEIFR2_BITS  bit;
};

struct PIEIER3_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Enable for Interrupt 3.1
    Uint16 INTx2:1;                     // 1 Enable for Interrupt 3.2
    Uint16 INTx3:1;                     // 2 Enable for Interrupt 3.3
    Uint16 INTx4:1;                     // 3 Enable for Interrupt 3.4
    Uint16 INTx5:1;                     // 4 Enable for Interrupt 3.5
    Uint16 INTx6:1;                     // 5 Enable for Interrupt 3.6
    Uint16 INTx7:1;                     // 6 Enable for Interrupt 3.7
    Uint16 INTx8:1;                     // 7 Enable for Interrupt 3.8
    Uint16 INTx9:1;                     // 8 Enable for Interrupt 3.9
    Uint16 INTx10:1;                    // 9 Enable for Interrupt 3.10
    Uint16 INTx11:1;                    // 10 Enable for Interrupt 3.11
    Uint16 INTx12:1;                    // 11 Enable for Interrupt 3.12
    Uint16 INTx13:1;                    // 12 Enable for Interrupt 3.13
    Uint16 INTx14:1;                    // 13 Enable for Interrupt 3.14
    Uint16 INTx15:1;                    // 14 Enable for Interrupt 3.15
    Uint16 INTx16:1;                    // 15 Enable for Interrupt 3.16
};

union PIEIER3_REG {
    Uint16  all;
    struct  PIEIER3_BITS  bit;
};

struct PIEIFR3_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Flag for Interrupt 3.1
    Uint16 INTx2:1;                     // 1 Flag for Interrupt 3.2
    Uint16 INTx3:1;                     // 2 Flag for Interrupt 3.3
    Uint16 INTx4:1;                     // 3 Flag for Interrupt 3.4
    Uint16 INTx5:1;                     // 4 Flag for Interrupt 3.5
    Uint16 INTx6:1;                     // 5 Flag for Interrupt 3.6
    Uint16 INTx7:1;                     // 6 Flag for Interrupt 3.7
    Uint16 INTx8:1;                     // 7 Flag for Interrupt 3.8
    Uint16 INTx9:1;                     // 8 Flag for Interrupt 3.9
    Uint16 INTx10:1;                    // 9 Flag for Interrupt 3.10
    Uint16 INTx11:1;                    // 10 Flag for Interrupt 3.11
    Uint16 INTx12:1;                    // 11 Flag for Interrupt 3.12
    Uint16 INTx13:1;                    // 12 Flag for Interrupt 3.13
    Uint16 INTx14:1;                    // 13 Flag for Interrupt 3.14
    Uint16 INTx15:1;                    // 14 Flag for Interrupt 3.15
    Uint16 INTx16:1;                    // 15 Flag for Interrupt 3.16
};

union PIEIFR3_REG {
    Uint16  all;
    struct  PIEIFR3_BITS  bit;
};

struct PIEIER4_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Enable for Interrupt 4.1
    Uint16 INTx2:1;                     // 1 Enable for Interrupt 4.2
    Uint16 INTx3:1;                     // 2 Enable for Interrupt 4.3
    Uint16 INTx4:1;                     // 3 Enable for Interrupt 4.4
    Uint16 INTx5:1;                     // 4 Enable for Interrupt 4.5
    Uint16 INTx6:1;                     // 5 Enable for Interrupt 4.6
    Uint16 INTx7:1;                     // 6 Enable for Interrupt 4.7
    Uint16 INTx8:1;                     // 7 Enable for Interrupt 4.8
    Uint16 INTx9:1;                     // 8 Enable for Interrupt 4.9
    Uint16 INTx10:1;                    // 9 Enable for Interrupt 4.10
    Uint16 INTx11:1;                    // 10 Enable for Interrupt 4.11
    Uint16 INTx12:1;                    // 11 Enable for Interrupt 4.12
    Uint16 INTx13:1;                    // 12 Enable for Interrupt 4.13
    Uint16 INTx14:1;                    // 13 Enable for Interrupt 4.14
    Uint16 INTx15:1;                    // 14 Enable for Interrupt 4.15
    Uint16 INTx16:1;                    // 15 Enable for Interrupt 4.16
};

union PIEIER4_REG {
    Uint16  all;
    struct  PIEIER4_BITS  bit;
};

struct PIEIFR4_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Flag for Interrupt 4.1
    Uint16 INTx2:1;                     // 1 Flag for Interrupt 4.2
    Uint16 INTx3:1;                     // 2 Flag for Interrupt 4.3
    Uint16 INTx4:1;                     // 3 Flag for Interrupt 4.4
    Uint16 INTx5:1;                     // 4 Flag for Interrupt 4.5
    Uint16 INTx6:1;                     // 5 Flag for Interrupt 4.6
    Uint16 INTx7:1;                     // 6 Flag for Interrupt 4.7
    Uint16 INTx8:1;                     // 7 Flag for Interrupt 4.8
    Uint16 INTx9:1;                     // 8 Flag for Interrupt 4.9
    Uint16 INTx10:1;                    // 9 Flag for Interrupt 4.10
    Uint16 INTx11:1;                    // 10 Flag for Interrupt 4.11
    Uint16 INTx12:1;                    // 11 Flag for Interrupt 4.12
    Uint16 INTx13:1;                    // 12 Flag for Interrupt 4.13
    Uint16 INTx14:1;                    // 13 Flag for Interrupt 4.14
    Uint16 INTx15:1;                    // 14 Flag for Interrupt 4.15
    Uint16 INTx16:1;                    // 15 Flag for Interrupt 4.16
};

union PIEIFR4_REG {
    Uint16  all;
    struct  PIEIFR4_BITS  bit;
};

struct PIEIER5_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Enable for Interrupt 5.1
    Uint16 INTx2:1;                     // 1 Enable for Interrupt 5.2
    Uint16 INTx3:1;                     // 2 Enable for Interrupt 5.3
    Uint16 INTx4:1;                     // 3 Enable for Interrupt 5.4
    Uint16 INTx5:1;                     // 4 Enable for Interrupt 5.5
    Uint16 INTx6:1;                     // 5 Enable for Interrupt 5.6
    Uint16 INTx7:1;                     // 6 Enable for Interrupt 5.7
    Uint16 INTx8:1;                     // 7 Enable for Interrupt 5.8
    Uint16 INTx9:1;                     // 8 Enable for Interrupt 5.9
    Uint16 INTx10:1;                    // 9 Enable for Interrupt 5.10
    Uint16 INTx11:1;                    // 10 Enable for Interrupt 5.11
    Uint16 INTx12:1;                    // 11 Enable for Interrupt 5.12
    Uint16 INTx13:1;                    // 12 Enable for Interrupt 5.13
    Uint16 INTx14:1;                    // 13 Enable for Interrupt 5.14
    Uint16 INTx15:1;                    // 14 Enable for Interrupt 5.15
    Uint16 INTx16:1;                    // 15 Enable for Interrupt 5.16
};

union PIEIER5_REG {
    Uint16  all;
    struct  PIEIER5_BITS  bit;
};

struct PIEIFR5_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Flag for Interrupt 5.1
    Uint16 INTx2:1;                     // 1 Flag for Interrupt 5.2
    Uint16 INTx3:1;                     // 2 Flag for Interrupt 5.3
    Uint16 INTx4:1;                     // 3 Flag for Interrupt 5.4
    Uint16 INTx5:1;                     // 4 Flag for Interrupt 5.5
    Uint16 INTx6:1;                     // 5 Flag for Interrupt 5.6
    Uint16 INTx7:1;                     // 6 Flag for Interrupt 5.7
    Uint16 INTx8:1;                     // 7 Flag for Interrupt 5.8
    Uint16 INTx9:1;                     // 8 Flag for Interrupt 5.9
    Uint16 INTx10:1;                    // 9 Flag for Interrupt 5.10
    Uint16 INTx11:1;                    // 10 Flag for Interrupt 5.11
    Uint16 INTx12:1;                    // 11 Flag for Interrupt 5.12
    Uint16 INTx13:1;                    // 12 Flag for Interrupt 5.13
    Uint16 INTx14:1;                    // 13 Flag for Interrupt 5.14
    Uint16 INTx15:1;                    // 14 Flag for Interrupt 5.15
    Uint16 INTx16:1;                    // 15 Flag for Interrupt 5.16
};

union PIEIFR5_REG {
    Uint16  all;
    struct  PIEIFR5_BITS  bit;
};

struct PIEIER6_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Enable for Interrupt 6.1
    Uint16 INTx2:1;                     // 1 Enable for Interrupt 6.2
    Uint16 INTx3:1;                     // 2 Enable for Interrupt 6.3
    Uint16 INTx4:1;                     // 3 Enable for Interrupt 6.4
    Uint16 INTx5:1;                     // 4 Enable for Interrupt 6.5
    Uint16 INTx6:1;                     // 5 Enable for Interrupt 6.6
    Uint16 INTx7:1;                     // 6 Enable for Interrupt 6.7
    Uint16 INTx8:1;                     // 7 Enable for Interrupt 6.8
    Uint16 INTx9:1;                     // 8 Enable for Interrupt 6.9
    Uint16 INTx10:1;                    // 9 Enable for Interrupt 6.10
    Uint16 INTx11:1;                    // 10 Enable for Interrupt 6.11
    Uint16 INTx12:1;                    // 11 Enable for Interrupt 6.12
    Uint16 INTx13:1;                    // 12 Enable for Interrupt 6.13
    Uint16 INTx14:1;                    // 13 Enable for Interrupt 6.14
    Uint16 INTx15:1;                    // 14 Enable for Interrupt 6.15
    Uint16 INTx16:1;                    // 15 Enable for Interrupt 6.16
};

union PIEIER6_REG {
    Uint16  all;
    struct  PIEIER6_BITS  bit;
};

struct PIEIFR6_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Flag for Interrupt 6.1
    Uint16 INTx2:1;                     // 1 Flag for Interrupt 6.2
    Uint16 INTx3:1;                     // 2 Flag for Interrupt 6.3
    Uint16 INTx4:1;                     // 3 Flag for Interrupt 6.4
    Uint16 INTx5:1;                     // 4 Flag for Interrupt 6.5
    Uint16 INTx6:1;                     // 5 Flag for Interrupt 6.6
    Uint16 INTx7:1;                     // 6 Flag for Interrupt 6.7
    Uint16 INTx8:1;                     // 7 Flag for Interrupt 6.8
    Uint16 INTx9:1;                     // 8 Flag for Interrupt 6.9
    Uint16 INTx10:1;                    // 9 Flag for Interrupt 6.10
    Uint16 INTx11:1;                    // 10 Flag for Interrupt 6.11
    Uint16 INTx12:1;                    // 11 Flag for Interrupt 6.12
    Uint16 INTx13:1;                    // 12 Flag for Interrupt 6.13
    Uint16 INTx14:1;                    // 13 Flag for Interrupt 6.14
    Uint16 INTx15:1;                    // 14 Flag for Interrupt 6.15
    Uint16 INTx16:1;                    // 15 Flag for Interrupt 6.16
};

union PIEIFR6_REG {
    Uint16  all;
    struct  PIEIFR6_BITS  bit;
};

struct PIEIER7_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Enable for Interrupt 7.1
    Uint16 INTx2:1;                     // 1 Enable for Interrupt 7.2
    Uint16 INTx3:1;                     // 2 Enable for Interrupt 7.3
    Uint16 INTx4:1;                     // 3 Enable for Interrupt 7.4
    Uint16 INTx5:1;                     // 4 Enable for Interrupt 7.5
    Uint16 INTx6:1;                     // 5 Enable for Interrupt 7.6
    Uint16 INTx7:1;                     // 6 Enable for Interrupt 7.7
    Uint16 INTx8:1;                     // 7 Enable for Interrupt 7.8
    Uint16 INTx9:1;                     // 8 Enable for Interrupt 7.9
    Uint16 INTx10:1;                    // 9 Enable for Interrupt 7.10
    Uint16 INTx11:1;                    // 10 Enable for Interrupt 7.11
    Uint16 INTx12:1;                    // 11 Enable for Interrupt 7.12
    Uint16 INTx13:1;                    // 12 Enable for Interrupt 7.13
    Uint16 INTx14:1;                    // 13 Enable for Interrupt 7.14
    Uint16 INTx15:1;                    // 14 Enable for Interrupt 7.15
    Uint16 INTx16:1;                    // 15 Enable for Interrupt 7.16
};

union PIEIER7_REG {
    Uint16  all;
    struct  PIEIER7_BITS  bit;
};

struct PIEIFR7_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Flag for Interrupt 7.1
    Uint16 INTx2:1;                     // 1 Flag for Interrupt 7.2
    Uint16 INTx3:1;                     // 2 Flag for Interrupt 7.3
    Uint16 INTx4:1;                     // 3 Flag for Interrupt 7.4
    Uint16 INTx5:1;                     // 4 Flag for Interrupt 7.5
    Uint16 INTx6:1;                     // 5 Flag for Interrupt 7.6
    Uint16 INTx7:1;                     // 6 Flag for Interrupt 7.7
    Uint16 INTx8:1;                     // 7 Flag for Interrupt 7.8
    Uint16 INTx9:1;                     // 8 Flag for Interrupt 7.9
    Uint16 INTx10:1;                    // 9 Flag for Interrupt 7.10
    Uint16 INTx11:1;                    // 10 Flag for Interrupt 7.11
    Uint16 INTx12:1;                    // 11 Flag for Interrupt 7.12
    Uint16 INTx13:1;                    // 12 Flag for Interrupt 7.13
    Uint16 INTx14:1;                    // 13 Flag for Interrupt 7.14
    Uint16 INTx15:1;                    // 14 Flag for Interrupt 7.15
    Uint16 INTx16:1;                    // 15 Flag for Interrupt 7.16
};

union PIEIFR7_REG {
    Uint16  all;
    struct  PIEIFR7_BITS  bit;
};

struct PIEIER8_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Enable for Interrupt 8.1
    Uint16 INTx2:1;                     // 1 Enable for Interrupt 8.2
    Uint16 INTx3:1;                     // 2 Enable for Interrupt 8.3
    Uint16 INTx4:1;                     // 3 Enable for Interrupt 8.4
    Uint16 INTx5:1;                     // 4 Enable for Interrupt 8.5
    Uint16 INTx6:1;                     // 5 Enable for Interrupt 8.6
    Uint16 INTx7:1;                     // 6 Enable for Interrupt 8.7
    Uint16 INTx8:1;                     // 7 Enable for Interrupt 8.8
    Uint16 INTx9:1;                     // 8 Enable for Interrupt 8.9
    Uint16 INTx10:1;                    // 9 Enable for Interrupt 8.10
    Uint16 INTx11:1;                    // 10 Enable for Interrupt 8.11
    Uint16 INTx12:1;                    // 11 Enable for Interrupt 8.12
    Uint16 INTx13:1;                    // 12 Enable for Interrupt 8.13
    Uint16 INTx14:1;                    // 13 Enable for Interrupt 8.14
    Uint16 INTx15:1;                    // 14 Enable for Interrupt 8.15
    Uint16 INTx16:1;                    // 15 Enable for Interrupt 8.16
};

union PIEIER8_REG {
    Uint16  all;
    struct  PIEIER8_BITS  bit;
};

struct PIEIFR8_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Flag for Interrupt 8.1
    Uint16 INTx2:1;                     // 1 Flag for Interrupt 8.2
    Uint16 INTx3:1;                     // 2 Flag for Interrupt 8.3
    Uint16 INTx4:1;                     // 3 Flag for Interrupt 8.4
    Uint16 INTx5:1;                     // 4 Flag for Interrupt 8.5
    Uint16 INTx6:1;                     // 5 Flag for Interrupt 8.6
    Uint16 INTx7:1;                     // 6 Flag for Interrupt 8.7
    Uint16 INTx8:1;                     // 7 Flag for Interrupt 8.8
    Uint16 INTx9:1;                     // 8 Flag for Interrupt 8.9
    Uint16 INTx10:1;                    // 9 Flag for Interrupt 8.10
    Uint16 INTx11:1;                    // 10 Flag for Interrupt 8.11
    Uint16 INTx12:1;                    // 11 Flag for Interrupt 8.12
    Uint16 INTx13:1;                    // 12 Flag for Interrupt 8.13
    Uint16 INTx14:1;                    // 13 Flag for Interrupt 8.14
    Uint16 INTx15:1;                    // 14 Flag for Interrupt 8.15
    Uint16 INTx16:1;                    // 15 Flag for Interrupt 8.16
};

union PIEIFR8_REG {
    Uint16  all;
    struct  PIEIFR8_BITS  bit;
};

struct PIEIER9_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Enable for Interrupt 9.1
    Uint16 INTx2:1;                     // 1 Enable for Interrupt 9.2
    Uint16 INTx3:1;                     // 2 Enable for Interrupt 9.3
    Uint16 INTx4:1;                     // 3 Enable for Interrupt 9.4
    Uint16 INTx5:1;                     // 4 Enable for Interrupt 9.5
    Uint16 INTx6:1;                     // 5 Enable for Interrupt 9.6
    Uint16 INTx7:1;                     // 6 Enable for Interrupt 9.7
    Uint16 INTx8:1;                     // 7 Enable for Interrupt 9.8
    Uint16 INTx9:1;                     // 8 Enable for Interrupt 9.9
    Uint16 INTx10:1;                    // 9 Enable for Interrupt 9.10
    Uint16 INTx11:1;                    // 10 Enable for Interrupt 9.11
    Uint16 INTx12:1;                    // 11 Enable for Interrupt 9.12
    Uint16 INTx13:1;                    // 12 Enable for Interrupt 9.13
    Uint16 INTx14:1;                    // 13 Enable for Interrupt 9.14
    Uint16 INTx15:1;                    // 14 Enable for Interrupt 9.15
    Uint16 INTx16:1;                    // 15 Enable for Interrupt 9.16
};

union PIEIER9_REG {
    Uint16  all;
    struct  PIEIER9_BITS  bit;
};

struct PIEIFR9_BITS {                   // bits description
    Uint16 INTx1:1;                     // 0 Flag for Interrupt 9.1
    Uint16 INTx2:1;                     // 1 Flag for Interrupt 9.2
    Uint16 INTx3:1;                     // 2 Flag for Interrupt 9.3
    Uint16 INTx4:1;                     // 3 Flag for Interrupt 9.4
    Uint16 INTx5:1;                     // 4 Flag for Interrupt 9.5
    Uint16 INTx6:1;                     // 5 Flag for Interrupt 9.6
    Uint16 INTx7:1;                     // 6 Flag for Interrupt 9.7
    Uint16 INTx8:1;                     // 7 Flag for Interrupt 9.8
    Uint16 INTx9:1;                     // 8 Flag for Interrupt 9.9
    Uint16 INTx10:1;                    // 9 Flag for Interrupt 9.10
    Uint16 INTx11:1;                    // 10 Flag for Interrupt 9.11
    Uint16 INTx12:1;                    // 11 Flag for Interrupt 9.12
    Uint16 INTx13:1;                    // 12 Flag for Interrupt 9.13
    Uint16 INTx14:1;                    // 13 Flag for Interrupt 9.14
    Uint16 INTx15:1;                    // 14 Flag for Interrupt 9.15
    Uint16 INTx16:1;                    // 15 Flag for Interrupt 9.16
};

union PIEIFR9_REG {
    Uint16  all;
    struct  PIEIFR9_BITS  bit;
};

struct PIEIER10_BITS {                  // bits description
    Uint16 INTx1:1;                     // 0 Enable for Interrupt 10.1
    Uint16 INTx2:1;                     // 1 Enable for Interrupt 10.2
    Uint16 INTx3:1;                     // 2 Enable for Interrupt 10.3
    Uint16 INTx4:1;                     // 3 Enable for Interrupt 10.4
    Uint16 INTx5:1;                     // 4 Enable for Interrupt 10.5
    Uint16 INTx6:1;                     // 5 Enable for Interrupt 10.6
    Uint16 INTx7:1;                     // 6 Enable for Interrupt 10.7
    Uint16 INTx8:1;                     // 7 Enable for Interrupt 10.8
    Uint16 INTx9:1;                     // 8 Enable for Interrupt 10.9
    Uint16 INTx10:1;                    // 9 Enable for Interrupt 10.10
    Uint16 INTx11:1;                    // 10 Enable for Interrupt 10.11
    Uint16 INTx12:1;                    // 11 Enable for Interrupt 10.12
    Uint16 INTx13:1;                    // 12 Enable for Interrupt 10.13
    Uint16 INTx14:1;                    // 13 Enable for Interrupt 10.14
    Uint16 INTx15:1;                    // 14 Enable for Interrupt 10.15
    Uint16 INTx16:1;                    // 15 Enable for Interrupt 10.16
};

union PIEIER10_REG {
    Uint16  all;
    struct  PIEIER10_BITS  bit;
};

struct PIEIFR10_BITS {                  // bits description
    Uint16 INTx1:1;                     // 0 Flag for Interrupt 10.1
    Uint16 INTx2:1;                     // 1 Flag for Interrupt 10.2
    Uint16 INTx3:1;                     // 2 Flag for Interrupt 10.3
    Uint16 INTx4:1;                     // 3 Flag for Interrupt 10.4
    Uint16 INTx5:1;                     // 4 Flag for Interrupt 10.5
    Uint16 INTx6:1;                     // 5 Flag for Interrupt 10.6
    Uint16 INTx7:1;                     // 6 Flag for Interrupt 10.7
    Uint16 INTx8:1;                     // 7 Flag for Interrupt 10.8
    Uint16 INTx9:1;                     // 8 Flag for Interrupt 10.9
    Uint16 INTx10:1;                    // 9 Flag for Interrupt 10.10
    Uint16 INTx11:1;                    // 10 Flag for Interrupt 10.11
    Uint16 INTx12:1;                    // 11 Flag for Interrupt 10.12
    Uint16 INTx13:1;                    // 12 Flag for Interrupt 10.13
    Uint16 INTx14:1;                    // 13 Flag for Interrupt 10.14
    Uint16 INTx15:1;                    // 14 Flag for Interrupt 10.15
    Uint16 INTx16:1;                    // 15 Flag for Interrupt 10.16
};

union PIEIFR10_REG {
    Uint16  all;
    struct  PIEIFR10_BITS  bit;
};

struct PIEIER11_BITS {                  // bits description
    Uint16 INTx1:1;                     // 0 Enable for Interrupt 11.1
    Uint16 INTx2:1;                     // 1 Enable for Interrupt 11.2
    Uint16 INTx3:1;                     // 2 Enable for Interrupt 11.3
    Uint16 INTx4:1;                     // 3 Enable for Interrupt 11.4
    Uint16 INTx5:1;                     // 4 Enable for Interrupt 11.5
    Uint16 INTx6:1;                     // 5 Enable for Interrupt 11.6
    Uint16 INTx7:1;                     // 6 Enable for Interrupt 11.7
    Uint16 INTx8:1;                     // 7 Enable for Interrupt 11.8
    Uint16 INTx9:1;                     // 8 Enable for Interrupt 11.9
    Uint16 INTx10:1;                    // 9 Enable for Interrupt 11.10
    Uint16 INTx11:1;                    // 10 Enable for Interrupt 11.11
    Uint16 INTx12:1;                    // 11 Enable for Interrupt 11.12
    Uint16 INTx13:1;                    // 12 Enable for Interrupt 11.13
    Uint16 INTx14:1;                    // 13 Enable for Interrupt 11.14
    Uint16 INTx15:1;                    // 14 Enable for Interrupt 11.15
    Uint16 INTx16:1;                    // 15 Enable for Interrupt 11.16
};

union PIEIER11_REG {
    Uint16  all;
    struct  PIEIER11_BITS  bit;
};

struct PIEIFR11_BITS {                  // bits description
    Uint16 INTx1:1;                     // 0 Flag for Interrupt 11.1
    Uint16 INTx2:1;                     // 1 Flag for Interrupt 11.2
    Uint16 INTx3:1;                     // 2 Flag for Interrupt 11.3
    Uint16 INTx4:1;                     // 3 Flag for Interrupt 11.4
    Uint16 INTx5:1;                     // 4 Flag for Interrupt 11.5
    Uint16 INTx6:1;                     // 5 Flag for Interrupt 11.6
    Uint16 INTx7:1;                     // 6 Flag for Interrupt 11.7
    Uint16 INTx8:1;                     // 7 Flag for Interrupt 11.8
    Uint16 INTx9:1;                     // 8 Flag for Interrupt 11.9
    Uint16 INTx10:1;                    // 9 Flag for Interrupt 11.10
    Uint16 INTx11:1;                    // 10 Flag for Interrupt 11.11
    Uint16 INTx12:1;                    // 11 Flag for Interrupt 11.12
    Uint16 INTx13:1;                    // 12 Flag for Interrupt 11.13
    Uint16 INTx14:1;                    // 13 Flag for Interrupt 11.14
    Uint16 INTx15:1;                    // 14 Flag for Interrupt 11.15
    Uint16 INTx16:1;                    // 15 Flag for Interrupt 11.16
};

union PIEIFR11_REG {
    Uint16  all;
    struct  PIEIFR11_BITS  bit;
};

struct PIEIER12_BITS {                  // bits description
    Uint16 INTx1:1;                     // 0 Enable for Interrupt 12.1
    Uint16 INTx2:1;                     // 1 Enable for Interrupt 12.2
    Uint16 INTx3:1;                     // 2 Enable for Interrupt 12.3
    Uint16 INTx4:1;                     // 3 Enable for Interrupt 12.4
    Uint16 INTx5:1;                     // 4 Enable for Interrupt 12.5
    Uint16 INTx6:1;                     // 5 Enable for Interrupt 12.6
    Uint16 INTx7:1;                     // 6 Enable for Interrupt 12.7
    Uint16 INTx8:1;                     // 7 Enable for Interrupt 12.8
    Uint16 INTx9:1;                     // 8 Enable for Interrupt 12.9
    Uint16 INTx10:1;                    // 9 Enable for Interrupt 12.10
    Uint16 INTx11:1;                    // 10 Enable for Interrupt 12.11
    Uint16 INTx12:1;                    // 11 Enable for Interrupt 12.12
    Uint16 INTx13:1;                    // 12 Enable for Interrupt 12.13
    Uint16 INTx14:1;                    // 13 Enable for Interrupt 12.14
    Uint16 INTx15:1;                    // 14 Enable for Interrupt 12.15
    Uint16 INTx16:1;                    // 15 Enable for Interrupt 12.16
};

union PIEIER12_REG {
    Uint16  all;
    struct  PIEIER12_BITS  bit;
};

struct PIEIFR12_BITS {                  // bits description
    Uint16 INTx1:1;                     // 0 Flag for Interrupt 12.1
    Uint16 INTx2:1;                     // 1 Flag for Interrupt 12.2
    Uint16 INTx3:1;                     // 2 Flag for Interrupt 12.3
    Uint16 INTx4:1;                     // 3 Flag for Interrupt 12.4
    Uint16 INTx5:1;                     // 4 Flag for Interrupt 12.5
    Uint16 INTx6:1;                     // 5 Flag for Interrupt 12.6
    Uint16 INTx7:1;                     // 6 Flag for Interrupt 12.7
    Uint16 INTx8:1;                     // 7 Flag for Interrupt 12.8
    Uint16 INTx9:1;                     // 8 Flag for Interrupt 12.9
    Uint16 INTx10:1;                    // 9 Flag for Interrupt 12.10
    Uint16 INTx11:1;                    // 10 Flag for Interrupt 12.11
    Uint16 INTx12:1;                    // 11 Flag for Interrupt 12.12
    Uint16 INTx13:1;                    // 12 Flag for Interrupt 12.13
    Uint16 INTx14:1;                    // 13 Flag for Interrupt 12.14
    Uint16 INTx15:1;                    // 14 Flag for Interrupt 12.15
    Uint16 INTx16:1;                    // 15 Flag for Interrupt 12.16
};

union PIEIFR12_REG {
    Uint16  all;
    struct  PIEIFR12_BITS  bit;
};

struct PIE_CTRL_REGS {
    union   PIECTRL_REG                      PIECTRL;                      // ePIE Control Register
    union   PIEACK_REG                       PIEACK;                       // Interrupt Acknowledge Register
    union   PIEIER1_REG                      PIEIER1;                      // Interrupt Group 1 Enable Register
    union   PIEIFR1_REG                      PIEIFR1;                      // Interrupt Group 1 Flag Register
    union   PIEIER2_REG                      PIEIER2;                      // Interrupt Group 2 Enable Register
    union   PIEIFR2_REG                      PIEIFR2;                      // Interrupt Group 2 Flag Register
    union   PIEIER3_REG                      PIEIER3;                      // Interrupt Group 3 Enable Register
    union   PIEIFR3_REG                      PIEIFR3;                      // Interrupt Group 3 Flag Register
    union   PIEIER4_REG                      PIEIER4;                      // Interrupt Group 4 Enable Register
    union   PIEIFR4_REG                      PIEIFR4;                      // Interrupt Group 4 Flag Register
    union   PIEIER5_REG                      PIEIER5;                      // Interrupt Group 5 Enable Register
    union   PIEIFR5_REG                      PIEIFR5;                      // Interrupt Group 5 Flag Register
    union   PIEIER6_REG                      PIEIER6;                      // Interrupt Group 6 Enable Register
    union   PIEIFR6_REG                      PIEIFR6;                      // Interrupt Group 6 Flag Register
    union   PIEIER7_REG                      PIEIER7;                      // Interrupt Group 7 Enable Register
    union   PIEIFR7_REG                      PIEIFR7;                      // Interrupt Group 7 Flag Register
    union   PIEIER8_REG                      PIEIER8;                      // Interrupt Group 8 Enable Register
    union   PIEIFR8_REG                      PIEIFR8;                      // Interrupt Group 8 Flag Register
    union   PIEIER9_REG                      PIEIER9;                      // Interrupt Group 9 Enable Register
    union   PIEIFR9_REG                      PIEIFR9;                      // Interrupt Group 9 Flag Register
    union   PIEIER10_REG                     PIEIER10;                     // Interrupt Group 10 Enable Register
    union   PIEIFR10_REG                     PIEIFR10;                     // Interrupt Group 10 Flag Register
    union   PIEIER11_REG                     PIEIER11;                     // Interrupt Group 11 Enable Register
    union   PIEIFR11_REG                     PIEIFR11;                     // Interrupt Group 11 Flag Register
    union   PIEIER12_REG                     PIEIER12;                     // Interrupt Group 12 Enable Register
    union   PIEIFR12_REG                     PIEIFR12;                     // Interrupt Group 12 Flag Register
};

//---------------------------------------------------------------------------
// PIECTRL External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct PIE_CTRL_REGS PieCtrlRegs;
#endif
#ifdef CPU2
extern volatile struct PIE_CTRL_REGS PieCtrlRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
