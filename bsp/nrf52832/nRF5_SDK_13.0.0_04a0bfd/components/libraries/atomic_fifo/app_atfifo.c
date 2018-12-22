/**
 * Copyright (c) 2011 - 2017, Nordic Semiconductor ASA
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

#include "app_atfifo.h"
#include "app_atfifo_internal.h"
#include <string.h>
#include "app_util.h"


/* Unions testing */
STATIC_ASSERT(sizeof(nrf_atfifo_postag_t) == sizeof(uint32_t));


ret_code_t app_atfifo_init(app_atfifo_t * const p_fifo, void * p_buf, uint16_t buf_size, uint16_t item_size)
{
    if(NULL == p_buf)
    {
        return NRF_ERROR_NULL;
    }
    if(0 != (buf_size % item_size))
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    p_fifo->p_buf     = p_buf;
    p_fifo->tail.tag  = 0;
    p_fifo->head.tag  = 0;
    p_fifo->buf_size  = buf_size;
    p_fifo->item_size = item_size;

    return NRF_SUCCESS;
}


ret_code_t app_atfifo_clear(app_atfifo_t * const p_fifo)
{
    bool resleased = app_atfifo_space_clear(p_fifo);
    return resleased ? NRF_SUCCESS : NRF_ERROR_BUSY;
}


ret_code_t app_atfifo_put(app_atfifo_t * const p_fifo, void const * p_var, size_t size, bool * const p_visible)
{
    app_atfifo_wcontext_t context;
    bool visible;
    void * p_d = app_atfifo_wopen(p_fifo, &context, size);
    if(NULL == p_d)
    {
        return NRF_ERROR_NO_MEM;
    }

    memcpy(p_d, p_var, size);

    visible = app_atfifo_wcommit(p_fifo, &context);
    if(NULL != p_visible)
    {
        *p_visible = visible;
    }
    return NRF_SUCCESS;
}


void * app_atfifo_wopen_internal(app_atfifo_t * const p_fifo, app_atfifo_wcontext_t * p_context)
{
    if(app_atfifo_wspace_req(p_fifo, &(p_context->last_tail)))
    {
        return ((uint8_t*)(p_fifo->p_buf)) + p_context->last_tail.pos.wr;
    }
    return NULL;
}


bool app_atfifo_wcommit(app_atfifo_t * const p_fifo, app_atfifo_wcontext_t * p_context)
{
    if((p_context->last_tail.pos.wr) == (p_context->last_tail.pos.rd))
    {
        app_atfifo_wspace_close(p_fifo);
        return true;
    }
    return false;
}


ret_code_t app_atfifo_get(app_atfifo_t * const p_fifo, void * const p_var, size_t size, bool * p_released)
{
    app_atfifo_rcontext_t context;
    bool released;
    void const * p_s = app_atfifo_ropen(p_fifo, &context, size);
    if(NULL == p_s)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    memcpy(p_var, p_s, size);

    released = app_atfifo_rflush(p_fifo, &context);
    if(NULL != p_released)
    {
        *p_released = released;
    }
    return NRF_SUCCESS;
}


void const * app_atfifo_ropen_internal(app_atfifo_t * const p_fifo, app_atfifo_rcontext_t * p_context)
{
    if(app_atfifo_rspace_req(p_fifo, &(p_context->last_head)))
    {
        return ((uint8_t*)(p_fifo->p_buf)) + p_context->last_head.pos.rd;
    }
    return NULL;
}


bool app_atfifo_rflush(app_atfifo_t * const p_fifo, app_atfifo_rcontext_t * p_context)
{
    if((p_context->last_head.pos.wr) == (p_context->last_head.pos.rd))
    {
        app_atfifo_rspace_close(p_fifo);
        return true;
    }
    return false;
}
