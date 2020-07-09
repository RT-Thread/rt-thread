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

/**@brief Generic type to hold pointer to value and length
 */
typedef struct
{
    uint8_t * p_value;
    uint32_t  length;

} nrf_value_length_t;


/**@defgroup NRF_CRYPTO_CURVES Cryptographic curves
 * @brief Cryptographic curves that are available to the application.
 * @{ */
typedef enum
{
    NRF_CRYPTO_CURVE_INVALID        = 0x00,     //!< Invalid curve.
    NRF_CRYPTO_CURVE_SECP160R1      = 0x01,     //!< NIST 160-bit.
    NRF_CRYPTO_CURVE_SECP192R1      = 0x02,     //!< NIST 192-bit.
    NRF_CRYPTO_CURVE_SECP224R1      = 0x03,     //!< NIST 224-bit.
    NRF_CRYPTO_CURVE_SECP256R1      = 0x04,     //!< NIST 256-bit.
    NRF_CRYPTO_CURVE_SECP384R1      = 0x05,     //!< NIST 384-bit.
    NRF_CRYPTO_CURVE_SECP521R1      = 0x06,     //!< NIST 521-bit.
    NRF_CRYPTO_CURVE_SECP192K1      = 0x07,     //!< Koblitz 192-bit.
    NRF_CRYPTO_CURVE_SECP224K1      = 0x08,     //!< Koblitz 224-bit.
    NRF_CRYPTO_CURVE_SECP256K1      = 0x09,     //!< Koblitz 256-bit.
    NRF_CRYPTO_CURVE_CURVE25519     = 0x0A,     //!< Curve 25519.
} nrf_ecc_curve_type_t;
/** @}  */

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

/**@defgroup NRF_CRYPTO_ECDSA_SIGNATURE_SIZES ECDSA signature sizes.
 * @brief Sizes of different ECDSA signatures.
 * @{ */
#define NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP160R1   (40)
#define NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP192R1   (48)
#define NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP224R1   (56)
#define NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP256R1   (64)
#define NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP384R1   (96)
#define NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP521R1   (132)
#define NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP192K1   (48)
#define NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP224K1   (56)
#define NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP256K1   (64)
#define NRF_CRYPTO_ECDSA_SIGNATURE_MAX_SIZE NRF_CRYPTO_ECDSA_SIGNATURE_SIZE_SECP521R1
/** @}  */


/**@defgroup NRF_CRYPTO_ECC_PRIVATE_KEY_SIZES ECC private key sizes.
 * @brief Sizes of different elliptical curve cryptography private keys.
 * @{ */
#define NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP160R1   (20)
#define NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP192R1   (24)
#define NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP224R1   (28)
#define NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP256R1   (32)
#define NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP384R1   (48)
#define NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP521R1   (66)
#define NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP192K1   (24)
#define NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP224K1   (28)
#define NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP256K1   (32)
/** @}  */

/**@defgroup NRF_CRYPTO_ECC_PUBLIC_KEY_SIZES ECC public key sizes.
 * @brief Sizes of different elliptical curve cryptographic public keys.
 * @{ */
#define NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP160R1   (40)
#define NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP192R1   (48)
#define NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP224R1   (56)
#define NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP256R1   (64)
#define NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP384R1   (96)
#define NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP521R1   (132)
#define NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP192K1   (48)
#define NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP224K1   (56)
#define NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP256K1   (64)
/** @}  */

/**@defgroup NRF_CRYPTO_ECDH_SHARED_SECRET_SIZES ECDH shared secret sizes.
 * @brief Sizes of ECDH shared secret values.
 * @{ */
#define NRF_CRYPTO_ECDH_SHARED_SECRET_SIZE_SECP160R1   (20)
#define NRF_CRYPTO_ECDH_SHARED_SECRET_SIZE_SECP192R1   (24)
#define NRF_CRYPTO_ECDH_SHARED_SECRET_SIZE_SECP224R1   (28)
#define NRF_CRYPTO_ECDH_SHARED_SECRET_SIZE_SECP256R1   (32)
#define NRF_CRYPTO_ECDH_SHARED_SECRET_SIZE_SECP384R1   (48)
#define NRF_CRYPTO_ECDH_SHARED_SECRET_SIZE_SECP521R1   (66)
#define NRF_CRYPTO_ECDH_SHARED_SECRET_SIZE_SECP192K1   (24)
#define NRF_CRYPTO_ECDH_SHARED_SECRET_SIZE_SECP224K1   (28)
#define NRF_CRYPTO_ECDH_SHARED_SECRET_SIZE_SECP256K1   (32)
#define NRF_CRYPTO_ECDH_SHARED_SECRET_MAX_SIZE          NRF_CRYPTO_ECDH_SHARED_SECRET_SIZE_SECP521R1
/** @}  */




/** @brief Type definition for endianness.
 */
typedef enum
{
    NRF_CRYPTO_ENDIAN_LE            = 0x00,
    NRF_CRYPTO_ENDIAN_BE            = 0x01

} nrf_endian_type_t;


/** @brief Combined structure containing curve type, hash type and endian type.
 */
typedef struct
{
    nrf_ecc_curve_type_t    curve_type;
    nrf_hash_type_t         hash_type;
    nrf_endian_type_t       endian_type;

} nrf_crypto_signature_info_t;


/** @brief Combined structure containin curve type and endian type.
 */
typedef struct
{
    nrf_ecc_curve_type_t    curve_type;
    nrf_endian_type_t       endian_type;

} nrf_crypto_curve_info_t;


/** @brief Combined structure containing hash type and endian type.
 */
typedef struct
{
    nrf_hash_type_t         hash_type;
    nrf_endian_type_t       endian_type;

} nrf_crypto_hash_info_t;


/**@brief Combined to hold sizes used by ECDSA sign/verify.
 */
typedef struct
{
    uint32_t    public_key_size;    //!< Public key size.
    uint32_t    private_key_size;   //!< Private key size.
    uint32_t    signature_size;     //!< Signature size.
    uint32_t    hash_size;          //!< Hash size.
} nrf_crypto_ecdsa_sizes_t;


/**@brief Structure holding hash size according to algorithm.
 */
typedef struct
{
    uint32_t        hash_size;
} nrf_crypto_hash_sizes_t;


/**@brief Macro to declare a cryptographic curve used in
 *        BLE Secure Connections (LESC).
 */
#define BLE_LESC_CURVE_TYPE_INFO                    \
(nrf_crypto_curve_info_t)                           \
{                                                   \
    .curve_type     = NRF_CRYPTO_CURVE_SECP256R1,   \
    .endian_type    = NRF_CRYPTO_ENDIAN_LE          \
}

#ifdef __cplusplus
}
#endif

/**@} */

#endif // #ifndef NRF_CRYPTO_TYPES_H__
