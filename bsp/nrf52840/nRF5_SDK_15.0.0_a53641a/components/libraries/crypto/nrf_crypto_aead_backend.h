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

#ifndef NRF_CRYPTO_AEAD_BACKEND_H__
#define NRF_CRYPTO_AEAD_BACKEND_H__

#include "cc310_backend_aes_aead.h"
#include "cc310_backend_chacha_poly_aead.h"
#include "cifra_backend_aes_aead.h"
#include "mbedtls_backend_aes_aead.h"
#include "oberon_backend_chacha_poly_aead.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@internal @brief Fallback type for AES CCM context (if no backend is enabled).
 */
#if !NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CCM)
typedef nrf_crypto_aead_internal_context_t nrf_crypto_backend_aes_ccm_context_t;
#endif

/**@internal @brief Fallback type for AES CCM* context (if no backend is enabled).
 */
#if !NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CCM_STAR)
typedef nrf_crypto_aead_internal_context_t nrf_crypto_backend_aes_ccm_star_context_t;
#endif

/**@internal @brief Fallback type for AES EAX context (if no backend is enabled).
 */
#if !NRF_MODULE_ENABLED(NRF_CRYPTO_AES_EAX)
typedef nrf_crypto_aead_internal_context_t nrf_crypto_backend_aes_eax_context_t;
#endif

/**@internal @brief Fallback type for AES GCM context (if no backend is enabled).
 */
#if !NRF_MODULE_ENABLED(NRF_CRYPTO_AES_GCM)
typedef nrf_crypto_aead_internal_context_t nrf_crypto_backend_aes_gcm_context_t;
#endif

/**@internal @brief Fallback type for CHACHA-POLY context (if no backend is enabled).
 */
#if !NRF_MODULE_ENABLED(NRF_CRYPTO_CHACHA_POLY)
typedef nrf_crypto_aead_internal_context_t nrf_crypto_backend_chacha_poly_context_t;
#endif

/** @internal @brief Union holding a AEAD context. */
typedef union
{
    nrf_crypto_backend_aes_ccm_context_t      ccm_context;          /**< @brief Holds context for AES CCM. */
    nrf_crypto_backend_aes_ccm_star_context_t ccm_star_context;     /**< @brief Holds context for AES CCM*. */
    nrf_crypto_backend_aes_eax_context_t      eax_context;          /**< @brief Holds context for AES EAX. */
    nrf_crypto_backend_aes_gcm_context_t      gcm_context;          /**< @brief Holds context for AES GCM. */

    nrf_crypto_backend_chacha_poly_context_t  chacha_poly_context;  /**< @brief Holds context for ChaCha-Poly. */
} nrf_crypto_backend_aead_context_t;


#ifdef __cplusplus
}
#endif

#endif // NRF_CRYPTO_AEAD_BACKEND_H__
