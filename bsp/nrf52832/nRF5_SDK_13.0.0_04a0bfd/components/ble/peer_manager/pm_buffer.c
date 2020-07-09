/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(PEER_MANAGER)
#include "pm_buffer.h"

#include <stdbool.h>
#include <string.h>
#include "nrf_error.h"
#include "pm_mutex.h"


#define BUFFER_IS_VALID(p_buffer) ((p_buffer != NULL)             \
                                && (p_buffer->p_memory != NULL)   \
                                && (p_buffer->p_mutex  != NULL))



ret_code_t pm_buffer_init(pm_buffer_t * p_buffer,
                          uint8_t     * p_buffer_memory,
                          uint32_t      buffer_memory_size,
                          uint8_t     * p_mutex_memory,
                          uint32_t      mutex_memory_size,
                          uint32_t      n_blocks,
                          uint32_t      block_size)
{
    if (   (p_buffer           != NULL)
        && (p_buffer_memory    != NULL)
        && (p_mutex_memory     != NULL)
        && (buffer_memory_size >= (n_blocks * block_size))
        && (mutex_memory_size  >= MUTEX_STORAGE_SIZE(n_blocks))
        && (n_blocks           != 0)
        && (block_size         != 0))
    {
        p_buffer->p_memory   = p_buffer_memory;
        p_buffer->p_mutex    = p_mutex_memory;
        p_buffer->n_blocks   = n_blocks;
        p_buffer->block_size = block_size;
        pm_mutex_init(p_buffer->p_mutex, n_blocks);

        return NRF_SUCCESS;
    }
    else
    {
        return NRF_ERROR_INVALID_PARAM;
    }
}


uint8_t pm_buffer_block_acquire(pm_buffer_t * p_buffer, uint32_t n_blocks)
{
    if (!BUFFER_IS_VALID(p_buffer))
    {
        return ( PM_BUFFER_INVALID_ID );
    }

    uint8_t first_locked_mutex = PM_BUFFER_INVALID_ID;

    for (uint8_t i = 0; i < p_buffer->n_blocks; i++)
    {
        if (pm_mutex_lock(p_buffer->p_mutex, i))
        {
            if (first_locked_mutex == PM_BUFFER_INVALID_ID)
            {
                first_locked_mutex = i;
            }
            if ((i - first_locked_mutex + 1) == n_blocks)
            {
                return first_locked_mutex;
            }
        }
        else if (first_locked_mutex != PM_BUFFER_INVALID_ID)
        {
            for (uint8_t j = first_locked_mutex; j < i; j++)
            {
                pm_buffer_release(p_buffer, j);
            }
            first_locked_mutex = PM_BUFFER_INVALID_ID;
        }
    }

    return ( PM_BUFFER_INVALID_ID );
}


uint8_t * pm_buffer_ptr_get(pm_buffer_t * p_buffer, uint8_t id)
{
    if (!BUFFER_IS_VALID(p_buffer))
    {
        return ( NULL );
    }

    if ( (id != PM_BUFFER_INVALID_ID)
    &&   pm_mutex_lock_status_get(p_buffer->p_mutex, id) )
    {
        return ( &p_buffer->p_memory[id * p_buffer->block_size] );
    }
    else
    {
        return ( NULL );
    }
}


void pm_buffer_release(pm_buffer_t * p_buffer, uint8_t id)
{
    if (    BUFFER_IS_VALID(p_buffer)
       &&  (id != PM_BUFFER_INVALID_ID)
       &&   pm_mutex_lock_status_get(p_buffer->p_mutex, id))
    {
        pm_mutex_unlock(p_buffer->p_mutex, id);
    }
}
#endif // NRF_MODULE_ENABLED(PEER_MANAGER)
