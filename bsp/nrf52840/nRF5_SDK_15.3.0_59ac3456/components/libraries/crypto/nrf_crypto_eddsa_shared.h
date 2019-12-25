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

#ifndef NRF_CRYPTO_EDDSA_SHARED_H__
#define NRF_CRYPTO_EDDSA_SHARED_H__

#include <stdint.h>

#include "nordic_common.h"
#include "nrf_crypto_ecc.h"


#ifdef __cplusplus
extern "C" {
#endif


/** @internal @brief Sign a message using Edwards-curve Digital Signature Algorithm (EdDSA).
 *
 * @note All parameters provided to the backend are vefified in frontend. Verification includes
 * checking of NULL pointers, buffer size, initialization values. Front end also take full care of
 * common ECC key hearder @ref nrf_crypto_internal_ecc_key_header_t.
 *
 *  @param[in]     p_context         Pointer to temporary structure holding context information.
 *                                   If it is NULL, necessary data will be allocated with
 *                                   @ref NRF_CRYPTO_ALLOC and freed at the end of the function.
 *  @param[in]     p_private_key     Pointer to structure holding a private Ed25519 key.
 *                                   (Buffer size @ref NRF_CRYPTO_ECC_ED25519_RAW_PRIVATE_KEY_SIZE).
 *  @param[in]     p_message         Pointer to message to sign.
 *  @param[in]     message_size      Number of bytes in p_message.
 *  @param[out]    p_signature       Pointer to buffer where EdDSA signature will be put. Must be
 *                                   @ref NRF_CRYPTO_EDDSA_ED25519_SIGNATURE_SIZE bytes.
 *
 *  @return NRF_SUCCESS on success.
 */
ret_code_t nrf_crypto_backend_ed25519_sign(
    void                                  * p_context,
    nrf_crypto_ecc_private_key_t    const * p_private_key,
    uint8_t                         const * p_message,
    size_t                                  message_size,
    uint8_t                               * p_signature);


/** @internal @brief Verify a message using Edwards-curve Digital Signature Algorithm (EdDSA).
 *
 * @note All parameters provided to the backend are vefified in frontend. Verification includes
 * checking of NULL pointers, buffer size, initialization values. Front end also take full care of
 * common ECC key hearder @ref nrf_crypto_internal_ecc_key_header_t.
 *
 *  @param[in]     p_context       Pointer to temporary structure holding context information.
 *                                 If it is NULL, necessary data will be allocated with
 *                                 @ref NRF_CRYPTO_ALLOC and freed at the end of the function.
 *  @param[in]     p_public_key    Pointer to structure holding a public Ed25519 key.
 *                                 (Buffer size @ref NRF_CRYPTO_ECC_ED25519_RAW_PUBLIC_KEY_SIZE).
 *  @param[in]     p_message       Pointer to message to verify.
 *  @param[in]     message_size    Number of bytes in p_message.
 *  @param[in]     p_signature     Pointer to buffer containing EdDSA signature
 *                                 (@ref NRF_CRYPTO_EDDSA_ED25519_SIGNATURE_SIZE bytes).
 *
 *  @return NRF_SUCCESS on success.
 */
ret_code_t nrf_crypto_backend_ed25519_verify(
    void                              * p_context,
    nrf_crypto_ecc_public_key_t const * p_public_key,
    uint8_t                     const * p_message,
    size_t                              message_size,
    uint8_t                     const * p_signature);


#ifdef __cplusplus
}
#endif

#endif // NRF_CRYPTO_EDDSA_SHARED_H__
