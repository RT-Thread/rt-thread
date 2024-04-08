/**
 *******************************************************************************
 * @file  hc32_ll_aos.c
 * @brief This file provides firmware functions to manage the AOS.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_aos.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_AOS AOS
 * @brief AOS Driver Library
 * @{
 */

#if (LL_AOS_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup AOS_Local_Macros AOS Local Macros
 * @{
 */

/**
 * @defgroup AOS_Common_Trigger_ID_Validity AOS Common Trigger ID Validity
 * @{
 */
#define IS_AOS_COMM_TRIG(x)                                                    \
(   ((x) != 0UL)                                &&                             \
    ((x) | AOS_COMM_TRIG_MASK) == AOS_COMM_TRIG_MASK)

/**
 * @}
 */

/**
 * @defgroup AOS_Target_Select_Validity AOS Target Select Validity
 * @{
 */
#define IS_AOS_TARGET(x)                                                       \
(   ((x) == AOS_DCU1)                           ||                             \
    ((x) == AOS_DCU2)                           ||                             \
    ((x) == AOS_DCU3)                           ||                             \
    ((x) == AOS_DCU4)                           ||                             \
    ((x) == AOS_DMA1_0)                         ||                             \
    ((x) == AOS_DMA1_1)                         ||                             \
    ((x) == AOS_DMA1_2)                         ||                             \
    ((x) == AOS_DMA1_3)                         ||                             \
    ((x) == AOS_DMA1_4)                         ||                             \
    ((x) == AOS_DMA1_5)                         ||                             \
    ((x) == AOS_DMA2_0)                         ||                             \
    ((x) == AOS_DMA2_1)                         ||                             \
    ((x) == AOS_DMA2_2)                         ||                             \
    ((x) == AOS_DMA2_3)                         ||                             \
    ((x) == AOS_DMA2_4)                         ||                             \
    ((x) == AOS_DMA2_5)                         ||                             \
    ((x) == AOS_DMA_RC)                         ||                             \
    ((x) == AOS_TMR6_0)                         ||                             \
    ((x) == AOS_TMR6_1)                         ||                             \
    ((x) == AOS_TMR4_0)                         ||                             \
    ((x) == AOS_TMR4_1)                         ||                             \
    ((x) == AOS_TMR4_2)                         ||                             \
    ((x) == AOS_EVTPORT12)                      ||                             \
    ((x) == AOS_EVTPORT34)                      ||                             \
    ((x) == AOS_TMR0)                           ||                             \
    ((x) == AOS_TMRA_0)                         ||                             \
    ((x) == AOS_TMRA_1)                         ||                             \
    ((x) == AOS_TMRA_2)                         ||                             \
    ((x) == AOS_TMRA_3)                         ||                             \
    ((x) == AOS_ADC1_0)                         ||                             \
    ((x) == AOS_ADC1_1)                         ||                             \
    ((x) == AOS_ADC2_0)                         ||                             \
    ((x) == AOS_ADC2_1)                         ||                             \
    ((x) == AOS_ADC3_0)                         ||                             \
    ((x) == AOS_ADC3_1)                         ||                             \
    ((x) == AOS_COMM_1)                         ||                             \
    ((x) == AOS_COMM_2))

/**
 * @}
 */

/**
 * @defgroup AOS_PLU_Check_Parameters_Validity AOS PLU check parameters validity
 * @{
 */
#define IS_AOS_PLU_ID(x)                ((x) <= AOS_PLU_ID3)
#define IS_AOS_PLU_SEL(x)               ((x) == AOS_PLU_SEL_NONE || (x) <= AOS_PLU_SEL_UNIT3)
#define IS_AOS_PLU_PLIN_ID(x)           ((x) <= AOS_PLU_PLIN_ID_D)
#define IS_AOS_PLU_PLIN_SRC(x)          ((x) <= AOS_PLU_PLIN_SRC_PORT_IN)
#define IS_AOS_PLU_MODE(x)              ((x) <= AOS_PLU_MODE_AND_AND)
/**
 * @}
 */

/**
 * @defgroup AOS_PLU_Control_Register AOS PLU Control Register
 * @{
 */
#define AOS_PLUx_CTRL_REG(x)            ((__IO uint32_t *)(&(CM_AOS->PLU0_CR) + (x)))
/**
 * @}
 */

#define IS_AOS_PWC_UNLOCKED()           ((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1)

/* AOS reset timeout */
#define AOS_RMU_TIMEOUT                 (100UL)

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup AOS_Global_Functions AOS Global Functions
 * @{
 */

/**
 * @brief  De-Initialize AOS.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          Works timeout.
 */
int32_t AOS_DeInit(void)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32TimeOut = 0U;

    /* Check parameters */
    DDL_ASSERT(IS_AOS_PWC_UNLOCKED());

    CLR_REG32_BIT(CM_RMU->FRST0, RMU_FRST0_AOS);
    /* Ensure reset procedure is completed */
    while (RMU_FRST0_AOS != READ_REG32_BIT(CM_RMU->FRST0, RMU_FRST0_AOS)) {
        u32TimeOut++;
        if (u32TimeOut > AOS_RMU_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    return i32Ret;
}

/**
 * @brief  Common trigger function command
 * @param  [in] u32Target           AOS target that need to be triggered by common trigger @ref AOS_Target_Select in details
 * @param  [in] u32CommonTrigger    Common trigger ID
 *                                  This parameter can be one of the following values:
 *   @arg  AOS_COMM_TRIG1:          Common trigger 1.
 *   @arg  AOS_COMM_TRIG2:          Common trigger 2.
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void AOS_CommonTriggerCmd(uint32_t u32Target, uint32_t u32CommonTrigger, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_AOS_TARGET(u32Target));
    DDL_ASSERT(IS_AOS_COMM_TRIG(u32CommonTrigger));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(*(__IO uint32_t *)u32Target, u32CommonTrigger);
    } else {
        CLR_REG32_BIT(*(__IO uint32_t *)u32Target, u32CommonTrigger);
    }
}

/**
 * @brief  Set trigger event source
 * @param  [in] u32Target       AOS target that need to be triggered by AOS source @ref AOS_Target_Select in details
 * @param  [in] enSource        AOS source that trigger the AOS target @ref en_event_src_t in details
 * @retval None
 */
void AOS_SetTriggerEventSrc(uint32_t u32Target, en_event_src_t enSource)
{
    DDL_ASSERT(IS_AOS_TARGET(u32Target));

    MODIFY_REG32(*(__IO uint32_t *)u32Target, AOS_TRIG_SEL_MASK, enSource);
}

/**
 * @brief  Set trigger event source for PL input
 * @param  [in] u32PluId                PL unit ID.Can be one of @ref AOS_PLU_ID
 * @param  [in] u32PlinId               PL input ID.Can be one of @ref AOS_PLU_PLInput_ID
 * @param  [in] enSource                AOS source @ref en_event_src_t
 * @retval None
 */
void AOS_PLU_SetPlinTriggerEventSrc(uint32_t u32PluId, uint32_t u32PlinId, en_event_src_t enSource)
{
    DDL_ASSERT(IS_AOS_PLU_ID(u32PluId));
    DDL_ASSERT(IS_AOS_PLU_PLIN_ID(u32PlinId));
    __IO uint32_t *TRGSELReg;

    TRGSELReg = (__IO uint32_t *)(&(CM_AOS->PLU0_TRGSELA) + (u32PluId * 4U + u32PlinId));
    MODIFY_REG32(*TRGSELReg, AOS_TRIG_SEL_MASK, enSource);
}

/**
 * @brief  Set input source for PL input
 * @param  [in] u32PluId                PL unit ID.Can be one of @ref AOS_PLU_ID
 * @param  [in] u32PlinId               PL input ID.Can be one of @ref AOS_PLU_PLInput_ID
 * @param  [in] u32Source               Source of PL input Can be one of @ref AOS_PLU_PLInput_Src
 * @retval None
 */
void AOS_PLU_SetPlinSrc(uint32_t u32PluId, uint32_t u32PlinId, uint32_t u32Source)
{
    DDL_ASSERT(IS_AOS_PLU_ID(u32PluId));
    DDL_ASSERT(IS_AOS_PLU_PLIN_ID(u32PlinId));
    DDL_ASSERT(IS_AOS_PLU_PLIN_SRC(u32Source));
    __IO uint32_t *CR;
    uint32_t u32SrcMask, u32SrcValue;

    CR = AOS_PLUx_CTRL_REG(u32PluId);
    u32SrcMask = AOS_PLU_CR_PLINASEL << (u32PlinId * 2U);
    u32SrcValue = u32Source << (AOS_PLU_CR_PLINASEL_POS + (u32PlinId * 2U));
    MODIFY_REG32(*CR, u32SrcMask, u32SrcValue);
}

/**
 * @brief  Set PLU logic operation mode
 * @param  [in] u32PluId                PL unit ID.Can be one of @ref AOS_PLU_ID
 * @param  [in] u32Mode                 PLU logic operation mode.Can be one of @ref AOS_PLU_Mode
 * @retval None
 */
void AOS_PLU_SetLogicOperationMode(uint32_t u32PluId, uint32_t u32Mode)
{
    DDL_ASSERT(IS_AOS_PLU_ID(u32PluId));
    DDL_ASSERT(IS_AOS_PLU_MODE(u32Mode));
    __IO uint32_t *CR;

    CR = AOS_PLUx_CTRL_REG(u32PluId);
    MODIFY_REG32(*CR, AOS_PLU_CR_PLMODE, u32Mode);
}

/**
 * @brief  Select PL unit or do not select pl unit to trigger the specified AOS target
 * @param  [in] u32Target               AOS target. Can be one of @ref AOS_Target_Select
 * @param  [in] u32PluSel               PL unit selection.Can be one of @ref AOS_PLU_SEL
 * @retval None
 */
void AOS_SelectPLU(uint32_t u32Target, uint32_t u32PluSel)
{
    DDL_ASSERT(IS_AOS_TARGET(u32Target));
    DDL_ASSERT(IS_AOS_PLU_SEL(u32PluSel));
    uint32_t u32SELValue;

    if (u32PluSel == AOS_PLU_SEL_NONE) {
        u32SELValue = 0U;
    } else {
        u32SELValue = (u32PluSel + 1U) << AOS_DCU_TRGSEL_PLCHSEL_POS;
    }
    MODIFY_REG32(*(__IO uint32_t *)u32Target, AOS_DCU_TRGSEL_PLCHSEL, u32SELValue);
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
