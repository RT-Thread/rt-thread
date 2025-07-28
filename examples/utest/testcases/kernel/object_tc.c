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
 *          1. Object name handling (truncation, NULL, exact length, long names)
 *          2. Static and dynamic object initialization
 *          3. Object finding functionality (rt_object_find, rt_thread_find, rt_device_find)
 *          4. Object information and enumeration
 *          5. Type checking and system object detection
 *          6. Memory safety and boundary conditions
 */

/* Global counter for unique object names */
static rt_uint32_t name_counter = 0;

/* Generate unique name to avoid conflicts, considering RT_NAME_MAX truncation */
static void generate_unique_name(char *buf, rt_size_t size, const char *prefix)
{
    rt_snprintf(buf, size, "%s%d", prefix, name_counter++);
    rt_size_t len = rt_strlen(buf);
    if (len > RT_NAME_MAX - 1)
    {
        len = RT_NAME_MAX - 1;
        buf[len] = '\0';
    }
    /* Check if name (or truncated name) exists */
    while (rt_object_find(buf, RT_Object_Class_Unknown) != RT_NULL ||
           rt_thread_find(buf) != RT_NULL ||
           rt_device_find(buf) != RT_NULL)
    {
        name_counter++;
        rt_snprintf(buf, size, "%s%d", prefix, name_counter);
        len = rt_strlen(buf);
        if (len > RT_NAME_MAX - 1)
        {
            len = RT_NAME_MAX - 1;
            buf[len] = '\0';
        }
    }
    rt_kprintf("Generated unique name: %s\n", buf);
}

static void test_object_name_handling(void)
{
    struct rt_object static_obj1, static_obj2, static_obj3;
    rt_object_t dyn_obj = RT_NULL;
    char test_name[RT_NAME_MAX + 5];
    char unique_name[RT_NAME_MAX];

    /* Prepare a long test name */
    for (int i = 0; i < sizeof(test_name) - 1; i++)
    {
        test_name[i] = 'A' + (i % 26);
    }
    test_name[sizeof(test_name) - 1] = '\0';

    /* Test 1: Static Object with Extra Long Name */
    generate_unique_name(unique_name, RT_NAME_MAX, "long");
    rt_object_init(&static_obj1, RT_Object_Class_Thread, test_name);
    uassert_true(rt_strlen(static_obj1.name) <= RT_NAME_MAX - 1);
    uassert_true(static_obj1.name[RT_NAME_MAX - 1] == '\0');
    uassert_true(rt_strncmp(static_obj1.name, test_name, RT_NAME_MAX - 1) == 0);
    uassert_true(rt_object_is_systemobject(&static_obj1));

    /* Test 2: Dynamic Object with Long Name */
    generate_unique_name(unique_name, RT_NAME_MAX, "dynlong");
    dyn_obj = rt_object_allocate(RT_Object_Class_Thread, test_name);
    uassert_not_null(dyn_obj);
    if (dyn_obj)
    {
        uassert_true(rt_strlen(dyn_obj->name) <= RT_NAME_MAX - 1);
        uassert_true(dyn_obj->name[RT_NAME_MAX - 1] == '\0');
        uassert_true(rt_strncmp(dyn_obj->name, test_name, RT_NAME_MAX - 1) == 0);
        uassert_false(rt_object_is_systemobject(dyn_obj));
        rt_object_delete(dyn_obj);
        dyn_obj = RT_NULL;
    }

    /* Test 3: NULL Name Handling */
    generate_unique_name(unique_name, RT_NAME_MAX, "null");
    rt_object_init(&static_obj2, RT_Object_Class_Thread, NULL);
    uassert_true(static_obj2.name[0] == '\0');

    generate_unique_name(unique_name, RT_NAME_MAX, "dynull");
    dyn_obj = rt_object_allocate(RT_Object_Class_Thread, NULL);
    uassert_not_null(dyn_obj);
    if (dyn_obj)
    {
        uassert_true(dyn_obj->name[0] == '\0');
        rt_object_delete(dyn_obj);
        dyn_obj = RT_NULL;
    }

    /* Test 4: Exact Length Name */
    char exact_name[RT_NAME_MAX];
    rt_memset(exact_name, 'B', RT_NAME_MAX - 1);
    exact_name[RT_NAME_MAX - 1] = '\0';
    generate_unique_name(unique_name, RT_NAME_MAX, "exact");
    rt_object_init(&static_obj3, RT_Object_Class_Thread, exact_name);
    uassert_str_equal(static_obj3.name, exact_name);

    /* Cleanup */
    rt_object_detach(&static_obj1);
    rt_object_detach(&static_obj2);
    rt_object_detach(&static_obj3);
}

