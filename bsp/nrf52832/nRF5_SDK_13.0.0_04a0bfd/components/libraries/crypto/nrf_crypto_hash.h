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
#ifndef NRF_CRYPTO_HASH_H__
#define NRF_CRYPTO_HASH_H__

/** @file
 *
 * @defgroup nrf_crypto_hash Cryptographic hash related functions.
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides cryptographic hash related functionality through nrf_crypto.
 */

#include <stdint.h>
#include "nrf_crypto_types.h"
#include "app_util.h"

#ifdef __cplusplus
extern "C" {
#if 0
}
#endif
#endif


/** @brief Internal macro to get the size of a given hash type
 *
 * @param[in]   type    Either MD5, SHA0, SHA1, SHA224, SHA256, SHA384 or SHA512
 */
#define NRF_CRYPTO_HASH_SIZE(type)                                  \
    STRING_CONCATENATE(NRF_CRYPTO_HASH_SIZE_, type)


/** @brief Macro to create an instance of a hash context by a given name and type.
 *
 *  @note This creates the value length structure and
 *        a backing buffer without using dynamically allocated memory.
 */
#define NRF_CRYPTO_HASH_CONTEXT_CREATE(name, type)                              \
__ALIGN(4) static uint8_t name ## _buffer[NRF_CRYPTO_HASH_CONTEXT_MAX_SIZE];    \
static nrf_value_length_t  name =                                               \
{                                                                               \
    .p_value = name ## _buffer,                                                 \
    .length = NRF_CRYPTO_HASH_CONTEXT_MAX_SIZE                                  \
}


/** @brief Macro to create an instance of a hash by a given name and type.
 *
 * @param[in]   name    Name of the hash instance.
 * @param[in]   type    Either MD5, SHA0, SHA1, SHA224, SHA256, SHA384 or SHA512.
 *
 * @note    This creates the value length structure and a backing
 *          buffer without using dynamically allocated memory.
 */
#define NRF_CRYPTO_HASH_CREATE(name, type)                                      \
__ALIGN(4) static uint8_t name ## _buffer[NRF_CRYPTO_HASH_SIZE(type)];          \
static nrf_value_length_t name =                                                \
{                                                                               \
    .p_value = name ## _buffer,                                                 \
    .length = NRF_CRYPTO_HASH_SIZE(type)                                        \
}


/** @brief Macro to create an instance of a hash by a given name and type and
 *         input buffer.
 *
 *  If the input is not of the correct size a static assert will be occur compile-time.
 *
 * @param[in]   name    Name of the hash instance.
 * @param[in]   type    Either MD5, SHA0, SHA1, SHA224, SHA256, SHA384 or SHA512.
 * @param[in]   input   Array used as input buffer.
 *
 * @note    This creates the value length structure and a backing
 *          buffer without using dynamically allocated memory.
 */
#define NRF_CRYPTO_HASH_CREATE_FROM_ARRAY(name, type, input)            \
STATIC_ASSERT(sizeof(input) == NRF_CRYPTO_HASH_SIZE(type))              \
static nrf_value_length_t name =                                        \
{                                                                       \
    .p_value = (uint8_t*) input,                                        \
    .length = NRF_CRYPTO_HASH_SIZE(type)                                \
}


/**@brief   Function to get the size of a given hash type
 *
 * @param[in]       hash_type       Type of hash.
 * @param[in,out]   p_hash_size     Pointer to variable to hold the hash size. Must not be NULL.
 *
 * @retval NRF_SUCCESS              Hash function found.
 * @retval NRF_ERROR_NULL           p_hash_size was NULL.
 * @retval NRF_ERROR_NOT_SUPPORTED  Requested hash type isn't supported.
 */
uint32_t nrf_crypto_hash_size_get(nrf_hash_type_t hash_type, uint32_t * p_hash_size);


/**@brief   Function to dynamically allocate memory to hold a hash context used
 *          when calculating hash as a non-integrated step.
 *
 * @param[in]       hash_info       Hashing algorithm to create context for
 * @param[in,out]   p_hash_context  Pointer to value-length structure to hold allocated space.
 *
 * @retval          NRF_SUCCESS     Space was successfully allocated.
 */
