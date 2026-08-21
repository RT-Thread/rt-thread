/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-02-12      yeml    first version
 */

 #ifndef __BOARD_H__
 #define __BOARD_H__
 
 #include <rtthread.h>
 #include "tae32g58xx_ll.h"
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
#define TAE32_FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define TAE32_FLASH_SIZE             (32 * 8192)
#define TAE32_FLASH_END_ADDRESS      ((uint32_t)(TAE32_FLASH_START_ADRESS + TAE32_FLASH_SIZE))

#define TAE32_SRAM_SIZE           128
#define TAE32_SRAM_END            (0x20000000 + TAE32_SRAM_SIZE * 1024)
 
#if defined(__ARMCC_VERSION)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN      (&__bss_end)
#endif

#define HEAP_END        (TAE32_SRAM_END - 0x800)
 
 void SystemClock_Config(void);
 int rt_hw_usart_init(void);
 #ifdef __cplusplus
 }
 #endif
 
 #endif
 
 