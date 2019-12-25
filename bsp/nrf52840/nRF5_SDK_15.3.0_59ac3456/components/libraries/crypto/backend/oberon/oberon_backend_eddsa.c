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
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON) && \
    NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_ED25519)

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "nrf_crypto_ecc.h"
#include "nrf_crypto_rng.h"
#include "nrf_crypto_eddsa.h"
#include "occ_ed25519.h"


ret_code_t nrf_crypto_backend_ed25519_sign(
    void                                  * p_context,
    nrf_crypto_ecc_private_key_t    const * p_private_key,
    uint8_t                         const * p_message,
    size_t                                  message_size,
    uint8_t                               * p_signature)
{
    occ_ed25519_sign(p_signature,
                     p_message,
                     message_size,
                     p_private_key->key_ed25519.private_part,
                     p_private_key->key_ed25519.public_part);

    return NRF_SUCCESS;
}

ret_code_t nrf_crypto_backend_ed25519_verify(
    void                              * p_context,
    nrf_crypto_ecc_public_key_t const * p_public_key,
    uint8_t                     const * p_message,
    size_t                              message_size,
    uint8_t                     const * p_signature)
{
    int result;

    result = occ_ed25519_verify(p_signature,
                                p_message,
                                message_size,
                                p_public_key->key_ed25519.key);

    if (result != 0)
    {
        return NRF_ERROR_CRYPTO_ECDSA_INVALID_SIGNATURE;
    }

    return NRF_SUCCESS;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OBERON_ECC_ED25519)
