/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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

#include "nordic_common.h"
#include "nrf_crypto_error.h"

typedef struct
{
    ret_code_t   error;
    const char * p_text;
} error_code_pair;

static const error_code_pair m_crypto_error[] =
{
    { NRF_ERROR_CRYPTO_NOT_INITIALIZED,         "nrf_crypto_init was not called prior to this crypto function" },
    { NRF_ERROR_CRYPTO_CONTEXT_NULL,            "A null pointer was provided for the context structure" },
    { NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED, "The context was not initialized prior to this call or it was corrupted. Please call the corresponding init function for the algorithm to initialize it" },
    { NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE,     "The function was called with a feature that is unavailable" },
    { NRF_ERROR_CRYPTO_BUSY,                    "The function could not be called because the crypto backend was busy. Please rerun the cryptographic routine at a later time" },
    { NRF_ERROR_CRYPTO_INPUT_NULL,              "One or more of the input arguments for this function was NULL" },
    { NRF_ERROR_CRYPTO_INPUT_LENGTH,            "The length of one or more of the input arguments was invalid" },
    { NRF_ERROR_CRYPTO_INPUT_LOCATION,          "Input data not in RAM" },
    { NRF_ERROR_CRYPTO_OUTPUT_NULL,             "One or more of the output arguments for this function was NULL" },
    { NRF_ERROR_CRYPTO_OUTPUT_LENGTH,           "The length of the one or more output arguments was too small" },
    { NRF_ERROR_CRYPTO_ALLOC_FAILED,            "A required memory allocation failed" },
    { NRF_ERROR_CRYPTO_INTERNAL,                "An internal error occurred when calling this function" },
    { NRF_ERROR_CRYPTO_INVALID_PARAM,           "Invalid combination of input parameters" },
    { NRF_ERROR_CRYPTO_KEY_SIZE,                "Size of the key is not supported by choosen backend" },
    { NRF_ERROR_CRYPTO_STACK_OVERFLOW,          "Stack overflow detected" },
    { NRF_ERROR_CRYPTO_ECC_KEY_NOT_INITIALIZED, "ECC key was not initialized" },
    { NRF_ERROR_CRYPTO_ECDH_CURVE_MISMATCH,     "Public and private key provided to ECDH have different types of curves" },
    { NRF_ERROR_CRYPTO_ECDSA_INVALID_SIGNATURE, "Signature verification check reported invalid signature" },
    { NRF_ERROR_CRYPTO_ECC_INVALID_KEY,         "Provided key is invalid" },
    { NRF_ERROR_CRYPTO_AES_INVALID_PADDING,     "Message padding is corrupted." },
    { NRF_ERROR_CRYPTO_AEAD_INVALID_MAC,        "MAC not matching encrypted text" },
    { NRF_ERROR_CRYPTO_AEAD_NONCE_SIZE,         "Size of the nonce is not supported in this AEAD mode" },
    { NRF_ERROR_CRYPTO_AEAD_MAC_SIZE,           "Size of the MAC (tag) is not supported in this AEAD mode" },
    { NRF_ERROR_CRYPTO_RNG_INIT_FAILED,         "Initialization or startup of RNG failed" },
    { NRF_ERROR_CRYPTO_RNG_RESEED_REQUIRED,     "Reseed required (reseed counter overflowed)" },
};

char const * nrf_crypto_error_string_get(ret_code_t error)
{
    if (error == NRF_SUCCESS)
    {
        return "No error";
    }
    else
    {
        uint32_t i;
        for (i = 0; i < ARRAY_SIZE(m_crypto_error); i++)
        {
            if (m_crypto_error[i].error == error)
            {
                return m_crypto_error[i].p_text;
            }
        }
    }
    return "Error not related to nrf_crypto library";
}

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
