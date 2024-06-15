/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-5      SummerGift   first version
 * 2023-08-20     Donocean     Set STM32_SRAM_SIZE to 128 and heap addr on 0x10000000
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <stm32f4xx.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STM32_FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define STM32_FLASH_SIZE             (1024 * 1024)
#define STM32_FLASH_END_ADDRESS      ((uint32_t)(STM32_FLASH_START_ADRESS + STM32_FLASH_SIZE))

#define STM32_SRAM_SIZE           128
#define STM32_SRAM_END            (0x20000000 + STM32_SRAM_SIZE * 1024)

#define HEAP_BEGIN 0x10000000
#define HEAP_END   (HEAP_BEGIN + 0x00010000)


void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif

