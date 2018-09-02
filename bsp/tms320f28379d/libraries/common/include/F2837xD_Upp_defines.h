//###########################################################################
//
// FILE:   F2837xD_Upp_defines.h
//
// TITLE:  #defines used in Upp examples
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

#ifndef F2837xD_UPP_DEFINES_H
#define F2837xD_UPP_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//
#define uPP_TX_MSGRAM_ADDR 0x6C00
#define uPP_TX_MSGRAM_SIZE 512

#define uPP_RX_MSGRAM_ADDR 0x6E00
#define uPP_RX_MSGRAM_SIZE 512

#define uPP_RX_MODE 0
#define uPP_TX_MODE 1

#define uPP_SDR 0
#define uPP_DDR 1

#define uPP_TX_SIZE_64B 0
#define uPP_TX_SIZE_128B 1
#define uPP_TX_SIZE_256B 3

#define uPP_RX_SIZE_64B 0
#define uPP_RX_SIZE_128B 1
#define uPP_RX_SIZE_256B 3

#define uPP_INT_EOWI 0x8
#define uPP_INT_EOLI 0x10
#define uPP_INT_EOWQ 0x800
#define uPP_INT_EOLQ 0x1000

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F2837xD_UPP_DEFINES_H

//
// End of file
//
