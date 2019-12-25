/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#ifndef MBUF_H__
#define MBUF_H__

/**
 * @file mbuf.h
 *
 * @defgroup iot_socket_mbuf Memory management for socket
 * @ingroup iot_sdk_socket
 * @{
 * @brief Memory management for socket.
 */

#include <stdbool.h>
#include "nrf_fifo.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Function for reading data from a buffer. */
typedef uint32_t (*mbuf_read_fn)(void     * p_ctx,
                                 uint32_t   read_offset,
                                 uint8_t  * p_dest,
                                 uint32_t   dest_len);

/**@brief Function for checking buffer length. */
typedef uint32_t (*mbuf_buf_len_fn)(void * p_ctx);

/**@brief Function for freeing a buffer. */
typedef void     (*mbuf_free_fn)(void * p_ctx);

/**@brief Memory management structure. */
typedef struct
{
    nrf_fifo_t      fifo;       /**< FIFO for storing data buffers. */
    mbuf_read_fn    read;       /**< Function for reading data from a buffer. */
    mbuf_buf_len_fn buf_len;    /**< Function for checking buffer length. */
    mbuf_free_fn    free;       /**< Function for freeing a buffer. */
    uint32_t        read_pos;   /**< Read position in the currently processed buffer. */
    void          * p_current;  /**< Pointer to the currently processed buffer. */
} mbuf_t;

/**
 * @brief Function for initializing the memory buffer manager.
 *
 * This function allocates resources for the mbuf FIFO and initializes the mbuf.
 *
 * @param[in, out] p_mbuf       Pointer to the mbuf structure to initialize.
 * @param[in]      read_fn      Function for reading data from a buffer.
 * @param[in]      buf_len_fn   Function for checking buffer length.
 * @param[in]      free_fn      Function for freeing a buffer.
 * @param[in]      nmemb        Maximum number of data buffers.
 *
 * @return NRF_SUCCESS on success, otherwise error code is returned.
 */
uint32_t mbuf_init(mbuf_t        * p_mbuf,
                   mbuf_read_fn    read_fn,
                   mbuf_buf_len_fn buf_len_fn,
                   mbuf_free_fn    free_fn,
                   uint32_t        nmemb);

/**
 * @brief Function for deinitializing the memory buffer manager.
 *
 * This function releases any resources allocated for mbuf instance pointed by p_mbuf.
 *
 * @param[in, out] p_mbuf Pointer to the mbuf structure to deinitialize.
 */
void     mbuf_deinit(mbuf_t * p_mbuf);

/**
 * @brief Function for putting a data buffer in the mbuf.
 *
 * @param[in, out] p_mbuf Pointer to the mbuf structure that shall store the buffer.
 * @param[in]      p_ctx  Pointer to the data buffer to store.
 *
 * @return NRF_SUCCESS on success, otherwise error code is returned.
 */
uint32_t mbuf_write(mbuf_t * p_mbuf, void * p_ctx);

/**
 * @brief Function for reading data from the mbuf.
 *
 * @param[in, out] p_mbuf   Pointer to the mbuf structure to read data from.
 * @param[in]      p_buf    Pointer to the buffer where data shall be read from.
 * @param[out]     buf_size Size of the buffer pointed by p_buf.
 *
 * @return NRF_SUCCESS on success, otherwise error code is returned.
 */
uint32_t mbuf_read(mbuf_t * p_mbuf, void * p_buf, uint32_t buf_size);

/**
 * @brief Function for checking if the mbuf is empty.
 *
 * @param[in] p_mbuf Pointer to the mbuf structure that shall be checked.
 *
 * @return True if mbuf is empty, false otherwise.
 */
bool     mbuf_empty(mbuf_t * p_mbuf);

#ifdef __cplusplus
}
#endif

/**@} */

#endif // MBUF_H__
