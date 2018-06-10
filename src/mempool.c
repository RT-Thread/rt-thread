/*
 * File      : mempool.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-05-27     Bernard      implement memory pool
 * 2006-06-03     Bernard      fix the thread timer init bug
 * 2006-06-30     Bernard      fix the allocate/free block bug
 * 2006-08-04     Bernard      add hook support
 * 2006-08-10     Bernard      fix interrupt bug in rt_mp_alloc
 * 2010-07-13     Bernard      fix RT_ALIGN issue found by kuronca
 * 2010-10-26     yi.qiu       add module support in rt_mp_delete
 * 2011-01-24     Bernard      add object allocation check.
 * 2012-03-22     Bernard      fix align issue in rt_mp_init and rt_mp_create.
 */

#include <rthw.h>
#include <rtthread.h>

#ifdef RT_USING_MEMPOOL

#ifdef RT_USING_HOOK
static void (*rt_mp_alloc_hook)(struct rt_mempool *mp, void *block);
static void (*rt_mp_free_hook)(struct rt_mempool *mp, void *block);

/**
 * @addtogroup Hook
 */

/**@{*/

/**
 * This function will set a hook function, which will be invoked when a memory
 * block is allocated from memory pool.
 *
 * @param hook the hook function
 */
void rt_mp_alloc_sethook(void (*hook)(struct rt_mempool *mp, void *block))
{
    rt_mp_alloc_hook = hook;
}

/**
 * This function will set a hook function, which will be invoked when a memory
 * block is released to memory pool.
 *
 * @param hook the hook function
 */
void rt_mp_free_sethook(void (*hook)(struct rt_mempool *mp, void *block))
{
    rt_mp_free_hook = hook;
}

/**@}*/
#endif

/**
 * @addtogroup MM
 */

/**@{*/

/**
 * This function will initialize a memory pool object, normally which is used
 * for static object.
 *
 * @param mp the memory pool object
 * @param name the name of memory pool
 * @param start the star address of memory pool
 * @param size the total size of memory pool
 * @param block_size the size for each block
 *
 * @return RT_EOK
 */
rt_err_t rt_mp_init(struct rt_mempool *mp,
                    const char        *name,
                    void              *start,
                    rt_size_t          size,
                    rt_size_t          block_size)
{
    rt_uint8_t *block_ptr;
    register rt_size_t offset;

    /* parameter check */
    RT_ASSERT(mp != RT_NULL);

    /* initialize object */
    rt_object_init(&(mp->parent), RT_Object_Class_MemPool, name);

    /* initialize memory pool */
    mp->start_address = start;
    mp->size = RT_ALIGN_DOWN(size, RT_ALIGN_SIZE);

    /* align the block size */
    block_size = RT_ALIGN(block_size, RT_ALIGN_SIZE);
    mp->block_size = block_size;

    /* align to align size byte */
    mp->block_total_count = mp->size / (mp->block_size + sizeof(rt_uint8_t *));
    mp->block_free_count  = mp->block_total_count;

    /* initialize suspended thread list */
    rt_list_init(&(mp->suspend_thread));
    mp->suspend_thread_count = 0;

    /* initialize free block list */
    block_ptr = (rt_uint8_t *)mp->start_address;
    for (offset = 0; offset < mp->block_total_count; offset ++)
    {
        *(rt_uint8_t **)(block_ptr + offset * (block_size + sizeof(rt_uint8_t *))) =
            (rt_uint8_t *)(block_ptr + (offset + 1) * (block_size + sizeof(rt_uint8_t *)));
    }

    *(rt_uint8_t **)(block_ptr + (offset - 1) * (block_size + sizeof(rt_uint8_t *))) =
        RT_NULL;

    mp->block_list = block_ptr;

    return RT_EOK;
}
RTM_EXPORT(rt_mp_init);

/**
 * This function will detach a memory pool from system object management.
 *
 * @param mp the memory pool object
 *
 * @return RT_EOK
 */
