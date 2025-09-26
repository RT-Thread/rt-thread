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
 * @brief   Comprehensive test suite for RT-Thread object system
 *
 * @note    This test suite validates:
 *          1. Object name handling (truncation, NULL, exact length)
 *          2. Static and dynamic object initialization
 *          3. Object finding functionality (rt_object_find, rt_thread_find, rt_device_find)
 *          4. Object information and enumeration
 *          5. Type checking and system object detection
 *          6. Memory safety and boundary conditions
 */

/* Define TEST_RT_NAME_MAX for testing purposes */
#define TEST_RT_NAME_MAX RT_NAME_MAX

/* Global counter for unique object names */
static rt_uint32_t name_counter = 0;

/* Generate unique name to avoid conflicts, respecting TEST_RT_NAME_MAX */
static rt_err_t generate_unique_name(char *buf, rt_size_t size, const char *prefix)
{
    if (!buf || !prefix || size < TEST_RT_NAME_MAX)
        return -RT_EINVAL;

    for (int i = 0; i < 1000; i++) /* Limit attempts to prevent infinite loop */
    {
        rt_snprintf(buf, size, "%s%d", prefix, name_counter++);
        rt_size_t len = rt_strlen(buf);
        if (len >= TEST_RT_NAME_MAX)
        {
            buf[TEST_RT_NAME_MAX - 1] = '\0';
            len = TEST_RT_NAME_MAX - 1;
        }

        /* Check if name (or truncated name) is unique */
        if (rt_object_find(buf, RT_Object_Class_Unknown) == RT_NULL &&
            rt_thread_find(buf) == RT_NULL &&
            rt_device_find(buf) == RT_NULL)
        {
            return RT_EOK;
        }
    }
    return -RT_ENOMEM;
}

static void test_object_name_handling(void)
{
    struct rt_object static_obj1, static_obj2, static_obj3;
    rt_object_t dyn_obj = RT_NULL;
    char test_name[TEST_RT_NAME_MAX];
    char unique_name[TEST_RT_NAME_MAX];

    /* Prepare a test name within TEST_RT_NAME_MAX */
    rt_memset(test_name, 'A', TEST_RT_NAME_MAX - 1);
    test_name[TEST_RT_NAME_MAX - 1] = '\0';

    /* Test 1: Static Object with Name Within TEST_RT_NAME_MAX */
    uassert_true(generate_unique_name(unique_name, TEST_RT_NAME_MAX, "long") == RT_EOK);
    rt_object_init(&static_obj1, RT_Object_Class_Thread, test_name);
    uassert_true(rt_strlen(static_obj1.name) <= TEST_RT_NAME_MAX - 1);
    uassert_true(static_obj1.name[TEST_RT_NAME_MAX - 1] == '\0');
    uassert_true(rt_strncmp(static_obj1.name, test_name, TEST_RT_NAME_MAX - 1) == 0);
    uassert_true(rt_object_is_systemobject(&static_obj1));
    rt_object_detach(&static_obj1);

    /* Test 2: Dynamic Object with Name Within TEST_RT_NAME_MAX */
    uassert_true(generate_unique_name(unique_name, TEST_RT_NAME_MAX, "dyn") == RT_EOK);
    dyn_obj = rt_object_allocate(RT_Object_Class_Thread, test_name);
    uassert_not_null(dyn_obj);
    uassert_true(rt_strlen(dyn_obj->name) <= TEST_RT_NAME_MAX - 1);
    uassert_true(dyn_obj->name[TEST_RT_NAME_MAX - 1] == '\0');
    uassert_true(rt_strncmp(dyn_obj->name, test_name, TEST_RT_NAME_MAX - 1) == 0);
    uassert_false(rt_object_is_systemobject(dyn_obj));
    rt_object_delete(dyn_obj);

    /* Test 3: NULL Name Handling */
    uassert_true(generate_unique_name(unique_name, TEST_RT_NAME_MAX, "null") == RT_EOK);
    rt_object_init(&static_obj2, RT_Object_Class_Thread, NULL);
    uassert_true(static_obj2.name[0] == '\0');
    rt_object_detach(&static_obj2);

    uassert_true(generate_unique_name(unique_name, TEST_RT_NAME_MAX, "dynull") == RT_EOK);
    dyn_obj = rt_object_allocate(RT_Object_Class_Thread, NULL);
    uassert_not_null(dyn_obj);
    uassert_true(dyn_obj->name[0] == '\0');
    rt_object_delete(dyn_obj);

    /* Test 4: Exact Length Name */
    char exact_name[TEST_RT_NAME_MAX];
    rt_memset(exact_name, 'B', TEST_RT_NAME_MAX - 1);
    exact_name[TEST_RT_NAME_MAX - 1] = '\0';
    uassert_true(generate_unique_name(unique_name, TEST_RT_NAME_MAX, "exact") == RT_EOK);
    rt_object_init(&static_obj3, RT_Object_Class_Thread, exact_name);
    uassert_str_equal(static_obj3.name, exact_name);
    rt_object_detach(&static_obj3);
}

