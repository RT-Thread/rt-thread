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

#include <rtthread.h>
#include <utest.h>

#define TEST_BUF_SIZE 400

static char *buf;
static char *buf2;

static rt_err_t utest_tc_init(void)
{
    buf = rt_malloc(TEST_BUF_SIZE * sizeof(char));
    uassert_not_null(buf);
    buf2 = rt_malloc(TEST_BUF_SIZE * sizeof(char));
    uassert_not_null(buf2);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_free(buf);
    rt_free(buf2);
    return RT_EOK;
}

static void test_align(int align, size_t len)
{
    char *s = (char *)RT_ALIGN(((rt_ubase_t)buf + 64), 64) + align;
    char *want = (char *)RT_ALIGN(((rt_ubase_t)buf2 + 64), 64) + align;
    char *p;
    int i;

    uassert_false(len + 64 > (size_t)(buf + TEST_BUF_SIZE - s));
    uassert_false(len + 64 > (size_t)(buf2 + TEST_BUF_SIZE - want));

    for(i = 0; i < TEST_BUF_SIZE; i++)
    {
        buf[i] = buf2[i] = ' ';
    }

    for(i = 0; i < (int)len; i++)
    {
        want[i] = '#';
    }

    p = rt_memset(s, '#', len);

    uassert_ptr_equal(p, s);

    for(i = -64; i < (int)len + 64; i++)
    {
        uassert_int_equal(s[i], want[i]);
    }
}

static void TC_rt_memcpy_align(void)
{
    for(int i = 0; i < 16; i++)
    {
        for(size_t j = 0; j < 200; j++)
        {
            test_align(i, j);
        }
    }
}

static void test_input(char c)
{
    rt_memset(buf, c, 10);
    for(int i = 0; i < 10; i++)
    {
        uassert_int_equal(buf[i], c);
    }
}

static void TC_rt_memcpy_input(void)
{
    test_input('c');
    test_input(0);
    test_input(-1);
    test_input(0xab);
    test_input((char)RT_UINT32_MAX);
    test_input((char)-RT_UINT32_MAX);
}

static void utest_do_tc(void)
{
    UTEST_UNIT_RUN(TC_rt_memcpy_align);
    UTEST_UNIT_RUN(TC_rt_memcpy_input);
}

UTEST_TC_EXPORT(utest_do_tc, "klibc.rt_memset", utest_tc_init, utest_tc_cleanup, 1000);
