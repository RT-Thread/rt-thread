/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef COMPLETION_H_
#define COMPLETION_H_

#include <rtdef.h>
#include <rtconfig.h>

/**
 * Completion - A tiny IPC implementation for resource-constrained scenarios
 *
 * It's an IPC using one CPU word with the encoding:
 *
 * BIT      | MAX-1 ----------------- 1 |       0        |
 * CONTENT  |   suspended_thread & ~1   | completed flag |
 */

struct rt_completion
{
    /* suspended thread, and completed flag */
    rt_base_t susp_thread_n_flag;
};

#define RT_COMPLETION_INIT(comp) {0}

void rt_completion_init(struct rt_completion *completion);
rt_err_t rt_completion_wait(struct rt_completion *completion,
                            rt_int32_t            timeout);
void rt_completion_done(struct rt_completion *completion);
rt_err_t rt_completion_wakeup(struct rt_completion *completion);

#endif
