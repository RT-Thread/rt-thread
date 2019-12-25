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

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL)

#include <string.h>

#include "nrf_crypto_mem.h"
#include "nrf_crypto_ecc.h"
#include "nrf_crypto_shared.h"
#include "cc310_bl_backend_ecc.h"


#if defined(NRF_CRYPTO_BACKEND_CC310_BL_ECC_LITTLE_ENDIAN_ENABLED)

#error The configuration NRF_CRYPTO_BACKEND_CC310_BL_ECC_LITTLE_ENDIAN_ENABLED was removed in SDK 15.1.0. Please see release notes for details on removing this error message.

#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_ECC_SECP224R1)


ret_code_t nrf_crypto_backend_secp224r1_public_key_from_raw(
    void          * p_public_key,
    uint8_t const * p_raw_data)
{
    nrf_crypto_backend_secp224r1_public_key_t * p_pub =
        (nrf_crypto_backend_secp224r1_public_key_t *)p_public_key;

    memcpy(&p_pub->public_key.x[0],
           &p_raw_data[0],
           NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE);
    memcpy(&p_pub->public_key.y[0],
           &p_raw_data[NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE],
           NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE);

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_secp224r1_public_key_to_raw(
    void const * p_public_key,
    uint8_t    * p_raw_data)
{
    nrf_crypto_backend_secp224r1_public_key_t const * p_pub =
        (nrf_crypto_backend_secp224r1_public_key_t const *)p_public_key;

    memcpy(&p_raw_data[0],
           &p_pub->public_key.x[0],
           NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE);
    memcpy(&p_raw_data[NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE],
           &p_pub->public_key.y[0],
           NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE);

    return NRF_SUCCESS;
}


nrf_crypto_ecc_curve_info_t const g_nrf_crypto_ecc_secp224r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_secp224r1_public_key_t),
    .private_key_size     = 0,
    .curve_type           = NRF_CRYPTO_ECC_SECP224R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP224R1_RAW_PUBLIC_KEY_SIZE,
};


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_ECC_SECP224R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_ECC_SECP256R1)


ret_code_t nrf_crypto_backend_secp256r1_public_key_from_raw(
    void          * p_public_key,
    uint8_t const * p_raw_data)
{
    nrf_crypto_backend_secp256r1_public_key_t * p_pub =
        (nrf_crypto_backend_secp256r1_public_key_t *)p_public_key;

    memcpy(&p_pub->public_key.x[0],
           &p_raw_data[0],
           NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE);
    memcpy(&p_pub->public_key.y[0],
           &p_raw_data[NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE],
           NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE);

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_secp256r1_public_key_to_raw(
    void const * p_public_key,
    uint8_t    * p_raw_data)
{
    nrf_crypto_backend_secp256r1_public_key_t const * p_pub =
        (nrf_crypto_backend_secp256r1_public_key_t const *)p_public_key;

    memcpy(&p_raw_data[0],
           &p_pub->public_key.x[0],
           NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE);
    memcpy(&p_raw_data[NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE],
           &p_pub->public_key.y[0],
           NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE);

    return NRF_SUCCESS;
}


nrf_crypto_ecc_curve_info_t const g_nrf_crypto_ecc_secp256r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_secp256r1_public_key_t),
    .private_key_size     = 0,
    .curve_type           = NRF_CRYPTO_ECC_SECP256R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE,
};


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_ECC_SECP256R1)


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL)
