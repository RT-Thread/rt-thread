/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-01     RT-Thread    first version
 */

#ifndef __FAL_CFG_H__
#define __FAL_CFG_H__

#include <rtthread.h>
#include <board.h>

extern const struct fal_flash_dev imxrt1180_nor_flash;

/* flash device table */
#define FAL_FLASH_DEV_TABLE      \
{                                \
    &imxrt1180_nor_flash,             \
}

/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG

/* partition table */
#define FAL_PART_TABLE                                                               \
{                                                                                    \
    {FAL_PART_MAGIC_WROD, "app",        "norflash0",          0, 8*1024*1024, 0},  \
    {FAL_PART_MAGIC_WROD, "filesystem", "norflash0", 8*1024*1024, 8*1024*1024, 0}, \
}

#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* __FAL_CFG_H__ */
