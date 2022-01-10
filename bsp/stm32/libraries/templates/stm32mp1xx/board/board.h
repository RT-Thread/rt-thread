/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-5      SummerGift   first version
 * 2019-04-09     WillianChan  add stm32f469-st-disco bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include "stm32mp1xx.h"
#include "stm32mp1xx_hal.h"
#include "drv_common.h"
#include "drv_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define STM32_FLASH_START_ADRESS     ((uint32_t)0x10000000)
#define STM32_FLASH_SIZE             (256 * 1024)
#define STM32_FLASH_END_ADDRESS      ((uint32_t)(STM32_FLASH_START_ADRESS + STM32_FLASH_SIZE))

#define STM32_SRAM_SIZE           (128)
#define STM32_SRAM_END            ((uint32_t)0x10040000 + (STM32_SRAM_SIZE * 1024))

#if defined(__ARMCC_VERSION)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end__;
#define HEAP_BEGIN       (0x10040000 + 64 * 1024)
#endif

#define HEAP_END        STM32_SRAM_END

void SystemClock_Config(void);

extern void _Error_Handler(char *s, int num);

#ifdef __cplusplus
}
#endif

#endif

