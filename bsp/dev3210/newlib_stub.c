#include <rtthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* some newlib leaked function in CodeSourcery G++ Lite for MIPS version */

int
getpid()
{
	return 0;
}

int
gettimeofday(struct timeval *__tp, void *__tzp)
{
	struct timespec tp;

	if (libc_get_time(&tp) == 0)
	{
		if (__tp != RT_NULL)
		{
			__tp->tv_sec  = tp.tv_sec;
			__tp->tv_usec = tp.tv_nsec * 1000UL;
		}

		return tp.tv_sec;
	}

	return 0;
}
