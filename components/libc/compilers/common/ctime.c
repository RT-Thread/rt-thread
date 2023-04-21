/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-08-21     zhangjun     copy from minilibc
 * 2020-09-07     Meco Man     combine gcc armcc iccarm
 * 2021-02-05     Meco Man     add timegm()
 * 2021-02-07     Meco Man     fixed gettimeofday()
 * 2021-02-08     Meco Man     add settimeofday() stime()
 * 2021-02-10     Meco Man     add ctime_r() and re-implement ctime()
 * 2021-02-11     Meco Man     fix bug #3183 - align days[] and months[] to 4 bytes
 * 2021-02-12     Meco Man     add errno
 * 2012-12-08     Bernard      <clock_time.c> fix the issue of _timevalue.tv_usec initialization,
 *                             which found by Rob <rdent@iinet.net.au>
 * 2021-02-12     Meco Man     move all of the functions located in <clock_time.c> to this file
 * 2021-03-15     Meco Man     fixed a bug of leaking memory in asctime()
 * 2021-05-01     Meco Man     support fixed timezone
 * 2021-07-21     Meco Man     implement that change/set timezone APIs
 */

#include "sys/time.h"
#include <sys/errno.h>
#include <rtthread.h>
#include <rthw.h>
#include <unistd.h>
#ifdef RT_USING_SMART
#include "lwp.h"
#endif
#ifdef RT_USING_POSIX_DELAY
#include <delay.h>
#endif
#if defined( RT_USING_RTC ) || defined( RT_USING_CPUTIME)
#include <rtdevice.h>
#endif

#define DBG_TAG    "time"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#define _WARNING_NO_RTC "Cannot find a RTC device!"

/* seconds per day */
#define SPD 24*60*60

/* days per month -- nonleap! */
static const short __spm[13] =
{
    0,
    (31),
    (31 + 28),
    (31 + 28 + 31),
    (31 + 28 + 31 + 30),
    (31 + 28 + 31 + 30 + 31),
    (31 + 28 + 31 + 30 + 31 + 30),
    (31 + 28 + 31 + 30 + 31 + 30 + 31),
    (31 + 28 + 31 + 30 + 31 + 30 + 31 + 31),
    (31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30),
    (31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31),
    (31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30),
    (31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31),
};

rt_align(4) static const char *days = "Sun Mon Tue Wed Thu Fri Sat ";
rt_align(4) static const char *months = "Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec ";

static int __isleap(int year)
{
    /* every fourth year is a leap year except for century years that are
     * not divisible by 400. */
    /*  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)); */
    return (!(year % 4) && ((year % 100) || !(year % 400)));
}

static void num2str(char *c, int i)
{
    c[0] = i / 10 + '0';
    c[1] = i % 10 + '0';
}

/**
 * Get time from RTC device (without timezone, UTC+0)
 * @param tv: struct timeval
 * @return the operation status, RT_EOK on successful
 */
static rt_err_t get_timeval(struct timeval *tv)
{
#ifdef RT_USING_RTC
    static rt_device_t device = RT_NULL;
    rt_err_t rst = -RT_ERROR;

    if (tv == RT_NULL)
        return -RT_EINVAL;

    /* default is 0 */
    tv->tv_sec = 0;
    tv->tv_usec = 0;

    /* optimization: find rtc device only first */
    if (device == RT_NULL)
    {
        device = rt_device_find("rtc");
    }

    /* read timestamp from RTC device */
    if (device != RT_NULL)
    {
        if (rt_device_open(device, 0) == RT_EOK)
        {
            rst = rt_device_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &tv->tv_sec);
            rt_device_control(device, RT_DEVICE_CTRL_RTC_GET_TIMEVAL, tv);
            rt_device_close(device);
        }
    }
    else
    {
        LOG_W(_WARNING_NO_RTC);
        return -RT_ENOSYS;
    }

    return rst;

#else
    LOG_W(_WARNING_NO_RTC);
    return -RT_ENOSYS;
#endif /* RT_USING_RTC */
}

/**
 * Set time to RTC device (without timezone)
 * @param tv: struct timeval
 * @return the operation status, RT_EOK on successful
 */
static int set_timeval(struct timeval *tv)
{
#ifdef RT_USING_RTC
    static rt_device_t device = RT_NULL;
    rt_err_t rst = -RT_ERROR;

    if (tv == RT_NULL)
        return -RT_EINVAL;

    /* optimization: find rtc device only first */
    if (device == RT_NULL)
    {
        device = rt_device_find("rtc");
    }

    /* read timestamp from RTC device */
    if (device != RT_NULL)
    {
        if (rt_device_open(device, 0) == RT_EOK)
        {
            rst = rt_device_control(device, RT_DEVICE_CTRL_RTC_SET_TIME, &tv->tv_sec);
            rt_device_control(device, RT_DEVICE_CTRL_RTC_SET_TIMEVAL, tv);
            rt_device_close(device);
        }
    }
    else
    {
        LOG_W(_WARNING_NO_RTC);
        return -RT_ENOSYS;
    }

    return rst;

#else
    LOG_W(_WARNING_NO_RTC);
    return -RT_ENOSYS;
#endif /* RT_USING_RTC */
}

struct tm *gmtime_r(const time_t *timep, struct tm *r)
{
    int i;
    int work = *timep % (SPD);

    if(timep == RT_NULL || r == RT_NULL)
    {
        rt_set_errno(EFAULT);
        return RT_NULL;
    }

