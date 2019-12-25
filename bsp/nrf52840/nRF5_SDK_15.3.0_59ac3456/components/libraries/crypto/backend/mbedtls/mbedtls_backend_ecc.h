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

#ifndef MBEDTLS_BACKEND_ECC_H__
#define MBEDTLS_BACKEND_ECC_H__

#include "sdk_config.h"
#include "nordic_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS)

#include <stdint.h>
#include <stdbool.h>
#include "nrf_crypto_ecc_shared.h"

/*lint -save -e????*/
#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif
#include "mbedtls/ecp.h"
/*lint -restore*/


#ifdef __cplusplus
extern "C" {
#endif


/** @internal @brief Common structure holding private key for mbed TLS.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header */
    mbedtls_mpi key;                             /**< @internal @brief mbed TLS specific key representation */
} nrf_crypto_backend_mbedtls_ecc_private_key_t;


/** @internal @brief Common structure holding public key for mbed TLS.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header */
    mbedtls_ecp_point key;                       /**< @internal @brief mbed TLS specific key representation */
} nrf_crypto_backend_mbedtls_ecc_public_key_t;


/** @internal See @ref nrf_crypto_backend_ecc_key_pair_generate_fn_t.
 */
ret_code_t nrf_crypto_backend_mbedtls_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_calculate_fn_t.
*/
ret_code_t nrf_crypto_backend_mbedtls_public_key_calculate(
    void       * p_context,
    void const * p_private_key,
    void       * p_public_key);


/** @internal See @ref nrf_crypto_backend_ecc_private_key_from_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_mbedtls_private_key_from_raw(
    void          * p_private_key,
    uint8_t const * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_private_key_to_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_mbedtls_private_key_to_raw(
    void    const * p_private_key,
    uint8_t       * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_from_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_mbedtls_public_key_from_raw(
    void          * p_public_key,
    uint8_t const * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_to_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_mbedtls_public_key_to_raw(
    void const * p_public_key,
    uint8_t    * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_key_free_fn_t.
*/
ret_code_t nrf_crypto_backend_mbedtls_private_key_free(
    void * p_private_key);


/** @internal See @ref nrf_crypto_backend_ecc_key_free_fn_t.
*/
ret_code_t nrf_crypto_backend_mbedtls_public_key_free(
    void * p_public_key);


/** @internal @brief Loads mbed TLS ECC group of specified curve type.
 *
 *  @param[out] p_group    Pointer to place where to load a group. Data have to be later deallocated.
 *  @param[in]  curve_type ECC curve type from enum @ref nrf_crypto_ecc_curve_type_t.
 *  @returns               true on success, false if curve is not supported or no found in mbed TLS.
 */
bool nrf_crypto_backend_mbedtls_ecc_group_load(
    mbedtls_ecp_group                        * p_group,
    struct nrf_crypto_ecc_curve_info_s const * p_info);


/** @internal @brief Function that can be used as a parameter to mbed TLS functions requiring random
 *  number generator.
 *
 *  It uses RNG from libary front end to generate random numbers.
 *
 *  @param[in]  p_param   Opaque pointer passed by mbed TLS. Unused by this implementation.
 *  @param[out] p_data    Pointer where to put random number.
 *  @returns              0 on success, mbed TLS error code on error.
 */
int nrf_crypto_backend_mbedtls_ecc_mbedtls_rng(void * p_param, unsigned char * p_data, size_t size);


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP192R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP192R1)
#error "More than one backend enabled for secp192r1 (NIST 192-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP192R1_ENABLED 1

