/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-12     RT-Thread    the first version
 * 2023-08-15     Shell        Support more mapping attribution
 */
#ifndef __MMU_H_
#define __MMU_H_

#ifndef __ASSEMBLY__

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

#endif /* !__ASSEMBLY__ */

#define RT_HW_MMU_PROT_READ 1
#define RT_HW_MMU_PROT_WRITE 2
#define RT_HW_MMU_PROT_EXECUTE 4
#define RT_HW_MMU_PROT_KERNEL 8
#define RT_HW_MMU_PROT_USER 16
#define RT_HW_MMU_PROT_CACHE 32

#define MMU_AF_SHIFT     10
#define MMU_SHARED_SHIFT 8
#define MMU_AP_SHIFT     6
#define MMU_MA_SHIFT     2
#define MMU_AP_MASK      (0x3 << MMU_AP_SHIFT)

#define MMU_AP_KAUN      0UL /* kernel r/w, user none */
#define MMU_AP_KAUA      1UL /* kernel r/w, user r/w */
#define MMU_AP_KRUN      2UL /* kernel r, user none */
#define MMU_AP_KRUR      3UL /* kernel r, user r */
#define MMU_ATTR_AF      (1ul << MMU_AF_SHIFT)  /* the access flag */
#define MMU_ATTR_DBM     (1ul << 51)            /* the dirty bit modifier */

#define MMU_MAP_CUSTOM(ap, mtype)                                              \
    ((0x1UL << MMU_AF_SHIFT) | (0x2UL << MMU_SHARED_SHIFT) |                   \
     ((ap) << MMU_AP_SHIFT) | ((mtype) << MMU_MA_SHIFT))
#define MMU_MAP_K_ROCB      MMU_MAP_CUSTOM(MMU_AP_KRUN, NORMAL_MEM)
#define MMU_MAP_K_RO        MMU_MAP_CUSTOM(MMU_AP_KRUN, NORMAL_NOCACHE_MEM)
#define MMU_MAP_K_RWCB      MMU_MAP_CUSTOM(MMU_AP_KAUN, NORMAL_MEM)
#define MMU_MAP_K_RW        MMU_MAP_CUSTOM(MMU_AP_KAUN, NORMAL_NOCACHE_MEM)
#define MMU_MAP_K_DEVICE    MMU_MAP_CUSTOM(MMU_AP_KAUN, DEVICE_MEM)
#define MMU_MAP_U_ROCB      MMU_MAP_CUSTOM(MMU_AP_KRUR, NORMAL_MEM)
#define MMU_MAP_U_RO        MMU_MAP_CUSTOM(MMU_AP_KRUR, NORMAL_NOCACHE_MEM)
#define MMU_MAP_U_RWCB      MMU_MAP_CUSTOM(MMU_AP_KAUA, NORMAL_MEM)
#define MMU_MAP_U_RW        MMU_MAP_CUSTOM(MMU_AP_KAUA, NORMAL_NOCACHE_MEM)
#define MMU_MAP_U_DEVICE    MMU_MAP_CUSTOM(MMU_AP_KAUA, DEVICE_MEM)
#define MMU_MAP_TRACE(attr) ((attr) & ~(MMU_ATTR_AF | MMU_ATTR_DBM))

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

#ifndef __ASSEMBLY__

struct rt_aspace;

void rt_hw_mmu_ktbl_set(unsigned long tbl);
void rt_hw_mem_setup_early(unsigned long *tbl0, unsigned long *tbl1,
                           unsigned long size, unsigned long pv_off);
void rt_hw_mmu_setup(struct rt_aspace *aspace, struct mem_desc *mdesc,
                     int desc_nr);

int rt_hw_mmu_map_init(rt_aspace_t aspace, void *v_address, size_t size, size_t *vtable, size_t pv_off);
void *rt_hw_mmu_map(struct rt_aspace *aspace, void *v_addr, void *p_addr,
                    size_t size, size_t attr);
void rt_hw_mmu_unmap(struct rt_aspace *aspace, void *v_addr, size_t size);
void rt_hw_aspace_switch(struct rt_aspace *aspace);
void *rt_hw_mmu_v2p(struct rt_aspace *aspace, void *vaddr);
void rt_hw_mmu_kernel_map_init(struct rt_aspace *aspace, rt_size_t vaddr_start,
                               rt_size_t size);
void *rt_hw_mmu_pgtbl_create(void);
void rt_hw_mmu_pgtbl_delete(void *pgtbl);
void *rt_hw_mmu_tbl_get(void);

static inline void *rt_hw_mmu_kernel_v2p(void *v_addr)
{
    rt_ubase_t par;
    void *paddr;
    __asm__ volatile("at s1e1w, %0"::"r"(v_addr):"memory");
    __asm__ volatile("mrs %0, par_el1":"=r"(par)::"memory");

    if (par & 0x1)
    {
        paddr = ARCH_MAP_FAILED;
    }
    else
    {
        #define MMU_ADDRESS_MASK 0x0000fffffffff000UL
        par &= MMU_ADDRESS_MASK;
        par |= (rt_ubase_t)v_addr & ARCH_PAGE_MASK;
        paddr =  (void *)par;
    }

    return paddr;
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
        /* remove write permission for user */
        case RT_HW_MMU_PROT_WRITE | RT_HW_MMU_PROT_USER:
            attr = (attr & ~MMU_AP_MASK) | (MMU_AP_KAUA << MMU_AP_SHIFT);
            break;
        default:
            RT_ASSERT(0);
    }
    return attr;
}

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
            if (attr & 0x40)
                attr |= 0x80;
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
    rt_bool_t rc;
    switch (prot)
    {
        /* test write permission for user */
        case RT_HW_MMU_PROT_WRITE | RT_HW_MMU_PROT_USER:
            if ((attr & MMU_AP_MASK) == (MMU_AP_KAUA << MMU_AP_SHIFT))
                rc = RT_TRUE;
            else
                rc = RT_FALSE;
            break;
        default:
            RT_ASSERT(0);
    }
    return rc;
}

int rt_hw_mmu_control(struct rt_aspace *aspace, void *vaddr, size_t size,
                      enum rt_mmu_cntl cmd);

#endif /* !__ASSEMBLY__ */

#endif