    rt_memset(r, RT_NULL, sizeof(struct tm));

    r->tm_sec = work % 60;
    work /= 60;
    r->tm_min = work % 60;
    r->tm_hour = work / 60;
    work = (int)(*timep / (SPD));
    r->tm_wday = (4 + work) % 7;
    for (i = 1970;; ++i)
    {
        int k = __isleap(i) ? 366 : 365;
        if (work >= k)
            work -= k;
        else
            break;
    }
    r->tm_year = i - 1900;
    r->tm_yday = work;

    r->tm_mday = 1;
    if (__isleap(i) && (work > 58))
    {
        if (work == 59)
            r->tm_mday = 2; /* 29.2. */
        work -= 1;
    }

    for (i = 11; i && (__spm[i] > work); --i);

    r->tm_mon = i;
    r->tm_mday += work - __spm[i];

    r->tm_isdst = tz_is_dst();
    return r;
}
RTM_EXPORT(gmtime_r);

struct tm* gmtime(const time_t* t)
{
    static struct tm tmp;
    return gmtime_r(t, &tmp);
}
RTM_EXPORT(gmtime);

struct tm* localtime_r(const time_t* t, struct tm* r)
{
    time_t local_tz;

    local_tz = *t + (time_t)tz_get() * 3600;
    return gmtime_r(&local_tz, r);
}
RTM_EXPORT(localtime_r);

struct tm* localtime(const time_t* t)
{
    static struct tm tmp;
    return localtime_r(t, &tmp);
}
RTM_EXPORT(localtime);

time_t mktime(struct tm * const t)
{
    time_t timestamp;

    timestamp = timegm(t);
    timestamp = timestamp - 3600 * (time_t)tz_get();
    return timestamp;
}
RTM_EXPORT(mktime);

char* asctime_r(const struct tm *t, char *buf)
{
    if(t == RT_NULL || buf == RT_NULL)
    {
        rt_set_errno(EFAULT);
        return RT_NULL;
    }

    rt_memset(buf, RT_NULL, 26);

    /* Checking input validity */
    if ((int)rt_strlen(days) <= (t->tm_wday << 2) || (int)rt_strlen(months) <= (t->tm_mon << 2))
    {
        LOG_W("asctime_r: the input parameters exceeded the limit, please check it.");
        *(int*) buf = *(int*) days;
        *(int*) (buf + 4) = *(int*) months;
        num2str(buf + 8, t->tm_mday);
        if (buf[8] == '0')
            buf[8] = ' ';
        buf[10] = ' ';
        num2str(buf + 11, t->tm_hour);
        buf[13] = ':';
        num2str(buf + 14, t->tm_min);
        buf[16] = ':';
        num2str(buf + 17, t->tm_sec);
        buf[19] = ' ';
        num2str(buf + 20, 2000 / 100);
        num2str(buf + 22, 2000 % 100);
        buf[24] = '\n';
        buf[25] = '\0';
        return buf;
    }

    /* "Wed Jun 30 21:49:08 1993\n" */
    *(int*) buf = *(int*) (days + (t->tm_wday << 2));
    *(int*) (buf + 4) = *(int*) (months + (t->tm_mon << 2));
    num2str(buf + 8, t->tm_mday);
    if (buf[8] == '0')
        buf[8] = ' ';
    buf[10] = ' ';
    num2str(buf + 11, t->tm_hour);
    buf[13] = ':';
    num2str(buf + 14, t->tm_min);
    buf[16] = ':';
    num2str(buf + 17, t->tm_sec);
    buf[19] = ' ';
    num2str(buf + 20, (t->tm_year + 1900) / 100);
    num2str(buf + 22, (t->tm_year + 1900) % 100);
    buf[24] = '\n';
    buf[25] = '\0';
    return buf;
}
RTM_EXPORT(asctime_r);

char* asctime(const struct tm *timeptr)
{
    static char buf[26];
    return asctime_r(timeptr, buf);
}
RTM_EXPORT(asctime);

char *ctime_r(const time_t * tim_p, char * result)
{
    struct tm tm;
    return asctime_r(localtime_r(tim_p, &tm), result);
}
RTM_EXPORT(ctime_r);

char* ctime(const time_t *tim_p)
{
    return asctime(localtime(tim_p));
}
RTM_EXPORT(ctime);

#ifndef __ICCARM__
double difftime(time_t time1, time_t time2)
{
    return (double)(time1 - time2);
}
#endif /* __ICCARM__ */
RTM_EXPORT(difftime);

RTM_EXPORT(strftime); /* inherent in the toolchain */

/**
 * Returns the current time.
 *
 * @param time_t * t the timestamp pointer, if not used, keep NULL.
 *
 * @return The value ((time_t)-1) is returned if the calendar time is not available.
 *         If timer is not a NULL pointer, the return value is also stored in timer.
 *
 */
rt_weak time_t time(time_t *t)
{
    struct timeval now;

    if(get_timeval(&now) == RT_EOK)
    {
        if (t)
        {
            *t = now.tv_sec;
        }
        return now.tv_sec;
    }
    else
    {
        rt_set_errno(EFAULT);
        return ((time_t)-1);
    }
}
RTM_EXPORT(time);

rt_weak clock_t clock(void)
{
    return rt_tick_get();
}
RTM_EXPORT(clock);

