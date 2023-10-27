/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-17     Shell        test case for aspace_map(MAP_FIXED)
 */
#include "common.h"
#include "lwp_user_mm.h"
#include "utest_assert.h"
#include <mm_aspace.h>

#include <rtthread.h>

static struct rt_lwp *lwp;
static size_t former_vsz;
static size_t former_vcount;

static void *vaddr = (void *)0x100000000;
static size_t ex_size = 0x5000;
static char *override_start;
static size_t override_size = 0x2000;
static long fd = -1;
static long pgoffset = 0;
static size_t ex_prot = PROT_NONE;
static size_t ex_flags = MAP_PRIVATE | MAP_ANONYMOUS;
static size_t override_prot = PROT_READ | PROT_WRITE;
static size_t override_flags = MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED;

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

static char put_data[] = "hello,world";

static void test_map_fixed(void)
{
    void *effect_override;

    former_vsz = rt_aspace_count_vsz(lwp->aspace);
    former_vcount = count_vcount(lwp->aspace);

    /* create an existed mapping */
    vaddr = lwp_mmap2(lwp, vaddr, ex_size, ex_prot, ex_flags, fd, pgoffset);
    uassert_true((long)vaddr > 0);
    utest_int_equal(former_vsz + ex_size, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount + 1, count_vcount(lwp->aspace));
    former_vsz += ex_size;
    former_vcount += 1;

    /* fix private in the middle */
    override_start = (char *)vaddr + 0x1000;
    effect_override = lwp_mmap2(lwp, override_start, override_size, override_prot, override_flags, fd, pgoffset);
    uassert_true(effect_override == override_start);
    utest_int_equal(former_vsz, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount + 2, count_vcount(lwp->aspace));
    utest_int_equal(
        lwp_data_put(lwp, effect_override, put_data, sizeof(put_data)),
        sizeof(put_data)
    );

    utest_int_equal(RT_EOK, rt_aspace_unmap_range(lwp->aspace, vaddr, ex_size));
}

static void aspace_unmap_tc(void)
{
    test_map_fixed();
}

static rt_size_t total, used, max_used;
static rt_size_t totala, useda, max_useda;
static rt_ubase_t level;
static rt_err_t utest_tc_init(void)
{
    lwp = lwp_create(0);
    if (lwp)
        lwp_user_space_init(lwp, 1);
    else
        return -RT_ENOMEM;

    /* stats */
    level = rt_heap_lock();
    rt_memory_info(&total, &used, &max_used);

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    lwp_ref_dec(lwp);

    /* check */
    rt_memory_info(&totala, &useda, &max_useda);
    rt_heap_unlock(level);
    utest_int_equal(total, totala);
    utest_int_less_equal(useda, used);

    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(aspace_unmap_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.lwp.mman.mmap_anon.fix_private", utest_tc_init, utest_tc_cleanup, 10);
