/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-20     Zhujiale   the first version
 */
#include <rtthread.h>
#include <stdlib.h>
#include <msh.h>
#include "utest.h"
#include "utest_assert.h"
#include "common.h"

void run_copy()
{
    int ret = 0;
    ret     = msh_exec("cd /tmp", 7);
    if (ret != 0)
    {
        LOG_E("errno=%d, ret=%d\n", errno, ret);
        LOG_E("cd /tmp error");
        uassert_false(1);
    }
    uassert_true(1);
    ret = msh_exec("touch test", 10);
    if (ret != 0)
    {
        LOG_E("errno=%d, ret=%d\n", errno, ret);
        LOG_E("touch test error");
        uassert_false(1);
    }
    uassert_true(1);
    ret = msh_exec("echo this_is_a_test_file test", 29);
    if (ret != 0)
    {
        LOG_E("errno=%d, ret=%d\n", errno, ret);
        LOG_E("echo this_is_a_test_file test error");
        uassert_false(1);
    }
    uassert_true(1);
    ret = msh_exec("cp test test1", 13);
    if (ret != 0)
    {
        LOG_E("errno=%d, ret=%d\n", errno, ret);
        LOG_E("cp test test1 error");
        uassert_false(1);
    }

    uassert_true(1);
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
    UTEST_UNIT_RUN(run_copy);
}
UTEST_TC_EXPORT(testcase, "testcase.tfs.tmpfs", utest_tc_init, utest_tc_cleanup, 10);
