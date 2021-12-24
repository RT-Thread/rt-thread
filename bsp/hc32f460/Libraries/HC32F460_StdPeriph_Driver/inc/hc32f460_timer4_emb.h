/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_timer4_emb.h
 **
 ** A detailed description is available at
 ** @link Timer4EmbGroup Timer4EMB description @endlink
 **
 **   - 2018-11-02 CDT First version for Device Driver Library of Timer4EMB.
 **
 ******************************************************************************/
#ifndef __HC32F460_TIMER4_EMB_H__
#define __HC32F460_TIMER4_EMB_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_TIMER4_EMB_ENABLE == DDL_ON)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup Timer4EmbGroup Timer4 Emergency Brake(Timer4EMB)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/**
 *******************************************************************************
 ** \brief Timer4 EMB hold function selection enumeration
 **
 ******************************************************************************/
typedef enum en_timer4_emb_hold_mode
{
    EmbChangePwm = 0u,                      ///< Don't hold PWM output when EMB signal occurs
    EmbHoldPwm   = 1u,                      ///< Hold PWM output when EMB signal occurs
} en_timer4_emb_hold_mode_t;

/**
 *******************************************************************************
 ** \brief Timer4 EMB state selection enumeration
 **
 ******************************************************************************/
typedef enum en_timer4_emb_state
{
    EmbTrigPwmOutputNormal    = 0u,         ///< PWM output signal normally.
    EmbTrigPwmOutputHiz       = 1u,         ///< PWM output Hiz signal.
    EmbTrigPwmOutputLowLevel  = 2u,         ///< PWM output low level signal.
    EmbTrigPwmOutputHighLevel = 3u,         ///< PWM output high level signal.
} en_timer4_emb_state_t;

/**
 *******************************************************************************
 ** \brief Timer4 EMB configure
 **
 ******************************************************************************/
typedef struct stc_timer4_emb_init
{
    en_timer4_emb_state_t     enEmbState;   ///< Timer4 EMB state selection and this parameter can be a value of @ref en_timer4_emb_state_t

    en_timer4_emb_hold_mode_t enPwmHold;    ///< Timer4 EMB hold function selection and this parameter can be a value of @ref en_timer4_emb_hold_mode_t
} stc_timer4_emb_init_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
en_result_t TIMER4_EMB_Init(M4_TMR4_TypeDef *TMR4x,
                                const stc_timer4_emb_init_t *pstcInitCfg);
en_result_t TIMER4_EMB_DeInit(M4_TMR4_TypeDef *TMR4x);
en_result_t TIMER4_EMB_SetHoldMode(M4_TMR4_TypeDef *TMR4x,
                                en_timer4_emb_hold_mode_t enHoldMode);
en_timer4_emb_hold_mode_t TIMER4_EMB_GetHoldMode(M4_TMR4_TypeDef *TMR4x);
en_result_t TIMER4_EMB_SetState(const M4_TMR4_TypeDef *TMR4x,
                                en_timer4_emb_state_t enEmbState);
en_timer4_emb_state_t TIMER4_EMB_GetState(const M4_TMR4_TypeDef *TMR4x);

//@} // Timer4EmbGroup

#ifdef __cplusplus
}
#endif

#endif /* DDL_TIMER4_EMB_ENABLE */

#endif /* __HC32F460_TIMER4_EMB_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
