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

#define N 80 /**< Define the constant N for buffer size as 80 */
#define TEST_BUF_SIZE 512 /**< Define the constant TEST_BUF_SIZE as 512 */
static char *buf; /**< Define a static buffer of 512 bytes, initialized to 0 */

static rt_err_t utest_tc_init(void)
{
    buf = rt_malloc(TEST_BUF_SIZE * sizeof(char)); /**< Allocate memory for the buffer */
    uassert_not_null(buf);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_free(buf);
    return RT_EOK;
}

/**
 * Test memory copy with alignment.
 * @param dalign The alignment offset for the destination buffer.
 * @param salign The alignment offset for the source buffer.
 * @param len The length of data to copy.
 */
static void test_align(unsigned dalign, unsigned salign, size_t len)
{
    char *src = (char *)RT_ALIGN((rt_ubase_t)buf, 64); /**< Source buffer starting address, 64-byte aligned */
    char *dst = (char *)RT_ALIGN(((rt_ubase_t)buf + 128), 64); /**< Destination buffer starting address, 64-byte aligned from buf+128 */
    char *want = (char *)RT_ALIGN(((rt_ubase_t)buf + 256), 64); /**< Expected result buffer starting address, 64-byte aligned from buf+256 */
    char *p; /**< Pointer to receive the return value of rt_memcpy */
    unsigned i;

    /** Assert that the source alignment offset plus length does not exceed N */
    uassert_false(salign + len > N);
    /** Assert that the destination alignment offset plus length does not exceed N */
    uassert_false(dalign + len > N);

    /** Initialize all buffers with '#' or ' ' */
    for(i = 0; i < N; i++)
    {
        src[i] = '#';
        dst[i] = want[i] = ' ';
    }

    /** Set data in the specified alignment offsets of the source and expected result buffers */
    for(i = 0; i < len; i++)
    {
        src[salign + i] = want[dalign + i] = (char)('0' + i);
    }

    /** Call rt_memcpy to copy data */
    p = rt_memcpy(dst + dalign, src + salign, len);

    /** Assert that the return value of rt_memcpy is the pointer to the start of the copied data in the destination buffer */
    uassert_ptr_equal(p, dst + dalign);

    /** Assert that the content of the destination buffer matches the expected result buffer */
    for(i = 0; i < N; i++)
    {
        uassert_int_equal(dst[i], want[i]);
    }
}

/**
 * Test case to iterate over all possible alignment offsets and length combinations.
 */
static void TC_rt_memcpy_align(void)
{
    for(unsigned i = 0; i < 16; i++) /**< Iterate over source alignment offsets from 0 to 15 */
    {
        for(unsigned j = 0; j < 16; j++) /**< Iterate over destination alignment offsets from 0 to 15 */
        {
            for(size_t k = 0; k < 64; k++) /**< Iterate over data lengths from 0 to 63 */
            {
                test_align(i, j, k); /**< Call the test_align function */
            }
        }
    }
}

static void TC_rt_memcpy_str(void)
{
    const char src[] = "Hello, memcpy!";
    char dest[20] = {0};
    rt_memcpy(dest, src, sizeof(src));
    uassert_true(rt_strcmp(src, dest) == 0);
}

static void utest_do_tc(void)
{
    UTEST_UNIT_RUN(TC_rt_memcpy_str);
    UTEST_UNIT_RUN(TC_rt_memcpy_align);
}

UTEST_TC_EXPORT(utest_do_tc, "klibc.rt_memcpy", utest_tc_init, utest_tc_cleanup, 1000);
