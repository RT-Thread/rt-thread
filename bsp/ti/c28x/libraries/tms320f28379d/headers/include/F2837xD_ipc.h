//###########################################################################
//
// FILE:    F2837xD_ipc.h
//
// TITLE:   IPC Register Definitions.
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

#ifndef __F2837xD_IPC_H__
#define __F2837xD_IPC_H__

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// IPC Individual Register Bit Definitions:

struct IPCACK_BITS {                    // bits description
    Uint16 IPC0:1;                      // 0 Local IPC Flag 0 Acknowledgement
    Uint16 IPC1:1;                      // 1 Local IPC Flag 1 Acknowledgement
    Uint16 IPC2:1;                      // 2 Local IPC Flag 2 Acknowledgement
    Uint16 IPC3:1;                      // 3 Local IPC Flag 3 Acknowledgement
    Uint16 IPC4:1;                      // 4 Local IPC Flag 4 Acknowledgement
    Uint16 IPC5:1;                      // 5 Local IPC Flag 5 Acknowledgement
    Uint16 IPC6:1;                      // 6 Local IPC Flag 6 Acknowledgement
    Uint16 IPC7:1;                      // 7 Local IPC Flag 7 Acknowledgement
    Uint16 IPC8:1;                      // 8 Local IPC Flag 8 Acknowledgement
    Uint16 IPC9:1;                      // 9 Local IPC Flag 9 Acknowledgement
    Uint16 IPC10:1;                     // 10 Local IPC Flag 10 Acknowledgement
    Uint16 IPC11:1;                     // 11 Local IPC Flag 11 Acknowledgement
    Uint16 IPC12:1;                     // 12 Local IPC Flag 12 Acknowledgement
    Uint16 IPC13:1;                     // 13 Local IPC Flag 13 Acknowledgement
    Uint16 IPC14:1;                     // 14 Local IPC Flag 14 Acknowledgement
    Uint16 IPC15:1;                     // 15 Local IPC Flag 15 Acknowledgement
    Uint16 IPC16:1;                     // 16 Local IPC Flag 16 Acknowledgement
    Uint16 IPC17:1;                     // 17 Local IPC Flag 17 Acknowledgement
    Uint16 IPC18:1;                     // 18 Local IPC Flag 18 Acknowledgement
    Uint16 IPC19:1;                     // 19 Local IPC Flag 19 Acknowledgement
    Uint16 IPC20:1;                     // 20 Local IPC Flag 20 Acknowledgement
    Uint16 IPC21:1;                     // 21 Local IPC Flag 21 Acknowledgement
    Uint16 IPC22:1;                     // 22 Local IPC Flag 22 Acknowledgement
    Uint16 IPC23:1;                     // 23 Local IPC Flag 23 Acknowledgement
    Uint16 IPC24:1;                     // 24 Local IPC Flag 24 Acknowledgement
    Uint16 IPC25:1;                     // 25 Local IPC Flag 25 Acknowledgement
    Uint16 IPC26:1;                     // 26 Local IPC Flag 26 Acknowledgement
    Uint16 IPC27:1;                     // 27 Local IPC Flag 27 Acknowledgement
    Uint16 IPC28:1;                     // 28 Local IPC Flag 28 Acknowledgement
    Uint16 IPC29:1;                     // 29 Local IPC Flag 29 Acknowledgement
    Uint16 IPC30:1;                     // 30 Local IPC Flag 30 Acknowledgement
    Uint16 IPC31:1;                     // 31 Local IPC Flag 31 Acknowledgement
};

union IPCACK_REG {
    Uint32  all;
    struct  IPCACK_BITS  bit;
};

