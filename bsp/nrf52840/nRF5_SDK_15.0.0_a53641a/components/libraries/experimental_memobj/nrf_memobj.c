/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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

#include "nrf_memobj.h"
#include "nrf_atomic.h"
#include "nrf_assert.h"

typedef struct memobj_elem_s memobj_elem_t;

typedef struct
{
    memobj_elem_t * p_next;
} memobj_header_t;

typedef struct
{
    uint8_t  user_cnt;
    uint8_t  chunk_cnt;
    uint16_t chunk_size;
} memobj_head_header_fields_t;

typedef struct
{
    union
    {
        nrf_atomic_u32_t            atomic_user_cnt;
        memobj_head_header_fields_t fields;
    } data;
} memobj_head_header_t;

typedef struct
{
    memobj_header_t      header;
    memobj_head_header_t head_header;
    uint8_t              data[1];
} memobj_head_t;

STATIC_ASSERT(sizeof(memobj_header_t) == NRF_MEMOBJ_STD_HEADER_SIZE);

struct memobj_elem_s
{
    memobj_header_t  header;
    uint8_t          data[1];
};

ret_code_t nrf_memobj_pool_init(nrf_memobj_pool_t const * p_pool)
{
    return nrf_balloc_init((nrf_balloc_t const *)p_pool);
}

nrf_memobj_t * nrf_memobj_alloc(nrf_memobj_pool_t const * p_pool,
                                size_t size)
{
    uint32_t bsize = (uint32_t)NRF_BALLOC_ELEMENT_SIZE((nrf_balloc_t const *)p_pool) - sizeof(memobj_header_t);
    uint8_t num_of_chunks = (uint8_t)CEIL_DIV(size + sizeof(memobj_head_header_t), bsize);

    memobj_head_t * p_head = nrf_balloc_alloc((nrf_balloc_t const *)p_pool);
    if (p_head == NULL)
    {
        return NULL;
    }
    p_head->head_header.data.fields.user_cnt = 0;
    p_head->head_header.data.fields.chunk_cnt = 1;
    p_head->head_header.data.fields.chunk_size = bsize;

    memobj_header_t * p_prev = (memobj_header_t *)p_head;
    memobj_header_t * p_curr;
    uint32_t i;
    uint32_t chunk_less1 = (uint32_t)num_of_chunks - 1;

    p_prev->p_next =  (memobj_elem_t *)p_pool;
    for (i = 0; i < chunk_less1; i++)
    {
        p_curr = (memobj_header_t *)nrf_balloc_alloc((nrf_balloc_t const *)p_pool);
        if (p_curr)
        {
            (p_head->head_header.data.fields.chunk_cnt)++;
            p_prev->p_next = (memobj_elem_t *)p_curr;
            p_curr->p_next = (memobj_elem_t *)p_pool;
            p_prev = p_curr;
        }
        else
        {
            //Couldn't allocate all requested buffers
            nrf_memobj_free((nrf_memobj_t *)p_head);
            return NULL;
        }
    }
    return (nrf_memobj_t *)p_head;
}

void nrf_memobj_free(nrf_memobj_t * p_obj)
{
    memobj_head_t * p_head = (memobj_head_t *)p_obj;
    uint8_t chunk_cnt = p_head->head_header.data.fields.chunk_cnt;
    uint32_t i;
    memobj_header_t * p_curr = (memobj_header_t *)p_obj;
    memobj_header_t * p_next;
    uint32_t chunk_less1 = (uint32_t)chunk_cnt - 1;

    for (i = 0; i < chunk_less1; i++)
    {
        p_curr = (memobj_header_t *)p_curr->p_next;
    }
    nrf_balloc_t const * p_pool2 = (nrf_balloc_t const *)p_curr->p_next;

    p_curr = (memobj_header_t *)p_obj;
    for (i = 0; i < chunk_cnt; i++)
    {
        p_next = (memobj_header_t *)p_curr->p_next;
        nrf_balloc_free(p_pool2, p_curr);
        p_curr = p_next;
    }
}

void nrf_memobj_get(nrf_memobj_t const * p_obj)
{
    memobj_head_t * p_head = (memobj_head_t *)p_obj;
    (void)nrf_atomic_u32_add(&p_head->head_header.data.atomic_user_cnt, 1);
}

void nrf_memobj_put(nrf_memobj_t * p_obj)
{
    memobj_head_t * p_head = (memobj_head_t *)p_obj;
    uint32_t user_cnt = nrf_atomic_u32_sub(&p_head->head_header.data.atomic_user_cnt, 1);
    memobj_head_header_fields_t * p_fields = (memobj_head_header_fields_t *)&user_cnt;
    if (p_fields->user_cnt == 0)
    {
        nrf_memobj_free(p_obj);
    }
}

static void memobj_op(nrf_memobj_t * p_obj,
                      void * p_data,
                      uint32_t len,
                      uint32_t offset,
                      bool read)
{

    memobj_head_t * p_head  = (memobj_head_t *)p_obj;
    uint32_t space_in_chunk = p_head->head_header.data.fields.chunk_size;
    memobj_elem_t * p_curr_chunk = (memobj_elem_t *)p_obj;
    uint32_t chunk_idx = (offset + sizeof(memobj_head_header_fields_t))/space_in_chunk;
    uint32_t chunk_offset = (offset + sizeof(memobj_head_header_fields_t)) % space_in_chunk;

    uint8_t chunks_expected = CEIL_DIV((offset + sizeof(memobj_head_header_fields_t) + len),
                                       space_in_chunk);
    UNUSED_VARIABLE(chunks_expected);
    ASSERT(p_head->head_header.data.fields.chunk_cnt >= chunks_expected);

    while (chunk_idx > 0)
    {
        p_curr_chunk = p_curr_chunk->header.p_next;
        chunk_idx--;
    }

    uint32_t src_offset  = 0;
    uint32_t curr_cpy_size = space_in_chunk-chunk_offset;
    curr_cpy_size = curr_cpy_size > len ? len : curr_cpy_size;

    while (len)
    {
        if (read)
        {
            memcpy(&((uint8_t *)p_data)[src_offset], &p_curr_chunk->data[chunk_offset], curr_cpy_size);
        }
        else
        {
            memcpy(&p_curr_chunk->data[chunk_offset], &((uint8_t *)p_data)[src_offset], curr_cpy_size);
        }
        chunk_offset = 0;
        p_curr_chunk = p_curr_chunk->header.p_next;
        len -= curr_cpy_size;
        src_offset += curr_cpy_size;
        curr_cpy_size = (space_in_chunk > len) ? len : space_in_chunk;
    }
}

void nrf_memobj_write(nrf_memobj_t * p_obj,
                      void * p_data,
                      uint32_t len,
                      uint32_t offset)
{

    memobj_op(p_obj, p_data, len, offset, false);
}

void nrf_memobj_read(nrf_memobj_t * p_obj,
                     void * p_data,
                     uint32_t len,
                     uint32_t offset)
{
    memobj_op(p_obj, p_data, len, offset, true);
}
