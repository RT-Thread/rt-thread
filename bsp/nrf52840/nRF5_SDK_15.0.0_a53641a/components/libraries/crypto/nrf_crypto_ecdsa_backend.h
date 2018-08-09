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

#ifndef NRF_CRYPTO_ECDSA_BACKEND_H__
#define NRF_CRYPTO_ECDSA_BACKEND_H__
#if !defined(__SDK_DOXYGEN__)

#include <stdint.h>
#include <stddef.h>

#include "sdk_config.h"
#include "nrf_crypto_ecdsa_shared.h"

// Include all backends
#include "cc310_backend_ecdsa.h"
#include "cc310_bl_backend_ecdsa.h"
#include "mbedtls_backend_ecdsa.h"
#include "oberon_backend_ecdsa.h"
#include "micro_ecc_backend_ecdsa.h"


#ifdef __cplusplus
extern "C" {
#endif


#if !NRF_CRYPTO_ECC_SECP160R1_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_SECP160R1_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP160R1_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_secp160r1_sign_context_t;
typedef uint8_t nrf_crypto_backend_secp160r1_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_secp160r1_sign NULL
#define nrf_crypto_backend_secp160r1_verify NULL
#endif

#if !NRF_CRYPTO_ECC_SECP160R2_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_SECP160R2_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP160R2_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_secp160r2_sign_context_t;
typedef uint8_t nrf_crypto_backend_secp160r2_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_secp160r2_sign NULL
#define nrf_crypto_backend_secp160r2_verify NULL
#endif

#if !NRF_CRYPTO_ECC_SECP192R1_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_SECP192R1_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP192R1_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_secp192r1_sign_context_t;
typedef uint8_t nrf_crypto_backend_secp192r1_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_secp192r1_sign NULL
#define nrf_crypto_backend_secp192r1_verify NULL
#endif

#if !NRF_CRYPTO_ECC_SECP224R1_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_SECP224R1_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP224R1_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_secp224r1_sign_context_t;
typedef uint8_t nrf_crypto_backend_secp224r1_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_secp224r1_sign NULL
#define nrf_crypto_backend_secp224r1_verify NULL
#endif

#if !NRF_CRYPTO_ECC_SECP256R1_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_SECP256R1_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP256R1_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_secp256r1_sign_context_t;
typedef uint8_t nrf_crypto_backend_secp256r1_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_secp256r1_sign NULL
#define nrf_crypto_backend_secp256r1_verify NULL
#endif

#if !NRF_CRYPTO_ECC_SECP384R1_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_SECP384R1_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP384R1_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_secp384r1_sign_context_t;
typedef uint8_t nrf_crypto_backend_secp384r1_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_secp384r1_sign NULL
#define nrf_crypto_backend_secp384r1_verify NULL
#endif

#if !NRF_CRYPTO_ECC_SECP521R1_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_SECP521R1_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP521R1_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_secp521r1_sign_context_t;
typedef uint8_t nrf_crypto_backend_secp521r1_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_secp521r1_sign NULL
#define nrf_crypto_backend_secp521r1_verify NULL
#endif

#if !NRF_CRYPTO_ECC_SECP160K1_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_SECP160K1_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP160K1_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_secp160k1_sign_context_t;
typedef uint8_t nrf_crypto_backend_secp160k1_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_secp160k1_sign NULL
#define nrf_crypto_backend_secp160k1_verify NULL
#endif

#if !NRF_CRYPTO_ECC_SECP192K1_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_SECP192K1_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP192K1_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_secp192k1_sign_context_t;
typedef uint8_t nrf_crypto_backend_secp192k1_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_secp192k1_sign NULL
#define nrf_crypto_backend_secp192k1_verify NULL
#endif

#if !NRF_CRYPTO_ECC_SECP224K1_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_SECP224K1_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP224K1_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_secp224k1_sign_context_t;
typedef uint8_t nrf_crypto_backend_secp224k1_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_secp224k1_sign NULL
#define nrf_crypto_backend_secp224k1_verify NULL
#endif

#if !NRF_CRYPTO_ECC_SECP256K1_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_SECP256K1_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_SECP256K1_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_secp256k1_sign_context_t;
typedef uint8_t nrf_crypto_backend_secp256k1_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_secp256k1_sign NULL
#define nrf_crypto_backend_secp256k1_verify NULL
#endif

#if !NRF_CRYPTO_ECC_BP256R1_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_BP256R1_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_BP256R1_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_bp256r1_sign_context_t;
typedef uint8_t nrf_crypto_backend_bp256r1_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_bp256r1_sign NULL
#define nrf_crypto_backend_bp256r1_verify NULL
#endif

#if !NRF_CRYPTO_ECC_BP384R1_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_BP384R1_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_BP384R1_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_bp384r1_sign_context_t;
typedef uint8_t nrf_crypto_backend_bp384r1_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_bp384r1_sign NULL
#define nrf_crypto_backend_bp384r1_verify NULL
#endif

#if !NRF_CRYPTO_ECC_BP512R1_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_BP512R1_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_BP512R1_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_bp512r1_sign_context_t;
typedef uint8_t nrf_crypto_backend_bp512r1_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_bp512r1_sign NULL
#define nrf_crypto_backend_bp512r1_verify NULL
#endif

#if !NRF_CRYPTO_ECC_CURVE25519_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_CURVE25519_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_CURVE25519_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_curve25519_sign_context_t;
typedef uint8_t nrf_crypto_backend_curve25519_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_curve25519_sign NULL
#define nrf_crypto_backend_curve25519_verify NULL
#endif

#if !NRF_CRYPTO_ECC_ED25519_ENABLED
// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_ED25519_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_ED25519_VERIFY_CONTEXT_SIZE 0
// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_ed25519_sign_context_t;
typedef uint8_t nrf_crypto_backend_ed25519_verify_context_t;
// Backend implementation is NULL to indicate feature not supported
#define nrf_crypto_backend_ed25519_sign NULL
#define nrf_crypto_backend_ed25519_verify NULL
#endif


#ifdef __cplusplus
}
#endif

#endif // !defined(__SDK_DOXYGEN__)
#endif // NRF_CRYPTO_ECDSA_BACKEND_H__
