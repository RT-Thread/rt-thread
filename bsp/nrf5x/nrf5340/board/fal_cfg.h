/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-05-05     supperthomas this is sample you can change by yourself
 *
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtconfig.h>
#include <board.h>

#if (defined(BSP_USING_QSPI_FLASH)&&defined(BSP_USING_ON_CHIP_FLASH))

#define ON_CHIP_FLASH_DEV_NAME             "mcu_onchip"
#define NOR_FLASH_DEV_NAME             "norflash0"

extern const struct fal_flash_dev mcu_onchip_flash;
extern struct fal_flash_dev nor_flash0;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
    {                                                                    \
        &mcu_onchip_flash,                                           \
        &nor_flash0,                                                     \
    }
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                               \
    {                                                                                    \
        {FAL_PART_MAGIC_WORD, "bl",            ON_CHIP_FLASH_DEV_NAME,         0,   64*1024, 0}, \
        {FAL_PART_MAGIC_WORD, "app_flash",     ON_CHIP_FLASH_DEV_NAME,   64*1024,  960*1024, 0}, \
        {FAL_PART_MAGIC_WORD, "nor_flash_part_0", NOR_FLASH_DEV_NAME,         0, 1024*1024, 0}, \
        {FAL_PART_MAGIC_WORD, "nor_flash_part_1", NOR_FLASH_DEV_NAME, 1024*1024, 7*1024*1024, 0}, \
    }
#endif /* FAL_PART_HAS_TABLE_CFG */

#elif defined(BSP_USING_QSPI_FLASH)

#define NOR_FLASH_DEV_NAME             "norflash0"
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
        {FAL_PART_MAGIC_WORD, "nor_flash_part_0", NOR_FLASH_DEV_NAME,         0, 1024*1024, 0}, \
        {FAL_PART_MAGIC_WORD,  "nor_flash_part_1", NOR_FLASH_DEV_NAME, 1024*1024, 7*1024*1024, 0}, \
    }
#endif
#elif defined(BSP_USING_ON_CHIP_FLASH)
extern const struct fal_flash_dev mcu_onchip_flash;
#define ON_CHIP_FLASH_DEV_NAME             "mcu_onchip"
/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
    {                                                                    \
        &mcu_onchip_flash,                                               \
    }
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                               \
    {                                                                                    \
        {FAL_PART_MAGIC_WORD,        "bl",           ON_CHIP_FLASH_DEV_NAME,         0,   64*1024, 0}, \
        {FAL_PART_MAGIC_WORD,       "app_flash",     ON_CHIP_FLASH_DEV_NAME,   64*1024,  960*1024, 0}, \
    }
#endif
#endif

#endif /* _FAL_CFG_H_ */
