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
#include "nrf_block_dev_sdc.h"

/**@file
 *
 * @ingroup nrf_block_dev_sdc
 * @{
 *
 * @brief This module implements block device API. It should be used as a reference block device.
 */


static volatile sdc_result_t m_last_result;


/**
 * @brief Active SDC block device handle. Only one instance.
 * */
static nrf_block_dev_sdc_t const * m_active_sdc_dev;



static void wait_func(void)
{
}

static void sdc_wait()
{
    while (app_sdc_busy_check())
    {
        wait_func();
    }
}


static void sdc_handler(sdc_evt_t const * p_event)
{
    m_last_result = p_event->result;
    nrf_block_dev_sdc_t const * p_sdc_dev = m_active_sdc_dev;
    nrf_block_dev_sdc_work_t *  p_work = p_sdc_dev->p_work;

    switch (p_event->type)
    {
        case SDC_EVT_INIT:
            {
                p_work->geometry.blk_count = app_sdc_info_get()->num_blocks;
                p_work->geometry.blk_size  = SDC_SECTOR_SIZE;
                if (m_active_sdc_dev->p_work->ev_handler)
                {
                    const nrf_block_dev_event_t ev = {
                            NRF_BLOCK_DEV_EVT_INIT,
                            ((p_event->result == SDC_SUCCESS) ? \
                                    NRF_BLOCK_DEV_RESULT_SUCCESS : NRF_BLOCK_DEV_RESULT_IO_ERROR),
                            NULL,
                            p_work->p_context
                    };
                    p_work->ev_handler(&p_sdc_dev->block_dev, &ev);
                }
            }
            break;

        case SDC_EVT_READ:
            if (m_active_sdc_dev->p_work->ev_handler)
            {
                const nrf_block_dev_event_t ev = {
                        NRF_BLOCK_DEV_EVT_BLK_READ_DONE,
                        ((p_event->result == SDC_SUCCESS) ? \
                                NRF_BLOCK_DEV_RESULT_SUCCESS : NRF_BLOCK_DEV_RESULT_IO_ERROR),
                        &p_work->req,
                        p_work->p_context
                };
                p_work->ev_handler(&p_sdc_dev->block_dev, &ev);
            }
            break;

        case SDC_EVT_WRITE:
            if (m_active_sdc_dev->p_work->ev_handler)
            {
                const nrf_block_dev_event_t ev = {
                        NRF_BLOCK_DEV_EVT_BLK_WRITE_DONE,
                        ((p_event->result == SDC_SUCCESS) ? \
                                NRF_BLOCK_DEV_RESULT_SUCCESS : NRF_BLOCK_DEV_RESULT_IO_ERROR),
                        &p_work->req,
                        p_work->p_context
                };
                p_work->ev_handler(&p_sdc_dev->block_dev, &ev);
            }
            break;

        default:
            APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
            return;
    }
}


