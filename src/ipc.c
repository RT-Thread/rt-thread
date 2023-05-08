/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-14     Bernard      the first version
 * 2006-04-25     Bernard      implement semaphore
 * 2006-05-03     Bernard      add RT_IPC_DEBUG
 *                             modify the type of IPC waiting time to rt_int32_t
 * 2006-05-10     Bernard      fix the semaphore take bug and add IPC object
 * 2006-05-12     Bernard      implement mailbox and message queue
 * 2006-05-20     Bernard      implement mutex
 * 2006-05-23     Bernard      implement fast event
 * 2006-05-24     Bernard      implement event
 * 2006-06-03     Bernard      fix the thread timer init bug
 * 2006-06-05     Bernard      fix the mutex release bug
 * 2006-06-07     Bernard      fix the message queue send bug
 * 2006-08-04     Bernard      add hook support
 * 2009-05-21     Yi.qiu       fix the sem release bug
 * 2009-07-18     Bernard      fix the event clear bug
 * 2009-09-09     Bernard      remove fast event and fix ipc release bug
 * 2009-10-10     Bernard      change semaphore and mutex value to unsigned value
 * 2009-10-25     Bernard      change the mb/mq receive timeout to 0 if the
 *                             re-calculated delta tick is a negative number.
 * 2009-12-16     Bernard      fix the rt_ipc_object_suspend issue when IPC flag
 *                             is RT_IPC_FLAG_PRIO
 * 2010-01-20     mbbill       remove rt_ipc_object_decrease function.
 * 2010-04-20     Bernard      move memcpy outside interrupt disable in mq
 * 2010-10-26     yi.qiu       add module support in rt_mp_delete and rt_mq_delete
 * 2010-11-10     Bernard      add IPC reset command implementation.
 * 2011-12-18     Bernard      add more parameter checking in message queue
 * 2013-09-14     Grissiom     add an option check in rt_event_recv
 * 2018-10-02     Bernard      add 64bit support for mailbox
 * 2019-09-16     tyx          add send wait support for message queue
 * 2020-07-29     Meco Man     fix thread->event_set/event_info when received an
 *                             event without pending
 * 2020-10-11     Meco Man     add value overflow-check code
 * 2021-01-03     Meco Man     implement rt_mb_urgent()
 * 2021-05-30     Meco Man     implement rt_mutex_trytake()
 * 2022-01-07     Gabriel      Moving __on_rt_xxxxx_hook to ipc.c
 * 2022-01-24     THEWON       let rt_mutex_take return thread->error when using signal
 * 2022-04-08     Stanley      Correct descriptions
 * 2022-10-15     Bernard      add nested mutex feature
 * 2022-10-16     Bernard      add prioceiling feature in mutex
 */

#include <rtthread.h>
#include <rthw.h>

#ifndef __on_rt_object_trytake_hook
    #define __on_rt_object_trytake_hook(parent)     __ON_HOOK_ARGS(rt_object_trytake_hook, (parent))
#endif
#ifndef __on_rt_object_take_hook
    #define __on_rt_object_take_hook(parent)        __ON_HOOK_ARGS(rt_object_take_hook, (parent))
#endif
#ifndef __on_rt_object_put_hook
    #define __on_rt_object_put_hook(parent)         __ON_HOOK_ARGS(rt_object_put_hook, (parent))
#endif

#if defined(RT_USING_HOOK) && defined(RT_HOOK_USING_FUNC_PTR)
extern void (*rt_object_trytake_hook)(struct rt_object *object);
extern void (*rt_object_take_hook)(struct rt_object *object);
extern void (*rt_object_put_hook)(struct rt_object *object);
#endif /* RT_USING_HOOK */

/**
 * @addtogroup IPC
 * @{
 */

/**
 * @brief    This function will initialize an IPC object, such as semaphore, mutex, messagequeue and mailbox.
 *
 * @note     Executing this function will complete an initialization of the suspend thread list of the ipc object.
 *
 * @param    ipc is a pointer to the IPC object.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the initialization is successful.
 *           When the return value is any other values, it means the initialization failed.
 *
 * @warning  This function can be called from all IPC initialization and creation.
 */
rt_inline rt_err_t _ipc_object_init(struct rt_ipc_object *ipc)
{
    /* initialize ipc object */
    rt_list_init(&(ipc->suspend_thread));

    return RT_EOK;
}


/**
 * @brief    This function will suspend a thread to a IPC object list.
 *
 * @param    list is a pointer to a suspended thread list of the IPC object.
 *
 * @param    thread is a pointer to the thread object to be suspended.
 *
 * @param    flag is a flag for the thread object to be suspended. It determines how the thread is suspended.
 *           The flag can be ONE of the following values:
 *
 *               RT_IPC_FLAG_PRIO          The pending threads will queue in order of priority.
 *
 *               RT_IPC_FLAG_FIFO          The pending threads will queue in the first-in-first-out method
 *                                         (also known as first-come-first-served (FCFS) scheduling strategy).
 *
 *               NOTE: RT_IPC_FLAG_FIFO is a non-real-time scheduling mode. It is strongly recommended to use
 *               RT_IPC_FLAG_PRIO to ensure the thread is real-time UNLESS your applications concern about
 *               the first-in-first-out principle, and you clearly understand that all threads involved in
 *               this semaphore will become non-real-time threads.
 *
 * @param    suspend_flag status flag of the thread to be suspended.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the function is successfully executed.
 *           When the return value is any other values, it means the initialization failed.
 *
 * @warning  This function can ONLY be called in the thread context, you can use RT_DEBUG_IN_THREAD_CONTEXT to
 *           check the context.
 *           In addition, this function is generally called by the following functions:
 *           rt_sem_take(),  rt_mutex_take(),  rt_event_recv(),   rt_mb_send_wait(),
 *           rt_mb_recv(),   rt_mq_recv(),     rt_mq_send_wait()
 */
rt_inline rt_err_t _ipc_list_suspend(rt_list_t        *list,
                                       struct rt_thread *thread,
                                       rt_uint8_t        flag,
                                       int suspend_flag)
{
    if ((thread->stat & RT_THREAD_SUSPEND_MASK) != RT_THREAD_SUSPEND_MASK)
    {
        rt_err_t ret = rt_thread_suspend_with_flag(thread, suspend_flag);

        /* suspend thread */
        if (ret != RT_EOK)
        {
            return ret;
        }
    }

    switch (flag)
    {
    case RT_IPC_FLAG_FIFO:
        rt_list_insert_before(list, &(thread->tlist));
        break; /* RT_IPC_FLAG_FIFO */

    case RT_IPC_FLAG_PRIO:
        {
            struct rt_list_node *n;
            struct rt_thread *sthread;

            /* find a suitable position */
            for (n = list->next; n != list; n = n->next)
            {
                sthread = rt_list_entry(n, struct rt_thread, tlist);

                /* find out */
                if (thread->current_priority < sthread->current_priority)
                {
                    /* insert this thread before the sthread */
                    rt_list_insert_before(&(sthread->tlist), &(thread->tlist));
                    break;
                }
            }

            /*
             * not found a suitable position,
             * append to the end of suspend_thread list
             */
            if (n == list)
                rt_list_insert_before(list, &(thread->tlist));
        }
        break;/* RT_IPC_FLAG_PRIO */

    default:
        RT_ASSERT(0);
        break;
    }

    return RT_EOK;
}


/**
 * @brief    This function will resume a thread.
 *
 * @note     This function will resume the first thread in the list of a IPC object.
 *           1. remove the thread from suspend queue of a IPC object.
 *           2. put the thread into system ready queue.
 *
 *           By contrast, the rt_ipc_list_resume_all() function will resume all suspended threads
 *           in the list of a IPC object.
 *
 * @param    list is a pointer to a suspended thread list of the IPC object.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the function is successfully executed.
 *           When the return value is any other values, it means this operation failed.
 *
 * @warning  This function is generally called by the following functions:
 *           rt_sem_release(),    rt_mutex_release(),    rt_mb_send_wait(),    rt_mq_send_wait(),
 *           rt_mb_urgent(),      rt_mb_recv(),          rt_mq_urgent(),       rt_mq_recv(),
 */
rt_inline rt_err_t _ipc_list_resume(rt_list_t *list)
{
    struct rt_thread *thread;

    /* get thread entry */
    thread = rt_list_entry(list->next, struct rt_thread, tlist);

    thread->error = RT_EOK;

    RT_DEBUG_LOG(RT_DEBUG_IPC, ("resume thread:%s\n", thread->parent.name));

    /* resume it */
    rt_thread_resume(thread);

    return RT_EOK;
}


/**
 * @brief   This function will resume all suspended threads in the IPC object list,
 *          including the suspended list of IPC object, and private list of mailbox etc.
 *
 * @note    This function will resume all threads in the IPC object list.
 *          By contrast, the rt_ipc_list_resume() function will resume a suspended thread in the list of a IPC object.
 *
 * @param   list is a pointer to a suspended thread list of the IPC object.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the function is successfully executed.
 *           When the return value is any other values, it means this operation failed.
 *
 */
rt_inline rt_err_t _ipc_list_resume_all(rt_list_t *list)
{
    struct rt_thread *thread;
    rt_base_t level;

    /* wakeup all suspended threads */
    while (!rt_list_isempty(list))
    {
        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        /* get next suspended thread */
        thread = rt_list_entry(list->next, struct rt_thread, tlist);
        /* set error code to RT_ERROR */
        thread->error = -RT_ERROR;

        /*
         * resume thread
         * In rt_thread_resume function, it will remove current thread from
         * suspended list
         */
        rt_thread_resume(thread);

        /* enable interrupt */
        rt_hw_interrupt_enable(level);
    }

    return RT_EOK;
}

#ifdef RT_USING_SEMAPHORE
/**
 * @addtogroup semaphore
 * @{
 */

/**
 * @brief    This function will initialize a static semaphore object.
 *
 * @note     For the static semaphore object, its memory space is allocated by the compiler during compiling,
 *           and shall placed on the read-write data segment or on the uninitialized data segment.
 *           By contrast, the rt_sem_create() function will allocate memory space automatically and initialize
 *           the semaphore.
 *
 * @see      rt_sem_create()
 *
 * @param    sem is a pointer to the semaphore to initialize. It is assumed that storage for the semaphore will be
 *           allocated in your application.
 *
 * @param    name is a pointer to the name you would like to give the semaphore.
 *
 * @param    value is the initial value for the semaphore.
 *           If used to share resources, you should initialize the value as the number of available resources.
 *           If used to signal the occurrence of an event, you should initialize the value as 0.
 *
 * @param    flag is the semaphore flag, which determines the queuing way of how multiple threads wait
 *           when the semaphore is not available.
 *           The semaphore flag can be ONE of the following values:
 *
 *               RT_IPC_FLAG_PRIO          The pending threads will queue in order of priority.
 *
 *               RT_IPC_FLAG_FIFO          The pending threads will queue in the first-in-first-out method
 *                                         (also known as first-come-first-served (FCFS) scheduling strategy).
 *
 *               NOTE: RT_IPC_FLAG_FIFO is a non-real-time scheduling mode. It is strongly recommended to
 *               use RT_IPC_FLAG_PRIO to ensure the thread is real-time UNLESS your applications concern about
 *               the first-in-first-out principle, and you clearly understand that all threads involved in
 *               this semaphore will become non-real-time threads.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the initialization is successful.
 *           If the return value is any other values, it represents the initialization failed.
 *
 * @warning  This function can ONLY be called from threads.
 */
rt_err_t rt_sem_init(rt_sem_t    sem,
                     const char *name,
                     rt_uint32_t value,
                     rt_uint8_t  flag)
{
    RT_ASSERT(sem != RT_NULL);
    RT_ASSERT(value < 0x10000U);
    RT_ASSERT((flag == RT_IPC_FLAG_FIFO) || (flag == RT_IPC_FLAG_PRIO));

    /* initialize object */
    rt_object_init(&(sem->parent.parent), RT_Object_Class_Semaphore, name);

    /* initialize ipc object */
    _ipc_object_init(&(sem->parent));

    /* set initial value */
    sem->value = (rt_uint16_t)value;

    /* set parent */
    sem->parent.parent.flag = flag;

    return RT_EOK;
}
RTM_EXPORT(rt_sem_init);


/**
 * @brief    This function will detach a static semaphore object.
 *
 * @note     This function is used to detach a static semaphore object which is initialized by rt_sem_init() function.
 *           By contrast, the rt_sem_delete() function will delete a semaphore object.
 *           When the semaphore is successfully detached, it will resume all suspended threads in the semaphore list.
 *
 * @see      rt_sem_delete()
 *
 * @param    sem is a pointer to a semaphore object to be detached.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the initialization is successful.
 *           If the return value is any other values, it means that the semaphore detach failed.
 *
 * @warning  This function can ONLY detach a static semaphore initialized by the rt_sem_init() function.
 *           If the semaphore is created by the rt_sem_create() function, you MUST NOT USE this function to detach it,
 *           ONLY USE the rt_sem_delete() function to complete the deletion.
 */
rt_err_t rt_sem_detach(rt_sem_t sem)
{
    /* parameter check */
    RT_ASSERT(sem != RT_NULL);
    RT_ASSERT(rt_object_get_type(&sem->parent.parent) == RT_Object_Class_Semaphore);
    RT_ASSERT(rt_object_is_systemobject(&sem->parent.parent));

    /* wakeup all suspended threads */
    _ipc_list_resume_all(&(sem->parent.suspend_thread));

    /* detach semaphore object */
    rt_object_detach(&(sem->parent.parent));

    return RT_EOK;
}
RTM_EXPORT(rt_sem_detach);

#ifdef RT_USING_HEAP
/**
 * @brief    Creating a semaphore object.
 *
 * @note     For the semaphore object, its memory space is allocated automatically.
 *           By contrast, the rt_sem_init() function will initialize a static semaphore object.
 *
 * @see      rt_sem_init()
 *
 * @param    name is a pointer to the name you would like to give the semaphore.
 *
 * @param    value is the initial value for the semaphore.
 *           If used to share resources, you should initialize the value as the number of available resources.
 *           If used to signal the occurrence of an event, you should initialize the value as 0.
 *
 * @param    flag is the semaphore flag, which determines the queuing way of how multiple threads wait
 *           when the semaphore is not available.
 *           The semaphore flag can be ONE of the following values:
 *
 *               RT_IPC_FLAG_PRIO          The pending threads will queue in order of priority.
 *
 *               RT_IPC_FLAG_FIFO          The pending threads will queue in the first-in-first-out method
 *                                         (also known as first-come-first-served (FCFS) scheduling strategy).
 *
 *               NOTE: RT_IPC_FLAG_FIFO is a non-real-time scheduling mode. It is strongly recommended to
 *               use RT_IPC_FLAG_PRIO to ensure the thread is real-time UNLESS your applications concern about
 *               the first-in-first-out principle, and you clearly understand that all threads involved in
 *               this semaphore will become non-real-time threads.
 *
 * @return   Return a pointer to the semaphore object. When the return value is RT_NULL, it means the creation failed.
 *
 * @warning  This function can NOT be called in interrupt context. You can use macor RT_DEBUG_NOT_IN_INTERRUPT to check it.
 */
