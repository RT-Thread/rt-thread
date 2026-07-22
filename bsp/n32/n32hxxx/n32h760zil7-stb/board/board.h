/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 * 2026-07-13     ox-horse         Modify SRAM_SIZE and HEAP_BEGIN
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include "n32h7xx_cfg.h"
#include "n32h7xx_exti.h"
#include "misc.h"
#include "n32h7xx_mmu.h"
#include "n32h7xx_dma.h"
#include "n32h7xx_dmamux.h"
#include "n32h7xx_pwr.h"
#include "n32h7xx_dbg.h"
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
#define HEAP_BEGIN (&Image$$RW_AXI_SRAM$$ZI$$Limit)
#else
extern int _app_estack;
#define HEAP_BEGIN (&_app_estack)
#endif

#define HEAP_END        N32_SRAM_END

void System_Initialize(void);

#ifdef __cplusplus
}
#endif

#endif
