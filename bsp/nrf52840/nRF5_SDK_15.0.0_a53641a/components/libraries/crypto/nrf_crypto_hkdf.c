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
#if NRF_MODULE_ENABLED(NRF_CRYPTO)

#include "stddef.h"
#include "nrf_assert.h"
#include "nrf_crypto_hmac.h"
#include "nrf_crypto_hkdf.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_mem.h"
#include "nrf_crypto_shared.h"
#include "nrf_crypto_hmac_shared.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_HMAC)

static ret_code_t hkdf_expand(nrf_crypto_hmac_context_t      * const p_context,
                              nrf_crypto_hmac_info_t         const * p_info,
                              uint8_t                        * const p_output_key,
                              size_t                                 output_key_size,
                              uint8_t                  const * const p_ainfo,
                              size_t                                 ainfo_size,
                              uint8_t                        * const p_temp,
                              uint8_t                  const * const p_prk,
                              size_t                                 prk_size)
{
    size_t const    hash_digest_size  = p_info->digest_size;
    uint32_t const  n_iterations      = (output_key_size + hash_digest_size - 1) / hash_digest_size;
    ret_code_t      err_code          = NRF_SUCCESS;
    size_t          temp_size;
    uint8_t         n_current;
    int             write_offset;

    VERIFY_TRUE(n_iterations <= 255, NRF_ERROR_CRYPTO_OUTPUT_LENGTH);

    write_offset = 0;
    for (uint32_t i = 0; i < n_iterations; i++)
    {
        n_current = i + 1;

        err_code = nrf_crypto_hmac_init(p_context, p_info, p_prk, prk_size);
        VERIFY_SUCCESS(err_code);

        if (i != 0)
        {
            err_code = nrf_crypto_hmac_update(p_context, p_temp, hash_digest_size);
            VERIFY_SUCCESS(err_code);
        }

        if (p_ainfo != NULL)
        {
            err_code = nrf_crypto_hmac_update(p_context, p_ainfo, ainfo_size);
            VERIFY_SUCCESS(err_code);
        }

        err_code = nrf_crypto_hmac_update(p_context, &n_current, 1);
        VERIFY_SUCCESS(err_code);

        temp_size = hash_digest_size;
        err_code = nrf_crypto_hmac_finalize(p_context, p_temp, &temp_size);
        VERIFY_SUCCESS(err_code);

        memcpy(p_output_key + write_offset,
               p_temp,
               (n_current != n_iterations) ? hash_digest_size : (output_key_size - write_offset));

        write_offset += hash_digest_size;
    }

    return err_code;
}


ret_code_t nrf_crypto_hkdf_calculate(nrf_crypto_hmac_context_t      * const p_context,
                                     nrf_crypto_hmac_info_t         const * p_info,
                                     uint8_t                        * const p_output_key,
                                     size_t                         * const p_output_key_size,
                                     uint8_t                  const * const p_input_key,
                                     size_t                                 input_key_size,
                                     uint8_t                        const * p_salt,
                                     size_t                                 salt_size,
                                     uint8_t                  const * const p_ainfo,
                                     size_t                                 ainfo_size,
                                     nrf_crypto_hkdf_mode_t                 mode)
{
    uint8_t         prk[NRF_CRYPTO_HASH_SIZE_SHA512];                           // Scaled for the largest supported hash size.
    uint8_t         temp[NRF_CRYPTO_HASH_SIZE_SHA512];                          // Scaled for the largest supported hash size.
    void          * p_ctx                               = NULL;
    void          * p_allocated_context                 = NULL;
    size_t          prk_size                            = sizeof(prk);
    size_t          output_key_size                     = *p_output_key_size;
    ret_code_t      err_code;

    VERIFY_TRUE(p_info != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    VERIFY_TRUE(p_output_key != NULL, NRF_ERROR_CRYPTO_OUTPUT_NULL);
    VERIFY_TRUE(*p_output_key_size > 0, NRF_ERROR_CRYPTO_OUTPUT_LENGTH);
    VERIFY_TRUE(p_input_key != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    VERIFY_TRUE(input_key_size > 0, NRF_ERROR_CRYPTO_INPUT_LENGTH);

    if (p_salt != NULL)
    {
        VERIFY_TRUE(salt_size > 0, NRF_ERROR_CRYPTO_INPUT_LENGTH);
    }

    if (p_ainfo != NULL)
    {
        VERIFY_TRUE(ainfo_size > 0, NRF_ERROR_CRYPTO_INPUT_LENGTH);
    }

    *p_output_key_size = 0; // Set output length to 0 as default value (in case of error).

    // Allocate context internally if p_context is NULL
    if (p_context == NULL)
    {
        p_allocated_context = NRF_CRYPTO_ALLOC(p_info->context_size);
        if (p_allocated_context == NULL)
        {
            return NRF_ERROR_CRYPTO_ALLOC_FAILED;
        }
        p_ctx = p_allocated_context;
    }
    else
    {
        p_ctx = p_context;
    }

    if (mode == NRF_CRYPTO_HKDF_EXTRACT_AND_EXPAND)
    {
        if (p_salt == NULL)
        {
            // Use default salt defined in RFC 5869: String of zeros of hash length.
            salt_size = p_info->digest_size;
            ASSERT(sizeof(temp) >= salt_size);
            memset(temp, 0, salt_size);
            p_salt = temp;
        }

        // Step 1: Extract
        err_code = nrf_crypto_hmac_calculate(p_context,
                                             p_info,
                                             prk,
                                             &prk_size,
                                             p_salt,
                                             salt_size,
                                             p_input_key,
                                             input_key_size);
        NRF_CRYPTO_VERIFY_SUCCESS_DEALLOCATE(err_code, p_allocated_context);

        // Step 2: Expand
        err_code = hkdf_expand(p_ctx,
                               p_info,
                               p_output_key,
                               output_key_size,
                               p_ainfo,
                               ainfo_size,
                               temp,
                               prk,
                               prk_size);
        NRF_CRYPTO_VERIFY_SUCCESS_DEALLOCATE(err_code, p_allocated_context);
    }
    else // NRF_CRYPTO_HKDF_EXPAND_ONLY
    {
        err_code = hkdf_expand(p_ctx,
                               p_info,
                               p_output_key,
                               output_key_size,
                               p_ainfo,
                               ainfo_size,
                               temp,
                               p_input_key,
                               input_key_size);
        NRF_CRYPTO_VERIFY_SUCCESS_DEALLOCATE(err_code, p_allocated_context);
    }

    if (p_allocated_context != NULL)
    {
        NRF_CRYPTO_FREE(p_allocated_context);
    }

    *p_output_key_size = output_key_size;

    return NRF_SUCCESS;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_HMAC)
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