// Aliases for one common MBEDTLS implementation
#define nrf_crypto_backend_secp192r1_key_pair_generate    nrf_crypto_backend_mbedtls_key_pair_generate
#define nrf_crypto_backend_secp192r1_public_key_calculate nrf_crypto_backend_mbedtls_public_key_calculate
#define nrf_crypto_backend_secp192r1_private_key_from_raw nrf_crypto_backend_mbedtls_private_key_from_raw
#define nrf_crypto_backend_secp192r1_private_key_to_raw   nrf_crypto_backend_mbedtls_private_key_to_raw
#define nrf_crypto_backend_secp192r1_public_key_from_raw  nrf_crypto_backend_mbedtls_public_key_from_raw
#define nrf_crypto_backend_secp192r1_public_key_to_raw    nrf_crypto_backend_mbedtls_public_key_to_raw
#define nrf_crypto_backend_secp192r1_private_key_free     nrf_crypto_backend_mbedtls_private_key_free
#define nrf_crypto_backend_secp192r1_public_key_free      nrf_crypto_backend_mbedtls_public_key_free
// mbed TLS does not require context, so its size is 0.
#define NRF_CRYPTO_BACKEND_SECP192R1_KEY_PAIR_GENERATE_CONTEXT_SIZE    0
#define NRF_CRYPTO_BACKEND_SECP192R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0
// All MBEDTLS curve types share the same data structures
typedef nrf_crypto_backend_mbedtls_ecc_private_key_t nrf_crypto_backend_secp192r1_private_key_t;
typedef nrf_crypto_backend_mbedtls_ecc_public_key_t  nrf_crypto_backend_secp192r1_public_key_t;
// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp192r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp192r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP192R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP224R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP224R1)
#error "More than one backend enabled for secp224r1 (NIST 224-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP224R1_ENABLED 1

// Aliases for one common MBEDTLS implementation
#define nrf_crypto_backend_secp224r1_key_pair_generate    nrf_crypto_backend_mbedtls_key_pair_generate
#define nrf_crypto_backend_secp224r1_public_key_calculate nrf_crypto_backend_mbedtls_public_key_calculate
#define nrf_crypto_backend_secp224r1_private_key_from_raw nrf_crypto_backend_mbedtls_private_key_from_raw
#define nrf_crypto_backend_secp224r1_private_key_to_raw   nrf_crypto_backend_mbedtls_private_key_to_raw
#define nrf_crypto_backend_secp224r1_public_key_from_raw  nrf_crypto_backend_mbedtls_public_key_from_raw
#define nrf_crypto_backend_secp224r1_public_key_to_raw    nrf_crypto_backend_mbedtls_public_key_to_raw
#define nrf_crypto_backend_secp224r1_private_key_free     nrf_crypto_backend_mbedtls_private_key_free
#define nrf_crypto_backend_secp224r1_public_key_free      nrf_crypto_backend_mbedtls_public_key_free
// mbed TLS does not require context, so its size is 0.
#define NRF_CRYPTO_BACKEND_SECP224R1_KEY_PAIR_GENERATE_CONTEXT_SIZE    0
#define NRF_CRYPTO_BACKEND_SECP224R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0
// All MBEDTLS curve types share the same data structures
typedef nrf_crypto_backend_mbedtls_ecc_private_key_t nrf_crypto_backend_secp224r1_private_key_t;
typedef nrf_crypto_backend_mbedtls_ecc_public_key_t  nrf_crypto_backend_secp224r1_public_key_t;
// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp224r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp224r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP224R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP256R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP256R1)
#error "More than one backend enabled for secp256r1 (NIST 256-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP256R1_ENABLED 1

// Aliases for one common MBEDTLS implementation
#define nrf_crypto_backend_secp256r1_key_pair_generate    nrf_crypto_backend_mbedtls_key_pair_generate
#define nrf_crypto_backend_secp256r1_public_key_calculate nrf_crypto_backend_mbedtls_public_key_calculate
#define nrf_crypto_backend_secp256r1_private_key_from_raw nrf_crypto_backend_mbedtls_private_key_from_raw
#define nrf_crypto_backend_secp256r1_private_key_to_raw   nrf_crypto_backend_mbedtls_private_key_to_raw
#define nrf_crypto_backend_secp256r1_public_key_from_raw  nrf_crypto_backend_mbedtls_public_key_from_raw
#define nrf_crypto_backend_secp256r1_public_key_to_raw    nrf_crypto_backend_mbedtls_public_key_to_raw
#define nrf_crypto_backend_secp256r1_private_key_free     nrf_crypto_backend_mbedtls_private_key_free
#define nrf_crypto_backend_secp256r1_public_key_free      nrf_crypto_backend_mbedtls_public_key_free
// mbed TLS does not require context, so its size is 0.
#define NRF_CRYPTO_BACKEND_SECP256R1_KEY_PAIR_GENERATE_CONTEXT_SIZE    0
#define NRF_CRYPTO_BACKEND_SECP256R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0
// All MBEDTLS curve types share the same data structures
typedef nrf_crypto_backend_mbedtls_ecc_private_key_t nrf_crypto_backend_secp256r1_private_key_t;
typedef nrf_crypto_backend_mbedtls_ecc_public_key_t  nrf_crypto_backend_secp256r1_public_key_t;
// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp256r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp256r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP256R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP384R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP384R1)
#error "More than one backend enabled for secp384r1 (NIST 384-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP384R1_ENABLED 1

