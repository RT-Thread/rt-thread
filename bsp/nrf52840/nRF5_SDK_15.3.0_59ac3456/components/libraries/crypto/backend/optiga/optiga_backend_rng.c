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

#include "sdk_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OPTIGA)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OPTIGA_RNG)

#include "nrf_crypto_rng.h"
#include "optiga_backend_rng.h"
#include "optiga/optiga_crypt.h"


/** @brief Minimal size output of random data in OPTIGA Trust X
 *
 * @details See Solution Reference Manual v1.35, section 4.4.3.4
 */
#define OPTIGA_RNG_MIN_SIZE         (0x8)


/** @brief Maximum size output of random data in OPTIGA Trust X
 *
 * @details See Solution Reference Manual v1.35, section 4.4.3.4
 */
#define OPTIGA_RNG_MAX_SIZE         (0x100)


ret_code_t nrf_crypto_rng_backend_init(void * const p_context,
                                       void * const p_temp_buffer)
{
    UNUSED_PARAMETER(p_context);
    UNUSED_PARAMETER(p_temp_buffer);

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_rng_backend_uninit(void * const p_context)
{
    UNUSED_PARAMETER(p_context);

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_rng_backend_vector_generate(void      * const p_context,
                                                  uint8_t   * const p_target,
                                                  size_t            size,
                                                  bool              use_mutex)
{
    UNUSED_PARAMETER(use_mutex);
    UNUSED_PARAMETER(p_context);

    uint8_t backup[OPTIGA_RNG_MIN_SIZE] = {0};
    optiga_lib_status_t err;

    uint8_t * out_cur = p_target;

    size_t size_left = size;
    size_t cur_len = size_left;

    do
    {
        cur_len = size_left > OPTIGA_RNG_MAX_SIZE ? OPTIGA_RNG_MAX_SIZE : size_left;

        if (cur_len < OPTIGA_RNG_MIN_SIZE)
        {
            err = optiga_crypt_random(OPTIGA_RNG_TYPE_TRNG, backup, OPTIGA_RNG_MIN_SIZE);
            if(err != OPTIGA_LIB_SUCCESS)
            {
                return NRF_ERROR_CRYPTO_INTERNAL;
            }

            memcpy(out_cur, backup, cur_len);
        }
        else
        {
            err = optiga_crypt_random(OPTIGA_RNG_TYPE_TRNG, out_cur, cur_len);
            if (err != OPTIGA_LIB_SUCCESS)
            {
                return NRF_ERROR_CRYPTO_INTERNAL;
            }
        }

        out_cur += cur_len;
        size_left -= cur_len;

    } while(size_left > 0);

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_rng_backend_reseed(void   * const p_context,
                                         void         * p_temp_buffer,
                                         uint8_t      * p_input_data,
                                         size_t         size)
{
    UNUSED_PARAMETER(p_context);
    UNUSED_PARAMETER(p_temp_buffer);
    UNUSED_PARAMETER(p_input_data);
    UNUSED_PARAMETER(size);

    return NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
}

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OPTIGA_RNG)
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OPTIGA)
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
