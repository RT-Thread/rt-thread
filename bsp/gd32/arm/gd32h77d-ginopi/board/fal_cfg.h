/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __FAL_CFG_H__
#define __FAL_CFG_H__

#include <rtconfig.h>

#define GD25Q64E_FLASH_DEV_NAME         "gd25q64e"
#define GD25Q64E_FILESYSTEM_PART_NAME   "filesystem"
#define GD25Q64E_FLASH_SIZE             (8U * 1024U * 1024U)

extern const struct fal_flash_dev gd25q64e_flash;

#define FAL_FLASH_DEV_TABLE             \
{                                       \
    &gd25q64e_flash,                    \
}

#ifdef FAL_PART_HAS_TABLE_CFG
#define FAL_PART_TABLE                                                          \
{                                                                               \
    {FAL_PART_MAGIC_WORD, GD25Q64E_FILESYSTEM_PART_NAME,                       \
     GD25Q64E_FLASH_DEV_NAME, 0, GD25Q64E_FLASH_SIZE, 0},                      \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* __FAL_CFG_H__ */
