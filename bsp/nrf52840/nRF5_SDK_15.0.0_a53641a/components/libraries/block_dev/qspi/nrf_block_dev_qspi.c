/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#include "nrf_serial_flash_params.h"
#include "nrf_block_dev_qspi.h"

/**@file
 *
 * @ingroup nrf_block_dev_qspi
 * @{
 *
 * @brief This module implements block device API. It should be used as a reference block device.
 */

#define QSPI_STD_CMD_WRSR    0x01   /**< Write status register command*/
#define QSPI_STD_CMD_RSTEN   0x66   /**< Reset enable command*/
#define QSPI_STD_CMD_RST     0x99   /**< Reset command*/
#define QSPI_STD_CMD_READ_ID 0x9F   /**< Read ID command*/

#define BD_PAGE_PROGRAM_SIZE 256    /**< Page program size (minimum block size)*/

#define BD_ERASE_UNIT_INVALID_ID   0xFFFFFFFF /**< Invalid erase unit number*/
#define BD_ERASE_UNIT_ERASE_VAL    0xFFFFFFFF /**< Erased memory value*/

/**
 * @brief Block to erase unit translation
 *
 * @param blk_id    Block index
 * @param blk_size  Block size
 * */
#define BD_BLOCK_TO_ERASEUNIT(blk_id, blk_size)   \
    ((blk_id) * (blk_size)) / (NRF_BLOCK_DEV_QSPI_ERASE_UNIT_SIZE)

/**
 * @brief Blocks per erase unit
 *
 * @param blk_size  Block size
 * */
#define BD_BLOCKS_PER_ERASEUNIT(blk_size)         \
    (NRF_BLOCK_DEV_QSPI_ERASE_UNIT_SIZE / (blk_size))


static ret_code_t block_dev_qspi_eunit_write(nrf_block_dev_qspi_t const * p_qspi_dev,
                                             nrf_block_req_t * p_blk_left);


static void block_dev_qspi_read_from_eunit(nrf_block_dev_qspi_t const * p_qspi_dev)
{
    nrf_block_dev_qspi_work_t const * p_work = p_qspi_dev->p_work;

    /*In write-back mode data that we read might not be the same as in erase unit buffer*/
    uint32_t eunit_start = BD_BLOCK_TO_ERASEUNIT(p_work->req.blk_id,
                                                 p_work->geometry.blk_size);

    uint32_t eunit_end = BD_BLOCK_TO_ERASEUNIT(p_work->req.blk_id + p_work->req.blk_count,
                                               p_work->geometry.blk_size);

    if ((eunit_start > p_work->erase_unit_idx) || (eunit_end < p_work->erase_unit_idx))
    {
        /*Do nothing. Read request doesn't hit current cached erase unit*/
        return;
    }

    /*Case 1: Copy data from start erase unit*/
    if (eunit_start == p_work->erase_unit_idx)
    {
         size_t blk = p_work->req.blk_id %
                      BD_BLOCKS_PER_ERASEUNIT(p_work->geometry.blk_size);
         size_t cnt = BD_BLOCKS_PER_ERASEUNIT(p_work->geometry.blk_size) - blk;
         size_t off = p_work->geometry.blk_size * blk;

         if (cnt > p_work->req.blk_count)
         {
             cnt = p_work->req.blk_count;
         }

         memcpy(p_work->req.p_buff,
                p_work->p_erase_unit_buff + off,
                cnt * p_work->geometry.blk_size);

         return;
    }

    /*Case 2: Copy data from end erase unit*/
    if (eunit_end == p_work->erase_unit_idx)
    {
         size_t cnt = (p_work->req.blk_id + p_work->req.blk_count) %
                       BD_BLOCKS_PER_ERASEUNIT(p_work->geometry.blk_size);
         size_t off = (p_work->erase_unit_idx * BD_BLOCKS_PER_ERASEUNIT(p_work->geometry.blk_size) -
                       p_work->req.blk_id) * p_work->geometry.blk_size;

         if (cnt > p_work->req.blk_count)
         {
             cnt = p_work->req.blk_count;
         }

         memcpy((uint8_t *)p_work->req.p_buff + off,
                p_work->p_erase_unit_buff,
                cnt * p_work->geometry.blk_size);

         return;
    }

    /*Case 3: Copy data from  eunit_start < p_work->erase_unit_idx < eunit_end*/
    size_t off = (p_work->erase_unit_idx * BD_BLOCKS_PER_ERASEUNIT(p_work->geometry.blk_size) -
                  p_work->req.blk_id) * p_work->geometry.blk_size;

    memcpy((uint8_t *)p_work->req.p_buff + off,
           p_work->p_erase_unit_buff,
           NRF_BLOCK_DEV_QSPI_ERASE_UNIT_SIZE);
}