// Aliases for one common MBEDTLS implementation
#define nrf_crypto_backend_secp384r1_key_pair_generate    nrf_crypto_backend_mbedtls_key_pair_generate
#define nrf_crypto_backend_secp384r1_public_key_calculate nrf_crypto_backend_mbedtls_public_key_calculate
#define nrf_crypto_backend_secp384r1_private_key_from_raw nrf_crypto_backend_mbedtls_private_key_from_raw
#define nrf_crypto_backend_secp384r1_private_key_to_raw   nrf_crypto_backend_mbedtls_private_key_to_raw
#define nrf_crypto_backend_secp384r1_public_key_from_raw  nrf_crypto_backend_mbedtls_public_key_from_raw
#define nrf_crypto_backend_secp384r1_public_key_to_raw    nrf_crypto_backend_mbedtls_public_key_to_raw
#define nrf_crypto_backend_secp384r1_private_key_free     nrf_crypto_backend_mbedtls_private_key_free
#define nrf_crypto_backend_secp384r1_public_key_free      nrf_crypto_backend_mbedtls_public_key_free
// mbed TLS does not require context, so its size is 0.
#define NRF_CRYPTO_BACKEND_SECP384R1_KEY_PAIR_GENERATE_CONTEXT_SIZE    0
#define NRF_CRYPTO_BACKEND_SECP384R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0
// All MBEDTLS curve types share the same data structures
typedef nrf_crypto_backend_mbedtls_ecc_private_key_t nrf_crypto_backend_secp384r1_private_key_t;
typedef nrf_crypto_backend_mbedtls_ecc_public_key_t  nrf_crypto_backend_secp384r1_public_key_t;
// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp384r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp384r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP384R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP521R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP521R1)
#error "More than one backend enabled for secp521r1 (NIST 521-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP521R1_ENABLED 1

// Aliases for one common MBEDTLS implementation
#define nrf_crypto_backend_secp521r1_key_pair_generate    nrf_crypto_backend_mbedtls_key_pair_generate
#define nrf_crypto_backend_secp521r1_public_key_calculate nrf_crypto_backend_mbedtls_public_key_calculate
#define nrf_crypto_backend_secp521r1_private_key_from_raw nrf_crypto_backend_mbedtls_private_key_from_raw
#define nrf_crypto_backend_secp521r1_private_key_to_raw   nrf_crypto_backend_mbedtls_private_key_to_raw
#define nrf_crypto_backend_secp521r1_public_key_from_raw  nrf_crypto_backend_mbedtls_public_key_from_raw
#define nrf_crypto_backend_secp521r1_public_key_to_raw    nrf_crypto_backend_mbedtls_public_key_to_raw
#define nrf_crypto_backend_secp521r1_private_key_free     nrf_crypto_backend_mbedtls_private_key_free
#define nrf_crypto_backend_secp521r1_public_key_free      nrf_crypto_backend_mbedtls_public_key_free
// mbed TLS does not require context, so its size is 0.
#define NRF_CRYPTO_BACKEND_SECP521R1_KEY_PAIR_GENERATE_CONTEXT_SIZE    0
#define NRF_CRYPTO_BACKEND_SECP521R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0
// All MBEDTLS curve types share the same data structures
typedef nrf_crypto_backend_mbedtls_ecc_private_key_t nrf_crypto_backend_secp521r1_private_key_t;
typedef nrf_crypto_backend_mbedtls_ecc_public_key_t  nrf_crypto_backend_secp521r1_public_key_t;
// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp521r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp521r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP521R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP192K1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP192K1)
#error "More than one backend enabled for secp192k1 (Koblitz 192-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP192K1_ENABLED 1

