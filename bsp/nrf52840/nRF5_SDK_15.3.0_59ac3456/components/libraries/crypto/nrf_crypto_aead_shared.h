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

#ifndef NRF_CRYPTO_AEAD_SHARED_H__
#define NRF_CRYPTO_AEAD_SHARED_H__

/** @file
 *
 * @defgroup nrf_crypto_aead_shared AEAD related functions
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides AEAD related functionality through nrf_crypto.
 */

#include <stdint.h>
#include "nrf_crypto_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@internal @brief Magic value to signal that the nrf_crypto_hash context structure is initialized.
 */
#define NRF_CRYPTO_AEAD_INIT_MAGIC_VALUE    (0x44414541)    // ASCII "AEAD"

#define NRF_CRYPTO_AES_CCM_STAR_MAC_BITMASK     (0x1C) /* [0, 4, 8, 16] allowed MAC size in CCM mode */
#define NRF_CRYPTO_AES_CCM_MAC_MIN              (4u)   /* MAC min value in CCM mode */
#define NRF_CRYPTO_AES_CCM_MAC_MAX              (16u)  /* MAC max value in CCM mode */
#define NRF_CRYPTO_AES_GCM_MAC_MIN              (4u)   /* MAC min value in GCM mode */
#define NRF_CRYPTO_AES_GCM_MAC_MAX              (16u)  /* MAC max value in GCM mode */
#define NRF_CRYPTO_AES_CCM_NONCE_SIZE_MIN       (7u)   /* [7...13] allowed nonce size in CCM mode */
#define NRF_CRYPTO_AES_CCM_NONCE_SIZE_MAX       (13u)  /* [7...13] allowed nonce size in CCM mode */
#define NRF_CRYPTO_AES_CCM_STAR_NONCE_SIZE      (13u)  /* [13] allowed nonce size in CCM* mode */
#define NRF_CRYPTO_CHACHA_POLY_NONCE_SIZE       (12u)  /* [12] allowed nonce size in chacha-poly mode */
#define NRF_CRYPTO_CHACHA_POLY_MAC_SIZE         (16u)  /* [16] allowed MAC size in chacha-poly mode */

/**@internal @brief Enumeration of supported modes of operation in nrf_crypto_aead.
 */
typedef enum
{
    NRF_CRYPTO_AEAD_MODE_AES_CCM,       // supported by: MBEDTLS & CC310
    NRF_CRYPTO_AEAD_MODE_AES_CCM_STAR,  // supported by: CC310
    NRF_CRYPTO_AEAD_MODE_AES_EAX,       // supported by: CIFRA
    NRF_CRYPTO_AEAD_MODE_AES_GCM,       // supported by: MBEDTLS
    NRF_CRYPTO_AEAD_MODE_CHACHA_POLY    // supported by: CC310 & OBERON
} nrf_crypto_aead_mode_t;


/**@internal @brief Type declaration to perform AEAD initialization in the nrf_crypto backend.
 *
 *  This is internal API. See @ref nrf_crypto_aead_init for documentation.
 */
typedef ret_code_t (*aead_init_fn_t)(void * const p_context, uint8_t * p_key);

/**@internal @brief Type declaration to perform AEAD uninitialization in the nrf_crypto backend.
 *
 *  This is internal API. See @ref nrf_crypto_aead_uninit for documentation.
 */
typedef ret_code_t (*aead_uninit_fn_t)(void * const p_context);

/**@internal @brief Type declaration to perform AEAD encryption in nrf_crypto backend.
 *
 *  This is internal API. See @ref nrf_crypto_aead_crypt for documentation.
 */
typedef ret_code_t (*aead_crypt_fn_t)(void * const           p_context,
                                      nrf_crypto_operation_t operation,
                                      uint8_t *              p_nonce,
                                      uint8_t                nonce_size,
                                      uint8_t *              p_adata,
                                      size_t                 adata_size,
                                      uint8_t *              p_data_in,
                                      size_t                 data_in_size,
                                      uint8_t *              p_data_out,
                                      uint8_t *              p_mac,
                                      uint8_t                mac_size);

/**@internal @brief Type declaration for the nrf_crypto_aead info structure.
 *
 * @details     This structure contains the calling interface and any metadata required
 *              to call the nrf_crypto_aead API functions.
 */
typedef struct
{
    nrf_crypto_aead_mode_t   const mode;
    nrf_crypto_key_size_id_t const key_size;

    aead_init_fn_t   const init_fn;
    aead_uninit_fn_t const uninit_fn;
    aead_crypt_fn_t  const crypt_fn;
} nrf_crypto_aead_info_t;

/**@internal @brief Type declaration of internal representation of an AEAD context structure.
 *
 * @details     This is an internal type that should not be used directly.
 */
typedef struct
{
    uint32_t init_value;
    nrf_crypto_aead_info_t const * p_info;
} nrf_crypto_aead_internal_context_t;

/** @} */

#ifdef __cplusplus
}
#endif

#endif // #ifndef NRF_CRYPTO_AEAD_SHARED_H__

