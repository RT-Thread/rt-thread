#ifndef WORKQUEUE_H__
#define WORKQUEUE_H__

#include <rtthread.h>

/* workqueue implementation */
struct rt_workqueue
{
    rt_list_t      work_list;
    struct rt_work *work_current; /* current work */

    struct rt_semaphore sem; 
    rt_thread_t    work_thread;
};

struct rt_work
{
    rt_list_t list;

    void (*work_func)(struct rt_work* work, void* work_data);
    void *work_data;
};

#ifdef RT_USING_HEAP
/**
 * WorkQueue for DeviceDriver
 */
struct rt_workqueue *rt_workqueue_create(const char* name, rt_uint16_t stack_size, rt_uint8_t priority);
rt_err_t rt_workqueue_destroy(struct rt_workqueue* queue);
rt_err_t rt_workqueue_dowork(struct rt_workqueue* queue, struct rt_work* work);
rt_err_t rt_workqueue_cancel_work(struct rt_workqueue* queue, struct rt_work* work);
rt_err_t rt_workqueue_cancel_work_sync(struct rt_workqueue* queue, struct rt_work* work);

rt_inline void rt_work_init(struct rt_work* work, void (*work_func)(struct rt_work* work, void* work_data),
    void* work_data)
{
    rt_list_init(&(work->list));
    work->work_func = work_func;
    work->work_data = work_data;
}
#endif

#endif