int stime(const time_t *t)
{
    struct timeval tv;

    if (t == RT_NULL)
    {
        rt_set_errno(EFAULT);
        return -1;
    }

    tv.tv_sec = *t;
    tv.tv_usec = 0;
    if (set_timeval(&tv) == RT_EOK)
    {
        return 0;
    }
    else
    {
        rt_set_errno(EFAULT);
        return -1;
    }
}
RTM_EXPORT(stime);

time_t timegm(struct tm * const t)
{
    time_t day;
    time_t i;
    time_t years;

    if(t == RT_NULL)
    {
        rt_set_errno(EFAULT);
        return (time_t)-1;
    }

    years = (time_t)t->tm_year - 70;
    if (t->tm_sec > 60)         /* seconds after the minute - [0, 60] including leap second */
    {
        t->tm_min += t->tm_sec / 60;
        t->tm_sec %= 60;
    }
    if (t->tm_min >= 60)        /* minutes after the hour - [0, 59] */
    {
        t->tm_hour += t->tm_min / 60;
        t->tm_min %= 60;
    }
    if (t->tm_hour >= 24)       /* hours since midnight - [0, 23] */
    {
        t->tm_mday += t->tm_hour / 24;
        t->tm_hour %= 24;
    }
    if (t->tm_mon >= 12)        /* months since January - [0, 11] */
    {
        t->tm_year += t->tm_mon / 12;
        t->tm_mon %= 12;
    }
    while (t->tm_mday > __spm[1 + t->tm_mon])
    {
        if (t->tm_mon == 1 && __isleap(t->tm_year + 1900))
        {
            --t->tm_mday;
        }
        t->tm_mday -= __spm[t->tm_mon];
        ++t->tm_mon;
        if (t->tm_mon > 11)
        {
            t->tm_mon = 0;
            ++t->tm_year;
        }
    }

    if (t->tm_year < 70)
    {
        rt_set_errno(EINVAL);
        return (time_t) -1;
    }

    /* Days since 1970 is 365 * number of years + number of leap years since 1970 */
    day = years * 365 + (years + 1) / 4;

    /* After 2100 we have to substract 3 leap years for every 400 years
     This is not intuitive. Most mktime implementations do not support
     dates after 2059, anyway, so we might leave this out for it's
     bloat. */
    if (years >= 131)
    {
        years -= 131;
        years /= 100;
        day -= (years >> 2) * 3 + 1;
        if ((years &= 3) == 3)
            years--;
        day -= years;
    }

    day += t->tm_yday = __spm[t->tm_mon] + t->tm_mday - 1 +
                        (__isleap(t->tm_year + 1900) & (t->tm_mon > 1));

    /* day is now the number of days since 'Jan 1 1970' */
    i = 7;
    t->tm_wday = (int)((day + 4) % i); /* Sunday=0, Monday=1, ..., Saturday=6 */

    i = 24;
    day *= i;
    i = 60;
    return ((day + t->tm_hour) * i + t->tm_min) * i + t->tm_sec;
}
RTM_EXPORT(timegm);

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    /* The use of the timezone structure is obsolete;
     * the tz argument should normally be specified as NULL.
     * The tz_dsttime field has never been used under Linux.
     * Thus, the following is purely of historic interest.
     */
    if(tz != RT_NULL)
    {
        tz->tz_dsttime = DST_NONE;
        tz->tz_minuteswest = -(tz_get() * 60);
    }

    if (tv != RT_NULL && get_timeval(tv) == RT_EOK)
    {
        return 0;
    }
    else
    {
        rt_set_errno(EINVAL);
        return -1;
    }
}
RTM_EXPORT(gettimeofday);

int settimeofday(const struct timeval *tv, const struct timezone *tz)
{
    /* The use of the timezone structure is obsolete;
     * the tz argument should normally be specified as NULL.
     * The tz_dsttime field has never been used under Linux.
     * Thus, the following is purely of historic interest.
     */
    if (tv != RT_NULL
        && tv->tv_usec >= 0
        && set_timeval((struct timeval *)tv) == RT_EOK)
    {
        return 0;
    }
    else
    {
        rt_set_errno(EINVAL);
        return -1;
    }
}
RTM_EXPORT(settimeofday);

#ifdef RT_USING_POSIX_DELAY
int nanosleep(const struct timespec *rqtp, struct timespec *rmtp)
{
    if (rqtp->tv_sec < 0 || rqtp->tv_nsec < 0 || rqtp->tv_nsec >= NANOSECOND_PER_SECOND)
    {
        rt_set_errno(EINVAL);
        return -1;
    }
#ifdef RT_USING_CPUTIME
    rt_uint64_t unit = clock_cpu_getres();
    rt_uint64_t ns = rqtp->tv_sec * NANOSECOND_PER_SECOND + rqtp->tv_nsec;
    rt_uint64_t tick = (ns * (1000UL * 1000)) / unit;
    rt_cputime_sleep(tick);

    if (rt_get_errno() == -RT_EINTR)
    {
        if (rmtp)
        {
            uint64_t rmtp_cpu_tick = tick - clock_cpu_gettime();
            rmtp->tv_sec = ((time_t)((rmtp_cpu_tick * unit) / (1000UL * 1000))) / NANOSECOND_PER_SECOND;
            rmtp->tv_nsec = ((long)((rmtp_cpu_tick * unit) / (1000UL * 1000))) % NANOSECOND_PER_SECOND;
        }
        rt_set_errno(EINTR);
        return -1;
    }
#else
    rt_tick_t tick, tick_old = rt_tick_get();
    tick = rqtp->tv_sec * RT_TICK_PER_SECOND + ((uint64_t)rqtp->tv_nsec * RT_TICK_PER_SECOND) / NANOSECOND_PER_SECOND;
    rt_thread_delay(tick);

    if (rt_get_errno() == -RT_EINTR)
    {
        if (rmtp)
        {
            tick = tick_old + tick - rt_tick_get();
            /* get the passed time */
            rmtp->tv_sec = tick / RT_TICK_PER_SECOND;
            rmtp->tv_nsec = (tick % RT_TICK_PER_SECOND) * (NANOSECOND_PER_SECOND / RT_TICK_PER_SECOND);
        }
        rt_set_errno(EINTR);
        return -1;
    }
#endif
    return 0;
}
RTM_EXPORT(nanosleep);
#endif /* RT_USING_POSIX_DELAY */