struct IPCSTS_BITS {                    // bits description
    Uint16 IPC0:1;                      // 0 Local IPC Flag 0 Status
    Uint16 IPC1:1;                      // 1 Local IPC Flag 1 Status
    Uint16 IPC2:1;                      // 2 Local IPC Flag 2 Status
    Uint16 IPC3:1;                      // 3 Local IPC Flag 3 Status
    Uint16 IPC4:1;                      // 4 Local IPC Flag 4 Status
    Uint16 IPC5:1;                      // 5 Local IPC Flag 5 Status
    Uint16 IPC6:1;                      // 6 Local IPC Flag 6 Status
    Uint16 IPC7:1;                      // 7 Local IPC Flag 7 Status
    Uint16 IPC8:1;                      // 8 Local IPC Flag 8 Status
    Uint16 IPC9:1;                      // 9 Local IPC Flag 9 Status
    Uint16 IPC10:1;                     // 10 Local IPC Flag 10 Status
    Uint16 IPC11:1;                     // 11 Local IPC Flag 11 Status
    Uint16 IPC12:1;                     // 12 Local IPC Flag 12 Status
    Uint16 IPC13:1;                     // 13 Local IPC Flag 13 Status
    Uint16 IPC14:1;                     // 14 Local IPC Flag 14 Status
    Uint16 IPC15:1;                     // 15 Local IPC Flag 15 Status
    Uint16 IPC16:1;                     // 16 Local IPC Flag 16 Status
    Uint16 IPC17:1;                     // 17 Local IPC Flag 17 Status
    Uint16 IPC18:1;                     // 18 Local IPC Flag 18 Status
    Uint16 IPC19:1;                     // 19 Local IPC Flag 19 Status
    Uint16 IPC20:1;                     // 20 Local IPC Flag 20 Status
    Uint16 IPC21:1;                     // 21 Local IPC Flag 21 Status
    Uint16 IPC22:1;                     // 22 Local IPC Flag 22 Status
    Uint16 IPC23:1;                     // 23 Local IPC Flag 23 Status
    Uint16 IPC24:1;                     // 24 Local IPC Flag 24 Status
    Uint16 IPC25:1;                     // 25 Local IPC Flag 25 Status
    Uint16 IPC26:1;                     // 26 Local IPC Flag 26 Status
    Uint16 IPC27:1;                     // 27 Local IPC Flag 27 Status
    Uint16 IPC28:1;                     // 28 Local IPC Flag 28 Status
    Uint16 IPC29:1;                     // 29 Local IPC Flag 29 Status
    Uint16 IPC30:1;                     // 30 Local IPC Flag 30 Status
    Uint16 IPC31:1;                     // 31 Local IPC Flag 31 Status
};

union IPCSTS_REG {
    Uint32  all;
    struct  IPCSTS_BITS  bit;
};

struct IPCSET_BITS {                    // bits description
    Uint16 IPC0:1;                      // 0 Set Remote IPC0 Flag
    Uint16 IPC1:1;                      // 1 Set Remote IPC1 Flag
    Uint16 IPC2:1;                      // 2 Set Remote IPC2 Flag
    Uint16 IPC3:1;                      // 3 Set Remote IPC3 Flag
    Uint16 IPC4:1;                      // 4 Set Remote IPC4 Flag
    Uint16 IPC5:1;                      // 5 Set Remote IPC5 Flag
    Uint16 IPC6:1;                      // 6 Set Remote IPC6 Flag
    Uint16 IPC7:1;                      // 7 Set Remote IPC7 Flag
    Uint16 IPC8:1;                      // 8 Set Remote IPC8 Flag
    Uint16 IPC9:1;                      // 9 Set Remote IPC9 Flag
    Uint16 IPC10:1;                     // 10 Set Remote IPC10 Flag
    Uint16 IPC11:1;                     // 11 Set Remote IPC11 Flag
    Uint16 IPC12:1;                     // 12 Set Remote IPC12 Flag
    Uint16 IPC13:1;                     // 13 Set Remote IPC13 Flag
    Uint16 IPC14:1;                     // 14 Set Remote IPC14 Flag
    Uint16 IPC15:1;                     // 15 Set Remote IPC15 Flag
    Uint16 IPC16:1;                     // 16 Set Remote IPC16 Flag
    Uint16 IPC17:1;                     // 17 Set Remote IPC17 Flag
    Uint16 IPC18:1;                     // 18 Set Remote IPC18 Flag
    Uint16 IPC19:1;                     // 19 Set Remote IPC19 Flag
    Uint16 IPC20:1;                     // 20 Set Remote IPC20 Flag
    Uint16 IPC21:1;                     // 21 Set Remote IPC21 Flag
    Uint16 IPC22:1;                     // 22 Set Remote IPC22 Flag
    Uint16 IPC23:1;                     // 23 Set Remote IPC23 Flag
    Uint16 IPC24:1;                     // 24 Set Remote IPC24 Flag
    Uint16 IPC25:1;                     // 25 Set Remote IPC25 Flag
    Uint16 IPC26:1;                     // 26 Set Remote IPC26 Flag
    Uint16 IPC27:1;                     // 27 Set Remote IPC27 Flag
    Uint16 IPC28:1;                     // 28 Set Remote IPC28 Flag
    Uint16 IPC29:1;                     // 29 Set Remote IPC29 Flag
    Uint16 IPC30:1;                     // 30 Set Remote IPC30 Flag
    Uint16 IPC31:1;                     // 31 Set Remote IPC31 Flag
};

union IPCSET_REG {
    Uint32  all;
    struct  IPCSET_BITS  bit;
};

