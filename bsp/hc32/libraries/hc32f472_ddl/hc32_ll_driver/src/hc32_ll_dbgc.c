/**
 *******************************************************************************
 * @file  hc32_ll_dbgc.c
 * @brief This file provides firmware functions to manage the DBGC.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-06-30       CDT             First version
   2023-09-30       CDT             Add assert to DBGC_PeriphCmd & DBGC_Periph2Cmd
                                    Add assert IS_DGBC_TRACE_MD and add API DBGC_TraceIoCmd,DBGC_TraceModeConfig
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
#include "hc32_ll_dbgc.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_DBGC DBGC
 * @brief DBGC Driver Library
 * @{
 */

#if (LL_DBGC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup DBGC_Local_Macros DBGC Local Macros
 * @{
 */

/**
 * @defgroup DBGC_Check_Parameters_Validity DBGC Check Parameters Validity
 * @{
 */
#define IS_SECURITY_FLAG(x)                                                    \
(   ((x) != 0U)                                     &&                         \
    (((x) | DBGC_SECURITY_ALL) == DBGC_SECURITY_ALL))

/* Parameter valid check for debug trace mode */
#define IS_DGBC_TRACE_MD(x)                                                    \
(   ((x) == DBGC_TRACE_ASYNC)                       ||                         \
    ((x) == DBGC_TRACE_SYNC_1BIT)                   ||                         \
    ((x) == DBGC_TRACE_SYNC_2BIT)                   ||                         \
    ((x) == DBGC_TRACE_SYNC_4BIT))
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
 * @defgroup DBGC_Global_Functions DBGC Global Functions
 * @{
 */

/**
 * @brief  Whether to stop the peripheral while mcu core stop.
 * @param  [in] u32Periph Specifies the peripheral. @ref DBGC_Periph_Sel
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DBGC_PeriphCmd(uint32_t u32Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        CLR_REG32_BIT(CM_DBGC->MCUSTPCTL, u32Periph);
    } else {
        SET_REG32_BIT(CM_DBGC->MCUSTPCTL, u32Periph);
    }
}

/**
 * @brief  Whether to stop the peripheral2 while mcu core stop.
 * @param  [in] u32Periph Specifies the peripheral. @ref DBGC_Periph2_Sel
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DBGC_Periph2Cmd(uint32_t u32Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        CLR_REG32_BIT(CM_DBGC->MCUSTPCTL2, u32Periph);
    } else {
        SET_REG32_BIT(CM_DBGC->MCUSTPCTL2, u32Periph);
    }
}

/**
 * @brief  Enable or disable the trace pin output.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DBGC_TraceIoCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_DBGC->MCUTRACECTL, DBGC_MCUTRACECTL_TRACEIOEN);
    } else {
        CLR_REG32_BIT(CM_DBGC->MCUTRACECTL, DBGC_MCUTRACECTL_TRACEIOEN);
    }
}

/**
 * @brief  Config trace mode.
 * @param  [in] u32TraceMode Specifies the trace mode. @ref DBGC_Trace_Mode
 * @retval None
 */
void DBGC_TraceModeConfig(uint32_t u32TraceMode)
{
    DDL_ASSERT(IS_DGBC_TRACE_MD(u32TraceMode));

    MODIFY_REG32(CM_DBGC->MCUTRACECTL, DBGC_MCUTRACECTL_TRACEMODE, u32TraceMode);
}

/**
 * @}
 */

#endif /* LL_DBGC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
