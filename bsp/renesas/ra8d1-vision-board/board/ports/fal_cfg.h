/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
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

extern const struct fal_flash_dev _onchip_flash_hp0;
extern const struct fal_flash_dev _onchip_flash_hp1;
extern const struct fal_flash_dev _onchip_flash_hp3;

/* flash device table */
#define FAL_FLASH_DEV_TABLE             \
{                                       \
    &_onchip_flash_hp0,                 \
    &_onchip_flash_hp1,                 \
    &_onchip_flash_hp3,                 \
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/** partition table, The chip flash partition is defined in "\ra\fsp\src\bsp\mcu\ra6m4\bsp_feature.h".
 * More details can be found in the RA6M4 Group User Manual: Hardware section 47 Flash memory.*/
#define FAL_PART_TABLE                                                                                                      \
{                                                                                                                           \
    {FAL_PART_MAGIC_WROD, "boot", "onchip_flash_hp0", 0, BSP_FEATURE_FLASH_HP_CF_REGION0_SIZE, 0},                          \
    {FAL_PART_MAGIC_WROD, "app", "onchip_flash_hp1", 0, (BSP_ROM_SIZE_BYTES - BSP_FEATURE_FLASH_HP_CF_REGION0_SIZE), 0},    \
    {FAL_PART_MAGIC_WROD, "disk", "onchip_flash_hp3", 0, (BSP_DATA_FLASH_SIZE_BYTES), 0},                             \
}
#endif /* FAL_PART_HAS_TABLE_CFG */
#endif /* _FAL_CFG_H_ */

