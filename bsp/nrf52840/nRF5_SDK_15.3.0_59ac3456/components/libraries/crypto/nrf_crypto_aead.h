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

#ifndef NRF_CRYPTO_AEAD_H__
#define NRF_CRYPTO_AEAD_H__

/** @file
 *
 * @defgroup nrf_crypto_aead AEAD (Authenticated Encryption with Associated Data) related
 * functions.
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides AEAD related functionality through nrf_crypto.
 */

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_CRYPTO) || defined(__SDK_DOXYGEN__)

#include <stdint.h>
#include "nrf_crypto_types.h"
#include "nrf_crypto_aead_shared.h"
#include "nrf_crypto_aead_backend.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief External variable declaration to the info structure for AES CCM mode with a 128-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aead_info_t g_nrf_crypto_aes_ccm_128_info;

/**@brief External variable declaration to the info structure for AES CCM mode with a 192-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aead_info_t g_nrf_crypto_aes_ccm_192_info;

/**@brief External variable declaration to the info structure for AES CCM mode with a 256-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aead_info_t g_nrf_crypto_aes_ccm_256_info;

/**@brief External variable declaration to the info structure for AES CCM* mode with a 128-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aead_info_t g_nrf_crypto_aes_ccm_star_128_info;

/**@brief External variable declaration to the info structure for AES EAX mode with a 128-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aead_info_t g_nrf_crypto_aes_eax_128_info;

/**@brief External variable declaration to the info structure for AES EAX mode with a 192-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aead_info_t g_nrf_crypto_aes_eax_192_info;

/**@brief External variable declaration to the info structure for AES EAX mode with a 256-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aead_info_t g_nrf_crypto_aes_eax_256_info;

/**@brief External variable declaration to the info structure for AES GCM mode with a 128-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is enabled in the @ref sdk_config.
*
*/
extern const nrf_crypto_aead_info_t g_nrf_crypto_aes_gcm_128_info;

/**@brief External variable declaration to the info structure for AES GCM mode with a 192-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is enabled in the @ref sdk_config.
*
*/
extern const nrf_crypto_aead_info_t g_nrf_crypto_aes_gcm_192_info;

/**@brief External variable declaration to the info structure for AES GCM mode with a 256-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is enabled in the @ref sdk_config.
*
*/
extern const nrf_crypto_aead_info_t g_nrf_crypto_aes_gcm_256_info;

/**@brief External variable declaration to the info structure for CHACHA-POLY mode with a 256-bit
*         key.
*
* @note The variable is defined in the nrf_crypto backend that is enabled in the @ref sdk_config.
*
*/
extern const nrf_crypto_aead_info_t g_nrf_crypto_chacha_poly_256_info;


/**
 * @brief Context type for AEAD.
 *
 * @note The size of this type is scaled for the largest AEAD backend context that is
 *       enabled in @ref sdk_config.
 */
typedef nrf_crypto_backend_aead_context_t nrf_crypto_aead_context_t;


/**@brief Function for initializing the AEAD calculation context.
 *
 * @param[in] p_context     Pointer to the context object. It must be a context type associated with
 *                          the object provided in the p_info parameter or other memory that can
 *                          hold that context type.
 * @param[in] p_info        Pointer to structure holding information about: selected AES AEAD mode,
 *                          and key size.
 * @param[in] p_key         Pointer to AEAD mode key.
 *
 * @retval  NRF_SUCCESS  Context was successfully initialized.
 */
ret_code_t nrf_crypto_aead_init(nrf_crypto_aead_context_t * const    p_context,
                                nrf_crypto_aead_info_t const * const p_info,
                                uint8_t *                            p_key);

/**@brief Function for uninitializing the AEAD calculation context.
 *
 * @param[in] p_context  Pointer to the context object. It must be initialized before function call.
 *
 * @retval  NRF_SUCCESS  Context was successfully uninitialized.
 */
ret_code_t nrf_crypto_aead_uninit(void * const p_context);

/**@brief Integrated encryption / decryption function.
 *
 * @param[in]  p_context        Context object. Must be initialized before the call.
 * @param[in]  operation        Parameter indicating whether an encrypt (NRF_CRYPTO_ENCRYPT) or
 *                              a decrypt (NRF_CRYPTO_DECRYPT) operation shall be performed.
 * @param[in]  p_nonce          Pointer to nonce. For nonce_size == 0 p_nonce can be NULL.
 * @param[in]  nonce_size       Nonce byte size. Valid values for supported modes:
 *                                - CCM         [7 ... 13]
 *                                - CCM*        [13]
 *                                - EAX         nonce size can be any length
 *                                - GCM         nonce size can be any length
 *                                - CHACHA-POLY [12]
 * @param[in]  p_adata          Pointer to additional authenticated data (adata).
 * @param[in]  adata_size       Length of additional authenticated data in bytes.
 *                              For CHACHA-POLY mode must be > 0.
 * @param[in]  p_data_in        Pointer to the input data buffer for encryption or decryption.
 * @param[in]  data_in_size     Length of the data in p_data_in buffer in bytes. Size of the
 *                              p_data_out buffer must not be smaller than this value.
 *                              When selecting CC310 backend data_in_size value shall be limited
 *                              to 65535 bytes. Data out buffer must be at least the same length.
 * @param[out] p_data_out       Pointer to the output buffer where encrypted or decrypted data
 *                              will be stored. Must be at least 'data_in_size' bytes wide.
 *                                - GCM: On encryption, the p_data_out buffer can be the same as
 *                                       the p_data_in buffer.
 *                                       On decryption, the p_data_out buffer cannot be the same
 *                                       as p_data_in buffer. If buffers overlap, the p_data_out
 *                                       buffer must trail at least 8 bytes behind the p_data_in
 *                                       buffer.
 * @param[out] p_mac            Pointer to the MAC result buffer. Fo mac_size == 0 p_mac can be NULL.
 * @param[in]  mac_size         MAC byte size. Valid values for supported modes:
 *                                -CCM          [4, 6, 8, 10, 12, 14, 16]
 *                                -CCM*         [0, 4, 8, 16]
 *                                -EAX          [1 ... 16]
 *                                -GCM          [4 ... 16]
 *                                -CHACHA-POLY  [16]
 *
 * @retval  NRF_SUCCESS  Message was successfully encrypted.
 */
ret_code_t nrf_crypto_aead_crypt(nrf_crypto_aead_context_t * const p_context,
                                 nrf_crypto_operation_t            operation,
                                 uint8_t *                         p_nonce,
                                 uint8_t                           nonce_size,
                                 uint8_t *                         p_adata,
                                 size_t                            adata_size,
                                 uint8_t *                         p_data_in,
                                 size_t                            data_in_size,
                                 uint8_t *                         p_data_out,
                                 uint8_t *                         p_mac,
                                 uint8_t                           mac_size);

#ifdef __cplusplus
}
#endif

#endif // #if NRF_MODULE_ENABLED(NRF_CRYPTO) || defined(__SDK_DOXYGEN__)

/** @} */

#endif // NRF_CRYPTO_AEAD_H__
