/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     breo.com     first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <n32g45x.h>
#include "n32_msp.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Just only support for N32G452XX */
#define N32_FLASH_START_ADRESS      ((uint32_t)0x08000000)
#define FLASH_PAGE_SIZE             (2 * 1024)
#define N32_FLASH_SIZE              (256 * 1024)
#define N32_FLASH_END_ADDRESS       ((uint32_t)(N32_FLASH_START_ADRESS + N32_FLASH_SIZE))

/* Internal SRAM memory size[Kbytes] <80>, Default: 80*/
#define N32_SRAM_SIZE       (144)
#define N32_SRAM_END        (0x20000000 + N32_SRAM_SIZE * 1024)

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

#define HEAP_END        N32_SRAM_END

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
