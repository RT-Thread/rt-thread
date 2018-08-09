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

#ifndef NRF_CRYPTO_HMAC_H__
#define NRF_CRYPTO_HMAC_H__

/** @file
 *
 * @defgroup nrf_crypto_hmac Hash-based message authentication code (HMAC) related functions
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides functions to generate Hash-based message authentication code (HMAC).
 *
 * @details Provides functions to generate Hash-based message authentication code (HMAC) using
 * one of the supported hash algorithms. This layer is independent of backend crypto library.
 */

#include <stdint.h>
#include "sdk_common.h"
#include "nrf_crypto_types.h"
#include "nrf_crypto_hmac_backend.h"
#include "nrf_crypto_hmac_shared.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Information structures used to select the specific algorithm (SHA-256)
 *
 * @details The information structure is used in a generic way but is populated by the backend,
 * and contains backend specific data. */
extern const nrf_crypto_hmac_info_t g_nrf_crypto_hmac_sha256_info;


/**
 * @brief Information structures used to select the specific algorithm (SHA-512)
 *
 * @details The information structure is used in a generic way but is populated by the backend,
 * and contains backend specific data.
 */
extern const nrf_crypto_hmac_info_t g_nrf_crypto_hmac_sha512_info;


/**
 * @brief Context type for HMAC.
 *
 * @note The size of this type is scaled for the largest HMAC backend context that is
 *       enabled in @ref sdk_config.
 */
typedef nrf_crypto_backend_hmac_context_t nrf_crypto_hmac_context_t;

/**
 * @brief Initialize context object for HMAC
 *
 * @details Use to initialize a context once it has been allocated.
 *
 * @note Must be called before @ref nrf_crypto_hmac_update. Can also be called after
 *       @ref nrf_crypto_hmac_finalize order to start a new HMAC calculation re-using an
 *       existing context object.
 *
 * @param[in,out]   p_context       Pointer to context structure.
 * @param[in]       p_info          Pointer to static info structure. This defines the algorithm.
 *                                  This should be either @ref g_nrf_crypto_hmac_sha256_info or
 *                                  @ref g_nrf_crypto_hmac_sha512_info.
 * @param[in]       p_key           HMAC key.
 * @param[in]       key_size        Length of the HMAC key in bytes.
 *
 * @retval  NRF_SUCCESS                     Data successfully consumed.
 * @retval  NRF_ERROR_CRYPTO_CONTEXT_NULL   If p_context has not been initialized.
 * @retval  NRF_ERROR_CRYPTO_INPUT_NULL     If p_info or p_key was NULL.
 * @retval  NRF_ERROR_CRYPTO_INPUT_LENGTH   If key_size was invalid.
 * @retval  NRF_ERROR_CRYPTO_INPUT_LOCATION Input data not in RAM (CC310 only).
 * @retval  NRF_ERROR_CRYPTO_INTERNAL       An error occurred in the crypto backend.
 * @retval  NRF_ERROR_CRYPTO_BUSY           The function could not be called because the
 *                                          nrf_crypto backend was busy. Please rerun
 *                                          the cryptographic routine at a later time.
 *                                          CC310 only.
 */
ret_code_t nrf_crypto_hmac_init(nrf_crypto_hmac_context_t   * const p_context,
                                nrf_crypto_hmac_info_t      const * p_info,
                                uint8_t                     const * p_key,
                                size_t                              key_size);


/**
 * @brief Feed data to HMAC algorithm.
 *
 * @note Must be called after @ref nrf_crypto_hmac_init and before @ref nrf_crypto_hmac_finalize.
 *       Can be called repeatedly to consume data as it arrives.
 *
 * @param[in,out]   p_context   Context pointer.
 * @param[in]       p_data      Pointer to input data buffer.
 * @param[in]       data_size   Length of input data.
 *
 * @retval  NRF_SUCCESS                                 Data successfully consumed.
 * @retval  NRF_ERROR_CRYPTO_CONTEXT_NULL               If p_context has not been initialized.
 * @retval  NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED    If p_data was NULL.
 * @retval  NRF_ERROR_CRYPTO_INPUT_NULL                 If p_data was NULL.
 * @retval  NRF_ERROR_CRYPTO_INPUT_LENGTH               If size was invalid.
 * @retval  NRF_ERROR_CRYPTO_INPUT_LOCATION             Input data not in RAM (CC310 only).
 * @retval  NRF_ERROR_CRYPTO_INTERNAL                   An error occurred in the crypto backend.
 * @retval  NRF_ERROR_CRYPTO_BUSY                       The function could not be called because the
 *                                                      nrf_crypto backend was busy. Please rerun
 *                                                      the cryptographic routine at a later time.
 *                                                      CC310 only.
 */
