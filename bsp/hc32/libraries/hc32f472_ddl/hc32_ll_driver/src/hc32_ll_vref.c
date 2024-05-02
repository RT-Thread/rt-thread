/**
 *******************************************************************************
 * @file  hc32_ll_vref.c
 * @brief This file provides firmware functions to manage the high precision
 *        Reference Voltage(VREF).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Modify typo
                                    Add API VREF_DeInit()
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
#include "hc32_ll_vref.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_VREF VREF
 * @brief VREF Driver Library
 * @{
 */

#if (LL_VREF_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup VREF_Local_Macros VREF Local Macros
 * @{
 */

#define VREF_RMU_TIMEOUT             (100UL)

/**
 * @defgroup VREF_Check_Parameters_Validity VREF Check Parameters Validity
 * @{
 */
#define IS_VREF_OPERATING_MD(x)                                                \
(   ((x) == VREF_EXT_REF_MD)                    ||                             \
    ((x) == VREF_SHORT_MD)                      ||                             \
    ((x) == VREF_INTERN_REF_MD))

#define IS_VREF_AVCC_DIV_OUTPUT(x)                                             \
(   ((x) == VREF_AVCC_DIV_QUARTER)              ||                             \
    ((x) == VREF_AVCC_DIV_ONE_THIRD)            ||                             \
    ((x) == VREF_AVCC_DIV_TWO_FIFTHS)           ||                             \
    ((x) == VREF_AVCC_DIV_HALF))
/**
 * @}
 */

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
 * @defgroup VREF_Global_Functions VREF Global Functions
 * @{
 */

/**
 * @brief  Enable or disable Band Gap Reference circuit.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void VREF_BandGapRefCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    WRITE_REG32(CM_VREF->BGRCR, enNewState);
}

/**
 * @brief  Enable or disable Current Source circuit.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void VREF_CurrentSrcCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    WRITE_REG32(CM_VREF->CSCR, enNewState);
}

/**
 * @brief  AVCC divider voltage command.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void VREF_AvccDivCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    if (enNewState == ENABLE) {
        SET_REG32_BIT(CM_VREF->CR, VREF_CR_AVCCMONEN);
    } else {
        CLR_REG32_BIT(CM_VREF->CR, VREF_CR_AVCCMONEN);
    }
}

/**
 * @brief  AVCC divider configure.
 * @param  [in]  u32Div                 AVCC voltage divider @ref VREF_Avcc_Div_Config
 * @retval None
 */
void VREF_AvccDivConfig(uint32_t u32Div)
{
    DDL_ASSERT(IS_VREF_AVCC_DIV_OUTPUT(u32Div));
    MODIFY_REG32(CM_VREF->CR, VREF_CR_AVCCMONS, u32Div);
}

/**
 * @brief  VREFINT voltage command
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void VREF_VrefintCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    if (enNewState == ENABLE) {
        SET_REG32_BIT(CM_VREF->CR, VREF_CR_VREFINTEN);
    } else {
        CLR_REG32_BIT(CM_VREF->CR, VREF_CR_VREFINTEN);
    }
}

/**
 * @brief  IVREF(internal reference) voltage command
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void VREF_IvrefCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    if (enNewState == ENABLE) {
        SET_REG32_BIT(CM_VREF->CR, VREF_CR_IVREFEN);
    } else {
        CLR_REG32_BIT(CM_VREF->CR, VREF_CR_IVREFEN);
    }
}

/**
 * @brief  Set the mode of IVREF voltage.
 * @param  [in] u32Mode                 VREF operating mode.
 *                                      This parameter can be a value of @ref VREF_Intern_Vref_Mode
 *   @arg  VREF_EXT_REF_MD:             External reference voltage mode, VREFH input as reference voltage.
 *                                      Internal reference voltage is OFF.
 *   @arg  VREF_SHORT_MD:               VREFH is short to VSS. Internal reference voltage is OFF.
 *   @arg  VREF_INTERN_REF_MD:          Use internal reference voltage.
 *                                      External VREFH is short to internal VREF circuit.
 * @retval None
 */
void VREF_SetIvrefMode(uint32_t u32Mode)
{
    DDL_ASSERT(IS_VREF_OPERATING_MD(u32Mode));
    MODIFY_REG32(CM_VREF->CR, VREF_CR_HIZ | VREF_CR_IVREFEN, u32Mode);
}

/**
 * @brief  De-initializes the VREF peripheral.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   De-Initialize success.
 *           - LL_ERR_TIMEOUT:          Timeout.
 */
int32_t VREF_DeInit(void)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32TimeOut = 0U;
    /* Check RMU_FRST register protect */
    DDL_ASSERT((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1);

    /* Reset */
    WRITE_REG32(bCM_RMU->FRST3_b.VREF, 0UL);
    /* Ensure reset procedure is completed */
    while (0UL == READ_REG32(bCM_RMU->FRST3_b.VREF)) {
        u32TimeOut++;
        if (u32TimeOut > VREF_RMU_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }
    return i32Ret;
}

/**
 * @}
 */

#endif /* LL_VREF_ENABLE */

/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
