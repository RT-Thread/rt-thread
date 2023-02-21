/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-4-1        Wayne        First version
*
******************************************************************************/

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtconfig.h>
#include <board.h>

/* ===================== Flash device Configuration ========================= */
#if defined(FAL_PART_HAS_TABLE_CFG)

#if defined(BSP_USING_FMC)
    extern const struct fal_flash_dev Onchip_aprom_flash;
    extern const struct fal_flash_dev Onchip_ldrom_flash;
#endif

#if defined(FAL_USING_SFUD_PORT)
    extern struct fal_flash_dev nor_flash0;
#endif

#if defined(BSP_USING_FMC) && defined(FAL_USING_SFUD_PORT)
#define FAL_FLASH_DEV_TABLE         \
{                                   \
    &Onchip_aprom_flash,            \
      &Onchip_ldrom_flash,            \
    &nor_flash0,                    \
}
#elif defined(BSP_USING_FMC)
#define FAL_FLASH_DEV_TABLE         \
{                                   \
    &Onchip_aprom_flash,            \
      &Onchip_ldrom_flash,            \
    &nor_flash0,                    \
}
#elif defined(FAL_USING_SFUD_PORT)
#define FAL_FLASH_DEV_TABLE         \
{                                   \
    &nor_flash0,                    \
}
#else
#define FAL_FLASH_DEV_TABLE         \
{                                   \
}
#endif

#define FAL_PART_TABLE                                                        \
{                                                                             \
    {FAL_PART_MAGIC_WORD,   "filesystem",     FAL_USING_NOR_FLASH_DEV_NAME,    0,   8*1024*1024, 0},  \
    {FAL_PART_MAGIC_WORD,        "ldrom",     "OnChip_LDROM",                  0,        0x1000, 0},  \
    {FAL_PART_MAGIC_WORD,        "aprom",     "OnChip_APROM",            0x60000,       0x20000, 0},  \
}

#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
