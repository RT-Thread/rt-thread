#include <rtthread.h>
#include "tc_comm.h"

static rt_thread_t tid = RT_NULL;
static void sample_thread(void* parameter)
{
    rt_kprintf("I'm sample!\n");
}
static void sample_thread_cleanup(struct rt_thread *p)
{
    tid = RT_NULL;
    tc_done(TC_STAT_PASSED);
}

int sample_init()
{
    tid = rt_thread_create("t",
        sample_thread, RT_NULL,
        THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
        tid->cleanup = sample_thread_cleanup;
    }
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    return 0;
}

#ifdef RT_USING_TC
static void _tc_cleanup()
{
    /* lock scheduler */
    rt_enter_critical();
    /* delete thread */
    if (tid != RT_NULL)
    {
        rt_kprintf("tid1 is bad\n");
        tc_stat(TC_STAT_FAILED);
    }
    /* unlock scheduler */
    rt_exit_critical();
}

int _tc_sample()
{
    /* set tc cleanup */
    tc_cleanup(_tc_cleanup);
    sample_init();

    return 25;
}
FINSH_FUNCTION_EXPORT(_tc_sample, a thread testcase example);
#else
int rt_application_init()
{
    sample_init();

    return 0;
}
#endif
