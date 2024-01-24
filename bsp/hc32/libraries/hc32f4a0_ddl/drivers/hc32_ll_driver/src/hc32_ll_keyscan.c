/**
 *******************************************************************************
 * @file  hc32_ll_keyscan.c
 * @brief This file provides firmware functions to manage the matrix keyscan
 * function (KEYSCAN).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-06-30       CDT             Add function KEYSCAN_DeInit
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
#include "hc32_ll_keyscan.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_KEYSCAN KEYSCAN
 * @brief Matrix keyscan Driver Library
 * @{
 */

#if (LL_KEYSCAN_ENABLE == DDL_ON)

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
#define IS_KEYSCAN_HIZ_CYCLE(clc)                                               \
(   ((clc) == KEYSCAN_HIZ_CYCLE_4)          ||                                  \
    ((clc) == KEYSCAN_HIZ_CYCLE_8)          ||                                  \
    ((clc) == KEYSCAN_HIZ_CYCLE_16)         ||                                  \
    ((clc) == KEYSCAN_HIZ_CYCLE_32)         ||                                  \
    ((clc) == KEYSCAN_HIZ_CYCLE_64)         ||                                  \
    ((clc) == KEYSCAN_HIZ_CYCLE_256)        ||                                  \
    ((clc) == KEYSCAN_HIZ_CYCLE_512)        ||                                  \
    ((clc) == KEYSCAN_HIZ_CYCLE_1024))

/*! Parameter valid check for KEYSCAN low level output cycles. */
#define IS_KEYSCAN_LOW_CYCLE(clc)                                                 \
(   ((clc) == KEYSCAN_LOW_CYCLE_4)          ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_8)          ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_16)         ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_32)         ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_64)         ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_128)        ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_256)        ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_512)        ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_1K)         ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_2K)         ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_4K)         ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_8K)         ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_16K)        ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_32K)        ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_64K)        ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_128K)       ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_256K)       ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_512K)       ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_1M)         ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_2M)         ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_4M)         ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_8M)         ||                                  \
    ((clc) == KEYSCAN_LOW_CYCLE_16M))

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
    (((in) | KEYSCAN_IN_ALL) == KEYSCAN_IN_ALL))

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
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void KEYSCAN_Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    WRITE_REG32(CM_KEYSCAN->SER, enNewState);
}

/**
 * @brief  Initialize KEYSCAN config structure. Fill each pstcKeyscanInit with default value
 * @param  [in] pstcKeyscanInit Pointer to a stc_keyscan_init_t structure that
 *                            contains configuration information.
 * @retval int32_t:
 *           - LL_OK: KEYSCAN structure initialize successful
 *           - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t KEYSCAN_StructInit(stc_keyscan_init_t *pstcKeyscanInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcKeyscanInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcKeyscanInit->u32HizCycle = KEYSCAN_HIZ_CYCLE_4;
        pstcKeyscanInit->u32LowCycle = KEYSCAN_LOW_CYCLE_4;
        pstcKeyscanInit->u32KeyClock = KEYSCAN_CLK_HCLK;
        pstcKeyscanInit->u32KeyOut   = KEYSCAN_OUT_0T1;
        pstcKeyscanInit->u32KeyIn    = KEYSCAN_IN_0;
    }
    return i32Ret;
}

/**
 * @brief  KEYSCAN initialize.
 * @param  [in] pstcKeyscanInit KEYSCAN config structure.
 *   @arg  u32HizCycle  Hiz state keep cycles during low level output.
 *   @arg  u32LowCycle  Low level output cycles.
 *   @arg  u32KeyClock    Scan clock.
 *   @arg  u32KeyOut    KEYOUT selection.
 *   @arg  u32KeyIn     KEYIN(EIRQ) selection.
 * @retval int32_t:
 *           - LL_OK: KEYSCAN function initialize successful
 *           - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t KEYSCAN_Init(const stc_keyscan_init_t *pstcKeyscanInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcKeyscanInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        DDL_ASSERT(IS_KEYSCAN_HIZ_CYCLE(pstcKeyscanInit->u32HizCycle));
        DDL_ASSERT(IS_KEYSCAN_LOW_CYCLE(pstcKeyscanInit->u32LowCycle));
        DDL_ASSERT(IS_KEYSCAN_CLK(pstcKeyscanInit->u32KeyClock));
        DDL_ASSERT(IS_KEYSCAN_OUT(pstcKeyscanInit->u32KeyOut));
        DDL_ASSERT(IS_KEYSCAN_IN(pstcKeyscanInit->u32KeyIn));

        WRITE_REG32(CM_KEYSCAN->SCR, \
                    (pstcKeyscanInit->u32HizCycle | pstcKeyscanInit->u32LowCycle | \
                     pstcKeyscanInit->u32KeyClock | pstcKeyscanInit->u32KeyOut   | \
                     pstcKeyscanInit->u32KeyIn));
    }
    return i32Ret;
}

/**
 * @brief  De-initialize the KEYSCAN.
 * @param  None
 * @retval int32_t:
 *           - LL_OK: De-Initialize success.
 */
int32_t KEYSCAN_DeInit(void)
{
    int32_t i32Ret = LL_OK;
    WRITE_REG32(CM_KEYSCAN->SER, 0UL);
    WRITE_REG32(CM_KEYSCAN->SCR, 0UL);
    return i32Ret;
}

/**
 * @}
 */

#endif  /* LL_KEYSCAN_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
