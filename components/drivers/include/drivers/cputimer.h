#ifndef CPUTIMER_H__
#define CPUTIMER_H__

#include <rtthread.h>

struct rt_cputime_timer
{
    struct rt_object parent; /**< inherit from rt_object */
    rt_list_t row;
    void (*timeout_func)(void *parameter);
    void *parameter;
    rt_uint64_t init_tick;
    rt_uint64_t timeout_tick;
};
typedef struct rt_cputime_timer *rt_cputime_timer_t;

int rt_cputime_timer_init(void);
rt_err_t rt_cputime_timer_detach(rt_cputime_timer_t timer);

#ifdef RT_USING_HEAP
void rt_cputime_timer_create(rt_cputime_timer_t timer,
                             const char *name,
                             void (*timeout)(void *parameter),
                             void *parameter,
                             rt_uint64_t time,
                             rt_uint8_t flag);
rt_err_t rt_cputime_timer_delete(rt_cputime_timer_t timer);
#endif

rt_err_t rt_cputime_timer_start(rt_cputime_timer_t timer);
rt_err_t rt_cputime_timer_stop(rt_cputime_timer_t timer);
rt_err_t rt_cputime_timer_control(rt_cputime_timer_t timer, int cmd, void *arg);
rt_err_t rt_cputime_sleep(rt_uint64_t tick);
rt_err_t rt_cputime_ndelay(rt_uint64_t ns);
rt_err_t rt_cputime_udelay(rt_uint64_t us);
rt_err_t rt_cputime_mdelay(rt_uint64_t ms);

#endif
