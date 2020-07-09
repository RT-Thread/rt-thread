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
#ifndef NRF_CRYPTO_KEYS_H__
#define NRF_CRYPTO_KEYS_H__

/** @file
 *
 * @defgroup nrf_crypto_keys ECC key handling functions.
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides functions to allocate, free, generate and convert ECC key types.
 */

#include <stdint.h>
#include "nrf_crypto_types.h"

#include "sdk_config.h"
#if NRF_CRYPTO_BACKEND_CC310_LIB
#include "cc310_lib_keys.h"
#endif

#if NRF_CRYPTO_BACKEND_MICRO_ECC
#include "micro_ecc_lib_keys.h"
#endif


#ifdef __cplusplus
extern "C" {
#if 0
}
#endif
#endif


/**  @brief Internal macro to calculate size required to hold a ECC private key
 *          given curve type(domain), according to the used nrf_crypto backend.
 *
 *  @warning The size representation by running this macro is described by the
 *           memory requirements of the nrf_crypto backend. This size does not
 *           correspond to the size required to hold a raw key.
 * @param[in]   type  Curve type. Either SECP192R1, SECP224R1, SECP256R1, SECP384R1,
 *                    SECP521R1, SECP192K1, SECP224K1, or SECP256K1.
 */
#if defined(NRF_CRYPTO_BACKEND_CC310_LIB) && (NRF_CRYPTO_BACKEND_CC310_LIB == 1)

#define NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE(type)                       \
    (NRF_CRYPTO_ECC_PRIVATE_KEY_MAX_SIZE)

#else

#define NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE(type)                       \
    (STRING_CONCATENATE(NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_, type))

#endif // defined(NRF_CRYPTO_BACKEND_CC310_LIB)


/**  @brief Internal macro to calculate size required to hold a ECC public key
 *          given curve type(domain), according to the used nrf_crypto backend.
 *
 *  @warning The size representation by running this macro is described by the
 *           memory requirements of the nrf_crypto backend. This size does not
 *           correspond to the size required to hold a raw key.
 *
 * @param[in]   type    Curve type. Either SECP192R1, SECP224R1, SECP256R1, SECP384R1,
 *                      SECP521R1, SECP192K1, SECP224K1, or SECP256K1.
 */
#if defined(NRF_CRYPTO_BACKEND_CC310_LIB) && (NRF_CRYPTO_BACKEND_CC310_LIB == 1)

#define NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE(type)                       \
    (NRF_CRYPTO_ECC_PUBLIC_KEY_MAX_SIZE)

#else

#define NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE(type)                       \
    (STRING_CONCATENATE(NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_, type))

#endif // defined(NRF_CRYPTO_BACKEND_CC310_LIB)

/** @brief Macro to create an instance of an ECC private key
 *         given name and type.
 *
 * @note    This creates the value length structure used for Nordic APIs with a buffer
 *          to hold the actual ECC private key data. The ECC private key type is opaque and
 *          the size and format of the data is dependant on the nrf_crypto backend.
 *
 * @note    To convert this key to a raw representation required for external APIS, please
 *          use the function @ref nrf_crypto_ecc_public_key_to_raw.
 *          This may not be supported by all nrf_crypto backends.
 *
 * @param[in]   name    Name of the ECC private key instance.
 * @param[in]   type    Curve type. Either SECP192R1, SECP224R1, SECP256R1, SECP384R1,
 *                      SECP521R1, SECP192K1, SECP224K1, or SECP256K1.
 */
#define NRF_CRYPTO_ECC_PRIVATE_KEY_CREATE(name, type)                                   \
__ALIGN(4) static uint8_t                                                               \
    name ## _buffer[NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE(type)];                             \
nrf_value_length_t name =                                                               \
{                                                                                       \
    .p_value = name ## _buffer,                                                         \
    .length = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE(type)                                     \
}


