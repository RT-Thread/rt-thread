/*
 * File      : fal_cfg.h
 * This file is part of FAL (Flash Abstraction Layer) package
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#ifdef RT_USING_FAL

#include <rtconfig.h>
#include <board.h>

#define FLASH_SIZE_GRANULARITY_128K     (16 * 128 * 1024)

/* ===================== Flash device Configuration ========================= */
extern const struct fal_flash_dev stm32_onchip_flash_128k;
extern struct fal_flash_dev nor_flash0;
extern struct fal_flash_dev nor_flash1;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &stm32_onchip_flash_128k,                                        \
    &nor_flash0,                                                     \
    &nor_flash1,                                                     \
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                                              \
{                                                                                                   \
    {FAL_PART_MAGIC_WORD, "bootloader",           "onchip_flash_128k",        0,      128*1024, 0}, \
    {FAL_PART_MAGIC_WORD, "filesystem",  FAL_USING_NOR_FLASH_DEV_NAME,        0,   8*1024*1024, 0}, \
    {FAL_PART_MAGIC_WORD,    "fs_qspi",                    "W25Q64_q",        0,   8*1024*1024, 0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* RT_USING_FAL */

#endif /* _FAL_CFG_H_ */
