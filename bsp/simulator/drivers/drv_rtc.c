/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-13     armink       the first version
 * 2022-05-17     Meco Man     improve and beautify
 */

#include <sys/time.h>
#include <rtdevice.h>

static struct rt_device rtc_dev;

#ifdef BSP_USING_ALARM
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
#endif /* BSP_USING_ALARM */

static void get_rtc_timeval(struct timeval *tv)
{
#ifdef _WIN32
    struct tm newtime = { 0 };
    SYSTEMTIME sys_time;

    GetSystemTime(&sys_time); /* get RTC from Windows */

    newtime.tm_year = sys_time.wYear - 1900;
    newtime.tm_mon = sys_time.wMonth - 1;
    newtime.tm_mday = sys_time.wDay;
    newtime.tm_hour = sys_time.wHour;
    newtime.tm_min = sys_time.wMinute;
    newtime.tm_sec = sys_time.wSecond;

    tv->tv_sec = timegm(&newtime);
    tv->tv_usec = sys_time.wMilliseconds * 1000UL;
#else
    tv->tv_sec = 0;
    tv->tv_usec = 0;
#endif
}

static rt_err_t pc_rtc_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
    {
        struct timeval tv;
        get_rtc_timeval(&tv);
        *(time_t*) args = tv.tv_sec;
        break;
    }
    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
    {
        get_rtc_timeval((struct timeval *) args);
        break;
    }
#ifdef BSP_USING_ALARM
    case RT_DEVICE_CTRL_RTC_SET_TIME:
    {
        soft_rtc_alarm_update(&wkalarm);
        break;
    }
    case RT_DEVICE_CTRL_RTC_GET_ALARM:
    {
        *((struct rt_rtc_wkalarm *)args) = wkalarm;
        break;
    }
    case RT_DEVICE_CTRL_RTC_SET_ALARM:
    {
        wkalarm = *((struct rt_rtc_wkalarm *)args);
        soft_rtc_alarm_update(&wkalarm);
        break;
    }
#endif /* BSP_USING_ALARM */
    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops pc_rtc_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    pc_rtc_control
};
#endif

int rt_pc_rtc_init(void)
{
    /* make sure only one 'rtc' device */
    RT_ASSERT(!rt_device_find("rtc"));

#ifdef BSP_USING_ALARM
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
    rtc_dev.ops = &pc_rtc_ops;
#else
    rtc_dev.init = RT_NULL;
    rtc_dev.open = RT_NULL;
    rtc_dev.close = RT_NULL;
    rtc_dev.read = RT_NULL;
    rtc_dev.write = RT_NULL;
    rtc_dev.control = pc_rtc_control;
#endif
    rtc_dev.user_data = RT_NULL; /* no private */

    rt_device_register(&rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR);
    return 0;
}
INIT_BOARD_EXPORT(rt_pc_rtc_init);
