/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_timer4_pwm.h
 **
 ** A detailed description is available at
 ** @link Timer4PwmGroup Timer4PWM description @endlink
 **
 **   - 2018-11-02 CDT First version for Device Driver Library of Timer4PWM.
 **
 ******************************************************************************/
#ifndef __HC32F460_TIMER4_PWM_H__
#define __HC32F460_TIMER4_PWM_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_TIMER4_PWM_ENABLE == DDL_ON)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup Timer4PwmGroup Timer4 Pulse-Width Modulation(Timer4PWM)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 ** \brief Timer4 PWM channel enumeration
 **
 ******************************************************************************/
typedef enum en_timer4_pwm_ch
{
    Timer4PwmU = 0u,                    ///< Timer4 PWM couple channel: U
    Timer4PwmV = 1u,                    ///< Timer4 PWM couple channel: V
    Timer4PwmW = 2u,                    ///< Timer4 PWM couple channel: W
} en_timer4_pwm_ch_t;

/*******************************************************************************
 ** \brief Timer4 PWM operation mode enumeration
 **
 ******************************************************************************/
typedef enum en_timer4_pwm_mode
{
    PwmThroughMode         = 0u,        ///< through mode
    PwmDeadTimerMode       = 1u,        ///< Dead timer mode
    PwmDeadTimerFilterMode = 2u,        ///< Dead timer filter mode
} en_timer4_pwm_mode_t;

/*******************************************************************************
 ** \brief Timer4 PWM DMOD bit setting enumeration
 **
 ******************************************************************************/
typedef enum en_timer4_pwm_output_state
{
    PwmHPwmLHold        = 0u,           ///< Output PWML and PWMH signals without changing the level
    PwmHPwmLReverse     = 1u,           ///< Output both PWML and PWMH signals reversed
    PwmHReversePwmLHold = 2u,           ///< Output the PWMH signal reversed, outputs the PWML signal without changing the level.
    PwmHHoldPwmLReverse = 3u,           ///< Output the PWMH signal without changing the level, Outputs the PWML signal reversed.
} en_timer4_pwm_output_state_t;

/*******************************************************************************
 ** \brief Timer4 PWM count clock prescaler enumeration
 **
 ******************************************************************************/
typedef enum en_timer4_pwm_timer_clk_div
{
    PwmPlckDiv1   = 0u,                 ///< PWM timer clock prescaler: None
    PwmPlckDiv2   = 1u,                 ///< PWM timer clock prescaler: 1/2
    PwmPlckDiv4   = 2u,                 ///< PWM timer clock prescaler: 1/4
    PwmPlckDiv8   = 3u,                 ///< PWM timer clock prescaler: 1/8
    PwmPlckDiv16  = 4u,                 ///< PWM timer clock prescaler: 1/16
    PwmPlckDiv32  = 5u,                 ///< PWM timer clock prescaler: 1/32
    PwmPlckDiv64  = 6u,                 ///< PWM timer clock prescaler: 1/64
    PwmPlckDiv128 = 7u,                 ///< PWM timer clock prescaler: 1/128
} en_timer4_pwm_timer_clk_div_t;

/*******************************************************************************
 ** \brief Timer4 PWM initialization configuration
 **
 ******************************************************************************/
typedef struct stc_timer4_pwm_init
{
    en_timer4_pwm_mode_t          enMode;           ///< Select PWM mode and this parameter can be a value of @ref en_timer4_pwm_mode_t

    en_timer4_pwm_timer_clk_div_t enClkDiv;         ///< Clock division of PWM timer and this parameter can be a value of @ref en_timer4_pwm_timer_clk_div_t

    en_timer4_pwm_output_state_t  enOutputState;    ///< Polarity for PWMH and PWML signal output and this parameter can be a value of @ref en_timer4_pwm_output_state_t

    en_functional_state_t         enRtIntMaskCmd;   ///< Enable: Enable mask reload-timer interrupt, FALSE: don't mask reload-timer interrupt
} stc_timer4_pwm_init_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
en_result_t TIMER4_PWM_Init(M4_TMR4_TypeDef *TMR4x,
                                en_timer4_pwm_ch_t enCh,
                                const stc_timer4_pwm_init_t *pstcInitCfg);
en_result_t TIMER4_PWM_DeInit(M4_TMR4_TypeDef *TMR4x,
                                en_timer4_pwm_ch_t enCh);
en_result_t TIMER4_PWM_StartTimer(M4_TMR4_TypeDef *TMR4x,
                                en_timer4_pwm_ch_t enCh);
en_result_t TIMER4_PWM_StopTimer(M4_TMR4_TypeDef *TMR4x,
                                en_timer4_pwm_ch_t enCh);
en_flag_status_t TIMER4_PWM_GetIrqFlag(M4_TMR4_TypeDef *TMR4x,
                                en_timer4_pwm_ch_t enCh);
en_result_t TIMER4_PWM_ClearIrqFlag(M4_TMR4_TypeDef *TMR4x,
                                en_timer4_pwm_ch_t enCh);
en_result_t TIMER4_PWM_WriteDeadRegionValue(M4_TMR4_TypeDef *TMR4x,
                                en_timer4_pwm_ch_t enCh,
                                uint16_t u16PDAR,
                                uint16_t u16PDBR);
en_result_t TIMER4_PWM_ReadDeadRegionValue(M4_TMR4_TypeDef *TMR4x,
                                en_timer4_pwm_ch_t enCh,
                                uint16_t* u16PDAR,
                                uint16_t* u16PDBR);
en_result_t TIMER4_PWM_SetFilterCountValue(M4_TMR4_TypeDef *TMR4x,
                                en_timer4_pwm_ch_t enCh,
                                uint16_t u16Count);

//@} // Timer4PwmGroup

#ifdef __cplusplus
}
#endif

#endif /* DDL_TIMER4_PWM_ENABLE */

#endif /* __HC32F460_TIMER4_PWM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
