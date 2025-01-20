/**
 *******************************************************************************
 * @file  hc32_ll_aes.h
 * @brief This file contains all the functions prototypes of the AES driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
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
#ifndef __HC32_LL_AES_H__
#define __HC32_LL_AES_H__

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
 * @addtogroup LL_AES
 * @{
 */

#if (LL_AES_ENABLE == DDL_ON)

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

/**
 * @defgroup AES_Key_Size AES Key Size
 * @{
 */
#define AES_KEY_SIZE_16BYTE                 (16U)
#define AES_KEY_SIZE_24BYTE                 (24U)
#define AES_KEY_SIZE_32BYTE                 (32U)
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
int32_t AES_Encrypt(const uint8_t *pu8Plaintext, uint32_t u32PlaintextSize,
                    const uint8_t *pu8Key, uint8_t u8KeySize,
                    uint8_t *pu8Ciphertext);

int32_t AES_Decrypt(const uint8_t *pu8Ciphertext, uint32_t u32CiphertextSize,
                    const uint8_t *pu8Key, uint8_t u8KeySize,
                    uint8_t *pu8Plaintext);

int32_t AES_DeInit(void);
/**
 * @}
 */

#endif /* LL_AES_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_AES_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
