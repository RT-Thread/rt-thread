/***************************************************************************//**
* \file cy_crypto_core_aes_v2.c
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

#include "cy_crypto_core_aes_v2.h"

#if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_AES_C)

#include "cy_crypto_core_hw_v2.h"
#include "cy_crypto_core_mem_v2.h"
#include "cy_syslib.h"
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 18, \
'Intentional Pointer Type Conversion');

#define CY_CRYPTO_IS_KEYLENGTH_VALID(keyLength) ((CY_CRYPTO_KEY_AES_128 == (keyLength)) || \
                                                 (CY_CRYPTO_KEY_AES_192 == (keyLength)) || \
                                                 (CY_CRYPTO_KEY_AES_256 == (keyLength)))

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Aes_LoadEncKey
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
void Cy_Crypto_Core_V2_Aes_LoadEncKey(CRYPTO_Type *base,
                                      cy_stc_crypto_aes_state_t const *aesState)
{
    /* Set the key mode: 128, 192 or 256 Bit */
    uint32_t keySize = CY_CRYPTO_AES_128_KEY_SIZE + ((uint32_t)aesState->keyLength * 8u);

    Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD0, (uint8_t *)aesState->buffers->key, keySize);
    Cy_Crypto_Core_V2_BlockMov  (base, CY_CRYPTO_V2_RB_KEY0, CY_CRYPTO_V2_RB_FF_LOAD0, CY_CRYPTO_AES_128_KEY_SIZE);

    keySize -= CY_CRYPTO_AES_128_KEY_SIZE;

    if (keySize != 0u)
    {
        Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_KEY1, CY_CRYPTO_V2_RB_FF_LOAD0, keySize);
    }

    REG_CRYPTO_AES_CTL(base) = (uint32_t)(_VAL2FLD(CRYPTO_AES_CTL_KEY_SIZE, aesState->keyLength));

    Cy_Crypto_Core_WaitForReady(base);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Aes_LoadDecKey
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
void Cy_Crypto_Core_V2_Aes_LoadDecKey(CRYPTO_Type *base,
                                      cy_stc_crypto_aes_state_t const *aesState)
{
    /* Issue the AES_KEY instruction to prepare the key for decrypt operation */
    uint32_t keySize = CY_CRYPTO_AES_128_KEY_SIZE + ((uint32_t)aesState->keyLength * 8u);

    Cy_Crypto_Core_V2_Aes_LoadEncKey(base, aesState);

    Cy_Crypto_Core_V2_RunAes(base);             /* dummy encryption */

    Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_KEY0, CY_CRYPTO_V2_RB_KEY2, CY_CRYPTO_AES_128_KEY_SIZE);

    keySize -= CY_CRYPTO_AES_128_KEY_SIZE;

    if (keySize != 0u)
    {
        Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_KEY1, CY_CRYPTO_V2_RB_KEY3, keySize);
    }

    Cy_Crypto_Core_WaitForReady(base);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Aes_Free
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
cy_en_crypto_status_t Cy_Crypto_Core_V2_Aes_Free(CRYPTO_Type *base, cy_stc_crypto_aes_state_t *aesState)
{
    Cy_Crypto_Core_V2_MemSet(base, (void *)aesState->buffers, 0u, ((uint16_t)sizeof(cy_stc_crypto_aes_buffers_t)));
    Cy_Crypto_Core_V2_MemSet(base, (void *)aesState, 0u, ((uint16_t)sizeof(cy_stc_crypto_aes_state_t)));

    return (CY_CRYPTO_SUCCESS);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Aes_Init
****************************************************************************//**
*
* Sets AES mode and prepares inverse key.
*
* For CAT1C devices when D-Cache is enabled parameters key, aesState and aesBuffers must align and end in 32 byte boundary.
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
cy_en_crypto_status_t Cy_Crypto_Core_V2_Aes_Init(CRYPTO_Type *base,
                                                 uint8_t const *key,
                                                 cy_en_crypto_aes_key_length_t keyLength,
                                                 cy_stc_crypto_aes_state_t *aesState,
                                                 cy_stc_crypto_aes_buffers_t *aesBuffers)
{
    CY_ASSERT_L1(NULL != key);
    CY_ASSERT_L1(NULL != aesState);
    CY_ASSERT_L1(NULL != aesBuffers);
    CY_ASSERT_L3(CY_CRYPTO_IS_KEYLENGTH_VALID(keyLength));

    uint16_t keySize = CY_CRYPTO_AES_128_KEY_SIZE + ((uint16_t)keyLength * 8u);
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    /* Flush the cache */
    SCB_CleanDCache_by_Addr((volatile void *)key,(int32_t)keySize);
#endif
    Cy_Crypto_Core_V2_MemSet(base, aesState, 0u, ((uint16_t)sizeof(cy_stc_crypto_aes_state_t)));

#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    SCB_InvalidateDCache_by_Addr((volatile void *)aesState, (int32_t)sizeof(cy_stc_crypto_aes_state_t));
#endif

    aesState->buffers = (cy_stc_crypto_aes_buffers_t*) aesBuffers;
    aesState->keyLength = keyLength;
    Cy_Crypto_Core_V2_MemCpy(base, aesState->buffers->key, key, keySize);
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    SCB_InvalidateDCache_by_Addr(aesState->buffers->key, (int32_t)keySize);
#endif

    return (CY_CRYPTO_SUCCESS);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Aes_Ecb
****************************************************************************//**
*
* Performs an AES operation on one block.
*
* For CAT1C devices when D-Cache is enabled parameters dst and src must align and end in 32 byte boundary.
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
cy_en_crypto_status_t Cy_Crypto_Core_V2_Aes_Ecb(CRYPTO_Type *base,
                                            cy_en_crypto_dir_mode_t dirMode,
                                            uint8_t *dst,
                                            uint8_t const *src,
                                            cy_stc_crypto_aes_state_t *aesState)
{
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    /* Flush the cache */
    SCB_CleanDCache_by_Addr((volatile void *)src,(int32_t)CY_CRYPTO_AES_BLOCK_SIZE);
#endif
    (CY_CRYPTO_ENCRYPT == dirMode) ? \
        Cy_Crypto_Core_V2_Aes_LoadEncKey(base, aesState) : Cy_Crypto_Core_V2_Aes_LoadDecKey(base, aesState);

    Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD0, src, CY_CRYPTO_AES_BLOCK_SIZE);
    Cy_Crypto_Core_V2_FFStart   (base, CY_CRYPTO_V2_RB_FF_STORE, dst, CY_CRYPTO_AES_BLOCK_SIZE);

    Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_BLOCK0, CY_CRYPTO_V2_RB_FF_LOAD0, CY_CRYPTO_AES_BLOCK_SIZE);

    (CY_CRYPTO_ENCRYPT == dirMode) ? Cy_Crypto_Core_V2_RunAes(base) : Cy_Crypto_Core_V2_RunAesInv(base);

    Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_FF_STORE, CY_CRYPTO_V2_RB_BLOCK1, CY_CRYPTO_AES_BLOCK_SIZE);

    Cy_Crypto_Core_WaitForReady(base);

