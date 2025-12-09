/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-04     RT-Thread    Unified clock_time subsystem
 */

#ifndef __CLOCK_TIME_H__
#define __CLOCK_TIME_H__

#include <rtthread.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RT_CLOCK_TIME_RESMUL (1000000ULL)

/* Capabilities flags */
#define RT_CLOCK_TIME_CAP_CLOCKSOURCE   (1 << 0)  /* Provides free-running counter */
#define RT_CLOCK_TIME_CAP_CLOCKEVENT    (1 << 1)  /* Supports oneshot timeout events */

/**
 * @brief Clock time device operations
 * 
 * This structure defines the operations that a clock time device must support.
 * At minimum, get_freq and get_counter must be implemented for clocksource capability.
 * For clockevent capability, set_timeout must also be implemented.
 */
struct rt_clock_time_ops
{
    rt_uint64_t (*get_freq)(void);                  /* Get counting frequency in Hz */
    rt_uint64_t (*get_counter)(void);               /* Get current free-running counter value */
    rt_err_t    (*set_timeout)(rt_uint64_t delta);  /* Set relative timeout in counter units, 0 to cancel */
};

/**
 * @brief Clock time device structure
 * 
 * This represents a unified time device that can provide both clocksource
 * (continuous time counter) and clockevent (programmable timeout) capabilities.
 */
struct rt_clock_time_device
{
    struct rt_device parent;                        /* Inherit from rt_device */
    const struct rt_clock_time_ops *ops;           /* Device operations */
    rt_uint64_t res_scale;                         /* Resolution scale factor (ns * scale / freq -> cnt) */
    rt_uint8_t  caps;                              /* Capability flags */
};
typedef struct rt_clock_time_device *rt_clock_time_t;

/**
 * @brief Register a clock time device
 * 
 * @param dev Clock time device to register
 * @param name Device name
 * @param caps Capability flags (RT_CLOCK_TIME_CAP_CLOCKSOURCE | RT_CLOCK_TIME_CAP_CLOCKEVENT)
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_time_device_register(struct rt_clock_time_device *dev, 
                                       const char *name, 
                                       rt_uint8_t caps);

/**
 * @brief Set the system default clock time device
 * 
 * @param dev Clock time device to set as default
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_time_set_default(struct rt_clock_time_device *dev);

/**
 * @brief Get the system default clock time device
 * 
 * @return Pointer to default clock time device, or RT_NULL if none set
 */
struct rt_clock_time_device *rt_clock_time_get_default(void);

/* Clocksource APIs - Get time information */

/**
 * @brief Get clock resolution in nanoseconds
 * 
 * @return Resolution value multiplied by RT_CLOCK_TIME_RESMUL
 */
rt_uint64_t rt_clock_time_getres(void);

/**
 * @brief Get clock frequency in Hz
 * 
 * @return Frequency in Hz
 */
rt_uint64_t rt_clock_time_getfreq(void);

/**
 * @brief Get current counter value
 * 
 * @return Current counter value
 */
rt_uint64_t rt_clock_time_getcnt(void);

/**
 * @brief Get boottime (time since boot) in various formats
 */
rt_err_t rt_clock_time_boottime_ns(struct timespec *ts);
rt_err_t rt_clock_time_boottime_us(struct timeval *tv);
rt_err_t rt_clock_time_boottime_s(time_t *t);

/**
 * @brief Convert counter ticks to time units
 */
rt_uint64_t rt_clock_time_cnt_to_ns(rt_uint64_t cnt);
rt_uint64_t rt_clock_time_cnt_to_us(rt_uint64_t cnt);
rt_uint64_t rt_clock_time_cnt_to_ms(rt_uint64_t cnt);

/**
 * @brief Convert time units to counter ticks
 */
rt_uint64_t rt_clock_time_ns_to_cnt(rt_uint64_t ns);
rt_uint64_t rt_clock_time_us_to_cnt(rt_uint64_t us);
rt_uint64_t rt_clock_time_ms_to_cnt(rt_uint64_t ms);

