/*
 * COPYRIGHT (C) 2011-2021, Real-Thread Information Technology Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-04-16     Grissiom     first version
 */

struct rt_watermark_queue
{
    /* Current water level. */
    unsigned int level;
    unsigned int high_mark;
    unsigned int low_mark;
    rt_list_t suspended_threads;
};

/** Init the struct rt_watermark_queue.
 */
void rt_wm_que_init(struct rt_watermark_queue *wg,
                    unsigned int low, unsigned int high);
void rt_wm_que_set_mark(struct rt_watermark_queue *wg,
                        unsigned int low, unsigned int high);
void rt_wm_que_dump(struct rt_watermark_queue *wg);

/* Water marks are often used in performance critical places. Benchmark shows
 * inlining functions will have 10% performance gain in some situation(for
 * example, VBus). So keep the inc/dec compact and inline. */

/** Increase the water level.
 *
 * It should be called in the thread that want to raise the water level. If the
 * current level is above the high mark, the thread will be suspended up to
 * @timeout ticks.
 *
 * @return RT_EOK if water level increased successfully. -RT_EFULL on @timeout
 * is zero and the level is above water mark. -RT_ETIMEOUT if timeout occurred.
 */
rt_inline rt_err_t rt_wm_que_inc(struct rt_watermark_queue *wg,
                                 int timeout)
{
    rt_base_t ilvl;

    /* Assert as early as possible. */
    if (timeout != 0)
    {
        RT_DEBUG_IN_THREAD_CONTEXT;
    }

    ilvl = rt_hw_interrupt_disable();

    while (wg->level > wg->high_mark)
    {
        rt_thread_t thread;

        if (timeout == 0)
        {
            rt_hw_interrupt_enable(ilvl);
            return -RT_EFULL;
        }

        thread = rt_thread_self();
        thread->error = RT_EOK;
        rt_thread_suspend(thread);
        rt_list_insert_after(&wg->suspended_threads, &thread->tlist);
        if (timeout > 0)
        {
            rt_timer_control(&(thread->thread_timer),
                             RT_TIMER_CTRL_SET_TIME,
                             &timeout);
            rt_timer_start(&(thread->thread_timer));
        }
        rt_hw_interrupt_enable(ilvl);
        rt_schedule();
        if (thread->error != RT_EOK)
            return thread->error;

        ilvl = rt_hw_interrupt_disable();
    }

    wg->level++;

    if (wg->level == 0)
    {
        wg->level = ~0;
    }

    rt_hw_interrupt_enable(ilvl);

    return RT_EOK;
}

/** Decrease the water level.
 *
 * It should be called by the consumer that drain the water out. If the water
 * level reached low mark, all the thread suspended in this queue will be waken
 * up. It's safe to call this function in interrupt context.
 */
rt_inline void rt_wm_que_dec(struct rt_watermark_queue *wg)
{
    int need_sched = 0;
    rt_base_t ilvl;

    if (wg->level == 0)
        return;

    ilvl = rt_hw_interrupt_disable();
    wg->level--;
    if (wg->level == wg->low_mark)
    {
        /* There should be spaces between the low mark and high mark, so it's
         * safe to resume all the threads. */
        while (!rt_list_isempty(&wg->suspended_threads))
        {
            rt_thread_t thread;

            thread = rt_list_entry(wg->suspended_threads.next,
                                   struct rt_thread,
                                   tlist);
            rt_thread_resume(thread);
            need_sched = 1;
        }
    }
    rt_hw_interrupt_enable(ilvl);

    if (need_sched)
        rt_schedule();
}
