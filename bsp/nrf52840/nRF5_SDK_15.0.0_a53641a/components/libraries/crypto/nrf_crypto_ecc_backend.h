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

#ifndef NRF_CRYPTO_ECC_BACKEND_H__
#define NRF_CRYPTO_ECC_BACKEND_H__
#if !defined(__SDK_DOXYGEN__)

#include <stdint.h>
#include <stddef.h>

#include "sdk_config.h"
#include "nordic_common.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_ecc_shared.h"

// Include all backends
#include "cc310_backend_ecc.h"
#include "cc310_bl_backend_ecc.h"
#include "mbedtls_backend_ecc.h"
#include "oberon_backend_ecc.h"
#include "micro_ecc_backend_ecc.h"


#ifdef __cplusplus
extern "C" {
#endif


// Make sure that all required defines are defined
#if !defined(NRF_CRYPTO_ECC_SECP160R1_ENABLED)
#define NRF_CRYPTO_ECC_SECP160R1_ENABLED 0
#endif
#if !defined(NRF_CRYPTO_ECC_SECP160R2_ENABLED)
#define NRF_CRYPTO_ECC_SECP160R2_ENABLED 0
#endif
#if !defined(NRF_CRYPTO_ECC_SECP192R1_ENABLED)
#define NRF_CRYPTO_ECC_SECP192R1_ENABLED 0
#endif
#if !defined(NRF_CRYPTO_ECC_SECP224R1_ENABLED)
#define NRF_CRYPTO_ECC_SECP224R1_ENABLED 0
#endif
#if !defined(NRF_CRYPTO_ECC_SECP256R1_ENABLED)
#define NRF_CRYPTO_ECC_SECP256R1_ENABLED 0
#endif
#if !defined(NRF_CRYPTO_ECC_SECP384R1_ENABLED)
#define NRF_CRYPTO_ECC_SECP384R1_ENABLED 0
#endif
#if !defined(NRF_CRYPTO_ECC_SECP521R1_ENABLED)
#define NRF_CRYPTO_ECC_SECP521R1_ENABLED 0
#endif
#if !defined(NRF_CRYPTO_ECC_SECP160K1_ENABLED)
#define NRF_CRYPTO_ECC_SECP160K1_ENABLED 0
#endif
#if !defined(NRF_CRYPTO_ECC_SECP192K1_ENABLED)
#define NRF_CRYPTO_ECC_SECP192K1_ENABLED 0
#endif
#if !defined(NRF_CRYPTO_ECC_SECP224K1_ENABLED)
#define NRF_CRYPTO_ECC_SECP224K1_ENABLED 0
#endif
#if !defined(NRF_CRYPTO_ECC_SECP256K1_ENABLED)
#define NRF_CRYPTO_ECC_SECP256K1_ENABLED 0
#endif
#if !defined(NRF_CRYPTO_ECC_BP256R1_ENABLED)
#define NRF_CRYPTO_ECC_BP256R1_ENABLED 0
#endif
#if !defined(NRF_CRYPTO_ECC_BP384R1_ENABLED)
#define NRF_CRYPTO_ECC_BP384R1_ENABLED 0
#endif
#if !defined(NRF_CRYPTO_ECC_BP512R1_ENABLED)
#define NRF_CRYPTO_ECC_BP512R1_ENABLED 0
#endif
#if !defined(NRF_CRYPTO_ECC_CURVE25519_ENABLED)
#define NRF_CRYPTO_ECC_CURVE25519_ENABLED 0
#endif
#if !defined(NRF_CRYPTO_ECC_ED25519_ENABLED)
#define NRF_CRYPTO_ECC_ED25519_ENABLED 0
#endif


/** @internal @brief Definition to detect if ECC submodule is enabled. It will be enabled if any
 *  curve of any of the backends is enabled.
 */
#define NRF_CRYPTO_ECC_ENABLED ( \
    NRF_MODULE_ENABLED(NRF_CRYPTO) && ( \
    NRF_CRYPTO_ECC_SECP160R1_ENABLED | \
    NRF_CRYPTO_ECC_SECP160R2_ENABLED | \
    NRF_CRYPTO_ECC_SECP192R1_ENABLED | \
    NRF_CRYPTO_ECC_SECP224R1_ENABLED | \
    NRF_CRYPTO_ECC_SECP256R1_ENABLED | \
    NRF_CRYPTO_ECC_SECP384R1_ENABLED | \
    NRF_CRYPTO_ECC_SECP521R1_ENABLED | \
    NRF_CRYPTO_ECC_SECP160K1_ENABLED | \
    NRF_CRYPTO_ECC_SECP192K1_ENABLED | \
    NRF_CRYPTO_ECC_SECP224K1_ENABLED | \
    NRF_CRYPTO_ECC_SECP256K1_ENABLED | \
    NRF_CRYPTO_ECC_BP256R1_ENABLED | \
    NRF_CRYPTO_ECC_BP384R1_ENABLED | \
    NRF_CRYPTO_ECC_BP512R1_ENABLED | \
    NRF_CRYPTO_ECC_CURVE25519_ENABLED | \
    NRF_CRYPTO_ECC_ED25519_ENABLED))


