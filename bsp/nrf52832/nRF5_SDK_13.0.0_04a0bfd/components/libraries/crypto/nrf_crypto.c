/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#include "nrf_error.h"
#include "sdk_common.h"
#include "ecc.h"
#include "sha256.h"
#include "nrf_crypto.h"

uint32_t nrf_crypto_init(void)
{
    ecc_init(false);

    return NRF_SUCCESS;
}


uint32_t nrf_crypto_public_key_compute(uint32_t curve,
                             nrf_crypto_key_t const *p_sk,
                             nrf_crypto_key_t *p_pk)
{
    if(curve != NRF_CRYPTO_CURVE_SECP256R1)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if(p_sk->len != ECC_P256_SK_LEN || p_pk->len != ECC_P256_PK_LEN)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    return ecc_p256_public_key_compute(p_sk->p_le_data, p_pk->p_le_data);
}


uint32_t nrf_crypto_shared_secret_compute(uint32_t curve,
                                 nrf_crypto_key_t const *p_sk,
                                 nrf_crypto_key_t const *p_pk,
                                 nrf_crypto_key_t *p_ss)
{
    if(curve != NRF_CRYPTO_CURVE_SECP256R1)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if(p_sk->len != ECC_P256_SK_LEN || p_pk->len != ECC_P256_PK_LEN || p_ss->len != ECC_P256_SK_LEN)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    return ecc_p256_shared_secret_compute(p_sk->p_le_data, p_pk->p_le_data, p_ss->p_le_data);
}

uint32_t nrf_crypto_sign(uint32_t curve,
                nrf_crypto_key_t const *p_sk,
                nrf_crypto_key_t const *p_hash,
                nrf_crypto_key_t *p_sig)
{
    if(curve != NRF_CRYPTO_CURVE_SECP256R1)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if(p_sk->len != ECC_P256_SK_LEN || p_sig->len != ECC_P256_PK_LEN)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    return ecc_p256_sign(p_sk->p_le_data, p_hash->p_le_data, p_hash->len, p_sig->p_le_data);
}

uint32_t nrf_crypto_verify(uint32_t curve,
                  nrf_crypto_key_t const *p_pk,
                  nrf_crypto_key_t const *p_hash,
                  nrf_crypto_key_t const *p_sig)
{
    if(curve != NRF_CRYPTO_CURVE_SECP256R1)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if(p_pk->len != ECC_P256_PK_LEN || p_sig->len != ECC_P256_PK_LEN)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    return ecc_p256_verify(p_pk->p_le_data, p_hash->p_le_data, p_hash->len, p_sig->p_le_data);
}


uint32_t nrf_crypto_hash_compute(uint32_t hash_alg,
                        uint8_t const *p_data,
                        uint32_t len,
                        nrf_crypto_key_t *p_hash)
{
    ret_code_t       err_code;
    sha256_context_t ctx;

    if(hash_alg != NRF_CRYPTO_HASH_ALG_SHA256)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if(p_hash->len != (256 >> 3))
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    err_code = sha256_init(&ctx);
    VERIFY_SUCCESS(err_code);

    err_code = sha256_update(&ctx, p_data, len);
    VERIFY_SUCCESS(err_code);

    err_code = sha256_final(&ctx, p_hash->p_le_data, 1);
    VERIFY_SUCCESS(err_code);

    p_hash->len = (256 >> 3);

    return NRF_SUCCESS;
}


