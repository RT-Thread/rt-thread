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

#ifndef CC310_BACKEND_ECC_H__
#define CC310_BACKEND_ECC_H__

#include "sdk_config.h"
#include "nordic_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)

#include <stdbool.h>
#include "nrf_crypto_ecc_shared.h"
#include "crys_ecpki_kg.h"
#include "crys_ec_mont_api.h"
#include "crys_ec_edw_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @internal @brief Common structure holding private key for CC310.
 *
 * @details Used for most curves (except Curve25519 and Ed25519).
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header;      /**< @internal @brief Common ECC key header */
    CRYS_ECPKI_UserPrivKey_t             private_key; /**< @internal @brief CC310 specific key representation */
} nrf_crypto_backend_cc310_ecc_private_key_t;


/** @internal @brief Common structure holding public key for CC310.
 *
 * @details Used for most curves (except Curve25519 and Ed25519).
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header;        /**< @internal @brief Common ECC key header */
    bool                                 key_converted; /**< @internal @brief True if key was already converted from raw_public_key to cc310_public_key */
    union
    {
        CRYS_ECPKI_UserPublKey_t cc310_public_key;    /**< @internal @brief CC310 specific key representation */
        uint8_t                  raw_public_key[132]; /**< @internal @brief raw key representation */
    } key;
} nrf_crypto_backend_cc310_ecc_public_key_t;


/** @internal @brief Common structure holding context for key pair generation.
 *
 * @details Used for most curves (except Curve25519 and Ed25519).
 */
typedef struct
{
    CRYS_ECPKI_KG_TempData_t temp_data;           /**< @internal @brief Temporary buffer for CC310 internal storage */
} nrf_crypto_backend_cc310_key_pair_generate_context_t;


/** @internal See @ref nrf_crypto_backend_ecc_key_pair_generate_fn_t.
 *
 * @details Used for most curves (except Curve25519 and Ed25519).
 */
ret_code_t nrf_crypto_backend_cc310_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key);


/** @internal See @ref nrf_crypto_backend_ecc_private_key_from_raw_fn_t.
 *
 * @details Used for most curves (except Curve25519 and Ed25519).
*/
ret_code_t nrf_crypto_backend_cc310_private_key_from_raw(
    void          * p_private_key,
    uint8_t const * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_private_key_to_raw_fn_t.
 *
 * @details Used for most curves (except Curve25519 and Ed25519).
*/
ret_code_t nrf_crypto_backend_cc310_private_key_to_raw(
    void const * p_private_key,
    uint8_t    * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_from_raw_fn_t.
 *
 * @details Used for most curves (except Curve25519 and Ed25519).
*/
ret_code_t nrf_crypto_backend_cc310_public_key_from_raw(
    void          * p_public_key,
    uint8_t const * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_to_raw_fn_t.
 *
 * @details Used for most curves (except Curve25519 and Ed25519).
*/
ret_code_t nrf_crypto_backend_cc310_public_key_to_raw(
    void const * p_public_key,
    uint8_t    * p_raw_data);


/** @internal @brief Convert error code from CC310 to nrf_crypto error code.
 *
 *  @param[in]  crys_error   CC310 error code.
 *  @return                  nrf_crypto error code.
 */
ret_code_t nrf_crypto_backend_cc310_ecc_error_convert(uint32_t crys_error);


/** @internal @brief Converts public key from raw to CC310 representation if not converted already.
 *
 *  Data are read from p_pub->key.raw_public_key to stored into p_pub->cc310_public_key.
 *
 *  @param[in]  p_pub        Public key to convert.
 *  @param[in]  p_temp_data  Buffer for temporary data used by CC310 lib.
 *  @return                  nrf_crypto error code.
 */
ret_code_t nrf_crypto_backend_cc310_ecc_public_key_convert(
    nrf_crypto_backend_cc310_ecc_public_key_t * p_pub,
    CRYS_ECPKI_BUILD_TempData_t               * p_temp_data);


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP160R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP160R1)
#error "More than one backend enabled for secp160r1 (NIST 160-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP160R1_ENABLED 1

// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp160r1_key_pair_generate    nrf_crypto_backend_cc310_key_pair_generate
#define nrf_crypto_backend_secp160r1_public_key_calculate NULL
#define nrf_crypto_backend_secp160r1_private_key_from_raw nrf_crypto_backend_cc310_private_key_from_raw
#define nrf_crypto_backend_secp160r1_private_key_to_raw   nrf_crypto_backend_cc310_private_key_to_raw
#define nrf_crypto_backend_secp160r1_public_key_from_raw  nrf_crypto_backend_cc310_public_key_from_raw
#define nrf_crypto_backend_secp160r1_public_key_to_raw    nrf_crypto_backend_cc310_public_key_to_raw
#define nrf_crypto_backend_secp160r1_private_key_free     NULL
#define nrf_crypto_backend_secp160r1_public_key_free      NULL

// Context sizes required by CC310
#define NRF_CRYPTO_BACKEND_SECP160R1_KEY_PAIR_GENERATE_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_key_pair_generate_context_t)
#define NRF_CRYPTO_BACKEND_SECP160R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Most CC310 curve types share the same data structures for keys
typedef nrf_crypto_backend_cc310_ecc_private_key_t nrf_crypto_backend_secp160r1_private_key_t;
typedef nrf_crypto_backend_cc310_ecc_public_key_t  nrf_crypto_backend_secp160r1_public_key_t;

// Most CC310 curve types share the same data structures for context
typedef nrf_crypto_backend_cc310_key_pair_generate_context_t
    nrf_crypto_backend_secp160r1_key_pair_generate_context_t;

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp160r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP160R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP160R2)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP160R2)
#error "More than one backend enabled for secp160r2 (NIST 160-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP160R2_ENABLED 1

// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp160r2_key_pair_generate    nrf_crypto_backend_cc310_key_pair_generate
#define nrf_crypto_backend_secp160r2_public_key_calculate NULL
#define nrf_crypto_backend_secp160r2_private_key_from_raw nrf_crypto_backend_cc310_private_key_from_raw
#define nrf_crypto_backend_secp160r2_private_key_to_raw   nrf_crypto_backend_cc310_private_key_to_raw
#define nrf_crypto_backend_secp160r2_public_key_from_raw  nrf_crypto_backend_cc310_public_key_from_raw
#define nrf_crypto_backend_secp160r2_public_key_to_raw    nrf_crypto_backend_cc310_public_key_to_raw
#define nrf_crypto_backend_secp160r2_private_key_free     NULL
#define nrf_crypto_backend_secp160r2_public_key_free      NULL

// Context sizes required by CC310
#define NRF_CRYPTO_BACKEND_SECP160R2_KEY_PAIR_GENERATE_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_key_pair_generate_context_t)
#define NRF_CRYPTO_BACKEND_SECP160R2_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Most CC310 curve types share the same data structures for keys
typedef nrf_crypto_backend_cc310_ecc_private_key_t nrf_crypto_backend_secp160r2_private_key_t;
typedef nrf_crypto_backend_cc310_ecc_public_key_t  nrf_crypto_backend_secp160r2_public_key_t;

// Most CC310 curve types share the same data structures for context
typedef nrf_crypto_backend_cc310_key_pair_generate_context_t
    nrf_crypto_backend_secp160r2_key_pair_generate_context_t;

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp160r2_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP160R2)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP192R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP192R1)
#error "More than one backend enabled for secp192r1 (NIST 192-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP192R1_ENABLED 1

// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp192r1_key_pair_generate    nrf_crypto_backend_cc310_key_pair_generate
#define nrf_crypto_backend_secp192r1_public_key_calculate NULL
#define nrf_crypto_backend_secp192r1_private_key_from_raw nrf_crypto_backend_cc310_private_key_from_raw
#define nrf_crypto_backend_secp192r1_private_key_to_raw   nrf_crypto_backend_cc310_private_key_to_raw
#define nrf_crypto_backend_secp192r1_public_key_from_raw  nrf_crypto_backend_cc310_public_key_from_raw
#define nrf_crypto_backend_secp192r1_public_key_to_raw    nrf_crypto_backend_cc310_public_key_to_raw
#define nrf_crypto_backend_secp192r1_private_key_free     NULL
#define nrf_crypto_backend_secp192r1_public_key_free      NULL

