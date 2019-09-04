/*
 * Copyright (c) 2015-2019, Leap Value IOT Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-08-16     flyu      first implementation
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include <stm32l1xx.h>
#include "drv_common.h"
#include "drv_gpio.h"

/* Internal SRAM memory size[Kbytes] <8-64>, Default: 64*/
#define STM32_SRAM_SIZE      32   // CB-A 32k, CB 16k
#define STM32_SRAM_END       (0x20000000 + STM32_SRAM_SIZE * 1024)

#ifdef __CC_ARM
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

#endif

