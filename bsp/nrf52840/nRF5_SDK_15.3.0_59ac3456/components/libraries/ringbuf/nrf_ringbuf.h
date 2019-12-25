/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
#ifndef NRF_RINGBUF_H
#define NRF_RINGBUF_H

/**
* @defgroup nrf_ringbuf Ring buffer
* @{
* @ingroup app_common
* @brief Functions for controlling the ring buffer.
*/

#include <stdint.h>
#include "nrf_atomic.h"
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Ring buffer instance control block.
 * */
typedef struct
{
    nrf_atomic_flag_t   wr_flag;   //!< Protection flag.
    nrf_atomic_flag_t   rd_flag;   //!< Protection flag.
    uint32_t            wr_idx;     //!< Write index (updated when putting).
    uint32_t            tmp_wr_idx; //!< Temporary write index (updated when allocating).
    uint32_t            rd_idx;     //!< Read index (updated when freeing).
    uint32_t            tmp_rd_idx; //!< Temporary read index (updated when getting).
} nrf_ringbuf_cb_t;

/**
 * @brief Ring buffer instance structure.
 * */
typedef struct
{
    uint8_t           * p_buffer;     //!< Pointer to the memory used by the ring buffer.
    uint32_t            bufsize_mask; //!< Buffer size mask (buffer size must be a power of 2).
    nrf_ringbuf_cb_t  * p_cb;         //!< Pointer to the instance control block.
} nrf_ringbuf_t;

/**
 * @brief Macro for defining a ring buffer instance.
 *
 * @param _name Instance name.
 * @param _size Size of the ring buffer (must be a power of 2).
 * */
#define NRF_RINGBUF_DEF(_name, _size)                                         \
    STATIC_ASSERT(IS_POWER_OF_TWO(_size));                                    \
    static uint8_t CONCAT_2(_name,_buf)[_size];                               \
    static nrf_ringbuf_cb_t CONCAT_2(_name,_cb);                              \
    static const nrf_ringbuf_t _name = {                                      \
            .p_buffer = CONCAT_2(_name,_buf),                                 \
            .bufsize_mask = _size - 1,                                        \
            .p_cb         = &CONCAT_2(_name,_cb),                             \
    }

/**
 * @brief Function for initializing a ring buffer instance.
 *
 * @param p_ringbuf             Pointer to the ring buffer instance.
 *
 * */
void nrf_ringbuf_init(nrf_ringbuf_t const * p_ringbuf);

/**
 * @brief Function for allocating memory from a ring buffer.
 *
 * This function attempts to allocate the amount of memory requested by the user, or a smaller amount if
 * the requested amount is not available. If a start flag is set, then exclusive access to allocation
 * is established. @ref nrf_ringbuf_put frees access to allocation. If a start flag is not set, then
 * exclusive access check is omitted.
 *
 * @param[in] p_ringbuf      Pointer to the ring buffer instance.
 * @param[in] pp_data        Pointer to the pointer to the allocated buffer.
 * @param[in, out] p_length  Pointer to length. Length is set to the requested amount and filled
 *                           by the function with actually allocated amount.
 * @param[in] start          Set to true if exclusive access should be controlled.
 *
 * @retval NRF_SUCCESS       Successful allocation (can be smaller amount than requested).
 *         NRF_ERROR_BUSY    Ring buffer allocation process (alloc-put) is ongoing.
 *
 * */
ret_code_t nrf_ringbuf_alloc(nrf_ringbuf_t const * p_ringbuf, uint8_t * * pp_data, size_t * p_length, bool start);

/**
 * @brief Function for commiting data to a ring buffer.
 *
 * When an allocated buffer (see @ref nrf_ringbuf_alloc) has been filled with data, it must be committed
 * to make it available for @ref nrf_ringbuf_get and @ref nrf_ringbuf_cpy_get. This function commits
 * the data (can be smaller amount than allocated).
 *
 * @param[in] p_ringbuf          Pointer to the ring buffer instance.
 * @param[in] length             Amount of bytes to put.

 * @return  NRF_SUCCESS on successful put or error.
 * */
ret_code_t nrf_ringbuf_put(nrf_ringbuf_t const * p_ringbuf, size_t length);

/**
 * @brief Function for copying data directly into the ring buffer.
 *
 * This function copies a user buffer to the ring buffer.
 *
 * @param[in] p_ringbuf       Pointer to the ring buffer instance.
 * @param[in] p_data          Pointer to the input buffer.
 * @param[in, out] p_length   Amount of bytes to copy. Amount of bytes copied.

 * @return  NRF_SUCCESS on successful put or error.
 * */
ret_code_t nrf_ringbuf_cpy_put(nrf_ringbuf_t const * p_ringbuf,
                               uint8_t const* p_data,
                               size_t * p_length);


/**
 * Function for getting data from the ring buffer.
 *
 * This function attempts to get the requested amount of data from the ring buffer. If a start flag is set, then
 * exclusive access to getting data from the ring buffer is established. @ref nrf_ringbuf_free frees
 * access to getting data from the ring buffer. If a start flag is not set, then
 * exclusive access check is omitted.
 *
 * @param[in] p_ringbuf     Pointer to the ring buffer instance.
 * @param[in] pp_data       Pointer to the pointer to the buffer with data.
 * @param[in, out] p_length Pointer to length. Length is set to the requested amount and filled
 *                          by the function with the actual amount.
 * @param[in] start         Set to true if exclusive access should be controlled.
 *
 * @retval NRF_SUCCESS            Successful getting (can be smaller amount than requested).
 *         NRF_ERROR_BUSY         Ring buffer getting process (get-free) is ongoing.
 */
ret_code_t nrf_ringbuf_get(nrf_ringbuf_t const * p_ringbuf, uint8_t * * pp_data, size_t * p_length, bool start);

/**
 * @brief Function for freeing a buffer back to the ring buffer.
 *
 * When a buffer with data taken from the ring buffer (see @ref nrf_ringbuf_get) has been processed, it
 * must be freed to make it available for further use. This function frees the buffer (can be smaller
 * amount than get).
 *
 * @param[in] p_ringbuf          Pointer to the ring buffer instance.
 * @param[in] length             Amount of bytes to free.

 * @return  NRF_SUCCESS on successful put or error.
 * */
ret_code_t nrf_ringbuf_free(nrf_ringbuf_t const * p_ringbuf, size_t length);

/**
 * @brief Function for copying data directly out of the ring buffer.
 *
 * This function copies available data from the ring buffer to a user buffer.
 *
 * @param[in]      p_ringbuf    Pointer to the ring buffer instance.
 * @param[in]      p_data       Pointer to the input buffer.
 * @param[in, out] p_length     Amount of bytes to copy. Amount of bytes copied.

 * @return  NRF_SUCCESS on successful put or error.
 * */
ret_code_t nrf_ringbuf_cpy_get(nrf_ringbuf_t const * p_ringbuf,
                               uint8_t * p_data,
                               size_t * p_length);
#ifdef __cplusplus
}
#endif

#endif //NRF_RINGBUF_H
/** @} */
