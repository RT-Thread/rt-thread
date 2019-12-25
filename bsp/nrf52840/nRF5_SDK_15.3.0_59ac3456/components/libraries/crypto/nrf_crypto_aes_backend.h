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

#ifndef NRF_CRYPTO_AES_BACKEND_H__
#define NRF_CRYPTO_AES_BACKEND_H__

#include "cc310_backend_aes.h"
#include "mbedtls_backend_aes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@internal @brief Fallback type for AES CBC context (if no backend is enabled).
 */
#if !NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CBC)
typedef nrf_crypto_aes_internal_context_t nrf_crypto_backend_aes_cbc_context_t;
#endif

/**@internal @brief Fallback type for AES CFB context (if no backend is enabled).
 */
#if !NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CFB)
typedef nrf_crypto_aes_internal_context_t nrf_crypto_backend_aes_cfb_context_t;
#endif

/**@internal @brief Fallback type for AES CTR context (if no backend is enabled).
 */
#if !NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CTR)
typedef nrf_crypto_aes_internal_context_t nrf_crypto_backend_aes_ctr_context_t;
#endif

/**@internal @brief Fallback type for AES ECB context (if no backend is enabled).
 */
#if !NRF_MODULE_ENABLED(NRF_CRYPTO_AES_ECB)
typedef nrf_crypto_aes_internal_context_t nrf_crypto_backend_aes_ecb_context_t;
#endif


/**@internal @brief Fallback type for AES CBC_MAC context (if no backend is enabled).
 */
#if !NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CBC_MAC)
typedef nrf_crypto_aes_internal_context_t nrf_crypto_backend_aes_cbc_mac_context_t;
#endif

/**@internal @brief Fallback type for AES CMAC context (if no backend is enabled).
 */
#if !NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CMAC)
typedef nrf_crypto_aes_internal_context_t nrf_crypto_backend_aes_cmac_context_t;
#endif

/**@internal @brief Fallback type for AES CMAC_PRF128 context (if no backend is enabled).
 */
#if !NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CMAC_PRF128)
typedef nrf_crypto_aes_internal_context_t nrf_crypto_backend_aes_cmac_prf128_context_t;
#endif


/** @internal @brief Union holding a AES context. */
typedef union
{
    nrf_crypto_backend_aes_cbc_context_t cbc_context;   /**< @brief Holds context for AES CBC. */
    nrf_crypto_backend_aes_cfb_context_t cfb_context;   /**< @brief Holds context for AES CFB. */
    nrf_crypto_backend_aes_ctr_context_t ctr_context;   /**< @brief Holds context for AES CFB. */
    nrf_crypto_backend_aes_ecb_context_t ecb_context;   /**< @brief Holds context for AES ECB. */

    nrf_crypto_backend_aes_cbc_mac_context_t     cbc_mac_context;       /**< @brief Holds context for CBC-MAC. */
    nrf_crypto_backend_aes_cmac_context_t        cmac_context;          /**< @brief Holds context for CMAC. */
    nrf_crypto_backend_aes_cmac_prf128_context_t cmac_prf128_context;   /**< @brief Holds context for CMAC_PRF128. */
} nrf_crypto_backend_aes_context_t;

#ifdef __cplusplus
}
#endif

#endif // NRF_CRYPTO_AES_BACKEND_H__
