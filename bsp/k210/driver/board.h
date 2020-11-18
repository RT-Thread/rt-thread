/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-5-30      Bernard      the first version
 */

#ifndef BOARD_H__
#define BOARD_H__

#include <rtconfig.h>

#if PKG_KENDRYTE_SDK_VERNUM < 0x0054
#error The version of Kendryte sdk is too old, please update to V0.5.4 or newer
#endif

extern unsigned int __bss_start;
extern unsigned int __bss_end;

#define RT_HW_HEAP_BEGIN    (void*)&__bss_end
#define RT_HW_HEAP_END      (void*)(0x80000000 + 6 * 1024 * 1024)

void rt_hw_board_init(void);

#endif
