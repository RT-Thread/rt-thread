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

#ifdef ARCH_MM_MMU

#include <mmu.h>
#include <page.h>
#include <lwp_mm_area.h>
#include <lwp_user_mm.h>
#include <lwp_arch.h>

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
    rt_memcpy(mmu_table + (KERNEL_VADDR_START >> ARCH_SECTION_SHIFT), MMUTable + (KERNEL_VADDR_START >> ARCH_SECTION_SHIFT), ARCH_PAGE_SIZE);
    rt_memset(mmu_table, 0, 3 * ARCH_PAGE_SIZE);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, mmu_table, 4 * ARCH_PAGE_SIZE);
    rt_hw_mmu_map_init(&lwp->mmu_info, (void*)USER_VADDR_START, USER_VADDR_TOP - USER_VADDR_START, mmu_table, PV_OFFSET);

    return 0;
}

void *arch_kernel_mmu_table_get(void)
{
    return (void*)((char*)MMUTable + PV_OFFSET);
}

void arch_kuser_init(rt_mmu_info *mmu_info, void *vectors)
{
    extern char __kuser_helper_start[], __kuser_helper_end[];
    int kuser_sz = __kuser_helper_end - __kuser_helper_start;

    rt_hw_mmu_map_auto(mmu_info, vectors, 0x1000, MMU_MAP_U_RO);

    rt_memcpy((void*)((char*)vectors + 0x1000 - kuser_sz), __kuser_helper_start, kuser_sz);
    /*
     * vectors + 0xfe0 = __kuser_get_tls
     * vectors + 0xfe8 = hardware TLS instruction at 0xffff0fe8
     */
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void*)((char*)vectors + 0x1000 - kuser_sz), kuser_sz);
    rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, (void*)((char*)vectors + 0x1000 - kuser_sz), kuser_sz);
}

void arch_user_space_vtable_free(struct rt_lwp *lwp)
{
    if (lwp && lwp->mmu_info.vtable)
    {
        rt_pages_free(lwp->mmu_info.vtable, 2);
    }
}

int arch_expand_user_stack(void *addr)
{
    int ret = 0;
    size_t stack_addr = (size_t)addr;

    stack_addr &= ~ARCH_PAGE_MASK;
    if ((stack_addr >= (size_t)USER_STACK_VSTART) && (stack_addr < (size_t)USER_STACK_VEND))
    {
        void *map = lwp_map_user(lwp_self(), (void*)stack_addr, ARCH_PAGE_SIZE, 0);

        if (map || lwp_user_accessable(addr, 1))
        {
            ret = 1;
        }
    }
    return ret;
}

#ifdef LWP_ENABLE_ASID
#define MAX_ASID_BITS 8
#define MAX_ASID (1 << MAX_ASID_BITS)
static uint64_t global_generation = 1;
static char asid_valid_bitmap[MAX_ASID];
unsigned int arch_get_asid(struct rt_lwp *lwp)
{
    if (lwp == RT_NULL)
    {
        // kernel
        return 0;
    }

    if (lwp->generation == global_generation)
    {
        return lwp->asid;
    }

    if (lwp->asid && !asid_valid_bitmap[lwp->asid])
    {
        asid_valid_bitmap[lwp->asid] = 1;
        return lwp->asid;
    }

    for (unsigned i = 1; i < MAX_ASID; i++)
    {
        if (asid_valid_bitmap[i] == 0)
        {
            asid_valid_bitmap[i] = 1;
            lwp->generation = global_generation;
            lwp->asid = i;
            return lwp->asid;
        }
    }

    global_generation++;
    memset(asid_valid_bitmap, 0, MAX_ASID * sizeof(char));

    asid_valid_bitmap[1] = 1;
    lwp->generation = global_generation;
    lwp->asid = 1;

    asm volatile ("mcr p15, 0, r0, c8, c7, 0\ndsb\nisb" ::: "memory");

    return lwp->asid;
}
#endif

#endif
