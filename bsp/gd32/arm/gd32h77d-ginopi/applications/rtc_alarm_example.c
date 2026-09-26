/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-08     CYFS         add a one-shot RTC alarm command with ulog output
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>

#define DBG_TAG "rtc.alarm"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef BSP_USING_RTC_ALARM_EXAMPLE
#include <finsh.h>

#define RTC_ALARM_DEFAULT_SECONDS 5UL
#define RTC_ALARM_MAX_SECONDS     86400UL

static rt_alarm_t demo_alarm;
static time_t demo_deadline;

static void alarm_log_time(const char *state, time_t timestamp)
{
    struct tm local;

    if (localtime_r(&timestamp, &local) == RT_NULL)
    {
        LOG_E("Cannot convert alarm time");
        return;
    }

    LOG_I("%s: %04d-%02d-%02d %02d:%02d:%02d (local time)", state,
          local.tm_year + 1900, local.tm_mon + 1, local.tm_mday,
          local.tm_hour, local.tm_min, local.tm_sec);
}

static void alarm_callback(rt_alarm_t alarm, time_t timestamp)
{
    /* The Alarm service owns the list during callbacks; keep the object alive. */
    RT_UNUSED(alarm);
    alarm_log_time("Triggered", timestamp);
}

static rt_err_t alarm_remove(void)
{
    rt_err_t result = RT_EOK;

    if (demo_alarm != RT_NULL)
    {
        result = rt_alarm_delete(demo_alarm);
        demo_alarm = RT_NULL;
    }

    return result;
}

static void alarm_usage(void)
{
    LOG_I("rtc_alarm [seconds]  - one-shot alarm, 1..86400 seconds, default 5");
    LOG_I("rtc_alarm status     - show the example alarm");
    LOG_I("rtc_alarm stop       - cancel and delete the example alarm");
}

static int rtc_alarm(int argc, char **argv)
{
    struct rt_alarm_setup setup = {0};
    struct timeval now;
    time_t deadline;
    rt_int64_t deadline_seconds;
    unsigned long seconds = RTC_ALARM_DEFAULT_SECONDS;
    char *end;
    rt_err_t result;

    if (argc > 2)
    {
        alarm_usage();
        return -RT_EINVAL;
    }

    if (argc == 2)
    {
        if (rt_strcmp(argv[1], "help") == 0)
        {
            alarm_usage();
            return RT_EOK;
        }
        if (rt_strcmp(argv[1], "status") == 0)
        {
            if (demo_alarm == RT_NULL)
            {
                LOG_I("No example alarm");
            }
            else
            {
                rt_base_t level = rt_hw_interrupt_disable();
                rt_bool_t armed = (demo_alarm->flag & RT_ALARM_STATE_START) != 0;
                rt_hw_interrupt_enable(level);
                alarm_log_time(armed ? "Armed" : "Expired", demo_deadline);
            }
            return RT_EOK;
        }
        if (rt_strcmp(argv[1], "stop") == 0)
        {
            result = alarm_remove();
            if (result != RT_EOK)
            {
                LOG_E("Cannot disable hardware alarm: %d", result);
                return result;
            }
            LOG_I("Example alarm stopped");
            return RT_EOK;
        }

        errno = 0;
        seconds = strtoul(argv[1], &end, 10);
        if ((errno == ERANGE) || (end == argv[1]) || (*end != '\0') ||
            (argv[1][0] < '0') || (argv[1][0] > '9') ||
            (seconds == 0UL) || (seconds > RTC_ALARM_MAX_SECONDS))
        {
            LOG_E("Invalid delay: use 1..86400 seconds");
            return -RT_EINVAL;
        }
    }

    /* gettimeofday opens and initializes the RTC before the Alarm API uses it. */
    if (gettimeofday(&now, RT_NULL) != 0)
    {
        LOG_E("Cannot read RTC; check the drv.rtc log");
        return -RT_ERROR;
    }

    deadline_seconds = (rt_int64_t)now.tv_sec + seconds;
    deadline = (time_t)deadline_seconds;
    if ((rt_int64_t)deadline != deadline_seconds)
    {
        LOG_E("Alarm deadline exceeds the time_t range");
        return -RT_EINVAL;
    }
    setup.flag = RT_ALARM_ONESHOT;
#ifdef RT_ALARM_USING_LOCAL_TIME
    if (localtime_r(&deadline, &setup.wktime) == RT_NULL)
#else
    if (gmtime_r(&deadline, &setup.wktime) == RT_NULL)
#endif
    {
        LOG_E("Cannot convert alarm deadline");
        return -RT_EINVAL;
    }
    if ((setup.wktime.tm_year < 100) || (setup.wktime.tm_year > 199))
    {
        LOG_E("Alarm date must be between 2000 and 2099");
        return -RT_EINVAL;
    }

    result = alarm_remove();
    if (result != RT_EOK)
    {
        LOG_E("Cannot replace the previous alarm: %d", result);
        return result;
    }

    demo_alarm = rt_alarm_create(alarm_callback, &setup);
    if (demo_alarm == RT_NULL)
    {
        LOG_E("Cannot allocate alarm");
        return -RT_ENOMEM;
    }

    demo_deadline = deadline;
    result = rt_alarm_start(demo_alarm);
    if (result != RT_EOK)
    {
        alarm_remove();
        LOG_E("Cannot start alarm: %d", result);
        return result;
    }

    LOG_I("One-shot alarm in %lu seconds", seconds);
    alarm_log_time("Armed", deadline);
    return RT_EOK;
}
MSH_CMD_EXPORT(rtc_alarm, set a one-shot RTC alarm or use status/stop/help);
#endif
