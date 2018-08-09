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

#include "sdk_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_NRF_SW)

#include "nrf_sw_backend_hash.h"
#include "sha256.h"
#include "nrf_crypto_types.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_hash_shared.h"
#include "sdk_macros.h"
#include "nrf_log.h"
#include "nrf_assert.h"

#if defined(NRF_CRYPTO_BACKEND_NRF_SW_HASH_LITTLE_ENDIAN_DIGEST_ENABLED) &&     \
    (NRF_CRYPTO_BACKEND_NRF_SW_HASH_LITTLE_ENDIAN_DIGEST_ENABLED == 1)

    #define LITTLE_ENDIAN_HASH (true)

#elif defined(NRF_CRYPTO_BACKEND_NRF_SW_HASH_LITTLE_ENDIAN_DIGEST_ENABLED) &&   \
      (NRF_CRYPTO_BACKEND_NRF_SW_HASH_LITTLE_ENDIAN_DIGEST_ENABLED == 0)

    #define LITTLE_ENDIAN_HASH (false)

#else

    #define LITTLE_ENDIAN_HASH (false)

    #warning NRF_CRYPTO_BACKEND_NRF_SW_HASH_LITTLE_ENDIAN_DIGEST define not found in sdk_config.h (Is the sdk_config.h valid?).

#endif

static ret_code_t nrf_sw_backend_hash_sha256_init(void * const p_context)
{
    ret_code_t ret_val;

    // No parameter testing on this level.
    // This has been done on upper level.

    sha256_context_t * p_backend_context
        = &(((nrf_crypto_backend_hash_sha256_context_t *) p_context)->context);

    ret_val = sha256_init(p_backend_context);

    return ret_val;
}

static uint32_t nrf_sw_backend_hash_sha256_update(void     * const p_context,
                                                  uint8_t  const * p_data,
                                                  size_t           len)
{
    ret_code_t ret_val;

    // Limited parameter testing on this level.
    // This has been done on upper level.

    sha256_context_t * p_backend_context
        = &(((nrf_crypto_backend_hash_sha256_context_t * ) p_context)->context);

    ret_val = sha256_update(p_backend_context, p_data, len);

    return ret_val;
}


static uint32_t nrf_sw_backend_hash_sha256_finalize(void   * const p_context,
                                                 uint8_t         * p_digest,
                                                 size_t    * const p_digest_len)
{
    ret_code_t ret_val;

    // Limited parameter testing on this level.
    // This has been done on upper level.

    sha256_context_t * p_backend_context
        = &(((nrf_crypto_backend_hash_sha256_context_t * )p_context)->context);

    if (NRF_CRYPTO_HASH_SIZE_SHA256 > *p_digest_len)
    {
        return NRF_ERROR_CRYPTO_OUTPUT_LENGTH;
    }


    ret_val = sha256_final(p_backend_context, p_digest, LITTLE_ENDIAN_HASH);

    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    *p_digest_len = NRF_CRYPTO_HASH_SIZE_SHA256;

    return NRF_SUCCESS;

}


const nrf_crypto_hash_info_t g_nrf_crypto_hash_sha256_info =
{
    .init_fn        = nrf_sw_backend_hash_sha256_init,
    .update_fn      = nrf_sw_backend_hash_sha256_update,
    .finalize_fn    = nrf_sw_backend_hash_sha256_finalize,
    .digest_size    = NRF_CRYPTO_HASH_SIZE_SHA256,
    .context_size   = sizeof(nrf_crypto_backend_hash_sha256_context_t),
    .hash_mode      = NRF_CRYPTO_HASH_MODE_SHA256
};



#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_NRF_SW)
