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

#include "nrf_crypto_ecdsa.h"
#include "nrf_crypto_hash.h"
#include "nrf_crypto_mem.h"

#if NRF_CRYPTO_BACKEND_CC310_LIB
#include "cc310_lib_ecdsa.h"
#endif

#if NRF_CRYPTO_BACKEND_MICRO_ECC
#include "micro_ecc_lib_ecdsa.h"
#endif


uint32_t nrf_crypto_ecdsa_signature_size_get(nrf_ecc_curve_type_t curve_type, uint32_t * p_sig_size)
{
    switch(curve_type)
    {
        case NRF_CRYPTO_CURVE_SECP160R1:
            (*p_sig_size)= NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP160R1;
            break;

        case NRF_CRYPTO_CURVE_SECP192R1:
            (*p_sig_size) = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP192R1;
            break;

        case NRF_CRYPTO_CURVE_SECP224R1:
            (*p_sig_size) = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP224R1;
            break;

        case NRF_CRYPTO_CURVE_SECP256R1:
            (*p_sig_size) = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP256R1;
            break;

        case NRF_CRYPTO_CURVE_SECP384R1:
            (*p_sig_size) = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP384R1;
            break;

        case NRF_CRYPTO_CURVE_SECP521R1:
            (*p_sig_size) = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP521R1;
            break;

        case NRF_CRYPTO_CURVE_SECP192K1:
            (*p_sig_size) = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP192K1;
            break;

        case NRF_CRYPTO_CURVE_SECP224K1:
            (*p_sig_size) = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP224K1;
            break;

        case NRF_CRYPTO_CURVE_SECP256K1:
            (*p_sig_size) = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP256K1;
            break;

        case NRF_CRYPTO_CURVE_CURVE25519:
            // Not supported. Use Ed25519 instead of ECDSA.
            (*p_sig_size) = 0;
            return NRF_ERROR_NOT_SUPPORTED;

        default:
            (*p_sig_size) = 0;
            return NRF_ERROR_NOT_SUPPORTED;
    }

    return NRF_SUCCESS;
}


uint32_t nrf_crypto_ecdsa_sizes_get(nrf_crypto_signature_info_t sig_info,
                                    nrf_crypto_ecdsa_sizes_t * p_sizes)
{
    uint32_t ret_val;

    switch(sig_info.curve_type)
    {
        case NRF_CRYPTO_CURVE_SECP160R1:
            p_sizes->private_key_size = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP160R1;
            p_sizes->public_key_size = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP160R1;
            p_sizes->signature_size = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP160R1;
            break;

        case NRF_CRYPTO_CURVE_SECP192R1:
            p_sizes->private_key_size = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP192R1;
            p_sizes->public_key_size = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP192R1;
            p_sizes->signature_size = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP192R1;
            break;

        case NRF_CRYPTO_CURVE_SECP224R1:
            p_sizes->private_key_size = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP224R1;
            p_sizes->public_key_size = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP224R1;
            p_sizes->signature_size = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP224R1;
            break;

        case NRF_CRYPTO_CURVE_SECP256R1:
            p_sizes->private_key_size = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP256R1;
            p_sizes->public_key_size = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP256R1;
            p_sizes->signature_size = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP256R1;
            break;

        case NRF_CRYPTO_CURVE_SECP384R1:
            p_sizes->private_key_size = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP384R1;
            p_sizes->public_key_size = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP384R1;
            p_sizes->signature_size = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP384R1;
            break;

        case NRF_CRYPTO_CURVE_SECP521R1:
            p_sizes->private_key_size = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP521R1;
            p_sizes->public_key_size = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP521R1;
            p_sizes->signature_size = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP521R1;
            break;

        case NRF_CRYPTO_CURVE_SECP192K1:
            p_sizes->private_key_size = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP192K1;
            p_sizes->public_key_size = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP192K1;
            p_sizes->signature_size = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP192K1;
            break;

        case NRF_CRYPTO_CURVE_SECP224K1:
            p_sizes->private_key_size = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP224K1;
            p_sizes->public_key_size = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP224K1;
            p_sizes->signature_size = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP224K1;
            break;

        case NRF_CRYPTO_CURVE_SECP256K1:
            p_sizes->private_key_size = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP256K1;
            p_sizes->public_key_size = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP256K1;
            p_sizes->signature_size = NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP256K1;
            break;

        case NRF_CRYPTO_CURVE_CURVE25519:
            // Not supported. Use Ed25519 (EDDSA) instead of ECDSA.
            p_sizes->private_key_size = 0;
            p_sizes->public_key_size = 0;
            p_sizes->signature_size = 0;
            return NRF_ERROR_NOT_SUPPORTED;

        default:
            p_sizes->private_key_size = 0;
            p_sizes->public_key_size = 0;
            p_sizes->signature_size = 0;
            return NRF_ERROR_NOT_SUPPORTED;
    }

    ret_val = nrf_crypto_hash_size_get(sig_info.hash_type, &p_sizes->hash_size);
    return ret_val;
}


uint32_t nrf_crypto_ecdsa_signature_allocate(nrf_crypto_signature_info_t    sig_info,
                                             nrf_value_length_t           * p_signature,
                                             nrf_value_length_t     const * p_raw_signature)
{
    uint32_t        ret_val;
    uint32_t        sig_size;

    if (p_signature == NULL)
    {
        return NRF_ERROR_NULL;
    }

    ret_val = nrf_crypto_ecdsa_signature_size_get(sig_info.curve_type, &sig_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    ret_val = nrf_crypto_mem_allocate(sig_size, p_signature);
    return ret_val;
}


uint32_t nrf_crypto_ecdsa_signature_free(nrf_value_length_t * p_signature)
{
    uint32_t ret_val;

    if (p_signature == NULL)
    {
        return NRF_ERROR_NULL;
    }

    ret_val = nrf_crypto_mem_free(p_signature);
    return ret_val;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
