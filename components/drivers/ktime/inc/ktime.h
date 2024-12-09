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

#define RT_KTIME_RESMUL (1000000ULL)

struct rt_ktime_hrtimer
{
    rt_uint8_t           flag;                  /**< compatible to tick timer's flag */
    char                 name[RT_NAME_MAX];
    rt_list_t            node;
    void                *parameter;
    unsigned long        delay_cnt;
    unsigned long        timeout_cnt;
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
 * @brief Get cputimer resolution
 *
 * @return (resolution * RT_KTIME_RESMUL)
 */
rt_uint64_t rt_ktime_cputimer_getres(void);

/**
 * @brief Get cputimer frequency
 *
 * @return frequency
 */
unsigned long rt_ktime_cputimer_getfrq(void);

/**
 * @brief Get cputimer the value of the cnt counter
 *
 * @return cnt
 */
unsigned long rt_ktime_cputimer_getcnt(void);

/**
 * @brief Get cputimer the cnt value corresponding to 1 os tick
 *
 * @return step
 */
unsigned long rt_ktime_cputimer_getstep(void);

/**
 * @brief Init cputimer
 *
 */
void rt_ktime_cputimer_init(void);

/**
 * @brief Get hrtimer resolution
 *
 * @return (resolution * RT_KTIME_RESMUL)
 */
rt_uint64_t rt_ktime_hrtimer_getres(void);

/**
 * @brief Get hrtimer frequency
 *
 * @return frequency
 */
unsigned long rt_ktime_hrtimer_getfrq(void);

/**
 * @brief Get hrtimer the value of the cnt counter
 *
 * @return cnt
 */
unsigned long rt_ktime_hrtimer_getcnt(void);

/**
 * @brief set hrtimer interrupt timeout count (cnt), you should re-implemented it in hrtimer device driver
 *
 * @param cnt: hrtimer requires a timing cnt value
 * @return rt_err_t
 */
rt_err_t rt_ktime_hrtimer_settimeout(unsigned long cnt);

/**
 * @brief called in hrtimer device driver isr routinue, it will process the timeouts
 */
void     rt_ktime_hrtimer_process(void);

void     rt_ktime_hrtimer_init(rt_ktime_hrtimer_t timer,
                               const char        *name,
                               rt_uint8_t         flag,
                               void (*timeout)(void *parameter),
                               void *parameter);
rt_err_t rt_ktime_hrtimer_start(rt_ktime_hrtimer_t timer, unsigned long cnt);
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
rt_err_t rt_ktime_hrtimer_sleep(struct rt_ktime_hrtimer *timer, unsigned long cnt);

/**
 * @brief sleep by ns
 *
 * @param ns: ns
 * @return rt_err_t
 */
rt_err_t rt_ktime_hrtimer_ndelay(struct rt_ktime_hrtimer *timer, unsigned long ns);

/**
 * @brief sleep by us
 *
 * @param us: us
 * @return rt_err_t
 */
rt_err_t rt_ktime_hrtimer_udelay(struct rt_ktime_hrtimer *timer, unsigned long us);

/**
 * @brief sleep by ms
 *
 * @param ms: ms
 * @return rt_err_t
 */
rt_err_t rt_ktime_hrtimer_mdelay(struct rt_ktime_hrtimer *timer, unsigned long ms);

#endif
