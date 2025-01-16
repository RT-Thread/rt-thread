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

static void TC_rt_memcmp_str(void)
{
    const char* s = "abc 123";

    uassert_int_equal(rt_memcmp("abc", "abc", 4), 0);
    uassert_int_equal(rt_memcmp(s, "abc", 3), 0);
    uassert_int_equal(rt_memcmp("abc", s, 3), 0);

    /* The following tests intentionally use a length > 3 */
    /* To test what rt_memcmp does in such a situation */
    uassert_value_greater(rt_memcmp(s, "abc", 6), 0);
    uassert_value_less(rt_memcmp("abc", s, 6), 0);
}

static void TC_rt_memcmp_int_array(void)
{
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5};
    int arr3[] = {1, 2, 3, 4, 6};

    uassert_int_equal(rt_memcmp(arr1, arr2, sizeof(arr1)), 0);
    uassert_value_less(rt_memcmp(arr1, arr3, sizeof(arr1)), 0);
    uassert_value_greater(rt_memcmp(arr3, arr1, sizeof(arr1)), 0);
}

static void TC_rt_memcmp_float_array(void)
{
    float arr1[] = {1.0f, 2.0f, 3.0f};
    float arr2[] = {1.0f, 2.0f, 3.0f};
    float arr3[] = {1.0f, 2.0f, 3.1f};

    uassert_int_equal(rt_memcmp(arr1, arr2, sizeof(arr1)), 0);
    uassert_value_less(rt_memcmp(arr1, arr3, sizeof(arr1)), 0);
    uassert_value_greater(rt_memcmp(arr3, arr1, sizeof(arr1)), 0);
}

typedef struct {
    int id;
    float value;
} Item;

static void TC_rt_memcmp_struct_array(void)
{
    Item arr1[] = {{1, 1.0f}, {2, 2.0f}};
    Item arr2[] = {{1, 1.0f}, {2, 2.0f}};
    Item arr3[] = {{1, 1.0f}, {2, 2.1f}};

    uassert_int_equal(rt_memcmp(arr1, arr2, sizeof(arr1)), 0);
    uassert_value_less(rt_memcmp(arr1, arr3, sizeof(arr1)), 0);
    uassert_value_greater(rt_memcmp(arr3, arr1, sizeof(arr1)), 0);
}

typedef struct {
    int id;
    float value;
    char name[10];
} MixedItem;

static void TC_rt_memcmp_mixed_array(void)
{
    MixedItem arr1[] = {{1, 1.0f, "item1"}, {2, 2.0f, "item2"}};
    MixedItem arr2[] = {{1, 1.0f, "item1"}, {2, 2.0f, "item2"}};
    MixedItem arr3[] = {{1, 1.0f, "item1"}, {2, 2.1f, "item2"}};

    uassert_int_equal(rt_memcmp(arr1, arr2, sizeof(arr1)), 0);
    uassert_value_less(rt_memcmp(arr1, arr3, sizeof(arr1)), 0);
    uassert_value_greater(rt_memcmp(arr3, arr1, sizeof(arr1)), 0);
}

typedef struct {
    int id;
    float score;
} Student;

typedef struct {
    Student students[3];
    char className[10];
} Class;

static void TC_rt_memcmp_nested_struct_array(void)
{
    Class class1 = {
        .students = {{1, 90.5}, {2, 85.0}, {3, 92.0}},
        .className = "ClassA"
    };

    Class class2 = {
        .students = {{1, 90.5}, {2, 85.0}, {3, 92.0}},
        .className = "ClassA"
    };

    Class class3 = {
        .students = {{1, 90.5}, {2, 85.1}, {3, 92.0}},
        .className = "ClassA"
    };

    uassert_int_equal(rt_memcmp(&class1, &class2, sizeof(Class)), 0);
    uassert_int_not_equal(rt_memcmp(&class1, &class3, sizeof(Class)), 0);
}

static void TC_rt_memcmp_partial_match(void)
{
    char arr1[] = "abcdefghijklmnopqrstuvwxyz";
    char arr2[] = "abcdefghijklmxyznopqrstuvw";

    uassert_int_equal(rt_memcmp(arr1, arr2, 13), 0);
    uassert_int_not_equal(rt_memcmp(arr1, arr2, sizeof(arr1)), 0);
}

#define LARGE_ARRAY_SIZE 1000

static void TC_rt_memcmp_large_array(void)
{
    int *arr1 = rt_calloc(LARGE_ARRAY_SIZE, sizeof(int));
    int *arr2 = rt_calloc(LARGE_ARRAY_SIZE, sizeof(int));

    uassert_not_null(arr1);
    uassert_not_null(arr2);

    for (int i = 0; i < LARGE_ARRAY_SIZE; i++) {
        arr1[i] = i;
        arr2[i] = i;
    }

    uassert_int_equal(rt_memcmp(arr1, arr2, LARGE_ARRAY_SIZE * sizeof(int)), 0);
    arr2[LARGE_ARRAY_SIZE - 1] = LARGE_ARRAY_SIZE;

    uassert_value_less(rt_memcmp(arr1, arr2, LARGE_ARRAY_SIZE * sizeof(int)), 0);
    uassert_value_greater(rt_memcmp(arr2, arr1, LARGE_ARRAY_SIZE * sizeof(int)), 0);

    rt_free(arr1);
    rt_free(arr2);
}

static void utest_do_tc(void)
{
    UTEST_UNIT_RUN(TC_rt_memcmp_str);
    UTEST_UNIT_RUN(TC_rt_memcmp_int_array);
    UTEST_UNIT_RUN(TC_rt_memcmp_float_array);
    UTEST_UNIT_RUN(TC_rt_memcmp_struct_array);
    UTEST_UNIT_RUN(TC_rt_memcmp_mixed_array);
    UTEST_UNIT_RUN(TC_rt_memcmp_nested_struct_array);
    UTEST_UNIT_RUN(TC_rt_memcmp_partial_match);
    UTEST_UNIT_RUN(TC_rt_memcmp_large_array);
}

UTEST_TC_EXPORT(utest_do_tc, "klibc.rt_memcmp", RT_NULL, RT_NULL, 1000);