rt_sem_t rt_sem_create(const char *name, rt_uint32_t value, rt_uint8_t flag)
{
    rt_sem_t sem;

    RT_ASSERT(value < 0x10000U);
    RT_ASSERT((flag == RT_IPC_FLAG_FIFO) || (flag == RT_IPC_FLAG_PRIO));

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* allocate object */
    sem = (rt_sem_t)rt_object_allocate(RT_Object_Class_Semaphore, name);
    if (sem == RT_NULL)
        return sem;

    /* initialize ipc object */
    _ipc_object_init(&(sem->parent));

    /* set initial value */
    sem->value = value;

    /* set parent */
    sem->parent.parent.flag = flag;

    return sem;
}
RTM_EXPORT(rt_sem_create);


/**
 * @brief    This function will delete a semaphore object and release the memory space.
 *
 * @note     This function is used to delete a semaphore object which is created by the rt_sem_create() function.
 *           By contrast, the rt_sem_detach() function will detach a static semaphore object.
 *           When the semaphore is successfully deleted, it will resume all suspended threads in the semaphore list.
 *
 * @see      rt_sem_detach()
 *
 * @param    sem is a pointer to a semaphore object to be deleted.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the semaphore detach failed.
 *
 * @warning  This function can ONLY delete a semaphore initialized by the rt_sem_create() function.
 *           If the semaphore is initialized by the rt_sem_init() function, you MUST NOT USE this function to delete it,
 *           ONLY USE the rt_sem_detach() function to complete the detachment.
 */
rt_err_t rt_sem_delete(rt_sem_t sem)
{
    /* parameter check */
    RT_ASSERT(sem != RT_NULL);
    RT_ASSERT(rt_object_get_type(&sem->parent.parent) == RT_Object_Class_Semaphore);
    RT_ASSERT(rt_object_is_systemobject(&sem->parent.parent) == RT_FALSE);

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* wakeup all suspended threads */
    _ipc_list_resume_all(&(sem->parent.suspend_thread));

    /* delete semaphore object */
    rt_object_delete(&(sem->parent.parent));

    return RT_EOK;
}
RTM_EXPORT(rt_sem_delete);
#endif /* RT_USING_HEAP */


/**
 * @brief    This function will take a semaphore, if the semaphore is unavailable, the thread shall wait for
 *           the semaphore up to a specified time.
 *
 * @note     When this function is called, the count value of the sem->value will decrease 1 until it is equal to 0.
 *           When the sem->value is 0, it means that the semaphore is unavailable. At this time, it will suspend the
 *           thread preparing to take the semaphore.
 *           On the contrary, the rt_sem_release() function will increase the count value of sem->value by 1 each time.
 *
 * @see      rt_sem_trytake()
 *
 * @param    sem is a pointer to a semaphore object.
 *
 * @param    timeout is a timeout period (unit: an OS tick). If the semaphore is unavailable, the thread will wait for
 *           the semaphore up to the amount of time specified by this parameter.
 *
 *           NOTE:
 *           If use Macro RT_WAITING_FOREVER to set this parameter, which means that when the
 *           message is unavailable in the queue, the thread will be waiting forever.
 *           If use macro RT_WAITING_NO to set this parameter, which means that this
 *           function is non-blocking and will return immediately.
 *
 * @return   Return the operation status. ONLY When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the semaphore take failed.
 *
 * @warning  This function can ONLY be called in the thread context. It MUST NOT BE called in interrupt context.
 */
static rt_err_t _rt_sem_take(rt_sem_t sem, rt_int32_t timeout, int suspend_flag)
{
    rt_base_t level;
    struct rt_thread *thread;
    rt_err_t ret;

    /* parameter check */
    RT_ASSERT(sem != RT_NULL);
    RT_ASSERT(rt_object_get_type(&sem->parent.parent) == RT_Object_Class_Semaphore);

    RT_OBJECT_HOOK_CALL(rt_object_trytake_hook, (&(sem->parent.parent)));

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    RT_DEBUG_LOG(RT_DEBUG_IPC, ("thread %s take sem:%s, which value is: %d\n",
                                rt_thread_self()->parent.name,
                                sem->parent.parent.name,
                                sem->value));

    if (sem->value > 0)
    {
        /* semaphore is available */
        sem->value --;

        /* enable interrupt */
        rt_hw_interrupt_enable(level);
    }
    else
    {
        /* no waiting, return with timeout */
        if (timeout == 0)
        {
            rt_hw_interrupt_enable(level);

            return -RT_ETIMEOUT;
        }
        else
        {
            /* current context checking */
            RT_DEBUG_SCHEDULER_AVAILABLE(RT_TRUE);

            /* semaphore is unavailable, push to suspend list */
            /* get current thread */
            thread = rt_thread_self();

            /* reset thread error number */
            thread->error = -RT_EINTR;

            RT_DEBUG_LOG(RT_DEBUG_IPC, ("sem take: suspend thread - %s\n", thread->parent.name));

            /* suspend thread */
            ret = _ipc_list_suspend(&(sem->parent.suspend_thread),
                                thread,
                                sem->parent.parent.flag,
                                suspend_flag);
            if (ret != RT_EOK)
            {
                rt_hw_interrupt_enable(level);
                return ret;
            }

            /* has waiting time, start thread timer */
            if (timeout > 0)
            {
                RT_DEBUG_LOG(RT_DEBUG_IPC, ("set thread:%s to timer list\n", thread->parent.name));

                /* reset the timeout of thread timer and start it */
                rt_timer_control(&(thread->thread_timer),
                                 RT_TIMER_CTRL_SET_TIME,
                                 &timeout);
                rt_timer_start(&(thread->thread_timer));
            }

            /* enable interrupt */
            rt_hw_interrupt_enable(level);

            /* do schedule */
            rt_schedule();

            if (thread->error != RT_EOK)
            {
                return thread->error;
            }
        }
    }

    RT_OBJECT_HOOK_CALL(rt_object_take_hook, (&(sem->parent.parent)));

    return RT_EOK;
}

rt_err_t rt_sem_take(rt_sem_t sem, rt_int32_t time)
{
    return _rt_sem_take(sem, time, RT_UNINTERRUPTIBLE);
}
RTM_EXPORT(rt_sem_take);

rt_err_t rt_sem_take_interruptible(rt_sem_t sem, rt_int32_t time)
{
    return _rt_sem_take(sem, time, RT_INTERRUPTIBLE);
}
RTM_EXPORT(rt_sem_take_interruptible);

rt_err_t rt_sem_take_killable(rt_sem_t sem, rt_int32_t time)
{
    return _rt_sem_take(sem, time, RT_KILLABLE);
}
RTM_EXPORT(rt_sem_take_killable);

/**
 * @brief    This function will try to take a semaphore, if the semaphore is unavailable, the thread returns immediately.
 *
 * @note     This function is very similar to the rt_sem_take() function, when the semaphore is not available,
 *           the rt_sem_trytake() function will return immediately without waiting for a timeout.
 *           In other words, rt_sem_trytake(sem) has the same effect as rt_sem_take(sem, 0).
 *
 * @see      rt_sem_take()
 *
 * @param    sem is a pointer to a semaphore object.
 *
 * @return   Return the operation status. ONLY When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the semaphore take failed.
 */
rt_err_t rt_sem_trytake(rt_sem_t sem)
{
    return rt_sem_take(sem, RT_WAITING_NO);
}
RTM_EXPORT(rt_sem_trytake);


/**
 * @brief    This function will release a semaphore. If there is thread suspended on the semaphore, it will get resumed.
 *
 * @note     If there are threads suspended on this semaphore, the first thread in the list of this semaphore object
 *           will be resumed, and a thread scheduling (rt_schedule) will be executed.
 *           If no threads are suspended on this semaphore, the count value sem->value of this semaphore will increase by 1.
 *
 * @param    sem is a pointer to a semaphore object.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the semaphore release failed.
 */
