/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-30     heyuanjie87  the first version
 *
 */

#include <rthw.h>
#include <rtthread.h>

#ifndef SYSTEM_THREAD_STACK_SIZE
#define SYSTEM_THREAD_STACK_SIZE IDLE_THREAD_STACK_SIZE
#endif
static rt_list_t          _rt_thread_defunct = RT_LIST_OBJECT_INIT(_rt_thread_defunct);
static struct rt_spinlock _defunct_spinlock;
#if defined(RT_USING_SMP) || defined(RT_USING_SMART)
static struct rt_thread rt_system_thread;
rt_align(RT_ALIGN_SIZE) static rt_uint8_t rt_system_stack[SYSTEM_THREAD_STACK_SIZE];
static struct rt_semaphore system_sem;
#endif

/**
 * @brief Enqueue a thread to defunct queue.
 *
 * @param thread the thread to be enqueued.
 *
 * @note It must be called between rt_hw_interrupt_disable and rt_hw_interrupt_enable
 */
void rt_thread_defunct_enqueue(rt_thread_t thread)
{
    rt_base_t level;
    level = rt_spin_lock_irqsave(&_defunct_spinlock);
    rt_list_insert_after(&_rt_thread_defunct, &RT_THREAD_LIST_NODE(thread));
    rt_spin_unlock_irqrestore(&_defunct_spinlock, level);
#if defined(RT_USING_SMP) || defined(RT_USING_SMART)
    rt_sem_release(&system_sem);
#endif
}

/**
 * @brief Dequeue a thread from defunct queue.
 */
rt_thread_t rt_thread_defunct_dequeue(void)
{
    rt_base_t   level;
    rt_thread_t thread = RT_NULL;
    rt_list_t  *l      = &_rt_thread_defunct;

    level = rt_spin_lock_irqsave(&_defunct_spinlock);
    if (!rt_list_isempty(l))
    {
        thread = RT_THREAD_LIST_NODE_ENTRY(l->next);
        rt_list_remove(&RT_THREAD_LIST_NODE(thread));
    }
    rt_spin_unlock_irqrestore(&_defunct_spinlock, level);

    return thread;
}

/**
 * @brief This function will perform system background job when system idle.
 */
void rt_defunct_execute(void)
{
    /* Loop until there is no dead thread. So one call to rt_defunct_execute
     * will do all the cleanups. */
    while (1)
    {
        rt_thread_t thread;
        rt_bool_t   object_is_systemobject;
        void (*cleanup)(struct rt_thread *tid);

#ifdef RT_USING_MODULE
        struct rt_dlmodule *module = RT_NULL;
#endif
        /* get defunct thread */
        thread = rt_thread_defunct_dequeue();
        if (thread == RT_NULL)
        {
            break;
        }

#ifdef RT_USING_MODULE
        module = (struct rt_dlmodule *)thread->parent.module_id;
        if (module)
        {
            dlmodule_destroy(module);
        }
#endif

#ifdef RT_USING_SIGNALS
        rt_thread_free_sig(thread);
#endif

        /* store the point of "thread->cleanup" avoid to lose */
        cleanup = thread->cleanup;

        /* if it's a system object, detach it */
        object_is_systemobject = rt_object_is_systemobject((rt_object_t)thread);
        if (object_is_systemobject == RT_TRUE)
        {
            /* detach this object */
            rt_object_detach((rt_object_t)thread);
        }

        /* invoke thread cleanup */
        if (cleanup != RT_NULL)
        {
            cleanup(thread);
        }

#ifdef RT_USING_HEAP
#ifdef RT_USING_MEM_PROTECTION
        if (thread->mem_regions != RT_NULL)
        {
            RT_KERNEL_FREE(thread->mem_regions);
        }
#endif
        /* if need free, delete it */
        if (object_is_systemobject == RT_FALSE)
        {
            /* release thread's stack */
#ifdef RT_USING_HW_STACK_GUARD
            RT_KERNEL_FREE(thread->stack_buf);
#else
            RT_KERNEL_FREE(thread->stack_addr);
#endif
            /* delete thread object */
            rt_object_delete((rt_object_t)thread);
        }
#endif
    }
}

#if defined(RT_USING_SMP) || defined(RT_USING_SMART)
static void rt_thread_system_entry(void *parameter)
{
    RT_UNUSED(parameter);

    while (1)
    {
        int ret = rt_sem_take(&system_sem, RT_WAITING_FOREVER);
        if (ret != RT_EOK)
        {
            rt_kprintf("failed to sem_take() error %d\n", ret);
            RT_ASSERT(0);
        }
        rt_defunct_execute();
    }
}
#endif

void rt_thread_defunct_init(void)
{
    RT_ASSERT(RT_THREAD_PRIORITY_MAX > 2);

    rt_spin_lock_init(&_defunct_spinlock);

#if defined(RT_USING_SMP) || defined(RT_USING_SMART)
    rt_sem_init(&system_sem, "defunct", 0, RT_IPC_FLAG_FIFO);

    /* create defunct thread */
    rt_thread_init(&rt_system_thread,
                   "tsystem",
                   rt_thread_system_entry,
                   RT_NULL,
                   rt_system_stack,
                   sizeof(rt_system_stack),
                   RT_THREAD_PRIORITY_MAX - 2,
                   32);
    /* startup */
    rt_thread_startup(&rt_system_thread);
#endif
}
