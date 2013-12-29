#include <rtthread.h>
#include "tc_comm.h"

static void thread_entry(void* parameter)
{
    rt_kprintf("thread dynamicly created ok\n");
    rt_thread_delay(10);
    rt_kprintf("thread exit\n");

    tc_done(TC_STAT_PASSED);
}

int thread_dynamic_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("test",
        thread_entry, RT_NULL,
        THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid != RT_NULL)
        rt_thread_startup(tid);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    return 0;
}

#ifdef RT_USING_TC
int _tc_thread_dynamic()
{
    thread_dynamic_init();

    return 20;
}
FINSH_FUNCTION_EXPORT(_tc_thread_dynamic, a dynamic thread test);
#else
int rt_application_init()
{
    thread_dynamic_init();

    return 0;
}
#endif

