/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-22     Shell        Support hook list
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
UTEST_TC_EXPORT(testcase, "testcases.kernel.hooklist_tc", utest_tc_init, utest_tc_cleanup, 10);
