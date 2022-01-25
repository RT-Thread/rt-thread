/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_emb.h
 **
 ** A detailed description is available at
 ** @link EMBGroup EMB description @endlink
 **
 **   - 2018-11-24  CDT  First version for Device Driver Library of EMB.
 **
 ******************************************************************************/
#ifndef __HC32F460_EMB_H__
#define __HC32F460_EMB_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_EMB_ENABLE == DDL_ON)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/**
 *******************************************************************************
 ** \defgroup EMBGroup Emergency Brake(EMB)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/**
 *******************************************************************************
 ** \brief EMB status enumeration
 ******************************************************************************/
typedef enum en_emb_status
{
    EMBFlagPortIn  = 0u,      ///< EMB port in brake flag
    EMBFlagPWMSame = 1u,      ///< EMB PWM same brake flag
    EMBFlagCmp     = 2u,      ///< EMB CMP brake flag
    EMBFlagOSCFail  = 3u,     ///< EMB oscillator fail brake flag
    EMBPortInState = 4u,      ///< EMB port in state
    EMBPWMState    = 5u,      ///< EMB PWM same state
} en_emb_status_t;

/**
 *******************************************************************************
 ** \brief EMB status clear(recover) enumeration
 ******************************************************************************/
typedef enum en_emb_status_clr
{
    EMBPortInFlagClr  = 0u,   ///< EMB port in brake flag clear
    EMBPWMSameFlagCLr = 1u,   ///< EMB PWM same brake flag clear
    EMBCmpFlagClr     = 2u,   ///< EMB CMP brake flag clear
    EMBOSCFailFlagCLr  = 3u,  ///< EMB oscillator fail brake flag clear
} en_emb_status_clr_t;

/**
 *******************************************************************************
 ** \brief EMB irq enumeration
 ******************************************************************************/
typedef enum en_emb_irq_type
{
    PORTBrkIrq   = 0u,        ///< EMB port brake interrupt
    PWMSmBrkIrq  = 1u,        ///< EMB PWM same brake interrupt
    CMPBrkIrq    = 2u,        ///< EMB CMP brake interrupt
    OSCFailBrkIrq = 3u,        ///< EMB oscillator fail brake interrupt
} en_emb_irq_type_t;

/**
 *******************************************************************************
 ** \brief EMB port in filter enumeration
 ******************************************************************************/
typedef enum en_emb_port_filter
{
    EMBPortFltDiv0    = 0u,   ///< EMB port in filter with PCLK clock
    EMBPortFltDiv8    = 1u,   ///< EMB port in filter with PCLK/8 clock
    EMBPortFltDiv32   = 2u,   ///< EMB port in filter with PCLK/32 clock
    EMBPortFltDiv128  = 3u,   ///< EMB port in filter with PCLK/128 clock
} en_emb_port_filter_t;

/**
 *******************************************************************************
 ** \brief EMB CR0 for timer6 config
 ** \note
 ******************************************************************************/
typedef struct stc_emb_ctrl_timer6
{
    bool                  bEnPortBrake;             ///< Enable port brake
    bool                  bEnCmp1Brake;             ///< Enable CMP1 brake
    bool                  bEnCmp2Brake;             ///< Enable CMP2 brake
    bool                  bEnCmp3Brake;             ///< Enable CMP3 brake
    bool                  bEnOSCFailBrake;          ///< Enable OSC fail brake
    bool                  bEnTimer61PWMSBrake;      ///< Enable tiemr61 PWM same brake
    bool                  bEnTimer62PWMSBrake;      ///< Enable tiemr62 PWM same brake
    bool                  bEnTimer63PWMSBrake;      ///< Enable tiemr63 PWM same brake
    en_emb_port_filter_t  enPortInFltClkSel;        ///< Port in filter clock selection
    bool                  bEnPorInFlt;              ///< Enable port in filter
    bool                  bEnPortInLevelSel_Low;    ///< Poit input active level 1: LowLevel 0:HighLevel
}stc_emb_ctrl_timer6_t;

/**
 *******************************************************************************
 ** \brief EMB CR1~3 for timer4x config
 ** \note
 ******************************************************************************/
