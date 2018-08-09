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

#include "nrf.h"
#include "cc310_backend_hash.h"
#include "crys_hash.h"
#include "crys_hash_error.h"
#include "nrf_crypto_init.h"
#include "nrf_crypto_types.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_hash_shared.h"
#include "sdk_macros.h"
#include "nrf_log.h"
#include "nrf_assert.h"
#include "cc310_backend_mutex.h"
#include "cc310_backend_shared.h"
#include <drivers/nrfx_common.h>

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HASH_SHA256) || \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HASH_SHA512) 

static ret_code_t hash_result_get(CRYSError_t error)
{
    ret_code_t ret_val;

    switch (error)
    {
        case CRYS_OK:
            ret_val = NRF_SUCCESS;
            break;

        case CRYS_HASH_INVALID_USER_CONTEXT_POINTER_ERROR:
            ret_val = NRF_ERROR_CRYPTO_CONTEXT_NULL;
            break;

        case CRYS_HASH_ILLEGAL_OPERATION_MODE_ERROR:
            ret_val = NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
            break;

        case CRYS_HASH_USER_CONTEXT_CORRUPTED_ERROR:
            ret_val = NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED;
            break;

        // May be added to specialized errors for hash.
        case CRYS_HASH_LAST_BLOCK_ALREADY_PROCESSED_ERROR:
            ret_val = NRF_ERROR_CRYPTO_INTERNAL;
            break;

        case CRYS_HASH_IS_NOT_SUPPORTED:
            ret_val = NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
            break;

        default:
            ret_val = NRF_ERROR_CRYPTO_INTERNAL;
            break;
    }

    return ret_val;
}

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HASH_SHA256)

static ret_code_t cc310_backend_hash_sha256_init(void * const p_context)
{
    uint32_t                        ret_val;
    CRYSError_t                     crys_error;
    CRYS_HASH_OperationMode_t       hash_mode = CRYS_HASH_SHA256_mode;

    // No parameter testing on this level.
    // This has been done on upper level.

    CRYS_HASHUserContext_t * const p_backend_context
        = &(((nrf_crypto_backend_hash_sha256_context_t *)p_context)->context);

    crys_error = CRYS_HASH_Init(p_backend_context, hash_mode);

    ret_val = hash_result_get(crys_error);

    return ret_val;
}


static ret_code_t cc310_backend_hash_sha256_update(void        * const p_context,
                                                   uint8_t     const * p_data,
                                                   size_t              size)
{
    ret_code_t          ret_val;
    CRYSError_t         crys_error;
    bool                mutex_locked;
    size_t              cur_len;
    size_t              len_left  = size;
    uint8_t const *     p_cur     = p_data;

    // Limited parameter testing on this level.
    // This has been done on upper level.

    CRYS_HASHUserContext_t * const p_backend_context
        = &(((nrf_crypto_backend_hash_sha256_context_t *)p_context)->context);

    // Data in flash could lead to silently calculating wrong Hash.
    VERIFY_TRUE(nrfx_is_in_ram(p_data), NRF_ERROR_CRYPTO_INPUT_LOCATION);

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_backend_enable();

    // If the input is larger than CC310_MAX_LENGTH_DMA_OPERATIONS, split into smaller
    do
    {
        cur_len = (len_left > CC310_MAX_LENGTH_DMA_OPERATIONS) ?
            CC310_MAX_LENGTH_DMA_OPERATIONS : len_left;

        crys_error = CRYS_HASH_Update(p_backend_context, (uint8_t *)p_cur, cur_len);

        len_left -= cur_len;
        p_cur += cur_len;

    } while (crys_error == CRYS_OK && len_left > 0);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    ret_val = hash_result_get(crys_error);


    return ret_val;
}


