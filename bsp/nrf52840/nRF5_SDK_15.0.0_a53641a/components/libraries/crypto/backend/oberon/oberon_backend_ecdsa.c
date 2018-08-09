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

#include "sdk_config.h"
#include "nordic_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON)

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "nrf_crypto_ecc.h"
#include "nrf_crypto_rng.h"
#include "nrf_crypto_ecdsa.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_SECP256R1)

#include "occ_ecdsa_p256.h"


#define OBERON_HASH_SIZE_FOR_SECP256R1 (256 / 8)


ret_code_t nrf_crypto_backend_secp256r1_sign(
    void          * p_context,
    void    const * p_private_key,
    uint8_t const * p_data,
    size_t          data_size,
    uint8_t       * p_signature)
{
    int     result;
    uint8_t session_key[32];

    nrf_crypto_backend_secp256r1_private_key_t const * p_prv =
        (nrf_crypto_backend_secp256r1_private_key_t const *)p_private_key;

    if (data_size < OBERON_HASH_SIZE_FOR_SECP256R1)
    {
        return NRF_ERROR_CRYPTO_INPUT_LENGTH;
    }

    result = nrf_crypto_backend_oberon_ecc_secp256r1_rng(session_key);
    if (result != NRF_SUCCESS)
    {
        return result;
    }

    result = occ_ecdsa_p256_sign_hash(p_signature, p_data, p_prv->key, session_key);

    return result == 0 ? NRF_SUCCESS : NRF_ERROR_CRYPTO_INTERNAL;
}


ret_code_t nrf_crypto_backend_secp256r1_verify(
    void          * p_context,
    void    const * p_public_key,
    uint8_t const * p_data,
    size_t          data_size,
    uint8_t const * p_signature)
{
    int result;

    nrf_crypto_backend_secp256r1_public_key_t const * p_pub =
        (nrf_crypto_backend_secp256r1_public_key_t const *)p_public_key;

    if (data_size < OBERON_HASH_SIZE_FOR_SECP256R1)
    {
        return NRF_ERROR_CRYPTO_INPUT_LENGTH;
    }

    result = occ_ecdsa_p256_verify_hash(p_signature, p_data, p_pub->key);

    if (result != 0)
    {
        return NRF_ERROR_CRYPTO_ECDSA_INVALID_SIGNATURE;
    }
    return NRF_SUCCESS;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_SECP256R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_ED25519)

#include "occ_ed25519.h"


ret_code_t nrf_crypto_backend_ed25519_sign(
    void          * p_context,
    void    const * p_private_key,
    uint8_t const * p_data,
    size_t          data_size,
    uint8_t       * p_signature)
{
    nrf_crypto_backend_ed25519_private_key_t const * p_prv =
        (nrf_crypto_backend_ed25519_private_key_t const *)p_private_key;

    occ_ed25519_sign(p_signature, p_data, data_size, p_prv->private_part, p_prv->public_part);

    return NRF_SUCCESS;
}

ret_code_t nrf_crypto_backend_ed25519_verify(
    void          * p_context,
    void    const * p_public_key,
    uint8_t const * p_data,
    size_t          data_size,
    uint8_t const * p_signature)
{
    int result;

    nrf_crypto_backend_ed25519_public_key_t const * p_pub =
        (nrf_crypto_backend_ed25519_public_key_t const *)p_public_key;

    result = occ_ed25519_verify(p_signature, p_data, data_size, p_pub->key);

    if (result != 0)
    {
        return NRF_ERROR_CRYPTO_ECDSA_INVALID_SIGNATURE;
    }
    return NRF_SUCCESS;
}

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_ED25519)

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON)