typedef struct stc_emb_ctrl_timer4
{
    bool                  bEnPortBrake;             ///< Enable port brake
    bool                  bEnCmp1Brake;             ///< Enable CMP1 brake
    bool                  bEnCmp2Brake;             ///< Enable CMP2 brake
    bool                  bEnCmp3Brake;             ///< Enable CMP3 brake
    bool                  bEnOSCFailBrake;          ///< Enable OS fail brake
    bool                  bEnTimer4xWHLSammeBrake;  ///< Enable tiemr4x PWM WH WL same brake
    bool                  bEnTimer4xVHLSammeBrake;  ///< Enable tiemr4x PWM VH VL same brake
    bool                  bEnTimer4xUHLSammeBrake;  ///< Enable tiemr4x PWM UH UL same brake
    en_emb_port_filter_t  enPortInFltClkSel;        ///< Port in filter clock selection
    bool                  bEnPorInFlt;              ///< Enable port in filter
    bool                  bEnPortInLevelSel_Low;    ///< Poit input active level 1: LowLevel 0:HighLevel
}stc_emb_ctrl_timer4_t;


/**
 *******************************************************************************
 ** \brief EMB PWM level detect timer6 config
 ** \note
 ******************************************************************************/
typedef struct stc_emb_pwm_level_timer6
{
    bool      bEnTimer61HighLevelDect;             ///< Enable tiemr61 active detected level 1:HighLevel 0:LowLevel
    bool      bEnTimer62HighLevelDect;             ///< Enable tiemr62 active detected level 1:HighLevel 0:LowLevel
    bool      bEnTimer63HighLevelDect;             ///< Enable tiemr63 active detected level 1:HighLevel 0:LowLevel
}stc_emb_pwm_level_timer6_t;

/**
 *******************************************************************************
 ** \brief EMB PWM level detect timer4x config
 ** \note
 ******************************************************************************/
typedef struct stc_emb_pwm_level_timer4
{
    bool      bEnUHLPhaseHighLevelDect;            ///< Enable tiemr4x UH UL active detected level 1:HighLevel 0:LowLevel
    bool      bEnVHLPhaseHighLevelDect;            ///< Enable tiemr4x VH VL active detected level 1:HighLevel 0:LowLevel
    bool      bEnWHLphaseHighLevelDect;            ///< Enable tiemr4x WH WL active detected level 1:HighLevel 0:LowLevel
}stc_emb_pwm_level_timer4_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/* IRQ config */
en_result_t EMB_ConfigIrq(M4_EMB_TypeDef *EMBx,
                                en_emb_irq_type_t enEMBIrq,
                                bool bEn);
/* Get status(flag) */
bool EMB_GetStatus(M4_EMB_TypeDef *EMBx, en_emb_status_t enStatus);
/*  Status(flag) clear (recover) */
en_result_t EMB_ClrStatus(M4_EMB_TypeDef *EMBx,
                                en_emb_status_clr_t enStatusClr);
/*  Control Register(CTL) config for timer6 */
en_result_t EMB_Config_CR_Timer6(const stc_emb_ctrl_timer6_t* pstcEMBConfigCR);
/*  Control Register(CTL) config for timer4 */
en_result_t EMB_Config_CR_Timer4(M4_EMB_TypeDef *EMBx,
                                const stc_emb_ctrl_timer4_t* pstcEMBConfigCR);
/*  PWM level detect (short detection) selection config for timer6 */
en_result_t EMB_PWMLv_Timer6(const stc_emb_pwm_level_timer6_t* pstcEMBPWMlv);
/*  PWM level detect (short detection) selection config for timer4 */
en_result_t EMB_PWMLv_Timer4(M4_EMB_TypeDef *EMBx,
                                const stc_emb_pwm_level_timer4_t* pstcEMBPWMlv);
/*  Software brake */
en_result_t EMB_SwBrake(M4_EMB_TypeDef *EMBx, bool bEn);

//@} // EMBGroup

#ifdef __cplusplus
}
#endif

#endif /* DDL_EMB_ENABLE */

#endif /* __HC32F460_EMB_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
