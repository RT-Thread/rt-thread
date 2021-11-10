/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file system_hc32f460.h
 **
 ** A detailed description is available at
 ** @link Hc32f460SystemGroup Hc32f460System description @endlink
 **
 **   - 2018-10-15  CDT  First version.
 **
 ******************************************************************************/
#ifndef __SYSTEM_HC32F460_H__
#define __SYSTEM_HC32F460_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <stdint.h>

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/**
 *******************************************************************************
 ** \defgroup Hc32f460SystemGroup HC32F460 System Configure
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global pre-processor symbols/macros ('define')
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief Clock Setup macro definition
 **
 ** - 0: CLOCK_SETTING_NONE  - User provides own clock setting in application
 ** - 1: CLOCK_SETTING_CMSIS -
 ******************************************************************************/
#define CLOCK_SETTING_NONE  0u
#define CLOCK_SETTING_CMSIS 1u

#define HRC_FREQ_MON()                  (*((volatile unsigned int*)(0x40010684UL)))

#if !defined (HRC_16MHz_VALUE)
    #define HRC_16MHz_VALUE             ((uint32_t)16000000UL)  /*!< Internal high speed RC freq.(16MHz) */
#endif

#if !defined (HRC_20MHz_VALUE)
    #define HRC_20MHz_VALUE             ((uint32_t)20000000UL)  /*!< Internal high speed RC freq.(20MHz) */
#endif

#if !defined (MRC_VALUE)
#define MRC_VALUE ((uint32_t)8000000)   /*!< Internal middle speed RC freq. */
#endif

#if !defined (LRC_VALUE)
#define LRC_VALUE ((uint32_t)32768)     /*!< Internal low speed RC freq. */
#endif

#if !defined (XTAL_VALUE)
#define XTAL_VALUE ((uint32_t)8000000)  /*!< External high speed OSC freq. */
#endif

#if !defined (XTAL32_VALUE)
#define XTAL32_VALUE ((uint32_t)32768)  /*!< External low speed OSC freq. */
#endif

/******************************************************************************/
/*                                                                            */
/*                      START OF USER SETTINGS HERE                           */
/*                      ===========================                           */
/*                                                                            */
/*                 All lines with '<<<' can be set by user.                   */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global function prototypes ('extern', definition in C source)              */
/******************************************************************************/
extern uint32_t HRC_VALUE;                // HRC Clock Frequency (Core Clock)
extern uint32_t SystemCoreClock;          // System Clock Frequency (Core Clock)
extern void SystemInit(void);             // Initialize the system
extern void SystemCoreClockUpdate(void);  // Update SystemCoreClock variable

//@} // Hc32f460SystemGroup

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_HC32F460_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
