/**
 *******************************************************************************
 * @file  hc32_ll_rmu.c
 * @brief This file provides firmware functions to manage the Reset Manage Unit
 *        (RMU).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-06-30       CDT             Use IS_RMU_UNLOCKED() to assert
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
#include "hc32_ll_rmu.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_RMU RMU
 * @brief RMU Driver Library
 * @{
 */

#if (LL_RMU_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup RMU_Local_Macros RMU Local Macros
 * @{
 */
#define IS_RMU_UNLOCKED()       ((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1)

/**
 * @defgroup RMU_Check_Parameters_Validity RMU Check Parameters Validity
 * @{
 */

/*! Parameter validity check for RMU reset cause. */
#define IS_VALID_RMU_RST_FLAG(x)                                                \
(   ((x) != 0UL)                            &&                                  \
    (((x) | RMU_FLAG_ALL) == RMU_FLAG_ALL))

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
 * @defgroup RMU_Global_Functions RMU Global Functions
 * @{
 */

/**
 * @brief  Get the reset cause.
 * @param  [in] u32RmuResetCause    Reset flags that need to be queried, @ref RMU_ResetCause in details
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t RMU_GetStatus(uint32_t u32RmuResetCause)
{
    en_flag_status_t enStatus;
    DDL_ASSERT(IS_VALID_RMU_RST_FLAG(u32RmuResetCause));

    enStatus = ((0UL == READ_REG32_BIT(CM_RMU->RSTF0, u32RmuResetCause)) ? RESET : SET);
    return enStatus;
}

/**
 * @brief  Clear reset Status.
 * @param  None
 * @retval NOne
 * @note   Clear reset flag should be done after read RMU_RSTF0 register.
 *         Call PWC_Unlock(PWC_UNLOCK_CODE_1) unlock RMU_RSTF0 register first.
 */
void RMU_ClearStatus(void)
{
    DDL_ASSERT(IS_RMU_UNLOCKED());
    SET_REG_BIT(CM_RMU->RSTF0, RMU_RSTF0_CLRF);
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
}

/**
 * @brief  Enable or disable LOCKUP reset.
 * @param  [in] enNewState    An @ref en_functional_state_t enumeration value.
 * @retval None
 * @note   Call LL_PERIPH_WE(LL_PERIPH_PWC_CLK_RMU) unlock RMU_PRSTCR0 register first.
 */
void RMU_CPULockUpCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_RMU_UNLOCKED());

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    WRITE_REG32(bCM_RMU->PRSTCR0_b.LKUPREN, enNewState);
}

/**
 * @}
 */

#endif /* LL_RMU_ENABLE */

/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
