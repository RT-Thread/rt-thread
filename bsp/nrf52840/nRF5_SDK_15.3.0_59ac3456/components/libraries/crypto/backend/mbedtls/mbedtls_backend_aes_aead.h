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

#ifndef MBEDTLS_BACKEND_AES_AEAD_H__
#define MBEDTLS_BACKEND_AES_AEAD_H__

/** @file
 *
 * @defgroup nrf_crypto_mbedtls_backend_aes_aead nrf_crypto mbed TLS backend AES AEAD
 * @{
 * @ingroup nrf_crypto_mbedtls_backend
 *
 * @brief AES AEAD functionality provided by the nrf_crypto mbed TLS backend.
 */

#include "sdk_config.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS)
/*lint -save -e????*/
#include "mbedtls/ccm.h"
#include "mbedtls/gcm.h"
#include "mbedtls/platform.h"
/*lint -restore*/
#include "nrf_crypto_error.h"
#include "nrf_crypto_aead_shared.h"

#ifdef __cplusplus
extern "C" {
#endif

/* AES CCM */
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CCM)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CCM)
#error "Duplicate definition of AES CCM mode. More than one backend enabled");
#endif
#define NRF_CRYPTO_AES_CCM_ENABLED 1
#undef  NRF_CRYPTO_AEAD_ENABLED
#define NRF_CRYPTO_AEAD_ENABLED 1
#undef  NRF_CRYPTO_MBEDTLS_AES_AEAD_ENABLED
#define NRF_CRYPTO_MBEDTLS_AES_AEAD_ENABLED 1

/* defines for test purposes */
#define NRF_CRYPTO_AES_CCM_128_ENABLED  1
#define NRF_CRYPTO_AES_CCM_192_ENABLED  1
#define NRF_CRYPTO_AES_CCM_256_ENABLED  1

typedef struct
{
    nrf_crypto_aead_internal_context_t header;   /**< Common header for context. */
    mbedtls_ccm_context                context;  /**< AES CCM context internal to mbed TLS. */
} nrf_crypto_backend_aes_ccm_context_t;
#endif

/* AES GCM */
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_GCM)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_AES_GCM)
#error "Duplicate definition of AES GCM mode. More than one backend enabled");
#endif
#define NRF_CRYPTO_AES_GCM_ENABLED 1
#undef  NRF_CRYPTO_AEAD_ENABLED
#define NRF_CRYPTO_AEAD_ENABLED 1
#undef  NRF_CRYPTO_MBEDTLS_AES_AEAD_ENABLED
#define NRF_CRYPTO_MBEDTLS_AES_AEAD_ENABLED 1

/* defines for test purposes */
#define NRF_CRYPTO_AES_GCM_128_ENABLED  1
#define NRF_CRYPTO_AES_GCM_192_ENABLED  1
#define NRF_CRYPTO_AES_GCM_256_ENABLED  1

typedef struct
{
    nrf_crypto_aead_internal_context_t header;   /**< Common header for context. */
    mbedtls_gcm_context                context;  /**< AES GCM context internal to mbed TLS. */
} nrf_crypto_backend_aes_gcm_context_t;
#endif

#ifdef __cplusplus
}
#endif

#endif  // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS)

/** @} */

#endif // MBEDTLS_BACKEND_AES_AEAD_H__

