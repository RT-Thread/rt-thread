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

#include "sdk_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_RNG)

#include "nrf_crypto_error.h"
#include "nrf_log.h"
#include "cc310_backend_mutex.h"
#include "cc310_backend_rng.h"
#include "crys_rnd.h"
#include "crys_rnd_error.h"
#include "cc310_backend_shared.h"

static ret_code_t result_get(CRYSError_t err_code)
{
    ret_code_t ret_val;

    switch (err_code)
    {
        case CRYS_OK:
            ret_val = NRF_SUCCESS;
            break;

        case CRYS_RND_ILLEGAL_PARAMETER_ERROR:
            ret_val = NRF_ERROR_CRYPTO_INVALID_PARAM;
            break;

        case CRYS_RND_INIT_FAILED:
        case CRYS_RND_STARTUP_FAILED:
        case CRYS_RND_INSTANTIATION_ERROR:
            ret_val = NRF_ERROR_CRYPTO_RNG_INIT_FAILED;
            break;

        case CRYS_RND_IS_NOT_SUPPORTED:
        case CRYS_RND_CAN_NOT_GENERATE_RAND_IN_RANGE:
        case CRYS_RND_TRNG_KAT_NOT_SUPPORTED_ERROR:
        case CRYS_RND_SRAM_NOT_SUPPORTED_ERROR:
        case CRYS_RND_OPERATION_IS_NOT_SUPPORTED_ERROR:
            ret_val = NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
            break;

        case CRYS_RND_DATA_OUT_POINTER_INVALID_ERROR:
        case CRYS_RND_VECTOR_OUT_PTR_ERROR:
            ret_val = NRF_ERROR_CRYPTO_OUTPUT_NULL;
            break;

        case CRYS_RND_ADDITIONAL_INPUT_BUFFER_NULL:
        case CRYS_RND_WORK_BUFFER_PTR_INVALID_ERROR:
        case CRYS_RND_ILLEGAL_DATA_PTR_ERROR:
            ret_val = NRF_ERROR_CRYPTO_INPUT_NULL;
            break;

        case CRYS_RND_DATA_SIZE_OVERFLOW_ERROR:
        case CRYS_RND_ADDITIONAL_INPUT_SIZE_ERROR:
        case CRYS_RND_ILLEGAL_DATA_SIZE_ERROR:
        case CRYS_RND_MAX_VECTOR_IS_TOO_SMALL_ERROR:
            ret_val = NRF_ERROR_CRYPTO_INPUT_LENGTH;
            break;

        case CRYS_RND_ILLEGAL_AES_KEY_SIZE_ERROR:
        case CRYS_RND_VECTOR_OUT_SIZE_ERROR:
        case CRYS_RND_VECTOR_SIZE_ERROR:
            ret_val = NRF_ERROR_CRYPTO_OUTPUT_LENGTH;
            break;

        case CRYS_RND_CONTEXT_PTR_INVALID_ERROR:
        case CRYS_RND_STATE_PTR_INVALID_ERROR:
            ret_val = NRF_ERROR_CRYPTO_CONTEXT_NULL;
            break;

        case CRYS_RND_INSTANTIATION_NOT_DONE_ERROR:
            ret_val = NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED;
            break;

        case CRYS_RND_RESEED_COUNTER_OVERFLOW_ERROR:
            ret_val = NRF_ERROR_CRYPTO_RNG_RESEED_REQUIRED;
            break;

        case CRYS_RND_CPRNG_TEST_FAIL_ERROR:
        case CRYS_RND_TRNG_LOSS_SAMPLES_ERROR:
        case CRYS_RND_TRNG_TIME_EXCEED_ERROR:
        case CRYS_RND_TRNG_LOSS_SAMPLES_AND_TIME_EXCEED_ERROR:
        case CRYS_RND_IS_KAT_MODE_ERROR:
        case CRYS_RND_STATE_VALIDATION_TAG_ERROR:
        case CRYS_RND_GEN_VECTOR_FUNC_ERROR:
        case CRYS_RND_TRNG_ERRORS_ERROR:
        case CRYS_RND_KAT_DATA_PARAMS_ERROR:
        case CRYS_RND_AES_ERROR:
        default:
            ret_val = NRF_ERROR_CRYPTO_INTERNAL;
            break;
    }
    return ret_val;
}


