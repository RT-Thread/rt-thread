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
#include <drivers/nrfx_common.h>
#if NRF_MODULE_ENABLED(NRF_CRYPTO)

#include "nrf_crypto_error.h"
#include "mbedtls_backend_aes_aead.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_MBEDTLS_AES_AEAD)

/**@internal @brief Type declaration of a template suiting all possible context sizes
 *                  for this backend.
 */
typedef union
{
    nrf_crypto_aead_internal_context_t header;      /**< Common header for context. */
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CCM)
    nrf_crypto_backend_aes_ccm_context_t ccm;
#endif
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_GCM)
    nrf_crypto_backend_aes_gcm_context_t gcm;
#endif
} nrf_crypto_backend_mbedtls_aes_aead_context_t;


static ret_code_t result_get(int error)
{
    ret_code_t ret_val;

    switch (error)
    {
        case 0:
            ret_val = NRF_SUCCESS;
            break;

        case MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA:
            ret_val = NRF_ERROR_CRYPTO_INPUT_LENGTH;
            break;

        case MBEDTLS_ERR_CIPHER_ALLOC_FAILED:
            ret_val = NRF_ERROR_CRYPTO_ALLOC_FAILED;
            break;

        case MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE:
            ret_val = NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
            break;

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CCM)
        case MBEDTLS_ERR_CCM_BAD_INPUT:
            ret_val = NRF_ERROR_CRYPTO_INVALID_PARAM;
            break;

        case MBEDTLS_ERR_CCM_AUTH_FAILED:
            ret_val = NRF_ERROR_CRYPTO_AEAD_INVALID_MAC;
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_GCM)
         case MBEDTLS_ERR_GCM_BAD_INPUT:
            ret_val = NRF_ERROR_CRYPTO_INVALID_PARAM;
            break;

         case MBEDTLS_ERR_GCM_AUTH_FAILED:
            ret_val = NRF_ERROR_CRYPTO_AEAD_INVALID_MAC;
            break;
#endif

        default:
            ret_val = NRF_ERROR_CRYPTO_INTERNAL;
            break;
    }
    return ret_val;
}

static ret_code_t backend_mbedtls_init(void * const p_context, uint8_t * p_key)
{
    int        result;
    ret_code_t ret_val;

    nrf_crypto_backend_mbedtls_aes_aead_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_aes_aead_context_t *)p_context;

    if ((p_ctx->header.p_info->key_size != NRF_CRYPTO_KEY_SIZE_128) &&
        (p_ctx->header.p_info->key_size != NRF_CRYPTO_KEY_SIZE_192) &&
        (p_ctx->header.p_info->key_size != NRF_CRYPTO_KEY_SIZE_256))
    {
        return NRF_ERROR_CRYPTO_KEY_SIZE;
    }

    switch (p_ctx->header.p_info->mode)
    {
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CCM)
        case NRF_CRYPTO_AEAD_MODE_AES_CCM:
            mbedtls_ccm_init(&p_ctx->ccm.context);

            result = mbedtls_ccm_setkey(&p_ctx->ccm.context,
                                        MBEDTLS_CIPHER_ID_AES,
                                        p_key,
                                        p_ctx->header.p_info->key_size);
            break;
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_GCM)
        case NRF_CRYPTO_AEAD_MODE_AES_GCM:
            mbedtls_gcm_init(&p_ctx->gcm.context);

            result = mbedtls_gcm_setkey(&p_ctx->gcm.context,
                                        MBEDTLS_CIPHER_ID_AES,
                                        p_key,
                                        p_ctx->header.p_info->key_size);
            break;
#endif

        default:
            return NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
    }

    if (result != 0)
    {
        ret_val = result_get(result);
        return ret_val;
    }

    return NRF_SUCCESS;
}

