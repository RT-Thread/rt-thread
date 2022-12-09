/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 * 2021-05-03     lizhirui     porting to c906
 */

#ifndef __RISCV_MMU_H__
#define __RISCV_MMU_H__

#include <rthw.h>
#include <rtthread.h>
#include "riscv.h"

#undef PAGE_SIZE

/* C-SKY extend */
#define PTE_SEC   (1UL << 59)   /* Security */
#define PTE_SHARE (1UL << 60)   /* Shareable */
#define PTE_BUF   (1UL << 61)   /* Bufferable */
#define PTE_CACHE (1UL << 62)   /* Cacheable */
#define PTE_SO    (1UL << 63)   /* Strong Order */

#define PAGE_OFFSET_SHIFT 0
#define PAGE_OFFSET_BIT 12
#define PAGE_SIZE __SIZE(PAGE_OFFSET_BIT)
#define PAGE_OFFSET_MASK __MASK(PAGE_OFFSET_BIT)
#define VPN0_SHIFT (PAGE_OFFSET_SHIFT + PAGE_OFFSET_BIT)
#define VPN0_BIT 9
#define VPN1_SHIFT (VPN0_SHIFT + VPN0_BIT)
#define VPN1_BIT 9
#define VPN2_SHIFT (VPN1_SHIFT + VPN1_BIT)
#define VPN2_BIT 9

#define PPN0_SHIFT (PAGE_OFFSET_SHIFT + PAGE_OFFSET_BIT)
#define PPN0_BIT 9
#define PPN1_SHIFT (PPN0_SHIFT + PPN0_BIT)
#define PPN1_BIT 9
#define PPN2_SHIFT (PPN1_SHIFT + PPN1_BIT)
#define PPN2_BIT 26

#define L1_PAGE_SIZE __SIZE(PAGE_OFFSET_BIT + VPN0_BIT + VPN1_BIT)
#define L2_PAGE_SIZE __SIZE(PAGE_OFFSET_BIT + VPN0_BIT)
#define L3_PAGE_SIZE __SIZE(PAGE_OFFSET_BIT)

#define ARCH_ADDRESS_WIDTH_BITS 64

#define PHYSICAL_ADDRESS_WIDTH_BITS 56

#define PAGE_ATTR_NEXT_LEVEL (0)
#define PAGE_ATTR_RWX (PTE_X | PTE_W | PTE_R)
#define PAGE_ATTR_READONLY (PTE_R)
#define PAGE_ATTR_READEXECUTE (PTE_X | PTE_R)

#define PAGE_ATTR_USER (PTE_U)
#define PAGE_ATTR_SYSTEM (0)

#define PAGE_DEFAULT_ATTR_LEAF (PAGE_ATTR_RWX | PAGE_ATTR_USER | PTE_V | PTE_G | PTE_SHARE | PTE_BUF | PTE_CACHE | PTE_A | PTE_D)
#define PAGE_DEFAULT_ATTR_NEXT (PAGE_ATTR_NEXT_LEVEL | PTE_V | PTE_G | PTE_SHARE | PTE_BUF | PTE_CACHE | PTE_A | PTE_D)

#define PAGE_IS_LEAF(pte) __MASKVALUE(pte,PAGE_ATTR_RWX)

#define PTE_USED(pte) __MASKVALUE(pte,PTE_V)

#define mmu_flush_tlb() do{asm volatile("sfence.vma x0,x0");}while(0)

//compatible to rt-smart new version
#define MMU_MAP_K_DEVICE (PAGE_ATTR_RWX | PTE_V | PTE_G | PTE_SO | PTE_BUF | PTE_A | PTE_D)
#define MMU_MAP_K_RWCB (PAGE_ATTR_RWX | PTE_V | PTE_G | PTE_SHARE | PTE_BUF | PTE_CACHE | PTE_A | PTE_D)
#define ARCH_PAGE_SIZE PAGE_SIZE
#define ARCH_PAGE_MASK (ARCH_PAGE_SIZE - 1)
#define ARCH_PAGE_SHIFT PAGE_OFFSET_BIT

void mmu_set_pagetable(rt_ubase_t addr);
void mmu_enable_user_page_access();
void mmu_disable_user_page_access();

#endif
