/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-22     quanzhao     first version
 */

.data
#define DEVICE_MEM  0x10c06
#define NORMAL_MEM  0x11c0e
.align 14
.globl platform_mmap_table
platform_mmap_table:
	//vaddr: 0x00000000
	.equ mmu_tbl_map_paddr, 0x00000000
	.rept 0x800
	.word mmu_tbl_map_paddr | DEVICE_MEM
	.equ mmu_tbl_map_paddr, mmu_tbl_map_paddr + 0x100000
	.endr

	//vaddr: 0x80000000
	.equ mmu_tbl_map_paddr, 0x80000000
	.rept 0x800
	.word mmu_tbl_map_paddr | NORMAL_MEM
	.equ mmu_tbl_map_paddr, mmu_tbl_map_paddr + 0x100000
	.endr

