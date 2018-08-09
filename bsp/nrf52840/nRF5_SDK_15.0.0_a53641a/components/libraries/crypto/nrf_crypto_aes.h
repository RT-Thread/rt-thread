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

#ifndef NRF_CRYPTO_AES_H__
#define NRF_CRYPTO_AES_H__

/** @file
 *
 * @defgroup nrf_crypto_aes AES related functions
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides AES related functionality through nrf_crypto.
 */
#include "sdk_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) || defined(__SDK_DOXYGEN__)

#include <stdint.h>
#include "nrf_crypto_types.h"
#include "nrf_crypto_aes_shared.h"
#include "nrf_crypto_aes_backend.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief External variable declaration to the info structure for AES CBC mode with a 128-bit key.
*         No padding.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cbc_128_info;

/**@brief External variable declaration to the info structure for AES CBC mode with a 192-bit key.
*         No padding.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cbc_192_info;

/**@brief External variable declaration to the info structure for AES CBC mode with a 256-bit key.
*         No padding.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cbc_256_info;

/**@brief External variable declaration to the info structure for AES CBC mode with a 128-bit key.
*         Padding pkcs7 enabled.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cbc_128_pad_pkcs7_info;

/**@brief External variable declaration to the info structure for AES CBC mode with a 192-bit key.
*         Padding pkcs7 enabled.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cbc_192_pad_pkcs7_info;

/**@brief External variable declaration to the info structure for AES CBC mode with a 256-bit key.
*         Padding pkcs7 enabled.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cbc_256_pad_pkcs7_info;

/**@brief External variable declaration to the info structure for AES CTR mode with a 128-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_ctr_128_info;

/**@brief External variable declaration to the info structure for AES CTR mode with a 192-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_ctr_192_info;

/**@brief External variable declaration to the info structure for AES CTR mode with a 256-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_ctr_256_info;

/**@brief External variable declaration to the info structure for AES CFB mode with a 128-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cfb_128_info;

/**@brief External variable declaration to the info structure for AES CFB mode with a 192-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cfb_192_info;

/**@brief External variable declaration to the info structure for AES CFB mode with a 256-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cfb_256_info;

/**@brief External variable declaration to the info structure for AES ECB mode with a 128-bit key.
*         No padding.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_ecb_128_info;

/**@brief External variable declaration to the info structure for AES ECB mode with a 192-bit key.
*         No padding.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_ecb_192_info;

/**@brief External variable declaration to the info structure for AES ECB mode with a 256-bit key.
*         No padding.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_ecb_256_info;

/**@brief External variable declaration to the info structure for AES ECB mode with a 128-bit key.
*         Padding pkcs7 enabled.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_ecb_128_pad_pkcs7_info;

/**@brief External variable declaration to the info structure for AES ECB mode with a 192-bit key.
*         Padding pkcs7 enabled.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_ecb_192_pad_pkcs7_info;

/**@brief External variable declaration to the info structure for AES ECB mode with a 256-bit key.
*         Padding pkcs7 enabled.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_ecb_256_pad_pkcs7_info;

/**@brief External variable declaration to the info structure for AES CBC MAC mode with a 128-bit
*         key.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cbc_mac_128_info;

/**@brief External variable declaration to the info structure for AES CBC MAC mode with a 192-bit
*         key.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cbc_mac_192_info;

/**@brief External variable declaration to the info structure for AES CBC MAC mode with a 256-bit
*         key.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cbc_mac_256_info;

/**@brief External variable declaration to the info structure for AES CBC MAC mode with a 128-bit
*         key.
*         Padding pkcs7 enabled.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cbc_mac_128_pad_pkcs7_info;

/**@brief External variable declaration to the info structure for AES CBC MAC mode with a 192-bit
*         key.
*         Padding pkcs7 enabled.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cbc_mac_192_pad_pkcs7_info;

/**@brief External variable declaration to the info structure for AES CBC MAC mode with a 256-bit
*         key.
*         Padding pkcs7 enabled.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cbc_mac_256_pad_pkcs7_info;


/**@brief External variable declaration to the info structure for AES CMAC mode with a 128-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cmac_128_info;

/**@brief External variable declaration to the info structure for AES CMAC mode with a 192-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cmac_192_info;

/**@brief External variable declaration to the info structure for AES CMAC mode with a 256-bit key.
*
* @note The variable is defined in the nrf_crypto backend that is
*       enabled in the @c sdk_config file.
*
*/
extern const nrf_crypto_aes_info_t g_nrf_crypto_aes_cmac_256_info;

