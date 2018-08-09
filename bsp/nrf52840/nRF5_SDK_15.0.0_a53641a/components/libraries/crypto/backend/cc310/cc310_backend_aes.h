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

#ifndef CC310_BACKEND_AES_H__
#define CC310_BACKEND_AES_H__

/** @file
 *
 * @defgroup nrf_crypto_cc310_backend_aes nrf_crypto CC310 backend AES
 * @{
 * @ingroup nrf_crypto_cc310_backend
 *
 * @brief AES functionality provided by the nrf_crypto CC310 backend.
 */

#include "sdk_config.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310) || defined(__SDK_DOXYGEN__)

#include "ssi_aes.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_types.h"
#include "nrf_crypto_aes_shared.h"

#ifdef __cplusplus
extern "C" {
#endif


/* AES CBC */
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CBC)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CBC)
#error "Duplicate definition of AES CBC mode. More than one backend enabled");
#endif
#define NRF_CRYPTO_AES_CBC_ENABLED 1
#undef  NRF_CRYPTO_AES_ENABLED
#define NRF_CRYPTO_AES_ENABLED 1    // Flag that nrf_crypto_aes frontend can be compiled
#undef  NRF_CRYPTO_CC310_AES_ENABLED
#define NRF_CRYPTO_CC310_AES_ENABLED 1

/* define for test purposes */
#define NRF_CRYPTO_AES_CBC_128_ENABLED  1

typedef struct
{
    nrf_crypto_aes_internal_context_t header;  /**< Common header for context. */
    SaSiAesUserContext_t              context; /**< AES context internal to CC310. */
    nrf_crypto_backend_aes_ctx_t      backend;
} nrf_crypto_backend_aes_cbc_context_t;
#endif

/* AES CTR */
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CTR)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CTR)
#error "Duplicate definition of AES CTR mode. More than one backend enabled");
#endif
#define NRF_CRYPTO_AES_CTR_ENABLED 1
#undef  NRF_CRYPTO_AES_ENABLED
#define NRF_CRYPTO_AES_ENABLED 1    // Flag that nrf_crypto_aes frontend can be compiled
#undef  NRF_CRYPTO_CC310_AES_ENABLED
#define NRF_CRYPTO_CC310_AES_ENABLED 1

/* define for test purposes */
#define NRF_CRYPTO_AES_CTR_128_ENABLED 1

typedef struct
{
    nrf_crypto_aes_internal_context_t header;  /**< Common header for context. */
    SaSiAesUserContext_t              context; /**< AES context internal to CC310. */
    nrf_crypto_backend_aes_ctx_t      backend;
} nrf_crypto_backend_aes_ctr_context_t;
#endif

/* AES ECB */
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_ECB)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_AES_ECB)
#error "Duplicate definition of AES ECB mode. More than one backend enabled");
#endif
#define NRF_CRYPTO_AES_ECB_ENABLED 1
#undef  NRF_CRYPTO_AES_ENABLED
#define NRF_CRYPTO_AES_ENABLED 1    // Flag that nrf_crypto_aes frontend can be compiled
#undef  NRF_CRYPTO_CC310_AES_ENABLED
#define NRF_CRYPTO_CC310_AES_ENABLED 1

/* define for test purposes */
#define NRF_CRYPTO_AES_ECB_128_ENABLED 1

typedef struct
{
    nrf_crypto_aes_internal_context_t  header;  /**< Common header for context. */
    SaSiAesUserContext_t               context; /**< AES context internal to CC310. */
    nrf_crypto_backend_no_iv_aes_ctx_t backend;
} nrf_crypto_backend_aes_ecb_context_t;
#endif


/* AES CBC_MAC */
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CBC_MAC)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CBC_MAC)
#error "Duplicate definition of AES CBC_MAC mode. More than one backend enabled");
#endif
#define NRF_CRYPTO_AES_CBC_MAC_ENABLED 1
#undef  NRF_CRYPTO_AES_ENABLED
#define NRF_CRYPTO_AES_ENABLED 1    // Flag that nrf_crypto_aes frontend can be compiled
#undef  NRF_CRYPTO_CC310_AES_ENABLED
#define NRF_CRYPTO_CC310_AES_ENABLED 1

/* define for test purposes */
#define NRF_CRYPTO_AES_CBC_MAC_128_ENABLED 1

typedef struct
{
    nrf_crypto_aes_internal_context_t header;  /**< Common header for context. */
    SaSiAesUserContext_t              context; /**< AES context internal to CC310. */
    nrf_crypto_backend_aes_ctx_t      backend;
} nrf_crypto_backend_aes_cbc_mac_context_t;
#endif

/* AES CMAC */
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_AES_CMAC)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CMAC)
#error "Duplicate definition of AES CMAC mode. More than one backend enabled");
#endif
#define NRF_CRYPTO_AES_CMAC_ENABLED 1
#undef  NRF_CRYPTO_AES_ENABLED
#define NRF_CRYPTO_AES_ENABLED 1    // Flag that nrf_crypto_aes frontend can be compiled
#undef  NRF_CRYPTO_CC310_AES_ENABLED
#define NRF_CRYPTO_CC310_AES_ENABLED 1

/* define for test purposes */
#define NRF_CRYPTO_AES_CMAC_128_ENABLED 1

typedef struct
{
    nrf_crypto_aes_internal_context_t  header;  /**< Common header for context. */
    SaSiAesUserContext_t               context; /**< AES context internal to CC310. */
    nrf_crypto_backend_no_iv_aes_ctx_t backend;
} nrf_crypto_backend_aes_cmac_context_t;

#endif

#ifdef __cplusplus
}
#endif

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)

/** @} */

#endif // CC310_BACKEND_AES_H__
