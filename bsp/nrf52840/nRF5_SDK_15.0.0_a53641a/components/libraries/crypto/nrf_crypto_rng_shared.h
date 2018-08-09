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

#ifndef NRF_CRYPTO_RNG_SHARED_H__
#define NRF_CRYPTO_RNG_SHARED_H__

/** @file
 *
 * @defgroup nrf_crypto_rng_shared Types shared between all @ref nrf_crypto_rng backends.
 * @{
 * @ingroup nrf_crypto_rng
 *
 * @brief Types shared between all @ref nrf_crypto_rng backends.
 *
 * @details These types should not be used directly by the application.
 */

#include "sdk_common.h"

#ifdef __cplusplus
extern "C" {
#endif


#define NRF_CRYPTO_RNG_CONTEXT_INIT_MAGIC_VALUE (0x4d616961)


/**
 * @internal @brief Common header for each RNG backend context.
 *
 * @details This is an internal type that should not be used directly.
 */
typedef struct
{
    uint32_t    init_value; //!< Contains NRF_CRYPTO_RNG_CONTEXT_INIT_MAGIC_VALUE if initialized.
} nrf_crypto_rng_internal_context_t;


/**
 * @internal @brief Function for initializing the RNG backend.
 *
 * @note The backend function should never be called directly.
 *       Use @ref nrf_crypto_rng_init instead.
 *
 * @param[in,out]   p_context       Pointer to context structure.
 * @param[in,out]   p_temp_buffer   Temporary buffer needed during initialization of the backend.
 * @param[in]       use_mutex       Use mutex to prevent simultanious usage of backend resources.
 */
ret_code_t nrf_crypto_rng_backend_init(void * const p_context,
                                       void * const p_temp_buffer);


/**
 * @internal @brief Function for uninitializing the RNG backend.
 *
 * @note The backend function should never be called directly.
 *       Use @ref nrf_crypto_rng_uninit instead.
 *
 * @param[in,out]   p_context   Pointer to context structure.
 * @param[in]       use_mutex   Use mutex to prevent simultanious usage of backend resources.
 */
ret_code_t nrf_crypto_rng_backend_uninit(void   * const p_context);


/**
 * @internal @brief Function for retrieving a random vector from the RNG backend.
 *
 * @note The backend function should never be called directly.
 *       Use @ref nrf_crypto_rng_vector_generate instead.
 *
 * @param[in,out]   p_context   Pointer to context structure.
 * @param[out]      p_target    Buffer to hold the random generated data.
 * @param[in]       size        Length (in bytes) to generate random data for.
 * @param[in]       use_mutex   Use mutex to prevent simultanious usage of backend resources.
 */
ret_code_t nrf_crypto_rng_backend_vector_generate(void      * const p_context,
                                                  uint8_t   * const p_target,
                                                  size_t            size,
                                                  bool              use_mutex);


/**
 * @internal @brief This function is used for reseeding the RNG with additional entropy.
 *
 * @note The backend function should never be called directly.
 *       Use @ref nrf_crypto_rng_reseed instead.
 *
 * @param[in,out]   p_context       Pointer to context structure.
 * @param[in,out]   p_temp_buffer   Temporary buffer needed during initialization of the backend.
 * @param[in]       p_input_data    Input data used to increase the entropy.
 * @param[in]       size            Length of input data.
 */
ret_code_t nrf_crypto_rng_backend_reseed(void   * const p_context,
                                         void         * p_temp_buffer,
                                         uint8_t      * p_input_data,
                                         size_t         size);


#ifdef __cplusplus
}
#endif

/**@} */

#endif // NRF_CRYPTO_RNG_SHARED_H__
