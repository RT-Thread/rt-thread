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

#include "nrf_crypto_error.h"
#include "nrf_crypto_ecc.h"
#include "nrf_crypto_ecdsa.h"
#include "nrf_crypto_mem.h"
#include "app_util.h"
#include "sdk_macros.h"


#if NRF_CRYPTO_ECC_ENABLED


#if NRF_CRYPTO_ECC_IMPLEMENTED_CURVES_COUNT > 1


static const nrf_crypto_backend_ecdsa_sign_fn_t sign_impl[] =
{
#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
    nrf_crypto_backend_secp160r1_sign,
#endif
#if NRF_CRYPTO_ECC_SECP160R2_ENABLED
    nrf_crypto_backend_secp160r2_sign,
#endif
#if NRF_CRYPTO_ECC_SECP192R1_ENABLED
    nrf_crypto_backend_secp192r1_sign,
#endif
#if NRF_CRYPTO_ECC_SECP224R1_ENABLED
    nrf_crypto_backend_secp224r1_sign,
#endif
#if NRF_CRYPTO_ECC_SECP256R1_ENABLED
    nrf_crypto_backend_secp256r1_sign,
#endif
#if NRF_CRYPTO_ECC_SECP384R1_ENABLED
    nrf_crypto_backend_secp384r1_sign,
#endif
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
    nrf_crypto_backend_secp521r1_sign,
#endif
#if NRF_CRYPTO_ECC_SECP160K1_ENABLED
    nrf_crypto_backend_secp160k1_sign,
#endif
#if NRF_CRYPTO_ECC_SECP192K1_ENABLED
    nrf_crypto_backend_secp192k1_sign,
#endif
#if NRF_CRYPTO_ECC_SECP224K1_ENABLED
    nrf_crypto_backend_secp224k1_sign,
#endif
#if NRF_CRYPTO_ECC_SECP256K1_ENABLED
    nrf_crypto_backend_secp256k1_sign,
#endif
#if NRF_CRYPTO_ECC_BP256R1_ENABLED
    nrf_crypto_backend_bp256r1_sign,
#endif
#if NRF_CRYPTO_ECC_BP384R1_ENABLED
    nrf_crypto_backend_bp384r1_sign,
#endif
#if NRF_CRYPTO_ECC_BP512R1_ENABLED
    nrf_crypto_backend_bp512r1_sign,
#endif
#if NRF_CRYPTO_ECC_CURVE25519_ENABLED
    nrf_crypto_backend_curve25519_sign,
#endif
};

static const uint16_t sign_impl_context_size[] =
{
#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP160R1_SIGN_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP160R2_ENABLED
    NRF_CRYPTO_BACKEND_SECP160R2_SIGN_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP192R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP192R1_SIGN_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP224R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP224R1_SIGN_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP256R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP256R1_SIGN_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP384R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP384R1_SIGN_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP521R1_SIGN_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP160K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP160K1_SIGN_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP192K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP192K1_SIGN_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP224K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP224K1_SIGN_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP256K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP256K1_SIGN_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_BP256R1_ENABLED
    NRF_CRYPTO_BACKEND_BP256R1_SIGN_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_BP384R1_ENABLED
    NRF_CRYPTO_BACKEND_BP384R1_SIGN_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_BP512R1_ENABLED
    NRF_CRYPTO_BACKEND_BP512R1_SIGN_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_CURVE25519_ENABLED
    NRF_CRYPTO_BACKEND_CURVE25519_SIGN_CONTEXT_SIZE,
#endif
};

