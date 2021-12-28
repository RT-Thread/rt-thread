/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date          Author                          Notes
 * 2021-12-08    Nicola di Gruttola Giardino     First version
 */

#include <rtdevice.h>
#include <string.h>

#define DEBUG_DEFERRABLE 0

#define DEFERRABLE_SERVER_STACK_SIZE 4096

static rt_uint8_t rt_deferrable_stack[DEFERRABLE_SERVER_STACK_SIZE];
static rt_uint8_t active;
struct rt_deferrable_t deferrable_server;
/**
 * This function will start a new period of the deferrable server
 *
 * @param NULL parameter passed to the timer function
 *
 * @return void
 */
void rt_timer_deferrable_period(void *param)
{
    deferrable_server.capacity_left = deferrable_server.capacity;

    if (rt_list_isempty(deferrable_server.asyncTask.next))
        rt_thread_resume(&deferrable_server.deferrable);

    rt_thread_control(&deferrable_server.deferrable, RT_THREAD_CTRL_CHANGE_PRIORITY, deferrable_server.priority);

    rt_timer_control(&deferrable_server.tim_capacity, RT_TIMER_CTRL_SET_TIME, &deferrable_server.capacity_left);
}

/**
 * This function will stop the deferrable server when its capacity is finished
 *
 * @param NULL parameter passed to the timer function
 *
 * @return void
 */
void rt_timer_deferrable_capacity(void *param)
{
    deferrable_server.capacity_left = 0;
    rt_thread_control(&deferrable_server.deferrable, RT_THREAD_CTRL_CHANGE_PRIORITY, RT_THREAD_PRIORITY_MAX - 1);
}

/**
 * This function is the entry of the deferrable server,
 * it runs the aperiodic tasks until they're over or the capacity is over
 *
 * @param NULL parameter passed to the function
 *
 * @return void
 */
static void rt_thread_deferrable_entry(void *param)
{
    active = 0;
    while(1)
    {
#if DEBUG_DEFERRABLE
        rt_kprintf("**************Enter deferrable***************\n");
#endif
        if(!active)
        {
            rt_timer_start(&deferrable_server.tim_capacity);
            active = 1;
        }
        struct rt_aperiodic_task *task;
        task = rt_list_entry(deferrable_server.asyncTask.next,
                                            struct rt_aperiodic_task,
                                            tlist);
        (task->thd_fun)(task->args);

        rt_list_remove(&task->tlist);

        if(rt_list_isempty(deferrable_server.asyncTask.next))
        {
            rt_timer_stop(&deferrable_server.tim_capacity);
            rt_thread_suspend(&deferrable_server.deferrable);
            active = 0;
            rt_schedule();
        }

    }

}

/**
 * This function instantiate all the objects needed to the operation of the server
 *
 * @param capacity of the server
 * @param period of the server
 * @param priority of the server
 *
 * @return void
 */
rt_err_t rt_thread_deferrable_init(rt_uint32_t capacity, rt_uint32_t period, rt_uint8_t priority)
{
    rt_err_t err;

    char deferr_name[RT_NAME_MAX];

    rt_sprintf(deferr_name, "deferr");

    rt_thread_init(&deferrable_server.deferrable,
                        deferr_name,
                        rt_thread_deferrable_entry,
                        RT_NULL,
                        rt_deferrable_stack,
                        sizeof(rt_deferrable_stack),
                        priority,
                        period);

    rt_sprintf(deferr_name, "Timer");

    rt_timer_init(&deferrable_server.tim_server,
                        deferr_name,
                        rt_timer_deferrable_period,
                        RT_NULL,
                        period,
                        RT_TIMER_FLAG_PERIODIC);

    rt_sprintf(deferr_name, "Capac");

    rt_timer_init(&deferrable_server.tim_capacity,
                    deferr_name,
                    rt_timer_deferrable_capacity,
                    RT_NULL,
                    capacity,
                    RT_TIMER_FLAG_ONE_SHOT);

    deferrable_server.capacity = capacity;
    deferrable_server.capacity_left = capacity;

    rt_list_init(&deferrable_server.asyncTask);

    err = rt_thread_startup(&deferrable_server.deferrable);
    if(err != RT_EOK)
    {
        return err;
    }
    err = rt_thread_suspend(&deferrable_server.deferrable);

    return err;
}

/**
 * This function is used to get the handler of the deferrable server
 *
 * @return the thread structure
 */
rt_thread_t rt_thread_deferrable_gethandler(void)
{
    return (rt_thread_t)(&deferrable_server.deferrable);
};

/**
 * This function is used to insert a new asynchronous task into the server
 *
 * @param the aperiodic task to insert into the server queue
 *
 * @return void
 */
void rt_thread_deferrable_insert_task(struct rt_aperiodic_task *task)
{
    /*
     * If no asynchronous tasks are present in the server, add the first and set server in rdy state
     */
    if(rt_list_isempty(deferrable_server.asyncTask.next))
    {
        rt_list_init(&task->tlist);
        rt_list_insert_before(&deferrable_server.asyncTask, &task->tlist);
#if DEBUG_DEFERRABLE
        rt_kprintf("**************Add TASK***************\n");
#endif
        rt_thread_resume(&deferrable_server.deferrable);
    }
    /*
     * If asynchronous tasks are present, search for the first position available in the queue and put the task there
     */
    else
    {
        rt_list_init(&task->tlist);
        rt_list_insert_before(&deferrable_server.asyncTask, &task->tlist);
#if DEBUG_DEFERRABLE
        rt_kprintf("**************Add another TASK************\n");
#endif

    }

}
