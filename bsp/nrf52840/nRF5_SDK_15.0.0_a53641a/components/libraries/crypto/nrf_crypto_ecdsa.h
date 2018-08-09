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

#ifndef NRF_CRYPTO_ECDSA_H__
#define NRF_CRYPTO_ECDSA_H__

/** @addtogroup nrf_crypto
 *  @{
 *  @addtogroup nrf_crypto_ecdsa Elliptic Curve Digital Signature (ECDSA)
 *  @{
 *  @brief Provides elliptic curve cryptography functions for digital signature.
 *
 *  @addtogroup nrf_crypto_ecdsa_secp160r1    Definitions specific to secp160r1 (NIST 160-bit)
 *  @addtogroup nrf_crypto_ecdsa_secp160r2    Definitions specific to secp160r2 (NIST 160-bit)
 *  @addtogroup nrf_crypto_ecdsa_secp192r1    Definitions specific to secp192r1 (NIST 192-bit)
 *  @addtogroup nrf_crypto_ecdsa_secp224r1    Definitions specific to secp224r1 (NIST 224-bit)
 *  @addtogroup nrf_crypto_ecdsa_secp256r1    Definitions specific to secp256r1 (NIST 256-bit)
 *  @addtogroup nrf_crypto_ecdsa_secp384r1    Definitions specific to secp384r1 (NIST 384-bit)
 *  @addtogroup nrf_crypto_ecdsa_secp521r1    Definitions specific to secp521r1 (NIST 521-bit)
 *  @addtogroup nrf_crypto_ecdsa_secp160k1    Definitions specific to secp160k1 (Koblitz 160-bit)
 *  @addtogroup nrf_crypto_ecdsa_secp192k1    Definitions specific to secp192k1 (Koblitz 192-bit)
 *  @addtogroup nrf_crypto_ecdsa_secp224k1    Definitions specific to secp224k1 (Koblitz 224-bit)
 *  @addtogroup nrf_crypto_ecdsa_secp256k1    Definitions specific to secp256k1 (Koblitz 256-bit)
 *  @addtogroup nrf_crypto_ecdsa_bp256r1      Definitions specific to bp256r1 (Brainpool 256-bit)
 *  @addtogroup nrf_crypto_ecdsa_bp384r1      Definitions specific to bp384r1 (Brainpool 384-bit)
 *  @addtogroup nrf_crypto_ecdsa_bp512r1      Definitions specific to bp512r1 (Brainpool 512-bit)
 *  @addtogroup nrf_crypto_ecdsa_curve25519   Definitions specific to Curve25519
 *  @addtogroup nrf_crypto_ecdsa_ed25519      Definitions specific to Ed25519
 */

#include <stdint.h>
#include <stddef.h>

#include "nrf_crypto_error.h"
#include "nrf_crypto_ecc.h"
#include "nrf_crypto_ecdsa_shared.h"
#include "nrf_crypto_ecdsa_backend.h"


