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

/* SWDT Registers Clear Mask */
#define SWDT_CR_CLR_MASK                (SWDT_CR_PERI   | SWDT_CR_CKS | SWDT_CR_WDPT | \
                                         SWDT_CR_SLPOFF | SWDT_CR_ITS)

/**
 * @defgroup SWDT_Check_Parameters_Validity SWDT Check Parameters Validity
 * @{
 */

#define IS_SWDT_CNT_PERIOD(x)                                                  \
(   ((x) == SWDT_CNT_PERIOD256)                 ||                             \
    ((x) == SWDT_CNT_PERIOD4096)                ||                             \
    ((x) == SWDT_CNT_PERIOD16384)               ||                             \
    ((x) == SWDT_CNT_PERIOD65536))

#define IS_SWDT_CLK_DIV(x)                                                     \
(   ((x) == SWDT_CLK_DIV1)                      ||                             \
    ((x) == SWDT_CLK_DIV16)                     ||                             \
    ((x) == SWDT_CLK_DIV32)                     ||                             \
    ((x) == SWDT_CLK_DIV64)                     ||                             \
    ((x) == SWDT_CLK_DIV128)                    ||                             \
    ((x) == SWDT_CLK_DIV256)                    ||                             \
    ((x) == SWDT_CLK_DIV2048))

#define IS_SWDT_REFRESH_RANGE(x)                                               \
(   ((x) == SWDT_RANGE_0TO100PCT)               ||                             \
    ((x) == SWDT_RANGE_0TO25PCT)                ||                             \
    ((x) == SWDT_RANGE_25TO50PCT)               ||                             \
    ((x) == SWDT_RANGE_0TO50PCT)                ||                             \
    ((x) == SWDT_RANGE_50TO75PCT)               ||                             \
    ((x) == SWDT_RANGE_0TO25PCT_50TO75PCT)      ||                             \
    ((x) == SWDT_RANGE_25TO75PCT)               ||                             \
    ((x) == SWDT_RANGE_0TO75PCT)                ||                             \
    ((x) == SWDT_RANGE_75TO100PCT)              ||                             \
    ((x) == SWDT_RANGE_0TO25PCT_75TO100PCT)     ||                             \
    ((x) == SWDT_RANGE_25TO50PCT_75TO100PCT)    ||                             \
    ((x) == SWDT_RANGE_0TO50PCT_75TO100PCT)     ||                             \
    ((x) == SWDT_RANGE_50TO100PCT)              ||                             \
    ((x) == SWDT_RANGE_0TO25PCT_50TO100PCT)     ||                             \
    ((x) == SWDT_RANGE_25TO100PCT))

#define IS_SWDT_LPM_CNT(x)                                                     \
(   ((x) == SWDT_LPM_CNT_CONTINUE)              ||                             \
    ((x) == SWDT_LPM_CNT_STOP))

#define IS_SWDT_EXP_TYPE(x)                                                    \
(   ((x) == SWDT_EXP_TYPE_INT)                  ||                             \
    ((x) == SWDT_EXP_TYPE_RST))

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
 * @brief  Initializes SWDT.
 * @param  [in] pstcSwdtInit            Pointer to a @ref stc_swdt_init_t structure
 * @retval int32_t:
 *           - LL_OK: Initializes success
 *           - LL_ERR_INVD_PARAM: pstcSwdtInit == NULL
 */
int32_t SWDT_Init(const stc_swdt_init_t *pstcSwdtInit)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32Temp;

    if (NULL == pstcSwdtInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_SWDT_CNT_PERIOD(pstcSwdtInit->u32CountPeriod));
        DDL_ASSERT(IS_SWDT_CLK_DIV(pstcSwdtInit->u32ClockDiv));
        DDL_ASSERT(IS_SWDT_REFRESH_RANGE(pstcSwdtInit->u32RefreshRange));
        DDL_ASSERT(IS_SWDT_LPM_CNT(pstcSwdtInit->u32LPMCount));
        DDL_ASSERT(IS_SWDT_EXP_TYPE(pstcSwdtInit->u32ExceptionType));

        u32Temp = pstcSwdtInit->u32CountPeriod  | pstcSwdtInit->u32ClockDiv |
                  pstcSwdtInit->u32RefreshRange | pstcSwdtInit->u32LPMCount | pstcSwdtInit->u32ExceptionType;
        /* SWDT CR Configuration(Software Start Mode) */
        MODIFY_REG32(CM_SWDT->CR, SWDT_CR_CLR_MASK, u32Temp);
    }

    return i32Ret;
}

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
