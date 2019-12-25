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

#ifndef NRF_CRYPTO_ECC_H__
#define NRF_CRYPTO_ECC_H__

/** @addtogroup nrf_crypto
 *  @{
 *  @addtogroup nrf_crypto_ecc Elliptic Curve Cryptography Key Management
 *  @{
 *  @brief Provides elliptic curve cryptography API for public and private key management.
 *
 *  @addtogroup nrf_crypto_ecc_secp160r1   Definitions specific to secp160r1 (NIST 160-bit)
 *  @addtogroup nrf_crypto_ecc_secp160r2   Definitions specific to secp160r2 (NIST 160-bit)
 *  @addtogroup nrf_crypto_ecc_secp192r1   Definitions specific to secp192r1 (NIST 192-bit)
 *  @addtogroup nrf_crypto_ecc_secp224r1   Definitions specific to secp224r1 (NIST 224-bit)
 *  @addtogroup nrf_crypto_ecc_secp256r1   Definitions specific to secp256r1 (NIST 256-bit)
 *  @addtogroup nrf_crypto_ecc_secp384r1   Definitions specific to secp384r1 (NIST 384-bit)
 *  @addtogroup nrf_crypto_ecc_secp521r1   Definitions specific to secp521r1 (NIST 521-bit)
 *  @addtogroup nrf_crypto_ecc_secp160k1   Definitions specific to secp160k1 (Koblitz 160-bit)
 *  @addtogroup nrf_crypto_ecc_secp192k1   Definitions specific to secp192k1 (Koblitz 192-bit)
 *  @addtogroup nrf_crypto_ecc_secp224k1   Definitions specific to secp224k1 (Koblitz 224-bit)
 *  @addtogroup nrf_crypto_ecc_secp256k1   Definitions specific to secp256k1 (Koblitz 256-bit)
 *  @addtogroup nrf_crypto_ecc_bp256r1     Definitions specific to bp256r1 (Brainpool 256-bit)
 *  @addtogroup nrf_crypto_ecc_bp384r1     Definitions specific to bp384r1 (Brainpool 384-bit)
 *  @addtogroup nrf_crypto_ecc_bp512r1     Definitions specific to bp512r1 (Brainpool 512-bit)
 *  @addtogroup nrf_crypto_ecc_curve25519  Definitions specific to Curve25519
 *  @addtogroup nrf_crypto_ecc_ed25519     Definitions specific to Ed25519
 */

#include <stdint.h>
#include <stddef.h>

#include "nrf_crypto_error.h"
#include "nrf_crypto_ecc_shared.h"
#include "nrf_crypto_ecc_backend.h"


