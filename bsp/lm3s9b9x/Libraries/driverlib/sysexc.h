//*****************************************************************************
//
// sysexc.h - Prototypes for the System Exception Module routines.
//
// Copyright (c) 2011 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 8264 of the Stellaris Peripheral Driver Library.
//
//*****************************************************************************

#ifndef __SYSEXC_H__
#define __SYSEXC_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Values that can be passed to SysExcIntEnable, SysExcIntDisable, and
// SysExcIntClear as the ulIntFlags parameter, and returned from
// SysExcIntStatus.
//
//*****************************************************************************
#define SYSEXC_INT_FP_IXC       0x00000020  // FP Inexact exception interrupt
#define SYSEXC_INT_FP_OFC       0x00000010  // FP Overflow exception interrupt
#define SYSEXC_INT_FP_UFC       0x00000008  // FP Underflow exception interrupt
#define SYSEXC_INT_FP_IOC       0x00000004  // FP Invalid operation interrupt
#define SYSEXC_INT_FP_DZC       0x00000002  // FP Divide by zero exception int
#define SYSEXC_INT_FP_IDC       0x00000001  // FP Input denormal exception int

//*****************************************************************************
//
// Prototypes.
//
//*****************************************************************************
extern void SysExcIntRegister(void (*pfnHandler)(void));
extern void SysExcIntUnregister(void);
extern void SysExcIntEnable(unsigned long ulIntFlags);
extern void SysExcIntDisable(unsigned long ulIntFlags);
extern unsigned long SysExcIntStatus(tBoolean bMasked);
extern void SysExcIntClear(unsigned long ulIntFlags);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __SYSEXC_H__
