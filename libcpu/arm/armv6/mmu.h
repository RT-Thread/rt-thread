/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __MMU_H__
#define __MMU_H__

#include <rtthread.h>

#define CACHE_LINE_SIZE 32

/*
 * Hardware page table definitions.
 *
 * + Level 1 descriptor (PGD)
 *   - common
 */
#define PGD_TYPE_MASK       (3 << 0)
#define PGD_TYPE_FAULT      (0 << 0)
#define PGD_TYPE_TABLE      (1 << 0)
#define PGD_TYPE_SECT       (2 << 0)
#define PGD_BIT4            (1 << 4)
#define PGD_DOMAIN(x)       ((x) << 5)
#define PGD_PROTECTION      (1 << 9)    /* ARMv5 */
/*
 *   - section
 */
#define PGD_SECT_BUFFERABLE (1 << 2)
#define PGD_SECT_CACHEABLE  (1 << 3)
#define PGD_SECT_XN         (1 << 4)    /* ARMv6 */
#define PGD_SECT_AP0        (1 << 10)
#define PGD_SECT_AP1        (1 << 11)
#define PGD_SECT_TEX(x)     ((x) << 12) /* ARMv5 */
#define PGD_SECT_APX        (1 << 15)   /* ARMv6 */
#define PGD_SECT_S          (1 << 16)   /* ARMv6 */
#define PGD_SECT_nG         (1 << 17)   /* ARMv6 */
#define PGD_SECT_SUPER      (1 << 18)   /* ARMv6 */

#define PGD_SECT_UNCACHED   (0)
#define PGD_SECT_BUFFERED   (PGD_SECT_BUFFERABLE)
#define PGD_SECT_WT         (PGD_SECT_CACHEABLE)
#define PGD_SECT_WB         (PGD_SECT_CACHEABLE | PGD_SECT_BUFFERABLE)
#define PGD_SECT_MINICACHE  (PGD_SECT_TEX(1) | PGD_SECT_CACHEABLE)
#define PGD_SECT_WBWA       (PGD_SECT_TEX(1) | PGD_SECT_CACHEABLE | PGD_SECT_BUFFERABLE)
#define PGD_SECT_NONSHARED_DEV  (PGD_SECT_TEX(2))


/*
 * + Level 2 descriptor (PTE)
 *   - common
 */
#define PTE_TYPE_MASK       (3 << 0)
#define PTE_TYPE_FAULT      (0 << 0)
#define PTE_TYPE_LARGE      (1 << 0)
#define PTE_TYPE_SMALL      (2 << 0)
#define PTE_TYPE_EXT        (3 << 0)    /* ARMv5 */
#define PTE_BUFFERABLE      (1 << 2)
#define PTE_CACHEABLE       (1 << 3)

/*
 *   - extended small page/tiny page
 */
#define PTE_EXT_XN          (1 << 0)    /* ARMv6 */
#define PTE_EXT_AP_MASK     (3 << 4)
#define PTE_EXT_AP0         (1 << 4)
#define PTE_EXT_AP1         (2 << 4)
#define PTE_EXT_AP_UNO_SRO  (0 << 4)
#define PTE_EXT_AP_UNO_SRW  (PTE_EXT_AP0)
#define PTE_EXT_AP_URO_SRW  (PTE_EXT_AP1)
#define PTE_EXT_AP_URW_SRW  (PTE_EXT_AP1|PTE_EXT_AP0)
#define PTE_EXT_TEX(x)      ((x) << 6)  /* ARMv5 */
#define PTE_EXT_APX         (1 << 9)    /* ARMv6 */
#define PTE_EXT_SHARED      (1 << 10)   /* ARMv6 */
#define PTE_EXT_NG          (1 << 11)   /* ARMv6 */

/*
 *   - small page
 */
#define PTE_SMALL_AP_MASK       (0xff << 4)
#define PTE_SMALL_AP_UNO_SRO    (0x00 << 4)
#define PTE_SMALL_AP_UNO_SRW    (0x55 << 4)
#define PTE_SMALL_AP_URO_SRW    (0xaa << 4)
#define PTE_SMALL_AP_URW_SRW    (0xff << 4)


/*
 *  sector table properities
 */
#define SECT_CB          (PGD_SECT_CACHEABLE|PGD_SECT_BUFFERABLE) //cache_on, write_back
#define SECT_CNB         (PGD_SECT_CACHEABLE)                     //cache_on, write_through
#define SECT_NCB         (PGD_SECT_BUFFERABLE)                    //cache_off,WR_BUF on
#define SECT_NCNB        (0 << 2)                                 //cache_off,WR_BUF off