#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    SCB_InvalidateDCache_by_Addr(dst, (int32_t)CY_CRYPTO_AES_BLOCK_SIZE);
#endif

    return (CY_CRYPTO_SUCCESS);
}

#if defined(CY_CRYPTO_CFG_CIPHER_MODE_CBC)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Aes_Cbc
****************************************************************************//**
*
* Performs AES operation on a plain text with Cipher Block Chaining (CBC).
*
* For CAT1C devices when D-Cache is enabled parameters ivPtr, dst and src must align and end in 32 byte boundary.
* For CAT1A and CAT1C devices with DCache disabled, src must be 4-Byte aligned.
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
cy_en_crypto_status_t Cy_Crypto_Core_V2_Aes_Cbc(CRYPTO_Type *base,
                                            cy_en_crypto_dir_mode_t dirMode,
                                            uint32_t srcSize,
                                            uint8_t *ivPtr,
                                            uint8_t *dst,
                                            uint8_t const *src,
                                            cy_stc_crypto_aes_state_t *aesState)
{
    uint32_t size = srcSize;
    uint32_t ivBlockId = CY_CRYPTO_V2_RB_BLOCK1;
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_SIZE_NOT_X16;

#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    /* Flush the cache */
    SCB_CleanDCache_by_Addr((volatile void *)ivPtr,(int32_t)CY_CRYPTO_AES_BLOCK_SIZE);
    SCB_CleanDCache_by_Addr((volatile void *)src,(int32_t)srcSize);
#endif

    /* Check whether the data size is multiple of CY_CRYPTO_AES_BLOCK_SIZE */
    if (0UL == (srcSize & ((uint32_t)CY_CRYPTO_AES_BLOCK_SIZE - 1UL)))
    {

        (CY_CRYPTO_ENCRYPT == dirMode) ? \
            Cy_Crypto_Core_V2_Aes_LoadEncKey(base, aesState) : Cy_Crypto_Core_V2_Aes_LoadDecKey(base, aesState);

        Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD1, ivPtr, CY_CRYPTO_AES_BLOCK_SIZE);

        Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD0, src, size);
        Cy_Crypto_Core_V2_FFStart   (base, CY_CRYPTO_V2_RB_FF_STORE, dst, size);

        if (CY_CRYPTO_ENCRYPT == dirMode)
        {
            ivBlockId = CY_CRYPTO_V2_RB_BLOCK1;

            /* Load the Initialization Vector to the local buffer */
            Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_BLOCK1, CY_CRYPTO_V2_RB_FF_LOAD1, CY_CRYPTO_AES_BLOCK_SIZE);

            while (size != 0U)
            {
                Cy_Crypto_Core_V2_BlockXor(base, CY_CRYPTO_V2_RB_BLOCK0,
                                                 CY_CRYPTO_V2_RB_FF_LOAD0, CY_CRYPTO_V2_RB_BLOCK1, CY_CRYPTO_AES_BLOCK_SIZE);
                Cy_Crypto_Core_V2_RunAes(base);
                Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_FF_STORE, CY_CRYPTO_V2_RB_BLOCK1, CY_CRYPTO_AES_BLOCK_SIZE);

                size -= CY_CRYPTO_AES_BLOCK_SIZE;
            }
        }
        else
        {
            ivBlockId = CY_CRYPTO_V2_RB_BLOCK2;

            /* Load the Initialization Vector to the temporary buffer */
            Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_BLOCK2, CY_CRYPTO_V2_RB_FF_LOAD1, CY_CRYPTO_AES_BLOCK_SIZE);

            while (size != 0U)
            {
                Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_BLOCK0, CY_CRYPTO_V2_RB_FF_LOAD0, CY_CRYPTO_AES_BLOCK_SIZE);
                Cy_Crypto_Core_V2_RunAesInv(base);
                Cy_Crypto_Core_V2_BlockXor(base, CY_CRYPTO_V2_RB_FF_STORE,
                                                 CY_CRYPTO_V2_RB_BLOCK1, CY_CRYPTO_V2_RB_BLOCK2, CY_CRYPTO_AES_BLOCK_SIZE);

                /* temporary cipher block */
                Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_BLOCK2, CY_CRYPTO_V2_RB_BLOCK0, CY_CRYPTO_AES_BLOCK_SIZE);

                size -= CY_CRYPTO_AES_BLOCK_SIZE;
            }
        }

        Cy_Crypto_Core_V2_Sync(base);

        /* Copy the local Initialization Vector to the external Initialization Vector */
        Cy_Crypto_Core_V2_FFStart (base, CY_CRYPTO_V2_RB_FF_STORE, ivPtr, CY_CRYPTO_AES_BLOCK_SIZE);
        Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_FF_STORE, ivBlockId, CY_CRYPTO_AES_BLOCK_SIZE);

        Cy_Crypto_Core_V2_Sync(base);

        tmpResult = CY_CRYPTO_SUCCESS;
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
        SCB_InvalidateDCache_by_Addr(dst, (int32_t)srcSize);
