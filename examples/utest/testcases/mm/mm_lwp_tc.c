/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-27     WangXiaoyao  testcase for lwp
 */

#include "common.h"
#include <lwp.h>
#include "lwp_arch.h"
#include "lwp_user_mm.h"
#include "mm_aspace.h"
#include "mmu.h"

/**
 * @brief user map API
 * rt_varea_t lwp_map_user_varea(struct rt_lwp *lwp, void *map_va, size_t map_size);
 * rt_varea_t lwp_map_user_varea_ext(struct rt_lwp *lwp, void *map_va, size_t map_size, size_t flags);
 */
#if 1 /* make it clear to identify the block :) */
    /* for testing on _aspace_traverse */
    static void *_prev_end;
    static size_t _count;
    static int _test_increase(rt_varea_t varea, void *param)
    {
        uassert_true(varea->start >= _prev_end);
        _prev_end = varea->start + varea->size;
        _count += 1;
        return 0;
    }
    #define TEST_VAREA_INSERT(statement, aspace) do {\
        size_t _prev_count; \
        _count = 0;         \
        _prev_end = 0;      \
        rt_aspace_traversal((aspace), _test_increase, NULL);\
        _prev_count = _count; \
        statement;          \
        _count = 0;         \
        _prev_end = 0;      \
        rt_aspace_traversal((aspace), _test_increase, NULL);\
        uassert_true(_prev_count + 1 == _count); \
        } while (0)
#endif

static void test_user_map_varea(void)
{
    const size_t buf_sz = ARCH_PAGE_SIZE * 4;
    struct rt_lwp *lwp;
    rt_varea_t varea;
    lwp = lwp_new();

    /* prepare environment */
    uassert_true(!!lwp);
    uassert_true(!lwp_user_space_init(lwp, 1));
    TEST_VAREA_INSERT(
        varea = lwp_map_user_varea(lwp, 0, buf_sz),
        lwp->aspace);
    uassert_true(!!varea);
    uassert_true(varea->attr == (MMU_MAP_U_RWCB));
    uassert_true(varea->size == buf_sz);
    uassert_true(varea->aspace == lwp->aspace);
    uassert_true(varea->flag == 0);
    uassert_true(varea->start != 0);
    uassert_true(varea->start >= (void *)USER_VADDR_START && varea->start < (void *)USER_VADDR_TOP);

    uassert_true(!lwp_ref_dec(lwp));
}

static void test_user_map_varea_ext(void)
{
    const size_t buf_sz = ARCH_PAGE_SIZE * 4;
    struct rt_lwp *lwp;
    rt_varea_t varea;
    lwp = lwp_new();

    uassert_true(!!lwp);
    uassert_true(!lwp_user_space_init(lwp, 1));

    TEST_VAREA_INSERT(
        varea = lwp_map_user_varea_ext(lwp, 0, buf_sz, LWP_MAP_FLAG_NOCACHE),
        lwp->aspace);
    uassert_true(!!varea);
    uassert_true(varea->attr == (MMU_MAP_U_RW));
    uassert_true(varea->size == buf_sz);
    uassert_true(varea->aspace == lwp->aspace);
    uassert_true(varea->flag == 0);
    uassert_true(varea->start != 0);
    uassert_true(varea->start >= (void *)USER_VADDR_START && varea->start < (void *)USER_VADDR_TOP);

    uassert_true(!lwp_ref_dec(lwp));
}

static void user_map_varea_tc(void)
{
    CONSIST_HEAP(test_user_map_varea());
    CONSIST_HEAP(test_user_map_varea_ext());
}

static void test_user_accessible(void)
{
    /* Prepare Environment */
    char *test_address = (char *)(USER_STACK_VEND);
    struct rt_lwp *lwp;
    lwp = lwp_new();
    uassert_true(!!lwp);
    uassert_true(!lwp_user_space_init(lwp, 0));

    /* test if user accessible can operate */
    uassert_true(!lwp_user_accessible_ext(lwp, test_address + 0x1, 0x1));
    /* test if mapping exist, accessible can fill the page and return True */
    uassert_true(lwp_user_accessible_ext(lwp, test_address - 0x10, 0x10));

    /* Cleanup */
    lwp_ref_dec(lwp);
}

static void accessible_tc(void)
{
    CONSIST_HEAP(test_user_accessible());
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(user_map_varea_tc);
    UTEST_UNIT_RUN(accessible_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.lwp.mm_tc", utest_tc_init, utest_tc_cleanup, 20);