/** @brief Macro to create an instance of an ECC public key by a given name and type.
 *
 * @note    This creates the value length structure used for Nordic APIs with a buffer
 *          to hold the actual ECC public key data. The ECC public key type is opaque and
 *          the size and format of the data is dependant on the nrf_crypto backend.
 *
 * @note    To convert this key to a raw representation required for external APIS, please
 *          use the function @ref nrf_crypto_ecc_public_key_to_raw.
 *          This may not be supported by all nrf_crypto backends.
 *
 * @param[in]   name    Name of the ECC PUBLIC key instance.
 * @param[in]   type    Curve type. Either SECP192R1, SECP224R1, SECP256R1, SECP384R1,
 *                      SECP521R1, SECP192K1, SECP224K1, or SECP256K1.
 */
#define NRF_CRYPTO_ECC_PUBLIC_KEY_CREATE(name, type)                                    \
__ALIGN(4) static uint8_t                                                               \
    name ## _buffer[NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE(type)];                              \
nrf_value_length_t name =                                                               \
{                                                                                       \
    .p_value = name ## _buffer,                                                         \
    .length = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE(type)                                      \
}


/**  @brief Internal macro to calculate size required to hold a ECC private key
 *          in raw format given curve type(domain), according to the used
 *          nrf_crypto backend.
 *
 *  @warning The size representation by running this macro is described by the
 *           memory requirements of the nrf_crypto backend. This size does not
 *           correspond to the size required to hold a raw key.
 * @param[in]   type    Curve type. Either SECP192R1, SECP224R1, SECP256R1, SECP384R1,
 *                      SECP521R1, SECP192K1, SECP224K1, or SECP256K1.
 */

#define NRF_CRYPTO_ECC_PRIVATE_RAW_KEY_SIZE(type)                       \
    (STRING_CONCATENATE(NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_, type))


/**  @brief Internal macro to calculate size required to hold a ECC public key
 *          in raw representatio given curve type(domain),
 *          according to the used nrf_crypto backend.
 *
 *  @warning The size representation by running this macro is described by the
 *           memory requirements of the nrf_crypto backend. This size does not
 *           correspond to the size required to hold a raw key.
 *
 * @param[in]   type    Curve type. Either SECP192R1, SECP224R1, SECP256R1, SECP384R1,
 *                      SECP521R1, SECP192K1, SECP224K1, or SECP256K1.
 */
#define NRF_CRYPTO_ECC_PUBLIC_RAW_KEY_SIZE(type)                       \
    (STRING_CONCATENATE(NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_, type))


/** @brief  Macro to create an instance of a raw representation of an ECC private key
 *          given name and type.
 *
 * @note    This creates the value length structure used for external APIs that require
 *          an aligned version of a private key where curve-domain and endianness is
 *          described elsewhere.
 *
 * @warning The raw private key can not be used directly in the nrf_crypto APIs.
 *
 * @warning The output of this macro is subject to change.
 *
 * @param[in]   name    Name of the ECC private key instance.
 * @param[in]   type    Curve type. Either SECP192R1, SECP224R1, SECP256R1, SECP384R1,
 *                      SECP521R1, SECP192K1, SECP224K1, or SECP256K1.
 */
#define NRF_CRYPTO_ECC_PRIVATE_KEY_RAW_CREATE(name, type)                               \
__ALIGN(4) static uint8_t                                                               \
    name ## _buffer[NRF_CRYPTO_ECC_PRIVATE_RAW_KEY_SIZE(type)];                         \
nrf_value_length_t name =                                                               \
{                                                                                       \
    .p_value = name ## _buffer,                                                         \
    .length = NRF_CRYPTO_ECC_PRIVATE_RAW_KEY_SIZE(type)                                 \
}


