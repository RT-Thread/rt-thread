/*
 * Copyright (c) 2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include "asan.h"
#include "utest.h"

extern "C" void test_asan_cpp(void)
{
    volatile char *p = static_cast<char *>(rt_malloc(16));
    uassert_not_null(p);
    if (!p)
    {
        return;
    }
    rt_uint32_t before = rt_asan_report_count_get();
    p[15] = 1;
    uassert_int_equal(rt_asan_report_count_get(), before);
    p[16] = 2;
    uassert_true(rt_asan_report_count_get() > before);
    rt_free(const_cast<char *>(p));
}
