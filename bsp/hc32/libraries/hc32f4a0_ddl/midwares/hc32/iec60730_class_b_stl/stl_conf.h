/**
 *******************************************************************************
 * @file  stl_conf.h
 * @brief This file contains STL resource configure.
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

#ifndef __STL_CONF_H__
#define __STL_CONF_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "stl_bsp_conf.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup IEC60730_STL
 * @{
 */

/**
 * @addtogroup IEC60730_STL_Configure
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
*******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup IEC60730_STL_Configure_ROM_CRC32_Parameters IEC60730 STL Configure ROM CRC32 Parameters
 * @{
 */
#define STL_ROM_CRC32_START             (STL_ROM_START)
#define STL_ROM_CRC32_END               ((uint32_t)&__checksum - 1UL)
#define STL_ROM_CRC32_SIZE              (STL_ROM_CRC32_END - STL_ROM_CRC32_START + 1UL)
#define STL_ROM_CRC32_BLOCK_SIZE        (128UL)
#define STL_ROM_CRC32_CC_CHECKSUM       (__checksum)
/**
 * @}
 */

/**
 * @defgroup IEC60730_STL_Configure_RAM_Parameters IEC60730 STL Configure RAM Parameters
 * @{
 */
#define STL_MARCH_RAM_SIZE              (32UL)
#define STL_MARCH_RAM_WORDS             (STL_MARCH_RAM_SIZE >> 2)
#define STL_MARCH_RAM_BUF_SIZE          (16UL)
#define STL_MARCH_RAM_BUF_WORDS         (STL_MARCH_RAM_BUF_SIZE >> 2)

#define STL_MARCH_RAM_BCKGRND           (0x00000000UL)
#define STL_MARCH_RAM_INVBCKGRND        (0xFFFFFFFFUL)

#define STL_STACK_BOUNDARY_WORDS        (4UL)
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
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __STL_CONF_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
