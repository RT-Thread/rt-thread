/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-18     Parthiban    first version
 */

#include <rtthread.h>
#include "utest.h"

static volatile int ctor_value;

struct GlobalObject
{
    GlobalObject()
    {
        ctor_value = 42;
    }
};

static GlobalObject global_object;

static void test_global_ctor(void)
{
    uassert_int_equal(ctor_value, 42);
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_global_ctor);
}
UTEST_TC_EXPORT(testcase, "testcases.bsp.rh850.cxx_ctor", RT_NULL, RT_NULL, 10);
