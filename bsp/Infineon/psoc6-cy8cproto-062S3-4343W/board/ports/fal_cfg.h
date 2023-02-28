/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-27     Rbb666       first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtthread.h>
#include <board.h>

extern const struct fal_flash_dev ifx_onchip_flash_32k;
extern const struct fal_flash_dev ifx_onchip_flash_256k;

/* flash device table */
#define FAL_FLASH_DEV_TABLE         \
    {                               \
        &ifx_onchip_flash_32k,      \
        &ifx_onchip_flash_256k,     \
    }
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG

/* partition table */
#define FAL_PART_TABLE                                                                  \
    {                                                                                   \
        {FAL_PART_MAGIC_WROD, "param", "onchip_flash_32k", 0, IFX_EFLASH_SIZE, 0},      \
        {FAL_PART_MAGIC_WROD, "app", "onchip_flash_256k", 0, IFX_FLASH_SIZE, 0},        \
    }

#endif /* FAL_PART_HAS_TABLE_CFG */
#endif /* _FAL_CFG_H_ */
