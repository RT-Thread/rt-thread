//*****************************************************************************
//
// bl_crystal.h - Macros to convert a CRYSTAL_FREQ value into the appropriate
//                RCC XTAL field define.
//
// Copyright (c) 2010-2017 Texas Instruments Incorporated.  All rights reserved.
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

#ifndef __BL_CRYSTAL_H__
#define __BL_CRYSTAL_H__

//*****************************************************************************
//
// Convert the CRYSTAL_FREQ value into the corresponding to M and N values for
// the PLL.
//
//*****************************************************************************
#if CRYSTAL_FREQ == 5000000
#define PLL_M_TO_REG            96
#define PLL_N_TO_REG            0
#elif CRYSTAL_FREQ == 6000000
#define PLL_M_TO_REG            80
#define PLL_N_TO_REG            0
#elif CRYSTAL_FREQ == 8000000
#define PLL_M_TO_REG            60
#define PLL_N_TO_REG            0
#elif CRYSTAL_FREQ == 10000000
#define PLL_M_TO_REG            48
#define PLL_N_TO_REG            0
#elif CRYSTAL_FREQ == 12000000
#define PLL_M_TO_REG            40
#define PLL_N_TO_REG            0
#elif CRYSTAL_FREQ == 16000000
#define PLL_M_TO_REG            30
#define PLL_N_TO_REG            0
#elif CRYSTAL_FREQ == 25000000
#define PLL_M_TO_REG            96
#define PLL_N_TO_REG            4
#else
#error ERROR: Unknown CRYSTAL_FREQ value specified!
#endif

#endif // __BL_CRYSTAL_H__
