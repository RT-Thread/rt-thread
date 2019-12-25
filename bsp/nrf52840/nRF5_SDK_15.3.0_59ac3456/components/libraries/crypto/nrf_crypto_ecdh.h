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

#ifndef NRF_CRYPTO_ECDH_H__
#define NRF_CRYPTO_ECDH_H__

/** @addtogroup nrf_crypto
 *  @{
 *  @addtogroup nrf_crypto_ecdh Elliptic Curve Diffie-Hellman (ECDH)
 *  @{
 *  @brief Provides elliptic curve cryptography functions for Diffie-Hellman shared secret exchange.
 *
 *  @addtogroup nrf_crypto_ecdh_secp160r1   Definitions specific to secp160r1 (NIST 160-bit)
 *  @addtogroup nrf_crypto_ecdh_secp160r2   Definitions specific to secp160r2 (NIST 160-bit)
 *  @addtogroup nrf_crypto_ecdh_secp192r1   Definitions specific to secp192r1 (NIST 192-bit)
 *  @addtogroup nrf_crypto_ecdh_secp224r1   Definitions specific to secp224r1 (NIST 224-bit)
 *  @addtogroup nrf_crypto_ecdh_secp256r1   Definitions specific to secp256r1 (NIST 256-bit)
 *  @addtogroup nrf_crypto_ecdh_secp384r1   Definitions specific to secp384r1 (NIST 384-bit)
 *  @addtogroup nrf_crypto_ecdh_secp521r1   Definitions specific to secp521r1 (NIST 521-bit)
 *  @addtogroup nrf_crypto_ecdh_secp160k1   Definitions specific to secp160k1 (Koblitz 160-bit)
 *  @addtogroup nrf_crypto_ecdh_secp192k1   Definitions specific to secp192k1 (Koblitz 192-bit)
 *  @addtogroup nrf_crypto_ecdh_secp224k1   Definitions specific to secp224k1 (Koblitz 224-bit)
 *  @addtogroup nrf_crypto_ecdh_secp256k1   Definitions specific to secp256k1 (Koblitz 256-bit)
 *  @addtogroup nrf_crypto_ecdh_bp256r1     Definitions specific to bp256r1 (Brainpool 256-bit)
 *  @addtogroup nrf_crypto_ecdh_bp384r1     Definitions specific to bp384r1 (Brainpool 384-bit)
 *  @addtogroup nrf_crypto_ecdh_bp512r1     Definitions specific to bp512r1 (Brainpool 512-bit)
 *  @addtogroup nrf_crypto_ecdh_curve25519  Definitions specific to Curve25519
 */

#include <stdint.h>
#include <stddef.h>

#include "nrf_crypto_error.h"
#include "nrf_crypto_ecc.h"
#include "nrf_crypto_ecdh_shared.h"
#include "nrf_crypto_ecdh_backend.h"