static const nrf_crypto_backend_ecdsa_verify_fn_t verify_impl[] =
{
#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
    nrf_crypto_backend_secp160r1_verify,
#endif
#if NRF_CRYPTO_ECC_SECP160R2_ENABLED
    nrf_crypto_backend_secp160r2_verify,
#endif
#if NRF_CRYPTO_ECC_SECP192R1_ENABLED
    nrf_crypto_backend_secp192r1_verify,
#endif
#if NRF_CRYPTO_ECC_SECP224R1_ENABLED
    nrf_crypto_backend_secp224r1_verify,
#endif
#if NRF_CRYPTO_ECC_SECP256R1_ENABLED
    nrf_crypto_backend_secp256r1_verify,
#endif
#if NRF_CRYPTO_ECC_SECP384R1_ENABLED
    nrf_crypto_backend_secp384r1_verify,
#endif
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
    nrf_crypto_backend_secp521r1_verify,
#endif
#if NRF_CRYPTO_ECC_SECP160K1_ENABLED
    nrf_crypto_backend_secp160k1_verify,
#endif
#if NRF_CRYPTO_ECC_SECP192K1_ENABLED
    nrf_crypto_backend_secp192k1_verify,
#endif
#if NRF_CRYPTO_ECC_SECP224K1_ENABLED
    nrf_crypto_backend_secp224k1_verify,
#endif
#if NRF_CRYPTO_ECC_SECP256K1_ENABLED
    nrf_crypto_backend_secp256k1_verify,
#endif
#if NRF_CRYPTO_ECC_BP256R1_ENABLED
    nrf_crypto_backend_bp256r1_verify,
#endif
#if NRF_CRYPTO_ECC_BP384R1_ENABLED
    nrf_crypto_backend_bp384r1_verify,
#endif
#if NRF_CRYPTO_ECC_BP512R1_ENABLED
    nrf_crypto_backend_bp512r1_verify,
#endif
#if NRF_CRYPTO_ECC_CURVE25519_ENABLED
    nrf_crypto_backend_curve25519_verify,
#endif
};

static const uint16_t verify_impl_context_size[] =
{
#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP160R1_VERIFY_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP160R2_ENABLED
    NRF_CRYPTO_BACKEND_SECP160R2_VERIFY_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP192R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP192R1_VERIFY_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP224R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP224R1_VERIFY_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP256R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP256R1_VERIFY_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP384R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP384R1_VERIFY_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP521R1_VERIFY_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP160K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP160K1_VERIFY_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP192K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP192K1_VERIFY_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP224K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP224K1_VERIFY_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP256K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP256K1_VERIFY_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_BP256R1_ENABLED
    NRF_CRYPTO_BACKEND_BP256R1_VERIFY_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_BP384R1_ENABLED
    NRF_CRYPTO_BACKEND_BP384R1_VERIFY_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_BP512R1_ENABLED
    NRF_CRYPTO_BACKEND_BP512R1_VERIFY_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_CURVE25519_ENABLED
    NRF_CRYPTO_BACKEND_CURVE25519_VERIFY_CONTEXT_SIZE,
#endif
};

#define BACKEND_IMPL_GET(table, curve_type) (table)[(uint32_t)(curve_type)]

#else

