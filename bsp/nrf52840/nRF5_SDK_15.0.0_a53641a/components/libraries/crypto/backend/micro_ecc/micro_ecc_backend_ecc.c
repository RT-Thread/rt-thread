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

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC)

#include <stdbool.h>
#include <string.h>
#include <stddef.h>

#include "app_util.h"
#include "nrf_crypto_ecc.h"
#include "nrf_crypto_rng.h"
#include "nrf_crypto_shared.h"
#include "micro_ecc_backend_ecc.h"
#include "micro_ecc_backend_shared.h"
#include "uECC.h"


typedef uECC_Curve (*micro_ecc_curve_fn_t)(void);


int nrf_crypto_backend_micro_ecc_rng_callback(uint8_t * dest, unsigned size)
{
#if NRF_MODULE_ENABLED(NRF_CRYPTO_RNG)

    ret_code_t result;

    result = nrf_crypto_rng_vector_generate(dest, size);

    // Return values compatible with mbed TLS
    if (result != NRF_SUCCESS)
    {
        return 0;
    }
    return 1;

#else
    UNUSED_PARAMETER(dest);
    UNUSED_PARAMETER(size);
    return 0;
#endif
}


uECC_Curve nrf_crypto_backend_micro_ecc_curve_get(
    nrf_crypto_backend_micro_ecc_common_key_t const * p_key)
{
    nrf_crypto_internal_ecc_key_header_t const * p_key_header =
        (nrf_crypto_internal_ecc_key_header_t const *)p_key;

    //lint -save -e611 (Suspicious cast)
    micro_ecc_curve_fn_t micro_ecc_curve_fn =
        (micro_ecc_curve_fn_t)p_key_header->p_info->p_backend_data;
    //lint -restore

    uECC_Curve p_micro_ecc_curve = micro_ecc_curve_fn();

    return p_micro_ecc_curve;
}


ret_code_t nrf_crypto_backend_micro_ecc_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key)
{
    int result;

    nrf_crypto_backend_micro_ecc_common_key_t * p_prv =
        (nrf_crypto_backend_micro_ecc_common_key_t *)p_private_key;
    nrf_crypto_backend_micro_ecc_common_key_t * p_pub =
        (nrf_crypto_backend_micro_ecc_common_key_t *)p_public_key;

    uECC_Curve p_micro_ecc_curve = nrf_crypto_backend_micro_ecc_curve_get(p_prv);

    uECC_set_rng(nrf_crypto_backend_micro_ecc_rng_callback);

    result = uECC_make_key((uint8_t *)(&p_pub->key[0]),
                           (uint8_t *)(&p_prv->key[0]),
                           p_micro_ecc_curve);

    if (result == 0)
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }
    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_micro_ecc_public_key_calculate(
    void       * p_context,
    void const * p_private_key,
    void       * p_public_key)
{
    int result;

    nrf_crypto_backend_micro_ecc_common_key_t const * p_prv =
        (nrf_crypto_backend_micro_ecc_common_key_t const *)p_private_key;
    nrf_crypto_backend_micro_ecc_common_key_t       * p_pub =
        (nrf_crypto_backend_micro_ecc_common_key_t *)p_public_key;

    uECC_Curve p_micro_ecc_curve = nrf_crypto_backend_micro_ecc_curve_get(p_prv);

    result = uECC_compute_public_key((uint8_t *)(&p_prv->key[0]),
                                     (uint8_t *)(&p_pub->key[0]),
                                     p_micro_ecc_curve);

    if (result == 0)
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }
    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_micro_ecc_private_key_from_raw(
    void          * p_private_key,
    uint8_t const * p_raw_data)
{
    nrf_crypto_backend_micro_ecc_common_key_t * p_prv =
        (nrf_crypto_backend_micro_ecc_common_key_t *)p_private_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_prv->header.p_info;

#if ECC_BACKEND_SWAP_BYTES
    nrf_crypto_internal_swap_endian((uint8_t *)(&p_prv->key[0]),
                                    p_raw_data,
                                    p_info->raw_private_key_size);
#else
    memcpy(&p_prv->key[0], p_raw_data, p_info->raw_private_key_size);
#endif

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_micro_ecc_private_key_to_raw(
    void    const * p_private_key,
    uint8_t       * p_raw_data)
{
    nrf_crypto_backend_micro_ecc_common_key_t const * p_prv =
        (nrf_crypto_backend_micro_ecc_common_key_t const *)p_private_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_prv->header.p_info;

#if ECC_BACKEND_SWAP_BYTES
    nrf_crypto_internal_swap_endian(p_raw_data,
                                    (uint8_t *)(&p_prv->key[0]),
                                    p_info->raw_private_key_size);
#else
    memcpy(p_raw_data, &p_prv->key[0], p_info->raw_private_key_size);
#endif

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_micro_ecc_public_key_from_raw(
    void          * p_public_key,
    uint8_t const * p_raw_data)
{
    nrf_crypto_backend_micro_ecc_common_key_t * p_pub =
        (nrf_crypto_backend_micro_ecc_common_key_t *)p_public_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_pub->header.p_info;

    uECC_Curve p_micro_ecc_curve = nrf_crypto_backend_micro_ecc_curve_get(p_pub);

#if ECC_BACKEND_SWAP_BYTES
    nrf_crypto_internal_double_swap_endian((uint8_t *)(&p_pub->key[0]),
                                           p_raw_data,
                                           p_info->raw_private_key_size);
#else
    memcpy(&p_pub->key[0], p_raw_data, p_info->raw_public_key_size);
#endif

#if !NRF_CRYPTO_BACKEND_MICRO_ECC_PUBLIC_KEY_TRUSTED_ENABLED
    if (!uECC_valid_public_key((uint8_t *)(&p_pub->key[0]), p_micro_ecc_curve))
    {
        return NRF_ERROR_CRYPTO_ECC_INVALID_KEY;
    }
#else
    UNUSED_PARAMETER(p_micro_ecc_curve);
#endif

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_micro_ecc_public_key_to_raw(
    void const * p_public_key,
    uint8_t    * p_raw_data)
{
    nrf_crypto_backend_micro_ecc_common_key_t const * p_pub =
        (nrf_crypto_backend_micro_ecc_common_key_t const *)p_public_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_pub->header.p_info;

#if ECC_BACKEND_SWAP_BYTES
    nrf_crypto_internal_double_swap_endian(p_raw_data,
                                           (uint8_t *)(&p_pub->key[0]),
                                           p_info->raw_private_key_size);
#else
    memcpy(p_raw_data, &p_pub->key[0], p_info->raw_public_key_size);
#endif

    return NRF_SUCCESS;
}


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC_ECC_SECP192R1)

// Make sure that common key structure match secp192r1 (NIST 192-bit) key structure to safely cast types.
STATIC_ASSERT(offsetof(nrf_crypto_backend_micro_ecc_common_key_t, key) ==
              offsetof(nrf_crypto_backend_secp192r1_private_key_t, key),
              "Common uECC private key structure does not match secp192r1 (NIST 192-bit) one.");
STATIC_ASSERT(offsetof(nrf_crypto_backend_micro_ecc_common_key_t, key) ==
              offsetof(nrf_crypto_backend_secp192r1_public_key_t, key),
              "Common ECC public key structure does not match secp192r1 (NIST 192-bit) one.");

const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp192r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_secp192r1_private_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_secp192r1_public_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP192R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP192R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP192R1_RAW_PUBLIC_KEY_SIZE,
    //lint -save -e611 -e546 (Suspicious cast, Suspicious use of &)
    .p_backend_data       = (void *)&uECC_secp192r1,
    //lint -restore
};

#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC_ECC_SECP224R1)

// Make sure that common key structure match secp224r1 (NIST 224-bit) key structure to safely cast types.
STATIC_ASSERT(offsetof(nrf_crypto_backend_micro_ecc_common_key_t, key) ==
              offsetof(nrf_crypto_backend_secp224r1_private_key_t, key),
              "Common uECC private key structure does not match secp224r1 (NIST 224-bit) one.");
STATIC_ASSERT(offsetof(nrf_crypto_backend_micro_ecc_common_key_t, key) ==
              offsetof(nrf_crypto_backend_secp224r1_public_key_t, key),
              "Common ECC public key structure does not match secp224r1 (NIST 224-bit) one.");

const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp224r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_secp224r1_private_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_secp224r1_public_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP224R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP224R1_RAW_PUBLIC_KEY_SIZE,
    //lint -save -e611 -e546 (Suspicious cast, Suspicious use of &)
    .p_backend_data       = (void *)&uECC_secp224r1,
    //lint -restore
};