#ifdef __cplusplus
extern "C" {
#endif

#define NRF_CRYPTO_ECDSA_SECP160R1_SIGNATURE_SIZE  (2 * 160 / 8)   /**< @brief Size of a signature for secp160r1 (NIST 160-bit) curve.     @ingroup nrf_crypto_ecdsa_secp160r1 */
#define NRF_CRYPTO_ECDSA_SECP160R2_SIGNATURE_SIZE  (2 * 160 / 8)   /**< @brief Size of a signature for secp160r2 (NIST 160-bit) curve.     @ingroup nrf_crypto_ecdsa_secp160r2 */
#define NRF_CRYPTO_ECDSA_SECP192R1_SIGNATURE_SIZE  (2 * 192 / 8)   /**< @brief Size of a signature for secp192r1 (NIST 192-bit) curve.     @ingroup nrf_crypto_ecdsa_secp192r1 */
#define NRF_CRYPTO_ECDSA_SECP224R1_SIGNATURE_SIZE  (2 * 224 / 8)   /**< @brief Size of a signature for secp224r1 (NIST 224-bit) curve.     @ingroup nrf_crypto_ecdsa_secp224r1 */
#define NRF_CRYPTO_ECDSA_SECP256R1_SIGNATURE_SIZE  (2 * 256 / 8)   /**< @brief Size of a signature for secp256r1 (NIST 256-bit) curve.     @ingroup nrf_crypto_ecdsa_secp256r1 */
#define NRF_CRYPTO_ECDSA_SECP384R1_SIGNATURE_SIZE  (2 * 384 / 8)   /**< @brief Size of a signature for secp384r1 (NIST 384-bit) curve.     @ingroup nrf_crypto_ecdsa_secp384r1 */
#define NRF_CRYPTO_ECDSA_SECP521R1_SIGNATURE_SIZE  (2 * 528 / 8)   /**< @brief Size of a signature for secp521r1 (NIST 521-bit) curve.     @ingroup nrf_crypto_ecdsa_secp521r1 */
#define NRF_CRYPTO_ECDSA_SECP160K1_SIGNATURE_SIZE  (2 * 160 / 8)   /**< @brief Size of a signature for secp160k1 (Koblitz 160-bit) curve.  @ingroup nrf_crypto_ecdsa_secp160k1 */
#define NRF_CRYPTO_ECDSA_SECP192K1_SIGNATURE_SIZE  (2 * 192 / 8)   /**< @brief Size of a signature for secp192k1 (Koblitz 192-bit) curve.  @ingroup nrf_crypto_ecdsa_secp192k1 */
#define NRF_CRYPTO_ECDSA_SECP224K1_SIGNATURE_SIZE  (2 * 224 / 8)   /**< @brief Size of a signature for secp224k1 (Koblitz 224-bit) curve.  @ingroup nrf_crypto_ecdsa_secp224k1 */
#define NRF_CRYPTO_ECDSA_SECP256K1_SIGNATURE_SIZE  (2 * 256 / 8)   /**< @brief Size of a signature for secp256k1 (Koblitz 256-bit) curve.  @ingroup nrf_crypto_ecdsa_secp256k1 */
#define NRF_CRYPTO_ECDSA_BP256R1_SIGNATURE_SIZE    (2 * 256 / 8)   /**< @brief Size of a signature for bp256r1 (Brainpool 256-bit) curve.  @ingroup nrf_crypto_ecdsa_bp256r1 */
#define NRF_CRYPTO_ECDSA_BP384R1_SIGNATURE_SIZE    (2 * 384 / 8)   /**< @brief Size of a signature for bp384r1 (Brainpool 384-bit) curve.  @ingroup nrf_crypto_ecdsa_bp384r1 */
#define NRF_CRYPTO_ECDSA_BP512R1_SIGNATURE_SIZE    (2 * 512 / 8)   /**< @brief Size of a signature for bp512r1 (Brainpool 512-bit) curve.  @ingroup nrf_crypto_ecdsa_bp512r1 */
#define NRF_CRYPTO_ECDSA_CURVE25519_SIGNATURE_SIZE (2 * 256 / 8)   /**< @brief Size of a signature for Curve25519 curve.                   @ingroup nrf_crypto_ecdsa_curve25519 */
#define NRF_CRYPTO_ECDSA_ED25519_SIGNATURE_SIZE    (2 * 256 / 8)   /**< @brief Size of a signature for Ed25519 curve.                      @ingroup nrf_crypto_ecdsa_ed25519 */
#define NRF_CRYPTO_ECDSA_SIGNATURE_MAX_SIZE        (2 * NRF_CRYPTO_ECC_RAW_PRIVATE_KEY_MAX_SIZE)  /**< @brief Maximum size of a signature for all enabled curves. */


typedef uint8_t nrf_crypto_ecdsa_secp160r1_signature_t  [NRF_CRYPTO_ECDSA_SECP160R1_SIGNATURE_SIZE];    /**< @brief Type to hold signature output for secp160r1 (NIST 160-bit) curve.     @ingroup nrf_crypto_ecdsa_secp160r1 */
typedef uint8_t nrf_crypto_ecdsa_secp160r2_signature_t  [NRF_CRYPTO_ECDSA_SECP160R2_SIGNATURE_SIZE];    /**< @brief Type to hold signature output for secp160r2 (NIST 160-bit) curve.     @ingroup nrf_crypto_ecdsa_secp160r2 */
typedef uint8_t nrf_crypto_ecdsa_secp192r1_signature_t  [NRF_CRYPTO_ECDSA_SECP192R1_SIGNATURE_SIZE];    /**< @brief Type to hold signature output for secp192r1 (NIST 192-bit) curve.     @ingroup nrf_crypto_ecdsa_secp192r1 */
typedef uint8_t nrf_crypto_ecdsa_secp224r1_signature_t  [NRF_CRYPTO_ECDSA_SECP224R1_SIGNATURE_SIZE];    /**< @brief Type to hold signature output for secp224r1 (NIST 224-bit) curve.     @ingroup nrf_crypto_ecdsa_secp224r1 */
typedef uint8_t nrf_crypto_ecdsa_secp256r1_signature_t  [NRF_CRYPTO_ECDSA_SECP256R1_SIGNATURE_SIZE];    /**< @brief Type to hold signature output for secp256r1 (NIST 256-bit) curve.     @ingroup nrf_crypto_ecdsa_secp256r1 */
typedef uint8_t nrf_crypto_ecdsa_secp384r1_signature_t  [NRF_CRYPTO_ECDSA_SECP384R1_SIGNATURE_SIZE];    /**< @brief Type to hold signature output for secp384r1 (NIST 384-bit) curve.     @ingroup nrf_crypto_ecdsa_secp384r1 */
typedef uint8_t nrf_crypto_ecdsa_secp521r1_signature_t  [NRF_CRYPTO_ECDSA_SECP521R1_SIGNATURE_SIZE];    /**< @brief Type to hold signature output for secp521r1 (NIST 521-bit) curve.     @ingroup nrf_crypto_ecdsa_secp521r1 */
typedef uint8_t nrf_crypto_ecdsa_secp160k1_signature_t  [NRF_CRYPTO_ECDSA_SECP160K1_SIGNATURE_SIZE];    /**< @brief Type to hold signature output for secp160k1 (Koblitz 160-bit) curve.  @ingroup nrf_crypto_ecdsa_secp160k1 */
typedef uint8_t nrf_crypto_ecdsa_secp192k1_signature_t  [NRF_CRYPTO_ECDSA_SECP192K1_SIGNATURE_SIZE];    /**< @brief Type to hold signature output for secp192k1 (Koblitz 192-bit) curve.  @ingroup nrf_crypto_ecdsa_secp192k1 */
typedef uint8_t nrf_crypto_ecdsa_secp224k1_signature_t  [NRF_CRYPTO_ECDSA_SECP224K1_SIGNATURE_SIZE];    /**< @brief Type to hold signature output for secp224k1 (Koblitz 224-bit) curve.  @ingroup nrf_crypto_ecdsa_secp224k1 */
typedef uint8_t nrf_crypto_ecdsa_secp256k1_signature_t  [NRF_CRYPTO_ECDSA_SECP256K1_SIGNATURE_SIZE];    /**< @brief Type to hold signature output for secp256k1 (Koblitz 256-bit) curve.  @ingroup nrf_crypto_ecdsa_secp256k1 */
typedef uint8_t nrf_crypto_ecdsa_bp256r1_signature_t    [NRF_CRYPTO_ECDSA_BP256R1_SIGNATURE_SIZE];      /**< @brief Type to hold signature output for bp256r1 (Brainpool 256-bit) curve.  @ingroup nrf_crypto_ecdsa_bp256r1 */
typedef uint8_t nrf_crypto_ecdsa_bp384r1_signature_t    [NRF_CRYPTO_ECDSA_BP384R1_SIGNATURE_SIZE];      /**< @brief Type to hold signature output for bp384r1 (Brainpool 384-bit) curve.  @ingroup nrf_crypto_ecdsa_bp384r1 */
typedef uint8_t nrf_crypto_ecdsa_bp512r1_signature_t    [NRF_CRYPTO_ECDSA_BP512R1_SIGNATURE_SIZE];      /**< @brief Type to hold signature output for bp512r1 (Brainpool 512-bit) curve.  @ingroup nrf_crypto_ecdsa_bp512r1 */
typedef uint8_t nrf_crypto_ecdsa_curve25519_signature_t [NRF_CRYPTO_ECDSA_CURVE25519_SIGNATURE_SIZE];   /**< @brief Type to hold signature output for Curve25519 curve.                   @ingroup nrf_crypto_ecdsa_curve25519 */
typedef uint8_t nrf_crypto_ecdsa_ed25519_signature_t    [NRF_CRYPTO_ECDSA_ED25519_SIGNATURE_SIZE];      /**< @brief Type to hold signature output for Ed25519 curve.                      @ingroup nrf_crypto_ecdsa_ed25519 */
typedef uint8_t nrf_crypto_ecdsa_signature_t            [NRF_CRYPTO_ECDSA_SIGNATURE_MAX_SIZE];          /**< @brief Type big enough to hold signature output for any curve type. */


typedef nrf_crypto_backend_secp160r1_sign_context_t  nrf_crypto_ecdsa_secp160r1_sign_context_t;     /**< @brief Context used to store temporary data during signing with curve secp160r1 (NIST 160-bit).     @ingroup nrf_crypto_ecdsa_secp160r1 */
typedef nrf_crypto_backend_secp160r2_sign_context_t  nrf_crypto_ecdsa_secp160r2_sign_context_t;     /**< @brief Context used to store temporary data during signing with curve secp160r2 (NIST 160-bit).     @ingroup nrf_crypto_ecdsa_secp160r2 */
typedef nrf_crypto_backend_secp192r1_sign_context_t  nrf_crypto_ecdsa_secp192r1_sign_context_t;     /**< @brief Context used to store temporary data during signing with curve secp192r1 (NIST 192-bit).     @ingroup nrf_crypto_ecdsa_secp192r1 */
typedef nrf_crypto_backend_secp224r1_sign_context_t  nrf_crypto_ecdsa_secp224r1_sign_context_t;     /**< @brief Context used to store temporary data during signing with curve secp224r1 (NIST 224-bit).     @ingroup nrf_crypto_ecdsa_secp224r1 */
typedef nrf_crypto_backend_secp256r1_sign_context_t  nrf_crypto_ecdsa_secp256r1_sign_context_t;     /**< @brief Context used to store temporary data during signing with curve secp256r1 (NIST 256-bit).     @ingroup nrf_crypto_ecdsa_secp256r1 */
typedef nrf_crypto_backend_secp384r1_sign_context_t  nrf_crypto_ecdsa_secp384r1_sign_context_t;     /**< @brief Context used to store temporary data during signing with curve secp384r1 (NIST 384-bit).     @ingroup nrf_crypto_ecdsa_secp384r1 */
typedef nrf_crypto_backend_secp521r1_sign_context_t  nrf_crypto_ecdsa_secp521r1_sign_context_t;     /**< @brief Context used to store temporary data during signing with curve secp521r1 (NIST 521-bit).     @ingroup nrf_crypto_ecdsa_secp521r1 */
typedef nrf_crypto_backend_secp160k1_sign_context_t  nrf_crypto_ecdsa_secp160k1_sign_context_t;     /**< @brief Context used to store temporary data during signing with curve secp160k1 (Koblitz 160-bit).  @ingroup nrf_crypto_ecdsa_secp160k1 */
typedef nrf_crypto_backend_secp192k1_sign_context_t  nrf_crypto_ecdsa_secp192k1_sign_context_t;     /**< @brief Context used to store temporary data during signing with curve secp192k1 (Koblitz 192-bit).  @ingroup nrf_crypto_ecdsa_secp192k1 */
typedef nrf_crypto_backend_secp224k1_sign_context_t  nrf_crypto_ecdsa_secp224k1_sign_context_t;     /**< @brief Context used to store temporary data during signing with curve secp224k1 (Koblitz 224-bit).  @ingroup nrf_crypto_ecdsa_secp224k1 */
typedef nrf_crypto_backend_secp256k1_sign_context_t  nrf_crypto_ecdsa_secp256k1_sign_context_t;     /**< @brief Context used to store temporary data during signing with curve secp256k1 (Koblitz 256-bit).  @ingroup nrf_crypto_ecdsa_secp256k1 */
typedef nrf_crypto_backend_bp256r1_sign_context_t    nrf_crypto_ecdsa_bp256r1_sign_context_t;       /**< @brief Context used to store temporary data during signing with curve bp256r1 (Brainpool 256-bit).  @ingroup nrf_crypto_ecdsa_bp256r1 */
typedef nrf_crypto_backend_bp384r1_sign_context_t    nrf_crypto_ecdsa_bp384r1_sign_context_t;       /**< @brief Context used to store temporary data during signing with curve bp384r1 (Brainpool 384-bit).  @ingroup nrf_crypto_ecdsa_bp384r1 */
typedef nrf_crypto_backend_bp512r1_sign_context_t    nrf_crypto_ecdsa_bp512r1_sign_context_t;       /**< @brief Context used to store temporary data during signing with curve bp512r1 (Brainpool 512-bit).  @ingroup nrf_crypto_ecdsa_bp512r1 */
typedef nrf_crypto_backend_curve25519_sign_context_t nrf_crypto_ecdsa_curve25519_sign_context_t;    /**< @brief Context used to store temporary data during signing with curve Curve25519.                   @ingroup nrf_crypto_ecdsa_curve25519 */
typedef nrf_crypto_backend_ed25519_sign_context_t    nrf_crypto_ecdsa_ed25519_sign_context_t;       /**< @brief Context used to store temporary data during signing with curve Ed25519.                      @ingroup nrf_crypto_ecdsa_ed25519 */


typedef nrf_crypto_backend_secp160r1_verify_context_t  nrf_crypto_ecdsa_secp160r1_verify_context_t;     /**< @brief Context used to store temporary data during verifying with curve secp160r1 (NIST 160-bit).     @ingroup nrf_crypto_ecdsa_secp160r1 */
typedef nrf_crypto_backend_secp160r2_verify_context_t  nrf_crypto_ecdsa_secp160r2_verify_context_t;     /**< @brief Context used to store temporary data during verifying with curve secp160r2 (NIST 160-bit).     @ingroup nrf_crypto_ecdsa_secp160r2 */
typedef nrf_crypto_backend_secp192r1_verify_context_t  nrf_crypto_ecdsa_secp192r1_verify_context_t;     /**< @brief Context used to store temporary data during verifying with curve secp192r1 (NIST 192-bit).     @ingroup nrf_crypto_ecdsa_secp192r1 */
typedef nrf_crypto_backend_secp224r1_verify_context_t  nrf_crypto_ecdsa_secp224r1_verify_context_t;     /**< @brief Context used to store temporary data during verifying with curve secp224r1 (NIST 224-bit).     @ingroup nrf_crypto_ecdsa_secp224r1 */
typedef nrf_crypto_backend_secp256r1_verify_context_t  nrf_crypto_ecdsa_secp256r1_verify_context_t;     /**< @brief Context used to store temporary data during verifying with curve secp256r1 (NIST 256-bit).     @ingroup nrf_crypto_ecdsa_secp256r1 */
typedef nrf_crypto_backend_secp384r1_verify_context_t  nrf_crypto_ecdsa_secp384r1_verify_context_t;     /**< @brief Context used to store temporary data during verifying with curve secp384r1 (NIST 384-bit).     @ingroup nrf_crypto_ecdsa_secp384r1 */
typedef nrf_crypto_backend_secp521r1_verify_context_t  nrf_crypto_ecdsa_secp521r1_verify_context_t;     /**< @brief Context used to store temporary data during verifying with curve secp521r1 (NIST 521-bit).     @ingroup nrf_crypto_ecdsa_secp521r1 */
typedef nrf_crypto_backend_secp160k1_verify_context_t  nrf_crypto_ecdsa_secp160k1_verify_context_t;     /**< @brief Context used to store temporary data during verifying with curve secp160k1 (Koblitz 160-bit).  @ingroup nrf_crypto_ecdsa_secp160k1 */
typedef nrf_crypto_backend_secp192k1_verify_context_t  nrf_crypto_ecdsa_secp192k1_verify_context_t;     /**< @brief Context used to store temporary data during verifying with curve secp192k1 (Koblitz 192-bit).  @ingroup nrf_crypto_ecdsa_secp192k1 */
typedef nrf_crypto_backend_secp224k1_verify_context_t  nrf_crypto_ecdsa_secp224k1_verify_context_t;     /**< @brief Context used to store temporary data during verifying with curve secp224k1 (Koblitz 224-bit).  @ingroup nrf_crypto_ecdsa_secp224k1 */
typedef nrf_crypto_backend_secp256k1_verify_context_t  nrf_crypto_ecdsa_secp256k1_verify_context_t;     /**< @brief Context used to store temporary data during verifying with curve secp256k1 (Koblitz 256-bit).  @ingroup nrf_crypto_ecdsa_secp256k1 */
typedef nrf_crypto_backend_bp256r1_verify_context_t    nrf_crypto_ecdsa_bp256r1_verify_context_t;       /**< @brief Context used to store temporary data during verifying with curve bp256r1 (Brainpool 256-bit).  @ingroup nrf_crypto_ecdsa_bp256r1 */
typedef nrf_crypto_backend_bp384r1_verify_context_t    nrf_crypto_ecdsa_bp384r1_verify_context_t;       /**< @brief Context used to store temporary data during verifying with curve bp384r1 (Brainpool 384-bit).  @ingroup nrf_crypto_ecdsa_bp384r1 */
typedef nrf_crypto_backend_bp512r1_verify_context_t    nrf_crypto_ecdsa_bp512r1_verify_context_t;       /**< @brief Context used to store temporary data during verifying with curve bp512r1 (Brainpool 512-bit).  @ingroup nrf_crypto_ecdsa_bp512r1 */
typedef nrf_crypto_backend_curve25519_verify_context_t nrf_crypto_ecdsa_curve25519_verify_context_t;    /**< @brief Context used to store temporary data during verifying with curve Curve25519.                   @ingroup nrf_crypto_ecdsa_curve25519 */
typedef nrf_crypto_backend_ed25519_verify_context_t    nrf_crypto_ecdsa_ed25519_verify_context_t;       /**< @brief Context used to store temporary data during verifying with curve Ed25519.                      @ingroup nrf_crypto_ecdsa_ed25519 */


/** @brief Union holding a context for ECDSA hash sign.
 */
typedef union
{
    nrf_crypto_ecdsa_secp160r1_sign_context_t  context_secp160r1;    /**< @brief Occupies space for secp160r1 (NIST 160-bit). */
    nrf_crypto_ecdsa_secp160r2_sign_context_t  context_secp160r2;    /**< @brief Occupies space for secp160r2 (NIST 160-bit). */
    nrf_crypto_ecdsa_secp192r1_sign_context_t  context_secp192r1;    /**< @brief Occupies space for secp192r1 (NIST 192-bit). */
    nrf_crypto_ecdsa_secp224r1_sign_context_t  context_secp224r1;    /**< @brief Occupies space for secp224r1 (NIST 224-bit). */
    nrf_crypto_ecdsa_secp256r1_sign_context_t  context_secp256r1;    /**< @brief Occupies space for secp256r1 (NIST 256-bit). */
    nrf_crypto_ecdsa_secp384r1_sign_context_t  context_secp384r1;    /**< @brief Occupies space for secp384r1 (NIST 384-bit). */
    nrf_crypto_ecdsa_secp521r1_sign_context_t  context_secp521r1;    /**< @brief Occupies space for secp521r1 (NIST 521-bit). */
    nrf_crypto_ecdsa_secp160k1_sign_context_t  context_secp160k1;    /**< @brief Occupies space for secp160k1 (Koblitz 160-bit). */
    nrf_crypto_ecdsa_secp192k1_sign_context_t  context_secp192k1;    /**< @brief Occupies space for secp192k1 (Koblitz 192-bit). */
    nrf_crypto_ecdsa_secp224k1_sign_context_t  context_secp224k1;    /**< @brief Occupies space for secp224k1 (Koblitz 224-bit). */
    nrf_crypto_ecdsa_secp256k1_sign_context_t  context_secp256k1;    /**< @brief Occupies space for secp256k1 (Koblitz 256-bit). */
    nrf_crypto_ecdsa_bp256r1_sign_context_t    context_bp256r1;      /**< @brief Occupies space for bp256r1 (Brainpool 256-bit). */
    nrf_crypto_ecdsa_bp384r1_sign_context_t    context_bp384r1;      /**< @brief Occupies space for bp384r1 (Brainpool 384-bit). */
    nrf_crypto_ecdsa_bp512r1_sign_context_t    context_bp512r1;      /**< @brief Occupies space for bp512r1 (Brainpool 512-bit). */
    nrf_crypto_ecdsa_curve25519_sign_context_t context_curve25519;   /**< @brief Occupies space for Curve25519. */
    nrf_crypto_ecdsa_ed25519_sign_context_t    context_ed25519;      /**< @brief Occupies space for Ed25519. */
} nrf_crypto_ecdsa_sign_context_t;


/** @brief Union holding a context for ECDSA hash verify.
 */
typedef union
{
    nrf_crypto_ecdsa_secp160r1_verify_context_t  context_secp160r1;     /**< @brief Occupies spece for secp160r1 (NIST 160-bit). */
    nrf_crypto_ecdsa_secp160r2_verify_context_t  context_secp160r2;     /**< @brief Occupies spece for secp160r2 (NIST 160-bit). */
    nrf_crypto_ecdsa_secp192r1_verify_context_t  context_secp192r1;     /**< @brief Occupies spece for secp192r1 (NIST 192-bit). */
    nrf_crypto_ecdsa_secp224r1_verify_context_t  context_secp224r1;     /**< @brief Occupies spece for secp224r1 (NIST 224-bit). */
    nrf_crypto_ecdsa_secp256r1_verify_context_t  context_secp256r1;     /**< @brief Occupies spece for secp256r1 (NIST 256-bit). */
    nrf_crypto_ecdsa_secp384r1_verify_context_t  context_secp384r1;     /**< @brief Occupies spece for secp384r1 (NIST 384-bit). */
    nrf_crypto_ecdsa_secp521r1_verify_context_t  context_secp521r1;     /**< @brief Occupies spece for secp521r1 (NIST 521-bit). */
    nrf_crypto_ecdsa_secp160k1_verify_context_t  context_secp160k1;     /**< @brief Occupies spece for secp160k1 (Koblitz 160-bit). */
    nrf_crypto_ecdsa_secp192k1_verify_context_t  context_secp192k1;     /**< @brief Occupies spece for secp192k1 (Koblitz 192-bit). */
    nrf_crypto_ecdsa_secp224k1_verify_context_t  context_secp224k1;     /**< @brief Occupies spece for secp224k1 (Koblitz 224-bit). */
    nrf_crypto_ecdsa_secp256k1_verify_context_t  context_secp256k1;     /**< @brief Occupies spece for secp256k1 (Koblitz 256-bit). */
    nrf_crypto_ecdsa_bp256r1_verify_context_t    context_bp256r1;       /**< @brief Occupies spece for bp256r1 (Brainpool 256-bit). */
    nrf_crypto_ecdsa_bp384r1_verify_context_t    context_bp384r1;       /**< @brief Occupies spece for bp384r1 (Brainpool 384-bit). */
    nrf_crypto_ecdsa_bp512r1_verify_context_t    context_bp512r1;       /**< @brief Occupies spece for bp512r1 (Brainpool 512-bit). */
    nrf_crypto_ecdsa_curve25519_verify_context_t context_curve25519;    /**< @brief Occupies spece for Curve25519. */
    nrf_crypto_ecdsa_ed25519_verify_context_t    context_ed25519;       /**< @brief Occupies spece for Ed25519. */
} nrf_crypto_ecdsa_verify_context_t;


/** @brief Sign a hash of a message.
 *
 *  @param[in]     p_context         Pointer to temporary structure holding context information.
 *                                   If it is NULL, necessary data will be allocated with
 *                                   @ref NRF_CRYPTO_ALLOC and freed at the end of the function.
 *  @param[in]     p_private_key     Pointer to structure holding a private key.
 *  @param[in]     p_hash            Pointer to hash to sign.
 *  @param[in]     hash_size         Number of bytes in p_hash.
 *  @param[out]    p_signature       Pointer to buffer where digital signature will be put.
 *  @param[in,out] p_signature_size  Maximum number of bytes that @p p_signature buffer can hold on input
 *                                   and the actual number of bytes used by the data on output.
 *                                   Actual size for selected curve is defined by
 *                                   the preprocessor definitions, e.g.
 *                                   @ref NRF_CRYPTO_ECDSA_SECP256R1_SIGNATURE_SIZE.
 */
ret_code_t nrf_crypto_ecdsa_sign(
    nrf_crypto_ecdsa_sign_context_t       * p_context,
    nrf_crypto_ecc_private_key_t    const * p_private_key,
    uint8_t                         const * p_hash,
    size_t                                  hash_size,
    uint8_t                               * p_signature,
    size_t                                * p_signature_size);


/** @brief Verify a signature using a hash of a message.
 *
 *  @param[in]     p_context       Pointer to temporary structure holding context information.
 *                                 If it is NULL, necessary data will be allocated with
 *                                 @ref NRF_CRYPTO_ALLOC and freed at the end of the function.
 *  @param[in]     p_public_key    Pointer to structure holding a public key.
 *  @param[in]     p_hash          Pointer to hash to verify.
 *  @param[in]     hash_size       Number of bytes in p_hash.
 *  @param[in]     p_signature     Pointer to buffer containing digital signature.
 *  @param[in,out] signature_size  Number of bytes in p_signature.
 */
ret_code_t nrf_crypto_ecdsa_verify(
    nrf_crypto_ecdsa_verify_context_t       * p_context,
    nrf_crypto_ecc_public_key_t       const * p_public_key,
    uint8_t                           const * p_hash,
    size_t                                    hash_size,
    uint8_t                           const * p_signature,
    size_t                                    signature_size);

#ifdef __cplusplus
}
#endif

/** @}
 *  @}
 */

#endif // NRF_CRYPTO_ECDSA_H__
