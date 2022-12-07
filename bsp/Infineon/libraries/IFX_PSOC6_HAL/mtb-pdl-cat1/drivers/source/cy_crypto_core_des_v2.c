/***************************************************************************//**
* \file cy_crypto_core_des_v2.c
* \version 2.50
*
* \brief
*  This file provides the source code fro the API for the DES method
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

#include "cy_device.h"

#if defined (CY_IP_MXCRYPTO)

#include "cy_crypto_core_des_v2.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_DES == 1)

#include "cy_crypto_common.h"
#include "cy_crypto_core_hw_v2.h"
#include "cy_crypto_core_mem_v2.h"
#include "cy_syslib.h"

#define CY_CRYPTO_DES_WEAK_KEY_COUNT   (16U)
#define CY_CRYPTO_DES_KEY_BYTE_LENGTH  (8U)

/* Table with DES weak keys */
CY_ALIGN(4)
static uint8_t const cy_desWeakKeys[CY_CRYPTO_DES_WEAK_KEY_COUNT][CY_CRYPTO_DES_KEY_BYTE_LENGTH] =
{
    { 0x01u, 0x01u, 0x01u, 0x01u, 0x01u, 0x01u, 0x01u, 0x01u },
    { 0xFEu, 0xFEu, 0xFEu, 0xFEu, 0xFEu, 0xFEu, 0xFEu, 0xFEu },
    { 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x0Eu, 0x0Eu, 0x0Eu, 0x0Eu },
    { 0xE0u, 0xE0u, 0xE0u, 0xE0u, 0xF1u, 0xF1u, 0xF1u, 0xF1u },

    { 0x01u, 0x1Fu, 0x01u, 0x1Fu, 0x01u, 0x0Eu, 0x01u, 0x0Eu },
    { 0x1Fu, 0x01u, 0x1Fu, 0x01u, 0x0Eu, 0x01u, 0x0Eu, 0x01u },
    { 0x01u, 0xE0u, 0x01u, 0xE0u, 0x01u, 0xF1u, 0x01u, 0xF1u },
    { 0xE0u, 0x01u, 0xE0u, 0x01u, 0xF1u, 0x01u, 0xF1u, 0x01u },
    { 0x01u, 0xFEu, 0x01u, 0xFEu, 0x01u, 0xFEu, 0x01u, 0xFEu },
    { 0xFEu, 0x01u, 0xFEu, 0x01u, 0xFEu, 0x01u, 0xFEu, 0x01u },
    { 0x1Fu, 0xE0u, 0x1Fu, 0xE0u, 0x0Eu, 0xF1u, 0x0Eu, 0xF1u },
    { 0xE0u, 0x1Fu, 0xE0u, 0x1Fu, 0xF1u, 0x0Eu, 0xF1u, 0x0Eu },
    { 0x1Fu, 0xFEu, 0x1Fu, 0xFEu, 0x0Eu, 0xFEu, 0x0Eu, 0xFEu },
    { 0xFEu, 0x1Fu, 0xFEu, 0x1Fu, 0xFEu, 0x0Eu, 0xFEu, 0x0Eu },
    { 0xE0u, 0xFEu, 0xE0u, 0xFEu, 0xF1u, 0xFEu, 0xF1u, 0xFEu },
    { 0xFEu, 0xE0u, 0xFEu, 0xE0u, 0xFEu, 0xF1u, 0xFEu, 0xF1u }
};


