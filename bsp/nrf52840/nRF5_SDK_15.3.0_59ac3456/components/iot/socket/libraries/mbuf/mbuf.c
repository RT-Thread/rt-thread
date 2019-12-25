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
#include "sdk_config.h"
#include "mem_manager.h"
#include "mbuf.h"
#include "nrf_fifo.h"
#include "socket_common.h"

uint32_t mbuf_init(mbuf_t        * p_mbuf,
                   mbuf_read_fn    read_fn,
                   mbuf_buf_len_fn buf_len_fn,
                   mbuf_free_fn    free_fn,
                   uint32_t        nmemb)
{
    p_mbuf->p_current = NULL;
    p_mbuf->read_pos  = 0;
    p_mbuf->read      = read_fn;
    p_mbuf->buf_len   = buf_len_fn;
    p_mbuf->free      = free_fn;
    return nrf_fifo_init(&p_mbuf->fifo, nmemb, socket_wait, free_fn);
}

void mbuf_deinit(mbuf_t * p_mbuf)
{
    if (p_mbuf->p_current != NULL)
    {
        p_mbuf->free(p_mbuf->p_current);
        p_mbuf->p_current = NULL;
    }

    p_mbuf->read_pos = 0;
    p_mbuf->read     = NULL;
    p_mbuf->buf_len  = NULL;
    p_mbuf->free     = NULL;
    nrf_fifo_deinit(&p_mbuf->fifo);
}

static bool mbuf_empty_current(mbuf_t * p_mbuf)
{
    return (p_mbuf->buf_len(p_mbuf->p_current) == p_mbuf->read_pos);
}

bool mbuf_empty(mbuf_t * p_mbuf)
{
    return ((p_mbuf->p_current == NULL || mbuf_empty_current(p_mbuf)) &&
            nrf_fifo_empty(&p_mbuf->fifo));
}

uint32_t mbuf_write(mbuf_t * p_mbuf, void * p_ctx)
{
    return nrf_fifo_enq(&p_mbuf->fifo, p_ctx, false);
}

static void mbuf_load(mbuf_t * p_mbuf)
{
    if (p_mbuf->p_current == NULL)
    {
        (void)nrf_fifo_deq(&p_mbuf->fifo, &p_mbuf->p_current, false);
    }
}

uint32_t mbuf_read(mbuf_t * p_mbuf, void * p_buf, uint32_t buf_size)
{
    uint32_t nbytes = 0;
    while (nbytes < buf_size && mbuf_empty(p_mbuf) == false)
    {
        mbuf_load(p_mbuf);
        void * p_current = p_mbuf->p_current;
        const uint32_t copy_len = p_mbuf->read(p_current,
                                               p_mbuf->read_pos,
                                               ((uint8_t *)p_buf) + nbytes,
                                               buf_size - nbytes);
        p_mbuf->read_pos += copy_len;
        nbytes += copy_len;
        if (mbuf_empty_current(p_mbuf) == true)
        {
            p_mbuf->free(p_mbuf->p_current);
            p_mbuf->p_current = NULL;
            p_mbuf->read_pos = 0;
        }
    }
    return nbytes;
}
