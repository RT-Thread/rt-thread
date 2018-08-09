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

#ifndef NRF_CRYPTO_HASH_SHARED_H__
#define NRF_CRYPTO_HASH_SHARED_H__

#include "stdint.h"
#include "stddef.h"
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NRF_CRYPTO_HASH_INIT_VALUE  (0x4846526E) //!< Magic value to signal that the nrf_crypto_hash context structure is initialized.

/**@brief Enumeration of supported modes of operation in nrf_crypto_hash
 */
typedef enum
{
    NRF_CRYPTO_HASH_MODE_SHA256,
    NRF_CRYPTO_HASH_MODE_SHA512
} nrf_crypto_hash_mode_t;


/**@internal @brief Type declaration to do hash initialization in nrf_crypto backend.
 *
 *  This is an internal API. See @ref nrf_crypto_hash_init for documentation.
 */
typedef ret_code_t (*nrf_crypto_hash_init_fn_t)(void * const p_context);


/**@internal @brief Type declaration to do hash update in nrf_crypto backend.
 *
 *  This is an internal API. See @ref nrf_crypto_hash_init for documentation.
 */
typedef ret_code_t (*nrf_crypto_hash_update_fn_t)(void        * const p_context,
                                                  uint8_t     const * p_data,
                                                  size_t              size);


/**@internal @brief Type declaration to do hash finalize in nrf_crypto backend.
 *
 *  This is an internal API. See @ref nrf_crypto_hash_finalize for documentation.
 */
typedef ret_code_t (*nrf_crypto_hash_finalize_fn_t)(void      * const p_context,
                                                    uint8_t         * p_digest,
                                                    size_t    * const p_digest_size);


/**@internal @brief Type declaration to for a nrf_crypto_hash info strucure
 *
 * @details     This structure contains the calling interface and any meta data required
 *              to call the nrf_crypto_hash API functions.
 */
typedef struct
{
    nrf_crypto_hash_init_fn_t      const init_fn;           /**< Function pointer to call to initialize nrf_crypto_hash context in backend. */
    nrf_crypto_hash_update_fn_t    const update_fn;         /**< Function pointer to call to add data in the hash calculation. */
    nrf_crypto_hash_finalize_fn_t  const finalize_fn;       /**< Function pointer to call to finalize the hash calculation and return the result. */
    size_t                         const digest_size;       /**< Size of the digest. */
    size_t                         const context_size;      /**< Size of the context type. */
    nrf_crypto_hash_mode_t         const hash_mode;         /**< Mode of hash operation. */
} nrf_crypto_hash_info_t;


/**@internal @brief Type declaration of internal representation of a hash context structure.
 *
 * @details     This is an internal type that should not be used directly.
 */
typedef struct
{
    uint32_t                        init_val;   /**< Value that is set to NRF_CRYPTO_HASH_INIT_VALUE when context has been initialized. */
    nrf_crypto_hash_info_t  const * p_info;     /**< Pointer to an nrf_crypto_hash info structure. */

} nrf_crypto_hash_internal_context_t;


#ifdef __cplusplus
}
#endif

#endif // NRF_CRYPTO_HASH_SHARED_H__