#ifdef RT_USING_POSIX_CLOCK
#ifdef RT_USING_RTC
static volatile struct timeval _timevalue;
static int _rt_clock_time_system_init(void)
{
    rt_base_t level;
    time_t time = 0;
    rt_tick_t tick;
    rt_device_t device;

    device = rt_device_find("rtc");
    if (device != RT_NULL)
    {
        /* get realtime seconds */
        if(rt_device_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &time) == RT_EOK)
        {
            level = rt_hw_interrupt_disable();
            tick = rt_tick_get(); /* get tick */
            _timevalue.tv_usec = (tick%RT_TICK_PER_SECOND) * MICROSECOND_PER_TICK;
            _timevalue.tv_sec = time - tick/RT_TICK_PER_SECOND - 1;
            rt_hw_interrupt_enable(level);
            return 0;
        }
    }

    level = rt_hw_interrupt_disable();
    _timevalue.tv_usec = 0;
    _timevalue.tv_sec = 0;
    rt_hw_interrupt_enable(level);

    return -1;
}
INIT_COMPONENT_EXPORT(_rt_clock_time_system_init);
#endif /* RT_USING_RTC */

int clock_getres(clockid_t clockid, struct timespec *res)
{
#ifndef RT_USING_RTC
    LOG_W(_WARNING_NO_RTC);
    return -1;
#else
    int ret = 0;

    if (res == RT_NULL)
    {
        rt_set_errno(EFAULT);
        return -1;
    }

    switch (clockid)
    {
    case CLOCK_REALTIME:
#ifndef RT_USING_CPUTIME
        res->tv_sec = 0;
        res->tv_nsec = NANOSECOND_PER_SECOND/RT_TICK_PER_SECOND;
        break;
#endif
#ifdef RT_USING_CPUTIME
    case CLOCK_CPUTIME_ID:
        res->tv_sec  = 0;
        res->tv_nsec = (clock_cpu_getres() / (1000UL * 1000));
        break;
#endif

    default:
        res->tv_sec  = 0;
        res->tv_nsec = 0;
        ret = -1;
        rt_set_errno(EINVAL);
        break;
    }

    return ret;
#endif /* RT_USING_RTC */
}
RTM_EXPORT(clock_getres);

int clock_gettime(clockid_t clockid, struct timespec *tp)
{
#ifndef RT_USING_RTC
    LOG_W(_WARNING_NO_RTC);
    return -1;
#else
    int ret = 0;

    if (tp == RT_NULL)
    {
        rt_set_errno(EFAULT);
        return -1;
    }

    switch (clockid)
    {
    case CLOCK_REALTIME:
#ifndef RT_USING_CPUTIME
        {
            rt_tick_t tick;
            rt_base_t level;

            level = rt_hw_interrupt_disable();
            tick = rt_tick_get(); /* get tick */
            tp->tv_sec  = _timevalue.tv_sec + tick / RT_TICK_PER_SECOND;
            tp->tv_nsec = (_timevalue.tv_usec + (tick % RT_TICK_PER_SECOND) * MICROSECOND_PER_TICK) * 1000;
            rt_hw_interrupt_enable(level);
        }
        break;
#endif
#ifdef RT_USING_CPUTIME
    case CLOCK_MONOTONIC:
    case CLOCK_CPUTIME_ID:
        {
            uint64_t unit = 0;
            uint64_t cpu_tick;

            unit = clock_cpu_getres();
            cpu_tick = clock_cpu_gettime();

            tp->tv_sec  = ((uint64_t)((cpu_tick * unit) / (1000UL * 1000))) / NANOSECOND_PER_SECOND;
            tp->tv_nsec = ((uint64_t)((cpu_tick * unit) / (1000UL * 1000))) % NANOSECOND_PER_SECOND;
        }
        break;
#endif
    default:
        tp->tv_sec  = 0;
        tp->tv_nsec = 0;
        rt_set_errno(EINVAL);
        ret = -1;
    }

    return ret;
#endif /* RT_USING_RTC */
}
RTM_EXPORT(clock_gettime);

