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

#include "sdk_config.h"
#include "nordic_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL)

#include <string.h>
#include "app_util.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_mem.h"
#include "nrf_crypto_shared.h"
#include "cc310_bl_backend_ecdsa.h"
#include "cc310_bl_backend_shared.h"
#include "cc310_backend_mutex.h"
#include "crys_ecpki_error.h"


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_ECC_SECP224R1) || \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_ECC_SECP256R1)

static ret_code_t crys_error_to_ret_code(CRYSError_t crys_error)
{
    switch (crys_error)
    {
        case CRYS_OK:
            return NRF_SUCCESS;

        case CRYS_ECDSA_VERIFY_INCONSISTENT_VERIFY_ERROR:
            return NRF_ERROR_CRYPTO_ECDSA_INVALID_SIGNATURE;

        default:
            break;
    }

    return NRF_ERROR_CRYPTO_INTERNAL;
}

#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_ECC_SECP224R1)

STATIC_ASSERT(offsetof(nrf_cc310_bl_ecc_signature_secp224r1_t, r) == 0,
              "Offset of r in nrf_cc310_bl_ecc_signature_secp224r1_t is unexpected");
STATIC_ASSERT(offsetof(nrf_cc310_bl_ecc_signature_secp224r1_t, s) ==
              NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE,
              "Offset of s in nrf_cc310_bl_ecc_signature_secp224r1_t is unexpected");


ret_code_t nrf_crypto_backend_secp224r1_verify(
    void           * p_context,
    void     const * p_public_key,
    uint8_t  const * p_data,
    size_t           data_size,
    uint8_t  const * p_signature)
{
    ret_code_t  result;
    CRYSError_t crys_error;
    bool        mutex_locked;

    nrf_crypto_backend_secp224r1_verify_context_t * p_ctx =
        (nrf_crypto_backend_secp224r1_verify_context_t *)p_context;

    nrf_crypto_backend_secp224r1_public_key_t * p_pub =
        (nrf_crypto_backend_secp224r1_public_key_t *)p_public_key;

    p_ctx->user_context.init_val = NRF_CC310_BL_ECDSA_CONTEXT_INITIALIZED;

#if defined(NRF_CRYPTO_BACKEND_CC310_BL_ECC_LITTLE_ENDIAN_ENABLED) && (NRF_CRYPTO_BACKEND_CC310_BL_ECC_LITTLE_ENDIAN_ENABLED == 1)

    size_t    hash_size = MIN(data_size, NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE);
    uint8_t * p_hash_and_sig_le =
        NRF_CRYPTO_ALLOC(hash_size + 2 * NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE);
    
    if (p_hash_and_sig_le == NULL)
    {
        return NRF_ERROR_CRYPTO_ALLOC_FAILED;
    }

    nrf_crypto_internal_swap_endian(p_hash_and_sig_le, p_data, hash_size);

    nrf_crypto_internal_double_swap_endian(&p_hash_and_sig_le[hash_size],
                                           p_signature,
                                           NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE);

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_bl_backend_enable();

    crys_error = nrf_cc310_bl_ecdsa_verify_secp224r1(
        &p_ctx->user_context,
        &p_pub->public_key,
        (nrf_cc310_bl_ecc_signature_secp224r1_t const *)&p_hash_and_sig_le[hash_size],
        p_hash_and_sig_le,
        hash_size);

    cc310_bl_backend_disable();

    cc310_backend_mutex_unlock();

    NRF_CRYPTO_FREE(p_hash_and_sig_le);

#elif defined(NRF_CRYPTO_BACKEND_CC310_BL_ECC_LITTLE_ENDIAN_ENABLED) && (NRF_CRYPTO_BACKEND_CC310_BL_ECC_LITTLE_ENDIAN_ENABLED == 0)

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_bl_backend_enable();        

    crys_error = nrf_cc310_bl_ecdsa_verify_secp224r1(
        &p_ctx->user_context,
        &p_pub->public_key,
        (nrf_cc310_bl_ecc_signature_secp224r1_t const *)p_signature,
        p_data,
        data_size);

    cc310_bl_backend_disable();

    cc310_backend_mutex_unlock();

#else

    #error NRF_CRYPTO_BACKEND_CC310_BL_ECC_LITTLE_ENDIAN_ENABLED define not found in sdk_config.h Inalid sdk_config.h!

#endif

    result = crys_error_to_ret_code(crys_error);

    return result;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_ECC_SECP224R1)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_ECC_SECP256R1)


