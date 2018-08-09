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

#include <stdbool.h>
#include "cifra_backend_aes_aead.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_CIFRA_AES_AEAD)

/**@internal @brief Type declaration of a template matching all possible context sizes
 *                  for this backend.
 */
typedef struct
{
    nrf_crypto_aead_internal_context_t header;   /**< Common header for context. */
    cf_aes_context                     context;
} nrf_crypto_backend_cifra_aes_aead_context_t;


static ret_code_t result_get(int error)
{
    switch (error)
    {
        case 0:
            return NRF_SUCCESS;

        case 1:
            return NRF_ERROR_CRYPTO_AEAD_INVALID_MAC;

        default:
            return NRF_ERROR_CRYPTO_INTERNAL;
    }
}

static ret_code_t backend_cifra_init(void * const p_context, uint8_t * p_key)
{
    nrf_crypto_backend_cifra_aes_aead_context_t * p_ctx =
        (nrf_crypto_backend_cifra_aes_aead_context_t *)p_context;

    if ((p_ctx->header.p_info->key_size != NRF_CRYPTO_KEY_SIZE_128) &&
        (p_ctx->header.p_info->key_size != NRF_CRYPTO_KEY_SIZE_192) &&
        (p_ctx->header.p_info->key_size != NRF_CRYPTO_KEY_SIZE_256))
    {
        return NRF_ERROR_CRYPTO_KEY_SIZE;
    }

    VERIFY_TRUE((p_ctx->header.p_info->mode == NRF_CRYPTO_AEAD_MODE_AES_EAX),
                NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE);

    cf_aes_init(&p_ctx->context,
                p_key,
                (p_ctx->header.p_info->key_size)>>3);  // >>3: changes bits to bytes

    return NRF_SUCCESS;
}


static ret_code_t backend_cifra_uninit(void * const p_context)
{
    nrf_crypto_backend_cifra_aes_aead_context_t * p_ctx =
        (nrf_crypto_backend_cifra_aes_aead_context_t *)p_context;

    cf_aes_finish(&p_ctx->context);

    return NRF_SUCCESS;
}

static ret_code_t backend_cifra_crypt(void * const           p_context,
                                      nrf_crypto_operation_t operation,
                                      uint8_t *              p_nonce,
                                      uint8_t                nonce_size,
                                      uint8_t *              p_adata,
                                      size_t                 adata_size,
                                      uint8_t *              p_data_in,
                                      size_t                 data_in_size,
                                      uint8_t *              p_data_out,
                                      uint8_t *              p_mac,
                                      uint8_t                mac_size)
{

    int        result;
    ret_code_t ret_val;

    nrf_crypto_backend_cifra_aes_aead_context_t * p_ctx =
        (nrf_crypto_backend_cifra_aes_aead_context_t *)p_context;

    ret_val = NRF_SUCCESS;

    /* EAX mode allows following mac size: [1 ... 16] */
    if ((mac_size < 1) || (mac_size > NRF_CRYPTO_AES_BLOCK_SIZE))
    {
        return NRF_ERROR_CRYPTO_AEAD_MAC_SIZE;
    }

    if (operation == NRF_CRYPTO_ENCRYPT)
    {
        cf_eax_encrypt(&cf_aes,
                       &p_ctx->context,
                       p_data_in,
                       data_in_size,
                       p_adata,
                       adata_size,
                       p_nonce,
                       (size_t)nonce_size,
                       p_data_out,
                       p_mac,
                       mac_size);
    }
    else if (operation == NRF_CRYPTO_DECRYPT)
    {
        result = cf_eax_decrypt(&cf_aes,
                                &p_ctx->context,
                                p_data_in,
                                data_in_size,
                                p_adata,
                                adata_size,
                                p_nonce,
                                (size_t)nonce_size,
                                p_mac,
                                mac_size,
                                p_data_out);
        ret_val = result_get(result);
    }
    else
    {
        return NRF_ERROR_CRYPTO_INVALID_PARAM;
    }

    return ret_val;
}

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CIFRA_AES_EAX)
nrf_crypto_aead_info_t const g_nrf_crypto_aes_eax_128_info =
{
    .key_size  = NRF_CRYPTO_KEY_SIZE_128,
    .mode      = NRF_CRYPTO_AEAD_MODE_AES_EAX,

    .init_fn   = backend_cifra_init,
    .uninit_fn = backend_cifra_uninit,
    .crypt_fn  = backend_cifra_crypt
};

nrf_crypto_aead_info_t const g_nrf_crypto_aes_eax_192_info =
{
    .key_size  = NRF_CRYPTO_KEY_SIZE_192,
    .mode      = NRF_CRYPTO_AEAD_MODE_AES_EAX,

    .init_fn   = backend_cifra_init,
    .uninit_fn = backend_cifra_uninit,
    .crypt_fn  = backend_cifra_crypt
};

nrf_crypto_aead_info_t const g_nrf_crypto_aes_eax_256_info =
{
    .key_size  = NRF_CRYPTO_KEY_SIZE_256,
    .mode      = NRF_CRYPTO_AEAD_MODE_AES_EAX,

    .init_fn   = backend_cifra_init,
    .uninit_fn = backend_cifra_uninit,
    .crypt_fn  = backend_cifra_crypt
};
#endif

#endif // MODULE_ENABLED(NRF_CRYPTO_AES_CCM_BACKEND_MBEDTLS)
#endif // MODULE_ENABLED(NRF_CRYPTO)
