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
#if NRF_MODULE_ENABLED(NRF_CRYPTO)

#include "nrf_crypto_aes.h"
#include "nrf_crypto_mem.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_shared.h"
#include "nrf_crypto_aes_shared.h"
#include "nrf_crypto_aes_backend.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_AES)

static ret_code_t context_verify(nrf_crypto_aes_internal_context_t const * p_context)
{
    if (p_context == NULL)
    {
        return NRF_ERROR_CRYPTO_CONTEXT_NULL;
    }

    if (p_context->init_value != NRF_CRYPTO_AES_INIT_MAGIC_VALUE)
    {
        return NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED;
    }

    return NRF_SUCCESS;
}

ret_code_t nrf_crypto_aes_init(nrf_crypto_aes_context_t * const    p_context,
                               nrf_crypto_aes_info_t const * const p_info,
                               nrf_crypto_operation_t              operation)
{
    ret_code_t ret_val;

    nrf_crypto_aes_internal_context_t * p_int_context =
        (nrf_crypto_aes_internal_context_t *)p_context;

    ret_val = context_verify(p_int_context);
    VERIFY_TRUE((ret_val == NRF_SUCCESS) || (ret_val == NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED),
                ret_val);

    VERIFY_TRUE(p_info != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);

    p_int_context->p_info = p_info;

    ret_val = p_info->init_fn(p_context, operation);

    if (ret_val == NRF_SUCCESS)
    {
        p_int_context->init_value = NRF_CRYPTO_AES_INIT_MAGIC_VALUE;
    }

    return ret_val;
}

ret_code_t nrf_crypto_aes_uninit(nrf_crypto_aes_context_t * const p_context)
{
    ret_code_t ret_val;

    nrf_crypto_aes_internal_context_t * p_int_context =
        (nrf_crypto_aes_internal_context_t *)p_context;

    ret_val = context_verify(p_int_context);

    if (ret_val == NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED)
    {
        /* If context was uninitialized with function nrf_crypto_aes_finalize it shall be still
           possible to clear init_value */
        if (p_int_context->init_value == NRF_CRYPTO_AES_UNINIT_MAGIC_VALUE)
        {
            ret_val = NRF_SUCCESS;
        }
    }
    VERIFY_SUCCESS(ret_val);

    ret_val = p_int_context->p_info->uninit_fn(p_context);

    p_int_context->init_value = 0;

    return ret_val;
}

ret_code_t nrf_crypto_aes_key_set(nrf_crypto_aes_context_t * const p_context, uint8_t * p_key)
{
    ret_code_t ret_val;

    nrf_crypto_aes_internal_context_t * p_int_context =
        (nrf_crypto_aes_internal_context_t *)p_context;

    ret_val = context_verify(p_int_context);
    VERIFY_SUCCESS(ret_val);

    VERIFY_TRUE((p_key != NULL), NRF_ERROR_CRYPTO_INPUT_NULL);

    ret_val = p_int_context->p_info->key_set_fn(p_context, p_key);

    return ret_val;
}

ret_code_t nrf_crypto_aes_iv_set(nrf_crypto_aes_context_t * const p_context, uint8_t * p_iv)
{
    ret_code_t ret_val;

    nrf_crypto_aes_internal_context_t * p_int_context =
        (nrf_crypto_aes_internal_context_t *)p_context;

    ret_val = context_verify(p_int_context);
    VERIFY_SUCCESS(ret_val);

    VERIFY_TRUE((p_int_context->p_info->iv_set_fn != NULL), NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE);

    VERIFY_TRUE((p_iv != NULL), NRF_ERROR_CRYPTO_INPUT_NULL);

    ret_val = p_int_context->p_info->iv_set_fn(p_context, p_iv);

    return ret_val;
}

ret_code_t nrf_crypto_aes_iv_get(nrf_crypto_aes_context_t * const p_context, uint8_t * p_iv)
{
    ret_code_t ret_val;

    nrf_crypto_aes_internal_context_t * p_int_context =
        (nrf_crypto_aes_internal_context_t *)p_context;

    ret_val = context_verify(p_int_context);
    if (ret_val == NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED)
    {
        /* If context was uninitialized with function nrf_crypto_aes_finalize it shall be still
           possible to read IV value */
        if (p_int_context->init_value == NRF_CRYPTO_AES_UNINIT_MAGIC_VALUE)
        {
            ret_val = NRF_SUCCESS;
        }
    }
    VERIFY_SUCCESS(ret_val);

    VERIFY_TRUE((p_iv != NULL), NRF_ERROR_CRYPTO_INPUT_NULL);

    VERIFY_TRUE((p_int_context->p_info->iv_get_fn != NULL), NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE);

    ret_val = p_int_context->p_info->iv_get_fn(p_context, p_iv);

    return ret_val;
}

