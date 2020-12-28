/**
 *******************************************************************************
 * @file  hc32f4a0_trng.c
 * @brief This file provides firmware functions to manage the True Random
 *        Number Generator(TRNG).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Heqb          First version
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
#include "hc32f4a0_trng.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TRNG TRNG
 * @brief TRNG Driver Library
 * @{
 */

#if (DDL_TRNG_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TRNG_Local_Macros TRNG Local Macros
 * @{
 */
#define TRNG_TIMEOUT                        (20000UL)

/**
 * @defgroup TRNG_Check_Parameters_Validity TRNG Check Parameters Validity
 * @{
 */
#define IS_VALID_SHIFT_CNT(x)                                                  \
(   ((x) == TRNG_SHIFT_COUNT_32)                ||                             \
    ((x) == TRNG_SHIFT_COUNT_64)                ||                             \
    ((x) == TRNG_SHIFT_COUNT_128)               ||                             \
    ((x) == TRNG_SHIFT_COUNT_256))

#define IS_VALID_RELOAD(x)                                                     \
(   ((x) == TRNG_RELOAD_ENABLE)                 ||                             \
    ((x) == TRNG_RELOAD_DISABLE))

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
 * @defgroup TRNG_Global_Functions TRNG Global Functions
 * @{
 */

/**
 * @brief  Set shift times
 * @param  [in] u32ShiftCount            Config the shift times.
 *  This parameter can be a value of the following:
 *   @arg  TRNG_SHIFT_COUNT_32           Shift 32 times
 *   @arg  TRNG_SHIFT_COUNT_64           Shift 64 times
 *   @arg  TRNG_SHIFT_COUNT_128          Shift 128 times
 *   @arg  TRNG_SHIFT_COUNT_256          Shift 256 times
 * @retval None
 */
void TRNG_SetShiftCnt(uint32_t u32ShiftCount)
{
    DDL_ASSERT(IS_VALID_SHIFT_CNT(u32ShiftCount));
    MODIFY_REG32(M4_TRNG->MR, TRNG_MR_CNT, u32ShiftCount);
}

/**
 * @brief  Enable or disable load new value
 * @param  [in] u32ReloadCmd              Enable or disable load new value.
 *  This parameter can be a value of the following:
 *   @arg  TRNG_RELOAD_ENABLE             Enable the function
 *   @arg  TRNG_RELOAD_DISABLE            Disable the function
 * @retval None
 */
void TRNG_ReloadCmd(uint32_t u32ReloadCmd)
{
    DDL_ASSERT(IS_VALID_RELOAD(u32ReloadCmd));
    MODIFY_REG32(M4_TRNG->MR, TRNG_MR_LOAD, u32ReloadCmd);
}

/**
 * @brief  Start TRNG and get random number
 * @param  [in] au32Random       The destination address where the random number will be stored.
 * @retval Ok: Success
 *         ErrorTimeout: Process timeout
 *         ErrorInvalidParameter: Parameter error
 * @note   Please pass in an array of 64 bits or more
 */
en_result_t TRNG_Generate(uint32_t au32Random[])
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32TimeCount = 0U;
    if(au32Random != NULL)
    {
        enRet = Ok;
        /* Enable TRNG circuit. */
        SET_REG32_BIT(M4_TRNG->CR, TRNG_CR_EN);
        /* Start TRNG */
        SET_REG32_BIT(M4_TRNG->CR, TRNG_CR_RUN);
        /* Wait for the TRNG to stop */
        while(READ_REG32_BIT(M4_TRNG->CR, TRNG_CR_RUN) == 1U)
        {
            if(u32TimeCount++ > TRNG_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        if(enRet == Ok)
        {
            /* Get the random number. */
            au32Random[0U] = READ_REG32(M4_TRNG->DR0);
            au32Random[1U] = READ_REG32(M4_TRNG->DR1);
            /* Disable TRNG circuit. */
            CLEAR_REG32_BIT(M4_TRNG->CR, TRNG_CR_EN);
        }
    }
    return enRet;
}

/**
 * @}
 */

#endif /* DDL_TRNG_ENABLE */

/**
 * @}
 */

/**
* @}
*/
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
