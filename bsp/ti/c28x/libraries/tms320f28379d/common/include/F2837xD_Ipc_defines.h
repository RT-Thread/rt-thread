//###########################################################################
//
// FILE:    F2837xD_Ipc_defines.h
//
// TITLE:   F2837xD IPC support definitions
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

#ifndef F2837xD_IPC_DEFINES_H
#define F2837xD_IPC_DEFINES_H

//
// Defines
//
#define C1TOC2_MSG_RAM ((void *)0x3FC00)
#define C2TOC1_MSG_RAM ((void *)0x3F800)

#if defined(CPU1)
    #define SEND_MSG_RAM C1TOC2_MSG_RAM
    #define RECV_MSG_RAM C2TOC1_MSG_RAM
#elif defined(CPU2)
    #define SEND_MSG_RAM C2TOC1_MSG_RAM
    #define RECV_MSG_RAM C1TOC2_MSG_RAM
#endif
#define MSG_RAM_SIZE 0x400

//
//Used with SendIpcData() and SendIpcCommand() to avoid setting a flag
//
#define NO_IPC_FLAG 32

#endif  // end of F2837xD_IPC_DEFINES_H definition

//
// End of file
//
