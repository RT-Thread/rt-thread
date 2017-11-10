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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_CRYPTO)

#include "nrf_drv_rng.h"
#include "nrf_crypto_rng.h"

#if defined(NRF_CRYPTO_BACKEND_MICRO_ECC) && (NRF_CRYPTO_BACKEND_MICRO_ECC == 1)
#if defined(NRF_CRYPTO_SUPPORTS_RNG) && (NRF_CRYPTO_SUPPORTS_RNG == 1)

#include "uECC.h"

/** @brief  Function to greate random data conformant to the format of the
 *          micro_ecc API.
 */
static int rng_func(uint8_t * p_target, unsigned size)
{
    uint32_t err_code;
    err_code = nrf_crypto_rng_vector_generate(p_target, size);
    if (err_code == NRF_SUCCESS)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


uint32_t nrf_crypto_rng_init(void)
{
    uint32_t ret_val;

    ret_val = nrf_drv_rng_init(NULL);
    if (ret_val == NRF_SUCCESS)
    {
        uECC_set_rng(rng_func);
    }

    return ret_val;
}


uint32_t nrf_crypto_rng_vector_generate(uint8_t * p_target, uint32_t length)
{
    uint32_t err_code;
    uint8_t  available;
    uint8_t  cur_len;
    uint8_t  left           = length;

    if (p_target == NULL)
    {
        return NRF_ERROR_NULL;
    }

    do
    {
        nrf_drv_rng_bytes_available(&available);
        cur_len = MIN(left, available);

        err_code = nrf_drv_rng_rand(p_target + (length - left), cur_len);
        if(err_code != NRF_SUCCESS)
        {
            return err_code;
        }

        // Remove current length of generated data
        left -= cur_len;

    } while(left > 0);

    return NRF_SUCCESS;
}

#endif // NRF_CRYPTO_SUPPORTS_RNG

#endif // NRF_CRYPTO_BACKEND_MICRO_ECC

#endif // NRF_CRYPTO_BACKEND_SW