static void test_object_find_operations(void)
{
    rt_object_t found;
    char name[RT_NAME_MAX];
    char long_name[16]; /* Longer than typical RT_NAME_MAX=8 */
    const char *nonexist_name = "nonexistent_obj";

    /* Test 1: Find static thread object with rt_object_find */
    struct rt_object static_obj;
    generate_unique_name(name, RT_NAME_MAX, "sobj");
    rt_object_init(&static_obj, RT_Object_Class_Thread, name);
    found = rt_object_find(name, RT_Object_Class_Thread);
    if (found == RT_NULL)
    {
        rt_kprintf("Failed to find static thread object: %s\n", name);
    }
    uassert_not_null(found);
    uassert_ptr_equal(found, &static_obj);
    uassert_str_equal(found->name, name);
    rt_object_detach(&static_obj);

    /* Test 2: Find dynamic thread object with rt_object_find */
    generate_unique_name(name, RT_NAME_MAX, "dobj");
    rt_object_t dyn_obj = rt_object_allocate(RT_Object_Class_Thread, name);
    uassert_not_null(dyn_obj);
    if (dyn_obj)
    {
        found = rt_object_find(name, RT_Object_Class_Thread);
        if (found == RT_NULL)
        {
            rt_kprintf("Failed to find dynamic thread object: %s\n", name);
        }
        uassert_not_null(found);
        uassert_ptr_equal(found, dyn_obj);
        uassert_str_equal(found->name, name);
        rt_object_delete(dyn_obj);
    }

    /* Test 3: Find thread object with rt_thread_find */
    generate_unique_name(name, RT_NAME_MAX, "thr");
    rt_thread_t thread = rt_thread_create(name, RT_NULL, RT_NULL, 1024, 20, 10);
    uassert_not_null(thread);
    if (thread)
    {
        rt_thread_t found_thread = rt_thread_find(name);
        if (found_thread == RT_NULL)
        {
            rt_kprintf("Failed to find thread with rt_thread_find: %s\n", name);
        }
        uassert_not_null(found_thread);
        uassert_ptr_equal(found_thread, thread);
        uassert_str_equal(found_thread->parent.name, name);
        rt_thread_delete(thread);
    }

#ifdef RT_USING_DEVICE
    /* Test 4: Find device object with rt_device_find */
    struct rt_device device;
    generate_unique_name(name, RT_NAME_MAX, "dev");
    rt_err_t ret = rt_device_register(&device, name, RT_DEVICE_FLAG_RDONLY);
    uassert_int_equal(ret, RT_EOK);
    rt_device_t found_device = rt_device_find(name);
    if (found_device == RT_NULL)
    {
        rt_kprintf("Failed to find device with rt_device_find: %s\n", name);
    }
    uassert_not_null(found_device);
    uassert_ptr_equal(found_device, &device);
    uassert_str_equal(found_device->parent.name, name);
    rt_device_unregister(&device);
#endif

    /* Test 5: Find thread with long name (exceeding RT_NAME_MAX) */
    rt_snprintf(long_name, sizeof(long_name), "longthreadname%d", name_counter++);
    rt_thread_t long_thread = rt_thread_create(long_name, RT_NULL, RT_NULL, 1024, 20, 10);
    uassert_not_null(long_thread);
    if (long_thread)
    {
        char truncated_name[RT_NAME_MAX];
        rt_strncpy(truncated_name, long_name, RT_NAME_MAX - 1);
        truncated_name[RT_NAME_MAX - 1] = '\0';
        rt_kprintf("Testing long thread name: %s, truncated to: %s\n", long_name, truncated_name);
        rt_thread_t found_thread = rt_thread_find(truncated_name);
        if (found_thread == RT_NULL)
        {
            rt_kprintf("Failed to find thread with rt_thread_find: %s\n", truncated_name);
        }
        uassert_not_null(found_thread);
        uassert_ptr_equal(found_thread, long_thread);
        uassert_str_equal(found_thread->parent.name, truncated_name);
        rt_thread_delete(long_thread);
    }

    /* Test 6: Find thread with long name directly (no manual truncation) */
    rt_snprintf(long_name, sizeof(long_name), "longthreadname%d", name_counter++);
    rt_thread_t long_thread_direct = rt_thread_create(long_name, RT_NULL, RT_NULL, 1024, 20, 10);
    uassert_not_null(long_thread_direct);
    if (long_thread_direct)
    {
        rt_kprintf("Testing direct long name: %s\n", long_name);
        rt_thread_t found_thread = rt_thread_find(long_name);
        if (found_thread == RT_NULL)
        {
            rt_kprintf("Failed to find thread with rt_thread_find: %s\n", long_name);
        }
        uassert_not_null(found_thread);
        uassert_ptr_equal(found_thread, long_thread_direct);
        char truncated_name[RT_NAME_MAX];
        rt_strncpy(truncated_name, long_name, RT_NAME_MAX - 1);
        truncated_name[RT_NAME_MAX - 1] = '\0';
        uassert_str_equal(found_thread->parent.name, truncated_name);
        rt_thread_delete(long_thread_direct);
    }

#ifdef RT_USING_DEVICE
    /* Test 7: Find device with long name (exceeding RT_NAME_MAX) */
    rt_snprintf(long_name, sizeof(long_name), "longdevicename%d", name_counter++);
    struct rt_device long_device;
    ret = rt_device_register(&long_device, long_name, RT_DEVICE_FLAG_RDONLY);
    uassert_int_equal(ret, RT_EOK);
    if (ret == RT_EOK)
    {
        char truncated_name[RT_NAME_MAX];
        rt_strncpy(truncated_name, long_name, RT_NAME_MAX - 1);
        truncated_name[RT_NAME_MAX - 1] = '\0';
        rt_kprintf("Testing long device name: %s, truncated to: %s\n", long_name, truncated_name);
        rt_device_t found_device = rt_device_find(truncated_name);
        if (found_device == RT_NULL)
        {
            rt_kprintf("Failed to find device with rt_device_find: %s\n", truncated_name);
        }
        uassert_not_null(found_device);
        uassert_ptr_equal(found_device, &long_device);
        uassert_str_equal(found_device->parent.name, truncated_name);
        rt_device_unregister(&long_device);
    }
#endif

    /* Test 8: Find non-existent object with rt_object_find */
    found = rt_object_find(nonexist_name, RT_Object_Class_Thread);
    uassert_null(found);

    /* Test 9: Find with NULL name with rt_object_find */
    found = rt_object_find(NULL, RT_Object_Class_Thread);
    uassert_null(found);

    /* Test 10: Find with NULL name with rt_thread_find */
    rt_thread_t found_thread = rt_thread_find(NULL);
    uassert_null(found_thread);

#ifdef RT_USING_DEVICE
    /* Test 11: Find with NULL name with rt_device_find */
    rt_device_t found_device_null = rt_device_find(NULL);
    uassert_null(found_device_null);
#endif
}

