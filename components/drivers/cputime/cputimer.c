#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_CPUTIME
#include <rtdevice.h>
#endif

static rt_list_t _cputime_timer_list;

static void _cputime_timeout(void *parameter)
{
    struct rt_cputime_timer *timer;
    timer = (struct rt_cputime_timer *)parameter;
    timer->timeout_func(timer->parameter);
    rt_list_remove(&timer->row);

    if (&_cputime_timer_list != _cputime_timer_list.prev)
    {
        struct rt_cputime_timer *t;
        t = rt_list_entry(_cputime_timer_list.next, struct rt_cputime_timer, row);
        clock_cpu_settimeout(t->timeout_tick, _cputime_timeout, t);
    }
    else
        clock_cpu_settimeout(RT_NULL, RT_NULL, RT_NULL);
    if ((timer->parent.flag & RT_TIMER_FLAG_PERIODIC) &&
        (timer->parent.flag & RT_TIMER_FLAG_ACTIVATED))
    {
        /* start it */
        timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
        rt_cputime_timer_start(timer);
    }
}

void rt_cputime_timer_init(void)
{
    rt_list_init(&_cputime_timer_list);
}

void rt_cputime_timer_create(rt_cputime_timer_t timer,
                             const char *name,
                             void (*timeout)(void *parameter),
                             void *parameter,
                             rt_uint64_t time,
                             rt_uint8_t flag)
{
    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(timeout != RT_NULL);
    RT_ASSERT(clock_cpu_issettimeout() != RT_NULL);

    /* timer object initialization */
    rt_object_init(&(timer->parent), RT_Object_Class_Timer, name);

    /* set flag */
    timer->parent.flag = flag;

    /* set deactivated */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    timer->timeout_func = timeout;
    timer->parameter = parameter;

    timer->timeout_tick = 0;
    timer->init_tick = time;
    rt_list_init(&(timer->row));
}

void set_next_timeout()
{
    struct rt_cputime_timer *t;
    if (&_cputime_timer_list != _cputime_timer_list.prev)
    {
        t = rt_list_entry((&_cputime_timer_list)->next, struct rt_cputime_timer, row);
        clock_cpu_settimeout(t->timeout_tick, _cputime_timeout, t);
    }
    else
        clock_cpu_settimeout(RT_NULL, RT_NULL, RT_NULL);
}

rt_err_t rt_cputime_timer_delete(rt_cputime_timer_t timer)
{
    rt_base_t level;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(rt_object_get_type(&timer->parent) == RT_Object_Class_Timer);
    RT_ASSERT(rt_object_is_systemobject(&timer->parent) == RT_FALSE);
    RT_ASSERT(clock_cpu_issettimeout() != RT_NULL);
    
    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    rt_list_remove(&timer->row);
    /* stop timer */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    rt_object_delete(&(timer->parent));
    set_next_timeout();

    return RT_EOK;
}

rt_err_t rt_cputime_timer_start(rt_cputime_timer_t timer)
{
    rt_list_t *timer_list;
    rt_base_t level;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(rt_object_get_type(&timer->parent) == RT_Object_Class_Timer);
    RT_ASSERT(clock_cpu_issettimeout() != RT_NULL);

    /* stop timer firstly */
    level = rt_hw_interrupt_disable();
    /* remove timer from list */

    rt_list_remove(&timer->row);
    /* change status of timer */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    timer->timeout_tick = clock_cpu_gettime() + timer->init_tick;

    timer_list = &_cputime_timer_list;

    for (; timer_list != _cputime_timer_list.prev;
         timer_list = timer_list->next)
    {
        struct rt_cputime_timer *t;
        rt_list_t *p = timer_list->next;

        t = rt_list_entry(p, struct rt_cputime_timer, row);

        if ((t->timeout_tick - timer->timeout_tick) == 0)
        {
            continue;
        }
        else if ((t->timeout_tick - timer->timeout_tick) < 0x7fffffffffffffff)
        {
            break;
        }
    }

    rt_list_insert_after(timer_list, &(timer->row));

    timer->parent.flag |= RT_TIMER_FLAG_ACTIVATED;

    set_next_timeout();
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t rt_cputime_timer_stop(rt_cputime_timer_t timer)
{
    rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* timer check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(rt_object_get_type(&timer->parent) == RT_Object_Class_Timer);
    RT_ASSERT(clock_cpu_issettimeout() != RT_NULL);
    
    if (!(timer->parent.flag & RT_TIMER_FLAG_ACTIVATED))
    {
        rt_hw_interrupt_enable(level);
        return -RT_ERROR;
    }

    rt_list_remove(&timer->row);
    /* change status */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    set_next_timeout();
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t rt_cputime_timer_control(rt_cputime_timer_t timer, int cmd, void *arg)
{
    rt_base_t level;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(rt_object_get_type(&timer->parent) == RT_Object_Class_Timer);
    RT_ASSERT(clock_cpu_issettimeout() != RT_NULL);
    
    level = rt_hw_interrupt_disable();
    switch (cmd)
    {
    case RT_TIMER_CTRL_GET_TIME:
        *(rt_uint64_t *)arg = timer->init_tick;
        break;

    case RT_TIMER_CTRL_SET_TIME:
        RT_ASSERT((*(rt_uint64_t *)arg) < 0x7fffffffffffffff);
        timer->init_tick = *(rt_uint64_t *)arg;
        break;

    case RT_TIMER_CTRL_SET_ONESHOT:
        timer->parent.flag &= ~RT_TIMER_FLAG_PERIODIC;
        break;

    case RT_TIMER_CTRL_SET_PERIODIC:
        timer->parent.flag |= RT_TIMER_FLAG_PERIODIC;
        break;

    case RT_TIMER_CTRL_GET_STATE:
        if (timer->parent.flag & RT_TIMER_FLAG_ACTIVATED)
        {
            /*timer is start and run*/
            *(rt_uint32_t *)arg = RT_TIMER_FLAG_ACTIVATED;
        }
        else
        {
            /*timer is stop*/
            *(rt_uint32_t *)arg = RT_TIMER_FLAG_DEACTIVATED;
        }
        break;

    case RT_TIMER_CTRL_GET_REMAIN_TIME:
        *(rt_uint64_t *)arg = timer->timeout_tick;
        break;
    case RT_TIMER_CTRL_GET_FUNC:
        arg = (void *)timer->timeout_func;
        break;

    case RT_TIMER_CTRL_SET_FUNC:
        timer->timeout_func = (void (*)(void *))arg;
        break;

    case RT_TIMER_CTRL_GET_PARM:
        *(void **)arg = timer->parameter;
        break;

    case RT_TIMER_CTRL_SET_PARM:
        timer->parameter = arg;
        break;

    default:
        break;
    }
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t rt_cputime_timer_detach(rt_cputime_timer_t timer)
{
    rt_base_t level;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(rt_object_get_type(&timer->parent) == RT_Object_Class_Timer);
    RT_ASSERT(rt_object_is_systemobject(&timer->parent));
    RT_ASSERT(clock_cpu_issettimeout() != RT_NULL);
    
    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    rt_list_remove(&timer->row);
    /* stop timer */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    set_next_timeout();
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    rt_object_detach(&(timer->parent));

    return RT_EOK;
}
