/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-01     Meco Man     remove rt_delayed_work_init() and rt_delayed_work structure
 * 2021-08-14     Jackistang   add comments for rt_work_init()
 * 2026-03-21     RyanCW       refine sync/status workqueue APIs
 */
#ifndef WORKQUEUE_H__
#define WORKQUEUE_H__

#include <rtdef.h>
#include <rtconfig.h>
#include "completion.h"

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    RT_WORK_STATE_PENDING    = 0x0001,     /* Work item pending state */
    RT_WORK_STATE_SUBMITTING = 0x0002,     /* Work item submitting state */
    RT_WORK_STATE_CANCELING  = 0x0004,     /* Work item canceling state */
    RT_WORK_STATE_DONE       = 0x0020,     /* Work item finished execution */
    RT_WORK_STATE_CANCELED   = 0x0040,     /* Work item canceled before execution */
};

enum
{
    RT_WORK_STATUS_IDLE        = 0x0000,
    RT_WORK_STATUS_PENDING     = RT_WORK_STATE_PENDING,
    RT_WORK_STATUS_SUBMITTING  = RT_WORK_STATE_SUBMITTING,
    RT_WORK_STATUS_CANCELING   = RT_WORK_STATE_CANCELING,
    RT_WORK_STATUS_DONE        = RT_WORK_STATE_DONE,
    RT_WORK_STATUS_CANCELED    = RT_WORK_STATE_CANCELED,
    RT_WORK_STATUS_RUNNING     = 0x0008,
    RT_WORK_STATUS_OTHER_QUEUE = 0x0010,
};

/**
 * work type definitions
 */
enum
{
    RT_WORK_TYPE_DELAYED     = 0x0001,
};

enum
{
    RT_WORKQUEUE_FLAG_DESTROYING = 0x01,
    RT_WORKQUEUE_FLAG_SYNC_WAITING = 0x02,
};

/* workqueue implementation */
struct rt_workqueue
{
    rt_list_t      work_list;
    rt_list_t      delayed_list;
    struct rt_work *work_current; /* current work */
    rt_thread_t    work_thread;
    struct rt_spinlock spinlock;
    struct rt_completion wakeup_completion;
    struct rt_completion sync_completion;
    rt_uint8_t     flags;
};

struct rt_work
{
    rt_list_t list;

    void (*work_func)(struct rt_work *work, void *work_data);
    void *work_data;
    rt_uint16_t flags;
    rt_uint16_t type;
    rt_tick_t timeout_tick;
    struct rt_workqueue *workqueue;
};

#ifdef RT_USING_HEAP
void rt_work_init(struct rt_work *work, void (*work_func)(struct rt_work *work, void *work_data), void *work_data);
struct rt_workqueue *rt_workqueue_create(const char *name, rt_uint16_t stack_size, rt_uint8_t priority);
rt_err_t rt_workqueue_destroy(struct rt_workqueue *queue);
rt_err_t rt_workqueue_destroy_sync(struct rt_workqueue *queue);
rt_err_t rt_workqueue_dowork(struct rt_workqueue *queue, struct rt_work *work);
rt_err_t rt_workqueue_submit_work(struct rt_workqueue *queue, struct rt_work *work, rt_tick_t ticks);
rt_err_t rt_workqueue_cancel_work(struct rt_workqueue *queue, struct rt_work *work);
rt_uint16_t rt_workqueue_get_work_status(struct rt_workqueue *queue, struct rt_work *work);
rt_err_t rt_workqueue_cancel_work_sync(struct rt_workqueue *queue, struct rt_work *work);
rt_err_t rt_workqueue_cancel_all_work(struct rt_workqueue *queue);
rt_err_t rt_workqueue_urgent_work(struct rt_workqueue *queue, struct rt_work *work);

#ifdef RT_USING_SYSTEM_WORKQUEUE
rt_err_t rt_work_submit(struct rt_work *work, rt_tick_t ticks);
rt_err_t rt_work_urgent(struct rt_work *work);
rt_err_t rt_work_cancel(struct rt_work *work);
rt_err_t rt_work_cancel_sync(struct rt_work *work);
rt_uint16_t rt_work_get_status(struct rt_work *work);
#endif /* RT_USING_SYSTEM_WORKQUEUE */

#ifdef __cplusplus
}
#endif

#endif /* RT_USING_HEAP */

#endif
