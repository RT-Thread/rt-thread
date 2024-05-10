#include <stdio.h>
#include <time.h>
#include <errno.h>
#include "sys/types.h"
#include "vdso_sys.h"

static int VdsoGetRealtimeCoarse(struct timespec *ts, const VdsoDataPage *usrVdsoDataPage)
{
    do {
        if (!usrVdsoDataPage->lockCount) {
            ts->tv_sec = usrVdsoDataPage->realTimeSec;
            ts->tv_nsec = usrVdsoDataPage->realTimeNsec;
            return 0;
        }
        else {
            ts->tv_sec = 0;
            ts->tv_nsec = 0;
            return EPERM;
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
        else {
            ts->tv_sec = 0;
            ts->tv_nsec = 0;
            return EPERM;
        }
    } while (1);
}

static inline int
__cvdso_clock_gettime_common(const VdsoDataPage *vd, clockid_t clock,
			     struct timespec *ts)
{
	u_int32_t msk;

	if (unlikely((u_int32_t) clock >= MAX_CLOCKS))
		return -1;

	msk = 1U << clock;
	if (likely(msk & VDSO_REALTIME))
		return VdsoGetRealtimeCoarse(ts,vd);
	else if (msk & VDSO_MONOTIME)
		return VdsoGetMonotimeCoarse(ts,vd);
	else
        return ENOENT;
}

static __maybe_unused int
__cvdso_clock_gettime_data(const VdsoDataPage *vd, clockid_t clock,
			   struct timespec *ts)
{
	int ret = 0;
    ret = __cvdso_clock_gettime_common(vd, clock, ts);
	return ret;
}

int
__kernel_clock_gettime(clockid_t clock, struct timespec *ts)
{ 
	return __cvdso_clock_gettime_data(__arch_get_vdso_data(), clock, ts);
}
