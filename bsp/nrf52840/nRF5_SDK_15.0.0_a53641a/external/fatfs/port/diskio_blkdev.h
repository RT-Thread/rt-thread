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

#ifndef DISKIO_SDCARD_H_
#define DISKIO_SDCARD_H_

#include "diskio.h"
#include "nrf_block_dev.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@file
 *
 * @defgroup diskio_blockdev FatFS disk I/O interface based on block device.
 * @{
 *
 * @brief This module implements the FatFs disk API. Internals of this module are based on block device.
 *
 */

/**
 * @brief FatFs disk I/O block device configuration structure.
 * */
typedef struct
{
    const nrf_block_dev_t * p_block_device; ///< Block device associated with a FatFs drive.

    /**
     * @brief FatFs disk interface synchronous wait function.
     *
     * The function to be called repeatedly until the disk I/O operation is completed.
     */
    void (*wait_func)(void);
} diskio_blkdev_config_t;


/**
 * @brief Disk I/O block device.
 * */
typedef struct
{
    diskio_blkdev_config_t config;       ///< Disk I/O configuration.
    nrf_block_dev_result_t last_result;  ///< Result of the last I/O operation.
    volatile DSTATUS state;              ///< Current disk state.
    volatile bool    busy;               ///< Disk busy flag.
} diskio_blkdev_t;

/**
 * @brief Initializer of @ref diskio_blkdev_t.
 *
 * @param blk_device    Block device handle.
 * @param wait_funcion  User wait function (NULL is allowed).
 * */
#define DISKIO_BLOCKDEV_CONFIG(blk_device, wait_funcion)    {   \
    .config = {                                                 \
            .p_block_device = (blk_device),                     \
            .wait_func = (wait_funcion),                        \
    },                                                          \
    .last_result = NRF_BLOCK_DEV_RESULT_SUCCESS,                \
    .state       = STA_NOINIT,                                  \
    .busy        = false                                        \
}

/**
 * @brief FatFs disk initialization.
 *
 * Initializes a block device assigned to a drive number.
 *
 * @param[in] drv Drive number.
 *
 * @return Disk status code.
 * */
DSTATUS disk_initialize(BYTE drv);

/**
 * @brief FatFs disk uninitialization.
 *
 * Uninitializes a block device assigned to a drive number.
 *
 * @param[in] drv Drive index.
 *
 * @return Disk status code.
 * */
DSTATUS disk_uninitialize(BYTE drv);

/**
 * @brief FatFs disk status get.
 *
 * @param[in] drv Drive index.
 *
 * @return Disk status code.
 * */
DSTATUS disk_status(BYTE drv);

/**
 * @brief FatFs disk sector read.
 *
 * @param[in] drv       Drive number.
 * @param[out] buff     Output buffer.
 * @param[in] sector    Sector start number.
 * @param[in] count     Sector count.
 *
 * @return FatFs standard error code.
 * */
DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count);

/**
 * @brief FatFs disk sector write.
 *
 * @param[in] drv       Drive number.
 * @param[in] buff      Input buffer.
 * @param[in] sector    Sector start number.
 * @param[in] count     Sector count.
 *
 * @return FatFs standard error code.
 * */
DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count);

/**
 * @brief FatFs disk I/O control operation.
 *
 * @param[in] drv   Drive number.
 * @param[in] cmd   I/O control command.
 * @param buff      I/O control parameter (optional).
 *
 * @return FatFs standard error code.
 * */
DRESULT disk_ioctl(BYTE drv, BYTE cmd, void* buff);


/**
 * @brief Registers a block device array.
 *
 * @warning This function must be called before any other function from this header.
 *
 * @param[in] diskio_blkdevs    Disk I/O block device array.
 * @param[in] count             Number of elements in a block device array.
 * */
void diskio_blockdev_register(diskio_blkdev_t * diskio_blkdevs, size_t count);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /*DISKIO_SDCARD_H_*/
