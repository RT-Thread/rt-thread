/***************************************************************************//**
* \file cy_crypto_core_aes_v1.c
* \version 2.70
*
* \brief
*  This file provides the source code fro the API for the AES method
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

#include "cy_crypto_core_aes_v1.h"

#if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_AES_C)

#include "cy_crypto_core_hw_v1.h"
#include "cy_crypto_core_mem_v1.h"
#include "cy_syslib.h"

static void Cy_Crypto_Core_V1_Aes_InvKey(CRYPTO_Type *base, cy_stc_crypto_aes_state_t const *aesState);

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Aes_ProcessBlock
****************************************************************************//**
*
* Performs the AES block cipher.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param aesState
* The pointer to the AES state structure allocated by the user. The user
* must not modify anything in this structure.
*
* \param dirMode
* One of CRYPTO_ENCRYPT or CRYPTO_DECRYPT.
*
* \param dstBlock
* The pointer to the cipher text.
*
* \param srcBlock
* The pointer to the plain text. Must be 4-Byte aligned!
*
*******************************************************************************/
void Cy_Crypto_Core_V1_Aes_ProcessBlock(CRYPTO_Type *base,
                            cy_stc_crypto_aes_state_t const *aesState,
                            cy_en_crypto_dir_mode_t dirMode,
                            uint32_t *dstBlock,
                            uint32_t const *srcBlock)
{
    /* Set the key mode: 128, 192 or 256 Bit */
    REG_CRYPTO_AES_CTL(base) = (uint32_t)(_VAL2FLD(CRYPTO_AES_CTL_KEY_SIZE, (uint32_t)(aesState->keyLength)));

    Cy_Crypto_SetReg3Instr(base,
                           (CY_CRYPTO_DECRYPT == dirMode) ? (uint32_t)aesState->buffers->keyInv : (uint32_t)aesState->buffers->key,
                           (uint32_t)srcBlock,
                           (uint32_t)dstBlock);

    Cy_Crypto_Run3ParamInstr(base,
                            (CY_CRYPTO_DECRYPT == dirMode) ? CY_CRYPTO_V1_AES_BLOCK_INV_OPC : CY_CRYPTO_V1_AES_BLOCK_OPC,
                            CY_CRYPTO_RSRC0_SHIFT,
                            CY_CRYPTO_RSRC4_SHIFT,
                            CY_CRYPTO_RSRC12_SHIFT);

    /* Wait until the AES instruction is complete */
    while (0uL != _FLD2VAL(CRYPTO_STATUS_AES_BUSY, REG_CRYPTO_STATUS(base)))
    {
    }
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Aes_Xor
****************************************************************************//**
*
* Perform the XOR of two 16-Byte memory structures.
* All addresses must be 4-Byte aligned!
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param aesState
* The pointer to the AES state structure allocated by the user. The user
* must not modify anything in this structure.
*
* \param dstBlock
* The pointer to the memory structure with the XOR results.
*
* \param src0Block
* The pointer to the first memory structure. Must be 4-Byte aligned!
*
* \param src1Block
* The pointer to the second memory structure. Must be 4-Byte aligned!
*
*******************************************************************************/
void Cy_Crypto_Core_V1_Aes_Xor(CRYPTO_Type *base,
                            cy_stc_crypto_aes_state_t const *aesState,
                            uint32_t *dstBlock,
                            uint32_t const *src0Block,
                            uint32_t const *src1Block)
{
    /* Set the key mode: 128, 192 or 256 Bit */
    REG_CRYPTO_AES_CTL(base) = (uint32_t)(_VAL2FLD(CRYPTO_AES_CTL_KEY_SIZE, (uint32_t)(aesState->keyLength)));

    Cy_Crypto_SetReg3Instr(base,
                           (uint32_t)src0Block,
                           (uint32_t)src1Block,
                           (uint32_t)dstBlock);

    /* Issue the AES_XOR instruction */
    Cy_Crypto_Run3ParamInstr(base,
                             CY_CRYPTO_V1_AES_XOR_OPC,
                             CY_CRYPTO_RSRC0_SHIFT,
                             CY_CRYPTO_RSRC4_SHIFT,
                             CY_CRYPTO_RSRC8_SHIFT);

    /* Wait until the AES instruction is complete */
    while(0uL != _FLD2VAL(CRYPTO_STATUS_AES_BUSY, REG_CRYPTO_STATUS(base)))
    {
    }
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Aes_InvKey
****************************************************************************//**
*
* Calculates an inverse block cipher key from the block cipher key.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param aesState
* The pointer to the AES state structure allocated by the user. The user
* must not modify anything in this structure.
*
*******************************************************************************/
static void Cy_Crypto_Core_V1_Aes_InvKey(CRYPTO_Type *base, cy_stc_crypto_aes_state_t const *aesState)
{
    /* Set the key mode: 128, 192 or 256 Bit */
    REG_CRYPTO_AES_CTL(base) = (uint32_t)(_VAL2FLD(CRYPTO_AES_CTL_KEY_SIZE, (uint32_t)(aesState->keyLength)));

    /* Issue the AES_KEY instruction to prepare the key for decrypt operation */
    Cy_Crypto_SetReg2Instr(base, (uint32_t)aesState->buffers->key, (uint32_t)aesState->buffers->keyInv);

    Cy_Crypto_Run2ParamInstr(base,
                             CY_CRYPTO_V1_AES_KEY_OPC,
                             CY_CRYPTO_RSRC0_SHIFT,
                             CY_CRYPTO_RSRC8_SHIFT);

    /* Wait until the AES instruction is complete */
    while(0uL != _FLD2VAL(CRYPTO_STATUS_AES_BUSY, REG_CRYPTO_STATUS(base)))
    {
    }
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Aes_Init
****************************************************************************//**
*
* Sets AES mode and prepares an inverse key.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param key
* The pointer to the encryption/decryption key.
*
* \param keyLength
* \ref cy_en_crypto_aes_key_length_t
*
* \param aesState
* The pointer to the AES state structure allocated by the user. The user
* must not modify anything in this structure.
*
* \param aesBuffers
* The pointer to the memory buffers storage.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V1_Aes_Init(CRYPTO_Type *base,
                                                 uint8_t const *key,
                                                 cy_en_crypto_aes_key_length_t keyLength,
                                                 cy_stc_crypto_aes_state_t *aesState,
                                                 cy_stc_crypto_aes_buffers_t *aesBuffers)
{
    uint16_t keySize = CY_CRYPTO_AES_128_KEY_SIZE + ((uint16_t)keyLength * 8u);

    aesState->keyLength = keyLength;
    aesState->buffers = aesBuffers;

    Cy_Crypto_Core_V1_MemCpy(base, (uint8_t *)(aesState->buffers->key), key, keySize);

    Cy_Crypto_Core_V1_Aes_InvKey(base, aesState);

    return (CY_CRYPTO_SUCCESS);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Aes_Free
****************************************************************************//**
*
* Clears AES operation context.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param aesState
* The pointer to the AES state structure allocated by the user. The user
* must not modify anything in this structure.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V1_Aes_Free(CRYPTO_Type *base, cy_stc_crypto_aes_state_t *aesState)
{
    Cy_Crypto_Core_V1_MemSet(base, (void *)aesState->buffers, 0u, ((uint16_t)sizeof(cy_stc_crypto_aes_buffers_t)));
    Cy_Crypto_Core_V1_MemSet(base, (void *)aesState, 0u, ((uint16_t)sizeof(cy_stc_crypto_aes_state_t)));

    return (CY_CRYPTO_SUCCESS);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Aes_Ecb
****************************************************************************//**
*
* Performs an AES operation on one block.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param dirMode
* Can be \ref CY_CRYPTO_ENCRYPT or \ref CY_CRYPTO_DECRYPT
* (\ref cy_en_crypto_dir_mode_t).
*
* \param dst
* The pointer to a destination cipher block.
*
* \param src
* The pointer to a source block.
*
* \param aesState
* The pointer to the AES state structure allocated by the user. The user
* must not modify anything in this structure.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V1_Aes_Ecb(CRYPTO_Type *base,
                                            cy_en_crypto_dir_mode_t dirMode,
                                            uint8_t *dst,
                                            uint8_t const *src,
                                            cy_stc_crypto_aes_state_t *aesState)
{
    cy_stc_crypto_aes_buffers_t *aesBuffers = (cy_stc_crypto_aes_buffers_t*)aesState->buffers;

    Cy_Crypto_Core_V1_MemCpy(base, &aesBuffers->block0, src, CY_CRYPTO_AES_BLOCK_SIZE);

    Cy_Crypto_Core_V1_Aes_ProcessBlock(base, aesState, dirMode, (uint32_t*)&aesBuffers->block1, (uint32_t*)&aesBuffers->block0);

    Cy_Crypto_Core_V1_MemCpy(base, dst, &aesBuffers->block1, CY_CRYPTO_AES_BLOCK_SIZE);

    return (CY_CRYPTO_SUCCESS);
}

#if defined(CY_CRYPTO_CFG_CIPHER_MODE_CBC)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Aes_Cbc
****************************************************************************//**
*
* Performs AES operation on a plain text with Cipher Block Chaining (CBC).
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param dirMode
* Can be \ref CY_CRYPTO_ENCRYPT or \ref CY_CRYPTO_DECRYPT
* (\ref cy_en_crypto_dir_mode_t)
*
* \param srcSize
* The size of the source plain text.
*
* \param ivPtr
* The pointer to the initial vector.
*
* \param dst
* The pointer to a destination cipher text.
*
* \param src
* The pointer to a source plain text.
*
* \param aesState
* The pointer to the AES state structure allocated by the user. The user
* must not modify anything in this structure.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V1_Aes_Cbc(CRYPTO_Type *base,
                                            cy_en_crypto_dir_mode_t dirMode,
                                            uint32_t srcSize,
                                            uint8_t *ivPtr,
                                            uint8_t *dst,
                                            uint8_t const *src,
                                            cy_stc_crypto_aes_state_t *aesState)
{
    uint32_t size = srcSize;

    cy_stc_crypto_aes_buffers_t *aesBuffers = (cy_stc_crypto_aes_buffers_t*)aesState->buffers;
    uint32_t *srcBuff  = (uint32_t*)(&aesBuffers->block0);
    uint32_t *dstBuff  = (uint32_t*)(&aesBuffers->block1);
    uint32_t *tempBuff = (uint32_t*)(&aesBuffers->block2);

    cy_en_crypto_status_t tmpResult = CY_CRYPTO_SIZE_NOT_X16;

    /* Check whether the data size is multiple of CY_CRYPTO_AES_BLOCK_SIZE */
    if (0UL == (uint32_t)(size & (CY_CRYPTO_AES_BLOCK_SIZE - 1U)))
    {
        /* Copy the Initialization Vector to the local buffer because it changes during calculation */
        Cy_Crypto_Core_V1_MemCpy(base, tempBuff, ivPtr, CY_CRYPTO_AES_BLOCK_SIZE);

        if (CY_CRYPTO_DECRYPT == dirMode)
        {
            while (size != 0UL)
            {
                /* source message block */
                Cy_Crypto_Core_V1_MemCpy(base, srcBuff, src, CY_CRYPTO_AES_BLOCK_SIZE);

                Cy_Crypto_Core_V1_Aes_ProcessBlock(base, aesState, dirMode, dstBuff, srcBuff);
                Cy_Crypto_Core_V1_Aes_Xor(base, aesState, dstBuff, tempBuff, dstBuff);

                /* temporary cipher block */
                Cy_Crypto_Core_V1_MemCpy(base, tempBuff, srcBuff, CY_CRYPTO_AES_BLOCK_SIZE);

                /* destination cipher text block */
                Cy_Crypto_Core_V1_MemCpy(base, dst, dstBuff, CY_CRYPTO_AES_BLOCK_SIZE);

                src  += CY_CRYPTO_AES_BLOCK_SIZE;
                dst  += CY_CRYPTO_AES_BLOCK_SIZE;
                size -= CY_CRYPTO_AES_BLOCK_SIZE;
            }
        }
        else
        {
            while (size != 0UL)
            {
                /* source message block */
                Cy_Crypto_Core_V1_MemCpy(base, srcBuff, src, CY_CRYPTO_AES_BLOCK_SIZE);

                Cy_Crypto_Core_V1_Aes_Xor(base, aesState, tempBuff, srcBuff, tempBuff);
                Cy_Crypto_Core_V1_Aes_ProcessBlock(base, aesState, dirMode, dstBuff, tempBuff);

                /* temporary cipher block */
                Cy_Crypto_Core_V1_MemCpy(base, tempBuff, dstBuff, CY_CRYPTO_AES_BLOCK_SIZE);

                /* destination cipher text block */
                Cy_Crypto_Core_V1_MemCpy(base, dst, dstBuff, CY_CRYPTO_AES_BLOCK_SIZE);

                src  += CY_CRYPTO_AES_BLOCK_SIZE;
                dst  += CY_CRYPTO_AES_BLOCK_SIZE;
                size -= CY_CRYPTO_AES_BLOCK_SIZE;
            }
        }

        /* Copy the cipher block to the Initialization Vector */
        Cy_Crypto_Core_V1_MemCpy(base, ivPtr, tempBuff, CY_CRYPTO_AES_BLOCK_SIZE);

        tmpResult = CY_CRYPTO_SUCCESS;
    }

    return (tmpResult);
}
#endif /* defined(CY_CRYPTO_CFG_CIPHER_MODE_CBC) */

#if defined(CY_CRYPTO_CFG_CIPHER_MODE_CFB)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Aes_Cfb
********************************************************************************
*
* Performs AES operation on a plain text with the Cipher Feedback Block method (CFB).
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param dirMode
* Can be \ref CY_CRYPTO_ENCRYPT or \ref CY_CRYPTO_DECRYPT
* (\ref cy_en_crypto_dir_mode_t)
*
* \param srcSize
* The size of the source plain text.
*
* \param ivPtr
* The pointer to the initial vector.
*
* \param dst
* The pointer to a destination cipher text.
*
* \param src
* The pointer to a source plain text.
*
* \param aesState
* The pointer to the AES state structure allocated by the user. The user must
* must not modify anything in this structure.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V1_Aes_Cfb(CRYPTO_Type *base,
                                             cy_en_crypto_dir_mode_t dirMode,
                                             uint32_t srcSize,
                                             uint8_t *ivPtr,
                                             uint8_t *dst,
                                             uint8_t const *src,
                                             cy_stc_crypto_aes_state_t *aesState)
{
    uint32_t size = srcSize;
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_SIZE_NOT_X16;

    cy_stc_crypto_aes_buffers_t *aesBuffers = (cy_stc_crypto_aes_buffers_t*)aesState->buffers;

    uint32_t *srcBuff = (uint32_t*)(aesBuffers->block0);
    uint32_t *dstBuff = (uint32_t*)(aesBuffers->block1);

    uint32_t *encBuff = dstBuff;   /* Default operation is ENCRYPT */

    /* Check whether the data size is multiple of CY_CRYPTO_AES_BLOCK_SIZE */
    if (0UL == (size & (CY_CRYPTO_AES_BLOCK_SIZE - 1U)))
    {
        if (CY_CRYPTO_DECRYPT == dirMode)
        {
            encBuff = srcBuff;
        }

        /* Copies the Initialization Vector to the local encode buffer. */
        Cy_Crypto_Core_V1_MemCpy(base, encBuff, ivPtr, CY_CRYPTO_AES_BLOCK_SIZE);

        while (size != 0UL)
        {
            /* In this mode, (CFB) is always an encryption! */
            Cy_Crypto_Core_V1_Aes_ProcessBlock(base, aesState, CY_CRYPTO_ENCRYPT, dstBuff, encBuff);

            /* source message block */
            Cy_Crypto_Core_V1_MemCpy(base, srcBuff, src, CY_CRYPTO_AES_BLOCK_SIZE);

            Cy_Crypto_Core_V1_Aes_Xor(base, aesState, dstBuff, srcBuff, dstBuff);

            /* destination cipher text block */
            Cy_Crypto_Core_V1_MemCpy(base, dst, dstBuff, CY_CRYPTO_AES_BLOCK_SIZE);

            src  += CY_CRYPTO_AES_BLOCK_SIZE;
            dst  += CY_CRYPTO_AES_BLOCK_SIZE;

            size -= CY_CRYPTO_AES_BLOCK_SIZE;
        }

        /* Copies the local encode buffer to the Initialization Vector. */
        Cy_Crypto_Core_V1_MemCpy(base, ivPtr, encBuff, CY_CRYPTO_AES_BLOCK_SIZE);

        tmpResult = CY_CRYPTO_SUCCESS;
    }

    return (tmpResult);
}
#endif /* defined(CY_CRYPTO_CFG_CIPHER_MODE_CFB) */

#if defined(CY_CRYPTO_CFG_CIPHER_MODE_CTR)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Aes_Ctr
********************************************************************************
*
* Performs an AES operation on a plain text using the counter method (CTR).
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param srcSize
* The size of a source plain text.
*
* \param srcOffset
* The size of an offset within the current block stream for resuming within the
* current cipher stream.
*
* \param ivPtr
* The 128-bit initial vector that contains a 64-bit nonce and 64-bit counter.
*
* \param streamBlock
* The saved stream-block for resuming. Is over-written by the function.
*
* \param dst
* The pointer to a destination cipher text.
*
* \param src
* The pointer to a source plain text. Must be 4-Byte aligned.
*
* \param aesState
* The pointer to the AES state structure allocated by the user. The user must
* must not modify anything in this structure.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
#define CY_CRYPTO_AES_CTR_CNT_POS          (0x02U)
cy_en_crypto_status_t Cy_Crypto_Core_V1_Aes_Ctr(CRYPTO_Type *base,
                                            uint32_t srcSize,
                                            uint32_t *srcOffset,
                                            uint8_t  *ivPtr,
                                            uint8_t  *streamBlock,
                                            uint8_t  *dst,
                                            uint8_t  const *src,
                                            cy_stc_crypto_aes_state_t *aesState)
{
    uint32_t i;
    uint32_t cnt;
    uint64_t counter;
    uint32_t blockCounter[CY_CRYPTO_AES_BLOCK_SIZE_U32] = { 0UL };

    cy_stc_crypto_aes_buffers_t *aesBuffers = (cy_stc_crypto_aes_buffers_t*)aesState->buffers;
    uint32_t *srcBuff      = (uint32_t*)(&aesBuffers->block0);
    uint32_t *dstBuff      = (uint32_t*)(&aesBuffers->block1);
    uint32_t *streamBuff   = (uint32_t*)(&aesBuffers->block2);

    (void)streamBlock; /* Suppress warning */

    Cy_Crypto_Core_V1_MemCpy(base, blockCounter, ivPtr, CY_CRYPTO_AES_BLOCK_SIZE);

    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3','Intentional pointer type conversion');
    counter = CY_SWAP_ENDIAN64(*(uint64_t*)(blockCounter + CY_CRYPTO_AES_CTR_CNT_POS));

    cnt = (uint32_t)(srcSize / CY_CRYPTO_AES_BLOCK_SIZE);

    for (i = 0UL; i < cnt; i++)
    {
        /* source message block */
        Cy_Crypto_Core_V1_MemCpy(base, srcBuff, src, CY_CRYPTO_AES_BLOCK_SIZE);

        /* In this mode, (CTR) is always an encryption! */
        Cy_Crypto_Core_V1_Aes_ProcessBlock(base, aesState, CY_CRYPTO_ENCRYPT, streamBuff, blockCounter);

        /* Increment the block counter, at least 64Bits (from 128) is the counter part */
        counter++;
        CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3','Intentional pointer type conversion');
        *(uint64_t*)(blockCounter + CY_CRYPTO_AES_CTR_CNT_POS) = CY_SWAP_ENDIAN64(counter);

        Cy_Crypto_Core_V1_Aes_Xor(base, aesState, dstBuff, srcBuff, streamBuff);

        /* destination cipher text block */
        Cy_Crypto_Core_V1_MemCpy(base, dst, dstBuff, CY_CRYPTO_AES_BLOCK_SIZE);

        src += CY_CRYPTO_AES_BLOCK_SIZE;
        dst += CY_CRYPTO_AES_BLOCK_SIZE;
    }

    Cy_Crypto_Core_V1_MemCpy(base, ivPtr, blockCounter, CY_CRYPTO_AES_BLOCK_SIZE);

    /* Save the reminder of the last non-complete block */
    *srcOffset = (uint32_t)(srcSize % CY_CRYPTO_AES_BLOCK_SIZE);

    return (CY_CRYPTO_SUCCESS);
}
#endif /* defined(CY_CRYPTO_CFG_CIPHER_MODE_CTR) */

#endif /* (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_AES_C) */

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */

#endif /* defined(CY_IP_MXCRYPTO) */


/* [] END OF FILE */
