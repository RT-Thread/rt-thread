#include <rtthread.h>
#include "tc_comm.h"

static rt_sem_t sem;
static rt_uint8_t t1_count, t2_count;
static rt_thread_t t1, t2, worker;
static void thread1_entry(void* parameter)
{
    rt_err_t result;

    while (1)
    {
        result = rt_sem_take(sem, RT_WAITING_FOREVER);
        if (result != RT_EOK)
        {
            tc_done(TC_STAT_FAILED);
            return;
        }

        t1_count ++;
        rt_kprintf("thread1: got semaphore, count: %d\n", t1_count);
    }
}

static void thread2_entry(void* parameter)
{
    rt_err_t result;

    while (1)
    {
        result = rt_sem_take(sem, RT_WAITING_FOREVER);
        if (result != RT_EOK)
        {
            tc_done(TC_STAT_FAILED);
            return;
        }

        t2_count ++;
        rt_kprintf("thread2: got semaphore, count: %d\n", t2_count);
    }
}

static void worker_thread_entry(void* parameter)
{
    rt_thread_delay(10);

    while (1)
    {
        rt_sem_release(sem);
        rt_thread_delay(5);
    }
}

int semaphore_priority_init()
{
    sem = rt_sem_create("sem", 0, RT_IPC_FLAG_PRIO);
    if (sem == RT_NULL)
    {
        tc_stat(TC_STAT_END | TC_STAT_FAILED);
        return 0;
    }

    t1_count = t2_count = 0;

    t1 = rt_thread_create("t1",
                          thread1_entry, RT_NULL,
                          THREAD_STACK_SIZE, THREAD_PRIORITY + 1, THREAD_TIMESLICE);
    if (t1 != RT_NULL)
        rt_thread_startup(t1);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    t2 = rt_thread_create("t2",
                          thread2_entry, RT_NULL,
                          THREAD_STACK_SIZE, THREAD_PRIORITY - 1, THREAD_TIMESLICE);
    if (t2 != RT_NULL)
        rt_thread_startup(t2);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    worker = rt_thread_create("worker",
                              worker_thread_entry, RT_NULL,
                              THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (worker != RT_NULL)
        rt_thread_startup(worker);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    return 0;
}

#ifdef RT_USING_TC
static void _tc_cleanup()
{
    /* lock scheduler */
    rt_enter_critical();

    /* delete t1, t2 and worker thread */
    rt_thread_delete(t1);
    rt_thread_delete(t2);
    rt_thread_delete(worker);

    if (sem)
    {
        rt_sem_delete(sem);
        sem = RT_NULL;
    }

    if (t1_count > t2_count)
        tc_done(TC_STAT_FAILED);
    else
        tc_done(TC_STAT_PASSED);

    /* unlock scheduler */
    rt_exit_critical();
}

int _tc_semaphore_priority()
{
    /* set tc cleanup */
    tc_cleanup(_tc_cleanup);
    semaphore_priority_init();

    return 50;
}
FINSH_FUNCTION_EXPORT(_tc_semaphore_priority, a priority semaphore test);
#else
int rt_application_init()
{
    semaphore_priority_init();

    return 0;
}
#endif