/**
 * @brief Active QSPI block device handle. Only one instance.
 * */
static nrf_block_dev_qspi_t const * m_active_qspi_dev;

static void qspi_handler(nrf_drv_qspi_evt_t event, void * p_context)
{
    if (m_active_qspi_dev != p_context)
    {
        return;
    }

    nrf_block_dev_qspi_t const * p_qspi_dev = p_context;
    nrf_block_dev_qspi_work_t *  p_work = p_qspi_dev->p_work;
    nrf_block_req_t * p_blk_left = &p_work->left_req;

    switch (p_work->state)
    {
        case NRF_BLOCK_DEV_QSPI_STATE_READ_EXEC:
        {
            if (p_work->writeback_mode)
            {
                block_dev_qspi_read_from_eunit(p_qspi_dev);
            }

            p_work->state = NRF_BLOCK_DEV_QSPI_STATE_IDLE;
            if (p_work->ev_handler)
            {
                const nrf_block_dev_event_t ev = {
                        NRF_BLOCK_DEV_EVT_BLK_READ_DONE,
                        NRF_BLOCK_DEV_RESULT_SUCCESS,
                        &p_work->req,
                        p_work->p_context
                };

                p_work->ev_handler(&p_qspi_dev->block_dev, &ev);
            }

            break;
        }
        case NRF_BLOCK_DEV_QSPI_STATE_EUNIT_LOAD:
        {
            ret_code_t ret;
            uint32_t erase_unit = BD_BLOCK_TO_ERASEUNIT(p_blk_left->blk_id,
                                                        p_work->geometry.blk_size);
            UNUSED_VARIABLE(erase_unit);
            ASSERT(erase_unit == p_work->erase_unit_idx);

            /* Check if block is in erase unit buffer*/
            ret = block_dev_qspi_eunit_write(p_qspi_dev, p_blk_left);
            ASSERT(ret == NRF_SUCCESS);
            UNUSED_VARIABLE(ret);
            break;
        }
        case NRF_BLOCK_DEV_QSPI_STATE_WRITE_ERASE:
        case NRF_BLOCK_DEV_QSPI_STATE_WRITE_EXEC:
        {
            /*Clear last programmed block*/
            uint32_t block_to_program = __CLZ(__RBIT(p_work->erase_unit_dirty_blocks));

            if (p_work->state == NRF_BLOCK_DEV_QSPI_STATE_WRITE_EXEC)
            {
                p_work->erase_unit_dirty_blocks ^= 1u << block_to_program;
            }

            if (p_work->erase_unit_dirty_blocks == 0)
            {
                if (p_work->left_req.blk_count)
                {
                    /*Load next erase unit*/
                    ret_code_t ret;
                    uint32_t eunit = BD_BLOCK_TO_ERASEUNIT(p_blk_left->blk_id,
                                                           p_work->geometry.blk_size);

                    p_work->erase_unit_idx = eunit;
                    p_work->state = NRF_BLOCK_DEV_QSPI_STATE_EUNIT_LOAD;

                    ret = nrf_drv_qspi_read(p_work->p_erase_unit_buff,
                                            NRF_BLOCK_DEV_QSPI_ERASE_UNIT_SIZE,
                                            p_work->erase_unit_idx *
                                            NRF_BLOCK_DEV_QSPI_ERASE_UNIT_SIZE);
                    UNUSED_VARIABLE(ret);

                    break;
                }

                /*All blocks are programmed. Call event handler if required.*/
                p_work->state = NRF_BLOCK_DEV_QSPI_STATE_IDLE;
                if (p_work->ev_handler && !p_work->cache_flushing)
                {
                    const nrf_block_dev_event_t ev = {
                            NRF_BLOCK_DEV_EVT_BLK_WRITE_DONE,
                            NRF_BLOCK_DEV_RESULT_SUCCESS,
                            &p_work->req,
                            p_work->p_context
                    };

                    p_work->ev_handler(&p_qspi_dev->block_dev, &ev);
                }

                p_work->cache_flushing = false;
                break;
            }

            /*Get next block to program from program mask*/
            block_to_program = __CLZ(__RBIT(p_work->erase_unit_dirty_blocks));
            uint32_t dst_address = (p_work->erase_unit_idx * NRF_BLOCK_DEV_QSPI_ERASE_UNIT_SIZE) +
                                   (block_to_program * p_work->geometry.blk_size);

            const void * p_src_address = p_work->p_erase_unit_buff +
                                         block_to_program * p_work->geometry.blk_size;

            p_work->state = NRF_BLOCK_DEV_QSPI_STATE_WRITE_EXEC;
            ret_code_t ret = nrf_drv_qspi_write(p_src_address,
                                                p_work->geometry.blk_size,
                                                dst_address);
            UNUSED_VARIABLE(ret);
            break;
        }
        default:
            ASSERT(0);
            break;
    }
}

