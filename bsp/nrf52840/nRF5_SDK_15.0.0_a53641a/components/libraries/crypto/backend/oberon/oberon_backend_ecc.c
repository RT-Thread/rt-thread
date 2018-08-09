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

#include <stdbool.h>
#include <string.h>
#include <stddef.h>

#include "app_util.h"
#include "nrf_crypto_ecc.h"
#include "nrf_crypto_mem.h"
#include "nrf_crypto_rng.h"
#include "nrf_crypto_shared.h"
#include "oberon_backend_ecc.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_SECP256R1)
#include "occ_ecdh_p256.h"
#endif
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_CURVE25519)
#include "occ_curve25519.h"
#endif
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_ED25519)
#include "occ_ed25519.h"
#endif


/** @internal @brief Structure holding private key common to all curves implemented by the Oberon.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header;  /**< @internal @brief Common ECC key header. */
    uint8_t key[32];                              /**< @internal @brief Raw key. */
} nrf_crypto_backend_oberon_private_key_t;


/** @internal @brief Structure holding public key common to all curves implemented by the Oberon.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header;  /**< @internal @brief Common ECC key header. */
    uint8_t key[64];                              /**< @internal @brief Raw key. */
} nrf_crypto_backend_oberon_public_key_t;


/** @internal @brief Function to hold copy function (can be simple mem copy or copy with endian swap).
 */
typedef void (*copy_fn_t)(void * p_dest, void const * p_src, size_t size);


ret_code_t nrf_crypto_backend_oberon_private_key_to_raw(
    void    const * p_private_key,
    uint8_t       * p_raw_data)
{
    nrf_crypto_backend_oberon_private_key_t const * p_prv =
        (nrf_crypto_backend_oberon_private_key_t const *)p_private_key;

    //lint -save -e611 (Suspicious cast)
    copy_fn_t copy_fn = (copy_fn_t)p_prv->header.p_info->p_backend_data;
    //lint -restore

    copy_fn(p_raw_data, p_prv->key, p_prv->header.p_info->raw_private_key_size);

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_oberon_public_key_from_raw(
    void          * p_public_key,
    uint8_t const * p_raw_data)
{
    nrf_crypto_backend_oberon_public_key_t * p_pub =
        (nrf_crypto_backend_oberon_public_key_t *)p_public_key;

    //lint -save -e611 (Suspicious cast)
    copy_fn_t copy_fn = (copy_fn_t)p_pub->header.p_info->p_backend_data;
    //lint -restore

    copy_fn(p_pub->key, p_raw_data, p_pub->header.p_info->raw_public_key_size);

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_oberon_public_key_to_raw(
    void const * p_public_key,
    uint8_t    * p_raw_data)
{
    nrf_crypto_backend_oberon_public_key_t const * p_pub =
        (nrf_crypto_backend_oberon_public_key_t const *)p_public_key;

    //lint -save -e611 (Suspicious cast)
    copy_fn_t copy_fn = (copy_fn_t)p_pub->header.p_info->p_backend_data;
    //lint -restore

    copy_fn(p_raw_data, p_pub->key, p_pub->header.p_info->raw_public_key_size);

    return NRF_SUCCESS;
}


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_SECP256R1) \
    || NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_CURVE25519)


ret_code_t nrf_crypto_backend_oberon_private_key_from_raw(
    void          * p_private_key,
    uint8_t const * p_raw_data)
{
    nrf_crypto_backend_oberon_private_key_t * p_prv =
        (nrf_crypto_backend_oberon_private_key_t *)p_private_key;

    //lint -save -e611 (Suspicious cast)
    copy_fn_t copy_fn = (copy_fn_t)p_prv->header.p_info->p_backend_data;
    //lint -restore

    copy_fn(p_prv->key, p_raw_data, p_prv->header.p_info->raw_private_key_size);

    return NRF_SUCCESS;
}


#endif //NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_SECP256R1) || NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_CURVE25519)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_CURVE25519) \
    || NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_ED25519)


