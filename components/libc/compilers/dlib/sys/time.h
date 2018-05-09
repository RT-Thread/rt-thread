#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

#include <time.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
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

#if defined ( __ICCARM__ ) && (__VER__ >= 8011002)
#define _TIMESPEC_DEFINED
#endif

#ifndef _TIMESPEC_DEFINED
#define _TIMESPEC_DEFINED
/*
 * Structure defined by POSIX.1b to be like a timeval.
 */
struct timespec {
    time_t  tv_sec;     /* seconds */
    long    tv_nsec;    /* and nanoseconds */
};
#endif /* _TIMESPEC_DEFINED */ 

struct timezone {
  int tz_minuteswest;   /* minutes west of Greenwich */
  int tz_dsttime;       /* type of dst correction */
};

int gettimeofday(struct timeval *tp, void *ignore);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_TIME_H_ */
