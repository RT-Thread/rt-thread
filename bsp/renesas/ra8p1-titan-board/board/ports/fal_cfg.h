/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-20     Sherman      the first version
 */
#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include "hal_data.h"
#include "rtconfig.h"

#define NOR_FLASH_DEV_NAME              "ospi_flash"

extern const struct fal_flash_dev _ospi_flash;

/* flash device table */
#define FAL_FLASH_DEV_TABLE             \
{                                       \
    &_ospi_flash,                       \
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/** partition table, The chip flash partition is defined in "\ra\fsp\src\bsp\mcu\ra6m4\bsp_feature.h".
 * More details can be found in the RA6M4 Group User Manual: Hardware section 47 Flash memory.*/
#define FAL_PART_TABLE                                                                     \
{                                                                                          \
    {FAL_PART_MAGIC_WORD, "whd_firmware", NOR_FLASH_DEV_NAME,         0,     512*1024, 0}, \
    {FAL_PART_MAGIC_WORD, "whd_clm",    NOR_FLASH_DEV_NAME,    512*1024,     512*1024, 0}, \
    {FAL_PART_MAGIC_WORD, "download",   NOR_FLASH_DEV_NAME,   1024*1024,  2*1024*1024, 0}, \
    {FAL_PART_MAGIC_WORD, "easyflash",  NOR_FLASH_DEV_NAME, 3*1024*1024,  1*1024*1024, 0}, \
    {FAL_PART_MAGIC_WORD, "filesystem", NOR_FLASH_DEV_NAME, 4*1024*1024, 12*1024*1024, 0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */
#endif /* _FAL_CFG_H_ */