static ret_code_t block_dev_sdc_init(nrf_block_dev_t const * p_blk_dev,
                                     nrf_block_dev_ev_handler ev_handler,
                                     void const * p_context)
{
    ASSERT(p_blk_dev);
    nrf_block_dev_sdc_t const * p_sdc_dev =
                                CONTAINER_OF(p_blk_dev, nrf_block_dev_sdc_t, block_dev);
    nrf_block_dev_sdc_work_t *  p_work = p_sdc_dev->p_work;

    if (p_sdc_dev->sdc_bdev_config.block_size != SDC_SECTOR_SIZE)
    {
        /* Unsupported block size. */
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if (m_active_sdc_dev)
    {
        /* SDC instance is busy. */
        return NRF_ERROR_BUSY;
    }

    p_work->p_context  = p_context;
    p_work->ev_handler = ev_handler;
    m_active_sdc_dev   = p_sdc_dev;

    ret_code_t err_code = NRF_SUCCESS;

    err_code = app_sdc_init(&p_sdc_dev->sdc_bdev_config.sdc_config, sdc_handler);
    if (err_code == NRF_SUCCESS)
    {
        if (!ev_handler)
        {
            /* Synchronous mode - wait for the card. */
            sdc_wait();
            err_code = ((m_last_result == SDC_SUCCESS) ? NRF_SUCCESS : NRF_ERROR_TIMEOUT);
        }
    }

    if (err_code != NRF_SUCCESS)
    {
        m_active_sdc_dev = NULL;

        if (ev_handler)
        {
            /* Call the user handler with an error status. */
            const nrf_block_dev_event_t ev = {
                    NRF_BLOCK_DEV_EVT_INIT,
                    NRF_BLOCK_DEV_RESULT_IO_ERROR,
                    NULL,
                    p_work->p_context
            };
            p_work->ev_handler(p_blk_dev, &ev);
        }
    }

    return err_code;
}

static ret_code_t block_dev_sdc_uninit(nrf_block_dev_t const * p_blk_dev)
{
    ASSERT(p_blk_dev);
    nrf_block_dev_sdc_t const * p_sdc_dev =
                                CONTAINER_OF(p_blk_dev, nrf_block_dev_sdc_t, block_dev);
    nrf_block_dev_sdc_work_t *  p_work = p_sdc_dev->p_work;

    if (m_active_sdc_dev != p_sdc_dev)
    {
        /* SDC instance is busy. */
        return NRF_ERROR_BUSY;
    }

    if (app_sdc_busy_check())
    {
        /* Previous asynchronous operation in progress. */
        return NRF_ERROR_BUSY;
    }

    ret_code_t err_code = app_sdc_uninit();
    if (err_code == NRF_SUCCESS)
    {
        /* Free the instance on success. */
        m_active_sdc_dev = NULL;
    }

    if (p_work->ev_handler)
    {
        /* SDC uninitialization is a synchronous operation. Call event handler. */
        const nrf_block_dev_event_t ev = {
                NRF_BLOCK_DEV_EVT_UNINIT,
                ((err_code == NRF_SUCCESS) ? \
                              NRF_BLOCK_DEV_RESULT_SUCCESS : NRF_BLOCK_DEV_RESULT_IO_ERROR),
                NULL,
                p_work->p_context
        };

        p_work->ev_handler(p_blk_dev, &ev);
    }

    return err_code;
}

static ret_code_t block_dev_sdc_read_req(nrf_block_dev_t const * p_blk_dev,
                                         nrf_block_req_t const * p_blk)
{
    ASSERT(p_blk_dev);
    ASSERT(p_blk);
    nrf_block_dev_sdc_t const * p_sdc_dev =
                                CONTAINER_OF(p_blk_dev, nrf_block_dev_sdc_t, block_dev);
    nrf_block_dev_sdc_work_t *  p_work = p_sdc_dev->p_work;

    ret_code_t err_code = NRF_SUCCESS;

    if (m_active_sdc_dev != p_sdc_dev)
    {
        /* SDC instance is busy. */
        return NRF_ERROR_BUSY;
    }

    if (app_sdc_busy_check())
    {
        /* Previous asynchronous operation in progress. */
        return NRF_ERROR_BUSY;
    }

    p_work->req = *p_blk;
    err_code = app_sdc_block_read(p_blk->p_buff, p_blk->blk_id, p_blk->blk_count);
    if (err_code == NRF_SUCCESS)
    {
        if (!p_work->ev_handler)
        {
            /* Synchronous mode - wait for the card. */
            sdc_wait();
            err_code = ((m_last_result == SDC_SUCCESS) ? NRF_SUCCESS : NRF_ERROR_TIMEOUT);
        }
    }

    if ((p_work->ev_handler) && (err_code != NRF_SUCCESS))
    {
        /* Call the user handler with an error status. */
        const nrf_block_dev_event_t ev = {
                NRF_BLOCK_DEV_EVT_BLK_READ_DONE,
                NRF_BLOCK_DEV_RESULT_IO_ERROR,
                &p_work->req,
                p_work->p_context
        };
        p_work->ev_handler(p_blk_dev, &ev);
    }

    return err_code;
}

static ret_code_t block_dev_sdc_write_req(nrf_block_dev_t const * p_blk_dev,
                                         nrf_block_req_t const * p_blk)
{
    ASSERT(p_blk_dev);
    ASSERT(p_blk);
    nrf_block_dev_sdc_t const * p_sdc_dev =
                                CONTAINER_OF(p_blk_dev, nrf_block_dev_sdc_t, block_dev);
    nrf_block_dev_sdc_work_t *  p_work = p_sdc_dev->p_work;

    ret_code_t err_code = NRF_SUCCESS;

    if (m_active_sdc_dev != p_sdc_dev)
    {
        /* SDC instance is busy. */
        return NRF_ERROR_BUSY;
    }

    if (app_sdc_busy_check())
    {
        /* Previous asynchronous operation in progress. */
        return NRF_ERROR_BUSY;
    }

    p_work->req = *p_blk;
    err_code = app_sdc_block_write(p_blk->p_buff, p_blk->blk_id, p_blk->blk_count);
    if (err_code == NRF_SUCCESS)
    {
        if (!p_work->ev_handler)
        {
            /* Synchronous mode - wait for the card. */
            sdc_wait();
            err_code = ((m_last_result == SDC_SUCCESS) ? NRF_SUCCESS : NRF_ERROR_TIMEOUT);
        }
    }

    if ((p_work->ev_handler) && (err_code != NRF_SUCCESS))
    {
        /* Call the user handler with an error status. */
        const nrf_block_dev_event_t ev = {
                NRF_BLOCK_DEV_EVT_BLK_READ_DONE,
                NRF_BLOCK_DEV_RESULT_IO_ERROR,
                &p_work->req,
                p_work->p_context
        };
        p_work->ev_handler(p_blk_dev, &ev);
    }

    return err_code;
}

static ret_code_t block_dev_sdc_ioctl(nrf_block_dev_t const * p_blk_dev,
                                      nrf_block_dev_ioctl_req_t req,
                                      void * p_data)
{
    nrf_block_dev_sdc_t const * p_sdc_dev =
                                CONTAINER_OF(p_blk_dev, nrf_block_dev_sdc_t, block_dev);
    switch (req)
    {
        case NRF_BLOCK_DEV_IOCTL_REQ_CACHE_FLUSH:
        {
            bool * p_flushing = p_data;
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
            *pp_strings = &p_sdc_dev->info_strings;
            return NRF_SUCCESS;
        }
        default:
            break;
    }


    return NRF_ERROR_NOT_SUPPORTED;
}

static nrf_block_dev_geometry_t const * block_dev_sdc_geometry(nrf_block_dev_t const * p_blk_dev)
{
    ASSERT(p_blk_dev);
    nrf_block_dev_sdc_t const * p_sdc_dev =
                                CONTAINER_OF(p_blk_dev, nrf_block_dev_sdc_t, block_dev);
    nrf_block_dev_sdc_work_t const * p_work = p_sdc_dev->p_work;

    return &p_work->geometry;
}

const nrf_block_dev_ops_t nrf_block_device_sdc_ops = {
        .init = block_dev_sdc_init,
        .uninit = block_dev_sdc_uninit,
        .read_req = block_dev_sdc_read_req,
        .write_req = block_dev_sdc_write_req,
        .ioctl = block_dev_sdc_ioctl,
        .geometry = block_dev_sdc_geometry,
};


/** @} */
