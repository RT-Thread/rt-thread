/**
 * Copyright (c) 2013 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(APP_FIFO)
#include "app_fifo.h"

static __INLINE uint32_t fifo_length(app_fifo_t * p_fifo)
{
    uint32_t tmp = p_fifo->read_pos;
    return p_fifo->write_pos - tmp;
}


#define FIFO_LENGTH() fifo_length(p_fifo)  /**< Macro for calculating the FIFO length. */


/**@brief Put one byte to the FIFO. */
static __INLINE void fifo_put(app_fifo_t * p_fifo, uint8_t byte)
{
    p_fifo->p_buf[p_fifo->write_pos & p_fifo->buf_size_mask] = byte;
    p_fifo->write_pos++;
}


/**@brief Look at one byte in the FIFO. */
static __INLINE void fifo_peek(app_fifo_t * p_fifo, uint16_t index, uint8_t * p_byte)
{
    *p_byte = p_fifo->p_buf[(p_fifo->read_pos + index) & p_fifo->buf_size_mask];
}


/**@brief Get one byte from the FIFO. */
static __INLINE void fifo_get(app_fifo_t * p_fifo, uint8_t * p_byte)
{
    fifo_peek(p_fifo, 0, p_byte);
    p_fifo->read_pos++;
}


uint32_t app_fifo_init(app_fifo_t * p_fifo, uint8_t * p_buf, uint16_t buf_size)
{
    // Check buffer for null pointer.
    if (p_buf == NULL)
    {
        return NRF_ERROR_NULL;
    }

    // Check that the buffer size is a power of two.
    if (!IS_POWER_OF_TWO(buf_size))
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    p_fifo->p_buf         = p_buf;
    p_fifo->buf_size_mask = buf_size - 1;
    p_fifo->read_pos      = 0;
    p_fifo->write_pos     = 0;

    return NRF_SUCCESS;
}


uint32_t app_fifo_put(app_fifo_t * p_fifo, uint8_t byte)
{
    if (FIFO_LENGTH() <= p_fifo->buf_size_mask)
    {
        fifo_put(p_fifo, byte);
        return NRF_SUCCESS;
    }

    return NRF_ERROR_NO_MEM;
}


uint32_t app_fifo_get(app_fifo_t * p_fifo, uint8_t * p_byte)
{
    if (FIFO_LENGTH() != 0)
    {
        fifo_get(p_fifo, p_byte);
        return NRF_SUCCESS;
    }

    return NRF_ERROR_NOT_FOUND;

}


uint32_t app_fifo_peek(app_fifo_t * p_fifo, uint16_t index, uint8_t * p_byte)
{
    if (FIFO_LENGTH() > index)
    {
        fifo_peek(p_fifo, index, p_byte);
        return NRF_SUCCESS;
    }

    return NRF_ERROR_NOT_FOUND;
}


uint32_t app_fifo_flush(app_fifo_t * p_fifo)
{
    p_fifo->read_pos = p_fifo->write_pos;
    return NRF_SUCCESS;
}


uint32_t app_fifo_read(app_fifo_t * p_fifo, uint8_t * p_byte_array, uint32_t * p_size)
{
    VERIFY_PARAM_NOT_NULL(p_fifo);
    VERIFY_PARAM_NOT_NULL(p_size);

    const uint32_t byte_count    = fifo_length(p_fifo);
    const uint32_t requested_len = (*p_size);
    uint32_t       index         = 0;
    uint32_t       read_size     = MIN(requested_len, byte_count);

    (*p_size) = byte_count;

    // Check if the FIFO is empty.
    if (byte_count == 0)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    // Check if application has requested only the size.
    if (p_byte_array == NULL)
    {
        return NRF_SUCCESS;
    }

    // Fetch bytes from the FIFO.
    while (index < read_size)
    {
        fifo_get(p_fifo, &p_byte_array[index++]);
    }

    (*p_size) = read_size;

    return NRF_SUCCESS;
}


uint32_t app_fifo_write(app_fifo_t * p_fifo, uint8_t const * p_byte_array, uint32_t * p_size)
{
    VERIFY_PARAM_NOT_NULL(p_fifo);
    VERIFY_PARAM_NOT_NULL(p_size);

    const uint32_t available_count = p_fifo->buf_size_mask - fifo_length(p_fifo) + 1;
    const uint32_t requested_len   = (*p_size);
    uint32_t       index           = 0;
    uint32_t       write_size      = MIN(requested_len, available_count);

    (*p_size) = available_count;

    // Check if the FIFO is FULL.
    if (available_count == 0)
    {
        return NRF_ERROR_NO_MEM;
    }

    // Check if application has requested only the size.
    if (p_byte_array == NULL)
    {
        return NRF_SUCCESS;
    }

    //Fetch bytes from the FIFO.
    while (index < write_size)
    {
        fifo_put(p_fifo, p_byte_array[index++]);
    }

    (*p_size) = write_size;

    return NRF_SUCCESS;
}
#endif //NRF_MODULE_ENABLED(APP_FIFO)
