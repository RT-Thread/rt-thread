/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-08     QT-one       first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include "ht32.h"
#include "ht32_msp.h"

#ifdef BSP_USING_GPIO
    #include "drv_gpio.h"
#endif

#ifdef BSP_USING_SPI
    #include "drv_spi.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* whether use board external SRAM memory */
#define HT32_EXT_SRAM 0
#define HT32_EXT_SRAM_BEGIN 0x68000000
#define HT32_EXT_SRAM_END (HT32_EXT_SRAM_BEGIN + HT32_EXT_SRAM*1024)

/* internal sram memory size */
#define HT32_SRAM_END (0x20000000 + LIBCFG_RAM_SIZE)

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN  ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN  (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN  ((void *)&__bss_end)
#endif
#define HEAP_END    HT32_SRAM_END

void rt_hw_board_clock_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