struct IPCCLR_BITS {                    // bits description
    Uint16 IPC0:1;                      // 0 Clear Remote IPC0 Flag
    Uint16 IPC1:1;                      // 1 Clear Remote IPC1 Flag
    Uint16 IPC2:1;                      // 2 Clear Remote IPC2 Flag
    Uint16 IPC3:1;                      // 3 Clear Remote IPC3 Flag
    Uint16 IPC4:1;                      // 4 Clear Remote IPC4 Flag
    Uint16 IPC5:1;                      // 5 Clear Remote IPC5 Flag
    Uint16 IPC6:1;                      // 6 Clear Remote IPC6 Flag
    Uint16 IPC7:1;                      // 7 Clear Remote IPC7 Flag
    Uint16 IPC8:1;                      // 8 Clear Remote IPC8 Flag
    Uint16 IPC9:1;                      // 9 Clear Remote IPC9 Flag
    Uint16 IPC10:1;                     // 10 Clear Remote IPC10 Flag
    Uint16 IPC11:1;                     // 11 Clear Remote IPC11 Flag
    Uint16 IPC12:1;                     // 12 Clear Remote IPC12 Flag
    Uint16 IPC13:1;                     // 13 Clear Remote IPC13 Flag
    Uint16 IPC14:1;                     // 14 Clear Remote IPC14 Flag
    Uint16 IPC15:1;                     // 15 Clear Remote IPC15 Flag
    Uint16 IPC16:1;                     // 16 Clear Remote IPC16 Flag
    Uint16 IPC17:1;                     // 17 Clear Remote IPC17 Flag
    Uint16 IPC18:1;                     // 18 Clear Remote IPC18 Flag
    Uint16 IPC19:1;                     // 19 Clear Remote IPC19 Flag
    Uint16 IPC20:1;                     // 20 Clear Remote IPC20 Flag
    Uint16 IPC21:1;                     // 21 Clear Remote IPC21 Flag
    Uint16 IPC22:1;                     // 22 Clear Remote IPC22 Flag
    Uint16 IPC23:1;                     // 23 Clear Remote IPC23 Flag
    Uint16 IPC24:1;                     // 24 Clear Remote IPC24 Flag
    Uint16 IPC25:1;                     // 25 Clear Remote IPC25 Flag
    Uint16 IPC26:1;                     // 26 Clear Remote IPC26 Flag
    Uint16 IPC27:1;                     // 27 Clear Remote IPC27 Flag
    Uint16 IPC28:1;                     // 28 Clear Remote IPC28 Flag
    Uint16 IPC29:1;                     // 29 Clear Remote IPC29 Flag
    Uint16 IPC30:1;                     // 30 Clear Remote IPC30 Flag
    Uint16 IPC31:1;                     // 31 Clear Remote IPC31 Flag
};

union IPCCLR_REG {
    Uint32  all;
    struct  IPCCLR_BITS  bit;
};

struct IPCFLG_BITS {                    // bits description
    Uint16 IPC0:1;                      // 0 Remote IPC0 Flag Status
    Uint16 IPC1:1;                      // 1 Remote IPC1 Flag Status
    Uint16 IPC2:1;                      // 2 Remote IPC2 Flag Status
    Uint16 IPC3:1;                      // 3 Remote IPC3 Flag Status
    Uint16 IPC4:1;                      // 4 Remote IPC4 Flag Status
    Uint16 IPC5:1;                      // 5 Remote IPC5 Flag Status
    Uint16 IPC6:1;                      // 6 Remote IPC6 Flag Status
    Uint16 IPC7:1;                      // 7 Remote IPC7 Flag Status
    Uint16 IPC8:1;                      // 8 Remote IPC8 Flag Status
    Uint16 IPC9:1;                      // 9 Remote IPC9 Flag Status
    Uint16 IPC10:1;                     // 10 Remote IPC10 Flag Status
    Uint16 IPC11:1;                     // 11 Remote IPC11 Flag Status
    Uint16 IPC12:1;                     // 12 Remote IPC12 Flag Status
    Uint16 IPC13:1;                     // 13 Remote IPC13 Flag Status
    Uint16 IPC14:1;                     // 14 Remote IPC14 Flag Status
    Uint16 IPC15:1;                     // 15 Remote IPC15 Flag Status
    Uint16 IPC16:1;                     // 16 Remote IPC16 Flag Status
    Uint16 IPC17:1;                     // 17 Remote IPC17 Flag Status
    Uint16 IPC18:1;                     // 18 Remote IPC18 Flag Status
    Uint16 IPC19:1;                     // 19 Remote IPC19 Flag Status
    Uint16 IPC20:1;                     // 20 Remote IPC20 Flag Status
    Uint16 IPC21:1;                     // 21 Remote IPC21 Flag Status
    Uint16 IPC22:1;                     // 22 Remote IPC22 Flag Status
    Uint16 IPC23:1;                     // 23 Remote IPC23 Flag Status
    Uint16 IPC24:1;                     // 24 Remote IPC24 Flag Status
    Uint16 IPC25:1;                     // 25 Remote IPC25 Flag Status
    Uint16 IPC26:1;                     // 26 Remote IPC26 Flag Status
    Uint16 IPC27:1;                     // 27 Remote IPC27 Flag Status
    Uint16 IPC28:1;                     // 28 Remote IPC28 Flag Status
    Uint16 IPC29:1;                     // 29 Remote IPC29 Flag Status
    Uint16 IPC30:1;                     // 30 Remote IPC30 Flag Status
    Uint16 IPC31:1;                     // 31 Remote IPC31 Flag Status
};

