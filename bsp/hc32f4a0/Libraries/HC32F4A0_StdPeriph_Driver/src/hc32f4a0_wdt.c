/**
 *******************************************************************************
 * @file  hc32f4a0_wdt.c
 * @brief This file provides firmware functions to manage the General Watch Dog
 *        Timer(WDT).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
   2020-09-04       Yangjp          Optimize timeout handling in functions
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
#include "hc32f4a0_wdt.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_WDT WDT
 * @brief General Watch Dog Timer
 * @{
 */

#if (DDL_WDT_ENABLE == DDL_ON)

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

/* WDT Registers Clear Mask */
#define WDT_CR_CLEAR_MASK               (WDT_CR_PERI   | WDT_CR_CKS | WDT_CR_WDPT | \
                                         WDT_CR_SLPOFF | WDT_CR_ITS)

/* WDT Refresh Key */
#define WDT_REFRESH_KEY_START           (0x0123UL)
#define WDT_REFRESH_KEY_END             (0x3210UL)

/* WDT clear flag timeout(ms) */
#define WDT_CLEAR_FLAG_TIMEOUT          (5UL)

/**
 * @defgroup WDT_Check_Parameters_Validity WDT Check Parameters Validity
 * @{
 */
#define IS_WDT_COUNTER_CYCLE(x)                                                \
(   ((x) == WDT_COUNTER_CYCLE_256)              ||                             \
    ((x) == WDT_COUNTER_CYCLE_4096)             ||                             \
    ((x) == WDT_COUNTER_CYCLE_16384)            ||                             \
    ((x) == WDT_COUNTER_CYCLE_65536))

#define IS_WDT_CLOCK_DIVISION(x)                                               \
(   ((x) == WDT_CLOCK_DIV4)                     ||                             \
    ((x) == WDT_CLOCK_DIV64)                    ||                             \
    ((x) == WDT_CLOCK_DIV128)                   ||                             \
    ((x) == WDT_CLOCK_DIV256)                   ||                             \
    ((x) == WDT_CLOCK_DIV512)                   ||                             \
    ((x) == WDT_CLOCK_DIV1024)                  ||                             \
    ((x) == WDT_CLOCK_DIV2048)                  ||                             \
    ((x) == WDT_CLOCK_DIV8192))

#define IS_WDT_ALLOW_REFRESH_RANGE(x)                                          \
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

#define IS_WDT_LPM_COUNT(x)                                                    \
(   ((x) == WDT_LPM_COUNT_CONTINUE)             ||                             \
    ((x) == WDT_LPM_COUNT_STOP))

#define IS_WDT_REQUEST_TYPE(x)                                                 \
(   ((x) == WDT_TRIG_EVENT_INT)                 ||                             \
    ((x) == WDT_TRIG_EVENT_RESET))

#define IS_WDT_FLAG(x)                                                         \
(   (0UL != (x))                                &&                             \
    (0UL == ((x) & ((uint32_t)(~(WDT_FLAG_UDF   | WDT_FLAG_REF))))))

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
 * @brief  Initialize WDT.
 * @param  [in] pstcWdtInit             Pointer to a @ref stc_wdt_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t WDT_Init(const stc_wdt_init_t *pstcWdtInit)
{
    en_result_t enRet = Ok;

    if(NULL == pstcWdtInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_WDT_COUNTER_CYCLE(pstcWdtInit->u32CountCycle));
        DDL_ASSERT(IS_WDT_CLOCK_DIVISION(pstcWdtInit->u32ClockDivision));
        DDL_ASSERT(IS_WDT_ALLOW_REFRESH_RANGE(pstcWdtInit->u32RefreshRange));
        DDL_ASSERT(IS_WDT_LPM_COUNT(pstcWdtInit->u32LPModeCountEn));
        DDL_ASSERT(IS_WDT_REQUEST_TYPE(pstcWdtInit->u32TrigType));

        /* WDT CR Configuration(Software Start Mode) */
        MODIFY_REG32(M4_WDT->CR, WDT_CR_CLEAR_MASK,
                     (pstcWdtInit->u32CountCycle   | pstcWdtInit->u32ClockDivision |
                      pstcWdtInit->u32RefreshRange | pstcWdtInit->u32LPModeCountEn |
                      pstcWdtInit->u32TrigType));
    }

    return enRet;
}

/**
 * @brief  WDT feed dog.
 * @note   In software startup mode, Start counter when refreshing for the first time.
 * @param  None
 * @retval None
 */
void WDT_Feed(void)
{
    WRITE_REG32(M4_WDT->RR, WDT_REFRESH_KEY_START);
    WRITE_REG32(M4_WDT->RR, WDT_REFRESH_KEY_END);
}

/**
 * @brief  Get WDT flag status.
 * @param  [in] u32Flag                 Specifies the WDT flag type.
 *         This parameter can be one or any combination of the following values:
 *           @arg WDT_FLAG_UDF:     Count Underflow flag
 *           @arg WDT_FLAG_REF:     Refresh Error flag
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t WDT_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_WDT_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(M4_WDT->SR, u32Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/**
 * @brief  Clear WDT flag status.
 * @param  [in] u32Flag                 Specifies the WDT flag type.
 *         This parameter can be one or any combination of the following values:
 *           @arg WDT_FLAG_UDF:     Count Underflow flag
 *           @arg WDT_FLAG_REF:     Refresh Error flag
 * @retval An en_result_t enumeration value:
 *           - Ok: Clear flag success
 *           - ErrorTimeout: Clear flag timeout
 */
en_result_t WDT_ClearStatus(uint32_t u32Flag)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Ok;

    /* Check parameters */
    DDL_ASSERT(IS_WDT_FLAG(u32Flag));

    CLEAR_REG32_BIT(M4_WDT->SR, u32Flag);
    /* Waiting for FLAG bit clear */
    u32Count = WDT_CLEAR_FLAG_TIMEOUT * (HCLK_VALUE / 20000UL);
    while (0UL != READ_REG32_BIT(M4_WDT->SR, u32Flag))
    {
        if (0UL == u32Count)
        {
            enRet = ErrorTimeout;
            break;
        }
        u32Count--;
    }

    return enRet;
}

/**
 * @}
 */

#endif /* DDL_WDT_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
