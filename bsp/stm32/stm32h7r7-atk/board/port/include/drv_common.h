/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-7      SummerGift   first version
 */

#ifndef __DRV_COMMON_H__

#define __DRV_COMMON_H__

#include <rtthread.h>
#include <rthw.h>
#include <board.h>
#include <stm32h7rsxx.h>

#ifdef __cplusplus
extern "C"
{
#endif

void _Error_Handler(void);

#ifndef Error_Handler
#define Error_Handler(msg) _Error_Handler(msg)
#endif

#define DMA_NOT_AVAILABLE ((DMA_INSTANCE_TYPE *)0xFFFFFFFFU)

#define __STM32_PORT(port)  GPIO##port##_BASE
#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__STM32_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x0400UL) )) + PIN)
#define STM32_FLASH_START_ADRESS       ROM_START
#define STM32_FLASH_SIZE               ROM_SIZE
#define STM32_FLASH_END_ADDRESS        ROM_END

#define STM32_SRAM1_SIZE               RAM_SIZE
#define STM32_SRAM1_START              RAM_START
#define STM32_SRAM1_END                RAM_END

#define STM32_PSRAM_SIZE               ((uint32_t)32*1024*1024)
#define STM32_PSRAM_START              ((uint32_t)0x90000000)
#define STM32_PSRAM_END                ((uint32_t)(STM32_PSRAM_START + STM32_PSRAM_SIZE))

#define PSRAM_HEAP_BEGIN               STM32_PSRAM_START
#define PSRAM_HEAP_SIZE                STM32_PSRAM_SIZE
#define PSRAM_HEAP_END                 STM32_PSRAM_END

#if defined(__CC_ARM) || defined(__CLANG_ARM) || defined(__ARMCC_VERSION)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN      ((void *)&__bss_end)
#endif

#define HEAP_END                       STM32_SRAM1_END
#ifdef __cplusplus
}
#endif

#endif
