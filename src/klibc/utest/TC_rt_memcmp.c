/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author             Notes
 * 2020-05-06     Phillip Johnston   the first version
 * 2024-12-24     Meco Man           port to utest
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

static void TC_rt_memcmp_str(void)
{
    const char* s = "abc 123";

    uassert_int_equal(rt_memcmp("abc", "abc", 4), 0);
    uassert_int_equal(rt_memcmp(s, "abc", 3), 0);
    uassert_int_equal(rt_memcmp("abc", s, 3), 0);

    /* The following tests intentionally use a length > 3 */
    /* To test what rt_memcmp does in such a situation */
    uassert_int_equal(!!(rt_memcmp(s, "abc", 6) > 0), 1);
    uassert_int_equal(!!(rt_memcmp("abc", s, 6) < 0), 1);

    /* Check RT_NULL input handling */
    uassert_int_not_equal(rt_memcmp("abc", RT_NULL, 3), 0);
    uassert_int_not_equal(rt_memcmp(RT_NULL, "abc", 3), 0);

    /* Check that two RT_NULL strings will match */
    uassert_int_equal(rt_memcmp(RT_NULL, RT_NULL, 0), 0);
}

static void utest_do_tc(void)
{
    UTEST_UNIT_RUN(TC_rt_memcmp_str);
}

UTEST_TC_EXPORT(utest_do_tc, "klibc.rt_memcmp", utest_tc_init, utest_tc_cleanup, 1000);
