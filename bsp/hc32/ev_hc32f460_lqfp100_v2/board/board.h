/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022, Xiaohua Semiconductor Co., Ltd.
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

#define HC32_SRAM_SIZE                  (188)
#define HC32_SRAM_END                   (0x1FFF8000 + HC32_SRAM_SIZE * 1024)

#ifdef __ARMCC_VERSION
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN                      (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN                      (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN                      (&__bss_end)
#endif

#define HEAP_END                        HC32_SRAM_END

#ifdef __cplusplus
}
#endif

#endif