static void test_object_find_operations(void)
{
    rt_object_t found;
    rt_thread_t found_thread;
    rt_device_t found_device;
    char name[TEST_RT_NAME_MAX];
    rt_err_t ret;

    /* Scenario 1: Object Name Within TEST_RT_NAME_MAX */
    /* Test 1.1: Find static thread object with rt_object_find */
    struct rt_object static_obj;
    uassert_true(generate_unique_name(name, TEST_RT_NAME_MAX, "sobj") == RT_EOK);
    rt_object_init(&static_obj, RT_Object_Class_Thread, name);
    found = rt_object_find(name, RT_Object_Class_Thread);
    uassert_not_null(found);
    uassert_ptr_equal(found, &static_obj);
    uassert_str_equal(found->name, name);
    rt_object_detach(&static_obj);

    /* Test 1.2: Find thread object with rt_thread_find */
    uassert_true(generate_unique_name(name, TEST_RT_NAME_MAX, "thr") == RT_EOK);
    rt_thread_t thread = rt_thread_create(name, RT_NULL, RT_NULL, 1024, 20, 10);
    uassert_not_null(thread);
    found_thread = rt_thread_find(name);
    uassert_not_null(found_thread);
    uassert_ptr_equal(found_thread, thread);
    uassert_str_equal(found_thread->parent.name, name);
    rt_thread_delete(thread);

#ifdef RT_USING_DEVICE
    /* Test 1.3: Find device object with rt_device_find */
    struct rt_device device;
    uassert_true(generate_unique_name(name, TEST_RT_NAME_MAX, "dev") == RT_EOK);
    ret = rt_device_register(&device, name, RT_DEVICE_FLAG_RDONLY);
    uassert_int_equal(ret, RT_EOK);
    found_device = rt_device_find(name);
    uassert_not_null(found_device);
    uassert_ptr_equal(found_device, &device);
    uassert_str_equal(found_device->parent.name, name);
    rt_device_unregister(&device);
#endif

    /* Test 2: Same Prefix Within TEST_RT_NAME_MAX */
#ifdef RT_USING_DEVICE
    struct rt_device dev1, dev2;
    char name1[TEST_RT_NAME_MAX] = "norflash1";
    char name2[TEST_RT_NAME_MAX] = "norflash2";
    ret = rt_device_register(&dev1, name1, RT_DEVICE_FLAG_RDONLY);
    uassert_int_equal(ret, RT_EOK);
    ret = rt_device_register(&dev2, name2, RT_DEVICE_FLAG_RDONLY);
    uassert_int_equal(ret, RT_EOK); /* Expect success if RT-Thread allows distinct names */
    found_device = rt_device_find(name1);
    uassert_not_null(found_device);
    uassert_ptr_equal(found_device, &dev1);
    uassert_str_equal(found_device->parent.name, name1);
    found_device = rt_device_find(name2);
    uassert_not_null(found_device);
    uassert_ptr_equal(found_device, &dev2);
    uassert_str_equal(found_device->parent.name, name2);
    rt_device_unregister(&dev1);
    rt_device_unregister(&dev2);
#endif

    /* Test 3: Find non-existent object */
    const char *nonexist_name = "nonexist";
    uassert_true(rt_strlen(nonexist_name) <= TEST_RT_NAME_MAX - 1);
    found = rt_object_find(nonexist_name, RT_Object_Class_Thread);
    uassert_null(found);

    /* Test 4: Find with NULL name */
    found = rt_object_find(NULL, RT_Object_Class_Thread);
    uassert_null(found);
    found_thread = rt_thread_find(NULL);
    uassert_null(found_thread);

#ifdef RT_USING_DEVICE
    found_device = rt_device_find(NULL);
    uassert_null(found_device);
#endif
}