/** @brief  Macro to create a value length structure to represent a raw ECC private key
 *          by a given name, type and an uint8_t array buffer to hold the raw private key.
 *  If the input is not of the correct size a static assert will be occur compile-time.
 *
 *
 * @note    This creates the value length structure used for external APIs that require
 *          an aligned version of a private key where curve-domain and endianness is
 *          described elsewhere.
 *
 * @note    The value length pair generated by running this macro can be used as input in the
 *          function @ref nrf_crypto_ecc_private_key_to_raw to hold a raw private key type.
 *
 * @warning There is no API function to convert private key from a raw representation in the
 *          nrf_crypto CryptoCell (cc310) backend. Running this macro while nrf_crypto
 *          CryptoCell backend is enabled will cause a static assertion.
 *
 * @param[in]   name    Name of the ECC private key instance.
 * @param[in]   type    Curve type. Either SECP192R1, SECP224R1, SECP256R1, SECP384R1,
 *                      SECP521R1, SECP192K1, SECP224K1, or SECP256K1.
 * @param[in]   input   Array holding the private key.
 */
#define NRF_CRYPTO_ECC_PRIVATE_KEY_RAW_CREATE_FROM_ARRAY(name, type, input)             \
STATIC_ASSERT(sizeof(input) == NRF_CRYPTO_ECC_PRIVATE_RAW_KEY_SIZE(type))               \
static nrf_value_length_t name =                                                        \
{                                                                                       \
    .p_value = (uint8_t*)input,                                                         \
    .length = NRF_CRYPTO_ECC_PRIVATE_RAW_KEY_SIZE(type)                                 \
}

/** @brief Macro to create an instance of a araw representation of an ECC public key
 *         given name and type.
 *
 * @note    This creates the value length structure used for external APIs that require
 *          an aligned version of a public key where curve-domain and endianness is
 *          described elsewhere.
 *
¨* @note    The value length pair generated by running this macro can be used as input in the
 *          function @ref nrf_crypto_ecc_public_key_to_raw to hold a raw private key type.
 *
 * @param[in]   name    Name of the ECC PUBLIC key instance.
 * @param[in]   type    Curve type. Either SECP192R1, SECP224R1, SECP256R1, SECP384R1,
 *                      SECP521R1, SECP192K1, SECP224K1, or SECP256K1.
 */
#define NRF_CRYPTO_ECC_PUBLIC_KEY_RAW_CREATE(name, type)                                \
__ALIGN(4) static uint8_t                                                               \
    name ## _buffer[NRF_CRYPTO_ECC_PUBLIC_RAW_KEY_SIZE(type)];                          \
nrf_value_length_t name =                                                               \
{                                                                                       \
    .p_value = name ## _buffer,                                                         \
    .length = NRF_CRYPTO_ECC_PUBLIC_RAW_KEY_SIZE(type)                                  \
}


/** @brief Macro to create an instance of an ECC public key by a given
 *         name, type and array input.
 *  If the input is not of the correct size a static assert will be occur compile-time.
 *
 *
 * @note    This creates the value length structure used for external APIs that require
 *          an aligned version of a private key where curve-domain and endianness is
 *          described elsewhere.
 *
 * @note    The value length pair generated by running this macro can be used as input in the
 *          function @ref nrf_crypto_ecc_private_key_to_raw to hold a raw public key type.
 *
 * @param[in]   name    Name of the ECC PUBLIC key instance.
 * @param[in]   type    Curve type. Either SECP192R1, SECP224R1, SECP256R1, SECP384R1,
 *                      SECP521R1, SECP192K1, SECP224K1, or SECP256K1.
 * @param[in]   input   Array of data used as the buffer.
 */
#define NRF_CRYPTO_ECC_PUBLIC_KEY_RAW_CREATE_FROM_ARRAY(name, type, input)              \
STATIC_ASSERT(sizeof(input) == NRF_CRYPTO_ECC_PUBLIC_RAW_KEY_SIZE(type));               \
static nrf_value_length_t name =                                                        \
{                                                                                       \
    .p_value = (uint8_t*)input,                                                         \
    .length = NRF_CRYPTO_ECC_PUBLIC_RAW_KEY_SIZE(type)                                  \
}

/**@brief Function to get the private key size given curve_type.
 *
 * @param[in]       curve_type  Curve type to get private key size for.
 * @param[in,out]   p_key_size  Pointer to variable to hold the private key size.
 *
 * @retval  NRF_SUCCESS             If the private key size was successfully found.
 * @retval  NRF_ERROR_NULL          If the p_key_size was NULL.
 * @retval  NRF_ERROR_NOT_SUPPORTED If the curve type was not supported.
 */
