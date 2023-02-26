/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-12     RT-Thread    the first version
 */
#ifndef __MMU_H_
#define __MMU_H_

#include <rtthread.h>
#include <mm_aspace.h>

/* normal memory wra mapping type */
#define NORMAL_MEM           0
/* normal nocache memory mapping type */
#define NORMAL_NOCACHE_MEM   1
/* device mapping type */
#define DEVICE_MEM           2

struct mem_desc
{
    unsigned long vaddr_start;
    unsigned long vaddr_end;
    unsigned long paddr_start;
    unsigned long attr;
    struct rt_varea varea;
};

#define MMU_AF_SHIFT     10
#define MMU_SHARED_SHIFT 8
#define MMU_AP_SHIFT     6
#define MMU_MA_SHIFT     2

#define MMU_AP_KAUN      0UL /* kernel r/w, user none */
#define MMU_AP_KAUA      1UL /* kernel r/w, user r/w */
#define MMU_AP_KRUN      2UL /* kernel r, user none */
#define MMU_AP_KRUR      3UL /* kernel r, user r */

#define MMU_MAP_CUSTOM(ap, mtype)                                              \
    ((0x1UL << MMU_AF_SHIFT) | (0x2UL << MMU_SHARED_SHIFT) |                   \
     ((ap) << MMU_AP_SHIFT) | ((mtype) << MMU_MA_SHIFT))
#define MMU_MAP_K_RO     MMU_MAP_CUSTOM(MMU_AP_KRUN, NORMAL_MEM)
#define MMU_MAP_K_RWCB   MMU_MAP_CUSTOM(MMU_AP_KAUN, NORMAL_MEM)
#define MMU_MAP_K_RW     MMU_MAP_CUSTOM(MMU_AP_KAUN, NORMAL_NOCACHE_MEM)
#define MMU_MAP_K_DEVICE MMU_MAP_CUSTOM(MMU_AP_KAUN, DEVICE_MEM)
#define MMU_MAP_U_RO     MMU_MAP_CUSTOM(MMU_AP_KRUR, NORMAL_NOCACHE_MEM)
#define MMU_MAP_U_RWCB   MMU_MAP_CUSTOM(MMU_AP_KAUA, NORMAL_MEM)
#define MMU_MAP_U_RW     MMU_MAP_CUSTOM(MMU_AP_KAUA, NORMAL_NOCACHE_MEM)
#define MMU_MAP_U_DEVICE MMU_MAP_CUSTOM(MMU_AP_KAUA, DEVICE_MEM)

#define ARCH_SECTION_SHIFT  21
#define ARCH_SECTION_SIZE   (1 << ARCH_SECTION_SHIFT)
#define ARCH_SECTION_MASK   (ARCH_SECTION_SIZE - 1)
#define ARCH_PAGE_SHIFT     12
#define ARCH_PAGE_SIZE      (1 << ARCH_PAGE_SHIFT)
#define ARCH_PAGE_MASK      (ARCH_PAGE_SIZE - 1)
#define ARCH_PAGE_TBL_SHIFT 12
#define ARCH_PAGE_TBL_SIZE  (1 << ARCH_PAGE_TBL_SHIFT)
#define ARCH_PAGE_TBL_MASK  (ARCH_PAGE_TBL_SIZE - 1)

#define ARCH_VADDR_WIDTH        48
#define ARCH_ADDRESS_WIDTH_BITS 64

#define MMU_MAP_ERROR_VANOTALIGN  -1
#define MMU_MAP_ERROR_PANOTALIGN  -2
#define MMU_MAP_ERROR_NOPAGE      -3
#define MMU_MAP_ERROR_CONFLICT    -4

#define ARCH_MAP_FAILED ((void *)0x1ffffffffffff)

struct rt_aspace;

void rt_hw_mmu_ktbl_set(unsigned long tbl);
void rt_hw_mem_setup_early(unsigned long *tbl0, unsigned long *tbl1,
                           unsigned long size, unsigned long pv_off);
void rt_hw_mmu_setup(struct rt_aspace *aspace, struct mem_desc *mdesc,
                     int desc_nr);

int rt_hw_mmu_map_init(struct rt_aspace *aspace, void *v_address,
                       rt_size_t size, rt_size_t *vtable, rt_size_t pv_off);
void *rt_hw_mmu_map(struct rt_aspace *aspace, void *v_addr, void *p_addr,
                    size_t size, size_t attr);
void rt_hw_mmu_unmap(struct rt_aspace *aspace, void *v_addr, size_t size);
void rt_hw_aspace_switch(struct rt_aspace *aspace);
void *rt_hw_mmu_v2p(struct rt_aspace *aspace, void *vaddr);
void rt_hw_mmu_kernel_map_init(struct rt_aspace *aspace, rt_size_t vaddr_start,
                               rt_size_t size);
void rt_hw_mmu_ktbl_set(unsigned long tbl);

static inline void *rt_hw_mmu_tbl_get()
{
    uintptr_t tbl;
    __asm__ volatile("MRS %0, TTBR0_EL1" : "=r"(tbl));
    return (void *)(tbl & ((1ul << 48) - 2));
}

int rt_hw_mmu_control(struct rt_aspace *aspace, void *vaddr, size_t size,
                      enum rt_mmu_cntl cmd);

#endif