#define SECT_AP_RW       (PGD_SECT_AP0|PGD_SECT_AP1)              //supervisor=RW, user=RW
#define SECT_AP_RO       (PGD_SECT_AP0|PGD_SECT_AP1|PGD_SECT_APX) //supervisor=RO, user=RO

#define SECT_RWX_CB      (SECT_AP_RW|PGD_DOMAIN(0)|PGD_SECT_WB|PGD_TYPE_SECT) /* Read/Write/executable, cache, write back */
#define SECT_RWX_CNB     (SECT_AP_RW|PGD_DOMAIN(0)|PGD_SECT_WT|PGD_TYPE_SECT) /* Read/Write/executable, cache, write through */
#define SECT_RWX_NCNB    (SECT_AP_RW|PGD_DOMAIN(0)|PGD_TYPE_SECT) /* Read/Write/executable without cache and write buffer */
#define SECT_RWX_FAULT   (SECT_AP_RW|PGD_DOMAIN(1)|PGD_TYPE_SECT) /* Read/Write without cache and write buffer */

#define SECT_RWNX_CB     (SECT_AP_RW|PGD_DOMAIN(0)|PGD_SECT_WB|PGD_TYPE_SECT|PGD_SECT_XN) /* Read/Write, cache, write back */
#define SECT_RWNX_CNB    (SECT_AP_RW|PGD_DOMAIN(0)|PGD_SECT_WT|PGD_TYPE_SECT|PGD_SECT_XN) /* Read/Write, cache, write through */
#define SECT_RWNX_NCNB   (SECT_AP_RW|PGD_DOMAIN(0)|PGD_TYPE_SECT|PGD_SECT_XN) /* Read/Write without cache and write buffer */
#define SECT_RWNX_FAULT  (SECT_AP_RW|PGD_DOMAIN(1)|PGD_TYPE_SECT|PGD_SECT_XN) /* Read/Write without cache and write buffer */


#define SECT_ROX_CB      (SECT_AP_RO|PGD_DOMAIN(0)|PGD_SECT_WB|PGD_TYPE_SECT) /* Read Only/executable, cache, write back */
#define SECT_ROX_CNB     (SECT_AP_RO|PGD_DOMAIN(0)|PGD_SECT_WT|PGD_TYPE_SECT) /* Read Only/executable, cache, write through */
#define SECT_ROX_NCNB    (SECT_AP_RO|PGD_DOMAIN(0)|PGD_TYPE_SECT) /* Read Only/executable without cache and write buffer */
#define SECT_ROX_FAULT   (SECT_AP_RO|PGD_DOMAIN(1)|PGD_TYPE_SECT) /* Read Only without cache and write buffer */

#define SECT_RONX_CB     (SECT_AP_RO|PGD_DOMAIN(0)|PGD_SECT_WB|PGD_TYPE_SECT|PGD_SECT_XN) /* Read Only, cache, write back */
#define SECT_RONX_CNB    (SECT_AP_RO|PGD_DOMAIN(0)|PGD_SECT_WT|PGD_TYPE_SECT|PGD_SECT_XN) /* Read Only, cache, write through */
#define SECT_RONX_NCNB   (SECT_AP_RO|PGD_DOMAIN(0)|PGD_TYPE_SECT|PGD_SECT_XN) /* Read Only without cache and write buffer */
#define SECT_RONX_FAULT  (SECT_AP_RO|PGD_DOMAIN(1)|PGD_TYPE_SECT|PGD_SECT_XN) /* Read Only without cache and write buffer */

#define SECT_TO_PAGE     (PGD_DOMAIN(0)|PGD_TYPE_TABLE) /* Level 2 descriptor (PTE) entry properity */

/*
 * page table properities
 */
#define PAGE_CB          (PTE_BUFFERABLE|PTE_CACHEABLE)  //cache_on, write_back
#define PAGE_CNB         (PTE_CACHEABLE)                 //cache_on, write_through
#define PAGE_NCB         (PTE_BUFFERABLE)                //cache_off,WR_BUF on
#define PAGE_NCNB        (0 << 2)                        //cache_off,WR_BUF off

#define PAGE_AP_RW       (PTE_EXT_AP0|PTE_EXT_AP1)             //supervisor=RW, user=RW
#define PAGE_AP_RO       (PTE_EXT_AP0|PTE_EXT_AP1|PTE_EXT_APX) //supervisor=RO, user=RO

