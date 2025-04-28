/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef MEMORY_LAYOUT_H__
#define MEMORY_LAYOUT_H__

#include "../rtconfig.h"

/* Real start address of kernel is located after bootloader */
#define KERNEL_OFFSET 0x200000

#ifdef RT_USING_SMART
#define KERNEL_START (KERNEL_VADDR_START + KERNEL_OFFSET)
#define KERNEL_SIZE    64 * 1024 * 1024
#else
#define KERNEL_START (0x80000000 + KERNEL_OFFSET)
#define KERNEL_SIZE    32 * 1024 * 1024
#endif

#endif // MEMORY_LAYOUT_H__