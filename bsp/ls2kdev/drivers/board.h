/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-05     bigmagic     the first version
 */

#ifndef BOARD_H__
#define BOARD_H__

#include <stdint.h>

extern unsigned char __bss_end;

#define CPU_HZ              (1000 * 1000 * 1000) //QEMU 200*1000*1000
#define RT_HW_HEAP_BEGIN    (void*)&__bss_end
#define RT_HW_HEAP_END      (void*)(RT_HW_HEAP_BEGIN + 64 * 1024 * 1024)

void rt_hw_board_init(void);

#endif
