/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/08/30     Bernard      The first version
 */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/errno.h>
#include "termios.h"
#include <rtthread.h>

/**
 * @brief Get the terminal attributes for a given file descriptor.
 *
 * This function gets the current terminal attributes for the given file descriptor.
 *
 * @param fd  The file descriptor for the terminal.
 * @param tio A pointer to a `struct termios` where the attributes will be stored.
 *
 * @return 0 on success, -1 on failure.
 */
int tcgetattr(int fd, struct termios *tio)
{
    /* Get the current serial port settings. */
    if (ioctl(fd, TCGETA, tio))
        return -1;

    return 0;
}

/**
 * @brief Set the terminal attributes for a given file descriptor.
 *
 * This function sets the terminal attributes for the given file descriptor based on the provided action.
 *
 * @param fd   The file descriptor for the terminal.
 * @param act  The action to perform (TCSANOW, TCSADRAIN, or TCSAFLUSH).
 * @param tio  A pointer to a `struct termios` with the new attributes.
 *
 * @return 0 on success, -1 on failure.
 */
int tcsetattr(int fd, int act, const struct termios *tio)
{
    switch (act)
    {
    case TCSANOW:
        /* make the change immediately */
        return (ioctl(fd, TCSETA, (void *)tio));
    case TCSADRAIN:
        /*
         * Don't make the change until all currently written data
         * has been transmitted.
         */
        return (ioctl(fd, TCSETAW, (void *)tio));
    case TCSAFLUSH:
        /* Don't make the change until all currently written data
         * has been transmitted, at which point any received but
         * unread data is also discarded.
         */
        return (ioctl(fd, TCSETAF, (void *)tio));
    default:
        errno = EINVAL;
        return (-1);
    }
}

/**
 * @brief Get the session leader's process group ID for the controlling terminal.
 *
 * This function gets the process group ID for the session leader for the controlling terminal.
 *
 * @param fd  The file descriptor for the terminal.
 *
 * @return Always returns 0.
 */
pid_t tcgetsid(int fd)
{
    return 0;
}

/**
 * @brief Get the output baud rate from terminal attributes.
 *
 * This function gets the output baud rate from the terminal attributes.
 *
 * @param tio A pointer to a `struct termios` with the terminal attributes.
 *
 * @return The output baud rate.
 */
speed_t cfgetospeed(const struct termios *tio)
{
    return tio->c_cflag & CBAUD;
}

/**
 * @brief Get the input baud rate from terminal attributes.
 *
 * This function gets the input baud rate from the terminal attributes.
 *
 * @param tio A pointer to a `struct termios` with the terminal attributes.
 *
 * @return The input baud rate.
 */
speed_t cfgetispeed(const struct termios *tio)
{
    return cfgetospeed(tio);
}

/**
 * @brief Set the output baud rate in terminal attributes.
 *
 * This function sets the output baud rate in the terminal attributes.
 *
 * @param tio    A pointer to a `struct termios` with the terminal attributes.
 * @param speed  The output baud rate to set.
 *
 * @return 0 on success, -1 on failure.
 */
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

/**
 * @brief Set the input baud rate in terminal attributes.
 *
 * This function sets the input baud rate in the terminal attributes.
 *
 * @param tio    A pointer to a `struct termios` with the terminal attributes.
 * @param speed  The input baud rate to set.
 *
 * @return 0 on success, -1 on failure.
 */
int cfsetispeed(struct termios *tio, speed_t speed)
{
    return speed ? cfsetospeed(tio, speed) : 0;
}

/**
 * @brief Send a break signal on the terminal line.
 *
 * This function sends a break signal on the terminal line with a specified duration.
 *
 * @param fd   The file descriptor for the terminal.
 * @param dur  The duration of the break signal.
 *
 * @return 0.
 */
int tcsendbreak(int fd, int dur)
{
    /* Nonzero duration is implementation-defined, so ignore it. */
    return 0;
}

/**
 * @brief Flush data on the terminal.
 *
 * This function flushes data on the terminal by discarding or transmitting it.
 *
 * @param fd     The file descriptor for the terminal.
 * @param queue  The type of data to flush (TCIFLUSH, TCOFLUSH, or TCIOFLUSH).
 *
 * @return 0 on success, -1 on failure.
 */
int tcflush(int fd, int queue)
{
    return ioctl(fd, TCFLSH, (void *)(rt_ubase_t)queue);
}

/**
 * @brief Suspend or resume data transmission and reception on the terminal.
 *
 * This function suspends or resumes data transmission and reception on the terminal.
 *
 * @param fd      The file descriptor for the terminal.
 * @param action  The action to perform (TCOOFF, TCOON, or TCOFLUSH).
 *
 * @return 0 on success, -1 on failure.
 */
int tcflow(int fd, int action)
{
    return ioctl(fd, TCXONC, (void *)(rt_ubase_t)action);
}

/**
 * @brief Wait for transmission of output on the terminal.
 *
 * This function waits for the transmission of output on the terminal.
 *
 * @param fd  The file descriptor for the terminal.
 *
 * @return 0.
 */
int tcdrain(int fd)
{
    return 0;
}

/**
 * @brief Set the terminal attributes to raw mode.
 *
 * This function sets the terminal attributes to raw mode by clearing various flags in the `struct termios`.
 *
 * @param t  A pointer to a `struct termios` with the terminal attributes.
 */
void cfmakeraw(struct termios *t)
{
    t->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    t->c_oflag &= ~OPOST;
    t->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    t->c_cflag &= ~(CSIZE | PARENB);
    t->c_cflag |= CS8;
    t->c_cc[VMIN] = 1;
    t->c_cc[VTIME] = 0;
}

/**
 * @brief Set the terminal attributes to a specified baud rate.
 *
 * This function sets the output baud rate in the terminal attributes.
 *
 * @param tio    A pointer to a `struct termios` with the terminal attributes.
 * @param speed  The baud rate to set.
 *
 * @return 0 on success, -1 on failure.
 */
int cfsetspeed(struct termios *tio, speed_t speed)
{
    return cfsetospeed(tio, speed);
}
