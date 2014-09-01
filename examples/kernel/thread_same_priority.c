#include <rtthread.h>
#include "tc_comm.h"

static struct rt_thread thread1;
static struct rt_thread thread2;
static char thread1_stack[THREAD_STACK_SIZE];
static char thread2_stack[THREAD_STACK_SIZE];

volatile static rt_uint32_t t1_count = 0;
volatile static rt_uint32_t t2_count = 0;
static void thread1_entry(void* parameter)
{
    while (1)
    {
        t1_count ++;
    }
}

static void thread2_entry(void* parameter)
{
    while (1)
    {
        t2_count ++;
    }
}

rt_err_t thread_same_priority_init()
{
    rt_err_t result;

    result = rt_thread_init(&thread1,
        "t1",
        thread1_entry, RT_NULL,
        &thread1_stack[0], sizeof(thread1_stack),
        THREAD_PRIORITY, 10);
    if (result == RT_EOK)
        rt_thread_startup(&thread1);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    result = rt_thread_init(&thread2,
        "t2",
        thread2_entry, RT_NULL,
        &thread2_stack[0], sizeof(thread2_stack),
        THREAD_PRIORITY, 5);
    if (result == RT_EOK)
        rt_thread_startup(&thread2);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    return result;
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

    rt_kprintf("t1_count=%d t2_count=%d\n",t1_count,t2_count);

    if (t1_count / t2_count != 2)
        tc_stat(TC_STAT_END | TC_STAT_FAILED);
    else
        tc_done(TC_STAT_PASSED);
}

int _tc_thread_same_priority()
{
    t1_count = 0;
    t2_count = 0;

    /* set tc cleanup */
    tc_cleanup(_tc_cleanup);

    thread_same_priority_init();

    return 100;
}
FINSH_FUNCTION_EXPORT(_tc_thread_same_priority, a same priority thread test);
#else
int rt_application_init()
{
    thread_same_priority_init();

    return 0;
}
#endif
