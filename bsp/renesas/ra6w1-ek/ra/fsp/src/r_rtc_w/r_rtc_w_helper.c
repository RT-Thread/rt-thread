/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <string.h>
#include <stdio.h>

#include "bsp_rtc.h"
#include "r_rtc_w.h"
#include "r_rtc_w_helper.h"

#define RTC_OVERFLOW               0xFFFFFFFFFULL /* Real RTC Counter 36bit */
#define RTC_OVERFLOW_STACK_SIZE    256

#define _INT_MAX                   ((int) (~0U >> 1))
#define _INT_MIN                   (-_INT_MAX - 1)
#define WDAY                       1   /* to get day of week right */

/* Bias between 1900 (struct tm) and 1970 time_t. */
#define _TBIAS_DAYS                (70 * 365L + 17)
#define _TBIAS                     (_TBIAS_DAYS * 86400LU)

/* macros */
#define MONTAB(year)    ((year) & 03 || (year) == 0 ? mos : lmos)

/* from retmem.h */
#define CLK2US(clk)     ((((unsigned long long) clk) * 15625ULL) >> 9ULL)
#define CLK2MS(clk)     ((CLK2US(clk)) / 1000ULL)
#define CLK2SEC(clk)    (((unsigned long long) clk) >> 15ULL)
#define US2CLK(us)      ((((unsigned long long) us) << 9ULL) / 15625ULL)
#define SEC2CLK(clk)    (((unsigned long long) clk) << 15ULL)

