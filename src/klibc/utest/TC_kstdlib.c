/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-21     Meco Man     the first version
 */

#include <rtklibc.h>
#include <utest.h>

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void TC_rt_memcpy_1(void)
{
    const char src[] = "Hello, memcpy!";
    char dest[20] = {0};
    rt_memcpy(dest, src, sizeof(src));
    uassert_true(rt_strcmp(src, dest) == 0);
}

static void utest_do_tc(void)
{
    UTEST_UNIT_RUN(TC_rt_memcpy_1);
}

UTEST_TC_EXPORT(utest_do_tc, "klibc.kstdlibc", utest_tc_init, utest_tc_cleanup, 1000);
