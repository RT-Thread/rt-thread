#include <rtthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>

struct timeval _timevalue;
static void libc_system_time_init()
{
    rt_device_t device;
    time_t time;
    rt_tick_t tick;

    time = 0; tick = 0;
    device = rt_device_find("rtc");
    if (device != RT_NULL)
    {
        rt_device_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &time);
    }

    tick = rt_tick_get();

    _timevalue.tv_sec = time;
    _timevalue.tv_usec = (1000000UL * tick)/RT_TICK_PER_SECOND;
}

void libc_system_init(const char* tty_name)
{
	int fd;

	/* init console device */
	rt_console_init(tty_name);

	/* open console as stdin/stdout/stderr */
	fd = open("/dev/console", O_RDONLY, 0);	/* for stdin */
	fd = open("/dev/console", O_WRONLY, 0);	/* for stdout */
	fd = open("/dev/console", O_WRONLY, 0);	/* for stderr */

	/* set PATH and HOME */
	putenv("PATH=/");
	putenv("HOME=/");
}

int libc_time_to_tick(const struct timespec *time)
{
	int tick;

	tick = RT_WAITING_FOREVER;

	return tick;
}
