/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-15     shelton      first version
 * 2021-02-09     shelton      add flash macros
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include <at32f435_437.h>
#include <at32f435_437_conf.h>

#include "drv_common.h"
#include "drv_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Just only support for AT32F435 */
#define AT32_FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define FLASH_PAGE_SIZE             (4 * 1024)
#define AT32_FLASH_SIZE             (1024 * 1024)
#define AT32_FLASH_END_ADDRESS      ((uint32_t)(AT32_FLASH_START_ADRESS + AT32_FLASH_SIZE))

/* Internal SRAM memory size[Kbytes] <384>, Default: 384*/
#define AT32_SRAM1_SIZE      384
#define AT32_SRAM1_START     (0x20000000)
#define AT32_SRAM1_END       (AT32_SRAM1_START + AT32_SRAM1_SIZE * 1024)

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end__;
#define HEAP_BEGIN      ((void *)&__bss_end__)
#endif

#define HEAP_END        AT32_SRAM1_END

void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
