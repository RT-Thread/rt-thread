/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_CRYPTO)

#if defined(NRF_CRYPTO_BACKEND_CC310_LIB) && (NRF_CRYPTO_BACKEND_CC310_LIB == 1)

#include "cc310_lib_hash.h"
#include "cc310_lib_init.h"
#include <stdbool.h>
#include "crys_hash.h"
#include "crys_hash_error.h"
#include "nrf_error.h"
#include "crys_rnd.h"

bool hash_algorithm_get(nrf_hash_type_t hash_type, CRYS_HASH_OperationMode_t * p_hash_mode)
{
    if (p_hash_mode == NULL)
    {
        return false;
    }

    switch(hash_type)
    {
        case NRF_CRYPTO_HASH_TYPE_MD5:
            (*p_hash_mode) = CRYS_HASH_MD5_mode;
            break;

        case NRF_CRYPTO_HASH_TYPE_SHA1:
            (*p_hash_mode) = CRYS_HASH_SHA1_mode;
            break;

        case NRF_CRYPTO_HASH_TYPE_SHA224:
            (*p_hash_mode) = CRYS_HASH_SHA224_mode;
            break;

        case NRF_CRYPTO_HASH_TYPE_SHA256:
            (*p_hash_mode) = CRYS_HASH_SHA256_mode;
            break;

        case NRF_CRYPTO_HASH_TYPE_SHA384:
            (*p_hash_mode) = CRYS_HASH_SHA384_mode;
            break;

        case NRF_CRYPTO_HASH_TYPE_SHA512:
            (*p_hash_mode) = CRYS_HASH_SHA512_mode;
            break;

        default:
            return NRF_ERROR_NOT_SUPPORTED;
    }

    return NRF_SUCCESS;
}


static uint32_t hash_result_get(CRYSError_t error)
{
    uint32_t ret_val;

    switch(error)
    {
        case CRYS_OK:
            ret_val = NRF_SUCCESS;
            break;

        case CRYS_HASH_INVALID_USER_CONTEXT_POINTER_ERROR:
            ret_val = NRF_ERROR_INVALID_ADDR;
            break;

        case CRYS_HASH_ILLEGAL_OPERATION_MODE_ERROR:
            ret_val = NRF_ERROR_NOT_SUPPORTED;
            break;

        case CRYS_HASH_USER_CONTEXT_CORRUPTED_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        case CRYS_HASH_DATA_IN_POINTER_INVALID_ERROR:
            ret_val = NRF_ERROR_INVALID_ADDR;
            break;

        case CRYS_HASH_DATA_SIZE_ILLEGAL:
            ret_val = NRF_ERROR_INVALID_LENGTH;
            break;

        case CRYS_HASH_INVALID_RESULT_BUFFER_POINTER_ERROR:
            ret_val = NRF_ERROR_INVALID_ADDR;
            break;

        case CRYS_HASH_DATA_SIZE_IS_ILLEGAL_FOR_CSI_ERROR:
            ret_val = NRF_ERROR_INVALID_LENGTH;
            break;

        case CRYS_HASH_LAST_BLOCK_ALREADY_PROCESSED_ERROR:
            ret_val = NRF_ERROR_INVALID_STATE;
            break;

        case CRYS_HASH_ILLEGAL_PARAMS_ERROR:
            ret_val = NRF_ERROR_INTERNAL;
            break;

        case CRYS_HASH_CTX_SIZES_ERROR:
            ret_val = NRF_ERROR_INVALID_LENGTH;
            break;

        case CRYS_HASH_IS_NOT_SUPPORTED:
            ret_val = NRF_ERROR_NOT_SUPPORTED;
            break;

        default:
            ret_val = NRF_ERROR_INTERNAL;
            break;
    }

    return ret_val;
}


