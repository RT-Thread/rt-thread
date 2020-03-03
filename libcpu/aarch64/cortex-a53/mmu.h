/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author             Notes
 * 2020-02-20     bigmagic           first version
 */

#ifndef  __MMU_H__
#define  __MMU_H__

#define MMU_LEVEL_MASK 0x1ffUL
#define MMU_MAP_ERROR_VANOTALIGN  -1
#define MMU_MAP_ERROR_PANOTALIGN  -2
#define MMU_MAP_ERROR_NOPAGE      -3
#define MMU_MAP_ERROR_CONFLICT    -4

#define MEM_ATTR_MEMORY ((0x1UL << 10) | (0x2UL << 8) | (0x0UL << 6) | (0x1UL << 2))
#define MEM_ATTR_IO     ((0x1UL << 10) | (0x2UL << 8) | (0x0UL << 6) | (0x2UL << 2))

#define BUS_ADDRESS(phys)	(((phys) & ~0xC0000000)  |  0xC0000000)

void mmu_init(void);

void mmu_enable(void);

int armv8_map_2M(unsigned long va, unsigned long pa, int count, unsigned long attr);

void armv8_map(unsigned long va, unsigned long pa, unsigned long size, unsigned long attr);

#endif  /*__MMU_H__*/
