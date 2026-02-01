/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-01     RT-Thread    Clock time subsystem
 */
#ifndef __CLOCK_TIME_H__
#define __CLOCK_TIME_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>
#include <ipc/completion.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RT_CLOCK_TIME_RESMUL (1000000ULL)

#define RT_CLOCK_TIME_CAP_SOURCE (1U << 0)
#define RT_CLOCK_TIME_CAP_EVENT  (1U << 1)

struct rt_clock_time_device;

struct rt_clock_time_ops
{
    rt_uint64_t (*get_freq)(struct rt_clock_time_device *dev);
    rt_uint64_t (*get_counter)(struct rt_clock_time_device *dev);
    rt_err_t (*set_timeout)(struct rt_clock_time_device *dev, rt_uint64_t delta);
};

struct rt_clock_time_device
{
    struct rt_device parent;
    const struct rt_clock_time_ops *ops;
    rt_uint64_t res_scale;
    rt_uint8_t caps;
};

/* Clock time timer device (replacement for legacy hardware timer device) */
typedef enum
{
    CLOCK_TIMER_CTRL_FREQ_SET = RT_DEVICE_CTRL_BASE(Timer) + 0x01,
    CLOCK_TIMER_CTRL_STOP = RT_DEVICE_CTRL_BASE(Timer) + 0x02,
    CLOCK_TIMER_CTRL_INFO_GET = RT_DEVICE_CTRL_BASE(Timer) + 0x03,
    CLOCK_TIMER_CTRL_MODE_SET = RT_DEVICE_CTRL_BASE(Timer) + 0x04
} rt_clock_timer_ctrl_t;

typedef enum
{
    CLOCK_TIMER_MODE_ONESHOT = 0x01,
    CLOCK_TIMER_MODE_PERIOD
} rt_clock_timer_mode_t;

typedef struct rt_clock_timerval
{
    rt_int32_t sec;
    rt_int32_t usec;
} rt_clock_timerval_t;

#define CLOCK_TIMER_CNTMODE_UP 0x01
#define CLOCK_TIMER_CNTMODE_DW 0x02

struct rt_clock_timer_device;

struct rt_clock_timer_ops
{
    void (*init)(struct rt_clock_timer_device *timer, rt_uint32_t state);
    rt_err_t (*start)(struct rt_clock_timer_device *timer, rt_uint32_t cnt, rt_clock_timer_mode_t mode);
    void (*stop)(struct rt_clock_timer_device *timer);
    rt_uint32_t (*count_get)(struct rt_clock_timer_device *timer);
    rt_err_t (*control)(struct rt_clock_timer_device *timer, rt_uint32_t cmd, void *args);
};

struct rt_clock_timer_info
{
    rt_int32_t maxfreq;
    rt_int32_t minfreq;
    rt_uint32_t maxcnt;
    rt_uint8_t cntmode;
};

typedef struct rt_clock_timer_device
{
    struct rt_device parent;
    const struct rt_clock_timer_ops *ops;
    const struct rt_clock_timer_info *info;

    rt_int32_t freq;
    rt_int32_t overflow;
    float period_sec;
    rt_int32_t cycles;
    rt_int32_t reload;
    rt_clock_timer_mode_t mode;

} rt_clock_timer_t;

rt_err_t rt_clock_timer_register(rt_clock_timer_t *timer, const char *name, void *user_data);
void rt_clock_timer_isr(rt_clock_timer_t *timer);

#ifdef RT_USING_DM
extern void (*rt_clock_timer_us_delay)(rt_uint32_t us);
#endif

struct rt_clock_hrtimer
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
typedef struct rt_clock_hrtimer *rt_clock_hrtimer_t;

rt_err_t rt_clock_time_device_register(struct rt_clock_time_device *dev, const char *name, rt_uint8_t caps);

void rt_clock_time_set_default_source(struct rt_clock_time_device *dev);
void rt_clock_time_set_default_event(struct rt_clock_time_device *dev);
struct rt_clock_time_device *rt_clock_time_get_default_source(void);
struct rt_clock_time_device *rt_clock_time_get_default_event(void);

void rt_clock_time_source_init(void);

rt_uint64_t rt_clock_time_get_freq(void);
rt_uint64_t rt_clock_time_get_counter(void);
rt_uint64_t rt_clock_time_get_res_scaled(void);
rt_uint64_t rt_clock_time_get_event_freq(void);
rt_uint64_t rt_clock_time_get_event_res_scaled(void);

rt_uint64_t rt_clock_time_counter_to_ns(rt_uint64_t cnt);
rt_uint64_t rt_clock_time_ns_to_counter(rt_uint64_t ns);

rt_err_t rt_clock_time_set_timeout(rt_uint64_t delta);
void rt_clock_time_event_isr(void);

rt_err_t rt_clock_boottime_get_us(struct timeval *tv);
rt_err_t rt_clock_boottime_get_s(time_t *t);
rt_err_t rt_clock_boottime_get_ns(struct timespec *ts);

rt_uint64_t rt_clock_hrtimer_getres(void);
unsigned long rt_clock_hrtimer_getfrq(void);
rt_err_t rt_clock_hrtimer_settimeout(unsigned long cnt);
void     rt_clock_hrtimer_process(void);

void     rt_clock_hrtimer_init(rt_clock_hrtimer_t timer,
                                    const char        *name,
                                    rt_uint8_t         flag,
                                    void (*timeout)(void *parameter),
                                    void *parameter);
rt_err_t rt_clock_hrtimer_start(rt_clock_hrtimer_t timer, unsigned long cnt);
rt_err_t rt_clock_hrtimer_stop(rt_clock_hrtimer_t timer);
rt_err_t rt_clock_hrtimer_control(rt_clock_hrtimer_t timer, int cmd, void *arg);
rt_err_t rt_clock_hrtimer_detach(rt_clock_hrtimer_t timer);

rt_inline void rt_clock_hrtimer_keep_errno(rt_clock_hrtimer_t timer, rt_err_t err)
{
    RT_ASSERT(timer != RT_NULL);

    timer->error = err;
    rt_set_errno(-err);
}

void rt_clock_hrtimer_delay_init(struct rt_clock_hrtimer *timer);
void rt_clock_hrtimer_delay_detach(struct rt_clock_hrtimer *timer);
void rt_clock_hrtimer_process(void);

rt_err_t rt_clock_hrtimer_sleep(struct rt_clock_hrtimer *timer, unsigned long cnt);
rt_err_t rt_clock_hrtimer_ndelay(struct rt_clock_hrtimer *timer, unsigned long ns);
rt_err_t rt_clock_hrtimer_udelay(struct rt_clock_hrtimer *timer, unsigned long us);
rt_err_t rt_clock_hrtimer_mdelay(struct rt_clock_hrtimer *timer, unsigned long ms);

#ifdef __cplusplus
}
#endif

#endif /* __CLOCK_TIME_H__ */