int clock_nanosleep(clockid_t clockid, int flags, const struct timespec *rqtp, struct timespec *rmtp)
{
#ifndef RT_USING_RTC
    LOG_W(_WARNING_NO_RTC);
    return -1;
#else
    if (rqtp->tv_sec < 0 || rqtp->tv_nsec < 0 || rqtp->tv_nsec >= NANOSECOND_PER_SECOND)
    {
        rt_set_errno(EINVAL);
        return -1;
    }
    switch (clockid)
    {
    case CLOCK_REALTIME:
    {
        rt_tick_t tick, tick_old = rt_tick_get();
        if ((flags & TIMER_ABSTIME) == TIMER_ABSTIME)
        {
            rt_int64_t ts = ((rqtp->tv_sec - _timevalue.tv_sec) * RT_TICK_PER_SECOND);
            rt_int64_t tns = (rqtp->tv_nsec - _timevalue.tv_usec * 1000) * (RT_TICK_PER_SECOND / NANOSECOND_PER_SECOND);
            tick = ts + tns;
            rt_tick_t rt_tick = rt_tick_get();
            tick = tick < rt_tick ? 0 : tick - rt_tick;
        }
        else
        {
            tick = rqtp->tv_sec * RT_TICK_PER_SECOND + ((uint64_t)(rqtp->tv_nsec) * RT_TICK_PER_SECOND) / NANOSECOND_PER_SECOND;
        }
        rt_thread_delay(tick);

        if (rt_get_errno() == -RT_EINTR)
        {
            if (rmtp)
            {
                tick = tick_old + tick - rt_tick_get();
                /* get the passed time */
                rmtp->tv_sec = tick / RT_TICK_PER_SECOND;
                rmtp->tv_nsec = (tick % RT_TICK_PER_SECOND) * (NANOSECOND_PER_SECOND / RT_TICK_PER_SECOND);
            }
            rt_set_errno(EINTR);
            return -1;
        }
    }
    break;

#ifdef RT_USING_CPUTIME
    case CLOCK_MONOTONIC:
    case CLOCK_CPUTIME_ID:
    {
        rt_uint64_t cpu_tick_old = clock_cpu_gettime();
        uint64_t unit = clock_cpu_getres();
        rt_uint64_t ns = rqtp->tv_sec * NANOSECOND_PER_SECOND + rqtp->tv_nsec;
        rt_uint64_t tick = (ns * (1000UL * 1000)) / unit;
        if ((flags & TIMER_ABSTIME) == TIMER_ABSTIME)
            tick -= cpu_tick_old;
        rt_cputime_sleep(tick);

        if (rt_get_errno() == -RT_EINTR)
        {
            if (rmtp)
            {
                uint64_t rmtp_cpu_tick = tick - clock_cpu_gettime();
                rmtp->tv_sec = ((time_t)((rmtp_cpu_tick * unit) / (1000UL * 1000))) / NANOSECOND_PER_SECOND;
                rmtp->tv_nsec = ((long)((rmtp_cpu_tick * unit) / (1000UL * 1000))) % NANOSECOND_PER_SECOND;
            }
            rt_set_errno(EINTR);
            return -1;
        }
    }
    break;
#endif
    default:
        rt_set_errno(EINVAL);
        return -1;
    }
    return 0;
#endif
}
RTM_EXPORT(clock_nanosleep);

int clock_settime(clockid_t clockid, const struct timespec *tp)
{
#ifndef RT_USING_RTC
    LOG_W(_WARNING_NO_RTC);
    return -1;
#else
    rt_base_t level;
    int second;
    rt_tick_t tick;
    rt_device_t device;

    if ((clockid != CLOCK_REALTIME) || (tp == RT_NULL))
    {
        rt_set_errno(EFAULT);
        return -1;
    }

    /* get second */
    second = tp->tv_sec;

    level = rt_hw_interrupt_disable();
    tick = rt_tick_get(); /* get tick */
    /* update timevalue */
    _timevalue.tv_usec = MICROSECOND_PER_SECOND - (tick % RT_TICK_PER_SECOND) * MICROSECOND_PER_TICK;
    _timevalue.tv_sec = second - tick / RT_TICK_PER_SECOND - 1;
    rt_hw_interrupt_enable(level);

    /* update for RTC device */
    device = rt_device_find("rtc");
    if (device != RT_NULL)
    {
        /* set realtime seconds */
        if(rt_device_control(device, RT_DEVICE_CTRL_RTC_SET_TIME, &second) == RT_EOK)
        {
            return 0;
        }
    }

    return -1;
#endif /* RT_USING_RTC */
}
RTM_EXPORT(clock_settime);

int rt_timespec_to_tick(const struct timespec *time)
{
    int tick;
    int nsecond, second;
    struct timespec tp = {0};

    RT_ASSERT(time != RT_NULL);

    tick = RT_WAITING_FOREVER;
    if (time != NULL)
    {
        /* get current tp */
        clock_gettime(CLOCK_REALTIME, &tp);

        if ((time->tv_nsec - tp.tv_nsec) < 0)
        {
            nsecond = NANOSECOND_PER_SECOND - (tp.tv_nsec - time->tv_nsec);
            second  = time->tv_sec - tp.tv_sec - 1;
        }
        else
        {
            nsecond = time->tv_nsec - tp.tv_nsec;
            second  = time->tv_sec - tp.tv_sec;
        }

        tick = second * RT_TICK_PER_SECOND + nsecond * RT_TICK_PER_SECOND / NANOSECOND_PER_SECOND;
        if (tick < 0) tick = 0;
    }

    return tick;
}
RTM_EXPORT(rt_timespec_to_tick);

#endif /* RT_USING_POSIX_CLOCK */

#ifdef RT_USING_POSIX_TIMER

#define ACTIVE 1
#define NOT_ACTIVE 0

struct timer_obj
{
    union
    {
        struct rt_timer timer;
#ifdef RT_USING_CPUTIME
        struct rt_cputimer cputimer;
#endif
    };
    void (*sigev_notify_function)(union sigval val);
    union sigval val;
    struct timespec interval;              /* Reload value */
    struct timespec value;                 /* Reload value */
    rt_uint64_t reload;                    /* Reload value in ms */
    rt_uint32_t status;
    int sigev_signo;
    clockid_t clockid;
#ifdef RT_USING_SMART
    pid_t pid;
#endif
};

