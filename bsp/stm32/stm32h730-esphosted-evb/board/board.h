/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-2-3     yekai   first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include <stm32h7xx.h>
#include "drv_common.h"
#include "drv_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define STM32_FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define STM32_FLASH_SIZE             (128 * 1024)
#define STM32_FLASH_END_ADDRESS      ((uint32_t)(STM32_FLASH_START_ADRESS + STM32_FLASH_SIZE))

#define STM32_SRAM_SIZE           (64*5)
#define STM32_SRAM_END            (0x24000000 + STM32_SRAM_SIZE * 1024)

#if defined(__ARMCC_VERSION)
// use IRAM2(RAM D1)
extern int Image$$RW_IRAM2$$ZI$$Limit;
#define HEAP_BEGIN      (&Image$$RW_IRAM2$$ZI$$Limit)
#define HEAP_END        STM32_SRAM_END
#elif defined(__GNUC__)
extern uint8_t _heap_start[];
extern uint8_t _heap_end[];
#define HEAP_BEGIN      _heap_start
#define HEAP_END        _heap_end
#endif

void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif
