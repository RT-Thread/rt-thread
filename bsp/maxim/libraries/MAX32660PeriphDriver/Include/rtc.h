/**
 * @file
 * @brief   Real Time Clock (RTC) functions and prototypes.
 */

/* ****************************************************************************
 * Copyright (C) 2017 Maxim Integrated Products, Inc., All Rights Reserved.
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
 *
 * $Date: 2019-10-07 11:05:30 -0500 (Mon, 07 Oct 2019) $
 * $Revision: 47429 $
 *************************************************************************** */

/* Define to prevent redundant inclusion */
#ifndef _RTC_H_
#define _RTC_H_

/* **** Includes **** */
#include <stdint.h>
#include "mxc_config.h"
#include "rtc_regs.h"
#include "mxc_sys.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup rtc RTC
 * @ingroup periphlibs
 * @{
 */

/* **** Definitions **** */

typedef enum {
    SQUARE_WAVE_DISABLED, /**< Sq. wave output disabled */
    SQUARE_WAVE_ENABLED,  /**< Sq. wave output enabled  */
} rtc_sqwave_en_t;

typedef enum {
    F_1HZ   = MXC_S_RTC_CTRL_FT_FREQ1HZ,     /**< 1Hz (Compensated)   */
    F_512HZ = MXC_S_RTC_CTRL_FT_FREQ512HZ,   /**< 512Hz (Compensated) */
    F_4KHZ  = MXC_S_RTC_CTRL_FT_FREQ4KHZ,    /**< 4Khz                */
    F_32KHZ = 32,                          /**< 32Khz               */
} rtc_freq_sel_t;

typedef enum {
    NOISE_IMMUNE_MODE        = MXC_S_RTC_CTRL_X32KMD_NOISEIMMUNEMODE,
    QUIET_MODE               = MXC_S_RTC_CTRL_X32KMD_QUIETMODE,
    QUIET_STOP_WARMUP_MODE   = MXC_S_RTC_CTRL_X32KMD_QUIETINSTOPWITHWARMUP,
    QUIET_STOP_NOWARMUP_MODE = MXC_S_RTC_CTRL_X32KMD_QUIETINSTOPNOWARMUP,
} rtc_osc_mode_t;

/**
 *@brief     Enables Time-of-Day's Alarm Interrupt
 *@param     rtc    pointer to the rtc register structure
 *@return    #E_SUCCESS=pass
 *@return    #E_BAD_STATE=fail
 *@return    #E_BUSY=Fail
 */
int RTC_EnableTimeofdayInterrupt(mxc_rtc_regs_t *rtc);

/**
 *@brief     Disable Time-of-Day's Alarm Interrupt
 *@param     rtc    pointer to the rtc register structure
 *@return    #E_SUCCESS=pass
 *@return    #E_BAD_STATE=fail
 *@return    #E_BUSY=Fail
 */
int RTC_DisableTimeofdayInterrupt(mxc_rtc_regs_t *rtc);

/**
 *@brief     Enables Sub-Second's Alarm Interrupt
 *@param     rtc    pointer to the rtc register structure
 *@return    #E_SUCCESS=pass
 *@return    #E_BAD_STATE=fail
 *@return    #E_BUSY=Fail
 */
int RTC_EnableSubsecondInterrupt(mxc_rtc_regs_t *rtc);

/**
 *@brief     Disable Sub-Second's Alarm Interrupt
 *@param     rtc    pointer to the rtc register structure
 *@return    #E_SUCCESS=pass
 *@return    #E_BAD_STATE=fail
 *@return    #E_BUSY=Fail
 */
int RTC_DisableSubsecondInterrupt(mxc_rtc_regs_t *rtc);

/**
 *@brief     Set Time-of-Day alarm value and enable Interrupt
 *@param     rtc    pointer to the rtc register structure
 *@param     ras    20-bit value 0-0xFFFFF
 *@return    #E_SUCCESS=pass
 *@return    #E_BAD_STATE=fail
 *@return    #E_BUSY=Fail
 */
int RTC_SetTimeofdayAlarm(mxc_rtc_regs_t *rtc, uint32_t ras);

/**
 *@brief     Set Sub-Second alarm value and enable interrupt,
 *@brief     this is to be called after the init_rtc() function
 *@param     rtc    pointer to the rtc register structure
 *@param     rssa   32-bit value 0-0xFFFFFFFF
 *@return    #E_SUCCESS=pass
 *@return    #E_BAD_STATE=fail
 *@return    #E_BUSY=Fail
 */
int RTC_SetSubsecondAlarm(mxc_rtc_regs_t *rtc, uint32_t rssa);

/**
 *@brief     Enable/Start the Real Time Clock
 *@param     rtc    pointer to the rtc register structure
 *@return    #E_SUCCESS=Pass
 *@return    #E_BUSY=Fail
 */
int RTC_EnableRTCE(mxc_rtc_regs_t *rtc);

/**
 *@brief     Disable/Stop the Real Time Clock
 *@param     rtc    pointer to the rtc register structure
 *@return    #E_SUCCESS=Pass
 *@return    #E_BUSY=Fail
 */
int RTC_DisableRTCE(mxc_rtc_regs_t *rtc);

/**
 * @brief Initialize the sec and ssec registers and enable RTC
 * @param      rtc pointer to the rtc register structure
 * @param      sec set the RTC Sec counter (32-bit)
 * @param      ssec set the RTC Sub-second counter (8-bit)
 * @param      sys_cfg The system configuration
 * @return #E_SUCCESS=pass
 * @return #E_BAD_STATE=fail
 */
int RTC_Init(mxc_rtc_regs_t *rtc, uint32_t sec, uint8_t ssec, sys_cfg_rtc_t *sys_cfg);

/**
 * @brief Allow generation of Square Wave on the SQW pin
 * @param      rtc pointer to the rtc register structure
 * @param      sqe Enable/Disable square wave output
 * @param      ft Frequency output selection
 * @param      x32kmd 32KHz Oscillator mode
 * @param      sys_cfg The system configuration
 * @return #E_SUCCESS=Pass
 * @return #E_BUSY=Fail
 */
int RTC_SquareWave(mxc_rtc_regs_t *rtc, rtc_sqwave_en_t sqe, rtc_freq_sel_t ft,
                   rtc_osc_mode_t x32kmd, const sys_cfg_rtc_t* sys_cfg);

/**
 *@brief     Set Trim register value
 *@param     rtc    pointer to the rtc register structure
 *@param     trm    set the RTC Trim (8-bit, +/- 127)
 *@return    #E_SUCCESS=Pass
 *@return    #E_BUSY=Fail
 */
int RTC_Trim(mxc_rtc_regs_t *rtc, int8_t trm);

/**
 *@brief     Check if BUSY bit is 0.
 *@return    #E_SUCCESS=Pass
 *@return    #E_BUSY=Fail
 */
int RTC_CheckBusy(void);

/**
 *@brief     Gets Interrupt flags.
 *@return    Interrupts flags that have not been cleared
 */
int RTC_GetFlags(void);

/**
 *@brief     Clear Interrupt flag.
 *@param     flags the flags that need to be cleared
 */
int RTC_ClearFlags(int flags);

/**
 *@brief     Get SubSecond
 *@return    Returns subsecond value
 */
int RTC_GetSubSecond(void);

/**
 * @brief Get Second
 * @return returns Second value
 */
int RTC_GetSecond(void);

/**
 * @brief Read seconds, then subseconds, and finally seconds.  If RTC ready flag ever gets cleared during this sequence,
   the RTC is in the middle of updating the counts and the user should come back later and try again.  If the first
   read of the seconds register doesn't match the next read, then a subsecond overflow condition has happened and
   another attempt to read the counts should be made.
 * @param      sec    variable that will be changed to hold second value
 * @param      subsec variable that will be changed to hold Subsecond value
 * @return    #E_NO_ERROR=Pass
 * @return    #E_BUSY=Fail
 */
int RTC_GetTime(uint32_t* sec, uint32_t* subsec);

/**
 *@brief    Check if RTC is already running
 */
int RTC_IsEnabled(void);

#ifdef __cplusplus
}
#endif
/**@} end of group rtc */

#endif /* _RTC_H_ */
