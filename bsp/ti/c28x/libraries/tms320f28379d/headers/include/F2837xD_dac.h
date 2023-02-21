//###########################################################################
//
// FILE:    F2837xD_dac.h
//
// TITLE:   DAC Register Definitions.
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

#ifndef __F2837xD_DAC_H__
#define __F2837xD_DAC_H__

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// DAC Individual Register Bit Definitions:

struct DACREV_BITS {                    // bits description
    Uint16 REV:8;                       // 7:0 DAC Revision Register
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union DACREV_REG {
    Uint16  all;
    struct  DACREV_BITS  bit;
};

struct DACCTL_BITS {                    // bits description
    Uint16 DACREFSEL:1;                 // 0 DAC Reference Select
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 LOADMODE:1;                  // 2 DACVALA Load Mode
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 SYNCSEL:4;                   // 7:4 DAC PWMSYNC Select
    Uint16 rsvd3:8;                     // 15:8 Reserved
};

union DACCTL_REG {
    Uint16  all;
    struct  DACCTL_BITS  bit;
};

struct DACVALA_BITS {                   // bits description
    Uint16 DACVALA:12;                  // 11:0 DAC Active Output Code
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union DACVALA_REG {
    Uint16  all;
    struct  DACVALA_BITS  bit;
};

struct DACVALS_BITS {                   // bits description
    Uint16 DACVALS:12;                  // 11:0 DAC Shadow Output Code
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union DACVALS_REG {
    Uint16  all;
    struct  DACVALS_BITS  bit;
};

struct DACOUTEN_BITS {                  // bits description
    Uint16 DACOUTEN:1;                  // 0 DAC Output Code
    Uint16 rsvd1:15;                    // 15:1 Reserved
};

union DACOUTEN_REG {
    Uint16  all;
    struct  DACOUTEN_BITS  bit;
};

struct DACLOCK_BITS {                   // bits description
    Uint16 DACCTL:1;                    // 0 DAC Control Register Lock
    Uint16 DACVAL:1;                    // 1 DAC Value Register Lock
    Uint16 DACOUTEN:1;                  // 2 DAC Output Enable Register Lock
    Uint16 rsvd1:13;                    // 15:3 Reserved
};

union DACLOCK_REG {
    Uint16  all;
    struct  DACLOCK_BITS  bit;
};

struct DACTRIM_BITS {                   // bits description
    Uint16 OFFSET_TRIM:8;               // 7:0 DAC Offset Trim
    Uint16 rsvd1:4;                     // 11:8 Reserved
    Uint16 rsvd2:4;                     // 15:12 Reserved
};

union DACTRIM_REG {
    Uint16  all;
    struct  DACTRIM_BITS  bit;
};

struct DAC_REGS {
    union   DACREV_REG                       DACREV;                       // DAC Revision Register
    union   DACCTL_REG                       DACCTL;                       // DAC Control Register
    union   DACVALA_REG                      DACVALA;                      // DAC Value Register - Active
    union   DACVALS_REG                      DACVALS;                      // DAC Value Register - Shadow
    union   DACOUTEN_REG                     DACOUTEN;                     // DAC Output Enable Register
    union   DACLOCK_REG                      DACLOCK;                      // DAC Lock Register
    union   DACTRIM_REG                      DACTRIM;                      // DAC Trim Register
    Uint16                                   rsvd1;                        // Reserved
};

//---------------------------------------------------------------------------
// DAC External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct DAC_REGS DacaRegs;
extern volatile struct DAC_REGS DacbRegs;
extern volatile struct DAC_REGS DaccRegs;
#endif
#ifdef CPU2
extern volatile struct DAC_REGS DacaRegs;
extern volatile struct DAC_REGS DacbRegs;
extern volatile struct DAC_REGS DaccRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
