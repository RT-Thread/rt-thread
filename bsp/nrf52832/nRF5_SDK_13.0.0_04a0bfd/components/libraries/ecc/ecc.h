/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
/**
 * @defgroup ecc Elliptic Curve Cryptography interface
 * @{
 * @ingroup app_common
 * @brief Elliptic Curve Cryptography interface
 */

#ifndef ECC_H__
#define ECC_H__

#include <stdint.h>
#include <stdbool.h>
#include "nordic_common.h"
#include "nrf_error.h"
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ECC_P256_SK_LEN 32
#define ECC_P256_PK_LEN 64

/**@brief Initialize the ECC module.
 *
 * @param[in]   rng   Use a random number generator.
 *
 * */
void ecc_init(bool rng);

/**@brief Create a public/private key pair.
 *
 * @param[out]  p_le_sk   Private key. Pointer must be aligned to a 4-byte boundary.
 * @param[out]  p_le_pk   Public key. Pointer must be aligned to a 4-byte boundary.
 *
 * @retval     NRF_SUCCESS              Key pair successfuly created.
 * @retval     NRF_ERROR_NULL           NULL pointer provided.
 * @retval     NRF_ERROR_INVALID_ADDR   Unaligned pointer provided.
 * @retval     NRF_ERROR_INTERNAL       Internal error during key generation.
 */
ret_code_t ecc_p256_keypair_gen(uint8_t *p_le_sk, uint8_t* p_le_pk);

/**@brief Create a public key from a provided private key.
 *
 * @param[in]   p_le_sk   Private key. Pointer must be aligned to a 4-byte boundary.
 * @param[out]  p_le_pk   Public key. Pointer must be aligned to a 4-byte boundary.
 *
 * @retval     NRF_SUCCESS              Public key successfuly created.
 * @retval     NRF_ERROR_NULL           NULL pointer provided.
 * @retval     NRF_ERROR_INVALID_ADDR   Unaligned pointer provided.
 * @retval     NRF_ERROR_INTERNAL       Internal error during key generation.
 */
ret_code_t ecc_p256_public_key_compute(uint8_t const *p_le_sk, uint8_t* p_le_pk);

/**@brief Create a shared secret from a provided public/private key pair.
 *
 * @param[in]   p_le_sk   Private key. Pointer must be aligned to a 4-byte boundary.
 * @param[in]   p_le_pk   Public key. Pointer must be aligned to a 4-byte boundary.
 * @param[out]  p_le_ss   Shared secret. Pointer must be aligned to a 4-byte boundary.
 *
 * @retval     NRF_SUCCESS              Shared secret successfuly created.
 * @retval     NRF_ERROR_NULL           NULL pointer provided.
 * @retval     NRF_ERROR_INVALID_ADDR   Unaligned pointer provided.
 * @retval     NRF_ERROR_INTERNAL       Internal error during key generation.
 */
ret_code_t ecc_p256_shared_secret_compute(uint8_t const *p_le_sk, uint8_t const * p_le_pk, uint8_t *p_le_ss);

/**@brief Sign a hash or digest using a private key.
 *
 * @param[in]   p_le_sk   Private key. Pointer must be aligned to a 4-byte boundary.
 * @param[in]   p_le_hash Hash. Pointer must be aligned to a 4-byte boundary.
 * @param[in]   hlen      Hash length in bytes.
 * @param[out]  p_le_sig  Signature. Pointer must be aligned to a 4-byte boundary.
 *
 * @retval     NRF_SUCCESS              Signature successfuly created.
 * @retval     NRF_ERROR_NULL           NULL pointer provided.
 * @retval     NRF_ERROR_INVALID_ADDR   Unaligned pointer provided.
 * @retval     NRF_ERROR_INTERNAL       Internal error during signature generation.
 */
ret_code_t ecc_p256_sign(uint8_t const *p_le_sk, uint8_t const * p_le_hash, uint32_t hlen, uint8_t *p_le_sig);

/**@brief Verify a signature using a public key.
 *
 * @param[in]   p_le_pk   Public key. Pointer must be aligned to a 4-byte boundary.
 * @param[in]   p_le_hash Hash. Pointer must be aligned to a 4-byte boundary.
 * @param[in]   hlen      Hash length in bytes.
 * @param[in]   p_le_sig  Signature. Pointer must be aligned to a 4-byte boundary.
 *
 * @retval     NRF_SUCCESS              Signature verified.
 * @retval     NRF_ERROR_INVALID_DATA   Signature failed verification.
 * @retval     NRF_ERROR_NULL           NULL pointer provided.
 * @retval     NRF_ERROR_INVALID_ADDR   Unaligned pointer provided.
 * @retval     NRF_ERROR_INTERNAL       Internal error during signature verification.
 */
ret_code_t ecc_p256_verify(uint8_t const *p_le_pk, uint8_t const * p_le_hash, uint32_t hlen, uint8_t const *p_le_sig);


#ifdef __cplusplus
}
#endif

#endif // ECC_H__

/** @} */