ret_code_t nrf_crypto_aes_update(nrf_crypto_aes_context_t * const p_context,
                                 uint8_t *                        p_data_in,
                                 size_t                           data_size,
                                 uint8_t *                        p_data_out)
{
    ret_code_t ret_val;

    nrf_crypto_aes_internal_context_t * p_int_context =
        (nrf_crypto_aes_internal_context_t *)p_context;

    ret_val = context_verify(p_int_context);
    VERIFY_SUCCESS(ret_val);

    VERIFY_TRUE((data_size != 0), NRF_ERROR_CRYPTO_INPUT_LENGTH);

    VERIFY_TRUE((p_data_in != NULL), NRF_ERROR_CRYPTO_INPUT_NULL);

    VERIFY_TRUE((p_data_out != NULL), NRF_ERROR_CRYPTO_OUTPUT_NULL);

    if ((data_size & 0xF) != 0)
    {
        VERIFY_TRUE((p_int_context->p_info->mode == NRF_CRYPTO_AES_MODE_CFB),
                    NRF_ERROR_CRYPTO_INPUT_LENGTH);
    }

    ret_val = p_int_context->p_info->update_fn(p_context,
                                               p_data_in,
                                               data_size,
                                               p_data_out);

    return ret_val;
}

ret_code_t nrf_crypto_aes_finalize(nrf_crypto_aes_context_t * const p_context,
                                   uint8_t *                        p_data_in,
                                   size_t                           data_size,
                                   uint8_t *                        p_data_out,
                                   size_t *                         p_data_out_size)
{
    ret_code_t ret_val;

    nrf_crypto_aes_internal_context_t * p_int_context =
        (nrf_crypto_aes_internal_context_t *)p_context;

    ret_val = context_verify(p_int_context);
    VERIFY_SUCCESS(ret_val);

    VERIFY_TRUE((p_data_in != NULL), NRF_ERROR_CRYPTO_INPUT_NULL);

    VERIFY_TRUE((p_data_out != NULL), NRF_ERROR_CRYPTO_OUTPUT_NULL);

    VERIFY_TRUE((p_data_out_size != NULL), NRF_ERROR_CRYPTO_OUTPUT_NULL);

    ret_val = p_int_context->p_info->finalize_fn(p_context,
                                                 p_data_in,
                                                 data_size,
                                                 p_data_out,
                                                 p_data_out_size);

    VERIFY_TRUE((ret_val == NRF_SUCCESS), ret_val);

    ret_val = nrf_crypto_aes_uninit(p_context);

    if (ret_val == NRF_SUCCESS)
    {
        /* This line will allow to read IV for AES supporting IV get function. */
        p_int_context->init_value = NRF_CRYPTO_AES_UNINIT_MAGIC_VALUE;
    }

    return ret_val;
}

ret_code_t nrf_crypto_aes_crypt(nrf_crypto_aes_context_t * const    p_context,
                                nrf_crypto_aes_info_t const * const p_info,
                                nrf_crypto_operation_t              operation,
                                uint8_t *                           p_key,
                                uint8_t *                           p_iv,
                                uint8_t *                           p_data_in,
                                size_t                              data_size,
                                uint8_t *                           p_data_out,
                                size_t *                            p_data_out_size)
{
    ret_code_t ret_val;
    void *     p_allocated_context = NULL;

    nrf_crypto_aes_context_t * p_ctx = p_context;

    VERIFY_TRUE(p_info != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);

    if (p_ctx == NULL)
    {
        p_allocated_context = NRF_CRYPTO_ALLOC(p_info->context_size);
        if (p_allocated_context == NULL)
        {
            return NRF_ERROR_CRYPTO_ALLOC_FAILED;
        }
        p_ctx = (nrf_crypto_aes_context_t *)p_allocated_context;
    }

    ret_val = nrf_crypto_aes_init(p_ctx, p_info, operation);
    NRF_CRYPTO_VERIFY_SUCCESS_DEALLOCATE(ret_val, p_allocated_context);

    ret_val = nrf_crypto_aes_key_set(p_ctx, p_key);
    NRF_CRYPTO_VERIFY_SUCCESS_DEALLOCATE(ret_val, p_allocated_context);

    ret_val = nrf_crypto_aes_iv_set(p_ctx, p_iv);
    /* not all AES modes support IV */
    if (ret_val != NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE)
    {
        NRF_CRYPTO_VERIFY_SUCCESS_DEALLOCATE(ret_val, p_allocated_context);
    }

    ret_val = nrf_crypto_aes_finalize(p_ctx,
                                      p_data_in,
                                      data_size,
                                      p_data_out,
                                      p_data_out_size);
    if (ret_val != NRF_SUCCESS)
    {
        /* Context was not successfully deinitialized in nrf_crypto_aes_finalize */
        UNUSED_RETURN_VALUE(nrf_crypto_aes_uninit(p_ctx));
    }

    if (p_allocated_context != NULL)
    {
        NRF_CRYPTO_FREE(p_allocated_context);
    }

    return ret_val;
}

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_AES)
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)