#ifdef __cplusplus
extern "C" {
#endif


#define NRF_CRYPTO_ECDH_SECP160R1_SHARED_SECRET_SIZE  (160 / 8)   /**< @brief Number of bytes in a shared secret using secp160r1 (NIST 160-bit).     @ingroup nrf_crypto_ecdh_secp160r1 */
#define NRF_CRYPTO_ECDH_SECP160R2_SHARED_SECRET_SIZE  (160 / 8)   /**< @brief Number of bytes in a shared secret using secp160r2 (NIST 160-bit).     @ingroup nrf_crypto_ecdh_secp160r2 */
#define NRF_CRYPTO_ECDH_SECP192R1_SHARED_SECRET_SIZE  (192 / 8)   /**< @brief Number of bytes in a shared secret using secp192r1 (NIST 192-bit).     @ingroup nrf_crypto_ecdh_secp192r1 */
#define NRF_CRYPTO_ECDH_SECP224R1_SHARED_SECRET_SIZE  (224 / 8)   /**< @brief Number of bytes in a shared secret using secp224r1 (NIST 224-bit).     @ingroup nrf_crypto_ecdh_secp224r1 */
#define NRF_CRYPTO_ECDH_SECP256R1_SHARED_SECRET_SIZE  (256 / 8)   /**< @brief Number of bytes in a shared secret using secp256r1 (NIST 256-bit).     @ingroup nrf_crypto_ecdh_secp256r1 */
#define NRF_CRYPTO_ECDH_SECP384R1_SHARED_SECRET_SIZE  (384 / 8)   /**< @brief Number of bytes in a shared secret using secp384r1 (NIST 384-bit).     @ingroup nrf_crypto_ecdh_secp384r1 */
#define NRF_CRYPTO_ECDH_SECP521R1_SHARED_SECRET_SIZE  (528 / 8)   /**< @brief Number of bytes in a shared secret using secp521r1 (NIST 521-bit).     @ingroup nrf_crypto_ecdh_secp521r1 */
#define NRF_CRYPTO_ECDH_SECP160K1_SHARED_SECRET_SIZE  (160 / 8)   /**< @brief Number of bytes in a shared secret using secp160k1 (Koblitz 160-bit).  @ingroup nrf_crypto_ecdh_secp160k1 */
#define NRF_CRYPTO_ECDH_SECP192K1_SHARED_SECRET_SIZE  (192 / 8)   /**< @brief Number of bytes in a shared secret using secp192k1 (Koblitz 192-bit).  @ingroup nrf_crypto_ecdh_secp192k1 */
#define NRF_CRYPTO_ECDH_SECP224K1_SHARED_SECRET_SIZE  (224 / 8)   /**< @brief Number of bytes in a shared secret using secp224k1 (Koblitz 224-bit).  @ingroup nrf_crypto_ecdh_secp224k1 */
#define NRF_CRYPTO_ECDH_SECP256K1_SHARED_SECRET_SIZE  (256 / 8)   /**< @brief Number of bytes in a shared secret using secp256k1 (Koblitz 256-bit).  @ingroup nrf_crypto_ecdh_secp256k1 */
#define NRF_CRYPTO_ECDH_BP256R1_SHARED_SECRET_SIZE    (256 / 8)   /**< @brief Number of bytes in a shared secret using bp256r1 (Brainpool 256-bit).  @ingroup nrf_crypto_ecdh_bp256r1 */
#define NRF_CRYPTO_ECDH_BP384R1_SHARED_SECRET_SIZE    (384 / 8)   /**< @brief Number of bytes in a shared secret using bp384r1 (Brainpool 384-bit).  @ingroup nrf_crypto_ecdh_bp384r1 */
#define NRF_CRYPTO_ECDH_BP512R1_SHARED_SECRET_SIZE    (512 / 8)   /**< @brief Number of bytes in a shared secret using bp512r1 (Brainpool 512-bit).  @ingroup nrf_crypto_ecdh_bp512r1 */
#define NRF_CRYPTO_ECDH_CURVE25519_SHARED_SECRET_SIZE (256 / 8)   /**< @brief Number of bytes in a shared secret using Curve25519.                   @ingroup nrf_crypto_ecdh_curve25519 */
#define NRF_CRYPTO_ECDH_SHARED_SECRET_MAX_SIZE        NRF_CRYPTO_ECC_RAW_PRIVATE_KEY_MAX_SIZE  /**< @brief Maximum size of a shared secret in bytes for all enabled curves. */


typedef nrf_crypto_backend_secp160r1_ecdh_context_t  nrf_crypto_ecdh_secp160r1_context_t;    /**< @brief Context used to store temporary data during computing ECDH for curve secp160r1 (NIST 160-bit).     @ingroup nrf_crypto_ecdh_secp160r1 */
typedef nrf_crypto_backend_secp160r2_ecdh_context_t  nrf_crypto_ecdh_secp160r2_context_t;    /**< @brief Context used to store temporary data during computing ECDH for curve secp160r2 (NIST 160-bit).     @ingroup nrf_crypto_ecdh_secp160r2 */
typedef nrf_crypto_backend_secp192r1_ecdh_context_t  nrf_crypto_ecdh_secp192r1_context_t;    /**< @brief Context used to store temporary data during computing ECDH for curve secp192r1 (NIST 192-bit).     @ingroup nrf_crypto_ecdh_secp192r1 */
typedef nrf_crypto_backend_secp224r1_ecdh_context_t  nrf_crypto_ecdh_secp224r1_context_t;    /**< @brief Context used to store temporary data during computing ECDH for curve secp224r1 (NIST 224-bit).     @ingroup nrf_crypto_ecdh_secp224r1 */
typedef nrf_crypto_backend_secp256r1_ecdh_context_t  nrf_crypto_ecdh_secp256r1_context_t;    /**< @brief Context used to store temporary data during computing ECDH for curve secp256r1 (NIST 256-bit).     @ingroup nrf_crypto_ecdh_secp256r1 */
typedef nrf_crypto_backend_secp384r1_ecdh_context_t  nrf_crypto_ecdh_secp384r1_context_t;    /**< @brief Context used to store temporary data during computing ECDH for curve secp384r1 (NIST 384-bit).     @ingroup nrf_crypto_ecdh_secp384r1 */
typedef nrf_crypto_backend_secp521r1_ecdh_context_t  nrf_crypto_ecdh_secp521r1_context_t;    /**< @brief Context used to store temporary data during computing ECDH for curve secp521r1 (NIST 521-bit).     @ingroup nrf_crypto_ecdh_secp521r1 */
typedef nrf_crypto_backend_secp160k1_ecdh_context_t  nrf_crypto_ecdh_secp160k1_context_t;    /**< @brief Context used to store temporary data during computing ECDH for curve secp160k1 (Koblitz 160-bit).  @ingroup nrf_crypto_ecdh_secp160k1 */
typedef nrf_crypto_backend_secp192k1_ecdh_context_t  nrf_crypto_ecdh_secp192k1_context_t;    /**< @brief Context used to store temporary data during computing ECDH for curve secp192k1 (Koblitz 192-bit).  @ingroup nrf_crypto_ecdh_secp192k1 */
typedef nrf_crypto_backend_secp224k1_ecdh_context_t  nrf_crypto_ecdh_secp224k1_context_t;    /**< @brief Context used to store temporary data during computing ECDH for curve secp224k1 (Koblitz 224-bit).  @ingroup nrf_crypto_ecdh_secp224k1 */
typedef nrf_crypto_backend_secp256k1_ecdh_context_t  nrf_crypto_ecdh_secp256k1_context_t;    /**< @brief Context used to store temporary data during computing ECDH for curve secp256k1 (Koblitz 256-bit).  @ingroup nrf_crypto_ecdh_secp256k1 */
typedef nrf_crypto_backend_bp256r1_ecdh_context_t    nrf_crypto_ecdh_bp256r1_context_t;      /**< @brief Context used to store temporary data during computing ECDH for curve bp256r1 (Brainpool 256-bit).  @ingroup nrf_crypto_ecdh_bp256r1 */
typedef nrf_crypto_backend_bp384r1_ecdh_context_t    nrf_crypto_ecdh_bp384r1_context_t;      /**< @brief Context used to store temporary data during computing ECDH for curve bp384r1 (Brainpool 384-bit).  @ingroup nrf_crypto_ecdh_bp384r1 */
typedef nrf_crypto_backend_bp512r1_ecdh_context_t    nrf_crypto_ecdh_bp512r1_context_t;      /**< @brief Context used to store temporary data during computing ECDH for curve bp512r1 (Brainpool 512-bit).  @ingroup nrf_crypto_ecdh_bp512r1 */
typedef nrf_crypto_backend_curve25519_ecdh_context_t nrf_crypto_ecdh_curve25519_context_t;   /**< @brief Context used to store temporary data during computing ECDH for curve Curve25519.                   @ingroup nrf_crypto_ecdh_curve25519 */


typedef uint8_t nrf_crypto_ecdh_secp160r1_shared_secret_t
    [NRF_CRYPTO_ECDH_SECP160R1_SHARED_SECRET_SIZE];        /**< @brief Array type of a shared secret for curve secp160r1 (NIST 160-bit).  @ingroup nrf_crypto_ecdh_secp160r1 */
typedef uint8_t nrf_crypto_ecdh_secp160r2_shared_secret_t
    [NRF_CRYPTO_ECDH_SECP160R2_SHARED_SECRET_SIZE];        /**< @brief Array type of a shared secret for curve secp160r2 (NIST 160-bit).  @ingroup nrf_crypto_ecdh_secp160r2 */
typedef uint8_t nrf_crypto_ecdh_secp192r1_shared_secret_t
    [NRF_CRYPTO_ECDH_SECP192R1_SHARED_SECRET_SIZE];        /**< @brief Array type of a shared secret for curve secp192r1 (NIST 192-bit).  @ingroup nrf_crypto_ecdh_secp192r1 */
typedef uint8_t nrf_crypto_ecdh_secp224r1_shared_secret_t
    [NRF_CRYPTO_ECDH_SECP224R1_SHARED_SECRET_SIZE];        /**< @brief Array type of a shared secret for curve secp224r1 (NIST 224-bit).  @ingroup nrf_crypto_ecdh_secp224r1 */
typedef uint8_t nrf_crypto_ecdh_secp256r1_shared_secret_t
    [NRF_CRYPTO_ECDH_SECP256R1_SHARED_SECRET_SIZE];        /**< @brief Array type of a shared secret for curve secp256r1 (NIST 256-bit).  @ingroup nrf_crypto_ecdh_secp256r1 */
typedef uint8_t nrf_crypto_ecdh_secp384r1_shared_secret_t
    [NRF_CRYPTO_ECDH_SECP384R1_SHARED_SECRET_SIZE];        /**< @brief Array type of a shared secret for curve secp384r1 (NIST 384-bit).  @ingroup nrf_crypto_ecdh_secp384r1 */
typedef uint8_t nrf_crypto_ecdh_secp521r1_shared_secret_t
    [NRF_CRYPTO_ECDH_SECP521R1_SHARED_SECRET_SIZE];        /**< @brief Array type of a shared secret for curve secp521r1 (NIST 521-bit).  @ingroup nrf_crypto_ecdh_secp521r1 */
typedef uint8_t nrf_crypto_ecdh_secp160k1_shared_secret_t
    [NRF_CRYPTO_ECDH_SECP160K1_SHARED_SECRET_SIZE];        /**< @brief Array type of a shared secret for curve secp160k1 (Koblitz 160-bit).  @ingroup nrf_crypto_ecdh_secp160k1 */
typedef uint8_t nrf_crypto_ecdh_secp192k1_shared_secret_t
    [NRF_CRYPTO_ECDH_SECP192K1_SHARED_SECRET_SIZE];        /**< @brief Array type of a shared secret for curve secp192k1 (Koblitz 192-bit).  @ingroup nrf_crypto_ecdh_secp192k1 */
typedef uint8_t nrf_crypto_ecdh_secp224k1_shared_secret_t
    [NRF_CRYPTO_ECDH_SECP224K1_SHARED_SECRET_SIZE];        /**< @brief Array type of a shared secret for curve secp224k1 (Koblitz 224-bit).  @ingroup nrf_crypto_ecdh_secp224k1 */
typedef uint8_t nrf_crypto_ecdh_secp256k1_shared_secret_t
    [NRF_CRYPTO_ECDH_SECP256K1_SHARED_SECRET_SIZE];        /**< @brief Array type of a shared secret for curve secp256k1 (Koblitz 256-bit).  @ingroup nrf_crypto_ecdh_secp256k1 */
typedef uint8_t nrf_crypto_ecdh_bp256r1_shared_secret_t
    [NRF_CRYPTO_ECDH_BP256R1_SHARED_SECRET_SIZE];          /**< @brief Array type of a shared secret for curve bp256r1 (Brainpool 256-bit).  @ingroup nrf_crypto_ecdh_bp256r1 */
typedef uint8_t nrf_crypto_ecdh_bp384r1_shared_secret_t
    [NRF_CRYPTO_ECDH_BP384R1_SHARED_SECRET_SIZE];          /**< @brief Array type of a shared secret for curve bp384r1 (Brainpool 384-bit).  @ingroup nrf_crypto_ecdh_bp384r1 */
typedef uint8_t nrf_crypto_ecdh_bp512r1_shared_secret_t
    [NRF_CRYPTO_ECDH_BP512R1_SHARED_SECRET_SIZE];          /**< @brief Array type of a shared secret for curve bp512r1 (Brainpool 512-bit).  @ingroup nrf_crypto_ecdh_bp512r1 */
typedef uint8_t nrf_crypto_ecdh_curve25519_shared_secret_t
    [NRF_CRYPTO_ECDH_CURVE25519_SHARED_SECRET_SIZE];       /**< @brief Array type of a shared secret for curve Curve25519.  @ingroup nrf_crypto_ecdh_curve25519 */
typedef uint8_t nrf_crypto_ecdh_shared_secret_t
    [NRF_CRYPTO_ECDH_SHARED_SECRET_MAX_SIZE];              /**< @brief Array type of a shared secret for any of the enabled curves. */


/** @brief Union holding a context for ECDH computation.
 */
typedef union
{
    nrf_crypto_ecdh_secp160r1_context_t  context_secp160r1;   /**< @brief Occupies space for secp160r1 (NIST 160-bit). */
    nrf_crypto_ecdh_secp160r2_context_t  context_secp160r2;   /**< @brief Occupies space for secp160r2 (NIST 160-bit). */
    nrf_crypto_ecdh_secp192r1_context_t  context_secp192r1;   /**< @brief Occupies space for secp192r1 (NIST 192-bit). */
    nrf_crypto_ecdh_secp224r1_context_t  context_secp224r1;   /**< @brief Occupies space for secp224r1 (NIST 224-bit). */
    nrf_crypto_ecdh_secp256r1_context_t  context_secp256r1;   /**< @brief Occupies space for secp256r1 (NIST 256-bit). */
    nrf_crypto_ecdh_secp384r1_context_t  context_secp384r1;   /**< @brief Occupies space for secp384r1 (NIST 384-bit). */
    nrf_crypto_ecdh_secp521r1_context_t  context_secp521r1;   /**< @brief Occupies space for secp521r1 (NIST 521-bit). */
    nrf_crypto_ecdh_secp160k1_context_t  context_secp160k1;   /**< @brief Occupies space for secp160k1 (Koblitz 160-bit). */
    nrf_crypto_ecdh_secp192k1_context_t  context_secp192k1;   /**< @brief Occupies space for secp192k1 (Koblitz 192-bit). */
    nrf_crypto_ecdh_secp224k1_context_t  context_secp224k1;   /**< @brief Occupies space for secp224k1 (Koblitz 224-bit). */
    nrf_crypto_ecdh_secp256k1_context_t  context_secp256k1;   /**< @brief Occupies space for secp256k1 (Koblitz 256-bit). */
    nrf_crypto_ecdh_bp256r1_context_t    context_bp256r1;     /**< @brief Occupies space for bp256r1 (Brainpool 256-bit). */
    nrf_crypto_ecdh_bp384r1_context_t    context_bp384r1;     /**< @brief Occupies space for bp384r1 (Brainpool 384-bit). */
    nrf_crypto_ecdh_bp512r1_context_t    context_bp512r1;     /**< @brief Occupies space for bp512r1 (Brainpool 512-bit). */
    nrf_crypto_ecdh_curve25519_context_t context_curve25519;  /**< @brief Occupies space for Curve25519. */
} nrf_crypto_ecdh_context_t;


/** @brief Computes shared secret using ECC Diffie-Hellman.
 *
 *  @param[in]     p_context             Pointer to temporary structure holding context information.
 *                                       If it is NULL, necessary data will be allocated with
 *                                       @ref NRF_CRYPTO_ALLOC and freed at the end of the function.
 *  @param[in]     p_private_key         Pointer to structure holding a private key.
 *  @param[in]     p_public_key          Pointer to structure holding a public key received from the other party.
 *  @param[out]    p_shared_secret       Pointer to buffer where shared secret will be put.
 *  @param[in,out] p_shared_secret_size  Maximum number of bytes that @p p_shared_secret buffer can hold on input
 *                                       and the actual number of bytes used by the data on output.
 *                                       Actual size for selected curve is defined by
 *                                       the preprocessor definitions, e.g.
 *                                       @ref NRF_CRYPTO_ECDH_SECP256R1_SHARED_SECRET_SIZE.
 */
ret_code_t nrf_crypto_ecdh_compute(
    nrf_crypto_ecdh_context_t          * p_context,
    nrf_crypto_ecc_private_key_t const * p_private_key,
    nrf_crypto_ecc_public_key_t  const * p_public_key,
    uint8_t                            * p_shared_secret,
    size_t                             * p_shared_secret_size);


#ifdef __cplusplus
}
#endif

/** @}
 *  @}
 */

#endif // NRF_CRYPTO_ECDH_H__
