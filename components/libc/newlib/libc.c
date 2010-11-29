#include <rtthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include "libc.h"

struct timeval _timevalue;
static void libc_system_time_init()
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

int libc_get_time(struct timespec *time)
{
	rt_tick_t tick;
	RT_ASSERT(time != RT_NULL);

	/* get tick */
	tick = rt_tick_get();

	time->tv_sec = _timevalue.tv_sec + tick / RT_TICK_PER_SECOND;
	time->tv_nsec = (_timevalue.tv_usec + (tick % RT_TICK_PER_SECOND) * NANOSECOND_PER_TICK) * 1000;

	return 0;
}

int libc_set_time(const struct timespec *time)
{
	int second;
	rt_tick_t tick;
    rt_device_t device;

	second = time->tv_sec;
    device = rt_device_find("rtc");
    if (device != RT_NULL)
    {
		/* get realtime seconds */
        rt_device_control(device, RT_DEVICE_CTRL_RTC_SET_TIME, &second);
    }
	else return -1;

	/* get tick */
    tick = rt_tick_get();

	/* update timevalue */
    _timevalue.tv_usec = MICROSECOND_PER_SECOND - (tick % RT_TICK_PER_SECOND) * MICROSECOND_PER_TICK;
    _timevalue.tv_sec = second - tick/RT_TICK_PER_SECOND - 1;

	return 0;
}

int libc_time_to_tick(const struct timespec *time)
{
	int tick;
	int microsecond, second;

	RT_ASSERT(time != RT_NULL);

	tick = RT_WAITING_FOREVER;
	if (time != NULL)
	{
		if ((time->tv_nsec/1000 - _timevalue.tv_usec) < 0)
		{
			microsecond = (1000000UL + time->tv_nsec/1000) - _timevalue.tv_usec;
			second  = time->tv_sec - 1;
		}
		else
		{
			microsecond = time->tv_nsec/1000 - _timevalue.tv_usec;
			second  = time->tv_sec;
		}

		tick = second * RT_TICK_PER_SECOND + microsecond * RT_TICK_PER_SECOND / MICROSECOND_PER_SECOND;
		if (tick < 0) tick = 0;
	}

	return tick;
}

void libc_system_init(const char* tty_name)
{
	int fd;
	extern int pthread_system_init(void);

#ifndef RT_USING_DFS_DEVFS
#error Please enable devfs by defining RT_USING_DFS_DEVFS in rtconfig.h
#endif

	/* init console device */
	rt_console_init(tty_name);

	/* open console as stdin/stdout/stderr */
	fd = open("/dev/console", O_RDONLY, 0);	/* for stdin */
	fd = open("/dev/console", O_WRONLY, 0);	/* for stdout */
	fd = open("/dev/console", O_WRONLY, 0);	/* for stderr */

	/* set PATH and HOME */
	putenv("PATH=/");
	putenv("HOME=/");

	/* initialize system time */
	libc_system_time_init();
#ifdef RT_USING_PTHREADS
	pthread_system_init();
#endif
}
