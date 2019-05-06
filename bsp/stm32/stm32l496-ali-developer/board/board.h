/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-5      SummerGift   change to new framework
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include <stm32l4xx.h>
#include "drv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_GPIO
#include "drv_gpio.h"

/* Board Pin definitions */
#define LED1_PIN                       GET_PIN(B, 6)
#define LED2_PIN                       GET_PIN(E, 3)
#define LED3_PIN                       GET_PIN(D, 15)
#define KEY1_PIN                       GET_PIN(E, 11)
#define KEY2_PIN                       GET_PIN(E, 14)
#define KEY3_PIN                       GET_PIN(E, 10)
#endif /* BSP_USING_GPIO */

/* Internal SRAM memory size[Kbytes] <8-64>, Default: 64*/
#define STM32_SRAM_SIZE      320
#define STM32_SRAM_END       (0x20000000 + STM32_SRAM_SIZE * 1024)

#define STM32_FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define STM32_FLASH_SIZE             (1024 * 1024)
#define STM32_FLASH_END_ADDRESS      ((uint32_t)(STM32_FLASH_START_ADRESS + STM32_FLASH_SIZE))

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN      ((void *)&__bss_end)
#endif

#define HEAP_END        STM32_SRAM_END

void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif

