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

#include "sdk_config.h"
#include "nordic_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)

#include <string.h>

#include "nrf_crypto_ecc_shared.h"
#include "nrf_crypto_ecdh_shared.h"
#include "nrf_crypto_ecdh.h"
#include "nrf_crypto_mem.h"
#include "nrf_crypto_shared.h"
#include "cc310_backend_mutex.h"
#include "cc310_backend_shared.h"
#include "cc310_backend_ecdh.h"


ret_code_t nrf_crypto_backend_cc310_ecdh_compute(
    void       * p_context,
    void const * p_private_key,
    void const * p_public_key,
    uint8_t    * p_shared_secret)
{
    ret_code_t    result;
    CRYSError_t   crys_error;
    uint32_t      shared_secret_size;
    uint8_t       aligned_buffer[(NRF_CRYPTO_ECDH_SHARED_SECRET_MAX_SIZE + 3) & ~3];
    uint8_t     * p_output_buffer;
    bool          mutex_locked;

    nrf_crypto_backend_cc310_ecdh_compute_context_t * p_ctx =
        (nrf_crypto_backend_cc310_ecdh_compute_context_t *)p_context;

    nrf_crypto_backend_cc310_ecc_private_key_t  * p_prv =
        (nrf_crypto_backend_cc310_ecc_private_key_t *)p_private_key;

    nrf_crypto_backend_cc310_ecc_public_key_t   * p_pub =
        (nrf_crypto_backend_cc310_ecc_public_key_t *)p_public_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_prv->header.p_info;

    result = nrf_crypto_backend_cc310_ecc_public_key_convert(p_pub, &p_ctx->key_build_temp_data);
    if (result != NRF_SUCCESS)
    {
        return result;
    }

    shared_secret_size = p_info->raw_private_key_size;

    if ((shared_secret_size & 3) != 0) // Check if shared_secret_size is word aligned
    {
        shared_secret_size = (shared_secret_size + 3) & ~3;
        p_output_buffer = &aligned_buffer[0];
    }
    else
    {
        p_output_buffer = p_shared_secret;
    }

    mutex_locked = cc310_backend_mutex_trylock();
    if (!mutex_locked)
    {
        return NRF_ERROR_CRYPTO_BUSY;
    }

    cc310_backend_enable();

    crys_error = CRYS_ECDH_SVDP_DH(&p_pub->key.cc310_public_key,
                                   &p_prv->private_key,
                                   p_output_buffer,
                                   &shared_secret_size,
                                   &p_ctx->temp_data);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    if (p_output_buffer != p_shared_secret)
    {
        //lint -save -e645 (Symbol 'aligned_buffer' may not have been initialized)
        memcpy(p_shared_secret,
            &aligned_buffer[3 - ((p_info->raw_private_key_size + 3) & 3)], // Bytes at the beginning that were added during padding are now skipped
            p_info->raw_private_key_size);
        //lint -restore
    }

    result = nrf_crypto_backend_cc310_ecc_error_convert(crys_error);
    return result;
}


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_CURVE25519)

ret_code_t nrf_crypto_backend_cc310_curve25519_ecdh_compute(
    void       * p_context,
    void const * p_private_key,
    void const * p_public_key,
    uint8_t    * p_shared_secret)
{
    ret_code_t    result;
    CRYSError_t   crys_error;
    bool          mutex_locked;

    nrf_crypto_backend_cc310_curve25519_context_t * p_ctx =
        (nrf_crypto_backend_cc310_curve25519_context_t *)p_context;

    nrf_crypto_backend_curve25519_private_key_t   * p_prv =
        (nrf_crypto_backend_curve25519_private_key_t *)p_private_key;

    nrf_crypto_backend_curve25519_public_key_t    * p_pub =
        (nrf_crypto_backend_curve25519_public_key_t *)p_public_key;

    nrf_crypto_ecc_curve_info_t const * p_info              = p_prv->header.p_info;
    size_t                              shared_secret_size  = p_info->raw_private_key_size;
    size_t                              pub_key_size        = sizeof(p_pub->key);
    size_t                              prv_key_size        = sizeof(p_prv->key);

    mutex_locked = cc310_backend_mutex_trylock();
    if (!mutex_locked)
    {
        return NRF_ERROR_CRYPTO_BUSY;
    }

    cc310_backend_enable();

    crys_error = CRYS_ECMONT_Scalarmult(p_shared_secret,
                                        &shared_secret_size,
                                        p_prv->key,
                                        prv_key_size,
                                        p_pub->key,
                                        pub_key_size,
                                        &p_ctx->temp_data);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    // Swap endianess (only for Curve25519)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_CURVE25519_BIG_ENDIAN)
    nrf_crypto_internal_swap_endian_in_place(p_shared_secret,
                                             NRF_CRYPTO_ECDH_CURVE25519_SHARED_SECRET_SIZE);
#endif

    result = nrf_crypto_backend_cc310_ecc_error_convert(crys_error);
    return result;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_CURVE25519)

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)
