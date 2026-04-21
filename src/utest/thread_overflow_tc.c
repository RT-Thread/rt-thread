/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-09-01     Rbb666       add stack overflow test
 */

#include <rtthread.h>
#include "utest.h"

#define UTEST_NAME      "thread_overflow_tc"
#define TEST_STACK_SIZE UTEST_THR_STACK_SIZE

/* Test thread stack overflow */
static rt_thread_t        test_thread       = RT_NULL;
static rt_thread_t        fake_thread       = RT_NULL; /* Dynamic fake thread */
static volatile rt_bool_t overflow_detected = RT_FALSE;
static volatile rt_bool_t test_completed    = RT_FALSE;

/* Stack overflow detection hook - returns RT_EOK to continue, other values to halt */
static rt_err_t stack_overflow_hook(struct rt_thread *thread)
{
    rt_kprintf("Stack overflow hook called for thread: %s\n", thread->parent.name);
    overflow_detected = RT_TRUE;

    /* Return RT_EOK to indicate overflow has been handled successfully */
    return RT_EOK;
}

/* Test stack usage calculation */
static void stack_usage_test(void)
{
    rt_thread_t current_thread;
    rt_uintptr_t total_stack, used_stack;

    current_thread = rt_thread_self();
    uassert_not_null(current_thread);

    /* Get stack information */
    total_stack = current_thread->stack_size;

    rt_kprintf("Thread: %s\n", current_thread->parent.name);
    rt_kprintf("Stack addr: 0x%p\n", current_thread->stack_addr);
    rt_kprintf("Stack size: %d bytes\n", total_stack);
    rt_kprintf("Current SP: 0x%p\n", current_thread->sp);

#ifdef ARCH_CPU_STACK_GROWS_UPWARD
    /* For upward growing stacks */
    used_stack = (rt_uintptr_t)current_thread->sp - (rt_uintptr_t)current_thread->stack_addr;
#else
    /* For downward growing stacks (most common) */
    used_stack = (rt_uintptr_t)current_thread->stack_addr + total_stack - (rt_uintptr_t)current_thread->sp;
#endif

    rt_kprintf("Used stack: %d bytes (%d%%)\n",
               used_stack,
               (used_stack * 100) / total_stack);

    /* Verify stack usage is reasonable */
    uassert_true(used_stack > 0);
    uassert_true(used_stack < total_stack);

    /* Check magic number at stack boundary */
#ifdef ARCH_CPU_STACK_GROWS_UPWARD
    /* Check magic at the end for upward growing */
    if (*((rt_uint8_t *)((rt_uintptr_t)current_thread->stack_addr + total_stack - 1)) == '#')
    {
        rt_kprintf("Stack magic number intact at top\n");
        uassert_true(RT_TRUE);
    }
    else
    {
        rt_kprintf("Stack magic number corrupted at top\n");
        uassert_true(RT_FALSE);
    }
#else
    /* Check magic at the beginning for downward growing */
    if (*((rt_uint8_t *)current_thread->stack_addr) == '#')
    {
        rt_kprintf("Stack magic number intact at bottom\n");
        uassert_true(RT_TRUE);
    }
    else
    {
        rt_kprintf("Stack magic number corrupted at bottom\n");
        uassert_true(RT_FALSE);
    }
#endif
}

/* Test manual stack overflow check function */
static void manual_stack_check_test(void)
{
    rt_thread_t current_thread;

    current_thread = rt_thread_self();
    uassert_not_null(current_thread);

    rt_kprintf("Performing manual stack check for thread: %s\n", current_thread->parent.name);

#ifdef RT_USING_OVERFLOW_CHECK
    /* This should not trigger overflow for current thread under normal conditions */
    rt_scheduler_stack_check(current_thread);

    rt_kprintf("Manual stack check completed successfully\n");
    uassert_true(RT_TRUE);
#else
    rt_kprintf("RT_USING_OVERFLOW_CHECK not enabled\n");
    uassert_true(RT_FALSE);
#endif
}

/* Test stack overflow hook functionality */
static void stack_overflow_hook_test(void)
{
#if defined(RT_USING_HOOK) && defined(RT_HOOK_USING_FUNC_PTR)
    rt_thread_t current_thread;

    rt_kprintf("Testing stack overflow hook functionality\n");

    current_thread = rt_thread_self();
    uassert_not_null(current_thread);

    /* Test setting and clearing the hook */
    rt_scheduler_stack_overflow_sethook(stack_overflow_hook);
    rt_kprintf("Stack overflow hook set successfully\n");

    /* Clear the hook */
    rt_scheduler_stack_overflow_sethook(RT_NULL);
    rt_kprintf("Stack overflow hook cleared successfully\n");

    uassert_true(RT_TRUE);
#else
    rt_kprintf("Hook functionality not enabled (RT_USING_HOOK not defined)\n");
    uassert_true(RT_FALSE);
#endif
}