uint32_t nrf_crypto_hash_context_allocate(nrf_crypto_hash_info_t    hash_info,
                                          nrf_value_length_t      * p_hash_context);


/**@brief   Function to free dynamically allocated memory for hash context
 *          used when calculating hash as a non-integrated step.
 *
 * @note    The length value of the value length structure will be set to
 *          zero when the memory is freed. There is no impact of running this
 *          function on already deallocated memory.
 *
 * @param[in,out]   p_hash_context  Pointer a to value-length structure that holds the allocated space
 *                                  to be freed.
 * @retval          NRF_SUCCESS     Space was successfully freed.
 */
uint32_t nrf_crypto_hash_context_free(nrf_value_length_t * p_hash_context);


/**@brief   Function to dynamically allocate memory to hold a hash value.
 *
 * @param[in]       hash_info       Structure holding info about hash algorithm to use and
 *                                  endianness for the computed hash.
 * @param[in,out]   p_hash          Pointer to value-length structure to hold allocated space.
 * @param[in]       p_raw_hash      Pointer to value length structure to hold raw representation
 *                                  of hash.
 *
 * @retval          NRF_SUCCESS     Space was successfully alloacted.
 */
uint32_t nrf_crypto_hash_allocate(nrf_crypto_hash_info_t        hash_info,
                                  nrf_value_length_t          * p_hash,
                                  nrf_value_length_t    const * p_raw_hash);


/** @brief  Function to free dynamically allocated memory for a hash value.
 *
 * @note    The length value of the value length structure will be set to
 *          zero when the memory is freed. There is no impact of running this
 *          function on already deallocated memory.
 *
 * @param[in,out]   p_hash          Pointer to a value-length structure that holds the
 *                                  allocated space to be freed.
 *
 * @retval          NRF_SUCCESS     Space was successfully freed.
 */
uint32_t nrf_crypto_hash_free(nrf_value_length_t         * p_hash);


/**@brief Function for computing a hash from arbitrary data.
 *
 * @note    The context object is assumed to be an opaque type defined by the
 *          nrf_crypto backend. See @ref NRF_CRYPTO_HASH_CONTEXT_SIZE for the relevant
 *          nrf_crypto backend.
 *
 * @param[in]       hash_info       Structure holding info about hash algorithm to use and
 *                                  endianness for the computed hash.
 * @param[in,out]   p_hash_context  Pointer to structure holding context information for
 *                                  the hash computation.
 *
 * @retval  NRF_SUCCESS                 If the hash initialization was successful.
 * @retval  NRF_ERROR_INVALID_STATE     If the function was called when nrf_crypto was
 *                                      uninitialized.
 * @retval  NRF_ERROR_NULL              If the hash context parameter was NULL.
 * @retval  NRF_ERROR_NOT_SUPPORTED     If the selected hash algorithm is not supported.
 * @retval  NRF_ERROR_INVALID_ADDR      If any of the provided pointers are invalid.
 * @retval  NRF_ERROR_INVALID_LENGTH    If the hash is bigger than the size of the provided buffer.
 * @retval  NRF_ERROR_INVALID_DATA      If the hash context was deemed invalid by the nrf_crypto
 *                                      backend.
 * @retval  NRF_ERROR_INTERNAL          If an internal error occured in the nrf_crypto backend.
 */
uint32_t nrf_crypto_hash_init(nrf_crypto_hash_info_t    hash_info,
                              nrf_value_length_t      * p_hash_context);


