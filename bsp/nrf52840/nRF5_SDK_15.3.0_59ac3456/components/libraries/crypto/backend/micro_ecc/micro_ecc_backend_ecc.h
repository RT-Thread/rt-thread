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

#ifndef MICRO_ECC_BACKEND_ECC_H__
#define MICRO_ECC_BACKEND_ECC_H__

#include "sdk_config.h"
#include "nordic_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC)

#include <stdint.h>
#include <stdbool.h>
#include "nrf_crypto_ecc_shared.h"
#include "uECC.h"


#ifdef __cplusplus
extern "C" {
#endif


/** @internal See @ref nrf_crypto_backend_ecc_key_pair_generate_fn_t.
 */
ret_code_t nrf_crypto_backend_micro_ecc_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_calculate_fn_t.
*/
ret_code_t nrf_crypto_backend_micro_ecc_public_key_calculate(
    void       * p_context,
    void const * p_private_key,
    void       * p_public_key);


/** @internal See @ref nrf_crypto_backend_ecc_private_key_from_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_micro_ecc_private_key_from_raw(
    void          * p_private_key,
    uint8_t const * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_private_key_to_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_micro_ecc_private_key_to_raw(
    void    const * p_private_key,
    uint8_t       * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_from_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_micro_ecc_public_key_from_raw(
    void          * p_public_key,
    uint8_t const * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_to_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_micro_ecc_public_key_to_raw(
    void const * p_public_key,
    uint8_t    * p_raw_data);


/** @internal @brief Represents common uECC backend key structure.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header */
    uint32_t key[1];                             /**< @internal @brief micro-ecc specific key representation */
} nrf_crypto_backend_micro_ecc_common_key_t;


/** @internal @brief Callback RNG function that can be provided to uECC API.
 *  @param dest     Destination buffer.
 *  @param size     Size of the buffer.
 *  @return         1 on success, 0 on error.
 */
int nrf_crypto_backend_micro_ecc_rng_callback(uint8_t * dest, unsigned size);


/** @internal @brief Gets uECC type based on provided key.
 *  @param p_key    uECC backend key (public or private).
 *  @return         uECC specific value representing a curve.
 */
uECC_Curve nrf_crypto_backend_micro_ecc_curve_get(
    nrf_crypto_backend_micro_ecc_common_key_t const * p_key);


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC_ECC_SECP192R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP192R1)
#error "More than one backend enabled for secp192r1 (NIST 192-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP192R1_ENABLED 1

/** @internal @brief Structure holding private key for secp192r1 (NIST 192-bit) in micro-ecc.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header */
    uint32_t key[192 / 32];                      /**< @internal @brief micro-ecc specific key representation */
} nrf_crypto_backend_secp192r1_private_key_t;

/** @internal @brief Structure holding public key for secp192r1 (NIST 192-bit) in micro-ecc.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header */
    uint32_t key[2 * 192 / 32];                  /**< @internal @brief micro-ecc specific key representation */
} nrf_crypto_backend_secp192r1_public_key_t;

// Aliases for one common micro-ecc implementation
#define nrf_crypto_backend_secp192r1_key_pair_generate nrf_crypto_backend_micro_ecc_key_pair_generate
#define nrf_crypto_backend_secp192r1_public_key_calculate nrf_crypto_backend_micro_ecc_public_key_calculate
#define nrf_crypto_backend_secp192r1_private_key_from_raw nrf_crypto_backend_micro_ecc_private_key_from_raw
#define nrf_crypto_backend_secp192r1_private_key_to_raw nrf_crypto_backend_micro_ecc_private_key_to_raw
#define nrf_crypto_backend_secp192r1_public_key_from_raw nrf_crypto_backend_micro_ecc_public_key_from_raw
#define nrf_crypto_backend_secp192r1_public_key_to_raw nrf_crypto_backend_micro_ecc_public_key_to_raw
#define nrf_crypto_backend_secp192r1_private_key_free NULL
#define nrf_crypto_backend_secp192r1_public_key_free NULL
#define NRF_CRYPTO_BACKEND_SECP192R1_KEY_PAIR_GENERATE_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP192R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp192r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp192r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC_ECC_SECP192R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC_ECC_SECP224R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP224R1)
#error "More than one backend enabled for secp224r1 (NIST 224-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP224R1_ENABLED 1

/** @internal @brief Structure holding private key for secp224r1 (NIST 224-bit) in micro-ecc.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header */
    uint32_t key[224 / 32];                      /**< @internal @brief micro-ecc specific key representation */
} nrf_crypto_backend_secp224r1_private_key_t;

/** @internal @brief Structure holding public key for secp224r1 (NIST 224-bit) in micro-ecc.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header */
    uint32_t key[2 * 224 / 32];                  /**< @internal @brief micro-ecc specific key representation */
} nrf_crypto_backend_secp224r1_public_key_t;