static ret_code_t cc310_backend_hash_sha256_finalize(void      * const p_context,
                                                     uint8_t         * p_digest,
                                                     size_t    * const p_digest_size)
{
    ret_code_t              ret_val;
    CRYSError_t             crys_error;
    bool                    mutex_locked;
    CRYS_HASH_Result_t    * p_int_digest = (CRYS_HASH_Result_t *)p_digest;

    // Limited parameter testing on this level.
    // This has been done on upper level.

    CRYS_HASHUserContext_t * const p_backend_context
        = &(((nrf_crypto_backend_hash_sha256_context_t * )p_context)->context);

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    // Do the hash finalize calculation
    cc310_backend_enable();

    crys_error = CRYS_HASH_Finish(p_backend_context, *p_int_digest);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    ret_val = hash_result_get(crys_error);
    if (ret_val == NRF_SUCCESS)
    {
        *p_digest_size = NRF_CRYPTO_HASH_SIZE_SHA256;
    }

    return ret_val;
}


const nrf_crypto_hash_info_t g_nrf_crypto_hash_sha256_info =
{
    .init_fn        = cc310_backend_hash_sha256_init,
    .update_fn      = cc310_backend_hash_sha256_update,
    .finalize_fn    = cc310_backend_hash_sha256_finalize,
    .digest_size    = NRF_CRYPTO_HASH_SIZE_SHA256,
    .context_size   = sizeof(nrf_crypto_backend_hash_sha256_context_t),
    .hash_mode      = NRF_CRYPTO_HASH_MODE_SHA256
};

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HASH_SHA256)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HASH_SHA512)

// SHA-512 does not use CC310 hardware and therefore will not use a mutex lock

static ret_code_t cc310_backend_hash_sha512_init(void * p_context)
{
    uint32_t                                    ret_val;
    CRYSError_t                                 crys_error;
    CRYS_HASH_OperationMode_t                   hash_mode = CRYS_HASH_SHA512_mode;

    // No parameter testing on this level.
    // This has been done on upper level.

    CRYS_HASHUserContext_t * const p_backend_context
        = &(((nrf_crypto_backend_hash_sha512_context_t * ) p_context)->context);

    crys_error = CRYS_HASH_Init(p_backend_context, hash_mode);
    ret_val = hash_result_get(crys_error);

    return ret_val;
}


static ret_code_t cc310_backend_hash_sha512_update(void     * const p_context,
                                                   uint8_t  const * p_data,
                                                   size_t           size)
{
    ret_code_t      ret_val;
    CRYSError_t     crys_error;

    // Limited parameter testing on this level.
    // This has been done on upper level.

    CRYS_HASHUserContext_t * const p_backend_context
        = &(((nrf_crypto_backend_hash_sha512_context_t *)p_context)->context);

    // Data in flash could lead to silently calculating wrong Hash.
    VERIFY_TRUE(nrfx_is_in_ram(p_data), NRF_ERROR_CRYPTO_INPUT_LOCATION);

    crys_error = CRYS_HASH_Update(p_backend_context, (uint8_t *)p_data, size);

    ret_val = hash_result_get(crys_error);

    return ret_val;
}


static ret_code_t cc310_backend_hash_sha512_finalize(void       * const p_context,
                                                     uint8_t          * p_digest,
                                                     size_t     * const p_digest_size)
{
    ret_code_t              ret_val;
    CRYSError_t             crys_error;
    CRYS_HASH_Result_t *    p_int_digest = (CRYS_HASH_Result_t *)p_digest;

    // Limited parameter testing on this level.
    // This has been done on upper level.

    CRYS_HASHUserContext_t * const p_backend_context
        = &(((nrf_crypto_backend_hash_sha512_context_t *) p_context)->context);

    crys_error = CRYS_HASH_Finish(p_backend_context, *p_int_digest);
    ret_val = hash_result_get(crys_error);

    if (ret_val == NRF_SUCCESS)
    {
        *p_digest_size = NRF_CRYPTO_HASH_SIZE_SHA512;
    }

    return ret_val;
}


const nrf_crypto_hash_info_t g_nrf_crypto_hash_sha512_info =
{
    .init_fn        = cc310_backend_hash_sha512_init,
    .update_fn      = cc310_backend_hash_sha512_update,
    .finalize_fn    = cc310_backend_hash_sha512_finalize,
    .digest_size    = NRF_CRYPTO_HASH_SIZE_SHA512,
    .context_size   = sizeof(nrf_crypto_backend_hash_sha512_context_t),
    .hash_mode      = NRF_CRYPTO_HASH_MODE_SHA512
};


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HASH_SHA512)

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HASH_SHA256) || NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HASH_SHA512) 

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && #if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)
