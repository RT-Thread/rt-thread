/***************************************************************************//**
* \file cy_crypto_core_crc_v1.h
* \version 2.70
*
* \brief
*  This file provides the headers for CRC API
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


#if !defined (CY_CRYPTO_CORE_CRC_V1_H)
#define CY_CRYPTO_CORE_CRC_V1_H

#include "cy_crypto_common.h"

#if defined(CY_IP_MXCRYPTO) && defined(CY_CRYPTO_CFG_HW_V1_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_CRC == 1) && defined(CY_CRYPTO_CFG_CRC_C)

cy_en_crypto_status_t Cy_Crypto_Core_V1_Crc_Init(CRYPTO_Type *base,
                                        uint32_t polynomial,
                                        uint32_t dataReverse,
                                        uint32_t dataXor,
                                        uint32_t remReverse,
                                        uint32_t remXor);

cy_en_crypto_status_t Cy_Crypto_Core_V1_Crc(CRYPTO_Type *base,
                                        uint32_t *crc,
                                        void      const *data,
                                        uint32_t  dataSize,
                                        uint32_t  lfsrInitState);

/* The new partial calculation interface. */
cy_en_crypto_status_t Cy_Crypto_Core_V1_Crc_CalcInit(CRYPTO_Type *base,
                                        uint32_t width,
                                        uint32_t polynomial,
                                        uint32_t dataReverse,
                                        uint32_t dataXor,
                                        uint32_t remReverse,
                                        uint32_t remXor,
                                        uint32_t lfsrInitState);

cy_en_crypto_status_t Cy_Crypto_Core_V1_Crc_CalcStart(CRYPTO_Type *base, uint32_t width, uint32_t  lfsrInitState);

cy_en_crypto_status_t Cy_Crypto_Core_V1_Crc_CalcPartial(CRYPTO_Type *base, void const *data, uint32_t  dataSize);

cy_en_crypto_status_t Cy_Crypto_Core_V1_Crc_CalcFinish(CRYPTO_Type *base, uint32_t width, uint32_t *crc);

cy_en_crypto_status_t Cy_Crypto_Core_V1_Crc_Calc(CRYPTO_Type *base,
                                        uint32_t  width,
                                        uint32_t *crc,
                                        void      const *data,
                                        uint32_t  dataSize);

#endif /* (CPUSS_CRYPTO_CRC == 1) && defined(CY_CRYPTO_CFG_CRC_C) */

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_IP_MXCRYPTO) && defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */

#endif /* #if !defined (CY_CRYPTO_CORE_CRC_V1_H) */



/* [] END OF FILE */