#endif
    }


    return (tmpResult);
}
#endif /* defined(CY_CRYPTO_CFG_CIPHER_MODE_CBC) */

#if defined(CY_CRYPTO_CFG_CIPHER_MODE_CFB)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Aes_Cfb
********************************************************************************
*
* Performs AES operation on a plain text with the Cipher Feedback Block method (CFB).
*
* For CAT1C devices when D-Cache is enabled parameters ivPtr, dst and src must align and end in 32 byte boundary.
* For CAT1A and CAT1C devices with DCache disabled, src must be 4-Byte aligned.
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
cy_en_crypto_status_t Cy_Crypto_Core_V2_Aes_Cfb(CRYPTO_Type *base,
                                             cy_en_crypto_dir_mode_t dirMode,
                                             uint32_t srcSize,
                                             uint8_t *ivPtr,
                                             uint8_t *dst,
                                             uint8_t const *src,
                                             cy_stc_crypto_aes_state_t *aesState)
{
    uint32_t size = srcSize;

    cy_en_crypto_status_t tmpResult = CY_CRYPTO_SIZE_NOT_X16;

#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
        /* Flush the cache */
        SCB_CleanDCache_by_Addr((volatile void *)ivPtr,(int32_t)CY_CRYPTO_AES_BLOCK_SIZE);
        SCB_CleanDCache_by_Addr((volatile void *)src,(int32_t)srcSize);
#endif

    /* Check whether the data size is multiple of CY_CRYPTO_AES_BLOCK_SIZE */
    if (0UL == (size & ((uint32_t)CY_CRYPTO_AES_BLOCK_SIZE - 1UL)))
    {
        Cy_Crypto_Core_V2_Aes_LoadEncKey(base, aesState);

        /* Load the Initialization Vector to the src buffer */
        Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD1, ivPtr, CY_CRYPTO_AES_BLOCK_SIZE);
        Cy_Crypto_Core_V2_BlockMov  (base, CY_CRYPTO_V2_RB_BLOCK0, CY_CRYPTO_V2_RB_FF_LOAD1, CY_CRYPTO_AES_BLOCK_SIZE);

        Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD0, src, size);
        Cy_Crypto_Core_V2_FFStart   (base, CY_CRYPTO_V2_RB_FF_STORE, dst, size);

        if (CY_CRYPTO_ENCRYPT == dirMode)
        {
            while (size != 0U)
            {
                Cy_Crypto_Core_V2_RunAes(base);
                Cy_Crypto_Core_V2_BlockXor(base, CY_CRYPTO_V2_RB_BLOCK0,
                                                 CY_CRYPTO_V2_RB_FF_LOAD0, CY_CRYPTO_V2_RB_BLOCK1, CY_CRYPTO_AES_BLOCK_SIZE);
                Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_FF_STORE, CY_CRYPTO_V2_RB_BLOCK0, CY_CRYPTO_AES_BLOCK_SIZE);

                size -= CY_CRYPTO_AES_BLOCK_SIZE;
            }
        }
        else
        {
            while (size != 0U)
            {
                Cy_Crypto_Core_V2_RunAes(base);
                Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_BLOCK0, CY_CRYPTO_V2_RB_FF_LOAD0, CY_CRYPTO_AES_BLOCK_SIZE);
                Cy_Crypto_Core_V2_BlockXor(base, CY_CRYPTO_V2_RB_FF_STORE,
                                                 CY_CRYPTO_V2_RB_BLOCK1, CY_CRYPTO_V2_RB_BLOCK0, CY_CRYPTO_AES_BLOCK_SIZE);

                size -= CY_CRYPTO_AES_BLOCK_SIZE;
            }
        }

        Cy_Crypto_Core_V2_Sync(base);

        /* Copy the local Initialization Vector to the external Initialization Vector */
        Cy_Crypto_Core_V2_FFStart (base, CY_CRYPTO_V2_RB_FF_STORE, ivPtr, CY_CRYPTO_AES_BLOCK_SIZE);
        Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_FF_STORE, CY_CRYPTO_V2_RB_BLOCK0, CY_CRYPTO_AES_BLOCK_SIZE);

        Cy_Crypto_Core_V2_Sync(base);

        tmpResult = CY_CRYPTO_SUCCESS;
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
        SCB_InvalidateDCache_by_Addr(dst, (int32_t)srcSize);
