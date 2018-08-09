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

#include "nrf_crypto_error.h"
#include "nrf_crypto_aead.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_AEAD)

static ret_code_t context_verify(nrf_crypto_aead_internal_context_t const * p_context)
{
    VERIFY_TRUE((p_context != NULL), NRF_ERROR_CRYPTO_CONTEXT_NULL);

    VERIFY_TRUE((p_context->init_value == NRF_CRYPTO_AEAD_INIT_MAGIC_VALUE),
                NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED);

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_aead_init(nrf_crypto_aead_context_t * const    p_context,
                                nrf_crypto_aead_info_t const * const p_info,
                                uint8_t *                            p_key)
{
    ret_code_t ret_val;

    nrf_crypto_aead_internal_context_t * p_int_context =
        (nrf_crypto_aead_internal_context_t *)p_context;

    VERIFY_TRUE((p_info != NULL), NRF_ERROR_CRYPTO_INPUT_NULL);

    VERIFY_TRUE((p_key != NULL), NRF_ERROR_CRYPTO_INPUT_NULL);

    ret_val = context_verify(p_int_context);
    VERIFY_TRUE((ret_val == NRF_SUCCESS) || (ret_val == NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED),
                ret_val);

    p_int_context->init_value = NRF_CRYPTO_AEAD_INIT_MAGIC_VALUE;
    p_int_context->p_info     = p_info;

    ret_val = p_info->init_fn(p_context, p_key);

    if (ret_val != NRF_SUCCESS)
    {
        p_int_context->init_value = 0;
    }

    return ret_val;
}

ret_code_t nrf_crypto_aead_uninit(void * const p_context)
{
    ret_code_t ret_val;

    nrf_crypto_aead_internal_context_t * p_int_context =
        (nrf_crypto_aead_internal_context_t *)p_context;

    ret_val = context_verify(p_int_context);
    VERIFY_SUCCESS(ret_val);

    ret_val = p_int_context->p_info->uninit_fn(p_context);

    p_int_context->init_value = 0;

    return ret_val;
}

ret_code_t nrf_crypto_aead_crypt(nrf_crypto_aead_context_t * const p_context,
                                 nrf_crypto_operation_t            operation,
                                 uint8_t *                         p_nonce,
                                 uint8_t                           nonce_size,
                                 uint8_t *                         p_adata,
                                 size_t                            adata_size,
                                 uint8_t *                         p_data_in,
                                 size_t                            data_in_size,
                                 uint8_t *                         p_data_out,
                                 uint8_t *                         p_mac,
                                 uint8_t                           mac_size)
{
    ret_code_t ret_val;

    nrf_crypto_aead_internal_context_t * p_int_context =
        (nrf_crypto_aead_internal_context_t *)p_context;

    ret_val = context_verify(p_int_context);
    VERIFY_SUCCESS(ret_val);

    VERIFY_FALSE(((p_nonce == NULL) && (nonce_size != 0)),
                 NRF_ERROR_CRYPTO_INPUT_NULL);

    /* If mac_size == 0 MAC is updated and not stored under p_mac */
    VERIFY_FALSE(((p_mac == NULL) && (mac_size != 0)),
                 NRF_ERROR_CRYPTO_INPUT_NULL);

    VERIFY_FALSE(((p_adata == NULL) && (adata_size != 0)),
                 NRF_ERROR_CRYPTO_INPUT_NULL);

    VERIFY_FALSE(((p_data_in == NULL) && (data_in_size != 0)),
                 NRF_ERROR_CRYPTO_INPUT_NULL);

    VERIFY_FALSE(((p_data_out == NULL) && (data_in_size != 0)),
                 NRF_ERROR_CRYPTO_OUTPUT_NULL);

    ret_val = p_int_context->p_info->crypt_fn(p_context,
                                              operation,
                                              p_nonce,
                                              nonce_size,
                                              p_adata,
                                              adata_size,
                                              p_data_in,
                                              data_in_size,
                                              p_data_out,
                                              p_mac,
                                              mac_size);
    return ret_val;
}

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_AEAD)
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)

