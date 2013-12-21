#include <rtthread.h>
#include "tc_comm.h"

struct rt_thread thread1;
struct rt_thread thread2;
static char thread1_stack[THREAD_STACK_SIZE];
static char thread2_stack[THREAD_STACK_SIZE];
static rt_uint32_t count = 0;

/*
 * the priority of thread1 > the priority of thread2
 */
static void thread1_entry(void* parameter)
{
    while (1)
    {
        count ++;
        rt_kprintf("count = %d\n", count);

        rt_thread_delay(10);
    }
}

static void thread2_entry(void* parameter)
{
    rt_tick_t tick;

    tick = rt_tick_get();
    while (1)
    {
        if (rt_tick_get() - tick >= 50)
        {
            if (count == 0)
                tc_done(TC_STAT_FAILED);
            else
                tc_done(TC_STAT_PASSED);

            break;
        }
    }
}

int thread_priority_init()
{
    rt_err_t result;

    result = rt_thread_init(&thread1,
                            "t1",
                            thread1_entry, RT_NULL,
                            &thread1_stack[0], sizeof(thread1_stack),
                            THREAD_PRIORITY - 1, THREAD_TIMESLICE);

    if (result == RT_EOK)
        rt_thread_startup(&thread1);
    else
        tc_stat(TC_STAT_FAILED);

    rt_thread_init(&thread2,
                   "t2",
                   thread2_entry, RT_NULL,
                   &thread2_stack[0], sizeof(thread2_stack),
                   THREAD_PRIORITY + 1, THREAD_TIMESLICE);

    if (result == RT_EOK)
        rt_thread_startup(&thread2);
    else
        tc_stat(TC_STAT_FAILED);

    return 0;
}

#ifdef RT_USING_TC
static void _tc_cleanup()
{
    /* lock scheduler */
    rt_enter_critical();

    if (thread1.stat != RT_THREAD_CLOSE)
        rt_thread_detach(&thread1);
    if (thread2.stat != RT_THREAD_CLOSE)
        rt_thread_detach(&thread2);

    /* unlock scheduler */
    rt_exit_critical();
}
int _tc_thread_priority()
{
    count = 0;

    /* set tc cleanup */
    tc_cleanup(_tc_cleanup);
    thread_priority_init();

    return RT_TICK_PER_SECOND;
}
FINSH_FUNCTION_EXPORT(_tc_thread_priority, a priority thread test);
#else
int rt_application_init()
{
    thread_priority_init();

    return 0;
}
#endif

