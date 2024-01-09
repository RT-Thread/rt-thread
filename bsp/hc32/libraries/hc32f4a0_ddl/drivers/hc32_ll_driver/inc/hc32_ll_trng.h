/**
 *******************************************************************************
 * @file  hc32_ll_trng.h
 * @brief This file contains all the functions prototypes of the TRNG driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-06-30       CDT             Add TRNG_Cmd,TRNG_DeInit functions
                                    API optimized for better random numbers: TRNG_GenerateRandom()
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
#ifndef __HC32_LL_TRNG_H__
#define __HC32_LL_TRNG_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"
/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_TRNG
 * @{
 */

#if (LL_TRNG_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup TRNG_Global_Macros TRNG Global Macros
 * @{
 */

/**
 * @defgroup TRNG_Reload_Init_Value TRNG Reload Initial Value
 * @{
 */
#define TRNG_RELOAD_INIT_VAL_ENABLE     (TRNG_MR_LOAD)                /* Enable reload new initial value. */
#define TRNG_RELOAD_INIT_VAL_DISABLE    (0x0U)                        /* Disable reload new initial value. */
/**
 * @}
 */

/**
 * @defgroup TRNG_Shift_Ctrl TRNG Shift Control
 * @{
 */
#define TRNG_SHIFT_CNT32                (0x3UL << TRNG_MR_CNT_POS)    /* Shift 32 times when capturing random noise. */
#define TRNG_SHIFT_CNT64                (0x4UL << TRNG_MR_CNT_POS)    /* Shift 64 times when capturing random noise. */
#define TRNG_SHIFT_CNT128               (0x5UL << TRNG_MR_CNT_POS)    /* Shift 128 times when capturing random noise. */
#define TRNG_SHIFT_CNT256               (0x6UL << TRNG_MR_CNT_POS)    /* Shift 256 times when capturing random noise. */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup TRNG_Global_Functions
 * @{
 */
int32_t TRNG_DeInit(void);
void TRNG_Init(uint32_t u32ShiftCount, uint32_t u32ReloadInitValueEn);
int32_t TRNG_GenerateRandom(uint32_t *pu32Random, uint32_t u32RandomLen);

void TRNG_Start(void);
void TRNG_Cmd(en_functional_state_t enNewState);
int32_t TRNG_GetRandom(uint32_t *pu32Random, uint8_t u8RandomLen);
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

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_TRNG_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
