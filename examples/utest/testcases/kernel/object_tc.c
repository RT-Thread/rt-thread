/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-18     kurisaW      First commit
 */

#include <utest.h>
#include <rtthread.h>
#include <string.h>

/**
 * @brief   Test case for verifying object name handling functionality
 *
 * @note    This test suite validates:
 *          1. Proper truncation of long object names
 *          2. Correct NULL name handling
 *          3. Exact length name preservation
 *          4. Both static and dynamic object initialization
 *          5. Memory safety and boundary conditions
 */

static void test_object_name_handling(void)
{
    struct rt_object static_obj1;
    struct rt_object static_obj2;
    struct rt_object static_obj3;
    rt_object_t dyn_obj = RT_NULL;
    char test_name[RT_NAME_MAX + 5];

    for (int i = 0; i < sizeof(test_name) - 1; i++)
    {
        test_name[i] = 'A' + (i % 26);
    }
    test_name[sizeof(test_name) - 1] = '\0';

    /* Test 1: Static Object Initialization - Extra Long Name */
    rt_object_init(&static_obj1, RT_Object_Class_Thread, test_name);
    uassert_true(rt_strlen(static_obj1.name) <= RT_NAME_MAX - 1);
    uassert_true(static_obj1.name[RT_NAME_MAX - 1] == '\0');

    /* Test 2: Dynamic Object Allocation */
    dyn_obj = rt_object_allocate(RT_Object_Class_Thread, test_name);
    uassert_not_null(dyn_obj);
    if (dyn_obj)
    {
        uassert_true(rt_strlen(dyn_obj->name) <= RT_NAME_MAX - 1);
        uassert_true(dyn_obj->name[RT_NAME_MAX - 1] == '\0');
        rt_object_delete(dyn_obj);
        dyn_obj = RT_NULL;
    }

    /* Test 3: NULL Name Handling - Using New Static Object */
    rt_object_init(&static_obj2, RT_Object_Class_Thread, NULL);
    uassert_true(static_obj2.name[0] == '\0');

    /* Test 4: Dynamic Object with NULL Name */
    dyn_obj = rt_object_allocate(RT_Object_Class_Thread, NULL);
    uassert_not_null(dyn_obj);
    if (dyn_obj)
    {
        uassert_true(dyn_obj->name[0] == '\0');
        rt_object_delete(dyn_obj);
        dyn_obj = RT_NULL;
    }

    /* Test 5: Fixed-Length Name - Using Third Static Object */
    char exact_name[RT_NAME_MAX];
    rt_memset(exact_name, 'B', RT_NAME_MAX - 1);
    exact_name[RT_NAME_MAX - 1] = '\0';

    rt_object_init(&static_obj3, RT_Object_Class_Thread, exact_name);
    uassert_str_equal(static_obj3.name, exact_name);

    rt_object_detach(&static_obj1);
    rt_object_detach(&static_obj2);
    rt_object_detach(&static_obj3);
}

static rt_err_t testcase_init(void)
{
    return RT_EOK;
}

static rt_err_t testcase_cleanup(void)
{
    return RT_EOK;
}

static void test_object_suite(void)
{
    UTEST_UNIT_RUN(test_object_name_handling);
}
UTEST_TC_EXPORT(test_object_suite, "testcases.kernel.object_test", testcase_init, testcase_cleanup, 10);
