/***************************************************************************//**
* \file cy_crypto_core_sha_v1.c
* \version 2.70
*
* \brief
*  This file provides the source code to the API for the SHA method
*  in the Crypto block driver.
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

#include "cy_crypto_core_sha_v1.h"

#if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C)

#include "cy_crypto_core_hw_v1.h"
#include "cy_crypto_core_mem_v1.h"
#include "cy_syslib.h"

typedef enum
{
#if (CPUSS_CRYPTO_SHA1 == 1) && defined(CY_CRYPTO_CFG_SHA1_ENABLED)
    CY_CRYPTO_V1_SHA_CTL_MODE_SHA1    = 0U,
#endif /*(CPUSS_CRYPTO_SHA1 == 1) && defined(CY_CRYPTO_CFG_SHA1_ENABLED) */

#if (CPUSS_CRYPTO_SHA256 == 1) && defined(CY_CRYPTO_CFG_SHA2_256_ENABLED)
    CY_CRYPTO_V1_SHA_CTL_MODE_SHA256  = 1U,
#endif /* (CPUSS_CRYPTO_SHA256 == 1) && defined(CY_CRYPTO_CFG_SHA2_256_ENABLED) */

#if (CPUSS_CRYPTO_SHA512 == 1) && defined(CY_CRYPTO_CFG_SHA2_512_ENABLED)
    CY_CRYPTO_V1_SHA_CTL_MODE_SHA512  = 2U,
#endif /* (CPUSS_CRYPTO_SHA512 == 1) && defined(CY_CRYPTO_CFG_SHA2_512_ENABLED) */
} cy_en_crypto_v1_sha_hw_mode_t;


