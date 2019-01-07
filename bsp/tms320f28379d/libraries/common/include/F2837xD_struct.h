//###########################################################################
//
// FILE:   F2837xD_sdfm_strut.h
//
// TITLE:  contains structures used for the SDFM driver.
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

#ifndef F2837xD_SDFM_STRUCT_H
#define F2837xD_SDFM_STRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_CPUTIMER 4
#define MAX_ECAP 7
#define MAX_EPWM 13
#define MAX_EQEP 4
#define MAX_I2C 2
#define MAX_MCBSP 2
#define MAX_SCI 2
#define MAX_SPI 4
#define MAX_ADC	5
#define MAX_SDFM 3
#define MAX_TRIPSEL 15

extern volatile Uint16 *TRIP_SEL[MAX_TRIPSEL];
extern volatile struct ADC_REGS *ADC[MAX_ADC];
extern volatile struct CPUTIMER_REGS *CPUTIMER[MAX_CPUTIMER];
extern volatile struct ECAP_REGS *ECAP[MAX_ECAP];
extern volatile struct EPWM_REGS *EPWM[MAX_EPWM];
extern volatile struct EQEP_REGS *EQEP[MAX_EQEP];
extern volatile struct I2C_REGS *I2C[MAX_I2C];
extern volatile struct McBSP_REGS *MCBSP[MAX_MCBSP];
extern volatile struct SCI_REGS *SCI[MAX_SCI];
extern volatile struct SPI_REGS *SPI[MAX_SPI];
extern volatile struct SDFM_REGS *SDFM[MAX_SDFM];

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F2837xD_SDFM_STRUCT_H

//
// End of file
//
