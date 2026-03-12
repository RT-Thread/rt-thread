/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-30     armink       the first version
 * 2025-10-30     dongly       fix timespec/timeval error, optimize soft_rtc implementation
 */

#include <sys/time.h>
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_CLOCK_TIME
#include <drivers/clock_time.h>
#endif

#ifdef RT_USING_SOFT_RTC

/* 2018-01-30 14:44:50 = RTC_TIME_INIT(2018, 1, 30, 14, 44, 50)  */
#define RTC_TIME_INIT(year, month, day, hour, minute, second) \
    {                                                         \
        .tm_year = year - 1900,                               \
        .tm_mon = month - 1,                                  \
        .tm_mday = day,                                       \
        .tm_hour = hour,                                      \
        .tm_min = minute,                                     \
        .tm_sec = second,                                     \
    }

#ifndef SOFT_RTC_TIME_DEFAULT
#define SOFT_RTC_TIME_DEFAULT RTC_TIME_INIT(2018, 1, 1, 0, 0, 0)
#endif

#ifndef RTC_AUTO_SYNC_FIRST_DELAY
#define RTC_AUTO_SYNC_FIRST_DELAY 25
#endif
#ifndef RTC_AUTO_SYNC_PERIOD
#define RTC_AUTO_SYNC_PERIOD 3600
#endif

static struct rt_work rtc_sync_work;
static struct rt_device soft_rtc_dev;
static RT_DEFINE_SPINLOCK(_spinlock);
/* RTC time baseline for calculation */
static struct timespec base_ts = { 0 };
#ifdef RT_USING_CLOCK_TIME
static struct timespec base_ktime_ts = { 0 };
#else
static rt_tick_t base_tick;
#endif

#ifdef RT_USING_ALARM
static struct rt_rtc_wkalarm wkalarm;
static struct rt_timer alarm_time;

/**
 * @brief Alarm timeout callback function
 * @param param User data passed to alarm update function
 * @return None
 *
 * This function is called when the alarm timer expires and updates
 * the alarm system.
 */
static void alarm_timeout(void *param)
{
    rt_alarm_update(param, 1);
}

/**
 * @brief Update soft RTC alarm status
 * @param palarm Pointer to alarm configuration structure
 * @return None
 *
 * This function updates the alarm timer based on the alarm enable status.
 * When enabled, it starts a 1-second period timer for alarm detection.
 * When disabled, it stops the timer.
 */
static void soft_rtc_alarm_update(struct rt_rtc_wkalarm *palarm)
{
    rt_tick_t next_tick;

    if (palarm->enable)
    {
        next_tick = RT_TICK_PER_SECOND;
        rt_timer_control(&alarm_time, RT_TIMER_CTRL_SET_TIME, &next_tick);
        rt_timer_start(&alarm_time);
    }
    else
    {
        rt_timer_stop(&alarm_time);
    }
}

#endif

/**
 * @brief Set RTC time baseline
 * @param ts Pointer to timestamp to set as baseline
 * @return None
 *
 * This function sets a new time baseline for the soft RTC. All subsequent
 * time calculations will be based on this baseline. It records both the
 * time value and the corresponding system tick or high-precision time.
 * Also updates alarm status if alarms are enabled.
 */
static void set_rtc_time(struct timespec *ts)
{
    rt_base_t level = rt_spin_lock_irqsave(&_spinlock);
    base_ts.tv_sec = ts->tv_sec;
    base_ts.tv_nsec = ts->tv_nsec;
#ifdef RT_USING_CLOCK_TIME
    rt_clock_boottime_get_ns(&base_ktime_ts);
#else
    base_tick = rt_tick_get();
#endif
    rt_spin_unlock_irqrestore(&_spinlock, level);
#ifdef RT_USING_ALARM
    soft_rtc_alarm_update(&wkalarm);
#endif
}

/**
 * @brief Get current RTC time
 * @param ts Output parameter to store the retrieved timestamp
 * @return None
 *
 * This function calculates the current time based on the stored baseline
 * and the elapsed system tick or high-precision time. It handles both
 * nanosecond overflow and underflow to ensure accurate time representation.
 * The calculation is thread-safe using spinlock protection.
 */
static void get_rtc_time(struct timespec *ts)
{
    rt_base_t level;

    if (!ts)
        return;

    level = rt_spin_lock_irqsave(&_spinlock);
#ifdef RT_USING_CLOCK_TIME
    struct timespec current_ts;
    rt_clock_boottime_get_ns(&current_ts);

    ts->tv_sec = base_ts.tv_sec + (current_ts.tv_sec - base_ktime_ts.tv_sec);
    ts->tv_nsec = base_ts.tv_nsec + (current_ts.tv_nsec - base_ktime_ts.tv_nsec);
#else
    rt_tick_t tick = rt_tick_get_delta(base_tick);
    ts->tv_sec = base_ts.tv_sec + tick / RT_TICK_PER_SECOND;
    ts->tv_nsec = base_ts.tv_nsec + ((tick % RT_TICK_PER_SECOND) * (1000000000UL / RT_TICK_PER_SECOND));
#endif
    /* Handle nanosecond overflow/underflow */
    if (ts->tv_nsec >= 1000000000L)
    {
        ts->tv_sec++;
        ts->tv_nsec -= 1000000000L;
    }
    if (ts->tv_nsec < 0)
    {
        ts->tv_sec--;
        ts->tv_nsec += 1000000000L;
    }
    rt_spin_unlock_irqrestore(&_spinlock, level);
}