/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Sha_ProcessBlock
****************************************************************************//**
*
* Performs the SHA calculation on one block.
* All addresses must be 4-Byte aligned!
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hashState
* The pointer to a Hash State.
*
* \param block
* The pointer to the block whose Hash is being computed.
*
*******************************************************************************/
void Cy_Crypto_Core_V1_Sha_ProcessBlock(CRYPTO_Type *base,
                                     cy_stc_crypto_sha_state_t *hashState, uint8_t const *block)
{
    /* Set the SHA mode */
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3','This piece of code is written for CRYPTO_V1_Type and will not execute for CRYPTO_V2_Type');
    REG_CRYPTO_SHA_CTL(base) = (uint32_t)(_VAL2FLD(CRYPTO_SHA_CTL_MODE, (uint32_t)hashState->modeHw));

    Cy_Crypto_SetReg4Instr(base,
                           (uint32_t)block,
                           (uint32_t)hashState->hash,  /* Initial hash */
                           (uint32_t)hashState->roundMem,
                           (uint32_t)hashState->hash);  /* Digest */

    /* Issue the SHA instruction */
    Cy_Crypto_Run4ParamInstr(base,
                             CY_CRYPTO_V1_SHA_OPC,
                             CY_CRYPTO_RSRC0_SHIFT,
                             CY_CRYPTO_RSRC4_SHIFT,
                             CY_CRYPTO_RSRC8_SHIFT,
                             CY_CRYPTO_RSRC12_SHIFT);

    /* Wait until the SHA instruction is complete */
    while(0uL != _FLD2VAL(CRYPTO_STATUS_SHA_BUSY, REG_CRYPTO_STATUS(base)))
    {
    }
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Sha_Init
****************************************************************************//**
*
* The function to initialize SHA operation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hashState
* The pointer to a Hash State.
*
* \param mode
* One of these: CY_CRYPTO_SHA256, CY_CRYPTO_SHA1, CY_CRYPTO_SHA256_224,
* CY_CRYPTO_SHA512, CY_CRYPTO_SHA384, CY_CRYPTO_SHA512_224, CY_CRYPTO_SHA512_256
*
* \param shaBuffers
* The pointer to the memory buffers storage, see \ref cy_stc_crypto_v1_sha_buffers_t
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V1_Sha_Init(CRYPTO_Type *base,
                             cy_stc_crypto_sha_state_t *hashState,
                             cy_en_crypto_sha_mode_t mode,
                             void *shaBuffers)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_SUCCESS;

    (void)base; /* Suppress warning */

    /* Initialization vectors for different modes of the SHA algorithm */
    #if (CPUSS_CRYPTO_SHA1 == 1) && defined(CY_CRYPTO_CFG_SHA1_ENABLED)
    static const uint32_t sha1InitHash[] =
    {
        0x67452301uL, 0xEFCDAB89uL, 0x98BADCFEuL, 0x10325476uL,
        0xC3D2E1F0uL
    };
    #endif /* (CPUSS_CRYPTO_SHA1 == 1) && defined(CY_CRYPTO_CFG_SHA1_ENABLED) */

    #if (CPUSS_CRYPTO_SHA256 == 1) && defined(CY_CRYPTO_CFG_SHA2_256_ENABLED)
    static const uint32_t sha224InitHash[] =
    {
        0xC1059ED8uL, 0x367CD507uL, 0x3070DD17uL, 0xF70E5939uL,
        0xFFC00B31uL, 0x68581511uL, 0x64F98FA7uL, 0xBEFA4FA4uL
    };

    static const uint32_t sha256InitHash[] =
    {
        0x6A09E667uL, 0xBB67AE85uL, 0x3C6EF372uL, 0xA54FF53AuL,
        0x510E527FuL, 0x9B05688CuL, 0x1F83D9ABuL, 0x5BE0CD19uL
    };
    #endif /* (CPUSS_CRYPTO_SHA256 == 1) && defined(CY_CRYPTO_CFG_SHA2_256_ENABLED) */

    #if (CPUSS_CRYPTO_SHA512 == 1) && defined(CY_CRYPTO_CFG_SHA2_512_ENABLED)
    static const uint32_t sha512_224InitHash[] =
    {
        0x8C3D37C8uL, 0x19544DA2uL, 0x73E19966uL, 0x89DCD4D6uL,
        0x1DFAB7AEuL, 0x32FF9C82uL, 0x679DD514uL, 0x582F9FCFuL,
        0x0F6D2B69uL, 0x7BD44DA8uL, 0x77E36F73uL, 0x04C48942uL,
        0x3F9D85A8uL, 0x6A1D36C8uL, 0x1112E6ADuL, 0x91D692A1uL
    };

    static const uint32_t sha512_256InitHash[] =
    {
        0x22312194uL, 0xFC2BF72CuL, 0x9F555FA3uL, 0xC84C64C2uL,
        0x2393B86BuL, 0x6F53B151uL, 0x96387719uL, 0x5940EABDuL,
        0x96283EE2uL, 0xA88EFFE3uL, 0xBE5E1E25uL, 0x53863992uL,
        0x2B0199FCuL, 0x2C85B8AAuL, 0x0EB72DDCuL, 0x81C52CA2uL
    };

    static const uint32_t sha384InitHash[] =
    {
        0xCBBB9D5DuL, 0xC1059ED8uL, 0x629A292AuL, 0x367CD507uL,
        0x9159015AuL, 0x3070DD17uL, 0x152FECD8uL, 0xF70E5939uL,
        0x67332667uL, 0xFFC00B31uL, 0x8EB44A87uL, 0x68581511uL,
        0xDB0C2E0DuL, 0x64F98FA7uL, 0x47B5481DuL, 0xBEFA4FA4uL
    };

    static const uint32_t sha512InitHash[] =
    {
        0x6A09E667uL, 0xF3BCC908uL, 0xBB67AE85uL, 0x84CAA73BuL,
        0x3C6EF372uL, 0xFE94F82BuL, 0xA54FF53AuL, 0x5F1D36F1uL,
        0x510E527FuL, 0xADE682D1uL, 0x9B05688CuL, 0x2B3E6C1FuL,
        0x1F83D9ABuL, 0xFB41BD6BuL, 0x5BE0CD19uL, 0x137E2179uL
    };
    #endif /* (CPUSS_CRYPTO_SHA512 == 1) && defined(CY_CRYPTO_CFG_SHA2_512_ENABLED) */

    CY_ASSERT_L1((shaBuffers != NULL) && (hashState != NULL));

    switch (mode)
    {
        #if (CPUSS_CRYPTO_SHA1 == 1) && defined(CY_CRYPTO_CFG_SHA1_ENABLED)
            case CY_CRYPTO_MODE_SHA1:
                hashState->block          = (uint8_t*)((cy_stc_crypto_v1_sha1_buffers_t*)shaBuffers)->block;
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v1_sha1_buffers_t*)shaBuffers)->hash;
                hashState->roundMem       = (uint8_t*)((cy_stc_crypto_v1_sha1_buffers_t*)shaBuffers)->roundMem;

                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V1_SHA_CTL_MODE_SHA1;
                hashState->initialHash    = (const uint8_t*)sha1InitHash;
                hashState->blockSize      = CY_CRYPTO_SHA1_BLOCK_SIZE;
                hashState->hashSize       = CY_CRYPTO_SHA1_HASH_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA1_DIGEST_SIZE;
                hashState->roundMemSize   = CY_CRYPTO_SHA1_ROUND_MEM_SIZE;
                break;
        #endif /* (CPUSS_CRYPTO_SHA1 == 1) && defined(CY_CRYPTO_CFG_SHA1_ENABLED) */

        #if (CPUSS_CRYPTO_SHA256 == 1) && defined(CY_CRYPTO_CFG_SHA2_256_ENABLED)
            case CY_CRYPTO_MODE_SHA224:
                hashState->block          = (uint8_t*)((cy_stc_crypto_v1_sha256_buffers_t*)shaBuffers)->block;
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v1_sha256_buffers_t*)shaBuffers)->hash;
                hashState->roundMem       = (uint8_t*)((cy_stc_crypto_v1_sha256_buffers_t*)shaBuffers)->roundMem;

                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V1_SHA_CTL_MODE_SHA256;
                hashState->initialHash    = (const uint8_t*)sha224InitHash;
                hashState->blockSize      = CY_CRYPTO_SHA256_BLOCK_SIZE;
                hashState->hashSize       = CY_CRYPTO_SHA256_HASH_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA224_DIGEST_SIZE;
                hashState->roundMemSize   = CY_CRYPTO_SHA256_ROUND_MEM_SIZE;
                break;

            case CY_CRYPTO_MODE_SHA256:
                hashState->block          = (uint8_t*)((cy_stc_crypto_v1_sha256_buffers_t*)shaBuffers)->block;
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v1_sha256_buffers_t*)shaBuffers)->hash;
                hashState->roundMem       = (uint8_t*)((cy_stc_crypto_v1_sha256_buffers_t*)shaBuffers)->roundMem;

                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V1_SHA_CTL_MODE_SHA256;
                hashState->initialHash    = (const uint8_t*)sha256InitHash;
                hashState->blockSize      = CY_CRYPTO_SHA256_BLOCK_SIZE;
                hashState->hashSize       = CY_CRYPTO_SHA256_HASH_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA256_DIGEST_SIZE;
                hashState->roundMemSize   = CY_CRYPTO_SHA256_ROUND_MEM_SIZE;
                break;
        #endif /* (CPUSS_CRYPTO_SHA256 == 1) && defined(CY_CRYPTO_CFG_SHA2_256_ENABLED) */

        #if (CPUSS_CRYPTO_SHA512 == 1) && defined(CY_CRYPTO_CFG_SHA2_512_ENABLED)

            case CY_CRYPTO_MODE_SHA384:
                hashState->block          = (uint8_t*)((cy_stc_crypto_v1_sha512_buffers_t*)shaBuffers)->block;
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v1_sha512_buffers_t*)shaBuffers)->hash;
                hashState->roundMem       = (uint8_t*)((cy_stc_crypto_v1_sha512_buffers_t*)shaBuffers)->roundMem;

                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V1_SHA_CTL_MODE_SHA512;
                hashState->initialHash    = (const uint8_t*)sha384InitHash;
                hashState->blockSize      = CY_CRYPTO_SHA512_BLOCK_SIZE;
                hashState->hashSize       = CY_CRYPTO_SHA512_HASH_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA384_DIGEST_SIZE;
                hashState->roundMemSize   = CY_CRYPTO_SHA512_ROUND_MEM_SIZE;
                break;

            case CY_CRYPTO_MODE_SHA512:
                hashState->block          = (uint8_t*)((cy_stc_crypto_v1_sha512_buffers_t*)shaBuffers)->block;
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v1_sha512_buffers_t*)shaBuffers)->hash;
                hashState->roundMem       = (uint8_t*)((cy_stc_crypto_v1_sha512_buffers_t*)shaBuffers)->roundMem;

                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V1_SHA_CTL_MODE_SHA512;
                hashState->initialHash    = (const uint8_t*)sha512InitHash;
                hashState->blockSize      = CY_CRYPTO_SHA512_BLOCK_SIZE;
                hashState->hashSize       = CY_CRYPTO_SHA512_HASH_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA512_DIGEST_SIZE;
                hashState->roundMemSize   = CY_CRYPTO_SHA512_ROUND_MEM_SIZE;
                break;

            case CY_CRYPTO_MODE_SHA512_224:
                hashState->block          = (uint8_t*)((cy_stc_crypto_v1_sha512_buffers_t*)shaBuffers)->block;
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v1_sha512_buffers_t*)shaBuffers)->hash;
                hashState->roundMem       = (uint8_t*)((cy_stc_crypto_v1_sha512_buffers_t*)shaBuffers)->roundMem;

                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V1_SHA_CTL_MODE_SHA512;
                hashState->initialHash    = (const uint8_t*)sha512_224InitHash;
                hashState->blockSize      = CY_CRYPTO_SHA512_BLOCK_SIZE;
                hashState->hashSize       = CY_CRYPTO_SHA512_HASH_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA512_224_DIGEST_SIZE;
                hashState->roundMemSize   = CY_CRYPTO_SHA512_ROUND_MEM_SIZE;
                break;

            case CY_CRYPTO_MODE_SHA512_256:
                hashState->block          = (uint8_t*)((cy_stc_crypto_v1_sha512_buffers_t*)shaBuffers)->block;
                hashState->hash           = (uint8_t*)((cy_stc_crypto_v1_sha512_buffers_t*)shaBuffers)->hash;
                hashState->roundMem       = (uint8_t*)((cy_stc_crypto_v1_sha512_buffers_t*)shaBuffers)->roundMem;

                hashState->mode           = (uint32_t)mode;
                hashState->modeHw         = (uint32_t)CY_CRYPTO_V1_SHA_CTL_MODE_SHA512;
                hashState->initialHash    = (const uint8_t*)sha512_256InitHash;
                hashState->blockSize      = CY_CRYPTO_SHA512_BLOCK_SIZE;
                hashState->hashSize       = CY_CRYPTO_SHA512_HASH_SIZE;
                hashState->digestSize     = CY_CRYPTO_SHA512_256_DIGEST_SIZE;
                hashState->roundMemSize   = CY_CRYPTO_SHA512_ROUND_MEM_SIZE;
                break;
        #endif /* (CPUSS_CRYPTO_SHA512 == 1) && defined(CY_CRYPTO_CFG_SHA2_512_ENABLED) */

            default:
                tmpResult = CY_CRYPTO_BAD_PARAMS;
                break;
    }

    return (tmpResult);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Sha_Start
