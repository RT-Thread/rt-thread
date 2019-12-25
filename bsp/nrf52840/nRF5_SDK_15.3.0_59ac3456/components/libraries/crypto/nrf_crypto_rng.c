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

#include "nrf_crypto_init.h"
#include "nrf_log.h"
#include "nrf_crypto_mem.h"
#include "nrf_crypto_rng.h"
#include "nrf_crypto_rng_shared.h"
#include "nrf_crypto_rng_backend.h"
#include "nrf_stack_info.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO_RNG)

#define NRF_CRYPTO_RNG_MODULE_INIT_MAGIC_VALUE   (0x4be57265)

static nrf_crypto_backend_rng_context_t   * mp_allocated_context    = NULL;
static nrf_crypto_backend_rng_context_t   * mp_context              = NULL;
static uint32_t                             m_initialized           = 0;


#if NRF_MODULE_ENABLED(NRF_CRYPTO_RNG_STATIC_MEMORY_BUFFERS)
static nrf_crypto_backend_rng_context_t     m_context;
static nrf_crypto_rng_temp_buffer_t         m_temp_buffer;
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_RNG_STATIC_MEMORY_BUFFERS)


static bool is_vector_greater_or_equal(uint8_t    const * const p_vector,
                                       uint8_t    const * const p_min,
                                       size_t                   size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (p_vector[i] != p_min[i])
        {
            if (p_vector[i] > p_min[i])
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}


// Return true if value p_vector is between (including) p_min and p_max.
static bool is_vector_in_range(uint8_t    const * const p_vector,
                               uint8_t    const * const p_min,
                               uint8_t    const * const p_max,
                               size_t                   size)
{
    if (!is_vector_greater_or_equal(p_vector, p_min, size))
    {
        return false;
    }

    if (!is_vector_greater_or_equal(p_max, p_vector, size))
    {
        return false;
    }

    return true;
}


static uint32_t count_leading_zeros(uint8_t const * const p_vector, size_t size)
{
    uint32_t leading_zeros  = 0;
    uint32_t nonzero_byte   = 0xFF;

    // Find leading all-zero elements.
    for (uint32_t i = 0; i < size; i++)
    {
        if (p_vector[i] == 0)
        {
            leading_zeros += 8;
        }
        else
        {
            nonzero_byte = p_vector[i];
            break;
        }
    }

    // Find leading zeros in non-zero element.
    for (uint32_t i = 0; i < 8; i++)
    {
        nonzero_byte <<= 1;

        if ((nonzero_byte & ~0xff) > 0)
        {
            break;
        }

        leading_zeros ++;
    }

    return leading_zeros;
}


static ret_code_t generate(uint8_t * const p_target, size_t size, bool use_mutex)
{
    ret_code_t ret_code;

    VERIFY_TRUE(p_target != NULL, NRF_ERROR_CRYPTO_OUTPUT_NULL);
    VERIFY_TRUE(size > 0, NRF_ERROR_CRYPTO_OUTPUT_LENGTH);

    VERIFY_TRUE(m_initialized == NRF_CRYPTO_RNG_MODULE_INIT_MAGIC_VALUE,
                NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED);

    ret_code = nrf_crypto_rng_backend_vector_generate(mp_context, p_target, size, use_mutex);

    // Reseed internally and try again if reseed is required by the backend.
    // (CC310 only as mbed TLS handles reseeding internally.)
    if (ret_code == NRF_ERROR_CRYPTO_RNG_RESEED_REQUIRED)
    {
        ret_code = nrf_crypto_rng_reseed(NULL, NULL, 0);

        if (ret_code != NRF_SUCCESS)
        {
            return ret_code;
        }

        ret_code = nrf_crypto_rng_backend_vector_generate(mp_context, p_target, size, use_mutex);
    }

    return ret_code;
}


static ret_code_t generate_in_range(uint8_t         * const p_target,
                                    uint8_t   const * const p_min,
                                    uint8_t   const * const p_max,
                                    size_t                  size,
                                    bool                    use_mutex)
{
    uint32_t const  max_leading_zeros = count_leading_zeros(p_max, size);
    ret_code_t      ret_code;

    VERIFY_TRUE(p_target != NULL, NRF_ERROR_CRYPTO_OUTPUT_NULL);
    VERIFY_TRUE(size > 0, NRF_ERROR_CRYPTO_OUTPUT_LENGTH);
    VERIFY_TRUE(p_min != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    VERIFY_TRUE(p_max != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    VERIFY_TRUE(is_vector_greater_or_equal(p_max, p_min, size), NRF_ERROR_CRYPTO_INVALID_PARAM);

    do
    {
        ret_code = nrf_crypto_rng_backend_vector_generate(mp_context, p_target, size, use_mutex);

        if (ret_code != NRF_SUCCESS)
        {
            return ret_code;
        }

        // Mask leading zeros in generated vector instead of always discarding a too large vectors.
        memset(p_target, 0, max_leading_zeros / 8);
        if ((max_leading_zeros & 0x07) > 0)
        {
            p_target[max_leading_zeros / 8] =
                p_target[max_leading_zeros / 8] & (0xff >> (max_leading_zeros & 0x07));
        }
    } while (!is_vector_in_range(p_target, p_min, p_max, size));

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_rng_vector_generate(uint8_t * const p_target, size_t size)
{
    ret_code_t ret_code;

    ret_code = generate(p_target, size, true);

    return ret_code;
}


ret_code_t nrf_crypto_rng_vector_generate_in_range(uint8_t          * const p_target,
                                                   uint8_t    const * const p_min,
                                                   uint8_t    const * const p_max,
                                                   size_t                   size)
{
    ret_code_t ret_code;

    ret_code = generate_in_range(p_target, p_min, p_max, size, true);

    return ret_code;
}


ret_code_t nrf_crypto_rng_vector_generate_no_mutex(uint8_t * const p_target, size_t size)
{
    ret_code_t ret_code;

    ret_code = generate(p_target, size, false);

    return ret_code;
}


ret_code_t nrf_crypto_rng_vector_generate_in_range_no_mutex(uint8_t         * const p_target,
                                                            uint8_t   const * const p_min,
                                                            uint8_t   const * const p_max,
                                                            size_t                  size)
{
    ret_code_t ret_code;

    ret_code = generate_in_range(p_target, p_min, p_max, size, false);

    return ret_code;
}


ret_code_t nrf_crypto_rng_init(nrf_crypto_rng_context_t       * p_context,
                               nrf_crypto_rng_temp_buffer_t   * p_temp_buffer)
{
    ret_code_t                      ret_code;
    nrf_crypto_rng_temp_buffer_t  * p_allocated_temp_buffer = NULL;

    // Check if the stack has overflowed. This can typically happen if the application has put the
    // ~6 kB large temp buffer for CC310 on the stack.
    if (nrf_stack_info_overflowed())
    {
        NRF_LOG_ERROR("Stack overflow detected.");
        return NRF_ERROR_CRYPTO_STACK_OVERFLOW;
    }

#if NRF_MODULE_ENABLED(NRF_CRYPTO_RNG_AUTO_INIT)
    VERIFY_TRUE(nrf_crypto_is_initializing(), NRF_ERROR_CRYPTO_NOT_INITIALIZED);
#else
    VERIFY_TRUE(nrf_crypto_is_initialized(), NRF_ERROR_CRYPTO_NOT_INITIALIZED);
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_RNG_AUTO_INIT)

    // Do nothing if RNG module is already initialized.
    if (mp_context != 0 && (m_initialized == NRF_CRYPTO_RNG_MODULE_INIT_MAGIC_VALUE))
    {
        return NRF_SUCCESS;
    }

#if NRF_MODULE_ENABLED(NRF_CRYPTO_RNG_STATIC_MEMORY_BUFFERS)

    VERIFY_TRUE(p_context == NULL, NRF_ERROR_CRYPTO_INVALID_PARAM);
    VERIFY_TRUE(p_temp_buffer == NULL, NRF_ERROR_CRYPTO_INVALID_PARAM);

    mp_context = &m_context;
    p_temp_buffer = &m_temp_buffer;

#else // !NRF_MODULE_ENABLED(NRF_CRYPTO_RNG_STATIC_MEMORY_BUFFERS)

    if (p_context == NULL)
    {
        if (NRF_CRYPTO_ALLOC_ON_STACK)
        {
            NRF_LOG_ERROR("RNG context cannot be allocated on the stack.");
            return NRF_ERROR_CRYPTO_ALLOC_FAILED;
        }
        else
        {
            mp_allocated_context = NRF_CRYPTO_ALLOC(sizeof(nrf_crypto_backend_rng_context_t));
            if (mp_allocated_context == NULL)
            {
                return NRF_ERROR_CRYPTO_ALLOC_FAILED;
            }
            mp_context = mp_allocated_context;
        }
    }
    else
    {
        mp_context = p_context;
    }

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_RNG_STATIC_MEMORY_BUFFERS)

    // Allocate temporary buffer internally if not statically allocated or provided by the user.
    if (p_temp_buffer == NULL)
    {
        p_allocated_temp_buffer = NRF_CRYPTO_ALLOC(sizeof(nrf_crypto_rng_temp_buffer_t));

        if (p_allocated_temp_buffer == NULL)
        {
            if (mp_allocated_context != NULL)
            {
                NRF_CRYPTO_FREE(mp_allocated_context);
            }

            return NRF_ERROR_CRYPTO_ALLOC_FAILED;
        }

        p_temp_buffer = p_allocated_temp_buffer;
    }

    ret_code = nrf_crypto_rng_backend_init(mp_context, p_temp_buffer);
    if (ret_code == NRF_SUCCESS)
    {
        m_initialized = NRF_CRYPTO_RNG_MODULE_INIT_MAGIC_VALUE;
        mp_context->header.init_value = NRF_CRYPTO_RNG_CONTEXT_INIT_MAGIC_VALUE;
    }

    if (p_allocated_temp_buffer != NULL)
    {
        NRF_CRYPTO_FREE(p_allocated_temp_buffer);
    }

    return ret_code;
}


ret_code_t nrf_crypto_rng_uninit(void)
{
    ret_code_t ret_code;

    VERIFY_TRUE(m_initialized == NRF_CRYPTO_RNG_MODULE_INIT_MAGIC_VALUE,
                NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED);

    VERIFY_TRUE(mp_context->header.init_value == NRF_CRYPTO_RNG_CONTEXT_INIT_MAGIC_VALUE,
                NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED);

    mp_context->header.init_value = 0;
    m_initialized = 0;

    ret_code = nrf_crypto_rng_backend_uninit(mp_context);

    if (mp_allocated_context != NULL)
    {
        NRF_CRYPTO_FREE(mp_allocated_context);
    }

    return ret_code;
}


ret_code_t nrf_crypto_rng_reseed(nrf_crypto_rng_temp_buffer_t * p_temp_buffer,
                                 uint8_t                      * p_input_data,
                                 size_t                         size)
{
    ret_code_t      ret_code;
    void          * p_allocated_temp_buffer = NULL;

    // Check if the stack has overflowed. This can typically happen if the application has put the
    // ~6 kB large temp buffer for CC310 on the stack.
    if (nrf_stack_info_overflowed())
    {
        NRF_LOG_ERROR("Stack overflow detected.");
        return NRF_ERROR_CRYPTO_STACK_OVERFLOW;
    }

    if (size > 0)
    {
        VERIFY_TRUE(p_input_data != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    }

    VERIFY_TRUE(m_initialized == NRF_CRYPTO_RNG_MODULE_INIT_MAGIC_VALUE,
                NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED);

#if NRF_MODULE_ENABLED(NRF_CRYPTO_RNG_STATIC_MEMORY_BUFFERS)

    VERIFY_TRUE(p_temp_buffer == NULL, NRF_ERROR_CRYPTO_INVALID_PARAM);
    p_temp_buffer = &m_temp_buffer;

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_RNG_STATIC_MEMORY_BUFFERS)

    // Allocate temporary buffer internally if not statically allocated or provided by the user.
    if (p_temp_buffer == NULL)
    {
        p_allocated_temp_buffer = NRF_CRYPTO_ALLOC(sizeof(nrf_crypto_rng_temp_buffer_t));
        if (p_allocated_temp_buffer == NULL)
        {
            return NRF_ERROR_CRYPTO_ALLOC_FAILED;
        }
        p_temp_buffer = (nrf_crypto_rng_temp_buffer_t *)p_allocated_temp_buffer;
    }

    ret_code = nrf_crypto_rng_backend_reseed(mp_context, p_temp_buffer, p_input_data, size);

    if (p_allocated_temp_buffer != NULL)
    {
        NRF_CRYPTO_FREE(p_allocated_temp_buffer);
    }

    return ret_code;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_RNG)
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
