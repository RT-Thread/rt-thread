/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-25     quanzhao     the first version
 * 2020-07-26     lizhirui     porting to ls2k
 */
#ifndef __MMU_H_
#define __MMU_H_

#include <rtthread.h>

#define DESC_SEC       (0x2)
#define MEMWBWA        ((1<<12)|(3<<2))      /* write back, write allocate */
#define MEMWB          (3<<2)                /* write back, no write allocate */
#define MEMWT          (2<<2)                /* write through, no write allocate */
#define SHAREDEVICE    (1<<2)                /* shared device */
#define STRONGORDER    (0<<2)                /* strong ordered */
#define XN             (1<<4)                /* execute Never */
#ifdef RT_USING_USERSPACE
#define AP_RW          (1<<10)               /* supervisor=RW, user=No */
#define AP_RO          ((1<<10) |(1 << 15))  /* supervisor=RW, user=No */
#else
#define AP_RW          (3<<10)               /* supervisor=RW, user=RW */
#define AP_RO          ((2<<10)              /* supervisor=RW, user=RO */
#endif

#define SHARED         (1<<16)               /* shareable */

#define DOMAIN_FAULT   (0x0)
#define DOMAIN_CHK     (0x1)
#define DOMAIN_NOTCHK  (0x3)
#define DOMAIN0        (0x0<<5)
#define DOMAIN1        (0x1<<5)

#define DOMAIN0_ATTR   (DOMAIN_CHK<<0)
#define DOMAIN1_ATTR   (DOMAIN_FAULT<<2)

/* device mapping type */
#define DEVICE_MEM     (SHARED|AP_RW|DOMAIN0|SHAREDEVICE|DESC_SEC|XN)
/* normal memory mapping type */
#define NORMAL_MEM     (SHARED|AP_RW|DOMAIN0|MEMWBWA|DESC_SEC)

#define STRONG_ORDER_MEM (SHARED|AP_RO|XN|DESC_SEC)

struct mem_desc
{
    rt_uint32_t vaddr_start;
    rt_uint32_t vaddr_end;
    rt_uint32_t paddr_start;
    rt_uint32_t attr;
};

#define MMU_MAP_MTBL_XN       (1<<0)
#define MMU_MAP_MTBL_A        (1<<1)
#define MMU_MAP_MTBL_B        (1<<2)
#define MMU_MAP_MTBL_C        (1<<3)
#define MMU_MAP_MTBL_AP01(x)  (x<<4)
#define MMU_MAP_MTBL_TEX(x)   (x<<6)
#define MMU_MAP_MTBL_AP2(x)   (x<<9)
#define MMU_MAP_MTBL_SHARE    (1<<10)

#define MMU_MAP_K_RO          (MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(1)|MMU_MAP_MTBL_AP01(1)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_C|MMU_MAP_MTBL_SHARE)
#define MMU_MAP_K_RWCB        (MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(0)|MMU_MAP_MTBL_AP01(1)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_B|MMU_MAP_MTBL_C|MMU_MAP_MTBL_SHARE)
#define MMU_MAP_K_RW          (MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(0)|MMU_MAP_MTBL_AP01(1)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_SHARE)
#define MMU_MAP_K_DEVICE      (MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(0)|MMU_MAP_MTBL_AP01(1)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_B|MMU_MAP_MTBL_SHARE)
#define MMU_MAP_U_RO          (MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(1)|MMU_MAP_MTBL_AP01(2)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_C|MMU_MAP_MTBL_SHARE)
#define MMU_MAP_U_RWCB        (MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(0)|MMU_MAP_MTBL_AP01(3)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_B|MMU_MAP_MTBL_C|MMU_MAP_MTBL_SHARE)
#define MMU_MAP_U_RW          (MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(0)|MMU_MAP_MTBL_AP01(3)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_SHARE)
#define MMU_MAP_U_DEVICE      (MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(0)|MMU_MAP_MTBL_AP01(3)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_B|MMU_MAP_MTBL_SHARE)

#define ARCH_SECTION_SHIFT  20
#define ARCH_SECTION_SIZE   (1 << ARCH_SECTION_SHIFT)
#define ARCH_SECTION_MASK   (ARCH_SECTION_SIZE - 1)
#define ARCH_PAGE_SHIFT     14
#define ARCH_PAGE_SIZE      (1 << ARCH_PAGE_SHIFT)
#define ARCH_PAGE_MASK      (ARCH_PAGE_SIZE - 1)
#define ARCH_PAGE_TBL_SHIFT 10
#define ARCH_PAGE_TBL_SIZE  (1 << ARCH_PAGE_TBL_SHIFT)
#define ARCH_PAGE_TBL_MASK  (ARCH_PAGE_TBL_SIZE - 1)

#define ARCH_MMU_USED_MASK  3

#define ARCH_TYPE_SUPERSECTION (1 << 18)

typedef struct
{
    size_t *vtable;
    size_t vstart;
    size_t vend;
    size_t pv_off;
} rt_mmu_info;

void *mmu_table_get();
void switch_mmu(void *mmu_table);

int rt_hw_mmu_map_init(rt_mmu_info *mmu_info, void* v_address, size_t size, size_t *vtable, size_t pv_off);
#ifdef RT_USING_USERSPACE
void *rt_hw_mmu_map(rt_mmu_info *mmu_info, void *v_addr, void* p_addr, size_t size, size_t attr);
void *rt_hw_mmu_map_auto(rt_mmu_info *mmu_info, void *v_addr, size_t size, size_t attr);
#else
void *rt_hw_mmu_map(rt_mmu_info *mmu_info, void* p_addr, size_t size, size_t attr);
#endif
void rt_hw_mmu_unmap(rt_mmu_info *mmu_info, void* v_addr, size_t size);
void *rt_hw_mmu_v2p(rt_mmu_info *mmu_info, void* v_addr);

void *rt_hw_kernel_phys_to_virt(void *p_addr, size_t size);
void *rt_hw_kernel_virt_to_phys(void *v_addr, size_t size);

#endif
