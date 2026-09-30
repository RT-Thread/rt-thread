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

/* Stored in work->flags. Internal runtime state. */
enum
{
    RT_WORK_STATE_PENDING = 0x0001,     /* Work is ready on work_list */
    RT_WORK_STATE_SUBMITTING = 0x0002,     /* Historical name: work is queued on delayed_list */
    RT_WORK_STATE_CANCELING = 0x0004,     /* Sync cancel/destroy waiter is targeting this work */
    RT_WORK_STATE_DONE = 0x0020,     /* Work finished and is no longer queued */
    RT_WORK_STATE_CANCELED = 0x0040,     /* Work was dropped before execution */
};

/**
 * Work status bits returned by rt_workqueue_get_work_status().
 *
 * This is a query-only view and is independent from the internal
 * RT_WORK_STATE_* storage. Prefer RT_WORK_STATUS_DELAYED in new code;
 * RT_WORK_STATUS_SUBMITTING is kept as a compatibility alias.
 */
enum
{
    RT_WORK_STATUS_IDLE = 0x0000,   /* Work is idle with no retained terminal state */
    RT_WORK_STATUS_PENDING = 0x0001,   /* Work is ready on work_list */
    RT_WORK_STATUS_DELAYED = 0x0002,   /* Work is waiting on delayed_list */
    RT_WORK_STATUS_CANCELING = 0x0004,   /* A sync cancel/destroy waiter targets this work */
    RT_WORK_STATUS_RUNNING = 0x0008,   /* Work callback is currently executing */
    RT_WORK_STATUS_OTHER_QUEUE = 0x0010,   /* Work is bound to a different workqueue */
    RT_WORK_STATUS_DONE = 0x0020,   /* Work finished and is no longer queued */
    RT_WORK_STATUS_CANCELED = 0x0040,   /* Work was dropped before execution */
    RT_WORK_STATUS_SUBMITTING = RT_WORK_STATUS_DELAYED, /* Compatibility alias of RT_WORK_STATUS_DELAYED */
};

/* Stored in queue->flags. Internal queue control state. */
enum
{
    RT_WORKQUEUE_FLAG_DESTROYING = 0x01,  /* Queue rejects new work and drains to exit */
    RT_WORKQUEUE_FLAG_SYNC_WAITING = 0x02, /* One sync waiter is blocked on this queue */
};

/**
 * Workqueue runtime object.
 *
 * The fields below are internal runtime data used by the worker thread,
 * submit path and sync-wait paths.
 */
struct rt_workqueue
{
    rt_list_t work_list;                  /* Immediate works ready to run */
    rt_list_t delayed_list;               /* Delayed works sorted by timeout_tick */
    struct rt_work *work_current;         /* Work currently executing on work_thread */
    rt_thread_t work_thread;              /* Worker thread owned by this queue */
    struct rt_spinlock spinlock;          /* Protects lists, work_current and flags */
    struct rt_completion wakeup_completion; /* Wakes worker for new work or delayed-head changes */
    struct rt_completion sync_completion; /* Wakes cancel_work_sync/destroy_sync waiter */
    rt_uint8_t flags;                     /* Internal RT_WORKQUEUE_FLAG_* bits */
};

/**
 * Work item runtime object.
 *
 * A work item can be idle, delayed, pending or running. The same object is
 * reused across submissions, so terminal state bits may remain until the next
 * successful submit.
 */
struct rt_work
{
    rt_list_t list;                            /* List node used by work_list or delayed_list */
    void (*work_func)(struct rt_work *work, void *work_data); /* Work callback */
    void *work_data;                           /* Callback private argument */
    rt_uint16_t flags;                         /* Internal RT_WORK_STATE_* bits */
    rt_tick_t timeout_tick;                    /* Absolute wake tick while queued on delayed_list */
    struct rt_workqueue *workqueue;            /* Bound queue while queued or running */
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
