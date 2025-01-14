/**
 *******************************************************************************
 * @file  hc32_ll_trng.c
 * @brief This file provides firmware functions to manage the True Random
 *        Number Generator(TRNG).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             API fixed: TRNG_Init()
   2023-06-30       CDT             API fixed: rewrite TRNG_GenerateRandom() to Support get multiple random data
                                    API optimized for better random numbers: TRNG_GenerateRandom(), TRNG_GetRandom()
                                    Add TRNG_Cmd,TRNG_DeInit functions and optimize TRNG_Start function
   2023-09-30       CDT             Optimize the processing of discarded data and enable TRNG in TRNG_Init()
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
 * @brief  De-initializes TRNG.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          Works timeout.
 */
int32_t TRNG_DeInit(void)
{
    int32_t i32Ret = LL_ERR_TIMEOUT;
    __IO uint32_t u32TimeCount = TRNG_TIMEOUT;

    /* Wait generating done */
    while (u32TimeCount-- != 0UL) {
        if (READ_REG32(bCM_TRNG->CR_b.RUN) == 0U) {
            i32Ret = LL_OK;
            break;
        }
    }
    if (i32Ret == LL_OK) {
        WRITE_REG32(CM_TRNG->CR,  0UL);
        WRITE_REG32(CM_TRNG->MR,  0x00000012UL);
    }

    return i32Ret;
}

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
    uint32_t au32Random[20U];

    DDL_ASSERT(IS_TRNG_SHIFT_CNT(u32ShiftCount));
    DDL_ASSERT(IS_RNG_RELOAD_INIT_VAL_EN(u32ReloadInitValueEn));
    WRITE_REG32(CM_TRNG->MR, u32ShiftCount | u32ReloadInitValueEn);
    /* Enable TRNG */
    SET_REG32_BIT(CM_TRNG->CR, TRNG_CR_EN);
    /* Discard the first 10 generated data (64bit), 20 for 32bit variable storage */
    (void)TRNG_GenerateRandom(au32Random, 20U);
}

/**
 * @brief  Start TRNG and get random number.
 * @param  [out] pu32Random             The destination buffer to store the random number.
 * @param  [in]  u32RandomLen           The size(in word) of the destination buffer.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          Works timeout.
 *           - LL_ERR_INVD_PARAM:       pu32Random == NULL or u8RandomLen == 0
 */
int32_t TRNG_GenerateRandom(uint32_t *pu32Random, uint32_t u32RandomLen)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    __IO uint32_t u32TimeCount = TRNG_TIMEOUT;
    uint32_t u32Count = 0U;

    if ((pu32Random != NULL) && (u32RandomLen > 0U)) {
        while (u32RandomLen != u32Count) {
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
                /* XOR with 0x55555555 for better random number */
                pu32Random[u32Count++] = READ_REG32(CM_TRNG->DR0) ^ 0x55555555UL;
                if (u32Count < u32RandomLen) {
                    pu32Random[u32Count++] = READ_REG32(CM_TRNG->DR1) ^ 0x55555555UL;
                }
            }
        }
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
    WRITE_REG32(bCM_TRNG->CR_b.RUN, 1U);
}

/**
 * @brief  TRNG function enable or disable.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TRNG_Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_TRNG->CR, TRNG_CR_EN);
    } else {
        CLR_REG32_BIT(CM_TRNG->CR, TRNG_CR_EN);
    }
}

/**
 * @brief  Get random number.
 * @param  [out] pu32Random             The destination buffer to store the random number.
 * @param  [in]  u8RandomLen            The size(in word) of the destination buffer.(MAX = 2U)
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pu32Random == NULL or u8RandomLen == 0
 */
int32_t TRNG_GetRandom(uint32_t *pu32Random, uint8_t u8RandomLen)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((pu32Random != NULL) && (u8RandomLen > 0U)) {
        /* Get the random number. */
        /* XOR with 0x55555555 for better random number */
        pu32Random[0U] = READ_REG32(CM_TRNG->DR0) ^ 0x55555555UL;
        if (u8RandomLen > 1U) {
            pu32Random[1U] = READ_REG32(CM_TRNG->DR1) ^ 0x55555555UL;
        }
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
