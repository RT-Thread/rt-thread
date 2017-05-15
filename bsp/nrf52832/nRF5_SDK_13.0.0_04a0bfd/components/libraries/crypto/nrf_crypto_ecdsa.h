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
#ifndef NRF_CRYPTO_ECDSA_H__
#define NRF_CRYPTO_ECDSA_H__

/** @file
 *
 * @defgroup nrf_crypto_ecdsa ECDSA related functions
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides ECDSA related functionality through nrf_crypto.
 */

#include <stdint.h>
#include "nrf_crypto_types.h"

#ifdef __cplusplus
extern "C" {
#if 0
}
#endif
#endif


/** @brief Macro to create an instance of a ECDSA sign context by a given name.
 *
 * @note    This creates the value length structure used for nrf_crypto APIs and a
 *          buffer to hold the sign context without using dynamically allocated memory.
 */
#define NRF_CRYPTO_ECDSA_SIGN_CONTEXT_INSTANCE_CREATE(name)             \
static uint8_t name ## _buffer[NRF_CRYPTO_ECDSASIGN_CONTEXT_SIZE];      \
static nrf_value_length_t  name =                                       \
{                                                                       \
    .p_value = name ## _buffer,                                         \
    .length = NRF_CRYPTO_SIGN_CONTEXT_SIZE                              \
}


/** @brief Macro to create an instance of a ECDSA verify context by a given name.
 *
 * @note    This creates the value length structure used for nrf_crypto APIs and a
 *          buffer to hold the verify context without using dynamically allocated memory.
 */
#define NRF_CRYPTO_VERIFY_CONTEXT_INSTANCE_CREATE(name)                 \
static uint8_t name ## _buffer[NRF_CRYPTO_ECDSA_VERIFY_CONTEXT_SIZE];   \
static nrf_value_length_t  name =                                       \
{                                                                       \
    .p_value = name ## _buffer,                                         \
    .length = NRF_CRYPTO_ECDSA_VERIFY_CONTEXT_SIZE                      \
}


/** @brief Macro to create an instance of an ECDSA signature by a given name and type.
 *
 * @param[in]   name    Name of the ECDSA signature instance.
 * @param[in]   type    Either SECP160R1, SECP192R1, SECP224R1, SECP256R1, SECP384R1,
 *                      SECP521R1, SECP192K1, SECP224K1, or SECP256K1
 *
 * @note    This creates the value length structure used for nrf_crypto APIs and a
 *          buffer to hold the signature without using dynamically allocated memory.
 */
#define NRF_CRYPTO_ECDSA_SIGNATURE_CREATE(name, type)                                           \
static uint8_t  name ## _buffer[STRING_CONCATENATE(NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_, type)];    \
static nrf_value_length_t name =                                                                \
{                                                                                               \
    .p_value = name ## _buffer,                                                                 \
    .length = STRING_CONCATENATE(NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_, type)                        \
}


/** @brief Macro to create an instance of an ECDSA signature by a given name, type and input.
 *
 *  If the input is not of the correct size a static assert will be occur compile-time.
 *
 * @note    This creates the value length structure used for nrf_crypto APIs and a
 *          buffer to hold the signature without using dynamically allocated memory.
 *
 * @param[in]   name    Name of the ECDSA signature instance.
 * @param[in]   type    Either SECP160R1, SECP192R1, SECP224R1, SECP256R1, SECP384R1,
 *                      SECP521R1, SECP192K1, SECP224K1, or SECP256K1
 * @param[in]   input   Input must be an array of correct size according to the curve type.
 *
 */
#define NRF_CRYPTO_ECDSA_SIGNATURE_INSTANCE_CREATE_FROM_INPUT(name, type, input)                \
STATIC_ASSERT(sizeof(input) == STRING_CONCATENATE(NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_, type));     \
static nrf_value_length_t name =                                                                \
{                                                                                               \
    .p_value = name ## _buffer,                                                                 \
    .length = STRING_CONCATENATE(NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_, type)                        \
}


/**@brief   Function to get the size of a ECDSA signature given curve type.
 *
 * @param[in]   curve_type  Elliptic curve to use.
 * @param[in]   p_sig_size  Pointer to variable to hold size of a signature.
 *
 * @retval  NRF_SUCCESS             If the he signature size was calculated.
 * @retval  NRF_ERROR_NULL          If p_sizes was NULL.
 * @retval  NRF_ERROR_NOT_SUPPORTED Selected curve was not supported.
 */
uint32_t nrf_crypto_ecdsa_signature_size_get(nrf_ecc_curve_type_t curve_type, uint32_t * p_sig_size);


/**@brief   Function to get the sizes used for ECDSA sign/verify given curve_type
 *
 * @details This function will report back the private/public key, signature and hash sizes.
 *
 * @param[in]   sig_info    Elliptic curve and hash to use.
 * @param[in]   p_sizes     Pointer to variable to hold the key, hash and signature sizes.
 *
 * @retval  NRF_SUCCESS             If the ECDSA sizes was calculated.
 * @retval  NRF_ERROR_NULL          If p_sizes was NULL.
 * @retval  NRF_ERROR_NOT_SUPPORTED Selected curve or hash was not supported.
 */
