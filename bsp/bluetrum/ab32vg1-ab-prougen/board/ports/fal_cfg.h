/*
 * Copyright (c) 2006-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     greedyhao    first version
 */

#ifndef __FAL_CFG_H__
#define __FAL_CFG_H__

#include <rtthread.h>

#if defined(BSP_USING_ON_CHIP_FLASH)
extern const struct fal_flash_dev ab32_onchip_flash;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &ab32_onchip_flash,                                             \
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG

/* partition table */
#define FAL_PART_TABLE                                                                      \
{                                                                                           \
    {FAL_PART_MAGIC_WROD,       "boot",     "onchip_flash",     0,              8 * 1024,   0}, \
    {FAL_PART_MAGIC_WROD,       "app",      "onchip_flash",     8 * 1024,       996 * 1024, 0}, \
    {FAL_PART_MAGIC_WROD,       "param",    "onchip_flash",     1004 * 1024,    20 * 1024,  0},  \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

#else

#define FAL_FLASH_DEV_TABLE { 0 }
#define FAL_PART_TABLE  { 0 }

#endif

#endif /* __FAL_CFG_H__ */
