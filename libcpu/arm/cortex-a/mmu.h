/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-25     quanzhao     the first version
 * 2023-10-10     Shell        Add permission control API
 */
#ifndef __MMU_H_
#define __MMU_H_

#include <rtthread.h>
#include <mm_aspace.h>

#define DESC_SEC       (0x2)
#define MEMWBWA        ((1<<12)|(3<<2))     /* write back, write allocate */
#define MEMWB          (3<<2)  /* write back, no write allocate */
#define MEMWT          (2<<2)  /* write through, no write allocate */
#define SHAREDEVICE    (1<<2)  /* shared device */
#define STRONGORDER    (0<<2)  /* strong ordered */
#define XN             (1<<4)  /* eXecute Never */
#ifdef RT_USING_SMART
#define AP_RW          (1<<10) /* supervisor=RW, user=No */
#define AP_RO          ((1<<10) |(1 << 15)) /* supervisor=RW, user=No */
#else
#define AP_RW          (3<<10) /* supervisor=RW, user=RW */
#define AP_RO          (2<<10) /* supervisor=RW, user=RO */
#endif

#define SHARED         (1<<16) /* shareable */

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
    struct rt_varea varea;
};

#define MMU_MAP_MTBL_XN       (1<<0)
#define MMU_MAP_MTBL_A        (1<<1)
#define MMU_MAP_MTBL_B        (1<<2)
#define MMU_MAP_MTBL_C        (1<<3)
#define MMU_MAP_MTBL_AP01(x)  (x<<4)
#define MMU_MAP_MTBL_TEX(x)   (x<<6)
#define MMU_MAP_MTBL_AP2(x)   (x<<9)
#define MMU_MAP_MTBL_SHARE    (1<<10)
#define MMU_MAP_MTBL_NG(x)    (x<<11)

#define MMU_MAP_K_ROCB        ((MMU_MAP_MTBL_NG(0))|(MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(1)|MMU_MAP_MTBL_AP01(1)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_B|MMU_MAP_MTBL_C|MMU_MAP_MTBL_SHARE))
#define MMU_MAP_K_RO          ((MMU_MAP_MTBL_NG(0))|(MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(1)|MMU_MAP_MTBL_AP01(1)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_C|MMU_MAP_MTBL_SHARE))
#define MMU_MAP_K_RWCB        ((MMU_MAP_MTBL_NG(0))|(MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(0)|MMU_MAP_MTBL_AP01(1)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_B|MMU_MAP_MTBL_C|MMU_MAP_MTBL_SHARE))
#define MMU_MAP_K_RW          ((MMU_MAP_MTBL_NG(0))|(MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(0)|MMU_MAP_MTBL_AP01(1)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_SHARE))
#define MMU_MAP_K_DEVICE      ((MMU_MAP_MTBL_NG(0))|(MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(0)|MMU_MAP_MTBL_AP01(1)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_B|MMU_MAP_MTBL_SHARE))
#define MMU_MAP_U_ROCB        ((MMU_MAP_MTBL_NG(1))|(MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(0)|MMU_MAP_MTBL_AP01(2)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_B|MMU_MAP_MTBL_C|MMU_MAP_MTBL_SHARE))
#define MMU_MAP_U_RO          ((MMU_MAP_MTBL_NG(1))|(MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(0)|MMU_MAP_MTBL_AP01(2)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_C|MMU_MAP_MTBL_SHARE))
#define MMU_MAP_U_RWCB        ((MMU_MAP_MTBL_NG(1))|(MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(0)|MMU_MAP_MTBL_AP01(3)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_B|MMU_MAP_MTBL_C|MMU_MAP_MTBL_SHARE))
#define MMU_MAP_U_RW          ((MMU_MAP_MTBL_NG(1))|(MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(0)|MMU_MAP_MTBL_AP01(3)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_SHARE))
#define MMU_MAP_U_DEVICE      ((MMU_MAP_MTBL_NG(1))|(MMU_MAP_MTBL_A|MMU_MAP_MTBL_AP2(0)|MMU_MAP_MTBL_AP01(3)|MMU_MAP_MTBL_TEX(0)|MMU_MAP_MTBL_B|MMU_MAP_MTBL_SHARE))
#define MMU_MAP_TRACE(attr)   (attr)

#define ARCH_SECTION_SHIFT  20
#define ARCH_SECTION_SIZE   (1 << ARCH_SECTION_SHIFT)
#define ARCH_SECTION_MASK   (ARCH_SECTION_SIZE - 1)
#define ARCH_PAGE_SHIFT     12
#define ARCH_PAGE_SIZE      (1 << ARCH_PAGE_SHIFT)
#define ARCH_PAGE_MASK      (ARCH_PAGE_SIZE - 1)
#define ARCH_PAGE_TBL_SHIFT 10
#define ARCH_PAGE_TBL_SIZE  (1 << ARCH_PAGE_TBL_SHIFT)
#define ARCH_PAGE_TBL_MASK  (ARCH_PAGE_TBL_SIZE - 1)

#define ARCH_MMU_USED_MASK  3

