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

#define APP_START_ADDR              (0)
#define APP_SIZE                    (128*1024)
#define PARAM_START_ADDR            (APP_START_ADDR+APP_SIZE)
#define PARAM_SIZE                  (64*1024)
#define DOWNLOAD_START_ADDR         (PARAM_START_ADDR+PARAM_SIZE)
#define DOWNLOAD_SIZE               (APP_SIZE)
#define FONT_START_ADDR             (DOWNLOAD_START_ADDR+DOWNLOAD_SIZE)
#define FONT_SIZE                   (64*1024)
#define FILESYSTEM_ADDR             (FONT_START_ADDR+FONT_SIZE)
#define FILESYSTEM_SIZE             (128*1024)
/* partition table */
#define FAL_PART_TABLE                                                                                              \
{                                                                                                                   \
    {FAL_PART_MAGIC_WROD,        "app",    "onchip_flash",    APP_START_ADDR,           APP_SIZE, 0}, \
    {FAL_PART_MAGIC_WROD,      "param",    "onchip_flash",    PARAM_START_ADDR,         PARAM_SIZE, 0}, \
    {FAL_PART_MAGIC_WROD,   "download",    "onchip_flash",    DOWNLOAD_START_ADDR,      DOWNLOAD_SIZE, 0}, \
    {FAL_PART_MAGIC_WROD,       "font",    "onchip_flash",    FONT_START_ADDR,          FONT_SIZE, 0}, \
    {FAL_PART_MAGIC_WROD, "filesystem",    "onchip_flash",    FILESYSTEM_ADDR,          FILESYSTEM_SIZE, 0}, \
}

#endif /* FAL_PART_HAS_TABLE_CFG */
#endif /* _FAL_CFG_H_ */