// Aliases for one common MBEDTLS implementation
#define nrf_crypto_backend_secp192k1_key_pair_generate    nrf_crypto_backend_mbedtls_key_pair_generate
#define nrf_crypto_backend_secp192k1_public_key_calculate nrf_crypto_backend_mbedtls_public_key_calculate
#define nrf_crypto_backend_secp192k1_private_key_from_raw nrf_crypto_backend_mbedtls_private_key_from_raw
#define nrf_crypto_backend_secp192k1_private_key_to_raw   nrf_crypto_backend_mbedtls_private_key_to_raw
#define nrf_crypto_backend_secp192k1_public_key_from_raw  nrf_crypto_backend_mbedtls_public_key_from_raw
#define nrf_crypto_backend_secp192k1_public_key_to_raw    nrf_crypto_backend_mbedtls_public_key_to_raw
#define nrf_crypto_backend_secp192k1_private_key_free     nrf_crypto_backend_mbedtls_private_key_free
#define nrf_crypto_backend_secp192k1_public_key_free      nrf_crypto_backend_mbedtls_public_key_free
// mbed TLS does not require context, so its size is 0.
#define NRF_CRYPTO_BACKEND_SECP192K1_KEY_PAIR_GENERATE_CONTEXT_SIZE    0
#define NRF_CRYPTO_BACKEND_SECP192K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0
// All MBEDTLS curve types share the same data structures
typedef nrf_crypto_backend_mbedtls_ecc_private_key_t nrf_crypto_backend_secp192k1_private_key_t;
typedef nrf_crypto_backend_mbedtls_ecc_public_key_t  nrf_crypto_backend_secp192k1_public_key_t;
// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp192k1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp192k1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP192K1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP224K1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP224K1)
#error "More than one backend enabled for secp224k1 (Koblitz 224-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP224K1_ENABLED 1

// Aliases for one common MBEDTLS implementation
#define nrf_crypto_backend_secp224k1_key_pair_generate    nrf_crypto_backend_mbedtls_key_pair_generate
#define nrf_crypto_backend_secp224k1_public_key_calculate nrf_crypto_backend_mbedtls_public_key_calculate
#define nrf_crypto_backend_secp224k1_private_key_from_raw nrf_crypto_backend_mbedtls_private_key_from_raw
#define nrf_crypto_backend_secp224k1_private_key_to_raw   nrf_crypto_backend_mbedtls_private_key_to_raw
#define nrf_crypto_backend_secp224k1_public_key_from_raw  nrf_crypto_backend_mbedtls_public_key_from_raw
#define nrf_crypto_backend_secp224k1_public_key_to_raw    nrf_crypto_backend_mbedtls_public_key_to_raw
#define nrf_crypto_backend_secp224k1_private_key_free     nrf_crypto_backend_mbedtls_private_key_free
#define nrf_crypto_backend_secp224k1_public_key_free      nrf_crypto_backend_mbedtls_public_key_free
// mbed TLS does not require context, so its size is 0.
#define NRF_CRYPTO_BACKEND_SECP224K1_KEY_PAIR_GENERATE_CONTEXT_SIZE    0
#define NRF_CRYPTO_BACKEND_SECP224K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0
// All MBEDTLS curve types share the same data structures
typedef nrf_crypto_backend_mbedtls_ecc_private_key_t nrf_crypto_backend_secp224k1_private_key_t;
typedef nrf_crypto_backend_mbedtls_ecc_public_key_t  nrf_crypto_backend_secp224k1_public_key_t;
// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp224k1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp224k1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP224K1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP256K1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP256K1)
#error "More than one backend enabled for secp256k1 (Koblitz 256-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP256K1_ENABLED 1