/* High-resolution timer (hrtimer) APIs */

struct rt_clock_hrtimer
{
    rt_uint8_t           flag;                      /* Timer flags (compatible with rt_timer) */
    char                 name[RT_NAME_MAX];        /* Timer name */
    rt_list_t            node;                      /* List node */
    void                *parameter;                 /* User parameter */
    unsigned long        delay_cnt;                /* Delay in counter ticks */
    unsigned long        timeout_cnt;              /* Absolute timeout counter value */
    rt_err_t             error;                     /* Error code */
    struct rt_completion completion;                /* Completion for blocking waits */
    void (*timeout_func)(void *parameter);         /* Timeout callback */
};
typedef struct rt_clock_hrtimer *rt_clock_hrtimer_t;

/**
 * @brief Initialize a high-resolution timer
 * 
 * @param timer Timer structure to initialize
 * @param name Timer name
 * @param flag Timer flags (RT_TIMER_FLAG_ONE_SHOT or RT_TIMER_FLAG_PERIODIC)
 * @param timeout Timeout callback function
 * @param parameter Parameter passed to timeout callback
 */
void rt_clock_hrtimer_init(rt_clock_hrtimer_t timer,
                          const char *name,
                          rt_uint8_t flag,
                          void (*timeout)(void *parameter),
                          void *parameter);

/**
 * @brief Start a high-resolution timer
 * 
 * @param timer Timer to start
 * @param delay_cnt Delay in counter ticks
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_hrtimer_start(rt_clock_hrtimer_t timer, unsigned long delay_cnt);

/**
 * @brief Stop a high-resolution timer
 * 
 * @param timer Timer to stop
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_hrtimer_stop(rt_clock_hrtimer_t timer);

/**
 * @brief Control a high-resolution timer
 * 
 * @param timer Timer to control
 * @param cmd Control command
 * @param arg Command argument
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_hrtimer_control(rt_clock_hrtimer_t timer, int cmd, void *arg);

/**
 * @brief Detach a high-resolution timer
 * 
 * @param timer Timer to detach
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_hrtimer_detach(rt_clock_hrtimer_t timer);

/**
 * @brief High-precision delay functions
 */
rt_err_t rt_clock_hrtimer_sleep(rt_clock_hrtimer_t timer, unsigned long cnt);
rt_err_t rt_clock_hrtimer_ndelay(rt_clock_hrtimer_t timer, unsigned long ns);
rt_err_t rt_clock_hrtimer_udelay(rt_clock_hrtimer_t timer, unsigned long us);
rt_err_t rt_clock_hrtimer_mdelay(rt_clock_hrtimer_t timer, unsigned long ms);

/**
 * @brief Simple delay functions (use internal timer)
 */
rt_err_t rt_clock_ndelay(unsigned long ns);
rt_err_t rt_clock_udelay(unsigned long us);
rt_err_t rt_clock_mdelay(unsigned long ms);

/**
 * @brief Process hrtimer timeouts (called from device driver ISR)
 */
void rt_clock_hrtimer_process(void);

/* POSIX clock support */
#define CLOCK_REALTIME_ALARM    8
#define CLOCK_BOOTTIME_ALARM    9

/* CPU time and boottime APIs */
uint64_t clock_cpu_getres(void);
uint64_t clock_cpu_gettime(void);
uint64_t clock_cpu_microsecond(uint64_t cpu_tick);
uint64_t clock_cpu_millisecond(uint64_t cpu_tick);
rt_err_t rt_cputime_ndelay(rt_uint64_t ns);
rt_err_t rt_cputime_udelay(rt_uint64_t us);
rt_err_t rt_cputime_mdelay(rt_uint64_t ms);

rt_err_t rt_boottime_get_us(struct timeval *tv);
rt_err_t rt_boottime_get_s(time_t *t);
rt_err_t rt_boottime_get_ns(struct timespec *ts);

#ifdef __cplusplus
}
#endif

#endif /* __CLOCK_TIME_H__ */
