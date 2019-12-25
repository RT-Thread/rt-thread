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

#ifndef NRF_HW_BACKEND_RNG_H__
#define NRF_HW_BACKEND_RNG_H__

/** @file
 *
 * @defgroup nrf_crypto_nrf_hw_backend_rng nrf_crypto HW RNG backend
 * @{
 * @ingroup nrf_crypto_backends
 *
 * @brief RNG functionality provided by the nrf_crypto nRF HW RNG backend.
 */

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_NRF_HW_RNG) && \
    !NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_NRF_HW_RNG_MBEDTLS_CTR_DRBG)

#if !NRF_MODULE_ENABLED(RNG)
#error Enable RNG_ENABLED in sdk_config.h.
#endif

#if !NRFX_RNG_CONFIG_ERROR_CORRECTION
#error Enable NRFX_RNG_CONFIG_ERROR_CORRECTION and RNG_CONFIG_ERROR_CORRECTION in sdk_config.h.
#endif

#include "nrf_crypto_rng_shared.h"


#ifdef __cplusplus
extern "C" {
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_RNG)
#error "More than one RNG backend enabled."
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_RNG)
#define NRF_CRYPTO_RNG_ENABLED 1


/**
 * @internal @brief Context for nRF RNG peripheral.
 */
typedef struct
{
    nrf_crypto_rng_internal_context_t   header;         //!< Internal common context header.
} nrf_crypto_backend_rng_context_t;

/**
 * @internal @brief Dummy temp buffer for nRF RNG peripheral.
 */
typedef struct
{
    uint32_t reserved;
} nrf_crypto_backend_rng_temp_buffer_t;


#ifdef __cplusplus
}
#endif

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_NRF_HW_RNG) && !NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_NRF_HW_RNG_MBEDTLS_CTR_DRBG)

/**@} */

#endif // NRF_HW_BACKEND_RNG_H__
