/**
 *******************************************************************************
 * @file  hc32f4a0_keyscan.c
 * @brief This file provides firmware functions to manage the matrix keyscan
 * function (KEYSCAN).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Zhangxl         First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_keyscan.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_KEYSCAN KEYSCAN
 * @brief Matrix keyscan Driver Library
 * @{
 */

#if (DDL_KEYSCAN_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup KEYSCAN_Local_Macros KEYSCAN Local Macros
 * @{
 */

/**
 * @defgroup KEYSCAN_Check_Parameters_Validity KEYSCAN Check Parameters Validity
 * @{
 */
/*! Parameter valid check for KEYSCAN HiZ state cycles. */
#define IS_KEYSCAN_HIZ_CLC(clc)                                                 \
(   ((clc) == KEYSCAN_HIZ_CLC_4)            ||                                  \
    ((clc) == KEYSCAN_HIZ_CLC_8)            ||                                  \
    ((clc) == KEYSCAN_HIZ_CLC_16)           ||                                  \
    ((clc) == KEYSCAN_HIZ_CLC_32)           ||                                  \
    ((clc) == KEYSCAN_HIZ_CLC_64)           ||                                  \
    ((clc) == KEYSCAN_HIZ_CLC_256)          ||                                  \
    ((clc) == KEYSCAN_HIZ_CLC_512)          ||                                  \
    ((clc) == KEYSCAN_HIZ_CLC_1024))

/*! Parameter valid check for KEYSCAN low level output cycles. */
#define IS_KEYSCAN_LOW_CLC(clc)                                                 \
(   ((clc) == KEYSCAN_LOW_CLC_4)            ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_8)            ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_16)           ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_32)           ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_64)           ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_128)          ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_256)          ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_512)          ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_1K)           ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_2K)           ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_4K)           ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_8K)           ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_16K)          ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_32K)          ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_64K)          ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_128K)         ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_256K)         ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_512K)         ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_1M)           ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_2M)           ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_4M)           ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_8M)           ||                                  \
    ((clc) == KEYSCAN_LOW_CLC_16M))

/*! Parameter valid check for KEYSCAN scan clock. */
#define IS_KEYSCAN_CLK(clk)                                                     \
(   ((clk) == KEYSCAN_CLK_HCLK)             ||                                  \
    ((clk) == KEYSCAN_CLK_LRC)              ||                                  \
    ((clk) == KEYSCAN_CLK_XTAL32))

/*! Parameter valid check for KEYSCAN keyout pins. */
#define IS_KEYSCAN_OUT(out)                                                     \
(   ((out) == KEYSCAN_OUT_0T1)              ||                                  \
    ((out) == KEYSCAN_OUT_0T2)              ||                                  \
    ((out) == KEYSCAN_OUT_0T3)              ||                                  \
    ((out) == KEYSCAN_OUT_0T4)              ||                                  \
    ((out) == KEYSCAN_OUT_0T5)              ||                                  \
    ((out) == KEYSCAN_OUT_0T6)              ||                                  \
    ((out) == KEYSCAN_OUT_0T7))

/*! Parameter valid check for KEYSCAN keyin(EIRQ) pins. */
#define IS_KEYSCAN_IN(in)                                                       \
(   ((in) != 0x00U)                         &&                                  \
    (((in) | KEYSCAN_IN_MASK) == KEYSCAN_IN_MASK))

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
 * @defgroup KEYSCAN_Global_Functions KEYSCAN Global Functions
 * @{
 */

/**
 * @brief  KEYSCAN function config.
 * @param  [in] enNewState The function new state.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void KEYSCAN_Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    WRITE_REG32(M4_KEYSCAN->SER, enNewState);
}

/**
 * @brief  Initialize KEYSCAN config structure. Fill each pstcKeyscanInit with default value
 * @param  [in] pstcKeyscanInit Pointer to a stc_keyscan_init_t structure that
 *                            contains configuration information.
 * @retval Ok: KEYSCAN structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t KEYSCAN_StructInit(stc_keyscan_init_t *pstcKeyscanInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcKeyscanInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcKeyscanInit->u32HizCycle= KEYSCAN_HIZ_CLC_4;
        pstcKeyscanInit->u32LowCycle= KEYSCAN_LOW_CLC_4;
        pstcKeyscanInit->u32KeyClk  = KEYSCAN_CLK_HCLK;
        pstcKeyscanInit->u32KeyOut  = KEYSCAN_OUT_0T1;
        pstcKeyscanInit->u32KeyIn   = KEYSCAN_IN_0;
    }
    return enRet;
}

/**
 * @brief  KEYSCAN initialize.
 * @param  [in] pstcKeyscanInit KEYSCAN config structure.
 *   @arg  u32HizCycle  Hiz state keep cycles during low level output.
 *   @arg  u32LowCycle  Low level output cycles.
 *   @arg  u32KeyClk    Scan clock.
 *   @arg  u32KeyOut    KEYOUT selection.
 *   @arg  u32KeyIn     KEYIN(EIRQ) selection.
 * @retval Ok: KEYSCAN function initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t KEYSCAN_Init(const stc_keyscan_init_t *pstcKeyscanInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcKeyscanInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_KEYSCAN_HIZ_CLC(pstcKeyscanInit->u32HizCycle));
        DDL_ASSERT(IS_KEYSCAN_LOW_CLC(pstcKeyscanInit->u32LowCycle));
        DDL_ASSERT(IS_KEYSCAN_CLK(pstcKeyscanInit->u32KeyClk));
        DDL_ASSERT(IS_KEYSCAN_OUT(pstcKeyscanInit->u32KeyOut));
        DDL_ASSERT(IS_KEYSCAN_IN(pstcKeyscanInit->u32KeyIn));

        WRITE_REG32(M4_KEYSCAN->SCR,                                            \
            (pstcKeyscanInit->u32HizCycle | pstcKeyscanInit->u32LowCycle |      \
            pstcKeyscanInit->u32KeyClk    | pstcKeyscanInit->u32KeyOut   |      \
            pstcKeyscanInit->u32KeyIn ));
    }
    return enRet;
}

/**
 * @}
 */

#endif  /* DDL_KEYSCAN_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
