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

#include <stdbool.h>
#include "nrf_crypto_keys.h"
#include "cc310_lib_keys.h"
#include "cc310_lib_init.h"
#include "cc310_lib_shared.h"
#include "nrf_log.h"
#include "nrf_crypto_types.h"
#include "crys_ecpki_error.h"
#include "crys_ecpki_build.h"
#include "crys_ecpki_kg.h"
#include "string.h"

extern CRYS_RND_Context_t * gp_rnd_context;

static void swap_array_endian(uint8_t * p_in, uint32_t len, uint8_t * p_out)
{
    uint32_t i;
    for(i = 0; i < len; i++)
    {
        p_out[len-i-1] = p_in[i];
    }
}

static uint32_t key_pair_generate_result_get(CRYSError_t crys_error)
{
    uint32_t ret_val= NRF_ERROR_INTERNAL;

    switch(crys_error)
    {
        case CRYS_OK:
            ret_val = NRF_SUCCESS;
            break;
        case CRYS_ECPKI_RND_CONTEXT_PTR_ERROR:
            ret_val = NRF_ERROR_INVALID_STATE;
            break;

        case CRYS_ECPKI_ILLEGAL_D0MAIN_ID_ERROR:
            ret_val = NRF_ERROR_NOT_SUPPORTED;
            break;

        case CRYS_ECPKI_DOMAIN_PTR_ERROR:
            ret_val = NRF_ERROR_INTERNAL;
            break;

        case CRYS_ECPKI_GEN_KEY_INVALID_PRIVATE_KEY_PTR_ERROR:
            ret_val = NRF_ERROR_INVALID_ADDR;
            break;

        case CRYS_ECPKI_GEN_KEY_INVALID_PUBLIC_KEY_PTR_ERROR:
            ret_val = NRF_ERROR_INVALID_ADDR;
            break;

        case CRYS_ECPKI_GEN_KEY_INVALID_TEMP_DATA_PTR_ERROR:
            ret_val = NRF_ERROR_INTERNAL;
            break;

        #if 0
        /* From calling CRYS_RND_GenerateVectorInRange */
        case CRYS_RND_GEN_VECTOR_FUNC_ERROR:
            ret_val = NRF_ERROR_INVALID_STATE;
            break;

        case CRYS_RND_VECTOR_OUT_SIZE_ERROR:
            ret_val = NRF_ERROR_INVALID_STATE;
            break;

        case CRYS_RND_CONTEXT_PTR_INVALID_ERROR:
            ret_val = NRF_ERROR_INVALID_STATE;
            break;

        case CRYS_RND_MAX_VECTOR_IS_TOO_SMALL_ERROR:
            ret_val = NRF_ERROR_INVALID_STATE;
            break;
        #endif

        #if 0
        case ECWRST_SCALAR_MULT_INVALID_SCALAR_VALUE_ERROR:
            ret_val = NRF_ERROR_INVALID_STATE;
            break;

        case ECWRST_SCALAR_MULT_INVALID_MOD_ORDER_SIZE_ERROR:
            ret_val = NRF_ERROR_INVALID_STATE;
            break;
        #endif
        default:
            ret_val = NRF_ERROR_INTERNAL;
            break;
    }


    return ret_val;
}


static uint32_t public_key_calculate_result_get(CRYSError_t crys_error)
{
    uint32_t ret_val;

    switch(crys_error)
    {
        case CRYS_OK:
            ret_val = NRF_SUCCESS;
            break;

        default:
            ret_val = NRF_ERROR_INTERNAL;
            break;
    }

    return ret_val;
}


static uint32_t public_key_build_result_get(CRYSError_t crys_error)
{
    uint32_t ret_val;

    switch(crys_error)
    {
        case CRYS_OK:
            NRF_LOG_INFO("Key build result successful!\r\n");
            ret_val = NRF_SUCCESS;
            break;

        default:
            ret_val = NRF_ERROR_INTERNAL;
            break;
    }

    return ret_val;

}

static uint32_t public_key_export_result_get(CRYSError_t crys_error)
{
    uint32_t ret_val = NRF_SUCCESS;

    switch(crys_error)
    {
        case CRYS_OK:
            NRF_LOG_INFO("Key build result successful!\r\n");
            ret_val = NRF_SUCCESS;
            break;

        #if 0
        case CRYS_COMMON_DATA_SIZE_ILLEGAL:
            ret_val = NRF_ERROR_INTERNAL;
            break;
        #endif

        case CRYS_ECPKI_EXPORT_PUBL_KEY_INVALID_PUBL_KEY_SIZE_ERROR:
            ret_val = NRF_ERROR_INVALID_LENGTH;
            break;

        default:
            ret_val = NRF_ERROR_INTERNAL;
            break;
    }

    return ret_val;

}

