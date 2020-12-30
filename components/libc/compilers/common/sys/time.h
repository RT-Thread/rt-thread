/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-07     Meco Man     combine gcc armcc iccarm
 */
#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Skip define timespec for IAR version over 8.10.1 where __VER__ is 8010001.
 */
#if defined ( __ICCARM__ ) && (__VER__ >= 8010001)
#define _TIMESPEC_DEFINED
#endif


#ifndef _TIMEVAL_DEFINED
#define _TIMEVAL_DEFINED
/*
 * Structure returned by gettimeofday(2) system call,
 * and used in other calls.
 */
struct timeval {
    long    tv_sec;     /* seconds */
    long    tv_usec;    /* and microseconds */
};
#endif /* _TIMEVAL_DEFINED */

#if !defined __GNUC__ && !defined __ICCARM__
struct timespec {
    time_t  tv_sec;     /* seconds */
    long    tv_nsec;    /* and nanoseconds */
};
#endif

struct timezone {
  int tz_minuteswest;   /* minutes west of Greenwich */
  int tz_dsttime;       /* type of dst correction */
};

int gettimeofday(struct timeval *tp, void *ignore);
struct tm *gmtime_r(const time_t *timep, struct tm *r);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_TIME_H_ */
