/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-5      SummerGift   first version
 * 2020-5-17      yufanyufan77 support H7
 */

#ifndef __FAL_CFG_H__
#define __FAL_CFG_H__

#include <rtthread.h>
#include <board.h>

#define FLASH_SIZE_GRANULARITY_128K   (16 * 128 * 1024)
#define STM32_FLASH_START_ADRESS_128K (0x8000000)

extern const struct fal_flash_dev stm32_onchip_flash_128k;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &stm32_onchip_flash_128k,                                        \
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG

/* partition table */
#define FAL_PART_TABLE                                                                                     \
{                                                                                                          \
    {FAL_PART_MAGIC_WROD, "app",            "onchip_flash_128k", 0 ,             8*128*1024,  0},          \
    {FAL_PART_MAGIC_WROD, "param",          "onchip_flash_128k", 8*128*1024 ,    128*1024,    0},          \
    {FAL_PART_MAGIC_WROD, "factory",        "onchip_flash_128k", 9*128*1024 ,    7*128*1024,  0},          \
}

#endif /* FAL_PART_HAS_TABLE_CFG */
#endif /* _FAL_CFG_H_ */