#endif
    }


    return (tmpResult);
}
#endif /* defined(CY_CRYPTO_CFG_CIPHER_MODE_CFB) */

#if defined(CY_CRYPTO_CFG_CIPHER_MODE_CTR)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Aes_Ctr
********************************************************************************
*
* Performs AES operation on a plain text using the counter method (CTR).
*
* For CAT1C devices when D-Cache is enabled parameters ivPtr, streamBlock, dst and src must align and end in 32 byte boundary.
* For CAT1A and CAT1C devices with DCache disabled, src must be 4-Byte aligned.
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
#define CY_CRYPTO_AES_CTR_CNT_POS           (2U)
cy_en_crypto_status_t Cy_Crypto_Core_V2_Aes_Ctr(CRYPTO_Type *base,
                                            uint32_t srcSize,
                                            uint32_t *srcOffset,
                                            uint8_t *ivPtr,
                                            uint8_t *streamBlock,
                                            uint8_t *dst,
                                            uint8_t const *src,
                                            cy_stc_crypto_aes_state_t *aesState)
{
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    CY_ALIGN(__SCB_DCACHE_LINE_SIZE) static uint32_t blockCounter[CY_CRYPTO_AES_BLOCK_SIZE_U32] = { 0UL };
    Cy_Crypto_Core_V2_MemSet(base, (void*)blockCounter, 0x00U, (uint16_t)sizeof(blockCounter));
#else
    uint32_t blockCounter[CY_CRYPTO_AES_BLOCK_SIZE_U32] = { 0UL };
#endif
    uint64_t counter;
    uint32_t cnt;
    uint32_t i;

    (void)streamBlock; /* Suppress warning */
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    /* Flush the cache */
    SCB_CleanDCache_by_Addr((volatile void *)ivPtr,(int32_t)CY_CRYPTO_AES_BLOCK_SIZE);
    SCB_CleanDCache_by_Addr((volatile void *)src,(int32_t)srcSize);
    SCB_CleanDCache_by_Addr((volatile void *)streamBlock,(int32_t)CY_CRYPTO_AES_BLOCK_SIZE);
#endif

    blockCounter[ 0] = (uint32_t) CY_CRYPTO_MERGE_BYTES(ivPtr[ 3], ivPtr[ 2], ivPtr[ 1], ivPtr[ 0]);
    blockCounter[ 1] = (uint32_t) CY_CRYPTO_MERGE_BYTES(ivPtr[ 7], ivPtr[ 6], ivPtr[ 5], ivPtr[ 4]);
    blockCounter[ 2] = (uint32_t) CY_CRYPTO_MERGE_BYTES(ivPtr[11], ivPtr[10], ivPtr[ 9], ivPtr[ 8]);
    blockCounter[ 3] = (uint32_t) CY_CRYPTO_MERGE_BYTES(ivPtr[15], ivPtr[14], ivPtr[13], ivPtr[12]);

#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    /* Flush the cache */
    SCB_CleanDCache_by_Addr((volatile void *)blockCounter,(int32_t)sizeof(blockCounter));
#endif

    counter = CY_SWAP_ENDIAN64(*(uint64_t*)(blockCounter + CY_CRYPTO_AES_CTR_CNT_POS));

    Cy_Crypto_Core_V2_Aes_LoadEncKey(base, aesState);

    Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD1, (const uint8_t *) &blockCounter, CY_CRYPTO_AES_BLOCK_SIZE);
    Cy_Crypto_Core_V2_BlockMov  (base, CY_CRYPTO_V2_RB_BLOCK0,   CY_CRYPTO_V2_RB_FF_LOAD1, CY_CRYPTO_AES_BLOCK_SIZE);

    /* CTR counter is placed into last 4 bytes of the Nonce block */
    Cy_Crypto_Core_V2_RBSetByte(base, CY_CRYPTO_AES_BLOCK_SIZE - 4U, (uint8_t)((counter >> 24U) & 0xffU));
    Cy_Crypto_Core_V2_RBSetByte(base, CY_CRYPTO_AES_BLOCK_SIZE - 3U, (uint8_t)((counter >> 16U) & 0xffU));
    Cy_Crypto_Core_V2_RBSetByte(base, CY_CRYPTO_AES_BLOCK_SIZE - 2U, (uint8_t)((counter >>  8U) & 0xffU));
    Cy_Crypto_Core_V2_RBSetByte(base, CY_CRYPTO_AES_BLOCK_SIZE - 1U, (uint8_t)((counter) & 0xffU));

    Cy_Crypto_Core_V2_RunAes(base);

    Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD0, src, srcSize);
    Cy_Crypto_Core_V2_FFStart   (base, CY_CRYPTO_V2_RB_FF_STORE, dst, srcSize);

    cnt = (uint32_t)(srcSize / CY_CRYPTO_AES_BLOCK_SIZE);

    for (i = 0uL; i < cnt; i++)
    {
        Cy_Crypto_Core_V2_RunAes(base);

        /* Increment the nonce counter */
        counter++;
        *(uint64_t*)(blockCounter + CY_CRYPTO_AES_CTR_CNT_POS) = CY_SWAP_ENDIAN64(counter);

        /* CTR counter is placed into last 4 bytes of the Nonce block */
        Cy_Crypto_Core_V2_RBSetByte(base, CY_CRYPTO_AES_BLOCK_SIZE - 4U, (uint8_t)((counter >> 24u) & 0xffU));
        Cy_Crypto_Core_V2_RBSetByte(base, CY_CRYPTO_AES_BLOCK_SIZE - 3U, (uint8_t)((counter >> 16u) & 0xffU));
        Cy_Crypto_Core_V2_RBSetByte(base, CY_CRYPTO_AES_BLOCK_SIZE - 2U, (uint8_t)((counter >>  8u) & 0xffU));
        Cy_Crypto_Core_V2_RBSetByte(base, CY_CRYPTO_AES_BLOCK_SIZE - 1U, (uint8_t)((counter) & 0xffU));

        Cy_Crypto_Core_V2_RBXor  (base, CY_CRYPTO_AES_BLOCK_SIZE, CY_CRYPTO_AES_BLOCK_SIZE);
        Cy_Crypto_Core_V2_RBStore(base, CY_CRYPTO_AES_BLOCK_SIZE, CY_CRYPTO_AES_BLOCK_SIZE);
    }

    Cy_Crypto_Core_V2_MemCpy(base, ivPtr, blockCounter, CY_CRYPTO_AES_BLOCK_SIZE);

    /* Save the reminder of the last non-complete block */
    *srcOffset = (uint32_t)(srcSize % CY_CRYPTO_AES_BLOCK_SIZE);
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    SCB_InvalidateDCache_by_Addr(dst, (int32_t)srcSize);
#endif

    return (CY_CRYPTO_SUCCESS);
}
#endif /* defined(CY_CRYPTO_CFG_CIPHER_MODE_CTR) */
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');
#endif /* (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_AES_C) */

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */

#endif /* defined(CY_IP_MXCRYPTO) */


/* [] END OF FILE */