****************************************************************************//**
*
* Initializes the initial hash vector.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hashState
* The pointer to the SHA context.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V1_Sha_Start(CRYPTO_Type *base, cy_stc_crypto_sha_state_t *hashState)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_BAD_PARAMS;

    if (hashState != NULL)
    {
        hashState->blockIdx = 0U;
        hashState->messageSize = 0U;

        if (hashState->hashSize != 0U)
        {
            Cy_Crypto_Core_V1_MemCpy(base, (void*)hashState->hash, (void const*)hashState->initialHash, (uint16_t)hashState->hashSize);

            tmpResult = CY_CRYPTO_SUCCESS;
        }
    }

    return (tmpResult);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Sha_Update
****************************************************************************//**
*
* Performs the SHA calculation on one message.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hashState
* The pointer to the SHA context.
*
* \param message
* The pointer to the message whose Hash is being computed.
*
* \param messageSize
* The size of the message whose Hash is being computed.
*
* \return
* \ref cy_en_crypto_status_t
*
* \note
* This function can be called several times only with message lengths dividable
* by the block size. Only the last call to the function can process a message with
* a not-dividable size.
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V1_Sha_Update(CRYPTO_Type *base,
                               cy_stc_crypto_sha_state_t *hashState,
                               uint8_t const *message,
                               uint32_t  messageSize)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_BAD_PARAMS;

    if ((hashState != NULL) && (message != NULL))
    {
        if (hashState->blockSize != 0U)
        {
            if (messageSize != 0U)
            {
                hashState->messageSize += messageSize;

                uint32_t hashBlockIdx  = hashState->blockIdx;
                uint32_t hashBlockSize = hashState->blockSize;

                /* Processing the fully filled blocks with remaining buffer data */
                while ((hashBlockIdx + messageSize) >= hashBlockSize)
                {
                    uint32_t tempBlockSize = hashBlockSize - hashBlockIdx;

                    Cy_Crypto_Core_V1_MemCpy(base, (void *)((uint32_t)hashState->block + hashBlockIdx), (void const*)message, (uint16_t)tempBlockSize);

                    Cy_Crypto_Core_V1_Sha_ProcessBlock(base, hashState, hashState->block);

                    messageSize -= tempBlockSize;
                    message += tempBlockSize;

                    hashBlockIdx = 0U;
                }

                /* The remaining block will be calculated in the Finish function. */
                hashState->blockIdx = hashBlockIdx + messageSize;

                /* Copy the end of the message to the block */
                if (messageSize != 0U)
                {
                    Cy_Crypto_Core_V1_MemCpy(base, (void *)((uint32_t)hashState->block + hashBlockIdx), (void const*)message, (uint16_t)messageSize);
                }
            }

            tmpResult = CY_CRYPTO_SUCCESS;
        }
    }

    return (tmpResult);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Sha_Finish
