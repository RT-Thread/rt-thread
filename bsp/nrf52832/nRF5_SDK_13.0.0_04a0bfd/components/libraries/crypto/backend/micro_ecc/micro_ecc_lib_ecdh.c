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

#if defined(NRF_CRYPTO_BACKEND_MICRO_ECC) && (NRF_CRYPTO_BACKEND_MICRO_ECC == 1)

#if defined(NRF_CRYPTO_SUPPORTS_RNG) && NRF_CRYPTO_SUPPORTS_RNG == 1

#include "nrf_crypto.h"
#include "micro_ecc_lib_ecdh.h"
#include "micro_ecc_lib_keys.h"
#include "micro_ecc_lib_init.h"
#include "micro_ecc_lib_shared.h"

#include "uECC.h"


static void swap_array_endian(uint8_t * p_in, uint32_t len, uint8_t * p_out)
{
    uint32_t i;
    for(i = 0; i < len; i++)
    {
        p_out[len-i-1] = p_in[i];
    }
}


uint32_t nrf_crypto_ecdh_shared_secret_compute(nrf_crypto_curve_info_t    curve_info,
                                               nrf_value_length_t const * p_private_key,
                                               nrf_value_length_t const * p_public_key,
                                               nrf_value_length_t       * p_shared_secret)
{
    uint32_t            ret_val;
    uint32_t            public_key_size;
    uint32_t            private_key_size;
    uint32_t            shared_secret_size;
    const struct        uECC_Curve_t * p_curve;
    uint8_t             shared_secret[NRF_CRYPTO_ECDH_SHARED_SECRET_MAX_SIZE];

    // This function does not require initialized nrf_crypto for this backend.

    // Check private key
    if (p_private_key == NULL   ||
        p_public_key == NULL    ||
        p_shared_secret == NULL )
    {
        return NRF_ERROR_NULL;
    }

    if (p_private_key->p_value == NULL      ||
        p_public_key->p_value == NULL       ||
        p_shared_secret->p_value == NULL    )
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    // Check type alignment
    if (!is_word_aligned(p_private_key->p_value)    ||
        !is_word_aligned(p_public_key->p_value)     ||
        !is_word_aligned(p_shared_secret->p_value)  )
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    // Check public key size
    ret_val = nrf_crypto_ecc_public_key_size_get(curve_info.curve_type, &public_key_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    if (public_key_size != p_public_key->length)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Check private key size
    ret_val = nrf_crypto_ecc_private_key_size_get(curve_info.curve_type, &private_key_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    if (private_key_size != p_private_key->length)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Check shared secret size
    ret_val = nrf_crypto_ecdh_shared_secret_size_get(curve_info.curve_type, &shared_secret_size);
    if (ret_val != NRF_SUCCESS)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    if (shared_secret_size != p_shared_secret->length)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    if (!micro_ecc_curve_domain_get(curve_info.curve_type, &p_curve))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if (!uECC_shared_secret(p_public_key->p_value,
                            p_private_key->p_value,
                            shared_secret,
                            p_curve))
    {
        return NRF_ERROR_INTERNAL;
    }

    // Convert result to Little endian
    if (curve_info.endian_type == NRF_CRYPTO_ENDIAN_LE)
    {
        memcpy(p_shared_secret->p_value, shared_secret, shared_secret_size);
    }
    else
    {
        swap_array_endian(shared_secret, shared_secret_size, p_shared_secret->p_value);
    }


    return NRF_SUCCESS;
}

#endif // Supports RNG

#endif // NRF_CRYPTO_BACKEND_MICRO_ECC

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
