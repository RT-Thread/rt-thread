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

#ifndef MBEDTLS_BACKEND_AES_H__
#define MBEDTLS_BACKEND_AES_H__

/** @file
 *
 * @defgroup nrf_crypto_mbedtls_backend_aes nrf_crypto mbed TLS backend AES
 * @{
 * @ingroup nrf_crypto_mbedtls_backend
 *
 * @brief AES functionality provided by the nrf_crypto mbed TLS backend.
 */

#include "sdk_config.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS)

/*lint -save -e????*/
#include "mbedtls/aes.h"
#include "mbedtls/cmac.h"
#include "mbedtls/platform.h"
/*lint -restore*/
#include "nrf_crypto_error.h"
#include "nrf_crypto_types.h"
#include "nrf_crypto_aes_shared.h"

#ifdef __cplusplus
extern "C" {
#endif

/* AES CBC */
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CBC)
#error "Duplicate definition of AES CBC mode. More than one backend enabled");
#endif
/* Flag that AES CBC is enabled in backend */
#define NRF_CRYPTO_AES_CBC_ENABLED 1
#undef  NRF_CRYPTO_AES_ENABLED
#define NRF_CRYPTO_AES_ENABLED 1    // Flag that nrf_crypto_aes frontend can be compiled
#undef  NRF_CRYPTO_MBEDTLS_AES_ENABLED
#define NRF_CRYPTO_MBEDTLS_AES_ENABLED 1

/* defines for test purposes */
#define NRF_CRYPTO_AES_CBC_128_ENABLED  1
#define NRF_CRYPTO_AES_CBC_192_ENABLED  1
#define NRF_CRYPTO_AES_CBC_256_ENABLED  1

typedef struct
{
    nrf_crypto_aes_internal_context_t header;   /**< Common header for context. */
    nrf_crypto_backend_aes_ctx_t      backend;  /**< Backend-specific internal context. */
    mbedtls_aes_context               context;  /**< AES context internal to mbed TLS. */
} nrf_crypto_backend_aes_cbc_context_t;
#endif


/* AES CTR */
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CTR)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CTR)
#error "Duplicate definition of AES CTR mode. More than one backend enabled");
#endif
#define NRF_CRYPTO_AES_CTR_ENABLED 1
#undef  NRF_CRYPTO_AES_ENABLED
#define NRF_CRYPTO_AES_ENABLED 1    // Flag that nrf_crypto_aes frontend can be compiled
#undef  NRF_CRYPTO_MBEDTLS_AES_ENABLED
#define NRF_CRYPTO_MBEDTLS_AES_ENABLED 1

/* defines for test purposes */
#define NRF_CRYPTO_AES_CTR_128_ENABLED  1
#define NRF_CRYPTO_AES_CTR_192_ENABLED  1
#define NRF_CRYPTO_AES_CTR_256_ENABLED  1

typedef struct
{
    nrf_crypto_aes_internal_context_t header;   /**< Common header for context. */
    nrf_crypto_backend_aes_ctx_t      backend;  /**< Backend-specific internal context. */
    mbedtls_aes_context               context;  /**< AES context internal to mbed TLS. */
} nrf_crypto_backend_aes_ctr_context_t;
#endif

/* AES CFB */
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CFB)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CFB)
#error "Duplicate definition of AES CFB mode. More than one backend enabled");
#endif
#define NRF_CRYPTO_AES_CFB_ENABLED 1
#undef  NRF_CRYPTO_AES_ENABLED
#define NRF_CRYPTO_AES_ENABLED 1    // Flag that nrf_crypto_aes frontend can be compiled
#undef  NRF_CRYPTO_MBEDTLS_AES_ENABLED
#define NRF_CRYPTO_MBEDTLS_AES_ENABLED 1

/* defines for test purposes */
#define NRF_CRYPTO_AES_CFB_128_ENABLED  1
#define NRF_CRYPTO_AES_CFB_192_ENABLED  1
#define NRF_CRYPTO_AES_CFB_256_ENABLED  1