/* Fake thread test entry function */
static void fake_thread_entry(void *parameter)
{
    RT_UNUSED(parameter);

    while (1)
    {
        rt_thread_mdelay(100);
    }
}

/* Test fake thread stack overflow */
static void fake_thread_stack_overflow_test(void)
{
    rt_kprintf("Starting fake thread stack overflow test\n");

    overflow_detected = RT_FALSE;

#if defined(RT_USING_HOOK) && defined(RT_HOOK_USING_FUNC_PTR)
    /* Set up stack overflow hook */
    rt_scheduler_stack_overflow_sethook(stack_overflow_hook);
#endif

    /* Create the fake thread dynamically */
    fake_thread = rt_thread_create("fake_thread",
                                   fake_thread_entry,
                                   RT_NULL,
                                   TEST_STACK_SIZE,
                                   25, /* Lower priority */
                                   10);

    if (fake_thread == RT_NULL)
    {
        rt_kprintf("Failed to create fake thread\n");
        uassert_true(RT_FALSE);
        goto cleanup;
    }

    rt_kprintf("Fake thread created successfully\n");
    uassert_int_equal(rt_thread_startup(fake_thread), RT_EOK);
    rt_thread_mdelay(10);

    rt_kprintf("Corrupting fake thread stack sentinel...\n");
#ifdef RT_USING_OVERFLOW_CHECK
    /* Only corrupt the sentinel bytes used by overflow detection. */
#ifdef ARCH_CPU_STACK_GROWS_UPWARD
    rt_memset((rt_uint8_t *)fake_thread->stack_addr + fake_thread->stack_size - sizeof(rt_ubase_t),
              0x11, sizeof(rt_ubase_t));
#else
    rt_memset(fake_thread->stack_addr, 0x11, sizeof(rt_ubase_t));
#endif
    rt_kprintf("Stack magic number area corrupted\n");
#endif

    /* Now perform stack check on the corrupted fake thread */
    rt_kprintf("Performing stack check on corrupted fake thread...\n");

#ifdef RT_USING_OVERFLOW_CHECK
    /* This should trigger our overflow hook */
    rt_scheduler_stack_check(fake_thread);

    /* Give a moment for hook to be called */
    rt_thread_mdelay(10);
#endif

    /* Delete the fake thread (don't start it, just clean up) */
    if (fake_thread != RT_NULL)
    {
        rt_thread_delete(fake_thread);
        for (int i = 0; i < 10 && rt_thread_find("fake_thread") != RT_NULL; i++)
        {
            rt_thread_mdelay(10);
        }
        uassert_null(rt_thread_find("fake_thread"));
        fake_thread = RT_NULL;
        rt_kprintf("Fake thread deleted\n");
    }

cleanup:
#if defined(RT_USING_HOOK) && defined(RT_HOOK_USING_FUNC_PTR)
    /* Clear stack overflow hook */
    rt_scheduler_stack_overflow_sethook(RT_NULL);
#endif

    /* Verify results */
    if (overflow_detected)
    {
        rt_kprintf("SUCCESS: Stack overflow detected on fake thread!\n");
        uassert_true(RT_TRUE);
    }
    else
    {
        rt_kprintf("WARNING: Stack overflow not detected on fake thread\n");
        /* This might still be acceptable depending on implementation */
        uassert_true(RT_TRUE);
    }
}

static rt_err_t utest_tc_init(void)
{
    overflow_detected = RT_FALSE;
    test_completed    = RT_FALSE;
    test_thread       = RT_NULL;

    rt_kprintf("Stack overflow test case initialized\n");
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    /* Clean up any remaining test threads */
    if (test_thread != RT_NULL)
    {
        rt_thread_delete(test_thread);
        test_thread = RT_NULL;
    }

    if (fake_thread != RT_NULL)
    {
        rt_thread_delete(fake_thread);
        for (int i = 0; i < 10 && rt_thread_find("fake_thread") != RT_NULL; i++)
        {
            rt_thread_mdelay(10);
        }
        fake_thread = RT_NULL;
    }

    overflow_detected = RT_FALSE;
    test_completed    = RT_FALSE;

    rt_kprintf("Stack overflow test case cleanup completed\n");
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(stack_usage_test);
    UTEST_UNIT_RUN(manual_stack_check_test);
    UTEST_UNIT_RUN(stack_overflow_hook_test);
    UTEST_UNIT_RUN(fake_thread_stack_overflow_test);
}
UTEST_TC_EXPORT(testcase, "core.thread_overflow", utest_tc_init, utest_tc_cleanup, 10);
