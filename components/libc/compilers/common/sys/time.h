/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-07     Meco Man     combine gcc armcc iccarm
 * 2021-02-12     Meco Man     move all definitions located in <clock_time.h> to this file
 */
#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

#include <rtconfig.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DST_NONE    0   /* not on dst */
#define DST_USA     1   /* USA style dst */
#define DST_AUST    2   /* Australian style dst */
#define DST_WET     3   /* Western European dst */
#define DST_MET     4   /* Middle European dst */
#define DST_EET     5   /* Eastern European dst */
#define DST_CAN     6   /* Canada */
#define DST_GB      7   /* Great Britain and Eire */
#define DST_RUM     8   /* Rumania */
#define DST_TUR     9   /* Turkey */
#define DST_AUSTALT 10  /* Australian style with shift in 1986 */

#ifndef _TIMEVAL_DEFINED
#define _TIMEVAL_DEFINED
/*
 * Structure returned by gettimeofday(2) system call,
 * and used in other calls.
 */
#if !(defined(_WIN32))
struct timeval {
    long    tv_sec;     /* seconds */
    long    tv_usec;    /* and microseconds */
};
#endif
#endif /* _TIMEVAL_DEFINED */

#if !(defined(__GNUC__) && !defined(__ARMCC_VERSION)/*GCC*/) && !(defined(__ICCARM__) && (__VER__ >= 8010001)) && !defined(_WIN32)
struct timespec {
    time_t  tv_sec;     /* seconds */
    long    tv_nsec;    /* and nanoseconds */
};
#endif

struct timezone {
  int tz_minuteswest;   /* minutes west of Greenwich */
  int tz_dsttime;       /* type of dst correction */
};

int stime(const time_t *t);
time_t timegm(struct tm * const t);
int gettimeofday(struct timeval *tv, struct timezone *tz);
int settimeofday(const struct timeval *tv, const struct timezone *tz);
#if defined(__ARMCC_VERSION) || defined (__ICCARM__)
struct tm *gmtime_r(const time_t *timep, struct tm *r);
#endif

#ifdef RT_USING_POSIX
#include <sys/types.h>
/* posix clock and timer */
#define MILLISECOND_PER_SECOND  1000UL
#define MICROSECOND_PER_SECOND  1000000UL
#define NANOSECOND_PER_SECOND   1000000000UL

#define MILLISECOND_PER_TICK    (MILLISECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define MICROSECOND_PER_TICK    (MICROSECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define NANOSECOND_PER_TICK     (NANOSECOND_PER_SECOND  / RT_TICK_PER_SECOND)

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME      1
#endif

#define CLOCK_CPUTIME_ID    2

#ifndef CLOCK_PROCESS_CPUTIME_ID
#define CLOCK_PROCESS_CPUTIME_ID CLOCK_CPUTIME_ID
#endif
#ifndef CLOCK_THREAD_CPUTIME_ID
#define CLOCK_THREAD_CPUTIME_ID  CLOCK_CPUTIME_ID
#endif

#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC     4
#endif

int clock_getres  (clockid_t clockid, struct timespec *res);
int clock_gettime (clockid_t clockid, struct timespec *tp);
int clock_settime (clockid_t clockid, const struct timespec *tp);
int clock_time_to_tick(const struct timespec *time);
#endif /* RT_USING_POSIX */

#ifdef __cplusplus
}
#endif

#endif /* _SYS_TIME_H_ */