static ret_code_t oberon_vector_generate(uint8_t * p_data, size_t size)
{
#if defined(NRF_CRYPTO_RNG_ENABLED) && (NRF_CRYPTO_RNG_ENABLED == 1)

    return nrf_crypto_rng_vector_generate(p_data, size);

#elif defined(NRF_CRYPTO_RNG_ENABLED) && (NRF_CRYPTO_RNG_ENABLED == 0)

    return NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;

#else

    #warning NRF_CRYPTO_RNG_ENABLED define not found in sdk_config.h (Is the sdk_config.h valid?).

#endif
}


#endif //NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_CURVE25519) || NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_ED25519)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_SECP256R1)


// Make sure that common key structure match secp256r1 key structure to safely cast types.
STATIC_ASSERT(offsetof(nrf_crypto_backend_oberon_private_key_t, key) ==
              offsetof(nrf_crypto_backend_secp256r1_private_key_t, key),
              "Common Oberon private key structure does not match secp256r1 one.");
STATIC_ASSERT(offsetof(nrf_crypto_backend_oberon_public_key_t, key) ==
              offsetof(nrf_crypto_backend_secp256r1_public_key_t, key),
              "Common Oberon public key structure does not match secp256r1 one.");


ret_code_t nrf_crypto_backend_oberon_ecc_secp256r1_rng(uint8_t data[32])
{
#if NRF_MODULE_ENABLED(NRF_CRYPTO_RNG)

    static const uint8_t min_value[32] =
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    };
    static const uint8_t max_value[32] =
    {
        0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xBC, 0xE6, 0xFA, 0xAD, 0xA7, 0x17, 0x9E, 0x84, 0xF3, 0xB9, 0xCA, 0xC2, 0xFC, 0x63, 0x25, 0x50,
    };
    return nrf_crypto_rng_vector_generate_in_range(data, min_value, max_value, 32);

#else
    return NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
#endif
}


ret_code_t nrf_crypto_backend_secp256r1_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key)
{
    int result;

    nrf_crypto_backend_secp256r1_private_key_t * p_prv =
        (nrf_crypto_backend_secp256r1_private_key_t *)p_private_key;

    nrf_crypto_backend_secp256r1_public_key_t * p_pub =
        (nrf_crypto_backend_secp256r1_public_key_t *)p_public_key;

    result = nrf_crypto_backend_oberon_ecc_secp256r1_rng(p_prv->key);

    if (result != NRF_SUCCESS)
    {
        return result;
    }

    result = occ_ecdh_p256_public_key(p_pub->key, p_prv->key);

    if (result != 0)
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }
    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_secp256r1_public_key_calculate(
    void       * p_context,
    void const * p_private_key,
    void       * p_public_key)
{
    int result;

    nrf_crypto_backend_secp256r1_private_key_t const * p_prv =
        (nrf_crypto_backend_secp256r1_private_key_t const *)p_private_key;

    nrf_crypto_backend_secp256r1_public_key_t * p_pub =
        (nrf_crypto_backend_secp256r1_public_key_t *)p_public_key;

    result = occ_ecdh_p256_public_key(p_pub->key, p_prv->key);

    if (result != 0)
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }
    return NRF_SUCCESS;
}


const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp256r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_secp256r1_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_secp256r1_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP256R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE,
    //lint -save -e611 -e546 (Suspicious cast, Suspicious use of &)
    .p_backend_data       = (void *)&memcpy,
    //lint -restore
};


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_SECP256R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_CURVE25519)


// Make sure that common key structure match Curve25519 key structure to safely cast types.
STATIC_ASSERT(offsetof(nrf_crypto_backend_oberon_private_key_t, key) ==
              offsetof(nrf_crypto_backend_curve25519_private_key_t, key),
              "Common Oberon private key structure does not match Curve25519 one.");
STATIC_ASSERT(offsetof(nrf_crypto_backend_oberon_public_key_t, key) ==
              offsetof(nrf_crypto_backend_curve25519_public_key_t, key),
              "Common Oberon public key structure does not match Curve25519 one.");


