/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-29     flybreak     first implementation
 */

#ifndef __DRV_FLEXSPI_H__
#define __DRV_FLEXSPI_H__
#include "fsl_flexspi.h"
#include "fsl_common.h"
#ifdef BOARD_USING_QSPIFLASH
#define FLASH_SIZE 0x8000 /* 256Mb/KByte */
#define FLASH_PAGE_SIZE 256
#define FLEXSPI_NOR_SECTOR_SIZE 0x1000 /* 4K */
#elif defined(BOARD_USING_HYPERFLASH)
#define FLASH_SIZE 0x10000 /* 512Mb/KByte */
#define FLASH_PAGE_SIZE 512
#define FLEXSPI_NOR_SECTOR_SIZE 0x40000 /* 256K */
#endif
#define FLEXSPI_AMBA_BASE FlexSPI_AMBA_BASE
extern int      rt_hw_flexspi_init(void);
extern status_t flexspi_nor_flash_erase_sector(FLEXSPI_Type *base, uint32_t address);
extern status_t flexspi_nor_flash_page_program(FLEXSPI_Type *base, uint32_t address, const uint32_t *src);
#endif
