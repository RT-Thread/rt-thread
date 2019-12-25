/**
 * Copyright (c) 2011 - 2019, Nordic Semiconductor ASA
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

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "app_util.h"
#include "nrf_atfifo.h"
#include "nrf_atfifo_internal.h"

#if NRF_ATFIFO_CONFIG_LOG_ENABLED
    #define NRF_LOG_LEVEL             NRF_ATFIFO_CONFIG_LOG_LEVEL
    #define NRF_LOG_INIT_FILTER_LEVEL NRF_ATFIFO_CONFIG_LOG_INIT_FILTER_LEVEL
    #define NRF_LOG_INFO_COLOR        NRF_ATFIFO_CONFIG_INFO_COLOR
    #define NRF_LOG_DEBUG_COLOR       NRF_ATFIFO_CONFIG_DEBUG_COLOR
#else
    #define NRF_LOG_LEVEL       0
#endif // NRF_ATFIFO_CONFIG_LOG_ENABLED
#include "nrf_log.h"

/* Unions testing */
STATIC_ASSERT(sizeof(nrf_atfifo_postag_t) == sizeof(uint32_t));


ret_code_t nrf_atfifo_init(nrf_atfifo_t * const p_fifo, void * p_buf, uint16_t buf_size, uint16_t item_size)
{
    if (NULL == p_buf)
    {
        NRF_LOG_INST_ERROR(p_fifo->p_log, "Initialization failed. p_buf == NULL");
        return NRF_ERROR_NULL;
    }
    if (0 != (buf_size % item_size))
    {
        NRF_LOG_INST_ERROR(p_fifo->p_log, "Initialization failed. Buf_size not multiple of item_size");
        return NRF_ERROR_INVALID_LENGTH;
    }

    p_fifo->p_buf     = p_buf;
    p_fifo->tail.tag  = 0;
    p_fifo->head.tag  = 0;
    p_fifo->buf_size  = buf_size;
    p_fifo->item_size = item_size;

    NRF_LOG_INST_INFO(p_fifo->p_log, "Initialized.");
    return NRF_SUCCESS;
}


ret_code_t nrf_atfifo_clear(nrf_atfifo_t * const p_fifo)
{
    bool released = nrf_atfifo_space_clear(p_fifo);
    NRF_LOG_INST_INFO(p_fifo->p_log, "Cleared result:%s", released ? "success" : "busy");
    return released ? NRF_SUCCESS : NRF_ERROR_BUSY;
}


ret_code_t nrf_atfifo_alloc_put(nrf_atfifo_t * const p_fifo, void const * p_var, size_t size, bool * const p_visible)
{
    nrf_atfifo_item_put_t context;
    bool visible;
    void * p_data = nrf_atfifo_item_alloc(p_fifo, &context);
    if (NULL == p_data)
    {
        NRF_LOG_INST_WARNING(p_fifo->p_log, "Copying in element (0x%08X) failed - no space.", p_var);
        return NRF_ERROR_NO_MEM;
    }

    memcpy(p_data, p_var, size);

    visible = nrf_atfifo_item_put(p_fifo, &context);
    if (NULL != p_visible)
    {
        *p_visible = visible;
    }
    NRF_LOG_INST_DEBUG(p_fifo->p_log, "Element (0x%08X) copied in.", p_var);
    return NRF_SUCCESS;
}


void * nrf_atfifo_item_alloc(nrf_atfifo_t * const p_fifo, nrf_atfifo_item_put_t * p_context)
{
    if (nrf_atfifo_wspace_req(p_fifo, &(p_context->last_tail)))
    {
        void * p_item = ((uint8_t*)(p_fifo->p_buf)) + p_context->last_tail.pos.wr;
        NRF_LOG_INST_DEBUG(p_fifo->p_log, "Allocated  element (0x%08X).", p_item);
        return p_item;
    }
    NRF_LOG_INST_WARNING(p_fifo->p_log, "Allocation failed - no space.");
    return NULL;
}


bool nrf_atfifo_item_put(nrf_atfifo_t * const p_fifo, nrf_atfifo_item_put_t * p_context)
{
    if ((p_context->last_tail.pos.wr) == (p_context->last_tail.pos.rd))
    {
        NRF_LOG_INST_DEBUG(p_fifo->p_log, "Put (uninterrupted)");
        nrf_atfifo_wspace_close(p_fifo);
        return true;
    }
    NRF_LOG_INST_DEBUG(p_fifo->p_log, "Put (interrupted!)");
    return false;
}


ret_code_t nrf_atfifo_get_free(nrf_atfifo_t * const p_fifo, void * const p_var, size_t size, bool * p_released)
{
    nrf_atfifo_item_get_t context;
    bool released;
    void const * p_s = nrf_atfifo_item_get(p_fifo, &context);
    if (NULL == p_s)
    {
        NRF_LOG_INST_WARNING(p_fifo->p_log, "Copying out failed - no item in the FIFO.");
        return NRF_ERROR_NOT_FOUND;
    }

    memcpy(p_var, p_s, size);

    released = nrf_atfifo_item_free(p_fifo, &context);
    if (NULL != p_released)
    {
        *p_released = released;
    }
    NRF_LOG_INST_DEBUG(p_fifo->p_log, "Element (0x%08X) copied out.", p_var);
    return NRF_SUCCESS;
}


void * nrf_atfifo_item_get(nrf_atfifo_t * const p_fifo, nrf_atfifo_item_get_t * p_context)
{
    if (nrf_atfifo_rspace_req(p_fifo, &(p_context->last_head)))
    {
        void * p_item = ((uint8_t*)(p_fifo->p_buf)) + p_context->last_head.pos.rd;
        NRF_LOG_INST_DEBUG(p_fifo->p_log, "Get element: 0x%08X", p_item);
        return p_item;
    }
    NRF_LOG_INST_WARNING(p_fifo->p_log, "Get failed - no item in the FIFO.");
    return NULL;
}


bool nrf_atfifo_item_free(nrf_atfifo_t * const p_fifo, nrf_atfifo_item_get_t * p_context)
{
    if ((p_context->last_head.pos.wr) == (p_context->last_head.pos.rd))
    {
        NRF_LOG_INST_DEBUG(p_fifo->p_log, "Free (uninterrupted)");
        nrf_atfifo_rspace_close(p_fifo);
        return true;
    }
    NRF_LOG_INST_DEBUG(p_fifo->p_log, "Free (interrupted)");
    return false;
}
