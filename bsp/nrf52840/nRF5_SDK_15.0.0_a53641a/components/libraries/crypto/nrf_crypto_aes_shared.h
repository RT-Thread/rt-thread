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

#ifndef NRF_CRYPTO_AES_SHARED_H__
#define NRF_CRYPTO_AES_SHARED_H__

/** @file
 *
 * @defgroup nrf_crypto_aes AES related functions
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides AES related functionality through nrf_crypto.
 */

#include <stdint.h>
#include "nrf_crypto_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@internal @brief Magic value to signal that the nrf_crypto_hash context structure is initialized.
 */
#define NRF_CRYPTO_AES_INIT_MAGIC_VALUE     (0x53454163)    // ASCII "cAES"
#define NRF_CRYPTO_AES_UNINIT_MAGIC_VALUE   (0x63414553)    // ASCII "SEAc"

#define NRF_CRYPTO_MBEDTLS_AES_IV_SIZE  (16)


/** @internal @brief Enumeration of supported modes of operation in nrf_crypto_aes.
 */
typedef enum
{
    NRF_CRYPTO_AES_MODE_CBC,                // supported by: MBEDTLS & CC310
    NRF_CRYPTO_AES_MODE_CBC_PAD_PCKS7,      // supported by: MBEDTLS & CC310
    NRF_CRYPTO_AES_MODE_CFB,                // supported by: MBEDTLS
    NRF_CRYPTO_AES_MODE_CTR,                // supported by: MBEDTLS & CC310
    NRF_CRYPTO_AES_MODE_ECB,                // supported by: MBEDTLS & CC310
    NRF_CRYPTO_AES_MODE_ECB_PAD_PCKS7,      // supported by: MBEDTLS & CC310

    // Authentication modes
    NRF_CRYPTO_AES_MODE_CBC_MAC,            // supported by: MBEDTLS & CC310
    NRF_CRYPTO_AES_MODE_CBC_MAC_PAD_PCKS7,  // supported by: MBEDTLS & CC310
    NRF_CRYPTO_AES_MODE_CMAC,               // supported by: MBEDTLS & CC310
} nrf_crypto_aes_mode_t;

/**@internal @brief Type declaration to perform AES initialization in the nrf_crypto backend.
 *
 *  This is internal API. See @ref nrf_crypto_aes_init for documentation.
 */
typedef ret_code_t (*aes_init_fn_t)(void * const p_context, nrf_crypto_operation_t operation);

/**@internal @brief Type declaration to perform AES uninitialization in the nrf_crypto backend.
 *
 *  This is internal API. See @ref nrf_crypto_aes_uninit for documentation.
 */
typedef ret_code_t (*aes_uninit_fn_t)(void * const p_context);

/**@internal @brief Type declaration to set an AES key in the nrf_crypto backend.
 *
 *  This is internal API. See @ref nrf_crypto_aes_key_set for documentation.
 */
typedef ret_code_t (*aes_key_set_fn_t)(void * const p_context, uint8_t * p_key);

/**@internal @brief Type declaration to set an AES IV in the nrf_crypto backend.
 *
 *  This is internal API. See @ref nrf_crypto_aes_iv_set for documentation.
 */
typedef ret_code_t (*aes_iv_set_fn_t)(void * const p_context, uint8_t * p_iv);

/**@internal @brief Type declaration to get an AES IV in the nrf_crypto backend.
 *
 *  This is internal API. See @ref nrf_crypto_aes_iv_get for documentation.
 */
typedef ret_code_t (*aes_iv_get_fn_t)(void * const p_context, uint8_t * p_iv);

/**@internal @brief Type declaration to perform AES block operation in the nrf_crypto backend.
 *
 *  This is internal API. See @ref nrf_crypto_aes_update for documentation.
 */
typedef ret_code_t (*aes_update_fn_t)(void * const p_context,
                                      uint8_t *    p_data_in,
                                      size_t       data_size,
                                      uint8_t *    p_data_out);

/**@internal @brief Type declaration to finalize AES operation in the nrf_crypto backend.
 *
 *  This is internal API. See @ref nrf_crypto_aes_finalize for documentation.
 */
typedef ret_code_t (*aes_finalize_fn_t)(void * const p_context,
                                        uint8_t *    p_data_in,
                                        size_t       data_size,
                                        uint8_t *    p_data_out,
                                        size_t *     p_data_out_size);

/**@internal @brief Type declaration for an nrf_crypto_aes info structure.
 *
 * @details     This structure contains the calling interface and any metadata required
 *              to call the nrf_crypto_aes API functions.
 */
typedef struct
{
    nrf_crypto_aes_mode_t    const mode;
    nrf_crypto_key_size_id_t const key_size;
    size_t                   const context_size;

    aes_init_fn_t            const init_fn;
    aes_uninit_fn_t          const uninit_fn;
    aes_key_set_fn_t         const key_set_fn;
    aes_iv_set_fn_t          const iv_set_fn;
    aes_iv_get_fn_t          const iv_get_fn;
    aes_update_fn_t          const update_fn;
    aes_finalize_fn_t        const finalize_fn;
} nrf_crypto_aes_info_t;

/**@internal @brief Type declaration of internal representation of an AES context structure.
 *
 * @details     This is an internal type that should not be used directly.
 */
typedef struct
{
    uint32_t init_value;
    nrf_crypto_aes_info_t const * p_info;
} nrf_crypto_aes_internal_context_t;


/**@internal @brief Type declaration of internal representation of an AES backend context structure.
 *                  with initialization vector.
 *
 * @details     This is an internal type that should not be used directly.
 */
typedef struct
{
    nrf_crypto_operation_t operation;

    uint8_t  iv[NRF_CRYPTO_MBEDTLS_AES_IV_SIZE]; // space for 128-bit initialization vector
} nrf_crypto_backend_aes_ctx_t;

/**@internal @brief Type declaration of internal representation of an AES backend context structure
 *                   without initialization vector.
 *
 * @details     This is an internal type that should not be used directly.
 */
typedef struct
{
    nrf_crypto_operation_t operation;
} nrf_crypto_backend_no_iv_aes_ctx_t;


/**@internal @brief Function copies remainders (msg_ending_len) from p_message_buff to the
 *                  p_padding_buff. Next it adds pkcs7-padding to have a 16 bytes p_padding_buff.
 *
 * @param[in] p_padding_buff    Pointer the buffer with padded message.
 * @param[in] p_message_buff    Pointer to the buffer with message that must be padded.
 * @param[in] msg_ending_len    Message remainders length.
 *
 */
ret_code_t padding_pkcs7_add(uint8_t * p_padding_buff,
                             uint8_t * p_message_buff,
                             uint8_t   msg_ending_len);


/**@internal @brief Function calculate message length without padding.
 *
 * @param[in]     p_padded_message      Pointer the buffer with padded message.
 * @param[in/out] p_message_len         IN:  padded message length
 *                                      OUT: message length without padding
 */
ret_code_t padding_pkcs7_remove(uint8_t * p_padded_message,
                                size_t  * p_message_len);


#ifdef __cplusplus
}
#endif

/** @} */

#endif // #ifndef NRF_CRYPTO_AES_SHARED_H__