#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
#define sign_impl                nrf_crypto_backend_secp160r1_sign
#define sign_impl_context_size   NRF_CRYPTO_BACKEND_SECP160R1_SIGN_CONTEXT_SIZE
#define verify_impl              nrf_crypto_backend_secp160r1_verify
#define verify_impl_context_size NRF_CRYPTO_BACKEND_SECP160R1_VERIFY_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP160R2_ENABLED
#define sign_impl                nrf_crypto_backend_secp160r2_sign
#define sign_impl_context_size   NRF_CRYPTO_BACKEND_SECP160R2_SIGN_CONTEXT_SIZE
#define verify_impl              nrf_crypto_backend_secp160r2_verify
#define verify_impl_context_size NRF_CRYPTO_BACKEND_SECP160R2_VERIFY_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP192R1_ENABLED
#define sign_impl                nrf_crypto_backend_secp192r1_sign
#define sign_impl_context_size   NRF_CRYPTO_BACKEND_SECP192R1_SIGN_CONTEXT_SIZE
#define verify_impl              nrf_crypto_backend_secp192r1_verify
#define verify_impl_context_size NRF_CRYPTO_BACKEND_SECP192R1_VERIFY_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP224R1_ENABLED
#define sign_impl                nrf_crypto_backend_secp224r1_sign
#define sign_impl_context_size   NRF_CRYPTO_BACKEND_SECP224R1_SIGN_CONTEXT_SIZE
#define verify_impl              nrf_crypto_backend_secp224r1_verify
#define verify_impl_context_size NRF_CRYPTO_BACKEND_SECP224R1_VERIFY_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP256R1_ENABLED
#define sign_impl                nrf_crypto_backend_secp256r1_sign
#define sign_impl_context_size   NRF_CRYPTO_BACKEND_SECP256R1_SIGN_CONTEXT_SIZE
#define verify_impl              nrf_crypto_backend_secp256r1_verify
#define verify_impl_context_size NRF_CRYPTO_BACKEND_SECP256R1_VERIFY_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP384R1_ENABLED
#define sign_impl                nrf_crypto_backend_secp384r1_sign
#define sign_impl_context_size   NRF_CRYPTO_BACKEND_SECP384R1_SIGN_CONTEXT_SIZE
#define verify_impl              nrf_crypto_backend_secp384r1_verify
#define verify_impl_context_size NRF_CRYPTO_BACKEND_SECP384R1_VERIFY_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP521R1_ENABLED
#define sign_impl                nrf_crypto_backend_secp521r1_sign
#define sign_impl_context_size   NRF_CRYPTO_BACKEND_SECP521R1_SIGN_CONTEXT_SIZE
#define verify_impl              nrf_crypto_backend_secp521r1_verify
#define verify_impl_context_size NRF_CRYPTO_BACKEND_SECP521R1_VERIFY_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP160K1_ENABLED
#define sign_impl                nrf_crypto_backend_secp160k1_sign
#define sign_impl_context_size   NRF_CRYPTO_BACKEND_SECP160K1_SIGN_CONTEXT_SIZE
#define verify_impl              nrf_crypto_backend_secp160k1_verify
#define verify_impl_context_size NRF_CRYPTO_BACKEND_SECP160K1_VERIFY_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP192K1_ENABLED
#define sign_impl                nrf_crypto_backend_secp192k1_sign
#define sign_impl_context_size   NRF_CRYPTO_BACKEND_SECP192K1_SIGN_CONTEXT_SIZE
#define verify_impl              nrf_crypto_backend_secp192k1_verify
#define verify_impl_context_size NRF_CRYPTO_BACKEND_SECP192K1_VERIFY_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP224K1_ENABLED
#define sign_impl                nrf_crypto_backend_secp224k1_sign
#define sign_impl_context_size   NRF_CRYPTO_BACKEND_SECP224K1_SIGN_CONTEXT_SIZE
#define verify_impl              nrf_crypto_backend_secp224k1_verify
#define verify_impl_context_size NRF_CRYPTO_BACKEND_SECP224K1_VERIFY_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP256K1_ENABLED
#define sign_impl                nrf_crypto_backend_secp256k1_sign
#define sign_impl_context_size   NRF_CRYPTO_BACKEND_SECP256K1_SIGN_CONTEXT_SIZE
#define verify_impl              nrf_crypto_backend_secp256k1_verify
#define verify_impl_context_size NRF_CRYPTO_BACKEND_SECP256K1_VERIFY_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_BP256R1_ENABLED
#define sign_impl                nrf_crypto_backend_bp256r1_sign
#define sign_impl_context_size   NRF_CRYPTO_BACKEND_BP256R1_SIGN_CONTEXT_SIZE
#define verify_impl              nrf_crypto_backend_bp256r1_verify
#define verify_impl_context_size NRF_CRYPTO_BACKEND_BP256R1_VERIFY_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_BP384R1_ENABLED
#define sign_impl                nrf_crypto_backend_bp384r1_sign
#define sign_impl_context_size   NRF_CRYPTO_BACKEND_BP384R1_SIGN_CONTEXT_SIZE
#define verify_impl              nrf_crypto_backend_bp384r1_verify
#define verify_impl_context_size NRF_CRYPTO_BACKEND_BP384R1_VERIFY_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_BP512R1_ENABLED
#define sign_impl                nrf_crypto_backend_bp512r1_sign
#define sign_impl_context_size   NRF_CRYPTO_BACKEND_BP512R1_SIGN_CONTEXT_SIZE
#define verify_impl              nrf_crypto_backend_bp512r1_verify
#define verify_impl_context_size NRF_CRYPTO_BACKEND_BP512R1_VERIFY_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_CURVE25519_ENABLED
#define sign_impl                nrf_crypto_backend_curve25519_sign
#define sign_impl_context_size   NRF_CRYPTO_BACKEND_CURVE25519_SIGN_CONTEXT_SIZE
#define verify_impl              nrf_crypto_backend_curve25519_verify
#define verify_impl_context_size NRF_CRYPTO_BACKEND_CURVE25519_VERIFY_CONTEXT_SIZE
#else
#define sign_impl                NULL
#define sign_impl_context_size   0
#define verify_impl              NULL
#define verify_impl_context_size 0
#endif

#define BACKEND_IMPL_GET(function, curve_type) (function)

#endif


