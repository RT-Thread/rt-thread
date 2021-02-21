/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-01     Meco Man     first Version
 * 2021-02-12     Meco Man     move all functions located in <pthread_sleep.c> to this file
 */

#include <unistd.h>
#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_POSIX_TERMIOS
#include "termios.h"

int isatty(int fd)
{
    struct termios ts;
    return(tcgetattr(fd,&ts) != -1);/*true if no error (is a tty)*/
}
RTM_EXPORT(isatty);
#endif

char *ttyname(int fd)
{
    return "/dev/tty0"; /*TODO: need to add more specific*/
}
RTM_EXPORT(ttyname);

unsigned int sleep(unsigned int seconds)
{
    rt_tick_t delta_tick;

    delta_tick = rt_tick_get();
    rt_thread_delay(seconds * RT_TICK_PER_SECOND);
    delta_tick = rt_tick_get() - delta_tick;

    return seconds - delta_tick/RT_TICK_PER_SECOND;
}
RTM_EXPORT(sleep);

int usleep(useconds_t usec)
{
    rt_thread_mdelay(usec / 1000u);
    rt_hw_us_delay(usec % 1000u);
    return 0;
}
RTM_EXPORT(usleep);

pid_t getpid(void)
{
    /*TODO*/
    return 0;
}
RTM_EXPORT(getpid);

pid_t getppid(void)
{
    return 0;
}
RTM_EXPORT(getppid);

uid_t getuid(void)
{
    return 0; /*ROOT*/
}
RTM_EXPORT(getuid);

uid_t geteuid(void)
{
    return 0; /*ROOT*/
}
RTM_EXPORT(geteuid);

gid_t getgid(void)
{
    return 0; /*ROOT*/
}
RTM_EXPORT(getgid);

gid_t getegid(void)
{
    return 0; /*ROOT*/
}
RTM_EXPORT(getegid);