static void rtthread_timer_wrapper(void *timerobj)
{
    struct timer_obj *timer;

    timer = (struct timer_obj *)timerobj;

    if (timer->reload == 0U)
    {
        timer->status = NOT_ACTIVE;
    }

#ifdef RT_USING_CPUTIME
    if (timer->clockid == CLOCK_CPUTIME_ID && clock_cpu_issettimeout())
    {
        timer->reload = ((timer->interval.tv_sec * NANOSECOND_PER_SECOND + timer->interval.tv_nsec) * (1000UL * 1000)) / clock_cpu_getres();
        if (timer->reload)
            rt_cputimer_control(&timer->cputimer, RT_TIMER_CTRL_SET_TIME, &(timer->reload));
    }
    else
#endif /* RT_USING_CPUTIME */
    {
        timer->reload = (timer->interval.tv_sec * RT_TICK_PER_SECOND) + (timer->interval.tv_nsec * RT_TICK_PER_SECOND) / NANOSECOND_PER_SECOND;
        if (timer->reload)
            rt_timer_control(&timer->timer, RT_TIMER_CTRL_SET_TIME, &(timer->reload));
    }

#ifdef RT_USING_SMART
    sys_kill(timer->pid, timer->sigev_signo);
#else
    if(timer->sigev_notify_function != RT_NULL)
    {
        (timer->sigev_notify_function)(timer->val);
    }
#endif
}

#define TIMER_ID_MAX 50
static struct timer_obj *_g_timerid[TIMER_ID_MAX];
static int timerid_idx = 0;
RT_DEFINE_SPINLOCK(_timer_id_lock);

void timer_id_init(void)
{
    for (int i = 0; i < TIMER_ID_MAX; i++)
    {
        _g_timerid[i] = NULL;
    }
    timerid_idx = 0;
}

int timer_id_alloc(void)
{
    for (int i = 0; i < timerid_idx; i++)
    {
        if (_g_timerid[i] == NULL)
            return i;
    }
    if (timerid_idx < TIMER_ID_MAX)
    {
        timerid_idx++;
        return timerid_idx; /* todo */
    }

    return -1;
}

void timer_id_lock()
{
    rt_hw_spin_lock(&_timer_id_lock);
}

void timer_id_unlock()
{
    rt_hw_spin_unlock(&_timer_id_lock);
}

struct timer_obj *timer_id_get(rt_ubase_t timerid)
{
    struct timer_obj *timer;

    if (timerid < 0 || timerid >= TIMER_ID_MAX)
    {
        return NULL;
    }

    timer_id_lock();
    if (_g_timerid[timerid] == NULL)
    {
        timer_id_unlock();
        LOG_E("can not find timer!");
        return NULL;
    }
    timer = _g_timerid[timerid];
    timer_id_unlock();
    return timer;
}

int timer_id_put(int id)
{
    if (_g_timerid[id] == NULL)
        return -1;
    _g_timerid[id] = NULL;
    return 0;
}
/**
 * @brief Create a per-process timer.
 *
 * This API does not accept SIGEV_THREAD as valid signal event notification
 * type.
 *
 * See IEEE 1003.1
 */
int timer_create(clockid_t clockid, struct sigevent *evp, timer_t *timerid)
{
    static int num = 0;
    int _timerid = 0;
    struct timer_obj *timer;
    char timername[RT_NAME_MAX] = {0};

    if (clockid > CLOCK_ID_MAX ||
        (evp->sigev_notify != SIGEV_NONE &&
         evp->sigev_notify != SIGEV_SIGNAL))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    timer = rt_malloc(sizeof(struct timer_obj));
    if(timer == RT_NULL)
    {
        rt_set_errno(ENOMEM);
        return -1;
    }

    rt_snprintf(timername, RT_NAME_MAX, "psx_tm%02d", num++);
    num %= 100;
    timer->sigev_signo = evp->sigev_signo;
#ifdef RT_USING_SMART
    timer->pid = lwp_self()->pid;
#endif
    timer->sigev_notify_function = evp->sigev_notify_function;
    timer->val = evp->sigev_value;
    timer->interval.tv_sec = 0;
    timer->interval.tv_nsec = 0;
    timer->reload = 0U;
    timer->status = NOT_ACTIVE;
    timer->clockid = clockid;

#ifdef RT_USING_CPUTIME
    if (timer->clockid == CLOCK_CPUTIME_ID && clock_cpu_issettimeout())
    {
        rt_cputimer_init(&timer->cputimer, timername, rtthread_timer_wrapper, timer, 0, RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_SOFT_TIMER);
    }
    else
#endif /* RT_USING_CPUTIME */
    {
        if (evp->sigev_notify == SIGEV_NONE)
            rt_timer_init(&timer->timer, timername, RT_NULL, RT_NULL, 0, RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_SOFT_TIMER);
        else
            rt_timer_init(&timer->timer, timername, rtthread_timer_wrapper, timer, 0, RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_SOFT_TIMER);
    }

    timer_id_lock();
    _timerid = timer_id_alloc();
    if (_timerid < 0)
    {
        timer_id_unlock();
        LOG_E("_timerid overflow!");
        return -1; /* todo:memory leak */
    }
    _g_timerid[_timerid] = timer;
    *timerid = (timer_t)(rt_ubase_t)_timerid;
    timer_id_unlock();

    return 0;
}
RTM_EXPORT(timer_create);

/**
 * @brief Delete a per-process timer.
 *
 * See IEEE 1003.1
 */
int timer_delete(timer_t timerid)
{
    struct timer_obj *timer;
    rt_ubase_t ktimerid;

    ktimerid = (rt_ubase_t)timerid;

    if (ktimerid < 0 || ktimerid >= TIMER_ID_MAX)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    timer_id_lock();
    if (_g_timerid[ktimerid] == NULL)
    {
        timer_id_unlock();
        rt_set_errno(EINVAL);
        LOG_E("can not find timer!");
        return -1;
    }
    timer = _g_timerid[ktimerid];
    timer_id_put(ktimerid);
    timer_id_unlock();
    if (timer == RT_NULL)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

#ifdef RT_USING_CPUTIME
    if (timer->clockid == CLOCK_CPUTIME_ID && clock_cpu_issettimeout())
    {
        if (timer->status == ACTIVE)
        {
            timer->status = NOT_ACTIVE;
            rt_cputimer_stop(&timer->cputimer);
        }
        rt_cputimer_detach(&timer->cputimer);
    }
    else
#endif /* RT_USING_CPUTIME */
    {
        if (timer->status == ACTIVE)
        {
            timer->status = NOT_ACTIVE;
            rt_timer_stop(&timer->timer);
        }
        rt_timer_detach(&timer->timer);
    }
    rt_free(timer);

    return 0;
}
RTM_EXPORT(timer_delete);

/**
 *
 *  Return the overrun count for the last timer expiration.
 *  It is subefficient to create a new structure to get overrun count.
 **/
int timer_getoverrun(timer_t timerid)
{
    rt_set_errno(ENOSYS);
    return -1;
}

/**
 * @brief Get amount of time left for expiration on a per-process timer.
 *
 * See IEEE 1003.1
 */
int timer_gettime(timer_t timerid, struct itimerspec *its)
{
    struct timer_obj *timer;
    rt_uint32_t seconds, nanoseconds;

    timer = timer_id_get((rt_ubase_t)timerid);

    if (timer == NULL)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    if (its == NULL)
    {
        rt_set_errno(EFAULT);
        return -1;
    }

    if (timer->status == ACTIVE)
    {
#ifdef RT_USING_CPUTIME
        if (timer->clockid == CLOCK_CPUTIME_ID && clock_cpu_issettimeout())
        {
            rt_uint64_t remain_tick;
            rt_uint64_t remaining;
            rt_cputimer_control(&timer->cputimer, RT_TIMER_CTRL_GET_REMAIN_TIME, &remain_tick);
            remaining = ((remain_tick - clock_cpu_gettime()) * (1000UL * 1000)) / clock_cpu_getres();
            seconds = remaining / NANOSECOND_PER_SECOND;
            nanoseconds = remaining % NANOSECOND_PER_SECOND;
        }
        else
#endif /* RT_USING_CPUTIME */
        {
            rt_tick_t remain_tick;
            rt_tick_t remaining;

            rt_timer_control(&timer->timer, RT_TIMER_CTRL_GET_REMAIN_TIME, &remain_tick);

            /* 'remain_tick' is minimum-unit in the RT-Thread' timer,
            * so the seconds, nanoseconds will be calculated by 'remain_tick'.
            */
            remaining = remain_tick - rt_tick_get();

            /* calculate 'second' */
            seconds = remaining / RT_TICK_PER_SECOND;

            /* calculate 'nanosecond';  To avoid lost of accuracy, because "RT_TICK_PER_SECOND" maybe 100, 1000, 1024 and so on.
            *
            *        remain_tick                  millisecond                                 remain_tick * MILLISECOND_PER_SECOND
            *  ------------------------- = --------------------------  --->  millisecond = -------------------------------------------
            *    RT_TICK_PER_SECOND          MILLISECOND_PER_SECOND                                RT_TICK_PER_SECOND
            *
            *                    remain_tick * MILLISECOND_PER_SECOND                          remain_tick * MILLISECOND_PER_SECOND * MICROSECOND_PER_SECOND
            *   millisecond = ----------------------------------------  ---> nanosecond = -------------------------------------------------------------------
            *                         RT_TICK_PER_SECOND                                                           RT_TICK_PER_SECOND
            *
            */
            nanoseconds = (((remaining % RT_TICK_PER_SECOND) * MILLISECOND_PER_SECOND) * MICROSECOND_PER_SECOND) / RT_TICK_PER_SECOND;
        }
        its->it_value.tv_sec = (rt_int32_t)seconds;
        its->it_value.tv_nsec = (rt_int32_t)nanoseconds;
    }
    else
    {
        /* Timer is disarmed */
        its->it_value.tv_sec = 0;
        its->it_value.tv_nsec = 0;
    }

    /* The interval last set by timer_settime() */
    its->it_interval = timer->interval;
    return 0;
}
RTM_EXPORT(timer_gettime);

/**
 * @brief Sets expiration time of per-process timer.
 *
 * See IEEE 1003.1
 */
int timer_settime(timer_t timerid, int flags, const struct itimerspec *value,
                  struct itimerspec *ovalue)
{
    struct timer_obj *timer = timer_id_get((rt_ubase_t)timerid);
    if (timer == NULL ||
        value->it_interval.tv_nsec < 0 ||
        value->it_interval.tv_nsec >= NANOSECOND_PER_SECOND ||
        value->it_interval.tv_sec < 0 ||
        value->it_value.tv_nsec < 0 ||
        value->it_value.tv_nsec >= NANOSECOND_PER_SECOND ||
        value->it_value.tv_sec < 0)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    /*  Save time to expire and old reload value. */
    if (ovalue != NULL)
    {
        timer_gettime(timerid, ovalue);
    }

    /* Stop the timer if the value is 0 */
    if ((value->it_value.tv_sec == 0) && (value->it_value.tv_nsec == 0))
    {
        if (timer->status == ACTIVE)
        {
#ifdef RT_USING_CPUTIME
            if (timer->clockid == CLOCK_CPUTIME_ID && clock_cpu_issettimeout())
                rt_cputimer_stop(&timer->cputimer);
            else
#endif /* RT_USING_CPUTIME */
                rt_timer_stop(&timer->timer);
        }

        timer->status = NOT_ACTIVE;
        return 0;
    }

    /* calculate timer period(tick);  To avoid lost of accuracy, because "RT_TICK_PER_SECOND" maybe 100, 1000, 1024 and so on.
        *
        *          tick                        nanosecond                          nanosecond * RT_TICK_PER_SECOND
        *  ------------------------- = --------------------------  --->  tick = -------------------------------------
        *    RT_TICK_PER_SECOND           NANOSECOND_PER_SECOND                         NANOSECOND_PER_SECOND
        *
        */
#ifdef RT_USING_CPUTIME
    if (timer->clockid == CLOCK_CPUTIME_ID && clock_cpu_issettimeout())
    {
        rt_uint64_t tick;
        uint64_t unit = clock_cpu_getres();

        tick = ((value->it_value.tv_sec * NANOSECOND_PER_SECOND + value->it_value.tv_nsec) * (1000UL * 1000)) / unit;
        if ((flags & TIMER_ABSTIME) == TIMER_ABSTIME)
        {
            tick -= clock_cpu_gettime();
        }
        timer->reload = tick;
    }
    else
#endif /* RT_USING_CPUTIME */
    {
        if ((flags & TIMER_ABSTIME) == TIMER_ABSTIME)
        {
#ifndef RT_USING_RTC
            LOG_W(_WARNING_NO_RTC);
            return -1;
#else
                rt_int64_t ts = ((value->it_value.tv_sec - _timevalue.tv_sec) * RT_TICK_PER_SECOND);
                rt_int64_t tns = (value->it_value.tv_nsec - _timevalue.tv_usec * 1000) * (RT_TICK_PER_SECOND / NANOSECOND_PER_SECOND);
                rt_int64_t reload = ts + tns;
                rt_tick_t rt_tick = rt_tick_get();

                timer->reload = reload < rt_tick ? 0 : reload - rt_tick;
#endif
        }
        else
            timer->reload = (value->it_value.tv_sec * RT_TICK_PER_SECOND) + value->it_value.tv_nsec * (RT_TICK_PER_SECOND / NANOSECOND_PER_SECOND);
    }
    timer->interval.tv_sec = value->it_interval.tv_sec;
    timer->interval.tv_nsec = value->it_interval.tv_nsec;
    timer->value.tv_sec = value->it_value.tv_sec;
    timer->value.tv_nsec = value->it_value.tv_nsec;

    if (timer->status == ACTIVE)
    {
#ifdef RT_USING_CPUTIME
        if (timer->clockid == CLOCK_CPUTIME_ID && clock_cpu_issettimeout())
            rt_cputimer_stop(&timer->cputimer);
        else
#endif /* RT_USING_CPUTIME */
            rt_timer_stop(&timer->timer);
    }

    timer->status = ACTIVE;

#ifdef RT_USING_CPUTIME
    if (timer->clockid == CLOCK_CPUTIME_ID && clock_cpu_issettimeout())
    {
        if ((value->it_interval.tv_sec == 0) && (value->it_interval.tv_nsec == 0))
            rt_cputimer_control(&timer->cputimer, RT_TIMER_CTRL_SET_ONESHOT, RT_NULL);
        else
            rt_cputimer_control(&timer->cputimer, RT_TIMER_CTRL_SET_PERIODIC, RT_NULL);

        rt_cputimer_control(&timer->cputimer, RT_TIMER_CTRL_SET_TIME, &(timer->reload));
        rt_cputimer_start(&timer->cputimer);
    }
    else
#endif /* RT_USING_CPUTIME */
    {
        if ((value->it_interval.tv_sec == 0) && (value->it_interval.tv_nsec == 0))
            rt_timer_control(&timer->timer, RT_TIMER_CTRL_SET_ONESHOT, RT_NULL);
        else
            rt_timer_control(&timer->timer, RT_TIMER_CTRL_SET_PERIODIC, RT_NULL);

        rt_timer_control(&timer->timer, RT_TIMER_CTRL_SET_TIME, &(timer->reload));
        rt_timer_start(&timer->timer);
    }

    return 0;
}
RTM_EXPORT(timer_settime);
#endif /* RT_USING_POSIX_TIMER */


/* timezone */
#ifndef RT_LIBC_DEFAULT_TIMEZONE
#define RT_LIBC_DEFAULT_TIMEZONE    8
#endif

static volatile int8_t _current_timezone = RT_LIBC_DEFAULT_TIMEZONE;

void tz_set(int8_t tz)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    _current_timezone = tz;
    rt_hw_interrupt_enable(level);
}

int8_t tz_get(void)
{
    return _current_timezone;
}

int8_t tz_is_dst(void)
{
    return 0;
}