STATIC_ASSERT(offsetof(nrf_cc310_bl_ecc_signature_secp256r1_t, r) == 0,
              "Offset of r in nrf_cc310_bl_ecc_signature_secp256r1_t is unexpected");

STATIC_ASSERT(offsetof(nrf_cc310_bl_ecc_signature_secp256r1_t, s) ==
              NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE,
              "Offset of s in nrf_cc310_bl_ecc_signature_secp256r1_t is unexpected");


ret_code_t nrf_crypto_backend_secp256r1_verify(
    void           * p_context,
    void     const * p_public_key,
    uint8_t  const * p_data,
    size_t           data_size,
    uint8_t  const * p_signature)
{
    ret_code_t  result;
    CRYSError_t crys_error;
    bool        mutex_locked;
    

    nrf_crypto_backend_secp256r1_verify_context_t * p_ctx =
        (nrf_crypto_backend_secp256r1_verify_context_t *)p_context;

    nrf_crypto_backend_secp256r1_public_key_t * p_pub =
        (nrf_crypto_backend_secp256r1_public_key_t *)p_public_key;

    p_ctx->user_context.init_val = NRF_CC310_BL_ECDSA_CONTEXT_INITIALIZED;

#if defined(NRF_CRYPTO_BACKEND_CC310_BL_ECC_LITTLE_ENDIAN_ENABLED) && (NRF_CRYPTO_BACKEND_CC310_BL_ECC_LITTLE_ENDIAN_ENABLED == 1)
    
    uint8_t     hash_le[NRF_CRYPTO_HASH_SIZE_SHA256];
    uint8_t     signature_le[NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE * 2];
    size_t      hash_size = MIN(data_size, NRF_CRYPTO_HASH_SIZE_SHA256);

    nrf_crypto_internal_swap_endian(hash_le, p_data, hash_size);

    nrf_crypto_internal_double_swap_endian(signature_le,
                                           p_signature,
                                           NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE);

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_bl_backend_enable();

    crys_error = nrf_cc310_bl_ecdsa_verify_secp256r1(
        &p_ctx->user_context,
        &p_pub->public_key,
        (nrf_cc310_bl_ecc_signature_secp256r1_t const *)signature_le,
        hash_le,
        hash_size);

    cc310_bl_backend_disable();

    cc310_backend_mutex_unlock();

#elif defined(NRF_CRYPTO_BACKEND_CC310_BL_ECC_LITTLE_ENDIAN_ENABLED) && (NRF_CRYPTO_BACKEND_CC310_BL_ECC_LITTLE_ENDIAN_ENABLED == 0)

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_bl_backend_enable();

    crys_error = nrf_cc310_bl_ecdsa_verify_secp256r1(
        &p_ctx->user_context,
        &p_pub->public_key,
        (nrf_cc310_bl_ecc_signature_secp256r1_t const *)p_signature,
        p_data,
        data_size);

    cc310_bl_backend_disable();

    cc310_backend_mutex_unlock();

#else
    
    #error NRF_CRYPTO_BACKEND_CC310_BL_ECC_LITTLE_ENDIAN_ENABLED define not found in sdk_config.h. Invalid sdk_config.file!

#endif

    result = crys_error_to_ret_code(crys_error);

    return result;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_ECC_SECP256R1)

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL)
