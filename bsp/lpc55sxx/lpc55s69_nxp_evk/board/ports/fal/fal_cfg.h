/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-21     Wangyuqiang  the first version
 */
#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtthread.h>
#include <board.h>

#ifndef FAL_USING_NOR_FLASH_DEV_NAME
#define NOR_FLASH_DEV_NAME             "norflash0"
#else
#define NOR_FLASH_DEV_NAME              FAL_USING_NOR_FLASH_DEV_NAME
#endif

/* Flash device Configuration */

extern struct fal_flash_dev nor_flash0;

/* flash device table */

#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &nor_flash0,                                                     \
}

/* Partition Configuration */

#ifdef FAL_PART_HAS_TABLE_CFG

/* partition table */

#define FAL_PART_TABLE                                                                                                  \
{                                                                                                                       \
    {FAL_PART_MAGIC_WROD,  "easyflash", NOR_FLASH_DEV_NAME,                                    0,       512 * 1024, 0}, \
    {FAL_PART_MAGIC_WROD,   "download", NOR_FLASH_DEV_NAME,                           512 * 1024,      1024 * 1024, 0}, \
    {FAL_PART_MAGIC_WROD, "wifi_image", NOR_FLASH_DEV_NAME,                  (512 + 1024) * 1024,       512 * 1024, 0}, \
    {FAL_PART_MAGIC_WROD,       "font", NOR_FLASH_DEV_NAME,            (512 + 1024 + 512) * 1024,  7 * 1024 * 1024, 0}, \
    {FAL_PART_MAGIC_WROD, "filesystem", NOR_FLASH_DEV_NAME, (512 + 1024 + 512 + 7 * 1024) * 1024,  7 * 1024 * 1024, 0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