#define PAGE_RWX_CB      (PAGE_AP_RW|PAGE_CB|PTE_TYPE_SMALL) /* Read/Write/executable, cache, write back */
#define PAGE_RWX_CNB     (PAGE_AP_RW|PAGE_CNB|PTE_TYPE_SMALL) /* Read/Write/executable, cache, write through */
#define PAGE_RWX_NCNB    (PAGE_AP_RW|PTE_TYPE_SMALL) /* Read/Write/executable without cache and write buffer */
#define PAGE_RWX_FAULT   (PAGE_AP_RW|PTE_TYPE_SMALL) /* Read/Write without cache and write buffer */

#define PAGE_RWNX_CB     (PAGE_AP_RW|PAGE_CB|PTE_TYPE_SMALL|PTE_EXT_XN) /* Read/Write, cache, write back */
#define PAGE_RWNX_CNB    (PAGE_AP_RW|PAGE_CNB|PTE_TYPE_SMALL|PTE_EXT_XN) /* Read/Write, cache, write through */
#define PAGE_RWNX_NCNB   (PAGE_AP_RW|PTE_TYPE_SMALL|PTE_EXT_XN) /* Read/Write without cache and write buffer */
#define PAGE_RWNX_FAULT  (PAGE_AP_RW|PTE_TYPE_SMALL|PTE_EXT_XN) /* Read/Write without cache and write buffer */


#define PAGE_ROX_CB      (PAGE_AP_RO|PAGE_CB|PTE_TYPE_SMALL) /* Read Only/executable, cache, write back */
#define PAGE_ROX_CNB     (PAGE_AP_RO|PAGE_CNB|PTE_TYPE_SMALL) /* Read Only/executable, cache, write through */
#define PAGE_ROX_NCNB    (PAGE_AP_RO|PTE_TYPE_SMALL) /* Read Only/executable without cache and write buffer */
#define PAGE_ROX_FAULT   (PAGE_AP_RO|PTE_TYPE_SMALL) /* Read Only without cache and write buffer */

#define PAGE_RONX_CB     (PAGE_AP_RO|PAGE_CB|PTE_TYPE_SMALL|PTE_EXT_XN) /* Read Only, cache, write back */
#define PAGE_RONX_CNB    (PAGE_AP_RO|PAGE_CNB|PTE_TYPE_SMALL|PTE_EXT_XN) /* Read Only, cache, write through */
#define PAGE_RONX_NCNB   (PAGE_AP_RO|PTE_TYPE_SMALL|PTE_EXT_XN) /* Read Only without cache and write buffer */
#define PAGE_RONX_FAULT  (PAGE_AP_RO|PTE_TYPE_SMALL|PTE_EXT_XN) /* Read Only without cache and write buffer */


#define DESC_SEC        (0x2|(1<<4))
#define CB              (3<<2)  //cache_on, write_back
#define CNB             (2<<2)  //cache_on, write_through
#define NCB             (1<<2)  //cache_off,WR_BUF on
#define NCNB            (0<<2)  //cache_off,WR_BUF off
#define AP_RW           (3<<10) //supervisor=RW, user=RW
#define AP_RO           (2<<10) //supervisor=RW, user=RO

#define DOMAIN_FAULT    (0x0)
#define DOMAIN_CHK      (0x1)
#define DOMAIN_NOTCHK   (0x3)
#define DOMAIN0         (0x0<<5)
#define DOMAIN1         (0x1<<5)

#define DOMAIN0_ATTR    (DOMAIN_CHK<<0)
#define DOMAIN1_ATTR    (DOMAIN_FAULT<<2)

#define RW_CB       (AP_RW|DOMAIN0|CB|DESC_SEC)     /* Read/Write, cache, write back */
#define RW_CNB      (AP_RW|DOMAIN0|CNB|DESC_SEC)    /* Read/Write, cache, write through */
#define RW_NCNB     (AP_RW|DOMAIN0|NCNB|DESC_SEC)   /* Read/Write without cache and write buffer */
#define RW_FAULT    (AP_RW|DOMAIN1|NCNB|DESC_SEC)   /* Read/Write without cache and write buffer */

struct mem_desc {
    rt_uint32_t vaddr_start;
    rt_uint32_t vaddr_end;
    rt_uint32_t paddr_start;
    rt_uint32_t sect_attr;   /* when page mapped */
    rt_uint32_t page_attr;   /* only sector mapped valid */
    rt_uint32_t mapped_mode;
#define     SECT_MAPPED  0
#define     PAGE_MAPPED  1
};

void rt_hw_mmu_init(struct mem_desc *mdesc, rt_uint32_t size);

#endif

