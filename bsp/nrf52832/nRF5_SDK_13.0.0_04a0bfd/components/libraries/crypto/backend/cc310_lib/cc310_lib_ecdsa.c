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

#if defined(NRF_CRYPTO_BACKEND_CC310_LIB) && (NRF_CRYPTO_BACKEND_CC310_LIB == 1)

#include "cc310_lib_ecdsa.h"
#include "cc310_lib_init.h"
#include "cc310_lib_shared.h"
#include "ssi_pal_types.h"
#include "ssi_pal_mem.h"
#include "sns_silib.h"
#include "crys_rnd.h"
#include "crys_ecpki_ecdsa.h"
#include "crys_kdf_error.h"
#include "crys_hash_error.h"
#include "nrf_crypto_types.h"
#include "nrf_error.h"

extern CRYS_RND_Context_t    * gp_rnd_context;


static uint32_t ecdsa_result_get(CRYSError_t error)
{
    uint32_t ret_val = NRF_ERROR_INTERNAL;

    // TODO: Invalid data
    switch(error)
    {
        /* From calling CRYS_KDF_KeyDerivFunc */
        case CRYS_KDF_INVALID_ARGUMENT_POINTER_ERROR:
            ret_val = NRF_ERROR_INVALID_ADDR;
            break;

        case CRYS_KDF_INVALID_ARGUMENT_HASH_MODE_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        case CRYS_KDF_INVALID_KEY_DERIVATION_MODE_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        case CRYS_KDF_INVALID_SHARED_SECRET_VALUE_SIZE_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        case CRYS_KDF_INVALID_OTHER_INFO_SIZE_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        case CRYS_KDF_INVALID_KEYING_DATA_SIZE_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        /* From calling CRYS_HASH_Init, CRYS_HASH_Update and CRYS_HASH_Finish (KDF internal) */
        case CRYS_HASH_INVALID_USER_CONTEXT_POINTER_ERROR:
            ret_val = NRF_ERROR_INVALID_ADDR;
            break;

        case CRYS_HASH_ILLEGAL_OPERATION_MODE_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        case CRYS_HASH_USER_CONTEXT_CORRUPTED_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        case CRYS_HASH_DATA_IN_POINTER_INVALID_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        case CRYS_HASH_DATA_SIZE_ILLEGAL:
            ret_val = NRF_ERROR_INVALID_LENGTH;
            break;

        case CRYS_HASH_INVALID_RESULT_BUFFER_POINTER_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        case CRYS_HASH_DATA_SIZE_IS_ILLEGAL_FOR_CSI_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        case CRYS_HASH_LAST_BLOCK_ALREADY_PROCESSED_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        case CRYS_HASH_ILLEGAL_PARAMS_ERROR:

            break;
    }

    return ret_val;
}

/**@brief   Internal function to get the hash type that was used to generate the hash
 *          used for ECDSA sign/verify.
 */
bool ecdsa_hash_algorithm_get(nrf_hash_type_t hash_type,
                              CRYS_ECPKI_HASH_OpMode_t * p_hash_mode)
{
    switch(hash_type)
    {
        case NRF_CRYPTO_HASH_TYPE_SHA1:
            (*p_hash_mode) = CRYS_ECPKI_AFTER_HASH_SHA1_mode;
            break;

        case NRF_CRYPTO_HASH_TYPE_SHA224:
            (*p_hash_mode) = CRYS_ECPKI_AFTER_HASH_SHA224_mode;
            break;

        case NRF_CRYPTO_HASH_TYPE_SHA256:
            (*p_hash_mode) = CRYS_ECPKI_AFTER_HASH_SHA256_mode;
            break;

        case NRF_CRYPTO_HASH_TYPE_SHA384:
            (*p_hash_mode) = CRYS_ECPKI_AFTER_HASH_SHA384_mode;
            break;

        case NRF_CRYPTO_HASH_TYPE_SHA512:
            (*p_hash_mode) = CRYS_ECPKI_AFTER_HASH_SHA512_mode;
            break;

        default:
            return false;
    }

    return true;
}