uint32_t nrf_crypto_hash_init(nrf_crypto_hash_info_t    hash_info,
                              nrf_value_length_t      * p_hash_context)
{
    uint32_t                    ret_val;
    CRYSError_t                 crys_error;
    CRYS_HASH_OperationMode_t   hash_type = CRYS_HASH_OperationModeLast;
    CRYS_HASHUserContext_t    * p_hash_context_user;

    // Check if library has been initialized
    if (!nrf_crypto_is_initialized())
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (p_hash_context == NULL)
    {
        return NRF_ERROR_NULL;
    }

    if (p_hash_context->p_value == NULL)
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    if (p_hash_context->length != NRF_CRYPTO_HASH_CONTEXT_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    if (!hash_algorithm_get(hash_info.hash_type, &hash_type))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if (hash_info.endian_type != NRF_CRYPTO_ENDIAN_LE)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    // Convert hash context to cc310 user format
    p_hash_context_user = (CRYS_HASHUserContext_t *)p_hash_context->p_value;

    crys_error = CRYS_HASH_Init(p_hash_context_user, hash_type);
    ret_val = hash_result_get(crys_error);
    return ret_val;
}


uint32_t nrf_crypto_hash_update(nrf_value_length_t   * p_hash_context,
                                uint8_t        const * p_data,
                                uint32_t               len)
{
    uint32_t                    ret_val;
    CRYSError_t                 crys_error;
    CRYS_HASHUserContext_t    * p_hash_context_user;

    // Check if library has been initialized
    if (!nrf_crypto_is_initialized())
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (p_hash_context == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    if (p_hash_context->p_value == NULL)
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    if (p_hash_context->length != NRF_CRYPTO_HASH_CONTEXT_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Convert hash context to cc310 user format
    p_hash_context_user = (CRYS_HASHUserContext_t *)p_hash_context->p_value;

    crys_error = CRYS_HASH_Update(p_hash_context_user, (uint8_t*)p_data, len);
    ret_val = hash_result_get(crys_error);
    return ret_val;
}


uint32_t nrf_crypto_hash_finalize(nrf_crypto_hash_info_t    hash_info,
                                  nrf_value_length_t      * p_hash_context,
                                  nrf_value_length_t      * p_hash)
{
    uint32_t                    ret_val;
    CRYSError_t                 crys_error;
    CRYS_HASHUserContext_t    * p_hash_context_user;
    CRYS_HASH_Result_t *        p_hash_result = (CRYS_HASH_Result_t *)p_hash->p_value;

    // Check if library has been initialized
    if (!nrf_crypto_is_initialized())
    {
        return NRF_ERROR_INVALID_STATE;
    }

    // Check the parameters
    if (p_hash_context == NULL  ||
        p_hash == NULL          )
    {
        return NRF_ERROR_NULL;
    }

    if (p_hash_context->p_value == NULL ||
        p_hash->p_value == NULL)
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    // Check the length of the hash context
    if(p_hash_context->length != NRF_CRYPTO_HASH_CONTEXT_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Check the length of the hash


    // Convert hash context to cc310 user format
    p_hash_context_user = (CRYS_HASHUserContext_t *)p_hash_context->p_value;

    // Not sure about this
    crys_error = CRYS_HASH_Finish(p_hash_context_user, *p_hash_result);
    ret_val = hash_result_get(crys_error);
    return ret_val;
}


uint32_t nrf_crypto_hash_compute(nrf_crypto_hash_info_t    hash_info,
                                 uint8_t           const * p_data,
                                 uint32_t                  len,
                                 nrf_value_length_t      * p_hash)
{
    uint32_t                    ret_val;
    CRYSError_t                 crys_error;
    CRYS_HASH_OperationMode_t   hash_type = CRYS_HASH_OperationModeLast;
    CRYS_HASH_Result_t        * p_hash_result;

    if (p_data == NULL || p_hash == NULL)
    {
        return NRF_ERROR_NULL;
    }

    if (p_hash->p_value == NULL)
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    if(!hash_algorithm_get(hash_info.hash_type, &hash_type))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    // Currently only supporting LE hash
    if(hash_info.endian_type != NRF_CRYPTO_ENDIAN_LE)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    // Convert output buffer to valid.
    p_hash_result = (CRYS_HASH_Result_t *)p_hash->p_value;


    crys_error = CRYS_HASH(hash_type, (uint8_t*)p_data, len, *p_hash_result);
    ret_val = hash_result_get(crys_error);
    return ret_val;
}

#endif // NRF_CRYPTO_BACKEND_CC310_LIB

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)

