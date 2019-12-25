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

#ifndef NRF_CRYPTO_HASH_H__
#define NRF_CRYPTO_HASH_H__

/** @file
 *
 * @defgroup nrf_crypto_hash Cryptographic hash related functions
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides cryptographic hash related functionality through nrf_crypto.
 */

#include <stdint.h>
#include "nrf_crypto_types.h"
#include "nrf_crypto_hash_shared.h"
#include "nrf_crypto_hash_backend.h"
#include "app_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief External variable declaration to info structure for SHA-256
 *
 * @note The variable is defined in the nrf_crypto backend that is
 *       enabled in the @ref sdk_config.
 *
 */
extern const nrf_crypto_hash_info_t g_nrf_crypto_hash_sha256_info;


 /**@brief External variable declaration to info structure for SHA-512
 *
 * @note The variable is defined in the nrf_crypto backend that is
 *       enabled in the @ref sdk_config.
 *
 */
extern const nrf_crypto_hash_info_t g_nrf_crypto_hash_sha512_info;


/**
 * @brief Context type for Hash.
 *
 * @note The size of this type is scaled for the largest Hash backend context that is
 *       enabled in @ref sdk_config.
 */
typedef nrf_crypto_backend_hash_context_t nrf_crypto_hash_context_t;


/** @brief Type definition for an array holding a SHA-256 hash digest. */
typedef uint8_t nrf_crypto_hash_sha256_digest_t[NRF_CRYPTO_HASH_SIZE_SHA256];


/** @brief Type definition for an array holding a SHA-512 hash digest. */
typedef uint8_t nrf_crypto_hash_sha512_digest_t[NRF_CRYPTO_HASH_SIZE_SHA512];


/**@brief Function for initializing the context structure required to compute a hash digest from
 *        arbitrary input data.
 *
 * @note    The context structure is assumed to be an opaque type defined by the
 *          nrf_crypto backend.
 *
 * @note    The return codes @ref NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE and
 *          NRF_ERROR_CRYPTO_INTERNAL only happens in cc310 backend.
 *
 * @param[in,out]   p_context       Pointer to structure holding context information for
 *                                  the hash calculation.
 * @param[in]       p_info          Pointer to structure holding info about the hash algorithm
 *                                  used to do the computed hash.
 *
 * @retval  NRF_SUCCESS                          The hash initialization was successful.
 * @retval  NRF_ERROR_CRYPTO_NOT_INITIALIZED     @ref nrf_crypto_init was not called prior to
 *                                               this crypto function.
 * @retval  NRF_ERROR_CRYPTO_CONTEXT_NULL        A NULL pointer was provided for the context
 *                                               structure.
 * @retval  NRF_ERROR_CRYPTO_INPUT_NULL          The pointer to the info structure was NULL.
 * @retval  NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE The function was called with a hash mode that
 *                                               is unavailable.
 * @retval  NRF_ERROR_CRYPTO_INTERNAL            An internal error occurred when initializing
 *                                               the constext in the nrf_crypto backend.
 */
ret_code_t nrf_crypto_hash_init(nrf_crypto_hash_context_t * const p_context,
                                nrf_crypto_hash_info_t    const * p_info);


/**@brief Function for updating the hash calculation with partial arbitrary data.
 *
 * @details This function should be called one or more times until all arbituary input data
 *          required for the hash calcuation is provided.
 *
 * @note    @ref nrf_crypto_hash_init must be called prior to this function to configure the
 *          context structure used as input parameter to this function.
 *
 * @note    @ref nrf_crypto_hash_finalize must be called after all arbitruary input data
 *          has been provided to get the calculated hash digest.
 *
 * @note    The context object is assumed to be an opaque type defined by the
 *          nrf_crypto backend.
 *
 * @note    The return values @ref NRF_ERROR_CRYPTO_BUSY, @ref NRF_ERROR_CRYPTO_INPUT_LOCATION
 *          and @ref NRF_ERROR_CRYPTO_INPUT_LOCATION can only occur in CC310 backend.
 *
 * @param[in,out]   p_context       Pointer to structure holding context information for
 *                                  the hash calculation.
 * @param[in]       p_data          Pointer to data to be hashed.
 * @param[in]       data_size       Length of the data to be hashed.
 *
 * @retval  NRF_SUCCESS                               The hash digest was computed successfully.
 * @retval  NRF_ERROR_CRYPTO_NOT_INITIALIZED          @ref nrf_crypto_init was not called prior to
 *                                                    this crypto function.
 * @retval  NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED  The context was not initialized prior to
 *                                                    this call or it was corrupted. Please call
 *                                                    @ref nrf_crypto_hash_init to initialize it.
 * @retval  NRF_ERROR_CRYPTO_CONTEXT_NULL             A NULL pointer was provided for the context
 *                                                    structure.
 * @retval  NRF_ERROR_CRYPTO_INPUT_NULL               p_data was NULL.
 * @retval  NRF_ERROR_CRYPTO_INPUT_LOCATION           Input data not in RAM.
 * @retval  NRF_ERROR_CRYPTO_BUSY                     The function could not be called because the
 *                                                    nrf_crypto backend was busy. Please rerun the
 *                                                    cryptographic routine at a later time.
 * @retval  NRF_ERROR_CRYPTO_INTERNAL                 An internal error occurred in the nrf_crypto
 *                                                    backend.
 */
ret_code_t nrf_crypto_hash_update(nrf_crypto_hash_context_t   * const p_context,
                                  uint8_t                     const * p_data,
                                  size_t                              data_size);