/* static data */
static const short lmos[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
static const short mos[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

static struct tm _Ttotm_ts = {0};

static void set_systimeoffset_to_rtm (unsigned long long offset)
{
    RTM_TIME_PTR->systime_offset = offset;
}

static unsigned long long get_rtc_oldtime_from_rtm (void)
{
    return (unsigned long long) (RTM_TIME_PTR->rtc_oldtime);
}

static unsigned long long get_systimeoffset_from_rtm (void)
{
    return (unsigned long long) RTM_TIME_PTR->systime_offset;
}

static void set_rtc_oldtime_to_rtm (unsigned long long time)
{
    RTM_TIME_PTR->rtc_oldtime = time;
}

void ra6w1_SetTzoff (long offset)
{
    RTM_TIME_PTR->__timezone = offset;
}

long ra6w1_Tzoff (void)
{
    return RTM_TIME_PTR->__timezone;
}

static int ra6w1_Daysto64 (int year, int mon)
{
    /* year >= 1900: leapdays from 1900 up to (not including) year plus
     *  days to start of month.
     * year <  1900: leapdays backwards from 1900 down to (including)
     * year (negative) plus days to start of month from year. */
    int days;
    int y, ly;

    if (year >= 0)
    {
        y  = year - 1;
        ly = y + 300;
    }
    else
    {
        y  = year;
        ly = y - 100;
    }

    days  = y / 4;
    days -= y / 100;
    days += ly / 400;

    return days + MONTAB(year)[mon];
}

#define __isleap(y)    (!((y) % 4) && (((y) % 100) || !((y) % 400)))

static struct tm * ra6w1_Ttotm64 (struct tm * t, __time64_t secsarg, int isdst)
{
    /* Convert scalar time to time structure */
    int              year;
    long             days;
    signed long long secs;

    secsarg += _TBIAS;                 /* Changed to (wraparound) time since 1 Jan 1900 */

    if (t == 0)
    {
        t = &_Ttotm_ts;
        memset(t, 0x00, sizeof(struct tm));
    }

    t->tm_isdst = isdst;

    /* Loop to correct for DST */
    for (secs = (signed long long) secsarg; ; secs = (signed long long) secsarg + 3600)
    {
        /* If secs are negative we want to get a negative year that we then add
         * month, day, etc to */
        days = (long) (secs / 86400);
        secs = secs % 86400;

        if (secs < 0)
        {
            days--;
            secs += 86400;
        }

        t->tm_wday = (days + WDAY) % 7;

        if (t->tm_wday < 0)
        {
            t->tm_wday += 7;
        }

        /* Determine year */
        long i;
        year = days / 365;

        while (1)
        {
            i = ra6w1_Daysto64(year, 0) + 365L * year;

            if (days < i)
            {
                --year;                /* Correct guess and recheck */
                continue;
            }

            if (days <= (i + 365))
            {
                break;
            }

            if ((days == (i + 366)) && __isleap(year + 1900))
            {
                break;
            }

            ++year;
        }

        days      -= i;
        t->tm_year = year;
        t->tm_yday = days;

        {
            /* Determine month */
            int           mon;
            const short * pm = MONTAB(year);

            for (mon = 12; days < pm[--mon]; )
            {
                ;
            }

            t->tm_mon  = mon;
            t->tm_mday = days - pm[mon] + 1;
        }

        t->tm_hour = (int) (secs / 3600);
        secs      %= 3600;
        t->tm_min  = (int) (secs / 60);
        t->tm_sec  = (int) (secs % 60);

        return t;                      /* Loop only if <0 => 1 */
    }

    return NULL;
}

void ra6w1_mktime64 (struct tm * t, __time64_t * now)
{
    /* Convert local time structure to scalar time */
    long       cdays, csecs;
    int        mon, year, ymon;
    __time64_t secs;

    ymon = t->tm_mon / 12;
    mon  = t->tm_mon - ymon * 12;

    if (mon < 0)
    {
        mon += 12, --ymon;
    }

    if (((ymon < 0) && (t->tm_year < _INT_MIN - ymon)) || ((0 < ymon) && (_INT_MAX - ymon < t->tm_year)))
    {
        *now = ((__time64_t) (-1));

        return;
    }

    year = t->tm_year + ymon;

    /* Note that this is correct even with a 32 bit double. */

    /* Calculate number of days. */
    cdays  = ra6w1_Daysto64(year, mon) - 1;
    cdays += 365L * year;
    cdays += t->tm_mday;

    /* Calculate number of seconds. */
    cdays += t->tm_hour / 24;
    csecs  = 3600L * (t->tm_hour % 24);
    cdays += t->tm_min / (24 * 60);
    csecs += 60L * (t->tm_min % (24 * 60));
    cdays += t->tm_sec / 86400L;
    csecs += t->tm_sec % 86400L;

    /* Change from 1900 into 1970 representation. */
    cdays -= _TBIAS_DAYS;

    /* Add them together to get seconds since 1970. */
    secs = (__time64_t) cdays * 86400L + (__time64_t) csecs;

    ra6w1_Ttotm64(t, secs, t->tm_isdst);

    if (0 < t->tm_isdst)
    {
        secs -= 3600;
    }

    *now = (secs - (__time64_t) ra6w1_Tzoff());
}

static void ra6w1_time64_msec (__time64_t * p, __time64_t * cur_msec)
{
    unsigned long long time_ms;
    unsigned long long rtc;

    /* rtc is retained when SW reset, reset when POR */
    rtc = R_BSP_SystemRtcCountGet();

    time_ms = CLK2MS(rtc);             /* Elapsed time from Power On in msec */

    if (p != NULL)
    {
        /* msec : (time value to set) - (Elapsed time from Power On) */
        set_systimeoffset_to_rtm((unsigned long long) ((*p) * 1000ULL - time_ms));
    }
    else if ((get_rtc_oldtime_from_rtm() != 0) && (get_rtc_oldtime_from_rtm() > time_ms)) /* Check Overflow */
    {
        unsigned long long offset;

        offset = CLK2MS(RTC_OVERFLOW + 1ULL);                                             // Overflow time

        /* RTC overflow 36bit + old offset = Elapsed time from Power On */
        set_systimeoffset_to_rtm(offset + get_systimeoffset_from_rtm());                  /* newoffset */
    }

    set_rtc_oldtime_to_rtm(time_ms);

    time_ms   = time_ms + (unsigned long long) get_systimeoffset_from_rtm();
    *cur_msec = time_ms;               /* msec */
}

static void ra6w1_time64_sec (__time64_t * p, __time64_t * cur_sec)
{
    __time64_t cur_msec;

    ra6w1_time64_msec(p, &cur_msec);
    if ((long long) cur_msec < 0)
    {
        *cur_sec = (cur_msec / 1000LL);  /* sec */
    }
    else
    {
        *cur_sec = (cur_msec / 1000ULL); /* sec */
    }
}

void ra6w1_time64 (__time64_t * p, __time64_t * now)
{
    ra6w1_time64_sec(p, now);
}

struct tm * ra6w1_gmtime64 (const __time64_t * tod)
{
    /* Convert to Greenwich Mean Time (UTC) */
    return ra6w1_Ttotm64(0, *tod, -1);
}

struct tm * ra6w1_localtime64 (const __time64_t * tod)
{
    /* Convert to local time structure */
    return ra6w1_Ttotm64(0, *tod + (__time64_t) ra6w1_Tzoff(), 0);
}

void __boottime (__time64_t * boottime)
{
    __time64_t time   = 0;
    __time64_t uptime = 0;

    if (get_systimeoffset_from_rtm() == 0)
    {
        *boottime = 0;
    }
    else
    {
        ra6w1_time64(NULL, &time);
        uptime    = __uptime();
        *boottime = time - uptime;
    }
}

void rtc_w_lock_take (void)
{
    rtc_w_instance_ctrl_t * rtc_w_ctrl = (rtc_w_instance_ctrl_t *) R_RTC_W_GetCtrl();

    if (rtc_w_ctrl)
    {
        RTC_W_LOCK_TAKE(rtc_w_ctrl);
    }
}

void rtc_w_lock_give (void)
{
    rtc_w_instance_ctrl_t * rtc_w_ctrl = (rtc_w_instance_ctrl_t *) R_RTC_W_GetCtrl();

    if (rtc_w_ctrl)
    {
        RTC_W_LOCK_GIVE(rtc_w_ctrl);
    }
}
