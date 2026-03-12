/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-18     kurisaW      First commit
 * 2025-11-13     CYFS         Add standardized documentation block for object_tc
 * 2025-11-19     Rbb666       Refactor tests, add stress and error-path coverage
 */

/**
 * Test Case Name: Kernel Object Management Test
 *
 * Objectives:
 * - Validate RT-Thread object lifecycle, lookup, enumeration, metadata, and error handling
 * - Exercise both static and dynamic objects under realistic embedded constraints
 * - Apply repeated stress rounds to ensure determinism across multiple executions
 *
 * Test Implementation:
 *
 * 1. test_object_name_handling()
 *    - Tests object name storage, truncation, and null-termination
 *    - Validates RT_NAME_MAX boundary conditions
 *    - Verifies static vs dynamic object identification via rt_object_is_systemobject()
 *    - Tests both NULL and non-NULL name initialization
 *
 * 2. test_object_find_operations()
 *    - Tests rt_object_find() with static objects
 *    - Tests rt_thread_find() with dynamically created threads
 *    - Tests rt_device_find() with registered devices (when RT_USING_DEVICE enabled)
 *    - Validates NULL parameter handling and non-existent object queries
 *    - Ensures proper cleanup and object removal from containers
 *
 * 3. test_object_info_enumeration()
 *    - Tests rt_object_get_information() for object container metadata
 *    - Tests rt_object_get_length() for accurate object counting
 *    - Tests rt_object_get_pointers() for batch object retrieval
 *    - Validates mixed static and dynamic object enumeration
 *    - Tests boundary conditions with NULL/invalid parameters
 *
 * 4. test_object_type_handling()
 *    - Tests rt_object_get_type() for correct type identification
 *    - Tests rt_object_get_name() with various buffer sizes
 *    - Validates truncation behavior when buffer is too small
 *    - Tests error handling for invalid parameters
 *
 * 5. test_object_error_paths()
 *    - Tests invalid object class (RT_Object_Class_Null)
 *    - Tests rt_object_for_each() iteration mechanism
 *    - Validates early termination and error propagation in iterators
 *
 * 6. test_custom_object_lifecycle() (when RT_USING_HEAP enabled)
 *    - Tests rt_custom_object_create() and rt_custom_object_destroy()
 *    - Validates custom cleanup callback execution
 *
 * 7. test_object_pressure()
 *    - Stress tests with OBJECT_STRESS_BATCH (24) objects across OBJECT_STRESS_ROUNDS (3) rounds
 *    - Validates memory cleanup and object container consistency under load
 *    - Ensures no resource leaks after repeated create/delete cycles
 *
 * Helper Functions:
 * - generate_unique_name(): Creates collision-free object names using incremental counter
 * - name_in_use(): Checks if a name is already registered in the object system
 *
 * Memory Safety:
 * - All dynamic objects are properly deleted with appropriate delays for defunct queue processing
 * - Static objects use stack allocation to prevent leaks
 * - testcase_cleanup() includes 50ms delay to ensure complete resource cleanup
 */

#include <utest.h>
#include <rtthread.h>
#include <string.h>

#define TEST_RT_NAME_MAX        RT_NAME_MAX
#define OBJECT_STRESS_BATCH     24
#define OBJECT_STRESS_ROUNDS    3

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

/* Global counter for unique object names */
static rt_uint32_t name_counter;

static rt_bool_t name_in_use(const char *name, enum rt_object_class_type type)
{
    if (!name)
        return RT_FALSE;

    if (rt_object_find(name, (rt_uint8_t)type))
        return RT_TRUE;

    if (type == RT_Object_Class_Thread)
    {
        if (rt_thread_find((char *)name))
            return RT_TRUE;
    }
#ifdef RT_USING_DEVICE
    if (type == RT_Object_Class_Device)
    {
        if (rt_device_find(name))
            return RT_TRUE;
    }
#endif

    return RT_FALSE;
}

static rt_err_t generate_unique_name(char *buf,
                                     rt_size_t size,
                                     const char *prefix,
                                     enum rt_object_class_type type)
{
    rt_size_t prefix_len, max_prefix_len;

