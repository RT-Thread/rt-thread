/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-04-16     bigmagic       first version
 */

#ifndef BOARD_H__
#define BOARD_H__

#include <stdint.h>
#include "raspi4.h"
#include "mmu.h"
#include "ioremap.h"

extern int __bss_end;
#define HEAP_BEGIN      ((void*)&__bss_end)

#ifdef RT_USING_SMART
#define HEAP_END        ((size_t)KERNEL_VADDR_START + 32 * 1024 * 1024)
#define PAGE_START      HEAP_END
#define PAGE_END        ((size_t)KERNEL_VADDR_START + 128 * 1024 * 1024)
#else
#define KERNEL_VADDR_START 0x0

#define HEAP_END        (KERNEL_VADDR_START + 64 * 1024 * 1024)
#define PAGE_START      HEAP_END
#define PAGE_END        ((size_t)PAGE_START + 64 * 1024 * 1024)
#endif

void rt_hw_board_init(void);

#endif