rt_err_t rt_sem_release(rt_sem_t sem)
{
    rt_base_t level;
    rt_bool_t need_schedule;

    /* parameter check */
    RT_ASSERT(sem != RT_NULL);
    RT_ASSERT(rt_object_get_type(&sem->parent.parent) == RT_Object_Class_Semaphore);

    RT_OBJECT_HOOK_CALL(rt_object_put_hook, (&(sem->parent.parent)));

    need_schedule = RT_FALSE;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    RT_DEBUG_LOG(RT_DEBUG_IPC, ("thread %s releases sem:%s, which value is: %d\n",
                                rt_thread_self()->parent.name,
                                sem->parent.parent.name,
                                sem->value));

    if (!rt_list_isempty(&sem->parent.suspend_thread))
    {
        /* resume the suspended thread */
        _ipc_list_resume(&(sem->parent.suspend_thread));
        need_schedule = RT_TRUE;
    }
    else
    {
        if(sem->value < RT_SEM_VALUE_MAX)
        {
            sem->value ++; /* increase value */
        }
        else
        {
            rt_hw_interrupt_enable(level); /* enable interrupt */
            return -RT_EFULL; /* value overflowed */
        }
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    /* resume a thread, re-schedule */
    if (need_schedule == RT_TRUE)
        rt_schedule();

    return RT_EOK;
}
RTM_EXPORT(rt_sem_release);


/**
 * @brief    This function will set some extra attributions of a semaphore object.
 *
 * @note     Currently this function only supports the RT_IPC_CMD_RESET command to reset the semaphore.
 *
 * @param    sem is a pointer to a semaphore object.
 *
 * @param    cmd is a command word used to configure some attributions of the semaphore.
 *
 * @param    arg is the argument of the function to execute the command.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that this function failed to execute.
 */
rt_err_t rt_sem_control(rt_sem_t sem, int cmd, void *arg)
{
    rt_base_t level;

    /* parameter check */
    RT_ASSERT(sem != RT_NULL);
    RT_ASSERT(rt_object_get_type(&sem->parent.parent) == RT_Object_Class_Semaphore);

    if (cmd == RT_IPC_CMD_RESET)
    {
        rt_ubase_t value;

        /* get value */
        value = (rt_ubase_t)arg;
        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        /* resume all waiting thread */
        _ipc_list_resume_all(&sem->parent.suspend_thread);

        /* set new value */
        sem->value = (rt_uint16_t)value;

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        rt_schedule();

        return RT_EOK;
    }

    return -RT_ERROR;
}
RTM_EXPORT(rt_sem_control);

/**@}*/
#endif /* RT_USING_SEMAPHORE */

#ifdef RT_USING_MUTEX
/* iterate over each suspended thread to update highest priority in pending threads */
rt_inline rt_uint8_t _mutex_update_priority(struct rt_mutex *mutex)
{
    struct rt_thread *thread;

    if (!rt_list_isempty(&mutex->parent.suspend_thread))
    {
        thread = rt_list_entry(mutex->parent.suspend_thread.next, struct rt_thread, tlist);
        mutex->priority = thread->current_priority;
    }
    else
    {
        mutex->priority = 0xff;
    }

    return mutex->priority;
}

/* get highest priority inside its taken object and its init priority */
rt_inline rt_uint8_t _thread_get_mutex_priority(struct rt_thread* thread)
{
    rt_list_t *node = RT_NULL;
    struct rt_mutex *mutex = RT_NULL;
    rt_uint8_t priority = thread->init_priority;

    rt_list_for_each(node, &(thread->taken_object_list))
    {
        mutex = rt_list_entry(node, struct rt_mutex, taken_list);
        rt_uint8_t mutex_prio = mutex->priority;
        /* prio at least be priority ceiling */
        mutex_prio = mutex_prio < mutex->ceiling_priority ? mutex_prio : mutex->ceiling_priority;

        if (priority > mutex_prio)
        {
            priority = mutex_prio;
        }
    }

    return priority;
}

/* update priority of target thread and the thread suspended it if any */
rt_inline void _thread_update_priority(struct rt_thread *thread, rt_uint8_t priority, int suspend_flag)
{
    rt_err_t ret;
    RT_DEBUG_LOG(RT_DEBUG_IPC,
            ("thread:%s priority -> %d\n", thread->parent.name, priority));

    /* change priority of the thread */
    rt_thread_control(thread,
                      RT_THREAD_CTRL_CHANGE_PRIORITY,
                      &priority);

    if ((thread->stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK)
    {
        /* whether change the priority of taken mutex */
        struct rt_object* pending_obj = thread->pending_object;

        if (pending_obj && rt_object_get_type(pending_obj) == RT_Object_Class_Mutex)
        {
            rt_uint8_t mutex_priority;
            struct rt_mutex* pending_mutex = (struct rt_mutex *)pending_obj;

            /* re-insert thread to suspended thread list */
            rt_list_remove(&(thread->tlist));

            ret = _ipc_list_suspend(&(pending_mutex->parent.suspend_thread),
                                thread,
                                pending_mutex->parent.parent.flag,
                                suspend_flag);
            if (ret != RT_EOK)
            {
                /* TODO */
                return ;
            }

            /* update priority */
            _mutex_update_priority(pending_mutex);
            /* change the priority of mutex owner thread */
            RT_DEBUG_LOG(RT_DEBUG_IPC,
                    ("mutex: %s priority -> %d\n", pending_mutex->parent.parent.name,
                    pending_mutex->priority));

            mutex_priority = _thread_get_mutex_priority(pending_mutex->owner);
            if (mutex_priority != pending_mutex->owner->current_priority)
            {
                _thread_update_priority(pending_mutex->owner, mutex_priority, suspend_flag);
            }
        }
    }
}

/**
 * @addtogroup mutex
 * @{
 */

/**
 * @brief    Initialize a static mutex object.
 *
 * @note     For the static mutex object, its memory space is allocated by the compiler during compiling,
 *           and shall placed on the read-write data segment or on the uninitialized data segment.
 *           By contrast, the rt_mutex_create() function will automatically allocate memory space
 *           and initialize the mutex.
 *
 * @see      rt_mutex_create()
 *
 * @param    mutex is a pointer to the mutex to initialize. It is assumed that storage for the mutex will be
 *           allocated in your application.
 *
 * @param    name is a pointer to the name that given to the mutex.
 *
 * @param    flag is the mutex flag, which determines the queuing way of how multiple threads wait
 *           when the mutex is not available.
 *           NOTE: This parameter has been obsoleted. It can be RT_IPC_FLAG_PRIO, RT_IPC_FLAG_FIFO or RT_NULL.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the initialization is successful.
 *           If the return value is any other values, it represents the initialization failed.
 *
 * @warning  This function can ONLY be called from threads.
 */
rt_err_t rt_mutex_init(rt_mutex_t mutex, const char *name, rt_uint8_t flag)
{
    /* flag parameter has been obsoleted */
    RT_UNUSED(flag);

    /* parameter check */
    RT_ASSERT(mutex != RT_NULL);

    /* initialize object */
    rt_object_init(&(mutex->parent.parent), RT_Object_Class_Mutex, name);

    /* initialize ipc object */
    _ipc_object_init(&(mutex->parent));

    mutex->owner    = RT_NULL;
    mutex->priority = 0xFF;
    mutex->hold     = 0;
    mutex->ceiling_priority = 0xFF;
    rt_list_init(&(mutex->taken_list));

    /* flag can only be RT_IPC_FLAG_PRIO. RT_IPC_FLAG_FIFO cannot solve the unbounded priority inversion problem */
    mutex->parent.parent.flag = RT_IPC_FLAG_PRIO;

    return RT_EOK;
}
RTM_EXPORT(rt_mutex_init);


/**
 * @brief    This function will detach a static mutex object.
 *
 * @note     This function is used to detach a static mutex object which is initialized by rt_mutex_init() function.
 *           By contrast, the rt_mutex_delete() function will delete a mutex object.
 *           When the mutex is successfully detached, it will resume all suspended threads in the mutex list.
 *
 * @see      rt_mutex_delete()
 *
 * @param    mutex is a pointer to a mutex object to be detached.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the initialization is successful.
 *           If the return value is any other values, it means that the mutex detach failed.
 *
 * @warning  This function can ONLY detach a static mutex initialized by the rt_mutex_init() function.
 *           If the mutex is created by the rt_mutex_create() function, you MUST NOT USE this function to detach it,
 *           ONLY USE the rt_mutex_delete() function to complete the deletion.
 */
rt_err_t rt_mutex_detach(rt_mutex_t mutex)
{
    rt_ubase_t level;

    /* parameter check */
    RT_ASSERT(mutex != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mutex->parent.parent) == RT_Object_Class_Mutex);
    RT_ASSERT(rt_object_is_systemobject(&mutex->parent.parent));

    level = rt_hw_interrupt_disable();
    /* wakeup all suspended threads */
    _ipc_list_resume_all(&(mutex->parent.suspend_thread));
    /* remove mutex from thread's taken list */
    rt_list_remove(&mutex->taken_list);
    rt_hw_interrupt_enable(level);

    /* detach mutex object */
    rt_object_detach(&(mutex->parent.parent));

    return RT_EOK;
}
RTM_EXPORT(rt_mutex_detach);

/* drop a thread from the suspend list of mutex */

/**
 * @brief drop a thread from the suspend list of mutex
 *
 * @param mutex is a pointer to a mutex object.
 * @param thread is the thread should be dropped from mutex.
 */
void rt_mutex_drop_thread(rt_mutex_t mutex, rt_thread_t thread)
{
    rt_uint8_t priority;
    rt_bool_t need_update = RT_FALSE;

    rt_list_remove(&(thread->tlist));

    /* should change the priority of mutex owner thread */
    if (mutex->owner->current_priority == thread->current_priority)
        need_update = RT_TRUE;

    /* update the priority of mutex */
    if (!rt_list_isempty(&mutex->parent.suspend_thread))
    {
        /* more thread suspended in the list */
        struct rt_thread *th;

        th = rt_list_entry(mutex->parent.suspend_thread.next,
                                struct rt_thread,
                                tlist);
        /* update the priority of mutex */
        mutex->priority = th->current_priority;
    }
    else
    {
        /* set mutex priority to maximal priority */
        mutex->priority = 0xff;
    }

    /* try to change the priority of mutex owner thread */
    if (need_update)
    {
        /* get the maximal priority of mutex in thread */
        priority = _thread_get_mutex_priority(mutex->owner);
        if (priority != mutex->owner->current_priority)
        {
            _thread_update_priority(mutex->owner, priority, RT_UNINTERRUPTIBLE);
        }
    }
}


/**
 * @brief set the prioceiling attribute of the mutex.
 *
 * @param mutex is a pointer to a mutex object.
 * @param priority is the priority should be set to mutex.
 *
 * @return return the old priority ceiling
 */
rt_uint8_t rt_mutex_setprioceiling(rt_mutex_t mutex, rt_uint8_t priority)
{
    rt_uint8_t ret_priority = 0xFF;

    if ((mutex) && (priority < RT_THREAD_PRIORITY_MAX))
    {
        /* critical section here if multiple updates to one mutex happen */
        rt_ubase_t level = rt_hw_interrupt_disable();
        ret_priority = mutex->ceiling_priority;
        mutex->ceiling_priority = priority;
        if (mutex->owner)
        {
            rt_uint8_t priority = _thread_get_mutex_priority(mutex->owner);
            if (priority != mutex->owner->current_priority)
                _thread_update_priority(mutex->owner, priority, RT_UNINTERRUPTIBLE);
        }
        rt_hw_interrupt_enable(level);
    }
    else
    {
        rt_set_errno(-RT_EINVAL);
    }

    return ret_priority;
}
RTM_EXPORT(rt_mutex_setprioceiling);


/**
 * @brief set the prioceiling attribute of the mutex.
 *
 * @param mutex is a pointer to a mutex object.
 *
 * @return return the current priority ceiling of the mutex.
 */
rt_uint8_t rt_mutex_getprioceiling(rt_mutex_t mutex)
{
    rt_uint8_t prio = 0xFF;

    if (mutex)
    {
        prio = mutex->ceiling_priority;
    }

    return prio;
}
RTM_EXPORT(rt_mutex_getprioceiling);


#ifdef RT_USING_HEAP
/**
 * @brief    This function will create a mutex object.
 *
 * @note     For the mutex object, its memory space is automatically allocated.
 *           By contrast, the rt_mutex_init() function will initialize a static mutex object.
 *
 * @see      rt_mutex_init()
 *
 * @param    name is a pointer to the name that given to the mutex.
 *
 * @param    flag is the mutex flag, which determines the queuing way of how multiple threads wait
 *           when the mutex is not available.
 *           NOTE: This parameter has been obsoleted. It can be RT_IPC_FLAG_PRIO, RT_IPC_FLAG_FIFO or RT_NULL.
 *
 * @return   Return a pointer to the mutex object. When the return value is RT_NULL, it means the creation failed.
 *
 * @warning  This function can ONLY be called from threads.
 */
rt_mutex_t rt_mutex_create(const char *name, rt_uint8_t flag)
{
    struct rt_mutex *mutex;

    /* flag parameter has been obsoleted */
    RT_UNUSED(flag);

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* allocate object */
    mutex = (rt_mutex_t)rt_object_allocate(RT_Object_Class_Mutex, name);
    if (mutex == RT_NULL)
        return mutex;

    /* initialize ipc object */
    _ipc_object_init(&(mutex->parent));

    mutex->owner    = RT_NULL;
    mutex->priority = 0xFF;
    mutex->hold     = 0;
    mutex->ceiling_priority = 0xFF;
    rt_list_init(&(mutex->taken_list));

    /* flag can only be RT_IPC_FLAG_PRIO. RT_IPC_FLAG_FIFO cannot solve the unbounded priority inversion problem */
    mutex->parent.parent.flag = RT_IPC_FLAG_PRIO;

    return mutex;
}
RTM_EXPORT(rt_mutex_create);


/**
 * @brief    This function will delete a mutex object and release this memory space.
 *
 * @note     This function is used to delete a mutex object which is created by the rt_mutex_create() function.
 *           By contrast, the rt_mutex_detach() function will detach a static mutex object.
 *           When the mutex is successfully deleted, it will resume all suspended threads in the mutex list.
 *
 * @see      rt_mutex_detach()
 *
 * @param    mutex is a pointer to a mutex object to be deleted.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the mutex detach failed.
 *
 * @warning  This function can ONLY delete a mutex initialized by the rt_mutex_create() function.
 *           If the mutex is initialized by the rt_mutex_init() function, you MUST NOT USE this function to delete it,
 *           ONLY USE the rt_mutex_detach() function to complete the detachment.
 */
rt_err_t rt_mutex_delete(rt_mutex_t mutex)
{
    rt_ubase_t level;

    /* parameter check */
    RT_ASSERT(mutex != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mutex->parent.parent) == RT_Object_Class_Mutex);
    RT_ASSERT(rt_object_is_systemobject(&mutex->parent.parent) == RT_FALSE);

    RT_DEBUG_NOT_IN_INTERRUPT;

    level = rt_hw_interrupt_disable();
    /* wakeup all suspended threads */
    _ipc_list_resume_all(&(mutex->parent.suspend_thread));
    /* remove mutex from thread's taken list */
    rt_list_remove(&mutex->taken_list);
    rt_hw_interrupt_enable(level);

    /* delete mutex object */
    rt_object_delete(&(mutex->parent.parent));

    return RT_EOK;
}
RTM_EXPORT(rt_mutex_delete);
#endif /* RT_USING_HEAP */


/**
 * @brief    This function will take a mutex, if the mutex is unavailable, the thread shall wait for
 *           the mutex up to a specified time.
 *
 * @note     When this function is called, the count value of the mutex->value will decrease 1 until it is equal to 0.
 *           When the mutex->value is 0, it means that the mutex is unavailable. At this time, it will suspend the
 *           thread preparing to take the mutex.
 *           On the contrary, the rt_mutex_release() function will increase the count value of mutex->value by 1 each time.
 *
 * @see      rt_mutex_trytake()
 *
 * @param    mutex is a pointer to a mutex object.
 *
 * @param    timeout is a timeout period (unit: an OS tick). If the mutex is unavailable, the thread will wait for
 *           the mutex up to the amount of time specified by the argument.
 *           NOTE: Generally, we set this parameter to RT_WAITING_FOREVER, which means that when the mutex is unavailable,
 *           the thread will be waitting forever.
 *
 * @return   Return the operation status. ONLY When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the mutex take failed.
 *
 * @warning  This function can ONLY be called in the thread context. It MUST NOT BE called in interrupt context.
 */
static rt_err_t _rt_mutex_take(rt_mutex_t mutex, rt_int32_t timeout, int suspend_flag)
{
    rt_base_t level;
    struct rt_thread *thread;
    rt_err_t ret;

    /* this function must not be used in interrupt even if time = 0 */
    /* current context checking */
    RT_DEBUG_SCHEDULER_AVAILABLE(RT_TRUE);

    /* parameter check */
    RT_ASSERT(mutex != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mutex->parent.parent) == RT_Object_Class_Mutex);

    /* get current thread */
    thread = rt_thread_self();

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    RT_OBJECT_HOOK_CALL(rt_object_trytake_hook, (&(mutex->parent.parent)));

    RT_DEBUG_LOG(RT_DEBUG_IPC,
                 ("mutex_take: current thread %s, hold: %d\n",
                  thread->parent.name, mutex->hold));

    /* reset thread error */
    thread->error = RT_EOK;

    if (mutex->owner == thread)
    {
        if(mutex->hold < RT_MUTEX_HOLD_MAX)
        {
            /* it's the same thread */
            mutex->hold ++;
        }
        else
        {
            rt_hw_interrupt_enable(level); /* enable interrupt */
            return -RT_EFULL; /* value overflowed */
        }
    }
    else
    {
        /* whether the mutex has owner thread. */
        if (mutex->owner == RT_NULL)
        {
            /* set mutex owner and original priority */
            mutex->owner    = thread;
            mutex->priority = 0xff;
            mutex->hold     = 1;

            if (mutex->ceiling_priority != 0xFF)
            {
                /* set the priority of thread to the ceiling priority */
                if (mutex->ceiling_priority < mutex->owner->current_priority)
                    _thread_update_priority(mutex->owner, mutex->ceiling_priority, suspend_flag);
            }

            /* insert mutex to thread's taken object list */
            rt_list_insert_after(&thread->taken_object_list, &mutex->taken_list);
        }
        else
        {
            /* no waiting, return with timeout */
            if (timeout == 0)
            {
                /* set error as timeout */
                thread->error = -RT_ETIMEOUT;

                /* enable interrupt */
                rt_hw_interrupt_enable(level);

                return -RT_ETIMEOUT;
            }
            else
            {
                rt_uint8_t priority = thread->current_priority;

                /* mutex is unavailable, push to suspend list */
                RT_DEBUG_LOG(RT_DEBUG_IPC, ("mutex_take: suspend thread: %s\n",
                                            thread->parent.name));

                /* suspend current thread */
                ret = _ipc_list_suspend(&(mutex->parent.suspend_thread),
                                    thread,
                                    mutex->parent.parent.flag,
                                    suspend_flag);
                if (ret != RT_EOK)
                {
                    rt_hw_interrupt_enable(level);
                    return ret;
                }

                /* set pending object in thread to this mutex */
                thread->pending_object = &(mutex->parent.parent);

                /* update the priority level of mutex */
                if (priority < mutex->priority)
                {
                    mutex->priority = priority;
                    if (mutex->priority < mutex->owner->current_priority)
                    {
                        _thread_update_priority(mutex->owner, priority, RT_UNINTERRUPTIBLE); /* TODO */
                    }
                }

                /* has waiting time, start thread timer */
                if (timeout > 0)
                {
                    RT_DEBUG_LOG(RT_DEBUG_IPC,
                                 ("mutex_take: start the timer of thread:%s\n",
                                  thread->parent.name));

                    /* reset the timeout of thread timer and start it */
                    rt_timer_control(&(thread->thread_timer),
                                     RT_TIMER_CTRL_SET_TIME,
                                     &timeout);
                    rt_timer_start(&(thread->thread_timer));
                }

                /* enable interrupt */
                rt_hw_interrupt_enable(level);

                /* do schedule */
                rt_schedule();

                /* disable interrupt */
                level = rt_hw_interrupt_disable();

                if (thread->error == RT_EOK)
                {
                    /* get mutex successfully */
                }
                else
                {
                    /* the mutex has not been taken and thread has detach from the pending list. */

                    rt_bool_t need_update = RT_FALSE;

                    /* should change the priority of mutex owner thread */
                    if (mutex->owner->current_priority == thread->current_priority)
                        need_update = RT_TRUE;

                    /* update the priority of mutex */
                    if (!rt_list_isempty(&mutex->parent.suspend_thread))
                    {
                        /* more thread suspended in the list */
                        struct rt_thread *th;

                        th = rt_list_entry(mutex->parent.suspend_thread.next,
                                                struct rt_thread,
                                                tlist);
                        /* update the priority of mutex */
                        mutex->priority = th->current_priority;
                    }
                    else
                    {
                        /* set mutex priority to maximal priority */
                        mutex->priority = 0xff;
                    }

                    /* try to change the priority of mutex owner thread */
                    if (need_update)
                    {
                        /* get the maximal priority of mutex in thread */
                        priority = _thread_get_mutex_priority(mutex->owner);
                        if (priority != mutex->owner->current_priority)
                        {
                            _thread_update_priority(mutex->owner, priority, RT_UNINTERRUPTIBLE);
                        }
                    }

                    /* enable interrupt */
                    rt_hw_interrupt_enable(level);

                    /* return error */
                    return thread->error;
                }
            }
        }
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    RT_OBJECT_HOOK_CALL(rt_object_take_hook, (&(mutex->parent.parent)));

    return RT_EOK;
}

