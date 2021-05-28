/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef WORKQUEUE_H__
#define WORKQUEUE_H__

#include <rtthread.h>

enum
{
    RT_WORK_STATE_PENDING    = 0x0001,     /* Work item pending state */
    RT_WORK_STATE_SUBMITTING = 0x0002,     /* Work item submitting state */
};

/**
 * work type defitions
 */
enum
{
    RT_WORK_TYPE_DELAYED     = 0x0001,
};

/* workqueue implementation */
struct rt_workqueue
{
    rt_list_t      work_list;
    rt_list_t      delayed_list;
    struct rt_work *work_current; /* current work */

    struct rt_semaphore sem;
    rt_thread_t    work_thread;
};

struct rt_work
{
    rt_list_t list;

    void (*work_func)(struct rt_work *work, void *work_data);
    void *work_data;
    rt_uint16_t flags;
    rt_uint16_t type;
    struct rt_timer timer;
    struct rt_workqueue *workqueue;
};

struct rt_delayed_work
{
    struct rt_work work;
};

#ifdef RT_USING_HEAP
/**
 * WorkQueue for DeviceDriver
 */
struct rt_workqueue *rt_workqueue_create(const char *name, rt_uint16_t stack_size, rt_uint8_t priority);
rt_err_t rt_workqueue_destroy(struct rt_workqueue *queue);
rt_err_t rt_workqueue_dowork(struct rt_workqueue *queue, struct rt_work *work);
rt_err_t rt_workqueue_submit_work(struct rt_workqueue *queue, struct rt_work *work, rt_tick_t time);
rt_err_t rt_workqueue_cancel_work(struct rt_workqueue *queue, struct rt_work *work);
rt_err_t rt_workqueue_cancel_work_sync(struct rt_workqueue *queue, struct rt_work *work);
rt_err_t rt_workqueue_cancel_all_work(struct rt_workqueue *queue);
rt_err_t rt_workqueue_critical_work(struct rt_workqueue *queue, struct rt_work *work);

#ifdef RT_USING_SYSTEM_WORKQUEUE
rt_err_t rt_work_submit(struct rt_work *work, rt_tick_t time);
rt_err_t rt_work_cancel(struct rt_work *work);
#endif

rt_inline void rt_work_init(struct rt_work *work, void (*work_func)(struct rt_work *work, void *work_data),
                            void *work_data)
{
    rt_list_init(&(work->list));
    work->work_func = work_func;
    work->work_data = work_data;
    work->workqueue = RT_NULL;
    work->flags = 0;
    work->type = 0;
}

void rt_delayed_work_init(struct rt_delayed_work *work, void (*work_func)(struct rt_work *work,
                          void *work_data), void *work_data);

int rt_work_sys_workqueue_init(void);
#endif

#endif
