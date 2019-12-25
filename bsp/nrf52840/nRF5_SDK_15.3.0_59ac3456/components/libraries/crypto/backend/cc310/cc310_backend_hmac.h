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

#ifndef CC310_BACKEND_HMAC_H__
#define CC310_BACKEND_HMAC_H__

/** @file
 *
 * @defgroup nrf_crypto_cc310_backend_hmac CC310 backend for HMAC
 * @{
 * @ingroup nrf_crypto_cc310_backend
 *
 * @brief Backend wrapper for CryptoCell (CC310). None of these types should be used directly by the
 * application.
 */

#include "sdk_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310) &&                   \
        ( NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HMAC_SHA256) || \
          NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HMAC_SHA512) )

#include "nrf_crypto_hmac_shared.h"
#include "crys_hmac.h"

#ifdef __cplusplus
extern "C" {
#endif

#undef  NRF_CRYPTO_HMAC_ENABLED
#define NRF_CRYPTO_HMAC_ENABLED         1


/**
 * @internal @brief Internal context object used by the CC310 backend wrapper.
 *
 * @details The same type is used for all variants (hash types).
 *
 * @note This should never be used directly. Use @ref nrf_crypto_backend_hmac_sha256_context_t or
 * @ref nrf_crypto_backend_hmac_sha512_context_t instead.
 */
typedef struct
{
    nrf_crypto_hmac_internal_context_t  header;         //!< Internal nrf_crypto_hmac context header.
    CRYS_HMACUserContext_t              crys_context;   //!< CC310 context object.
} nrf_crypto_backend_cc310_hmac_context_t;


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HMAC_SHA256)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_HMAC_SHA256)
#error "Duplicate definition of HMAC SHA-256. More than one backend enabled"
#endif // NRF_CRYPTO_HMAC_SHA256_ENABLED
#define NRF_CRYPTO_HMAC_SHA256_ENABLED  1

/**
 * @internal @brief Context for HMAC SHA256 using CC310 backend.
 */
typedef nrf_crypto_backend_cc310_hmac_context_t nrf_crypto_backend_hmac_sha256_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HMAC_SHA256)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HMAC_SHA512)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_HMAC_SHA512)
#error "Duplicate definition of HMAC SHA-512. More than one backend enabled"
#endif // NRF_CRYPTO_HMAC_SHA512_ENABLED
#define NRF_CRYPTO_HMAC_SHA512_ENABLED  1

/**
 * @internal @brief Context for HMAC SHA512 using CC310 backend.
 */
typedef nrf_crypto_backend_cc310_hmac_context_t nrf_crypto_backend_hmac_sha512_context_t;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HMAC_SHA256)

#ifdef __cplusplus
}
#endif

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310) && ( NRF_MODULE_ENABLED((NRF_CRYPTO_BACKEND_CC310_HMAC_SHA256) || NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_HMAC_SHA512) )

/**@} */

#endif // CC310_BACKEND_HMAC_H__
