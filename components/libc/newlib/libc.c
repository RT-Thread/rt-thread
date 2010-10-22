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
	rt_kprintf("stdin: %d\n", fd);
	fd = open("/dev/console", O_WRONLY, 0);	/* for stdout */
	rt_kprintf("stdout: %d\n", fd);
	fd = open("/dev/console", O_WRONLY, 0);	/* for stderr */
	rt_kprintf("stderr: %d\n", fd);
}