rt_err_t rt_mutex_take(rt_mutex_t mutex, rt_int32_t time)
{
    return _rt_mutex_take(mutex, time, RT_UNINTERRUPTIBLE);
}
RTM_EXPORT(rt_mutex_take);

rt_err_t rt_mutex_take_interruptible(rt_mutex_t mutex, rt_int32_t time)
{
    return _rt_mutex_take(mutex, time, RT_INTERRUPTIBLE);
}
RTM_EXPORT(rt_mutex_take_interruptible);

rt_err_t rt_mutex_take_killable(rt_mutex_t mutex, rt_int32_t time)
{
    return _rt_mutex_take(mutex, time, RT_KILLABLE);
}
RTM_EXPORT(rt_mutex_take_killable);

/**
 * @brief    This function will try to take a mutex, if the mutex is unavailable, the thread returns immediately.
 *
 * @note     This function is very similar to the rt_mutex_take() function, when the mutex is not available,
 *           except that rt_mutex_trytake() will return immediately without waiting for a timeout
 *           when the mutex is not available.
 *           In other words, rt_mutex_trytake(mutex) has the same effect as rt_mutex_take(mutex, 0).
 *
 * @see      rt_mutex_take()
 *
 * @param    mutex is a pointer to a mutex object.
 *
 * @return   Return the operation status. ONLY When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the mutex take failed.
 */
rt_err_t rt_mutex_trytake(rt_mutex_t mutex)
{
    return rt_mutex_take(mutex, RT_WAITING_NO);
}
RTM_EXPORT(rt_mutex_trytake);


/**
 * @brief    This function will release a mutex. If there is thread suspended on the mutex, the thread will be resumed.
 *
 * @note     If there are threads suspended on this mutex, the first thread in the list of this mutex object
 *           will be resumed, and a thread scheduling (rt_schedule) will be executed.
 *           If no threads are suspended on this mutex, the count value mutex->value of this mutex will increase by 1.
 *
 * @param    mutex is a pointer to a mutex object.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the mutex release failed.
 */
rt_err_t rt_mutex_release(rt_mutex_t mutex)
{
    rt_base_t level;
    struct rt_thread *thread;
    rt_bool_t need_schedule;

    /* parameter check */
    RT_ASSERT(mutex != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mutex->parent.parent) == RT_Object_Class_Mutex);

    need_schedule = RT_FALSE;

    /* only thread could release mutex because we need test the ownership */
    RT_DEBUG_IN_THREAD_CONTEXT;

    /* get current thread */
    thread = rt_thread_self();

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    RT_DEBUG_LOG(RT_DEBUG_IPC,
                 ("mutex_release:current thread %s, hold: %d\n",
                  thread->parent.name, mutex->hold));

    RT_OBJECT_HOOK_CALL(rt_object_put_hook, (&(mutex->parent.parent)));

    /* mutex only can be released by owner */
    if (thread != mutex->owner)
    {
        thread->error = -RT_ERROR;

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        return -RT_ERROR;
    }

    /* decrease hold */
    mutex->hold --;
    /* if no hold */
    if (mutex->hold == 0)
    {
        /* remove mutex from thread's taken list */
        rt_list_remove(&mutex->taken_list);

        /* whether change the thread priority */
        if ((mutex->ceiling_priority != 0xFF) || (thread->current_priority == mutex->priority))
        {
            rt_uint8_t priority = 0xff;

            /* get the highest priority in the taken list of thread */
            priority = _thread_get_mutex_priority(thread);

            rt_thread_control(thread,
                              RT_THREAD_CTRL_CHANGE_PRIORITY,
                              &priority);

            need_schedule = RT_TRUE;
        }

        /* wakeup suspended thread */
        if (!rt_list_isempty(&mutex->parent.suspend_thread))
        {
            /* get the first suspended thread */
            struct rt_thread *next_thread = rt_list_entry(mutex->parent.suspend_thread.next,
                                   struct rt_thread,
                                   tlist);

            RT_DEBUG_LOG(RT_DEBUG_IPC, ("mutex_release: resume thread: %s\n",
                    next_thread->parent.name));

            /* remove the thread from the suspended list of mutex */
            rt_list_remove(&(next_thread->tlist));

            /* set new owner and put mutex into taken list of thread */
            mutex->owner = next_thread;
            mutex->hold  = 1;
            rt_list_insert_after(&next_thread->taken_object_list, &mutex->taken_list);
            /* cleanup pending object */
            next_thread->pending_object = RT_NULL;

            /* resume thread */
            rt_thread_resume(next_thread);

            /* update mutex priority */
            if (!rt_list_isempty(&(mutex->parent.suspend_thread)))
            {
                struct rt_thread *th;

                th = rt_list_entry(mutex->parent.suspend_thread.next,
                        struct rt_thread,
                        tlist);
                mutex->priority = th->current_priority;
            }
            else
            {
                mutex->priority = 0xff;
            }

            need_schedule = RT_TRUE;
        }
        else
        {
            /* clear owner */
            mutex->owner    = RT_NULL;
            mutex->priority = 0xff;
        }
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    /* perform a schedule */
    if (need_schedule == RT_TRUE)
        rt_schedule();

    return RT_EOK;
}
RTM_EXPORT(rt_mutex_release);


/**
 * @brief    This function will set some extra attributions of a mutex object.
 *
 * @note     Currently this function does not implement the control function.
 *
 * @param    mutex is a pointer to a mutex object.
 *
 * @param    cmd is a command word used to configure some attributions of the mutex.
 *
 * @param    arg is the argument of the function to execute the command.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that this function failed to execute.
 */
rt_err_t rt_mutex_control(rt_mutex_t mutex, int cmd, void *arg)
{
    /* parameter check */
    RT_ASSERT(mutex != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mutex->parent.parent) == RT_Object_Class_Mutex);

    return -RT_ERROR;
}
RTM_EXPORT(rt_mutex_control);

/**@}*/
#endif /* RT_USING_MUTEX */

#ifdef RT_USING_EVENT
/**
 * @addtogroup event
 * @{
 */

/**
 * @brief    The function will initialize a static event object.
 *
 * @note     For the static event object, its memory space is allocated by the compiler during compiling,
 *           and shall placed on the read-write data segment or on the uninitialized data segment.
 *           By contrast, the rt_event_create() function will allocate memory space automatically
 *           and initialize the event.
 *
 * @see      rt_event_create()
 *
 * @param    event is a pointer to the event to initialize. It is assumed that storage for the event
 *           will be allocated in your application.
 *
 * @param    name is a pointer to the name that given to the event.
 *
 * @param    flag is the event flag, which determines the queuing way of how multiple threads wait
 *           when the event is not available.
 *           The event flag can be ONE of the following values:
 *
 *               RT_IPC_FLAG_PRIO          The pending threads will queue in order of priority.
 *
 *               RT_IPC_FLAG_FIFO          The pending threads will queue in the first-in-first-out method
 *                                         (also known as first-come-first-served (FCFS) scheduling strategy).
 *
 *               NOTE: RT_IPC_FLAG_FIFO is a non-real-time scheduling mode. It is strongly recommended to
 *               use RT_IPC_FLAG_PRIO to ensure the thread is real-time UNLESS your applications concern about
 *               the first-in-first-out principle, and you clearly understand that all threads involved in
 *               this event will become non-real-time threads.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the initialization is successful.
 *           If the return value is any other values, it represents the initialization failed.
 *
 * @warning  This function can ONLY be called from threads.
 */
rt_err_t rt_event_init(rt_event_t event, const char *name, rt_uint8_t flag)
{
    /* parameter check */
    RT_ASSERT(event != RT_NULL);
    RT_ASSERT((flag == RT_IPC_FLAG_FIFO) || (flag == RT_IPC_FLAG_PRIO));

    /* initialize object */
    rt_object_init(&(event->parent.parent), RT_Object_Class_Event, name);

    /* set parent flag */
    event->parent.parent.flag = flag;

    /* initialize ipc object */
    _ipc_object_init(&(event->parent));

    /* initialize event */
    event->set = 0;

    return RT_EOK;
}
RTM_EXPORT(rt_event_init);


/**
 * @brief    This function will detach a static event object.
 *
 * @note     This function is used to detach a static event object which is initialized by rt_event_init() function.
 *           By contrast, the rt_event_delete() function will delete an event object.
 *           When the event is successfully detached, it will resume all suspended threads in the event list.
 *
 * @see      rt_event_delete()
 *
 * @param    event is a pointer to an event object to be detached.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the initialization is successful.
 *           If the return value is any other values, it means that the event detach failed.
 *
 * @warning  This function can ONLY detach a static event initialized by the rt_event_init() function.
 *           If the event is created by the rt_event_create() function, you MUST NOT USE this function to detach it,
 *           ONLY USE the rt_event_delete() function to complete the deletion.
 */
rt_err_t rt_event_detach(rt_event_t event)
{
    /* parameter check */
    RT_ASSERT(event != RT_NULL);
    RT_ASSERT(rt_object_get_type(&event->parent.parent) == RT_Object_Class_Event);
    RT_ASSERT(rt_object_is_systemobject(&event->parent.parent));

    /* resume all suspended thread */
    _ipc_list_resume_all(&(event->parent.suspend_thread));

    /* detach event object */
    rt_object_detach(&(event->parent.parent));

    return RT_EOK;
}
RTM_EXPORT(rt_event_detach);

#ifdef RT_USING_HEAP
/**
 * @brief    Creating an event object.
 *
 * @note     For the event object, its memory space is allocated automatically.
 *           By contrast, the rt_event_init() function will initialize a static event object.
 *
 * @see      rt_event_init()
 *
 * @param    name is a pointer to the name that given to the event.
 *
 * @param    flag is the event flag, which determines the queuing way of how multiple threads wait when the event
 *           is not available.
 *           The event flag can be ONE of the following values:
 *
 *               RT_IPC_FLAG_PRIO          The pending threads will queue in order of priority.
 *
 *               RT_IPC_FLAG_FIFO          The pending threads will queue in the first-in-first-out method
 *                                         (also known as first-come-first-served (FCFS) scheduling strategy).
 *
 *               NOTE: RT_IPC_FLAG_FIFO is a non-real-time scheduling mode. It is strongly recommended to
 *               use RT_IPC_FLAG_PRIO to ensure the thread is real-time UNLESS your applications concern about
 *               the first-in-first-out principle, and you clearly understand that all threads involved in
 *               this event will become non-real-time threads.
 *
 * @return   Return a pointer to the event object. When the return value is RT_NULL, it means the creation failed.
 *
 * @warning  This function can ONLY be called from threads.
 */
rt_event_t rt_event_create(const char *name, rt_uint8_t flag)
{
    rt_event_t event;

    RT_ASSERT((flag == RT_IPC_FLAG_FIFO) || (flag == RT_IPC_FLAG_PRIO));

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* allocate object */
    event = (rt_event_t)rt_object_allocate(RT_Object_Class_Event, name);
    if (event == RT_NULL)
        return event;

    /* set parent */
    event->parent.parent.flag = flag;

    /* initialize ipc object */
    _ipc_object_init(&(event->parent));

    /* initialize event */
    event->set = 0;

    return event;
}
RTM_EXPORT(rt_event_create);


/**
 * @brief    This function will delete an event object and release the memory space.
 *
 * @note     This function is used to delete an event object which is created by the rt_event_create() function.
 *           By contrast, the rt_event_detach() function will detach a static event object.
 *           When the event is successfully deleted, it will resume all suspended threads in the event list.
 *
 * @see      rt_event_detach()
 *
 * @param    event is a pointer to an event object to be deleted.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the event detach failed.
 *
 * @warning  This function can ONLY delete an event initialized by the rt_event_create() function.
 *           If the event is initialized by the rt_event_init() function, you MUST NOT USE this function to delete it,
 *           ONLY USE the rt_event_detach() function to complete the detachment.
 */
rt_err_t rt_event_delete(rt_event_t event)
{
    /* parameter check */
    RT_ASSERT(event != RT_NULL);
    RT_ASSERT(rt_object_get_type(&event->parent.parent) == RT_Object_Class_Event);
    RT_ASSERT(rt_object_is_systemobject(&event->parent.parent) == RT_FALSE);

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* resume all suspended thread */
    _ipc_list_resume_all(&(event->parent.suspend_thread));

    /* delete event object */
    rt_object_delete(&(event->parent.parent));

    return RT_EOK;
}
RTM_EXPORT(rt_event_delete);
#endif /* RT_USING_HEAP */


/**
 * @brief    This function will send an event to the event object.
 *           If there is a thread suspended on the event, the thread will be resumed.
 *
 * @note     When using this function, you need to use the parameter (set) to specify the event flag of the event object,
 *           then the function will traverse the list of suspended threads waiting on the event object.
 *           If there is a thread suspended on the event, and the thread's event_info and the event flag of
 *           the current event object matches, the thread will be resumed.
 *
 * @param    event is a pointer to the event object to be sent.
 *
 * @param    set is a flag that you will set for this event's flag.
 *           You can set an event flag, or you can set multiple flags through OR logic operation.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the event detach failed.
 */