/**
 * @brief Context type for AES.
 *
 * @note The size of this type is scaled for the largest AES backend context that is
 *       enabled in @ref sdk_config.
 */
typedef nrf_crypto_backend_aes_context_t nrf_crypto_aes_context_t;

/**@brief Function for initializing the AES context.
 *
 * @param[in]  p_context        Pointer to the context object. It must be a context type associated
 *                              with the object provided in the p_info parameter or other memory
 *                              that can hold that context type.
 * @param[in]  p_info           Pointer to structure holding information about: selected AES mode,
 *                              key size, and padding.
 * @param[in]  operation        Parameter indicating whether an encrypt (NRF_CRYPTO_ENCRYPT),
 *                              a decrypt (NRF_CRYPTO_DECRYPT) or MAC calculation
 *                              (NRF_CRYPTO_MAC_CALCULATE) operation shall be performed.
 *
 * @return NRF_SUCCESS on success.
 */
ret_code_t nrf_crypto_aes_init(nrf_crypto_aes_context_t * const    p_context,
                               nrf_crypto_aes_info_t const * const p_info,
                               nrf_crypto_operation_t              operation);

/**@brief Internal function for uninitializing the AES context.
 *
 * @param[in]  p_context    Context object. Must be initialized before the call.
 *
 * @return NRF_SUCCESS on success.
 */
ret_code_t nrf_crypto_aes_uninit(nrf_crypto_aes_context_t * const p_context);

/**@brief Function for setting the AES key.
 *
 * @param[in]  p_context    Context object. Must be initialized before the call.
 * @param[in]  p_key        Pointer to the AES key. This buffer will be copied and there is no need
 *                          to keep it by the user.
 *
 * @return NRF_SUCCESS on success.
 */
ret_code_t nrf_crypto_aes_key_set(nrf_crypto_aes_context_t * const p_context, uint8_t * p_key);

/**@brief Function for setting an AES IV or a counter for AES modes which are using it.
 *
 * @param[in]  p_context    Context object. Must be initialized before the call.
 * @param[in]  p_iv         Pointer to a buffer of the IV or a counter. This buffer will be copied
 *                          and there is no need to keep it by the user.
 *
 * @return NRF_SUCCESS on success.
 */
ret_code_t nrf_crypto_aes_iv_set(nrf_crypto_aes_context_t * const p_context, uint8_t * p_iv);

/**@brief Function for getting an AES IV or a counter for mode which is supporting it.
 *
 * @param[in]  p_context    Context object. Must be initialized before the call.
 * @param[out] p_iv         Pointer to a buffer of the IV or a counter.
 *
 * @return NRF_SUCCESS on success.
 */
ret_code_t nrf_crypto_aes_iv_get(nrf_crypto_aes_context_t * const p_context, uint8_t * p_iv);

/**@brief AES update function for encryption, decryption and MAC calculation. It can be called once
 *  on the whole data block, or as many times as needed, until all the input data is processed.
 *  Functions: @ref nrf_crypto_aes_init, @ref nrf_crypto_aes_key_set, and, for some ciphers,
 *  @ref nrf_crypto_aes_iv_set, must be called before call to this API with the same context.

 *
 * @param[in]  p_context    Context object. Must be initialized before the call.
 * @param[in]  p_data_in    Pointer to the input buffer to the AES.
 * @param[in]  data_size    Size of the data to be processed in bytes.
 *                          For all modes except CFB it must be multiple of 16 bytes.
 * @param[out] p_data_out   Pointer to the output buffer.
 *
 * @return NRF_SUCCESS on success.
 */
ret_code_t nrf_crypto_aes_update(nrf_crypto_aes_context_t * const p_context,
                                 uint8_t *                        p_data_in,
                                 size_t                           data_size,
                                 uint8_t *                        p_data_out);


