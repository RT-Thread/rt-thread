/**
 * Copyright (c) 2018 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)

#include "sdk_common.h"
#include "nrf_log.h"
#include "nrf_crypto_hmac_shared.h"
#include "cc310_backend_hmac.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_types.h"
#include <drivers/nrfx_common.h>
#include "crys_hmac.h"
#include "crys_hmac_defs.h"
#include "crys_hmac_error.h"
#include "crys_hash.h"
#include "cc310_backend_mutex.h"
#include "cc310_backend_shared.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HMAC_SHA256) || \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HMAC_SHA512)

static ret_code_t result_get(CRYSError_t err_code)
{
    ret_code_t ret_val;

    switch (err_code)
    {
        case CRYS_OK:
            ret_val = NRF_SUCCESS;
            break;

        case CRYS_HMAC_INVALID_USER_CONTEXT_POINTER_ERROR:
            ret_val = NRF_ERROR_CRYPTO_CONTEXT_NULL;
            break;

        case CRYS_HMAC_USER_CONTEXT_CORRUPTED_ERROR:
            ret_val = NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED;
            break;

        case CRYS_HMAC_DATA_IN_POINTER_INVALID_ERROR:
        case CRYS_HMAC_INVALID_KEY_POINTER_ERROR:
            ret_val = NRF_ERROR_CRYPTO_INPUT_NULL;
            break;

        case CRYS_HMAC_INVALID_RESULT_BUFFER_POINTER_ERROR:
            ret_val = NRF_ERROR_CRYPTO_OUTPUT_NULL;
            break;

        case CRYS_HMAC_ILLEGAL_PARAMS_ERROR:
            ret_val = NRF_ERROR_CRYPTO_INVALID_PARAM;
            break;

        case CRYS_HMAC_UNVALID_KEY_SIZE_ERROR:
        case CRYS_HMAC_DATA_SIZE_ILLEGAL:
            ret_val = NRF_ERROR_CRYPTO_INPUT_LENGTH;
            break;

        case CRYS_HMAC_ILLEGAL_OPERATION_MODE_ERROR:
        case CRYS_HMAC_LAST_BLOCK_ALREADY_PROCESSED_ERROR:
        case CRYS_HMAC_IS_NOT_SUPPORTED:
        case CRYS_HMAC_CTX_SIZES_ERROR:
        default:
            ret_val = NRF_ERROR_CRYPTO_INTERNAL;
            break;
    }
    return ret_val;
}


static ret_code_t cc310_backend_hmac_init(void      * const p_context,
                                          uint8_t   const * p_key,
                                          size_t            key_size)
{
    CRYSError_t                 err_code;
    CRYS_HASH_OperationMode_t   hash_mode;
    ret_code_t                  ret_val;
    bool                        mutex_locked;


    nrf_crypto_backend_cc310_hmac_context_t * p_ctx =
        (nrf_crypto_backend_cc310_hmac_context_t *)p_context;

    switch (p_ctx->header.p_info->type)
    {
        case NRF_CRYPTO_HMAC_SHA256_TYPE:
        {
            hash_mode = CRYS_HASH_SHA256_mode;
        } break;
        case NRF_CRYPTO_HMAC_SHA512_TYPE:
        {
            hash_mode = CRYS_HASH_SHA512_mode;
        } break;
        default:
        {
            NRF_LOG_ERROR("Hash algorithm not supported by CC310 backend wrapper");
            return NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
        }
    }

    // Key in flash could lead to silently calculating wrong HMAC.
    VERIFY_TRUE(nrfx_is_in_ram(p_key), NRF_ERROR_CRYPTO_INPUT_LOCATION);

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_backend_enable();

    err_code = CRYS_HMAC_Init(&p_ctx->crys_context, hash_mode, (uint8_t *)p_key, key_size);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    ret_val = result_get(err_code);

    return ret_val;
}


static ret_code_t cc310_backend_hmac_update(void    * const p_context,
                                            uint8_t const * p_data,
                                            size_t          size)
{
    CRYSError_t         err_code;
    ret_code_t          ret_val;
    bool                mutex_locked;
    size_t              cur_len;
    size_t              len_left  = size;
    uint8_t const *     p_cur     = p_data;

    nrf_crypto_backend_cc310_hmac_context_t * p_ctx =
        (nrf_crypto_backend_cc310_hmac_context_t *)p_context;

    // Data in flash could lead to silently calculating wrong HMAC.
    VERIFY_TRUE(nrfx_is_in_ram(p_data), NRF_ERROR_CRYPTO_INPUT_LOCATION);

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_backend_enable();

    // If the input is larger than CC310_MAX_LENGTH_DMA_OPERATIONS, split into smaller
    do
    {
        cur_len = (len_left > CC310_MAX_LENGTH_DMA_OPERATIONS) ?
            CC310_MAX_LENGTH_DMA_OPERATIONS : len_left;

        err_code = CRYS_HMAC_Update(&p_ctx->crys_context, (uint8_t *)p_cur, cur_len);

        len_left -= cur_len;
        p_cur += cur_len;

    } while (err_code == CRYS_OK && len_left > 0);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    ret_val = result_get(err_code);

    return ret_val;
}


static ret_code_t cc310_backend_hmac_finalize(void      * const p_context,
                                              uint8_t         * p_digest,
                                              size_t    * const p_size)
{
    CRYSError_t     err_code;
    ret_code_t      ret_val;
    bool            mutex_locked;

    nrf_crypto_backend_cc310_hmac_context_t * p_ctx =
        (nrf_crypto_backend_cc310_hmac_context_t *)p_context;

    // Set the digest length to 0 so that this is used in case of any error.
    *p_size = 0;

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_backend_enable();

    err_code = CRYS_HMAC_Finish(&p_ctx->crys_context, p_ctx->crys_result);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    ret_val = result_get(err_code);
    if (err_code != NRF_SUCCESS)
    {
        return ret_val;
    }

    *p_size = p_ctx->header.p_info->digest_size;

    memcpy(p_digest, p_ctx->crys_result, *p_size);

    return ret_val;
}

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HMAC_SHA256)

// Information structure for HMAC SHA256 using CC310 backend.
const nrf_crypto_hmac_info_t g_nrf_crypto_hmac_sha256_info =
{
    .init_fn        = cc310_backend_hmac_init,
    .update_fn      = cc310_backend_hmac_update,
    .finalize_fn    = cc310_backend_hmac_finalize,
    .digest_size    = NRF_CRYPTO_HASH_SIZE_SHA256,
    .context_size   = sizeof(nrf_crypto_backend_hmac_sha256_context_t),
    .type           = NRF_CRYPTO_HMAC_SHA256_TYPE,
};

#endif // NRF_CRYPTO_BACKEND_CC310_HMAC_SHA256_ENABLED


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HMAC_SHA512)

// Information structure for HMAC SHA512 using CC310 backend.
const nrf_crypto_hmac_info_t g_nrf_crypto_hmac_sha512_info =
{
    .init_fn        = cc310_backend_hmac_init,
    .update_fn      = cc310_backend_hmac_update,
    .finalize_fn    = cc310_backend_hmac_finalize,
    .digest_size    = NRF_CRYPTO_HASH_SIZE_SHA512,
    .context_size   = sizeof(nrf_crypto_backend_hmac_sha512_context_t),
    .type = NRF_CRYPTO_HMAC_SHA512_TYPE,
};

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HMAC_SHA512)
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HMAC_SHA256) || NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HMAC_SHA512)
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)
