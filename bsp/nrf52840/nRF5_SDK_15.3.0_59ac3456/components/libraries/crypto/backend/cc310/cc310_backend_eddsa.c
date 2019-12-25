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

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310) && \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_ED25519)

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "nrf_crypto_ecc.h"
#include "nrf_crypto_rng.h"
#include "nrf_crypto_eddsa.h"
#include "cc310_backend_ecc.h"
#include "cc310_backend_shared.h"
#include "cc310_backend_mutex.h"
#include "crys_ec_edw_api.h"
#include "crys_ec_mont_edw_error.h"


ret_code_t nrf_crypto_backend_ed25519_sign(
    void                                  * p_context,
    nrf_crypto_ecc_private_key_t    const * p_private_key,
    uint8_t                         const * p_message,
    size_t                                  message_size,
    uint8_t                               * p_signature)
{
    ret_code_t  result;
    CRYSError_t crys_error;
    bool        mutex_locked;
    size_t      signature_size = 2 * CRYS_ECEDW_ORD_SIZE_IN_BYTES;

    nrf_crypto_backend_cc310_ed25519_context_t * p_ctx =
        (nrf_crypto_backend_cc310_ed25519_context_t *)p_context;

    nrf_crypto_backend_ed25519_private_key_t * p_prv =
        (nrf_crypto_backend_ed25519_private_key_t *)p_private_key;

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_backend_enable();

    crys_error = CRYS_ECEDW_Sign(p_signature,
                                 &signature_size,
                                 p_message,
                                 message_size,
                                 p_prv->key,
                                 sizeof(p_prv->key),
                                 &p_ctx->temp_data);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    result = nrf_crypto_backend_cc310_ecc_error_convert(crys_error);

    return result;
}

ret_code_t nrf_crypto_backend_ed25519_verify(
    void                              * p_context,
    nrf_crypto_ecc_public_key_t const * p_public_key,
    uint8_t                     const * p_message,
    size_t                              message_size,
    uint8_t                     const * p_signature)
{
    ret_code_t  result;
    CRYSError_t crys_error;
    bool        mutex_locked;

    nrf_crypto_backend_cc310_ed25519_context_t * p_ctx =
        (nrf_crypto_backend_cc310_ed25519_context_t *)p_context;

    nrf_crypto_backend_ed25519_public_key_t * p_pub =
        (nrf_crypto_backend_ed25519_public_key_t *)p_public_key;

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_backend_enable();

    crys_error = CRYS_ECEDW_Verify(p_signature,
                                   2 * CRYS_ECEDW_ORD_SIZE_IN_BYTES,
                                   p_pub->key,
                                   CRYS_ECEDW_ORD_SIZE_IN_BYTES,
                                   (uint8_t *)p_message,
                                   message_size,
                                   &p_ctx->temp_data);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    result = nrf_crypto_backend_cc310_ecc_error_convert(crys_error);

    return result;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_ED25519)
