/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 * 2023-10-12     Shell        Add permission control API
 * 2025-04-26     GuEe-GUI     Follow the specific and vendor
 */

#ifndef __MMU_H__
#define __MMU_H__

#include <page_def.h>
#include <asm-generic.h>

#ifndef __ASSEMBLY__
#include <mm_aspace.h>

/* Normal memory wra mapping type */
#define NORMAL_MEM                      0
/* Normal nocache memory mapping type */
#define NORMAL_NOCACHE_MEM              1
/* Device mapping type */
#define DEVICE_MEM                      2

struct mem_desc
{
    unsigned long vaddr_start;
    unsigned long vaddr_end;
    unsigned long paddr_start;
    unsigned long attr;
    struct rt_varea varea;
};

#ifdef __HAS_MMU_VENDOR__
#include <mmu_vendor.h>
#endif

#endif /* !__ASSEMBLY__ */

#define RT_HW_MMU_PROT_READ             1
#define RT_HW_MMU_PROT_WRITE            2
#define RT_HW_MMU_PROT_EXECUTE          4
#define RT_HW_MMU_PROT_KERNEL           8
#define RT_HW_MMU_PROT_USER             16
#define RT_HW_MMU_PROT_CACHE            32

/* Page table entry (PTE) fields */
#define PTE_V                           BIT(0) /* Valid */
#define PTE_R                           BIT(1) /* Read */
#define PTE_W                           BIT(2) /* Write */
#define PTE_X                           BIT(3) /* Execute */
#define PTE_U                           BIT(4) /* User */
#define PTE_G                           BIT(5) /* Global */
#define PTE_A                           BIT(6) /* Accessed */
#define PTE_D                           BIT(7) /* Dirty */
#define PTE_SOFT                        GENMASK(9, 8) /* Reserved for Software */

#define PTE_BITS                        10

#define PTE_ATTR_NONE                   _UL(0)
#define PTE_ATTR_RW                     (PTE_R | PTE_W)
#define PTE_ATTR_RWX                    (PTE_ATTR_RW | PTE_X)
#define PTE_ATTR_KERNEL                 (PTE_V | PTE_ATTR_RWX | PTE_A | PTE_D)
#define PTE_ATTR_USER                   (PTE_ATTR_KERNEL | PTE_U)

#if !defined(__HAS_MMU_VENDOR__) && __riscv_xlen != 32
#define SVPBMT_SHIFT                    61  /* ISA SVPBMT */

#define PTE_VENDOR_PMA                  (0x0ULL << SVPBMT_SHIFT)
#define PTE_VENDOR_NOCACHE              (0x1ULL << SVPBMT_SHIFT)
#define PTE_VENDOR_IO                   (0x2ULL << SVPBMT_SHIFT)
#define PTE_VENDOR_MTMASK               (0x3ULL << SVPBMT_SHIFT)
#endif /* !__HAS_MMU_VENDOR__ && __riscv_xlen != 32 */

#ifndef PTE_VENDOR_PMA
#define PTE_VENDOR_PMA                  PTE_ATTR_NONE
#endif

#ifndef PTE_VENDOR_NOCACHE
#define PTE_VENDOR_NOCACHE              PTE_ATTR_NONE
#endif

#ifndef PTE_VENDOR_IO
#define PTE_VENDOR_IO                   PTE_ATTR_NONE
#endif

#ifndef MMU_VENDOR_MAP_K_ROCB
#define MMU_VENDOR_MAP_K_ROCB           ((PTE_ATTR_KERNEL & ~PTE_W) | PTE_VENDOR_PMA)
#endif
#ifndef MMU_VENDOR_MAP_K_RO
#define MMU_VENDOR_MAP_K_RO             ((PTE_ATTR_KERNEL & ~PTE_W) | PTE_VENDOR_NOCACHE)
#endif
#ifndef MMU_VENDOR_MAP_K_RWCB
#define MMU_VENDOR_MAP_K_RWCB           (PTE_ATTR_KERNEL | PTE_VENDOR_PMA)
#endif
#ifndef MMU_VENDOR_MAP_K_RW
#define MMU_VENDOR_MAP_K_RW             (PTE_ATTR_KERNEL | PTE_VENDOR_NOCACHE)
#endif
#ifndef MMU_VENDOR_MAP_K_DEVICE
#define MMU_VENDOR_MAP_K_DEVICE         ((PTE_ATTR_KERNEL & ~PTE_X) | PTE_VENDOR_IO)
#endif
#ifndef MMU_VENDOR_MAP_U_ROCB
#define MMU_VENDOR_MAP_U_ROCB           ((PTE_ATTR_USER & ~PTE_W) | PTE_VENDOR_PMA)
#endif
#ifndef MMU_VENDOR_MAP_U_RO
#define MMU_VENDOR_MAP_U_RO             ((PTE_ATTR_USER & ~PTE_W) | PTE_VENDOR_NOCACHE)
#endif
#ifndef MMU_VENDOR_MAP_U_RWCB
#define MMU_VENDOR_MAP_U_RWCB           (PTE_ATTR_USER | PTE_VENDOR_PMA)
#endif
#ifndef MMU_VENDOR_MAP_U_RW
#define MMU_VENDOR_MAP_U_RW             (PTE_ATTR_USER | PTE_VENDOR_NOCACHE)
#endif
#ifndef MMU_VENDOR_MAP_U_DEVICE
#define MMU_VENDOR_MAP_U_DEVICE         ((PTE_ATTR_USER & ~PTE_X) | PTE_VENDOR_IO)
#endif
#ifndef MMU_VENDOR_MAP_EARLY
#define MMU_VENDOR_MAP_EARLY            (PTE_RWX | PTE_G | PTE_V)
#endif

