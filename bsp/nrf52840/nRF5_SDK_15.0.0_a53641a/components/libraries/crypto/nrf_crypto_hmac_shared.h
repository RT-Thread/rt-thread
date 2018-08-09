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

#ifndef NRF_CRYPTO_HMAC_SHARED_H__
#define NRF_CRYPTO_HMAC_SHARED_H__

/** @file
 *
 * @defgroup nrf_crypto_hmac_shared Types shared between all @ref nrf_crypto_hmac backends.
 * @{
 * @ingroup nrf_crypto_hmac
 *
 * @brief Types shared between all @ref nrf_crypto_hmac backends.
 *
 * @details These types should not be used directly by the application.
 */

#include <stdint.h>
#include "sdk_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @internal @brief HMAC algorithm type.
 */
typedef enum {
    NRF_CRYPTO_HMAC_SHA256_TYPE,    //!< HMAC using hash algorithm SHA256
    NRF_CRYPTO_HMAC_SHA512_TYPE,    //!< HMAC using hash algorithm SHA512
} nrf_crypto_hmac_type_t;


/**
 * @internal @brief Function pointer type for HMAC backend init function.
 *
 * @note The backend function should never be called directly.
 *       Use @ref nrf_crypto_hmac_init instead.
 *
 * @param[in,out]  p_context   Context pointer.
 * @param[in]      p_key       HMAC key.
 * @param[in]      key_size    Length of the HMAC key in bytes.
*/
typedef ret_code_t (*nrf_crypto_hmac_init_fn_t)(void    * const p_context,
                                                uint8_t const * p_key,
                                                size_t          key_size);


/**
 * @internal @brief Function pointer type for HMAC backend update function.
 *
 * @note The backend function should never be called directly.
 *       Use @ref nrf_crypto_hmac_update instead.
 *
 * @param[in,out]  p_context   Context pointer.
 * @param[in]      p_data      Pointer to input data buffer.
 * @param[in]      size        Length of input data.
*/
typedef ret_code_t (*nrf_crypto_hmac_update_fn_t)(void      * const p_context,
                                                  uint8_t   const * p_data,
                                                  size_t            size);


/**
 * @internal @brief Function pointer type for HMAC backend finalize function.
 *
 * @note The backend function should never be called directly.
 *       Use @ref nrf_crypto_hmac_finalize instead.
 *
 * @param[in,out]  p_context               Context pointer.
 * @param[out]     p_digest                HMAC digest (result) buffer.
 * @param[in,out]  p_size                  Length of buffer as input. Length of digest as output.
*/
typedef ret_code_t (*nrf_crypto_hmac_finalize_fn_t)(void    * const p_context,
                                                    uint8_t * const p_digest,
                                                    size_t        * p_size);


/**
 * @internal @brief structure holding the configuration of each particular algorithm.
 *
 * @details This is an internal type that should not be used directly.
 */
typedef struct
{
    nrf_crypto_hmac_init_fn_t         const init_fn;        //!< Pointer to update function for specific backend.
    nrf_crypto_hmac_update_fn_t       const update_fn;      //!< Pointer to update function for specific backend.
    nrf_crypto_hmac_finalize_fn_t     const finalize_fn;    //!< Pointer to finalize function for specific backend.
    size_t                            const digest_size;    //!< Size of the digest of the HMAC operation.
    size_t                            const context_size;   //!< Size of the context type.
    nrf_crypto_hmac_type_t            const type;           //!< HMAC algorithm type.
} nrf_crypto_hmac_info_t;


/**
 * @internal @brief Common header for each HMAC context structures
 *
 * @details This is an internal type that should not be used directly.
 */
typedef struct
{
    uint32_t                        init_value;     //!< Contains NRF_CRYPTO_HMAC_INIT_MAGIC_VALUE if it is correctly initialized.
    nrf_crypto_hmac_info_t  const * p_info;         //!< Points to information object related to selected algorithm.
} nrf_crypto_hmac_internal_context_t;


#ifdef __cplusplus
}
#endif

/**@} */

#endif // NRF_CRYPTO_HMAC_SHARED_H__
