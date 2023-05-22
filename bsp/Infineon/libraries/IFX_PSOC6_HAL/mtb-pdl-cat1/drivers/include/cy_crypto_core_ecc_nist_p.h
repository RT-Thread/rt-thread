/***************************************************************************//**
* \file cy_crypto_core_ecc_nist_p.h
* \version 2.70
*
* \brief
*  This file provides constant and parameters for the API for the ECC
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


#if !defined (CY_CRYPTO_CORE_NIST_P_H)
#define CY_CRYPTO_CORE_NIST_P_H

#include "cy_device.h"

#if defined (CY_IP_MXCRYPTO)

#include "cy_crypto_core_ecc.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if defined (CY_CRYPTO_CFG_ECP_C)

#if (CPUSS_CRYPTO_VU == 1)

void Cy_Crypto_Core_EC_NistP_SetMode(uint32_t bitsize);
void Cy_Crypto_Core_EC_NistP_SetRedAlg(cy_en_crypto_ecc_red_mul_algs_t alg);

/**
* \addtogroup group_crypto_lld_asymmetric_functions
* \{
*/
cy_en_crypto_status_t Cy_Crypto_Core_EC_NistP_PointMultiplication(CRYPTO_Type *base,
    cy_en_crypto_ecc_curve_id_t curveID,
    const uint8_t *ecpGX,
    const uint8_t *ecpGY,
    const uint8_t *ecpD,
    uint8_t *ecpQX,
    uint8_t *ecpQY);
/** \} group_crypto_lld_asymmetric_functions */

void Cy_Crypto_Core_EC_MulMod( CRYPTO_Type *base, uint32_t z, uint32_t a, uint32_t b, uint32_t size);
void Cy_Crypto_Core_EC_DivMod( CRYPTO_Type *base, uint32_t z, uint32_t a, uint32_t b, uint32_t size);
void Cy_Crypto_Core_EC_SquareMod( CRYPTO_Type *base, uint32_t z, uint32_t a, uint32_t size);
void Cy_Crypto_Core_EC_Bar_MulRed(CRYPTO_Type *base, uint32_t z, uint32_t x, uint32_t size);

void Cy_Crypto_Core_EC_AddMod( CRYPTO_Type *base, uint32_t z, uint32_t a, uint32_t b);
void Cy_Crypto_Core_EC_SubMod( CRYPTO_Type *base, uint32_t z, uint32_t a, uint32_t b);
void Cy_Crypto_Core_EC_HalfMod( CRYPTO_Type *base, uint32_t z, uint32_t a);

void Cy_Crypto_Core_JacobianEcAdd(CRYPTO_Type *base, uint32_t s_x, uint32_t s_y, uint32_t s_z, uint32_t t_x, uint32_t t_y, uint32_t size);
void Cy_Crypto_Core_JacobianEcDouble(CRYPTO_Type *base, uint32_t s_x, uint32_t s_y, uint32_t s_z, uint32_t size);
void Cy_Crypto_Core_JacobianEcScalarMul(CRYPTO_Type *base, uint32_t s_x, uint32_t s_y, uint32_t d, uint32_t size);

void Cy_Crypto_Core_JacobianTransform(CRYPTO_Type *base, uint32_t s_x, uint32_t s_y, uint32_t s_z);
void Cy_Crypto_Core_JacobianInvTransform(CRYPTO_Type *base, uint32_t s_x, uint32_t s_y, uint32_t s_z, uint32_t size);

void Cy_Crypto_Core_EC_NistP_PointMul(CRYPTO_Type *base, uint32_t p_x, uint32_t p_y, uint32_t p_d, uint32_t p_order, uint32_t bitsize);

#endif /* #if (CPUSS_CRYPTO_VU == 1) */

#endif /* defined (CY_CRYPTO_CFG_ECP_C) */

#if defined(__cplusplus)
}
#endif

#endif /* #if defined (CY_IP_MXCRYPTO) */

#endif /* #if !defined (CY_CRYPTO_CORE_NIST_P_H) */


/* [] END OF FILE */
