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

#include <rtthread.h>
#include <board.h>

#ifdef BSP_USING_SPI_FLASH_LITTLEFS
extern struct fal_flash_dev w25q128;
#else
#define FLASH_SIZE_GRANULARITY_16K   (4 * 16 * 1024)
#define FLASH_SIZE_GRANULARITY_64K   (64 * 1024)
#define FLASH_SIZE_GRANULARITY_128K  (7 * 128 * 1024)
#define STM32_FLASH_START_ADRESS_16K  STM32_FLASH_START_ADRESS
#define STM32_FLASH_START_ADRESS_64K  (STM32_FLASH_START_ADRESS_16K + FLASH_SIZE_GRANULARITY_16K)
#define STM32_FLASH_START_ADRESS_128K (STM32_FLASH_START_ADRESS_64K + FLASH_SIZE_GRANULARITY_64K)

extern const struct fal_flash_dev stm32_onchip_flash_16k;
extern const struct fal_flash_dev stm32_onchip_flash_64k;
extern const struct fal_flash_dev stm32_onchip_flash_128k;
#endif


/* flash device table */
#ifdef BSP_USING_SPI_FLASH_LITTLEFS
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &w25q128,                                                     \
}
#else
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &stm32_onchip_flash_16k,                                         \
    &stm32_onchip_flash_64k,                                         \
    &stm32_onchip_flash_128k,                                        \
}
#endif

/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG

/* partition table */
#ifdef BSP_USING_SPI_FLASH_LITTLEFS
#define FAL_PART_TABLE                                                                                                     \
{                                                                                                                          \
    {FAL_PART_MAGIC_WROD, "spiflash0", "W25Q128", 0 , 16 * 1024 * 1024, 0}, \
}
#else
#define FAL_PART_TABLE                                                                                                     \
{                                                                                                                          \
    {FAL_PART_MAGIC_WROD, "bootloader", "onchip_flash_16k",  0 , FLASH_SIZE_GRANULARITY_16K , 0}, \
    {FAL_PART_MAGIC_WROD, "param",      "onchip_flash_64k",  0 , FLASH_SIZE_GRANULARITY_64K , 0}, \
    {FAL_PART_MAGIC_WROD, "app",        "onchip_flash_128k", 0 , FLASH_SIZE_GRANULARITY_128K, 0}, \
}
#endif
#endif /* FAL_PART_HAS_TABLE_CFG */
#endif /* _FAL_CFG_H_ */
