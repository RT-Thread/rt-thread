/*
 * File      : fal_cfg.h
 * COPYRIGHT (C) 2012-2018, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtconfig.h>
#include <board.h>

/* ===================== Flash device Configuration ========================= */
extern struct fal_flash_dev nor_flash0;

#define RT_FAL_BL_PART_LEN              (256*1024)
#define RT_FAL_ENV_PART_LEN             (1*1024)
#define RT_FAL_PT_PART_LEN              (1*1024)
#define RT_FAL_APP_PART_LEN             (1*1024*1024)
#define RT_FAL_DL_PART_LEN              (1*1024*1024)

#define RT_FAL_FLASH_BASE               0
#define RT_FAL_BL_PART_OFFSET           RT_FAL_FLASH_BASE
#define RT_FAL_ENV_PART_OFFSET          (RT_FAL_BL_PART_OFFSET  + RT_FAL_BL_PART_LEN)
#define RT_FAL_PT_PART_OFFSET           (RT_FAL_ENV_PART_OFFSET + RT_FAL_ENV_PART_LEN)
#define RT_FAL_APP_PART_OFFSET          (RT_FAL_PT_PART_OFFSET  + RT_FAL_PT_PART_LEN)
#define RT_FAL_DL_PART_OFFSET           (RT_FAL_APP_PART_OFFSET + RT_FAL_APP_PART_LEN)
#define RT_FAL_FS_PART_OFFSET           (RT_FAL_DL_PART_OFFSET  + RT_FAL_DL_PART_LEN)

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &nor_flash0,                                                     \
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                          \
{                                                                               \
    {FAL_PART_MAGIC_WROD,       "bl",   "norflash0",  RT_FAL_BL_PART_OFFSET,   RT_FAL_BL_PART_LEN, 0}, \
    {FAL_PART_MAGIC_WROD,      "env",   "norflash0", RT_FAL_ENV_PART_OFFSET,  RT_FAL_ENV_PART_LEN, 0}, \
    {FAL_PART_MAGIC_WROD,       "pt",   "norflash0",  RT_FAL_PT_PART_OFFSET,   RT_FAL_PT_PART_LEN, 0}, \
    {FAL_PART_MAGIC_WROD,      "app",   "norflash0", RT_FAL_APP_PART_OFFSET,  RT_FAL_APP_PART_LEN, 0}, \
    {FAL_PART_MAGIC_WROD, "download",   "norflash0",  RT_FAL_DL_PART_OFFSET,   RT_FAL_DL_PART_LEN, 0}, \
    {FAL_PART_MAGIC_WROD,       "fs",   "norflash0",  RT_FAL_FS_PART_OFFSET,                    0, 0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
