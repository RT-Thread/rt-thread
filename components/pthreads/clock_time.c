#include <rtthread.h>
#include <pthread.h>

struct timeval _timevalue;
void clock_time_system_init()
{
    time_t time;
    rt_tick_t tick;
    rt_device_t device;

    time = 0;
    device = rt_device_find("rtc");
    if (device != RT_NULL)
    {
		/* get realtime seconds */
        rt_device_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &time);
    }

	/* get tick */
    tick = rt_tick_get();

    _timevalue.tv_usec = MICROSECOND_PER_SECOND - (tick%RT_TICK_PER_SECOND) * MICROSECOND_PER_TICK;
    _timevalue.tv_sec = time - tick/RT_TICK_PER_SECOND - 1;
}

int clock_time_to_tick(const struct timespec *time)
{
	int tick;
	int nsecond, second;
	struct timespec tp;

	RT_ASSERT(time != RT_NULL);

	tick = RT_WAITING_FOREVER;
	if (time != NULL)
	{
		/* get current tp */
		clock_gettime(CLOCK_REALTIME, &tp);

		if ((time->tv_nsec - tp.tv_nsec) < 0)
		{
			nsecond = NANOSECOND_PER_SECOND - (tp.tv_nsec - time->tv_nsec);
			second  = time->tv_sec - tp.tv_sec - 1;
		}
		else
		{
			nsecond = time->tv_nsec - tp.tv_nsec;
			second  = time->tv_sec - tp.tv_sec;
		}

		tick = second * RT_TICK_PER_SECOND + nsecond * RT_TICK_PER_SECOND / NANOSECOND_PER_SECOND;
		if (tick < 0) tick = 0;
	}

	return tick;
}

int clock_getres  (clockid_t clockid, struct timespec *res)
{
	if ((clockid != CLOCK_REALTIME) || (res == RT_NULL))
	{
		rt_set_errno(EINVAL);
		return -1;
	}

	res->tv_sec = 0;
	res->tv_nsec = NANOSECOND_PER_SECOND/RT_TICK_PER_SECOND;

	return 0;
}

int clock_gettime (clockid_t clockid, struct timespec *tp)
{
	rt_tick_t tick;

	if ((clockid != CLOCK_REALTIME) || (tp == RT_NULL))
	{
		rt_set_errno(EINVAL);
		return -1;
	}

	/* get tick */
	tick = rt_tick_get();

	tp->tv_sec = _timevalue.tv_sec + tick / RT_TICK_PER_SECOND;
	tp->tv_nsec = (_timevalue.tv_usec + (tick % RT_TICK_PER_SECOND) * NANOSECOND_PER_TICK) * 1000;
	
	return 0;
}

int clock_settime (clockid_t clockid, const struct timespec *tp)
{
	int second;
	rt_tick_t tick;
    rt_device_t device;

	if ((clockid != CLOCK_REALTIME) || (tp == RT_NULL))
	{
		rt_set_errno(EINVAL);
		return -1;
	}

	/* get second */
	second = tp->tv_sec;
	/* get tick */
    tick = rt_tick_get();

	/* update timevalue */
    _timevalue.tv_usec = MICROSECOND_PER_SECOND - (tick % RT_TICK_PER_SECOND) * MICROSECOND_PER_TICK;
    _timevalue.tv_sec = second - tick/RT_TICK_PER_SECOND - 1;

	/* update for RTC device */
    device = rt_device_find("rtc");
    if (device != RT_NULL)
    {
		/* set realtime seconds */
        rt_device_control(device, RT_DEVICE_CTRL_RTC_SET_TIME, &second);
    }
	else return -1;

	return 0;
}
