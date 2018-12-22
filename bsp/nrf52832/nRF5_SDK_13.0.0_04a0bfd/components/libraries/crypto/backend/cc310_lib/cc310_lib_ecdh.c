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
#include "nrf_crypto_hash.h"
#include "nrf_crypto_ecdh.h"

#if defined(NRF_CRYPTO_BACKEND_CC310_LIB) && (NRF_CRYPTO_BACKEND_CC310_LIB == 1)

#include <stdbool.h>
#include "cc310_lib_init.h"
#include "cc310_lib_keys.h"
#include "cc310_lib_shared.h"
#include "nrf_log.h"
#include "nrf_crypto_types.h"
#include "crys_ecpki_dh.h"

static void swap_array_endian(uint8_t * p_in, uint32_t len, uint8_t * p_out)
{
    for(uint32_t i = 0; i < len; i++)
    {
        p_out[len-i-1] = p_in[i];
    }
}

static uint32_t ecdh_shared_secret_compute_result_get(CRYSError_t error)
{
    uint32_t ret_val;

    switch(error)
    {
        case CRYS_OK:
            ret_val = NRF_SUCCESS;
            break;

        /* From calling CRYS_ECDH_SVDP_DH */
        case CRYS_ECDH_SVDP_DH_INVALID_PARTNER_PUBL_KEY_PTR_ERROR:
            ret_val = NRF_ERROR_INVALID_ADDR;
            break;

        case CRYS_ECDH_SVDP_DH_PARTNER_PUBL_KEY_VALID_TAG_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        case CRYS_ECDH_SVDP_DH_INVALID_USER_PRIV_KEY_PTR_ERROR:
            ret_val = NRF_ERROR_INVALID_ADDR;
            break;

        case CRYS_ECDH_SVDP_DH_USER_PRIV_KEY_VALID_TAG_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        case CRYS_ECDH_SVDP_DH_INVALID_SHARED_SECRET_VALUE_PTR_ERROR:
            ret_val = NRF_ERROR_INVALID_ADDR;
            break;

        case CRYS_ECDH_SVDP_DH_INVALID_TEMP_DATA_PTR_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        case CRYS_ECDH_SVDP_DH_INVALID_SHARED_SECRET_VALUE_SIZE_PTR_ERROR:
            ret_val = NRF_ERROR_INVALID_ADDR;
            break;

        case CRYS_ECDH_SVDP_DH_INVALID_SHARED_SECRET_VALUE_SIZE_ERROR:
            ret_val = NRF_ERROR_INVALID_LENGTH;
            break;

        case CRYS_ECDH_SVDP_DH_ILLEGAL_DOMAIN_ID_ERROR:
            ret_val = NRF_ERROR_NOT_SUPPORTED;
            break;

        case CRYS_ECDH_SVDP_DH_NOT_CONCENT_PUBL_AND_PRIV_DOMAIN_ID_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        /* From calling EcWrstDhDeriveSharedSecret */
        #if 0
        case ECWRST_DH_SHARED_VALUE_IS_ON_INFINITY_ERROR:
            ret_val = NRF_ERROR_INTERNAL;
            break;
        #endif
        default:
            ret_val = NRF_ERROR_INTERNAL;
            break;

    }

    return ret_val;
}


uint32_t nrf_crypto_ecdh_shared_secret_compute(nrf_crypto_curve_info_t    curve_info,
                                               nrf_value_length_t const * p_private_key,
                                               nrf_value_length_t const * p_public_key,
                                               nrf_value_length_t       * p_shared_secret)
{
    uint32_t                        ret_val;
    CRYSError_t                     crys_error;
    CRYS_ECPKI_Domain_t           * p_domain;
    CRYS_ECPKI_UserPrivKey_t      * p_private_key_user;
    CRYS_ECPKI_UserPublKey_t      * p_public_key_user;
    CRYS_ECDH_TempData_t            temp_buffer;
    uint32_t                        shared_secret_size;
    uint32_t                        shared_secret_size_temp;
    uint8_t                         shared_secret[NRF_CRYPTO_ECDH_SHARED_SECRET_MAX_SIZE];

    // Check that the library has been initialized
    if (!nrf_crypto_is_initialized())
    {
        return NRF_ERROR_INVALID_STATE;
    }

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

    // Get the curve domain from curve_type
    if (!cc310_curve_domain_get(curve_info.curve_type, &p_domain))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    // Ensure the private key size is valid
    if (p_private_key->length != NRF_CRYPTO_ECC_PRIVATE_KEY_MAX_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Ensure the public key size is valid
    if (p_public_key->length != NRF_CRYPTO_ECC_PUBLIC_KEY_MAX_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    ret_val = nrf_crypto_ecdh_shared_secret_size_get(curve_info.curve_type, &shared_secret_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    shared_secret_size_temp = shared_secret_size;

    // Ensure the shared secret can hold the output
    if (p_shared_secret->length != shared_secret_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Convert to the cc310 user types for private and public keys
    p_private_key_user  = (CRYS_ECPKI_UserPrivKey_t *) p_private_key->p_value;
    p_public_key_user   = (CRYS_ECPKI_UserPublKey_t *) p_public_key->p_value;

    crys_error = CRYS_ECDH_SVDP_DH(p_public_key_user,
                                   p_private_key_user,
                                   shared_secret,
                                   &shared_secret_size_temp,
                                   &temp_buffer);

    ret_val = ecdh_shared_secret_compute_result_get(crys_error);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    if (shared_secret_size_temp != shared_secret_size)
    {
        return NRF_ERROR_INTERNAL;
    }

    // Convert result to Little endian
    if (curve_info.endian_type == NRF_CRYPTO_ENDIAN_LE)
    {
        swap_array_endian(shared_secret, shared_secret_size, p_shared_secret->p_value);
    }
    else
    {
        memcpy(p_shared_secret->p_value, shared_secret, shared_secret_size);
    }


    return ret_val;
}

#endif // NRF_CRYPTO_BACKEND_CC310_LIB

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
