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

#ifndef CC310_BACKEND_ECDH_H__
#define CC310_BACKEND_ECDH_H__

#include "sdk_config.h"
#include "nordic_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)

#include "nrf_crypto_ecc.h"
#include "nrf_crypto_ecdh_shared.h"
#include "crys_ecpki_dh.h"


#ifdef __cplusplus
extern "C" {
#endif


/** @internal @brief Common structure holding context for ECDH.
 */
typedef union
{
    CRYS_ECDH_TempData_t        temp_data;           /**< @internal @brief Temporary buffer for CC310 internal storage */
    CRYS_ECPKI_BUILD_TempData_t key_build_temp_data; /**< @internal @brief Temporary buffer for CC310 public key build */
} nrf_crypto_backend_cc310_ecdh_compute_context_t;


/** @internal See @ref nrf_crypto_backend_ecdh_compute_fn_t.
 */
ret_code_t nrf_crypto_backend_cc310_ecdh_compute(
    void       * p_context,
    void const * p_private_key,
    void const * p_public_key,
    uint8_t    * p_shared_secret);


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP160R1)
// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp160r1_ecdh_compute nrf_crypto_backend_cc310_ecdh_compute
#define NRF_CRYPTO_BACKEND_SECP160R1_ECDH_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_ecdh_compute_context_t)
typedef nrf_crypto_backend_cc310_ecdh_compute_context_t nrf_crypto_backend_secp160r1_ecdh_context_t;
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP160R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP160R2)
// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp160r2_ecdh_compute nrf_crypto_backend_cc310_ecdh_compute
#define NRF_CRYPTO_BACKEND_SECP160R2_ECDH_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_ecdh_compute_context_t)
typedef nrf_crypto_backend_cc310_ecdh_compute_context_t nrf_crypto_backend_secp160r2_ecdh_context_t;
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP160R2)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP192R1)
// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp192r1_ecdh_compute nrf_crypto_backend_cc310_ecdh_compute
#define NRF_CRYPTO_BACKEND_SECP192R1_ECDH_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_ecdh_compute_context_t)
typedef nrf_crypto_backend_cc310_ecdh_compute_context_t nrf_crypto_backend_secp192r1_ecdh_context_t;
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP192R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP224R1)
// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp224r1_ecdh_compute nrf_crypto_backend_cc310_ecdh_compute
#define NRF_CRYPTO_BACKEND_SECP224R1_ECDH_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_ecdh_compute_context_t)
typedef nrf_crypto_backend_cc310_ecdh_compute_context_t nrf_crypto_backend_secp224r1_ecdh_context_t;
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP224R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP256R1)
// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp256r1_ecdh_compute nrf_crypto_backend_cc310_ecdh_compute
#define NRF_CRYPTO_BACKEND_SECP256R1_ECDH_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_ecdh_compute_context_t)
typedef nrf_crypto_backend_cc310_ecdh_compute_context_t nrf_crypto_backend_secp256r1_ecdh_context_t;
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP256R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP384R1)
// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp384r1_ecdh_compute nrf_crypto_backend_cc310_ecdh_compute
#define NRF_CRYPTO_BACKEND_SECP384R1_ECDH_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_ecdh_compute_context_t)
typedef nrf_crypto_backend_cc310_ecdh_compute_context_t nrf_crypto_backend_secp384r1_ecdh_context_t;
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP384R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP521R1)
// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp521r1_ecdh_compute nrf_crypto_backend_cc310_ecdh_compute
#define NRF_CRYPTO_BACKEND_SECP521R1_ECDH_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_ecdh_compute_context_t)
typedef nrf_crypto_backend_cc310_ecdh_compute_context_t nrf_crypto_backend_secp521r1_ecdh_context_t;
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP521R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP160K1)
// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp160k1_ecdh_compute nrf_crypto_backend_cc310_ecdh_compute
#define NRF_CRYPTO_BACKEND_SECP160K1_ECDH_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_ecdh_compute_context_t)
typedef nrf_crypto_backend_cc310_ecdh_compute_context_t nrf_crypto_backend_secp160k1_ecdh_context_t;
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP160K1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP192K1)
// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp192k1_ecdh_compute nrf_crypto_backend_cc310_ecdh_compute
#define NRF_CRYPTO_BACKEND_SECP192K1_ECDH_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_ecdh_compute_context_t)
typedef nrf_crypto_backend_cc310_ecdh_compute_context_t nrf_crypto_backend_secp192k1_ecdh_context_t;
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP192K1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP224K1)
// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp224k1_ecdh_compute nrf_crypto_backend_cc310_ecdh_compute
#define NRF_CRYPTO_BACKEND_SECP224K1_ECDH_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_ecdh_compute_context_t)
typedef nrf_crypto_backend_cc310_ecdh_compute_context_t nrf_crypto_backend_secp224k1_ecdh_context_t;
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP224K1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP256K1)
// Aliases for one common CC310 implementation
#define nrf_crypto_backend_secp256k1_ecdh_compute nrf_crypto_backend_cc310_ecdh_compute
#define NRF_CRYPTO_BACKEND_SECP256K1_ECDH_CONTEXT_SIZE \
    sizeof(nrf_crypto_backend_cc310_ecdh_compute_context_t)
typedef nrf_crypto_backend_cc310_ecdh_compute_context_t nrf_crypto_backend_secp256k1_ecdh_context_t;
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP256K1)


#ifdef __cplusplus
}
#endif

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)

#endif // CC310_BACKEND_ECDH_H__