// Aliases for one common micro-ecc implementation
#define nrf_crypto_backend_secp224r1_key_pair_generate nrf_crypto_backend_micro_ecc_key_pair_generate
#define nrf_crypto_backend_secp224r1_public_key_calculate nrf_crypto_backend_micro_ecc_public_key_calculate
#define nrf_crypto_backend_secp224r1_private_key_from_raw nrf_crypto_backend_micro_ecc_private_key_from_raw
#define nrf_crypto_backend_secp224r1_private_key_to_raw nrf_crypto_backend_micro_ecc_private_key_to_raw
#define nrf_crypto_backend_secp224r1_public_key_from_raw nrf_crypto_backend_micro_ecc_public_key_from_raw
#define nrf_crypto_backend_secp224r1_public_key_to_raw nrf_crypto_backend_micro_ecc_public_key_to_raw
#define nrf_crypto_backend_secp224r1_private_key_free NULL
#define nrf_crypto_backend_secp224r1_public_key_free NULL
#define NRF_CRYPTO_BACKEND_SECP224R1_KEY_PAIR_GENERATE_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP224R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp224r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp224r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC_ECC_SECP224R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC_ECC_SECP256R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP256R1)
#error "More than one backend enabled for secp256r1 (NIST 256-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP256R1_ENABLED 1

/** @internal @brief Structure holding private key for secp256r1 (NIST 256-bit) in micro-ecc.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header */
    uint32_t key[256 / 32];                      /**< @internal @brief micro-ecc specific key representation */
} nrf_crypto_backend_secp256r1_private_key_t;

/** @internal @brief Structure holding public key for secp256r1 (NIST 256-bit) in micro-ecc.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header */
    uint32_t key[2 * 256 / 32];                  /**< @internal @brief micro-ecc specific key representation */
} nrf_crypto_backend_secp256r1_public_key_t;

// Aliases for one common micro-ecc implementation
#define nrf_crypto_backend_secp256r1_key_pair_generate nrf_crypto_backend_micro_ecc_key_pair_generate
#define nrf_crypto_backend_secp256r1_public_key_calculate nrf_crypto_backend_micro_ecc_public_key_calculate
#define nrf_crypto_backend_secp256r1_private_key_from_raw nrf_crypto_backend_micro_ecc_private_key_from_raw
#define nrf_crypto_backend_secp256r1_private_key_to_raw nrf_crypto_backend_micro_ecc_private_key_to_raw
#define nrf_crypto_backend_secp256r1_public_key_from_raw nrf_crypto_backend_micro_ecc_public_key_from_raw
#define nrf_crypto_backend_secp256r1_public_key_to_raw nrf_crypto_backend_micro_ecc_public_key_to_raw
#define nrf_crypto_backend_secp256r1_private_key_free NULL
#define nrf_crypto_backend_secp256r1_public_key_free NULL
#define NRF_CRYPTO_BACKEND_SECP256R1_KEY_PAIR_GENERATE_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP256R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp256r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp256r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC_ECC_SECP256R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC_ECC_SECP256K1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP256K1)
#error "More than one backend enabled for secp256k1 (Koblitz 256-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP256K1_ENABLED 1

/** @internal @brief Structure holding private key for secp256k1 (Koblitz 256-bit) in micro-ecc.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header */
    uint32_t key[256 / 32];                      /**< @internal @brief micro-ecc specific key representation */
} nrf_crypto_backend_secp256k1_private_key_t;

/** @internal @brief Structure holding public key for secp256k1 (Koblitz 256-bit) in micro-ecc.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header */
    uint32_t key[2 * 256 / 32];                  /**< @internal @brief micro-ecc specific key representation */
} nrf_crypto_backend_secp256k1_public_key_t;

// Aliases for one common micro-ecc implementation
#define nrf_crypto_backend_secp256k1_key_pair_generate nrf_crypto_backend_micro_ecc_key_pair_generate
#define nrf_crypto_backend_secp256k1_public_key_calculate nrf_crypto_backend_micro_ecc_public_key_calculate
#define nrf_crypto_backend_secp256k1_private_key_from_raw nrf_crypto_backend_micro_ecc_private_key_from_raw
#define nrf_crypto_backend_secp256k1_private_key_to_raw nrf_crypto_backend_micro_ecc_private_key_to_raw
#define nrf_crypto_backend_secp256k1_public_key_from_raw nrf_crypto_backend_micro_ecc_public_key_from_raw
#define nrf_crypto_backend_secp256k1_public_key_to_raw nrf_crypto_backend_micro_ecc_public_key_to_raw
#define nrf_crypto_backend_secp256k1_private_key_free NULL
#define nrf_crypto_backend_secp256k1_public_key_free NULL
#define NRF_CRYPTO_BACKEND_SECP256K1_KEY_PAIR_GENERATE_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP256K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp256k1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp256k1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC_ECC_SECP256K1)


#ifdef __cplusplus
}
#endif

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC)

#endif // MICRO_ECC_BACKEND_ECC_H__
