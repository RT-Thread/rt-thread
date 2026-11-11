//*****************************************************************************
//
// fpu.h - Prototypes for the floatint point manipulation routines.
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

#ifndef __FPU_H__
#define __FPU_H__

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
// Values that can be passed to FPUHalfPrecisionSet as the ulMode parameter.
//
//*****************************************************************************
#define FPU_HALF_IEEE           0x00000000
#define FPU_HALF_ALTERNATE      0x04000000

//*****************************************************************************
//
// Values that can be passed to FPUNaNModeSet as the ulMode parameter.
//
//*****************************************************************************
#define FPU_NAN_PROPAGATE       0x00000000
#define FPU_NAN_DEFAULT         0x02000000

//*****************************************************************************
//
// Values that can be passed to FPUFlushToZeroModeSet as the ulMode parameter.
//
//*****************************************************************************
#define FPU_FLUSH_TO_ZERO_DIS   0x00000000
#define FPU_FLUSH_TO_ZERO_EN    0x01000000

//*****************************************************************************
//
// Values that can be passed to FPURoundingModeSet as the ulMode parameter.
//
//*****************************************************************************
#define FPU_ROUND_NEAREST       0x00000000
#define FPU_ROUND_POS_INF       0x00400000
#define FPU_ROUND_NEG_INF       0x00800000
#define FPU_ROUND_ZERO          0x00c00000

//*****************************************************************************
//
// Prototypes.
//
//*****************************************************************************
extern void FPUEnable(void);
extern void FPUDisable(void);
extern void FPUStackingEnable(void);
extern void FPULazyStackingEnable(void);
extern void FPUStackingDisable(void);
extern void FPUHalfPrecisionModeSet(unsigned long ulMode);
extern void FPUNaNModeSet(unsigned long ulMode);
extern void FPUFlushToZeroModeSet(unsigned long ulMode);
extern void FPURoundingModeSet(unsigned long ulMode);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __FPU_H__