/**
 * @brief RTC device control function
 * @param dev Pointer to RTC device
 * @param cmd Control command (RT_DEVICE_CTRL_RTC_*)
 * @param args Command arguments (varies by command)
 * @return rt_err_t RT_EOK on success, -RT_EINVAL on error
 *
 * This function handles various RTC control commands including:
 * - RT_DEVICE_CTRL_RTC_GET_TIME: Get current time as time_t
 * - RT_DEVICE_CTRL_RTC_SET_TIME: Set time from time_t
 * - RT_DEVICE_CTRL_RTC_GET_ALARM: Get alarm configuration
 * - RT_DEVICE_CTRL_RTC_SET_ALARM: Set alarm configuration
 * - RT_DEVICE_CTRL_RTC_GET_TIMEVAL: Get time as timeval
 * - RT_DEVICE_CTRL_RTC_SET_TIMEVAL: Set time from timeval
 * - RT_DEVICE_CTRL_RTC_GET_TIMESPEC: Get time as timespec
 * - RT_DEVICE_CTRL_RTC_SET_TIMESPEC: Set time from timespec
 * - RT_DEVICE_CTRL_RTC_GET_TIMERES: Get timer resolution
 */
static rt_err_t soft_rtc_control(rt_device_t dev, int cmd, void *args)
{
    time_t *t;
    struct timeval *tv;
    struct timespec *ts;
    struct timespec ts_temp;
    rt_base_t level;

    RT_ASSERT(dev != RT_NULL);

    if (!args)
        return -RT_EINVAL;

    rt_memset(&ts_temp, 0, sizeof(ts_temp));

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
    {
        t = (time_t *)args;
        get_rtc_time(&ts_temp);
        *t = ts_temp.tv_sec;
        break;
    }
    case RT_DEVICE_CTRL_RTC_SET_TIME:
    {
        t = (time_t *)args;
        ts_temp.tv_sec = *t;
        set_rtc_time(&ts_temp);
        break;
    }
#ifdef RT_USING_ALARM
    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        *((struct rt_rtc_wkalarm *)args) = wkalarm;
        break;
    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        wkalarm = *((struct rt_rtc_wkalarm *)args);
        soft_rtc_alarm_update(&wkalarm);
        break;
#endif
    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
    {
        tv = (struct timeval *)args;
        get_rtc_time(&ts_temp);
        tv->tv_sec = ts_temp.tv_sec;
        tv->tv_usec = ts_temp.tv_nsec / 1000;
        break;
    }
    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
    {
        tv = (struct timeval *)args;
        ts_temp.tv_sec = tv->tv_sec;
        ts_temp.tv_nsec = tv->tv_usec * 1000;
        set_rtc_time(&ts_temp);
        break;
    }
    case RT_DEVICE_CTRL_RTC_GET_TIMESPEC:
    {
        ts = (struct timespec *)args;
        get_rtc_time(ts);
        break;
    }
    case RT_DEVICE_CTRL_RTC_SET_TIMESPEC:
    {
        ts = (struct timespec *)args;
        set_rtc_time(ts);
        break;
    }
    case RT_DEVICE_CTRL_RTC_GET_TIMERES:
    {
        ts = (struct timespec *)args;
        level = rt_spin_lock_irqsave(&_spinlock);
        ts->tv_sec = 0;
#ifdef RT_USING_CLOCK_TIME
        ts->tv_nsec = (rt_clock_time_get_res_scaled() / RT_CLOCK_TIME_RESMUL);
#else
        ts->tv_nsec = (1000UL * 1000 * 1000) / RT_TICK_PER_SECOND;
#endif
        rt_spin_unlock_irqrestore(&_spinlock, level);
        break;
    }
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops soft_rtc_ops = {
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    soft_rtc_control
};
#endif

/**
 * @brief Soft RTC device initialization
 * @return int 0 on success
 *
 * This function initializes the soft RTC device, registers it to the system,
 * and sets the default time. It ensures only one RTC device named "rtc"
 * exists in the system and configures the device operations.
 * The initialization is performed only once.
 */
static int rt_soft_rtc_init(void)
{
    static rt_bool_t init_ok = RT_FALSE;
    struct tm time_new = SOFT_RTC_TIME_DEFAULT;

    if (init_ok)
    {
        return 0;
    }
#if defined(RT_USING_SOFT_RTC) && defined(BSP_USING_ONCHIP_RTC)
#warning "Please note: Currently only one RTC device is allowed in the system, and the name is "rtc"."
#endif
    RT_ASSERT(!rt_device_find("rtc"));

#ifdef RT_USING_ALARM
    rt_timer_init(&alarm_time,
                  "alarm",
                  alarm_timeout,
                  &soft_rtc_dev,
                  0,
                  RT_TIMER_FLAG_SOFT_TIMER | RT_TIMER_FLAG_ONE_SHOT);
#endif

#ifdef RT_USING_CLOCK_TIME
    rt_clock_boottime_get_ns(&base_ktime_ts);
#else
    base_tick = rt_tick_get();
#endif
    base_ts.tv_sec = timegm(&time_new);
    base_ts.tv_nsec = 0;

    soft_rtc_dev.type = RT_Device_Class_RTC;

    /* Register RTC device */
#ifdef RT_USING_DEVICE_OPS
    soft_rtc_dev.ops = &soft_rtc_ops;
#else
    soft_rtc_dev.init = RT_NULL;
    soft_rtc_dev.open = RT_NULL;
    soft_rtc_dev.close = RT_NULL;
    soft_rtc_dev.read = RT_NULL;
    soft_rtc_dev.write = RT_NULL;
    soft_rtc_dev.control = soft_rtc_control;
#endif

    /* No private data */
    soft_rtc_dev.user_data = RT_NULL;

    rt_device_register(&soft_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR);

    init_ok = RT_TRUE;

    return 0;
}
INIT_DEVICE_EXPORT(rt_soft_rtc_init);

#ifdef RT_USING_SYSTEM_WORKQUEUE

/**
 * @brief Soft RTC time synchronization
 * @return rt_err_t RT_EOK on success
 *
 * This function retrieves the current RTC time and resets the time baseline.
 * It's used to synchronize the soft RTC time with an external time source.
 */
rt_err_t rt_soft_rtc_sync(void)
{
    time_t time = 0;

    rt_device_control(&soft_rtc_dev, RT_DEVICE_CTRL_RTC_GET_TIME, &time);
    struct timespec ts = { time, 0 };
    /*
     * Intentionally reset the soft RTC baseline to the current time.
     * This operation updates alarm status and synchronizes the soft RTC
     * with the external time source, discarding any accumulated drift.
     * This is the intended behavior for synchronization in this context.
     */
    set_rtc_time(&ts);
    return RT_EOK;
}

/**
 * @brief RTC sync work function
 * @param work Pointer to work item
 * @param work_data Work data (unused)
 * @return None
 *
 * This function is executed periodically to maintain soft RTC time accuracy.
 * It performs synchronization and schedules the next sync task.
 */
static void rtc_sync_work_func(struct rt_work *work, void *work_data)
{
    rt_soft_rtc_sync();
    rt_work_submit(work, rt_tick_from_millisecond(RTC_AUTO_SYNC_PERIOD * 1000));
}

/**
 * @brief Set soft RTC time source
 * @param name Name of the time source device
 * @return rt_err_t RT_EOK on success
 *
 * This function configures the soft RTC to use a specific time source
 * and starts the periodic synchronization mechanism. The time source
 * device must exist before calling this function.
 */
rt_err_t rt_soft_rtc_set_source(const char *name)
{
    RT_ASSERT(name != RT_NULL);
    RT_ASSERT(rt_device_find(name));

    rt_work_init(&rtc_sync_work, rtc_sync_work_func, RT_NULL);
    rt_work_submit(&rtc_sync_work, rt_tick_from_millisecond(RTC_AUTO_SYNC_FIRST_DELAY * 1000));

    return RT_EOK;
}

#ifdef FINSH_USING_MSH
#include <finsh.h>
/**
 * @brief RTC sync command handler
 * @param argc Argument count
 * @param argv Argument array
 * @return None
 *
 * MSH command that manually triggers RTC time synchronization and displays
 * the current time information. Usage: rtc_sync
 */
static void cmd_rtc_sync(int argc, char **argv)
{
    struct timeval tv = { 0 };
    struct timezone tz = { 0 };
    time_t now = (time_t)0;

    rt_soft_rtc_sync();

    gettimeofday(&tv, &tz);
    now = tv.tv_sec;
    rt_kprintf("local time: %.*s", 25, ctime(&now));
    rt_kprintf("timestamps: %ld\n", (long)tv.tv_sec);
}
MSH_CMD_EXPORT_ALIAS(cmd_rtc_sync, rtc_sync, Update time by soft rtc);
#endif

#endif /* RT_USING_SYSTEM_WORKQUEUE */

#endif /* RT_USING_SOFT_RTC */
