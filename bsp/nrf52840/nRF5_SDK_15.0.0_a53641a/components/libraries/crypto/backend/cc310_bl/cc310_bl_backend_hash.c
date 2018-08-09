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

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL)

#include "nrf.h"
#include "cc310_bl_backend_hash.h"
#include "cc310_bl_backend_shared.h"
#include "cc310_backend_mutex.h"
#include "cc310_backend_shared.h"
#include "nrf_cc310_bl_hash_sha256.h"
#include "crys_hash_error.h"
#include "nrf_crypto_init.h"
#include "nrf_crypto_types.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_shared.h"
#include "nrf_crypto_hash_shared.h"
#include "sdk_macros.h"
#include "nrf_log.h"
#include "nrf_assert.h"
#include <drivers/nrfx_common.h>


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_HASH_SHA256)

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_HASH_AUTOMATIC_RAM_BUFFER)

__ALIGN(4) static uint8_t  m_hash_buffer[NRF_CRYPTO_BACKEND_CC310_BL_HASH_AUTOMATIC_RAM_BUFFER_SIZE];

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_HASH_AUTOMATIC_RAM_BUFFER)


static ret_code_t hash_result_get(CRYSError_t error)
{
    ret_code_t ret_val;

    switch (error)
    {
        case CRYS_OK:
            ret_val = NRF_SUCCESS;
            break;

        case CRYS_HASH_INVALID_USER_CONTEXT_POINTER_ERROR:
            ret_val = NRF_ERROR_CRYPTO_CONTEXT_NULL;
            break;

        case CRYS_HASH_ILLEGAL_OPERATION_MODE_ERROR:
            ret_val = NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
            break;

        case CRYS_HASH_USER_CONTEXT_CORRUPTED_ERROR:
            ret_val = NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED;
            break;

        // May be added to specialized errors for hash.
        case CRYS_HASH_LAST_BLOCK_ALREADY_PROCESSED_ERROR:
            ret_val = NRF_ERROR_CRYPTO_INTERNAL;
            break;

        case CRYS_HASH_IS_NOT_SUPPORTED:
            ret_val = NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
            break;

        default:
            ret_val = NRF_ERROR_CRYPTO_INTERNAL;
            break;
    }

    return ret_val;
}


static ret_code_t cc310_bl_backend_hash_sha256_init(void * const p_context)
{
    uint32_t    ret_val;
    CRYSError_t crys_error;

    // Limited parameter testing on this level.
    // This has been done on upper level.

    nrf_cc310_bl_hash_context_sha256_t * const p_backend_context
        = &(((nrf_crypto_backend_hash_sha256_context_t *)p_context)->context);

    crys_error = nrf_cc310_bl_hash_sha256_init(p_backend_context);

    ret_val = hash_result_get(crys_error);

    return ret_val;
}


static uint32_t cc310_bl_backend_hash_sha256_update(void      * const p_context,
                                                    uint8_t   const * p_data,
                                                    size_t            size)
{
    ret_code_t  ret_val;
    CRYSError_t crys_error;
    uint32_t    cur_size;
    uint32_t    size_left;
    uint8_t   * p_cur;
    bool        mutex_locked;

    // Limited parameter testing on this level.
    // This has been done on upper level.

    nrf_cc310_bl_hash_context_sha256_t * const p_backend_context
        = &(((nrf_crypto_backend_hash_sha256_context_t *)p_context)->context);

    p_cur = (uint8_t *)p_data;
    size_left = size;

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_bl_backend_enable();

#if defined (NRF_CRYPTO_BACKEND_CC310_BL_HASH_AUTOMATIC_RAM_BUFFER_ENABLED) && (NRF_CRYPTO_BACKEND_CC310_BL_HASH_AUTOMATIC_RAM_BUFFER_ENABLED == 1)

    do
    {
        // Copy a block from FLASH to RAM for use in CC310
        cur_size = (size_left > NRF_CRYPTO_BACKEND_CC310_BL_HASH_AUTOMATIC_RAM_BUFFER_SIZE) ?
            NRF_CRYPTO_BACKEND_CC310_BL_HASH_AUTOMATIC_RAM_BUFFER_SIZE : size_left;

        // Copy from FLASH to ram
        memcpy(m_hash_buffer, p_cur, cur_size);

        // Update the hash with current input.
        crys_error = nrf_cc310_bl_hash_sha256_update(p_backend_context, m_hash_buffer, cur_size);

        size_left -= cur_size;
        p_cur += cur_size;

    } while(crys_error == SASI_OK && size_left > 0);

#elif defined(NRF_CRYPTO_BACKEND_CC310_BL_HASH_AUTOMATIC_RAM_BUFFER_ENABLED) && (NRF_CRYPTO_BACKEND_CC310_BL_HASH_AUTOMATIC_RAM_BUFFER_ENABLED == 0) 

    // Verify that the data is in RAM (required for CC310 hashing)
    VERIFY_TRUE(nrfx_is_in_ram(p_data), NRF_ERROR_CRYPTO_INPUT_LOCATION);

    do
    {
        // Get the largest block that can sent to the CC310 through DMA
        cur_size = (size_left > CC310_MAX_LENGTH_DMA_OPERATIONS) ?
            CC310_MAX_LENGTH_DMA_OPERATIONS : size_left;

        crys_error = nrf_cc310_bl_hash_sha256_update(p_backend_context, p_cur, cur_size);

        size_left -= cur_size;
        p_cur += cur_size;
    } while(crys_error == SASI_OK && size_left > 0);

#else

    UNUSED_PARAMETER(p_backend_context);
    UNUSED_PARAMETER(cur_size);
    UNUSED_PARAMETER(size_left);
    UNUSED_PARAMETER(p_cur);

    #warning NRF_CRYPTO_BACKEND_CC310_BL_HASH_AUTOMATIC_RAM_BUFFER_ENABLED define not found in sdk_config.h (Is the sdk_config.h valid?).

#endif

    cc310_bl_backend_disable();

    cc310_backend_mutex_unlock();

    ret_val = hash_result_get(crys_error);

    return ret_val;
}


