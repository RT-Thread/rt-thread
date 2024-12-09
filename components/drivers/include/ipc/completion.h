/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-28     Shell        Add new wait_flags() & wakeup_by_errno() API
 * 2024-10-24     yekai        Add C++ support
 */
#ifndef COMPLETION_H_
#define COMPLETION_H_

#include <rtdef.h>
#include <rtconfig.h>

/**
 * RT-Completion - A Tiny(resource-constrained) & Rapid(lockless) IPC Primitive
 *
 * It's an IPC using one pointer word with the encoding:
 *
 * BIT      | MAX-1 ----------------- 1 |       0        |
 * CONTENT  |   suspended_thread & ~1   | completed flag |
 */

struct rt_completion
{
    /* suspended thread, and completed flag */
    rt_atomic_t susp_thread_n_flag;
};

#define RT_COMPLETION_INIT(comp) {0}

#ifdef __cplusplus
extern "C" {
#endif

void rt_completion_init(struct rt_completion *completion);
rt_err_t rt_completion_wait(struct rt_completion *completion,
                            rt_int32_t            timeout);
rt_err_t rt_completion_wait_noisr(struct rt_completion *completion,
                                  rt_int32_t            timeout);
rt_err_t rt_completion_wait_flags(struct rt_completion *completion,
                                  rt_int32_t timeout, int suspend_flag);
rt_err_t rt_completion_wait_flags_noisr(struct rt_completion *completion,
                                        rt_int32_t timeout, int suspend_flag);
void rt_completion_done(struct rt_completion *completion);
rt_err_t rt_completion_wakeup(struct rt_completion *completion);
rt_err_t rt_completion_wakeup_by_errno(struct rt_completion *completion, rt_err_t error);

#ifdef __cplusplus
}
#endif

#endif