    if (!buf || !prefix || size < TEST_RT_NAME_MAX)
        return -RT_EINVAL;

    /* Reserve space for up to 5-digit counter (99999) plus '\0' */
    max_prefix_len = TEST_RT_NAME_MAX - 6;
    prefix_len = rt_strlen(prefix);

    /* Limit prefix length to fit within name constraints */
    if (prefix_len > max_prefix_len)
        prefix_len = max_prefix_len;

    for (int i = 0; i < 2000; i++)
    {
        /* Generate name with truncated prefix if necessary */
        rt_snprintf(buf, size, "%.*s%u", (int)prefix_len, prefix, name_counter++);
        buf[TEST_RT_NAME_MAX - 1] = '\0';

        if (!name_in_use(buf, type))
            return RT_EOK;
    }

    return -RT_ENOMEM;
}

static void test_object_name_handling(void)
{
    struct rt_object static_obj;
    rt_object_t dyn_obj = RT_NULL;
    char test_name[TEST_RT_NAME_MAX];
    char exact_name[TEST_RT_NAME_MAX];

    rt_memset(test_name, 'A', TEST_RT_NAME_MAX - 1);
    test_name[TEST_RT_NAME_MAX - 1] = '\0';

    rt_object_init(&static_obj, RT_Object_Class_Thread, test_name);
    uassert_true(rt_strlen(static_obj.name) <= TEST_RT_NAME_MAX - 1);
    uassert_true(static_obj.name[TEST_RT_NAME_MAX - 1] == '\0');
    uassert_true(rt_strncmp(static_obj.name, test_name, TEST_RT_NAME_MAX - 1) == 0);
    uassert_true(rt_object_is_systemobject(&static_obj));
    rt_object_detach(&static_obj);

    dyn_obj = rt_object_allocate(RT_Object_Class_Thread, test_name);
    uassert_not_null(dyn_obj);
    uassert_true(dyn_obj->name[TEST_RT_NAME_MAX - 1] == '\0');
    uassert_false(rt_object_is_systemobject(dyn_obj));
    rt_object_delete(dyn_obj);

    rt_object_init(&static_obj, RT_Object_Class_Thread, RT_NULL);
    uassert_true(static_obj.name[0] == '\0');
    rt_object_detach(&static_obj);

    dyn_obj = rt_object_allocate(RT_Object_Class_Thread, RT_NULL);
    uassert_not_null(dyn_obj);
    uassert_true(dyn_obj->name[0] == '\0');
    rt_object_delete(dyn_obj);

    rt_memset(exact_name, 'B', TEST_RT_NAME_MAX - 1);
    exact_name[TEST_RT_NAME_MAX - 1] = '\0';
    rt_object_init(&static_obj, RT_Object_Class_Thread, exact_name);
    uassert_str_equal(static_obj.name, exact_name);
    rt_object_detach(&static_obj);
}

