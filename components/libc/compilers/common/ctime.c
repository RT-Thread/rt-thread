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
 * 2023-07-03     xqyjlj       refactor posix time and timer
 * 2023-07-16     Shell        update signal generation routine for lwp
 *                             adapt to new api and do the signal handling in thread context
 */

#include "sys/time.h"
#include <rthw.h>
#include <rtdevice.h>
#include <drivers/rtc.h>
#include <sys/errno.h>
#include <unistd.h>
#ifdef RT_USING_SMART
#include <lwp.h>
#endif
#ifdef RT_USING_POSIX_DELAY
#include <delay.h>
#endif
#ifdef RT_USING_KTIME
#include <ktime.h>
#endif

#define DBG_TAG    "time"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#define _WARNING_NO_RTC "Cannot find a RTC device!"

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

rt_align(RT_ALIGN_SIZE) static const char *days = "Sun Mon Tue Wed Thu Fri Sat ";
rt_align(RT_ALIGN_SIZE) static const char *months = "Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec ";

#ifndef __isleap
static int __isleap(int year)
{
    /* every fourth year is a leap year except for century years that are
     * not divisible by 400. */
    /*  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)); */
    return (!(year % 4) && ((year % 100) || !(year % 400)));
}
#endif

static void num2str(char *c, int i)
{
    c[0] = i / 10 + '0';
    c[1] = i % 10 + '0';
}

