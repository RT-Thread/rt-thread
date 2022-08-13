/**
 *******************************************************************************
 * @file  hc32_ll_trng.c
 * @brief This file provides firmware functions to manage the True Random
 *        Number Generator(TRNG).
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
#include "hc32_ll_trng.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_TRNG TRNG
 * @brief TRNG Driver Library
 * @{
 */

#if (LL_TRNG_ENABLE == DDL_ON)

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
#define IS_TRNG_SHIFT_CNT(x)                                                   \
(   ((x) == TRNG_SHIFT_CNT32)                   ||                             \
    ((x) == TRNG_SHIFT_CNT64)                   ||                             \
    ((x) == TRNG_SHIFT_CNT128)                  ||                             \
    ((x) == TRNG_SHIFT_CNT256))

#define IS_RNG_RELOAD_INIT_VAL_EN(x)                                           \
(   ((x) == TRNG_RELOAD_INIT_VAL_ENABLE)        ||                             \
    ((x) == TRNG_RELOAD_INIT_VAL_DISABLE))

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
 * @brief  Initializes TRNG.
 * @param  [in] u32ShiftCount           TRNG shift control. This parameter can be a value of @ref TRNG_Shift_Ctrl
 *   @arg  TRNG_SHIFT_CNT32:            Shift 32 times when capturing random noise.
 *   @arg  TRNG_SHIFT_CNT64:            Shift 64 times when capturing random noise.
 *   @arg  TRNG_SHIFT_CNT128:           Shift 128 times when capturing random noise.
 *   @arg  TRNG_SHIFT_CNT256:           Shift 256 times when capturing random noise.
 * @param  [in] u32ReloadInitValueEn    Enable or disable load new initial value.
 *                                      This parameter can be a value of @ref TRNG_Reload_Init_Value
 *   @arg  TRNG_RELOAD_INIT_VAL_ENABLE:  Enable load new initial value.
 *   @arg  TRNG_RELOAD_INIT_VAL_DISABLE: Disable load new initial value.
 * @retval None
 */
void TRNG_Init(uint32_t u32ShiftCount, uint32_t u32ReloadInitValueEn)
{
    DDL_ASSERT(IS_TRNG_SHIFT_CNT(u32ShiftCount));
    DDL_ASSERT(IS_RNG_RELOAD_INIT_VAL_EN(u32ReloadInitValueEn));
    WRITE_REG32(CM_TRNG->MR, u32ShiftCount | u32ReloadInitValueEn);
}

/**
 * @brief  Start TRNG and get random number.
 * @param  [out] pu32Random             The destination buffer to store the random number.
 * @param  [in]  u8RandomLen            The size(in word) of the destination buffer.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          Works timeout.
 *           - LL_ERR_INVD_PARAM:       pu32Random == NULL or u8RandomLen == 0
 */
int32_t TRNG_GenerateRandom(uint32_t *pu32Random, uint8_t u8RandomLen)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    __IO uint32_t u32TimeCount = TRNG_TIMEOUT;

    if ((pu32Random != NULL) && (u8RandomLen > 0U)) {
        /* Enable TRNG circuit. */
        WRITE_REG32(bCM_TRNG->CR_b.EN, 1U);
        /* Start TRNG */
        WRITE_REG32(bCM_TRNG->CR_b.RUN, 1U);
        /* Wait generating done. */
        i32Ret = LL_ERR_TIMEOUT;
        while (u32TimeCount-- != 0UL) {
            if (READ_REG32(bCM_TRNG->CR_b.RUN) == 0U) {
                i32Ret = LL_OK;
                break;
            }
        }

        if (i32Ret == LL_OK) {
            /* Get the random number. */
            pu32Random[0U] = READ_REG32(CM_TRNG->DR0);
            if (u8RandomLen > 1U) {
                pu32Random[1U] = READ_REG32(CM_TRNG->DR1);
            }
        } else {
            /* Stop TRNG */
            WRITE_REG32(bCM_TRNG->CR_b.RUN, 0U);
        }
        /* Disable TRNG circuit. */
        CLR_REG32_BIT(CM_TRNG->CR, TRNG_CR_EN);
    }

    return i32Ret;
}

/**
 * @brief  Start TRNG
 * @param  None
 * @retval None
 */
void TRNG_Start(void)
{
    /* Enable TRNG circuit. */
    WRITE_REG32(bCM_TRNG->CR_b.EN, 1U);
    /* Start TRNG */
    WRITE_REG32(bCM_TRNG->CR_b.RUN, 1U);
}

/**
 * @brief  Get random number.
 * @param  [out] pu32Random             The destination buffer to store the random number.
 * @param  [in]  u8RandomLen            The size(in word) of the destination buffer.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pu32Random == NULL or u8RandomLen == 0
 */
int32_t TRNG_GetRandom(uint32_t *pu32Random, uint8_t u8RandomLen)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((pu32Random != NULL) && (u8RandomLen > 0U)) {
        /* Get the random number. */
        pu32Random[0U] = READ_REG32(CM_TRNG->DR0);
        if (u8RandomLen > 1U) {
            pu32Random[1U] = READ_REG32(CM_TRNG->DR1);
        }
        /* Disable TRNG circuit. */
        CLR_REG32_BIT(CM_TRNG->CR, TRNG_CR_EN);

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @}
 */

#endif /* LL_TRNG_ENABLE */

/**
 * @}
 */

/**
* @}
*/
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