#define ARCH_TYPE_SUPERSECTION (1 << 18)

#define ARCH_ADDRESS_WIDTH_BITS 32
#define ARCH_VADDR_WIDTH        32

/**
 * *info it's possible to map (-1ul & ~ARCH_PAGE_MASK) but a not aligned -1 is
 * never returned on a successful mapping
 */
#define ARCH_MAP_FAILED ((void *)-1)

#define RT_HW_MMU_PROT_READ 1
#define RT_HW_MMU_PROT_WRITE 2
#define RT_HW_MMU_PROT_EXECUTE 4
#define RT_HW_MMU_PROT_KERNEL 8
#define RT_HW_MMU_PROT_USER 16
#define RT_HW_MMU_PROT_CACHE 32

int rt_hw_mmu_ioremap_init(struct rt_aspace *aspace, void *v_address, size_t size);
void rt_hw_init_mmu_table(struct mem_desc *mdesc, rt_uint32_t size);

void rt_hw_mmu_setup(struct rt_aspace *aspace, struct mem_desc *mdesc, int desc_nr);
void rt_hw_mmu_init(void);
int rt_hw_mmu_map_init(struct rt_aspace *aspace, void *v_address, size_t size, size_t *vtable, size_t pv_off);
void *rt_hw_mmu_map(struct rt_aspace *aspace, void *v_addr, void *p_addr, size_t size, size_t attr);
void rt_hw_mmu_unmap(struct rt_aspace *aspace, void *v_addr, size_t size);

void rt_hw_aspace_switch(struct rt_aspace *aspace);
void rt_hw_mmu_switch(void *tbl);

void *rt_hw_mmu_v2p(struct rt_aspace *aspace, void *vaddr);
void *rt_hw_mmu_tbl_get(void);

int rt_hw_mmu_control(struct rt_aspace *aspace, void *vaddr, size_t size, enum rt_mmu_cntl cmd);

void *rt_hw_mmu_pgtbl_create(void);
void rt_hw_mmu_pgtbl_delete(void *pgtbl);

#define AP_APX_MASK (MMU_MAP_MTBL_AP2(0x1) | MMU_MAP_MTBL_AP01(0x3))
#define AP_APX_URW_KRW (MMU_MAP_MTBL_AP2(0x0) | MMU_MAP_MTBL_AP01(0x3))
#define AP_APX_URO_KRO (MMU_MAP_MTBL_AP2(0x1) | MMU_MAP_MTBL_AP01(0x2))

/**
 * @brief Remove permission from attribution
 *
 * @param attr architecture specified mmu attribution
 * @param prot protect that will be removed
 * @return size_t returned attribution
 */
rt_inline size_t rt_hw_mmu_attr_rm_perm(size_t attr, rt_base_t prot)
{
    switch (prot)
    {
        /* remove write permission for user */
        case RT_HW_MMU_PROT_WRITE | RT_HW_MMU_PROT_USER:
            if ((attr & AP_APX_MASK) == AP_APX_URW_KRW)
                attr &= ~MMU_MAP_MTBL_AP01(0x1);
            break;
        case RT_HW_MMU_PROT_WRITE | RT_HW_MMU_PROT_KERNEL:
            switch (attr & AP_APX_MASK)
            {
                case MMU_MAP_MTBL_AP01(0):
                    break;
                case MMU_MAP_MTBL_AP01(3):
                    attr = (attr & AP_APX_MASK) | AP_APX_URO_KRO;
                default:
                    attr |= MMU_MAP_MTBL_AP2(0x1);
                    break;
            }
            break;
        default:
            RT_ASSERT(0);
    }
    return attr;
}

/**
 * @brief Add permission from attribution
 *
 * @param attr architecture specified mmu attribution
 * @param prot protect that will be added
 * @return size_t returned attribution
 */
rt_inline size_t rt_hw_mmu_attr_add_perm(size_t attr, rt_base_t prot)
{
    switch (prot)
    {
        /* add write permission for user */
        case RT_HW_MMU_PROT_WRITE | RT_HW_MMU_PROT_USER:
        case RT_HW_MMU_PROT_WRITE | RT_HW_MMU_PROT_KERNEL:
            attr |= MMU_MAP_MTBL_AP01(0x3);
            attr &= ~MMU_MAP_MTBL_AP2(0x1);
            break;
        default:
            RT_ASSERT(0);
    }
    return attr;
}

/**
 * @brief Test permission from attribution
 *
 * @param attr architecture specified mmu attribution
 * @param prot protect that will be test
 * @return rt_bool_t RT_TRUE if the prot is allowed, otherwise RT_FALSE
 */
rt_inline rt_bool_t rt_hw_mmu_attr_test_perm(size_t attr, rt_base_t prot)
{
    rt_bool_t rc = 0;
    switch (prot)
    {
        /* test write permission for user */
        case RT_HW_MMU_PROT_WRITE | RT_HW_MMU_PROT_USER:
            rc = (AP_APX_MASK & attr) == (AP_APX_URW_KRW);
            break;
        default:
            RT_ASSERT(0);
    }
    return rc;
}

#endif
