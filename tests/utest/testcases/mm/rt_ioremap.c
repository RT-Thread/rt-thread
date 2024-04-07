/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-14     WangXiaoyao  the first version
 * 2023-03-20     WangXiaoyao  Format & add more testcases for API under mm_aspace.h
 */

#include "common.h"

void ioremap_tc(void)
{
    const size_t bufsz = 0x1000;
    void *paddr = (void *)rt_pages_alloc(rt_page_bits(bufsz)) + PV_OFFSET;
    int *vaddr;
    vaddr = rt_ioremap_cached(paddr, bufsz);
    if (vaddr)
    {
        TC_ASSERT(*vaddr == *(int *)(paddr - PV_OFFSET));

        rt_iounmap(vaddr);
        rt_pages_free(paddr - PV_OFFSET, 0);
    }
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void test_main(void)
{
    CONSIST_HEAP(ioremap_tc());
}
UTEST_TC_EXPORT(test_main, "testcases.mm.ioremap", utest_tc_init, utest_tc_cleanup, 20);
