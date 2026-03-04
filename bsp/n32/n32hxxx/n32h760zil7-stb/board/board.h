/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include "n32h76x_78x.h"
#include "n32h76x_78x_gpio.h"
#include "n32h76x_78x_exti.h"
#include "n32h76x_78x_usart.h"
#include "n32h76x_78x_dbg.h"
#include "n32h76x_78x_pwr.h"
#include "n32h76x_78x_cfg.h"
#include "drv_common.h"
#include "drv_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define N32_FLASH_START_ADRESS     ((uint32_t)0x15000000)
#define N32_FLASH_SIZE             ((2 *1024 * 1024) - (128 * 1024))
#define N32_FLASH_END_ADDRESS      ((uint32_t)(N32_FLASH_START_ADRESS + N32_FLASH_SIZE))

#define N32_SRAM_SIZE              (128)
#define N32_SRAM_END               (0x24000000 + N32_SRAM_SIZE * 1024)

#if defined(__ARMCC_VERSION)
extern int Image$$RW_AXI_SRAM$$ZI$$Limit;
#define HEAP_BEGIN      (&Image$$RW_AXI_SRAM$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN      (&__bss_end)
#endif

#define HEAP_END        N32_SRAM_END

void System_Initialize(void);

#ifdef __cplusplus
}
#endif

#endif