// Context sizes required by CC310
#define NRF_CRYPTO_BACKEND_SECP192R1_KEY_PAIR_GENERATE_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_key_pair_generate_context_t)
#define NRF_CRYPTO_BACKEND_SECP192R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Most CC310 curve types share the same data structures for keys
typedef nrf_crypto_backend_cc310_ecc_private_key_t nrf_crypto_backend_secp192r1_private_key_t;
typedef nrf_crypto_backend_cc310_ecc_public_key_t  nrf_crypto_backend_secp192r1_public_key_t;

// Most CC310 curve types share the same data structures for context
typedef nrf_crypto_backend_cc310_key_pair_generate_context_t
    nrf_crypto_backend_secp192r1_key_pair_generate_context_t;

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp192r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP192R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP224R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP224R1)
#error "More than one backend enabled for secp224r1 (NIST 224-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP224R1_ENABLED 1

// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp224r1_key_pair_generate    nrf_crypto_backend_cc310_key_pair_generate
#define nrf_crypto_backend_secp224r1_public_key_calculate NULL
#define nrf_crypto_backend_secp224r1_private_key_from_raw nrf_crypto_backend_cc310_private_key_from_raw
#define nrf_crypto_backend_secp224r1_private_key_to_raw   nrf_crypto_backend_cc310_private_key_to_raw
#define nrf_crypto_backend_secp224r1_public_key_from_raw  nrf_crypto_backend_cc310_public_key_from_raw
#define nrf_crypto_backend_secp224r1_public_key_to_raw    nrf_crypto_backend_cc310_public_key_to_raw
#define nrf_crypto_backend_secp224r1_private_key_free     NULL
#define nrf_crypto_backend_secp224r1_public_key_free      NULL

// Context sizes required by CC310
#define NRF_CRYPTO_BACKEND_SECP224R1_KEY_PAIR_GENERATE_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_key_pair_generate_context_t)
#define NRF_CRYPTO_BACKEND_SECP224R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Most CC310 curve types share the same data structures for keys
typedef nrf_crypto_backend_cc310_ecc_private_key_t nrf_crypto_backend_secp224r1_private_key_t;
typedef nrf_crypto_backend_cc310_ecc_public_key_t  nrf_crypto_backend_secp224r1_public_key_t;

// Most CC310 curve types share the same data structures for context
typedef nrf_crypto_backend_cc310_key_pair_generate_context_t
    nrf_crypto_backend_secp224r1_key_pair_generate_context_t;

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp224r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP224R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP256R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP256R1)
#error "More than one backend enabled for secp256r1 (NIST 256-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP256R1_ENABLED 1

// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp256r1_key_pair_generate    nrf_crypto_backend_cc310_key_pair_generate
#define nrf_crypto_backend_secp256r1_public_key_calculate NULL
#define nrf_crypto_backend_secp256r1_private_key_from_raw nrf_crypto_backend_cc310_private_key_from_raw
#define nrf_crypto_backend_secp256r1_private_key_to_raw   nrf_crypto_backend_cc310_private_key_to_raw
#define nrf_crypto_backend_secp256r1_public_key_from_raw  nrf_crypto_backend_cc310_public_key_from_raw
#define nrf_crypto_backend_secp256r1_public_key_to_raw    nrf_crypto_backend_cc310_public_key_to_raw
#define nrf_crypto_backend_secp256r1_private_key_free     NULL
#define nrf_crypto_backend_secp256r1_public_key_free      NULL

// Context sizes required by CC310
#define NRF_CRYPTO_BACKEND_SECP256R1_KEY_PAIR_GENERATE_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_key_pair_generate_context_t)
#define NRF_CRYPTO_BACKEND_SECP256R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Most CC310 curve types share the same data structures for keys
typedef nrf_crypto_backend_cc310_ecc_private_key_t nrf_crypto_backend_secp256r1_private_key_t;
typedef nrf_crypto_backend_cc310_ecc_public_key_t  nrf_crypto_backend_secp256r1_public_key_t;

// Most CC310 curve types share the same data structures for context
typedef nrf_crypto_backend_cc310_key_pair_generate_context_t
    nrf_crypto_backend_secp256r1_key_pair_generate_context_t;

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp256r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP256R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP384R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP384R1)
#error "More than one backend enabled for secp384r1 (NIST 384-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP384R1_ENABLED 1

// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp384r1_key_pair_generate    nrf_crypto_backend_cc310_key_pair_generate
#define nrf_crypto_backend_secp384r1_public_key_calculate NULL
#define nrf_crypto_backend_secp384r1_private_key_from_raw nrf_crypto_backend_cc310_private_key_from_raw
#define nrf_crypto_backend_secp384r1_private_key_to_raw   nrf_crypto_backend_cc310_private_key_to_raw
#define nrf_crypto_backend_secp384r1_public_key_from_raw  nrf_crypto_backend_cc310_public_key_from_raw
#define nrf_crypto_backend_secp384r1_public_key_to_raw    nrf_crypto_backend_cc310_public_key_to_raw
#define nrf_crypto_backend_secp384r1_private_key_free     NULL
#define nrf_crypto_backend_secp384r1_public_key_free      NULL

// Context sizes required by CC310
#define NRF_CRYPTO_BACKEND_SECP384R1_KEY_PAIR_GENERATE_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_key_pair_generate_context_t)
#define NRF_CRYPTO_BACKEND_SECP384R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Most CC310 curve types share the same data structures for keys
typedef nrf_crypto_backend_cc310_ecc_private_key_t nrf_crypto_backend_secp384r1_private_key_t;
typedef nrf_crypto_backend_cc310_ecc_public_key_t  nrf_crypto_backend_secp384r1_public_key_t;

// Most CC310 curve types share the same data structures for context
typedef nrf_crypto_backend_cc310_key_pair_generate_context_t
    nrf_crypto_backend_secp384r1_key_pair_generate_context_t;

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp384r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP384R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP521R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP521R1)
#error "More than one backend enabled for secp521r1 (NIST 521-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP521R1_ENABLED 1

// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp521r1_key_pair_generate    nrf_crypto_backend_cc310_key_pair_generate
#define nrf_crypto_backend_secp521r1_public_key_calculate NULL
#define nrf_crypto_backend_secp521r1_private_key_from_raw nrf_crypto_backend_cc310_private_key_from_raw
#define nrf_crypto_backend_secp521r1_private_key_to_raw   nrf_crypto_backend_cc310_private_key_to_raw
#define nrf_crypto_backend_secp521r1_public_key_from_raw  nrf_crypto_backend_cc310_public_key_from_raw
#define nrf_crypto_backend_secp521r1_public_key_to_raw    nrf_crypto_backend_cc310_public_key_to_raw
#define nrf_crypto_backend_secp521r1_private_key_free     NULL
#define nrf_crypto_backend_secp521r1_public_key_free      NULL

// Context sizes required by CC310
#define NRF_CRYPTO_BACKEND_SECP521R1_KEY_PAIR_GENERATE_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_key_pair_generate_context_t)
#define NRF_CRYPTO_BACKEND_SECP521R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Most CC310 curve types share the same data structures for keys
typedef nrf_crypto_backend_cc310_ecc_private_key_t nrf_crypto_backend_secp521r1_private_key_t;
typedef nrf_crypto_backend_cc310_ecc_public_key_t  nrf_crypto_backend_secp521r1_public_key_t;

// Most CC310 curve types share the same data structures for context
typedef nrf_crypto_backend_cc310_key_pair_generate_context_t
    nrf_crypto_backend_secp521r1_key_pair_generate_context_t;

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp521r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP521R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP160K1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP160K1)
#error "More than one backend enabled for secp160k1 (Koblitz 160-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP160K1_ENABLED 1

// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp160k1_key_pair_generate    nrf_crypto_backend_cc310_key_pair_generate
#define nrf_crypto_backend_secp160k1_public_key_calculate NULL
#define nrf_crypto_backend_secp160k1_private_key_from_raw nrf_crypto_backend_cc310_private_key_from_raw
#define nrf_crypto_backend_secp160k1_private_key_to_raw   nrf_crypto_backend_cc310_private_key_to_raw
#define nrf_crypto_backend_secp160k1_public_key_from_raw  nrf_crypto_backend_cc310_public_key_from_raw
#define nrf_crypto_backend_secp160k1_public_key_to_raw    nrf_crypto_backend_cc310_public_key_to_raw
#define nrf_crypto_backend_secp160k1_private_key_free     NULL
#define nrf_crypto_backend_secp160k1_public_key_free      NULL

