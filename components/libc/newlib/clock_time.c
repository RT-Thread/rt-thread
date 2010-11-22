#include <rtthread.h>

#include <time.h>
#include <errno.h>
#include "libc.h"

int clock_getres(clockid_t clock_id, struct timespec *res)
{
	if ((clock_id != CLOCK_REALTIME) || (res == RT_NULL))
	{
		rt_set_errno(EINVAL);
		return -1;
	}

	res->tv_sec  = 0;
	res->tv_nsec = NANOSECOND_PER_TICK;

	return 0;
}

int clock_gettime(clockid_t clock_id, struct timespec *tp)
{
	if ((clock_id != CLOCK_REALTIME) || (tp == RT_NULL))
	{
		rt_set_errno(EINVAL);
		return -1;
	}

	libc_get_time(tp);
	return 0;
}

int clock_settime(clockid_t clock_id, const struct timespec *tp)
{
	if ((clock_id != CLOCK_REALTIME) || (tp == RT_NULL))
	{
		rt_set_errno(EINVAL);
		return -1;
	}

	libc_set_time(tp);
	return 0;
}
