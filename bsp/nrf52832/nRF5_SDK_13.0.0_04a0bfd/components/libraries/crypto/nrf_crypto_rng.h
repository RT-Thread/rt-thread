/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#ifndef NRF_CRYPTO_RNG_H__
#define NRF_CRYPTO_RNG_H__

/** @file
 *
 * @defgroup nrf_crypto_rng Random number generation related functions.
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides functions to initialize rng subsystem and generate random data.
 */

#include <stdint.h>
#include "nrf_crypto_types.h"

#ifdef __cplusplus
extern "C" {
#if 0
}
#endif
#endif

/**@brief Initialize the random number generator
 *
 * @note This function is called by @ref nrf_crypto_init.
 *
 * @retval  NRF_SUCCESS             If random number generator was initialized successfully.
 * @retval  NRF_ERROR_INTERNAL      If an internal error occured in the nrf_crypto backend.
 */
uint32_t nrf_crypto_rng_init(void);

/**@brief Generate random data into a buffer, given length as an input.
 *
 * @param[in,out]   p_target    Pointer to a buffer to accept the random generated data.
 *                              This buffer must be the same length as the length input.
 * @param[in]       length      Length (in bytes) to generate random data for.
 *
 * @retval  NRF_SUCCESS         Data was generated successfully.
 * @retval  NRF_ERROR_NULL      p_target was NULL.
 * @retval  NRF_ERROR_INTERNAL  If an internal error occured in the nrf_crypto backend.
 */
uint32_t nrf_crypto_rng_vector_generate(uint8_t * p_target, uint32_t length);

#ifdef __cplusplus
}
#endif

/**@} */

#endif // #ifndef NRF_CRYPTO_RNG_H__