#ifdef __cplusplus
extern "C" {
#endif


#if defined(__SDK_DOXYGEN__)
#define NRF_CRYPTO_ECC_SECP160R1_ENABLED  1  /**< @brief Defined as 1 if secp160r1 (NIST 160-bit) is enabled in any of the backends and it is usable in the API, 0 otherwise.    @ingroup nrf_crypto_ecc_secp160r1 */
#define NRF_CRYPTO_ECC_SECP160R2_ENABLED  1  /**< @brief Defined as 1 if secp160r2 (NIST 160-bit) is enabled in any of the backends and it is usable in the API, 0 otherwise.    @ingroup nrf_crypto_ecc_secp160r2 */
#define NRF_CRYPTO_ECC_SECP192R1_ENABLED  1  /**< @brief Defined as 1 if secp192r1 (NIST 192-bit) is enabled in any of the backends and it is usable in the API, 0 otherwise.    @ingroup nrf_crypto_ecc_secp192r1 */
#define NRF_CRYPTO_ECC_SECP224R1_ENABLED  1  /**< @brief Defined as 1 if secp224r1 (NIST 224-bit) is enabled in any of the backends and it is usable in the API, 0 otherwise.    @ingroup nrf_crypto_ecc_secp224r1 */
#define NRF_CRYPTO_ECC_SECP256R1_ENABLED  1  /**< @brief Defined as 1 if secp256r1 (NIST 256-bit) is enabled in any of the backends and it is usable in the API, 0 otherwise.    @ingroup nrf_crypto_ecc_secp256r1 */
#define NRF_CRYPTO_ECC_SECP384R1_ENABLED  1  /**< @brief Defined as 1 if secp384r1 (NIST 384-bit) is enabled in any of the backends and it is usable in the API, 0 otherwise.    @ingroup nrf_crypto_ecc_secp384r1 */
#define NRF_CRYPTO_ECC_SECP521R1_ENABLED  1  /**< @brief Defined as 1 if secp521r1 (NIST 521-bit) is enabled in any of the backends and it is usable in the API, 0 otherwise.    @ingroup nrf_crypto_ecc_secp521r1 */
#define NRF_CRYPTO_ECC_SECP160K1_ENABLED  1  /**< @brief Defined as 1 if secp160k1 (Koblitz 160-bit) is enabled in any of the backends and it is usable in the API, 0 otherwise. @ingroup nrf_crypto_ecc_secp160k1 */
#define NRF_CRYPTO_ECC_SECP192K1_ENABLED  1  /**< @brief Defined as 1 if secp192k1 (Koblitz 192-bit) is enabled in any of the backends and it is usable in the API, 0 otherwise. @ingroup nrf_crypto_ecc_secp192k1 */
#define NRF_CRYPTO_ECC_SECP224K1_ENABLED  1  /**< @brief Defined as 1 if secp224k1 (Koblitz 224-bit) is enabled in any of the backends and it is usable in the API, 0 otherwise. @ingroup nrf_crypto_ecc_secp224k1 */
#define NRF_CRYPTO_ECC_SECP256K1_ENABLED  1  /**< @brief Defined as 1 if secp256k1 (Koblitz 256-bit) is enabled in any of the backends and it is usable in the API, 0 otherwise. @ingroup nrf_crypto_ecc_secp256k1 */
#define NRF_CRYPTO_ECC_BP256R1_ENABLED    1  /**< @brief Defined as 1 if bp256r1 (Brainpool 256-bit) is enabled in any of the backends and it is usable in the API, 0 otherwise. @ingroup nrf_crypto_ecc_bp256r1 */
#define NRF_CRYPTO_ECC_BP384R1_ENABLED    1  /**< @brief Defined as 1 if bp384r1 (Brainpool 384-bit) is enabled in any of the backends and it is usable in the API, 0 otherwise. @ingroup nrf_crypto_ecc_bp384r1 */
#define NRF_CRYPTO_ECC_BP512R1_ENABLED    1  /**< @brief Defined as 1 if bp512r1 (Brainpool 512-bit) is enabled in any of the backends and it is usable in the API, 0 otherwise. @ingroup nrf_crypto_ecc_bp512r1 */
#define NRF_CRYPTO_ECC_CURVE25519_ENABLED 1  /**< @brief Defined as 1 if Curve25519 is enabled in any of the backends and it is usable in the API, 0 otherwise.                  @ingroup nrf_crypto_ecc_curve25519 */
#define NRF_CRYPTO_ECC_ED25519_ENABLED    1  /**< @brief Defined as 1 if Ed25519 is enabled in any of the backends and it is usable in the API, 0 otherwise.                     @ingroup nrf_crypto_ecc_ed25519 */
#endif


#define NRF_CRYPTO_ECC_SECP160R1_RAW_PRIVATE_KEY_SIZE  (160 / 8)      /**< @brief Raw private key size for secp160r1 (NIST 160-bit).         @ingroup nrf_crypto_ecc_secp160r1 */
#define NRF_CRYPTO_ECC_SECP160R2_RAW_PRIVATE_KEY_SIZE  (160 / 8)      /**< @brief Raw private key size for secp160r2 (NIST 160-bit).         @ingroup nrf_crypto_ecc_secp160r2 */
#define NRF_CRYPTO_ECC_SECP192R1_RAW_PRIVATE_KEY_SIZE  (192 / 8)      /**< @brief Raw private key size for secp192r1 (NIST 192-bit).         @ingroup nrf_crypto_ecc_secp192r1 */
#define NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE  (224 / 8)      /**< @brief Raw private key size for secp224r1 (NIST 224-bit).         @ingroup nrf_crypto_ecc_secp224r1 */
#define NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE  (256 / 8)      /**< @brief Raw private key size for secp256r1 (NIST 256-bit).         @ingroup nrf_crypto_ecc_secp256r1 */
#define NRF_CRYPTO_ECC_SECP384R1_RAW_PRIVATE_KEY_SIZE  (384 / 8)      /**< @brief Raw private key size for secp384r1 (NIST 384-bit).         @ingroup nrf_crypto_ecc_secp384r1 */
#define NRF_CRYPTO_ECC_SECP521R1_RAW_PRIVATE_KEY_SIZE  (528 / 8)      /**< @brief Raw private key size for secp521r1 (NIST 521-bit).         @ingroup nrf_crypto_ecc_secp521r1 */
#define NRF_CRYPTO_ECC_SECP160K1_RAW_PRIVATE_KEY_SIZE  (160 / 8)      /**< @brief Raw private key size for secp160k1 (Koblitz 160-bit).      @ingroup nrf_crypto_ecc_secp160k1 */
#define NRF_CRYPTO_ECC_SECP192K1_RAW_PRIVATE_KEY_SIZE  (192 / 8)      /**< @brief Raw private key size for secp192k1 (Koblitz 192-bit).      @ingroup nrf_crypto_ecc_secp192k1 */
#define NRF_CRYPTO_ECC_SECP224K1_RAW_PRIVATE_KEY_SIZE  (224 / 8)      /**< @brief Raw private key size for secp224k1 (Koblitz 224-bit).      @ingroup nrf_crypto_ecc_secp224k1 */
#define NRF_CRYPTO_ECC_SECP256K1_RAW_PRIVATE_KEY_SIZE  (256 / 8)      /**< @brief Raw private key size for secp256k1 (Koblitz 256-bit).      @ingroup nrf_crypto_ecc_secp256k1 */
#define NRF_CRYPTO_ECC_BP256R1_RAW_PRIVATE_KEY_SIZE    (256 / 8)      /**< @brief Raw private key size for bp256r1 (Brainpool 256-bit).      @ingroup nrf_crypto_ecc_bp256r1 */
#define NRF_CRYPTO_ECC_BP384R1_RAW_PRIVATE_KEY_SIZE    (384 / 8)      /**< @brief Raw private key size for bp384r1 (Brainpool 384-bit).      @ingroup nrf_crypto_ecc_bp384r1 */
#define NRF_CRYPTO_ECC_BP512R1_RAW_PRIVATE_KEY_SIZE    (512 / 8)      /**< @brief Raw private key size for bp512r1 (Brainpool 512-bit).      @ingroup nrf_crypto_ecc_bp512r1 */
#define NRF_CRYPTO_ECC_CURVE25519_RAW_PRIVATE_KEY_SIZE (256 / 8)      /**< @brief Raw private key size for Curve25519.                       @ingroup nrf_crypto_ecc_curve25519 */
#define NRF_CRYPTO_ECC_ED25519_RAW_PRIVATE_KEY_SIZE    (256 / 8)      /**< @brief Raw private key size for Ed25519.                          @ingroup nrf_crypto_ecc_ed25519 */


#define NRF_CRYPTO_ECC_SECP160R1_RAW_PUBLIC_KEY_SIZE   (2 * 160 / 8)  /**< @brief Raw public key size for curve secp160r1 (NIST 160-bit).    @ingroup nrf_crypto_ecc_secp160r1 */
#define NRF_CRYPTO_ECC_SECP160R2_RAW_PUBLIC_KEY_SIZE   (2 * 160 / 8)  /**< @brief Raw public key size for curve secp160r2 (NIST 160-bit).    @ingroup nrf_crypto_ecc_secp160r2 */
#define NRF_CRYPTO_ECC_SECP192R1_RAW_PUBLIC_KEY_SIZE   (2 * 192 / 8)  /**< @brief Raw public key size for curve secp192r1 (NIST 192-bit).    @ingroup nrf_crypto_ecc_secp192r1 */
#define NRF_CRYPTO_ECC_SECP224R1_RAW_PUBLIC_KEY_SIZE   (2 * 224 / 8)  /**< @brief Raw public key size for curve secp224r1 (NIST 224-bit).    @ingroup nrf_crypto_ecc_secp224r1 */
#define NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE   (2 * 256 / 8)  /**< @brief Raw public key size for curve secp256r1 (NIST 256-bit).    @ingroup nrf_crypto_ecc_secp256r1 */
#define NRF_CRYPTO_ECC_SECP384R1_RAW_PUBLIC_KEY_SIZE   (2 * 384 / 8)  /**< @brief Raw public key size for curve secp384r1 (NIST 384-bit).    @ingroup nrf_crypto_ecc_secp384r1 */
#define NRF_CRYPTO_ECC_SECP521R1_RAW_PUBLIC_KEY_SIZE   (2 * 528 / 8)  /**< @brief Raw public key size for curve secp521r1 (NIST 521-bit).    @ingroup nrf_crypto_ecc_secp521r1 */
#define NRF_CRYPTO_ECC_SECP160K1_RAW_PUBLIC_KEY_SIZE   (2 * 160 / 8)  /**< @brief Raw public key size for curve secp160k1 (Koblitz 160-bit). @ingroup nrf_crypto_ecc_secp160k1 */
#define NRF_CRYPTO_ECC_SECP192K1_RAW_PUBLIC_KEY_SIZE   (2 * 192 / 8)  /**< @brief Raw public key size for curve secp192k1 (Koblitz 192-bit). @ingroup nrf_crypto_ecc_secp192k1 */
#define NRF_CRYPTO_ECC_SECP224K1_RAW_PUBLIC_KEY_SIZE   (2 * 224 / 8)  /**< @brief Raw public key size for curve secp224k1 (Koblitz 224-bit). @ingroup nrf_crypto_ecc_secp224k1 */
#define NRF_CRYPTO_ECC_SECP256K1_RAW_PUBLIC_KEY_SIZE   (2 * 256 / 8)  /**< @brief Raw public key size for curve secp256k1 (Koblitz 256-bit). @ingroup nrf_crypto_ecc_secp256k1 */
#define NRF_CRYPTO_ECC_BP256R1_RAW_PUBLIC_KEY_SIZE     (2 * 256 / 8)  /**< @brief Raw public key size for curve bp256r1 (Brainpool 256-bit). @ingroup nrf_crypto_ecc_bp256r1 */
#define NRF_CRYPTO_ECC_BP384R1_RAW_PUBLIC_KEY_SIZE     (2 * 384 / 8)  /**< @brief Raw public key size for curve bp384r1 (Brainpool 384-bit). @ingroup nrf_crypto_ecc_bp384r1 */
#define NRF_CRYPTO_ECC_BP512R1_RAW_PUBLIC_KEY_SIZE     (2 * 512 / 8)  /**< @brief Raw public key size for curve bp512r1 (Brainpool 512-bit). @ingroup nrf_crypto_ecc_bp512r1 */
#define NRF_CRYPTO_ECC_CURVE25519_RAW_PUBLIC_KEY_SIZE  (256 / 8)      /**< @brief Raw public key size for curve Curve25519.                  @ingroup nrf_crypto_ecc_curve25519 */
#define NRF_CRYPTO_ECC_ED25519_RAW_PUBLIC_KEY_SIZE     (256 / 8)      /**< @brief Raw public key size for curve Ed25519.                     @ingroup nrf_crypto_ecc_ed25519 */


#define NRF_CRYPTO_ECC_RAW_PRIVATE_KEY_MAX_SIZE NRF_CRYPTO_BACKEND_ECC_RAW_PRIVATE_KEY_MAX_SIZE  /**< @brief Maximum size of a raw private key for all enabled curves. */
#define NRF_CRYPTO_ECC_RAW_PUBLIC_KEY_MAX_SIZE  NRF_CRYPTO_BACKEND_ECC_RAW_PUBLIC_KEY_MAX_SIZE   /**< @brief Maximum size of a raw public key for all enabled curves. */


/** @brief Defines type of ECC curve.
 */
typedef enum
{
#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
    NRF_CRYPTO_ECC_SECP160R1_CURVE_TYPE,   /**< secp160r1 (NIST 160-bit) */
#endif
#if NRF_CRYPTO_ECC_SECP160R2_ENABLED
    NRF_CRYPTO_ECC_SECP160R2_CURVE_TYPE,   /**< secp160r2 (NIST 160-bit) */
#endif
#if NRF_CRYPTO_ECC_SECP192R1_ENABLED
    NRF_CRYPTO_ECC_SECP192R1_CURVE_TYPE,   /**< secp192r1 (NIST 192-bit) */
#endif
#if NRF_CRYPTO_ECC_SECP224R1_ENABLED
    NRF_CRYPTO_ECC_SECP224R1_CURVE_TYPE,   /**< secp224r1 (NIST 224-bit) */
#endif
#if NRF_CRYPTO_ECC_SECP256R1_ENABLED
    NRF_CRYPTO_ECC_SECP256R1_CURVE_TYPE,   /**< secp256r1 (NIST 256-bit) */
#endif
#if NRF_CRYPTO_ECC_SECP384R1_ENABLED
    NRF_CRYPTO_ECC_SECP384R1_CURVE_TYPE,   /**< secp384r1 (NIST 384-bit) */
#endif
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
    NRF_CRYPTO_ECC_SECP521R1_CURVE_TYPE,   /**< secp521r1 (NIST 521-bit) */
#endif
#if NRF_CRYPTO_ECC_SECP160K1_ENABLED
    NRF_CRYPTO_ECC_SECP160K1_CURVE_TYPE,   /**< secp160k1 (Koblitz 160-bit) */
#endif
#if NRF_CRYPTO_ECC_SECP192K1_ENABLED
    NRF_CRYPTO_ECC_SECP192K1_CURVE_TYPE,   /**< secp192k1 (Koblitz 192-bit) */
#endif
#if NRF_CRYPTO_ECC_SECP224K1_ENABLED
    NRF_CRYPTO_ECC_SECP224K1_CURVE_TYPE,   /**< secp224k1 (Koblitz 224-bit) */
#endif
#if NRF_CRYPTO_ECC_SECP256K1_ENABLED
    NRF_CRYPTO_ECC_SECP256K1_CURVE_TYPE,   /**< secp256k1 (Koblitz 256-bit) */
#endif
#if NRF_CRYPTO_ECC_BP256R1_ENABLED
    NRF_CRYPTO_ECC_BP256R1_CURVE_TYPE,     /**< bp256r1 (Brainpool 256-bit) */
#endif
#if NRF_CRYPTO_ECC_BP384R1_ENABLED
    NRF_CRYPTO_ECC_BP384R1_CURVE_TYPE,     /**< bp384r1 (Brainpool 384-bit) */
#endif
#if NRF_CRYPTO_ECC_BP512R1_ENABLED
    NRF_CRYPTO_ECC_BP512R1_CURVE_TYPE,     /**< bp512r1 (Brainpool 512-bit) */
#endif
#if NRF_CRYPTO_ECC_CURVE25519_ENABLED
    NRF_CRYPTO_ECC_CURVE25519_CURVE_TYPE,  /**< Curve25519 */
#endif
#if NRF_CRYPTO_ECC_ED25519_ENABLED
    NRF_CRYPTO_ECC_ED25519_CURVE_TYPE,     /**< Ed25519 */
#endif
#if !NRF_CRYPTO_ECC_SECP160R1_ENABLED
    NRF_CRYPTO_ECC_SECP160R1_CURVE_TYPE,   /**< secp160r1 (NIST 160-bit) */
#endif
#if !NRF_CRYPTO_ECC_SECP160R2_ENABLED
    NRF_CRYPTO_ECC_SECP160R2_CURVE_TYPE,   /**< secp160r2 (NIST 160-bit) */
#endif
#if !NRF_CRYPTO_ECC_SECP192R1_ENABLED
    NRF_CRYPTO_ECC_SECP192R1_CURVE_TYPE,   /**< secp192r1 (NIST 192-bit) */
#endif
#if !NRF_CRYPTO_ECC_SECP224R1_ENABLED
    NRF_CRYPTO_ECC_SECP224R1_CURVE_TYPE,   /**< secp224r1 (NIST 224-bit) */
#endif
#if !NRF_CRYPTO_ECC_SECP256R1_ENABLED
    NRF_CRYPTO_ECC_SECP256R1_CURVE_TYPE,   /**< secp256r1 (NIST 256-bit) */
#endif
#if !NRF_CRYPTO_ECC_SECP384R1_ENABLED
    NRF_CRYPTO_ECC_SECP384R1_CURVE_TYPE,   /**< secp384r1 (NIST 384-bit) */
#endif
#if !NRF_CRYPTO_ECC_SECP521R1_ENABLED
    NRF_CRYPTO_ECC_SECP521R1_CURVE_TYPE,   /**< secp521r1 (NIST 521-bit) */
#endif
#if !NRF_CRYPTO_ECC_SECP160K1_ENABLED
    NRF_CRYPTO_ECC_SECP160K1_CURVE_TYPE,   /**< secp160k1 (Koblitz 160-bit) */
#endif
#if !NRF_CRYPTO_ECC_SECP192K1_ENABLED
    NRF_CRYPTO_ECC_SECP192K1_CURVE_TYPE,   /**< secp192k1 (Koblitz 192-bit) */
#endif
#if !NRF_CRYPTO_ECC_SECP224K1_ENABLED
    NRF_CRYPTO_ECC_SECP224K1_CURVE_TYPE,   /**< secp224k1 (Koblitz 224-bit) */
#endif
#if !NRF_CRYPTO_ECC_SECP256K1_ENABLED
    NRF_CRYPTO_ECC_SECP256K1_CURVE_TYPE,   /**< secp256k1 (Koblitz 256-bit) */
#endif
#if !NRF_CRYPTO_ECC_BP256R1_ENABLED
    NRF_CRYPTO_ECC_BP256R1_CURVE_TYPE,     /**< bp256r1 (Brainpool 256-bit) */
#endif
#if !NRF_CRYPTO_ECC_BP384R1_ENABLED
    NRF_CRYPTO_ECC_BP384R1_CURVE_TYPE,     /**< bp384r1 (Brainpool 384-bit) */
#endif
#if !NRF_CRYPTO_ECC_BP512R1_ENABLED
    NRF_CRYPTO_ECC_BP512R1_CURVE_TYPE,     /**< bp512r1 (Brainpool 512-bit) */
#endif
#if !NRF_CRYPTO_ECC_CURVE25519_ENABLED
    NRF_CRYPTO_ECC_CURVE25519_CURVE_TYPE,  /**< Curve25519 */
#endif
#if !NRF_CRYPTO_ECC_ED25519_ENABLED
    NRF_CRYPTO_ECC_ED25519_CURVE_TYPE,     /**< Ed25519 */
#endif
} nrf_crypto_ecc_curve_type_t;


/** @brief Structure holding information on a specific curve.
 *
 *  @note This structure cannot be used to create a new variable. Only the variables defined by this
 *  library can be used, e.g. @ref g_nrf_crypto_ecc_secp256r1_curve_info.
 */
typedef struct nrf_crypto_ecc_curve_info_s
{
    uint16_t                    public_key_size;       /**< @brief Size of a structure holding internal public key. */
    uint16_t                    private_key_size;      /**< @brief Size of a structure holding internal private key. */
    nrf_crypto_ecc_curve_type_t curve_type;            /**< @brief Type of the curve. */
    uint8_t                     raw_private_key_size;  /**< @brief Size of a buffer containing raw private key. */
    uint8_t                     raw_public_key_size;   /**< @brief Size of a buffer containing raw public key. */
    void *                      p_backend_data;        /**< @brief Field to hold backend specific internal data. */
} nrf_crypto_ecc_curve_info_t;


/** @addtogroup nrf_crypto_ecc_secp160r1
 *  @{ */

typedef nrf_crypto_backend_secp160r1_key_pair_generate_context_t
    nrf_crypto_ecc_secp160r1_key_pair_generate_context_t;            /**< @brief Context structure for key generation using secp160r1 (NIST 160-bit). */
typedef nrf_crypto_backend_secp160r1_public_key_calculate_context_t
    nrf_crypto_ecc_secp160r1_public_key_calculate_context_t;         /**< @brief Context structure for public key calculation using secp160r1 (NIST 160-bit). */
typedef nrf_crypto_backend_secp160r1_private_key_t
    nrf_crypto_ecc_secp160r1_private_key_t;                          /**< @brief Structure holding internal representation of a private key for secp160r1 (NIST 160-bit) */
typedef nrf_crypto_backend_secp160r1_public_key_t
    nrf_crypto_ecc_secp160r1_public_key_t;                           /**< @brief Structure holding internal representation of a public key for secp160r1 (NIST 160-bit) */
typedef uint8_t nrf_crypto_ecc_secp160r1_raw_private_key_t
    [NRF_CRYPTO_ECC_SECP160R1_RAW_PRIVATE_KEY_SIZE];                 /**< @brief Array holding raw private key for secp160r1 (NIST 160-bit) */
typedef uint8_t nrf_crypto_ecc_secp160r1_raw_public_key_t
    [NRF_CRYPTO_ECC_SECP160R1_RAW_PUBLIC_KEY_SIZE];                  /**< @brief Array holding raw public key for secp160r1 (NIST 160-bit) */



/** @brief Variable containing information on secp160r1 (NIST 160-bit).
 *
 *  It can be used as a parameter for the functions creating secp160r1 (NIST 160-bit) keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp160r1_curve_info;


/** @} */


/** @addtogroup nrf_crypto_ecc_secp160r2
 *  @{ */

typedef nrf_crypto_backend_secp160r2_key_pair_generate_context_t
    nrf_crypto_ecc_secp160r2_key_pair_generate_context_t;            /**< @brief Context structure for key generation using secp160r2 (NIST 160-bit). */
typedef nrf_crypto_backend_secp160r2_public_key_calculate_context_t
    nrf_crypto_ecc_secp160r2_public_key_calculate_context_t;         /**< @brief Context structure for public key calculation using secp160r2 (NIST 160-bit). */
typedef nrf_crypto_backend_secp160r2_private_key_t
    nrf_crypto_ecc_secp160r2_private_key_t;                          /**< @brief Structure holding internal representation of a private key for secp160r2 (NIST 160-bit) */
typedef nrf_crypto_backend_secp160r2_public_key_t
    nrf_crypto_ecc_secp160r2_public_key_t;                           /**< @brief Structure holding internal representation of a public key for secp160r2 (NIST 160-bit) */
typedef uint8_t nrf_crypto_ecc_secp160r2_raw_private_key_t
    [NRF_CRYPTO_ECC_SECP160R2_RAW_PRIVATE_KEY_SIZE];                 /**< @brief Array holding raw private key for secp160r2 (NIST 160-bit) */
typedef uint8_t nrf_crypto_ecc_secp160r2_raw_public_key_t
    [NRF_CRYPTO_ECC_SECP160R2_RAW_PUBLIC_KEY_SIZE];                  /**< @brief Array holding raw public key for secp160r2 (NIST 160-bit) */



/** @brief Variable containing information on secp160r2 (NIST 160-bit).
 *
 *  It can be used as a parameter for the functions creating secp160r2 (NIST 160-bit) keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp160r2_curve_info;


/** @} */


/** @addtogroup nrf_crypto_ecc_secp192r1
 *  @{ */

typedef nrf_crypto_backend_secp192r1_key_pair_generate_context_t
    nrf_crypto_ecc_secp192r1_key_pair_generate_context_t;            /**< @brief Context structure for key generation using secp192r1 (NIST 192-bit). */
typedef nrf_crypto_backend_secp192r1_public_key_calculate_context_t
    nrf_crypto_ecc_secp192r1_public_key_calculate_context_t;         /**< @brief Context structure for public key calculation using secp192r1 (NIST 192-bit). */
typedef nrf_crypto_backend_secp192r1_private_key_t
    nrf_crypto_ecc_secp192r1_private_key_t;                          /**< @brief Structure holding internal representation of a private key for secp192r1 (NIST 192-bit) */
typedef nrf_crypto_backend_secp192r1_public_key_t
    nrf_crypto_ecc_secp192r1_public_key_t;                           /**< @brief Structure holding internal representation of a public key for secp192r1 (NIST 192-bit) */
typedef uint8_t nrf_crypto_ecc_secp192r1_raw_private_key_t
    [NRF_CRYPTO_ECC_SECP192R1_RAW_PRIVATE_KEY_SIZE];                 /**< @brief Array holding raw private key for secp192r1 (NIST 192-bit) */
typedef uint8_t nrf_crypto_ecc_secp192r1_raw_public_key_t
    [NRF_CRYPTO_ECC_SECP192R1_RAW_PUBLIC_KEY_SIZE];                  /**< @brief Array holding raw public key for secp192r1 (NIST 192-bit) */



/** @brief Variable containing information on secp192r1 (NIST 192-bit).
 *
 *  It can be used as a parameter for the functions creating secp192r1 (NIST 192-bit) keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp192r1_curve_info;


/** @} */


/** @addtogroup nrf_crypto_ecc_secp224r1
 *  @{ */

typedef nrf_crypto_backend_secp224r1_key_pair_generate_context_t
    nrf_crypto_ecc_secp224r1_key_pair_generate_context_t;            /**< @brief Context structure for key generation using secp224r1 (NIST 224-bit). */
typedef nrf_crypto_backend_secp224r1_public_key_calculate_context_t
    nrf_crypto_ecc_secp224r1_public_key_calculate_context_t;         /**< @brief Context structure for public key calculation using secp224r1 (NIST 224-bit). */
typedef nrf_crypto_backend_secp224r1_private_key_t
    nrf_crypto_ecc_secp224r1_private_key_t;                          /**< @brief Structure holding internal representation of a private key for secp224r1 (NIST 224-bit) */
typedef nrf_crypto_backend_secp224r1_public_key_t
    nrf_crypto_ecc_secp224r1_public_key_t;                           /**< @brief Structure holding internal representation of a public key for secp224r1 (NIST 224-bit) */
typedef uint8_t nrf_crypto_ecc_secp224r1_raw_private_key_t
    [NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE];                 /**< @brief Array holding raw private key for secp224r1 (NIST 224-bit) */
typedef uint8_t nrf_crypto_ecc_secp224r1_raw_public_key_t
    [NRF_CRYPTO_ECC_SECP224R1_RAW_PUBLIC_KEY_SIZE];                  /**< @brief Array holding raw public key for secp224r1 (NIST 224-bit) */



/** @brief Variable containing information on secp224r1 (NIST 224-bit).
 *
 *  It can be used as a parameter for the functions creating secp224r1 (NIST 224-bit) keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp224r1_curve_info;


/** @} */


/** @addtogroup nrf_crypto_ecc_secp256r1
 *  @{ */

typedef nrf_crypto_backend_secp256r1_key_pair_generate_context_t
    nrf_crypto_ecc_secp256r1_key_pair_generate_context_t;            /**< @brief Context structure for key generation using secp256r1 (NIST 256-bit). */
typedef nrf_crypto_backend_secp256r1_public_key_calculate_context_t
    nrf_crypto_ecc_secp256r1_public_key_calculate_context_t;         /**< @brief Context structure for public key calculation using secp256r1 (NIST 256-bit). */
typedef nrf_crypto_backend_secp256r1_private_key_t
    nrf_crypto_ecc_secp256r1_private_key_t;                          /**< @brief Structure holding internal representation of a private key for secp256r1 (NIST 256-bit) */
typedef nrf_crypto_backend_secp256r1_public_key_t
    nrf_crypto_ecc_secp256r1_public_key_t;                           /**< @brief Structure holding internal representation of a public key for secp256r1 (NIST 256-bit) */
typedef uint8_t nrf_crypto_ecc_secp256r1_raw_private_key_t
    [NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE];                 /**< @brief Array holding raw private key for secp256r1 (NIST 256-bit) */
typedef uint8_t nrf_crypto_ecc_secp256r1_raw_public_key_t
    [NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE];                  /**< @brief Array holding raw public key for secp256r1 (NIST 256-bit) */



/** @brief Variable containing information on secp256r1 (NIST 256-bit).
 *
 *  It can be used as a parameter for the functions creating secp256r1 (NIST 256-bit) keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp256r1_curve_info;


/** @} */


/** @addtogroup nrf_crypto_ecc_secp384r1
 *  @{ */

typedef nrf_crypto_backend_secp384r1_key_pair_generate_context_t
    nrf_crypto_ecc_secp384r1_key_pair_generate_context_t;            /**< @brief Context structure for key generation using secp384r1 (NIST 384-bit). */
typedef nrf_crypto_backend_secp384r1_public_key_calculate_context_t
    nrf_crypto_ecc_secp384r1_public_key_calculate_context_t;         /**< @brief Context structure for public key calculation using secp384r1 (NIST 384-bit). */
typedef nrf_crypto_backend_secp384r1_private_key_t
    nrf_crypto_ecc_secp384r1_private_key_t;                          /**< @brief Structure holding internal representation of a private key for secp384r1 (NIST 384-bit) */
typedef nrf_crypto_backend_secp384r1_public_key_t
    nrf_crypto_ecc_secp384r1_public_key_t;                           /**< @brief Structure holding internal representation of a public key for secp384r1 (NIST 384-bit) */
typedef uint8_t nrf_crypto_ecc_secp384r1_raw_private_key_t
    [NRF_CRYPTO_ECC_SECP384R1_RAW_PRIVATE_KEY_SIZE];                 /**< @brief Array holding raw private key for secp384r1 (NIST 384-bit) */
typedef uint8_t nrf_crypto_ecc_secp384r1_raw_public_key_t
    [NRF_CRYPTO_ECC_SECP384R1_RAW_PUBLIC_KEY_SIZE];                  /**< @brief Array holding raw public key for secp384r1 (NIST 384-bit) */



/** @brief Variable containing information on secp384r1 (NIST 384-bit).
 *
 *  It can be used as a parameter for the functions creating secp384r1 (NIST 384-bit) keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp384r1_curve_info;


/** @} */


/** @addtogroup nrf_crypto_ecc_secp521r1
 *  @{ */

typedef nrf_crypto_backend_secp521r1_key_pair_generate_context_t
    nrf_crypto_ecc_secp521r1_key_pair_generate_context_t;            /**< @brief Context structure for key generation using secp521r1 (NIST 521-bit). */
typedef nrf_crypto_backend_secp521r1_public_key_calculate_context_t
    nrf_crypto_ecc_secp521r1_public_key_calculate_context_t;         /**< @brief Context structure for public key calculation using secp521r1 (NIST 521-bit). */
typedef nrf_crypto_backend_secp521r1_private_key_t
    nrf_crypto_ecc_secp521r1_private_key_t;                          /**< @brief Structure holding internal representation of a private key for secp521r1 (NIST 521-bit) */
typedef nrf_crypto_backend_secp521r1_public_key_t
    nrf_crypto_ecc_secp521r1_public_key_t;                           /**< @brief Structure holding internal representation of a public key for secp521r1 (NIST 521-bit) */
typedef uint8_t nrf_crypto_ecc_secp521r1_raw_private_key_t
    [NRF_CRYPTO_ECC_SECP521R1_RAW_PRIVATE_KEY_SIZE];                 /**< @brief Array holding raw private key for secp521r1 (NIST 521-bit) */
typedef uint8_t nrf_crypto_ecc_secp521r1_raw_public_key_t
    [NRF_CRYPTO_ECC_SECP521R1_RAW_PUBLIC_KEY_SIZE];                  /**< @brief Array holding raw public key for secp521r1 (NIST 521-bit) */



/** @brief Variable containing information on secp521r1 (NIST 521-bit).
 *
 *  It can be used as a parameter for the functions creating secp521r1 (NIST 521-bit) keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp521r1_curve_info;


/** @} */


/** @addtogroup nrf_crypto_ecc_secp160k1
 *  @{ */

typedef nrf_crypto_backend_secp160k1_key_pair_generate_context_t
    nrf_crypto_ecc_secp160k1_key_pair_generate_context_t;            /**< @brief Context structure for key generation using secp160k1 (Koblitz 160-bit). */
typedef nrf_crypto_backend_secp160k1_public_key_calculate_context_t
    nrf_crypto_ecc_secp160k1_public_key_calculate_context_t;         /**< @brief Context structure for public key calculation using secp160k1 (Koblitz 160-bit). */
typedef nrf_crypto_backend_secp160k1_private_key_t
    nrf_crypto_ecc_secp160k1_private_key_t;                          /**< @brief Structure holding internal representation of a private key for secp160k1 (Koblitz 160-bit) */
typedef nrf_crypto_backend_secp160k1_public_key_t
    nrf_crypto_ecc_secp160k1_public_key_t;                           /**< @brief Structure holding internal representation of a public key for secp160k1 (Koblitz 160-bit) */
typedef uint8_t nrf_crypto_ecc_secp160k1_raw_private_key_t
    [NRF_CRYPTO_ECC_SECP160K1_RAW_PRIVATE_KEY_SIZE];                 /**< @brief Array holding raw private key for secp160k1 (Koblitz 160-bit) */
typedef uint8_t nrf_crypto_ecc_secp160k1_raw_public_key_t
    [NRF_CRYPTO_ECC_SECP160K1_RAW_PUBLIC_KEY_SIZE];                  /**< @brief Array holding raw public key for secp160k1 (Koblitz 160-bit) */



/** @brief Variable containing information on secp160k1 (Koblitz 160-bit).
 *
 *  It can be used as a parameter for the functions creating secp160k1 (Koblitz 160-bit) keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp160k1_curve_info;


/** @} */


/** @addtogroup nrf_crypto_ecc_secp192k1
 *  @{ */

typedef nrf_crypto_backend_secp192k1_key_pair_generate_context_t
    nrf_crypto_ecc_secp192k1_key_pair_generate_context_t;            /**< @brief Context structure for key generation using secp192k1 (Koblitz 192-bit). */
typedef nrf_crypto_backend_secp192k1_public_key_calculate_context_t
    nrf_crypto_ecc_secp192k1_public_key_calculate_context_t;         /**< @brief Context structure for public key calculation using secp192k1 (Koblitz 192-bit). */
typedef nrf_crypto_backend_secp192k1_private_key_t
    nrf_crypto_ecc_secp192k1_private_key_t;                          /**< @brief Structure holding internal representation of a private key for secp192k1 (Koblitz 192-bit) */
typedef nrf_crypto_backend_secp192k1_public_key_t
    nrf_crypto_ecc_secp192k1_public_key_t;                           /**< @brief Structure holding internal representation of a public key for secp192k1 (Koblitz 192-bit) */
typedef uint8_t nrf_crypto_ecc_secp192k1_raw_private_key_t
    [NRF_CRYPTO_ECC_SECP192K1_RAW_PRIVATE_KEY_SIZE];                 /**< @brief Array holding raw private key for secp192k1 (Koblitz 192-bit) */
typedef uint8_t nrf_crypto_ecc_secp192k1_raw_public_key_t
    [NRF_CRYPTO_ECC_SECP192K1_RAW_PUBLIC_KEY_SIZE];                  /**< @brief Array holding raw public key for secp192k1 (Koblitz 192-bit) */



/** @brief Variable containing information on secp192k1 (Koblitz 192-bit).
 *
 *  It can be used as a parameter for the functions creating secp192k1 (Koblitz 192-bit) keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp192k1_curve_info;


/** @} */


/** @addtogroup nrf_crypto_ecc_secp224k1
 *  @{ */

typedef nrf_crypto_backend_secp224k1_key_pair_generate_context_t
    nrf_crypto_ecc_secp224k1_key_pair_generate_context_t;            /**< @brief Context structure for key generation using secp224k1 (Koblitz 224-bit). */
typedef nrf_crypto_backend_secp224k1_public_key_calculate_context_t
    nrf_crypto_ecc_secp224k1_public_key_calculate_context_t;         /**< @brief Context structure for public key calculation using secp224k1 (Koblitz 224-bit). */
typedef nrf_crypto_backend_secp224k1_private_key_t
    nrf_crypto_ecc_secp224k1_private_key_t;                          /**< @brief Structure holding internal representation of a private key for secp224k1 (Koblitz 224-bit) */
typedef nrf_crypto_backend_secp224k1_public_key_t
    nrf_crypto_ecc_secp224k1_public_key_t;                           /**< @brief Structure holding internal representation of a public key for secp224k1 (Koblitz 224-bit) */
typedef uint8_t nrf_crypto_ecc_secp224k1_raw_private_key_t
    [NRF_CRYPTO_ECC_SECP224K1_RAW_PRIVATE_KEY_SIZE];                 /**< @brief Array holding raw private key for secp224k1 (Koblitz 224-bit) */
typedef uint8_t nrf_crypto_ecc_secp224k1_raw_public_key_t
    [NRF_CRYPTO_ECC_SECP224K1_RAW_PUBLIC_KEY_SIZE];                  /**< @brief Array holding raw public key for secp224k1 (Koblitz 224-bit) */



/** @brief Variable containing information on secp224k1 (Koblitz 224-bit).
 *
 *  It can be used as a parameter for the functions creating secp224k1 (Koblitz 224-bit) keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp224k1_curve_info;


/** @} */


/** @addtogroup nrf_crypto_ecc_secp256k1
 *  @{ */

typedef nrf_crypto_backend_secp256k1_key_pair_generate_context_t
    nrf_crypto_ecc_secp256k1_key_pair_generate_context_t;            /**< @brief Context structure for key generation using secp256k1 (Koblitz 256-bit). */
typedef nrf_crypto_backend_secp256k1_public_key_calculate_context_t
    nrf_crypto_ecc_secp256k1_public_key_calculate_context_t;         /**< @brief Context structure for public key calculation using secp256k1 (Koblitz 256-bit). */
typedef nrf_crypto_backend_secp256k1_private_key_t
    nrf_crypto_ecc_secp256k1_private_key_t;                          /**< @brief Structure holding internal representation of a private key for secp256k1 (Koblitz 256-bit) */
typedef nrf_crypto_backend_secp256k1_public_key_t
    nrf_crypto_ecc_secp256k1_public_key_t;                           /**< @brief Structure holding internal representation of a public key for secp256k1 (Koblitz 256-bit) */
typedef uint8_t nrf_crypto_ecc_secp256k1_raw_private_key_t
    [NRF_CRYPTO_ECC_SECP256K1_RAW_PRIVATE_KEY_SIZE];                 /**< @brief Array holding raw private key for secp256k1 (Koblitz 256-bit) */
typedef uint8_t nrf_crypto_ecc_secp256k1_raw_public_key_t
    [NRF_CRYPTO_ECC_SECP256K1_RAW_PUBLIC_KEY_SIZE];                  /**< @brief Array holding raw public key for secp256k1 (Koblitz 256-bit) */



/** @brief Variable containing information on secp256k1 (Koblitz 256-bit).
 *
 *  It can be used as a parameter for the functions creating secp256k1 (Koblitz 256-bit) keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp256k1_curve_info;


/** @} */


/** @addtogroup nrf_crypto_ecc_bp256r1
 *  @{ */

typedef nrf_crypto_backend_bp256r1_key_pair_generate_context_t
    nrf_crypto_ecc_bp256r1_key_pair_generate_context_t;              /**< @brief Context structure for key generation using bp256r1 (Brainpool 256-bit). */
typedef nrf_crypto_backend_bp256r1_public_key_calculate_context_t
    nrf_crypto_ecc_bp256r1_public_key_calculate_context_t;           /**< @brief Context structure for public key calculation using bp256r1 (Brainpool 256-bit). */
typedef nrf_crypto_backend_bp256r1_private_key_t
    nrf_crypto_ecc_bp256r1_private_key_t;                            /**< @brief Structure holding internal representation of a private key for bp256r1 (Brainpool 256-bit) */
typedef nrf_crypto_backend_bp256r1_public_key_t
    nrf_crypto_ecc_bp256r1_public_key_t;                             /**< @brief Structure holding internal representation of a public key for bp256r1 (Brainpool 256-bit) */
typedef uint8_t nrf_crypto_ecc_bp256r1_raw_private_key_t
    [NRF_CRYPTO_ECC_BP256R1_RAW_PRIVATE_KEY_SIZE];                   /**< @brief Array holding raw private key for bp256r1 (Brainpool 256-bit) */
typedef uint8_t nrf_crypto_ecc_bp256r1_raw_public_key_t
    [NRF_CRYPTO_ECC_BP256R1_RAW_PUBLIC_KEY_SIZE];                    /**< @brief Array holding raw public key for bp256r1 (Brainpool 256-bit) */



/** @brief Variable containing information on bp256r1 (Brainpool 256-bit).
 *
 *  It can be used as a parameter for the functions creating bp256r1 (Brainpool 256-bit) keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_bp256r1_curve_info;


/** @} */


/** @addtogroup nrf_crypto_ecc_bp384r1
 *  @{ */

typedef nrf_crypto_backend_bp384r1_key_pair_generate_context_t
    nrf_crypto_ecc_bp384r1_key_pair_generate_context_t;              /**< @brief Context structure for key generation using bp384r1 (Brainpool 384-bit). */
typedef nrf_crypto_backend_bp384r1_public_key_calculate_context_t
    nrf_crypto_ecc_bp384r1_public_key_calculate_context_t;           /**< @brief Context structure for public key calculation using bp384r1 (Brainpool 384-bit). */
typedef nrf_crypto_backend_bp384r1_private_key_t
    nrf_crypto_ecc_bp384r1_private_key_t;                            /**< @brief Structure holding internal representation of a private key for bp384r1 (Brainpool 384-bit) */
typedef nrf_crypto_backend_bp384r1_public_key_t
    nrf_crypto_ecc_bp384r1_public_key_t;                             /**< @brief Structure holding internal representation of a public key for bp384r1 (Brainpool 384-bit) */
typedef uint8_t nrf_crypto_ecc_bp384r1_raw_private_key_t
    [NRF_CRYPTO_ECC_BP384R1_RAW_PRIVATE_KEY_SIZE];                   /**< @brief Array holding raw private key for bp384r1 (Brainpool 384-bit) */
typedef uint8_t nrf_crypto_ecc_bp384r1_raw_public_key_t
    [NRF_CRYPTO_ECC_BP384R1_RAW_PUBLIC_KEY_SIZE];                    /**< @brief Array holding raw public key for bp384r1 (Brainpool 384-bit) */



/** @brief Variable containing information on bp384r1 (Brainpool 384-bit).
 *
 *  It can be used as a parameter for the functions creating bp384r1 (Brainpool 384-bit) keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_bp384r1_curve_info;


/** @} */


/** @addtogroup nrf_crypto_ecc_bp512r1
 *  @{ */

typedef nrf_crypto_backend_bp512r1_key_pair_generate_context_t
    nrf_crypto_ecc_bp512r1_key_pair_generate_context_t;              /**< @brief Context structure for key generation using bp512r1 (Brainpool 512-bit). */
typedef nrf_crypto_backend_bp512r1_public_key_calculate_context_t
    nrf_crypto_ecc_bp512r1_public_key_calculate_context_t;           /**< @brief Context structure for public key calculation using bp512r1 (Brainpool 512-bit). */
typedef nrf_crypto_backend_bp512r1_private_key_t
    nrf_crypto_ecc_bp512r1_private_key_t;                            /**< @brief Structure holding internal representation of a private key for bp512r1 (Brainpool 512-bit) */
typedef nrf_crypto_backend_bp512r1_public_key_t
    nrf_crypto_ecc_bp512r1_public_key_t;                             /**< @brief Structure holding internal representation of a public key for bp512r1 (Brainpool 512-bit) */
typedef uint8_t nrf_crypto_ecc_bp512r1_raw_private_key_t
    [NRF_CRYPTO_ECC_BP512R1_RAW_PRIVATE_KEY_SIZE];                   /**< @brief Array holding raw private key for bp512r1 (Brainpool 512-bit) */
typedef uint8_t nrf_crypto_ecc_bp512r1_raw_public_key_t
    [NRF_CRYPTO_ECC_BP512R1_RAW_PUBLIC_KEY_SIZE];                    /**< @brief Array holding raw public key for bp512r1 (Brainpool 512-bit) */



/** @brief Variable containing information on bp512r1 (Brainpool 512-bit).
 *
 *  It can be used as a parameter for the functions creating bp512r1 (Brainpool 512-bit) keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_bp512r1_curve_info;


/** @} */


/** @addtogroup nrf_crypto_ecc_curve25519
 *  @{ */

typedef nrf_crypto_backend_curve25519_key_pair_generate_context_t
    nrf_crypto_ecc_curve25519_key_pair_generate_context_t;           /**< @brief Context structure for key generation using Curve25519. */
typedef nrf_crypto_backend_curve25519_public_key_calculate_context_t
    nrf_crypto_ecc_curve25519_public_key_calculate_context_t;        /**< @brief Context structure for public key calculation using Curve25519. */
typedef nrf_crypto_backend_curve25519_private_key_t
    nrf_crypto_ecc_curve25519_private_key_t;                         /**< @brief Structure holding internal representation of a private key for Curve25519 */
typedef nrf_crypto_backend_curve25519_public_key_t
    nrf_crypto_ecc_curve25519_public_key_t;                          /**< @brief Structure holding internal representation of a public key for Curve25519 */
typedef uint8_t nrf_crypto_ecc_curve25519_raw_private_key_t
    [NRF_CRYPTO_ECC_CURVE25519_RAW_PRIVATE_KEY_SIZE];                /**< @brief Array holding raw private key for Curve25519 */
typedef uint8_t nrf_crypto_ecc_curve25519_raw_public_key_t
    [NRF_CRYPTO_ECC_CURVE25519_RAW_PUBLIC_KEY_SIZE];                 /**< @brief Array holding raw public key for Curve25519 */


/** @brief Variable containing information on Curve25519.
 *
 *  It can be used as a parameter for the functions creating Curve25519 keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_curve25519_curve_info;


/** @} */


/** @addtogroup nrf_crypto_ecc_ed25519
 *  @{ */

typedef nrf_crypto_backend_ed25519_key_pair_generate_context_t
    nrf_crypto_ecc_ed25519_key_pair_generate_context_t;              /**< @brief Context structure for key generation using Ed25519. */
typedef nrf_crypto_backend_ed25519_public_key_calculate_context_t
    nrf_crypto_ecc_ed25519_public_key_calculate_context_t;           /**< @brief Context structure for public key calculation using Ed25519. */
typedef nrf_crypto_backend_ed25519_private_key_t
    nrf_crypto_ecc_ed25519_private_key_t;                            /**< @brief Structure holding internal representation of a private key for Ed25519 */
typedef nrf_crypto_backend_ed25519_public_key_t
    nrf_crypto_ecc_ed25519_public_key_t;                             /**< @brief Structure holding internal representation of a public key for Ed25519 */
typedef uint8_t nrf_crypto_ecc_ed25519_raw_private_key_t
    [NRF_CRYPTO_ECC_ED25519_RAW_PRIVATE_KEY_SIZE];                   /**< @brief Array holding raw private key for Ed25519 */
typedef uint8_t nrf_crypto_ecc_ed25519_raw_public_key_t
    [NRF_CRYPTO_ECC_ED25519_RAW_PUBLIC_KEY_SIZE];                    /**< @brief Array holding raw public key for Ed25519 */



/** @brief Variable containing information on Ed25519.
 *
 *  It can be used as a parameter for the functions creating Ed25519 keys.
 */
extern const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_ed25519_curve_info;


/** @} */


typedef uint8_t nrf_crypto_ecc_raw_private_key_t[NRF_CRYPTO_ECC_RAW_PRIVATE_KEY_MAX_SIZE];  /**< @brief Type big enough to hold a raw private key for any the enabled curves. */
typedef uint8_t nrf_crypto_ecc_raw_public_key_t [NRF_CRYPTO_ECC_RAW_PUBLIC_KEY_MAX_SIZE];   /**< @brief Type big enough to hold a raw public key for any the enabled curves. */


/** @brief Union holding a context for a key pair generation.
 */
typedef union
{
    nrf_crypto_ecc_secp160r1_key_pair_generate_context_t  context_secp160r1;    /**< @brief Holds context for secp160r1 (NIST 160-bit). */
    nrf_crypto_ecc_secp160r2_key_pair_generate_context_t  context_secp160r2;    /**< @brief Holds context for secp160r2 (NIST 160-bit). */
    nrf_crypto_ecc_secp192r1_key_pair_generate_context_t  context_secp192r1;    /**< @brief Holds context for secp192r1 (NIST 192-bit). */
    nrf_crypto_ecc_secp224r1_key_pair_generate_context_t  context_secp224r1;    /**< @brief Holds context for secp224r1 (NIST 224-bit). */
    nrf_crypto_ecc_secp256r1_key_pair_generate_context_t  context_secp256r1;    /**< @brief Holds context for secp256r1 (NIST 256-bit). */
    nrf_crypto_ecc_secp384r1_key_pair_generate_context_t  context_secp384r1;    /**< @brief Holds context for secp384r1 (NIST 384-bit). */
    nrf_crypto_ecc_secp521r1_key_pair_generate_context_t  context_secp521r1;    /**< @brief Holds context for secp521r1 (NIST 521-bit). */
    nrf_crypto_ecc_secp160k1_key_pair_generate_context_t  context_secp160k1;    /**< @brief Holds context for secp160k1 (Koblitz 160-bit). */
    nrf_crypto_ecc_secp192k1_key_pair_generate_context_t  context_secp192k1;    /**< @brief Holds context for secp192k1 (Koblitz 192-bit). */
    nrf_crypto_ecc_secp224k1_key_pair_generate_context_t  context_secp224k1;    /**< @brief Holds context for secp224k1 (Koblitz 224-bit). */
    nrf_crypto_ecc_secp256k1_key_pair_generate_context_t  context_secp256k1;    /**< @brief Holds context for secp256k1 (Koblitz 256-bit). */
    nrf_crypto_ecc_bp256r1_key_pair_generate_context_t    context_bp256r1;      /**< @brief Holds context for bp256r1 (Brainpool 256-bit). */
    nrf_crypto_ecc_bp384r1_key_pair_generate_context_t    context_bp384r1;      /**< @brief Holds context for bp384r1 (Brainpool 384-bit). */
    nrf_crypto_ecc_bp512r1_key_pair_generate_context_t    context_bp512r1;      /**< @brief Holds context for bp512r1 (Brainpool 512-bit). */
    nrf_crypto_ecc_curve25519_key_pair_generate_context_t context_curve25519;   /**< @brief Holds context for Curve25519. */
    nrf_crypto_ecc_ed25519_key_pair_generate_context_t    context_ed25519;      /**< @brief Holds context for Ed25519. */
} nrf_crypto_ecc_key_pair_generate_context_t;


/** @brief Union holding a context for a public key calculation.
 */
typedef union
{
    nrf_crypto_ecc_secp160r1_public_key_calculate_context_t  context_secp160r1;    /**< @brief Holds context for secp160r1 (NIST 160-bit). */
    nrf_crypto_ecc_secp160r2_public_key_calculate_context_t  context_secp160r2;    /**< @brief Holds context for secp160r2 (NIST 160-bit). */
    nrf_crypto_ecc_secp192r1_public_key_calculate_context_t  context_secp192r1;    /**< @brief Holds context for secp192r1 (NIST 192-bit). */
    nrf_crypto_ecc_secp224r1_public_key_calculate_context_t  context_secp224r1;    /**< @brief Holds context for secp224r1 (NIST 224-bit). */
    nrf_crypto_ecc_secp256r1_public_key_calculate_context_t  context_secp256r1;    /**< @brief Holds context for secp256r1 (NIST 256-bit). */
    nrf_crypto_ecc_secp384r1_public_key_calculate_context_t  context_secp384r1;    /**< @brief Holds context for secp384r1 (NIST 384-bit). */
    nrf_crypto_ecc_secp521r1_public_key_calculate_context_t  context_secp521r1;    /**< @brief Holds context for secp521r1 (NIST 521-bit). */
    nrf_crypto_ecc_secp160k1_public_key_calculate_context_t  context_secp160k1;    /**< @brief Holds context for secp160k1 (Koblitz 160-bit). */
    nrf_crypto_ecc_secp192k1_public_key_calculate_context_t  context_secp192k1;    /**< @brief Holds context for secp192k1 (Koblitz 192-bit). */
    nrf_crypto_ecc_secp224k1_public_key_calculate_context_t  context_secp224k1;    /**< @brief Holds context for secp224k1 (Koblitz 224-bit). */
    nrf_crypto_ecc_secp256k1_public_key_calculate_context_t  context_secp256k1;    /**< @brief Holds context for secp256k1 (Koblitz 256-bit). */
    nrf_crypto_ecc_bp256r1_public_key_calculate_context_t    context_bp256r1;      /**< @brief Holds context for bp256r1 (Brainpool 256-bit). */
    nrf_crypto_ecc_bp384r1_public_key_calculate_context_t    context_bp384r1;      /**< @brief Holds context for bp384r1 (Brainpool 384-bit). */
    nrf_crypto_ecc_bp512r1_public_key_calculate_context_t    context_bp512r1;      /**< @brief Holds context for bp512r1 (Brainpool 512-bit). */
    nrf_crypto_ecc_curve25519_public_key_calculate_context_t context_curve25519;   /**< @brief Holds context for Curve25519. */
    nrf_crypto_ecc_ed25519_public_key_calculate_context_t    context_ed25519;      /**< @brief Holds context for Ed25519. */
} nrf_crypto_ecc_public_key_calculate_context_t;


/** @brief Union holding representation of a private key for any curve type.
 */
typedef union
{
    nrf_crypto_ecc_secp160r1_private_key_t  key_secp160r1;    /**< @brief Holds internal representation of a private key for secp160r1 (NIST 160-bit). */
    nrf_crypto_ecc_secp160r2_private_key_t  key_secp160r2;    /**< @brief Holds internal representation of a private key for secp160r2 (NIST 160-bit). */
    nrf_crypto_ecc_secp192r1_private_key_t  key_secp192r1;    /**< @brief Holds internal representation of a private key for secp192r1 (NIST 192-bit). */
    nrf_crypto_ecc_secp224r1_private_key_t  key_secp224r1;    /**< @brief Holds internal representation of a private key for secp224r1 (NIST 224-bit). */
    nrf_crypto_ecc_secp256r1_private_key_t  key_secp256r1;    /**< @brief Holds internal representation of a private key for secp256r1 (NIST 256-bit). */
    nrf_crypto_ecc_secp384r1_private_key_t  key_secp384r1;    /**< @brief Holds internal representation of a private key for secp384r1 (NIST 384-bit). */
    nrf_crypto_ecc_secp521r1_private_key_t  key_secp521r1;    /**< @brief Holds internal representation of a private key for secp521r1 (NIST 521-bit). */
    nrf_crypto_ecc_secp160k1_private_key_t  key_secp160k1;    /**< @brief Holds internal representation of a private key for secp160k1 (Koblitz 160-bit). */
    nrf_crypto_ecc_secp192k1_private_key_t  key_secp192k1;    /**< @brief Holds internal representation of a private key for secp192k1 (Koblitz 192-bit). */
    nrf_crypto_ecc_secp224k1_private_key_t  key_secp224k1;    /**< @brief Holds internal representation of a private key for secp224k1 (Koblitz 224-bit). */
    nrf_crypto_ecc_secp256k1_private_key_t  key_secp256k1;    /**< @brief Holds internal representation of a private key for secp256k1 (Koblitz 256-bit). */
    nrf_crypto_ecc_bp256r1_private_key_t    key_bp256r1;      /**< @brief Holds internal representation of a private key for bp256r1 (Brainpool 256-bit). */
    nrf_crypto_ecc_bp384r1_private_key_t    key_bp384r1;      /**< @brief Holds internal representation of a private key for bp384r1 (Brainpool 384-bit). */
    nrf_crypto_ecc_bp512r1_private_key_t    key_bp512r1;      /**< @brief Holds internal representation of a private key for bp512r1 (Brainpool 512-bit). */
    nrf_crypto_ecc_curve25519_private_key_t key_curve25519;   /**< @brief Holds internal representation of a private key for Curve25519. */
    nrf_crypto_ecc_ed25519_private_key_t    key_ed25519;      /**< @brief Holds internal representation of a private key for Ed25519. */
} nrf_crypto_ecc_private_key_t;


/** @brief Union holding representation of a public key for any curve type.
 */
typedef union
{
    nrf_crypto_ecc_secp160r1_public_key_t  key_secp160r1;    /**< @brief Holds internal representation of a public key for secp160r1 (NIST 160-bit). */
    nrf_crypto_ecc_secp160r2_public_key_t  key_secp160r2;    /**< @brief Holds internal representation of a public key for secp160r2 (NIST 160-bit). */
    nrf_crypto_ecc_secp192r1_public_key_t  key_secp192r1;    /**< @brief Holds internal representation of a public key for secp192r1 (NIST 192-bit). */
    nrf_crypto_ecc_secp224r1_public_key_t  key_secp224r1;    /**< @brief Holds internal representation of a public key for secp224r1 (NIST 224-bit). */
    nrf_crypto_ecc_secp256r1_public_key_t  key_secp256r1;    /**< @brief Holds internal representation of a public key for secp256r1 (NIST 256-bit). */
    nrf_crypto_ecc_secp384r1_public_key_t  key_secp384r1;    /**< @brief Holds internal representation of a public key for secp384r1 (NIST 384-bit). */
    nrf_crypto_ecc_secp521r1_public_key_t  key_secp521r1;    /**< @brief Holds internal representation of a public key for secp521r1 (NIST 521-bit). */
    nrf_crypto_ecc_secp160k1_public_key_t  key_secp160k1;    /**< @brief Holds internal representation of a public key for secp160k1 (Koblitz 160-bit). */
    nrf_crypto_ecc_secp192k1_public_key_t  key_secp192k1;    /**< @brief Holds internal representation of a public key for secp192k1 (Koblitz 192-bit). */
    nrf_crypto_ecc_secp224k1_public_key_t  key_secp224k1;    /**< @brief Holds internal representation of a public key for secp224k1 (Koblitz 224-bit). */
    nrf_crypto_ecc_secp256k1_public_key_t  key_secp256k1;    /**< @brief Holds internal representation of a public key for secp256k1 (Koblitz 256-bit). */
    nrf_crypto_ecc_bp256r1_public_key_t    key_bp256r1;      /**< @brief Holds internal representation of a public key for bp256r1 (Brainpool 256-bit). */
    nrf_crypto_ecc_bp384r1_public_key_t    key_bp384r1;      /**< @brief Holds internal representation of a public key for bp384r1 (Brainpool 384-bit). */
    nrf_crypto_ecc_bp512r1_public_key_t    key_bp512r1;      /**< @brief Holds internal representation of a public key for bp512r1 (Brainpool 512-bit). */
    nrf_crypto_ecc_curve25519_public_key_t key_curve25519;   /**< @brief Holds internal representation of a public key for Curve25519. */
    nrf_crypto_ecc_ed25519_public_key_t    key_ed25519;      /**< @brief Holds internal representation of a public key for Ed25519. */
} nrf_crypto_ecc_public_key_t;


/** @brief Generate a new pair of a public key and a private key.
 *
 *  Generated keys have to deallocated using @ref nrf_crypto_ecc_private_key_free and
 *  @ref nrf_crypto_ecc_public_key_free.
 *  @param[in]  p_context      Pointer to temporary structure holding context information.
 *                             If it is NULL, necessary data will be allocated with
 *                             @ref NRF_CRYPTO_ALLOC and freed at the end of the function.
 *  @param[in]  p_curve_info   Pointer to information on selected curve. Use only global variables
 *                             defined by nrf_crypto, e.g. @ref g_nrf_crypto_ecc_secp256r1_curve_info.
 *  @param[out] p_private_key  Pointer to structure where newly generated private key will be put.
 *  @param[out] p_public_key   Pointer to structure where newly generated public key will be put.
 */
ret_code_t nrf_crypto_ecc_key_pair_generate(
    nrf_crypto_ecc_key_pair_generate_context_t       * p_context,
    nrf_crypto_ecc_curve_info_t                const * p_curve_info,
    nrf_crypto_ecc_private_key_t                     * p_private_key,
    nrf_crypto_ecc_public_key_t                      * p_public_key);


/** @brief Calculate public key associated with provided private key.
 *
 *  Calculated public key has to be deallocated using @ref nrf_crypto_ecc_public_key_free.
 *  @param[in]  p_context      Pointer to temporary structure holding context information.
 *                             If it is NULL, necessary data will be allocated with
 *                             @ref NRF_CRYPTO_ALLOC and freed at the end of the function.
 *  @param[in]  p_private_key  Pointer to structure holding a private key that will be used for computation.
 *  @param[out] p_public_key   Pointer to structure where newly generated public key will be put.
 */
ret_code_t nrf_crypto_ecc_public_key_calculate(
    nrf_crypto_ecc_public_key_calculate_context_t       * p_context,
    nrf_crypto_ecc_private_key_t                  const * p_private_key,
    nrf_crypto_ecc_public_key_t                         * p_public_key);


/** @brief Create a private key from a raw data.
 *
 *  Generated private key has to be deallocated using @ref nrf_crypto_ecc_private_key_free.
 * 
 *  @note Ed25519 only: Memory is allocated internally using @ref nrf_crypto_mem.
 * 
 *  @param[in]  p_curve_info   Pointer to information on selected curve. Use only global variables
 *                             defined by nrf_crypto, e.g. @ref g_nrf_crypto_ecc_secp256r1_curve_info.
 *  @param[out] p_private_key  Pointer to structure where newly converted private key will be put.
 *  @param[in]  p_raw_data     Pointer to buffer containing a big endian raw data.
 *  @param[in]  raw_data_size  Number of bytes of a raw data. Correct size for selected curve can be found in
 *                             @p p_curve_info and it is also defined by the preprocessor definitions, e.g.
 *                             @ref NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE.
 */
ret_code_t nrf_crypto_ecc_private_key_from_raw(
    nrf_crypto_ecc_curve_info_t  const * p_curve_info,
    nrf_crypto_ecc_private_key_t       * p_private_key,
    uint8_t                      const * p_raw_data,
    size_t                               raw_data_size);


/** @brief Convert a private key to a raw data.
 *
 *  @param[in]     p_private_key    Pointer to structure holding private key that will be convert.
 *  @param[out]    p_raw_data       Pointer to buffer containing a big endian raw data.
 *  @param[in,out] p_raw_data_size  Maximum number of bytes that @p p_raw_data buffer can hold on input
 *                                  and the actual number of bytes used by the raw data on output.
 *                                  Actual size for selected curve can be found in
 *                                  @ref nrf_crypto_ecc_curve_info_t and it is also defined by
 *                                  the preprocessor definitions, e.g.
 *                                  @ref NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE.
 */
ret_code_t nrf_crypto_ecc_private_key_to_raw(
    nrf_crypto_ecc_private_key_t const * p_private_key,
    uint8_t                            * p_raw_data,
    size_t                             * p_raw_data_size);


/** @brief Create a public key from a raw data.
 *
 *  Generated public key has to be deallocated using @ref nrf_crypto_ecc_public_key_free.
 *  @param[in]  p_curve_info   Pointer to information on selected curve. Use only global variables
 *                             defined by nrf_crypto, e.g. @ref g_nrf_crypto_ecc_secp256r1_curve_info.
 *  @param[out] p_public_key   Pointer to structure where newly converted public key will be put.
 *  @param[in]  p_raw_data     Pointer to buffer containing a big endian raw data.
 *  @param[in]  raw_data_size  Number of bytes of a raw data. Correct size for selected curve can be found in
 *                             @p p_curve_info and it is also defined by the preprocessor definitions, e.g.
 *                             @ref NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE.
 */
ret_code_t nrf_crypto_ecc_public_key_from_raw(
    nrf_crypto_ecc_curve_info_t const * p_curve_info,
    nrf_crypto_ecc_public_key_t       * p_public_key,
    uint8_t                     const * p_raw_data,
    size_t                              raw_data_size);


/** @brief Convert a public key to a raw data.
 *
 *  @param[in]     p_public_key     Pointer to structure holding public key that will be convert.
 *  @param[out]    p_raw_data       Pointer to buffer containing a big endian raw data.
 *  @param[in,out] p_raw_data_size  Maximum number of bytes that @p p_raw_data buffer can hold on input
 *                                  and the actual number of bytes used by the raw data on output.
 *                                  Actual size for selected curve can be found in
 *                                  @ref nrf_crypto_ecc_curve_info_t and it is also defined by
 *                                  the preprocessor definitions, e.g.
 *                                  @ref NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE.
 */
ret_code_t nrf_crypto_ecc_public_key_to_raw(
    nrf_crypto_ecc_public_key_t const * p_public_key,
    uint8_t                           * p_raw_data,
    size_t                            * p_raw_data_size);


/** @brief Release resources taken by a private key.
 *
 *  @param[in] p_private_key   Pointer to structure holding private key to release.
 */
ret_code_t nrf_crypto_ecc_private_key_free(
    nrf_crypto_ecc_private_key_t * p_private_key);


/** @brief Release resources taken by a public key.
 *
 *  @param[in] p_public_key    Pointer to structure holding public key to release.
 */
ret_code_t nrf_crypto_ecc_public_key_free(
    nrf_crypto_ecc_public_key_t * p_public_key);


/** @brief Gets curve information structure from provided key (private or public).
 *
 *  @param[in]  p_key          Pointer to structure holding private or public key.
 *  @param[out] pp_curve_info  Pointer to location where put retrieved pointer to curve information structure.
 */
ret_code_t nrf_crypto_ecc_curve_info_get(
    void                         const * p_key,
    nrf_crypto_ecc_curve_info_t const ** pp_curve_info);


/** @brief Inverts byte order of a big integers contained in a raw data.
 *
 *  All the ECC API accepts only data with big endian integers, so this function have to be used
 *  if little endian is required. If input is in little endian byte order it will be converted
 *  to big endian. If input is in big endian byte order it will be converted to little endian.
 *  It works for ECC raw private key, raw public key, signature and shared secret. If raw data
 *  contains two big integers (e.g. R, S, or X, Y) each integer is inverted separately.
 *  If @p p_curve_info is NULL then all bytes in buffer will be inverted regardless what is the
 *  content of the buffer.
 *
 *  @param[in]  p_curve_info   Pointer to information on selected curve. Use only global variables
 *                             defined by nrf_crypto, e.g. @ref g_nrf_crypto_ecc_secp256r1_curve_info.
 *  @param[in]  p_raw_input    Pointer to buffer holding source data.
 *  @param[out] p_raw_output   Pointer to buffer that will be filled with inverted byte order.
 *                             This parameter can be the same as @p p_raw_input, otherwise the
 *                             buffers cannot overlap.
 *  @param[in]  raw_data_size  Size of input and output buffer.
 */
ret_code_t nrf_crypto_ecc_byte_order_invert(
    nrf_crypto_ecc_curve_info_t const * p_curve_info,
    uint8_t                     const * p_raw_input,
    uint8_t                           * p_raw_output,
    size_t                              raw_data_size);


#ifdef __cplusplus
}
#endif

/** @}
 *  @}
 */

#endif // NRF_CRYPTO_ECC_H__
