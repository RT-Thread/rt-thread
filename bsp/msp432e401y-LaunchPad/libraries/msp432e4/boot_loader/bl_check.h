//*****************************************************************************
//
// bl_check.h - Definitions for the forced update check function.
//
// Copyright (c) 2007-2017 Texas Instruments Incorporated.  All rights reserved.
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
//*****************************************************************************

#ifndef __BL_CHECK_H__
#define __BL_CHECK_H__

//*****************************************************************************
//
// Prototype for the forced update check function.
//
//*****************************************************************************
extern uint32_t CheckForceUpdate(void);
#ifdef ENABLE_UPDATE_CHECK
extern uint32_t CheckGPIOForceUpdate(void);
extern uint32_t g_ui32Forced;
#endif

#endif // __BL_CHECK_H__