/**@brief Function for computing a hash or a digest from arbitrary data.
 *
 * @note    The context object is assumed to be an opaque type defined by the
 *          nrf_crypto backend. See @ref NRF_CRYPTO_HASH_CONTEXT_SIZE for the relevant
 *          nrf_crypto backend.
 *
 * @param[in,out]   p_hash_context  Pointer to structure holding context information for
 *                                  the hash computation.
 * @param[in]       p_data          Pointer to data to be hashed.
 * @param[in]       len             Length of the data to be hashed.
 *
 * @retval  NRF_SUCCESS                 If the hash was computed successfully.
 * @retval  NRF_ERROR_NULL              If the hash context parameter was NULL.
 * @retval  NRF_ERROR_INVALID_STATE     If the function was called when nrf_crypto was
 *                                      uninitialized.
 * @retval  NRF_ERROR_NOT_SUPPORTED     If the selected hash algorithm is not supported.
 * @retval  NRF_ERROR_INVALID_ADDR      If any of the provided pointers are invalid.
 * @retval  NRF_ERROR_INVALID_LENGTH    If the size of the hash context is invalid.
 * @retval  NRF_ERROR_INVALID_DATA      If the hash context was deemed invalid by the nrf_crypto
 *                                      backend.
 * @retval  NRF_ERROR_INTERNAL          If an internal error occured in the nrf_crypto backend.
 */
uint32_t nrf_crypto_hash_update(nrf_value_length_t   * p_hash_context,
                                uint8_t        const * p_data,
                                uint32_t               len);


/**@brief Function for computing a hash from arbitrary data.
 *
 * @note    The context object is assumed to be an opaque type defined by the
 *          nrf_crypto backend. See @ref NRF_CRYPTO_HASH_CONTEXT_SIZE for the relevant
 *          nrf_crypto backend.
 *
 * @param[in]       hash_info       Structure holding info about hash algorithm to use.
 * @param[in,out]   p_hash_context  Pointer to structure holding context information for
 *                                  the hash computation.
 * @param[in,out]   p_hash          Pointer to structure holding the calculated hash.
 *
 * @retval  NRF_SUCCESS                 If the hash was computed successfully.
 * @retval  NRF_ERROR_INVALID_STATE     If the function was called when nrf_crypto was
 *                                      uninitialized.
 * @retval  NRF_ERROR_NULL              If the any of the parameters was NULL.
 * @retval  NRF_ERROR_NOT_SUPPORTED     If the selected hash algorithm is not supported.
 * @retval  NRF_ERROR_INVALID_ADDR      If any of the provided pointers are invalid.
 * @retval  NRF_ERROR_INVALID_LENGTH    If the hash is bigger than the size of the provided buffer
 *                                      or the size of the hash context is invalid.
 * @retval  NRF_ERROR_INVALID_DATA      If the hash context was deemed invalid by the nrf_crypto
 *                                      backend.
 * @retval  NRF_ERROR_INTERNAL          If an internal error occured in the nrf_crypto backend.
 */
uint32_t nrf_crypto_hash_finalize(nrf_crypto_hash_info_t    hash_info,
                                  nrf_value_length_t      * p_hash_context,
                                  nrf_value_length_t      * p_hash);


/**@brief Function for computing a hash from arbitrary data in a single integrated step.
 *
 * @param[in]       hash_info   Structure holding info about hash algorithm to use and endianness
 *                              for the computed hash.
 * @param[in]       p_data      Pointer to data to be hashed.
 * @param[in]       len         Length of the data to be hashed.
 * @param[in,out]   p_hash      Pointer to structure holding the calculated hash.
 *
 * @retval  NRF_SUCCESS                 If the hash was computed successfully.
 * @retval  NRF_ERROR_INVALID_STATE     If the function was called when nrf_crypto was
 *                                      uninitialized.
 * @retval  NRF_ERROR_NOT_SUPPORTED     If the selected hash algorithm is not supported.
 * @retval  NRF_ERROR_INVALID_ADDR      If any of the provided pointers are invalid.
 * @retval  NRF_ERROR_INVALID_LENGTH    If the hash is bigger than the size of the provided buffer
 *                                      or the size of the hash context is invalid.
 * @retval  NRF_ERROR_INVALID_DATA      If the hash context was deemed invalid by the nrf_crypto
 *                                      backend.
 * @retval  NRF_ERROR_INTERNAL          If an internal error occured in the nrf_crypto backend.
 */
uint32_t nrf_crypto_hash_compute(nrf_crypto_hash_info_t    hash_info,
                                 uint8_t           const * p_data,
                                 uint32_t                  len,
                                 nrf_value_length_t      * p_hash);


#ifdef __cplusplus
}
#endif

/**@} */

#endif // #ifndef NRF_CRYPTO_HASH_H__
