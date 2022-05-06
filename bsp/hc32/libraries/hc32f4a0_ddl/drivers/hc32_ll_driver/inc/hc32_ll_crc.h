/**
 *******************************************************************************
 * @file  hc32_ll_crc.h
 * @brief This file contains all the functions prototypes of the CRC driver
 *        library.
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
#ifndef __HC32_LL_CRC_H__
#define __HC32_LL_CRC_H__

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
 * @addtogroup LL_CRC
 * @{
 */

#if (LL_CRC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CRC_Global_Types CRC Global Types
 * @{
 */

/**
 * @brief CRC initialization structure definition
 */
typedef struct {
    uint32_t u32Protocol;   /*!< Specifies CRC Protocol.
                                 This parameter can be a value of @ref CRC_Protocol_Control_Bit */
    uint32_t u32InitValue;  /*!< Specifies initial CRC value and value upper 16 bit is ignored when using CRC16.
                                 This parameter can be a value of @ref CRC_Initial_Value */
} stc_crc_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CRC_Global_Macros CRC Global Macros
 * @{
 */

/**
 * @defgroup CRC_Protocol_Control_Bit CRC Protocol Control Bit
 * @note: - CRC16 polynomial is X^16 + X^12 + X^5 + 1
 *        - CRC32 polynomial is X^32 + X^26 + X^23 + X^22 + X^16 + X^12 + X^11 + \
 *                              X^10 + X^8  + X^7  + X^5  + X^4  + X^2  + X + 1
 * @{
 */
#define CRC_CRC16                   (0x0UL)
#define CRC_CRC32                   (CRC_CR_CR)
/**
 * @}
 */

/**
 * @defgroup CRC_Initial_Value CRC Initial Value
 * @{
 */
#define CRC16_INIT_VALUE            (0xFFFFUL)
#define CRC32_INIT_VALUE            (0xFFFFFFFFUL)
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
int32_t CRC_StructInit(stc_crc_init_t *pstcCrcInit);
int32_t CRC_Init(const stc_crc_init_t *pstcCrcInit);
void CRC_DeInit(void);

en_flag_status_t CRC_GetResultStatus(void);

uint32_t CRC_AccumulateData8(const uint8_t au8Data[], uint32_t u32Len);
uint32_t CRC_AccumulateData16(const uint16_t au16Data[], uint32_t u32Len);
uint32_t CRC_AccumulateData32(const uint32_t au32Data[], uint32_t u32Len);

uint32_t CRC_CalculateData8(uint32_t u32InitValue, const uint8_t au8Data[], uint32_t u32Len);
uint32_t CRC_CalculateData16(uint32_t u32InitValue, const uint16_t au16Data[], uint32_t u32Len);
uint32_t CRC_CalculateData32(uint32_t u32InitValue, const uint32_t au32Data[], uint32_t u32Len);

en_flag_status_t CRC_CheckData8(uint32_t u32InitValue, const uint8_t au8Data[],
                                uint32_t u32Len, uint32_t u32ExpectValue);
en_flag_status_t CRC_CheckData16(uint32_t u32InitValue, const uint16_t au16Data[],
                                 uint32_t u32Len, uint32_t u32ExpectValue);
en_flag_status_t CRC_CheckData32(uint32_t u32InitValue, const uint32_t au32Data[],
                                 uint32_t u32Len, uint32_t u32ExpectValue);

/**
 * @}
 */

#endif /* LL_CRC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_CRC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
