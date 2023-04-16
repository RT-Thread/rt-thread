/***************************************************************************//**
* \file cy_crypto_core_rsa.h
* \version 2.70
*
* \brief
*  This file provides provides constant and parameters
*  for the API of the RSA in the Crypto block driver.
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

#if !defined (CY_CRYPTO_CORE_RSA_H)
#define CY_CRYPTO_CORE_RSA_H

#include "cy_device.h"

#if defined (CY_IP_MXCRYPTO)

#include "cy_crypto_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_VU == 1) && defined(CY_CRYPTO_CFG_RSA_C)

typedef cy_en_crypto_status_t (*cy_crypto_rsa_proc_func_t)(CRYPTO_Type *base,
                                              cy_stc_crypto_rsa_pub_key_t const *key,
                                              uint8_t const *message,
                                              uint32_t messageSize,
                                              uint8_t *processedMessage);

typedef cy_en_crypto_status_t (*cy_crypto_rsa_coef_func_t)(CRYPTO_Type *base,
                                              cy_stc_crypto_rsa_pub_key_t const *key);



cy_en_crypto_status_t Cy_Crypto_Core_Rsa_Proc(CRYPTO_Type *base,
                                              cy_stc_crypto_rsa_pub_key_t const *key,
                                              uint8_t const *message,
                                              uint32_t messageSize,
                                              uint8_t *processedMessage);

cy_en_crypto_status_t Cy_Crypto_Core_Rsa_Coef(CRYPTO_Type *base,
                                              cy_stc_crypto_rsa_pub_key_t const *key);

#if defined(CY_CRYPTO_CFG_RSA_VERIFY_ENABLED)
typedef cy_en_crypto_status_t (*cy_crypto_rsa_ver_func_t)(CRYPTO_Type *base,
                                              cy_en_crypto_rsa_ver_result_t *verResult,
                                              cy_en_crypto_sha_mode_t digestType,
                                              uint8_t const *digest,
                                              uint8_t const *decryptedSignature,
                                              uint32_t decryptedSignatureLength);

cy_en_crypto_status_t Cy_Crypto_Core_Rsa_Verify(CRYPTO_Type *base,
                            cy_en_crypto_rsa_ver_result_t *verResult,
                            cy_en_crypto_sha_mode_t digestType,
                            uint8_t const *digest,
                            uint8_t const *decryptedSignature,
                            uint32_t decryptedSignatureLength);

cy_en_crypto_status_t Cy_Crypto_Core_Rsa_Verify_Ext(CRYPTO_Type *base,
                            cy_en_crypto_rsa_ver_result_t *verResult,
                            cy_en_crypto_sha_mode_t digestType,
                            uint8_t const *digest,
                            uint32_t digestLength,
                            uint8_t const *decryptedSignature,
                            uint32_t decryptedSignatureLength);

#endif /* defined(CY_CRYPTO_CFG_RSA_VERIFY_ENABLED) */

#endif /* (CPUSS_CRYPTO_VU == 1) && defined(CY_CRYPTO_CFG_RSA_C) */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */

#endif /* #if !defined (CY_CRYPTO_CORE_RSA_H) */


/* [] END OF FILE */
