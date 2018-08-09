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

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_CRYPTO) && \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_NRF_HW_RNG) && \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_NRF_HW_RNG_MBEDTLS_CTR_DRBG)

#include "nrf_crypto_rng.h"
#include "nrf_drv_rng.h"
#include "nrf_hw_backend_rng_mbedtls.h"


// Function to convert mbedtls error codes to ret_code_t.
static ret_code_t result_get(int mbedtls_ret_val)
{
    ret_code_t ret_val;
    switch (mbedtls_ret_val)
    {
        case 0:
            ret_val = NRF_SUCCESS;
            break;

        case MBEDTLS_ERR_CTR_DRBG_INPUT_TOO_BIG:
            ret_val = NRF_ERROR_CRYPTO_INPUT_LENGTH;
            break;

        case MBEDTLS_ERR_CTR_DRBG_REQUEST_TOO_BIG:
            ret_val = NRF_ERROR_CRYPTO_OUTPUT_LENGTH;
            break;

        case MBEDTLS_ERR_CTR_DRBG_ENTROPY_SOURCE_FAILED:
        default:
            ret_val = NRF_ERROR_CRYPTO_INTERNAL;
            break;
    }

    return ret_val;
}


// Callback function used by mbed TLS to seed and reseed.
static int entropy_callback(void * p_entropy, unsigned char * p_buffer, size_t size)
{
    UNUSED_PARAMETER(p_entropy);

    nrf_drv_rng_block_rand(p_buffer, size);

    return 0;
}


ret_code_t nrf_crypto_rng_backend_init(void * const p_context, void * const p_temp_buffer)
{
    ret_code_t                  ret_val;
    int                         mbedtls_ret_val;
    mbedtls_ctr_drbg_context  * p_mbedtls_context =
        &((nrf_crypto_backend_rng_context_t *)p_context)->mbedtls_context;

    UNUSED_PARAMETER(p_temp_buffer);

    ret_val = nrf_drv_rng_init(NULL);

    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    mbedtls_ctr_drbg_init(p_mbedtls_context);

    // Initial seeding. The nrf_crypto_rng API does not support additional entropy in the initial
    // seeding. Additional entropy can be provided using nrf_crypto_rng_backend_reseed(),
    // which calls mbedtls_ctr_drbg_reseed().
    mbedtls_ret_val = mbedtls_ctr_drbg_seed(p_mbedtls_context,
                                            entropy_callback,
                                            NULL,
                                            NULL,
                                            0);

    ret_val = result_get(mbedtls_ret_val);

    return ret_val;
}


ret_code_t nrf_crypto_rng_backend_uninit(void * const p_context)
{
    mbedtls_ctr_drbg_context  * p_mbedtls_context =
        &((nrf_crypto_backend_rng_context_t *)p_context)->mbedtls_context;

    mbedtls_ctr_drbg_free(p_mbedtls_context);
    nrf_drv_rng_uninit();

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_rng_backend_vector_generate(void      * const p_context,
                                                  uint8_t   * const p_target,
                                                  size_t            size,
                                                  bool              use_mutex)
{
    int                         mbedtls_ret_val;
    mbedtls_ctr_drbg_context  * p_mbedtls_context =
        &((nrf_crypto_backend_rng_context_t *)p_context)->mbedtls_context;

    UNUSED_PARAMETER(use_mutex);

    mbedtls_ret_val = mbedtls_ctr_drbg_random(p_mbedtls_context, p_target, size);

    return result_get(mbedtls_ret_val);
}


ret_code_t nrf_crypto_rng_backend_reseed(void   * const p_context,
                                         void         * p_temp_buffer,
                                         uint8_t      * p_input_data,
                                         size_t         size)
{
    int                         mbedtls_ret_val;
    mbedtls_ctr_drbg_context  * p_mbedtls_context =
        &((nrf_crypto_backend_rng_context_t *)p_context)->mbedtls_context;

    UNUSED_PARAMETER(p_temp_buffer);

    mbedtls_ret_val = mbedtls_ctr_drbg_reseed(p_mbedtls_context, p_input_data, size);

    return result_get(mbedtls_ret_val);
}

#endif //NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_NRF_HW_RNG) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_NRF_HW_RNG_MBEDTLS_CTR_DRBG)
