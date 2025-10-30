/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-12     BruceOu    the first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <registers.h>
#include <irq_numbers.h>

#include "imx91.h"
#include "rtconfig.h"

#if defined(__CC_ARM)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void*)&Image$$RW_IRAM1$$ZI$$Limit)
#elif defined(__GNUC__)
extern int __bss_end;
#define HEAP_BEGIN      ((void*)&__bss_end)
#endif

#ifndef KERNEL_VADDR_START
#define KERNEL_VADDR_START (ARCH_RAM_OFFSET + ARCH_TEXT_OFFSET)
#endif

#define HEAP_END        (void*)(HEAP_BEGIN + 32 * 1024 * 1024)
#define PAGE_START      HEAP_END
#define PAGE_END        ((size_t)PAGE_START + 128 * 1024 * 1024)

void rt_hw_board_init(void);

#endif