uint32_t nrf_crypto_ecc_key_pair_generate(nrf_crypto_curve_info_t   curve_type,
                                          nrf_value_length_t      * p_private_key,
                                          nrf_value_length_t      * p_public_key)
{
    uint32_t                        ret_val;
    CRYSError_t                     crys_error;
    CRYS_ECPKI_Domain_t           * p_domain;

    CRYS_ECPKI_KG_TempData_t        temp_ecpki_kg_buffer;

    CRYS_ECPKI_UserPrivKey_t      * p_private_key_user;
    CRYS_ECPKI_UserPublKey_t      * p_public_key_user;

    // Check that the library has been initialized
    if (!nrf_crypto_is_initialized())
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (p_private_key == NULL || p_public_key == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    // Get the curve domain from curve_type
    if (!cc310_curve_domain_get(curve_type.curve_type, &p_domain))
    {
        NRF_LOG_INFO("Could not get curve domain!\r\n");
        return NRF_ERROR_NOT_SUPPORTED;
    }


    // Ensure the private key can hold the internal type.
    if (p_private_key->length != NRF_CRYPTO_ECC_PRIVATE_KEY_MAX_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Ensure the public key can hold the external type.
    if (p_public_key->length != NRF_CRYPTO_ECC_PUBLIC_KEY_MAX_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }


    p_private_key_user = (CRYS_ECPKI_UserPrivKey_t *)p_private_key->p_value;
    p_public_key_user = (CRYS_ECPKI_UserPublKey_t *)p_public_key->p_value;

    crys_error = CRYS_ECPKI_GenKeyPair(gp_rnd_context,
                                       p_domain,
                                       p_private_key_user,
                                       p_public_key_user,
                                       &temp_ecpki_kg_buffer,
                                       NULL );



    ret_val = key_pair_generate_result_get(crys_error);
    return ret_val;
}


uint32_t nrf_crypto_ecc_public_key_calculate(nrf_crypto_curve_info_t       curve_type,
                                             nrf_value_length_t    const * p_private_key,
                                             nrf_value_length_t          * p_public_key)
{
    uint32_t                ret_val;

    ret_val = public_key_calculate_result_get(CRYS_OK);
    return ret_val;
}


uint32_t nrf_crypto_ecc_private_key_to_raw(nrf_crypto_curve_info_t          curve_info,
                                           nrf_value_length_t       const * p_private_key,
                                           nrf_value_length_t             * p_private_key_raw)
{
    return NRF_SUCCESS;
}


uint32_t nrf_crypto_ecc_public_key_to_raw(nrf_crypto_curve_info_t       curve_type,
                                          nrf_value_length_t    const * p_public_key,
                                          nrf_value_length_t          * p_raw_key)
{
    uint32_t                        ret_val;
    CRYSError_t                     crys_error;
    CRYS_ECPKI_UserPublKey_t      * p_public_key_user;
    CRYS_ECPKI_Domain_t           * p_domain;
    uint32_t                        raw_param_size;
    uint32_t                        compact_key_size;
    uint32_t                        public_key_raw_size;
    uint8_t                         public_key_buffer[NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP521R1 + 1];

    // Check that both the public key and raw key is valid
    if (p_public_key == NULL || p_raw_key == NULL)
    {
        return NRF_ERROR_NULL;
    }

    // Get the curve domain from curve_type
    if (!cc310_curve_domain_get(curve_type.curve_type, &p_domain))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    ret_val = nrf_crypto_ecc_public_key_size_get(curve_type.curve_type, &public_key_raw_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    // Ensure the public key can hold the raw representation.
    if(public_key_raw_size != p_raw_key->length)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    compact_key_size = public_key_raw_size + 1;

    // Convert the key to the
    p_public_key_user = (CRYS_ECPKI_UserPublKey_t *)p_public_key->p_value;

    crys_error = CRYS_ECPKI_ExportPublKey(p_public_key_user,
                                          CRYS_EC_PointUncompressed,
                                          public_key_buffer,
                                          &compact_key_size);
    ret_val = public_key_export_result_get(crys_error);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    // format is [tag][x][y]
    if(compact_key_size != public_key_raw_size + 1)
    {
        return NRF_ERROR_INTERNAL;
    }

    if (public_key_buffer[0] != 0x04)
    {
        return NRF_ERROR_INTERNAL;
    }

    raw_param_size = compact_key_size / 2;

    if (curve_type.endian_type == NRF_CRYPTO_ENDIAN_LE)
    {
        // Swap X value
        swap_array_endian(public_key_buffer + 1, raw_param_size, p_raw_key->p_value);
        // Swap Y value
        swap_array_endian(public_key_buffer + raw_param_size + 1, raw_param_size, p_raw_key->p_value + raw_param_size);
    }
    else
    {
        // X and Y value is already in the correct order.
        memcpy(p_raw_key->p_value, public_key_buffer + 1, compact_key_size);
    }

    return NRF_SUCCESS;
}


uint32_t nrf_crypto_ecc_public_key_from_raw(nrf_crypto_curve_info_t   curve_type,
                                            nrf_value_length_t      * p_public_key_raw,
                                            nrf_value_length_t      * p_public_key)
{
    uint32_t                        ret_val;
    CRYSError_t                     crys_error;
    CRYS_ECPKI_UserPublKey_t      * p_public_key_user;
    CRYS_ECPKI_Domain_t           * p_domain;
    uint32_t                        raw_key_size;
    uint32_t                        raw_param_size;

    // Compact representation of public key according to IEEE1363,
    // using 1 byte to designate the format.
    // Using a largest public key for size (used key will be equal or smaller).
    uint8_t                         compact_rep[NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP521R1 + 1];

    // Check that both the public key and raw key is valid
    if (p_public_key == NULL || p_public_key_raw == NULL)
    {
        return NRF_ERROR_NULL;
    }

    if (p_public_key->p_value == NULL       ||
        p_public_key_raw->p_value == NULL   )
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    // Get the curve domain from curve_type
    if (!cc310_curve_domain_get(curve_type.curve_type, &p_domain))
    {
        NRF_LOG_INFO("Could not get curve domain\r\n");
        return NRF_ERROR_NOT_SUPPORTED;
    }

    ret_val = nrf_crypto_ecc_public_key_size_get(curve_type.curve_type, &raw_key_size);
    if (ret_val != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Could not get key size\r\n");
        return NRF_SUCCESS;
    }

    // Ensure the public key can hold the external type.
    if (p_public_key_raw->length != raw_key_size)
    {
        NRF_LOG_INFO("p_raw_key->length != raw_key_size\r\n");
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Ensure the public key can hold the internal type.
    if (p_public_key->length != sizeof(CRYS_ECPKI_UserPublKey_t))
    {
        NRF_LOG_INFO("p_public_key->length != sizeof(CRYS_ECPKI_UserPublKey_t)\r\n");
        return NRF_ERROR_INVALID_LENGTH;
    }

    raw_param_size = raw_key_size / 2;

    // Add one to hold the prefix.
    raw_key_size += 1;

    // Compact representation is big-endian by IEEE1636 spec.
    // Indicate that we have a key with X and Y (non-compressed)
    compact_rep[0] = 0x04;
    if(curve_type.endian_type == NRF_CRYPTO_ENDIAN_LE)
    {
        // Swap X value
        swap_array_endian(p_public_key_raw->p_value, raw_param_size, compact_rep + 1);
        // Swap Y value
        swap_array_endian(p_public_key_raw->p_value + raw_param_size, raw_param_size, compact_rep + raw_param_size + 1);
    }
    else
    {
        // X and Y value is already in the correct order for CryptoCell.
        memcpy(compact_rep + 1, p_public_key_raw->p_value, raw_key_size);
    }

    // Set the pointer to be the return value.
    p_public_key_user = (CRYS_ECPKI_UserPublKey_t *)p_public_key->p_value;

    NRF_LOG_INFO("Building public key!\r\n");
    crys_error = CRYS_ECPKI_BuildPublKey(p_domain,
                                         compact_rep,
                                         raw_key_size,
                                         p_public_key_user);
    NRF_LOG_INFO("Finished building public key: 0x%08x!\r\n", crys_error);

    ret_val = public_key_build_result_get(crys_error);
    return ret_val;
}


#endif // NRF_CRYPTO_BACKEND_CC310_LIB

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
