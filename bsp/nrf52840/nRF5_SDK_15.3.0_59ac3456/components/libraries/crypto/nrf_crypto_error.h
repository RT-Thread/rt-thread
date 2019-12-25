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

#ifndef NRF_CRYPTO_ERROR_H__
#define NRF_CRYPTO_ERROR_H__

/**@file
 *
 * @defgroup nrf_crypto_error nrf_crypto error codes
 * @{
 * @ingroup nrf_crypto
 *
 * @details This is the standardized error codes provided when calling nrf_crypto APIs.
 *          The error codes provided here are enumerated based on @ref NRF_ERROR_CRYPTO_ERR_BASE.
 *
 * @note Success code, NRF_SUCCESS, is used if the nrf_crypto operation was successful.
 *
 */

#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NRF_ERROR_CRYPTO_NOT_INITIALIZED            (NRF_ERROR_CRYPTO_ERR_BASE + 0x00)      /**< @ref nrf_crypto_init was not called prior to this crypto function. */
#define NRF_ERROR_CRYPTO_CONTEXT_NULL               (NRF_ERROR_CRYPTO_ERR_BASE + 0x01)      /**< A null pointer was provided for the context structure. */
#define NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED    (NRF_ERROR_CRYPTO_ERR_BASE + 0x02)      /**< The context was not initialized prior to this call or it was corrupted. Call the corresponding init function for the algorithm to initialize it. */
#define NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE        (NRF_ERROR_CRYPTO_ERR_BASE + 0x03)      /**< The function was called with a feature that is unavailable. */
#define NRF_ERROR_CRYPTO_BUSY                       (NRF_ERROR_CRYPTO_ERR_BASE + 0x04)      /**< The function could not be called because the crypto backend was busy. Rerun the cryptographic routine at a later time. */

#define NRF_ERROR_CRYPTO_INPUT_NULL                 (NRF_ERROR_CRYPTO_ERR_BASE + 0x10)      /**< One or more of the input arguments for this function were NULL. */
#define NRF_ERROR_CRYPTO_INPUT_LENGTH               (NRF_ERROR_CRYPTO_ERR_BASE + 0x11)      /**< The length of one or more of the input arguments was invalid. */
#define NRF_ERROR_CRYPTO_INPUT_LOCATION             (NRF_ERROR_CRYPTO_ERR_BASE + 0x12)      /**< Input data not in RAM. */
#define NRF_ERROR_CRYPTO_OUTPUT_NULL                (NRF_ERROR_CRYPTO_ERR_BASE + 0x13)      /**< One or more of the output arguments for this function were NULL. */
#define NRF_ERROR_CRYPTO_OUTPUT_LENGTH              (NRF_ERROR_CRYPTO_ERR_BASE + 0x14)      /**< The length of one or more output arguments was too small. */
#define NRF_ERROR_CRYPTO_ALLOC_FAILED               (NRF_ERROR_CRYPTO_ERR_BASE + 0x15)      /**< A required memory allocation failed. */
#define NRF_ERROR_CRYPTO_INTERNAL                   (NRF_ERROR_CRYPTO_ERR_BASE + 0x16)      /**< An internal error occurred when calling this function. */
#define NRF_ERROR_CRYPTO_INVALID_PARAM              (NRF_ERROR_CRYPTO_ERR_BASE + 0x17)      /**< Invalid combination of input parameters. */
#define NRF_ERROR_CRYPTO_KEY_SIZE                   (NRF_ERROR_CRYPTO_ERR_BASE + 0x18)      /**< Size of the key is not supported by choosen backend. */
#define NRF_ERROR_CRYPTO_STACK_OVERFLOW             (NRF_ERROR_CRYPTO_ERR_BASE + 0x19)      /**< Stack overflow detected. */

#define NRF_ERROR_CRYPTO_ECC_ERR_BASE               (NRF_ERROR_CRYPTO_ERR_BASE + 0x40)      /**< Base error code for ECC. */
#define NRF_ERROR_CRYPTO_ECC_KEY_NOT_INITIALIZED    (NRF_ERROR_CRYPTO_ECC_ERR_BASE + 0x00)  /**< The key was not initialized. */
#define NRF_ERROR_CRYPTO_ECDH_CURVE_MISMATCH        (NRF_ERROR_CRYPTO_ECC_ERR_BASE + 0x01)  /**< Public and private key provided to ECDH have different types of curves. */
#define NRF_ERROR_CRYPTO_ECDSA_INVALID_SIGNATURE    (NRF_ERROR_CRYPTO_ECC_ERR_BASE + 0x02)  /**< Signature verification check reported invalid signature. */
#define NRF_ERROR_CRYPTO_ECC_INVALID_KEY            (NRF_ERROR_CRYPTO_ECC_ERR_BASE + 0x03)  /**< Provided key is invalid. */

#define NRF_ERROR_CRYPTO_AES_ERR_BASE               (NRF_ERROR_CRYPTO_ERR_BASE + 0x50)      /**< Base error code for all AES modes. */
#define NRF_ERROR_CRYPTO_AES_INVALID_PADDING        (NRF_ERROR_CRYPTO_AES_ERR_BASE + 0x00)  /**< Message padding is corrupted. */

#define NRF_ERROR_CRYPTO_AEAD_ERR_BASE              (NRF_ERROR_CRYPTO_ERR_BASE + 0x60)      /**< Base error code for all AEAD modes. */
#define NRF_ERROR_CRYPTO_AEAD_INVALID_MAC           (NRF_ERROR_CRYPTO_AEAD_ERR_BASE + 0x00) /**< MAC not matching encrypted text. */
#define NRF_ERROR_CRYPTO_AEAD_NONCE_SIZE            (NRF_ERROR_CRYPTO_AEAD_ERR_BASE + 0x01) /**< Size of the nonce is not supported in this AEAD mode. */
#define NRF_ERROR_CRYPTO_AEAD_MAC_SIZE              (NRF_ERROR_CRYPTO_AEAD_ERR_BASE + 0x02) /**< Size of the MAC (tag) is not supported in this AEAD mode. */

#define NRF_ERROR_CRYPTO_RNG_ERR_BASE               (NRF_ERROR_CRYPTO_ERR_BASE + 0x70)      /**< Base error code for all RNG modes. */
#define NRF_ERROR_CRYPTO_RNG_INIT_FAILED            (NRF_ERROR_CRYPTO_RNG_ERR_BASE + 0x00)  /**< Initialization or startup of RNG failed. */
#define NRF_ERROR_CRYPTO_RNG_RESEED_REQUIRED        (NRF_ERROR_CRYPTO_RNG_ERR_BASE + 0x01)  /**< Reseed required (reseed counter overflowed). */

/**
 * @brief Function for converting an nrf_crypto error to a printable string pointer.
 *
 * @param[in] error     Error code.
 *
 * @return              Pointer to string explaining nrf_crypto error.
 * */
char const * nrf_crypto_error_string_get(ret_code_t error);

#ifdef __cplusplus
}
#endif

/** @} */

#endif // NRF_CRYPTO_ERROR_H__
