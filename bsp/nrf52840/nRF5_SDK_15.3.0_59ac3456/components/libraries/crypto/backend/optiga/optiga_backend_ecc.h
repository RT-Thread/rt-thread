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

#ifndef OPTIGA_BACKEND_ECC_H__
#define OPTIGA_BACKEND_ECC_H__

#include "sdk_config.h"
#include "nordic_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OPTIGA)

#include <stdint.h>
#include <stdbool.h>
#include "nrf_crypto_ecc.h"

/*lint -save -e????*/
#include "optiga/optiga_crypt.h"
/*lint -restore*/


#ifdef __cplusplus
extern "C" {
#endif

/** @internal Magic OID that indicates a host supplied public key
*/
#define NRF_CRYPTO_INFINEON_PUBKEY_HOST_OID 0xFFFF

/** @internal Magic OID that indicates to export the private key
*/
#define NRF_CRYPTO_INFINEON_PRIVKEY_HOST_OID 0xFFFE

/** @internal @brief Common structure holding private key for the OPTIGA backend.
 */
typedef struct nrf_crypto_backend_optiga_ecc_private_key_t
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header */
    optiga_key_id_t oid; // OID where the private key is stored
    uint8_t raw_privkey[64+2]; // Private Key encoded as DER OCTET STRING
} nrf_crypto_backend_optiga_ecc_private_key_t;

#define NRF_CRYPTO_INFINEON_SECP256R1_PRIVATE_KEY_FROM_OID(oid_value) {   \
    .key_secp256r1 = {                                                    \
        .header = {                                                       \
            .init_value = NRF_CRYPTO_INTERNAL_ECC_PRIVATE_KEY_INIT_VALUE, \
            .p_info = &g_nrf_crypto_ecc_secp256r1_curve_info              \
         },                                                               \
        .oid = (optiga_key_id_t)(oid_value)                                                \
    }                                                                     \
}

/** @internal @brief Common structure holding public key for the OPTIGA backend.
 */
typedef struct
{
    nrf_crypto_internal_ecc_key_header_t header; /**< @internal @brief Common ECC key header */
    optiga_key_id_t oid; // OID where the public key is stored
    uint8_t raw_pubkey[64+4]; // Public Key encoded as DER BITSTRING with header
} nrf_crypto_backend_secp256r1_public_key_t;

#define NRF_CRYPTO_INFINEON_SECP256R1_PUBLIC_KEY_FROM_OID(oid_value) {    \
    .key_secp256r1 = {                                                    \
        .header = {                                                       \
            .init_value = NRF_CRYPTO_INTERNAL_ECC_PUBLIC_KEY_INIT_VALUE,  \
            .p_info = &g_nrf_crypto_ecc_secp256r1_curve_info              \
         },                                                               \
        .oid = (optiga_key_id_t)(oid_value)                               \
    }                                                                     \
}

#define NRF_CRYPTO_INFINEON_SECP256R1_PUBLIC_KEY_RAW \
    NRF_CRYPTO_INFINEON_SECP256R1_PUBLIC_KEY_FROM_OID(NRF_CRYPTO_INFINEON_PUBKEY_HOST_OID)


/** @internal See @ref nrf_crypto_backend_ecc_key_pair_generate_fn_t.
 */
ret_code_t nrf_crypto_backend_optiga_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_calculate_fn_t.
*/
ret_code_t nrf_crypto_backend_optiga_public_key_calculate(
    void       * p_context,
    void const * p_private_key,
    void       * p_public_key);


/** @internal See @ref nrf_crypto_backend_ecc_private_key_from_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_optiga_private_key_from_raw(
    void          * p_private_key,
    uint8_t const * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_private_key_to_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_optiga_private_key_to_raw(
    void    const * p_private_key,
    uint8_t       * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_from_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_optiga_public_key_from_raw(
    void          * p_public_key,
    uint8_t const * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_public_key_to_raw_fn_t.
*/
ret_code_t nrf_crypto_backend_optiga_public_key_to_raw(
    void const * p_public_key,
    uint8_t    * p_raw_data);


/** @internal See @ref nrf_crypto_backend_ecc_key_free_fn_t.
*/
ret_code_t nrf_crypto_backend_optiga_private_key_free(
    void * p_private_key);


/** @internal See @ref nrf_crypto_backend_ecc_key_free_fn_t.
*/
ret_code_t nrf_crypto_backend_optiga_public_key_free(
    void * p_public_key);

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OPTIGA_ECC_SECP256R1)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_ECC_SECP256R1)
#error "More than one backend enabled for secp256r1 (NIST 256-bit).");
#endif
#define NRF_CRYPTO_ECC_SECP256R1_ENABLED 1

// Aliases for one common OPTIGA implementation
#define nrf_crypto_backend_secp256r1_key_pair_generate    nrf_crypto_backend_optiga_key_pair_generate
#define nrf_crypto_backend_secp256r1_public_key_calculate nrf_crypto_backend_optiga_public_key_calculate
#define nrf_crypto_backend_secp256r1_private_key_from_raw nrf_crypto_backend_optiga_private_key_from_raw
#define nrf_crypto_backend_secp256r1_private_key_to_raw   nrf_crypto_backend_optiga_private_key_to_raw
#define nrf_crypto_backend_secp256r1_public_key_from_raw  nrf_crypto_backend_optiga_public_key_from_raw
#define nrf_crypto_backend_secp256r1_public_key_to_raw    nrf_crypto_backend_optiga_public_key_to_raw
#define nrf_crypto_backend_secp256r1_private_key_free     nrf_crypto_backend_optiga_private_key_free
#define nrf_crypto_backend_secp256r1_public_key_free      nrf_crypto_backend_optiga_public_key_free
// OPTIGA does not require context, so its size is 0.
#define NRF_CRYPTO_BACKEND_SECP256R1_KEY_PAIR_GENERATE_CONTEXT_SIZE    0
#define NRF_CRYPTO_BACKEND_SECP256R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE 0
// All OPTIGA curve types share the same private key data structures
typedef nrf_crypto_backend_optiga_ecc_private_key_t nrf_crypto_backend_secp256r1_private_key_t;
// Dummy typedef for unused context
typedef uint32_t nrf_crypto_backend_secp256r1_key_pair_generate_context_t;
typedef uint32_t nrf_crypto_backend_secp256r1_public_key_calculate_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OPTIGA_ECC_SECP256R1)

#ifdef __cplusplus
}
#endif

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OPTIGA)

#endif // OPTIGA_BACKEND_ECC_H__
