/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-22     Shell        test case for aspace_map with varea_expand
 */
#include "common.h"
#include "lwp_user_mm.h"
#include <mm_aspace.h>

#include <rtthread.h>

static size_t flags = MMF_PREFETCH | MMF_MAP_FIXED;
static size_t attr = MMU_MAP_K_RWCB;
static rt_mem_obj_t mem_obj = &rt_mm_dummy_mapper;

static char *ex_vaddr = (void *)0x100000000;
static size_t ex_offset = 1024;
static size_t map_size = 0x3000;

static size_t former_vsz;
static size_t former_vcount;

static struct rt_lwp *lwp;

static int _count_vsz(rt_varea_t varea, void *arg)
{
    rt_base_t *pvsz = arg;
    *pvsz += 1;
    return 0;
}

static rt_base_t count_vcount(rt_aspace_t aspace)
{
    rt_base_t vcount = 0;
    rt_aspace_traversal(aspace, _count_vsz, &vcount);
    return vcount;
}

static void test_map_varea_expand(void)
{
    char *next_va;
    size_t next_offset;

    /* create an existed mapping */
    next_va = ex_vaddr;
    former_vsz = rt_aspace_count_vsz(lwp->aspace);
    former_vcount = count_vcount(lwp->aspace);
    utest_int_equal(
        RT_EOK,
        rt_aspace_map(lwp->aspace, (void *)&ex_vaddr, map_size, attr, flags, mem_obj, ex_offset)
    );
    uassert_true(next_va == ex_vaddr);
    utest_int_equal(former_vsz + map_size, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount + 1, count_vcount(lwp->aspace));
    former_vsz += map_size;
    former_vcount += 1;

    /* test the RIGHT side expansion of varea by rt_aspace_map */
    next_va = ex_vaddr + map_size;
    next_offset = ex_offset + (map_size >> MM_PAGE_SHIFT);
    utest_int_equal(
        RT_EOK,
        rt_aspace_map(lwp->aspace, (void *)&next_va, map_size, attr, flags, mem_obj, next_offset)
    );
    uassert_true(next_va == (char *)ex_vaddr + map_size);
    utest_int_equal(former_vsz + map_size, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount, count_vcount(lwp->aspace));
    former_vsz += map_size;

    /* test the LEFT side expansion of varea by rt_aspace_map */
    next_va = ex_vaddr - map_size;
    next_offset = ex_offset - (map_size >> MM_PAGE_SHIFT);
    utest_int_equal(
        RT_EOK,
        rt_aspace_map(lwp->aspace, (void *)&next_va, map_size, attr, flags, mem_obj, next_offset)
    );
    uassert_true(next_va == ex_vaddr - map_size);
    utest_int_equal(former_vsz + map_size, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount, count_vcount(lwp->aspace));
    former_vsz += map_size;

    /* test the expand varea routine from rt_aspace_map_static */
    utest_int_equal(RT_EOK, rt_aspace_unmap_range(lwp->aspace, next_va, 3 * map_size));

    /* test the expand varea routine from rt_aspace_map_phy */
    /* test the expand varea routine from rt_aspace_map_phy_static */
    /* these 2 from another file */
}

static void aspace_map_tc(void)
{
    CONSIST_HEAP(test_map_varea_expand());
}

static rt_err_t utest_tc_init(void)
{
    lwp = lwp_create(0);
    if (lwp)
        lwp_user_space_init(lwp, 1);
    else
        return -RT_ENOMEM;
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    lwp_ref_dec(lwp);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(aspace_map_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.mm.aspace_map.varea_expand", utest_tc_init, utest_tc_cleanup, 10);