static void test_object_info_enumeration(void)
{
    struct rt_object static_objs[3];
    rt_object_t dyn_objs[2] = {RT_NULL, RT_NULL};
    char names[5][TEST_RT_NAME_MAX];

    /* Generate unique names */
    for (int i = 0; i < 5; i++)
    {
        uassert_true(generate_unique_name(names[i], TEST_RT_NAME_MAX, "enum") == RT_EOK);
    }

    /* Create test objects */
    for (int i = 0; i < 3; i++)
    {
        rt_object_init(&static_objs[i], RT_Object_Class_Thread, names[i]);
    }
    for (int i = 0; i < 2; i++)
    {
        dyn_objs[i] = rt_object_allocate(RT_Object_Class_Thread, names[i + 3]);
        uassert_not_null(dyn_objs[i]);
    }

    /* Test 1: Get object information */
    struct rt_object_information *info = rt_object_get_information(RT_Object_Class_Thread);
    uassert_not_null(info);
    uassert_int_equal(info->type, RT_Object_Class_Thread);

    /* Test 2: Get object count */
    int count = rt_object_get_length(RT_Object_Class_Thread);
    uassert_true(count >= 5);

    /* Test 3: Get object pointers with sufficient buffer */
    rt_object_t *objects = (rt_object_t *)rt_malloc((count + 2) * sizeof(rt_object_t));
    uassert_not_null(objects);
    int ret = rt_object_get_pointers(RT_Object_Class_Thread, objects, count + 2);
    uassert_int_equal(ret, count);
    int found_count = 0;
    for (int i = 0; i < ret; i++)
    {
        for (int j = 0; j < 3; j++)
            if (objects[i] == &static_objs[j]) found_count++;
        for (int j = 0; j < 2; j++)
            if (objects[i] == dyn_objs[j]) found_count++;
    }
    uassert_int_equal(found_count, 5);
    rt_free(objects);

    /* Test 4: Get object pointers with small buffer */
    rt_object_t one_object[1];
    ret = rt_object_get_pointers(RT_Object_Class_Thread, one_object, 1);
    uassert_true(ret <= 1);

    /* Test 5: Empty container (Semaphore) */
#ifdef RT_USING_SEMAPHORE
    int empty_count = rt_object_get_length(RT_Object_Class_Semaphore);
    uassert_true(empty_count >= 0);
#endif

    /* Cleanup */
    for (int i = 0; i < 3; i++)
        rt_object_detach(&static_objs[i]);
    for (int i = 0; i < 2; i++)
        if (dyn_objs[i]) rt_object_delete(dyn_objs[i]);
}

static void test_object_type_handling(void)
{
    struct rt_object obj;
    char name[TEST_RT_NAME_MAX];
    uassert_true(generate_unique_name(name, TEST_RT_NAME_MAX, "typ") == RT_EOK);
    rt_object_init(&obj, RT_Object_Class_Thread, name);

    /* Test 1: Get object type */
    uassert_int_equal(rt_object_get_type(&obj), RT_Object_Class_Thread);

    /* Test 2: Check system object */
    uassert_true(rt_object_is_systemobject(&obj));

    /* Test 3: Get name with sufficient buffer */
    char name_buf[TEST_RT_NAME_MAX];
    rt_err_t ret = rt_object_get_name(&obj, name_buf, sizeof(name_buf));
    uassert_int_equal(ret, RT_EOK);
    uassert_str_equal(name_buf, name);

    /* Test 4: Get name with small buffer */
    char small_buf[4] = {0};
    ret = rt_object_get_name(&obj, small_buf, sizeof(small_buf));
    uassert_int_equal(ret, RT_EOK);
    uassert_true(rt_strncmp(small_buf, name, sizeof(small_buf) - 1) == 0);
    uassert_true(small_buf[sizeof(small_buf) - 1] == '\0');

    /* Test 5: Get name with invalid parameters */
    ret = rt_object_get_name(RT_NULL, name_buf, sizeof(name_buf));
    uassert_int_equal(ret, -RT_EINVAL);
    ret = rt_object_get_name(&obj, NULL, sizeof(name_buf));
    uassert_int_equal(ret, -RT_EINVAL);
    ret = rt_object_get_name(&obj, name_buf, 0);
    uassert_int_equal(ret, -RT_EINVAL);

    rt_object_detach(&obj);
}

static rt_err_t testcase_init(void)
{
    if (!rt_scheduler_is_available())
    {
        return -RT_ERROR;
    }
    name_counter = 0;
    return RT_EOK;
}

static rt_err_t testcase_cleanup(void)
{
    return RT_EOK;
}

static void test_object_suite(void)
{
#if RT_NAME_MAX < 10
    rt_kprintf("Error: Please increase \'RT_NAME_MAX\' to be greater than 10.\n");
    return;
#endif
    UTEST_UNIT_RUN(test_object_name_handling);
    UTEST_UNIT_RUN(test_object_find_operations);
    UTEST_UNIT_RUN(test_object_info_enumeration);
    UTEST_UNIT_RUN(test_object_type_handling);
}
UTEST_TC_EXPORT(test_object_suite, "core.object", testcase_init, testcase_cleanup, 20);