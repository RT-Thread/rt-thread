/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_trng.h
 **
 ** A detailed description is available at
 ** @link TrngGroup Trng description @endlink
 **
 **   - 2018-10-20  CDT First version for Device Driver Library of Trng.
 **
 ******************************************************************************/
#ifndef __HC32F460_TRNG_H__
#define __HC32F460_TRNG_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_TRNG_ENABLE == DDL_ON)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup TrngGroup True Random Number Generator(TRNG)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* The data register loads the new initial value from the random number
   generator before the random number is generated. */
typedef enum en_trng_load_ctrl
{
    TrngLoadNewInitValue_Disable = 0x0,     ///< Disable load new initial values.
    TrngLoadNewInitValue_Enable  = 0x1,     ///< Enable load new initial values.
} en_trng_load_ctrl_t;

/* Shift n times when capturing random noise. */
typedef enum en_trng_shift_cnt
{
    TrngShiftCount_32            = 0x3,     ///< Shift 32 times when capturing random noise.
    TrngShiftCount_64            = 0x4,     ///< Shift 64 times when capturing random noise.
    TrngShiftCount_128           = 0x5,     ///< Shift 128 times when capturing random noise.
    TrngShiftCount_256           = 0x6,     ///< Shift 256 times when capturing random noise.
} en_trng_shift_cnt_t;

/* TRNG initialization structure definition. */
typedef struct stc_trng_init
{
    en_trng_load_ctrl_t enLoadCtrl;         ///< @ref en_trng_load_ctrl_t.
    en_trng_shift_cnt_t enShiftCount;       ///< @ref en_trng_shift_cnt_t.
} stc_trng_init_t;

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

en_result_t TRNG_Init(const stc_trng_init_t *pstcInit);
void TRNG_DeInit(void);
en_result_t TRNG_Generate(uint32_t *pu32Random, uint8_t u8Length, uint32_t u32Timeout);

void TRNG_StartIT(void);
void TRNG_GetRandomNum(uint32_t *pu32Random, uint8_t u8Length);

//@} // TrngGroup

#ifdef __cplusplus
}
#endif

#endif /* DDL_TRNG_ENABLE */

#endif /* __HC32F460_TRNG_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
