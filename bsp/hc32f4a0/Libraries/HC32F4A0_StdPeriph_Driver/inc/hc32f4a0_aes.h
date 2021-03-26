/**
 *******************************************************************************
 * @file  hc32f4a0_aes.h
 * @brief This file contains all the functions prototypes of the AES driver
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
#ifndef __HC32F4A0_AES_H__
#define __HC32F4A0_AES_H__

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
 * @addtogroup DDL_AES
 * @{
 */

#if (DDL_AES_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup AES_Global_Macros AES Global Macros
 * @{
 */

/* AES key length in bytes is 16. */
#define AES_BLOCK_LEN                 (16U)

/**
 * @defgroup AES_STATUS AES Start or Stop
 * @{
 */
#define AES_START                     (AES_CR_START)
#define AES_STOP                      (0x0UL)
/**
 * @}
 */

/**
 * @defgroup AES_KEY_SIZE AES Key Size
 * @{
 */
#define AES_KEY_SIZE_128BIT              (0UL << AES_CR_KEYSIZE_POS)
#define AES_KEY_SIZE_192BIT              (1UL << AES_CR_KEYSIZE_POS)
#define AES_KEY_SIZE_256BIT              (2UL << AES_CR_KEYSIZE_POS)
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
 * @addtogroup AES_Global_Functions
 * @{
 */
en_result_t AES_Encrypt(uint8_t au8Plaintext[],
                        uint32_t u32PlaintextSize,
                        const uint8_t *pu8Key,
                        uint8_t u8KeyLength,
                        uint8_t au8Ciphertext[]);

en_result_t AES_Decrypt(uint8_t au8Ciphertext[],
                        uint32_t u32CiphertextSize,
                        const uint8_t *pu8Key,
                        uint8_t u8KeyLength,
                        uint8_t au8Plaintext[]);
/**
 * @}
 */

#endif /* DDL_AES_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_AES_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
