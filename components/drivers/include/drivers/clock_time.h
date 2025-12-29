/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-01     RT-Thread    Unified clock_time subsystem (replaces hwtimer/ktime/cputime)
 */

#ifndef __CLOCK_TIME_H__
#define __CLOCK_TIME_H__

#include <rtthread.h>
#include <sys/time.h>
#include <ipc/completion.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Resolution multiplier for time calculations */
#define RT_CLOCK_TIME_RESMUL (1000000ULL)

/* Clock time device capabilities */
#define RT_CLOCK_TIME_CAP_CLOCKSOURCE   (1 << 0)  /* Device provides time source */
#define RT_CLOCK_TIME_CAP_CLOCKEVENT    (1 << 1)  /* Device provides event generation */

/**
 * @brief Clock time device operations structure
 * 
 * This structure defines the hardware interface for clock/timer devices.
 * BSPs should implement these operations for their specific hardware.
 */
struct rt_clock_time_ops
{
    /**
     * Get the counting frequency in Hz
     * @return Frequency in Hz
     */
    rt_uint64_t (*get_freq)(void);
    
    /**
     * Get the current free-running counter value
     * @return Current counter value
     */
    rt_uint64_t (*get_counter)(void);
    
    /**
     * Set a timeout relative to current counter value
     * @param delta Timeout in counter ticks (0 to cancel)
     * @return RT_EOK on success, error code otherwise
     */
    rt_err_t (*set_timeout)(rt_uint64_t delta);
};

/**
 * @brief Clock time device structure
 * 
 * Unified device abstraction for time sources and event generators.
 * This replaces the separate hwtimer, ktime, and cputime devices.
 */
struct rt_clock_time_device
{
    struct rt_device parent;                    /* Standard device interface */
    const struct rt_clock_time_ops *ops;        /* Hardware operations */
    rt_uint64_t res_scale;                      /* Resolution scale factor */
    rt_uint8_t caps;                            /* Device capabilities (RT_CLOCK_TIME_CAP_*) */
};
typedef struct rt_clock_time_device *rt_clock_time_t;

/**
 * @brief High-resolution timer structure
 * 
 * Software timer built on top of clock_time device.
 * Compatible with rt_ktime_hrtimer interface.
 */
struct rt_clock_hrtimer
{
    rt_uint8_t flag;                            /* Timer flags (compatible with rt_timer) */
    char name[RT_NAME_MAX];                     /* Timer name */
    rt_list_t node;                             /* List node for timer management */
    void *parameter;                            /* User parameter */
    unsigned long delay_cnt;                    /* Delay count */
    unsigned long timeout_cnt;                  /* Absolute timeout count */
    rt_err_t error;                             /* Last error code */
    struct rt_completion completion;            /* For synchronous waiting */
    void (*timeout_func)(void *parameter);      /* Timeout callback */
};
typedef struct rt_clock_hrtimer *rt_clock_hrtimer_t;

/*
 * ============================================================================
 * Device Management APIs
 * ============================================================================
 */

/**
 * @brief Register a clock time device
 * 
 * @param dev Clock time device to register
 * @param name Device name (e.g., "cputimer", "hwtimer0")
 * @param caps Device capabilities (RT_CLOCK_TIME_CAP_*)
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_time_device_register(struct rt_clock_time_device *dev, 
                                        const char *name, 
                                        rt_uint8_t caps);

/**
 * @brief Get the default system clock time device
 * @return Pointer to default device, or RT_NULL if none
 */
rt_clock_time_t rt_clock_time_default(void);

/**
 * @brief Set the default system clock time device
 * @param dev Device to set as default
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_time_set_default(rt_clock_time_t dev);

/*
 * ============================================================================
 * Clock Source APIs (Boottime)
 * ============================================================================
 */

/**
 * @brief Get boottime with microsecond precision
 * @param tv Output timeval structure
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_boottime_get_us(struct timeval *tv);

/**
 * @brief Get boottime with second precision
 * @param t Output time_t value
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_boottime_get_s(time_t *t);

/**
 * @brief Get boottime with nanosecond precision
 * @param ts Output timespec structure
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_boottime_get_ns(struct timespec *ts);

/*
 * ============================================================================
 * CPU Timer APIs (Clock Source)
 * ============================================================================
 */

/**
 * @brief Get CPU timer resolution (resolution * RT_CLOCK_TIME_RESMUL)
 * @return Resolution value
 */
rt_uint64_t rt_clock_cputimer_getres(void);

/**
 * @brief Get CPU timer frequency in Hz
 * @return Frequency in Hz
 */
unsigned long rt_clock_cputimer_getfrq(void);

/**
 * @brief Get current CPU timer counter value
 * @return Counter value
 */
unsigned long rt_clock_cputimer_getcnt(void);

/**
 * @brief Initialize CPU timer subsystem
 */
void rt_clock_cputimer_init(void);

/*
 * ============================================================================
 * High-Resolution Timer APIs
 * ============================================================================
 */

/**
 * @brief Get hrtimer resolution (resolution * RT_CLOCK_TIME_RESMUL)
 * @return Resolution value
 */
rt_uint64_t rt_clock_hrtimer_getres(void);

/**
 * @brief Get hrtimer frequency in Hz
 * @return Frequency in Hz
 */
unsigned long rt_clock_hrtimer_getfrq(void);

/**
 * @brief Set hrtimer interrupt timeout (BSP should implement)
 * @param cnt Timeout in counter ticks
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_hrtimer_settimeout(unsigned long cnt);

/**
 * @brief Process expired hrtimers (call from ISR)
 */