uint32_t nrf_crypto_ecdsa_sign_hash(nrf_crypto_signature_info_t  sig_info,
                                    nrf_value_length_t   const * p_private_key,
                                    nrf_value_length_t   const * p_hash,
                                    nrf_value_length_t         * p_signature)
{
    uint32_t                        ret_val;
    CRYSError_t                     crys_error;
    CRYS_ECPKI_Domain_t           * p_domain;
    nrf_crypto_ecdsa_sizes_t        sig_sizes;

    // TODO: What is this?
    CRYS_ECDSA_SignUserContext_t * p_sig_user_context = NULL;
    CRYS_ECPKI_UserPrivKey_t     * p_private_key_user;
    CRYS_ECPKI_HASH_OpMode_t       hash_mode;

    // Check if library has been initialized
    if (!nrf_crypto_is_initialized())
    {
        return NRF_ERROR_INVALID_STATE;
    }

    // Basic parameter testing.
    if (p_private_key == NULL   ||
        p_signature == NULL     ||
        p_hash == NULL          )
    {
        return NRF_ERROR_NULL;
    }

    if (p_private_key->p_value == NULL  ||
        p_hash->p_value == NULL         ||
        p_signature->p_value == NULL    )
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    // Get the sizes for the keys, hash and signature
    ret_val = nrf_crypto_ecdsa_sizes_get(sig_info, &sig_sizes);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    // Check signature size.
    if (p_signature->length != sig_sizes.signature_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Check if private key size.
    if (p_private_key->length != sig_sizes.private_key_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Check the hash size.
    if (p_hash->length != sig_sizes.hash_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Try to get the correct curve domain.
    if (!cc310_curve_domain_get(sig_info.curve_type, &p_domain))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    // Get the hash type to indicate that hash has already been calculated.
    if (!ecdsa_hash_algorithm_get(sig_info.hash_type, &hash_mode))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    p_private_key_user = (CRYS_ECPKI_UserPrivKey_t*)p_private_key->p_value;

    crys_error = CRYS_ECDSA_Sign(gp_rnd_context,
                                 p_sig_user_context,
                                 p_private_key_user,
                                 hash_mode,
                                 p_hash->p_value,
                                 p_hash->length,
                                 p_signature->p_value,
                                 &p_signature->length);

    ret_val = ecdsa_result_get(crys_error);
    return ret_val;
}


uint32_t nrf_crypto_ecdsa_verify_hash(nrf_crypto_signature_info_t  sig_info,
                                      nrf_value_length_t   const * p_public_key,
                                      nrf_value_length_t   const * p_hash,
                                      nrf_value_length_t   const * p_signature)
{
    uint32_t                         ret_val;
    CRYSError_t                      crys_error;
    CRYS_ECPKI_Domain_t            * p_domain;
    CRYS_ECDSA_VerifyUserContext_t * p_verify_context_user = NULL;
    nrf_crypto_ecdsa_sizes_t         sig_sizes;
    CRYS_ECPKI_UserPublKey_t       * p_public_key_user;
    CRYS_ECPKI_HASH_OpMode_t         hash_mode;

    // Check if library has been initialized
    if (!nrf_crypto_is_initialized())
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (p_public_key == NULL    ||
        p_hash == NULL          ||
        p_signature == NULL     )
    {
        return NRF_ERROR_NULL;
    }

    if (p_public_key->p_value == NULL   ||
        p_hash->p_value == NULL         ||
        p_signature->p_value == NULL    )
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    // Get the sizes for the keys, hash and signature
    ret_val = nrf_crypto_ecdsa_sizes_get(sig_info, &sig_sizes);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    // Check the signature size.
    if (p_signature->length != sig_sizes.signature_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Check the private key size.
    if (p_public_key->length != sig_sizes.public_key_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Check the hash size.
    if (p_hash->length != sig_sizes.hash_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Try to get the correct curve domain
    if (!cc310_curve_domain_get(sig_info.curve_type, &p_domain))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    // Get the hash type to indicate that hash has already been calculated.
    if (!ecdsa_hash_algorithm_get(sig_info.hash_type, &hash_mode))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    p_public_key_user = (CRYS_ECPKI_UserPublKey_t *)p_public_key->p_value;

    crys_error = CRYS_ECDSA_Verify(p_verify_context_user,
                                   p_public_key_user,
                                   hash_mode,
                                   p_signature->p_value,
                                   p_signature->length,
                                   p_hash->p_value,
                                   p_hash->length);

    ret_val = ecdsa_result_get(crys_error);
    return ret_val;
}

#endif // NRF_CRYPTO_BACKEND_CC310_LIB

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
