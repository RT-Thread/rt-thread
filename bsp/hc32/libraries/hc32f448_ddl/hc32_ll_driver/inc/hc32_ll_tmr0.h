/**
 *******************************************************************************
 * @file  hc32_ll_tmr0.h
 * @brief This file contains all the functions prototypes of the TMR0 driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_TMR0_H__
#define __HC32_LL_TMR0_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_TMR0
 * @{
 */

#if (LL_TMR0_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMR0_Global_Types TMR0 Global Types
 * @{
 */

/**
 * @brief TMR0 initialization structure definition
 * @note  The 'u32ClockDiv' is invalid when the value of 'u32ClockSrc' is "TMR0_CLK_SRC_SPEC_EVT".
 */
typedef struct {
    uint32_t u32ClockSrc;               /*!< Specifies the clock source of TMR0 channel.
                                             This parameter can be a value of @ref TMR0_Clock_Source */
    uint32_t u32ClockDiv;               /*!< Specifies the clock division of TMR0 channel.
                                             This parameter can be a value of @ref TMR0_Clock_Division */
    uint32_t u32Func;                   /*!< Specifies the function of TMR0 channel.
                                             This parameter can be a value of @ref TMR0_Function */
    uint16_t u16CompareValue;           /*!< Specifies the compare value of TMR0 channel.
                                             This parameter can be a value of half-word */
} stc_tmr0_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR0_Global_Macros TMR0 Global Macros
 * @{
 */

/**
 * @defgroup TMR0_Channel TMR0 Channel
 * @{
 */
#define TMR0_CH_A                       (0UL)
#define TMR0_CH_B                       (1UL)
/**
 * @}
 */

/**
 * @defgroup TMR0_Clock_Source TMR0 Clock Source
 * @note In asynchronous clock, continuous operation of the BCONR register requires waiting for 3 asynchronous clocks.
 * @{
 */
#define TMR0_CLK_SRC_INTERN_CLK         (0UL)                                       /*!< Internal clock (Synchronous clock)  */
#define TMR0_CLK_SRC_SPEC_EVT           (TMR0_BCONR_SYNCLKA)                        /*!< Specified event (Synchronous clock) */
#define TMR0_CLK_SRC_LRC                (TMR0_BCONR_SYNSA)                          /*!< LRC (Asynchronous clock)            */
#define TMR0_CLK_SRC_XTAL32             (TMR0_BCONR_ASYNCLKA | TMR0_BCONR_SYNSA)    /*!< XTAL32 (Asynchronous clock)         */
/**
 * @}
 */

/**
 * @defgroup TMR0_Clock_Division TMR0 Clock Division
 * @{
 */
#define TMR0_CLK_DIV1                   (0UL  << TMR0_BCONR_CKDIVA_POS)     /*!< CLK      */
#define TMR0_CLK_DIV2                   (1UL  << TMR0_BCONR_CKDIVA_POS)     /*!< CLK/2    */
#define TMR0_CLK_DIV4                   (2UL  << TMR0_BCONR_CKDIVA_POS)     /*!< CLK/4    */
#define TMR0_CLK_DIV8                   (3UL  << TMR0_BCONR_CKDIVA_POS)     /*!< CLK/8    */
#define TMR0_CLK_DIV16                  (4UL  << TMR0_BCONR_CKDIVA_POS)     /*!< CLK/16   */
#define TMR0_CLK_DIV32                  (5UL  << TMR0_BCONR_CKDIVA_POS)     /*!< CLK/32   */
#define TMR0_CLK_DIV64                  (6UL  << TMR0_BCONR_CKDIVA_POS)     /*!< CLK/64   */
#define TMR0_CLK_DIV128                 (7UL  << TMR0_BCONR_CKDIVA_POS)     /*!< CLK/128  */
#define TMR0_CLK_DIV256                 (8UL  << TMR0_BCONR_CKDIVA_POS)     /*!< CLK/256  */
#define TMR0_CLK_DIV512                 (9UL  << TMR0_BCONR_CKDIVA_POS)     /*!< CLK/512  */
#define TMR0_CLK_DIV1024                (10UL << TMR0_BCONR_CKDIVA_POS)     /*!< CLK/1024 */
/**
 * @}
 */

/**
 * @defgroup TMR0_Function TMR0 Function
 * @{
 */
#define TMR0_FUNC_CMP                   (0UL)                                   /*!< Output compare function */
#define TMR0_FUNC_CAPT                  (TMR0_BCONR_CAPMDA | TMR0_BCONR_HICPA)  /*!< Input capture function */
/**
 * @}
 */

/**
 * @defgroup TMR0_Interrupt TMR0 Interrupt
 * @{
 */
#define TMR0_INT_CMP_A                  (TMR0_BCONR_CMENA)
#define TMR0_INT_CMP_B                  (TMR0_BCONR_CMENB)
#define TMR0_INT_OVF_A                  (TMR0_BCONR_OVENA)
#define TMR0_INT_OVF_B                  (TMR0_BCONR_OVENB)
#define TMR0_INT_ALL                    (TMR0_INT_CMP_A | TMR0_INT_OVF_A | TMR0_INT_CMP_B | TMR0_INT_OVF_B)
/**
 * @}
 */

/**
 * @defgroup TMR0_FLAG TMR0 Flag
 * @{
 */
#define TMR0_FLAG_CMP_A                 (TMR0_STFLR_CMFA)
#define TMR0_FLAG_CMP_B                 (TMR0_STFLR_CMFB)
#define TMR0_FLAG_REPEAT_CAPT_A         (TMR0_STFLR_ICPA)
#define TMR0_FLAG_REPEAT_CAPT_B         (TMR0_STFLR_ICPB)
#define TMR0_FLAG_OVF_A                 (TMR0_STFLR_OVFA)
#define TMR0_FLAG_OVF_B                 (TMR0_STFLR_OVFB)
#define TMR0_FLAG_ALL                   (TMR0_FLAG_CMP_A | TMR0_FLAG_CMP_B | TMR0_FLAG_REPEAT_CAPT_A | \
                                         TMR0_FLAG_REPEAT_CAPT_B | TMR0_FLAG_OVF_A | TMR0_FLAG_OVF_B)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup TMR0_Global_Functions
 * @{
 */

/* Initialization functions */
void TMR0_DeInit(CM_TMR0_TypeDef *TMR0x);
int32_t TMR0_Init(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, const stc_tmr0_init_t *pstcTmr0Init);
int32_t TMR0_StructInit(stc_tmr0_init_t *pstcTmr0Init);
void TMR0_Start(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch);
void TMR0_Stop(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch);

/* Control configuration functions */
void TMR0_SetCountValue(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint16_t u16Value);
uint16_t TMR0_GetCountValue(const CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch);
void TMR0_SetCompareValue(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint16_t u16Value);
uint16_t TMR0_GetCompareValue(const CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch);
void TMR0_SetClockSrc(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint32_t u32Src);
void TMR0_SetClockDiv(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint32_t u32Div);
void TMR0_SetFunc(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint32_t u32Func);

/* Hardware trigger Functions */
void TMR0_HWCaptureCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, en_functional_state_t enNewState);
void TMR0_HWStartCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, en_functional_state_t enNewState);
void TMR0_HWStopCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, en_functional_state_t enNewState);
void TMR0_HWClearCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, en_functional_state_t enNewState);

/* Interrupt and flag management functions */
void TMR0_IntCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32IntType, en_functional_state_t enNewState);
en_flag_status_t TMR0_GetStatus(const CM_TMR0_TypeDef *TMR0x, uint32_t u32Flag);
void TMR0_ClearStatus(CM_TMR0_TypeDef *TMR0x, uint32_t u32Flag);

/**
 * @}
 */

#endif /* LL_TMR0_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_TMR0_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
