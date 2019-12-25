/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
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

#include "nrf_crypto_error.h"
#include "nrf_crypto_hash.h"
#include "nrf_crypto_mem.h"
#include "nrf_crypto_hash_backend.h"
#include "nrf_crypto_hash_shared.h"
#include "nrf_crypto_shared.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_HASH)

static ret_code_t verify_context(nrf_crypto_hash_internal_context_t * const p_context)
{
    if (p_context == NULL)
    {
        return NRF_ERROR_CRYPTO_CONTEXT_NULL;
    }

    if (p_context->init_val != NRF_CRYPTO_HASH_INIT_VALUE)
    {
        return NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED;
    }

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_hash_init(nrf_crypto_hash_context_t * const p_context,
                                nrf_crypto_hash_info_t    const * p_info)
{
    ret_code_t                              ret_val;
    nrf_crypto_hash_internal_context_t    * p_int_context;

    VERIFY_TRUE(p_context != NULL, NRF_ERROR_CRYPTO_CONTEXT_NULL);
    VERIFY_TRUE(p_info != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);

    p_int_context = (nrf_crypto_hash_internal_context_t *) p_context;
    p_int_context->p_info = p_info;

    ret_val = p_info->init_fn(p_context);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    p_int_context->init_val = NRF_CRYPTO_HASH_INIT_VALUE;

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_hash_update(nrf_crypto_hash_context_t   * const p_context,
                                  uint8_t                     const * p_data,
                                  size_t                              data_size)
{
    ret_code_t                              ret_val;
    nrf_crypto_hash_internal_context_t    * p_int_context
        = (nrf_crypto_hash_internal_context_t *) p_context;

    ret_val = verify_context(p_int_context);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    VERIFY_TRUE(p_data != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    
    // Allow zero size input
    if (data_size == 0)
    {
        return NRF_SUCCESS;
    }

    ret_val = p_int_context->p_info->update_fn(p_context, p_data, data_size);

    return ret_val;
}


ret_code_t nrf_crypto_hash_finalize(nrf_crypto_hash_context_t * const p_context,
                                    uint8_t                         * p_digest,
                                    size_t                    * const p_digest_size)
{
    ret_code_t                              ret_val;
    nrf_crypto_hash_internal_context_t    * p_int_context
        = (nrf_crypto_hash_internal_context_t *) p_context;

    ret_val = verify_context(p_int_context);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    VERIFY_TRUE(p_digest != NULL, NRF_ERROR_CRYPTO_OUTPUT_NULL);
    VERIFY_TRUE(*p_digest_size >= p_int_context->p_info->digest_size, NRF_ERROR_CRYPTO_OUTPUT_LENGTH);

    ret_val = p_int_context->p_info->finalize_fn(p_context, p_digest, p_digest_size);

    return ret_val;
}


ret_code_t nrf_crypto_hash_calculate(nrf_crypto_hash_context_t    * const p_context,
                                     nrf_crypto_hash_info_t       const * p_info,
                                     uint8_t                      const * p_data,
                                     size_t                               data_size,
                                     uint8_t                            * p_digest,
                                     size_t                       * const p_digest_size)
{
    ret_code_t                      ret_val;
    nrf_crypto_hash_context_t     * p_ctx  = (nrf_crypto_hash_context_t *)p_context;
    void                          * p_allocated_context = NULL;

// Internal allocation of context not available for CC310_BL in order to save code size.
#if defined(NRF_CRYPTO_BACKEND_CC310_BL_HASH_SHA256_ENABLED) && (NRF_CRYPTO_BACKEND_CC310_BL_HASH_SHA256_ENABLED == 1)
    
    // Do nothing
    
#elif defined(NRF_CRYPTO_BACKEND_CC310_BL_HASH_SHA256_ENABLED) && (NRF_CRYPTO_BACKEND_CC310_BL_HASH_SHA256_ENABLED == 0)
    
    // Validate input. Only validate input parameters that are used locally, others are validated
    // in the init, update and/or finalize functions.
    VERIFY_TRUE(p_info != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);

    // Allocate context if needed (not provided by the user).
    if (p_context == NULL)
    {
        p_allocated_context = NRF_CRYPTO_ALLOC(p_info->context_size);
        if (p_allocated_context == NULL)
        {
            return NRF_ERROR_CRYPTO_ALLOC_FAILED;
        }
        p_ctx = (nrf_crypto_hash_context_t *)p_allocated_context;
    }
    
#else

    #warning NRF_CRYPTO_BACKEND_CC310_BL_HASH_SHA256_ENABLED define not found in sdk_config.h (Is the sdk_config.h valid?).
    
#endif // NRF_CRYPTO_BACKEND_CC310_BL_HASH_SHA256_ENABLED

    ret_val = nrf_crypto_hash_init(p_ctx, p_info);
    NRF_CRYPTO_VERIFY_SUCCESS_DEALLOCATE(ret_val, p_allocated_context);

    ret_val = nrf_crypto_hash_update(p_ctx, p_data, data_size);
    NRF_CRYPTO_VERIFY_SUCCESS_DEALLOCATE(ret_val, p_allocated_context);

    ret_val = nrf_crypto_hash_finalize(p_ctx, p_digest, p_digest_size);
    NRF_CRYPTO_VERIFY_SUCCESS_DEALLOCATE(ret_val, p_allocated_context);

#if !NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_HASH_SHA256)
    // Free context if allocated internally
    if (p_allocated_context != NULL)
    {
        NRF_CRYPTO_FREE(p_allocated_context);
    }
#endif // !NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_HASH_SHA256)

    return NRF_SUCCESS;
}

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_HASH)

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
