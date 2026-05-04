/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef MEMORY_LAYOUT_H__
#define MEMORY_LAYOUT_H__

#include "../rtconfig.h"

/*
 * Physical Memory layout:
 *
 * +---------+ <- CONFIG_MEM_TOTAL_SIZE
 * | ......  | maybe zero
 * +---------+ <- CONFIG_MEM_MMZ_BASE + CONFIG_MEM_MMZ_SIZE
 * |         |
 * |         |
 * |         |
 * |         |
 * |         |
 * |         |
 * |         |
 * |         |
 * |---------| <- CONFIG_MEM_MMZ_BASE
 * | ......  | maybe zero
 * +---------+ <- CONFIG_MEM_RTSMART_SIZE
 * | guard   | MEM_GUARD_SIZE
 * +---------+ <- End of Kernel
 * |         |
 * |         |
 * +---------+
 * | heap    | CONFIG_MEM_RTSMART_HEAP_SIZE
 * +---------+
 * |         |
 * +---------+ <- Beginning of Kernel <- mapping to KERNEL_VADDR_START + MEM_OPENSBI_SIZE
 * | opensbi | MEM_OPENSBI_SIZE
 * +---------+ <- Beginning of Physical Memory (0)  <- mapping to KERNEL_VADDR_START
 */

#define MEM_OPENSBI_SIZE	0x20000	// 128K
#define MEM_GUARD_SIZE		0x1000	// 4K

/*
 * The value of CONFIG_XXX may come from rtconfig.h. This is mainly for
 * compatibility with compiling RT-Thread in the SDK environment and using
 * the SDK configuration.
 *
 * If CONFIG_XXX is defined, it means that the value comes from the SDK
 * configuration, otherwise the default configuration defined in this file
 * is used.
 */

#if defined(SOC_K230D)
/*
 * ATK-DNK230D: 128MB DDR
 *
 * +---------+ <- 0x8000000 (128MB)
 * | MMZ     | CONFIG_MEM_MMZ_SIZE = 0x4600000 (70MB)
 * +---------+ <- CONFIG_MEM_MMZ_BASE = 0x3A00000 (58MB)
 * | heap    | CONFIG_MEM_RTSMART_HEAP_SIZE = 0x800000 (8MB)
 * +---------+
 * | kernel  | CONFIG_MEM_RTSMART_SIZE - MEM_OPENSBI_SIZE - MEM_GUARD_SIZE - heap
 * +---------+ <- CONFIG_MEM_RTSMART_BASE + MEM_OPENSBI_SIZE (128KB)
 * | opensbi | MEM_OPENSBI_SIZE = 0x20000 (128KB)
 * +---------+ <- 0x0
 */
#ifndef CONFIG_MEM_TOTAL_SIZE
#define CONFIG_MEM_TOTAL_SIZE	0x8000000 // 128M
#endif

#ifndef CONFIG_MEM_RTSMART_SIZE
#define CONFIG_MEM_RTSMART_SIZE	0x3A00000 // 58M
#endif

#ifndef CONFIG_MEM_RTSMART_HEAP_SIZE
#define CONFIG_MEM_RTSMART_HEAP_SIZE	0x800000 // 8M
#endif

#ifndef CONFIG_MEM_MMZ_BASE
#define CONFIG_MEM_MMZ_BASE	0x3A00000 // 58M
#endif

#ifndef CONFIG_MEM_MMZ_SIZE
#define CONFIG_MEM_MMZ_SIZE	0x4600000 // 70M
#endif

#elif defined(SOC_K230)
/*
 * K230: default memory configuration
 *
 * The K230 chip supports different DDR sizes (256MB, 512MB, 1GB, 2GB).
 * Override the CONFIG_MEM_XXX values in rtconfig.h or SDK configuration
 * to match your board's actual DDR size.
 */
#ifndef CONFIG_MEM_TOTAL_SIZE
#define CONFIG_MEM_TOTAL_SIZE	0x8000000 // 128M
#endif

#ifndef CONFIG_MEM_RTSMART_SIZE
#define CONFIG_MEM_RTSMART_SIZE	0x3A00000 // 58M
#endif

#ifndef CONFIG_MEM_RTSMART_HEAP_SIZE
#define CONFIG_MEM_RTSMART_HEAP_SIZE	0x800000 // 8M
#endif

#ifndef CONFIG_MEM_MMZ_BASE
#define CONFIG_MEM_MMZ_BASE	0x3A00000 // 58M
#endif

#ifndef CONFIG_MEM_MMZ_SIZE
#define CONFIG_MEM_MMZ_SIZE	0x4600000 // 70M
#endif

#else
#error "Either SOC_K230 or SOC_K230D must be defined"
#endif

#define MEM_KERNEL_SIZE (CONFIG_MEM_RTSMART_SIZE - MEM_OPENSBI_SIZE - MEM_GUARD_SIZE)

#endif // MEMORY_LAYOUT_H__
