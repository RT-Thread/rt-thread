/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_aes.h
 **
 ** A detailed description is available at
 ** @link AesGroup Aes description @endlink
 **
 **   - 2018-10-20  CDT First version for Device Driver Library of Aes.
 **
 ******************************************************************************/
#ifndef __HC32F460_AES_H__
#define __HC32F460_AES_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_AES_ENABLE == DDL_ON)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup AesGroup Advanced Encryption Standard(AES)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
 /* AES key length in bytes is 16. */
#define AES_KEYLEN                          ((uint8_t)16)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
en_result_t AES_Encrypt(const uint8_t *pu8Plaintext,
                        uint32_t u32PlaintextSize,
                        const uint8_t *pu8Key,
                        uint8_t *pu8Ciphertext);

en_result_t AES_Decrypt(const uint8_t *pu8Ciphertext,
                        uint32_t u32CiphertextSize,
                        const uint8_t *pu8Key,
                        uint8_t *pu8Plaintext);

//@} // AesGroup

#ifdef __cplusplus
}
#endif

#endif /* DDL_AES_ENABLE */

#endif /* __HC32F460_AES_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
