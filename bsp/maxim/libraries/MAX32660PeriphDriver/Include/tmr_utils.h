/**
 * @file       tmr_utils.h
 * @brief      Timer utility function declarations
 */
/* *****************************************************************************
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
 * $Date: 2018-10-17 14:16:30 -0500 (Wed, 17 Oct 2018) $
 * $Revision: 38560 $
 *
 **************************************************************************** */

/* Define to prevent redundant inclusion */
#ifndef _TMR_UTILS_H
#define _TMR_UTILS_H

/***** Includes *****/
#include "mxc_config.h"
#include "tmr_regs.h"
#include "mxc_sys.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup tmr
 * @defgroup tmr_utils Timer Utility Functions
 * @{
 */
 
/* **** Definitions **** */

/** @def Macro to convert the parameter \p s from seconds to micro-seconds. */
#define SEC(s)            (((unsigned long)s) * 1000000UL) 

/** @def Macro to convert the parameter \p ms from milli-seconds to micro-seconds. */
#define MSEC(ms)          (ms * 1000UL)

/** @def Macro to convert the parameter \p us to micro-seconds. */
#define USEC(us)          (us)

/* **** Globals **** */

/* **** Function Prototypes **** */

/**
 * @brief      Delays for the specified number of microseconds.
 * @param      tmr   Which Timer instance to use
 * @param      us    Number of microseconds to delay.
 * @param      sys_cfg  System configuration object, identical to TMR_Init()
 */
void TMR_Delay(mxc_tmr_regs_t *tmr, unsigned long us, const sys_cfg_tmr_t *sys_cfg);

/**
 * @brief      Start the timeout time for the specified number of microseconds.
 * @param      tmr     Which Timer instance to use
 * @param      us      Number of microseconds in the timeout.
 * @param      sys_cfg  System configuration object, identical to TMR_Init()
 */
void TMR_TO_Start(mxc_tmr_regs_t *tmr, unsigned long us, const sys_cfg_tmr_t *sys_cfg);

/**
 * @brief      Check if the timeout has occurred.
 * @param      tmr   Which Timer instance to use
 * @return     #E_NO_ERROR if the timeout has not occurred, #E_TIME_OUT if it has.
 */
int TMR_TO_Check(mxc_tmr_regs_t *tmr);

/**
 * @brief      Stops the timer for the timeout.
 * @param      tmr   Which Timer instance to use
 */
void TMR_TO_Stop(mxc_tmr_regs_t *tmr);

/**
 * @brief      Clears the timeout flag.
 * @param      tmr   Which Timer instance to use
 */
void TMR_TO_Clear(mxc_tmr_regs_t *tmr);

/**
 * @brief      Get the number of microseconds elapsed since TMR_TO_Start().
 * @param      tmr   Which Timer instance to use
 * @return     Number of microseconds since TMR_TO_Start().
 */
unsigned int TMR_TO_Elapsed(mxc_tmr_regs_t *tmr);

/**
 * @brief      Get the number of microseconds remaining in the timeout.
 * @param      tmr   Which Timer instance to use
 * @return     Number of microseconds until timeout.
 */
unsigned int TMR_TO_Remaining(mxc_tmr_regs_t *tmr);

/**
 * @brief      Start the stopwatch.
 * @note 	   This function does not handle overflows
 * @param      tmr   Which Timer to use
 * @param      sys_cfg  System configuration object, identical to TMR_Init()
 */
void TMR_SW_Start(mxc_tmr_regs_t *tmr, const sys_cfg_tmr_t *sys_cfg);

/**
 * @brief      Stop the stopwatch and return the number of microseconds that
 *             have elapsed.
 * @note 	   This function does not handle overflows
 * @param      tmr   Which Timer instance to use
 * @return     Number of microseconds since TMR_SW_Start().
 */
unsigned int TMR_SW_Stop(mxc_tmr_regs_t *tmr);
  
/**@} end of defgroup tmr_utils*/
#ifdef __cplusplus
}
#endif

#endif /* _TMR_UTILS_H */
