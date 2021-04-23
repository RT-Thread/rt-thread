/**
 * @file    wdt.h
 * @brief   Watchdog timer (WDT) function prototypes and data types.
 */

/* ****************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2020-04-20 15:06:58 -0500 (Mon, 20 Apr 2020) $
 * $Revision: 53142 $
 *
 *************************************************************************** */

/* Define to prevent redundant inclusion */
#ifndef _WDT_H_
#define _WDT_H_

/* **** Includes **** */
#include <stdint.h>
#include "mxc_config.h"
#include "mxc_sys.h"
#include "wdt_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup wdt Watchdog Timer (WDT)
 * @ingroup periphlibs
 * @{
 */

/* **** Definitions **** */

/** @brief Watchdog period enumeration. 
    Used to configure the period of the watchdog interrupt */
typedef enum {
    WDT_PERIOD_2_31 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW31, /**< Period 2^31 */
    WDT_PERIOD_2_30 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW30, /**< Period 2^30 */
    WDT_PERIOD_2_29 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW29, /**< Period 2^29 */
    WDT_PERIOD_2_28 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW28, /**< Period 2^28 */
    WDT_PERIOD_2_27 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW27, /**< Period 2^27 */
    WDT_PERIOD_2_26 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW26, /**< Period 2^26 */
    WDT_PERIOD_2_25 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW25, /**< Period 2^25 */
    WDT_PERIOD_2_24 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW24, /**< Period 2^24 */
    WDT_PERIOD_2_23 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW23, /**< Period 2^23 */
    WDT_PERIOD_2_22 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW22, /**< Period 2^22 */
    WDT_PERIOD_2_21 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW21, /**< Period 2^21 */
    WDT_PERIOD_2_20 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW20, /**< Period 2^20 */
    WDT_PERIOD_2_19 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW19, /**< Period 2^19 */
    WDT_PERIOD_2_18 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW18, /**< Period 2^18 */
    WDT_PERIOD_2_17 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW17, /**< Period 2^17 */
    WDT_PERIOD_2_16 = MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW16, /**< Period 2^16 */
} wdt_period_t;

/* **** Function Prototypes **** */

/**
 * @brief Initialize the Watchdog Timer
 * @param      wdt      Pointer to the watchdog registers
 * @param      sys_cfg  The system configuration object
 */
int WDT_Init(mxc_wdt_regs_t* wdt, sys_cfg_wdt_t sys_cfg);
/**
 * @brief       Set the period of the watchdog interrupt.
 * @param       wdt     Pointer to watchdog registers.
 * @param       period  Enumeration of the desired watchdog period.
 */
void WDT_SetIntPeriod(mxc_wdt_regs_t* wdt, wdt_period_t period);

/**
 * @brief       Set the period of the watchdog reset.
 * @param       wdt     Pointer to watchdog registers.
 * @param       period  Enumeration of the desired watchdog period.
 */
void WDT_SetResetPeriod(mxc_wdt_regs_t* wdt, wdt_period_t period);

/**
 * @brief       Enable the watchdog timer.
 * @param       wdt     Pointer to watchdog registers.
 * @param       enable  1 to enable the timer, 0 to disable.
 */
void WDT_Enable(mxc_wdt_regs_t* wdt, int enable);

/**
 * @brief       Enable the watchdog interrupt.
 * @param       wdt     Pointer to watchdog registers.
 * @param       enable  1 to enable the interrupt, 0 to disable.
 */
void WDT_EnableInt(mxc_wdt_regs_t* wdt, int enable);

/**
 * @brief       Enable the watchdog reset.
 * @param       wdt     Pointer to watchdog registers.
 * @param       enable  1 to enable the reset, 0 to disable.
 */
void WDT_EnableReset(mxc_wdt_regs_t* wdt, int enable);

/**
 * @brief       Reset the watchdog timer.
 * @param       wdt     Pointer to watchdog registers.
 */
void WDT_ResetTimer(mxc_wdt_regs_t* wdt);

/**
 * @brief       Get the status of the reset flag.
 * @param       wdt     Pointer to watchdog registers.
 * @returns     1 if the previous reset was caused by the watchdog, 0 otherwise.
 */
int WDT_GetResetFlag(mxc_wdt_regs_t* wdt);

/**
 * @brief       Clears the reset flag.
 * @param       wdt     Pointer to watchdog registers.
 */
void WDT_ClearResetFlag(mxc_wdt_regs_t* wdt);

/**
 * @brief     Get the status of the interrupt flag.
 * @param       wdt     Pointer to watchdog registers.
 * @returns   1 if the interrupt is pending, 0 otherwise.
 */
int WDT_GetIntFlag(mxc_wdt_regs_t* wdt);

/**
 * @brief       Clears the interrupt flag.
 * @param       wdt     Pointer to watchdog registers.
 */
void WDT_ClearIntFlag(mxc_wdt_regs_t* wdt);

/**@} end of group wdt */

#ifdef __cplusplus
}
#endif

#endif /* _WDT_H_ */