uint32_t nrf_crypto_ecc_private_key_size_get(nrf_ecc_curve_type_t   curve_type,
                                             uint32_t             * p_key_size);


/**@brief Function to get the public key size given curve_type.
 *
 * @param[in]       curve_type  Curve type to get public key size for.
 * @param[in,out]   p_key_size  Pointer to variable to hold the public key size.
 *
 * @retval  NRF_SUCCESS             If the public key size was successfully found.
 * @retval  NRF_ERROR_NULL          If the p_key_size was NULL.
 * @retval  NRF_ERROR_NOT_SUPPORTED If the curve type was not supported.
 */
uint32_t nrf_crypto_ecc_public_key_size_get(nrf_ecc_curve_type_t    curve_type,
                                            uint32_t              * p_key_size);


/**@brief Function to allocate dynamic memory for holding a ECC private key.
 *
  * @note   Memory dynamically allocated by calling this function will be aligned to a
 *          uint32_t address.
 *
 * @param[in]       curve_info      Curve type used for ECC private key.
 * @param[in,out]   p_private_key   Pointer to a value length structure to hold a private key.
 * @param[in]       p_raw_key       Pointer to value length structure holding raw
 *                                  representation of a private key taken as input.
 *                                  If this is set to NULL, no initialization will take place.
 *
 * @retval  NRF_SUCCESS     If memory for the private key was successfully allocated.
 * @retval  NRF_ERROR_NULL  If p_private_key was NULL.
 * @retval  Any other error code reported by the memory manager.
 */
uint32_t nrf_crypto_ecc_private_key_allocate(nrf_crypto_curve_info_t    curve_info,
                                             nrf_value_length_t       * p_private_key,
                                             nrf_value_length_t const * p_raw_key);


/**@brief Function to free allocated memory for ECC private key.
 *
 * @note    Memory dynamically allocated by calling this function will be aligned to a
 *          uint32_t address.
 *
 * @param[in]   p_private_key   Pointer to structure holdign
 *

 * @retval  NRF_SUCCESS     if memory for the private key was successfully freed.
 * @retval  NRF_ERROR_NULL  If p_private_key was NULL.
 * @retval  Any other error code reported by the memory manager.
 */
uint32_t nrf_crypto_ecc_private_key_free(nrf_value_length_t * p_private_key);


/**@brief Function to allocate dynamic memory for holdign a ECC public key.
 *
 * @param[in]       curve_info      Curve type used for ECC public key.
 * @param[in,out]   p_public_key    Pointer to a value length structure to hold a public key.
 * @param[in]       p_raw_key       Pointer to value length structure holding raw
 *                                  representation of a public key taken as input.
 *                                  If this is set to NULL, no initialization will take place.
 *
 * @retval  NRF_SUCCESS     If memory for the public key was successfully allocated.
 * @retval  NRF_ERROR_NULL  If p_public_key was NULL.
 * @retval  Any other error code reported by the memory manager.
 */
uint32_t nrf_crypto_ecc_public_key_allocate(nrf_crypto_curve_info_t     curve_info,
                                            nrf_value_length_t       * p_public_key,
                                            nrf_value_length_t const * p_raw_key);


/**@brief Function to free allocated memory for ECC private key.
 *
 * @param[in]   p_public_key    Pointer to value length structure holding public key to free.
 *
 * @retval  NRF_SUCCESS     If memory for the public key was successfully freed.
 * @retval  NRF_ERROR_NULL  If p_public_key was NULL.
 * @retval  Any other error code reported by the memory manager.
 */
uint32_t nrf_crypto_ecc_public_key_free(nrf_value_length_t * p_public_key);


