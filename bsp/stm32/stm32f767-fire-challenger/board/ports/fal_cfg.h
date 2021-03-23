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

#define FLASH_SIZE_GRANULARITY_32K   (4 * 32 * 1024)
#define FLASH_SIZE_GRANULARITY_128K  (128 * 1024)
#define FLASH_SIZE_GRANULARITY_256K  (3 * 256 * 1024)

#define STM32_FLASH_START_ADRESS_32K  STM32_FLASH_START_ADRESS
#define STM32_FLASH_START_ADRESS_128K (STM32_FLASH_START_ADRESS_32K + FLASH_SIZE_GRANULARITY_32K)
#define STM32_FLASH_START_ADRESS_256K (STM32_FLASH_START_ADRESS_128K + FLASH_SIZE_GRANULARITY_128K)

extern const struct fal_flash_dev stm32_onchip_flash_32k;
extern const struct fal_flash_dev stm32_onchip_flash_128k;
extern const struct fal_flash_dev stm32_onchip_flash_256k;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &stm32_onchip_flash_32k,                                         \
    &stm32_onchip_flash_128k,                                        \
    &stm32_onchip_flash_256k,                                        \
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG

/* partition table */
#define FAL_PART_TABLE                                                                                                     \
{                                                                                                                          \
    {FAL_PART_MAGIC_WROD, "bootloader", "onchip_flash_32k",  0 , FLASH_SIZE_GRANULARITY_32K , 0}, \
    {FAL_PART_MAGIC_WROD, "param",      "onchip_flash_128k", 0 , FLASH_SIZE_GRANULARITY_128K, 0}, \
    {FAL_PART_MAGIC_WROD, "app",        "onchip_flash_256k", 0 , FLASH_SIZE_GRANULARITY_256K, 0}, \
}

#endif /* FAL_PART_HAS_TABLE_CFG */
#endif /* _FAL_CFG_H_ */
