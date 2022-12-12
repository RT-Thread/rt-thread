/*
 * Copyright (c) 2006-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     greedyhao    first version
 */

#ifndef __DRV_FLASH_H__
#define __DRV_FLASH_H__

#include <stdint.h>

/**
 * @brief Read a block of data
 *
 * @param buf output data
 * @param addr
 * @param len less than 512
 * @return uint16_t
 */
uint16_t os_spiflash_read(void *buf, uint32_t addr, uint16_t len);

/**
 * @brief Write a block of data
 *
 * @param buf input data
 * @param addr 256 alignment
 * @param len 256 alignment
 */
void os_spiflash_program(const void *buf, uint32_t addr, uint16_t len);

/**
 * @brief Erases a block of data
 *
 * @param addr 4k alignment
 */
void os_spiflash_erase(uint32_t addr);

#endif /* __DRV_FLASH_H__ */