ret_code_t nrf_crypto_ecdsa_sign(
    nrf_crypto_ecdsa_sign_context_t       * p_context,
    nrf_crypto_ecc_private_key_t    const * p_private_key,
    uint8_t                         const * p_hash,
    size_t                                  hash_size,
    uint8_t                               * p_signature,
    size_t                                * p_signature_size)
{
    ret_code_t                           result;
    void                               * p_allocated_context = NULL;
    nrf_crypto_backend_ecdsa_sign_fn_t   backend_implementation;
    size_t                               context_size;
    nrf_crypto_ecc_curve_info_t  const * p_info;

    // Get pointer to header
    nrf_crypto_internal_ecc_key_header_t const * p_private_key_header =
        (nrf_crypto_internal_ecc_key_header_t const *)p_private_key;

    // Check and prepare parameters
    VERIFY_TRUE(p_hash != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    result = nrf_crypto_internal_ecc_key_input_check(
        p_private_key_header,
        NRF_CRYPTO_INTERNAL_ECC_PRIVATE_KEY_INIT_VALUE);
    VERIFY_SUCCESS(result);
    p_info = p_private_key_header->p_info;
    result = nrf_crypto_internal_ecc_raw_output_prepare(p_signature,
                                                        p_signature_size,
                                                        2 * p_info->raw_private_key_size);
    VERIFY_SUCCESS(result);

    // Get backend specific information
    backend_implementation = BACKEND_IMPL_GET(sign_impl, p_info->curve_type);
    context_size = BACKEND_IMPL_GET(sign_impl_context_size, p_info->curve_type);
    VERIFY_TRUE(backend_implementation != NULL, NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE);

    // Allocate context if not provided
    if (p_context == NULL && context_size > 0)
    {
        p_allocated_context = NRF_CRYPTO_ALLOC(context_size);
        VERIFY_TRUE(p_allocated_context != NULL, NRF_ERROR_CRYPTO_ALLOC_FAILED);
        p_context = p_allocated_context;
    }

    // Execute backend implementation
    result = backend_implementation(p_context, p_private_key, p_hash, hash_size, p_signature);

    // Deallocate context if allocated
    if (p_allocated_context != NULL)
    {
        NRF_CRYPTO_FREE(p_allocated_context);
    }

    return result;
}


ret_code_t nrf_crypto_ecdsa_verify(
    nrf_crypto_ecdsa_verify_context_t       * p_context,
    nrf_crypto_ecc_public_key_t       const * p_public_key,
    uint8_t                           const * p_hash,
    size_t                                    hash_size,
    uint8_t                           const * p_signature,
    size_t                                    signature_size)
{
    ret_code_t                                   result;
    void                                       * p_allocated_context = NULL;
    nrf_crypto_backend_ecdsa_verify_fn_t         backend_implementation;
    size_t                                       context_size;
    nrf_crypto_ecc_curve_info_t          const * p_info;

    // Get pointer to header
    nrf_crypto_internal_ecc_key_header_t const * p_public_key_header =
        (nrf_crypto_internal_ecc_key_header_t const *)p_public_key;

    // Check and prepare parameters
    result = nrf_crypto_internal_ecc_key_input_check(
        p_public_key_header,
        NRF_CRYPTO_INTERNAL_ECC_PUBLIC_KEY_INIT_VALUE);
    VERIFY_SUCCESS(result);
    p_info = p_public_key_header->p_info;
    result = nrf_crypto_internal_ecc_raw_input_check(p_signature,
                                                     signature_size,
                                                     2 * p_info->raw_private_key_size);
    VERIFY_SUCCESS(result);
    VERIFY_TRUE(p_hash != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);

    // Get backend specific information
    backend_implementation = BACKEND_IMPL_GET(verify_impl, p_info->curve_type);
    context_size = BACKEND_IMPL_GET(verify_impl_context_size, p_info->curve_type);
    VERIFY_TRUE(backend_implementation != NULL, NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE);

    // Allocate context if not provided
    if (p_context == NULL && context_size > 0)
    {
        p_allocated_context = NRF_CRYPTO_ALLOC(context_size);
        VERIFY_TRUE(p_allocated_context != NULL, NRF_ERROR_CRYPTO_ALLOC_FAILED);
        p_context = p_allocated_context;
    }

    // Execute backend implementation
    result = backend_implementation(p_context, p_public_key, p_hash, hash_size, p_signature);

    // Deallocate context if allocated
    if (p_allocated_context != NULL)
    {
        NRF_CRYPTO_FREE(p_allocated_context);
    }

    return result;
}


#endif // NRF_CRYPTO_ECC_ENABLED
