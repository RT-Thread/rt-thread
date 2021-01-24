/**
 *******************************************************************************
 * @file  hc32f4a0_crc.h
 * @brief This file contains all the functions prototypes of the CRC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Heqb            First version
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
#ifndef __HC32F4A0_CRC_H__
#define __HC32F4A0_CRC_H__

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
 * @addtogroup DDL_CRC
 * @{
 */

#if (DDL_CRC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Bits definitions of CRC control register(CRC_CR). */
/**
 * @defgroup CRC_Global_Macros CRC Global Macros
 * @{
 */

/**
 * @defgroup CRC_Protocol_Control_Bit CRC Protocol Control Bit
 * @note: - CRC16 polynomial is X16 + X12 + X5 + 1
 *        - CRC32 polynomial is X32 + X26 + X23 + X22 + X16 + X12 + X11 + X10 + \
 *                              X8 + X7 + X5 + X4 + X2 + X + 1
 * @{
 */
#define CRC_CRC16           (0x0UL)
#define CRC_CRC32           (CRC_CR_CR)
/**
 * @}
 */

/**
 * @defgroup CRC_Flag_Bit_Mask CRC Flag Bit Mask
 * @{
 */
#define CRC_FLAG_MASK       (CRC_CR_FLAG)
/**
 * @}
 */

/**
 * @defgroup CRC_Bit_Width CRC Bit Width
 * @{
 */
#define CRC_BW_8            (8U)
#define CRC_BW_16           (16U)
#define CRC_BW_32           (32U)
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
 * @addtogroup CRC_Global_Functions
 * @{
 */
uint32_t CRC_Calculate(uint32_t u32CrcProtocol,
                       const void *pvData,
                       uint32_t u32InitVal,
                       uint32_t u32Length,
                       uint8_t u8BitWidth);

en_flag_status_t CRC_Check(uint32_t u32CrcProtocol,
                           uint32_t u32CheckSum,
                           const void *pvData,
                           uint32_t u32InitVal,
                           uint32_t u32Length,
                           uint8_t u8BitWidth);
/**
 * @}
 */

#endif /* DDL_CRC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_CRC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
