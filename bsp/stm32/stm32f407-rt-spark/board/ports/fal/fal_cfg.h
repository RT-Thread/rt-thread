/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-5      SummerGift   first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <board.h>
#include <fal_def.h>

#define FLASH_SIZE_GRANULARITY_16K   (4 * 16 * 1024)
#define FLASH_SIZE_GRANULARITY_64K   (8 * 64 * 1024)
#define FLASH_SIZE_GRANULARITY_128K  (8 * 128 * 1024)
#define STM32_FLASH_START_ADRESS_16K  STM32_FLASH_START_ADRESS
#define STM32_FLASH_START_ADRESS_64K  STM32_FLASH_START_ADRESS
#define STM32_FLASH_START_ADRESS_128K STM32_FLASH_START_ADRESS

extern const struct fal_flash_dev stm32_onchip_flash_16k;
extern const struct fal_flash_dev stm32_onchip_flash_64k;
extern const struct fal_flash_dev stm32_onchip_flash_128k;
extern struct fal_flash_dev w25q64;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &stm32_onchip_flash_128k,                                        \
    &w25q64,                                                        \
}

/* ====================== Partition Configuration ========================== */
#ifdef BSP_USING_BOOTLOADER
    #define FAL_PART_TABLE                                                                                              \
    {                                                                                                                   \
        {FAL_PART_MAGIC_WROD, "bootloader", "onchip_flash_128k",                             0,       128 * 1024, 0}, \
        {FAL_PART_MAGIC_WROD,        "app", "onchip_flash_128k",                    128 * 1024,       384 * 1024, 0}, \
        {FAL_PART_MAGIC_WROD,  "easyflash",    "W25Q64",                                    0,       512 * 1024, 0}, \
        {FAL_PART_MAGIC_WROD,   "download",    "W25Q64",                           512 * 1024,      1024 * 1024, 0}, \
        {FAL_PART_MAGIC_WROD, "wifi_image",    "W25Q64",                  (512 + 1024) * 1024,       512 * 1024, 0}, \
        {FAL_PART_MAGIC_WROD,       "font",    "W25Q64",            (512 + 1024 + 512) * 1024,  3 * 1024 * 1024, 0}, \
        {FAL_PART_MAGIC_WROD, "filesystem",    "W25Q64", (512 + 1024 + 512 + 3 * 1024) * 1024,  3 * 1024 * 1024, 0}, \
    }
#else
    #define FAL_PART_TABLE                                                                                              \
    {                                                                                                                   \
        {FAL_PART_MAGIC_WROD,        "app", "onchip_flash_128k",                            0,       384 * 1024, 0}, \
        {FAL_PART_MAGIC_WROD,      "param", "onchip_flash_128k",                   384 * 1024,       640 * 1024, 0}, \
        {FAL_PART_MAGIC_WROD,  "easyflash",    "W25Q64",                                    0,       512 * 1024, 0}, \
        {FAL_PART_MAGIC_WROD,   "download",    "W25Q64",                           512 * 1024,      1024 * 1024, 0}, \
        {FAL_PART_MAGIC_WROD, "wifi_image",    "W25Q64",                  (512 + 1024) * 1024,       512 * 1024, 0}, \
        {FAL_PART_MAGIC_WROD,       "font",    "W25Q64",            (512 + 1024 + 512) * 1024,  3 * 1024 * 1024, 0}, \
        {FAL_PART_MAGIC_WROD, "filesystem",    "W25Q64", (512 + 1024 + 512 + 3 * 1024) * 1024,  3 * 1024 * 1024, 0}, \
    }
#endif /*FAL_PART_TABLE*/
#endif /*BSP_USING_BOOTLOADER*/