static void test_object_find_operations(void)
{
    struct rt_object static_obj;
    char name[TEST_RT_NAME_MAX];
    rt_thread_t thread;
    rt_thread_t found_thread;
    rt_object_t found;
    char missing_name[] = "object.not.exists";

    uassert_true(generate_unique_name(name, sizeof(name), "sobj", RT_Object_Class_Thread) == RT_EOK);
    rt_object_init(&static_obj, RT_Object_Class_Thread, name);
    found = rt_object_find(name, RT_Object_Class_Thread);
    uassert_not_null(found);
    uassert_ptr_equal(found, &static_obj);
    uassert_str_equal(found->name, name);
    rt_object_detach(&static_obj);

    uassert_true(generate_unique_name(name, sizeof(name), "thr", RT_Object_Class_Thread) == RT_EOK);
    thread = rt_thread_create(name, RT_NULL, RT_NULL, 512, RT_THREAD_PRIORITY_MAX / 2, 10);
    uassert_not_null(thread);
    found_thread = rt_thread_find(name);
    uassert_not_null(found_thread);
    uassert_ptr_equal(found_thread, thread);
    uassert_str_equal(found_thread->parent.name, name);
    rt_thread_delete(thread);
    rt_thread_mdelay(10);
    uassert_null(rt_thread_find(name));

#ifdef RT_USING_DEVICE
    struct rt_device device;
    rt_device_t found_device;

    uassert_true(generate_unique_name(name, sizeof(name), "dev", RT_Object_Class_Device) == RT_EOK);
    uassert_int_equal(rt_device_register(&device, name, RT_DEVICE_FLAG_RDONLY), RT_EOK);
    found_device = rt_device_find(name);
    uassert_not_null(found_device);
    uassert_ptr_equal(found_device, &device);
    uassert_str_equal(found_device->parent.name, name);
    rt_device_unregister(&device);
    /* Verify device is properly unregistered */
    uassert_null(rt_device_find(name));
#endif

    uassert_null(rt_object_find(missing_name, RT_Object_Class_Thread));
    uassert_null(rt_thread_find(missing_name));

#ifdef RT_USING_DEVICE
    uassert_null(rt_device_find(missing_name));
#endif

    uassert_null(rt_object_find(RT_NULL, RT_Object_Class_Thread));
    uassert_null(rt_thread_find(RT_NULL));
#ifdef RT_USING_DEVICE
    uassert_null(rt_device_find(RT_NULL));
#endif
}

static void test_object_info_enumeration(void)
{
    enum { STATIC_OBJ_COUNT = 2, DYNAMIC_OBJ_COUNT = 2 };
    struct rt_object static_objs[STATIC_OBJ_COUNT];
    rt_object_t dyn_objs[DYNAMIC_OBJ_COUNT] = {RT_NULL};
    char names[STATIC_OBJ_COUNT + DYNAMIC_OBJ_COUNT][TEST_RT_NAME_MAX];
    int baseline;

    for (int i = 0; i < ARRAY_SIZE(names); i++)
    {
        uassert_true(generate_unique_name(names[i], sizeof(names[i]), "obj", RT_Object_Class_Thread) == RT_EOK);
    }

    baseline = rt_object_get_length(RT_Object_Class_Thread);

    for (int i = 0; i < STATIC_OBJ_COUNT; i++)
    {
        rt_object_init(&static_objs[i], RT_Object_Class_Thread, names[i]);
    }

    for (int i = 0; i < DYNAMIC_OBJ_COUNT; i++)
    {
        dyn_objs[i] = rt_object_allocate(RT_Object_Class_Thread, names[i + STATIC_OBJ_COUNT]);
        uassert_not_null(dyn_objs[i]);
    }

    struct rt_object_information *info = rt_object_get_information(RT_Object_Class_Thread);
    uassert_not_null(info);
    uassert_int_equal(info->type, RT_Object_Class_Thread);

    int count_after = rt_object_get_length(RT_Object_Class_Thread);
    uassert_true(count_after >= baseline + STATIC_OBJ_COUNT + DYNAMIC_OBJ_COUNT);

    int max_objects = count_after + 2;
    rt_object_t *objects = (rt_object_t *)rt_malloc(max_objects * sizeof(rt_object_t));
    uassert_not_null(objects);
    int ret = rt_object_get_pointers(RT_Object_Class_Thread, objects, max_objects);
    uassert_true(ret <= max_objects);

    for (int i = 0; i < STATIC_OBJ_COUNT; i++)
    {
        rt_bool_t seen = RT_FALSE;
        for (int j = 0; j < ret; j++)
        {
            if (objects[j] == &static_objs[i])
            {
                seen = RT_TRUE;
                break;
            }
        }
        uassert_true(seen);
    }

    for (int i = 0; i < DYNAMIC_OBJ_COUNT; i++)
    {
        rt_bool_t seen = RT_FALSE;
        for (int j = 0; j < ret; j++)
        {
            if (objects[j] == dyn_objs[i])
            {
                seen = RT_TRUE;
                break;
            }
        }
        uassert_true(seen);
    }

    rt_free(objects);

    uassert_int_equal(rt_object_get_pointers(RT_Object_Class_Thread, RT_NULL, 0), 0);
    uassert_int_equal(rt_object_get_pointers(RT_Object_Class_Thread, RT_NULL, -1), 0);

#ifdef RT_USING_SEMAPHORE
    uassert_true(rt_object_get_length(RT_Object_Class_Semaphore) >= 0);
#endif

    for (int i = 0; i < STATIC_OBJ_COUNT; i++)
    {
        rt_object_detach(&static_objs[i]);
    }

    for (int i = 0; i < DYNAMIC_OBJ_COUNT; i++)
    {
        if (dyn_objs[i])
            rt_object_delete(dyn_objs[i]);
    }
}

