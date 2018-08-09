/**
 * Copyright (c) 2016 - 2018 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 * 
 * All Rights Reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
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
#ifndef SYS_RINGBUFFER_H_INCLUDED
#define SYS_RINGBUFFER_H_INCLUDED

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/** @file
 * This file contains declarations of the Ring buffer routines and necessary types. Please note that
 * each ring buffer element should have size of 1 byte.
 *
 * @defgroup sys_ringbuffer System Ring buffer API
 * @ingroup sys_15_4
 * @{
 * @brief Module for declaring System Ring buffer API.
 * @details The Ring Buffer module implements routines to deal with the ring buffer. The following routines are supported:
 * sys_ringbuffer_insert(), sys_ringbuffer_remove() to operate with single element. The
 * sys_ringbuffer_remove_multiple() can be used to remove (read) several elements at once. The
 * sys_ringbuffer_clear(), sys_ringbuffer_init(), and sys_ringbuffer_init_over() functions are used to clean up and
 * initialize the ring buffer. Some information about the initialized ring buffer is available via the
 * following routines: sys_ringbuffer_size_get() to get the number of used elements, sys_ringbuffer_chunk_get()
 * to return the biggest, available to read, continuous chunk of elements, sys_ringbuffer_is_empty() and
 * sys_ringbuffer_is_full() to check if the ring buffer is empty/full, and sys_ringbuffer_max_size_get() to get
 * the ring buffer capacity. One of the samples for ring buffer usage is the UART implementation.
 */

/** This structure holds all necessary information about a ring buffer. It is intentionally left undocumented
 * by Doxygen.
 *
 * All these fields are private and must NOT be changed by the user.
 */
typedef struct
{
    size_t    write_index;
    size_t    read_index;
    uint8_t * array;
    size_t    size;
    bool      is_full;
} sys_ringbuffer_t;

/** @brief Function for initializing an empty ring buffer over passed memory.
 *
 * @param[inout] buffer  Instance of sys_ringbuffer_t that will be initialized.
 * @param[in]    memory  Start address of the memory region used as a ring buffer.
 * @param[in]    length  Size in bytes of the memory region used as a ring buffer.
 */
void    sys_ringbuffer_init(sys_ringbuffer_t * buffer,
                            const void * memory,
                            const size_t length);

/** @brief Function for initializing a ring buffer over passed memory and marking all 
 *         pre_init_length elements as inserted.
 *
 * @details This function may be used to initialize a buffer with some
 * pre-initialized data in it. Passed memory region is interpreted by this function
 * as an already filled (partly or fully) ring buffer so that \a pre_init_length
 * elements are marked as inserted.
 *
 * @param[inout] buffer          Instance of sys_ringbuffer_t that will be initialized.
 * @param[in]    memory          Start address of the memory region used as a ring buffer.
 * @param[in]    pre_init_length Number of elements (bytes) that had already been in \a memory.
 * They would be inserted into the newly-initialized ring buffer in a FIFO manner.
 * @param[in]    length          Size of the memory region used as a ring buffer.
 */
void    sys_ringbuffer_init_over(sys_ringbuffer_t * buffer,
                                 const void * memory,
                                 const size_t pre_init_length,
                                 const size_t length);

/** @brief Function for removing an element from a ring buffer and returning it.
 *
 * @param[inout] buf Instance of @c sys_ringbuffer_t.
 *
 * @return Value of the removed element.
 *
 * @warning This buffer has no underflow control except assert.
 */
uint8_t sys_ringbuffer_remove(sys_ringbuffer_t * buf);

/** @brief Function for quickly removing up to chunk_size elements from a ring buffer
 *         and marking those elements as available in the ring buffer.
 *
 * @param[inout] buffer  Instance of @c sys_ringbuffer_t.
 * @param[in] chunk_size Number of elements to release.
 */
void    sys_ringbuffer_remove_multiple(sys_ringbuffer_t * buffer,
                                       const size_t chunk_size);

/** @brief Function for inserting a new element into a ring buffer.
 *
 * @param[inout] buffer Instance of @c sys_ringbuffer_t.
 * @param[in] data      Element value to insert.
 *
 * @warning In case of overflow, this buffer will overwrite the oldest
 * element and the number of available elements will remain unchanged.
 */
void    sys_ringbuffer_insert(sys_ringbuffer_t * buffer, const uint8_t data);

/** @brief Function for clearing an instance of \a sys_ringbuffer_t, making it empty.
 *
 * @param[inout] buffer Instance of @c sys_ringbuffer_t.
 */
void    sys_ringbuffer_clear(sys_ringbuffer_t * buffer);

/** @brief Function for returning the number of used elements in a ring buffer instance.
 *
 * @param[inout] buf Instance of sys_ringbuffer_t.
 *
 * @return Number of elements.
 */
size_t  sys_ringbuffer_size_get(const sys_ringbuffer_t * buf);

/** @brief Function for returning the biggest, available to read, continuous chunk from a ring buffer array.
 *
 * @param[inout] buffer     Instance of @c sys_ringbuffer_t.
 * @param[out]   chunk      Pointer to a memory chunk removed from the ring buffer.
 * @param[out]   chunk_size Size of the removed chunk.
 *
 * @warning The returned chunk is still part of the ring buffer. To make the chunk elements available
 * for write, call @c sys_ringbuffer_remove_multiple() after the chunk is processed.
 */
void sys_ringbuffer_chunk_get(sys_ringbuffer_t * buffer,
                              void ** chunk,
                              size_t * chunk_size);

/** @brief Function for checking whether a ring buffer is empty.
 *
 * @param[inout] buf Instance of @c sys_ringbuffer_t.
 *
 * @return True if the ring buffer is empty.
 */
static inline bool sys_ringbuffer_is_empty(const sys_ringbuffer_t * buf)
{
    return ((buf->write_index == buf->read_index) && (!buf->is_full));
}

/** @brief Function for checking whether a ring buffer is full.
 *
 * @param[inout] buf Instance of @c sys_ringbuffer_t.
 *
 * @return True if number of items in the buffer equals to (length - 1).
 */
static inline bool sys_ringbuffer_is_full(const sys_ringbuffer_t * buf)
{
    return buf->is_full;
}

/** @brief Function for returning number of elements that can be potentially put into the buffer.
 *
 * @param[inout] buf Instance of @c sys_ringbuffer_t.
 *
 * @return Number of elements.
 */
static inline size_t sys_ringbuffer_max_size_get(const sys_ringbuffer_t * buf)
{
    return buf->size;
}

/** @} */

#endif /* SYS_RINGBUFFER_H_INCLUDED */
