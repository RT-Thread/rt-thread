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

#include "nrf_crypto_error.h"
#include "nrf_crypto_ecc.h"
#include "nrf_crypto_eddsa.h"
#include "nrf_crypto_mem.h"
#include "app_util.h"
#include "sdk_macros.h"


#if NRF_CRYPTO_ECC_ENABLED && NRF_CRYPTO_ECC_ED25519_ENABLED



ret_code_t nrf_crypto_eddsa_sign(nrf_crypto_eddsa_sign_context_t          * p_context,
                                 nrf_crypto_ecc_private_key_t       const * p_private_key,
                                 uint8_t                            const * p_message,
                                 size_t                                     message_size,
                                 uint8_t                                  * p_signature,
                                 size_t                                   * p_signature_size)
{
    ret_code_t                          result = NRF_SUCCESS;
    void                              * p_allocated_context = NULL;

    // Get pointer to header
    nrf_crypto_internal_ecc_key_header_t const * p_private_key_header =
        (nrf_crypto_internal_ecc_key_header_t const *)p_private_key;

    // Verify parameters (zero-length message is valid per RFC 8032)
    if (message_size > 0)
    {
        VERIFY_TRUE(p_message != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    }

    result = nrf_crypto_internal_ecc_key_input_check(
        p_private_key_header,
        NRF_CRYPTO_INTERNAL_ECC_PRIVATE_KEY_INIT_VALUE);
    VERIFY_SUCCESS(result);

    result = nrf_crypto_internal_ecc_raw_output_prepare(p_signature,
                                                        p_signature_size,
                                                        NRF_CRYPTO_EDDSA_ED25519_SIGNATURE_SIZE);
    VERIFY_SUCCESS(result);

    // Allocate context if not provided
    if (p_context == NULL && NRF_CRYPTO_BACKEND_ED25519_SIGN_CONTEXT_SIZE > 0)
    {
        p_allocated_context = NRF_CRYPTO_ALLOC(NRF_CRYPTO_BACKEND_ED25519_SIGN_CONTEXT_SIZE);
        VERIFY_TRUE(p_allocated_context != NULL, NRF_ERROR_CRYPTO_ALLOC_FAILED);
        p_context = p_allocated_context;
    }

    // Execute backend implementation
    result = nrf_crypto_backend_ed25519_sign(p_context,
                                             p_private_key,
                                             p_message,
                                             message_size,
                                             p_signature);

    // Deallocate context if allocated
    if (p_allocated_context != NULL)
    {
        NRF_CRYPTO_FREE(p_allocated_context);
    }

    return result;
}


ret_code_t nrf_crypto_eddsa_verify(nrf_crypto_eddsa_verify_context_t          * p_context,
                                   nrf_crypto_ecc_public_key_t          const * p_public_key,
                                   uint8_t                              const * p_message,
                                   size_t                                       message_size,
                                   uint8_t                              const * p_signature,
                                   size_t                                       signature_size)
{
    ret_code_t                          result = NRF_SUCCESS;
    void                              * p_allocated_context = NULL;

    // Get pointer to header
    nrf_crypto_internal_ecc_key_header_t const * p_public_key_header =
        (nrf_crypto_internal_ecc_key_header_t const *)p_public_key;

    // Verify parameters (zero-length message is valid per RFC 8032)
    if (message_size > 0)
    {
        VERIFY_TRUE(p_message != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    }

    result = nrf_crypto_internal_ecc_key_input_check(
        p_public_key_header,
        NRF_CRYPTO_INTERNAL_ECC_PUBLIC_KEY_INIT_VALUE);
    VERIFY_SUCCESS(result);

    result = nrf_crypto_internal_ecc_raw_input_check(p_signature,
                                                     signature_size,
                                                     NRF_CRYPTO_EDDSA_ED25519_SIGNATURE_SIZE);
    VERIFY_SUCCESS(result);

    // Allocate context if not provided
    if (p_context == NULL && NRF_CRYPTO_BACKEND_ED25519_VERIFY_CONTEXT_SIZE > 0)
    {
        p_allocated_context = NRF_CRYPTO_ALLOC(NRF_CRYPTO_BACKEND_ED25519_VERIFY_CONTEXT_SIZE);
        VERIFY_TRUE(p_allocated_context != NULL, NRF_ERROR_CRYPTO_ALLOC_FAILED);
        p_context = p_allocated_context;
    }

    // Execute backend implementation
    result = nrf_crypto_backend_ed25519_verify(p_context,
                                               p_public_key,
                                               p_message,
                                               message_size,
                                               p_signature);

    // Deallocate context if allocated
    if (p_allocated_context != NULL)
    {
        NRF_CRYPTO_FREE(p_allocated_context);
    }

    return result;
}

#endif // NRF_CRYPTO_ECC_ENABLED && NRF_CRYPTO_ECC_ED25519_ENABLED
