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

#include <fal.h>
#include "drv_fmc.h"
#include "rtconfig.h"

/* ===================== Flash device Configuration ========================= */
#if defined(FAL_PART_HAS_TABLE_CFG)

/* ---------------- FMC ---------------- */
#if defined(BSP_USING_FMC)
#define IFDEF_BOARD_USING_FMC   &g_falFMC_AP, &g_falFMC_LD, &g_falFMC_DF,
#define FAL_PART_FMC  \
            {FAL_PART_MAGIC_WORD, "ldrom",     "FMC_LD",  0x0,    (8*1024),   0},  \
            {FAL_PART_MAGIC_WORD, "aprom",     "FMC_AP",  0x0,    (512*1024), 0},  \
            {FAL_PART_MAGIC_WORD, "dataflash", "FMC_DF",  0x0,    (4*1024),   0},
#else
#define IFDEF_BOARD_USING_FMC
#define FAL_PART_FMC
#endif

/* ---------------- QSPI ---------------- */
#if defined(BOARD_USING_QSPI_FLASH) || defined(BOARD_USING_NUFUN_QSPI_FLASH)
extern struct fal_flash_dev        nor_flash0;
#define IFDEF_BOARD_USING_QSPI     &nor_flash0,
#define FAL_PART_QSPI \
            {FAL_PART_MAGIC_WORD, "filesystem", FAL_USING_NOR_FLASH_DEV_NAME, 0, (2 * 1024 * 1024), 0},
#else
#define IFDEF_BOARD_USING_QSPI
#define FAL_PART_QSPI
#endif

/* ---------------- Device Table ---------------- */
#if defined(BSP_USING_FMC) || defined(BOARD_USING_QSPI_FLASH) || defined(BOARD_USING_NUFUN_QSPI_FLASH)
#define FAL_FLASH_DEV_TABLE     \
        {                               \
            IFDEF_BOARD_USING_FMC       \
            IFDEF_BOARD_USING_QSPI      \
        }
#else
#define FAL_FLASH_DEV_TABLE { }
#endif

/* ---------------- Partition Table ---------------- */
#if defined(BSP_USING_FMC) || defined(BOARD_USING_QSPI_FLASH) || defined(BOARD_USING_NUFUN_QSPI_FLASH)
#define FAL_PART_TABLE          \
        {                               \
            FAL_PART_FMC                \
            FAL_PART_QSPI               \
        }
#else
#define FAL_PART_TABLE { }
#endif

#else   /* !FAL_PART_HAS_TABLE_CFG */

#define FAL_FLASH_DEV_TABLE  { }
#define FAL_PART_TABLE  { }

#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