ret_code_t nrf_crypto_backend_curve25519_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key)
{
    ret_code_t result;

    nrf_crypto_backend_curve25519_private_key_t * p_prv =
        (nrf_crypto_backend_curve25519_private_key_t *)p_private_key;

    nrf_crypto_backend_curve25519_public_key_t * p_pub =
        (nrf_crypto_backend_curve25519_public_key_t *)p_public_key;

    result = oberon_vector_generate(p_prv->key, sizeof(p_prv->key));

    if (result != NRF_SUCCESS)
    {
        return result;
    }

    p_prv->key[0]  &= 0xF8; // Private key is multiply of 8 (by definition), so lower 3 bits are 0.
    p_prv->key[31] &= 0x7F; // Highest bit has to be 0, because private key is 255-bit long.
    p_prv->key[31] |= 0x40; // Bit 254 has to be 1 (by definition)

    occ_curve25519_scalarmult_base(p_pub->key, p_prv->key);

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_curve25519_public_key_calculate(
    void       * p_context,
    void const * p_private_key,
    void       * p_public_key)
{
    nrf_crypto_backend_curve25519_private_key_t * p_prv =
        (nrf_crypto_backend_curve25519_private_key_t *)p_private_key;

    nrf_crypto_backend_curve25519_public_key_t * p_pub =
        (nrf_crypto_backend_curve25519_public_key_t *)p_public_key;

    // Private key bit fixing is done inside Oberon library.
    occ_curve25519_scalarmult_base(p_pub->key, p_prv->key);

    return NRF_SUCCESS;
}


const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_curve25519_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_curve25519_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_curve25519_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_CURVE25519_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_CURVE25519_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_CURVE25519_RAW_PUBLIC_KEY_SIZE,
    //lint -save -e611 -e546 (Suspicious cast, Suspicious use of &)
    .p_backend_data       = (void *)&nrf_crypto_internal_swap_endian,
    //lint -restore
};


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_CURVE25519)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_ED25519)


// Make sure that common key structure match Ed25519 key structure to safely cast types.
STATIC_ASSERT(offsetof(nrf_crypto_backend_oberon_private_key_t, key) ==
              offsetof(nrf_crypto_backend_ed25519_private_key_t, private_part),
              "Common Oberon private key structure does not match Ed25519 one.");
STATIC_ASSERT(offsetof(nrf_crypto_backend_oberon_public_key_t, key) ==
              offsetof(nrf_crypto_backend_ed25519_public_key_t, key),
              "Common Oberon public key structure does not match Ed25519 one.");


ret_code_t nrf_crypto_backend_ed25519_private_key_from_raw(
    void          * p_private_key,
    uint8_t const * p_raw_data)
{
    nrf_crypto_backend_ed25519_private_key_t * p_prv =
        (nrf_crypto_backend_ed25519_private_key_t *)p_private_key;

    memcpy(p_prv->private_part, p_raw_data, sizeof(p_prv->private_part));

    occ_ed25519_public_key(p_prv->public_part, p_prv->private_part);

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_ed25519_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key)
{
    ret_code_t result;

    nrf_crypto_backend_ed25519_private_key_t * p_prv =
        (nrf_crypto_backend_ed25519_private_key_t *)p_private_key;

    nrf_crypto_backend_ed25519_public_key_t * p_pub =
        (nrf_crypto_backend_ed25519_public_key_t *)p_public_key;

    result = oberon_vector_generate(p_prv->private_part, sizeof(p_prv->private_part));

    if (result != NRF_SUCCESS)
    {
        return result;
    }

    occ_ed25519_public_key(p_prv->public_part, p_prv->private_part);

    memcpy(p_pub->key, p_prv->public_part, sizeof(p_pub->key));

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_ed25519_public_key_calculate(
    void       * p_context,
    void const * p_private_key,
    void       * p_public_key)
{
    nrf_crypto_backend_ed25519_private_key_t * p_prv =
        (nrf_crypto_backend_ed25519_private_key_t *)p_private_key;

    nrf_crypto_backend_ed25519_public_key_t * p_pub =
        (nrf_crypto_backend_ed25519_public_key_t *)p_public_key;

    memcpy(p_pub->key, p_prv->public_part, sizeof(p_pub->key));

    return NRF_SUCCESS;
}


const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_ed25519_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_ed25519_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_ed25519_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_ED25519_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_ED25519_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_ED25519_RAW_PUBLIC_KEY_SIZE,
    //lint -save -e611 -e546 (Suspicious cast, Suspicious use of &)
    .p_backend_data       = (void *)&memcpy,
    //lint -restore
};


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_ED25519)


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON)