#define MMU_MAP_K_ROCB                  MMU_VENDOR_MAP_K_ROCB
#define MMU_MAP_K_RO                    MMU_VENDOR_MAP_K_RO
#define MMU_MAP_K_RWCB                  MMU_VENDOR_MAP_K_RWCB
#define MMU_MAP_K_RW                    MMU_VENDOR_MAP_K_RW
#define MMU_MAP_K_DEVICE                MMU_VENDOR_MAP_K_DEVICE
#define MMU_MAP_U_ROCB                  MMU_VENDOR_MAP_U_ROCB
#define MMU_MAP_U_RO                    MMU_VENDOR_MAP_U_RO
#define MMU_MAP_U_RWCB                  MMU_VENDOR_MAP_U_RWCB
#define MMU_MAP_U_RW                    MMU_VENDOR_MAP_U_RW
#define MMU_MAP_U_DEVICE                MMU_VENDOR_MAP_U_DEVICE

#define MMU_MAP_ERROR_VANOTALIGN        -1
#define MMU_MAP_ERROR_PANOTALIGN        -2
#define MMU_MAP_ERROR_NOPAGE            -3
#define MMU_MAP_ERROR_CONFLICT          -4

#define ARCH_VADDR_WIDTH                rt_hw_arch_vaddr_width
#define ARCH_ADDRESS_WIDTH_BITS         __riscv_xlen

#define ARCH_MAP_FAILED                 _AT(void *, _ULL(-1))

#define ARCH_EARLY_MAP_SIZE             0x80000000

#ifndef __ASSEMBLY__

struct rt_aspace;

extern rt_uint8_t rt_hw_arch_vaddr_width;

void *rt_hw_mmu_tbl_get(void);
void rt_hw_mmu_tbl_set(unsigned long tbl);
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

#ifndef MMU_VENDOR_ATTR_RM_PERM_IMPL
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
        attr &= ~PTE_W;
        break;
    /* remove write permission for kernel */
    case RT_HW_MMU_PROT_WRITE | RT_HW_MMU_PROT_KERNEL:
        attr &= ~PTE_W;
        break;
    default:
        RT_ASSERT(0);
    }
    return attr;
}
#endif /* MMU_VENDOR_ATTR_RM_PERM_IMPL */

#ifndef MMU_VENDOR_ATTR_ADD_PERM_IMPL
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
        attr |= (PTE_R | PTE_W | PTE_U);
        break;
    default:
        RT_ASSERT(0);
    }
    return attr;
}
#endif /* MMU_VENDOR_ATTR_ADD_PERM_IMPL */

#ifndef MMU_VENDOR_ATTR_TEST_PERM_IMPL
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

    switch (prot & ~RT_HW_MMU_PROT_USER)
    {
    /* test write permission for user */
    case RT_HW_MMU_PROT_WRITE:
        rc = ((attr & PTE_W) && (attr & PTE_R));
        break;
    case RT_HW_MMU_PROT_READ:
        rc = !!(attr & PTE_R);
        break;
    case RT_HW_MMU_PROT_EXECUTE:
        rc = !!(attr & PTE_X);
        break;
    default:
        RT_ASSERT(0);
    }

    if (rc && (prot & RT_HW_MMU_PROT_USER))
    {
        rc = !!(attr & PTE_U);
    }
    return rc;
}
#endif /* MMU_VENDOR_ATTR_TEST_PERM_IMPL */

#endif /* !__ASSEMBLY__ */

#endif /* __MMU_H__ */
