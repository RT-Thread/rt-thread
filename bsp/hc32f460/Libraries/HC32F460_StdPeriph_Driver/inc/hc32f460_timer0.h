/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_timer0.h
 **
 ** A detailed description is available at
 ** @link Timer0Group description @endlink
 **
 **   - 2018-10-11  CDT  First version for Device Driver Library of TIMER0.
 **
 ******************************************************************************/

#ifndef __HC32F460_TIMER0_H__
#define __HC32F460_TIMER0_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/

#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_TIMER0_ENABLE == DDL_ON)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup Timer0Group Timer0
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief Timer0 channel enumeration
 **
 ******************************************************************************/
typedef enum en_tim0_channel
{
    Tim0_ChannelA = 0x00u,
    Tim0_ChannelB = 0x01u
}en_tim0_channel_t;

/**
 *******************************************************************************
 ** \brief Timer0 Async Mode clock enumeration
 **
 ******************************************************************************/
typedef enum en_tim0_async_clock_src
{
    Tim0_LRC    = 0x00u,
    Tim0_XTAL32 = 0x01u
}en_tim0_async_clock_src_t;

/**
 *******************************************************************************
 ** \brief Timer0 Sync Mode clock enumeration
 **
 ******************************************************************************/
typedef enum en_tim0_sync_clock_src
{
    Tim0_Pclk1          = 0x00u,
    Tim0_InsideHardTrig = 0x01u
}en_tim0_sync_clock_src_t;

/**
 *******************************************************************************
 ** \brief Timer0 counter mode enumeration
 **
 ******************************************************************************/
typedef enum en_tim0_counter_mode
{
    Tim0_Sync  = 0x00u,
    Tim0_Async = 0x01u
}en_tim0_counter_mode_t;

/**
 *******************************************************************************
 ** \brief Timer0 trigger event mode enumeration
 **
 ******************************************************************************/
typedef enum en_tim0_function
{
    Tim0_OutputCapare = 0x00u,
    Tim0_InputCaptrue = 0x01u
}en_tim0_function_t;

/**
 *******************************************************************************
 ** \brief Timer0 clock division enumeration
 **
 ******************************************************************************/
typedef enum en_tim0_clock_div
{
    Tim0_ClkDiv0 = 0u,
    Tim0_ClkDiv2,
    Tim0_ClkDiv4,
    Tim0_ClkDiv8,
    Tim0_ClkDiv16,
    Tim0_ClkDiv32,
    Tim0_ClkDiv64,
    Tim0_ClkDiv128,
    Tim0_ClkDiv256,
    Tim0_ClkDiv512,
    Tim0_ClkDiv1024
}en_tim0_clock_div_t;

/**
 *******************************************************************************
 ** \brief Timer0 common trigger source select enumeration
 **
 ******************************************************************************/
typedef enum en_tim0_com_trigger
{
    Tim0ComTrigger_1   = 1u,                 ///< Select common trigger 1.
    Tim0ComTrigger_2   = 2u,                 ///< Select common trigger 2.
    Tim0ComTrigger_1_2 = 3u,                 ///< Select common trigger 1 and 2.
} en_tim0_com_trigger_t;

/**
 *******************************************************************************
 ** \brief Timer0 trigger function init structrue definition
 **
 ******************************************************************************/
typedef struct stc_tim0_trigger_init
{
    en_tim0_function_t  Tim0_OCMode;      ///<specifies the TIM mode value of @ref en_tim0_function_t
    en_event_src_t      Tim0_SelTrigSrc;  ///<specifies the TIM Clk Src, and this parameter can be a value of @ref en_event_src_t
    bool                Tim0_InTrigEnable;///<specifies the TIM enable trigger
    bool                Tim0_InTrigClear; ///<specifies the TIM enable trigger clear
    bool                Tim0_InTrigStop;  ///<specifies the TIM enable trigger stop
    bool                Tim0_InTrigStart; ///<specifies the TIM enable trigger start
}stc_tim0_trigger_init_t;


/**
 *******************************************************************************
 ** \brief Timer0 base counter function init structrue definition
 **
 ******************************************************************************/
typedef struct stc_tim0_base_init
{
    en_tim0_clock_div_t       Tim0_ClockDivision;   ///<specifies the TIM clock division, and this parameter can be a value of @ref en_tim0_clock_div_t*/
    en_tim0_sync_clock_src_t  Tim0_SyncClockSource; ///<specifies the TIM sync clock source, and this parameter can be a value of @ref en_tim0_sync_clock_src_t*/
    en_tim0_async_clock_src_t Tim0_AsyncClockSource;///<specifies the TIM async clock source, and this parameter can be a value of @ref en_tim0_async_clock_src_t*/
    en_tim0_counter_mode_t    Tim0_CounterMode;     ///<specifies the TIM counter mode, and this parameter can be a value of @ref en_tim0_counter_mode_t*/
    uint16_t                  Tim0_CmpValue;        ///<specifies the TIM counter value This value can be set 0-0xFFFF
}stc_tim0_base_init_t;


/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/


/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
en_flag_status_t TIMER0_GetFlag(M4_TMR0_TypeDef* pstcTim0Reg, en_tim0_channel_t enCh);
en_result_t TIMER0_ClearFlag(M4_TMR0_TypeDef* pstcTim0Reg, en_tim0_channel_t enCh);
en_result_t TIMER0_Cmd(M4_TMR0_TypeDef* pstcTim0Reg, en_tim0_channel_t enCh,
                en_functional_state_t enCmd);
en_result_t TIMER0_SetFunc(M4_TMR0_TypeDef* pstcTim0Reg, en_tim0_channel_t enCh,
                       en_tim0_function_t enFunc);
en_result_t TIMER0_IntCmd(M4_TMR0_TypeDef* pstcTim0Reg, en_tim0_channel_t enCh,
                       en_functional_state_t enCmd);
uint16_t TIMER0_GetCntReg(M4_TMR0_TypeDef* pstcTim0Reg,en_tim0_channel_t enCh);
en_result_t TIMER0_WriteCntReg(M4_TMR0_TypeDef* pstcTim0Reg,en_tim0_channel_t enCh,uint16_t u16Cnt);
uint16_t TIMER0_GetCmpReg(M4_TMR0_TypeDef* pstcTim0Reg,en_tim0_channel_t enCh);
en_result_t TIMER0_WriteCmpReg(M4_TMR0_TypeDef* pstcTim0Reg, en_tim0_channel_t enCh,uint16_t u16Cnt);
en_result_t TIMER0_BaseInit(M4_TMR0_TypeDef* pstcTim0Reg,en_tim0_channel_t enCh,
                       const stc_tim0_base_init_t* pstcBaseInit);
en_result_t TIMER0_DeInit(M4_TMR0_TypeDef* pstcTim0Reg,en_tim0_channel_t enCh);
en_result_t TIMER0_HardTriggerInit(M4_TMR0_TypeDef* pstcTim0Reg,en_tim0_channel_t enCh,
                                const stc_tim0_trigger_init_t* pStcInit);
void TIMER0_SetTriggerSrc(en_event_src_t enEvent);
void TIMER0_ComTriggerCmd(en_tim0_com_trigger_t enComTrigger, en_functional_state_t enState);

//@} // Timer0Group

#ifdef __cplusplus
}
#endif

#endif /* DDL_TIMER0_ENABLE */

#endif /* __HC32F460_TIMER0_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
