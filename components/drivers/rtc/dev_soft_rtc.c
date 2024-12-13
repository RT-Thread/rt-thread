/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-30     armink       the first version
 */

#include <sys/time.h>
#include <string.h>
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_KTIME
#include <ktime.h>
#endif

#ifdef RT_USING_SOFT_RTC

/* 2018-01-30 14:44:50 = RTC_TIME_INIT(2018, 1, 30, 14, 44, 50)  */
#define RTC_TIME_INIT(year, month, day, hour, minute, second)        \
    {.tm_year = year - 1900, .tm_mon = month - 1, .tm_mday = day, .tm_hour = hour, .tm_min = minute, .tm_sec = second}

#ifndef SOFT_RTC_TIME_DEFAULT
#define SOFT_RTC_TIME_DEFAULT                    RTC_TIME_INIT(2018, 1, 1, 0, 0 ,0)
#endif

#ifndef RTC_AUTO_SYNC_FIRST_DELAY
#define RTC_AUTO_SYNC_FIRST_DELAY 25
#endif
#ifndef RTC_AUTO_SYNC_PERIOD
#define RTC_AUTO_SYNC_PERIOD 3600
#endif

static struct rt_work rtc_sync_work;
static rt_device_t    source_device = RT_NULL;

static struct rt_device soft_rtc_dev;
static rt_tick_t init_tick;
static time_t init_time;
static struct timeval init_tv = {0};

#ifdef RT_USING_KTIME
static struct timespec init_ts = {0};
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

static void set_rtc_time(time_t t)
{
    init_time = t - (rt_tick_get() - init_tick) / RT_TICK_PER_SECOND;
#ifdef RT_USING_ALARM
    soft_rtc_alarm_update(&wkalarm);
#endif
}

static void _source_device_control(int cmd, void *args)
{
    if (source_device == RT_NULL)
        return;

    if (rt_device_open(source_device, 0) == RT_EOK)
    {
        rt_device_control(source_device, cmd, args);
        rt_device_close(source_device);
    }
}