rt_err_t rt_mp_detach(struct rt_mempool *mp)
{
    struct rt_thread *thread;
    register rt_ubase_t temp;

    /* parameter check */
    RT_ASSERT(mp != RT_NULL);

    /* wake up all suspended threads */
    while (!rt_list_isempty(&(mp->suspend_thread)))
    {
        /* disable interrupt */
        temp = rt_hw_interrupt_disable();

        /* get next suspend thread */
        thread = rt_list_entry(mp->suspend_thread.next, struct rt_thread, tlist);
        /* set error code to RT_ERROR */
        thread->error = -RT_ERROR;

        /*
         * resume thread
         * In rt_thread_resume function, it will remove current thread from
         * suspend list
         */
        rt_thread_resume(thread);

        /* decrease suspended thread count */
        mp->suspend_thread_count --;

        /* enable interrupt */
        rt_hw_interrupt_enable(temp);
    }

    /* detach object */
    rt_object_detach(&(mp->parent));

    return RT_EOK;
}
RTM_EXPORT(rt_mp_detach);

#ifdef RT_USING_HEAP
/**
 * This function will create a mempool object and allocate the memory pool from
 * heap.
 *
 * @param name the name of memory pool
 * @param block_count the count of blocks in memory pool
 * @param block_size the size for each block
 *
 * @return the created mempool object
 */
rt_mp_t rt_mp_create(const char *name,
                     rt_size_t   block_count,
                     rt_size_t   block_size)
{
    rt_uint8_t *block_ptr;
    struct rt_mempool *mp;
    register rt_size_t offset;

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* allocate object */
    mp = (struct rt_mempool *)rt_object_allocate(RT_Object_Class_MemPool, name);
    /* allocate object failed */
    if (mp == RT_NULL)
        return RT_NULL;

    /* initialize memory pool */
    block_size     = RT_ALIGN(block_size, RT_ALIGN_SIZE);
    mp->block_size = block_size;
    mp->size       = (block_size + sizeof(rt_uint8_t *)) * block_count;

    /* allocate memory */
    mp->start_address = rt_malloc((block_size + sizeof(rt_uint8_t *)) *
                                  block_count);
    if (mp->start_address == RT_NULL)
    {
        /* no memory, delete memory pool object */
        rt_object_delete(&(mp->parent));

        return RT_NULL;
    }

    mp->block_total_count = block_count;
    mp->block_free_count  = mp->block_total_count;

    /* initialize suspended thread list */
    rt_list_init(&(mp->suspend_thread));
    mp->suspend_thread_count = 0;

    /* initialize free block list */
    block_ptr = (rt_uint8_t *)mp->start_address;
    for (offset = 0; offset < mp->block_total_count; offset ++)
    {
        *(rt_uint8_t **)(block_ptr + offset * (block_size + sizeof(rt_uint8_t *)))
            = block_ptr + (offset + 1) * (block_size + sizeof(rt_uint8_t *));
    }

    *(rt_uint8_t **)(block_ptr + (offset - 1) * (block_size + sizeof(rt_uint8_t *)))
        = RT_NULL;

    mp->block_list = block_ptr;

    return mp;
}
RTM_EXPORT(rt_mp_create);

/**
 * This function will delete a memory pool and release the object memory.
 *
 * @param mp the memory pool object
 *
 * @return RT_EOK
 */
rt_err_t rt_mp_delete(rt_mp_t mp)
{
    struct rt_thread *thread;
    register rt_ubase_t temp;

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* parameter check */
    RT_ASSERT(mp != RT_NULL);

    /* wake up all suspended threads */
    while (!rt_list_isempty(&(mp->suspend_thread)))
    {
        /* disable interrupt */
        temp = rt_hw_interrupt_disable();

        /* get next suspend thread */
        thread = rt_list_entry(mp->suspend_thread.next, struct rt_thread, tlist);
        /* set error code to RT_ERROR */
        thread->error = -RT_ERROR;

        /*
         * resume thread
         * In rt_thread_resume function, it will remove current thread from
         * suspend list
         */
        rt_thread_resume(thread);

        /* decrease suspended thread count */
        mp->suspend_thread_count --;

        /* enable interrupt */
        rt_hw_interrupt_enable(temp);
    }

    /* release allocated room */
    rt_free(mp->start_address);

    /* detach object */
    rt_object_delete(&(mp->parent));

    return RT_EOK;
}
RTM_EXPORT(rt_mp_delete);
#endif

