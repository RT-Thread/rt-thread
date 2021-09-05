/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-3-03       FYChou       First version
*
******************************************************************************/

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtconfig.h>
#include <board.h>


/* ===================== Flash device Configuration ========================= */
extern const struct fal_flash_dev Onchip_aprom_flash;
extern const struct fal_flash_dev Onchip_ldrom_flash;

/* -flash device table------------------------------------------------------- */
#define FAL_FLASH_DEV_TABLE                                                                   \
{                                                                                             \
    &Onchip_aprom_flash,                                                                      \
    &Onchip_ldrom_flash,                                                                      \
}

/* ====================== Partition Configuration ============================ */
#ifdef FAL_PART_HAS_TABLE_CFG

/* -partition table----------------------------------------------------------- */
#define FAL_PART_TABLE                                                                        \
{                                                                                             \
    {FAL_PART_MAGIC_WORD,        "ldrom",     "OnChip_LDROM",         0,          0x1000,  0},   \
    {FAL_PART_MAGIC_WORD,        "aprom",     "OnChip_APROM",         0xF0000,    0x10000, 0},   \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