/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Des
****************************************************************************//**
*
* Performs DES operation on a Single Block. All addresses must be 4-Byte aligned.
* Ciphertext (dst) may overlap with plaintext (src)
* This function is independent from the previous Crypto state.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param dirMode
* Can be \ref CY_CRYPTO_ENCRYPT or \ref CY_CRYPTO_DECRYPT
* (\ref cy_en_crypto_dir_mode_t)
*
* \param key
* The pointer to the encryption/decryption key.
*
* \param dst
* The pointer to a destination cipher block.
*
* \param src
* The pointer to a source data block.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Des(CRYPTO_Type *base,
                                        cy_en_crypto_dir_mode_t dirMode,
                                        uint8_t const *key,
                                        uint8_t *dst,
                                        uint8_t const *src)
{
    uint32_t i;
    cy_en_crypto_status_t status = CY_CRYPTO_SUCCESS;

    /* Check weak keys */
    for (i = 0U; i < CY_CRYPTO_DES_WEAK_KEY_COUNT; i++)
    {
        if (Cy_Crypto_Core_V2_MemCmp(base, key, (uint8_t const *)cy_desWeakKeys[i], CY_CRYPTO_DES_KEY_BYTE_LENGTH) == 0U)
        {
            status = CY_CRYPTO_DES_WEAK_KEY;
            break;
        }
    }

    /* Load key */
    Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD0, key, CY_CRYPTO_DES_KEY_BYTE_LENGTH);
    Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_KEY0, CY_CRYPTO_V2_RB_FF_LOAD0, CY_CRYPTO_DES_KEY_BYTE_LENGTH);

    Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD0, src, CY_CRYPTO_DES_KEY_BYTE_LENGTH);
    Cy_Crypto_Core_V2_FFStart(base,    CY_CRYPTO_V2_RB_FF_STORE, dst, CY_CRYPTO_DES_KEY_BYTE_LENGTH);

    Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_BLOCK0, CY_CRYPTO_V2_RB_FF_LOAD0, CY_CRYPTO_DES_KEY_BYTE_LENGTH);
    Cy_Crypto_Core_V2_Run(base, (uint32_t)((dirMode == CY_CRYPTO_ENCRYPT) ? (CY_CRYPTO_V2_DES_OPC) : (CY_CRYPTO_V2_DES_INV_OPC)));
    Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_FF_STORE, CY_CRYPTO_V2_RB_BLOCK1, CY_CRYPTO_DES_KEY_BYTE_LENGTH);

    return (status);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Tdes
****************************************************************************//**
*
* Performs TDES operation on a Single Block. All addresses must be 4-Byte aligned.
* Ciphertext (dstBlock) may overlap with plaintext (srcBlock)
* This function is independent from the previous Crypto state.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param dirMode
* Can be \ref CY_CRYPTO_ENCRYPT or \ref CY_CRYPTO_DECRYPT
* (\ref cy_en_crypto_dir_mode_t)
*
* \param key
* The pointer to the encryption/decryption keys.
*
* \param dst
* The pointer to a destination cipher block.
*
* \param src
* The pointer to a source data block.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Tdes(CRYPTO_Type *base,
                                        cy_en_crypto_dir_mode_t dirMode,
                                        uint8_t const *key,
                                        uint8_t *dst,
                                        uint8_t const *src)
{
    uint32_t i;
    cy_en_crypto_status_t status = CY_CRYPTO_SUCCESS;

    /* Check weak keys */
    for (i = 0U; i < CY_CRYPTO_DES_WEAK_KEY_COUNT; i++)
    {
    for (uint32_t keynum=0U; keynum < (CY_CRYPTO_TDES_KEY_SIZE / CY_CRYPTO_DES_KEY_SIZE); keynum++)
        {
            if (Cy_Crypto_Core_V2_MemCmp(base, &(key[keynum * CY_CRYPTO_DES_KEY_BYTE_LENGTH]), (uint8_t const *)cy_desWeakKeys[i], CY_CRYPTO_DES_KEY_BYTE_LENGTH) == 0U)
            {
                status = CY_CRYPTO_DES_WEAK_KEY;
                break;
            }
    }
        if (status == CY_CRYPTO_DES_WEAK_KEY)
    {
            break;
        }
    }

    /* Load keys */
    Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD0, key, CY_CRYPTO_DES_KEY_BYTE_LENGTH * 3U);
    Cy_Crypto_Core_V2_BlockMov  (base, CY_CRYPTO_V2_RB_KEY0, CY_CRYPTO_V2_RB_FF_LOAD0, CY_CRYPTO_DES_KEY_BYTE_LENGTH * 2U);
    Cy_Crypto_Core_V2_BlockMov  (base, CY_CRYPTO_V2_RB_KEY1, CY_CRYPTO_V2_RB_FF_LOAD0, CY_CRYPTO_DES_KEY_BYTE_LENGTH);

    Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD0, src, CY_CRYPTO_DES_KEY_BYTE_LENGTH);
    Cy_Crypto_Core_V2_FFStart   (base, CY_CRYPTO_V2_RB_FF_STORE, dst, CY_CRYPTO_DES_KEY_BYTE_LENGTH);

    Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_BLOCK0, CY_CRYPTO_V2_RB_FF_LOAD0, CY_CRYPTO_DES_KEY_BYTE_LENGTH);
    Cy_Crypto_Core_V2_Run(base, (uint32_t)((dirMode == CY_CRYPTO_ENCRYPT) ? (CY_CRYPTO_V2_TDES_OPC) : (CY_CRYPTO_V2_TDES_INV_OPC)));
    Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_FF_STORE, CY_CRYPTO_V2_RB_BLOCK1, CY_CRYPTO_DES_KEY_BYTE_LENGTH);

    return (status);
}

#endif /* #if (CPUSS_CRYPTO_DES == 1) */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */


/* [] END OF FILE */