static rt_err_t _control_rtc(int cmd, void *arg)
{
#ifdef RT_USING_RTC
    static rt_device_t device = RT_NULL;
    rt_err_t rst = -RT_ERROR;

    if (device == RT_NULL)
    {
        device = rt_device_find("rtc");
    }

    /* read timestamp from RTC device */
    if (device != RT_NULL)
    {
        if (rt_device_open(device, 0) == RT_EOK)
        {
            rst = rt_device_control(device, cmd, arg);
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
    int work;

    if(timep == RT_NULL || r == RT_NULL)
    {
        rt_set_errno(EFAULT);
        return RT_NULL;
    }

    rt_memset(r, RT_NULL, sizeof(struct tm));

    work = *timep % (24*60*60);
    r->tm_sec = work % 60;
    work /= 60;
    r->tm_min = work % 60;
    r->tm_hour = work / 60;
    work = (int)(*timep / (24*60*60));
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

char *asctime(const struct tm *timeptr)
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

char *ctime(const time_t *tim_p)
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
    time_t _t;

    if (_control_rtc(RT_DEVICE_CTRL_RTC_GET_TIME, &_t) != RT_EOK)
    {
        rt_set_errno(EFAULT);
        return (time_t)-1;
    }

    if (t)
        *t = _t;

    return _t;
}
RTM_EXPORT(time);

rt_weak clock_t clock(void)
{
    return rt_tick_get();  // TODO should return cpu usage time
}
RTM_EXPORT(clock);

int stime(const time_t *t)
{
    if ((t != RT_NULL) && (_control_rtc(RT_DEVICE_CTRL_RTC_SET_TIME, (void *)t) == RT_EOK))
    {
        return 0;
    }

    rt_set_errno(EFAULT);
    return -1;
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

    if (tv != RT_NULL)
    {
        tv->tv_sec  = 0;
        tv->tv_usec = 0;

        if (_control_rtc(RT_DEVICE_CTRL_RTC_GET_TIMEVAL, tv) == RT_EOK)
            return 0;
    }

    rt_set_errno(EINVAL);
    return -1;
}
RTM_EXPORT(gettimeofday);

int settimeofday(const struct timeval *tv, const struct timezone *tz)
{
    /* The use of the timezone structure is obsolete;
     * the tz argument should normally be specified as NULL.
     * The tz_dsttime field has never been used under Linux.
     * Thus, the following is purely of historic interest.
     */
    if (tv != RT_NULL && (long)tv->tv_usec >= 0 && (long)tv->tv_sec >= 0)
    {
        if (_control_rtc(RT_DEVICE_CTRL_RTC_SET_TIMEVAL, (void *)tv) == RT_EOK)
            return 0;
    }

    rt_set_errno(EINVAL);
    return -1;
}
RTM_EXPORT(settimeofday);

#if defined(RT_USING_POSIX_DELAY) && defined(RT_USING_KTIME)
int nanosleep(const struct timespec *rqtp, struct timespec *rmtp)
{
    struct timespec old_ts = {0};
    struct timespec new_ts = {0};

    if (rqtp == RT_NULL)
    {
        rt_set_errno(EFAULT);
        return -1;
    }

    if (rqtp->tv_sec < 0 || rqtp->tv_nsec < 0 || rqtp->tv_nsec >= NANOSECOND_PER_SECOND)
    {
        rt_set_errno(EINVAL);
        return -1;
    }
    unsigned long ns = rqtp->tv_sec * NANOSECOND_PER_SECOND + rqtp->tv_nsec;
    rt_ktime_boottime_get_ns(&old_ts);
    rt_ktime_hrtimer_ndelay(ns);
    if (rt_get_errno() == -RT_EINTR)
    {
        if (rmtp)
        {
            rt_ktime_boottime_get_ns(&new_ts);

            rmtp->tv_sec = 0;
            rmtp->tv_nsec =
                (old_ts.tv_nsec + ns) - ((new_ts.tv_sec - old_ts.tv_sec) * NANOSECOND_PER_SECOND + new_ts.tv_nsec);

            if (rmtp->tv_nsec > NANOSECOND_PER_SECOND)
            {
                rmtp->tv_nsec %= NANOSECOND_PER_SECOND;
                rmtp->tv_sec += rmtp->tv_nsec / NANOSECOND_PER_SECOND;
            }
        }
        rt_set_errno(EINTR);
        return -1;
    }
    return 0;
}
RTM_EXPORT(nanosleep);
#endif /* RT_USING_POSIX_DELAY && RT_USING_KTIME */

#if defined(RT_USING_POSIX_CLOCK) && defined(RT_USING_KTIME)

int clock_getres(clockid_t clockid, struct timespec *res)
{
    if (res == RT_NULL)
    {
        rt_set_errno(EFAULT);
        return -1;
    }

    switch (clockid)
    {
        case CLOCK_REALTIME:  // use RTC
        case CLOCK_REALTIME_COARSE:
            return _control_rtc(RT_DEVICE_CTRL_RTC_GET_TIMERES, res);

        case CLOCK_MONOTONIC:  // use cputimer
        case CLOCK_MONOTONIC_COARSE:
        case CLOCK_MONOTONIC_RAW:
        case CLOCK_BOOTTIME:
        case CLOCK_PROCESS_CPUTIME_ID:
        case CLOCK_THREAD_CPUTIME_ID:
            res->tv_sec  = 0;
            res->tv_nsec = (rt_ktime_cputimer_getres() / RT_KTIME_RESMUL);
            return 0;

        default:
            rt_set_errno(EINVAL);
            return -1;
    }
}
RTM_EXPORT(clock_getres);

int clock_gettime(clockid_t clockid, struct timespec *tp)
{
    if (tp == RT_NULL)
    {
        rt_set_errno(EFAULT);
        return -1;
    }

    switch (clockid)
    {
        case CLOCK_REALTIME:  // use RTC
        case CLOCK_REALTIME_COARSE:
            return _control_rtc(RT_DEVICE_CTRL_RTC_GET_TIMESPEC, tp);

        case CLOCK_MONOTONIC:  // use boottime
        case CLOCK_MONOTONIC_COARSE:
        case CLOCK_MONOTONIC_RAW:
        case CLOCK_BOOTTIME:
            return rt_ktime_boottime_get_ns(tp);

        case CLOCK_PROCESS_CPUTIME_ID:
        case CLOCK_THREAD_CPUTIME_ID:
            return rt_ktime_boottime_get_ns(tp);  // TODO not yet implemented

        default:
            tp->tv_sec  = 0;
            tp->tv_nsec = 0;
            rt_set_errno(EINVAL);
            return -1;
    }
}
RTM_EXPORT(clock_gettime);

int clock_nanosleep(clockid_t clockid, int flags, const struct timespec *rqtp, struct timespec *rmtp)
{
    struct timespec ts = {0};
    rt_err_t        err;

    if (rqtp == RT_NULL)
    {
        rt_set_errno(EFAULT);
        return -1;
    }

    if (rqtp->tv_sec < 0 || rqtp->tv_nsec < 0 || rqtp->tv_nsec >= NANOSECOND_PER_SECOND)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    switch (clockid)
    {
        case CLOCK_REALTIME:  // use RTC
            if (flags & TIMER_ABSTIME)
                err = _control_rtc(RT_DEVICE_CTRL_RTC_GET_TIMESPEC, &ts);
            break;

        case CLOCK_MONOTONIC:  // use boottime
        case CLOCK_PROCESS_CPUTIME_ID:
            if (flags & TIMER_ABSTIME)
                err = rt_ktime_boottime_get_ns(&ts);
            break;

        default:
            rt_set_errno(EINVAL);
            return -1;
    }

    if (err != RT_EOK)
        return err;

    int64_t ns = rqtp->tv_nsec - ts.tv_nsec + (rqtp->tv_sec - ts.tv_sec) * NANOSECOND_PER_SECOND;
    if (ns <= 0)
        return 0;

    if (flags & TIMER_ABSTIME)
    {
        ts.tv_nsec = ns % NANOSECOND_PER_SECOND;
        ts.tv_sec  = ns / NANOSECOND_PER_SECOND;
        return nanosleep(&ts, rmtp);
    }
    else
    {
        return nanosleep(rqtp, rmtp);
    }
}
RTM_EXPORT(clock_nanosleep);

int clock_settime(clockid_t clockid, const struct timespec *tp)
{
    if (tp == RT_NULL)
    {
        rt_set_errno(EFAULT);
        return -1;
    }

    if (tp->tv_sec < 0 || tp->tv_nsec < 0 || tp->tv_nsec >= NANOSECOND_PER_SECOND)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    switch (clockid)
    {
        case CLOCK_REALTIME:
            return _control_rtc(RT_DEVICE_CTRL_RTC_SET_TIMESPEC, (void *)tp);

        case CLOCK_REALTIME_COARSE:
        case CLOCK_MONOTONIC:
        case CLOCK_MONOTONIC_COARSE:
        case CLOCK_MONOTONIC_RAW:
        case CLOCK_BOOTTIME:
        case CLOCK_PROCESS_CPUTIME_ID:
        case CLOCK_THREAD_CPUTIME_ID:
            rt_set_errno(EPERM);
            return -1;

        default:
            rt_set_errno(EINVAL);
            return -1;
    }
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

#endif /* RT_USING_POSIX_CLOCK && RT_USING_KTIME */

#if defined(RT_USING_POSIX_TIMER) && defined(RT_USING_KTIME)

#include <resource_id.h>

#define ACTIVE 1
#define NOT_ACTIVE 0

struct timer_obj
{
    struct rt_ktime_hrtimer hrtimer;
    void (*sigev_notify_function)(union sigval val);
    union sigval val;
    struct timespec interval;              /* Reload value */
    struct timespec value;                 /* Reload value */
    unsigned long reload;                    /* Reload value in ms */
    rt_uint32_t status;
    int sigev_signo;
    clockid_t clockid;
    timer_t timer_id;
#ifdef RT_USING_SMART
    pid_t pid;
    struct rt_work *work;
    rt_list_t lwp_node;
#endif
};

#ifdef RT_USING_SMART
struct lwp_timer_event_param
{
    struct rt_work work;

    union
    {
        int tid;
        pid_t pid;
    };
    int signo;
};

static void _lwp_timer_event_from_tid(struct rt_work *work, void *param)
{
    rt_err_t ret;
    struct lwp_timer_event_param *data = rt_container_of(work, struct lwp_timer_event_param, work);
    rt_thread_t thread;

    RT_ASSERT(data->tid);

    thread = lwp_tid_get_thread(data->tid);
    ret = lwp_thread_signal_kill(thread, data->signo, SI_TIMER, 0);
    if (ret)
    {
        LOG_W("%s: Do kill failed(tid %d) returned %d", __func__, data->tid, ret);
    }
}

static void _lwp_timer_event_from_pid(struct rt_work *work, void *param)
{
    rt_err_t ret;
    struct lwp_timer_event_param *data = rt_container_of(work, struct lwp_timer_event_param, work);

    ret = lwp_signal_kill(lwp_from_pid(data->pid), data->signo, SI_TIMER, 0);
    if (ret)
    {
        LOG_W("%s: Do kill failed(pid %d) returned %d", __func__, data->pid, ret);
    }
}

int timer_list_free(rt_list_t *timer_list)
{
    struct timer_obj *pos, *n;
    rt_list_for_each_entry_safe(pos, n, timer_list, lwp_node)
    {
        timer_delete(pos->timer_id);
    }
    return 0;
}

#endif /* RT_USING_SMART */

static void rtthread_timer_wrapper(void *timerobj)
{
    struct timer_obj *timer;

    timer = (struct timer_obj *)timerobj;

    if (timer->reload == 0U)
    {
        timer->status = NOT_ACTIVE;
    }

    timer->reload = ((timer->interval.tv_sec * NANOSECOND_PER_SECOND + timer->interval.tv_nsec) * RT_KTIME_RESMUL) /
                    rt_ktime_cputimer_getres();
    if (timer->reload)
    {
        rt_ktime_hrtimer_control(&timer->hrtimer, RT_TIMER_CTRL_SET_TIME, &(timer->reload));
        rt_ktime_hrtimer_start(&timer->hrtimer);
    }
#ifdef RT_USING_SMART
    /* this field is named as tid in musl */
    int tid = *(int *)&timer->sigev_notify_function;
    struct lwp_timer_event_param *data = rt_container_of(timer->work, struct lwp_timer_event_param, work);
    data->signo = timer->sigev_signo;

    if (!tid)
    {
        data->pid = timer->pid;
        rt_work_init(timer->work, _lwp_timer_event_from_pid, 0);
    }
    else
    {
        data->tid = tid;
        rt_work_init(timer->work, _lwp_timer_event_from_tid, 0);
    }

    if (rt_work_submit(timer->work, 0))
        RT_ASSERT(0);
#else
    if(timer->sigev_notify_function != RT_NULL)
    {
        (timer->sigev_notify_function)(timer->val);
    }
#endif /* RT_USING_SMART */
}

#define TIMER_ID_MAX 50
static struct timer_obj *_g_timerid[TIMER_ID_MAX];
static void *timer_id[TIMER_ID_MAX];
static resource_id_t id_timer = RESOURCE_ID_INIT(TIMER_ID_MAX, timer_id);

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

    if (evp == RT_NULL || timerid == RT_NULL)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    if (evp->sigev_notify == SIGEV_THREAD)  // TODO need to implement
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    switch (clockid)
    {
        case CLOCK_REALTIME:
        case CLOCK_REALTIME_ALARM:
        case CLOCK_MONOTONIC:
        case CLOCK_BOOTTIME:
        case CLOCK_BOOTTIME_ALARM:
        case CLOCK_PROCESS_CPUTIME_ID:
        case CLOCK_THREAD_CPUTIME_ID:
            break;  // Only these ids are supported
        default:
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
    struct rt_work *work;
    struct rt_lwp *lwp = lwp_self();
    struct lwp_timer_event_param *param;
    param = rt_malloc(sizeof(struct lwp_timer_event_param));
    work = &param->work;

    if (!work)
    {
        rt_set_errno(ENOMEM);
        return -1;
    }

    if (lwp)
    {
        timer->pid = lwp_self()->pid;
        rt_list_insert_after(&lwp->timer, &timer->lwp_node);
    }
    else
    {
        timer->pid = 0; /* pid 0 is never used */
    }

    timer->work = work;
#endif /* RT_USING_SMART */
    timer->sigev_notify_function = evp->sigev_notify_function;
    timer->val = evp->sigev_value;
    timer->interval.tv_sec = 0;
    timer->interval.tv_nsec = 0;
    timer->reload = 0U;
    timer->status = NOT_ACTIVE;
    timer->clockid = clockid;

    rt_ktime_hrtimer_init(&timer->hrtimer, timername, 0, RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_HARD_TIMER,
                          rtthread_timer_wrapper, timer);

    _timerid = resource_id_get(&id_timer);
    if (_timerid < 0)
    {
        LOG_E("_timerid overflow!");
        return -1; /* todo:memory leak */
    }
    _g_timerid[_timerid] = timer;

    timer->timer_id = (timer_t)(rt_ubase_t)_timerid;
    *timerid = (timer_t)(rt_ubase_t)_timerid;

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

    if (_g_timerid[ktimerid] == NULL)
    {
        rt_set_errno(EINVAL);
        LOG_E("can not find timer!");
        return -1;
    }
    timer = _g_timerid[ktimerid];
    resource_id_put(&id_timer, ktimerid);
    if (timer == RT_NULL)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    if (timer->status == ACTIVE)
    {
        timer->status = NOT_ACTIVE;
        rt_ktime_hrtimer_stop(&timer->hrtimer);
    }
    rt_ktime_hrtimer_detach(&timer->hrtimer);

#ifdef RT_USING_SMART
    if (timer->pid)
        rt_list_remove(&timer->lwp_node);
    rt_free(timer->work);
#endif
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

    timer = _g_timerid[(rt_ubase_t)timerid];

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
        unsigned long remain_cnt;
        rt_ktime_hrtimer_control(&timer->hrtimer, RT_TIMER_CTRL_GET_REMAIN_TIME, &remain_cnt);
        nanoseconds = ((remain_cnt - rt_ktime_cputimer_getcnt()) * rt_ktime_cputimer_getres()) / RT_KTIME_RESMUL;
        seconds     = nanoseconds / NANOSECOND_PER_SECOND;
        nanoseconds = nanoseconds % NANOSECOND_PER_SECOND;
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
    struct timespec ts = {0};
    rt_err_t        err = RT_EOK;

    struct timer_obj *timer;
    timer = _g_timerid[(rt_ubase_t)timerid];
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
            rt_ktime_hrtimer_stop(&timer->hrtimer);
        }

        timer->status = NOT_ACTIVE;
        return 0;
    }

    switch (timer->clockid)
    {
        case CLOCK_REALTIME:
        case CLOCK_REALTIME_ALARM:
            if (flags & TIMER_ABSTIME)
                err = _control_rtc(RT_DEVICE_CTRL_RTC_GET_TIMESPEC, &ts);
            break;
        case CLOCK_MONOTONIC:
        case CLOCK_BOOTTIME:
        case CLOCK_BOOTTIME_ALARM:
        case CLOCK_PROCESS_CPUTIME_ID:
        case CLOCK_THREAD_CPUTIME_ID:
            if (flags & TIMER_ABSTIME)
                err = rt_ktime_boottime_get_ns(&ts);
            break;
        default:
            rt_set_errno(EINVAL);
            return -1;
    }

    if (err != RT_EOK)
        return err;

    int64_t ns = value->it_value.tv_nsec - ts.tv_nsec + (value->it_value.tv_sec - ts.tv_sec) * NANOSECOND_PER_SECOND;

    if (ns <= 0)
        return 0;

    unsigned long res       = rt_ktime_cputimer_getres();
    timer->reload           = (ns * RT_KTIME_RESMUL) / res;
    timer->interval.tv_sec  = value->it_interval.tv_sec;
    timer->interval.tv_nsec = value->it_interval.tv_nsec;
    timer->value.tv_sec     = value->it_value.tv_sec;
    timer->value.tv_nsec    = value->it_value.tv_nsec;

    if (timer->status == ACTIVE)
    {
        rt_ktime_hrtimer_stop(&timer->hrtimer);
    }
    timer->status = ACTIVE;

    if ((value->it_interval.tv_sec == 0) && (value->it_interval.tv_nsec == 0))
        rt_ktime_hrtimer_control(&timer->hrtimer, RT_TIMER_CTRL_SET_ONESHOT, RT_NULL);
    else
        rt_ktime_hrtimer_control(&timer->hrtimer, RT_TIMER_CTRL_SET_PERIODIC, RT_NULL);

    rt_ktime_hrtimer_control(&timer->hrtimer, RT_TIMER_CTRL_SET_TIME, &(timer->reload));
    rt_ktime_hrtimer_start(&timer->hrtimer);

    return 0;
}
RTM_EXPORT(timer_settime);
#endif /* RT_USING_POSIX_TIMER && RT_USING_KTIME */


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
