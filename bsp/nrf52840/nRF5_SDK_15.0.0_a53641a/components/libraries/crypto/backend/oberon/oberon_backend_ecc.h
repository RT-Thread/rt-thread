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

#ifndef OBERON_BACKEND_ECC_H__
#define OBERON_BACKEND_ECC_H__

#include "sdk_config.h"
#include "nordic_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON)

#include <stdint.h>
#include <stdbool.h>
#include "nrf_crypto_ecc_shared.h"


#ifdef __cplusplus
extern "C" {
#endif


/** @internal See @ref nrf_crypto_backend_ecc_private_key_from_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_oberon_private_key_from_raw(
    void          * p_private_key,
    uint8_t const * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_private_key_to_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_oberon_private_key_to_raw(
    void    const * p_private_key,
    uint8_t       * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_from_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_oberon_public_key_from_raw(
    void          * p_public_key,
    uint8_t const * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_to_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_oberon_public_key_to_raw(
    void const * p_public_key,
    uint8_t    * p_raw_data);


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_SECP256R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP256R1)
#error "More than one backend enabled for secp256r1 (NIST 256-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP256R1_ENABLED 1


/** @internal @brief Generates random number that can be used as a private key for secp256r1.
 *
 *  It uses RNG from libary frontend to generate random numbers.
 *
 *  @param[out] data    Array where generated random number will be placed.
 *  @returns            NRF_SUCCESS or error code passed from RNG frontend.
 */
ret_code_t nrf_crypto_backend_oberon_ecc_secp256r1_rng(uint8_t data[32]);


/** @internal @brief Structure holding private key for Oberon's secp256r1.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header;  /**< @internal @brief Common ECC key header. */
    uint8_t key[32];                              /**< @internal @brief Raw key. */
} nrf_crypto_backend_secp256r1_private_key_t;


/** @internal @brief Structure holding public key for Oberon's secp256r1.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header;  /**< @internal @brief Common ECC key header. */
    uint8_t key[64];                              /**< @internal @brief Raw key. */
} nrf_crypto_backend_secp256r1_public_key_t;


/** @internal See @ref nrf_crypto_backend_ecc_key_pair_generate_fn_t.
 */
ret_code_t nrf_crypto_backend_secp256r1_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_calculate_fn_t.
*/
ret_code_t nrf_crypto_backend_secp256r1_public_key_calculate(
    void       * p_context,
    void const * p_private_key,
    void       * p_public_key);


// Common key conversion functions
#define nrf_crypto_backend_secp256r1_private_key_from_raw \
    nrf_crypto_backend_oberon_private_key_from_raw
#define nrf_crypto_backend_secp256r1_private_key_to_raw \
    nrf_crypto_backend_oberon_private_key_to_raw
#define nrf_crypto_backend_secp256r1_public_key_from_raw \
    nrf_crypto_backend_oberon_public_key_from_raw
#define nrf_crypto_backend_secp256r1_public_key_to_raw \
    nrf_crypto_backend_oberon_public_key_to_raw

// Free is not required for oberon keys
#define nrf_crypto_backend_secp256r1_private_key_free NULL
#define nrf_crypto_backend_secp256r1_public_key_free NULL

// Context is not used in oberon functions
#define NRF_CRYPTO_BACKEND_SECP256R1_KEY_PAIR_GENERATE_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP256R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp256r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp256r1_public_key_calculate_context_t;


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_SECP256R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_CURVE25519)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_CURVE25519)
#error "More than one backend enabled for Curve25519.");
#endif
#define NRF_CRYPTO_ECC_CURVE25519_ENABLED 1


/** @internal @brief Structure holding private key for Oberon's Curve25519.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header;  /**< @internal @brief Common ECC key header. */
    uint8_t key[32];                              /**< @internal @brief Raw key in little endian order. */
} nrf_crypto_backend_curve25519_private_key_t;


/** @internal @brief Structure holding public key for Oberon's Curve25519.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header. */
    uint8_t key[32];                             /**< @internal @brief Raw key in little endian order. */
} nrf_crypto_backend_curve25519_public_key_t;


/** @internal See @ref nrf_crypto_backend_ecc_key_pair_generate_fn_t.
 */
ret_code_t nrf_crypto_backend_curve25519_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_calculate_fn_t.
*/
ret_code_t nrf_crypto_backend_curve25519_public_key_calculate(
    void       * p_context,
    void const * p_private_key,
    void       * p_public_key);


// Common key conversion functions
#define nrf_crypto_backend_curve25519_private_key_from_raw \
    nrf_crypto_backend_oberon_private_key_from_raw
#define nrf_crypto_backend_curve25519_private_key_to_raw \
    nrf_crypto_backend_oberon_private_key_to_raw
#define nrf_crypto_backend_curve25519_public_key_from_raw \
    nrf_crypto_backend_oberon_public_key_from_raw
#define nrf_crypto_backend_curve25519_public_key_to_raw \
    nrf_crypto_backend_oberon_public_key_to_raw

// Free is not required for oberon keys
#define nrf_crypto_backend_curve25519_private_key_free NULL
#define nrf_crypto_backend_curve25519_public_key_free NULL

// Context is not used in oberon functions
#define NRF_CRYPTO_BACKEND_CURVE25519_KEY_PAIR_GENERATE_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_CURVE25519_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_curve25519_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_curve25519_public_key_calculate_context_t;


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_CURVE25519)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_ED25519)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_ED25519)
#error "More than one backend enabled for Ed25519.");
#endif
#define NRF_CRYPTO_ECC_ED25519_ENABLED 1



/** @internal @brief Structure holding private key for Oberon's Ed25519.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header. */
    uint8_t private_part[32];                    /**< @internal @brief Raw private key. */
    uint8_t public_part[32];                     /**< @internal @brief Raw public key. It is also required for Ed25519 signing. */
} nrf_crypto_backend_ed25519_private_key_t;


/** @internal @brief Structure holding private key for Oberon's Ed25519.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header. */
    uint8_t key[32];                             /**< @internal @brief Raw key. */
} nrf_crypto_backend_ed25519_public_key_t;


/** @internal See @ref nrf_crypto_backend_ecc_private_key_from_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_ed25519_private_key_from_raw(
    void          * p_private_key,
    uint8_t const * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_key_pair_generate_fn_t.
 */
ret_code_t nrf_crypto_backend_ed25519_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_calculate_fn_t.
*/
ret_code_t nrf_crypto_backend_ed25519_public_key_calculate(
    void       * p_context,
    void const * p_private_key,
    void       * p_public_key);


// Common key conversion functions
#define nrf_crypto_backend_ed25519_private_key_to_raw \
    nrf_crypto_backend_oberon_private_key_to_raw
#define nrf_crypto_backend_ed25519_public_key_from_raw \
    nrf_crypto_backend_oberon_public_key_from_raw
#define nrf_crypto_backend_ed25519_public_key_to_raw \
    nrf_crypto_backend_oberon_public_key_to_raw

// Free is not required for oberon keys
#define nrf_crypto_backend_ed25519_private_key_free NULL
#define nrf_crypto_backend_ed25519_public_key_free NULL

// Context is not used in oberon functions
#define NRF_CRYPTO_BACKEND_ED25519_KEY_PAIR_GENERATE_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_ED25519_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_ed25519_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_ed25519_public_key_calculate_context_t;


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_ED25519)


#ifdef __cplusplus
}
#endif

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON)

#endif // OBERON_BACKEND_ECC_H__
