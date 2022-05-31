/**
 *******************************************************************************
 * @file  stl_test_flash.h
 * @brief This file contains all the functions prototypes of the flash test.
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

#ifndef __STL_SW_CRC32_H__
#define __STL_SW_CRC32_H__

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
 * @addtogroup STL_IEC60730_CRC32
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
*******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup STL_IEC60730_CRC32_Global_Macros STL IEC60730 CRC32 Global Macros
 * @{
 */
#define STL_CRC32_INIT_VALUE    (0xFFFFFFFFUL)
/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/


/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup STL_IEC60730_CRC32_Global_Functions
 * @{
 */
uint32_t STL_CalculateCRC32Value(uint32_t u32Crc32Value, uint8_t *pu8Data, uint32_t u32Len);
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


#endif /* __STL_SW_CRC32_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
