/*
 * File      : fal_cfg.h
 * COPYRIGHT (C) 2012-2018, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-21     MurphyZhao   the first version
 */
#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtthread.h>
#include <board.h>

/* enable yc3122 onchip flash driver sample */
#define FAL_FLASH_PORT_DRIVER_YC3122
/* enable SFUD flash driver sample */
//#define FAL_FLASH_PORT_DRIVER_SFUD

extern const struct fal_flash_dev yc3122_onchip_flash;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &yc3122_onchip_flash,                                           \
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                                                              \
{                                                                                                                   \
    {FAL_PART_MAGIC_WROD,        "app", "onchip_flash",                                    0,       128 * 1024, 0}, \
    {FAL_PART_MAGIC_WROD,  "easyflash", "onchip_flash",                           (128+32) * 1024,   64 * 1024, 0}, \
    {FAL_PART_MAGIC_WROD,   "download", "onchip_flash",                           (128+32+64) * 1024,  128 * 1024, 0}, \
    {FAL_PART_MAGIC_WROD,       "font", "onchip_flash",            (128+32+64+128+32) * 1024, 64 * 1024, 0}, \
    {FAL_PART_MAGIC_WROD, "filesystem", "onchip_flash", (128+32+64+128+32+64) * 1024, 64 * 1024, 0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */
#endif /* _FAL_CFG_H_ */
