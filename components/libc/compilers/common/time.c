/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
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
 */

#include <sys/time.h>
#include <rtthread.h>
#ifdef RT_USING_DEVICE
#include <rtdevice.h>
#endif

/* seconds per day */
#define SPD 24*60*60

/* days per month -- nonleap! */
const short __spm[13] =
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

ALIGN(4) static const char days[] = "Sun Mon Tue Wed Thu Fri Sat ";
ALIGN(4) static const char months[] = "Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec ";

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

    r->tm_isdst = 0;
    return r;
}

struct tm* gmtime(const time_t* t)
{
    static struct tm tmp;
    return gmtime_r(t, &tmp);
}

/*TODO: timezone */
struct tm* localtime_r(const time_t* t, struct tm* r)
{
    time_t local_tz;
    int utc_plus;

    utc_plus = 0; /* GTM: UTC+0 */
    local_tz = *t + utc_plus * 3600;
    return gmtime_r(&local_tz, r);
}

struct tm* localtime(const time_t* t)
{
    static struct tm tmp;
    return localtime_r(t, &tmp);
}

/* TODO: timezone */
time_t mktime(struct tm * const t)
{
    return timegm(t);
}

char* asctime_r(const struct tm *t, char *buf)
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

char* asctime(const struct tm *timeptr)
{
    static char buf[25];
    return asctime_r(timeptr, buf);
}

char *ctime_r (const time_t * tim_p, char * result)
{
  struct tm tm;
  return asctime_r (localtime_r (tim_p, &tm), result);
}

char* ctime(const time_t *tim_p)
{
    return asctime (localtime (tim_p));
}

/**
 * Returns the current time.
 *
 * @param time_t * t the timestamp pointer, if not used, keep NULL.
 *
 * @return time_t return timestamp current.
 *
 */
RT_WEAK time_t time(time_t *t)
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

int stime(const time_t *t)
{
#ifdef RT_USING_RTC
    rt_device_t device;

    /* read timestamp from RTC device. */
    device = rt_device_find("rtc");
    if (rt_device_open(device, 0) == RT_EOK)
    {
        rt_device_control(device, RT_DEVICE_CTRL_RTC_SET_TIME, (void*)t);
        rt_device_close(device);
    }
    else
    {
        return -1;
    }
    return 0;

#else
    return -1;
#endif /* RT_USING_RTC */
}

time_t timegm(struct tm * const t)
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

/* TODO: timezone */
int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    if (tv != RT_NULL)
    {
        tv->tv_sec = time(RT_NULL);
        tv->tv_usec = 0;
        return 0;
    }
    else
    {
        return -1;
    }
}

/* TODO: timezone */
int settimeofday(const struct timeval *tv, const struct timezone *tz)
{
    if (tv != RT_NULL)
    {
        return stime((const time_t *)&tv->tv_sec);
    }
    else
    {
        return -1;
    }
}