rt_err_t rt_event_send(rt_event_t event, rt_uint32_t set)
{
    struct rt_list_node *n;
    struct rt_thread *thread;
    rt_base_t level;
    rt_base_t status;
    rt_bool_t need_schedule;

    /* parameter check */
    RT_ASSERT(event != RT_NULL);
    RT_ASSERT(rt_object_get_type(&event->parent.parent) == RT_Object_Class_Event);

    if (set == 0)
        return -RT_ERROR;

    need_schedule = RT_FALSE;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* set event */
    event->set |= set;

    RT_OBJECT_HOOK_CALL(rt_object_put_hook, (&(event->parent.parent)));

    if (!rt_list_isempty(&event->parent.suspend_thread))
    {
        /* search thread list to resume thread */
        n = event->parent.suspend_thread.next;
        while (n != &(event->parent.suspend_thread))
        {
            /* get thread */
            thread = rt_list_entry(n, struct rt_thread, tlist);

            status = -RT_ERROR;
            if (thread->event_info & RT_EVENT_FLAG_AND)
            {
                if ((thread->event_set & event->set) == thread->event_set)
                {
                    /* received an AND event */
                    status = RT_EOK;
                }
            }
            else if (thread->event_info & RT_EVENT_FLAG_OR)
            {
                if (thread->event_set & event->set)
                {
                    /* save the received event set */
                    thread->event_set = thread->event_set & event->set;

                    /* received an OR event */
                    status = RT_EOK;
                }
            }
            else
            {
                /* enable interrupt */
                rt_hw_interrupt_enable(level);

                return -RT_EINVAL;
            }

            /* move node to the next */
            n = n->next;

            /* condition is satisfied, resume thread */
            if (status == RT_EOK)
            {
                /* clear event */
                if (thread->event_info & RT_EVENT_FLAG_CLEAR)
                    event->set &= ~thread->event_set;

                /* resume thread, and thread list breaks out */
                rt_thread_resume(thread);
                thread->error = RT_EOK;

                /* need do a scheduling */
                need_schedule = RT_TRUE;
            }
        }
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    /* do a schedule */
    if (need_schedule == RT_TRUE)
        rt_schedule();

    return RT_EOK;
}
RTM_EXPORT(rt_event_send);


/**
 * @brief  This function will receive an event from event object. if the event is unavailable, the thread shall wait for
 *         the event up to a specified time.
 *
 * @note   If there are threads suspended on this semaphore, the first thread in the list of this semaphore object
 *         will be resumed, and a thread scheduling (rt_schedule) will be executed.
 *         If no threads are suspended on this semaphore, the count value sem->value of this semaphore will increase by 1.
 *
 * @param    event is a pointer to the event object to be received.
 *
 * @param    set is a flag that you will set for this event's flag.
 *           You can set an event flag, or you can set multiple flags through OR logic operation.
 *
 * @param    option is the option of this receiving event, it indicates how the receiving event is operated.
 *           The option can be one or more of the following values, When selecting multiple values,use logical OR to operate.
 *           (NOTE: RT_EVENT_FLAG_OR and RT_EVENT_FLAG_AND can only select one):
 *
 *
 *               RT_EVENT_FLAG_OR           The thread select to use logical OR to receive the event.
 *
 *               RT_EVENT_FLAG_AND          The thread select to use logical OR to receive the event.
 *
 *               RT_EVENT_FLAG_CLEAR        When the thread receives the corresponding event, the function
 *                                          determines whether to clear the event flag.
 *
 * @param    timeout is a timeout period (unit: an OS tick).
 *
 * @param    recved is a pointer to the received event. If you don't care about this value, you can use RT_NULL to set.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the semaphore release failed.
 */
static rt_err_t _rt_event_recv(rt_event_t   event,
                       rt_uint32_t  set,
                       rt_uint8_t   option,
                       rt_int32_t   timeout,
                       rt_uint32_t *recved,
                       int suspend_flag)
{
    struct rt_thread *thread;
    rt_base_t level;
    rt_base_t status;
    rt_err_t ret;

    /* parameter check */
    RT_ASSERT(event != RT_NULL);
    RT_ASSERT(rt_object_get_type(&event->parent.parent) == RT_Object_Class_Event);

    /* current context checking */
    RT_DEBUG_SCHEDULER_AVAILABLE(RT_TRUE);

    if (set == 0)
        return -RT_ERROR;

    /* initialize status */
    status = -RT_ERROR;
    /* get current thread */
    thread = rt_thread_self();
    /* reset thread error */
    thread->error = -RT_EINTR;

    RT_OBJECT_HOOK_CALL(rt_object_trytake_hook, (&(event->parent.parent)));

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* check event set */
    if (option & RT_EVENT_FLAG_AND)
    {
        if ((event->set & set) == set)
            status = RT_EOK;
    }
    else if (option & RT_EVENT_FLAG_OR)
    {
        if (event->set & set)
            status = RT_EOK;
    }
    else
    {
        /* either RT_EVENT_FLAG_AND or RT_EVENT_FLAG_OR should be set */
        RT_ASSERT(0);
    }

    if (status == RT_EOK)
    {
        thread->error = RT_EOK;

        /* set received event */
        if (recved)
            *recved = (event->set & set);

        /* fill thread event info */
        thread->event_set = (event->set & set);
        thread->event_info = option;

        /* received event */
        if (option & RT_EVENT_FLAG_CLEAR)
            event->set &= ~set;
    }
    else if (timeout == 0)
    {
        /* no waiting */
        thread->error = -RT_ETIMEOUT;

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        return -RT_ETIMEOUT;
    }
    else
    {
        /* fill thread event info */
        thread->event_set  = set;
        thread->event_info = option;

        /* put thread to suspended thread list */
        ret = _ipc_list_suspend(&(event->parent.suspend_thread),
                            thread,
                            event->parent.parent.flag,
                            suspend_flag);
        if (ret != RT_EOK)
        {
            rt_hw_interrupt_enable(level);
            return ret;
        }

        /* if there is a waiting timeout, active thread timer */
        if (timeout > 0)
        {
            /* reset the timeout of thread timer and start it */
            rt_timer_control(&(thread->thread_timer),
                             RT_TIMER_CTRL_SET_TIME,
                             &timeout);
            rt_timer_start(&(thread->thread_timer));
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        /* do a schedule */
        rt_schedule();

        if (thread->error != RT_EOK)
        {
            /* return error */
            return thread->error;
        }

        /* received an event, disable interrupt to protect */
        level = rt_hw_interrupt_disable();

        /* set received event */
        if (recved)
            *recved = thread->event_set;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    RT_OBJECT_HOOK_CALL(rt_object_take_hook, (&(event->parent.parent)));

    return thread->error;
}

rt_err_t rt_event_recv(rt_event_t   event,
                       rt_uint32_t  set,
                       rt_uint8_t   option,
                       rt_int32_t   timeout,
                       rt_uint32_t *recved)
{
    return _rt_event_recv(event, set, option, timeout, recved, RT_UNINTERRUPTIBLE);
}
RTM_EXPORT(rt_event_recv);

rt_err_t rt_event_recv_interruptible(rt_event_t   event,
                       rt_uint32_t  set,
                       rt_uint8_t   option,
                       rt_int32_t   timeout,
                       rt_uint32_t *recved)
{
    return _rt_event_recv(event, set, option, timeout, recved, RT_INTERRUPTIBLE);
}
RTM_EXPORT(rt_event_recv_interruptible);

rt_err_t rt_event_recv_killable(rt_event_t   event,
                       rt_uint32_t  set,
                       rt_uint8_t   option,
                       rt_int32_t   timeout,
                       rt_uint32_t *recved)
{
    return _rt_event_recv(event, set, option, timeout, recved, RT_KILLABLE);
}
RTM_EXPORT(rt_event_recv_killable);
/**
 * @brief    This function will set some extra attributions of an event object.
 *
 * @note     Currently this function only supports the RT_IPC_CMD_RESET command to reset the event.
 *
 * @param    event is a pointer to an event object.
 *
 * @param    cmd is a command word used to configure some attributions of the event.
 *
 * @param    arg is the argument of the function to execute the command.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that this function failed to execute.
 */
rt_err_t rt_event_control(rt_event_t event, int cmd, void *arg)
{
    rt_base_t level;

    /* parameter check */
    RT_ASSERT(event != RT_NULL);
    RT_ASSERT(rt_object_get_type(&event->parent.parent) == RT_Object_Class_Event);

    if (cmd == RT_IPC_CMD_RESET)
    {
        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        /* resume all waiting thread */
        _ipc_list_resume_all(&event->parent.suspend_thread);

        /* initialize event set */
        event->set = 0;

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        rt_schedule();

        return RT_EOK;
    }

    return -RT_ERROR;
}
RTM_EXPORT(rt_event_control);

/**@}*/
#endif /* RT_USING_EVENT */

#ifdef RT_USING_MAILBOX
/**
 * @addtogroup mailbox
 * @{
 */

/**
 * @brief    Initialize a static mailbox object.
 *
 * @note     For the static mailbox object, its memory space is allocated by the compiler during compiling,
 *           and shall placed on the read-write data segment or on the uninitialized data segment.
 *           By contrast, the rt_mb_create() function will allocate memory space automatically and initialize the mailbox.
 *
 * @see      rt_mb_create()
 *
 * @param    mb is a pointer to the mailbox to initialize.
 *           It is assumed that storage for the mailbox will be allocated in your application.
 *
 * @param    name is a pointer to the name that given to the mailbox.
 *
 * @param    msgpool the begin address of buffer to save received mail.
 *
 * @param    size is the maximum number of mails in the mailbox.
 *           For example, when the mailbox buffer capacity is N, size is N/4.
 *
 * @param    flag is the mailbox flag, which determines the queuing way of how multiple threads wait
 *           when the mailbox is not available.
 *           The mailbox flag can be ONE of the following values:
 *
 *               RT_IPC_FLAG_PRIO          The pending threads will queue in order of priority.
 *
 *               RT_IPC_FLAG_FIFO          The pending threads will queue in the first-in-first-out method
 *                                       (also known as first-come-first-served (FCFS) scheduling strategy).
 *
 *               NOTE: RT_IPC_FLAG_FIFO is a non-real-time scheduling mode. It is strongly recommended to
 *               use RT_IPC_FLAG_PRIO to ensure the thread is real-time UNLESS your applications concern about
 *               the first-in-first-out principle, and you clearly understand that all threads involved in
 *               this mailbox will become non-real-time threads.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the initialization is successful.
 *           If the return value is any other values, it represents the initialization failed.
 *
 * @warning  This function can ONLY be called from threads.
 */
rt_err_t rt_mb_init(rt_mailbox_t mb,
                    const char  *name,
                    void        *msgpool,
                    rt_size_t    size,
                    rt_uint8_t   flag)
{
    RT_ASSERT(mb != RT_NULL);
    RT_ASSERT((flag == RT_IPC_FLAG_FIFO) || (flag == RT_IPC_FLAG_PRIO));

    /* initialize object */
    rt_object_init(&(mb->parent.parent), RT_Object_Class_MailBox, name);

    /* set parent flag */
    mb->parent.parent.flag = flag;

    /* initialize ipc object */
    _ipc_object_init(&(mb->parent));

    /* initialize mailbox */
    mb->msg_pool   = (rt_ubase_t *)msgpool;
    mb->size       = (rt_uint16_t)size;
    mb->entry      = 0;
    mb->in_offset  = 0;
    mb->out_offset = 0;

    /* initialize an additional list of sender suspend thread */
    rt_list_init(&(mb->suspend_sender_thread));

    return RT_EOK;
}
RTM_EXPORT(rt_mb_init);


/**
 * @brief    This function will detach a static mailbox object.
 *
 * @note     This function is used to detach a static mailbox object which is initialized by rt_mb_init() function.
 *           By contrast, the rt_mb_delete() function will delete a mailbox object.
 *           When the mailbox is successfully detached, it will resume all suspended threads in the mailbox list.
 *
 * @see      rt_mb_delete()
 *
 * @param    mb is a pointer to a mailbox object to be detached.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the initialization is successful.
 *           If the return value is any other values, it means that the mailbox detach failed.
 *
 * @warning  This function can ONLY detach a static mailbox initialized by the rt_mb_init() function.
 *           If the mailbox is created by the rt_mb_create() function, you MUST NOT USE this function to detach it,
 *           ONLY USE the rt_mb_delete() function to complete the deletion.
 */
rt_err_t rt_mb_detach(rt_mailbox_t mb)
{
    /* parameter check */
    RT_ASSERT(mb != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mb->parent.parent) == RT_Object_Class_MailBox);
    RT_ASSERT(rt_object_is_systemobject(&mb->parent.parent));

    /* resume all suspended thread */
    _ipc_list_resume_all(&(mb->parent.suspend_thread));
    /* also resume all mailbox private suspended thread */
    _ipc_list_resume_all(&(mb->suspend_sender_thread));

    /* detach mailbox object */
    rt_object_detach(&(mb->parent.parent));

    return RT_EOK;
}
RTM_EXPORT(rt_mb_detach);

#ifdef RT_USING_HEAP
/**
 * @brief  Creating a mailbox object.
 *
 * @note   For the mailbox object, its memory space is allocated automatically.
 *         By contrast, the rt_mb_init() function will initialize a static mailbox object.
 *
 * @see    rt_mb_init()
 *
 * @param  name is a pointer that given to the mailbox.
 *
 * @param    size is the maximum number of mails in the mailbox.
 *           For example, when mailbox buffer capacity is N, size is N/4.
 *
 * @param    flag is the mailbox flag, which determines the queuing way of how multiple threads wait
 *           when the mailbox is not available.
 *           The mailbox flag can be ONE of the following values:
 *
 *               RT_IPC_FLAG_PRIO          The pending threads will queue in order of priority.
 *
 *               RT_IPC_FLAG_FIFO          The pending threads will queue in the first-in-first-out method
 *                                         (also known as first-come-first-served (FCFS) scheduling strategy).
 *
 *               NOTE: RT_IPC_FLAG_FIFO is a non-real-time scheduling mode. It is strongly recommended to
 *               use RT_IPC_FLAG_PRIO to ensure the thread is real-time UNLESS your applications concern about
 *               the first-in-first-out principle, and you clearly understand that all threads involved in
 *               this mailbox will become non-real-time threads.
 *
 * @return   Return a pointer to the mailbox object. When the return value is RT_NULL, it means the creation failed.
 *
 * @warning  This function can ONLY be called from threads.
 */
rt_mailbox_t rt_mb_create(const char *name, rt_size_t size, rt_uint8_t flag)
{
    rt_mailbox_t mb;

    RT_ASSERT((flag == RT_IPC_FLAG_FIFO) || (flag == RT_IPC_FLAG_PRIO));

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* allocate object */
    mb = (rt_mailbox_t)rt_object_allocate(RT_Object_Class_MailBox, name);
    if (mb == RT_NULL)
        return mb;

    /* set parent */
    mb->parent.parent.flag = flag;

    /* initialize ipc object */
    _ipc_object_init(&(mb->parent));

    /* initialize mailbox */
    mb->size     = (rt_uint16_t)size;
    mb->msg_pool = (rt_ubase_t *)RT_KERNEL_MALLOC(mb->size * sizeof(rt_ubase_t));
    if (mb->msg_pool == RT_NULL)
    {
        /* delete mailbox object */
        rt_object_delete(&(mb->parent.parent));

        return RT_NULL;
    }
    mb->entry      = 0;
    mb->in_offset  = 0;
    mb->out_offset = 0;

    /* initialize an additional list of sender suspend thread */
    rt_list_init(&(mb->suspend_sender_thread));

    return mb;
}
RTM_EXPORT(rt_mb_create);


/**
 * @brief    This function will delete a mailbox object and release the memory space.
 *
 * @note     This function is used to delete a mailbox object which is created by the rt_mb_create() function.
 *           By contrast, the rt_mb_detach() function will detach a static mailbox object.
 *           When the mailbox is successfully deleted, it will resume all suspended threads in the mailbox list.
 *
 * @see      rt_mb_detach()
 *
 * @param    mb is a pointer to a mailbox object to be deleted.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the mailbox detach failed.
 *
 * @warning  This function can only delete mailbox created by the rt_mb_create() function.
 *           If the mailbox is initialized by the rt_mb_init() function, you MUST NOT USE this function to delete it,
 *           ONLY USE the rt_mb_detach() function to complete the detachment.
 */
rt_err_t rt_mb_delete(rt_mailbox_t mb)
{
    /* parameter check */
    RT_ASSERT(mb != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mb->parent.parent) == RT_Object_Class_MailBox);
    RT_ASSERT(rt_object_is_systemobject(&mb->parent.parent) == RT_FALSE);

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* resume all suspended thread */
    _ipc_list_resume_all(&(mb->parent.suspend_thread));

    /* also resume all mailbox private suspended thread */
    _ipc_list_resume_all(&(mb->suspend_sender_thread));

    /* free mailbox pool */
    RT_KERNEL_FREE(mb->msg_pool);

    /* delete mailbox object */
    rt_object_delete(&(mb->parent.parent));

    return RT_EOK;
}
RTM_EXPORT(rt_mb_delete);
#endif /* RT_USING_HEAP */


/**
 * @brief    This function will send an mail to the mailbox object. If there is a thread suspended on the mailbox,
 *           the thread will be resumed.
 *
 * @note     When using this function to send a mail, if the mailbox if fully used, the current thread will
 *           wait for a timeout. If the set timeout time is reached and there is still no space available,
 *           the sending thread will be resumed and an error code will be returned.
 *           By contrast, the rt_mb_send() function will return an error code immediately without waiting time
 *           when the mailbox if fully used.
 *
 * @see      rt_mb_send()
 *
 * @param    mb is a pointer to the mailbox object to be sent.
 *
 * @param    value is a value to the content of the mail you want to send.
 *
 * @param    timeout is a timeout period (unit: an OS tick).
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the mailbox detach failed.
 *
 * @warning  This function can be called in interrupt context and thread context.
 */
static rt_err_t _rt_mb_send_wait(rt_mailbox_t mb,
                         rt_ubase_t   value,
                         rt_int32_t   timeout,
                         int suspend_flag)
{
    struct rt_thread *thread;
    rt_base_t level;
    rt_uint32_t tick_delta;
    rt_err_t ret;

    /* parameter check */
    RT_ASSERT(mb != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mb->parent.parent) == RT_Object_Class_MailBox);

    /* current context checking */
    RT_DEBUG_SCHEDULER_AVAILABLE(timeout != 0);

    /* initialize delta tick */
    tick_delta = 0;
    /* get current thread */
    thread = rt_thread_self();

    RT_OBJECT_HOOK_CALL(rt_object_put_hook, (&(mb->parent.parent)));

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* for non-blocking call */
    if (mb->entry == mb->size && timeout == 0)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EFULL;
    }

    /* mailbox is full */
    while (mb->entry == mb->size)
    {
        /* reset error number in thread */
        thread->error = -RT_EINTR;

        /* no waiting, return timeout */
        if (timeout == 0)
        {
            /* enable interrupt */
            rt_hw_interrupt_enable(level);

            return -RT_EFULL;
        }

        /* suspend current thread */
        ret = _ipc_list_suspend(&(mb->suspend_sender_thread),
                            thread,
                            mb->parent.parent.flag,
                            suspend_flag);

        if (ret != RT_EOK)
        {
            rt_hw_interrupt_enable(level);
            return ret;
        }

        /* has waiting time, start thread timer */
        if (timeout > 0)
        {
            /* get the start tick of timer */
            tick_delta = rt_tick_get();

            RT_DEBUG_LOG(RT_DEBUG_IPC, ("mb_send_wait: start timer of thread:%s\n",
                                        thread->parent.name));

            /* reset the timeout of thread timer and start it */
            rt_timer_control(&(thread->thread_timer),
                             RT_TIMER_CTRL_SET_TIME,
                             &timeout);
            rt_timer_start(&(thread->thread_timer));
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        /* re-schedule */
        rt_schedule();

        /* resume from suspend state */
        if (thread->error != RT_EOK)
        {
            /* return error */
            return thread->error;
        }

        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        /* if it's not waiting forever and then re-calculate timeout tick */
        if (timeout > 0)
        {
            tick_delta = rt_tick_get() - tick_delta;
            timeout -= tick_delta;
            if (timeout < 0)
                timeout = 0;
        }
    }

    /* set ptr */
    mb->msg_pool[mb->in_offset] = value;
    /* increase input offset */
    ++ mb->in_offset;
    if (mb->in_offset >= mb->size)
        mb->in_offset = 0;

    if(mb->entry < RT_MB_ENTRY_MAX)
    {
        /* increase message entry */
        mb->entry ++;
    }
    else
    {
        rt_hw_interrupt_enable(level); /* enable interrupt */
        return -RT_EFULL; /* value overflowed */
    }

    /* resume suspended thread */
    if (!rt_list_isempty(&mb->parent.suspend_thread))
    {
        _ipc_list_resume(&(mb->parent.suspend_thread));

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        rt_schedule();

        return RT_EOK;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t rt_mb_send_wait(rt_mailbox_t mb,
                         rt_ubase_t   value,
                         rt_int32_t   timeout)
{
    return _rt_mb_send_wait(mb, value, timeout, RT_UNINTERRUPTIBLE);
}
RTM_EXPORT(rt_mb_send_wait);

rt_err_t rt_mb_send_wait_interruptible(rt_mailbox_t mb,
                         rt_ubase_t   value,
                         rt_int32_t   timeout)
{
    return _rt_mb_send_wait(mb, value, timeout, RT_INTERRUPTIBLE);
}
RTM_EXPORT(rt_mb_send_wait_interruptible);

rt_err_t rt_mb_send_wait_killable(rt_mailbox_t mb,
                         rt_ubase_t   value,
                         rt_int32_t   timeout)
{
    return _rt_mb_send_wait(mb, value, timeout, RT_KILLABLE);
}
RTM_EXPORT(rt_mb_send_wait_killable);
/**
 * @brief    This function will send an mail to the mailbox object. If there is a thread suspended on the mailbox,
 *           the thread will be resumed.
 *
 * @note     When using this function to send a mail, if the mailbox is fully used, this function will return an error
 *           code immediately without waiting time.
 *           By contrast, the rt_mb_send_wait() function is set a timeout to wait for the mail to be sent.
 *
 * @see      rt_mb_send_wait()
 *
 * @param    mb is a pointer to the mailbox object to be sent.
 *
 * @param    value is a value to the content of the mail you want to send.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the mailbox detach failed.
 */
rt_err_t rt_mb_send(rt_mailbox_t mb, rt_ubase_t value)
{
    return rt_mb_send_wait(mb, value, 0);
}
RTM_EXPORT(rt_mb_send);

rt_err_t rt_mb_send_interruptible(rt_mailbox_t mb, rt_ubase_t value)
{
    return rt_mb_send_wait_interruptible(mb, value, 0);
}
RTM_EXPORT(rt_mb_send_interruptible);

rt_err_t rt_mb_send_killable(rt_mailbox_t mb, rt_ubase_t value)
{
    return rt_mb_send_wait_killable(mb, value, 0);
}
RTM_EXPORT(rt_mb_send_killable);

/**
 * @brief    This function will send an urgent mail to the mailbox object.
 *
 * @note     This function is almost the same as the rt_mb_send() function. The only difference is that
 *           when sending an urgent mail, the mail will be placed at the head of the mail queue so that
 *           the recipient can receive the urgent mail first.
 *
 * @see      rt_mb_send()
 *
 * @param    mb is a pointer to the mailbox object to be sent.
 *
 * @param    value is the content of the mail you want to send.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the mailbox detach failed.
 */
rt_err_t rt_mb_urgent(rt_mailbox_t mb, rt_ubase_t value)
{
    rt_base_t level;

    /* parameter check */
    RT_ASSERT(mb != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mb->parent.parent) == RT_Object_Class_MailBox);

    RT_OBJECT_HOOK_CALL(rt_object_put_hook, (&(mb->parent.parent)));

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    if (mb->entry == mb->size)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EFULL;
    }

    /* rewind to the previous position */
    if (mb->out_offset > 0)
    {
        mb->out_offset --;
    }
    else
    {
        mb->out_offset = mb->size - 1;
    }

    /* set ptr */
    mb->msg_pool[mb->out_offset] = value;

    /* increase message entry */
    mb->entry ++;

    /* resume suspended thread */
    if (!rt_list_isempty(&mb->parent.suspend_thread))
    {
        _ipc_list_resume(&(mb->parent.suspend_thread));

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        rt_schedule();

        return RT_EOK;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}
RTM_EXPORT(rt_mb_urgent);


/**
 * @brief    This function will receive a mail from mailbox object, if there is no mail in mailbox object,
 *           the thread shall wait for a specified time.
 *
 * @note     Only when there is mail in the mailbox, the receiving thread can get the mail immediately and
 *           return RT_EOK, otherwise the receiving thread will be suspended until the set timeout. If the mail
 *           is still not received within the specified time, it will return-RT_ETIMEOUT.
 *
 * @param    mb is a pointer to the mailbox object to be received.
 *
 * @param    value is a flag that you will set for this mailbox's flag.
 *           You can set an mailbox flag, or you can set multiple flags through OR logic operations.
 *
 * @param    timeout is a timeout period (unit: an OS tick). If the mailbox object is not avaliable in the queue,
 *           the thread will wait for the object in the queue up to the amount of time specified by this parameter.
 *
 *           NOTE:
 *           If use Macro RT_WAITING_FOREVER to set this parameter, which means that when the
 *           mailbox object is unavailable in the queue, the thread will be waiting forever.
 *           If use macro RT_WAITING_NO to set this parameter, which means that this
 *           function is non-blocking and will return immediately.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the mailbox release failed.
 */
static rt_err_t _rt_mb_recv(rt_mailbox_t mb, rt_ubase_t *value, rt_int32_t timeout, int suspend_flag)
{
    struct rt_thread *thread;
    rt_base_t level;
    rt_uint32_t tick_delta;
    rt_err_t ret;

    /* parameter check */
    RT_ASSERT(mb != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mb->parent.parent) == RT_Object_Class_MailBox);

    /* current context checking */
    RT_DEBUG_SCHEDULER_AVAILABLE(timeout != 0);

    /* initialize delta tick */
    tick_delta = 0;
    /* get current thread */
    thread = rt_thread_self();

    RT_OBJECT_HOOK_CALL(rt_object_trytake_hook, (&(mb->parent.parent)));

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* for non-blocking call */
    if (mb->entry == 0 && timeout == 0)
    {
        rt_hw_interrupt_enable(level);

        return -RT_ETIMEOUT;
    }

    /* mailbox is empty */
    while (mb->entry == 0)
    {
        /* reset error number in thread */
        thread->error = -RT_EINTR;

        /* no waiting, return timeout */
        if (timeout == 0)
        {
            /* enable interrupt */
            rt_hw_interrupt_enable(level);

            thread->error = -RT_ETIMEOUT;

            return -RT_ETIMEOUT;
        }

        /* suspend current thread */
        ret = _ipc_list_suspend(&(mb->parent.suspend_thread),
                            thread,
                            mb->parent.parent.flag,
                            suspend_flag);
        if (ret != RT_EOK)
        {
            rt_hw_interrupt_enable(level);
            return ret;
        }

        /* has waiting time, start thread timer */
        if (timeout > 0)
        {
            /* get the start tick of timer */
            tick_delta = rt_tick_get();

            RT_DEBUG_LOG(RT_DEBUG_IPC, ("mb_recv: start timer of thread:%s\n",
                                        thread->parent.name));

            /* reset the timeout of thread timer and start it */
            rt_timer_control(&(thread->thread_timer),
                             RT_TIMER_CTRL_SET_TIME,
                             &timeout);
            rt_timer_start(&(thread->thread_timer));
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        /* re-schedule */
        rt_schedule();

        /* resume from suspend state */
        if (thread->error != RT_EOK)
        {
            /* return error */
            return thread->error;
        }

        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        /* if it's not waiting forever and then re-calculate timeout tick */
        if (timeout > 0)
        {
            tick_delta = rt_tick_get() - tick_delta;
            timeout -= tick_delta;
            if (timeout < 0)
                timeout = 0;
        }
    }

    /* fill ptr */
    *value = mb->msg_pool[mb->out_offset];

    /* increase output offset */
    ++ mb->out_offset;
    if (mb->out_offset >= mb->size)
        mb->out_offset = 0;

    /* decrease message entry */
    if(mb->entry > 0)
    {
        mb->entry --;
    }

    /* resume suspended thread */
    if (!rt_list_isempty(&(mb->suspend_sender_thread)))
    {
        _ipc_list_resume(&(mb->suspend_sender_thread));

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        RT_OBJECT_HOOK_CALL(rt_object_take_hook, (&(mb->parent.parent)));

        rt_schedule();

        return RT_EOK;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    RT_OBJECT_HOOK_CALL(rt_object_take_hook, (&(mb->parent.parent)));

    return RT_EOK;
}

rt_err_t rt_mb_recv(rt_mailbox_t mb, rt_ubase_t *value, rt_int32_t timeout)
{
    return _rt_mb_recv(mb, value, timeout, RT_UNINTERRUPTIBLE);
}
RTM_EXPORT(rt_mb_recv);

rt_err_t rt_mb_recv_interruptibale(rt_mailbox_t mb, rt_ubase_t *value, rt_int32_t timeout)
{
    return _rt_mb_recv(mb, value, timeout, RT_INTERRUPTIBLE);
}
RTM_EXPORT(rt_mb_recv_interruptibale);

rt_err_t rt_mb_recv_killable(rt_mailbox_t mb, rt_ubase_t *value, rt_int32_t timeout)
{
    return _rt_mb_recv(mb, value, timeout, RT_KILLABLE);
}
RTM_EXPORT(rt_mb_recv_killable);

/**
 * @brief    This function will set some extra attributions of a mailbox object.
 *
 * @note     Currently this function only supports the RT_IPC_CMD_RESET command to reset the mailbox.
 *
 * @param    mb is a pointer to a mailbox object.
 *
 * @param    cmd is a command used to configure some attributions of the mailbox.
 *
 * @param    arg is the argument of the function to execute the command.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that this function failed to execute.
 */
rt_err_t rt_mb_control(rt_mailbox_t mb, int cmd, void *arg)
{
    rt_base_t level;

    /* parameter check */
    RT_ASSERT(mb != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mb->parent.parent) == RT_Object_Class_MailBox);

    if (cmd == RT_IPC_CMD_RESET)
    {
        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        /* resume all waiting thread */
        _ipc_list_resume_all(&(mb->parent.suspend_thread));
        /* also resume all mailbox private suspended thread */
        _ipc_list_resume_all(&(mb->suspend_sender_thread));

        /* re-init mailbox */
        mb->entry      = 0;
        mb->in_offset  = 0;
        mb->out_offset = 0;

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        rt_schedule();

        return RT_EOK;
    }

    return -RT_ERROR;
}
RTM_EXPORT(rt_mb_control);

/**@}*/
#endif /* RT_USING_MAILBOX */

#ifdef RT_USING_MESSAGEQUEUE
/**
 * @addtogroup messagequeue
 * @{
 */

struct rt_mq_message
{
    struct rt_mq_message *next;
};


/**
 * @brief    Initialize a static messagequeue object.
 *
 * @note     For the static messagequeue object, its memory space is allocated by the compiler during compiling,
 *           and shall placed on the read-write data segment or on the uninitialized data segment.
 *           By contrast, the rt_mq_create() function will allocate memory space automatically
 *           and initialize the messagequeue.
 *
 * @see      rt_mq_create()
 *
 * @param    mq is a pointer to the messagequeue to initialize. It is assumed that storage for
 *           the messagequeue will be allocated in your application.
 *
 * @param    name is a pointer to the name that given to the messagequeue.
 *
 * @param    msgpool is a pointer to the starting address of the memory space you allocated for
 *           the messagequeue in advance.
 *           In other words, msgpool is a pointer to the messagequeue buffer of the starting address.
 *
 * @param    msg_size is the maximum length of a message in the messagequeue (Unit: Byte).
 *
 * @param    pool_size is the size of the memory space allocated for the messagequeue in advance.
 *
 * @param    flag is the messagequeue flag, which determines the queuing way of how multiple threads wait
 *           when the messagequeue is not available.
 *           The messagequeue flag can be ONE of the following values:
 *
 *               RT_IPC_FLAG_PRIO          The pending threads will queue in order of priority.
 *
 *               RT_IPC_FLAG_FIFO          The pending threads will queue in the first-in-first-out method
 *                                         (also known as first-come-first-served (FCFS) scheduling strategy).
 *
 *               NOTE: RT_IPC_FLAG_FIFO is a non-real-time scheduling mode. It is strongly recommended to
 *               use RT_IPC_FLAG_PRIO to ensure the thread is real-time UNLESS your applications concern about
 *               the first-in-first-out principle, and you clearly understand that all threads involved in
 *               this messagequeue will become non-real-time threads.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the initialization is successful.
 *           If the return value is any other values, it represents the initialization failed.
 *
 * @warning  This function can ONLY be called from threads.
 */
rt_err_t rt_mq_init(rt_mq_t     mq,
                    const char *name,
                    void       *msgpool,
                    rt_size_t   msg_size,
                    rt_size_t   pool_size,
                    rt_uint8_t  flag)
{
    struct rt_mq_message *head;
    rt_base_t temp;
    register rt_size_t msg_align_size;

    /* parameter check */
    RT_ASSERT(mq != RT_NULL);
    RT_ASSERT((flag == RT_IPC_FLAG_FIFO) || (flag == RT_IPC_FLAG_PRIO));

    /* initialize object */
    rt_object_init(&(mq->parent.parent), RT_Object_Class_MessageQueue, name);

    /* set parent flag */
    mq->parent.parent.flag = flag;

    /* initialize ipc object */
    _ipc_object_init(&(mq->parent));

    /* set message pool */
    mq->msg_pool = msgpool;

    /* get correct message size */
    msg_align_size = RT_ALIGN(msg_size, RT_ALIGN_SIZE);
    mq->msg_size = msg_size;
    mq->max_msgs = pool_size / (msg_align_size + sizeof(struct rt_mq_message));

    if (0 == mq->max_msgs)
    {
        return -RT_EINVAL;
    }

    /* initialize message list */
    mq->msg_queue_head = RT_NULL;
    mq->msg_queue_tail = RT_NULL;

    /* initialize message empty list */
    mq->msg_queue_free = RT_NULL;
    for (temp = 0; temp < mq->max_msgs; temp ++)
    {
        head = (struct rt_mq_message *)((rt_uint8_t *)mq->msg_pool +
                                        temp * (msg_align_size + sizeof(struct rt_mq_message)));
        head->next = (struct rt_mq_message *)mq->msg_queue_free;
        mq->msg_queue_free = head;
    }

    /* the initial entry is zero */
    mq->entry = 0;

    /* initialize an additional list of sender suspend thread */
    rt_list_init(&(mq->suspend_sender_thread));

    return RT_EOK;
}
RTM_EXPORT(rt_mq_init);


/**
 * @brief    This function will detach a static messagequeue object.
 *
 * @note     This function is used to detach a static messagequeue object which is initialized by rt_mq_init() function.
 *           By contrast, the rt_mq_delete() function will delete a messagequeue object.
 *           When the messagequeue is successfully detached, it will resume all suspended threads in the messagequeue list.
 *
 * @see      rt_mq_delete()
 *
 * @param    mq is a pointer to a messagequeue object to be detached.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the initialization is successful.
 *           If the return value is any other values, it means that the messagequeue detach failed.
 *
 * @warning  This function can ONLY detach a static messagequeue initialized by the rt_mq_init() function.
 *           If the messagequeue is created by the rt_mq_create() function, you MUST NOT USE this function to detach it,
 *           and ONLY USE the rt_mq_delete() function to complete the deletion.
 */
rt_err_t rt_mq_detach(rt_mq_t mq)
{
    /* parameter check */
    RT_ASSERT(mq != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mq->parent.parent) == RT_Object_Class_MessageQueue);
    RT_ASSERT(rt_object_is_systemobject(&mq->parent.parent));

    /* resume all suspended thread */
    _ipc_list_resume_all(&mq->parent.suspend_thread);
    /* also resume all message queue private suspended thread */
    _ipc_list_resume_all(&(mq->suspend_sender_thread));

    /* detach message queue object */
    rt_object_detach(&(mq->parent.parent));

    return RT_EOK;
}
RTM_EXPORT(rt_mq_detach);

