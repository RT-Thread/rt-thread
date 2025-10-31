/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
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

#ifdef RT_USING_KTIME
#include <ktime.h>
#endif

#ifdef RT_USING_SOFT_RTC

/* 2018-01-30 14:44:50 = RTC_TIME_INIT(2018, 1, 30, 14, 44, 50)  */
#define RTC_TIME_INIT(year, month, day, hour, minute, second)                                                            \
    {                                                                                                                    \
        .tm_year = year - 1900, .tm_mon = month - 1, .tm_mday = day, .tm_hour = hour, .tm_min = minute, .tm_sec = second \
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
static struct timespec init_ts = { 0 };
static RT_DEFINE_SPINLOCK(_spinlock);
#ifdef RT_USING_KTIME
static struct timespec init_ktime_ts = { 0 };
#else
static rt_tick_t init_tick;
#endif

#ifdef RT_USING_ALARM
static struct rt_rtc_wkalarm wkalarm;
static struct rt_timer alarm_time;

static void alarm_timeout(void *param)
{
    rt_alarm_update(param, 1);
}

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

static void set_rtc_time(struct timespec *ts)
{
    rt_base_t level = rt_spin_lock_irqsave(&_spinlock);
    init_ts.tv_sec = ts->tv_sec;
    init_ts.tv_nsec = ts->tv_nsec;
#ifdef RT_USING_KTIME
    rt_ktime_boottime_get_ns(&init_ktime_ts);
#else
    init_tick = rt_tick_get();
#endif
    rt_spin_unlock_irqrestore(&_spinlock, level);
#ifdef RT_USING_ALARM
    soft_rtc_alarm_update(&wkalarm);
#endif
}

static void get_rtc_time(struct timespec *ts)
{
    rt_base_t level;

    if (!ts)
        return;

    level = rt_spin_lock_irqsave(&_spinlock);
#ifdef RT_USING_KTIME
    struct timespec current_ts;
    rt_ktime_boottime_get_ns(&current_ts);

    /* Calculate time difference */
    ts->tv_sec = init_ktime_ts.tv_sec + (current_ts.tv_sec - init_ktime_ts.tv_sec);
    ts->tv_nsec = init_ktime_ts.tv_nsec + (current_ts.tv_nsec - init_ktime_ts.tv_nsec);
#else
    rt_tick_t tick = rt_tick_get_delta(init_tick);
    ts->tv_sec = init_ts.tv_sec + tick / RT_TICK_PER_SECOND;
    ts->tv_nsec = init_ts.tv_nsec + ((tick % RT_TICK_PER_SECOND) * (1000000000UL / RT_TICK_PER_SECOND));
#endif
    /* Handle nanosecond overflow */
    if (ts->tv_nsec >= 1000000000L)
    {
        ts->tv_sec++;
        ts->tv_nsec -= 1000000000L;
    }
    /* Handle nanosecond underflow */
    if (ts->tv_nsec < 0)
    {
        ts->tv_sec--;
        ts->tv_nsec += 1000000000L;
    }
    rt_spin_unlock_irqrestore(&_spinlock, level);
}

static rt_err_t soft_rtc_control(rt_device_t dev, int cmd, void *args)
{
    time_t *t;
    rt_base_t level;
    struct tm time_temp;

    RT_ASSERT(dev != RT_NULL);
    rt_memset(&time_temp, 0, sizeof(struct tm));

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
    {
        if (!args)
            return -RT_EINVAL;
        t = (time_t *)args;
        struct timespec ts;
        get_rtc_time(&ts);
        *t = ts.tv_sec;
        break;
    }
    case RT_DEVICE_CTRL_RTC_SET_TIME:
    {
        if (!args)
            return -RT_EINVAL;
        t = (time_t *)args;
        struct timespec ts = { *t, 0 };
        set_rtc_time(&ts);
        break;
    }
#ifdef RT_USING_ALARM
    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        if (!args)
            return -RT_EINVAL;
        *((struct rt_rtc_wkalarm *)args) = wkalarm;
        break;
    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        if (!args)
            return -RT_EINVAL;
        wkalarm = *((struct rt_rtc_wkalarm *)args);
        soft_rtc_alarm_update(&wkalarm);
        break;
#endif
    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
    {
        if (!args)
            return -RT_EINVAL;
        struct timeval *tv = (struct timeval *)args;
        struct timespec ts;
        get_rtc_time(&ts);
        tv->tv_sec = ts.tv_sec;
        tv->tv_usec = ts.tv_nsec / 1000;
        break;
    }
    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
    {
        if (!args)
            return -RT_EINVAL;
        struct timeval *tv = (struct timeval *)args;
        struct timespec ts = { tv->tv_sec, tv->tv_usec * 1000 };
        set_rtc_time(&ts);
        break;
    }
    case RT_DEVICE_CTRL_RTC_GET_TIMESPEC:
    {
        if (!args)
            return -RT_EINVAL;
        struct timespec *ts = (struct timespec *)args;
        get_rtc_time(ts);
        break;
    }
    case RT_DEVICE_CTRL_RTC_SET_TIMESPEC:
    {
        if (!args)
            return -RT_EINVAL;
        struct timespec *ts = (struct timespec *)args;
        set_rtc_time(ts);
        break;
    }
    case RT_DEVICE_CTRL_RTC_GET_TIMERES:
    {
        if (!args)
            return -RT_EINVAL;
        struct timespec *ts = (struct timespec *)args;
        level = rt_spin_lock_irqsave(&_spinlock);
        ts->tv_sec = 0;
#ifdef RT_USING_KTIME
        ts->tv_nsec = (rt_ktime_cputimer_getres() / RT_KTIME_RESMUL);
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

static int rt_soft_rtc_init(void)
{
    static rt_bool_t init_ok = RT_FALSE;
    struct tm time_new = SOFT_RTC_TIME_DEFAULT;

    if (init_ok)
    {
        return 0;
    }
    /* Make sure only one 'rtc' device */
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

#ifdef RT_USING_KTIME
    rt_ktime_boottime_get_ns(&init_ktime_ts);
#else
    init_tick = rt_tick_get();
#endif
    init_ts.tv_sec = timegm(&time_new);

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

rt_err_t rt_soft_rtc_sync(void)
{
    time_t time = 0;

    rt_device_control(&soft_rtc_dev, RT_DEVICE_CTRL_RTC_GET_TIME, &time);
    struct timespec ts = { time, 0 };
    set_rtc_time(&ts);
    return RT_EOK;
}

static void rtc_sync_work_func(struct rt_work *work, void *work_data)
{
    rt_soft_rtc_sync();
    rt_work_submit(work, rt_tick_from_millisecond(RTC_AUTO_SYNC_PERIOD * 1000));
}

rt_err_t rt_soft_rtc_set_source(const char *name)
{
    RT_ASSERT(name != RT_NULL);
    RT_ASSERT(rt_device_find(name));  /* make sure source is exist*/

    rt_work_init(&rtc_sync_work, rtc_sync_work_func, RT_NULL);
    rt_work_submit(&rtc_sync_work, rt_tick_from_millisecond(RTC_AUTO_SYNC_FIRST_DELAY * 1000));

    return RT_EOK;
}

#ifdef FINSH_USING_MSH
#include <finsh.h>
static void cmd_rtc_sync(int argc, char **argv)
{
    struct timeval tv = { 0 };
    struct timezone tz = { 0 };
    time_t now = (time_t)0;

    rt_soft_rtc_sync();

    gettimeofday(&tv, &tz);
    now = tv.tv_sec;
    /* Output current time */
    rt_kprintf("local time: %.*s", 25, ctime(&now));
    rt_kprintf("timestamps: %ld\n", (long)tv.tv_sec);
}
MSH_CMD_EXPORT_ALIAS(cmd_rtc_sync, rtc_sync, Update time by soft rtc);
#endif

#endif /* RT_USING_SYSTEM_WORKQUEUE */

#endif /* RT_USING_SOFT_RTC */
