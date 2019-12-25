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

#ifndef NRF_SW_BACKEND_HASH_H__
#define NRF_SW_BACKEND_HASH_H__

/** @file
 *
 * @defgroup nrf_crypto_nrf_sw_backend_hash nrf_crypto nRF SW backend hash
 * @{
 * @ingroup nrf_crypto_nrf_sw_backend
 *
 * @brief Legacy hash functionality for bootloader use in nRFx devices
 */

#include "sdk_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_NRF_SW)

#include "sha256.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_types.h"
#include "nrf_crypto_hash_shared.h"

#ifdef __cplusplus
extern "C" {
#endif

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_NRF_SW_HASH_SHA256)

// Flag that nrf_crypto_hash frontend can be compiled
#undef  NRF_CRYPTO_HASH_ENABLED
#define NRF_CRYPTO_HASH_ENABLED 1

// Duplicate backend enabled test for SHA-256
#if NRF_MODULE_ENABLED(NRF_CRYPTO_HASH_SHA256)
#error "Duplicate definition of SHA-256. More than one backend enabled");
#endif

// Flag that SHA-256 is enabled in backend
#define NRF_CRYPTO_HASH_SHA256_ENABLED 1

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_NRF_SW_HASH_SHA256)


/**@brief nrf_crypto_hash context for SHA-256 in nrf_crypto nrf_sw backend. */
typedef struct
{
    nrf_crypto_hash_internal_context_t  header;     /**< Common header for context. */
    sha256_context_t                    context;    /**< Hash context internal to nrf_sw. */
} nrf_crypto_backend_hash_sha256_context_t;


#ifdef __cplusplus
}
#endif

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_NRF_SW)

/**@} */

#endif // NRF_SW_BACKEND_HASH_H__
