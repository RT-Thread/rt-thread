/**
 *******************************************************************************
 * @file  stl_test_interrupt.h
 * @brief This file contains all the functions prototypes of the interrupt test.
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

#ifndef __STL_TEST_INTERRUPT_H__
#define __STL_TEST_INTERRUPT_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "stl_common.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup STL_IEC60730
 * @{
 */

/**
 * @addtogroup STL_IEC60730_Interrupt
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
*******************************************************************************/
/**
 * @defgroup STL_IEC60730_Interrupt_Global_Type STL IEC60730 Interrupt Global Type
 * @{
 */
typedef struct stc_stl_int_params {
    uint32_t u32FreqInitVal;
    uint32_t u32FreqLowerVal;
    uint32_t u32FreqUpperVal;
    uint32_t u32PrivateParam;
} stc_stl_int_params_t;
/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup STL_IEC60730_Interrupt_Global_Functions
 * @{
 */
uint32_t STL_IntRuntimeTableInit(stc_stl_int_params_t *pstcParamsTable, uint32_t u32TableSize);
uint32_t STL_IntRuntimeTest(void);
void STL_IntUpdateCount(uint8_t u8ParamIndex);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
{
#endif


#endif /* __STL_TEST_INTERRUPT_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
