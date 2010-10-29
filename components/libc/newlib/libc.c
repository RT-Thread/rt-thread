#include <rtthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

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