uint32_t nrf_crypto_ecdsa_sizes_get(nrf_crypto_signature_info_t     sig_info,
                                    nrf_crypto_ecdsa_sizes_t      * p_sizes);


/**@brief   Function to allocate dynamic memory for holding a signature
 *
 * @note    The signature must be allocated before calling this
 *          function.
 *
 * @note    If p_raw_signature is not NULL, then the content will be copied to the
 *          allocated buffer.
 *
 * @param[in]       sig_info        Curve and hash function used for representing a signature
 * @param[in,out]   p_signature     Pointer to value-length structure to hold the signature.
 * @param[in]       p_raw_signature Pointer to byte representation of raw key given curve type.
 *
 * @retval  NRF_SUCCESS     Memory for the signature was successfully allocated.
 * @retval  NRF_ERROR_NULL  Signature parameter was NULL.
 * @retval  Any other error code reported by the memory manager.
 */
uint32_t nrf_crypto_ecdsa_signature_allocate(nrf_crypto_signature_info_t    sig_info,
                                             nrf_value_length_t           * p_signature,
                                             nrf_value_length_t     const * p_raw_signature);


/**@brief Function to free dynamic memory allocated for holding a signature
 *
 * @param[in,out]   p_signature     Pointer to value-length structure that holds the
 *                                  allocated space to be freed.
 *
 * @retval  NRF_SUCCESS     Memory for the signature was successfully allocated.
 * @retval  NRF_ERROR_NULL  Signature parameter was NULL.
 * @retval  Any other error code reported by the memory manager.
 */
uint32_t nrf_crypto_ecdsa_signature_free(nrf_value_length_t * p_signature);


/**@brief Function for signing a hash using a private key.
 *
 * @note    Key sizes and signature must be allocated before calling this
 *          function.
 *
 * @param[in]       sig_info        Elliptic curve to use for signing and endianness
 *                                  of the resulting signature.
 * @param[in]       p_private_key   Pointer to structure holding private key.
 * @param[in]       p_hash          Pointer to structure holding hash to use for signing.
 * @param[in,out]   p_signature     Pointer to structure holding signature.
 *
 * @retval  NRF_SUCCESS                 If the signature was created successfully.
 * @retval  NRF_ERROR_INVALID_STATE     If the function was called when nrf_crypto was
 *                                      uninitialized.
 * @retval  NRF_ERROR_NULL              If the provided key, hash or signature parameters was NULL.
 * @retval  NRF_ERROR_NOT_SUPPORTED     If the selected curve or hash type is not supported.
 * @retval  NRF_ERROR_INVALID_ADDR      If the key, hash or signature paramenters aren't aligned.
 * @retval  NRF_ERROR_INVALID_LENGTH    If the allocated length of the provided private key or hash
 *                                      is invalid or the signature is bigger than the size of the
 *                                      provided buffer.
 * @retval  NRF_ERROR_INVALID_DATA      If any of the keys or result data is deemed invalid by the
 *                                      nrf_crypto backend.
 * @retval  NRF_ERROR_INTERNAL          If an internal error occured in the nrf_crypto backend.
 */
uint32_t nrf_crypto_ecdsa_sign_hash(nrf_crypto_signature_info_t  sig_info,
                                    nrf_value_length_t   const * p_private_key,
                                    nrf_value_length_t   const * p_hash,
                                    nrf_value_length_t         * p_signature);


/**@brief Function for verifying a hash using a public key.
 *
 * @note    Key sizes and signature must be allocated before calling this
 *          function.
 *
 * @param[in]       sig_info        Elliptic curve to use for verification and endianness
 *                                  of the signature given as input.
 * @param[in]       p_public_key    Pointer to structure holding public key.
 * @param[in]       p_hash          Pointer to structure holding hash to use for verification.
 * @param[in,out]   p_signature     Pointer to structure holding signature.
 *
 * @retval  NRF_SUCCESS                 If the signature was verified and is valid.
 * @retval  NRF_ERROR_INVALID_DATA      If the signature did not match the provided hash.
 * @retval  NRF_ERROR_INVALID_ADDR      If the key, hash or signature data aren't aligned.
 * @retval  NRF_ERROR_INVALID_STATE     If the function was called when nrf_crypto was uninitialized.
 * @retval  NRF_ERROR_NULL              If the provided key, hash or signature parameters was NULL.
 * @retval  NRF_ERROR_INVALID_LENGTH    If the length of the provided public key, hash, or signature
 *                                      is invalid.
 * @retval  NRF_ERROR_NOT_SUPPORTED     If the selected curve or hash type is not supported.
 * @retval  NRF_ERROR_INVALID_ADDR      If any of the provided pointers is invalid.
 * @retval  NRF_ERROR_INTERNAL          If an internal error occured in the nrf_crypto backend.
 */
uint32_t nrf_crypto_ecdsa_verify_hash(nrf_crypto_signature_info_t  sig_info,
                                      nrf_value_length_t   const * p_public_key,
                                      nrf_value_length_t   const * p_hash,
                                      nrf_value_length_t   const * p_signature);

#ifdef __cplusplus
}
#endif

/**@} */

#endif // #ifndef NRF_CRYPTO_ECDSA_H__
