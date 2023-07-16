//*****************************************************************************
//
// bl_can_timing.h - Timing definitions for the CAN controller.
//
// Copyright (c) 2008-2017 Texas Instruments Incorporated.  All rights reserved.
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

#ifndef __BL_CAN_TIMING_H__
#define __BL_CAN_TIMING_H__

#ifdef CAN_ENABLE_UPDATE

//*****************************************************************************
//
// This macro is used to generate the proper value for CAN_BIT_TIMING.  The
// values selected for each crystal/bit rate combination assumes a propagation
// delay of 300ns (which will always be rounded up to the next integer multiple
// of the CAN time quanta).
//
//*****************************************************************************
#define CAN_BIT_REG(seg1, seg2, sjw, brp)                                     \
                                ((((seg2 - 1) << CAN_BIT_TSEG2_S) &           \
                                  CAN_BIT_TSEG2_M) |                          \
                                 (((seg1 - 1) << CAN_BIT_TSEG1_S) &           \
                                  CAN_BIT_TSEG1_M) |                          \
                                 (((sjw - 1) << CAN_BIT_SJW_S) &              \
                                  CAN_BIT_SJW_M) |                            \
                                 (((brp - 1) << CAN_BIT_BRP_S) &              \
                                  CAN_BIT_BRP_M))

//*****************************************************************************
//
// The settings for a 16MHz crystal frequency.
//
//*****************************************************************************
#if CRYSTAL_FREQ == 16000000
#if CAN_BIT_RATE == 1000000
#define CAN_BIT_TIMING          CAN_BIT_REG(10, 5, 4, 1)    // tProp = 312ns
#elif CAN_BIT_RATE == 500000
#define CAN_BIT_TIMING          CAN_BIT_REG(9, 6, 4, 2)     // tProp = 375ns
#elif CAN_BIT_RATE == 250000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 3, 8)     // tProp = 500ns
#elif CAN_BIT_RATE == 125000
#define CAN_BIT_TIMING          CAN_BIT_REG(8, 7, 4, 8)     // tProp = 500ns
#elif CAN_BIT_RATE == 50000
#define CAN_BIT_TIMING          CAN_BIT_REG(8, 7, 4, 20)    // tProp = 1250ns
#elif CAN_BIT_RATE == 20000
#define CAN_BIT_TIMING          CAN_BIT_REG(8, 7, 4, 50)    // tProp = 3125ns
#else
#error Invalid CAN_BIT_RATE value used with a 16MHz crystal.
#endif

//*****************************************************************************
//
// The settings for a 12MHz crystal frequency.
//
//*****************************************************************************
#elif CRYSTAL_FREQ == 12000000
#if CAN_BIT_RATE == 1000000
#define CAN_BIT_TIMING          CAN_BIT_REG(8, 3, 3, 1)     // tProp = 416ns
#elif CAN_BIT_RATE == 500000
#define CAN_BIT_TIMING          CAN_BIT_REG(7, 4, 4, 2)     // tProp = 500ns
#elif CAN_BIT_RATE == 250000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 4, 4)     // tProp = 333ns
#elif CAN_BIT_RATE == 125000
#define CAN_BIT_TIMING          CAN_BIT_REG(8, 7, 4, 6)     // tProp = 500ns
#elif CAN_BIT_RATE == 50000
#define CAN_BIT_TIMING          CAN_BIT_REG(8, 7, 4, 15)    // tProp = 1250ns
#elif CAN_BIT_RATE == 20000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 4, 50)    // tProp = 4166ns
#else
#error Invalid CAN_BIT_RATE value used with a 12MHz crystal.
#endif

//*****************************************************************************
//
// The settings for a 10MHz crystal frequency.
//
//*****************************************************************************
#elif CRYSTAL_FREQ == 10000000
#if CAN_BIT_RATE == 1000000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 3, 3, 1)     // tProp = 300ns
#elif CAN_BIT_RATE == 500000
#define CAN_BIT_TIMING          CAN_BIT_REG(11, 8, 4, 1)    // tProp = 300ns
#elif CAN_BIT_RATE == 250000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 4, 4)     // tProp = 400ns
#elif CAN_BIT_RATE == 125000
#define CAN_BIT_TIMING          CAN_BIT_REG(8, 7, 4, 5)     // tProp = 500ns
#elif CAN_BIT_RATE == 50000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 4, 20)    // tProp = 2000ns
#elif CAN_BIT_RATE == 20000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 4, 50)    // tProp = 5000ns
#else
#error Invalid CAN_BIT_RATE value used with a 10MHz crystal.
#endif

//*****************************************************************************
//
// The settings for a 8MHz crystal frequency.
//
//*****************************************************************************
#elif CRYSTAL_FREQ == 8000000
#if CAN_BIT_RATE == 1000000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 2, 2, 1)     // tProp = 375ns
#elif CAN_BIT_RATE == 500000
#define CAN_BIT_TIMING          CAN_BIT_REG(9, 6, 4, 1)     // tProp = 375ns
#elif CAN_BIT_RATE == 250000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 3, 4)     // tProp = 500ns
#elif CAN_BIT_RATE == 125000
#define CAN_BIT_TIMING          CAN_BIT_REG(8, 7, 4, 4)     // tProp = 500ns
#elif CAN_BIT_RATE == 50000
#define CAN_BIT_TIMING          CAN_BIT_REG(8, 7, 4, 10)    // tProp = 1250ns
#elif CAN_BIT_RATE == 20000
#define CAN_BIT_TIMING          CAN_BIT_REG(8, 7, 4, 25)    // tProp = 3125ns
#else
#error Invalid CAN_BIT_RATE value used with a 8MHz crystal.
#endif

//*****************************************************************************
//
// The settings for a 6MHz crystal frequency.
//
//*****************************************************************************
#elif CRYSTAL_FREQ == 6000000
#if CAN_BIT_RATE == 500000
#define CAN_BIT_TIMING          CAN_BIT_REG(7, 4, 4, 1)     // tProp = 500ns
#elif CAN_BIT_RATE == 250000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 4, 2)     // tProp = 333ns
#elif CAN_BIT_RATE == 125000
#define CAN_BIT_TIMING          CAN_BIT_REG(8, 7, 4, 3)     // tProp = 500ns
#elif CAN_BIT_RATE == 50000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 4, 10)    // tProp = 1666ns
#elif CAN_BIT_RATE == 20000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 4, 25)    // tProp = 4166ns
#else
#error Invalid CAN_BIT_RATE value used with a 6MHz crystal.
#endif

//*****************************************************************************
//
// The settings for a 5MHz crystal frequency.
//
//*****************************************************************************
#elif CRYSTAL_FREQ == 5000000
#if CAN_BIT_RATE == 500000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 3, 3, 1)     // tProp = 600ns
#elif CAN_BIT_RATE == 250000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 4, 2)     // tProp = 400ns
#elif CAN_BIT_RATE == 125000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 4, 4)     // tProp = 800ns
#elif CAN_BIT_RATE == 50000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 4, 10)    // tProp = 2000ns
#elif CAN_BIT_RATE == 20000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 4, 25)    // tProp = 5000ns
#else
#error Invalid CAN_BIT_RATE value used with a 5MHz crystal.
#endif

//*****************************************************************************
//
// An unsupported crystal frequency was specified.
//
//*****************************************************************************
#else
#error The CRYSTAL_FREQ value is not supported by the CAN controller.
#endif

#endif

#endif // __BL_CAN_TIMING_H__
