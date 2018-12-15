//###########################################################################
//
// FILE:    F2837xD_xint.h
//
// TITLE:   XINT Register Definitions.
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

#ifndef __F2837xD_XINT_H__
#define __F2837xD_XINT_H__

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// XINT Individual Register Bit Definitions:

struct XINT1CR_BITS {                   // bits description
    Uint16 ENABLE:1;                    // 0 XINT1 Enable
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 POLARITY:2;                  // 3:2 XINT1 Polarity
    Uint16 rsvd2:12;                    // 15:4 Reserved
};

union XINT1CR_REG {
    Uint16  all;
    struct  XINT1CR_BITS  bit;
};

struct XINT2CR_BITS {                   // bits description
    Uint16 ENABLE:1;                    // 0 XINT2 Enable
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 POLARITY:2;                  // 3:2 XINT2 Polarity
    Uint16 rsvd2:12;                    // 15:4 Reserved
};

union XINT2CR_REG {
    Uint16  all;
    struct  XINT2CR_BITS  bit;
};

struct XINT3CR_BITS {                   // bits description
    Uint16 ENABLE:1;                    // 0 XINT3 Enable
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 POLARITY:2;                  // 3:2 XINT3 Polarity
    Uint16 rsvd2:12;                    // 15:4 Reserved
};

union XINT3CR_REG {
    Uint16  all;
    struct  XINT3CR_BITS  bit;
};

struct XINT4CR_BITS {                   // bits description
    Uint16 ENABLE:1;                    // 0 XINT4 Enable
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 POLARITY:2;                  // 3:2 XINT4 Polarity
    Uint16 rsvd2:12;                    // 15:4 Reserved
};

union XINT4CR_REG {
    Uint16  all;
    struct  XINT4CR_BITS  bit;
};

struct XINT5CR_BITS {                   // bits description
    Uint16 ENABLE:1;                    // 0 XINT5 Enable
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 POLARITY:2;                  // 3:2 XINT5 Polarity
    Uint16 rsvd2:12;                    // 15:4 Reserved
};

union XINT5CR_REG {
    Uint16  all;
    struct  XINT5CR_BITS  bit;
};

struct XINT_REGS {
    union   XINT1CR_REG                      XINT1CR;                      // XINT1 configuration register
    union   XINT2CR_REG                      XINT2CR;                      // XINT2 configuration register
    union   XINT3CR_REG                      XINT3CR;                      // XINT3 configuration register
    union   XINT4CR_REG                      XINT4CR;                      // XINT4 configuration register
    union   XINT5CR_REG                      XINT5CR;                      // XINT5 configuration register
    Uint16                                   rsvd1[3];                     // Reserved
    Uint16                                   XINT1CTR;                     // XINT1 counter register
    Uint16                                   XINT2CTR;                     // XINT2 counter register
    Uint16                                   XINT3CTR;                     // XINT3 counter register
};

//---------------------------------------------------------------------------
// XINT External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct XINT_REGS XintRegs;
#endif
#ifdef CPU2
extern volatile struct XINT_REGS XintRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
