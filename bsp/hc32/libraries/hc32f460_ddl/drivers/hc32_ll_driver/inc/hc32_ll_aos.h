/**
 *******************************************************************************
 * @file  hc32_ll_aos.h
 * @brief This file contains all the functions prototypes of the AOS driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-01-15       CDT             Modified parameters name of API AOS_CommonTriggerCmd() and AOS_SetTriggerEventSrc()
   2023-09-30       CDT             Modify for new head file
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
#define AOS_DMA2_0              (uint32_t)(&CM_AOS->DMA2_TRGSEL0)
#define AOS_DMA2_1              (uint32_t)(&CM_AOS->DMA2_TRGSEL1)
#define AOS_DMA2_2              (uint32_t)(&CM_AOS->DMA2_TRGSEL2)
#define AOS_DMA2_3              (uint32_t)(&CM_AOS->DMA2_TRGSEL3)
#define AOS_DMA_RC              (uint32_t)(&CM_AOS->DMA_RC_TRGSEL)
#define AOS_TMR6_0              (uint32_t)(&CM_AOS->TMR6_TRGSEL0)
#define AOS_TMR6_1              (uint32_t)(&CM_AOS->TMR6_TRGSEL1)
#define AOS_TMR0                (uint32_t)(&CM_AOS->TMR0_TRGSEL)
#define AOS_EVTPORT12           (uint32_t)(&CM_AOS->PEVNT_TRGSEL12)
#define AOS_EVTPORT34           (uint32_t)(&CM_AOS->PEVNT_TRGSEL34)
#define AOS_TMRA_0              (uint32_t)(&CM_AOS->TMRA_TRGSEL0)
#define AOS_TMRA_1              (uint32_t)(&CM_AOS->TMRA_TRGSEL1)
#define AOS_OTS                 (uint32_t)(&CM_AOS->OTS_TRGSEL)
#define AOS_ADC1_0              (uint32_t)(&CM_AOS->ADC1_TRGSEL0)
#define AOS_ADC1_1              (uint32_t)(&CM_AOS->ADC1_TRGSEL1)
#define AOS_ADC2_0              (uint32_t)(&CM_AOS->ADC2_TRGSEL0)
#define AOS_ADC2_1              (uint32_t)(&CM_AOS->ADC2_TRGSEL1)
#define AOS_COMM_1              (uint32_t)(&CM_AOS->COMTRG1)
#define AOS_COMM_2              (uint32_t)(&CM_AOS->COMTRG2)

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

void AOS_CommonTriggerCmd(uint32_t u32Target, uint32_t u32CommonTrigger, en_functional_state_t enNewState);
void AOS_SetTriggerEventSrc(uint32_t u32Target, en_event_src_t enSource);
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