void rt_clock_hrtimer_process(void);

/**
 * @brief Initialize a high-resolution timer
 * 
 * @param timer Timer structure to initialize
 * @param name Timer name
 * @param flag Timer flags (RT_TIMER_FLAG_*)
 * @param timeout Timeout callback function
 * @param parameter User parameter for callback
 */
void rt_clock_hrtimer_init(rt_clock_hrtimer_t timer,
                            const char *name,
                            rt_uint8_t flag,
                            void (*timeout)(void *parameter),
                            void *parameter);

/**
 * @brief Start a high-resolution timer
 * @param timer Timer to start
 * @param cnt Timeout in counter ticks
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_hrtimer_start(rt_clock_hrtimer_t timer, unsigned long cnt);

/**
 * @brief Stop a high-resolution timer
 * @param timer Timer to stop
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_hrtimer_stop(rt_clock_hrtimer_t timer);

/**
 * @brief Control a high-resolution timer
 * @param timer Timer to control
 * @param cmd Control command
 * @param arg Command argument
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_hrtimer_control(rt_clock_hrtimer_t timer, int cmd, void *arg);

/**
 * @brief Detach a high-resolution timer
 * @param timer Timer to detach
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_hrtimer_detach(rt_clock_hrtimer_t timer);

/**
 * @brief Keep errno in timer structure
 * @param timer Timer structure
 * @param err Error code to keep
 */
rt_inline void rt_clock_hrtimer_keep_errno(rt_clock_hrtimer_t timer, rt_err_t err)
{
    RT_ASSERT(timer != RT_NULL);
    timer->error = err;
    rt_set_errno(-err);
}

/**
 * @brief Initialize timer for delay operations
 * @param timer Timer structure
 */
void rt_clock_hrtimer_delay_init(struct rt_clock_hrtimer *timer);

/**
 * @brief Detach timer after delay operations
 * @param timer Timer structure
 */
void rt_clock_hrtimer_delay_detach(struct rt_clock_hrtimer *timer);

/**
 * @brief Sleep for specified counter ticks
 * @param timer Timer structure to use
 * @param cnt Number of counter ticks to sleep
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_hrtimer_sleep(struct rt_clock_hrtimer *timer, unsigned long cnt);

/**
 * @brief Delay for specified nanoseconds
 * @param timer Timer structure to use
 * @param ns Nanoseconds to delay
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_hrtimer_ndelay(struct rt_clock_hrtimer *timer, unsigned long ns);

/**
 * @brief Delay for specified microseconds
 * @param timer Timer structure to use
 * @param us Microseconds to delay
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_hrtimer_udelay(struct rt_clock_hrtimer *timer, unsigned long us);

/**
 * @brief Delay for specified milliseconds
 * @param timer Timer structure to use
 * @param ms Milliseconds to delay
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_clock_hrtimer_mdelay(struct rt_clock_hrtimer *timer, unsigned long ms);

/*
 * ============================================================================
 * Legacy Compatibility Macros (Will be removed in future versions)
 * ============================================================================
 */

/* Compatibility with rt_ktime_* APIs */
#define RT_KTIME_RESMUL                     RT_CLOCK_TIME_RESMUL
#define rt_ktime_hrtimer                    rt_clock_hrtimer
#define rt_ktime_hrtimer_t                  rt_clock_hrtimer_t
#define rt_ktime_boottime_get_us            rt_clock_boottime_get_us
#define rt_ktime_boottime_get_s             rt_clock_boottime_get_s
#define rt_ktime_boottime_get_ns            rt_clock_boottime_get_ns
#define rt_ktime_cputimer_getres            rt_clock_cputimer_getres
#define rt_ktime_cputimer_getfrq            rt_clock_cputimer_getfrq
#define rt_ktime_cputimer_getcnt            rt_clock_cputimer_getcnt
#define rt_ktime_cputimer_init              rt_clock_cputimer_init
#define rt_ktime_hrtimer_getres             rt_clock_hrtimer_getres
#define rt_ktime_hrtimer_getfrq             rt_clock_hrtimer_getfrq
#define rt_ktime_hrtimer_settimeout         rt_clock_hrtimer_settimeout
#define rt_ktime_hrtimer_process            rt_clock_hrtimer_process
#define rt_ktime_hrtimer_init               rt_clock_hrtimer_init
#define rt_ktime_hrtimer_start              rt_clock_hrtimer_start
#define rt_ktime_hrtimer_stop               rt_clock_hrtimer_stop
#define rt_ktime_hrtimer_control            rt_clock_hrtimer_control
#define rt_ktime_hrtimer_detach             rt_clock_hrtimer_detach
#define rt_ktime_hrtimer_keep_errno         rt_clock_hrtimer_keep_errno
#define rt_ktime_hrtimer_delay_init         rt_clock_hrtimer_delay_init
#define rt_ktime_hrtimer_delay_detach       rt_clock_hrtimer_delay_detach
#define rt_ktime_hrtimer_sleep              rt_clock_hrtimer_sleep
#define rt_ktime_hrtimer_ndelay             rt_clock_hrtimer_ndelay
#define rt_ktime_hrtimer_udelay             rt_clock_hrtimer_udelay
#define rt_ktime_hrtimer_mdelay             rt_clock_hrtimer_mdelay

#ifdef __cplusplus
}
#endif

#endif /* __CLOCK_TIME_H__ */
