/***************************************************************************//**
* \file cy_crypto_core_hmac_v2.c
* \version 2.50
*
* \brief
*  This file provides the source code to the API for the HMAC method
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

#if defined (CY_IP_MXCRYPTO)

#include "cy_crypto_core_hmac_v2.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_SHA == 1)

#include "cy_crypto_core_sha_v2.h"
#include "cy_crypto_core_hw_v2.h"
#include "cy_crypto_core_mem_v2.h"
#include "cy_syslib.h"

#define CY_CRYPTO_HMAC_IPAD               (0x36u)
#define CY_CRYPTO_HMAC_0PAD               (0x5Cu)
#define CY_CRYPTO_HMAC_MAX_PAD_SIZE       (128u)
#define CY_CRYPTO_HMAC_MAX_M0_KEY_SIZE    (128u)

typedef struct
{
    uint8_t *ipad;
    uint8_t *opad;
    uint8_t *m0Key;
} cy_stc_crypto_v2_hmac_state_t;

/* Allocating internal variables into the CRYPTO SRAM Buffer */
typedef struct
{
    uint8_t ipad[CY_CRYPTO_HMAC_MAX_PAD_SIZE];
    uint8_t opad[CY_CRYPTO_HMAC_MAX_PAD_SIZE];
    uint8_t m0Key[CY_CRYPTO_SHA_MAX_BLOCK_SIZE];
    cy_stc_crypto_v2_sha512_buffers_t shaBuffers;
    cy_stc_crypto_v2_hmac_state_t hmacState;
} cy_stc_crypto_v2_hmac_buffers_t;

/* Static fubctions declarations */
static void Cy_Crypto_Core_V2_Hmac_Init(cy_stc_crypto_v2_hmac_state_t *hmacState,
                                uint8_t *ipad,
                                uint8_t *opad,
                                uint8_t *m0Key);
static cy_en_crypto_status_t Cy_Crypto_Core_V2_Hmac_Calculate(CRYPTO_Type *base,
                                   cy_stc_crypto_v2_hmac_state_t *hmacState,
                                   cy_stc_crypto_sha_state_t  *hashState,
                                   uint8_t   const *key,
                                   uint32_t  keyLength,
                                   uint8_t   const *message,
                                   uint32_t  messageSize,
                                   uint8_t  *hmac);
