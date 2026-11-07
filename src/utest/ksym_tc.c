/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include "utest.h"
#include "utest_assert.h"

static void __attribute__((noinline)) ksym_test_level1(void);
static void __attribute__((noinline)) ksym_test_level2(void);
static void __attribute__((noinline)) ksym_test_level3(void);

static void __attribute__((noinline)) ksym_test_level1(void)
{
    ksym_test_level2();
}

static void __attribute__((noinline)) ksym_test_level2(void)
{
    ksym_test_level3();
}

static void __attribute__((noinline)) ksym_test_level3(void)
{
    rt_backtrace();
}

static void test_ksym_lookup(void)
{
    struct rt_ksym_info info;
    rt_uintptr_t address;

    address = (rt_uintptr_t)(void *)ksym_test_level1;
    uassert_int_equal(rt_ksym_lookup(address, &info), RT_EOK);
    uassert_str_equal(info.name, "ksym_test_level1");
    uassert_int_equal(info.start,
#if defined(ARCH_ARM) && !defined(ARCH_CPU_64BIT)
                      address & ~((rt_uintptr_t)1)
#else
                      address
#endif
                      );
    uassert_int_equal(info.offset, 0);

#if defined(ARCH_ARM) && !defined(ARCH_CPU_64BIT)
    uassert_int_equal(rt_ksym_lookup(address | 1, &info), RT_EOK);
    uassert_int_equal(info.offset, 0);
#endif

    uassert_int_equal(rt_ksym_lookup((rt_uintptr_t)-1, &info), -RT_ENOENT);
    uassert_int_equal(rt_ksym_lookup(address, RT_NULL), -RT_EINVAL);
}

static void test_ksym_static_chain(void)
{
    struct rt_ksym_info info;

#if defined(ARCH_ARM_CORTEX_A) || defined(ARCH_ARMV8)
    ksym_test_level1();
#endif
    uassert_int_equal(rt_ksym_lookup((rt_uintptr_t)(void *)ksym_test_level2,
                                     &info), RT_EOK);
    uassert_str_equal(info.name, "ksym_test_level2");
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
    UTEST_UNIT_RUN(test_ksym_lookup);
    UTEST_UNIT_RUN(test_ksym_static_chain);
}

UTEST_TC_EXPORT(testcase, "core.ksym", utest_tc_init, utest_tc_cleanup, 10);