****************************************************************************//**
*
* Completes the SHA calculation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hashState
* The pointer to the SHA context.
*
* \param digest
* The pointer to the calculated hash digest.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V1_Sha_Finish(CRYPTO_Type *base,
                               cy_stc_crypto_sha_state_t *hashState,
                               uint8_t *digest)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_BAD_PARAMS;

    if ((hashState != NULL) && (digest != NULL))
    {
        uint8_t *hashPtr = hashState->hash;
        uint8_t *blockPtr = hashState->block;
        uint32_t hashBlockSize = hashState->blockSize;
        uint32_t hashBlockIdx = hashState->blockIdx;
        uint64_t finalMessageSizeInBits = (uint64_t)hashState->messageSize * 8U;
        uint32_t padSize;

        if (CY_CRYPTO_SHA512_BLOCK_SIZE == hashBlockSize)
        {
            padSize = CY_CRYPTO_SHA512_PAD_SIZE; /* Pad size = 112 */
        }
        else
        {
            padSize = CY_CRYPTO_SHA256_PAD_SIZE; /* Pad size = 56 */
        }

        /* Append 1 bit to the end of the message */
        blockPtr[hashBlockIdx] = 0x80U;

        /* Clear the rest of the block */
        Cy_Crypto_Core_V1_MemSet(base, (void* )&blockPtr[hashBlockIdx + 1U], 0x00U, (uint16_t)(hashBlockSize - hashBlockIdx - 1U));

        if (hashBlockIdx >= padSize)
        {
            /* Here we need one additional last block to calculate SHA, prepare it: */
            Cy_Crypto_Core_V1_Sha_ProcessBlock(base, hashState, (uint8_t*)blockPtr);

            /* Clear the last block */
            Cy_Crypto_Core_V1_MemSet(base, (void*)blockPtr, 0x00u, (uint16_t)hashBlockSize);
        }

        blockPtr[hashBlockSize - 4U] = (uint8_t)((finalMessageSizeInBits) >> 24U);
        blockPtr[hashBlockSize - 3U] = (uint8_t)((finalMessageSizeInBits) >> 16U);
        blockPtr[hashBlockSize - 2U] = (uint8_t)((finalMessageSizeInBits) >> 8U);
        blockPtr[hashBlockSize - 1U] = (uint8_t)(finalMessageSizeInBits);

        /* Process the last block */
        Cy_Crypto_Core_V1_Sha_ProcessBlock(base, hashState, (uint8_t*)blockPtr);

        /* Invert endians of the hash and copy it to digest, re-use the padSize variable */
        padSize = (uint32_t)(hashState->digestSize / 4U);

        for(; padSize != 0U; padSize--)
        {
            *(digest)   = *(hashPtr+3);
            *(digest+1) = *(hashPtr+2);
            *(digest+2) = *(hashPtr+1);
            *(digest+3) = *(hashPtr);

            digest  += 4U;
            hashPtr += 4U;
        }

        tmpResult = CY_CRYPTO_SUCCESS;
    }

    return (tmpResult);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Sha_Free