ret_code_t nrf_crypto_rng_backend_init(void * const p_context,
                                       void * const p_temp_buffer)
{
    bool                                mutex_locked;
    CRYSError_t                         err_code;
    ret_code_t                          ret_val;
    CRYS_RND_WorkBuff_t               * p_work_buffer   = (CRYS_RND_WorkBuff_t *)p_temp_buffer;
    nrf_crypto_backend_rng_context_t  * p_ctx = (nrf_crypto_backend_rng_context_t *)p_context;

    // Save time by not reinitializing an already valid CC310 RNG context.
    // (Useful for example in case the context was stored in retained memory during system OFF.)
    if (p_ctx->header.init_value == NRF_CRYPTO_RNG_CONTEXT_INIT_MAGIC_VALUE)
    {
        return NRF_SUCCESS;
    }

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_backend_enable();

    err_code = CRYS_RndInit(&p_ctx->crys_rnd_state, p_work_buffer);
    ret_val = result_get(err_code);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    return ret_val;
}


ret_code_t nrf_crypto_rng_backend_uninit(void   * const p_context)
{
    bool                mutex_locked;
    CRYSError_t         err_code;
    ret_code_t          ret_val;
    CRYS_RND_State_t  * p_crys_rnd_state =
        &((nrf_crypto_backend_rng_context_t *)p_context)->crys_rnd_state;


    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_backend_enable();

    err_code = CRYS_RND_UnInstantiation(p_crys_rnd_state);

    cc310_backend_disable();

    ret_val = result_get(err_code);

    cc310_backend_mutex_unlock();

    return ret_val;
}


ret_code_t nrf_crypto_rng_backend_vector_generate(void      * const p_context,
                                                  uint8_t   * const p_target,
                                                  size_t            size,
                                                  bool              use_mutex)
{
    bool                mutex_locked;
    CRYSError_t         err_code;
    ret_code_t          ret_val;
    CRYS_RND_State_t  * p_crys_rnd_state =
        &((nrf_crypto_backend_rng_context_t *)p_context)->crys_rnd_state;

    if (use_mutex)
    {
        mutex_locked = cc310_backend_mutex_trylock();
        VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);
    }

    cc310_backend_enable();

    err_code = CRYS_RND_GenerateVector(p_crys_rnd_state, size, p_target);

    cc310_backend_disable();

    ret_val = result_get(err_code);

    if (use_mutex)
    {
        cc310_backend_mutex_unlock();
    }

    return ret_val;
}


ret_code_t nrf_crypto_rng_backend_reseed(void   * const p_context,
                                         void         * p_temp_buffer,
                                         uint8_t      * p_input_data,
                                         size_t         size)
{
    bool                    mutex_locked;
    CRYSError_t             err_code;
    ret_code_t              ret_val = NRF_SUCCESS;
    CRYS_RND_WorkBuff_t   * p_work_buffer = (CRYS_RND_WorkBuff_t *)p_temp_buffer;
    CRYS_RND_State_t      * p_crys_rnd_state =
        &((nrf_crypto_backend_rng_context_t *)p_context)->crys_rnd_state;

    VERIFY_TRUE(size <= CRYS_RND_ADDITINAL_INPUT_MAX_SIZE_WORDS, NRF_ERROR_CRYPTO_INPUT_LENGTH);
    VERIFY_TRUE((size & 0x3) == 0, NRF_ERROR_CRYPTO_INTERNAL);

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_backend_enable();

    if (size > 0)
    {
        err_code = CRYS_RND_AddAdditionalInput(p_crys_rnd_state, p_input_data, size);
        ret_val = result_get(err_code);
        if (ret_val != NRF_SUCCESS)
        {
            goto exit;
        }
    }

    err_code = CRYS_RND_Reseeding(p_crys_rnd_state, p_work_buffer);
    ret_val = result_get(err_code);

exit:
    cc310_backend_disable();
    cc310_backend_mutex_unlock();
    return ret_val;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_RNG)
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
