/***************************************************************************//**
* \file cy_crypto_core_sha.h
* \version 2.70
*
* \brief
*  This file provides constants and function prototypes
*  for the API for the SHA method in the Crypto block driver.
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

#if !defined (CY_CRYPTO_CORE_SHA_H)
#define CY_CRYPTO_CORE_SHA_H

#include "cy_device.h"

#if defined (CY_IP_MXCRYPTO)

#include "cy_crypto_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C)

#include "cy_crypto_core_sha_v1.h"
#include "cy_crypto_core_sha_v2.h"

typedef cy_en_crypto_status_t (*cy_crypto_sha_func_t)(CRYPTO_Type *base,
                                         uint8_t const *message,
                                         uint32_t  messageSize,
                                         uint8_t *digest,
                                         cy_en_crypto_sha_mode_t mode);

/**
* \addtogroup group_crypto_lld_sha_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Sha
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
* The pointer to the message whose hash value is being computed.
*
* \param messageSize
* The size of the message.
*
* \param digest
* The pointer to the hash digest.
*
* \return
* \ref cy_en_crypto_status_t
*
* \funcusage
* \snippet crypto/snippet/main.c snippet_myCryptoCoreSha256Use
*
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Sha(CRYPTO_Type *base,
                                uint8_t const *message,
                                uint32_t messageSize,
                                uint8_t *digest,
                                cy_en_crypto_sha_mode_t mode)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_NOT_SUPPORTED;

    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_Sha(base, message, messageSize, digest, mode);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_Sha(base, message, messageSize, digest, mode);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return tmpResult;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Sha_Init
****************************************************************************//**
*
* The function to initialize the SHA operation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param shaHashState
* The pointer to a Hash state.
*
* \param mode
* One of these: CY_CRYPTO_SHA256, CY_CRYPTO_SHA1, CY_CRYPTO_SHA256_224,
* CY_CRYPTO_SHA512, CY_CRYPTO_SHA384, CY_CRYPTO_SHA512_224, CY_CRYPTO_SHA512_256
*
* \param shaBuffers
* The pointer to the memory buffers storage.
* Can be one of two buffers types according to selected hardware platform:
* cy_stc_crypto_v1_sha_buffers_t or cy_stc_crypto_v2_sha_buffers_t
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Sha_Init(CRYPTO_Type *base,
                             cy_stc_crypto_sha_state_t *shaHashState,
                             cy_en_crypto_sha_mode_t mode,
                             void *shaBuffers)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_NOT_SUPPORTED;

    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_Sha_Init(base, shaHashState, mode, shaBuffers);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_Sha_Init(base, shaHashState, mode, shaBuffers);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return tmpResult;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Sha_Start
****************************************************************************//**
*
* Initializes the initial Hash vector.
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
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Sha_Start(CRYPTO_Type *base, cy_stc_crypto_sha_state_t *hashState)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_NOT_SUPPORTED;

    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_Sha_Start(base, hashState);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_Sha_Start(base, hashState);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return tmpResult;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Sha_Update
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
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Sha_Update(CRYPTO_Type *base,
                               cy_stc_crypto_sha_state_t *hashState,
                               uint8_t const *message,
                               uint32_t  messageSize)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_NOT_SUPPORTED;

    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_Sha_Update(base, hashState, message, messageSize);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_Sha_Update(base, hashState, message, messageSize);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return tmpResult;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Sha_Finish
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
* The pointer to the calculated Hash digest.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Sha_Finish(CRYPTO_Type *base,
                               cy_stc_crypto_sha_state_t *hashState,
                               uint8_t *digest)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_NOT_SUPPORTED;

    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_Sha_Finish(base, hashState, digest);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_Sha_Finish(base, hashState, digest);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return tmpResult;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Sha_Free
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
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Sha_Free(CRYPTO_Type *base, cy_stc_crypto_sha_state_t *hashState)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_NOT_SUPPORTED;

    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_Sha_Free(base, hashState);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_Sha_Free(base, hashState);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return tmpResult;
}

/** \} group_crypto_lld_sha_functions */

#endif /* (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C) */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */

#endif /* #if !defined (CY_CRYPTO_CORE_SHA_H) */


/* [] END OF FILE */