#ifdef RT_USING_HEAP
/**
 * @brief    Creating a messagequeue object.
 *
 * @note     For the messagequeue object, its memory space is allocated automatically.
 *           By contrast, the rt_mq_init() function will initialize a static messagequeue object.
 *
 * @see      rt_mq_init()
 *
 * @param    name is a pointer that given to the messagequeue.
 *
 * @param    msg_size is the maximum length of a message in the messagequeue (Unit: Byte).
 *
 * @param    max_msgs is the maximum number of messages in the messagequeue.
 *
 * @param    flag is the messagequeue flag, which determines the queuing way of how multiple threads wait
 *           when the messagequeue is not available.
 *           The messagequeue flag can be ONE of the following values:
 *
 *               RT_IPC_FLAG_PRIO          The pending threads will queue in order of priority.
 *
 *               RT_IPC_FLAG_FIFO          The pending threads will queue in the first-in-first-out method
 *                                         (also known as first-come-first-served (FCFS) scheduling strategy).
 *
 *               NOTE: RT_IPC_FLAG_FIFO is a non-real-time scheduling mode. It is strongly recommended to
 *               use RT_IPC_FLAG_PRIO to ensure the thread is real-time UNLESS your applications concern about
 *               the first-in-first-out principle, and you clearly understand that all threads involved in
 *               this messagequeue will become non-real-time threads.
 *
 * @return   Return a pointer to the messagequeue object. When the return value is RT_NULL, it means the creation failed.
 *
 * @warning  This function can NOT be called in interrupt context. You can use macor RT_DEBUG_NOT_IN_INTERRUPT to check it.
 */
