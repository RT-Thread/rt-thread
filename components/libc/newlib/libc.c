#include <rtthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include "libc.h"

#ifdef RT_USING_PTHREADS
#include <pthread.h>
#endif

#ifdef RT_USING_DFS
#include <dfs_posix.h>

#ifdef RT_USING_DFS_DEVFS
#include <devfs.h>
#endif

#endif

int libc_system_init(void)
{
#ifdef RT_USING_DFS
    int fd;
    struct rt_device *console_dev;

#ifndef RT_USING_DFS_DEVFS
#error Please enable devfs by defining RT_USING_DFS_DEVFS in rtconfig.h
#endif

    console_dev = rt_console_get_device();
    if (console_dev)
    {
        /* initialize console device */
        rt_console_init(console_dev->parent.name);

        /* open console as stdin/stdout/stderr */
        fd = open("/dev/console", O_RDONLY, 0); /* for stdin */
        fd = open("/dev/console", O_WRONLY, 0); /* for stdout */
        fd = open("/dev/console", O_WRONLY, 0); /* for stderr */

        /* skip warning */
        fd = fd;
    }
#endif

    /* set PATH and HOME */
    putenv("PATH=/bin");
    putenv("HOME=/home");

#ifdef RT_USING_PTHREADS
    pthread_system_init();
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(libc_system_init);
