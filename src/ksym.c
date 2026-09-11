/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>

#ifdef RT_USING_KSYMS

/* These objects are replaced by the generated table when using GCC builds. */
rt_weak volatile const rt_uintptr_t rt_ksym_first_addr = 0;
rt_weak volatile const rt_uint32_t rt_ksym_count = 0;
rt_weak volatile const rt_uint32_t rt_ksym_entries[1][3] = {{0, 0, 0}};
rt_weak const char rt_ksym_names[1] = "";

static rt_uintptr_t _rt_ksym_normalize_addr(rt_uintptr_t addr)
{
#if defined(ARCH_ARM) && !defined(ARCH_CPU_64BIT)
    return addr & ~((rt_uintptr_t)1);
#else
    return addr;
#endif
}

static rt_uintptr_t _rt_ksym_entry_addr(rt_uint32_t index)
{
    return rt_ksym_first_addr + rt_ksym_entries[index][0];
}

rt_err_t rt_ksym_lookup(rt_uintptr_t addr, struct rt_ksym_info *info)
{
    rt_uint32_t low;
    rt_uint32_t high;
    rt_uintptr_t start;
    rt_uint32_t size;

    if (!info)
        return -RT_EINVAL;
    if (rt_ksym_count == 0)
        return -RT_ENOSYS;

    addr = _rt_ksym_normalize_addr(addr);

    if (addr < rt_ksym_first_addr ||
        addr - rt_ksym_first_addr > 0xffffffffu)
        return -RT_ENOENT;

    low = 0;
    high = rt_ksym_count;
    while (high - low > 1)
    {
        rt_uint32_t middle = low + (high - low) / 2;

        if (_rt_ksym_entry_addr(middle) <= addr)
            low = middle;
        else
            high = middle;
    }

    if (_rt_ksym_entry_addr(low) > addr)
        return -RT_ENOENT;

    /* Keep aliases together even if a hand-built table contains them. */
    while (low > 0 &&
           _rt_ksym_entry_addr(low - 1) == _rt_ksym_entry_addr(low))
    {
        low--;
    }

    start = _rt_ksym_entry_addr(low);
    size = rt_ksym_entries[low][2];

    if (size == 0 && addr != start)
        return -RT_ENOENT;
    if (size != 0 && addr - start >= size)
        return -RT_ENOENT;

    info->name = &rt_ksym_names[rt_ksym_entries[low][1]];
    info->start = start;
    info->offset = addr - start;
    info->size = size;

    return RT_EOK;
}

#endif /* RT_USING_KSYMS */