// Aliases for one common MBEDTLS implementation
#define nrf_crypto_backend_secp256k1_key_pair_generate    nrf_crypto_backend_mbedtls_key_pair_generate
#define nrf_crypto_backend_secp256k1_public_key_calculate nrf_crypto_backend_mbedtls_public_key_calculate
#define nrf_crypto_backend_secp256k1_private_key_from_raw nrf_crypto_backend_mbedtls_private_key_from_raw
#define nrf_crypto_backend_secp256k1_private_key_to_raw   nrf_crypto_backend_mbedtls_private_key_to_raw
#define nrf_crypto_backend_secp256k1_public_key_from_raw  nrf_crypto_backend_mbedtls_public_key_from_raw
#define nrf_crypto_backend_secp256k1_public_key_to_raw    nrf_crypto_backend_mbedtls_public_key_to_raw
#define nrf_crypto_backend_secp256k1_private_key_free     nrf_crypto_backend_mbedtls_private_key_free
#define nrf_crypto_backend_secp256k1_public_key_free      nrf_crypto_backend_mbedtls_public_key_free
// mbed TLS does not require context, so its size is 0.
#define NRF_CRYPTO_BACKEND_SECP256K1_KEY_PAIR_GENERATE_CONTEXT_SIZE    0
#define NRF_CRYPTO_BACKEND_SECP256K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0
// All MBEDTLS curve types share the same data structures
typedef nrf_crypto_backend_mbedtls_ecc_private_key_t nrf_crypto_backend_secp256k1_private_key_t;
typedef nrf_crypto_backend_mbedtls_ecc_public_key_t  nrf_crypto_backend_secp256k1_public_key_t;
// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp256k1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp256k1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP256K1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_BP256R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_BP256R1)
#error "More than one backend enabled for bp256r1 (Brainpool 256-bit).");
#endif
#define NRF_CRYPTO_ECC_BP256R1_ENABLED 1

// Aliases for one common MBEDTLS implementation
#define nrf_crypto_backend_bp256r1_key_pair_generate    nrf_crypto_backend_mbedtls_key_pair_generate
#define nrf_crypto_backend_bp256r1_public_key_calculate nrf_crypto_backend_mbedtls_public_key_calculate
#define nrf_crypto_backend_bp256r1_private_key_from_raw nrf_crypto_backend_mbedtls_private_key_from_raw
#define nrf_crypto_backend_bp256r1_private_key_to_raw   nrf_crypto_backend_mbedtls_private_key_to_raw
#define nrf_crypto_backend_bp256r1_public_key_from_raw  nrf_crypto_backend_mbedtls_public_key_from_raw
#define nrf_crypto_backend_bp256r1_public_key_to_raw    nrf_crypto_backend_mbedtls_public_key_to_raw
#define nrf_crypto_backend_bp256r1_private_key_free     nrf_crypto_backend_mbedtls_private_key_free
#define nrf_crypto_backend_bp256r1_public_key_free      nrf_crypto_backend_mbedtls_public_key_free
// mbed TLS does not require context, so its size is 0.
#define NRF_CRYPTO_BACKEND_BP256R1_KEY_PAIR_GENERATE_CONTEXT_SIZE    0
#define NRF_CRYPTO_BACKEND_BP256R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0
// All MBEDTLS curve types share the same data structures
typedef nrf_crypto_backend_mbedtls_ecc_private_key_t nrf_crypto_backend_bp256r1_private_key_t;
typedef nrf_crypto_backend_mbedtls_ecc_public_key_t  nrf_crypto_backend_bp256r1_public_key_t;
// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_bp256r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_bp256r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_BP256R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_BP384R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_BP384R1)
#error "More than one backend enabled for bp384r1 (Brainpool 384-bit).");
#endif
#define NRF_CRYPTO_ECC_BP384R1_ENABLED 1

// Aliases for one common MBEDTLS implementation
#define nrf_crypto_backend_bp384r1_key_pair_generate    nrf_crypto_backend_mbedtls_key_pair_generate
#define nrf_crypto_backend_bp384r1_public_key_calculate nrf_crypto_backend_mbedtls_public_key_calculate
#define nrf_crypto_backend_bp384r1_private_key_from_raw nrf_crypto_backend_mbedtls_private_key_from_raw
#define nrf_crypto_backend_bp384r1_private_key_to_raw   nrf_crypto_backend_mbedtls_private_key_to_raw
#define nrf_crypto_backend_bp384r1_public_key_from_raw  nrf_crypto_backend_mbedtls_public_key_from_raw
#define nrf_crypto_backend_bp384r1_public_key_to_raw    nrf_crypto_backend_mbedtls_public_key_to_raw
#define nrf_crypto_backend_bp384r1_private_key_free     nrf_crypto_backend_mbedtls_private_key_free
#define nrf_crypto_backend_bp384r1_public_key_free      nrf_crypto_backend_mbedtls_public_key_free
// mbed TLS does not require context, so its size is 0.
#define NRF_CRYPTO_BACKEND_BP384R1_KEY_PAIR_GENERATE_CONTEXT_SIZE    0
#define NRF_CRYPTO_BACKEND_BP384R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0
// All MBEDTLS curve types share the same data structures
typedef nrf_crypto_backend_mbedtls_ecc_private_key_t nrf_crypto_backend_bp384r1_private_key_t;
typedef nrf_crypto_backend_mbedtls_ecc_public_key_t  nrf_crypto_backend_bp384r1_public_key_t;
// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_bp384r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_bp384r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_BP384R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_BP512R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_BP512R1)
#error "More than one backend enabled for bp512r1 (Brainpool 512-bit).");
#endif
#define NRF_CRYPTO_ECC_BP512R1_ENABLED 1

