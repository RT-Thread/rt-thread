/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NRF_BLOCK_DEV_EMPTY)
#include "nrf_block_dev_empty.h"
#include <inttypes.h>

/**@file
 *
 * @ingroup nrf_block_dev
 * @{
 *
 * @brief This module implements block device API. It would behave like:
 *           - /dev/empty for write operations
 *           - /dev/zero for read operations
 */

#if NRF_BLOCK_DEV_EMPTY_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       NRF_BLOCK_DEV_EMPTY_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NRF_BLOCK_DEV_EMPTY_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR NRF_BLOCK_DEV_EMPTY_CONFIG_DEBUG_COLOR
#else
#define NRF_LOG_LEVEL       0
#endif
#include "nrf_log.h"


static ret_code_t block_dev_empty_init(nrf_block_dev_t const * p_blk_dev,
                                       nrf_block_dev_ev_handler ev_handler,
                                       void const * p_context)
{
    ASSERT(p_blk_dev);
    nrf_block_dev_empty_t const * p_empty_dev =
                                  CONTAINER_OF(p_blk_dev, nrf_block_dev_empty_t, block_dev);
    nrf_block_dev_empty_work_t * p_work = p_empty_dev->p_work;

    NRF_LOG_INST_DEBUG(p_empty_dev->p_log, "Init.");

    /* Calculate block device geometry.... */
    p_work->geometry.blk_size = p_empty_dev->empty_config.block_size;
    p_work->geometry.blk_count = p_empty_dev->empty_config.block_count;
    p_work->p_context = p_context;
    p_work->ev_handler = ev_handler;

    if (p_work->ev_handler)
    {
        /*Asynchronous operation (simulation)*/
        const nrf_block_dev_event_t ev = {
                NRF_BLOCK_DEV_EVT_INIT,
                NRF_BLOCK_DEV_RESULT_SUCCESS,
                NULL,
                p_work->p_context
        };

        p_work->ev_handler(p_blk_dev, &ev);
    }

    return NRF_SUCCESS;
}

static ret_code_t block_dev_empty_uninit(nrf_block_dev_t const * p_blk_dev)
{
    ASSERT(p_blk_dev);
    nrf_block_dev_empty_t const * p_empty_dev =
                                  CONTAINER_OF(p_blk_dev, nrf_block_dev_empty_t, block_dev);
    nrf_block_dev_empty_work_t * p_work = p_empty_dev->p_work;

    NRF_LOG_INST_DEBUG(p_empty_dev->p_log, "Uninit.");

    if (p_work->ev_handler)
    {
        /*Asynchronous operation (simulation)*/
        const nrf_block_dev_event_t ev = {
                NRF_BLOCK_DEV_EVT_UNINIT,
                NRF_BLOCK_DEV_RESULT_SUCCESS,
                NULL,
                p_work->p_context
        };

        p_work->ev_handler(p_blk_dev, &ev);
    }

    memset(p_work, 0, sizeof(nrf_block_dev_empty_work_t));
    return NRF_SUCCESS;
}

static ret_code_t block_dev_empty_read_req(nrf_block_dev_t const * p_blk_dev,
                                           nrf_block_req_t const * p_blk)
{
    ASSERT(p_blk_dev);
    ASSERT(p_blk);
    nrf_block_dev_empty_t const * p_empty_dev =
                                  CONTAINER_OF(p_blk_dev, nrf_block_dev_empty_t, block_dev);
    nrf_block_dev_empty_work_t * p_work = p_empty_dev->p_work;

    NRF_LOG_INST_DEBUG(
        p_empty_dev->p_log,
        "Read req from block %"PRIu32" size %"PRIu32"(x%"PRIu32") to %"PRIXPTR,
        p_blk->blk_id,
        p_blk->blk_count,
        p_blk_dev->p_ops->geometry(p_blk_dev)->blk_size,
        p_blk->p_buff);

    if ((p_blk->blk_id + p_blk->blk_count) > p_work->geometry.blk_count)
    {
        NRF_LOG_INST_ERROR(
            p_empty_dev->p_log,
            "Out of range read req block %"PRIu32" count %"PRIu32" while max is %"PRIu32,
            p_blk->blk_id,
            p_blk->blk_count,
            p_blk_dev->p_ops->geometry(p_blk_dev)->blk_count);
        return NRF_ERROR_INVALID_ADDR;
    }

    memset(p_blk->p_buff, 0, p_empty_dev->p_work->geometry.blk_size * p_blk->blk_count);
    if (p_work->ev_handler)
    {
        /*Asynchronous operation (simulation)*/
        const nrf_block_dev_event_t ev = {
                NRF_BLOCK_DEV_EVT_BLK_READ_DONE,
                NRF_BLOCK_DEV_RESULT_SUCCESS,
                p_blk,
                p_work->p_context
        };

        p_work->ev_handler(p_blk_dev, &ev);
    }

    return NRF_SUCCESS;
}