/**
 * This function will allocate a block from memory pool
 *
 * @param mp the memory pool object
 * @param time the waiting time
 *
 * @return the allocated memory block or RT_NULL on allocated failed
 */
void *rt_mp_alloc(rt_mp_t mp, rt_int32_t time)
{
    rt_uint8_t *block_ptr;
    register rt_base_t level;
    struct rt_thread *thread;
    rt_uint32_t before_sleep = 0;

    /* get current thread */
    thread = rt_thread_self();

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    while (mp->block_free_count == 0)
    {
        /* memory block is unavailable. */
        if (time == 0)
        {
            /* enable interrupt */
            rt_hw_interrupt_enable(level);

            rt_set_errno(-RT_ETIMEOUT);

            return RT_NULL;
        }

        RT_DEBUG_NOT_IN_INTERRUPT;

        thread->error = RT_EOK;

        /* need suspend thread */
        rt_thread_suspend(thread);
        rt_list_insert_after(&(mp->suspend_thread), &(thread->tlist));
        mp->suspend_thread_count++;

        if (time > 0)
        {
            /* get the start tick of timer */
            before_sleep = rt_tick_get();

            /* init thread timer and start it */
            rt_timer_control(&(thread->thread_timer),
                             RT_TIMER_CTRL_SET_TIME,
                             &time);
            rt_timer_start(&(thread->thread_timer));
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        /* do a schedule */
        rt_schedule();

        if (thread->error != RT_EOK)
            return RT_NULL;

        if (time > 0)
        {
            time -= rt_tick_get() - before_sleep;
            if (time < 0)
                time = 0;
        }
        /* disable interrupt */
        level = rt_hw_interrupt_disable();
    }

    /* memory block is available. decrease the free block counter */
    mp->block_free_count--;

    /* get block from block list */
    block_ptr = mp->block_list;
    RT_ASSERT(block_ptr != RT_NULL);

    /* Setup the next free node. */
    mp->block_list = *(rt_uint8_t **)block_ptr;

    /* point to memory pool */
    *(rt_uint8_t **)block_ptr = (rt_uint8_t *)mp;

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    RT_OBJECT_HOOK_CALL(rt_mp_alloc_hook,
                        (mp, (rt_uint8_t *)(block_ptr + sizeof(rt_uint8_t *))));

    return (rt_uint8_t *)(block_ptr + sizeof(rt_uint8_t *));
}
RTM_EXPORT(rt_mp_alloc);

/**
 * This function will release a memory block
 *
 * @param block the address of memory block to be released
 */
void rt_mp_free(void *block)
{
    rt_uint8_t **block_ptr;
    struct rt_mempool *mp;
    struct rt_thread *thread;
    register rt_base_t level;

    /* get the control block of pool which the block belongs to */
    block_ptr = (rt_uint8_t **)((rt_uint8_t *)block - sizeof(rt_uint8_t *));
    mp        = (struct rt_mempool *)*block_ptr;

    RT_OBJECT_HOOK_CALL(rt_mp_free_hook, (mp, block));

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* increase the free block count */
    mp->block_free_count ++;

    /* link the block into the block list */
    *block_ptr = mp->block_list;
    mp->block_list = (rt_uint8_t *)block_ptr;

    if (mp->suspend_thread_count > 0)
    {
        /* get the suspended thread */
        thread = rt_list_entry(mp->suspend_thread.next,
                               struct rt_thread,
                               tlist);

        /* set error */
        thread->error = RT_EOK;

        /* resume thread */
        rt_thread_resume(thread);

        /* decrease suspended thread count */
        mp->suspend_thread_count --;

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        /* do a schedule */
        rt_schedule();

        return;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);
}
RTM_EXPORT(rt_mp_free);

/**@}*/

#endif

