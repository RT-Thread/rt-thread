/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-15     shelton      first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <at32f4xx.h>
#include "at32_msp.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Internal SRAM memory size[Kbytes] <96>, Default: 96*/
#define AT32_SRAM_SIZE      96
#define AT32_SRAM_END       (0x20000000 + AT32_SRAM_SIZE * 1024)

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

#define HEAP_END        AT32_SRAM_END

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
