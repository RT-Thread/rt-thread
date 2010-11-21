#include <rtthread.h>
#include "pthread_internal.h"
#include <time.h>

int clock_getres(clockid_t clock_id, struct timespec *res)
{
	if ((clock_id != CLOCK_REALTIME) || (res == RT_NULL))
	{
		rt_set_errno(EINVAL);
		return -1;
	}

	res->tv_sec  = 0;
	res->tv_nsec = NSEC_PER_TICK;

	return 0;
}

int clock_gettime(clockid_t clock_id, struct timespec *tp)
{
	return 0;
}

int clock_settime(clockid_t clock_id, const struct timespec *tp)
{
	return 0;
}
