/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-25     Meco Man     first version
 */

#include <rtthread.h>
#include <utest.h>

/* Basic move with no overlap */
static void TC_rt_memmove_basic(void)
{
    char src[] = "Hello";
    char dest[10] = {0};
    rt_memmove(dest, src, rt_strlen(src) + 1);
    uassert_str_equal(dest, "Hello");
}

/* Move with overlap (src before dest) */
static void TC_rt_memmove_overlap_src_before(void)
{
    char buffer[] = "1234567890";
    rt_memmove(&buffer[3], buffer, 5);
    uassert_str_equal(buffer, "1231234590");
}

/* Move with overlap (src after dest) */
static void TC_rt_memmove_overlap_src_after(void)
{
    char buffer[] = "1234567890";
    rt_memmove(&buffer[2], &buffer[5], 5);
    uassert_str_equal(buffer, "1267890890");
}

/* Move with zero length */
static void TC_rt_memmove_zero_length(void)
{
    char src[] = "Hello";
    char dest[10] = "World";
    rt_memmove(dest, src, 0);
    uassert_str_equal(dest, "World");
}

/* Move to the same location */
static void TC_rt_memmove_same_location(void)
{
    char buffer[] = "Hello";
    rt_memmove(buffer, buffer, rt_strlen(buffer) + 1);
    uassert_str_equal(buffer, "Hello");
}

/* Move from NULL */
static void TC_rt_memmove_null_src(void)
{
    char dest[10];
    rt_memset(dest, 'A', sizeof(dest));
    rt_memmove(dest, RT_NULL, 0); /* Should not crash and do nothing */
    uassert_buf_equal(dest, "AAAAAAAAAA", 10);
}

/* Move to NULL */
static void TC_rt_memmove_null_dest(void)
{
    char src[] = "Hello";
    rt_memmove(RT_NULL, src, 0); /* Should not crash and do nothing */
}

/* Move more than source size */
static void TC_rt_memmove_too_long(void)
{
    char src[] = "Short";
    char dest[10] = {0};
    rt_memmove(dest, src, sizeof(src) + 5); /* Should only copy up to src length */
    uassert_str_equal(dest, "Short");
    uassert_int_equal(dest[5], 0); /* Ensure no buffer overflow */
}

/* Move empty string */
static void TC_rt_memmove_empty_string(void)
{
    char src[] = "";
    char dest[10] = "Unchanged";
    rt_memmove(dest, src, rt_strlen(src) + 1);

    /* Expect dest to only contain '\0' at the start */
    uassert_str_equal(dest, "");  /* Destination should now be an empty string */
    uassert_int_equal(dest[0], '\0'); /* First character should be '\0' */
}

/* Utest function to run all test cases */
static void utest_do_tc(void)
{
    UTEST_UNIT_RUN(TC_rt_memmove_basic);
    UTEST_UNIT_RUN(TC_rt_memmove_overlap_src_before);
    UTEST_UNIT_RUN(TC_rt_memmove_overlap_src_after);
    UTEST_UNIT_RUN(TC_rt_memmove_zero_length);
    UTEST_UNIT_RUN(TC_rt_memmove_same_location);
    UTEST_UNIT_RUN(TC_rt_memmove_null_src);
    UTEST_UNIT_RUN(TC_rt_memmove_null_dest);
    UTEST_UNIT_RUN(TC_rt_memmove_too_long);
    UTEST_UNIT_RUN(TC_rt_memmove_empty_string);
}

UTEST_TC_EXPORT(utest_do_tc, "klibc.rt_memmove", RT_NULL, RT_NULL, 1000);
