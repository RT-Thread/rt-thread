/***************************************************************************//**
* \file cy_crypto_core_des_v1.c
* \version 2.70
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

#if defined(CY_IP_MXCRYPTO)

#include "cy_crypto_core_des_v1.h"

#if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_DES == 1) && defined(CY_CRYPTO_CFG_DES_C)

#include "cy_crypto_core_mem_v1.h"
#include "cy_crypto_core_hw_v1.h"
#include "cy_syslib.h"

#define CY_CRYPTO_DES_WEAK_KEY_COUNT   (16u)
#define CY_CRYPTO_DES_KEY_BYTE_LENGTH  (8u)

typedef struct
{
    uint32_t block0[CY_CRYPTO_DES_KEY_BYTE_LENGTH / 4u];
    uint32_t block1[CY_CRYPTO_DES_KEY_BYTE_LENGTH / 4u];
    uint32_t key[(CY_CRYPTO_DES_KEY_BYTE_LENGTH / 4u) * 3u ];
} cy_stc_crypto_des_buffers_t;

typedef enum
{
    CY_CRYPTO_DES_MODE_SINGLE = 0,
    CY_CRYPTO_DES_MODE_TRIPLE = 1
} cy_en_crypto_des_mode_t;

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

static void Cy_Crypto_Core_V1_Des_ProcessBlock(CRYPTO_Type *base,
                                     cy_en_crypto_des_mode_t desMode,
                                     cy_en_crypto_dir_mode_t dirMode,
                                     uint32_t const *key,
                                     uint32_t const *dstBlock,
                                     uint32_t const *srcBlock);

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Des_ProcessBlock
****************************************************************************//**
*
* Performs the DES or TDES block cipher.
* All addresses must be 4Byte aligned,
* srcBlock could overlap dstBlock.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param desMode
* DES cipher operation mode.
*
* \param dirMode
* One of CRYPTO_ENCRYPT or CRYPTO_DECRYPT.
*
* \param key
* The pointer to the encryption/decryption key.
*
* \param dstBlock
* The pointer to the cipher text.
*
* \param srcBlock
* The pointer to the plain text. Must be 4-Byte aligned!
*
*******************************************************************************/
static void Cy_Crypto_Core_V1_Des_ProcessBlock(CRYPTO_Type *base,
                                     cy_en_crypto_des_mode_t desMode,
                                     cy_en_crypto_dir_mode_t dirMode,
                                     uint32_t const *key,
                                     uint32_t const *dstBlock,
                                     uint32_t const *srcBlock)
{
    uint8_t const cy_desCommands[2][2] = {
        { CY_CRYPTO_V1_DES_BLOCK_OPC,  CY_CRYPTO_V1_DES_BLOCK_INV_OPC  },   /*  DES mode */
        { CY_CRYPTO_V1_TDES_BLOCK_OPC, CY_CRYPTO_V1_TDES_BLOCK_INV_OPC }    /* TDES mode */
    };

    Cy_Crypto_SetReg3Instr(base,
                          (uint32_t)key,
                          (uint32_t)srcBlock,
                          (uint32_t)dstBlock);

    /* Issue the DES_BLOCK instruction */
    Cy_Crypto_Run3ParamInstr(base,
                             cy_desCommands[(uint8_t)desMode][(uint8_t)dirMode],
                             CY_CRYPTO_RSRC0_SHIFT,
                             CY_CRYPTO_RSRC4_SHIFT,
                             CY_CRYPTO_RSRC8_SHIFT);

    /* Wait until the AES instruction is complete */
    while (0uL != _FLD2VAL(CRYPTO_STATUS_DES_BUSY, REG_CRYPTO_STATUS(base)))
    {
    }
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Des
****************************************************************************//**
*
* Performs DES operation on a Single Block. All addresses must be 4-Byte aligned.
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
* The pointer to the encryption/decryption key.
*
* \param dst
* The pointer to a destination cipher block.
*
* \param src
* The pointer to a source block.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V1_Des(CRYPTO_Type *base,
                                        cy_en_crypto_dir_mode_t dirMode,
                                        uint8_t const *key,
                                        uint8_t *dst,
                                        uint8_t const *src)
{
    uint32_t i;
    cy_en_crypto_status_t status = CY_CRYPTO_SUCCESS;

    cy_stc_crypto_des_buffers_t *desBuffers = (cy_stc_crypto_des_buffers_t *)((void *)Cy_Crypto_Core_GetVuMemoryAddress(base));

    /* Check weak keys */
    for (i = 0U; i < CY_CRYPTO_DES_WEAK_KEY_COUNT; i++)
    {
        if (Cy_Crypto_Core_V1_MemCmp(base, key, (uint8_t const *)cy_desWeakKeys[i], CY_CRYPTO_DES_KEY_BYTE_LENGTH) == 0U)
        {
            status = CY_CRYPTO_DES_WEAK_KEY;
            break;
        }
    }

    Cy_Crypto_Core_V1_MemCpy(base, desBuffers->key,    key, CY_CRYPTO_DES_KEY_BYTE_LENGTH);
    Cy_Crypto_Core_V1_MemCpy(base, desBuffers->block0, src, CY_CRYPTO_DES_KEY_BYTE_LENGTH);

    Cy_Crypto_Core_V1_Des_ProcessBlock(base, CY_CRYPTO_DES_MODE_SINGLE, dirMode,
        (uint32_t const *)desBuffers->key, (uint32_t const *)desBuffers->block1, (uint32_t const *)desBuffers->block0);

    Cy_Crypto_Core_V1_MemCpy(base, dst, desBuffers->block1, CY_CRYPTO_DES_KEY_BYTE_LENGTH);

    return (status);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Tdes
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
cy_en_crypto_status_t Cy_Crypto_Core_V1_Tdes(CRYPTO_Type *base,
                                        cy_en_crypto_dir_mode_t dirMode,
                                        uint8_t const *key,
                                        uint8_t *dst,
                                        uint8_t const *src)
{
    uint32_t i;
    cy_en_crypto_status_t status = CY_CRYPTO_SUCCESS;

    cy_stc_crypto_des_buffers_t *desBuffers = (cy_stc_crypto_des_buffers_t *)((void *)Cy_Crypto_Core_GetVuMemoryAddress(base));

    /* Check weak keys */
    for (i = 0U; i < CY_CRYPTO_DES_WEAK_KEY_COUNT; i++)
    {
        for (uint32_t keynum=0U; keynum < (CY_CRYPTO_TDES_KEY_SIZE / CY_CRYPTO_DES_KEY_SIZE); keynum++)
        {
            if (Cy_Crypto_Core_V1_MemCmp(base, &(key[keynum * CY_CRYPTO_DES_KEY_BYTE_LENGTH]), (uint8_t const *)cy_desWeakKeys[i], CY_CRYPTO_DES_KEY_BYTE_LENGTH) == 0U)
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

    Cy_Crypto_Core_V1_MemCpy(base, desBuffers->key,    key, CY_CRYPTO_DES_KEY_BYTE_LENGTH * 3U);
    Cy_Crypto_Core_V1_MemCpy(base, desBuffers->block0, src, CY_CRYPTO_DES_KEY_BYTE_LENGTH);

    Cy_Crypto_Core_V1_Des_ProcessBlock(base, CY_CRYPTO_DES_MODE_TRIPLE, dirMode,
        (uint32_t const *)desBuffers->key, (uint32_t const *)desBuffers->block1, (uint32_t const *)desBuffers->block0);

    Cy_Crypto_Core_V1_MemCpy(base, dst, desBuffers->block1, CY_CRYPTO_DES_KEY_BYTE_LENGTH);

    return (status);
}

#endif /* (CPUSS_CRYPTO_DES == 1) && defined(CY_CRYPTO_CFG_DES_C) */

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */

#endif /* defined(CY_IP_MXCRYPTO) */


/* [] END OF FILE */