// Context sizes required by CC310
#define NRF_CRYPTO_BACKEND_SECP160K1_KEY_PAIR_GENERATE_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_key_pair_generate_context_t)
#define NRF_CRYPTO_BACKEND_SECP160K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Most CC310 curve types share the same data structures for keys
typedef nrf_crypto_backend_cc310_ecc_private_key_t nrf_crypto_backend_secp160k1_private_key_t;
typedef nrf_crypto_backend_cc310_ecc_public_key_t  nrf_crypto_backend_secp160k1_public_key_t;

// Most CC310 curve types share the same data structures for context
typedef nrf_crypto_backend_cc310_key_pair_generate_context_t
    nrf_crypto_backend_secp160k1_key_pair_generate_context_t;

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp160k1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP160K1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP192K1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP192K1)
#error "More than one backend enabled for secp192k1 (Koblitz 192-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP192K1_ENABLED 1

// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp192k1_key_pair_generate    nrf_crypto_backend_cc310_key_pair_generate
#define nrf_crypto_backend_secp192k1_public_key_calculate NULL
#define nrf_crypto_backend_secp192k1_private_key_from_raw nrf_crypto_backend_cc310_private_key_from_raw
#define nrf_crypto_backend_secp192k1_private_key_to_raw   nrf_crypto_backend_cc310_private_key_to_raw
#define nrf_crypto_backend_secp192k1_public_key_from_raw  nrf_crypto_backend_cc310_public_key_from_raw
#define nrf_crypto_backend_secp192k1_public_key_to_raw    nrf_crypto_backend_cc310_public_key_to_raw
#define nrf_crypto_backend_secp192k1_private_key_free     NULL
#define nrf_crypto_backend_secp192k1_public_key_free      NULL

// Context sizes required by CC310
#define NRF_CRYPTO_BACKEND_SECP192K1_KEY_PAIR_GENERATE_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_key_pair_generate_context_t)
#define NRF_CRYPTO_BACKEND_SECP192K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Most CC310 curve types share the same data structures for keys
typedef nrf_crypto_backend_cc310_ecc_private_key_t nrf_crypto_backend_secp192k1_private_key_t;
typedef nrf_crypto_backend_cc310_ecc_public_key_t  nrf_crypto_backend_secp192k1_public_key_t;

// Most CC310 curve types share the same data structures for context
typedef nrf_crypto_backend_cc310_key_pair_generate_context_t
    nrf_crypto_backend_secp192k1_key_pair_generate_context_t;

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp192k1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP192K1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP224K1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP224K1)
#error "More than one backend enabled for secp224k1 (Koblitz 224-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP224K1_ENABLED 1

// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp224k1_key_pair_generate    nrf_crypto_backend_cc310_key_pair_generate
#define nrf_crypto_backend_secp224k1_public_key_calculate NULL
#define nrf_crypto_backend_secp224k1_private_key_from_raw nrf_crypto_backend_cc310_private_key_from_raw
#define nrf_crypto_backend_secp224k1_private_key_to_raw   nrf_crypto_backend_cc310_private_key_to_raw
#define nrf_crypto_backend_secp224k1_public_key_from_raw  nrf_crypto_backend_cc310_public_key_from_raw
#define nrf_crypto_backend_secp224k1_public_key_to_raw    nrf_crypto_backend_cc310_public_key_to_raw
#define nrf_crypto_backend_secp224k1_private_key_free     NULL
#define nrf_crypto_backend_secp224k1_public_key_free      NULL

// Context sizes required by CC310
#define NRF_CRYPTO_BACKEND_SECP224K1_KEY_PAIR_GENERATE_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_key_pair_generate_context_t)
#define NRF_CRYPTO_BACKEND_SECP224K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Most CC310 curve types share the same data structures for keys
typedef nrf_crypto_backend_cc310_ecc_private_key_t nrf_crypto_backend_secp224k1_private_key_t;
typedef nrf_crypto_backend_cc310_ecc_public_key_t  nrf_crypto_backend_secp224k1_public_key_t;

// Most CC310 curve types share the same data structures for context
typedef nrf_crypto_backend_cc310_key_pair_generate_context_t
    nrf_crypto_backend_secp224k1_key_pair_generate_context_t;

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp224k1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP224K1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP256K1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP256K1)
#error "More than one backend enabled for secp256k1 (Koblitz 256-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP256K1_ENABLED 1

// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp256k1_key_pair_generate    nrf_crypto_backend_cc310_key_pair_generate
#define nrf_crypto_backend_secp256k1_public_key_calculate NULL
#define nrf_crypto_backend_secp256k1_private_key_from_raw nrf_crypto_backend_cc310_private_key_from_raw
#define nrf_crypto_backend_secp256k1_private_key_to_raw   nrf_crypto_backend_cc310_private_key_to_raw
#define nrf_crypto_backend_secp256k1_public_key_from_raw  nrf_crypto_backend_cc310_public_key_from_raw
#define nrf_crypto_backend_secp256k1_public_key_to_raw    nrf_crypto_backend_cc310_public_key_to_raw
#define nrf_crypto_backend_secp256k1_private_key_free     NULL
#define nrf_crypto_backend_secp256k1_public_key_free      NULL

// Context sizes required by CC310
#define NRF_CRYPTO_BACKEND_SECP256K1_KEY_PAIR_GENERATE_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_key_pair_generate_context_t)
#define NRF_CRYPTO_BACKEND_SECP256K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// Most CC310 curve types share the same data structures for keys
typedef nrf_crypto_backend_cc310_ecc_private_key_t nrf_crypto_backend_secp256k1_private_key_t;
typedef nrf_crypto_backend_cc310_ecc_public_key_t  nrf_crypto_backend_secp256k1_public_key_t;

// Most CC310 curve types share the same data structures for context
typedef nrf_crypto_backend_cc310_key_pair_generate_context_t
    nrf_crypto_backend_secp256k1_key_pair_generate_context_t;

// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp256k1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP256K1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_CURVE25519)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_CURVE25519)
#error "More than one backend enabled for Curve25519.");
#endif
#define NRF_CRYPTO_ECC_CURVE25519_ENABLED 1

/** @internal @brief Common structure holding context for Curve25519 (all operations).
 */
typedef struct
{
    CRYS_ECMONT_TempBuff_t temp_data;   /**< @internal @brief Temporary buffer for CC310 internal storage */
} nrf_crypto_backend_cc310_curve25519_context_t;

/** @internal @brief Structure holding keys for Curve25519.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header;  /**< @internal @brief Common ECC key header. */
    uint8_t key[32];                              /**< @internal @brief Raw key in little-endian order. */
} nrf_crypto_backend_curve25519_key_t;

// Most CC310 curve types share the same data structures for keys
typedef nrf_crypto_backend_curve25519_key_t     nrf_crypto_backend_curve25519_private_key_t;
typedef nrf_crypto_backend_curve25519_key_t     nrf_crypto_backend_curve25519_public_key_t;

/** @internal See @ref nrf_crypto_backend_ecc_key_pair_generate_fn_t.
 */
ret_code_t nrf_crypto_backend_cc310_curve25519_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key);

ret_code_t nrf_crypto_backend_cc310_curve25519_key_from_raw(
    void          * p_key,
    uint8_t const * p_raw_data);

ret_code_t nrf_crypto_backend_cc310_curve25519_key_to_raw(
    void const * p_key,
    uint8_t    * p_raw_data);

// Aliases for Curve25519-specific CC310 implementation.
#define nrf_crypto_backend_curve25519_key_pair_generate \
    nrf_crypto_backend_cc310_curve25519_key_pair_generate
#define nrf_crypto_backend_curve25519_private_key_from_raw \
    nrf_crypto_backend_cc310_curve25519_key_from_raw
#define nrf_crypto_backend_curve25519_private_key_to_raw   \
    nrf_crypto_backend_cc310_curve25519_key_to_raw
#define nrf_crypto_backend_curve25519_public_key_from_raw  \
    nrf_crypto_backend_cc310_curve25519_key_from_raw
#define nrf_crypto_backend_curve25519_public_key_to_raw    \
    nrf_crypto_backend_cc310_curve25519_key_to_raw

// Aliases for unused or unimplemented functions.
#define nrf_crypto_backend_curve25519_public_key_calculate NULL
#define nrf_crypto_backend_curve25519_private_key_free     NULL
#define nrf_crypto_backend_curve25519_public_key_free      NULL

// Context sizes required by CC310 Curve25519.
#define NRF_CRYPTO_BACKEND_CURVE25519_KEY_PAIR_GENERATE_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_curve25519_context_t)
#define NRF_CRYPTO_BACKEND_CURVE25519_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// All CC310 Curve25519 operations share the same data structures for context.
typedef nrf_crypto_backend_cc310_curve25519_context_t
    nrf_crypto_backend_curve25519_key_pair_generate_context_t;

