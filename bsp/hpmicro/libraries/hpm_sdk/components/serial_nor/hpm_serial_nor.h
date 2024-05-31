/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_SERIAL_NOR_H
#define _HPM_SERIAL_NOR_H

#include "hpm_serial_nor_host.h"

/**
 * @brief spi nor API error codes
 */
enum {
    status_spi_nor_sfdp_not_found = MAKE_STATUS(status_group_spi_nor_flash, 0),                       /**<  SFDP table was not found */
    status_spi_nor_ddr_read_dummy_cycle_probe_failed = MAKE_STATUS(status_group_spi_nor_flash, 1),    /**<  Probing Dummy cyles for DDR read failed */
    status_spi_nor_flash_not_found = MAKE_STATUS(status_group_spi_nor_flash, 2),                      /**< FLASH was not detected */
    status_spi_nor_flash_para_err = MAKE_STATUS(status_group_spi_nor_flash, 3),
    status_spi_nor_flash_is_busy = MAKE_STATUS(status_group_spi_nor_flash, 4),
    status_spi_nor_flash_not_qe_bit_in_sfdp = MAKE_STATUS(status_group_spi_nor_flash, 5),
};

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief determine whether the serial nor flash is busy
 * @param [in] host  the serial nor context
 * @return hpm_stat_t: status_spi_nor_flash_is_busy if the serial nor flash is busy
 */
hpm_stat_t hpm_serial_nor_is_busy(hpm_serial_nor_t *flash);

/**
 * @brief set serial nor flash write enable
 * @param [in] channel serial nor flash channel
 * @return hpm_stat_t: status_success if write enable success
 */
hpm_stat_t hpm_serial_nor_write_enable(hpm_serial_nor_t *flash);

/**
 * @brief erase the serial nor flash chip
 * @param [in] host  the serial nor context
 * @return hpm_stat_t: status_success if erase chip success
 */
hpm_stat_t hpm_serial_nor_erase_chip(hpm_serial_nor_t *flash);

/**
 * @brief erase the serial nor flash block using blocking transfer
 *
 * @note the erase block address must be block alignment
 *
 * @param [in] host  the serial nor context
 * @param [in] block_addr the serial nor flash block address
 * @return hpm_stat_t: status_success if erase block success
 */
hpm_stat_t hpm_serial_nor_erase_block_blocking(hpm_serial_nor_t *flash, uint32_t block_addr);

/**
 * @brief erase the serial nor flash block using noblocking transfer
 *
 * @note the erase block address must be block alignment, it'not wait flash busy status.
 *
 * @param [in] host  the serial nor context
 * @param [in] block_addr the serial nor flash block address
 * @return hpm_stat_t: status_success if erase block success
 */
hpm_stat_t hpm_serial_nor_erase_block_noblocking(hpm_serial_nor_t *flash, uint32_t block_addr);

/**
 * @brief erase the serial nor flash sector using blocking transfer
 *
 * @note the erase sector address must be sector alignment
 *
 * @param [in] host  the serial nor context
 * @param [in] sector_addr the serial nor flash sector address
 * @return hpm_stat_t: status_success if erase sector success
 */
hpm_stat_t hpm_serial_nor_erase_sector_blocking(hpm_serial_nor_t *flash, uint32_t sector_addr);

/**
 * @brief erase the serial nor flash sector using noblocking transfer
 *
 * @note the erase sector address must be sector alignment, it'not wait flash busy status.
 *
 * @param [in] host  the serial nor context
 * @param [in] sector_addr the serial nor flash sector address
 * @return hpm_stat_t: status_success if erase sector success
 */
hpm_stat_t hpm_serial_nor_erase_sector_noblocking(hpm_serial_nor_t *flash, uint32_t sector_addr);

/**
 * @brief erase the serial nor flash specified start address and length using blocking transfer
 *
 * @note the erase sector address must be sector alignment
 *
 * @param [in] host  the serial nor context
 * @param [in] sector_addr the serial nor flash sector address
 * @return hpm_stat_t: status_success if erase success
 */
hpm_stat_t hpm_serial_nor_erase_blocking(hpm_serial_nor_t *flash, uint32_t start, uint32_t length);

/**
 * @brief program data to the specified serial nor flash address using blocking transfer
 * @param [in] host  the serial nor context
 * @param [in] buf  the data source pointer
 * @param [in] data_len the data length
 * @param [in] address  the serial nor flash programming address
 * @return hpm_stat_t: status_success if program success
 */
hpm_stat_t hpm_serial_nor_program_blocking(hpm_serial_nor_t *flash, uint8_t *buf, uint32_t data_len,
                               uint32_t address);

/**
 * @brief program data to the page nor flash address using noblocking transfer
 * @param [in] host  the serial nor context
 * @param [in] buf  the data source pointer
 * @param [in] data_len the data length
 * @param [in] address  the serial nor flash programming address
 * @return hpm_stat_t: status_success if program success
 */
hpm_stat_t hpm_serial_nor_page_program_noblocking(hpm_serial_nor_t *flash, uint8_t *buf,
                                                  uint32_t data_len,
                                                  uint32_t address);

/**
 * @brief read the data of specified serial nor flash address
 * @param [in] host  the serial nor context
 * @param [in] buf  the data source pointer
 * @param [in] data_len the data length
 * @param [in] address  the serial nor flash reading address
 * @return hpm_stat_t: status_success if read success
 */
hpm_stat_t hpm_serial_nor_read(hpm_serial_nor_t *flash, uint8_t *buf, uint16_t data_len,
                            uint32_t address);

/**
 * @brief the serial nor flash initialization
 * @param [in] host  the serial nor context
 * @param [out] info  serial_nor_flash_info_t
 * @return hpm_stat_t: status_success if initialization success
 */
hpm_stat_t hpm_serial_nor_init(hpm_serial_nor_t *flash, hpm_serial_nor_info_t *info);

/**
 * @brief get the serial nor flash information
 * @param [in] host  the serial nor context
 * @param [out] info  serial_nor_flash_info_t
 * @return hpm_stat_t: status_success if get information success
 */
hpm_stat_t hpm_serial_nor_get_info(hpm_serial_nor_t *flash, hpm_serial_nor_info_t *info);

#ifdef __cplusplus
}
#endif
#endif
