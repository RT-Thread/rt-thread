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
 * Completion
 */

struct rt_completion
{
    rt_uint32_t flag;

    /* suspended list */
    rt_list_t suspended_list;
    struct rt_spinlock spinlock;
};

void rt_completion_init(struct rt_completion *completion);
rt_err_t rt_completion_wait(struct rt_completion *completion,
                            rt_int32_t            timeout);
void rt_completion_done(struct rt_completion *completion);

#endif