// Dummy typedef for unused context.
typedef nrf_crypto_backend_cc310_curve25519_context_t
    nrf_crypto_backend_curve25519_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_CURVE25519)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_ED25519)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_ED25519)
#error "More than one backend enabled for Ed25519.");
#endif
#define NRF_CRYPTO_ECC_ED25519_ENABLED 1

/** @internal @brief Common structure holding context for Ed25519 (all operations).
 */
typedef struct
{
    CRYS_ECEDW_TempBuff_t temp_data;   /**< @internal @brief Temporary buffer for CC310 internal storage. */
} nrf_crypto_backend_cc310_ed25519_context_t;


/** @internal @brief Structure holding private key for Ed25519.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header;    /**< @internal @brief Common ECC key header. */
    uint8_t key[2 * CRYS_ECEDW_ORD_SIZE_IN_BYTES];  /**< @internal @brief Raw private key (seed || pubKey) in little-endian order. */
} nrf_crypto_backend_ed25519_private_key_t;


/** @internal @brief Structure holding public key for Ed25519.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header;    /**< @internal @brief Common ECC key header. */
    uint8_t key[CRYS_ECEDW_ORD_SIZE_IN_BYTES];      /**< @internal @brief Raw public key in little-endian order. */
} nrf_crypto_backend_ed25519_public_key_t;


/** @internal See @ref nrf_crypto_backend_ecc_key_pair_generate_fn_t.
 */
ret_code_t nrf_crypto_backend_cc310_ed25519_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key);

ret_code_t nrf_crypto_backend_cc310_ed25519_private_key_from_raw(
    void          * p_key,
    uint8_t const * p_raw_data);

ret_code_t nrf_crypto_backend_cc310_ed25519_private_key_to_raw(
    void const * p_key,
    uint8_t    * p_raw_data);

ret_code_t nrf_crypto_backend_cc310_ed25519_public_key_from_raw(
    void          * p_key,
    uint8_t const * p_raw_data);

ret_code_t nrf_crypto_backend_cc310_ed25519_public_key_to_raw(
    void const * p_key,
    uint8_t    * p_raw_data);

ret_code_t nrf_crypto_backend_cc310_ed25519_public_key_calculate(
    void       * p_context,
    void const * p_private_key,
    void       * p_public_key);

// Aliases for Ed25519-specific CC310 implementation.
#define nrf_crypto_backend_ed25519_key_pair_generate        \
    nrf_crypto_backend_cc310_ed25519_key_pair_generate
#define nrf_crypto_backend_ed25519_private_key_from_raw     \
    nrf_crypto_backend_cc310_ed25519_private_key_from_raw
#define nrf_crypto_backend_ed25519_private_key_to_raw       \
    nrf_crypto_backend_cc310_ed25519_private_key_to_raw
#define nrf_crypto_backend_ed25519_public_key_from_raw      \
    nrf_crypto_backend_cc310_ed25519_public_key_from_raw
#define nrf_crypto_backend_ed25519_public_key_to_raw        \
    nrf_crypto_backend_cc310_ed25519_public_key_to_raw
#define nrf_crypto_backend_ed25519_public_key_calculate     \
    nrf_crypto_backend_cc310_ed25519_public_key_calculate

// Aliases for unused or unimplemented functions.
#define nrf_crypto_backend_ed25519_private_key_free     NULL
#define nrf_crypto_backend_ed25519_public_key_free      NULL

// Context sizes required by CC310 Ed25519
#define NRF_CRYPTO_BACKEND_ED25519_KEY_PAIR_GENERATE_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_ed25519_context_t)
#define NRF_CRYPTO_BACKEND_ED25519_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0

// All CC310 Ed25519 operations share the same data structures for context.
typedef nrf_crypto_backend_cc310_ed25519_context_t
    nrf_crypto_backend_ed25519_key_pair_generate_context_t;

// Dummy typedef for unused context.
typedef nrf_crypto_backend_cc310_ed25519_context_t
    nrf_crypto_backend_ed25519_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_ED25519)


#ifdef __cplusplus
}
#endif

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)

#endif // CC310_BACKEND_ECC_H__
