/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtthread.h>
#include <board.h>

/* enable hc32f4 onchip flash driver sample */
#define FAL_FLASH_PORT_DRIVER_HC32F4
/* enable SFUD flash driver sample */
#define FAL_FLASH_PORT_DRIVER_SFUD

extern const struct fal_flash_dev hc32_onchip_flash;
extern struct fal_flash_dev ext_nor_flash0;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &hc32_onchip_flash,                                              \
    &ext_nor_flash0,                                                 \
}

/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                                 \
{                                                                                      \
    {FAL_PART_MAGIC_WROD,          "app",   "onchip_flash",   0,  256 * 1024, 0},      \
    {FAL_PART_MAGIC_WROD,   "filesystem",         "w25q64",   0,  8 * 1024 * 1024, 0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