static ret_code_t backend_mbedtls_uninit(void * const p_context)
{
    nrf_crypto_backend_mbedtls_aes_aead_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_aes_aead_context_t *)p_context;

    if (p_ctx->header.p_info->mode == NRF_CRYPTO_AEAD_MODE_AES_CCM)
    {
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CCM)
        mbedtls_ccm_free(&p_ctx->ccm.context);
#endif
    }
    else
    {
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_GCM)
        mbedtls_gcm_free(&p_ctx->gcm.context);
#endif
    }

    return NRF_SUCCESS;
}

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CCM)
static ret_code_t backend_mbedtls_ccm_crypt(void * const            p_context,
                                            nrf_crypto_operation_t  operation,
                                            uint8_t *               p_nonce,
                                            uint8_t                 nonce_size,
                                            uint8_t *               p_adata,
                                            size_t                  adata_size,
                                            uint8_t *               p_data_in,
                                            size_t                  data_in_size,
                                            uint8_t *               p_data_out,
                                            uint8_t *               p_mac,
                                            uint8_t                 mac_size)
{
    int        result;
    ret_code_t ret_val;

    nrf_crypto_backend_mbedtls_aes_aead_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_aes_aead_context_t *)p_context;

    /* CCM mode allows following MAC sizes: [4, 6, 8, 10, 12, 14, 16] */
    if ((mac_size < NRF_CRYPTO_AES_CCM_MAC_MIN) || (mac_size > NRF_CRYPTO_AES_CCM_MAC_MAX) ||
        ((mac_size & 0x01) != 0))
    {
        return NRF_ERROR_CRYPTO_AEAD_MAC_SIZE;
    }

    if ((nonce_size < NRF_CRYPTO_AES_CCM_NONCE_SIZE_MIN) ||
        (nonce_size > NRF_CRYPTO_AES_CCM_NONCE_SIZE_MAX))
    {
        return NRF_ERROR_CRYPTO_AEAD_NONCE_SIZE;
    }

    if (operation == NRF_CRYPTO_ENCRYPT)
    {
        result = mbedtls_ccm_encrypt_and_tag(&p_ctx->ccm.context,
                                             data_in_size,
                                             p_nonce,
                                             nonce_size,
                                             p_adata,
                                             adata_size,
                                             p_data_in,
                                             p_data_out,
                                             p_mac,
                                             (size_t)mac_size);
    }
    else if (operation == NRF_CRYPTO_DECRYPT)
    {
        result = mbedtls_ccm_auth_decrypt(&p_ctx->ccm.context,
                                          data_in_size,
                                          p_nonce,
                                          nonce_size,
                                          p_adata,
                                          adata_size,
                                          p_data_in,
                                          p_data_out,
                                          p_mac,
                                          (size_t)mac_size);
    }
    else
    {
        return NRF_ERROR_CRYPTO_INVALID_PARAM;
    }

    ret_val = result_get(result);

    return ret_val;
}
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_GCM)
static ret_code_t backend_mbedtls_gcm_crypt(void * const            p_context,
                                            nrf_crypto_operation_t  operation,
                                            uint8_t *               p_nonce,
                                            uint8_t                 nonce_size,
                                            uint8_t *               p_adata,
                                            size_t                  adata_size,
                                            uint8_t *               p_data_in,
                                            size_t                  data_in_size,
                                            uint8_t *               p_data_out,
                                            uint8_t *               p_mac,
                                            uint8_t                 mac_size)
{
    int        result;
    ret_code_t ret_val;

    nrf_crypto_backend_mbedtls_aes_aead_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_aes_aead_context_t *)p_context;

    /* GCM allows following MAC size: [4 ... 16] */
    if ((mac_size < NRF_CRYPTO_AES_GCM_MAC_MIN) || (mac_size > NRF_CRYPTO_AES_GCM_MAC_MAX))
    {
        return NRF_ERROR_CRYPTO_AEAD_MAC_SIZE;
    }

    if (operation == NRF_CRYPTO_ENCRYPT)
    {
        result = mbedtls_gcm_crypt_and_tag(&p_ctx->gcm.context,
                                           MBEDTLS_GCM_ENCRYPT,
                                           data_in_size,
                                           p_nonce,
                                           nonce_size,
                                           p_adata,
                                           adata_size,
                                           p_data_in,
                                           p_data_out,
                                           (size_t)mac_size,
                                           p_mac);
    ret_val = result_get(result);
    }
    else if (operation == NRF_CRYPTO_DECRYPT)
    {
        result = mbedtls_gcm_auth_decrypt(&p_ctx->gcm.context,
                                          data_in_size,
                                          p_nonce,
                                          nonce_size,
                                          p_adata,
                                          adata_size,
                                          p_mac,
                                          (size_t)mac_size,
                                          p_data_in,
                                          p_data_out);
        ret_val = result_get(result);
    }
    else
    {
        return NRF_ERROR_CRYPTO_INVALID_PARAM;
    }

    return ret_val;
}
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CCM)
nrf_crypto_aead_info_t const g_nrf_crypto_aes_ccm_128_info =
{
    .key_size  = NRF_CRYPTO_KEY_SIZE_128,
    .mode      = NRF_CRYPTO_AEAD_MODE_AES_CCM,

    .init_fn   = backend_mbedtls_init,
    .uninit_fn = backend_mbedtls_uninit,
    .crypt_fn  = backend_mbedtls_ccm_crypt
};

