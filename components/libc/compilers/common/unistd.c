/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-01     Meco Man     First Version
 */

#include <unistd.h>

#ifdef RT_USING_POSIX_TERMIOS
#include <termios.h>

int isatty(int fd)
{
    struct termios ts;
    return(tcgetattr(fd,&ts) != -1);/*true if no error (is a tty)*/
}
#endif

char *ttyname(int fd)
{
    return "/dev/tty0"; /*TODO: need to add more specific*/
}
