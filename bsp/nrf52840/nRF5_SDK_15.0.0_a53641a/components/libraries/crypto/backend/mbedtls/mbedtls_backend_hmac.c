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
#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS)

#include "nrf_log.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_types.h"
#include "mbedtls_backend_hmac.h"


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_HMAC_SHA256)

static ret_code_t mbedtls_backend_hmac_init_sha256(void     * const p_context,
                                                   uint8_t  const * p_key,
                                                   size_t           key_size)
{
    int err_code;
    nrf_crypto_backend_mbedtls_hmac_sha256_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_hmac_sha256_context_t *)p_context;

    // Memset context to 0. This is equevalend with a call to mbedtls_md_init().
    memset(p_ctx->md_ctx_buffer, 0, sizeof(p_ctx->md_ctx_buffer));
    memset(p_ctx->hmac_ctx_buffer, 0, sizeof(p_ctx->hmac_ctx_buffer));

    // Set info and context pointers to buffer allocated by user.
    // This is Normally handled by mbedtls_md_setup(), but has to be done here in order
    // to avoid dynamic allocation of memory inside mbed TLS.
    p_ctx->mbedtls_ctx.md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
    p_ctx->mbedtls_ctx.md_ctx = p_ctx->md_ctx_buffer;
    p_ctx->mbedtls_ctx.hmac_ctx = p_ctx->hmac_ctx_buffer;

    // Enter key to start
    err_code = mbedtls_md_hmac_starts(&p_ctx->mbedtls_ctx,
                                      p_key,
                                      key_size);

    if (err_code != 0)
    {
        NRF_LOG_ERROR("Error in mbedtls_md_hmac_starts: %u", err_code);
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    return NRF_SUCCESS;
}


static ret_code_t mbedtls_backend_hmac_update_sha256(void       * const p_context,
                                                     uint8_t    const * p_data,
                                                     size_t             size)
{
    int err_code;
    nrf_crypto_backend_mbedtls_hmac_sha256_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_hmac_sha256_context_t *)p_context;

    err_code = mbedtls_md_hmac_update(&p_ctx->mbedtls_ctx, p_data, size);
    if (err_code != 0)
    {
        NRF_LOG_ERROR("Error in mbedtls_md_hmac_update: %u", err_code);
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    return NRF_SUCCESS;
}


static ret_code_t mbedtls_backend_hmac_finalize_sha256(void     * const p_context,
                                                       uint8_t        * p_digest,
                                                       size_t   * const p_size)
{
    int err_code;
    nrf_crypto_backend_mbedtls_hmac_sha256_context_t * const p_ctx =
        (nrf_crypto_backend_mbedtls_hmac_sha256_context_t *)p_context;

    // Set the digest length to 0 so that this is used in case of any error.
    *p_size = 0;

    err_code = mbedtls_md_hmac_finish(&p_ctx->mbedtls_ctx, p_digest);
    if (err_code != 0)
    {
        NRF_LOG_ERROR("Error in mbedtls_md_hmac_finish: %u", err_code);
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    *p_size = p_ctx->header.p_info->digest_size;

    return NRF_SUCCESS;
}


// Information structure for HMAC SHA256 using mbed TLS backend.
const nrf_crypto_hmac_info_t g_nrf_crypto_hmac_sha256_info =
{
    .init_fn        = mbedtls_backend_hmac_init_sha256,
    .update_fn      = mbedtls_backend_hmac_update_sha256,
    .finalize_fn    = mbedtls_backend_hmac_finalize_sha256,
    .digest_size    = NRF_CRYPTO_HASH_SIZE_SHA256,
    .context_size   = sizeof(nrf_crypto_backend_hmac_sha256_context_t),
    .type           = NRF_CRYPTO_HMAC_SHA256_TYPE
};

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_HMAC_SHA256)



#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_HMAC_SHA512)

static ret_code_t mbedtls_backend_hmac_init_sha512(void     * const p_context,
                                                   uint8_t  const * p_key,
                                                   size_t           key_size)
{
    int err_code;
    nrf_crypto_backend_mbedtls_hmac_sha512_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_hmac_sha512_context_t *)p_context;

    // Memset context to 0. This is equevalend with a call to mbedtls_md_init().
    memset(p_ctx->md_ctx_buffer, 0, sizeof(p_ctx->md_ctx_buffer));
    memset(p_ctx->hmac_ctx_buffer, 0, sizeof(p_ctx->hmac_ctx_buffer));

    // Set info and context pointers to buffer allocated by user.
    // (Normally handled by mbedtls_md_setup())
    p_ctx->mbedtls_ctx.md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA512);
    p_ctx->mbedtls_ctx.md_ctx = p_ctx->md_ctx_buffer;
    p_ctx->mbedtls_ctx.hmac_ctx = p_ctx->hmac_ctx_buffer;

    // Enter key to start
    err_code = mbedtls_md_hmac_starts(&p_ctx->mbedtls_ctx, p_key, key_size);
    if (err_code != 0)
    {
        NRF_LOG_ERROR("Error in mbedtls_md_hmac_starts: %u", err_code);
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    return NRF_SUCCESS;
}


static ret_code_t mbedtls_backend_hmac_update_sha512(void       * const p_context,
                                                     uint8_t    const * p_data,
                                                     size_t             size)
{
    int err_code;
    nrf_crypto_backend_mbedtls_hmac_sha512_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_hmac_sha512_context_t *)p_context;

    err_code = mbedtls_md_hmac_update(&p_ctx->mbedtls_ctx, p_data, size);
    if (err_code != 0)
    {
        NRF_LOG_ERROR("Error in mbedtls_md_hmac_update: %u", err_code);
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    return NRF_SUCCESS;
}


static ret_code_t mbedtls_backend_hmac_finalize_sha512(void     * const p_context,
                                                       uint8_t        * p_digest,
                                                       size_t   * const p_size)
{
    int err_code;
    nrf_crypto_backend_mbedtls_hmac_sha512_context_t * p_ctx =
        (nrf_crypto_backend_mbedtls_hmac_sha512_context_t *)p_context;

    // Set the digest length to 0 so that this is used in case of any error.
    *p_size = 0;

    err_code = mbedtls_md_hmac_finish(&p_ctx->mbedtls_ctx, p_digest);
    if (err_code != 0)
    {
        NRF_LOG_ERROR("Error in mbedtls_md_hmac_finish: %u", err_code);
        return NRF_ERROR_CRYPTO_INTERNAL;    }

    *p_size = p_ctx->header.p_info->digest_size;

    return NRF_SUCCESS;
}


// Information structure for HMAC SHA512 using mbed TLS backend.
const nrf_crypto_hmac_info_t g_nrf_crypto_hmac_sha512_info =
{
    .init_fn        = mbedtls_backend_hmac_init_sha512,
    .update_fn      = mbedtls_backend_hmac_update_sha512,
    .finalize_fn    = mbedtls_backend_hmac_finalize_sha512,
    .digest_size    = NRF_CRYPTO_HASH_SIZE_SHA512,
    .context_size   = sizeof(nrf_crypto_backend_hmac_sha512_context_t),
    .type           = NRF_CRYPTO_HMAC_SHA512_TYPE
};

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_HMAC_SHA512)
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS)
