#include "sys/time.h"
#include "sys/types.h"
#include "vdso_datapage.h"


#ifndef CLOCK_REALTIME_COARSE
#define CLOCK_REALTIME_COARSE 0
#endif /* CLOCK_REALTIME_COARSE */

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 1
#endif /* CLOCK_REALTIME */

#define CLOCK_CPUTIME_ID    2

#ifndef CLOCK_PROCESS_CPUTIME_ID
#define CLOCK_PROCESS_CPUTIME_ID CLOCK_CPUTIME_ID
#endif /* CLOCK_PROCESS_CPUTIME_ID */

#ifndef CLOCK_THREAD_CPUTIME_ID
#define CLOCK_THREAD_CPUTIME_ID 3
#endif /* CLOCK_THREAD_CPUTIME_ID */

#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC     4
#endif /* CLOCK_MONOTONIC */

#ifndef CLOCK_MONOTONIC_RAW
#define CLOCK_MONOTONIC_RAW 5
#endif /* CLOCK_MONOTONIC_RAW */

#ifndef CLOCK_MONOTONIC_COARSE
#define CLOCK_MONOTONIC_COARSE 6
#endif /* CLOCK_MONOTONIC_COARSE */

#ifndef CLOCK_BOOTTIME
#define CLOCK_BOOTTIME 7
#endif /* CLOCK_BOOTTIME */


static int VdsoGetRealtimeCoarse(struct timespec *ts, const VdsoDataPage *usrVdsoDataPage)
{
    do {
        if (!usrVdsoDataPage->lockCount) {
            ts->tv_sec = usrVdsoDataPage->realTimeSec;
            ts->tv_nsec = usrVdsoDataPage->realTimeNsec;
            return 0;
        }
    } while (1);
}

static int VdsoGetMonotimeCoarse(struct timespec *ts, const VdsoDataPage *usrVdsoDataPage)
{
    do {
        if (!usrVdsoDataPage->lockCount) {
            ts->tv_sec = usrVdsoDataPage->monoTimeSec;
            ts->tv_nsec = usrVdsoDataPage->monoTimeNsec;
            return 0;
        }
    } while (1);
}

int
__kernel_clock_gettime(clockid_t clock, struct timespec *ts)
{	
	int ret;
	size_t vdsoStart;
     
	VdsoDataPage *usrVdsoDataPage = (VdsoDataPage *)(uintptr_t)vdsoStart;

    switch (clock)
    {
        case CLOCK_REALTIME:
        case CLOCK_REALTIME_COARSE:
            return VdsoGetRealtimeCoarse(ts,usrVdsoDataPage);

        case CLOCK_MONOTONIC:
        case CLOCK_MONOTONIC_COARSE:
        case CLOCK_MONOTONIC_RAW:
        case CLOCK_BOOTTIME:
            return VdsoGetMonotimeCoarse(ts,usrVdsoDataPage);
		
        case CLOCK_PROCESS_CPUTIME_ID:
        case CLOCK_THREAD_CPUTIME_ID:
        default:
            ts->tv_sec  = 0;
            ts->tv_nsec = 0;
            return -1;
    }

    return ret;
}
