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
#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON)

#include "nrf_log.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_types.h"
#include "oberon_backend_hmac.h"


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_HMAC_SHA256)

#define HMAC_SHA256_BLOCK_SIZE 64

static ret_code_t oberon_backend_hmac_init_sha256(void      * const p_context,
                                                  uint8_t   const * p_key,
                                                  size_t            key_size)
{
    nrf_crypto_backend_oberon_hmac_sha256_context_t * p_ctx =
        (nrf_crypto_backend_oberon_hmac_sha256_context_t *)p_context;

    occ_hmac_sha256_init(&p_ctx->oberon_ctx, p_key, key_size);

    return NRF_SUCCESS;
}


static ret_code_t oberon_backend_hmac_update_sha256(void    * const p_context,
                                                    uint8_t const * p_data,
                                                    size_t          size)
{
    nrf_crypto_backend_oberon_hmac_sha256_context_t * p_ctx =
        (nrf_crypto_backend_oberon_hmac_sha256_context_t *)p_context;

    occ_hmac_sha256_update(&p_ctx->oberon_ctx, p_data, size);

    return NRF_SUCCESS;
}


static ret_code_t oberon_backend_hmac_finalize_sha256(void      * const p_context,
                                                      uint8_t         * p_digest,
                                                      size_t    * const p_size)
{
    nrf_crypto_backend_oberon_hmac_sha256_context_t * const p_ctx =
        (nrf_crypto_backend_oberon_hmac_sha256_context_t *)p_context;

    occ_hmac_sha256_final(p_digest, &p_ctx->oberon_ctx);

    // Assume operation was successful and update the digest size accordingly.
    *p_size = p_ctx->header.p_info->digest_size;

    return NRF_SUCCESS;
}


// Information structure for HMAC SHA256 using Oberon backend.
const nrf_crypto_hmac_info_t g_nrf_crypto_hmac_sha256_info =
{
    .init_fn        = oberon_backend_hmac_init_sha256,
    .update_fn      = oberon_backend_hmac_update_sha256,
    .finalize_fn    = oberon_backend_hmac_finalize_sha256,
    .digest_size    = NRF_CRYPTO_HASH_SIZE_SHA256,
    .context_size   = sizeof(nrf_crypto_backend_oberon_hmac_sha256_context_t),
    .type           = NRF_CRYPTO_HMAC_SHA256_TYPE
};

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_HMAC_SHA256)



#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_HMAC_SHA512)

#define HMAC_SHA512_BLOCK_SIZE 128

static ret_code_t oberon_backend_hmac_init_sha512(void      * const p_context,
                                                  uint8_t   const * p_key,
                                                  size_t            key_size)
{
    nrf_crypto_backend_oberon_hmac_sha512_context_t * p_ctx =
        (nrf_crypto_backend_oberon_hmac_sha512_context_t *)p_context;

    occ_hmac_sha512_init(&p_ctx->oberon_ctx, p_key, key_size);

    return NRF_SUCCESS;
}


static ret_code_t oberon_backend_hmac_update_sha512(void    * const p_context,
                                                    uint8_t const * p_data,
                                                    size_t          size)
{
    nrf_crypto_backend_oberon_hmac_sha512_context_t * p_ctx =
        (nrf_crypto_backend_oberon_hmac_sha512_context_t *)p_context;

    occ_hmac_sha512_update(&p_ctx->oberon_ctx, p_data, size);

    return NRF_SUCCESS;
}


static ret_code_t oberon_backend_hmac_finalize_sha512(void      * const p_context,
                                                      uint8_t         * p_digest,
                                                      size_t    * const p_size)
{
    nrf_crypto_backend_oberon_hmac_sha512_context_t * const p_ctx =
        (nrf_crypto_backend_oberon_hmac_sha512_context_t *)p_context;

    occ_hmac_sha512_final(p_digest, &p_ctx->oberon_ctx);

    // Assume operation was successful and update the digest size accordingly.
    *p_size = p_ctx->header.p_info->digest_size;

    return NRF_SUCCESS;
}


// Information structure for HMAC SHA512 using Oberon backend.
const nrf_crypto_hmac_info_t g_nrf_crypto_hmac_sha512_info =
{
    .init_fn        = oberon_backend_hmac_init_sha512,
    .update_fn      = oberon_backend_hmac_update_sha512,
    .finalize_fn    = oberon_backend_hmac_finalize_sha512,
    .digest_size    = NRF_CRYPTO_HASH_SIZE_SHA512,
    .context_size   = sizeof(nrf_crypto_backend_oberon_hmac_sha512_context_t),
    .type           = NRF_CRYPTO_HMAC_SHA512_TYPE
};

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_HMAC_SHA512)
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON)