rt_mq_t rt_mq_create(const char *name,
                     rt_size_t   msg_size,
                     rt_size_t   max_msgs,
                     rt_uint8_t  flag)
{
    struct rt_messagequeue *mq;
    struct rt_mq_message *head;
    rt_base_t temp;
    register rt_size_t msg_align_size;

    RT_ASSERT((flag == RT_IPC_FLAG_FIFO) || (flag == RT_IPC_FLAG_PRIO));

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* allocate object */
    mq = (rt_mq_t)rt_object_allocate(RT_Object_Class_MessageQueue, name);
    if (mq == RT_NULL)
        return mq;

    /* set parent */
    mq->parent.parent.flag = flag;

    /* initialize ipc object */
    _ipc_object_init(&(mq->parent));

    /* initialize message queue */

    /* get correct message size */
    msg_align_size = RT_ALIGN(msg_size, RT_ALIGN_SIZE);
    mq->msg_size = msg_size;
    mq->max_msgs = max_msgs;

    /* allocate message pool */
    mq->msg_pool = RT_KERNEL_MALLOC((msg_align_size + sizeof(struct rt_mq_message)) * mq->max_msgs);
    if (mq->msg_pool == RT_NULL)
    {
        rt_object_delete(&(mq->parent.parent));

        return RT_NULL;
    }

    /* initialize message list */
    mq->msg_queue_head = RT_NULL;
    mq->msg_queue_tail = RT_NULL;

    /* initialize message empty list */
    mq->msg_queue_free = RT_NULL;
    for (temp = 0; temp < mq->max_msgs; temp ++)
    {
        head = (struct rt_mq_message *)((rt_uint8_t *)mq->msg_pool +
                                        temp * (msg_align_size + sizeof(struct rt_mq_message)));
        head->next = (struct rt_mq_message *)mq->msg_queue_free;
        mq->msg_queue_free = head;
    }

    /* the initial entry is zero */
    mq->entry = 0;

    /* initialize an additional list of sender suspend thread */
    rt_list_init(&(mq->suspend_sender_thread));

    return mq;
}
RTM_EXPORT(rt_mq_create);


/**
 * @brief    This function will delete a messagequeue object and release the memory.
 *
 * @note     This function is used to delete a messagequeue object which is created by the rt_mq_create() function.
 *           By contrast, the rt_mq_detach() function will detach a static messagequeue object.
 *           When the messagequeue is successfully deleted, it will resume all suspended threads in the messagequeue list.
 *
 * @see      rt_mq_detach()
 *
 * @param    mq is a pointer to a messagequeue object to be deleted.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the messagequeue detach failed.
 *
 * @warning  This function can ONLY delete a messagequeue initialized by the rt_mq_create() function.
 *           If the messagequeue is initialized by the rt_mq_init() function, you MUST NOT USE this function to delete it,
 *           ONLY USE the rt_mq_detach() function to complete the detachment.
 *           for example,the rt_mq_create() function, it cannot be called in interrupt context.
 */
rt_err_t rt_mq_delete(rt_mq_t mq)
{
    /* parameter check */
    RT_ASSERT(mq != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mq->parent.parent) == RT_Object_Class_MessageQueue);
    RT_ASSERT(rt_object_is_systemobject(&mq->parent.parent) == RT_FALSE);

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* resume all suspended thread */
    _ipc_list_resume_all(&(mq->parent.suspend_thread));
    /* also resume all message queue private suspended thread */
    _ipc_list_resume_all(&(mq->suspend_sender_thread));

    /* free message queue pool */
    RT_KERNEL_FREE(mq->msg_pool);

    /* delete message queue object */
    rt_object_delete(&(mq->parent.parent));

    return RT_EOK;
}
RTM_EXPORT(rt_mq_delete);
#endif /* RT_USING_HEAP */


/**
 * @brief    This function will send a message to the messagequeue object. If
 *           there is a thread suspended on the messagequeue, the thread will be
 *           resumed.
 *
 * @note     When using this function to send a message, if the messagequeue is
 *           fully used, the current thread will wait for a timeout. If reaching
 *           the timeout and there is still no space available, the sending
 *           thread will be resumed and an error code will be returned. By
 *           contrast, the rt_mq_send() function will return an error code
 *           immediately without waiting when the messagequeue if fully used.
 *
 * @see      rt_mq_send()
 *
 * @param    mq is a pointer to the messagequeue object to be sent.
 *
 * @param    buffer is the content of the message.
 *
 * @param    size is the length of the message(Unit: Byte).
 *
 * @param    timeout is a timeout period (unit: an OS tick).
 *
 * @return   Return the operation status. When the return value is RT_EOK, the
 *           operation is successful. If the return value is any other values,
 *           it means that the messagequeue detach failed.
 *
 * @warning  This function can be called in interrupt context and thread
 * context.
 */