****************************************************************************//**
*
* Clears the used memory buffers.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hashState
* The pointer to the SHA context.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V1_Sha_Free(CRYPTO_Type *base, cy_stc_crypto_sha_state_t *hashState)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_BAD_PARAMS;

    if (hashState != NULL)
    {
        /* Clears the memory buffer. */
        Cy_Crypto_Core_V1_MemSet(base, (void*)hashState->block,    0x00U, (uint16_t)hashState->blockSize);
        Cy_Crypto_Core_V1_MemSet(base, (void*)hashState->hash,     0x00U, (uint16_t)hashState->hashSize);
        Cy_Crypto_Core_V1_MemSet(base, (void*)hashState->roundMem, 0x00U, (uint16_t)hashState->roundMemSize);

        tmpResult = CY_CRYPTO_SUCCESS;
    }

    return (tmpResult);
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Sha
****************************************************************************//**
*
* Performs the SHA Hash function.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param mode
* \ref cy_en_crypto_sha_mode_t
*
* \param message
* The pointer to a message whose hash value is being computed.
*
* \param messageSize
* The size of a message.
*
* \param digest
* The pointer to the hash digest.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V1_Sha(CRYPTO_Type *base,
                                uint8_t const *message,
                                uint32_t messageSize,
                                uint8_t *digest,
                                cy_en_crypto_sha_mode_t mode)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_BAD_PARAMS;

    void *shaBuffers = (void *)Cy_Crypto_Core_GetVuMemoryAddress(base);
    cy_stc_crypto_sha_state_t myHashState = { 0 };

    tmpResult = Cy_Crypto_Core_V1_Sha_Init (base, &myHashState, mode, shaBuffers);

    if (CY_CRYPTO_SUCCESS == tmpResult)
    {
        tmpResult = Cy_Crypto_Core_V1_Sha_Start  (base, &myHashState);
    }
    if (CY_CRYPTO_SUCCESS == tmpResult)
    {
        tmpResult = Cy_Crypto_Core_V1_Sha_Update (base, &myHashState, message, messageSize);
    }
    if (CY_CRYPTO_SUCCESS == tmpResult)
    {
        tmpResult = Cy_Crypto_Core_V1_Sha_Finish (base, &myHashState, digest);
    }
    if (CY_CRYPTO_SUCCESS == tmpResult)
    {
        tmpResult = Cy_Crypto_Core_V1_Sha_Free   (base, &myHashState);
    }

    return (tmpResult);
}

#endif /* (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C) */

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */

#endif /* defined(CY_IP_MXCRYPTO) */


/* [] END OF FILE */
