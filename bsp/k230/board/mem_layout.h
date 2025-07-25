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
 * +---------+ <- End of Kerenl
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
 * configuration, otherwise the default configuration of bsp/k230 in RT-Thead
 * is used. The default configuration of bsp/k230 is for the 01Studio CanMV
 * development board that supports 512MB of memory.
 */
#ifndef CONFIG_MEM_TOTAL_SIZE
#define CONFIG_MEM_TOTAL_SIZE	0x20000000 // 512M
#endif

#ifndef CONFIG_MEM_RTSMART_SIZE
#define CONFIG_MEM_RTSMART_SIZE	0x10000000 // 256M
#endif

#ifndef CONFIG_MEM_RTSMART_HEAP_SIZE
#define CONFIG_MEM_RTSMART_HEAP_SIZE	0x2000000 // 32M
#endif

#ifndef CONFIG_MEM_MMZ_BASE
#define CONFIG_MEM_MMZ_BASE	0x10000000 // 512M
#endif

#ifndef CONFIG_MEM_MMZ_SIZE
#define CONFIG_MEM_MMZ_SIZE	0x10000000 // 256M
#endif

#define MEM_KERNEL_SIZE (CONFIG_MEM_RTSMART_SIZE - MEM_OPENSBI_SIZE - MEM_GUARD_SIZE)

#endif // MEMORY_LAYOUT_H__