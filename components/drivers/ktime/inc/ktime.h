/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-10     xqyjlj       The first version.
 * 2024-04-26     Shell        Improve ipc performance
 */

#ifndef __KTIME_H__
#define __KTIME_H__

#include <stdint.h>
#include <sys/time.h>
#include <ipc/completion.h>

#include "rtthread.h"

struct rt_ktime_hrtimer
{
    rt_uint8_t           flag;                  /**< compatible to tick timer's flag */
    char                 name[RT_NAME_MAX];
    rt_list_t            node;
    void                *parameter;
    rt_tick_t            delay_cnt;
    rt_tick_t            timeout_cnt;
    rt_err_t             error;
    struct rt_completion completion;
    void (*timeout_func)(void *parameter);
};
typedef struct rt_ktime_hrtimer *rt_ktime_hrtimer_t;

/**
 * @brief Get boottime with us precision
 *
 * @param tv: timeval
 * @return rt_err_t
 */
rt_err_t rt_ktime_boottime_get_us(struct timeval *tv);

/**
 * @brief Get boottime with s precision
 *
 * @param t: time_t
 * @return rt_err_t
 */
rt_err_t rt_ktime_boottime_get_s(time_t *t);

/**
 * @brief Get boottime with ns precision
 *
 * @param ts: timespec
 * @return rt_err_t
 */
rt_err_t rt_ktime_boottime_get_ns(struct timespec *ts);

/**
 * @brief Get cputimer frequency
 *
 * @return frequency
 */
rt_uint32_t rt_ktime_cputimer_getfrq(void);

/**
 * @brief Get cputimer the value of the cnt counter
 *
 * @return cnt
 */
rt_tick_t rt_ktime_cputimer_getcnt(void);

/**
 * @brief Init cputimer
 *
 */
void rt_ktime_cputimer_init(void);

/**
 * @brief Get hrtimer frequency, you should re-implemented it in hrtimer device driver
 *
 * @return frequency
 */
rt_uint64_t rt_ktime_hrtimer_getfrq(void);

/**
 * @brief set hrtimer interrupt timeout count (cnt), you should re-implemented it in hrtimer device driver
 *
 * @param cnt: hrtimer requires a timing cnt value
 * @return rt_err_t
 */
rt_err_t rt_ktime_hrtimer_settimeout(rt_uint64_t cnt);

/**
 * @brief called in hrtimer device driver isr routinue, it will process the timeouts
 */
void     rt_ktime_hrtimer_process(void);

void     rt_ktime_hrtimer_init(rt_ktime_hrtimer_t timer,
                               const char        *name,
                               rt_uint8_t         flag,
                               void (*timeout)(void *parameter),
                               void *parameter);
/**
 * @brief start the hrtimer
 *
 * @param cnt the cputimer cnt value
 * @return rt_err_t
 */
rt_err_t rt_ktime_hrtimer_start(rt_ktime_hrtimer_t timer, rt_tick_t cnt);
rt_err_t rt_ktime_hrtimer_stop(rt_ktime_hrtimer_t timer);
rt_err_t rt_ktime_hrtimer_control(rt_ktime_hrtimer_t timer, int cmd, void *arg);
rt_err_t rt_ktime_hrtimer_detach(rt_ktime_hrtimer_t timer);

rt_inline void rt_ktime_hrtimer_keep_errno(rt_ktime_hrtimer_t timer, rt_err_t err)
{
    RT_ASSERT(timer != RT_NULL);

    timer->error = err;
    rt_set_errno(-err);
}

void rt_ktime_hrtimer_delay_init(struct rt_ktime_hrtimer *timer);
void rt_ktime_hrtimer_delay_detach(struct rt_ktime_hrtimer *timer);
void rt_ktime_hrtimer_process(void);

/**
 * @brief sleep by the cputimer cnt value
 *
 * @param cnt: the cputimer cnt value
 * @return rt_err_t
 */
rt_err_t rt_ktime_hrtimer_sleep(struct rt_ktime_hrtimer *timer, rt_tick_t cnt);

/**
 * @brief sleep by ns
 *
 * @param ns: ns
 * @return rt_err_t
 */
rt_err_t rt_ktime_hrtimer_ndelay(struct rt_ktime_hrtimer *timer, rt_uint64_t ns);

/**
 * @brief sleep by us
 *
 * @param us: us
 * @return rt_err_t
 */
rt_err_t rt_ktime_hrtimer_udelay(struct rt_ktime_hrtimer *timer, rt_uint64_t us);

/**
 * @brief sleep by ms
 *
 * @param ms: ms
 * @return rt_err_t
 */
rt_err_t rt_ktime_hrtimer_mdelay(struct rt_ktime_hrtimer *timer, rt_uint64_t ms);

#endif
