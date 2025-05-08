/**
 *******************************************************************************
 * @file  hc32_ll_swdt.c
 * @brief This file provides firmware functions to manage the Specialized Watch
 *        Dog Timer(SWDT).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-09-30       CDT             Optimize SWDT_ClearStatus function timeout
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
#include "hc32_ll_swdt.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_SWDT SWDT
 * @brief Specialized Watch Dog Timer
 * @{
 */

#if (LL_SWDT_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SWDT_Local_Macros SWDT Local Macros
 * @{
 */

/* SWDT Refresh Key */
#define SWDT_REFRESH_KEY_START          (0x0123UL)
#define SWDT_REFRESH_KEY_END            (0x3210UL)

/* SWDT clear flag timeout(ms) */
#define SWDT_CLR_FLAG_TIMEOUT           (400UL)

/**
 * @defgroup SWDT_Check_Parameters_Validity SWDT Check Parameters Validity
 * @{
 */

#define IS_SWDT_FLAG(x)                                                        \
(   ((x) != 0UL)                                &&                             \
    (((x) | SWDT_FLAG_ALL) == SWDT_FLAG_ALL))

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
 * @addtogroup SWDT_Global_Functions
 * @{
 */

/**
 * @brief  SWDT feed dog.
 * @note   In software startup mode, Start counter when refreshing for the first time.
 * @param  None
 * @retval None
 */
void SWDT_FeedDog(void)
{
    WRITE_REG32(CM_SWDT->RR, SWDT_REFRESH_KEY_START);
    WRITE_REG32(CM_SWDT->RR, SWDT_REFRESH_KEY_END);
}

/**
 * @brief  Get SWDT flag status.
 * @param  [in] u32Flag                 SWDT flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg SWDT_FLAG_UDF:        Count underflow flag
 *           @arg SWDT_FLAG_REFRESH:    Refresh error flag
 *           @arg SWDT_FLAG_ALL:        All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t SWDT_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_SWDT_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(CM_SWDT->SR, u32Flag))) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/**
 * @brief  Clear SWDT flag.
 * @param  [in] u32Flag                 SWDT flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg SWDT_FLAG_UDF:        Count underflow flag
 *           @arg SWDT_FLAG_REFRESH:    Refresh error flag
 *           @arg SWDT_FLAG_ALL:        All of the above
 * @retval int32_t:
 *           - LL_OK: Clear flag success
 *           - LL_ERR_TIMEOUT: Clear flag timeout
 */
int32_t SWDT_ClearStatus(uint32_t u32Flag)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_OK;

    /* Check parameters */
    DDL_ASSERT(IS_SWDT_FLAG(u32Flag));

    /* Waiting for FLAG bit clear */
    u32Count = SWDT_CLR_FLAG_TIMEOUT * (HCLK_VALUE / 25000UL);
    while (0UL != READ_REG32_BIT(CM_SWDT->SR, u32Flag)) {
        CLR_REG32_BIT(CM_SWDT->SR, u32Flag);
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

#endif /* LL_SWDT_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
