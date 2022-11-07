/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2022-10-26  huanghe      first commit
 *
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "fparameters.h"
#include "phytium_cpu.h"

#if defined(__CC_ARM)
    extern int Image$$RW_IRAM1$$ZI$$Limit;
    #define HEAP_BEGIN ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif defined(__GNUC__)
    extern int __bss_end;
    #define HEAP_BEGIN ((void *)&__bss_end)
#endif

#define HEAP_END (void *)(0x80000000 + 1024 * 1024 * 1024)

void rt_hw_board_init(void);

#endif