static void test_object_info_enumeration(void)
{
    struct rt_object static_objs[3];
    rt_object_t dyn_objs[2] = {RT_NULL, RT_NULL};
    char names[5][RT_NAME_MAX];

    /* Generate unique names */
    for (int i = 0; i < 5; i++)
    {
        generate_unique_name(names[i], RT_NAME_MAX, "enum");
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
    uassert_true(count >= 5); /* At least our 5 objects */

    /* Test 3: Get object pointers with sufficient buffer */
    rt_object_t *objects = (rt_object_t *)rt_malloc((count + 2) * sizeof(rt_object_t));
    uassert_not_null(objects);
    if (objects)
    {
        int ret = rt_object_get_pointers(RT_Object_Class_Thread, objects, count + 2);
        uassert_int_equal(ret, count);

        /* Verify our objects are in the list */
        int found_count = 0;
        for (int i = 0; i < ret; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (objects[i] == &static_objs[j]) found_count++;
            }

            for (int j = 0; j < 2; j++)
            {
                if (objects[i] == dyn_objs[j]) found_count++;
            }
        }
        uassert_int_equal(found_count, 5);

        rt_free(objects);
    }

    /* Test 4: Get object pointers with small buffer */
    rt_object_t one_object[1];
    int ret = rt_object_get_pointers(RT_Object_Class_Thread, one_object, 1);
    uassert_true(ret <= 1);

    /* Test 5: Empty container (use Semaphore as it may be empty) */
#ifdef RT_USING_SEMAPHORE
    int empty_count = rt_object_get_length(RT_Object_Class_Semaphore);
    uassert_true(empty_count >= 0); /* Cannot assume empty, but verify non-negative */
#endif

    /* Cleanup */
    for (int i = 0; i < 3; i++)
    {
        rt_object_detach(&static_objs[i]);
    }

    for (int i = 0; i < 2; i++)
    {
        if (dyn_objs[i])
        {
            rt_object_delete(dyn_objs[i]);
        }
    }
}

