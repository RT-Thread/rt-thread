/**
 *******************************************************************************
 * @file  hc32f4a0_mau.h
 * @brief This file contains all the functions prototypes of the MAU driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Hexiao          First version
   2020-07-15       Hexiao          Modify MAU_SqrtStartCmd to MAU_SqrtStart
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
#ifndef __HC32F4A0_MAU_H__
#define __HC32F4A0_MAU_H__

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
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_MAU
 * @{
 */

#if (DDL_MAU_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup MAU_Global_Macros MAU Global Macros
 * @{
 */

#define MAU_SQRT_TIMEOUT               (HCLK_VALUE / 10000UL)/* About 1mS timeout */
#define MAU_SQRT_OUTPUT_LSHIFT_MAX     (16U)
#define MAU_SIN_Q15_SCALAR             (0x8000UL)
#define MAU_SIN_ANGIDX_TOTAL           (0x1000UL)

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
 * @addtogroup MAU_Global_Functions
 * @{
 */

void MAU_SqrtInit(M4_MAU_TypeDef *MAUx, uint8_t u8LShBitsNumber, en_functional_state_t enIntNewState);
void MAU_SqrtDeInit(M4_MAU_TypeDef *MAUx);

void MAU_SqrtResultLShiftCfg(M4_MAU_TypeDef *MAUx, uint8_t u8LShBitsNumber);
void MAU_SqrtIntCmd(M4_MAU_TypeDef *MAUx, en_functional_state_t enNewState);
void MAU_SqrtWriteDataReg(M4_MAU_TypeDef *MAUx, uint32_t u32Radicand);
en_flag_status_t MAU_SqrtGetStatus(const M4_MAU_TypeDef *MAUx);
uint32_t MAU_SqrtReadDataReg(const M4_MAU_TypeDef *MAUx);
void MAU_SqrtStart(M4_MAU_TypeDef* MAUx);

en_result_t MAU_Sqrt(M4_MAU_TypeDef *MAUx, uint32_t u32Radicand, uint32_t *pu32Result);

int16_t MAU_Sin(M4_MAU_TypeDef *MAUx, uint16_t u16AngleIdx);

/**
 * @}
 */

#endif /* DDL_MAU_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_MAU_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