/** @internal @brief Definition containing number of enabled curves.
 */
#define NRF_CRYPTO_ECC_IMPLEMENTED_CURVES_COUNT ( \
    NRF_CRYPTO_ECC_SECP160R1_ENABLED + \
    NRF_CRYPTO_ECC_SECP160R2_ENABLED + \
    NRF_CRYPTO_ECC_SECP192R1_ENABLED + \
    NRF_CRYPTO_ECC_SECP224R1_ENABLED + \
    NRF_CRYPTO_ECC_SECP256R1_ENABLED + \
    NRF_CRYPTO_ECC_SECP384R1_ENABLED + \
    NRF_CRYPTO_ECC_SECP521R1_ENABLED + \
    NRF_CRYPTO_ECC_SECP160K1_ENABLED + \
    NRF_CRYPTO_ECC_SECP192K1_ENABLED + \
    NRF_CRYPTO_ECC_SECP224K1_ENABLED + \
    NRF_CRYPTO_ECC_SECP256K1_ENABLED + \
    NRF_CRYPTO_ECC_BP256R1_ENABLED + \
    NRF_CRYPTO_ECC_BP384R1_ENABLED + \
    NRF_CRYPTO_ECC_BP512R1_ENABLED + \
    NRF_CRYPTO_ECC_CURVE25519_ENABLED + \
    NRF_CRYPTO_ECC_ED25519_ENABLED)


#if !NRF_CRYPTO_ECC_SECP160R1_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_secp160r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp160r1_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp160r1_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp160r1_public_key_t;
#endif

#if !NRF_CRYPTO_ECC_SECP160R2_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_secp160r2_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp160r2_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp160r2_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp160r2_public_key_t;
#endif

#if !NRF_CRYPTO_ECC_SECP192R1_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_secp192r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp192r1_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp192r1_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp192r1_public_key_t;
#endif

#if !NRF_CRYPTO_ECC_SECP224R1_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_secp224r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp224r1_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp224r1_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp224r1_public_key_t;
#endif

#if !NRF_CRYPTO_ECC_SECP256R1_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_secp256r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp256r1_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp256r1_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp256r1_public_key_t;
#endif

#if !NRF_CRYPTO_ECC_SECP384R1_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_secp384r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp384r1_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp384r1_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp384r1_public_key_t;
#endif

#if !NRF_CRYPTO_ECC_SECP521R1_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_secp521r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp521r1_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp521r1_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp521r1_public_key_t;
#endif

#if !NRF_CRYPTO_ECC_SECP160K1_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_secp160k1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp160k1_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp160k1_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp160k1_public_key_t;
#endif

#if !NRF_CRYPTO_ECC_SECP192K1_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_secp192k1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp192k1_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp192k1_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp192k1_public_key_t;
#endif

#if !NRF_CRYPTO_ECC_SECP224K1_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_secp224k1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp224k1_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp224k1_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp224k1_public_key_t;
#endif

#if !NRF_CRYPTO_ECC_SECP256K1_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_secp256k1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp256k1_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp256k1_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_secp256k1_public_key_t;
#endif

#if !NRF_CRYPTO_ECC_BP256R1_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_bp256r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_bp256r1_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_bp256r1_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_bp256r1_public_key_t;
#endif

#if !NRF_CRYPTO_ECC_BP384R1_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_bp384r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_bp384r1_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_bp384r1_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_bp384r1_public_key_t;
#endif