static void wait_for_idle(nrf_block_dev_qspi_t const * p_qspi_dev)
{
    nrf_block_dev_qspi_work_t * p_work = p_qspi_dev->p_work;
    while (p_work->state != NRF_BLOCK_DEV_QSPI_STATE_IDLE)
    {
        __WFI();
    }
}

static ret_code_t block_dev_qspi_init(nrf_block_dev_t const * p_blk_dev,
                                      nrf_block_dev_ev_handler ev_handler,
                                      void const * p_context)
{
    ASSERT(p_blk_dev);
    nrf_block_dev_qspi_t const *  p_qspi_dev =
                                  CONTAINER_OF(p_blk_dev, nrf_block_dev_qspi_t, block_dev);
    nrf_block_dev_qspi_work_t *   p_work = p_qspi_dev->p_work;
    nrf_drv_qspi_config_t const * p_qspi_cfg = &p_qspi_dev->qspi_bdev_config.qspi_config;

    ret_code_t ret = NRF_SUCCESS;

    if (p_qspi_dev->qspi_bdev_config.block_size % BD_PAGE_PROGRAM_SIZE)
    {
        /*Unsupported block size*/
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if (NRF_BLOCK_DEV_QSPI_ERASE_UNIT_SIZE % p_qspi_dev->qspi_bdev_config.block_size)
    {
        /*Unsupported block size*/
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if (m_active_qspi_dev)
    {
        /* QSPI instance is BUSY*/
        return NRF_ERROR_BUSY;
    }

    ret = nrf_drv_qspi_init(p_qspi_cfg, qspi_handler, (void *)p_blk_dev);
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    nrf_qspi_cinstr_conf_t cinstr_cfg = {
        .opcode    = QSPI_STD_CMD_RSTEN,
        .length    = NRF_QSPI_CINSTR_LEN_1B,
        .io2_level = true,
        .io3_level = true,
        .wipwait   = true,
        .wren      = true
    };

    /* Send reset enable */
    ret = nrf_drv_qspi_cinstr_xfer(&cinstr_cfg, NULL, NULL);
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    /* Send reset command */
    cinstr_cfg.opcode = QSPI_STD_CMD_RST;
    ret = nrf_drv_qspi_cinstr_xfer(&cinstr_cfg, NULL, NULL);
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    /* Get 3 byte identification value */
    uint8_t rdid_buf[3] = {0, 0, 0};
    cinstr_cfg.opcode = QSPI_STD_CMD_READ_ID;
    cinstr_cfg.length = NRF_QSPI_CINSTR_LEN_4B;
    ret = nrf_drv_qspi_cinstr_xfer(&cinstr_cfg, NULL, rdid_buf);
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    nrf_serial_flash_params_t const * serial_flash_id = nrf_serial_flash_params_get(rdid_buf);

    if (!serial_flash_id)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if (serial_flash_id->erase_size != NRF_BLOCK_DEV_QSPI_ERASE_UNIT_SIZE)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    /* Calculate block device geometry.... */
    uint32_t blk_size = p_qspi_dev->qspi_bdev_config.block_size;
    uint32_t blk_count = serial_flash_id->size / p_qspi_dev->qspi_bdev_config.block_size;

    if (!blk_count || (blk_count % BD_BLOCKS_PER_ERASEUNIT(blk_size)))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    p_work->geometry.blk_size = blk_size;
    p_work->geometry.blk_count = blk_count;
    p_work->p_context = p_context;
    p_work->ev_handler = ev_handler;

    p_work->state = NRF_BLOCK_DEV_QSPI_STATE_IDLE;
    p_work->erase_unit_idx = BD_ERASE_UNIT_INVALID_ID;
    p_work->writeback_mode =  (p_qspi_dev->qspi_bdev_config.flags &
                               NRF_BLOCK_DEV_QSPI_FLAG_CACHE_WRITEBACK) != 0;
    m_active_qspi_dev = p_qspi_dev;

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

static ret_code_t block_dev_qspi_uninit(nrf_block_dev_t const * p_blk_dev)
{
    ASSERT(p_blk_dev);
    nrf_block_dev_qspi_t const * p_qspi_dev =
                                 CONTAINER_OF(p_blk_dev, nrf_block_dev_qspi_t, block_dev);
    nrf_block_dev_qspi_work_t * p_work = p_qspi_dev->p_work;

    if (m_active_qspi_dev != p_qspi_dev)
    {
        /* QSPI instance is BUSY*/
        return NRF_ERROR_BUSY;
    }

    if (p_work->state != NRF_BLOCK_DEV_QSPI_STATE_IDLE)
    {
        /* Previous asynchronous operation in progress*/
        return NRF_ERROR_BUSY;
    }

    if (p_work->ev_handler)
    {
        /*Asynchronous operation*/
        const nrf_block_dev_event_t ev = {
                NRF_BLOCK_DEV_EVT_UNINIT,
                NRF_BLOCK_DEV_RESULT_SUCCESS,
                NULL,
                p_work->p_context
        };

        p_work->ev_handler(p_blk_dev, &ev);
    }

    p_work->state = NRF_BLOCK_DEV_QSPI_STATE_DISABLED;
    nrf_drv_qspi_uninit();

    memset(p_work, 0, sizeof(nrf_block_dev_qspi_work_t));
    m_active_qspi_dev = NULL;
    return NRF_SUCCESS;
}

static ret_code_t block_dev_qspi_read_req(nrf_block_dev_t const * p_blk_dev,
                                          nrf_block_req_t const * p_blk)
{
    ASSERT(p_blk_dev);
    ASSERT(p_blk);
    nrf_block_dev_qspi_t const * p_qspi_dev =
                                 CONTAINER_OF(p_blk_dev, nrf_block_dev_qspi_t, block_dev);
    nrf_block_dev_qspi_work_t *  p_work = p_qspi_dev->p_work;

    ret_code_t ret = NRF_SUCCESS;

    if (m_active_qspi_dev != p_qspi_dev)
    {
        /* QSPI instance is BUSY*/
        return NRF_ERROR_BUSY;
    }

    if (p_work->state != NRF_BLOCK_DEV_QSPI_STATE_IDLE)
    {
        /* Previous asynchronous operation in progress*/
        return NRF_ERROR_BUSY;
    }

    p_work->left_req = *p_blk;
    p_work->req = *p_blk;
    nrf_block_req_t * p_blk_left = &p_work->left_req;

    p_work->state = NRF_BLOCK_DEV_QSPI_STATE_READ_EXEC;
    ret = nrf_drv_qspi_read(p_blk_left->p_buff,
                            p_blk_left->blk_count * p_work->geometry.blk_size,
                            p_blk_left->blk_id * p_work->geometry.blk_size);

    if (ret != NRF_SUCCESS)
    {
        p_work->state = NRF_BLOCK_DEV_QSPI_STATE_IDLE;
        return ret;
    }

    p_blk_left->p_buff = NULL;
    p_blk_left->blk_count = 0;

    if (!p_work->ev_handler && (p_work->state != NRF_BLOCK_DEV_QSPI_STATE_IDLE))
    {
        /*Synchronous operation*/
        wait_for_idle(p_qspi_dev);
    }

    return ret;
}

static bool block_dev_qspi_update_eunit(nrf_block_dev_qspi_t const * p_qspi_dev,
                                        size_t off,
                                        const void * p_src,
                                        size_t len)
{
    ASSERT((len % sizeof(uint32_t)) == 0)
    nrf_block_dev_qspi_work_t *  p_work = p_qspi_dev->p_work;

    uint32_t *       p_dst32 = (uint32_t *)(p_work->p_erase_unit_buff + off);
    const uint32_t * p_src32 = p_src;

    bool erase_required = false;
    len /= sizeof(uint32_t);

    /*Do normal copying until erase unit is not required*/
    do
    {
        if (*p_dst32 != *p_src32)
        {
            if (*p_dst32 != BD_ERASE_UNIT_ERASE_VAL)
            {
                erase_required = true;
            }

            /*Mark block as dirty*/
            p_work->erase_unit_dirty_blocks |= 1u << (off / p_work->geometry.blk_size);
        }

        *p_dst32++ = *p_src32++;
        off += sizeof(uint32_t);
    } while (--len);

    return erase_required;
}

static ret_code_t block_dev_qspi_write_start(nrf_block_dev_qspi_t const * p_qspi_dev)
{
    nrf_block_dev_qspi_work_t *  p_work = p_qspi_dev->p_work;

    if (!p_work->erase_required)
    {
        /*Get first block to program from program mask*/
        uint32_t block_to_program = __CLZ(__RBIT(p_work->erase_unit_dirty_blocks));
        uint32_t dst_address = (p_work->erase_unit_idx * NRF_BLOCK_DEV_QSPI_ERASE_UNIT_SIZE) +
                               (block_to_program * p_work->geometry.blk_size);

        const void * p_src_address = p_work->p_erase_unit_buff +
                                     block_to_program * p_work->geometry.blk_size;

        p_work->state = NRF_BLOCK_DEV_QSPI_STATE_WRITE_EXEC;
        return nrf_drv_qspi_write(p_src_address,
                                  p_work->geometry.blk_size,
                                  dst_address);
    }

    /*Erase is required*/
    uint32_t address = (p_work->erase_unit_idx * NRF_BLOCK_DEV_QSPI_ERASE_UNIT_SIZE);
    p_work->state = NRF_BLOCK_DEV_QSPI_STATE_WRITE_ERASE;
    p_work->erase_required = false;

    return nrf_drv_qspi_erase(NRF_QSPI_ERASE_LEN_4KB, address);
}

static ret_code_t block_dev_qspi_eunit_write(nrf_block_dev_qspi_t const * p_qspi_dev,
                                             nrf_block_req_t * p_blk_left)
{
    nrf_block_dev_qspi_work_t *  p_work = p_qspi_dev->p_work;

    size_t blk = p_blk_left->blk_id %
                 BD_BLOCKS_PER_ERASEUNIT(p_work->geometry.blk_size);
    size_t cnt = BD_BLOCKS_PER_ERASEUNIT(p_work->geometry.blk_size) - blk;
    size_t off = p_work->geometry.blk_size * blk;

    if (cnt > p_blk_left->blk_count)
    {
        cnt = p_blk_left->blk_count;
    }

    bool erase_required = block_dev_qspi_update_eunit(p_qspi_dev,
                                                      off,
                                                      p_blk_left->p_buff,
                                                      cnt * p_work->geometry.blk_size);
    if (erase_required)
    {
        p_work->erase_required = true;
    }

    p_blk_left->blk_count -= cnt;
    p_blk_left->blk_id += cnt;
    p_blk_left->p_buff = (uint8_t *)p_blk_left->p_buff + cnt * p_work->geometry.blk_size;

    if (p_work->erase_required)
    {
        uint32_t blk_size = p_work->geometry.blk_size;
        p_work->erase_unit_dirty_blocks |= (1u << BD_BLOCKS_PER_ERASEUNIT(blk_size)) - 1;
    }

    if (p_work->erase_unit_dirty_blocks == 0 || p_work->writeback_mode)
    {
        /*No dirty blocks detected. Write end.*/
        if (p_work->ev_handler && p_blk_left->blk_count == 0)
        {
            const nrf_block_dev_event_t ev = {
                    NRF_BLOCK_DEV_EVT_BLK_WRITE_DONE,
                    NRF_BLOCK_DEV_RESULT_SUCCESS,
                    &p_work->req,
                    p_work->p_context
            };


            p_work->state = NRF_BLOCK_DEV_QSPI_STATE_IDLE;
            p_work->ev_handler(&p_qspi_dev->block_dev, &ev);
            return NRF_SUCCESS;
        }
    }

    return block_dev_qspi_write_start(p_qspi_dev);
}

static ret_code_t block_dev_qspi_write_req(nrf_block_dev_t const * p_blk_dev,
                                           nrf_block_req_t const * p_blk)
{
    ASSERT(p_blk_dev);
    ASSERT(p_blk);
    nrf_block_dev_qspi_t const * p_qspi_dev =
                                 CONTAINER_OF(p_blk_dev, nrf_block_dev_qspi_t, block_dev);
    nrf_block_dev_qspi_work_t *  p_work = p_qspi_dev->p_work;

    ret_code_t ret = NRF_SUCCESS;

    if (m_active_qspi_dev != p_qspi_dev)
    {
        /* QSPI instance is BUSY*/
        return NRF_ERROR_BUSY;
    }

    if (p_work->state != NRF_BLOCK_DEV_QSPI_STATE_IDLE)
    {
        /* Previous asynchronous operation in progress*/
        return NRF_ERROR_BUSY;
    }

    p_work->left_req = *p_blk;
    p_work->req = *p_blk;

    nrf_block_req_t * p_blk_left = &p_work->left_req;

    uint32_t erase_unit = BD_BLOCK_TO_ERASEUNIT(p_blk_left->blk_id,
                                                p_work->geometry.blk_size);

    /* Check if block is in erase unit buffer*/
    if (erase_unit == p_work->erase_unit_idx)
    {
        ret = block_dev_qspi_eunit_write(p_qspi_dev, p_blk_left);
    }
    else
    {
        if (p_work->writeback_mode)
        {
            ret = block_dev_qspi_write_start(p_qspi_dev);
        }
        else
        {
            p_work->erase_unit_idx = erase_unit;
            p_work->state = NRF_BLOCK_DEV_QSPI_STATE_EUNIT_LOAD;

            ret = nrf_drv_qspi_read(p_work->p_erase_unit_buff,
                    NRF_BLOCK_DEV_QSPI_ERASE_UNIT_SIZE,
                    erase_unit * NRF_BLOCK_DEV_QSPI_ERASE_UNIT_SIZE);
        }
    }

    if (ret != NRF_SUCCESS)
    {
        p_work->state = NRF_BLOCK_DEV_QSPI_STATE_IDLE;
        return ret;
    }

    if (!p_work->ev_handler && (p_work->state != NRF_BLOCK_DEV_QSPI_STATE_IDLE))
    {
        /*Synchronous operation*/
        wait_for_idle(p_qspi_dev);
    }

    return ret;
}

static ret_code_t block_dev_qspi_ioctl(nrf_block_dev_t const * p_blk_dev,
                                       nrf_block_dev_ioctl_req_t req,
                                       void * p_data)
{
    ASSERT(p_blk_dev);
    nrf_block_dev_qspi_t const * p_qspi_dev =
                                 CONTAINER_OF(p_blk_dev, nrf_block_dev_qspi_t, block_dev);
    nrf_block_dev_qspi_work_t *  p_work = p_qspi_dev->p_work;

    switch (req)
    {
        case NRF_BLOCK_DEV_IOCTL_REQ_CACHE_FLUSH:
        {
            bool * p_flushing = p_data;
            if (p_work->state != NRF_BLOCK_DEV_QSPI_STATE_IDLE)
            {
                return NRF_ERROR_BUSY;
            }

            if (!p_work->writeback_mode || p_work->erase_unit_dirty_blocks == 0)
            {
                if (p_flushing)
                {
                    *p_flushing = false;
                }

                return NRF_SUCCESS;
            }

            ret_code_t ret =  block_dev_qspi_write_start(p_qspi_dev);
            if (ret == NRF_SUCCESS)
            {
                if (p_flushing)
                {
                    *p_flushing = true;
                }
                p_work->cache_flushing = true;
            }

            return ret;
        }
        case NRF_BLOCK_DEV_IOCTL_REQ_INFO_STRINGS:
        {
            if (p_data == NULL)
            {
                return NRF_ERROR_INVALID_PARAM;
            }

            nrf_block_dev_info_strings_t const * * pp_strings = p_data;
            *pp_strings = &p_qspi_dev->info_strings;
            return NRF_SUCCESS;
        }
        default:
            break;
    }

    return NRF_ERROR_NOT_SUPPORTED;
}

static nrf_block_dev_geometry_t const * block_dev_qspi_geometry(nrf_block_dev_t const * p_blk_dev)
{
    ASSERT(p_blk_dev);
    nrf_block_dev_qspi_t const * p_qspi_dev =
                                 CONTAINER_OF(p_blk_dev, nrf_block_dev_qspi_t, block_dev);
    nrf_block_dev_qspi_work_t const * p_work = p_qspi_dev->p_work;

    return &p_work->geometry;
}

const nrf_block_dev_ops_t nrf_block_device_qspi_ops = {
        .init = block_dev_qspi_init,
        .uninit = block_dev_qspi_uninit,
        .read_req = block_dev_qspi_read_req,
        .write_req = block_dev_qspi_write_req,
        .ioctl = block_dev_qspi_ioctl,
        .geometry = block_dev_qspi_geometry,
};


/** @} */