/**@brief Function processes the last data block if needed and finalizes the AES operation (ie. adds
 *  padding) and produces operation results (for MAC operations).
 *  Functions: @ref nrf_crypto_aes_init, @ref nrf_crypto_aes_key_set, and, for some ciphers,
 *  @ref nrf_crypto_aes_iv_set, must be called before call to this API with the same context.
 *
 *  Upon successful operation function will deinitialize the context but for some ciphers it will be
 *  possible to read IV. In order to fully deinitialize context you must call
 *  @ref nrf_crypto_aes_uninit.
 *
 * @param[in]     p_context         Context object. Must be initialized before the call.
 * @param[in]     p_data_in         Pointer to the input buffer to the AES.
 * @param[in]     data_size         Size of the data to be processed in bytes.
 * @param[out]    p_data_out        Pointer to the output buffer.
 *                                  When padding is set:
 *                                    - The size of p_data_out buffer must have extra space for
 *                                      padding. Otherwise, the function will return an error:
 *                                      NRF_ERROR_CRYPTO_OUTPUT_LENGTH.
 *                                    - When text_size is multiple of 16 bytes, p_text_out must be
 *                                      allocated with size equal to text_size + an additional block
 *                                      (i.e 16 bytes for padding).
 *                                    - When text_size is not a multiple of 16 bytes, p_text_out
 *                                      must be allocated with size aligned to the next full 16
 *                                       bytes block (i.e. 1 - 15 bytes for padding).
 * @param[in,out] p_data_out_size   IN:
 *                                      Size of the p_data_out buffer.
 *                                  OUT:
 *                                      Upon successfull function execution value will be updated
 *                                      with number of signifacnt bytes in p_data_out buffer.
 *                                      On decryption with padding function will result in a value
 *                                      without padded bytes.
 *
 * @return NRF_SUCCESS on success.
 */
ret_code_t nrf_crypto_aes_finalize(nrf_crypto_aes_context_t * const p_context,
                                   uint8_t *                        p_data_in,
                                   size_t                           data_size,
                                   uint8_t *                        p_data_out,
                                   size_t *                         p_data_out_size);




/**@brief AES integrated function for encryption, decryption and MAC calculation.
 *  It should be called once on the whole data block.
 *
 * @param[in]     p_context         Context object. If NULL, memory will be dynamically allocated.
 * @param[in]     p_info            Pointer to structure holding information about: selected AES
 *                                  mode, key size, and padding.
 * @param[in]     operation         Parameter indicating whether an encrypt (NRF_CRYPTO_ENCRYPT),
 *                                  a decrypt (NRF_CRYPTO_DECRYPT) or MAC calculation
 *                                  (NRF_CRYPTO_MAC_CALCULATE) operation shall be performed.
 * @param[in]     p_key             Pointer to the AES key. This buffer will be copied and there is
 *                                  no need to keep it by the user.
 * @param[in]     p_iv              Pointer to a buffer of the IV or a counter. This buffer will be
 *                                  copied and there is no need to keep it by the user.
 *                                  Can be NULL for ECB and CMAC.
 * @param[in]     p_data_in         Pointer to the input buffer to the AES.
 * @param[in]     data_size         Size of the data to be processed in bytes.
 * @param[out]    p_data_out        Pointer to the output buffer.
 *                                  When padding is set:
 *                                    - The size of p_data_out buffer must have extra space for
 *                                      padding. Otherwise, the function will return an error:
 *                                      NRF_ERROR_CRYPTO_OUTPUT_LENGTH.
 *                                    - When text_size is multiple of 16 bytes, p_text_out must be
 *                                      allocated with size equal to text_size + an additional block
 *                                      (i.e 16 bytes for padding).
 *                                    - When text_size is not a multiple of 16 bytes, p_text_out
 *                                      must be allocated with size aligned to the next full 16
 *                                      bytes block (i.e. 1 - 15 bytes for padding).
 * @param[in,out] p_data_out_size   IN:
 *                                      Size of the p_data_out buffer.
 *                                  OUT:
 *                                      Upon successfull function execution value will be updated
 *                                      with number of signifacnt bytes in p_data_out buffer.
 *                                      On decryption function will result in a value without padded
 *                                      bytes.
 *
 * @return NRF_SUCCESS on success.
 */
ret_code_t nrf_crypto_aes_crypt(nrf_crypto_aes_context_t * const    p_context,
                                nrf_crypto_aes_info_t const * const p_info,
                                nrf_crypto_operation_t              operation,
                                uint8_t *                           p_key,
                                uint8_t *                           p_iv,
                                uint8_t *                           p_data_in,
                                size_t                              data_size,
                                uint8_t *                           p_data_out,
                                size_t *                            p_data_out_size);
#ifdef __cplusplus
}
#endif

#endif // #if NRF_MODULE_ENABLED(NRF_CRYPTO) || defined(__SDK_DOXYGEN__)

/** @} */

#endif // #ifndef NRF_CRYPTO_AES_H__