static rt_err_t _rt_mq_send_wait(rt_mq_t     mq,
                         const void *buffer,
                         rt_size_t   size,
                         rt_int32_t  timeout,
                         int suspend_flag)
{
    rt_base_t level;
    struct rt_mq_message *msg;
    rt_uint32_t tick_delta;
    struct rt_thread *thread;
    rt_err_t ret;

    /* parameter check */
    RT_ASSERT(mq != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mq->parent.parent) == RT_Object_Class_MessageQueue);
    RT_ASSERT(buffer != RT_NULL);
    RT_ASSERT(size != 0);

    /* current context checking */
    RT_DEBUG_SCHEDULER_AVAILABLE(timeout != 0);

    /* greater than one message size */
    if (size > mq->msg_size)
        return -RT_ERROR;

    /* initialize delta tick */
    tick_delta = 0;
    /* get current thread */
    thread = rt_thread_self();

    RT_OBJECT_HOOK_CALL(rt_object_put_hook, (&(mq->parent.parent)));

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* get a free list, there must be an empty item */
    msg = (struct rt_mq_message *)mq->msg_queue_free;
    /* for non-blocking call */
    if (msg == RT_NULL && timeout == 0)
    {
        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        return -RT_EFULL;
    }

    /* message queue is full */
    while ((msg = (struct rt_mq_message *)mq->msg_queue_free) == RT_NULL)
    {
        /* reset error number in thread */
        thread->error = -RT_EINTR;

        /* no waiting, return timeout */
        if (timeout == 0)
        {
            /* enable interrupt */
            rt_hw_interrupt_enable(level);

            return -RT_EFULL;
        }

        /* suspend current thread */
        ret = _ipc_list_suspend(&(mq->suspend_sender_thread),
                            thread,
                            mq->parent.parent.flag,
                            suspend_flag);
        if (ret != RT_EOK)
        {
            rt_hw_interrupt_enable(level);
            return ret;
        }

        /* has waiting time, start thread timer */
        if (timeout > 0)
        {
            /* get the start tick of timer */
            tick_delta = rt_tick_get();

            RT_DEBUG_LOG(RT_DEBUG_IPC, ("mq_send_wait: start timer of thread:%s\n",
                                        thread->parent.name));

            /* reset the timeout of thread timer and start it */
            rt_timer_control(&(thread->thread_timer),
                             RT_TIMER_CTRL_SET_TIME,
                             &timeout);
            rt_timer_start(&(thread->thread_timer));
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        /* re-schedule */
        rt_schedule();

        /* resume from suspend state */
        if (thread->error != RT_EOK)
        {
            /* return error */
            return thread->error;
        }

        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        /* if it's not waiting forever and then re-calculate timeout tick */
        if (timeout > 0)
        {
            tick_delta = rt_tick_get() - tick_delta;
            timeout -= tick_delta;
            if (timeout < 0)
                timeout = 0;
        }
    }

    /* move free list pointer */
    mq->msg_queue_free = msg->next;

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    /* the msg is the new tailer of list, the next shall be NULL */
    msg->next = RT_NULL;
    /* copy buffer */
    rt_memcpy(msg + 1, buffer, size);

    /* disable interrupt */
    level = rt_hw_interrupt_disable();
    /* link msg to message queue */
    if (mq->msg_queue_tail != RT_NULL)
    {
        /* if the tail exists, */
        ((struct rt_mq_message *)mq->msg_queue_tail)->next = msg;
    }

    /* set new tail */
    mq->msg_queue_tail = msg;
    /* if the head is empty, set head */
    if (mq->msg_queue_head == RT_NULL)
        mq->msg_queue_head = msg;

    if(mq->entry < RT_MQ_ENTRY_MAX)
    {
        /* increase message entry */
        mq->entry ++;
    }
    else
    {
        rt_hw_interrupt_enable(level); /* enable interrupt */
        return -RT_EFULL; /* value overflowed */
    }

    /* resume suspended thread */
    if (!rt_list_isempty(&mq->parent.suspend_thread))
    {
        _ipc_list_resume(&(mq->parent.suspend_thread));

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        rt_schedule();

        return RT_EOK;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t rt_mq_send_wait(rt_mq_t     mq,
                         const void *buffer,
                         rt_size_t   size,
                         rt_int32_t  timeout)
{
    return _rt_mq_send_wait(mq, buffer, size, timeout, RT_UNINTERRUPTIBLE);
}
RTM_EXPORT(rt_mq_send_wait)

rt_err_t rt_mq_send_wait_interruptible(rt_mq_t     mq,
                         const void *buffer,
                         rt_size_t   size,
                         rt_int32_t  timeout)
{
    return _rt_mq_send_wait(mq, buffer, size, timeout, RT_INTERRUPTIBLE);
}
RTM_EXPORT(rt_mq_send_wait_interruptible)

rt_err_t rt_mq_send_wait_killable(rt_mq_t     mq,
                         const void *buffer,
                         rt_size_t   size,
                         rt_int32_t  timeout)
{
    return _rt_mq_send_wait(mq, buffer, size, timeout, RT_KILLABLE);
}
RTM_EXPORT(rt_mq_send_wait_killable)
/**
 * @brief    This function will send a message to the messagequeue object.
 *           If there is a thread suspended on the messagequeue, the thread will be resumed.
 *
 * @note     When using this function to send a message, if the messagequeue is fully used,
 *           the current thread will wait for a timeout.
 *           By contrast, when the messagequeue is fully used, the rt_mq_send_wait() function will
 *           return an error code immediately without waiting.
 *
 * @see      rt_mq_send_wait()
 *
 * @param    mq is a pointer to the messagequeue object to be sent.
 *
 * @param    buffer is the content of the message.
 *
 * @param    size is the length of the message(Unit: Byte).
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the messagequeue detach failed.
 *
 * @warning  This function can be called in interrupt context and thread context.
 */
rt_err_t rt_mq_send(rt_mq_t mq, const void *buffer, rt_size_t size)
{
    return rt_mq_send_wait(mq, buffer, size, 0);
}
RTM_EXPORT(rt_mq_send);

rt_err_t rt_mq_send_interrupt(rt_mq_t mq, const void *buffer, rt_size_t size)
{
    return rt_mq_send_wait_interruptible(mq, buffer, size, 0);
}
RTM_EXPORT(rt_mq_send_interrupt);

rt_err_t rt_mq_send_killable(rt_mq_t mq, const void *buffer, rt_size_t size)
{
    return rt_mq_send_wait_killable(mq, buffer, size, 0);
}
RTM_EXPORT(rt_mq_send_killable);
/**
 * @brief    This function will send an urgent message to the messagequeue object.
 *
 * @note     This function is almost the same as the rt_mq_send() function. The only difference is that
 *           when sending an urgent message, the message is placed at the head of the messagequeue so that
 *           the recipient can receive the urgent message first.
 *
 * @see      rt_mq_send()
 *
 * @param    mq is a pointer to the messagequeue object to be sent.
 *
 * @param    buffer is the content of the message.
 *
 * @param    size is the length of the message(Unit: Byte).
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the mailbox detach failed.
 */
rt_err_t rt_mq_urgent(rt_mq_t mq, const void *buffer, rt_size_t size)
{
    rt_base_t level;
    struct rt_mq_message *msg;

    /* parameter check */
    RT_ASSERT(mq != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mq->parent.parent) == RT_Object_Class_MessageQueue);
    RT_ASSERT(buffer != RT_NULL);
    RT_ASSERT(size != 0);

    /* greater than one message size */
    if (size > mq->msg_size)
        return -RT_ERROR;

    RT_OBJECT_HOOK_CALL(rt_object_put_hook, (&(mq->parent.parent)));

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* get a free list, there must be an empty item */
    msg = (struct rt_mq_message *)mq->msg_queue_free;
    /* message queue is full */
    if (msg == RT_NULL)
    {
        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        return -RT_EFULL;
    }
    /* move free list pointer */
    mq->msg_queue_free = msg->next;

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    /* copy buffer */
    rt_memcpy(msg + 1, buffer, size);

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* link msg to the beginning of message queue */
    msg->next = (struct rt_mq_message *)mq->msg_queue_head;
    mq->msg_queue_head = msg;

    /* if there is no tail */
    if (mq->msg_queue_tail == RT_NULL)
        mq->msg_queue_tail = msg;

    if(mq->entry < RT_MQ_ENTRY_MAX)
    {
        /* increase message entry */
        mq->entry ++;
    }
    else
    {
        rt_hw_interrupt_enable(level); /* enable interrupt */
        return -RT_EFULL; /* value overflowed */
    }

    /* resume suspended thread */
    if (!rt_list_isempty(&mq->parent.suspend_thread))
    {
        _ipc_list_resume(&(mq->parent.suspend_thread));

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        rt_schedule();

        return RT_EOK;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}
RTM_EXPORT(rt_mq_urgent);


/**
 * @brief    This function will receive a message from message queue object,
 *           if there is no message in messagequeue object, the thread shall wait for a specified time.
 *
 * @note     Only when there is mail in the mailbox, the receiving thread can get the mail immediately and return RT_EOK,
 *           otherwise the receiving thread will be suspended until timeout.
 *           If the mail is not received within the specified time, it will return -RT_ETIMEOUT.
 *
 * @param    mq is a pointer to the messagequeue object to be received.
 *
 * @param    buffer is the content of the message.
 *
 * @param    size is the length of the message(Unit: Byte).
 *
 * @param    timeout is a timeout period (unit: an OS tick). If the message is unavailable, the thread will wait for
 *           the message in the queue up to the amount of time specified by this parameter.
 *
 *           NOTE:
 *           If use Macro RT_WAITING_FOREVER to set this parameter, which means that when the
 *           message is unavailable in the queue, the thread will be waiting forever.
 *           If use macro RT_WAITING_NO to set this parameter, which means that this
 *           function is non-blocking and will return immediately.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the mailbox release failed.
 */
static rt_err_t _rt_mq_recv(rt_mq_t    mq,
                    void      *buffer,
                    rt_size_t  size,
                    rt_int32_t timeout,
                    int suspend_flag)
{
    struct rt_thread *thread;
    rt_base_t level;
    struct rt_mq_message *msg;
    rt_uint32_t tick_delta;
    rt_err_t ret;

    /* parameter check */
    RT_ASSERT(mq != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mq->parent.parent) == RT_Object_Class_MessageQueue);
    RT_ASSERT(buffer != RT_NULL);
    RT_ASSERT(size != 0);

    /* current context checking */
    RT_DEBUG_SCHEDULER_AVAILABLE(timeout != 0);

    /* initialize delta tick */
    tick_delta = 0;
    /* get current thread */
    thread = rt_thread_self();
    RT_OBJECT_HOOK_CALL(rt_object_trytake_hook, (&(mq->parent.parent)));

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* for non-blocking call */
    if (mq->entry == 0 && timeout == 0)
    {
        rt_hw_interrupt_enable(level);

        return -RT_ETIMEOUT;
    }

    /* message queue is empty */
    while (mq->entry == 0)
    {
        /* reset error number in thread */
        thread->error = -RT_EINTR;

        /* no waiting, return timeout */
        if (timeout == 0)
        {
            /* enable interrupt */
            rt_hw_interrupt_enable(level);

            thread->error = -RT_ETIMEOUT;

            return -RT_ETIMEOUT;
        }

        /* suspend current thread */
        ret = _ipc_list_suspend(&(mq->parent.suspend_thread),
                            thread,
                            mq->parent.parent.flag,
                            suspend_flag);
        if (ret != RT_EOK)
        {
            rt_hw_interrupt_enable(level);
            return ret;
        }

        /* has waiting time, start thread timer */
        if (timeout > 0)
        {
            /* get the start tick of timer */
            tick_delta = rt_tick_get();

            RT_DEBUG_LOG(RT_DEBUG_IPC, ("set thread:%s to timer list\n",
                                        thread->parent.name));

            /* reset the timeout of thread timer and start it */
            rt_timer_control(&(thread->thread_timer),
                             RT_TIMER_CTRL_SET_TIME,
                             &timeout);
            rt_timer_start(&(thread->thread_timer));
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        /* re-schedule */
        rt_schedule();

        /* recv message */
        if (thread->error != RT_EOK)
        {
            /* return error */
            return thread->error;
        }

        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        /* if it's not waiting forever and then re-calculate timeout tick */
        if (timeout > 0)
        {
            tick_delta = rt_tick_get() - tick_delta;
            timeout -= tick_delta;
            if (timeout < 0)
                timeout = 0;
        }
    }

    /* get message from queue */
    msg = (struct rt_mq_message *)mq->msg_queue_head;

    /* move message queue head */
    mq->msg_queue_head = msg->next;
    /* reach queue tail, set to NULL */
    if (mq->msg_queue_tail == msg)
        mq->msg_queue_tail = RT_NULL;

    /* decrease message entry */
    if(mq->entry > 0)
    {
        mq->entry --;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    /* copy message */
    rt_memcpy(buffer, msg + 1, size > mq->msg_size ? mq->msg_size : size);

    /* disable interrupt */
    level = rt_hw_interrupt_disable();
    /* put message to free list */
    msg->next = (struct rt_mq_message *)mq->msg_queue_free;
    mq->msg_queue_free = msg;

    /* resume suspended thread */
    if (!rt_list_isempty(&(mq->suspend_sender_thread)))
    {
        _ipc_list_resume(&(mq->suspend_sender_thread));

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        RT_OBJECT_HOOK_CALL(rt_object_take_hook, (&(mq->parent.parent)));

        rt_schedule();

        return RT_EOK;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    RT_OBJECT_HOOK_CALL(rt_object_take_hook, (&(mq->parent.parent)));

    return RT_EOK;
}

rt_err_t rt_mq_recv(rt_mq_t    mq,
                    void      *buffer,
                    rt_size_t  size,
                    rt_int32_t timeout)
{
    return _rt_mq_recv(mq, buffer, size, timeout, RT_UNINTERRUPTIBLE);
}
RTM_EXPORT(rt_mq_recv);

rt_err_t rt_mq_recv_interruptible(rt_mq_t    mq,
                    void      *buffer,
                    rt_size_t  size,
                    rt_int32_t timeout)
{
    return _rt_mq_recv(mq, buffer, size, timeout, RT_INTERRUPTIBLE);
}
RTM_EXPORT(rt_mq_recv_interruptible);

rt_err_t rt_mq_recv_killable(rt_mq_t    mq,
                    void      *buffer,
                    rt_size_t  size,
                    rt_int32_t timeout)
{
    return _rt_mq_recv(mq, buffer, size, timeout, RT_KILLABLE);
}
RTM_EXPORT(rt_mq_recv_killable);
/**
 * @brief    This function will set some extra attributions of a messagequeue object.
 *
 * @note     Currently this function only supports the RT_IPC_CMD_RESET command to reset the messagequeue.
 *
 * @param    mq is a pointer to a messagequeue object.
 *
 * @param    cmd is a command used to configure some attributions of the messagequeue.
 *
 * @param    arg is the argument of the function to execute the command.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that this function failed to execute.
 */
rt_err_t rt_mq_control(rt_mq_t mq, int cmd, void *arg)
{
    rt_base_t level;
    struct rt_mq_message *msg;

    /* parameter check */
    RT_ASSERT(mq != RT_NULL);
    RT_ASSERT(rt_object_get_type(&mq->parent.parent) == RT_Object_Class_MessageQueue);

    if (cmd == RT_IPC_CMD_RESET)
    {
        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        /* resume all waiting thread */
        _ipc_list_resume_all(&mq->parent.suspend_thread);
        /* also resume all message queue private suspended thread */
        _ipc_list_resume_all(&(mq->suspend_sender_thread));

        /* release all message in the queue */
        while (mq->msg_queue_head != RT_NULL)
        {
            /* get message from queue */
            msg = (struct rt_mq_message *)mq->msg_queue_head;

            /* move message queue head */
            mq->msg_queue_head = msg->next;
            /* reach queue tail, set to NULL */
            if (mq->msg_queue_tail == msg)
                mq->msg_queue_tail = RT_NULL;

            /* put message to free list */
            msg->next = (struct rt_mq_message *)mq->msg_queue_free;
            mq->msg_queue_free = msg;
        }

        /* clean entry */
        mq->entry = 0;

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        rt_schedule();

        return RT_EOK;
    }

    return -RT_ERROR;
}
RTM_EXPORT(rt_mq_control);

/**@}*/
#endif /* RT_USING_MESSAGEQUEUE */
/**@}*/