static uint32_t cc310_bl_backend_hash_sha256_finalize(void    * const p_context,
                                                      uint8_t        * p_digest,
                                                      size_t   * const p_digest_size)
{
    ret_code_t  ret_val;
    CRYSError_t crys_error;
    bool        mutex_locked;

    // Limited parameter testing on this level.
    // This has been done on upper level.

    nrf_cc310_bl_hash_context_sha256_t * const p_backend_context
        = &(((nrf_crypto_backend_hash_sha256_context_t * )p_context)->context);

    nrf_cc310_bl_hash_digest_sha256_t * p_int_digest
        = (nrf_cc310_bl_hash_digest_sha256_t *)p_digest;

    if (NRF_CRYPTO_HASH_SIZE_SHA256 > *p_digest_size)
    {
        return NRF_ERROR_CRYPTO_OUTPUT_LENGTH;
    }

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_bl_backend_enable();

    // Do the hash finalize calculation
    crys_error = nrf_cc310_bl_hash_sha256_finalize(p_backend_context, p_int_digest);

    cc310_bl_backend_disable();

    cc310_backend_mutex_unlock();

    ret_val = hash_result_get(crys_error);

    if (ret_val == NRF_SUCCESS)
    {
        *p_digest_size = NRF_CRYPTO_HASH_SIZE_SHA256;
    }

#if defined(NRF_CRYPTO_BACKEND_CC310_BL_HASH_LITTLE_ENDIAN_DIGEST_ENABLED) && (NRF_CRYPTO_BACKEND_CC310_BL_HASH_LITTLE_ENDIAN_DIGEST_ENABLED == 1)

    nrf_crypto_internal_swap_endian_in_place(p_digest, NRF_CRYPTO_HASH_SIZE_SHA256);

#elif defined(NRF_CRYPTO_BACKEND_CC310_BL_HASH_LITTLE_ENDIAN_DIGEST_ENABLED) && (NRF_CRYPTO_BACKEND_CC310_BL_HASH_LITTLE_ENDIAN_DIGEST_ENABLED == 0)

    // Do nothing

#else

    #warning NRF_CRYPTO_BACKEND_CC310_BL_HASH_LITTLE_ENDIAN_DIGEST_ENABLED define not found in sdk_config.h (Is the sdk_config.h valid?).

#endif

    return ret_val;
}

const nrf_crypto_hash_info_t g_nrf_crypto_hash_sha256_info =
{
    .init_fn        = cc310_bl_backend_hash_sha256_init,
    .update_fn      = cc310_bl_backend_hash_sha256_update,
    .finalize_fn    = cc310_bl_backend_hash_sha256_finalize,
    .digest_size    = NRF_CRYPTO_HASH_SIZE_SHA256,
    .hash_mode      = NRF_CRYPTO_HASH_MODE_SHA256
};

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL_HASH_SHA256)

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && #if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL)
