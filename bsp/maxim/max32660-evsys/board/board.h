/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-11     supperthomas first version
 *
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include <rtthread.h>
#include <rthw.h>

#include "mxc_config.h"
#include "mxc_assert.h"


#define MCU_FLASH_START_ADRESS       ((uint32_t)0x0)
#define MCU_FLASH_SIZE_KB               (256)
#define MCU_FLASH_END_ADDRESS        ((uint32_t)(MCU_FLASH_START_ADRESS + MCU_FLASH_SIZE*1024))

#define MCU_SRAM_SIZE_KB               (96)
#define MCU_SRAM_START              (0x20000000)
#define MCU_SRAM_END                (MCU_SRAM_START + MCU_SRAM_SIZE_KB * 1024)

#if defined(__ARMCC_VERSION)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int _ebss;
#define HEAP_BEGIN      ((void *)&_ebss)
#endif

#define HEAP_END       MCU_SRAM_END

void rt_hw_board_init(void);

#endif

