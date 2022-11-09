/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "n32g43x.h"
#include "drv_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define N32_FLASH_START_ADRESS      ((uint32_t)0x08000000)
#define N32_FLASH_SIZE              (128 * 1024)
#define N32_FLASH_END_ADDRESS       ((uint32_t)(N32_FLASH_START_ADRESS + N32_FLASH_SIZE))

/* Internal SRAM memory size[Kbytes] <32>, Default: 32 */
#define N32_SRAM_SIZE       (32)
#define N32_SRAM_END        (0x20000000 + N32_SRAM_SIZE * 1024)

void rt_hw_board_init(void);

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