static void test_object_type_handling(void)
{
    struct rt_object obj;
    char name[RT_NAME_MAX];
    generate_unique_name(name, RT_NAME_MAX, "typ"); /* Use short prefix */
    rt_kprintf("Object name for test: %s\n", name);
    rt_object_init(&obj, RT_Object_Class_Thread, name);

    /* Test 1: Get object type */
    uassert_int_equal(rt_object_get_type(&obj), RT_Object_Class_Thread);

    /* Test 2: Check system object */
    uassert_true(rt_object_is_systemobject(&obj));

    /* Test 3: Get name with sufficient buffer */
    char name_buf[RT_NAME_MAX];
    rt_err_t ret = rt_object_get_name(&obj, name_buf, sizeof(name_buf));
    uassert_int_equal(ret, RT_EOK);
    uassert_str_equal(name_buf, name);

    /* Test 4: Get name with small buffer */
    char small_buf[4] = {0}; /* Initialize to avoid undefined behavior */
    ret = rt_object_get_name(&obj, small_buf, sizeof(small_buf));
    uassert_int_equal(ret, RT_EOK);
    rt_kprintf("small_buf after rt_object_get_name: %s (bytes: %02x %02x %02x %02x)\n",
               small_buf, small_buf[0], small_buf[1], small_buf[2], small_buf[3]);
    uassert_true(rt_strncmp(small_buf, name, sizeof(small_buf) - 1) == 0);
    uassert_true(small_buf[sizeof(small_buf) - 1] == '\0'); /* Expect null-termination (assuming kernel fix) */

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
    /* Ensure scheduler is available */
    if (!rt_scheduler_is_available())
    {
        rt_kprintf("Scheduler is not available, test may fail\n");
        return -RT_ERROR;
    }
    /* Reset name counter for each test suite run */
    name_counter = 0;
    rt_kprintf("RT_NAME_MAX = %d\n", RT_NAME_MAX);
    return RT_EOK;
}

static rt_err_t testcase_cleanup(void)
{
    /* No dynamic cleanup needed, as each test case handles its own cleanup */
    return RT_EOK;
}

static void test_object_suite(void)
{
    UTEST_UNIT_RUN(test_object_name_handling);
    UTEST_UNIT_RUN(test_object_find_operations);
    UTEST_UNIT_RUN(test_object_info_enumeration);
    UTEST_UNIT_RUN(test_object_type_handling);
}
UTEST_TC_EXPORT(test_object_suite, "testcases.kernel.object_test", testcase_init, testcase_cleanup, 20);
