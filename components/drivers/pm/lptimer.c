/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-11     zhangsz      the first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <drivers/lptimer.h>

static rt_list_t rt_soft_lptimer_list = RT_LIST_OBJECT_INIT(rt_soft_lptimer_list);

/* lptimer init */
void rt_lptimer_init(rt_lptimer_t  timer,
                   const char *name,
                   void (*timeout)(void *parameter),
                   void       *parameter,
                   rt_tick_t   time,
                   rt_uint8_t  flag)
{
    rt_timer_init(&timer->timer, name, timeout, parameter, time, flag);
    rt_list_init(&timer->list);
}

/* lptimer detach */
rt_err_t rt_lptimer_detach(rt_lptimer_t timer)
{
    rt_base_t level;
    rt_err_t ret = RT_EOK;
    RT_ASSERT(timer != RT_NULL);

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    ret = rt_timer_detach(&timer->timer);
    rt_list_remove(&timer->list);

    /* enable interrupt */
    rt_hw_interrupt_enable(level);
    return ret;
}

/* lptimer start */
rt_err_t rt_lptimer_start(rt_lptimer_t timer)
{
    rt_base_t level;

    RT_ASSERT(timer != RT_NULL);

    /* disable interrupt */
    level = rt_hw_interrupt_disable();
    rt_list_remove(&timer->list); /* remove first */
    if (rt_timer_start(&timer->timer) == RT_EOK)
    {
        /* insert to lptimer list */
        rt_list_insert_after(&rt_soft_lptimer_list, &(timer->list));
    }
    else
    {
        /* enable interrupt */
        rt_hw_interrupt_enable(level);
        return -RT_ERROR;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

/* lptimer stop */
rt_err_t rt_lptimer_stop(rt_lptimer_t timer)
{
    rt_base_t level;
    RT_ASSERT(timer != RT_NULL);

    /* disable interrupt */
    level = rt_hw_interrupt_disable();
    rt_list_remove(&timer->list);
    if (rt_timer_stop(&timer->timer) == RT_EOK)
    {
        /* enable interrupt */
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    else
    {
        /* enable interrupt */
        rt_hw_interrupt_enable(level);
        return -RT_ERROR;
    }
}

rt_err_t rt_lptimer_control(rt_lptimer_t timer, int cmd, void *arg)
{
    RT_ASSERT(timer != RT_NULL);

    return rt_timer_control(&timer->timer, cmd, arg);
}

/* get the next soft lptimer timeout */
rt_tick_t rt_lptimer_next_timeout_tick(void)
{
    struct rt_lptimer *timer;
    rt_base_t level;
    rt_tick_t timeout_tick = RT_TICK_MAX;
    struct rt_list_node *node = RT_NULL;
    rt_tick_t temp_tick = 0;
    rt_tick_t min_tick = RT_TICK_MAX;
    rt_tick_t cur_tick = rt_tick_get();

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    if (!rt_list_isempty(&rt_soft_lptimer_list))
    {
        /* find the first active timer's timeout */
        rt_list_for_each(node, &rt_soft_lptimer_list)
        {
            timer = rt_list_entry(node, struct rt_lptimer, list);
            if (timer->timer.parent.flag & RT_TIMER_FLAG_ACTIVATED)
            {
                temp_tick = timer->timer.timeout_tick - cur_tick;

                /* find the least timeout_tick */
                if (min_tick > temp_tick)
                {
                    min_tick = temp_tick;
                    timeout_tick = timer->timer.timeout_tick;
                }
            }
        }
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return timeout_tick;
}

void lptimer_dump(void)
{
    struct rt_lptimer *timer;
    rt_base_t level;
    struct rt_list_node *node = RT_NULL;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    rt_kprintf("| lptimer       | periodic   | timeout    |  flag       |\n");
    rt_kprintf("+---------------+------------+------------+-------------+\n");

    if (!rt_list_isempty(&rt_soft_lptimer_list))
    {
        rt_list_for_each(node, &rt_soft_lptimer_list)
        {
            timer = rt_list_entry(node, struct rt_lptimer, list);
            rt_kprintf("| %-13s | 0x%08x | 0x%08x |",
                timer->timer.parent.name, timer->timer.init_tick,
                timer->timer.timeout_tick);
            if (timer->timer.parent.flag & RT_TIMER_FLAG_ACTIVATED)
                rt_kprintf(" activated   |\n");
            else
                rt_kprintf(" deactivated |\n");
        }
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);
    rt_kprintf("+---------------+------------+------------+-------------+\n");
}

MSH_CMD_EXPORT(lptimer_dump, soft lptimer dump);
