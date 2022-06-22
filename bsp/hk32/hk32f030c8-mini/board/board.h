/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-15     Jonas        first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <hk32f0xx.h>
#include "hk32_msp.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Just only support for HK32F030C8T6 */
#define HK32_FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define FLASH_PAGE_SIZE             (2 * 1024)
#define HK32_FLASH_SIZE             (64 * 1024)
#define HK32_FLASH_END_ADDRESS      ((uint32_t)(HK32_FLASH_START_ADRESS + HK32_FLASH_SIZE))

/* Internal SRAM memory size[Kbytes] <10>, Default: 10*/
#define HK32_SRAM_SIZE      10
#define HK32_SRAM_END       (0x20000000 + HK32_SRAM_SIZE * 1024)

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

#define HEAP_END        HK32_SRAM_END

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
