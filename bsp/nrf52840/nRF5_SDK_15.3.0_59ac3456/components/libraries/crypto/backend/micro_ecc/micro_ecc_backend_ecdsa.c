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

#include "sdk_config.h"
#include "nordic_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC)

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "nrf_crypto_ecc.h"
#include "nrf_crypto_ecdsa.h"
#include "nrf_crypto_shared.h"
#include "nrf_crypto_mem.h"
#include "micro_ecc_backend_ecc.h"
#include "micro_ecc_backend_shared.h"
#include "uECC.h"


ret_code_t nrf_crypto_backend_micro_ecc_sign(
    void           * p_context,
    void     const * p_private_key,
    uint8_t  const * p_data,
    size_t           data_size,
    uint8_t        * p_signature)
{
    int result;

    nrf_crypto_backend_micro_ecc_common_key_t const * p_prv =
        (nrf_crypto_backend_micro_ecc_common_key_t const *)p_private_key;

    uECC_Curve p_micro_ecc_curve = nrf_crypto_backend_micro_ecc_curve_get(p_prv);

#if ECC_BACKEND_SWAP_BYTES

    nrf_crypto_ecc_curve_info_t const * p_info = p_prv->header.p_info;

    size_t    hash_size = MIN(data_size, p_info->raw_private_key_size);
    uint8_t   hash_le[NRF_CRYPTO_ECC_RAW_PRIVATE_KEY_MAX_SIZE];

    nrf_crypto_internal_swap_endian(hash_le, p_data, hash_size);

    uECC_set_rng(nrf_crypto_backend_micro_ecc_rng_callback);

    result = uECC_sign((uint8_t const *)(&p_prv->key[0]),
                       hash_le,
                       hash_size,
                       p_signature,
                       p_micro_ecc_curve);

    nrf_crypto_internal_double_swap_endian_in_place(p_signature, p_info->raw_private_key_size);

#else

    uECC_set_rng(nrf_crypto_backend_micro_ecc_rng_callback);

    result = uECC_sign((uint8_t const *)(&p_prv->key[0]),
                       p_data,
                       data_size,
                       p_signature,
                       p_micro_ecc_curve);

#endif

    if (result == 0)
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }
    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_micro_ecc_verify(
    void           * p_context,
    void     const * p_public_key,
    uint8_t  const * p_data,
    size_t           data_size,
    uint8_t  const * p_signature)
{
    int result;

    nrf_crypto_backend_micro_ecc_common_key_t const * p_pub =
        (nrf_crypto_backend_micro_ecc_common_key_t const *)p_public_key;

    uECC_Curve p_micro_ecc_curve = nrf_crypto_backend_micro_ecc_curve_get(p_pub);

#if ECC_BACKEND_SWAP_BYTES

    nrf_crypto_ecc_curve_info_t const * p_info = p_pub->header.p_info;

    size_t  hash_size = MIN(data_size, p_info->raw_private_key_size);
    uint8_t hash_le     [NRF_CRYPTO_ECC_RAW_PRIVATE_KEY_MAX_SIZE];
    uint8_t signature_le[NRF_CRYPTO_ECDSA_SIGNATURE_MAX_SIZE];

    nrf_crypto_internal_swap_endian(hash_le, p_data, hash_size);

    nrf_crypto_internal_double_swap_endian(signature_le,
                                           p_signature,
                                           p_info->raw_private_key_size);

    result = uECC_verify((uint8_t const *)(&p_pub->key[0]),
                         hash_le,
                         hash_size,
                         signature_le,
                         p_micro_ecc_curve);

#else

    result = uECC_verify((uint8_t const *)(&p_pub->key[0]),
                         p_data,
                         data_size,
                         p_signature,
                         p_micro_ecc_curve);

#endif

    if (result == 0)
    {
        return NRF_ERROR_CRYPTO_ECDSA_INVALID_SIGNATURE;
    }

    return NRF_SUCCESS;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MICRO_ECC)