/**@brief Function for finalizing computation of a hash digest from arbitrary data.
 *
 * @details This function is called to get the calculated
 *
 * @note    @ref nrf_crypto_hash_init must be called prior to this function to configure the
 *          context structure used as input parameter to this function.
 *
 * @note    The input data for the calculated hash digest must be provided by calling
 *          @ref nrf_crypto_hash_update one or more times.
 *
 * @note    The context object is assumed to be an opaque type defined by the
 *          nrf_crypto backend.
 *
 * @note    The return values @ref NRF_ERROR_CRYPTO_BUSY and @ref NRF_ERROR_CRYPTO_INPUT_LOCATION
 *          can only occur in CC310 backend.
 *
 *
 * @param[in]       p_context       Pointer to structure holding context information for
 *                                  the hash calculation.
 * @param[out]      p_digest        Pointer to buffer holding the calculated hash digest.
 * @param[in,out]   p_digest_size   Pointer to a variable holding the length of the calculated hash.
 *                                  Set this to the length of buffer that p_digest is pointing to.
 *
 * @retval  NRF_SUCCESS                               The hash digest was computed successfully.
 * @retval  NRF_ERROR_CRYPTO_NOT_INITIALIZED          @ref nrf_crypto_init was not called prior to
 *                                                    this crypto function.
 * @retval  NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED  The context was not initialized prior to
 *                                                    this call or it was corrupted. Please call
 *                                                    @ref nrf_crypto_hash_init to initialize it.
 * @retval  NRF_ERROR_CRYPTO_CONTEXT_NULL             A NULL pointer was provided for the context
 *                                                    structure.
 * @retval  NRF_ERROR_CRYPTO_OUTPUT_NULL              p_digest or p_digest_size was NULL.
 * @retval  NRF_ERROR_CRYPTO_OUTPUT_LENGTH            The length of p_digest was too small for
 *                                                    the hash digest result.
 * @retval  NRF_ERROR_CRYPTO_BUSY                     The function could not be called because the
 *                                                    nrf_crypto backend was busy. Please rerun the
 *                                                    cryptographic routine at a later time.
 * @retval  NRF_ERROR_CRYPTO_INTERNAL                 An internal error occurred in the nrf_crypto
 *                                                    backend.
 */
ret_code_t nrf_crypto_hash_finalize(nrf_crypto_hash_context_t * const p_context,
                                    uint8_t                         * p_digest,
                                    size_t                    * const p_digest_size);


/**@brief Function for computing a hash from arbitrary data in a single integrated step.
 *
 * @details This function calculates the hash digest from arbitruary data in a single integrated step.
 *          This means calling init, update and finalize in one step.
 *
 * @note    The context object is assumed to be an opaque type defined by the
 *          nrf_crypto backend.
 *
 * @note    The return values @ref NRF_ERROR_CRYPTO_BUSY, @ref NRF_ERROR_CRYPTO_INPUT_LOCATION
 *          and @ref NRF_ERROR_CRYPTO_INPUT_LOCATION can only occur in CC310 backend.
 *
 * @param[in,out]   p_context       Pointer to structure holding context information for
 *                                  the hash calculation. If this
 *                                  is set to NULL, it will be allocated by the user configurable
 *                                  allocate/free function @ref NRF_CRYPTO_ALLOC and
 *                                  @ref NRF_CRYPTO_FREE.
 * @param[in]       p_info          Pointer to structure holding info about hash algorithm
 *                                  for the computed hash.
 * @param[in]       p_data          Pointer to data to be hashed.
 * @param[in]       data_size       Length of the data to be hashed.
 * @param[out]      p_digest        Pointer to buffer holding the calculated hash digest.
 * @param[in,out]   p_digest_size   Pointer to a variable holding the length of the calculated hash.
 *                                  Set this to the length of buffer that p_digest is pointing to.
 *
 * @retval  NRF_SUCCESS                         The hash initialization was successful.
 * @retval  NRF_ERROR_CRYPTO_NOT_INITIALIZED    @ref nrf_crypto_init was not called prior to
 *                                              this crypto function.
 * @retval  NRF_ERROR_CRYPTO_CONTEXT_NULL       A NULL pointer was provided for the context
 *                                              structure.
 * @retval  NRF_ERROR_CRYPTO_INPUT_NULL         p_info or p_data was NULL.
 * @retval  NRF_ERROR_CRYPTO_INPUT_LOCATION     Input data not in RAM.
 * @retval  NRF_ERROR_CRYPTO_OUTPUT_NULL        p_digest or p_digest_size was NULL.
 * @retval  NRF_ERROR_CRYPTO_OUTPUT_LENGTH      The length of p_digest was too small for
 *                                              the hash digest result.
 * @retval  NRF_ERROR_CRYPTO_BUSY               The function could not be called because the
 *                                              nrf_crypto backend was busy. Please rerun the
 *                                              cryptographic routine at a later time.
 * @retval  NRF_ERROR_CRYPTO_ALLOC_FAILED       Unable to allocate memory for the context.
 * @retval  NRF_ERROR_CRYPTO_INTERNAL           An internal error occurred in the nrf_crypto
 *                                              backend.
 */
ret_code_t nrf_crypto_hash_calculate(nrf_crypto_hash_context_t    * const p_context,
                                     nrf_crypto_hash_info_t       const * p_info,
                                     uint8_t                      const * p_data,
                                     size_t                               data_size,
                                     uint8_t                            * p_digest,
                                     size_t                       * const p_digest_size);

#ifdef __cplusplus
}
#endif

/**@} */

#endif // NRF_CRYPTO_HASH_H__
