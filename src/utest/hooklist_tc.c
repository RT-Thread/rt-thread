/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-22     Shell        Support hook list
 * 2025-11-11     Ze-Hou       Add standardized utest documentation block
 */

/**
 * Test Case Name: Kernel Core Hook List Test
 *
 * Test Objectives:
 * - Validate the RT-Thread hook list mechanism for thread initialization events
 * - Test registration, invocation, and removal of thread-initialized hooks
 *
 * Test Scenarios:
 * - Register two hook nodes for thread initialization
 * - Initialize a thread and check that both hooks are called
 * - Remove one hook and re-initialize the thread, verifying only the remaining hook is called
 * - Detach thread and clean up hooks after test
 *
 * Verification Metrics:
 * - hooker1_ent_count and hooker2_ent_count increment as expected
 * - After first thread init: both counters == 1
 * - After second thread init (with one hook removed): hooker1_ent_count == 2, hooker2_ent_count == 1
 * - After running this test case, check whether all assertions pass.
 *
 * Dependencies:
 * - Enable Hook List Test (RT-Thread Utestcases -> Kernel Core -> Hook List Test)
 * - Test on any RT-Thread supported platform (e.g., qemu-virt64-riscv)
 *
 * Expected Results:
 * - After executing this test in msh, the expected output should be:
 *   "[  PASSED  ] [ result   ] testcase (core.hooklist)"
 */

#include <rtthread.h>
#include "rtconfig.h"
#include "utest.h"
#include "utest_assert.h"

static int hooker1_ent_count;
static int hooker2_ent_count;
static struct rt_thread thr_tobe_inited;

static void thread_inited_hooker1(rt_thread_t thread)
{
    LOG_D("%s: count %d", __func__, hooker1_ent_count);
    hooker1_ent_count += 1;
}
RT_OBJECT_HOOKLIST_DEFINE_NODE(rt_thread_inited, hooker1_node, thread_inited_hooker1);

static void thread_inited_hooker2(rt_thread_t thread)
{
    LOG_D("%s: count %d", __func__, hooker2_ent_count);
    hooker2_ent_count += 1;
}
RT_OBJECT_HOOKLIST_DEFINE_NODE(rt_thread_inited, hooker2_node, thread_inited_hooker2);

static char _thr_stack[UTEST_THR_STACK_SIZE];
static void thr_tobe_inited_entry(void *param)
{
    rt_kprintf("Hello!\n");
}

static void hooklist_test(void)
{
    hooker1_ent_count = 0;
    hooker2_ent_count = 0;
    rt_thread_inited_sethook(&hooker1_node);
    rt_thread_inited_sethook(&hooker2_node);

    /* run 1 */
    rt_thread_init(&thr_tobe_inited,
                   "thr_tobe_inited",
                   thr_tobe_inited_entry,
                   NULL,
                   _thr_stack,
                   sizeof(_thr_stack),
                   25,
                   100);

    uassert_int_equal(hooker1_ent_count, 1);
    uassert_int_equal(hooker2_ent_count, 1);

    rt_thread_detach(&thr_tobe_inited);
    rt_thread_mdelay(1); /* wait recycling done */

    /* run 2 */
    rt_thread_inited_rmhook(&hooker2_node);

    rt_thread_init(&thr_tobe_inited,
                   "thr_tobe_inited",
                   thr_tobe_inited_entry,
                   NULL,
                   _thr_stack,
                   sizeof(_thr_stack),
                   25,
                   100);

    uassert_int_equal(hooker1_ent_count, 2);
    uassert_int_equal(hooker2_ent_count, 1);
}

static rt_err_t utest_tc_init(void)
{
    hooker1_ent_count = 0;
    hooker2_ent_count = 0;
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_thread_detach(&thr_tobe_inited);
    rt_thread_inited_rmhook(&hooker1_node);
    rt_thread_inited_rmhook(&hooker2_node);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(hooklist_test);
}
UTEST_TC_EXPORT(testcase, "core.hooklist", utest_tc_init, utest_tc_cleanup, 10);
