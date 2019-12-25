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

#ifndef NRF_CRYPTO_EDDSA_H__
#define NRF_CRYPTO_EDDSA_H__

/** @file
 *
 * @defgroup nrf_crypto_eddsa Edwards-curve Digital Signature Algorithm (EdDSA)
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides functionality related to Edwards-curve Digital Signature Algorithm (EdDSA).
 */

#include <stdint.h>
#include <stddef.h>

#include "nrf_crypto_error.h"
#include "nrf_crypto_ecc.h"
#include "nrf_crypto_eddsa_shared.h"
#include "nrf_crypto_eddsa_backend.h"

#ifdef __cplusplus
extern "C" {
#endif


/**< @brief Size of the EdDSA Ed25519 signature. */
#define NRF_CRYPTO_EDDSA_ED25519_SIGNATURE_SIZE    (2 * 256 / 8)

/**< @brief Context used to store temporary data during the signing with EdDSA Ed25519. */
typedef nrf_crypto_backend_ed25519_sign_context_t nrf_crypto_eddsa_sign_context_t;

/**< @brief Context used to store temporary data during the verification with EdDSA Ed25519. */
typedef nrf_crypto_backend_ed25519_verify_context_t nrf_crypto_eddsa_verify_context_t;


/** @brief Sign a message using Edwards-curve Digital Signature Algorithm (EdDSA).
 *
 *  @param[in]     p_context         Pointer to the temporary structure that holds context information.
 *                                   If it is NULL, the required data is allocated with
 *                                   @ref NRF_CRYPTO_ALLOC and freed at the end of the function.
 *  @param[in]     p_private_key     Pointer to the structure that holds a private key.
 *  @param[in]     p_message         Pointer to the message to sign.
 *  @param[in]     message_size      Number of bytes in p_message.
 *  @param[out]    p_signature       Pointer to the array where EdDSA signature is to be put. Minimum bytes required: @ref NRF_CRYPTO_EDDSA_ED25519_SIGNATURE_SIZE.
 *  @param[in,out] p_signature_size  Pointer to the maximum number of bytes that @p p_signature buffer
 *                                   can hold on input, and to the actual number of bytes used by the
 *                                   data on output (@ref NRF_CRYPTO_EDDSA_ED25519_SIGNATURE_SIZE).
 * 
 *  @return NRF_SUCCESS on success.
 */
ret_code_t nrf_crypto_eddsa_sign(nrf_crypto_eddsa_sign_context_t          * p_context,
                                 nrf_crypto_ecc_private_key_t       const * p_private_key,
                                 uint8_t                            const * p_message,
                                 size_t                                     message_size,
                                 uint8_t                                  * p_signature,
                                 size_t                                   * p_signature_size);


/** @brief Verify a message using Edwards-curve Digital Signature Algorithm (EdDSA).
 *
 *  @param[in]     p_context       Pointer to the temporary structure that holds context information.
 *                                 If it is NULL, necessary data is allocated with
 *                                 @ref NRF_CRYPTO_ALLOC and freed at the end of the function.
 *  @param[in]     p_public_key    Pointer to the structure that holds a public key.
 *  @param[in]     p_message       Pointer to the message to verify.
 *  @param[in]     message_size    Number of bytes in p_message.
 *  @param[in]     p_signature     Pointer to the array that contains EdDSA signature.
 *  @param[in]     signature_size  Number of bytes in p_signature.
 *
 *  @return NRF_SUCCESS on success.
 */
ret_code_t nrf_crypto_eddsa_verify(nrf_crypto_eddsa_verify_context_t          * p_context,
                                   nrf_crypto_ecc_public_key_t          const * p_public_key,
                                   uint8_t                              const * p_message,
                                   size_t                                       message_size,
                                   uint8_t                              const * p_signature,
                                   size_t                                       signature_size);


#ifdef __cplusplus
}
#endif

/** @}
 */

#endif // NRF_CRYPTO_EDDSA_H__