nrf_crypto_aead_info_t const g_nrf_crypto_aes_ccm_192_info =
{
    .key_size  = NRF_CRYPTO_KEY_SIZE_192,
    .mode      = NRF_CRYPTO_AEAD_MODE_AES_CCM,

    .init_fn   = backend_mbedtls_init,
    .uninit_fn = backend_mbedtls_uninit,
    .crypt_fn  = backend_mbedtls_ccm_crypt
};

nrf_crypto_aead_info_t const g_nrf_crypto_aes_ccm_256_info =
{
    .key_size  = NRF_CRYPTO_KEY_SIZE_256,
    .mode      = NRF_CRYPTO_AEAD_MODE_AES_CCM,

    .init_fn   = backend_mbedtls_init,
    .uninit_fn = backend_mbedtls_uninit,
    .crypt_fn  = backend_mbedtls_ccm_crypt
};
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_GCM)
nrf_crypto_aead_info_t const g_nrf_crypto_aes_gcm_128_info =
{
    .key_size  = NRF_CRYPTO_KEY_SIZE_128,
    .mode      = NRF_CRYPTO_AEAD_MODE_AES_GCM,

    .init_fn   = backend_mbedtls_init,
    .uninit_fn = backend_mbedtls_uninit,
    .crypt_fn  = backend_mbedtls_gcm_crypt
};

nrf_crypto_aead_info_t const g_nrf_crypto_aes_gcm_192_info =
{
    .key_size  = NRF_CRYPTO_KEY_SIZE_192,
    .mode      = NRF_CRYPTO_AEAD_MODE_AES_GCM,

    .init_fn   = backend_mbedtls_init,
    .uninit_fn = backend_mbedtls_uninit,
    .crypt_fn  = backend_mbedtls_gcm_crypt
};

nrf_crypto_aead_info_t const g_nrf_crypto_aes_gcm_256_info =
{
    .key_size  = NRF_CRYPTO_KEY_SIZE_256,
    .mode      = NRF_CRYPTO_AEAD_MODE_AES_GCM,

    .init_fn   = backend_mbedtls_init,
    .uninit_fn = backend_mbedtls_uninit,
    .crypt_fn  = backend_mbedtls_gcm_crypt
};
#endif

#endif // MODULE_ENABLED(NRF_CRYPTO_MBEDTLS_AES_AEAD)
#endif // MODULE_ENABLED(NRF_CRYPTO)
