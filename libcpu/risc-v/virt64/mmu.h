/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
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
    rt_size_t paddr_start;
    rt_size_t attr;
    struct rt_varea varea;
};

#define GET_PF_ID(addr)     ((addr) >> PAGE_OFFSET_BIT)
#define GET_PF_OFFSET(addr) __MASKVALUE(addr, PAGE_OFFSET_MASK)
#define GET_L1(addr)        __PARTBIT(addr, VPN2_SHIFT, VPN2_BIT)
#define GET_L2(addr)        __PARTBIT(addr, VPN1_SHIFT, VPN1_BIT)
#define GET_L3(addr)        __PARTBIT(addr, VPN0_SHIFT, VPN0_BIT)
#define GET_PPN(pte)                                                           \
    (__PARTBIT(pte, PTE_PPN_SHIFT, PHYSICAL_ADDRESS_WIDTH_BITS - PTE_PPN_SHIFT))
#define GET_PADDR(pte)            (GET_PPN(pte) << PAGE_OFFSET_BIT)
#define VPN_TO_PPN(vaddr, pv_off) (((rt_size_t)(vaddr)) + (pv_off))
#define PPN_TO_VPN(paddr, pv_off) (((rt_size_t)(paddr)) - (pv_off))
#define COMBINEVADDR(l1_off, l2_off, l3_off)                                   \
    (((l1_off) << VPN2_SHIFT) | ((l2_off) << VPN1_SHIFT) |                     \
     ((l3_off) << VPN0_SHIFT))
#define COMBINEPTE(paddr, attr)                                                \
    ((((paddr) >> PAGE_OFFSET_BIT) << PTE_PPN_SHIFT) | (attr))

#define MMU_MAP_ERROR_VANOTALIGN -1
#define MMU_MAP_ERROR_PANOTALIGN -2
#define MMU_MAP_ERROR_NOPAGE     -3
#define MMU_MAP_ERROR_CONFLICT   -4

void *rt_hw_mmu_tbl_get();
int rt_hw_mmu_map_init(rt_aspace_t aspace, void *v_address, rt_size_t size,
                       rt_size_t *vtable, rt_size_t pv_off);
void rt_hw_mmu_setup(rt_aspace_t aspace, struct mem_desc *mdesc, int desc_nr);
void rt_hw_mmu_kernel_map_init(rt_aspace_t aspace, rt_size_t vaddr_start,
                               rt_size_t size);
void *rt_hw_mmu_map(rt_aspace_t aspace, void *v_addr, void *p_addr, size_t size,
                    size_t attr);
void rt_hw_mmu_unmap(rt_aspace_t aspace, void *v_addr, size_t size);
void rt_hw_aspace_switch(rt_aspace_t aspace);
void *rt_hw_mmu_v2p(rt_aspace_t aspace, void *vaddr);

int rt_hw_mmu_control(struct rt_aspace *aspace, void *vaddr, size_t size,
                      enum rt_mmu_cntl cmd);

#endif
