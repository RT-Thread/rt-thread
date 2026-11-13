/*
 * Copyright (c) 2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtconfig.h>
#include <board.h>

#ifdef RT_USING_FAL
#define NOR_FLASH_DEV_NAME             "norflash0"
#define NOR_FLASH_MEM_BASE             0x80000000UL
#define NOR_FLASH_SIZE_IN_BYTES        0x100000UL

#define SPI_NOR_FLASH_DEV_NAME         "spi_norflash0"

/* ===================== Flash device Configuration ========================= */
extern const struct fal_flash_dev stm32f2_onchip_flash;
extern struct fal_flash_dev nor_flash0;

#if defined(RT_USING_SFUD) && defined(BSP_USING_SPI)
extern struct fal_flash_dev spi_nor_flash0;
/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &nor_flash0,                                                     \
    &spi_nor_flash0,                                                 \
}
#else
/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &nor_flash0,                                                     \
}
#endif

/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
//  #ifdef (BSP_USING_SPI) && defined(RT_USING_SFUD) && 
#define FAL_PART_TABLE                                                               \
{                                                                                    \
    {FAL_PART_MAGIC_WORD,       "app", NOR_FLASH_DEV_NAME,         0,           256*1024,    0}, \
    {FAL_PART_MAGIC_WORD, "easyflash", NOR_FLASH_DEV_NAME,         256*1024, 256*1024,    0}, \
    {FAL_PART_MAGIC_WORD,  "download", NOR_FLASH_DEV_NAME,         512*1024, 256*1024,    0}, \
    {FAL_PART_MAGIC_WORD,   "flashdb", NOR_FLASH_DEV_NAME,        768*1024, 256*1024,    0}, \
    {FAL_PART_MAGIC_WORD, "app", SPI_NOR_FLASH_DEV_NAME,          0,        6*1024*1024, 0}, \
    {FAL_PART_MAGIC_WORD, "fs", SPI_NOR_FLASH_DEV_NAME,           6*1024*1024,  10*1024*1024, 0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */
#endif /* RT_USING_FAL */

#endif /* _FAL_CFG_H_ */
