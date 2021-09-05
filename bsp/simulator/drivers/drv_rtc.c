/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-13     armink       the first version
 */

#include <sys/time.h>
#include <string.h>
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_RTC

static struct rt_device rtc_dev;

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

static rt_err_t soft_rtc_control(rt_device_t dev, int cmd, void *args)
{
    __time32_t *t;
    struct tm newtime;

    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
    {
        t = (__time32_t *)args;
        SYSTEMTIME sys_time;

        GetSystemTime(&sys_time);
        newtime.tm_year = sys_time.wYear - 1900;
        newtime.tm_mon = sys_time.wMonth - 1;
        newtime.tm_mday = sys_time.wDay;
        newtime.tm_hour = sys_time.wHour;
        newtime.tm_min = sys_time.wMinute;
        newtime.tm_sec = sys_time.wSecond;
        *t = timegm(&newtime);
        break;
    }
    case RT_DEVICE_CTRL_RTC_SET_TIME:
    {
#ifdef RT_USING_ALARM
        soft_rtc_alarm_update(&wkalarm);
#endif
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
    case RT_DEVICE_CTRL_RTC_GET_TIME_US:
    {
        long *tv_usec = (long *)args;
        SYSTEMTIME sys_time;
        GetSystemTime(&sys_time);
        *tv_usec = sys_time.wMilliseconds * 1000UL;
        break;
    }
    default:
        return -RT_ERROR;
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

int rt_win_rtc_init(void)
{
    static rt_bool_t init_ok = RT_FALSE;

    if (init_ok)
    {
        return 0;
    }
    /* make sure only one 'rtc' device */
    RT_ASSERT(!rt_device_find("rtc"));

#ifdef RT_USING_ALARM
    rt_timer_init(&alarm_time,
        "alarm",
        alarm_timeout,
        &rtc_dev,
        0,
        RT_TIMER_FLAG_SOFT_TIMER | RT_TIMER_FLAG_ONE_SHOT);
#endif

    rtc_dev.type = RT_Device_Class_RTC;

    /* register rtc device */
#ifdef RT_USING_DEVICE_OPS
    rtc_dev.ops = &soft_rtc_ops;
#else
    rtc_dev.init = RT_NULL;
    rtc_dev.open = RT_NULL;
    rtc_dev.close = RT_NULL;
    rtc_dev.read = RT_NULL;
    rtc_dev.write = RT_NULL;
    rtc_dev.control = soft_rtc_control;
#endif

    /* no private */
    rtc_dev.user_data = RT_NULL;

    rt_device_register(&rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR);

    init_ok = RT_TRUE;

    return 0;
}
INIT_BOARD_EXPORT(rt_win_rtc_init);

#endif /* RT_USING_RTC */
