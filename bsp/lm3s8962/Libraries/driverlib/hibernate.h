//*****************************************************************************
//
// hibernate.h - API definition for the Hibernation module.
//
// Copyright (c) 2007-2011 Texas Instruments Incorporated.  All rights reserved.
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

#ifndef __HIBERNATE_H__
#define __HIBERNATE_H__

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
// Macros needed for selecting the clock source for HibernateClockSelect()
//
//*****************************************************************************
#define HIBERNATE_CLOCK_SEL_RAW    0x00000004
#define HIBERNATE_CLOCK_SEL_DIV128 0x00000000

//*****************************************************************************
//
// Macros need to configure wake events for HibernateWakeSet()
//
//*****************************************************************************
#define HIBERNATE_WAKE_PIN        0x00000010
#define HIBERNATE_WAKE_RTC        0x00000008
#define HIBERNATE_WAKE_LOW_BAT    0x00000200

//*****************************************************************************
//
// Macros needed to configure low battery detect for HibernateLowBatSet()
//
//*****************************************************************************
#define HIBERNATE_LOW_BAT_DETECT  0x00000020
#define HIBERNATE_LOW_BAT_ABORT   0x000000A0
#define HIBERNATE_LOW_BAT_1_9V    0x00000000
#define HIBERNATE_LOW_BAT_2_1V    0x00002000
#define HIBERNATE_LOW_BAT_2_3V    0x00004000
#define HIBERNATE_LOW_BAT_2_5V    0x00006000

//*****************************************************************************
//
// Macros defining interrupt source bits for the interrupt functions.
//
//*****************************************************************************
#define HIBERNATE_INT_WR_COMPLETE 0x00000010
#define HIBERNATE_INT_PIN_WAKE    0x00000008
#define HIBERNATE_INT_LOW_BAT     0x00000004
#define HIBERNATE_INT_RTC_MATCH_0 0x00000001
#define HIBERNATE_INT_RTC_MATCH_1 0x00000002

//*****************************************************************************
//
// Macros defining oscillator configuration options for the
// HibernateClockConfig() function.
//
//*****************************************************************************
#define HIBERNATE_OSC_LOWDRIVE  0x00040000
#define HIBERNATE_OSC_HIGHDRIVE 0x00060000
#define HIBERNATE_OSC_DISABLE   0x00010000

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
extern void HibernateEnableExpClk(unsigned long ulHibClk);
extern void HibernateDisable(void);
extern void HibernateClockSelect(unsigned long ulClockInput);
extern void HibernateRTCEnable(void);
extern void HibernateRTCDisable(void);
extern void HibernateWakeSet(unsigned long ulWakeFlags);
extern unsigned long HibernateWakeGet(void);
extern void HibernateLowBatSet(unsigned long ulLowBatFlags);
extern unsigned long HibernateLowBatGet(void);
extern void HibernateRTCSet(unsigned long ulRTCValue);
extern unsigned long HibernateRTCGet(void);
extern void HibernateRTCMatch0Set(unsigned long ulMatch);
extern unsigned long HibernateRTCMatch0Get(void);
extern void HibernateRTCMatch1Set(unsigned long ulMatch);
extern unsigned long HibernateRTCMatch1Get(void);
extern void HibernateRTCTrimSet(unsigned long ulTrim);
extern unsigned long HibernateRTCTrimGet(void);
extern void HibernateDataSet(unsigned long *pulData, unsigned long ulCount);
extern void HibernateDataGet(unsigned long *pulData, unsigned long ulCount);
extern void HibernateRequest(void);
extern void HibernateIntEnable(unsigned long ulIntFlags);
extern void HibernateIntDisable(unsigned long ulIntFlags);
extern void HibernateIntRegister(void (*pfnHandler)(void));
extern void HibernateIntUnregister(void);
extern unsigned long HibernateIntStatus(tBoolean bMasked);
extern void HibernateIntClear(unsigned long ulIntFlags);
extern unsigned long HibernateIsActive(void);
extern void HibernateRTCSSMatch0Set(unsigned long ulMatch);
extern unsigned long HibernateRTCSSMatch0Get(void);
extern unsigned long HibernateRTCSSGet(void);
extern void HibernateClockConfig(unsigned long ulConfig);
extern void HibernateBatCheckStart(void);
extern unsigned long HibernateBatCheckDone(void);

//*****************************************************************************
//
// Several Hibernate module APIs have been renamed, with the original function
// name being deprecated.  These defines provide backward compatibility.
//
//*****************************************************************************
#ifndef DEPRECATED
#include "driverlib/sysctl.h"
#define HibernateEnable(a)                         \
        HibernateEnableExpClk(a, SysCtlClockGet())
#endif

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // __HIBERNATE_H__