static ret_code_t block_dev_empty_write_req(nrf_block_dev_t const * p_blk_dev,
                                            nrf_block_req_t const * p_blk)
{
    ASSERT(p_blk_dev);
    ASSERT(p_blk);
    nrf_block_dev_empty_t const * p_empty_dev =
                                  CONTAINER_OF(p_blk_dev, nrf_block_dev_empty_t, block_dev);
    nrf_block_dev_empty_work_t * p_work = p_empty_dev->p_work;

    NRF_LOG_INST_DEBUG(
        p_empty_dev->p_log,
        "Write req to block %"PRIu32" size %"PRIu32"(x%"PRIu32") from %"PRIXPTR,
        p_blk->blk_id,
        p_blk->blk_count,
        p_blk_dev->p_ops->geometry(p_blk_dev)->blk_size,
        p_blk->p_buff);

    if ((p_blk->blk_id + p_blk->blk_count) > p_work->geometry.blk_count)
    {
        NRF_LOG_INST_ERROR(
            p_empty_dev->p_log,
            "Out of range write req block %"PRIu32" count %"PRIu32" while max is %"PRIu32,
            p_blk->blk_id,
            p_blk->blk_count,
            p_blk_dev->p_ops->geometry(p_blk_dev)->blk_count);

        return NRF_ERROR_INVALID_ADDR;
    }

    if (p_work->ev_handler)
    {
        /*Asynchronous operation (simulation)*/
        const nrf_block_dev_event_t ev = {
                NRF_BLOCK_DEV_EVT_BLK_WRITE_DONE,
                NRF_BLOCK_DEV_RESULT_SUCCESS,
                p_blk,
                p_work->p_context
        };

        p_work->ev_handler(p_blk_dev, &ev);
    }

    return NRF_SUCCESS;
}

static ret_code_t block_dev_empty_ioctl(nrf_block_dev_t const * p_blk_dev,
                                        nrf_block_dev_ioctl_req_t req, void * p_data)
{
    nrf_block_dev_empty_t const * p_empty_dev =
                                  CONTAINER_OF(p_blk_dev, nrf_block_dev_empty_t, block_dev);
    switch (req)
    {
        case NRF_BLOCK_DEV_IOCTL_REQ_CACHE_FLUSH:
        {
            bool * p_flushing = p_data;
            NRF_LOG_INST_DEBUG(p_empty_dev, "IOCtl: Cache flush");
            if (p_flushing)
            {
                *p_flushing = false;
            }
            return NRF_SUCCESS;
        }
        case NRF_BLOCK_DEV_IOCTL_REQ_INFO_STRINGS:
        {
            if (p_data == NULL)
            {
                return NRF_ERROR_INVALID_PARAM;
            }

            nrf_block_dev_info_strings_t const * * pp_strings = p_data;
            *pp_strings = &p_empty_dev->info_strings;
            return NRF_SUCCESS;
        }
        default:
            break;
    }

    return NRF_ERROR_NOT_SUPPORTED;
}

static nrf_block_dev_geometry_t const * block_dev_empty_geometry(nrf_block_dev_t const * p_blk_dev)
{
    ASSERT(p_blk_dev);
    nrf_block_dev_empty_t const * p_empty_dev =
                                  CONTAINER_OF(p_blk_dev, nrf_block_dev_empty_t, block_dev);
    nrf_block_dev_empty_work_t const * p_work = p_empty_dev->p_work;

    return &p_work->geometry;
}

const nrf_block_dev_ops_t nrf_block_device_empty_ops = {
        .init = block_dev_empty_init,
        .uninit = block_dev_empty_uninit,
        .read_req = block_dev_empty_read_req,
        .write_req = block_dev_empty_write_req,
        .ioctl = block_dev_empty_ioctl,
        .geometry = block_dev_empty_geometry,
};

/** @} */
#endif // NRF_MODULE_ENABLED(NRF_BLOCK_DEV_EMPTY)
