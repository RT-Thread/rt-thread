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

#ifndef NRF_CRYPTO_HKDF_H__
#define NRF_CRYPTO_HKDF_H__

/** @file
 *
 * @defgroup nrf_crypto_hkdf HMAC based Key Derivation Function (HKDF) related functions
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides functions to generate HMAC based Key Derivation Function (HKDF).
 *
 * @details Provides functions to generate HMAC based Key Derivation Function (HKDF) using
 * one of the supported hash algorithms. This layer is independent of backend crypto library.
 * The HKDF module does not have a backend configuration, as it uses the nrf_crypto_hmac API,
 * including the backend configured for HMAC in @ref sdk_config.
 */


#include <stdint.h>
#include "sdk_common.h"
#include "nrf_crypto_hmac.h"
#include "nrf_crypto_hkdf.h"
#include "nrf_crypto_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Enumeration of HKDF modes.
 */
typedef enum
{
    NRF_CRYPTO_HKDF_EXTRACT_AND_EXPAND, //!< HKDF Extract and expand mode (normal).
    NRF_CRYPTO_HKDF_EXPAND_ONLY         //!< HKDF Expand only mode.
} nrf_crypto_hkdf_mode_t;


/**
 * @brief Integrated HKDF calculation function
 *
 * @details This HKDF calculation function uses the nrf_crypto HMAC frontend directly.
 *          The backend is selected by configuring the HMAC backend in @ref sdk_config.
 *
 * @param[in,out]  p_context        Pointer to context structure. Context memory will be
 *                                  allocated internally if the context pointer is NULL.
 * @param[in]      p_info           Pointer to static info structure. This defines the algorithm.
 *                                  This should be either @ref g_nrf_crypto_hmac_sha256_info or
 *                                  @ref g_nrf_crypto_hmac_sha512_info.
 * @param[out]     p_output_key     Pointer to buffer to hold the output key material.
 * @param[in,out]  p_output_key_size Pointer to the length of the wanted output key material as input
 *                                  and actual length of the output material as output. Can be any
 *                                  number between 1 and the hash digest size multiplied by 255
 *                                  (65280 for SHA-256 or 130560 for SHA-512). The p_output_key
 *                                  buffer must be large enough to hold this value.
 * @param[in]      p_input_key      Pointer to buffer holding the input key material.
 * @param[in]      input_key_size   Length of the input key material.
 * @param[in]      p_salt           Pointer to buffer of nonsecret random salt data. Set to NULL in
 *                                  order to use the default salt defined by RFC 5869 (all zero
 *                                  array of hash digest size) or if salt is not used (expand only).
 * @param[in]      salt_size        Length of the salt. Must be > 0 unless default salt is used, or
 *                                  in case mode is set to @ref NRF_CRYPTO_HKDF_EXPAND_ONLY.
 * @param[in]      p_ainfo          Pointer to optional application specific information.
 *                                  (set to NULL and set ainfo_size to 0 if unused).
 * @param[in]      ainfo_size       Length of the additional information.
 * @param[in]      mode             Set to @ref NRF_CRYPTO_HKDF_EXTRACT_AND_EXPAND for normal mode.
 *                                  Alternatively, set to @ref NRF_CRYPTO_HKDF_EXPAND_ONLY to skip
 *                                  the extraction step.
 *
 * @retval  NRF_SUCCESS                     Output key material hash was successfully calculated.
 * @retval  NRF_ERROR_CRYPTO_INPUT_NULL     If p_input_key was NULL.
 * @retval  NRF_ERROR_CRYPTO_INPUT_LENGTH   If input_key_size or salt_size was invalid.
 * @retval  NRF_ERROR_CRYPTO_OUTPUT_NULL    If p_output_key_sizen was NULL.
 * @retval  NRF_ERROR_CRYPTO_OUTPUT_LENGTH  If *p_output_key_size is 0.
 * @retval  NRF_ERROR_CRYPTO_ALLOC_FAILED   Unable to allocate memory for the context.
 * @retval  NRF_ERROR_CRYPTO_INTERNAL       An error occurred in the crypto backend.
 * @retval  NRF_ERROR_CRYPTO_BUSY           The function could not be called because the
 *                                          nrf_crypto backend was busy. Please rerun the
 *                                          cryptographic routine at a later time. CC310 only.
 */
ret_code_t nrf_crypto_hkdf_calculate(nrf_crypto_hmac_context_t      * const p_context,
                                     nrf_crypto_hmac_info_t         const * p_info,
                                     uint8_t                        * const p_output_key,
                                     size_t                         * const p_output_key_size,
                                     uint8_t                  const * const p_input_key,
                                     size_t                                 input_key_size,
                                     uint8_t                        const * p_salt,
                                     size_t                                 salt_size,
                                     uint8_t                  const * const p_ainfo,
                                     size_t                                 ainfo_size,
                                     nrf_crypto_hkdf_mode_t                 mode);


#ifdef __cplusplus
}
#endif

/**@} */

#endif // #ifndef NRF_CRYPTO_HKDF_H__
