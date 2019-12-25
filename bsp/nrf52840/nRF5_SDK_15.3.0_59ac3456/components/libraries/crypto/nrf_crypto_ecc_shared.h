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

#ifndef NRF_CRYPTO_ECC_SHARED_H__
#define NRF_CRYPTO_ECC_SHARED_H__
#if !defined(__SDK_DOXYGEN__)

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sdk_errors.h"


#ifdef __cplusplus
extern "C" {
#endif


#define NRF_CRYPTO_INTERNAL_ECC_PRIVATE_KEY_INIT_VALUE (0x4D465276) /**< @internal @brief Init value for all ECC private keys. ASCII "nRFv". */
#define NRF_CRYPTO_INTERNAL_ECC_PUBLIC_KEY_INIT_VALUE  (0x4D465270) /**< @internal @brief Init value for all ECC public keys. ASCII "nRFp". */


// Forward declaration only
struct nrf_crypto_ecc_curve_info_s;


/** @brief Header structure at the beginning of each key structure.
 */
typedef struct
{
    uint32_t                                   init_value;    /**< @internal @brief Init value to check if key was correctly initialized. */
    struct nrf_crypto_ecc_curve_info_s const * p_info;        /**< @internal @brief Points to information structure of an associated curve type. */
} nrf_crypto_internal_ecc_key_header_t;


/** @internal @brief Function pointer for backend implementation of a key pair garatarion.
 *
 * @note All parameters provided to the backend are vefified in frontend. Verification includes
 * checking of NULL pointers, buffer size, initialization values. Front end also take full care of
 * common ECC key hearder @ref nrf_crypto_internal_ecc_key_header_t.
 *
 * @param[in]  p_context      Pointer to context.
 * @param[out] p_private_key  Pointer where to put new private key.
 * @param[out] p_public_key   Pointer where to put new public key.
 */
typedef ret_code_t (*nrf_crypto_backend_ecc_key_pair_generate_fn_t)(
    void * p_context,
    void * p_private_key,
    void * p_public_key);


/** @internal @brief Function pointer for backend implementation of a public key calculation.
 *
 * @note All parameters provided to the backend are vefified in frontend. Verification includes
 * checking of NULL pointers, buffer size, initialization values. Front end also take full care of
 * common ECC key hearder @ref nrf_crypto_internal_ecc_key_header_t.
 *
 * @param[in]  p_context      Pointer to context.
 * @param[in]  p_private_key  Pointer to private key.
 * @param[out] p_public_key   Pointer where to put new public key.
 */
typedef ret_code_t (*nrf_crypto_backend_ecc_public_key_calculate_fn_t)(
    void       * p_context,
    void const * p_private_key,
    void       * p_public_key);


/** @internal @brief Function pointer for backend implementation of raw to private key conversion.
 *
 * @note All parameters provided to the backend are vefified in frontend. Verification includes
 * checking of NULL pointers, buffer size, initialization values. Front end also take full care of
 * common ECC key hearder @ref nrf_crypto_internal_ecc_key_header_t.
 *
 * @param[out] p_private_key  Pointer where to put new private key.
 * @param[in]  p_raw_data     Pointer to raw data.
 */
typedef ret_code_t (*nrf_crypto_backend_ecc_private_key_from_raw_fn_t)(
    void          * p_private_key,
    uint8_t const * p_raw_data);


/** @internal @brief Function pointer for backend implementation of private key to raw conversion.
 *
 * @note All parameters provided to the backend are vefified in frontend. Verification includes
 * checking of NULL pointers, buffer size, initialization values. Front end also take full care of
 * common ECC key hearder @ref nrf_crypto_internal_ecc_key_header_t.
 *
 * @param[in]  p_private_key  Pointer to private key.
 * @param[out] p_raw_data     Pointer where to put raw data.
 */
typedef ret_code_t (*nrf_crypto_backend_ecc_private_key_to_raw_fn_t)(
    void    const * p_private_key,
    uint8_t       * p_raw_data);


/** @internal @brief Function pointer for backend implementation of raw to public key conversion.
 *
 * @note All parameters provided to the backend are vefified in frontend. Verification includes
 * checking of NULL pointers, buffer size, initialization values. Front end also take full care of
 * common ECC key hearder @ref nrf_crypto_internal_ecc_key_header_t.
 *
 * @param[out] p_public_key  Pointer where to put new public key.
 * @param[in]  p_raw_data    Pointer to raw data.
 */
typedef ret_code_t (*nrf_crypto_backend_ecc_public_key_from_raw_fn_t)(
    void          * p_public_key,
    uint8_t const * p_raw_data);


/** @internal @brief Function pointer for backend implementation of public key to raw conversion.
 *
 * @note All parameters provided to the backend are vefified in frontend. Verification includes
 * checking of NULL pointers, buffer size, initialization values. Front end also take full care of
 * common ECC key hearder @ref nrf_crypto_internal_ecc_key_header_t.
 *
 * @param[in]  p_public_key  Pointer to public key.
 * @param[out] p_raw_data    Pointer where to put raw data.
 */
typedef ret_code_t (*nrf_crypto_backend_ecc_public_key_to_raw_fn_t)(
    void    const * p_public_key,
    uint8_t       * p_raw_data);


/** @internal @brief Function pointer for backend implementation of key (public or private) deallocation.
 *
 * @note All parameters provided to the backend are vefified in frontend. Verification includes
 * checking of NULL pointers, buffer size, initialization values. Front end also take full care of
 * common ECC key hearder @ref nrf_crypto_internal_ecc_key_header_t.
 *
 * @param[in]  p_key  Pointer to public or private key.
 */
typedef ret_code_t (*nrf_crypto_backend_ecc_key_free_fn_t)(
    void * p_key);


/** @internal @brief Function for checking and preparing ECC key output parameter.
 *
 * @param[in]  p_curve_info  Curve info provided by user that will be used to create a new key.
 * @param[out] p_key_header  Key header that have to be prepared.
 * @return                   NRF_SUCCESS if parameters are valid, error otherwise.
 */
ret_code_t nrf_crypto_internal_ecc_key_output_prepare(
    struct nrf_crypto_ecc_curve_info_s   const * p_curve_info,
    nrf_crypto_internal_ecc_key_header_t       * p_key_header);


/** @internal @brief Function for checking ECC key input parameter.
 *
 * @param[in] p_key_header Key header that have to be checked.
 * @param[in] init_value   Expected init value in this key.
 * @return                 NRF_SUCCESS if parameter is valid, error otherwise.
 */
ret_code_t nrf_crypto_internal_ecc_key_input_check(
    nrf_crypto_internal_ecc_key_header_t const * p_key_header,
    uint32_t                                     init_value);


/** @internal @brief Function for checking and preparing raw data output parameter.
 *
 * @param[out]    p_raw_data      Buffer where output will be written.
 * @param[in,out] p_raw_data_size Pointer to size of the data. On input this is size of provided by
 *                                the user buffer. On output is equal @p expected_size. This pointer
 *                                can be NULL if used does not want to do size checking.
 * @param[in]     expected_size   Size of output data that will be written to the buffer.
 * @return                        NRF_SUCCESS if parameters are valid, error otherwise.
 */
ret_code_t nrf_crypto_internal_ecc_raw_output_prepare(
    uint8_t    * p_raw_data,
    size_t     * p_raw_data_size,
    size_t       expected_size);


/** @internal @brief Function for checking raw data input parameter.
 *
 * @param[in] p_raw_data     Buffer where data is located.
 * @param[in] raw_data_size  Size of the data.Function will fail if it is different than @p expected_size.
 * @param[in] expected_size  Expected size of the data.
 * @return                   NRF_SUCCESS if parameters are valid, error otherwise.
 */
ret_code_t nrf_crypto_internal_ecc_raw_input_check(
    uint8_t const * p_raw_data,
    size_t          raw_data_size,
    size_t          expected_size);


#ifdef __cplusplus
}
#endif

#endif // !defined(__SDK_DOXYGEN__)
#endif // NRF_CRYPTO_ECC_SHARED_H__
