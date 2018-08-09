/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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

#ifndef NRF_CRYPTO_TYPES_H__
#define NRF_CRYPTO_TYPES_H__

/** @file
 *
 * @defgroup nrf_crypto_types Commonly shared types
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides definitions of commonly shared cryptographic types like hashes and curves used in the nrf_crypto APIs.
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Hashing algorithms that are available through nrf_crypto.
 *
 * @note    All cryptographic hash types may not be available through the nrf_crypto backend.
 */
typedef enum
{
    NRF_CRYPTO_HASH_TYPE_INVALID    = 0x00,        //!< Invalid hashing algorithm.
    NRF_CRYPTO_HASH_TYPE_MD5        = 0x01,        //!< MD5.
    NRF_CRYPTO_HASH_TYPE_SHA1       = 0x03,        //!< SHA-1.
    NRF_CRYPTO_HASH_TYPE_SHA224     = 0x04,        //!< SHA-224 (SHA-2).
    NRF_CRYPTO_HASH_TYPE_SHA256     = 0x05,        //!< SHA-256 (SHA-2).
    NRF_CRYPTO_HASH_TYPE_SHA384     = 0x06,        //!< SHA-384 (SHA-2).
    NRF_CRYPTO_HASH_TYPE_SHA512     = 0x07,        //!< SHA-512 (SHA-2).

} nrf_hash_type_t;

/**@defgroup NRF_CRYPTO_HASH_SIZES Cryptographic hash sizes
 * @brief Sizes of different cryptographic hashes.
 * @{ */
#define NRF_CRYPTO_HASH_SIZE_MD5        (20)
#define NRF_CRYPTO_HASH_SIZE_SHA1       (20)
#define NRF_CRYPTO_HASH_SIZE_SHA224     (28)
#define NRF_CRYPTO_HASH_SIZE_SHA256     (32)
#define NRF_CRYPTO_HASH_SIZE_SHA384     (48)
#define NRF_CRYPTO_HASH_SIZE_SHA512     (64)
/** @}  */


/**@brief Type definition for key size.
 */
typedef enum
{
    NRF_CRYPTO_KEY_SIZE_128 = 128,
    NRF_CRYPTO_KEY_SIZE_192 = 192,
    NRF_CRYPTO_KEY_SIZE_256 = 256
} nrf_crypto_key_size_id_t;

/**@brief Type specifying whether decrypt or encrypt operation shall be performed.
 */
typedef enum
{
    NRF_CRYPTO_DECRYPT       = 0,
    NRF_CRYPTO_ENCRYPT       = 1,
    NRF_CRYPTO_MAC_CALCULATE = 2
} nrf_crypto_operation_t;

#define NRF_CRYPTO_AES_BLOCK_SIZE   (16u) // 16 bytes

#ifdef __cplusplus
}
#endif

/**@} */

#endif // #ifndef NRF_CRYPTO_TYPES_H__