static void test_object_type_handling(void)
{
    struct rt_object obj;
    char name[TEST_RT_NAME_MAX];
    char name_buf[TEST_RT_NAME_MAX];
    char small_buf[4] = {0};
    rt_err_t ret;

    uassert_true(generate_unique_name(name, sizeof(name), "typ", RT_Object_Class_Thread) == RT_EOK);
    rt_object_init(&obj, RT_Object_Class_Thread, name);

    uassert_int_equal(rt_object_get_type(&obj), RT_Object_Class_Thread);
    uassert_true(rt_object_is_systemobject(&obj));

    ret = rt_object_get_name(&obj, name_buf, sizeof(name_buf));
    uassert_int_equal(ret, RT_EOK);
    uassert_str_equal(name_buf, name);

    ret = rt_object_get_name(&obj, small_buf, sizeof(small_buf));
    uassert_int_equal(ret, RT_EOK);
    uassert_true(rt_strncmp(small_buf, name, sizeof(small_buf) - 1) == 0);
    uassert_true(small_buf[sizeof(small_buf) - 1] == '\0');

    ret = rt_object_get_name(RT_NULL, name_buf, sizeof(name_buf));
    uassert_int_equal(ret, -RT_EINVAL);
    ret = rt_object_get_name(&obj, RT_NULL, sizeof(name_buf));
    uassert_int_equal(ret, -RT_EINVAL);
    ret = rt_object_get_name(&obj, name_buf, 0);
    uassert_int_equal(ret, -RT_EINVAL);
    ret = rt_object_get_name(&obj, name_buf, 1);
    uassert_int_equal(ret, RT_EOK);

    rt_object_detach(&obj);
}

struct for_each_ctx
{
    const char *target;
    rt_bool_t matched;
    rt_int8_t mode; /* 0: stop on match, 1: error on match */
};

static rt_err_t for_each_iter(struct rt_object *obj, void *data)
{
    struct for_each_ctx *ctx = (struct for_each_ctx *)data;

    if (!ctx || !ctx->target)
        return -RT_EINVAL;

    if (rt_strcmp(obj->name, ctx->target) == 0)
    {
        ctx->matched = RT_TRUE;
        if (ctx->mode == 0)
            return 1; /* early break */
        else
            return -RT_ERROR;
    }

    return RT_EOK;
}

static void test_object_error_paths(void)
{
    rt_object_t list_sample[2] = {RT_NULL};
    struct rt_object obj;
    char name[TEST_RT_NAME_MAX];
    struct for_each_ctx ctx;

    uassert_null(rt_object_get_information(RT_Object_Class_Null));
    uassert_int_equal(rt_object_get_length(RT_Object_Class_Null), 0);
    uassert_int_equal(rt_object_get_pointers(RT_Object_Class_Null, list_sample, ARRAY_SIZE(list_sample)), 0);
    rt_memset(&ctx, 0, sizeof(ctx));
    uassert_int_equal(rt_object_for_each(RT_Object_Class_Null, for_each_iter, &ctx), -RT_EINVAL);

    uassert_true(generate_unique_name(name, sizeof(name), "err", RT_Object_Class_Thread) == RT_EOK);
    rt_object_init(&obj, RT_Object_Class_Thread, name);

    ctx.target = name;
    ctx.mode = 0;
    ctx.matched = RT_FALSE;
    uassert_int_equal(rt_object_for_each(RT_Object_Class_Thread, for_each_iter, &ctx), RT_EOK);
    uassert_true(ctx.matched);

    ctx.mode = 1;
    ctx.matched = RT_FALSE;
    uassert_int_equal(rt_object_for_each(RT_Object_Class_Thread, for_each_iter, &ctx), -RT_ERROR);
    uassert_true(ctx.matched);

    rt_object_detach(&obj);
}