/**@brief Function to generate ECC private public keypair given curve type.
 *
 * @note    This function will not allocate any memory. Private and public keys given as
 *          input must be pointing to previously allocated memory.
 *
 * @note    This function needs RNG functionality. See @ref NRF_CRYPTO_SUPPORTS_RNG for the
 *          nrf_crypto backends that require external source of RNG data.
 *
 * @param[in]       curve_info      Curve type used for key pair generation.
 * @param[in,out]   p_private_key   Pointer to a value length structure to hold a private key.
 * @param[in,out]   p_public_key    Pointer to a value length structure to hold a public key.
 *
 * @retval  NRF_SUCCESS                 The ECC key pair was generated successfully.
 * @retval  NRF_ERROR_INVALID_STATE     If the function was called when nrf_crypto was
 *                                      uninitialized.
 * @retval  NRF_ERROR_NULL              If the any of the parameters was NULL.
 * @retval  NRF_ERROR_INVALID_ADDR      If any of the provided pointers are invalid.
 * @retval  NRF_ERROR_INVALID_LENGTH    If the key pair size is different to the provided buffers.
 * @retval  NRF_ERROR_NOT_SUPPORTED     If the key pair generation is not supported for the given curve type.
 * @retval  NRF_ERROR_INTERNAL          Unexpected error. Possibly because @ref NRF_CRYPTO_SUPPORTS_RNG is 0.
 */
uint32_t nrf_crypto_ecc_key_pair_generate(nrf_crypto_curve_info_t       curve_info,
                                          nrf_value_length_t          * p_private_key,
                                          nrf_value_length_t          * p_public_key);


/**@brief Function to calculate ECC public key given a ECC private key as input
 *
 * @note    This function will not allocate any memory. The public key given as input
 *          must be pointing to previously allocated memory.
 *
 * @param[in]       curve_info      Curve type used for public key.
 * @param[in]       p_private_key   Pointer to a value length structure holding a private key.
 * @param[in, out]  p_public_key    Pointer to a value length structure to hold the calculated
 *                                  key.
 *
 * @retval  NRF_SUCCESS                 If the public key was calculated successfully.
 * @retval  NRF_ERROR_INVALID_STATE     If the function was called when nrf_crypto was
 *                                      uninitialized.
 * @retval  NRF_ERROR_NULL              If the any of the parameters was NULL.
 * @retval  NRF_ERROR_INVALID_ADDR      If any of the provided pointers are invalid.
 * @retval  NRF_ERROR_INVALID_LENGTH    If the key pair size is different to the provided buffers.
 * @retval  NRF_ERROR_NOT_SUPPORTED     If the public key calculation is not supported.
 */
uint32_t nrf_crypto_ecc_public_key_calculate(nrf_crypto_curve_info_t       curve_info,
                                             nrf_value_length_t    const * p_private_key,
                                             nrf_value_length_t          * p_public_key);


/**@brief Function to convert ECC private key to a raw representation for use in external APIs.
 *
 * @note This function will not allocate any memory. The raw public key given as output parameter
 *       must be pointing to previously allocated memory.
 *
 * @note    The format of the data for the converted ECC public key must be aligned and will
 *       use the least amount of space required to represent the key.
 *
 * @warning The nrf_crypto backend may not support converting a private key to a raw representation.
 *          This is subject to change.
 *
 * @param[in]       curve_info          Info of the curve type (domain) and the endianness of the
 *                                      resulting raw key.
 * @param[in]       p_private_key       Value length structure holding a private key to be
 *                                      converted to a raw representation.
 * @param[in,out]   p_private_key_raw   Value length structure to hold the converted private key.
 *
 * @retval  NRF_SUCCESS                 If the private key was converted to raw representation.
 * @retval  NRF_ERROR_INVALID_STATE     If the function was called when nrf_crypto was
 *                                      uninitialized.
 * @retval  NRF_ERROR_NULL              If the any of the parameters was NULL.
 * @retval  NRF_ERROR_INVALID_ADDR      If any of the provided pointers are invalid.
 * @retval  NRF_ERROR_INVALID_LENGTH    If the size of the public key and result is invalid.
 * @retval  NRF_ERROR_NOT_SUPPORTED     If the selected curve is not supported.
 * @retval  NRF_ERROR_INVALID_DATA      If the private key was deemed invalid by the nrf_crypto
 *                                      backend.
 * @retval  NRF_ERROR_INTERNAL          If an internal error occured in the nrf_crypto backend.
 */
