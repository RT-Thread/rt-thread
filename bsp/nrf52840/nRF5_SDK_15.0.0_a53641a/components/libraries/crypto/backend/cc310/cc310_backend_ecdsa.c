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

#include "sdk_config.h"
#include "nordic_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)

#include <string.h>
#include "ssi_pal_types.h"
#include "ssi_pal_mem.h"
#include "sns_silib.h"
#include "crys_rnd.h"
#include "crys_ecpki_ecdsa.h"
#include "crys_ecpki_error.h"
#include "crys_kdf_error.h"
#include "crys_hash_error.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_ecc_shared.h"
#include "nrf_crypto_ecdsa_shared.h"
#include "nrf_crypto_ecdsa.h"
#include "cc310_backend_ecdsa.h"
#include "cc310_backend_shared.h"
#include "cc310_backend_mutex.h"


#define CC310_SHA1_DIGEST_SIZE   (160 / 8)  /**< @internal @brief Digest size of SHA-1 */
#define CC310_SHA224_DIGEST_SIZE (224 / 8)  /**< @internal @brief Digest size of SHA-224 */
#define CC310_SHA256_DIGEST_SIZE (256 / 8)  /**< @internal @brief Digest size of SHA-256 */
#define CC310_SHA384_DIGEST_SIZE (384 / 8)  /**< @internal @brief Digest size of SHA-384 */
#define CC310_SHA512_DIGEST_SIZE (512 / 8)  /**< @internal @brief Digest size of SHA-512 */


/** @internal @brief Returns enum value of @ref CRYS_ECPKI_HASH_OpMode_t based on provided hash size.
 *
 * @param[in] data_size  Hash size
 * @return               Value from @ref CRYS_ECPKI_HASH_OpMode_t or CRYS_ECPKI_HASH_OpModeLast if
 *                       cannot find implemented hash with provided size.
 */
static CRYS_ECPKI_HASH_OpMode_t hash_mode_from_size(uint32_t data_size)
{
    CRYS_ECPKI_HASH_OpMode_t hash_mode;

    switch (data_size)
    {
        case CC310_SHA1_DIGEST_SIZE:
            hash_mode = CRYS_ECPKI_AFTER_HASH_SHA1_mode;
            break;

        case CC310_SHA224_DIGEST_SIZE:
            hash_mode = CRYS_ECPKI_AFTER_HASH_SHA224_mode;
            break;

        case CC310_SHA256_DIGEST_SIZE:
            hash_mode = CRYS_ECPKI_AFTER_HASH_SHA256_mode;
            break;

        case CC310_SHA384_DIGEST_SIZE:
            hash_mode = CRYS_ECPKI_AFTER_HASH_SHA384_mode;
            break;

        case CC310_SHA512_DIGEST_SIZE:
            hash_mode = CRYS_ECPKI_AFTER_HASH_SHA512_mode;
            break;

        default:
            hash_mode = CRYS_ECPKI_HASH_OpModeLast;
            break;
    }

    return hash_mode;
}


ret_code_t nrf_crypto_backend_cc310_sign(
    void           * p_context,
    void     const * p_private_key,
    uint8_t  const * p_data,
    size_t           data_size,
    uint8_t        * p_signature)
{
    ret_code_t               result;
    CRYSError_t              crys_error;
    uint32_t                 signature_size;
    CRYS_ECPKI_HASH_OpMode_t hash_mode = hash_mode_from_size(data_size);
    bool                     mutex_locked;

    nrf_crypto_backend_cc310_sign_context_t * p_ctx =
        (nrf_crypto_backend_cc310_sign_context_t *)p_context;

    nrf_crypto_backend_cc310_ecc_private_key_t * p_prv =
        (nrf_crypto_backend_cc310_ecc_private_key_t *)p_private_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_prv->header.p_info;

    if (hash_mode == CRYS_ECPKI_HASH_OpModeLast)
    {
        return NRF_ERROR_CRYPTO_INPUT_LENGTH;
    }

    signature_size = p_info->raw_public_key_size;

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_backend_enable();

    crys_error = CRYS_ECDSA_Sign(p_context,
                                 nrf_crypto_backend_cc310_rng,
                                 &p_ctx->user_context,
                                 &p_prv->private_key,
                                 hash_mode,
                                 (uint8_t *)p_data,
                                 data_size,
                                 p_signature,
                                 &signature_size);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    result = nrf_crypto_backend_cc310_ecc_error_convert(crys_error);

    if (result == NRF_SUCCESS && signature_size != p_info->raw_public_key_size)
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    return result;
}


ret_code_t nrf_crypto_backend_cc310_verify(
    void           * p_context,
    void     const * p_public_key,
    uint8_t  const * p_data,
    size_t           data_size,
    uint8_t  const * p_signature)
{
    ret_code_t               result;
    CRYSError_t              crys_error;
    CRYS_ECPKI_HASH_OpMode_t hash_mode = hash_mode_from_size(data_size);
    bool                     mutex_locked;

    nrf_crypto_backend_cc310_verify_context_t * p_ctx =
        (nrf_crypto_backend_cc310_verify_context_t *)p_context;

    nrf_crypto_backend_cc310_ecc_public_key_t * p_pub =
        (nrf_crypto_backend_cc310_ecc_public_key_t *)p_public_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_pub->header.p_info;

    result = nrf_crypto_backend_cc310_ecc_public_key_convert(p_pub, &p_ctx->key_build_temp_data);
    if (result != NRF_SUCCESS)
    {
        return result;
    }

    if (hash_mode == CRYS_ECPKI_HASH_OpModeLast)
    {
        return NRF_ERROR_CRYPTO_INPUT_LENGTH;
    }

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_backend_enable();

    crys_error = CRYS_ECDSA_Verify(&p_ctx->user_context,
                                   &p_pub->key.cc310_public_key,
                                   hash_mode,
                                   (uint8_t *)p_signature,
                                   p_info->raw_public_key_size,
                                   (uint8_t *)p_data,
                                   data_size);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    result = nrf_crypto_backend_cc310_ecc_error_convert(crys_error);
    return result;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)
