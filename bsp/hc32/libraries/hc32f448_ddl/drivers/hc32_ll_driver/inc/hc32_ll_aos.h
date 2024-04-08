/**
 *******************************************************************************
 * @file  hc32_ll_aos.h
 * @brief This file contains all the functions prototypes of the AOS driver
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
#ifndef __HC32_LL_AOS_H__
#define __HC32_LL_AOS_H__

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
 * @addtogroup LL_AOS
 * @{
 */

#if (LL_AOS_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup AOS_Global_Macros AOS Global Macros
 * @{
 */

/**
 * @defgroup AOS_Target_Select AOS Target Select
 * @{
 */
#define AOS_DCU1                (uint32_t)(&CM_AOS->DCU_TRGSEL1)
#define AOS_DCU2                (uint32_t)(&CM_AOS->DCU_TRGSEL2)
#define AOS_DCU3                (uint32_t)(&CM_AOS->DCU_TRGSEL3)
#define AOS_DCU4                (uint32_t)(&CM_AOS->DCU_TRGSEL4)
#define AOS_DMA1_0              (uint32_t)(&CM_AOS->DMA1_TRGSEL0)
#define AOS_DMA1_1              (uint32_t)(&CM_AOS->DMA1_TRGSEL1)
#define AOS_DMA1_2              (uint32_t)(&CM_AOS->DMA1_TRGSEL2)
#define AOS_DMA1_3              (uint32_t)(&CM_AOS->DMA1_TRGSEL3)
#define AOS_DMA1_4              (uint32_t)(&CM_AOS->DMA1_TRGSEL4)
#define AOS_DMA1_5              (uint32_t)(&CM_AOS->DMA1_TRGSEL5)
#define AOS_DMA2_0              (uint32_t)(&CM_AOS->DMA2_TRGSEL0)
#define AOS_DMA2_1              (uint32_t)(&CM_AOS->DMA2_TRGSEL1)
#define AOS_DMA2_2              (uint32_t)(&CM_AOS->DMA2_TRGSEL2)
#define AOS_DMA2_3              (uint32_t)(&CM_AOS->DMA2_TRGSEL3)
#define AOS_DMA2_4              (uint32_t)(&CM_AOS->DMA2_TRGSEL4)
#define AOS_DMA2_5              (uint32_t)(&CM_AOS->DMA2_TRGSEL5)
#define AOS_DMA_RC              (uint32_t)(&CM_AOS->DMA_RC_TRGSEL)
#define AOS_TMR6_0              (uint32_t)(&CM_AOS->TMR6_TRGSEL0)
#define AOS_TMR6_1              (uint32_t)(&CM_AOS->TMR6_TRGSEL1)
#define AOS_TMR4_0              (uint32_t)(&CM_AOS->TMR4_TRGSEL0)
#define AOS_TMR4_1              (uint32_t)(&CM_AOS->TMR4_TRGSEL1)
#define AOS_TMR4_2              (uint32_t)(&CM_AOS->TMR4_TRGSEL2)
#define AOS_EVTPORT12           (uint32_t)(&CM_AOS->PEVNT_TRGSEL12)
#define AOS_EVTPORT34           (uint32_t)(&CM_AOS->PEVNT_TRGSEL34)
#define AOS_TMR0                (uint32_t)(&CM_AOS->TMR0_TRGSEL)
#define AOS_TMRA_0              (uint32_t)(&CM_AOS->TMRA_TRGSEL0)
#define AOS_TMRA_1              (uint32_t)(&CM_AOS->TMRA_TRGSEL1)
#define AOS_TMRA_2              (uint32_t)(&CM_AOS->TMRA_TRGSEL2)
#define AOS_TMRA_3              (uint32_t)(&CM_AOS->TMRA_TRGSEL3)
#define AOS_ADC1_0              (uint32_t)(&CM_AOS->ADC1_TRGSEL0)
#define AOS_ADC1_1              (uint32_t)(&CM_AOS->ADC1_TRGSEL1)
#define AOS_ADC2_0              (uint32_t)(&CM_AOS->ADC2_TRGSEL0)
#define AOS_ADC2_1              (uint32_t)(&CM_AOS->ADC2_TRGSEL1)
#define AOS_ADC3_0              (uint32_t)(&CM_AOS->ADC3_TRGSEL0)
#define AOS_ADC3_1              (uint32_t)(&CM_AOS->ADC3_TRGSEL1)
#define AOS_COMM_1              (uint32_t)(&CM_AOS->COMTRGSEL1)
#define AOS_COMM_2              (uint32_t)(&CM_AOS->COMTRGSEL2)

/**
 * @}
 */

/**
 * @defgroup AOS_Common_Trigger_ID AOS Common Trigger ID
 * @{
 */
#define AOS_COMM_TRIG1          (1UL << 30U)
#define AOS_COMM_TRIG2          (1UL << 31U)
#define AOS_COMM_TRIG_MASK      (AOS_COMM_TRIG1 | AOS_COMM_TRIG2)

/**
 * @}
 */

/**
 * @defgroup AOS_Trigger_Select_Mask AOS Trigger Select Mask
 * @{
 */
#define AOS_TRIG_SEL_MASK       (0x1FFUL)

/**
 * @}
 */

/**
 * @defgroup AOS_PLU_ID AOS PL Unit ID
 * @{
 */
#define AOS_PLU_ID0                     (0UL)
#define AOS_PLU_ID1                     (1UL)
#define AOS_PLU_ID2                     (2UL)
#define AOS_PLU_ID3                     (3UL)
/**
 * @}
 */

/**
 * @defgroup AOS_PLU_SEL AOS PL Unit Selection
 * @note AOS_PLU_SEL_NONE means selecting AOS source event to trigger AOS target.
 *       otherwise selecting ouput of selected PLU to trigger AOS target
 * @{
 */
#define AOS_PLU_SEL_UNIT0               (AOS_PLU_ID0)
#define AOS_PLU_SEL_UNIT1               (AOS_PLU_ID1)
#define AOS_PLU_SEL_UNIT2               (AOS_PLU_ID2)
#define AOS_PLU_SEL_UNIT3               (AOS_PLU_ID3)
#define AOS_PLU_SEL_NONE                (0xFFFFUL)
/**
 * @}
 */

/**
 * @defgroup AOS_PLU_PLInput_ID AOS PLU PL Input ID
 * @{
 */
#define AOS_PLU_PLIN_ID_A               (0UL)
#define AOS_PLU_PLIN_ID_B               (1UL)
#define AOS_PLU_PLIN_ID_C               (2UL)
#define AOS_PLU_PLIN_ID_D               (3UL)
/**
 * @}
 */

/**
 * @defgroup AOS_PLU_PLInput_Src AOS PL Input Source
 * @{
 */
#define AOS_PLU_PLIN_SRC_NUM0           (0UL)
#define AOS_PLU_PLIN_SRC_NUM1           (1UL)
#define AOS_PLU_PLIN_SRC_TRIG_EVT       (2UL)
#define AOS_PLU_PLIN_SRC_PORT_IN        (3UL)
/**
 * @}
 */

/**
 * @defgroup AOS_PLU_Mode AOS PLU logic Operation Mode
 * @{
 */
#define AOS_PLU_MODE_OR_OR              (0UL)   /*!< (PLINA | PLINB) | (PLINC | PLIND) */
#define AOS_PLU_MODE_AND_OR             (1UL)   /*!< (PLINA & PLINB) | (PLINC & PLIND) */
#define AOS_PLU_MODE_OR_XOR             (2UL)   /*!< (PLINA | PLINB) ^ (PLINC | PLIND) */
#define AOS_PLU_MODE_AND_AND            (3UL)   /*!< (PLINA & PLINB) & (PLINC & PLIND) */
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
 * @addtogroup AOS_Global_Functions
 * @{
 */

/**
 * @brief  AOS software trigger.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void AOS_SW_Trigger(void)
{
    WRITE_REG32(bCM_AOS->INTSFTTRG_b.STRG, SET);
}

int32_t AOS_DeInit(void);
void AOS_CommonTriggerCmd(uint32_t u32Target, uint32_t u32CommonTrigger, en_functional_state_t enNewState);
void AOS_SetTriggerEventSrc(uint32_t u32Target, en_event_src_t enSource);
void AOS_PLU_SetPlinTriggerEventSrc(uint32_t u32PluId, uint32_t u32PlinId, en_event_src_t enSource);
void AOS_PLU_SetPlinSrc(uint32_t u32PluId, uint32_t u32PlinId, uint32_t u32Source);
void AOS_PLU_SetLogicOperationMode(uint32_t u32PluId, uint32_t u32Mode);
void AOS_SelectPLU(uint32_t u32Target, uint32_t u32PluSel);
/**
 * @}
 */

#endif /* LL_AOS_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_AOS_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
