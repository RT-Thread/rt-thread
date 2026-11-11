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

extern const struct fal_flash_dev _onchip_flash_lp;

#define FLASH_START_ADDRESS 0x00000000

/* flash device table */
#define FAL_FLASH_DEV_TABLE             \
{                                       \
    &_onchip_flash_lp,                  \
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/** partition table, The chip flash partition is defined in "\script\memory_regions.ld".
 * The partition start at 0x440 instead of 0 because OFS0, OFS1 and security MPU registers exist.
 * More details can be found in the RA2E2 Group User Manual: Hardware Figure 6.1.
 *
 * The table is used to define flash partition by struct fal_partition in fal_def.h */
#define FAL_PART_TABLE                                                              \
{                                                                                   \
    {FAL_PART_MAGIC_WROD, "app", "onchip_flash_lp", 0x440, 0x0000fbc0, 0},          \
}
#endif /* FAL_PART_HAS_TABLE_CFG */
#endif /* _FAL_CFG_H_ */

