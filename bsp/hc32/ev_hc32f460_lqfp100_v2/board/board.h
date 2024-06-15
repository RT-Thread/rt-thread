/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include "hc32_ll.h"
#include "drv_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif


#define HC32_FLASH_SIZE_GRANULARITY     (8 * 1024)
#define HC32_FLASH_SIZE                 (512 * 1024)
#define HC32_FLASH_START_ADDRESS        (0)
#define HC32_FLASH_END_ADDRESS          (HC32_FLASH_START_ADDRESS + HC32_FLASH_SIZE)

#define HC32_SRAM_SIZE                  (188)
#define HC32_SRAM_END                   (0x1FFF8000 + HC32_SRAM_SIZE * 1024)

#ifdef __ARMCC_VERSION
extern int Image$$RW_IRAM2$$ZI$$Limit;
#define HEAP_BEGIN                      (&Image$$RW_IRAM2$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN                      (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN                      (&__bss_end)
#endif

#define HEAP_END                        HC32_SRAM_END

void PeripheralRegister_Unlock(void);
void PeripheralClock_Config(void);
void SystemBase_Config(void);
void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif
