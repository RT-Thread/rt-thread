/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __HOSAL_FLASH_H__
#define __HOSAL_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup hosal_flash FLASH
 *  HOSAL FLASH API
 *
 *  @{
 */

#include <stdint.h>

#define HOSAL_FLASH_FLAG_ADDR_0      0  /**< @brief Open flash prtition address 0 in prtition table */

#define HOSAL_FLASH_FLAG_ADDR_1      (1 << 0) /**< @brief Open flash prtition address 1 in prtition table */

/**
 * Open the partition table and use the bus physical address of flash.
 * (If it is not set, the offset address set in the partition table is used by default.)
 */
#define HOSAL_FLASH_FLAG_BUSADDR     (1 << 1)

/**
 * @brief Hal flash partition device
 */
typedef struct hosal_flash_dev {
    void *flash_dev;    /**< @brief flash device */
} hosal_flash_dev_t;

/**
 * @brief Hal flash partition manage struct
 */
typedef struct {
    const char  *partition_description; /**< @brief name */
    uint32_t     partition_start_addr;  /**< @brief start addr */
    uint32_t     partition_length;      /**< @brief length */
    uint32_t     partition_options;     /**< @brief options */
} hosal_logic_partition_t;

/**
 * @brief Open a flash partition device
 *
 * @param[in]  name     flash partition name
 * @param[in]  flags    flash flags
 *               - HOSAL_FLASH_FLAG_ADDR_0
 *               - HOSAL_FLASH_FLAG_ADDR_1
 *               - HOSAL_FLASH_FLAG_BUSADDR
 *
 * @return
 *  - NULL flash open error
 *  - otherwise is flash partition device
 */
hosal_flash_dev_t *hosal_flash_open(const char *name, unsigned int flags);

/**
 * @brief Get the information of the specified flash area
 *
 * @param[in]  p_dev     The target flash logical partition device
 * @param[out] partition The buffer to store partition info
 *
 * @return
 *  - 0 On success
 *  - otherwise is error
 */
int hosal_flash_info_get(hosal_flash_dev_t *p_dev, hosal_logic_partition_t *partition);

/**
 * @brief Erase an area on a Flash logical partition
 *
 * @note  Erase on an address will erase all data on a sector that the
 *        address is belonged to, this function does not save data that
 *        beyond the address area but in the affected sector, the data
 *        will be lost.
 *
 * @param[in]  p_dev         The target flash logical partition which should be erased
 * @param[in]  off_set       Start address of the erased flash area
 * @param[in]  size          Size of the erased flash area
 *
 * @return
 *  - 0 On success
 *  - otherwise is error
 */
int hosal_flash_erase(hosal_flash_dev_t *p_dev, uint32_t off_set, uint32_t size);

/**
 * @brief Write data to an area on a flash logical partition without erase
 *
 * @param[in]  p_dev           The target flash logical partition which should be read which should be written
 * @param[in/out]  off_set     Point to the start address that the data is written to, and
 *                             point to the last unwritten address after this function is
 *                             returned, so you can call this function serval times without
 *                             update this start address.
 * @param[in]  in_buf          point to the data buffer that will be written to flash
 * @param[in]  in_buf_size     The size of the buffer
 *
 * @return
 *  - 0 On success
 *  - otherwise is error
 */
int hosal_flash_write(hosal_flash_dev_t *p_dev, uint32_t *off_set,
                    const void *in_buf, uint32_t in_buf_size);

/**
 * @brief Write data to an area on a flash logical partition with erase first
 *
 * @param[in]  p_dev           The target flash logical partition which should be read which should be written
 * @param[in/out]  off_set     Point to the start address that the data is written to, and
 *                             point to the last unwritten address after this function is
 *                             returned, so you can call this function serval times without
 *                             update this start address.
 * @param[in]  in_buf          point to the data buffer that will be written to flash
 * @param[in]  in_buf_size     The length of the buffer
 *
 * @return
 *  - 0 On success
 *  - otherwise is error
 */
int hosal_flash_erase_write(hosal_flash_dev_t *p_dev, uint32_t *off_set,
                          const void *in_buf, uint32_t in_buf_size);

/**
 * @brief Read data from an area on a Flash to data buffer in RAM
 *
 * @param[in]  p_dev           The target flash logical partition which should be read
 * @param[in/out]  off_set     Point to the start address that the data is read, and
 *                             point to the last unread address after this function is
 *                             returned, so you can call this function serval times without
 *                             update this start address.
 * @param[in]  out_buf         Point to the data buffer that stores the data read from flash
 * @param[in]  out_buf_size    The length of the buffer
 *
 * @return
 *  - 0 On success
 *  - otherwise is error
 */
int hosal_flash_read(hosal_flash_dev_t *p_dev, uint32_t *off_set,
                   void *out_buf, uint32_t out_buf_size);

/**
 * @brief Close a flash partition device
 *
 * @param[in]  p_dev     flash partition device
 *
 * @return
 *  - 0 On success
 *  - otherwise is error
 */
int hosal_flash_close(hosal_flash_dev_t *p_dev);

/**
 * @brief Read data from a row address on a Flash to data buffer in RAM
 *
 * @param[in]  buffer          Point to the data buffer that stores the data read from flash
 * @param[in]  address         Address on flash to read from
 * @param[in]  length          Length (in bytes) of data to read
 *
 * @return
 *  - 0 On success
 *  - otherwise is error
 */
int hosal_flash_raw_read(void *buffer, uint32_t address, uint32_t length);

/**
 * @brief Write data to a row address on a Flash
 *
 * @param[in]  buffer          Point to the data buffer that will be written to flash
 * @param[in]  address         Address on flash to write to
 * @param[in]  length          Length (in bytes) of data to write
 *
 * @return
 *  - 0 On success
 *  - otherwise is error
 */
int hosal_flash_raw_write(void *buffer, uint32_t address, uint32_t length);

/**
 * @brief Erase a region of the flash
 *
 * @param[in]  start_addr      Address to start erasing flash.
 * @param[in]  length          Length of region to erase.
 *
 * @return
 *  - 0 On success
 *  - otherwise is error
 */
int hosal_flash_raw_erase(uint32_t start_addr, uint32_t length); 

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __HOSAL_FLASH_H__ */

/* end of file */
