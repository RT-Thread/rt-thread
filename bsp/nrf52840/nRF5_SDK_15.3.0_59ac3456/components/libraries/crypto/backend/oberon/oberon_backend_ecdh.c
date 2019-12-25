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

#include "sdk_config.h"
#include "nordic_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON)

#include <stdint.h>

#include "nrf_crypto_ecc.h"
#include "nrf_crypto_ecdh.h"
#include "nrf_crypto_shared.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_SECP256R1)
#include "occ_ecdh_p256.h"
#endif
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_CURVE25519)
#include "occ_curve25519.h"
#endif



#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_SECP256R1)

ret_code_t nrf_crypto_backend_secp256r1_ecdh_compute(
    void       * p_context,
    void const * p_private_key,
    void const * p_public_key,
    uint8_t    * p_shared_secret)
{
    int result;

    nrf_crypto_backend_secp256r1_private_key_t const * p_prv =
        (nrf_crypto_backend_secp256r1_private_key_t const *)p_private_key;

    nrf_crypto_backend_secp256r1_public_key_t const * p_pub =
        (nrf_crypto_backend_secp256r1_public_key_t const *)p_public_key;

    result = occ_ecdh_p256_common_secret(p_shared_secret, p_prv->key, p_pub->key);

    if (result != 0)
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }
    return NRF_SUCCESS;
}

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_SECP256R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_CURVE25519)

ret_code_t nrf_crypto_backend_curve25519_ecdh_compute(
    void       * p_context,
    void const * p_private_key,
    void const * p_public_key,
    uint8_t    * p_shared_secret)
{
    nrf_crypto_backend_curve25519_private_key_t const * p_prv =
        (nrf_crypto_backend_curve25519_private_key_t const *)p_private_key;

    nrf_crypto_backend_curve25519_public_key_t const * p_pub =
        (nrf_crypto_backend_curve25519_public_key_t const *)p_public_key;

    // Private key can be completely random at this point.
    // Oberon library updates bits in the key according to Curve25519 specification before use.
    occ_curve25519_scalarmult(p_shared_secret, p_prv->key, p_pub->key);

#if NRF_MODULE_ENABLED(NRF_CRYPTO_CURVE25519_BIG_ENDIAN)
    nrf_crypto_internal_swap_endian_in_place(p_shared_secret,
                                             NRF_CRYPTO_ECDH_CURVE25519_SHARED_SECRET_SIZE);
#endif

    return NRF_SUCCESS;
}

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_CURVE25519)

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON)