typedef struct
{
    nrf_crypto_aes_internal_context_t header;   /**< Common header for context. */
    nrf_crypto_backend_aes_ctx_t      backend;  /**< Backend-specific internal context. */
    mbedtls_aes_context               context;  /**< AES context internal to mbed TLS. */
} nrf_crypto_backend_aes_cfb_context_t;
#endif

/* AES ECB */
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_ECB)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_AES_ECB)
#error "Duplicate definition of AES ECB mode. More than one backend enabled");
#endif
#define NRF_CRYPTO_AES_ECB_ENABLED 1
#undef  NRF_CRYPTO_AES_ENABLED
#define NRF_CRYPTO_AES_ENABLED 1
#undef  NRF_CRYPTO_MBEDTLS_AES_ENABLED
#define NRF_CRYPTO_MBEDTLS_AES_ENABLED 1

/* defines for test purposes */
#define NRF_CRYPTO_AES_ECB_128_ENABLED  1
#define NRF_CRYPTO_AES_ECB_192_ENABLED  1
#define NRF_CRYPTO_AES_ECB_256_ENABLED  1

typedef struct
{
    nrf_crypto_aes_internal_context_t   header;   /**< Common header for context. */
    nrf_crypto_backend_no_iv_aes_ctx_t  backend;  /**< Backend-specific internal context. */
    mbedtls_aes_context                 context;  /**< AES context internal to mbed TLS. */
} nrf_crypto_backend_aes_ecb_context_t;
#endif


/* AES CBC MAC */
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CBC_MAC)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CBC_MAC)
#error "Duplicate definition of AES CBC MAC mode. More than one backend enabled");
#endif
/* Flag that AES CBC MAC is enabled in backend */
#define NRF_CRYPTO_AES_CBC_MAC_ENABLED 1
#undef  NRF_CRYPTO_AES_ENABLED
#define NRF_CRYPTO_AES_ENABLED 1    // Flag that nrf_crypto_aes frontend can be compiled
#undef  NRF_CRYPTO_MBEDTLS_AES_ENABLED
#define NRF_CRYPTO_MBEDTLS_AES_ENABLED 1

/* defines for test purposes */
#define NRF_CRYPTO_AES_CBC_MAC_128_ENABLED  1
#define NRF_CRYPTO_AES_CBC_MAC_192_ENABLED  1
#define NRF_CRYPTO_AES_CBC_MAC_256_ENABLED  1

typedef struct
{
    nrf_crypto_aes_internal_context_t header;   /**< Common header for context. */
    nrf_crypto_backend_aes_ctx_t      backend;  /**< Backend-specific internal context. */
    mbedtls_aes_context               context;  /**< AES context internal to mbed TLS. */
} nrf_crypto_backend_aes_cbc_mac_context_t;
#endif


/* AES CMAC */
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_AES_CMAC)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_AES_CMAC)
#error "Duplicate definition of AES CMAC mode. More than one backend enabled");
#endif
#define NRF_CRYPTO_AES_CMAC_ENABLED 1
#undef  NRF_CRYPTO_AES_ENABLED
#define NRF_CRYPTO_AES_ENABLED 1    // Flag that nrf_crypto_aes frontend can be compiled
#undef  NRF_CRYPTO_MBEDTLS_AES_ENABLED
#define NRF_CRYPTO_MBEDTLS_AES_ENABLED 1

/* defines for test purposes */
#define NRF_CRYPTO_AES_CMAC_128_ENABLED  1
#define NRF_CRYPTO_AES_CMAC_192_ENABLED  1
#define NRF_CRYPTO_AES_CMAC_256_ENABLED  1

typedef struct
{
    nrf_crypto_aes_internal_context_t  header;   /**< Common header for context. */
    nrf_crypto_backend_no_iv_aes_ctx_t backend;  /**< Backend-specific internal context. */
    mbedtls_cipher_context_t           context;  /**< AES context internal to mbedtls. */
} nrf_crypto_backend_aes_cmac_context_t;
#endif

#ifdef __cplusplus
}
#endif

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS)

/** @} */

#endif // MBEDTLS_BACKEND_AES_H__