ret_code_t nrf_crypto_hmac_update(nrf_crypto_hmac_context_t * const p_context,
                                  uint8_t                   const * p_data,
                                  size_t                            data_size);


/**
 * @brief Calculate HMAC
 *
 * @note @ref nrf_crypto_hmac_update must be called at least once before calling this.
 *
 * @param[in,out]  p_context     Context pointer.
 * @param[out]     p_digest      Pointer to HMAC digest (result) buffer. Must be large enough to
 *                               hold the digest (32 byte for SHA-256 and 64 byte for SHA-512).
 * @param[in,out]  p_digest_size Length of buffer as input. Length of digest as output.
 *
 * @retval  NRF_SUCCESS                                 HMAC hash was successfully calculated.
 * @retval  NRF_ERROR_CRYPTO_CONTEXT_NULL               If p_context was NULL.
 * @retval  NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED    If p_context has not been initialized.
 * @retval  NRF_ERROR_CRYPTO_OUTPUT_NULL                If p_digest was NULL.
 * @retval  NRF_ERROR_CRYPTO_OUTPUT_LENGTH              If p_size is not enough to hold the digest.
 * @retval  NRF_ERROR_CRYPTO_INTERNAL                   An error occurred in the crypto backend.
 * @retval  NRF_ERROR_CRYPTO_BUSY                       The function could not be called because the
 *                                                      nrf_crypto backend was busy. Please rerun
 *                                                      the cryptographic routine at a later time.
 *                                                      CC310 only.
 */
ret_code_t nrf_crypto_hmac_finalize(nrf_crypto_hmac_context_t   * const p_context,
                                    uint8_t                           * p_digest,
                                    size_t                      * const p_digest_size);


/**
 * @brief Integrated HMAC wrapper function
 *
 * @note This is an integrated wrapper functions that can be used instead of calling other HMAC
 *       functions individually.
 *
 * @param[in,out]  p_context     Optional pointer to context structure.
 *                               Context memory will be allocated internally if the pointer is NULL.
 * @param[in]      p_info        Pointer to static info structure. This defines the algorithm.
 *                               This should be either @ref g_nrf_crypto_hmac_sha256_info or
 *                               @ref g_nrf_crypto_hmac_sha512_info.
 * @param[out]     p_digest      Pointer to HMAC digest.
 *                               Buffer must be large enough to hold the digest.
 * @param[in,out]  p_digest_size Length of digest (result) buffer as input.
 *                               Length of digest as output.
 * @param[in]      p_key         Pointer to HMAC key.
 * @param[in]      key_size      Lenth of the HMAC key in bytes.
 * @param[in]      p_data        Pointer to input data.
 * @param[in]      data_size     Length of input data.
 *
 * @retval  NRF_SUCCESS                     HMAC hash was successfully calculated.
 * @retval  NRF_ERROR_CRYPTO_INPUT_NULL     If p_key or p_data was NULL.
 * @retval  NRF_ERROR_CRYPTO_INPUT_LOCATION Input data not in RAM (CC310 only).
 * @retval  NRF_ERROR_CRYPTO_INPUT_LENGTH   If key_size or data_size was invalid.
 * @retval  NRF_ERROR_CRYPTO_OUTPUT_NULL    If data_size was NULL.
 * @retval  NRF_ERROR_CRYPTO_OUTPUT_LENGTH  If data_size is not enough to hold the digest.
 * @retval  NRF_ERROR_CRYPTO_ALLOC_FAILED   Unable to allocate memory for the context.
 * @retval  NRF_ERROR_CRYPTO_INTERNAL       An error occurred in the crypto backend.
 * @retval  NRF_ERROR_CRYPTO_BUSY           The function could not be called because the
 *                                          nrf_crypto backend was busy. Please rerun the
 *                                          cryptographic routine at a later time. CC310 only.
 */
ret_code_t nrf_crypto_hmac_calculate(nrf_crypto_hmac_context_t  * const p_context,
                                     nrf_crypto_hmac_info_t     const * p_info,
                                     uint8_t                          * p_digest,
                                     size_t                     * const p_digest_size,
                                     uint8_t                    const * p_key,
                                     size_t                             key_size,
                                     uint8_t                    const * p_data,
                                     size_t                             data_size);


#ifdef __cplusplus
}
#endif

/**@} */

#endif // #ifndef NRF_CRYPTO_HMAC_H__
