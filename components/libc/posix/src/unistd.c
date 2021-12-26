/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-01     Meco Man     first Version
 * 2021-02-12     Meco Man     move all functions located in <pthread_sleep.c> to this file
 */

#include <rtthread.h>
#include <unistd.h>

#ifdef RT_USING_POSIX_TERMIOS
#include "termios.h"
int isatty(int fd)
{
    struct termios ts;
    return(tcgetattr(fd, &ts) != -1); /*true if no error (is a tty)*/
}
#else
int isatty(int fd)
{
    if (fd >=0 && fd < 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
#endif
RTM_EXPORT(isatty);

char *ttyname(int fd)
{
    return "/dev/tty"; /* TODO: need to add more specific */
}
RTM_EXPORT(ttyname);
