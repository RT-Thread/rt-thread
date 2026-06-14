/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-10-15     IronsideZhang     first version
 */

#ifndef MEM_LAYOUT_H__
#define MEM_LAYOUT_H__

#include <rtconfig.h>

/*
 * K1 Physical Memory layout:
 * Based on MUSE-Pi-Pro board with 8GB RAM.
 *
 * +------------------+ <- RAM_END (8GB)
 * |                  |
 * |      Page Pool   | (for RT-Smart in Phase 3)
 * |                  |
 * +------------------+ <- HEAP_END
 * |                  |
 * |   Kernel Heap    | KERNEL_HEAP_SIZE
 * |                  |
 * +------------------+ <- HEAP_BEGIN (__bss_end)
 * |       .bss       |
 * +------------------+
 * |       .data      |
 * +------------------+
 * |       .text      |
 * +------------------+ <- KERNEL_BASE
 * |     (U-Boot)     |
 * +------------------+
 */


#define K1_MEM_TOTAL_SIZE           (8 * 1024 *1024)
#define KERNEL_HEAP_SIZE            (32 * 1024 * 1024)

#endif // MEM_LAYOUT_H__