// Aliases for one common MBEDTLS implementation
#define nrf_crypto_backend_bp512r1_key_pair_generate    nrf_crypto_backend_mbedtls_key_pair_generate
#define nrf_crypto_backend_bp512r1_public_key_calculate nrf_crypto_backend_mbedtls_public_key_calculate
#define nrf_crypto_backend_bp512r1_private_key_from_raw nrf_crypto_backend_mbedtls_private_key_from_raw
#define nrf_crypto_backend_bp512r1_private_key_to_raw   nrf_crypto_backend_mbedtls_private_key_to_raw
#define nrf_crypto_backend_bp512r1_public_key_from_raw  nrf_crypto_backend_mbedtls_public_key_from_raw
#define nrf_crypto_backend_bp512r1_public_key_to_raw    nrf_crypto_backend_mbedtls_public_key_to_raw
#define nrf_crypto_backend_bp512r1_private_key_free     nrf_crypto_backend_mbedtls_private_key_free
#define nrf_crypto_backend_bp512r1_public_key_free      nrf_crypto_backend_mbedtls_public_key_free
// mbed TLS does not require context, so its size is 0.
#define NRF_CRYPTO_BACKEND_BP512R1_KEY_PAIR_GENERATE_CONTEXT_SIZE    0
#define NRF_CRYPTO_BACKEND_BP512R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0
// All MBEDTLS curve types share the same data structures
typedef nrf_crypto_backend_mbedtls_ecc_private_key_t nrf_crypto_backend_bp512r1_private_key_t;
typedef nrf_crypto_backend_mbedtls_ecc_public_key_t  nrf_crypto_backend_bp512r1_public_key_t;
// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_bp512r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_bp512r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_BP512R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_CURVE25519)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_CURVE25519)
#error "More than one backend enabled for Curve25519.");
#endif
#define NRF_CRYPTO_ECC_CURVE25519_ENABLED 1

// Aliases for one common MBEDTLS implementation
#define nrf_crypto_backend_curve25519_key_pair_generate    nrf_crypto_backend_mbedtls_key_pair_generate
#define nrf_crypto_backend_curve25519_public_key_calculate nrf_crypto_backend_mbedtls_public_key_calculate
#define nrf_crypto_backend_curve25519_private_key_from_raw nrf_crypto_backend_mbedtls_private_key_from_raw
#define nrf_crypto_backend_curve25519_private_key_to_raw   nrf_crypto_backend_mbedtls_private_key_to_raw
#define nrf_crypto_backend_curve25519_public_key_from_raw  nrf_crypto_backend_mbedtls_public_key_from_raw
#define nrf_crypto_backend_curve25519_public_key_to_raw    nrf_crypto_backend_mbedtls_public_key_to_raw
#define nrf_crypto_backend_curve25519_private_key_free     nrf_crypto_backend_mbedtls_private_key_free
#define nrf_crypto_backend_curve25519_public_key_free      nrf_crypto_backend_mbedtls_public_key_free
// mbed TLS does not require context, so its size is 0.
#define NRF_CRYPTO_BACKEND_CURVE25519_KEY_PAIR_GENERATE_CONTEXT_SIZE    0
#define NRF_CRYPTO_BACKEND_CURVE25519_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0
// All MBEDTLS curve types share the same data structures
typedef nrf_crypto_backend_mbedtls_ecc_private_key_t nrf_crypto_backend_curve25519_private_key_t;
typedef nrf_crypto_backend_mbedtls_ecc_public_key_t  nrf_crypto_backend_curve25519_public_key_t;
// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_curve25519_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_curve25519_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_CURVE25519)


#ifdef __cplusplus
}
#endif

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS)

#endif // MBEDTLS_BACKEND_ECC_H__