union IPCFLG_REG {
    Uint32  all;
    struct  IPCFLG_BITS  bit;
};

struct IPC_REGS_CPU1 {
    union   IPCACK_REG                       IPCACK;                       // IPC incoming flag clear (acknowledge) register
    union   IPCSTS_REG                       IPCSTS;                       // IPC incoming flag status register
    union   IPCSET_REG                       IPCSET;                       // IPC remote flag set register
    union   IPCCLR_REG                       IPCCLR;                       // IPC remote flag clear register
    union   IPCFLG_REG                       IPCFLG;                       // IPC remote flag status register
    Uint16                                   rsvd1[2];                     // Reserved
    Uint32                                   IPCCOUNTERL;                  // IPC Counter Low Register
    Uint32                                   IPCCOUNTERH;                  // IPC Counter High Register
    Uint32                                   IPCSENDCOM;                   // Local to Remote IPC Command Register
    Uint32                                   IPCSENDADDR;                  // Local to Remote IPC Address Register
    Uint32                                   IPCSENDDATA;                  // Local to Remote IPC Data Register
    Uint32                                   IPCREMOTEREPLY;               // Remote to Local IPC Reply Data Register
    Uint32                                   IPCRECVCOM;                   // Remote to Local IPC Command Register
    Uint32                                   IPCRECVADDR;                  // Remote to Local IPC Address Register
    Uint32                                   IPCRECVDATA;                  // Remote to Local IPC Data Register
    Uint32                                   IPCLOCALREPLY;                // Local to Remote IPC Reply Data Register
    Uint32                                   IPCBOOTSTS;                   // CPU2 to CPU1 IPC Boot Status Register
    Uint32                                   IPCBOOTMODE;                  // CPU1 to CPU2 IPC Boot Mode Register
};

struct IPC_REGS_CPU2 {
    union   IPCACK_REG                       IPCACK;                       // IPC incoming flag clear (acknowledge) register
    union   IPCSTS_REG                       IPCSTS;                       // IPC incoming flag status register
    union   IPCSET_REG                       IPCSET;                       // IPC remote flag set register
    union   IPCCLR_REG                       IPCCLR;                       // IPC remote flag clear register
    union   IPCFLG_REG                       IPCFLG;                       // IPC remote flag status register
    Uint16                                   rsvd1[2];                     // Reserved
    Uint32                                   IPCCOUNTERL;                  // IPC Counter Low Register
    Uint32                                   IPCCOUNTERH;                  // IPC Counter High Register
    Uint32                                   IPCRECVCOM;                   // Remote to Local IPC Command Register
    Uint32                                   IPCRECVADDR;                  // Remote to Local IPC Address Register
    Uint32                                   IPCRECVDATA;                  // Remote to Local IPC Data Register
    Uint32                                   IPCLOCALREPLY;                // Local to Remote IPC Reply Data Register
    Uint32                                   IPCSENDCOM;                   // Local to Remote IPC Command Register
    Uint32                                   IPCSENDADDR;                  // Local to Remote IPC Address Register
    Uint32                                   IPCSENDDATA;                  // Local to Remote IPC Data Register
    Uint32                                   IPCREMOTEREPLY;               // Remote to Local IPC Reply Data Register
    Uint32                                   IPCBOOTSTS;                   // CPU2 to CPU1 IPC Boot Status Register
    Uint32                                   IPCBOOTMODE;                  // CPU1 to CPU2 IPC Boot Mode Register
};

//---------------------------------------------------------------------------
// IPC External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct IPC_REGS_CPU1 IpcRegs;
#endif
#ifdef CPU2
extern volatile struct IPC_REGS_CPU2 IpcRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
