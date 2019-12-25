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

#include "stddef.h"
#include "nrf_log.h"
#include "nrf_crypto_hmac.h"
#include "nrf_crypto_hmac_shared.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_init.h"
#include "nrf_crypto_mem.h"
#include "nrf_crypto_shared.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_HMAC)

// Magic word that is set when initializing the context and checked by functions that use it.
#define NRF_CRYPTO_HMAC_INIT_MAGIC_VALUE     0xBADEBA11


static ret_code_t verify_context_valid(nrf_crypto_hmac_internal_context_t * const p_context)
{
    if (p_context == NULL)
    {
        return NRF_ERROR_CRYPTO_CONTEXT_NULL;
    }
    else if (p_context->init_value != NRF_CRYPTO_HMAC_INIT_MAGIC_VALUE)
    {
        return NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED;
    }
    else
    {
        return NRF_SUCCESS;
    }
}


ret_code_t nrf_crypto_hmac_init(nrf_crypto_hmac_context_t   * const p_context,
                                nrf_crypto_hmac_info_t      const * p_info,
                                uint8_t                     const * p_key,
                                size_t                              key_size)
{
    ret_code_t                           err_code;
    nrf_crypto_hmac_internal_context_t * p_ctx = (nrf_crypto_hmac_internal_context_t *)p_context;

    VERIFY_TRUE(nrf_crypto_is_initialized(), NRF_ERROR_CRYPTO_NOT_INITIALIZED);

    // Validate input
    VERIFY_TRUE(p_ctx != NULL, NRF_ERROR_CRYPTO_CONTEXT_NULL);
    VERIFY_TRUE(p_info != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    VERIFY_TRUE(p_key != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    VERIFY_TRUE(key_size > 0, NRF_ERROR_CRYPTO_INPUT_LENGTH);

    // Initialize generic part of the context
    p_ctx->p_info = p_info;

    // Do backend specific initialization by calling the backend init function pointed
    // to in the configuration struct in the context (nrf_crypto_hmac_config_t)
    err_code = p_ctx->p_info->init_fn(p_context, p_key, key_size);
    if (err_code == NRF_SUCCESS)
    {
        p_ctx->init_value = NRF_CRYPTO_HMAC_INIT_MAGIC_VALUE;
    }

    return err_code;
}


ret_code_t nrf_crypto_hmac_update(nrf_crypto_hmac_context_t * const p_context,
                                  uint8_t                   const * p_data,
                                  size_t                            data_size)
{
    ret_code_t err_code;

    // The context header by definition has to be the first element of the context struct.
    nrf_crypto_hmac_internal_context_t * p_ctx = (nrf_crypto_hmac_internal_context_t *)p_context;

    // Validate input
    err_code = verify_context_valid(p_ctx);
    VERIFY_SUCCESS(err_code);
    VERIFY_TRUE(p_data != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    VERIFY_TRUE(data_size > 0, NRF_ERROR_CRYPTO_INPUT_LENGTH);

    // Call backend specific update function (pointed to by config struct in context)
    err_code = p_ctx->p_info->update_fn(p_context, p_data, data_size);

    return err_code;
}


ret_code_t nrf_crypto_hmac_finalize(nrf_crypto_hmac_context_t   * const p_context,
                                    uint8_t                           * p_digest,
                                    size_t                      * const p_digest_size)
{
    ret_code_t err_code;

    // The context header by definition has to be the first element of the context struct.
    nrf_crypto_hmac_internal_context_t * p_ctx = (nrf_crypto_hmac_internal_context_t *)p_context;

    // Validate input
    err_code = verify_context_valid(p_ctx);
    VERIFY_SUCCESS(err_code);
    VERIFY_TRUE(p_digest != NULL, NRF_ERROR_CRYPTO_OUTPUT_NULL);
    VERIFY_TRUE(*p_digest_size >= p_ctx->p_info->digest_size, NRF_ERROR_CRYPTO_OUTPUT_LENGTH);

    // Call backend specific finish function (pointed to by config struct in context)
    err_code = p_ctx->p_info->finalize_fn(p_context, p_digest, p_digest_size);

    return err_code;
}


ret_code_t nrf_crypto_hmac_calculate(nrf_crypto_hmac_context_t  * const p_context,
                                     nrf_crypto_hmac_info_t     const * p_info,
                                     uint8_t                          * p_digest,
                                     size_t                     * const p_digest_size,
                                     uint8_t                    const * p_key,
                                     size_t                             key_size,
                                     uint8_t                    const * p_data,
                                     size_t                             data_size)
{
    ret_code_t                      err_code;
    nrf_crypto_hmac_context_t     * p_ctx;
    void                          * p_allocated_context = NULL;

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
        p_ctx = (nrf_crypto_hmac_context_t *)p_allocated_context;
    }
    else
    {
        p_ctx = (nrf_crypto_hmac_context_t *)p_context;
    }

    // Perform integrated HMAC calculation by caling the frontend functions defined in this file
    err_code = nrf_crypto_hmac_init(p_ctx, p_info, p_key, key_size);
    NRF_CRYPTO_VERIFY_SUCCESS_DEALLOCATE(err_code, p_allocated_context);

    err_code = nrf_crypto_hmac_update(p_ctx, p_data, data_size);
    NRF_CRYPTO_VERIFY_SUCCESS_DEALLOCATE(err_code, p_allocated_context);

    err_code = nrf_crypto_hmac_finalize(p_ctx, p_digest, p_digest_size);
    NRF_CRYPTO_VERIFY_SUCCESS_DEALLOCATE(err_code, p_allocated_context);

    // Free context if allocated internally
    if (p_allocated_context != NULL)
    {
        NRF_CRYPTO_FREE(p_allocated_context);
    }

    return err_code;
}

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_HMAC)
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
