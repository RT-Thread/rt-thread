#include <rtthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include "libc.h"

#ifdef RT_USING_PTHREADS
#include <pthread.h>
#endif

void libc_system_init(const char* tty_name)
{
#ifdef RT_USING_DFS
	int fd;

#ifndef RT_USING_DFS_DEVFS
#error Please enable devfs by defining RT_USING_DFS_DEVFS in rtconfig.h
#endif

	/* init console device */
	rt_console_init(tty_name);

	/* open console as stdin/stdout/stderr */
	fd = open("/dev/console", O_RDONLY, 0);	/* for stdin */
	fd = open("/dev/console", O_WRONLY, 0);	/* for stdout */
	fd = open("/dev/console", O_WRONLY, 0);	/* for stderr */
#endif

	/* set PATH and HOME */
	putenv("PATH=/");
	putenv("HOME=/");

#ifdef RT_USING_PTHREADS
	pthread_system_init();
#endif
}
