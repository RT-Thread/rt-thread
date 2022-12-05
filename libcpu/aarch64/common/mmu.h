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
};

#define MMU_AF_SHIFT     10
#define MMU_SHARED_SHIFT 8
#define MMU_AP_SHIFT     6
#define MMU_MA_SHIFT     2

#define MMU_AP_KAUN      0UL /* kernel r/w, user none */
#define MMU_AP_KAUA      1UL /* kernel r/w, user r/w */
#define MMU_AP_KRUN      2UL /* kernel r, user none */
#define MMU_AP_KRUR      3UL /* kernel r, user r */

#define MMU_MAP_K_RO     (\
                          (0x1UL << MMU_AF_SHIFT) |\
                          (0x2UL << MMU_SHARED_SHIFT) |\
                          (MMU_AP_KRUN << MMU_AP_SHIFT) |\
                          (NORMAL_MEM << MMU_MA_SHIFT)\
                         )
#define MMU_MAP_K_RWCB   (\
                          (0x1UL << MMU_AF_SHIFT) |\
                          (0x2UL << MMU_SHARED_SHIFT) |\
                          (MMU_AP_KAUN << MMU_AP_SHIFT) |\
                          (NORMAL_MEM << MMU_MA_SHIFT)\
                         )
#define MMU_MAP_K_RW     (\
                          (0x1UL << MMU_AF_SHIFT) |\
                          (0x2UL << MMU_SHARED_SHIFT) |\
                          (MMU_AP_KAUN << MMU_AP_SHIFT) |\
                          (NORMAL_NOCACHE_MEM << MMU_MA_SHIFT)\
                         )
#define MMU_MAP_K_DEVICE (\
                          (0x1UL << MMU_AF_SHIFT) |\
                          (0x2UL << MMU_SHARED_SHIFT) |\
                          (MMU_AP_KAUN << MMU_AP_SHIFT) |\
                          (DEVICE_MEM << MMU_MA_SHIFT)\
                         )
#define MMU_MAP_U_RO     (\
                          (0x1UL << MMU_AF_SHIFT) |\
                          (0x2UL << MMU_SHARED_SHIFT) |\
                          (MMU_AP_KRUR << MMU_AP_SHIFT) |\
                          (NORMAL_NOCACHE_MEM << MMU_MA_SHIFT)\
                         )
#define MMU_MAP_U_RWCB   (\
                          (0x1UL << MMU_AF_SHIFT) |\
                          (0x2UL << MMU_SHARED_SHIFT) |\
                          (MMU_AP_KAUA << MMU_AP_SHIFT) |\
                          (NORMAL_MEM << MMU_MA_SHIFT)\
                         )
#define MMU_MAP_U_RW     (\
                          (0x1UL << MMU_AF_SHIFT) |\
                          (0x2UL << MMU_SHARED_SHIFT) |\
                          (MMU_AP_KAUA << MMU_AP_SHIFT) |\
                          (NORMAL_NOCACHE_MEM << MMU_MA_SHIFT)\
                         )
#define MMU_MAP_U_DEVICE (\
                          (0x1UL << MMU_AF_SHIFT) |\
                          (0x2UL << MMU_SHARED_SHIFT) |\
                          (MMU_AP_KAUA << MMU_AP_SHIFT) |\
                          (DEVICE_MEM << MMU_MA_SHIFT)\
                         )
#define MMU_MAP_CUSTOM(ap, mtype) (\
                          (0x1UL << MMU_AF_SHIFT) |\
                          (0x2UL << MMU_SHARED_SHIFT) |\
                          ((ap) << MMU_AP_SHIFT) |\
                          ((mtype) << MMU_MA_SHIFT)\
                         )

#define ARCH_SECTION_SHIFT  21
#define ARCH_SECTION_SIZE   (1 << ARCH_SECTION_SHIFT)
#define ARCH_SECTION_MASK   (ARCH_SECTION_SIZE - 1)
#define ARCH_PAGE_SHIFT     12
#define ARCH_PAGE_SIZE      (1 << ARCH_PAGE_SHIFT)
#define ARCH_PAGE_MASK      (ARCH_PAGE_SIZE - 1)
#define ARCH_PAGE_TBL_SHIFT 12
#define ARCH_PAGE_TBL_SIZE  (1 << ARCH_PAGE_TBL_SHIFT)
#define ARCH_PAGE_TBL_MASK  (ARCH_PAGE_TBL_SIZE - 1)

#define ARCH_ADDRESS_WIDTH_BITS 64

#define MMU_MAP_ERROR_VANOTALIGN  -1
#define MMU_MAP_ERROR_PANOTALIGN  -2
#define MMU_MAP_ERROR_NOPAGE      -3
#define MMU_MAP_ERROR_CONFLICT    -4

typedef struct
{
    size_t *vtable;
    size_t vstart;
    size_t vend;
    size_t pv_off;
} rt_mmu_info;

void rt_hw_mmu_setup_early(unsigned long *tbl0, unsigned long *tbl1, unsigned long size, unsigned long pv_off);
void rt_hw_mmu_setup(struct mem_desc *mdesc, int desc_nr);

int rt_hw_mmu_map_init(rt_mmu_info *mmu_info, void* v_address, size_t size, size_t *vtable, size_t pv_off);
int rt_hw_mmu_ioremap_init(rt_mmu_info *mmu_info, void* v_address, size_t size);

#ifdef RT_USING_USERSPACE
void *rt_hw_mmu_map(rt_mmu_info *mmu_info, void *v_addr, void* p_addr, size_t size, size_t attr);
void *rt_hw_mmu_map_auto(rt_mmu_info *mmu_info, void *v_addr, size_t size, size_t attr);
#else
void *rt_hw_mmu_map(rt_mmu_info *mmu_info, void* p_addr, size_t size, size_t attr);
#endif

void rt_hw_mmu_unmap(rt_mmu_info *mmu_info, void* v_addr, size_t size);
void *rt_hw_mmu_v2p(rt_mmu_info *mmu_info, void* v_addr);

void rt_hw_mmu_ktbl_set(unsigned long tbl);
void *rt_hw_mmu_tbl_get();
void rt_hw_mmu_switch(void *mmu_table);

extern rt_mmu_info mmu_info;

#endif
