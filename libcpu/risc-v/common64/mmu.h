/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 * 2023-10-12     Shell        Add permission control API
 * 2026-08-25     chenguohao   Add SV48/SV57 support
 */

#ifndef __MMU_H__
#define __MMU_H__

#include "riscv.h"
#include "riscv_mmu.h"
#include <mm_aspace.h>
#include <stddef.h>

/* RAM, Flash, or ROM */
#define NORMAL_MEM 0
/* normal nocache memory mapping type */
#define NORMAL_NOCACHE_MEM 1
/* MMIO region */
#define DEVICE_MEM 2

typedef size_t rt_pte_t;

struct mem_desc
{
    rt_size_t vaddr_start;
    rt_size_t vaddr_end;
    rt_ubase_t paddr_start;
    rt_size_t attr;
    struct rt_varea varea;
};

#define GET_PF_ID(addr)     ((addr) >> PAGE_OFFSET_BIT)
#define GET_PF_OFFSET(addr) __MASKVALUE(addr, PAGE_OFFSET_MASK)

#if (ARCH_PAGE_TBL_LEVELS == 5)
#define GET_L1(addr) __PARTBIT(addr, VPN4_SHIFT, VPN4_BIT)
#define GET_L2(addr) __PARTBIT(addr, VPN3_SHIFT, VPN3_BIT)
#define GET_L3(addr) __PARTBIT(addr, VPN2_SHIFT, VPN2_BIT)
#define GET_L4(addr) __PARTBIT(addr, VPN1_SHIFT, VPN1_BIT)
#define GET_L5(addr) __PARTBIT(addr, VPN0_SHIFT, VPN0_BIT)
#elif (ARCH_PAGE_TBL_LEVELS == 4)
#define GET_L1(addr) __PARTBIT(addr, VPN3_SHIFT, VPN3_BIT)
#define GET_L2(addr) __PARTBIT(addr, VPN2_SHIFT, VPN2_BIT)
#define GET_L3(addr) __PARTBIT(addr, VPN1_SHIFT, VPN1_BIT)
#define GET_L4(addr) __PARTBIT(addr, VPN0_SHIFT, VPN0_BIT)
#elif (ARCH_PAGE_TBL_LEVELS == 3)
#define GET_L1(addr) __PARTBIT(addr, VPN2_SHIFT, VPN2_BIT)
#define GET_L2(addr) __PARTBIT(addr, VPN1_SHIFT, VPN1_BIT)
#define GET_L3(addr) __PARTBIT(addr, VPN0_SHIFT, VPN0_BIT)
#endif

/* Runtime level index extraction: get the page table index at given level (1-based) */
#define GET_LVL_INDEX(addr, level) \
    (((rt_ubase_t)(addr) >> (ARCH_PAGE_SHIFT + (ARCH_PAGE_TBL_LEVELS - (level)) * ARCH_INDEX_WIDTH)) & VPN_MASK)

#define GET_PPN(pte)                                                           \
    (__PARTBIT(pte, PTE_PPN_SHIFT, PHYSICAL_ADDRESS_WIDTH_BITS - PAGE_OFFSET_BIT))
#define GET_PADDR(pte)            (GET_PPN(pte) << PAGE_OFFSET_BIT)
#define VPN_TO_PPN(vaddr, pv_off) (((rt_uintptr_t)(vaddr)) + (pv_off))
#define PPN_TO_VPN(paddr, pv_off) (((rt_uintptr_t)(paddr)) - (pv_off))
#define COMBINEPTE(paddr, attr)                                                \
    ((((paddr) >> PAGE_OFFSET_BIT) << PTE_PPN_SHIFT) | (attr))

#define MMU_MAP_ERROR_VANOTALIGN -1
#define MMU_MAP_ERROR_PANOTALIGN -2
#define MMU_MAP_ERROR_NOPAGE     -3
#define MMU_MAP_ERROR_CONFLICT   -4

#define VPN_MASK    0x1ffUL
#define PTE_BITS    10
#define VPN_BITS    9

#if defined(RT_USING_SMP) && defined(ARCH_MM_MMU)
extern unsigned int __percpu_end, __percpu_start;
#endif /* RT_USING_SMP && ARCH_MM_MMU */

void *rt_hw_mmu_tbl_get(void);
int rt_hw_mmu_map_init(rt_aspace_t aspace, void *v_address, rt_ubase_t size,
                       rt_ubase_t *vtable, rt_ubase_t pv_off);
void rt_hw_mmu_setup(rt_aspace_t aspace, struct mem_desc *mdesc, int desc_nr);
void *rt_hw_mmu_map(rt_aspace_t aspace, void *v_addr, void *p_addr, size_t size,
                    size_t attr);
void rt_hw_mmu_unmap(rt_aspace_t aspace, void *v_addr, size_t size);
void rt_hw_aspace_switch(rt_aspace_t aspace);
void *rt_hw_mmu_v2p(rt_aspace_t aspace, void *vaddr);

int rt_hw_mmu_control(struct rt_aspace *aspace, void *vaddr, size_t size,
                      enum rt_mmu_cntl cmd);

void *rt_hw_mmu_pgtbl_create(void);
void rt_hw_mmu_pgtbl_delete(void *pgtbl);

unsigned long get_free_page(void);
#endif