#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC_ECC_SECP256R1)

// Make sure that common key structure match secp256r1 (NIST 256-bit) key structure to safely cast types.
STATIC_ASSERT(offsetof(nrf_crypto_backend_micro_ecc_common_key_t, key) ==
              offsetof(nrf_crypto_backend_secp256r1_private_key_t, key),
              "Common uECC private key structure does not match secp256r1 (NIST 256-bit) one.");
STATIC_ASSERT(offsetof(nrf_crypto_backend_micro_ecc_common_key_t, key) ==
              offsetof(nrf_crypto_backend_secp256r1_public_key_t, key),
              "Common ECC public key structure does not match secp256r1 (NIST 256-bit) one.");

const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp256r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_secp256r1_private_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_secp256r1_public_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP256R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE,
    //lint -save -e611 -e546 (Suspicious cast, Suspicious use of &)
    .p_backend_data       = (void *)&uECC_secp256r1,
    //lint -restore
};

#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC_ECC_SECP256K1)

// Make sure that common key structure match secp256k1 (Koblitz 256-bit) key structure to safely cast types.
STATIC_ASSERT(offsetof(nrf_crypto_backend_micro_ecc_common_key_t, key) ==
              offsetof(nrf_crypto_backend_secp256k1_private_key_t, key),
              "Common uECC private key structure does not match secp256k1 (Koblitz 256-bit) one.");
STATIC_ASSERT(offsetof(nrf_crypto_backend_micro_ecc_common_key_t, key) ==
              offsetof(nrf_crypto_backend_secp256k1_public_key_t, key),
              "Common ECC public key structure does not match secp256k1 (Koblitz 256-bit) one.");


const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp256k1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_secp256k1_private_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_secp256k1_public_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP256K1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP256K1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP256K1_RAW_PUBLIC_KEY_SIZE,
    //lint -save -e611 -e546 (Suspicious cast, Suspicious use of &)
    .p_backend_data       = (void *)&uECC_secp256k1,
    //lint -restore
};

#endif


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC)
