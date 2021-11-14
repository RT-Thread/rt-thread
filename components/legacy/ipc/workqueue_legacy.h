/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-14     Meco Man     the first version
 */

#ifndef __WORKQUEUE_LEGACY_H__
#define __WORKQUEUE_LEGACY_H__

#include <ipc/workqueue.h>

struct rt_delayed_work
{
    struct rt_work work;
};

void rt_delayed_work_init(struct rt_delayed_work *work,
                          void (*work_func)(struct rt_work *work,
                          void *work_data), void *work_data);

#endif
