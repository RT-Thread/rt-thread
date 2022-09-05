/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-02-16     Tuber             first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "CH57x_common.h"

#define CH579M_FLASH_START_ADRESS     ((uint32_t)0x00000000)
#define FLASH_PAGE_SIZE             (64)
#define CH579M_FLASH_SIZE             (512 * 1024)
#define CH579M_FLASH_END_ADDRESS      ((uint32_t)(CH579M_FLASH_START_ADRESS + CH579M_FLASH_SIZE))

#define CH579M_SRAM_SIZE      32
#define CH579M_SRAM_END       (0x20000000 + CH579M_SRAM_SIZE * 1024)

#if defined(__ARMCC_VERSION)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN      ((void *)&__bss_end)
#endif

#define HEAP_END        CH579M_SRAM_END

#endif /* __BOARD_H__ */
