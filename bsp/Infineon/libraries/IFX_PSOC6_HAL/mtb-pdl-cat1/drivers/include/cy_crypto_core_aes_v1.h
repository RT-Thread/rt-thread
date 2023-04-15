/***************************************************************************//**
* \file cy_crypto_core_aes_v1.h
* \version 2.70
*
* \brief
*  This file provides constant and parameters for the API for the AES method
*  in the Crypto driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/


#if !defined (CY_CRYPTO_CORE_AES_V1_H)
#define CY_CRYPTO_CORE_AES_V1_H

#include "cy_crypto_common.h"

#if defined(CY_IP_MXCRYPTO) && defined(CY_CRYPTO_CFG_HW_V1_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_AES_C)

void Cy_Crypto_Core_V1_Aes_ProcessBlock(CRYPTO_Type *base,
                            cy_stc_crypto_aes_state_t const *aesState,
                            cy_en_crypto_dir_mode_t dirMode,
                            uint32_t *dstBlock,
                            uint32_t const *srcBlock);

void Cy_Crypto_Core_V1_Aes_Xor(CRYPTO_Type *base,
                            cy_stc_crypto_aes_state_t const *aesState,
                            uint32_t *dstBlock,
                            uint32_t const *src0Block,
                            uint32_t const *src1Block);

cy_en_crypto_status_t Cy_Crypto_Core_V1_Aes_Free(CRYPTO_Type *base, cy_stc_crypto_aes_state_t *aesState);

cy_en_crypto_status_t Cy_Crypto_Core_V1_Aes_Init(CRYPTO_Type *base,
                                                 uint8_t const *key,
                                                 cy_en_crypto_aes_key_length_t keyLength,
                                                 cy_stc_crypto_aes_state_t *aesState,
                                                 cy_stc_crypto_aes_buffers_t *aesBuffers);

cy_en_crypto_status_t Cy_Crypto_Core_V1_Aes_Ecb(CRYPTO_Type *base,
                                                cy_en_crypto_dir_mode_t dirMode,
                                                uint8_t *dst,
                                                uint8_t const *src,
                                                cy_stc_crypto_aes_state_t *aesState);

#if defined(CY_CRYPTO_CFG_CIPHER_MODE_CBC)
cy_en_crypto_status_t Cy_Crypto_Core_V1_Aes_Cbc(CRYPTO_Type *base,
                                                cy_en_crypto_dir_mode_t dirMode,
                                                uint32_t srcSize,
                                                uint8_t *ivPtr,
                                                uint8_t *dst,
                                                uint8_t const *src,
                                                cy_stc_crypto_aes_state_t *aesState);
#endif /* defined(CY_CRYPTO_CFG_CIPHER_MODE_CBC) */

#if defined(CY_CRYPTO_CFG_CIPHER_MODE_CFB)
cy_en_crypto_status_t Cy_Crypto_Core_V1_Aes_Cfb(CRYPTO_Type *base,
                                                cy_en_crypto_dir_mode_t dirMode,
                                                uint32_t srcSize,
                                                uint8_t *ivPtr,
                                                uint8_t *dst,
                                                uint8_t const *src,
                                                cy_stc_crypto_aes_state_t *aesState);
#endif /* defined(CY_CRYPTO_CFG_CIPHER_MODE_CFB) */

#if defined(CY_CRYPTO_CFG_CIPHER_MODE_CTR)
cy_en_crypto_status_t Cy_Crypto_Core_V1_Aes_Ctr(CRYPTO_Type *base,
                                                uint32_t srcSize,
                                                uint32_t *srcOffset,
                                                uint8_t *ivPtr,
                                                uint8_t *streamBlock,
                                                uint8_t *dst,
                                                uint8_t const *src,
                                                cy_stc_crypto_aes_state_t *aesState);
#endif /* defined(CY_CRYPTO_CFG_CIPHER_MODE_CTR) */


#endif /* (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_AES_C) */

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_IP_MXCRYPTO) && defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */

#endif /* #if !defined (CY_CRYPTO_CORE_AES_V1_H) */


/* [] END OF FILE */
