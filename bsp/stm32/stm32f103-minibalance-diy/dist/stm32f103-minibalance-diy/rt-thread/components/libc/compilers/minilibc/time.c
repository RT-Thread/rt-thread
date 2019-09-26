/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <time.h>
#include <rtthread.h>

/* days per month -- nonleap! */
const short __spm[13] =
{   0,
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
static long int timezone;
static const char days[] = "Sun Mon Tue Wed Thu Fri Sat ";
static const char months[] = "Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec ";

/* seconds per day */
#define SPD 24*60*60

int __isleap(int year)
{
    /* every fourth year is a leap year except for century years that are
     * not divisible by 400. */
    /*  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)); */
    return (!(year % 4) && ((year % 100) || !(year % 400)));
}

struct tm *gmtime_r(const time_t *timep, struct tm *r)
{
    time_t i;
    register time_t work = *timep % (SPD);
    r->tm_sec = work % 60;
    work /= 60;
    r->tm_min = work % 60;
    r->tm_hour = work / 60;
    work = *timep / (SPD);
    r->tm_wday = (4 + work) % 7;
    for (i = 1970;; ++i)
    {
        register time_t k = __isleap(i) ? 366 : 365;
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

    for (i = 11; i && (__spm[i] > work); --i)
        ;
    r->tm_mon = i;
    r->tm_mday += work - __spm[i];
    return r;
}

struct tm* localtime_r(const time_t* t, struct tm* r)
{
    time_t tmp;
    struct timezone tz = {0};
    gettimeofday(0, &tz);
    timezone = tz.tz_minuteswest * 60L;
    tmp = *t + timezone;
    return gmtime_r(&tmp, r);
}

struct tm* localtime(const time_t* t)
{
    static struct tm tmp;
    return localtime_r(t, &tmp);
}

time_t mktime(struct tm * const t)
{
    register time_t day;
    register time_t i;
    register time_t years = t->tm_year - 70;

    if (t->tm_sec > 60)
    {
        t->tm_min += t->tm_sec / 60;
        t->tm_sec %= 60;
    }
    if (t->tm_min > 60)
    {
        t->tm_hour += t->tm_min / 60;
        t->tm_min %= 60;
    }
    if (t->tm_hour > 24)
    {
        t->tm_mday += t->tm_hour / 24;
        t->tm_hour %= 24;
    }
    if (t->tm_mon > 12)
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
        return (time_t) - 1;

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
    t->tm_wday = (day + 4) % i; /* Sunday=0, Monday=1, ..., Saturday=6 */

    i = 24;
    day *= i;
    i = 60;
    return ((day + t->tm_hour) * i + t->tm_min) * i + t->tm_sec;
}

static void num2str(char *c, int i)
{
    c[0] = i / 10 + '0';
    c[1] = i % 10 + '0';
}

char *asctime_r(const struct tm *t, char *buf)
{
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
    return buf;
}

char *asctime(const struct tm *timeptr)
{
    static char buf[25];
    return asctime_r(timeptr, buf);
}

char *ctime(const time_t *timep)
{
    return asctime(localtime(timep));
}

#ifdef RT_USING_DEVICE
int gettimeofday(struct timeval *tp, void *ignore)
{
    time_t time;
    rt_device_t device;

    device = rt_device_find("rtc");
    RT_ASSERT(device != RT_NULL);

    rt_device_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &time);
    if (tp != RT_NULL)
    {
        tp->tv_sec = time;
        tp->tv_usec = 0;
    }

    return time;
}
#endif

#ifndef _gettimeofday
/* Dummy function when hardware do not have RTC */
int _gettimeofday( struct timeval *tv, void *ignore)
{
    tv->tv_sec = 0;  // convert to seconds
    tv->tv_usec = 0;  // get remaining microseconds
    return 0;  // return non-zero for error
}
#endif

/**
 * Returns the current time.
 *
 * @param time_t * t the timestamp pointer, if not used, keep NULL.
 *
 * @return time_t return timestamp current.
 *
 */
/* for IAR 6.2 later Compiler */
#if defined (__IAR_SYSTEMS_ICC__) &&  (__VER__) >= 6020000
#pragma module_name = "?time"
time_t (__time32)(time_t *t) /* Only supports 32-bit timestamp */
#else
time_t time(time_t *t)
#endif
{
    time_t time_now = 0;

#ifdef RT_USING_RTC
    static rt_device_t device = RT_NULL;

    /* optimization: find rtc device only first. */
    if (device == RT_NULL)
    {
        device = rt_device_find("rtc");
    }

    /* read timestamp from RTC device. */
    if (device != RT_NULL)
    {
        if (rt_device_open(device, 0) == RT_EOK)
        {
            rt_device_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &time_now);
            rt_device_close(device);
        }
    }
#endif /* RT_USING_RTC */

    /* if t is not NULL, write timestamp to *t */
    if (t != RT_NULL)
    {
        *t = time_now;
    }

    return time_now;
}

RT_WEAK clock_t clock(void)
{
    return rt_tick_get();
}
