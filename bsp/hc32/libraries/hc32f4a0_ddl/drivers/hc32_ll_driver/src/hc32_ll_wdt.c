/**
 *******************************************************************************
 * @file  hc32_ll_wdt.c
 * @brief This file provides firmware functions to manage the General Watch Dog
 *        Timer(WDT).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
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
#include "hc32_ll_wdt.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_WDT WDT
 * @brief General Watch Dog Timer
 * @{
 */

#if (LL_WDT_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup WDT_Local_Macros WDT Local Macros
 * @{
 */

/* WDT Refresh Key */
#define WDT_REFRESH_KEY_START           (0x0123UL)
#define WDT_REFRESH_KEY_END             (0x3210UL)

/* WDT clear flag timeout(ms) */
#define WDT_CLR_FLAG_TIMEOUT            (5UL)

/* WDT Registers Clear Mask */
#define WDT_CR_CLR_MASK                 (WDT_CR_PERI   | WDT_CR_CKS | WDT_CR_WDPT | \
                                         WDT_CR_SLPOFF | WDT_CR_ITS)

/**
 * @defgroup WDT_Check_Parameters_Validity WDT Check Parameters Validity
 * @{
 */
#define IS_WDT_CNT_PERIOD(x)                                                   \
(   ((x) == WDT_CNT_PERIOD256)                  ||                             \
    ((x) == WDT_CNT_PERIOD4096)                 ||                             \
    ((x) == WDT_CNT_PERIOD16384)                ||                             \
    ((x) == WDT_CNT_PERIOD65536))

#define IS_WDT_CLK_DIV(x)                                                      \
(   ((x) == WDT_CLK_DIV4)                       ||                             \
    ((x) == WDT_CLK_DIV64)                      ||                             \
    ((x) == WDT_CLK_DIV128)                     ||                             \
    ((x) == WDT_CLK_DIV256)                     ||                             \
    ((x) == WDT_CLK_DIV512)                     ||                             \
    ((x) == WDT_CLK_DIV1024)                    ||                             \
    ((x) == WDT_CLK_DIV2048)                    ||                             \
    ((x) == WDT_CLK_DIV8192))

#define IS_WDT_REFRESH_RANGE(x)                                                \
(   ((x) == WDT_RANGE_0TO100PCT)                ||                             \
    ((x) == WDT_RANGE_0TO25PCT)                 ||                             \
    ((x) == WDT_RANGE_25TO50PCT)                ||                             \
    ((x) == WDT_RANGE_0TO50PCT)                 ||                             \
    ((x) == WDT_RANGE_50TO75PCT)                ||                             \
    ((x) == WDT_RANGE_0TO25PCT_50TO75PCT)       ||                             \
    ((x) == WDT_RANGE_25TO75PCT)                ||                             \
    ((x) == WDT_RANGE_0TO75PCT)                 ||                             \
    ((x) == WDT_RANGE_75TO100PCT)               ||                             \
    ((x) == WDT_RANGE_0TO25PCT_75TO100PCT)      ||                             \
    ((x) == WDT_RANGE_25TO50PCT_75TO100PCT)     ||                             \
    ((x) == WDT_RANGE_0TO50PCT_75TO100PCT)      ||                             \
    ((x) == WDT_RANGE_50TO100PCT)               ||                             \
    ((x) == WDT_RANGE_0TO25PCT_50TO100PCT)      ||                             \
    ((x) == WDT_RANGE_25TO100PCT))

#define IS_WDT_LPM_CNT(x)                                                      \
(   ((x) == WDT_LPM_CNT_CONTINUE)               ||                             \
    ((x) == WDT_LPM_CNT_STOP))

#define IS_WDT_EXP_TYPE(x)                                                     \
(   ((x) == WDT_EXP_TYPE_INT)                   ||                             \
    ((x) == WDT_EXP_TYPE_RST))

#define IS_WDT_FLAG(x)                                                         \
(   ((x) != 0UL)                                &&                             \
    (((x) | WDT_FLAG_ALL) == WDT_FLAG_ALL))

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
 * @defgroup WDT_Global_Functions WDT Global Functions
 * @{
 */

/**
 * @brief  Initializes WDT.
 * @param  [in] pstcWdtInit             Pointer to a @ref stc_wdt_init_t structure
 * @retval int32_t:
 *           - LL_OK: Initializes success
 *           - LL_ERR_INVD_PARAM: pstcWdtInit == NULL
 */
int32_t WDT_Init(const stc_wdt_init_t *pstcWdtInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcWdtInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_WDT_CNT_PERIOD(pstcWdtInit->u32CountPeriod));
        DDL_ASSERT(IS_WDT_CLK_DIV(pstcWdtInit->u32ClockDiv));
        DDL_ASSERT(IS_WDT_REFRESH_RANGE(pstcWdtInit->u32RefreshRange));
        DDL_ASSERT(IS_WDT_LPM_CNT(pstcWdtInit->u32LPMCount));
        DDL_ASSERT(IS_WDT_EXP_TYPE(pstcWdtInit->u32ExceptionType));

        /* WDT CR Configuration(Software Start Mode) */
        MODIFY_REG32(CM_WDT->CR, WDT_CR_CLR_MASK,
                     (pstcWdtInit->u32CountPeriod  | pstcWdtInit->u32ClockDiv |
                      pstcWdtInit->u32RefreshRange | pstcWdtInit->u32LPMCount |
                      pstcWdtInit->u32ExceptionType));
    }

    return i32Ret;
}

/**
 * @brief  WDT feed dog.
 * @note   In software startup mode, Start counter when refreshing for the first time.
 * @param  None
 * @retval None
 */
void WDT_FeedDog(void)
{
    WRITE_REG32(CM_WDT->RR, WDT_REFRESH_KEY_START);
    WRITE_REG32(CM_WDT->RR, WDT_REFRESH_KEY_END);
}

/**
 * @brief  Get WDT flag status.
 * @param  [in] u32Flag                 WDT flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg WDT_FLAG_UDF:         Count underflow flag
 *           @arg WDT_FLAG_REFRESH:     Refresh error flag
 *           @arg WDT_FLAG_ALL:         All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t WDT_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_WDT_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(CM_WDT->SR, u32Flag))) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/**
 * @brief  Clear WDT flag.
 * @param  [in] u32Flag                 WDT flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg WDT_FLAG_UDF:         Count underflow flag
 *           @arg WDT_FLAG_REFRESH:     Refresh error flag
 *           @arg WDT_FLAG_ALL:         All of the above
 * @retval int32_t:
 *           - LL_OK: Clear flag success
 *           - LL_ERR_TIMEOUT: Clear flag timeout
 */
int32_t WDT_ClearStatus(uint32_t u32Flag)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_OK;

    /* Check parameters */
    DDL_ASSERT(IS_WDT_FLAG(u32Flag));

    CLR_REG32_BIT(CM_WDT->SR, u32Flag);
    /* Waiting for FLAG bit clear */
    u32Count = WDT_CLR_FLAG_TIMEOUT * (HCLK_VALUE / 20000UL);
    while (0UL != READ_REG32_BIT(CM_WDT->SR, u32Flag)) {
        if (0UL == u32Count) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
        u32Count--;
    }

    return i32Ret;
}

/**
 * @}
 */

#endif /* LL_WDT_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
