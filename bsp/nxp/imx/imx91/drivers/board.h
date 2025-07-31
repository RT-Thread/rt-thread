/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-10     Siwei Xu     Add i.MX91 SDK
 * 2025-09-15     Siwei Xu     Fix LPUART driver
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "imx91.h"
#include "rtconfig.h"

extern int __bss_end;
#define HEAP_BEGIN      ((void*)&__bss_end)

#ifndef KERNEL_BOOT_ADDR
#define KERNEL_BOOT_ADDR (ARCH_RAM_OFFSET + ARCH_TEXT_OFFSET)
#endif

#define HEAP_END        ((void*)((char*) HEAP_BEGIN + 32 * 1024 * 1024))
#define PAGE_START      ((size_t)HEAP_END)
#define PAGE_END        ((size_t)PAGE_START + 128 * 1024 * 1024)

void rt_hw_board_init(void);

#endif
