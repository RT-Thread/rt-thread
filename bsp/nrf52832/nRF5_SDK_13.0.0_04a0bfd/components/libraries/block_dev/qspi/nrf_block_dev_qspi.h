/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#ifndef NRF_BLOCK_DEV_QSPI_H__
#define NRF_BLOCK_DEV_QSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_block_dev.h"
#include "nrf_drv_qspi.h"

/**@file
 *
 * @defgroup nrf_block_dev_qspi QSPI implementation
 * @ingroup nrf_block_dev
 * @{
 *
 */

/**
 * @brief QSPI block device operations
 * */
extern const nrf_block_dev_ops_t nrf_block_device_qspi_ops;

/**
 * @brief QSPI block device internal erase unit buffer size
 * */
#define NRF_BLOCK_DEV_QSPI_ERASE_UNIT_SIZE (4096)

/**
 * @brief Internal Block device state
 */
typedef enum {
    NRF_BLOCK_DEV_QSPI_STATE_DISABLED = 0,  /**< QSPI block device state DISABLED      */
    NRF_BLOCK_DEV_QSPI_STATE_IDLE,          /**< QSPI block device state IDLE          */
    NRF_BLOCK_DEV_QSPI_STATE_READ_EXEC,     /**< QSPI block device state READ_EXEC     */
    NRF_BLOCK_DEV_QSPI_STATE_EUNIT_LOAD,    /**< QSPI block device state EUNIT_LOAD    */
    NRF_BLOCK_DEV_QSPI_STATE_WRITE_ERASE,   /**< QSPI block device state WRITE_ERASE   */
    NRF_BLOCK_DEV_QSPI_STATE_WRITE_EXEC,    /**< QSPI block device state WRITE_EXEC    */
} nrf_block_dev_qspi_state_t;

/**
 * @brief Work structure of QSPI block device
 */
typedef struct {
    volatile nrf_block_dev_qspi_state_t state;        //!< QSPI block device state

    nrf_block_dev_geometry_t geometry;                //!< Block device geometry
    nrf_block_dev_ev_handler ev_handler;              //!< Block device event handler
    void const *             p_context;               //!< Context handle passed to event handler
    nrf_block_req_t          req;                     //!< Block READ/WRITE request: original value
    nrf_block_req_t          left_req;                //!< Block READ/WRITE request: left value

    bool     cache_flushing;                                        //!< QSPI cache flush in progress flag
    bool     writeback_mode;                                        //!< QSPI write-back mode flag
    bool     erase_required;                                        //!< QSPI erase required flag
    uint32_t erase_unit_idx;                                        //!< QSPI erase unit index
    uint32_t erase_unit_dirty_blocks;                               //!< QSPI erase unit dirty blocks mask
    uint8_t  p_erase_unit_buff[NRF_BLOCK_DEV_QSPI_ERASE_UNIT_SIZE]; //!< QSPI erase unit buffer (fixed value)
} nrf_block_dev_qspi_work_t;

/**
 * @brief QSPI block device flags*/
typedef enum {
    NRF_BLOCK_DEV_QSPI_FLAG_CACHE_WRITEBACK = (1u << 0)  //!< Cache write-back mode enable flag
} nrf_block_dev_qspi_flag_t;

/**
 * @brief QSPI block device config initializer (@ref nrf_block_dev_qspi_config_t)
 *
 * @param blk_size          Block size
 * @param blk_flags         Block device flags, @ref nrf_block_dev_qspi_flag_t
 * @param qspi_drv_config   QPSI driver config
 * */
#define NRF_BLOCK_DEV_QSPI_CONFIG(blk_size, blk_flags, qspi_drv_config)  {   \
        .block_size = (blk_size),                                            \
        .flags = (blk_flags),                                                \
        .qspi_config =  qspi_drv_config                                      \
}

/**
 * @brief QSPI block device config
 */
typedef struct {
    uint32_t block_size;                  //!< Desired block size
    uint32_t flags;                       //!< QSPI block device flags
    nrf_drv_qspi_config_t qspi_config;    //!< QSPI configuration
} nrf_block_dev_qspi_config_t;

/**
 * @brief QSPI block device
 * */
typedef struct {
    nrf_block_dev_t              block_dev;          //!< Block device
    nrf_block_dev_info_strings_t info_strings;       //!< Block device information strings
    nrf_block_dev_qspi_config_t  qspi_bdev_config;   //!< QSPI block device config
    nrf_block_dev_qspi_work_t *  p_work;             //!< QSPI block device work structure
} nrf_block_dev_qspi_t;

/**
 * @brief Defines a QSPI block device.
 *
 * @param name    Instance name
 * @param config  Configuration @ref nrf_block_dev_qspi_config_t
 * @param info    Info strings @ref NFR_BLOCK_DEV_INFO_CONFIG
 * */
#define NRF_BLOCK_DEV_QSPI_DEFINE(name, config, info)                \
    static nrf_block_dev_qspi_work_t CONCAT_2(name, _work);          \
    static const nrf_block_dev_qspi_t name = {                       \
            .block_dev = { .p_ops = &nrf_block_device_qspi_ops },    \
            .info_strings = BRACKET_EXTRACT(info),                   \
            .qspi_bdev_config = config,                              \
            .p_work = &CONCAT_2(name, _work),                        \
    }

/**
 * @brief Returns block device API handle from QSPI block device.
 *
 * @param[in] p_blk_qspi QSPI block device
 * @return Block device handle
 */
static inline nrf_block_dev_t const *
nrf_block_dev_qspi_ops_get(nrf_block_dev_qspi_t const * p_blk_qspi)
{
    return &p_blk_qspi->block_dev;
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* NRF_BLOCK_DEV_QSPI_H__ */
