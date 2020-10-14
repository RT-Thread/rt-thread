/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       			Notes
 * 2020-09-29     Dozingfiretruck   first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtthread.h>
#include <board.h>

extern const struct fal_flash_dev stm32_onchip_flash;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &stm32_onchip_flash,                                             \
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG

/* partition table */
#define FAL_PART_TABLE                                                                       \
{                                                                                            \
    {FAL_PART_MAGIC_WROD,        "app",   "onchip_flash",       0,           512 * 1024, 0}, \
    {FAL_PART_MAGIC_WROD,        "param", "onchip_flash",       512 * 1024 , 512 * 1024, 0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */
#endif /* _FAL_CFG_H_ */
