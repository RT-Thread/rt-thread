/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-14     Meco Man     the first version
 */

#include "workqueue_legacy.h"

void rt_delayed_work_init(struct rt_delayed_work *work,
                          void (*work_func)(struct rt_work *work,
                          void *work_data), void *work_data)
{
    rt_work_init(&work->work, work_func, work_data);
}
