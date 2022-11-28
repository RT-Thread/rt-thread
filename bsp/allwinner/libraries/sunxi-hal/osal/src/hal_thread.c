/*
 * ===========================================================================================
 *
 *       Filename:  thread.c
 *
 *    Description:  thread osal for hal layer
 *
 *        Version:  Melis3.0
 *         Create:  2019-11-25 20:29:13
 *       Revision:  none
 *       Compiler:  GCC:version 7.2.1 20170904 (release),ARM/embedded-7-branch revision 255204
 *
 *         Author:  caozilong@allwinnertech.com
 *   Organization:  BU1-PSW
 *  Last Modified:  2020-03-05 09:01:13
 *
 * ===========================================================================================
 */

#include <stdint.h>
#include <hal_thread.h>
#include <kconfig.h>
#include <log.h>
#include <init.h>

void *kthread_create(void (*threadfn)(void *data), void *data, const char *namefmt, ...)
{
    rt_thread_t thr;

    thr = rt_thread_create(namefmt, threadfn, data, \
                           HAL_THREAD_STACK_SIZE, \
                           HAL_THREAD_PRIORITY, \
                           HAL_THREAD_TIMESLICE);

    RT_ASSERT(thr != RT_NULL);

    return (void *)thr;
}

int kthread_start(void *thread)
{
    rt_thread_t thr;
    rt_err_t ret;

    RT_ASSERT(thread != RT_NULL);

    thr = (rt_thread_t)thread;

    ret = rt_thread_startup(thr);

    return ret;
}

int kthread_stop(void *thread)
{
    rt_thread_t thr;

    RT_ASSERT(thread != RT_NULL);

    thr = (rt_thread_t)thread;

    rt_thread_delete(thr);

    return 0;
}

int kthread_wakeup(void *thread)
{
    rt_thread_t thr;
    rt_err_t err;

    RT_ASSERT(thread != RT_NULL);

    thr = (rt_thread_t)thread;

    err = rt_thread_resume(thr);
    if (err)
    {
        return -1;
    }

    return 0;
}

int kthread_suspend(void *thread)
{
    rt_thread_t thr;
    rt_err_t err;

    RT_ASSERT(thread != RT_NULL);

    thr = (rt_thread_t)thread;

    err = rt_thread_suspend(thr);
    if (err)
    {
        return -1;
    }

    return 0;
}
