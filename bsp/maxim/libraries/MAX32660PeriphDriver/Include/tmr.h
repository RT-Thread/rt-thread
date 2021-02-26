/**
 * @file    tmr.h
 * @brief   Timer (TMR) function prototypes and data types.
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
 * $Date: 2019-09-11 14:32:22 -0500 (Wed, 11 Sep 2019) $
 * $Revision: 46047 $
 *
 *************************************************************************** */

/* Define to prevent redundant inclusion */
#ifndef _TMR_H_
#define _TMR_H_

/* **** Includes **** */
#include "mxc_config.h"
#include "tmr_regs.h"
#include "mxc_sys.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup tmr Timer (TMR)
 * @ingroup periphlibs
 * @{
 */

/**
 * @brief Timer prescaler values
 */
typedef enum {
    TMR_PRES_1      = MXC_S_TMR_CN_PRES_DIV1,           /// Divide input clock by 1
    TMR_PRES_2      = MXC_S_TMR_CN_PRES_DIV2,           /// Divide input clock by 2
    TMR_PRES_4      = MXC_S_TMR_CN_PRES_DIV4,           /// Divide input clock by 4
    TMR_PRES_8      = MXC_S_TMR_CN_PRES_DIV8,           /// Divide input clock by 8
    TMR_PRES_16     = MXC_S_TMR_CN_PRES_DIV16,          /// Divide input clock by 16
    TMR_PRES_32     = MXC_S_TMR_CN_PRES_DIV32,          /// Divide input clock by 32
    TMR_PRES_64     = MXC_S_TMR_CN_PRES_DIV64,          /// Divide input clock by 64
    TMR_PRES_128    = MXC_S_TMR_CN_PRES_DIV128,         /// Divide input clock by 128
    TMR_PRES_256    = MXC_F_TMR_CN_PRES3 | MXC_S_TMR_CN_PRES_DIV1,  /// Divide input clock by 256
    TMR_PRES_512    = MXC_F_TMR_CN_PRES3 | MXC_S_TMR_CN_PRES_DIV2,  /// Divide input clock by 512
    TMR_PRES_1024   = MXC_F_TMR_CN_PRES3 | MXC_S_TMR_CN_PRES_DIV4,  /// Divide input clock by 1024
    TMR_PRES_2048   = MXC_F_TMR_CN_PRES3 | MXC_S_TMR_CN_PRES_DIV8,  /// Divide input clock by 2048
    TMR_PRES_4096   = MXC_F_TMR_CN_PRES3 | MXC_S_TMR_CN_PRES_DIV16  /// Divide input clock by 4096
} tmr_pres_t;

/**
 * @brief Timer modes
 */
typedef enum {
    TMR_MODE_ONESHOT          = MXC_V_TMR_CN_TMODE_ONESHOT,       /// Timer Mode ONESHOT
    TMR_MODE_CONTINUOUS       = MXC_V_TMR_CN_TMODE_CONTINUOUS,    /// Timer Mode CONTINUOUS
    TMR_MODE_COUNTER          = MXC_V_TMR_CN_TMODE_COUNTER,       /// Timer Mode COUNTER
    TMR_MODE_PWM              = MXC_V_TMR_CN_TMODE_PWM,           /// Timer Mode PWM
    TMR_MODE_CAPTURE          = MXC_V_TMR_CN_TMODE_CAPTURE,       /// Timer Mode CAPTURE
    TMR_MODE_COMPARE          = MXC_V_TMR_CN_TMODE_COMPARE,       /// Timer Mode COMPARE
    TMR_MODE_GATED            = MXC_V_TMR_CN_TMODE_GATED,         /// Timer Mode GATED
    TMR_MODE_CAPTURE_COMPARE  = MXC_V_TMR_CN_TMODE_CAPTURECOMPARE /// Timer Mode CAPTURECOMPARE
} tmr_mode_t;

/**
 * @brief Timer units of time enumeration
 */
typedef enum {
    TMR_UNIT_NANOSEC = 0,       /**< Nanosecond Unit Indicator. */
    TMR_UNIT_MICROSEC,          /**< Microsecond Unit Indicator. */
    TMR_UNIT_MILLISEC,          /**< Millisecond Unit Indicator. */
    TMR_UNIT_SEC,               /**< Second Unit Indicator. */
} tmr_unit_t;

/**
 * @brief Timer Configuration
 */
typedef struct {
    tmr_mode_t mode;    /// Desired timer mode
    uint32_t cmp_cnt;   /// Compare register value in timer ticks
    unsigned pol;       /// Polarity (0 or 1)
} tmr_cfg_t;

/**
 * @brief Timer PWM Configuration
 */
typedef struct {
    unsigned pol;       /// PWM polarity (0 or 1)
    uint32_t per_cnt;   /// PWM period in timer ticks
    uint32_t duty_cnt;  /// PWM duty in timer ticks
} tmr_pwm_cfg_t;

/* **** Definitions **** */

/* **** Function Prototypes **** */

/**
 * @brief      Initialize timer module clock.
 * @param      tmr        Pointer to timer module to initialize.
 * @param      pres       Prescaler value.
 * @param      sys_cfg    System configuration object
 * @return     #E_NO_ERROR if successful, error code otherwise.
 */
int TMR_Init(mxc_tmr_regs_t *tmr, tmr_pres_t pres, const sys_cfg_tmr_t* sys_cfg);

/**
 * @brief      Shutdown timer module clock.
 * @param      tmr  Pointer to timer module to initialize.
 * @return     #E_NO_ERROR if successful, error code otherwise.
 */
int TMR_Shutdown(mxc_tmr_regs_t *tmr);

/**
 * @brief      Enable the timer.
 * @param      tmr  Pointer to timer module to initialize.
 */
void TMR_Enable(mxc_tmr_regs_t* tmr);

/**
 * @brief      Disable the timer.
 * @param      tmr  Pointer to timer module to initialize.
 */
void TMR_Disable(mxc_tmr_regs_t* tmr);

/**
 * @brief      Configure the timer.
 * @param      tmr  Pointer to timer module to initialize.
 * @param      cfg  Pointer to timer configuration struct.
 * @return     #E_NO_ERROR if successful.
 */
int TMR_Config(mxc_tmr_regs_t *tmr, const tmr_cfg_t *cfg);

/**
 * @brief   Configure the timer for PWM operation.
 * @param   tmr     Pointer to timer module to initialize.
 * @param   cfg     Pointer to timer PWM configuration struct.
 * @note    Can cause a glitch if the Timer is currently running.
 * @return  #E_BAD_PARAM if duty_cnt > per_cnt.
 */
int TMR_PWMConfig(mxc_tmr_regs_t *tmr, const tmr_pwm_cfg_t *cfg);

/**
 * @brief   Set the timer duty cycle.
 * @param   tmr     Pointer to timer module to initialize
 * @param   duty    New duty cycle count
 * @note    Will block until safe to change the duty count.
 * @return  #E_BAD_PARAM if duty_cnt > per_cnt.
 */
int TMR_PWMSetDuty(mxc_tmr_regs_t *tmr, uint32_t duty);

/**
 * @brief   Set the timer period.
 * @param   tmr     Pointer to timer module to initialize.
 * @param   per     New period count.
 * @note    Will block until safe to change the period count.
 * @return  #E_BAD_PARAM if duty_cnt > per_cnt.
 */
int TMR_PWMSetPeriod(mxc_tmr_regs_t* tmr, uint32_t per);

/**
 * @brief   Get the timer compare count.
 * @param   tmr     Pointer to timer module to initialize.
 * @return  Returns the current compare count.
 */
uint32_t TMR_GetCompare(mxc_tmr_regs_t* tmr);

/**
 * @brief   Get the timer capture count.
 * @param   tmr     Pointer to timer module to initialize.
 * @return  Returns the most recent capture count.
 */
uint32_t TMR_GetCapture(mxc_tmr_regs_t* tmr);

/**
 * @brief   Get the timer count.
 * @param   tmr     Pointer to timer module to initialize.
 * @return  Returns the current count.
 */
uint32_t TMR_GetCount(mxc_tmr_regs_t* tmr);

/**
 * @brief   Clear the timer interrupt.
 * @param   tmr     Pointer to timer module to initialize.
 */
void TMR_IntClear(mxc_tmr_regs_t* tmr);

/**
 * @brief   Get the timer interrupt status.
 * @param   tmr     Pointer to timer module to initialize.
 * @return  Returns the interrupt status. 1 if interrupt has occurred.
 */
uint32_t TMR_IntStatus(mxc_tmr_regs_t* tmr);

/**
 * @brief   Set the timer compare count.
 * @param   tmr     Pointer to timer module to initialize.
 * @param   cmp_cnt New compare count.
 * @note    This function does not protect against output glitches in PWM mode.
 *          Use TMR_PWMSetPeriod when in PWM mode.
 */
void TMR_SetCompare(mxc_tmr_regs_t *tmr, uint32_t cmp_cnt);

/**
 * @brief   Set the timer count.
 * @param   tmr     Pointer to timer module to initialize.
 * @param   cnt     New count.
 */
void TMR_SetCount(mxc_tmr_regs_t *tmr, uint32_t cnt);

/**
 * @brief   Convert real time to timer ticks.
 * @param   tmr     Pointer to timer module to initialize.
 * @param   time    Number of units of time.
 * @param   units   Which units of time you want to convert.
 * @param   ticks   Pointer to store the number of ticks calculated.
 * @return  #E_NO_ERROR if successful, error code otherwise.
 */
int TMR_GetTicks(mxc_tmr_regs_t *tmr, uint32_t time, tmr_unit_t units, uint32_t *ticks);

/**
 * @brief   Convert timer ticks to real time.
 * @param   tmr     Pointer to timer module to initialize.
 * @param   ticks   Number of ticks.
 * @param   time    Pointer to store number of units of time.
 * @param   units   Pointer to store the units that time represents.
 * @return  #E_NO_ERROR if successful, error code otherwise.
 */
int TMR_GetTime(mxc_tmr_regs_t *tmr, uint32_t ticks, uint32_t *time, tmr_unit_t *units);

/**@} end of group tmr */

#ifdef __cplusplus
}
#endif

#endif /* _TMR_H_ */
