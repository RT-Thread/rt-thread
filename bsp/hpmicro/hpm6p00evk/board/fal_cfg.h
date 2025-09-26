/*
 * Copyright (c) 2022 HPMicro
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
#define NOR_FLASH_SIZE_IN_BYTES        0x1000000UL

/* ===================== Flash device Configuration ========================= */
extern struct fal_flash_dev nor_flash0;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &nor_flash0,                                                     \
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                               \
{                                                                                    \
    {FAL_PART_MAGIC_WORD,       "app", NOR_FLASH_DEV_NAME,         0,           256*1024,    0}, \
    {FAL_PART_MAGIC_WORD, "easyflash", NOR_FLASH_DEV_NAME,         256*1024, 256*1024,    0}, \
    {FAL_PART_MAGIC_WORD,  "download", NOR_FLASH_DEV_NAME,         512*1024, 256*1024,    0}, \
    {FAL_PART_MAGIC_WORD,   "flashdb", NOR_FLASH_DEV_NAME,        768*1024, 256*1024,    0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */
#endif /* RT_USING_FAL */

#endif /* _FAL_CFG_H_ */
