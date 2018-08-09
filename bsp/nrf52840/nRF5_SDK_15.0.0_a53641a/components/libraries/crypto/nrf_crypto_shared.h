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

#ifndef NRF_CRYPTO_SHARED_H__
#define NRF_CRYPTO_SHARED_H__

/** @internal @file
 *
 * @defgroup nrf_crypto_shared Shared macros for nrf_crypto
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Module containing shared macros for nrf_crypto.
 */

#include "sdk_macros.h"
#include "nrf_crypto_mem.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @internal @brief Macro for verifying statement to be true. It will cause the exterior function
 *                   to return err_code if the statement is not true, but only after freeing the
 *                   memory pointed to by p_memory if p_memory is not NULL.
 *
 * @param[in]   statement   Statement to test.
 * @param[in]   err_code    Error value to return if test was invalid.
 * @param[in]   p_memory    The memory block to be freed in case of error.
 *
 * @retval      nothing, but will cause the exterior function to return @p err_code if @p statement
 *              is false.
 */
#define NRF_CRYPTO_VERIFY_TRUE_DEALLOCATE(statement, err_code, p_memory)    \
do                                                                          \
{                                                                           \
    if (!(statement))                                                       \
    {                                                                       \
        if (p_memory != NULL)                                               \
        {                                                                   \
            NRF_CRYPTO_FREE(p_memory);                                      \
        }                                                                   \
        return err_code;                                                    \
    }                                                                       \
} while (0)


/**
 * @internal @brief Macro for verifying that a function returned NRF_SUCCESS. It will cause the
 *                  exterior function to return err_code if the err_code is not @ref NRF_SUCCESS,
 *                  but only after freeing the memory pointed to by p_memory if p_memory is not
 *                  NULL.
 *
 * @param[in] err_code The error code to check.
 * @param[in] p_memory The memory block to be freed in case of error.
 */
#ifdef DISABLE_PARAM_CHECK
#define NRF_CRYPTO_VERIFY_SUCCESS_DEALLOCATE()
#else
#define NRF_CRYPTO_VERIFY_SUCCESS_DEALLOCATE(err_code, p_memory)                       \
    NRF_CRYPTO_VERIFY_TRUE_DEALLOCATE((err_code) == NRF_SUCCESS, (err_code), p_memory)
#endif /* DISABLE_PARAM_CHECK */


/**
 * @internal @brief Generate a vector with random data of given size.
 *
 * @details This function does not check or lock the CC310 mutex, and should only be used
 *
 * @note Only for internal use in nrf_crypto.
 *
 * @param[in,out]   p_target    Buffer to hold the random generated data.
 *                              This buffer must be at least as large as the size parameter.
 * @param[in]       size        Length (in bytes) to generate random data for.
 *
 * @retval      See return values for @ref nrf_crypto_rng_vector_generate.
 */
ret_code_t nrf_crypto_rng_vector_generate_no_mutex(uint8_t * const p_target, size_t size);


/**
 * @internal @brief Generate a vector of constrained random data of given size, between the
 *                  specified min and max values.
 *
 * @details This function does not check or lock the CC310 mutex, and should only be used
 *
 * @note Only for internal use in nrf_crypto.
 *
 * @param[in,out]   p_target    Buffer to hold the random generated data.
 *                              This buffer must be at least as large as the size parameter.
 * @param[in]       p_min       Byte array defining the lower limit of the random vector.
 * @param[in]       p_max       Byte array defining the upper limit of the random vector.
 * @param[in]       size        Length (in bytes) to generate random data for. Note that all three
 *                              buffers (p_target, p_min and p_max) must be of this size.
 *
 * @retval      See return values for @ref nrf_crypto_rng_vector_generate_in_range.
 */
ret_code_t nrf_crypto_rng_vector_generate_in_range_no_mutex(uint8_t         * const p_target,
                                                            uint8_t   const * const p_min,
                                                            uint8_t   const * const p_max,
                                                            size_t                  size);


/** @internal @brief Swap bytes order inside provided buffer (in place).
 *
 * @note Only for internal use in nrf_crypto.
 *
 * @param[in,out]   p_buffer    Buffer with data to swap.
 * @param[in]       size        Number of bytes in @p p_buffer.
 */
void nrf_crypto_internal_swap_endian_in_place(uint8_t * p_buffer, size_t size);


/** @internal @brief Copy from one buffer to another and swap byte order.
 *
 * @note Only for internal use in nrf_crypto.
 *
 * @param[out]   p_out   Buffer with source data.
 * @param[in]    p_in    Destination buffer with swapped bytes.
 * @param[in]    size    Number of bytes in @p p_out and @p p_in.
 */
void nrf_crypto_internal_swap_endian(uint8_t * p_out, uint8_t const * p_in, size_t size);


/** @internal @brief Swap bytes order inside buffer containing two integers (in place).
 *
 * @note Only for internal use in nrf_crypto.
 *
 * @param[in,out]   p_buffer    Buffer with data to swap.
 * @param[in]       part_size   Number of bytes in single integer which is half of size of @p p_buffer.
 */
void nrf_crypto_internal_double_swap_endian_in_place(uint8_t * p_buffer, size_t part_size);


/** @internal @brief Copy from one buffer containing two integers to another and swap byte order of each integer.
 *
 * @note Only for internal use in nrf_crypto.
 *
 * @param[out]   p_out      Buffer with source data.
 * @param[in]    p_in       Destination buffer with swapped bytes.
 * @param[in]    part_size  Number of bytes in single integer which is half of size of @p p_out and @p p_in.
 */
void nrf_crypto_internal_double_swap_endian(uint8_t * p_out, uint8_t const * p_in, size_t part_size);


#ifdef __cplusplus
}
#endif

/**@} */

#endif // NRF_CRYPTO_SHARED_H__