uint32_t nrf_crypto_ecc_private_key_to_raw(nrf_crypto_curve_info_t          curve_info,
                                           nrf_value_length_t       const * p_private_key,
                                           nrf_value_length_t             * p_private_key_raw);


/**@brief Function to convert ECC public key to a raw representation for use in external APIs.
 *
 * @note This function will not allocate any memory. The raw public key given as output parameter
 *       must be pointing to previously allocated memory.
 *       The format of the data for the converted ECC public key must be aligned and will
 *       use the least amount of space required to represent the key.
 *
 * @param[in]       curve_info          Info of the curve type (domain) and the endianness of
 *                                      the resulting raw key.
 * @param[in]       p_public_key       Value length structure holding a public key to be
 *                                      converted to a raw representation.
 * @param[in,out]   p_public_key_raw   Value length structure to hold the converted public key.
 *
 * @retval  NRF_SUCCESS                 If the public key was converted to raw representation.
 * @retval  NRF_ERROR_INVALID_STATE     If the function was called when nrf_crypto was
 *                                      uninitialized.
 * @retval  NRF_ERROR_NULL              If the any of the parameters was NULL.
 * @retval  NRF_ERROR_INVALID_ADDR      If any of the provided pointers are invalid.
 * @retval  NRF_ERROR_INVALID_LENGTH    If the size of the public key and result is invalid.
 * @retval  NRF_ERROR_NOT_SUPPORTED     If the selected curve is not supported.
 * @retval  NRF_ERROR_INVALID_DATA      If the public key was deemed invalid by the nrf_crypto
 *                                      backend.
 * @retval  NRF_ERROR_INTERNAL          If an internal error occured in the nrf_crypto backend.
 */
uint32_t nrf_crypto_ecc_public_key_to_raw(nrf_crypto_curve_info_t           curve_info,
                                          nrf_value_length_t        const * p_public_key,
                                          nrf_value_length_t              * p_public_key_raw);


/**@brief Function to convert ECC public key from a raw representation for use in nrf_crypto API.
 *
 * @note This function will not allocate any memory. The public key given as output parameter
 *       must be pointing to previously allocated memory.
 *       The format of the data for the converted ECC public key must be aligned and will
 *       use the least amount of space required to represent the key.
 *
 * @param[in]       curve_info          Info of the curve type (domain) and the endianness of the
 *                                      raw public key given as input.
 * @param[in]       p_public_key_raw    Value length structure to hold the converted public key.
 * @param[in,out]   p_public_key        Value length structure holding a private key to be converted to a raw representation.
 *
 * @retval  NRF_SUCCESS                 If the public key was converted fron raw representation.
 * @retval  NRF_ERROR_INVALID_STATE     If the function was called when nrf_crypto was
 *                                      uninitialized.
 * @retval  NRF_ERROR_NULL              If the any of the parameters was NULL.
 * @retval  NRF_ERROR_INVALID_ADDR      If any of the provided pointers are invalid.
 * @retval  NRF_ERROR_NOT_SUPPORTED     If the selected curve is not supported.
 * @retval  NRF_ERROR_INVALID_LENGTH    If the size of the public key and result is invalid.
 * @retval  NRF_ERROR_INVALID_DATA      If the public key was deemed invalid by the nrf_crypto
 *                                      backend.
 * @retval  NRF_ERROR_INTERNAL          If an internal error occured in the nrf_crypto backend.
 */
uint32_t nrf_crypto_ecc_public_key_from_raw(nrf_crypto_curve_info_t   curve_info,
                                            nrf_value_length_t      * p_public_key_raw,
                                            nrf_value_length_t      * p_public_key);
#ifdef __cplusplus
}
#endif

 /**@} */

#endif // NRF_CRYPTO_KEYS_H__