#ifdef RT_USING_HEAP
static rt_err_t custom_destroy_cb(void *data)
{
    rt_uint32_t *counter = (rt_uint32_t *)data;
    if (counter)
    {
        (*counter)++;
        return RT_EOK;
    }
    return -RT_ERROR;
}

static void test_custom_object_lifecycle(void)
{
    char name[TEST_RT_NAME_MAX];
    rt_uint32_t destroy_counter = 0;
    rt_object_t obj;

    uassert_true(generate_unique_name(name, sizeof(name), "cust", RT_Object_Class_Custom) == RT_EOK);
    obj = rt_custom_object_create(name, &destroy_counter, custom_destroy_cb);
    uassert_not_null(obj);
    uassert_false(rt_object_is_systemobject(obj));
    uassert_int_equal(rt_custom_object_destroy(obj), RT_EOK);
    uassert_int_equal(destroy_counter, 1);
}
#endif /* RT_USING_HEAP */

static void test_object_pressure(void)
{
    rt_object_t objects[OBJECT_STRESS_BATCH] = {RT_NULL};
    char names[OBJECT_STRESS_BATCH][TEST_RT_NAME_MAX];
    int baseline = rt_object_get_length(RT_Object_Class_Thread);

    for (int round = 0; round < OBJECT_STRESS_ROUNDS; round++)
    {
        for (int i = 0; i < OBJECT_STRESS_BATCH; i++)
        {
            uassert_true(generate_unique_name(names[i], sizeof(names[i]), "stress", RT_Object_Class_Thread) == RT_EOK);
            objects[i] = rt_object_allocate(RT_Object_Class_Thread, names[i]);
            uassert_not_null(objects[i]);
        }

        uassert_true(rt_object_get_length(RT_Object_Class_Thread) >= baseline + OBJECT_STRESS_BATCH);

        for (int i = 0; i < OBJECT_STRESS_BATCH; i += 5)
        {
            uassert_not_null(rt_object_find(names[i], RT_Object_Class_Thread));
        }

        for (int i = 0; i < OBJECT_STRESS_BATCH; i++)
        {
            if (objects[i])
            {
                rt_object_delete(objects[i]);
                objects[i] = RT_NULL;
            }
        }

        /* Allow time for memory cleanup */
        rt_thread_mdelay(5);

        for (int i = 0; i < OBJECT_STRESS_BATCH; i += 5)
        {
            uassert_null(rt_object_find(names[i], RT_Object_Class_Thread));
        }
    }

    uassert_true(rt_object_get_length(RT_Object_Class_Thread) >= baseline);
}

static rt_err_t testcase_init(void)
{
    if (!rt_scheduler_is_available())
    {
        return -RT_ERROR;
    }
    /* Reset counter to ensure consistent naming across multiple test runs */
    name_counter = 0;
    return RT_EOK;
}

static rt_err_t testcase_cleanup(void)
{
    /* Force garbage collection delay to ensure all deferred cleanup completes */
    rt_thread_mdelay(50);
    return RT_EOK;
}

static void test_object_suite(void)
{
#if RT_NAME_MAX < 8
    rt_kprintf("Error: RT_NAME_MAX=%d is too small, please increase to at least 8.\n", RT_NAME_MAX);
    return;
#endif
    UTEST_UNIT_RUN(test_object_name_handling);
    UTEST_UNIT_RUN(test_object_find_operations);
    UTEST_UNIT_RUN(test_object_info_enumeration);
    UTEST_UNIT_RUN(test_object_type_handling);
    UTEST_UNIT_RUN(test_object_error_paths);
#ifdef RT_USING_HEAP
    UTEST_UNIT_RUN(test_custom_object_lifecycle);
#endif
    UTEST_UNIT_RUN(test_object_pressure);
}
UTEST_TC_EXPORT(test_object_suite, "core.object", testcase_init, testcase_cleanup, 20);