static rt_err_t soft_rtc_control(rt_device_t dev, int cmd, void *args)
{
    time_t *t;
    struct tm time_temp;

    RT_ASSERT(dev != RT_NULL);
    rt_memset(&time_temp, 0, sizeof(struct tm));

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
    {
        t = (time_t *) args;
        *t = init_time + (rt_tick_get() - init_tick) / RT_TICK_PER_SECOND;
        break;
    }
    case RT_DEVICE_CTRL_RTC_SET_TIME:
    {
        t = (time_t *) args;
        set_rtc_time(*t);
        _source_device_control(RT_DEVICE_CTRL_RTC_SET_TIME, t);
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
#ifdef RT_USING_KTIME
    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
    {
        struct timeval _tv;
        struct timeval *tv = (struct timeval *)args;
        rt_ktime_boottime_get_us(&_tv);
        tv->tv_sec  = init_time + _tv.tv_sec;
        tv->tv_usec = init_tv.tv_usec + _tv.tv_usec;
        break;
    }
    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
    {
        struct timeval _tv;
        struct timeval *tv = (struct timeval *)args;
        rt_ktime_boottime_get_us(&_tv);
        set_rtc_time(tv->tv_sec);
        init_tv.tv_usec = tv->tv_usec - _tv.tv_usec;
        _source_device_control(RT_DEVICE_CTRL_RTC_SET_TIME, &(tv->tv_sec));
        break;
    }
    case RT_DEVICE_CTRL_RTC_GET_TIMESPEC:
    {
        struct timespec _ts;
        struct timespec *ts = (struct timespec *)args;
        rt_ktime_boottime_get_ns(&_ts);
        ts->tv_sec  = init_time + _ts.tv_sec;
        ts->tv_nsec = init_ts.tv_nsec + _ts.tv_nsec;
        break;
    }
    case RT_DEVICE_CTRL_RTC_SET_TIMESPEC:
    {
        struct timespec _ts;
        struct timespec *ts = (struct timespec *)args;
        rt_ktime_boottime_get_ns(&_ts);
        set_rtc_time(ts->tv_sec);
        init_ts.tv_nsec = ts->tv_nsec - _ts.tv_nsec;
        _source_device_control(RT_DEVICE_CTRL_RTC_SET_TIME, &(ts->tv_sec));
        break;
    }
    case RT_DEVICE_CTRL_RTC_GET_TIMERES:
    {
        struct timespec *ts = (struct timespec *)args;
        ts->tv_sec  = 0;
        ts->tv_nsec = (rt_ktime_cputimer_getres() / RT_KTIME_RESMUL);
        break;
    }
#else
    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
    {
        struct timeval *tv = (struct timeval *)args;
        rt_tick_t tick = rt_tick_get() - init_tick;
        tv->tv_sec = init_time + tick / RT_TICK_PER_SECOND;
        tv->tv_usec = init_tv.tv_usec + ((tick % RT_TICK_PER_SECOND) * (1000000 / RT_TICK_PER_SECOND));
        break;
    }
    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
    {
        struct timeval *tv = (struct timeval *)args;
        rt_tick_t tick = rt_tick_get() - init_tick;
        set_rtc_time(tv->tv_sec);
        init_tv.tv_usec = tv->tv_usec - ((tick % RT_TICK_PER_SECOND) * (1000000 / RT_TICK_PER_SECOND));
        _source_device_control(RT_DEVICE_CTRL_RTC_SET_TIME, &(tv->tv_sec));
        break;
    }
    case RT_DEVICE_CTRL_RTC_GET_TIMERES:
    {
        struct timespec *ts = (struct timespec *)args;
        ts->tv_sec  = 0;
        ts->tv_nsec = (1000UL * 1000 * 1000) / RT_TICK_PER_SECOND;
        break;
    }
#endif /* RT_USING_KTIME */
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops soft_rtc_ops =
{
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
    /* make sure only one 'rtc' device */
#if defined(RT_USING_SOFT_RTC) && defined(RT_USING_RTC)
#warning "Please note: Currently only one RTC device is allowed in the system, and the name is "rtc"."
#endif
    RT_ASSERT(!rt_device_find("rtc"));

#ifdef RT_USING_ALARM
    rt_timer_init(&alarm_time,
                  "alarm",
                  alarm_timeout,
                  &soft_rtc_dev,
                  0,
                  RT_TIMER_FLAG_SOFT_TIMER|RT_TIMER_FLAG_ONE_SHOT);
#endif

    init_tick = rt_tick_get();
    init_time = timegm(&time_new);

    soft_rtc_dev.type    = RT_Device_Class_RTC;

    /* register rtc device */
#ifdef RT_USING_DEVICE_OPS
    soft_rtc_dev.ops     = &soft_rtc_ops;
#else
    soft_rtc_dev.init    = RT_NULL;
    soft_rtc_dev.open    = RT_NULL;
    soft_rtc_dev.close   = RT_NULL;
    soft_rtc_dev.read    = RT_NULL;
    soft_rtc_dev.write   = RT_NULL;
    soft_rtc_dev.control = soft_rtc_control;
#endif

    /* no private */
    soft_rtc_dev.user_data = RT_NULL;

    rt_device_register(&soft_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR);

    source_device = &soft_rtc_dev;

    init_ok = RT_TRUE;

    return 0;
}
INIT_DEVICE_EXPORT(rt_soft_rtc_init);

#ifdef RT_USING_SYSTEM_WORKQUEUE

rt_err_t rt_soft_rtc_sync(void)
{
    time_t time = 0;

    if (source_device == RT_NULL)
    {
        rt_kprintf("error: rtc source not found, please set it!!!\n");
        return RT_ENOSYS;
    }

    _source_device_control(RT_DEVICE_CTRL_RTC_GET_TIME, &time);
    set_rtc_time(time);
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

    source_device = rt_device_find(name);
    rt_work_init(&rtc_sync_work, rtc_sync_work_func, RT_NULL);
    rt_work_submit(&rtc_sync_work, rt_tick_from_millisecond(RTC_AUTO_SYNC_FIRST_DELAY * 1000));

    return RT_EOK;
}

#ifdef FINSH_USING_MSH
#include <finsh.h>
static void cmd_rtc_sync(int argc, char **argv)
{
    struct timeval  tv  = {0};
    struct timezone tz  = {0};
    time_t          now = (time_t)0;

    rt_soft_rtc_sync();

    gettimeofday(&tv, &tz);
    now = tv.tv_sec;
    /* output current time */
    rt_kprintf("local time: %.*s", 25, ctime(&now));
    rt_kprintf("timestamps: %ld\n", (long)tv.tv_sec);
}
MSH_CMD_EXPORT_ALIAS(cmd_rtc_sync, rtc_sync, Update time by soft rtc);
#endif

#endif /* RT_USING_SYSTEM_WORKQUEUE */

#endif /* RT_USING_SOFT_RTC */
