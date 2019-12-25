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
#include "iot_defines.h"
#include "iot_errors.h"
#include "nrf_fifo.h"
#include "mem_manager.h"
#include "nrf.h"

static __INLINE uint32_t fifo_inc(nrf_fifo_t * p_fifo, uint32_t pos)
{
    return (pos + 1) % p_fifo->nmemb;
}

static __INLINE bool fifo_full(nrf_fifo_t * p_fifo)
{
    return fifo_inc(p_fifo, p_fifo->write_pos) == p_fifo->read_pos;
}

static __INLINE bool fifo_empty(nrf_fifo_t * p_fifo)
{
  return p_fifo->read_pos == p_fifo->write_pos;
}

static __INLINE void fifo_enq(nrf_fifo_t * p_fifo, void * p_ctx)
{
    p_fifo->pp_elements[p_fifo->write_pos] = p_ctx;
    __DSB();
    p_fifo->write_pos = fifo_inc(p_fifo, p_fifo->write_pos);
}


static __INLINE void fifo_deq(nrf_fifo_t * p_fifo, void ** pp_ctx)
{
    *pp_ctx = p_fifo->pp_elements[p_fifo->read_pos];
    __DSB();
    p_fifo->read_pos = fifo_inc(p_fifo, p_fifo->read_pos);
}

uint32_t nrf_fifo_init(nrf_fifo_t * p_fifo, uint32_t nmemb, fifo_wait_fn wait_fn, fifo_flush_fn flush_fn)
{
    uint32_t err_code = NRF_SUCCESS;
    uint32_t nmemb_actual = nmemb + 1; // Required to allow detection of empty and full state
    p_fifo->pp_elements = nrf_malloc(nmemb_actual * sizeof(void *));

    if (p_fifo->pp_elements == NULL)
    {
        err_code = NRF_ERROR_NO_MEM;
    }
    else
    {
        p_fifo->nmemb       = nmemb_actual;
        p_fifo->wait        = wait_fn;
        p_fifo->flush       = flush_fn;
        p_fifo->read_pos    = 0;
        p_fifo->write_pos   = 0;
    }
    return err_code;
}

void nrf_fifo_deinit(nrf_fifo_t * p_fifo)
{
    if (p_fifo->flush != NULL)
    {
        void * p_data;
        uint32_t err_code = nrf_fifo_deq(p_fifo, &p_data, false);
        while (err_code == NRF_SUCCESS)
        {
            p_fifo->flush(p_data);
            err_code = nrf_fifo_deq(p_fifo, &p_data, false);
        }
    }
    nrf_free(p_fifo->pp_elements);
    p_fifo->nmemb       = 0;
    p_fifo->read_pos    = 0;
    p_fifo->write_pos   = 0;
    p_fifo->wait        = NULL;
    p_fifo->flush       = NULL;
}

uint32_t nrf_fifo_enq(nrf_fifo_t * p_fifo, void * p_ctx, bool wait)
{
    uint32_t err_code = NRF_SUCCESS;

    if (fifo_full(p_fifo) == true)
    {
        if (wait == false || p_fifo->wait == NULL)
        {
            err_code = SOCKET_WOULD_BLOCK;
        }
        else
        {
            while (fifo_full(p_fifo) == true && err_code == NRF_SUCCESS)
            {
                err_code = p_fifo->wait();
            }
        }
    }
    else
    {
        fifo_enq(p_fifo, p_ctx);
    }
    return err_code;
}

uint32_t nrf_fifo_deq(nrf_fifo_t * p_fifo, void ** pp_ctx, bool wait)
{
    uint32_t err_code = NRF_SUCCESS;

    if (fifo_empty(p_fifo) == true)
    {
        if (wait == false || p_fifo->wait == NULL)
        {
            err_code = SOCKET_WOULD_BLOCK;
        }
        else
        {
            while (fifo_empty(p_fifo) == true && err_code == NRF_SUCCESS)
            {
                err_code = p_fifo->wait();
            }
        }
    }

    if (err_code == NRF_SUCCESS)
    {
        fifo_deq(p_fifo, pp_ctx);
    }
    return err_code;
}

bool nrf_fifo_empty(nrf_fifo_t * p_fifo)
{
    return fifo_empty(p_fifo);
}

bool nrf_fifo_full(nrf_fifo_t * p_fifo)
{
    return fifo_full(p_fifo);
}