static void Cy_Crypto_Core_V2_Hmac_Free(CRYPTO_Type *base,
                                   cy_stc_crypto_v2_hmac_state_t *hmacState);

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Hmac_Init
****************************************************************************//**
*
* Initializes HMAC (Hash-based Message Authentication Code) calculation.
* User should allocate two buffers (ipad and opad) for HMAC calculation.
*
* \param hmacState
* the pointer to the hmacState structure which stores internal variables
* for HMAC calculation.
*
* \param ipad
* The memory buffer for HMAC calculation,
* the max used size = CRYPTO_HMAC_MAX_PAD_SIZE.
*
* \param opad
* The memory buffer for HMAC calculation,
* the max used size = CRYPTO_HMAC_MAX_PAD_SIZE.
*
* \param m0Key
* The memory buffer for HMAC calculation,
* the max used size = CRYPTO_HMAC_MAX_M0_KEY_SIZE.
*
*******************************************************************************/
static void Cy_Crypto_Core_V2_Hmac_Init(cy_stc_crypto_v2_hmac_state_t *hmacState,
                                uint8_t *ipad,
                                uint8_t *opad,
                                uint8_t *m0Key)
{
    hmacState->ipad  = ipad;
    hmacState->opad  = opad;
    hmacState->m0Key = m0Key;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Hmac_Calculate
****************************************************************************//**
*
* Starts HMAC (Hash-based Message Authentication Code) calculation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hmacState
* The pointer to the hmacState structure which stores internal variables
* for HMAC calculation.
*
* \param hashState
* The pointer to the hashState structure which stores internal variables
* of the SHA algorithm because it is used for HMAC calculation.
*
* \param key
* The pointer to the key used in computing SHA.
*
* \param keyLength
* The size of the key.
*
* \param message
* The pointer to the input message.
*
* \param messageSize
* The size of the input message.
*
* \param hmac
* The pointer to the calculated HMAC.
*
*******************************************************************************/
static cy_en_crypto_status_t Cy_Crypto_Core_V2_Hmac_Calculate(CRYPTO_Type *base,
                                   cy_stc_crypto_v2_hmac_state_t *hmacState,
                                   cy_stc_crypto_sha_state_t  *hashState,
                                   uint8_t   const *key,
                                   uint32_t  keyLength,
                                   uint8_t   const *message,
                                   uint32_t  messageSize,
                                   uint8_t  *hmac)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_SUCCESS;

    uint32_t i = 0uL;
    uint32_t blockSizeTmp   = hashState->blockSize;
    uint32_t digestSizeTmp  = hashState->digestSize;
    uint8_t *ipadPtrTmp  = (uint8_t*)hmacState->ipad;
    uint8_t *opadPtrTmp  = (uint8_t*)hmacState->opad;
    uint8_t *m0KeyPtrTmp = (uint8_t*)hmacState->m0Key;

    Cy_Crypto_Core_V2_MemSet(base, m0KeyPtrTmp, 0x00u, (uint16_t)blockSizeTmp);

    /* Steps 1-3 according to FIPS 198-1 */
    if (keyLength > blockSizeTmp)
    {
        /* The key is larger than the block size. Do a hash on the key. */
        tmpResult = Cy_Crypto_Core_V2_Sha_Start  (base, hashState);

        if (CY_CRYPTO_SUCCESS == tmpResult)
        {
            tmpResult = Cy_Crypto_Core_V2_Sha_Update (base, hashState, key, keyLength);
        }
        if (CY_CRYPTO_SUCCESS == tmpResult)
        {
            tmpResult = Cy_Crypto_Core_V2_Sha_Finish (base, hashState, m0KeyPtrTmp);
        }

        /* Append zeros */
        Cy_Crypto_Core_V2_MemSet(base, (m0KeyPtrTmp + digestSizeTmp), 0x00u, (uint16_t)(blockSizeTmp - digestSizeTmp));
    }
    else if (keyLength < blockSizeTmp)
    {
        /* If the key is shorter than the block, append zeros */
        Cy_Crypto_Core_V2_MemCpy(base, m0KeyPtrTmp, key, (uint16_t)keyLength);
        Cy_Crypto_Core_V2_MemSet(base, m0KeyPtrTmp + keyLength, 0x00u, (uint16_t)(blockSizeTmp - keyLength));
    }
    else
    {
        Cy_Crypto_Core_V2_MemCpy(base, m0KeyPtrTmp, key, (uint16_t)keyLength);
    }

    if (CY_CRYPTO_SUCCESS == tmpResult)
    {
        /* Steps 4 and 7 according to FIPS 198-1 */
        while (i < blockSizeTmp)
        {
            ipadPtrTmp[i] = CY_CRYPTO_HMAC_IPAD ^ m0KeyPtrTmp[i];
            opadPtrTmp[i] = CY_CRYPTO_HMAC_0PAD ^ m0KeyPtrTmp[i];
            i++;
        }

        /* Step 6 according to FIPS 198-1 */
        tmpResult = Cy_Crypto_Core_V2_Sha_Start (base, hashState);

        if (CY_CRYPTO_SUCCESS == tmpResult)
        {
            tmpResult = Cy_Crypto_Core_V2_Sha_Update(base, hashState, ipadPtrTmp, blockSizeTmp);
        }

        if (CY_CRYPTO_SUCCESS == tmpResult)
        {
            /* Append a message */
            tmpResult = Cy_Crypto_Core_V2_Sha_Update(base, hashState, message,    messageSize);
        }
        if (CY_CRYPTO_SUCCESS == tmpResult)
        {
            tmpResult = Cy_Crypto_Core_V2_Sha_Finish(base, hashState, ipadPtrTmp);
        }

        /* Here is the ready part of HASH: Hash((Key^ipad)||text) */

        if (CY_CRYPTO_SUCCESS == tmpResult)
        {
            /* Steps 8, 9 according to FIPS 198-1 */
            tmpResult = Cy_Crypto_Core_V2_Sha_Start(base, hashState);

            if (CY_CRYPTO_SUCCESS == tmpResult)
            {
                tmpResult = Cy_Crypto_Core_V2_Sha_Update(base, hashState, opadPtrTmp, blockSizeTmp);
            }

            /* Append HASH from Step 6 */
            if (CY_CRYPTO_SUCCESS == tmpResult)
            {
                tmpResult = Cy_Crypto_Core_V2_Sha_Update(base, hashState, ipadPtrTmp, digestSizeTmp);
            }
            if (CY_CRYPTO_SUCCESS == tmpResult)
            {
                tmpResult = Cy_Crypto_Core_V2_Sha_Finish(base, hashState, hmac);
            }
        }
    }

    return (tmpResult);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Hmac_Free
****************************************************************************//**
*
* Clears the used memory buffers.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hmacState
* The pointer to the HMAC context.
*
*******************************************************************************/
static void Cy_Crypto_Core_V2_Hmac_Free(CRYPTO_Type *base, cy_stc_crypto_v2_hmac_state_t *hmacState)
{
    /* Clear the memory buffer. */
    Cy_Crypto_Core_V2_MemSet(base, hmacState, 0u, ((uint16_t)sizeof(cy_stc_crypto_v2_hmac_state_t)));
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Hmac
****************************************************************************//**
*
* Performs HMAC calculation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hmac
* The pointer to the calculated HMAC. Must be 4-byte aligned.
*
* \param message
* The pointer to a message whose hash value is being computed.
*
* \param messageSize
* The size of a message.
*
* \param key
* The pointer to the key.
*
* \param keyLength
* The length of the key.
*
* \param mode
* \ref cy_en_crypto_sha_mode_t
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Hmac(CRYPTO_Type *base,
                                          uint8_t *hmac,
                                          uint8_t  const *message,
                                          uint32_t messageSize,
                                          uint8_t  const *key,
                                          uint32_t keyLength,
                                          cy_en_crypto_sha_mode_t mode)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_SUCCESS;

    /* Allocating internal variables into the RAM */
    cy_stc_crypto_v2_hmac_buffers_t  hmacBuffersData = {{ 0 }, { 0 }, { 0 }, {{ 0 }, { 0 }}, {NULL, NULL, NULL}};
    cy_stc_crypto_v2_hmac_buffers_t *hmacBuffers = &hmacBuffersData;

    cy_stc_crypto_v2_hmac_state_t   *hmacStateTmp = &hmacBuffers->hmacState;
    cy_stc_crypto_sha_state_t        hashStateLoc = { 0 };

    uint8_t *ipadTmp      = (uint8_t*)&hmacBuffers->ipad;
    uint8_t *opadTmp      = (uint8_t*)&hmacBuffers->opad;
    uint8_t *m0KeyTmp     = (uint8_t*)&hmacBuffers->m0Key;

    tmpResult = Cy_Crypto_Core_V2_Sha_Init(base, &hashStateLoc, mode, &hmacBuffers->shaBuffers);

    if (CY_CRYPTO_SUCCESS == tmpResult)
    {
        Cy_Crypto_Core_V2_Hmac_Init(hmacStateTmp, ipadTmp, opadTmp, m0KeyTmp);
        tmpResult = Cy_Crypto_Core_V2_Hmac_Calculate(base, hmacStateTmp, &hashStateLoc, key, keyLength, message, messageSize, hmac);
        Cy_Crypto_Core_V2_Hmac_Free(base, hmacStateTmp);
    }

    (void)Cy_Crypto_Core_V2_Sha_Free(base, &hashStateLoc);

    return (tmpResult);
}

#endif /* #if (CPUSS_CRYPTO_SHA == 1) */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */


/* [] END OF FILE */
