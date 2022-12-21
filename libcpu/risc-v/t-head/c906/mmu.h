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
struct mem_desc
{
    rt_size_t vaddr_start;
    rt_size_t vaddr_end;
    rt_size_t paddr_start;
    rt_size_t attr;
};

#define GET_PF_ID(addr) ((addr) >> PAGE_OFFSET_BIT)
#define GET_PF_OFFSET(addr) __MASKVALUE(addr,PAGE_OFFSET_MASK)
#define GET_L1(addr) __PARTBIT(addr,VPN2_SHIFT,VPN2_BIT)
#define GET_L2(addr) __PARTBIT(addr,VPN1_SHIFT,VPN1_BIT)
#define GET_L3(addr) __PARTBIT(addr,VPN0_SHIFT,VPN0_BIT)
#define GET_PPN(pte) (__PARTBIT(pte,PTE_PPN_SHIFT,PHYSICAL_ADDRESS_WIDTH_BITS - PTE_PPN_SHIFT))
#define GET_PADDR(pte) (GET_PPN(pte) << PAGE_OFFSET_BIT)
#define VPN_TO_PPN(vaddr,pv_off) (((rt_size_t)(vaddr)) + (pv_off))
#define PPN_TO_VPN(paddr,pv_off) (((rt_size_t)(paddr)) - (pv_off))
#define COMBINEVADDR(l1_off,l2_off,l3_off) (((l1_off) << VPN2_SHIFT) | ((l2_off) << VPN1_SHIFT) | ((l3_off) << VPN0_SHIFT))
#define COMBINEPTE(paddr,attr) ((((paddr) >> PAGE_OFFSET_BIT) << PTE_PPN_SHIFT) | (attr))

typedef struct
{
    size_t *vtable;
    size_t vstart;
    size_t vend;
    size_t pv_off;
}rt_mmu_info;

void *rt_hw_mmu_tbl_get();
void rt_hw_mmu_switch(void *mmu_table);
int rt_hw_mmu_map_init(rt_mmu_info *mmu_info,void *v_address,rt_size_t size,rt_size_t *vtable,rt_size_t pv_off);
void rt_hw_mmu_kernel_map_init(rt_mmu_info *mmu_info,rt_size_t vaddr_start,rt_size_t size);
void *_rt_hw_mmu_map(rt_mmu_info *mmu_info,void *v_addr,void *p_addr,rt_size_t size,rt_size_t attr);
void *_rt_hw_mmu_map_auto(rt_mmu_info *mmu_info,void *v_addr,rt_size_t size,rt_size_t attr);
void _rt_hw_mmu_unmap(rt_mmu_info *mmu_info,void *v_addr,rt_size_t size);
void *rt_hw_mmu_map(rt_mmu_info *mmu_info,void *v_addr,void *p_addr,rt_size_t size,rt_size_t attr);
void *rt_hw_mmu_map_auto(rt_mmu_info *mmu_info,void *v_addr,rt_size_t size,rt_size_t attr);
void rt_hw_mmu_unmap(rt_mmu_info *mmu_info,void *v_addr,rt_size_t size);
void *_rt_hw_mmu_v2p(rt_mmu_info *mmu_info,void *v_addr);
void *rt_hw_mmu_v2p(rt_mmu_info *mmu_info,void *v_addr);

#endif
