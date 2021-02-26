/**
 *******************************************************************************
 * @file  hc32f4a0_trng.h
 * @brief This file contains all the functions prototypes of the TRNG driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Heqb         First version
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
#ifndef __HC32F4A0_TRNG_H__
#define __HC32F4A0_TRNG_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_TRNG
 * @{
 */

#if (DDL_TRNG_ENABLE == DDL_ON)

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
 * @defgroup TRNG_Load_New_Value TRNG load new value
 * @{
 */
#define TRNG_RELOAD_ENABLE          (TRNG_MR_LOAD)            /* Enable load new initial values. */
#define TRNG_RELOAD_DISABLE         (0x00000000UL)            /* Disable load new initial values. */
/**
 * @}
 */

/**
 * @defgroup TRNG_Shift_Control TRNG Shift Control
 * @{
 */
#define TRNG_SHIFT_COUNT_32         (0x0000000CUL)            /* Shift 32 times when capturing random noise. */
#define TRNG_SHIFT_COUNT_64         (0x00000010UL)            /* Shift 64 times when capturing random noise. */
#define TRNG_SHIFT_COUNT_128        (0x00000014UL)            /* Shift 128 times when capturing random noise. */
#define TRNG_SHIFT_COUNT_256        (0x00000018UL)            /* Shift 256 times when capturing random noise. */
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
void TRNG_SetShiftCnt(uint32_t u32ShiftCount);
void TRNG_ReloadCmd(uint32_t u32ReloadCmd);

en_result_t TRNG_Generate(uint32_t au32Random[]);
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

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_TRNG_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
