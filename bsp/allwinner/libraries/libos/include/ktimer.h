#ifndef __LIBOS_KTIMER_H__
#define __LIBOS_KTIMER_H__

#include <sys/time.h>

struct timespec64 {
    unsigned long tv_sec;   /* seconds */
    unsigned long tv_nsec;  /* nanoseconds */
};

int do_gettimeofday(struct timespec64 *ts);

#endif