#if !NRF_CRYPTO_ECC_BP512R1_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_bp512r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_bp512r1_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_bp512r1_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_bp512r1_public_key_t;
#endif

#if !NRF_CRYPTO_ECC_CURVE25519_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_curve25519_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_curve25519_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_curve25519_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_curve25519_public_key_t;
#endif

#if !NRF_CRYPTO_ECC_ED25519_ENABLED
// Dummy typedefs for disabled contexts
typedef uint32_t nrf_crypto_backend_ed25519_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_ed25519_public_key_calculate_context_t;
// Dummy typedefs for disabled keys
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_ed25519_private_key_t;
typedef nrf_crypto_internal_ecc_key_header_t nrf_crypto_backend_ed25519_public_key_t;
#endif


// Find biggest raw private and public key size that is currently enabled
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PRIVATE_KEY_MAX_SIZE (66)
#elif NRF_CRYPTO_ECC_BP512R1_ENABLED
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PRIVATE_KEY_MAX_SIZE (64)
#elif NRF_CRYPTO_ECC_BP384R1_ENABLED || NRF_CRYPTO_ECC_SECP384R1_ENABLED
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PRIVATE_KEY_MAX_SIZE (48)
#elif NRF_CRYPTO_ECC_BP256R1_ENABLED || NRF_CRYPTO_ECC_SECP256K1_ENABLED || NRF_CRYPTO_ECC_CURVE25519_ENABLED || NRF_CRYPTO_ECC_ED25519_ENABLED || NRF_CRYPTO_ECC_SECP256R1_ENABLED
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PRIVATE_KEY_MAX_SIZE (32)
#elif NRF_CRYPTO_ECC_SECP224K1_ENABLED || NRF_CRYPTO_ECC_SECP224R1_ENABLED
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PRIVATE_KEY_MAX_SIZE (28)
#elif NRF_CRYPTO_ECC_SECP192K1_ENABLED || NRF_CRYPTO_ECC_SECP192R1_ENABLED
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PRIVATE_KEY_MAX_SIZE (24)
#elif NRF_CRYPTO_ECC_SECP160K1_ENABLED || NRF_CRYPTO_ECC_SECP160R1_ENABLED || NRF_CRYPTO_ECC_SECP160R2_ENABLED
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PRIVATE_KEY_MAX_SIZE (20)
#else
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PRIVATE_KEY_MAX_SIZE (1)
#endif

#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PUBLIC_KEY_MAX_SIZE (2 * 66)
#elif NRF_CRYPTO_ECC_BP512R1_ENABLED
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PUBLIC_KEY_MAX_SIZE (2 * 64)
#elif NRF_CRYPTO_ECC_BP384R1_ENABLED || NRF_CRYPTO_ECC_SECP384R1_ENABLED
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PUBLIC_KEY_MAX_SIZE (2 * 48)
#elif NRF_CRYPTO_ECC_BP256R1_ENABLED || NRF_CRYPTO_ECC_SECP256K1_ENABLED || NRF_CRYPTO_ECC_SECP256R1_ENABLED
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PUBLIC_KEY_MAX_SIZE (2 * 32)
#elif NRF_CRYPTO_ECC_SECP224K1_ENABLED || NRF_CRYPTO_ECC_SECP224R1_ENABLED
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PUBLIC_KEY_MAX_SIZE (2 * 28)
#elif NRF_CRYPTO_ECC_SECP192K1_ENABLED || NRF_CRYPTO_ECC_SECP192R1_ENABLED
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PUBLIC_KEY_MAX_SIZE (2 * 24)
#elif NRF_CRYPTO_ECC_SECP160K1_ENABLED || NRF_CRYPTO_ECC_SECP160R1_ENABLED || NRF_CRYPTO_ECC_SECP160R2_ENABLED
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PUBLIC_KEY_MAX_SIZE (2 * 20)
#elif NRF_CRYPTO_ECC_CURVE25519_ENABLED || NRF_CRYPTO_ECC_ED25519_ENABLED
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PUBLIC_KEY_MAX_SIZE (32)
#else
#   define NRF_CRYPTO_BACKEND_ECC_RAW_PUBLIC_KEY_MAX_SIZE (1)
#endif


#ifdef __cplusplus
}
#endif


#endif // !defined(__SDK_DOXYGEN__)
#endif // NRF_CRYPTO_ECC_BACKEND_H__
