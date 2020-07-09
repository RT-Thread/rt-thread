/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/08/30      Bernard      The first version
 */
#include <stdlib.h>
#include <string.h>
#include <rtthread.h>
#include <dfs_posix.h>

#include <termios.h>

int tcgetattr(int fd, struct termios *tio)
{
    /* Get the current serial port settings. */
    if (ioctl(fd, TCGETA, tio))
        return -1;

    return 0;
}

int tcsetattr(int fd, int act, const struct termios *tio)
{
    switch (act)
    {
    case TCSANOW:
        /* make the change immediately */
        return (ioctl(fd, TCSETA, (void*)tio));
    case TCSADRAIN:
        /*
         * Don't make the change until all currently written data
         * has been transmitted.
         */
        return (ioctl(fd, TCSETAW, (void*)tio));
    case TCSAFLUSH:
        /* Don't make the change until all currently written data
         * has been transmitted, at which point any received but
         * unread data is also discarded.
         */
        return (ioctl(fd, TCSETAF, (void*)tio));
    default:
        errno = EINVAL;
        return (-1);
    }
}

/**
 * this function gets process group ID for session leader for controlling
 * terminal
 *
 * @return always 0
 */
pid_t tcgetsid(int fd)
{
    return 0;
}

speed_t cfgetospeed(const struct termios *tio)
{
    return tio->c_cflag & CBAUD;
}

speed_t cfgetispeed(const struct termios *tio)
{
    return cfgetospeed(tio);
}

int cfsetospeed(struct termios *tio, speed_t speed)
{
    if (speed & ~CBAUD)
    {
        errno = EINVAL;
        return -1;
    }

    tio->c_cflag &= ~CBAUD;
    tio->c_cflag |= speed;
    return 0;
}

int cfsetispeed(struct termios *tio, speed_t speed)
{
    return speed ? cfsetospeed(tio, speed) : 0;
}

int tcsendbreak(int fd, int dur)
{
    /* nonzero duration is implementation-defined, so ignore it */
    return 0;
}

int tcflush(int fd, int queue)
{
    return ioctl(fd, TCFLSH, (void*)queue);
}

int tcflow(int fd, int action)
{
    return ioctl(fd, TCXONC, (void*)action);
}

/**
 * this function waits for transmission of output
 */
int tcdrain(int fd)
{
    return 0;
}

int isatty (int  fd)
{
    struct termios term;

    return tcgetattr (fd, &term) == 0;
}

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
void cfmakeraw(struct termios *t)
{
    t->c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL|IXON);
    t->c_oflag &= ~OPOST;
    t->c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
    t->c_cflag &= ~(CSIZE|PARENB);
    t->c_cflag |= CS8;
    t->c_cc[VMIN] = 1;
    t->c_cc[VTIME] = 0;
}

int cfsetspeed(struct termios *tio, speed_t speed)
{
    return cfsetospeed(tio, speed);
}
#endif

