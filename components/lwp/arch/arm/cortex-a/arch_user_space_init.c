/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-28     Jesven       first version
 */

#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_USERSPACE

#include <mmu.h>
#include <page.h>
#include <lwp_mm_area.h>
#include <lwp_user_mm.h>
#include <lwp_arch.h>

#define USER_HEAP_VADDR  0x80000000
#define USER_VADDR_START 0x00100000

extern size_t MMUTable[];

int arch_user_space_init(struct rt_lwp *lwp)
{
    size_t *mmu_table;

    mmu_table = (size_t*)rt_pages_alloc(2);
    if (!mmu_table)
    {
        return -1;
    }

    lwp->end_heap = USER_HEAP_VADDR;
    memcpy(mmu_table + (KERNEL_VADDR_START >> ARCH_SECTION_SHIFT), MMUTable + (KERNEL_VADDR_START >> ARCH_SECTION_SHIFT), ARCH_PAGE_SIZE);
    memset(mmu_table, 0, 3 * ARCH_PAGE_SIZE);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, mmu_table, 4 * ARCH_PAGE_SIZE);
    rt_hw_mmu_map_init(&lwp->mmu_info, (void*)USER_VADDR_START, KERNEL_VADDR_START - USER_VADDR_START, mmu_table, PV_OFFSET);

    return 0;
}

void *arch_kernel_mmu_table_get(void)
{
    return (void*)MMUTable + PV_OFFSET;
}

void arch_kuser_init(rt_mmu_info *mmu_info, void *vectors)
{
    extern char __kuser_helper_start[], __kuser_helper_end[];
    int kuser_sz = __kuser_helper_end - __kuser_helper_start;

    rt_hw_mmu_map_auto(mmu_info, vectors, 0x1000, MMU_MAP_U_RO);

    rt_memcpy(vectors + 0x1000 - kuser_sz, __kuser_helper_start, kuser_sz);
    /*
     * vectors + 0xfe0 = __kuser_get_tls
     * vectors + 0xfe8 = hardware TLS instruction at 0xffff0fe8
     */
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, vectors + 0x1000 - kuser_sz, kuser_sz);
    rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, vectors + 0x1000 - kuser_sz, kuser_sz);
}
#endif
