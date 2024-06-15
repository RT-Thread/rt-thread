/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author          Notes
 * 2017-08-30       Bernard         The first version
 * 2024-04-26       TroyMitchell    Add comments for all functions
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/errno.h>
#include "termios.h"
#include <rtthread.h>

/**
 * @brief   Gets the current attributes of a terminal device.
 * @param   fd File descriptor of the terminal device.
 * @param   tio Pointer to a struct termios where the attributes will be stored.
 * @return  Upon successful completion, returns 0; otherwise, returns -1.
 *
 * @note    This function retrieves the current attributes of a terminal device specified by the file descriptor fd.
 *          It uses the ioctl system call with the TCGETA command to obtain the attributes and stores them in the
 *          struct termios pointed to by tio.
 *          If the ioctl operation fails, the function returns -1 to indicate an error.
 */
int tcgetattr(int fd, struct termios *tio)
{
    /* Get the current serial port settings. */
    if (ioctl(fd, TCGETA, tio))
        return -1;

    return 0;
}

/**
 * @brief   Sets the attributes of a terminal device.
 * @param   fd File descriptor of the terminal device.
 * @param   act Action to be taken for the attribute change (TCSANOW, TCSADRAIN, or TCSAFLUSH).
 * @param   tio Pointer to a struct termios containing the new attributes.
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function sets the attributes of a terminal device specified by the file descriptor fd.
 *          The act parameter determines when the attribute change takes effect:
 *          - TCSANOW: Make the change immediately.
 *          - TCSADRAIN: Make the change after all currently written data has been transmitted.
 *          - TCSAFLUSH: Make the change after all currently written data has been transmitted, and discard
 *            any received but unread data.
 *          The new attributes are specified in the struct termios pointed to by tio.
 *          The ioctl system call is used to set the attributes based on the value of act.
 *          If the ioctl operation fails or an invalid action is specified, errno is set to indicate the error,
 *          and the function returns -1.
 */
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
 * @brief   Gets the session ID of a terminal.
 * @param   fd File descriptor of the terminal device.
 * @return  Always returns 0.
 *
 * @note    This function is a stub and always returns 0.
 *          In POSIX systems, tcgetsid() is used to get the session ID of the terminal associated with the file descriptor fd.
 *          However, this function does not provide this functionality and simply returns 0 as a placeholder.
 */
pid_t tcgetsid(int fd)
{
    return 0;
}

/**
 * @brief   Gets the output baud rate from a termios structure.
 * @param   tio Pointer to a struct termios containing the terminal attributes.
 * @return  Output baud rate extracted from the terminal attributes.
 *
 * @note    This function extracts the output baud rate from the termios structure pointed to by tio.
 *          It retrieves the baud rate from the c_cflag member of the termios structure using the CBAUD mask.
 *          The output baud rate is returned as a speed_t type.
 */
speed_t cfgetospeed(const struct termios *tio)
{
    return tio->c_cflag & CBAUD;
}

/**
 * @brief   Gets the input baud rate from a termios structure.
 * @param   tio Pointer to a struct termios containing the terminal attributes.
 * @return  Input baud rate extracted from the terminal attributes.
 *
 * @note    This function is a wrapper for the cfgetospeed() function.
 *          It returns the input baud rate by calling cfgetospeed() with the termios structure pointer tio.
 */
speed_t cfgetispeed(const struct termios *tio)
{
    return cfgetospeed(tio);
}

/**
 * @brief   Sets the output baud rate in a termios structure.
 * @param   tio Pointer to a struct termios where the output baud rate will be set.
 * @param   speed Output baud rate to be set.
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function sets the output baud rate in the termios structure pointed to by tio.
 *          The speed parameter specifies the baud rate to be set.
 *          If the specified speed exceeds the CBAUD mask, indicating an invalid baud rate value,
 *          errno is set to EINVAL, and the function returns -1.
 *          Otherwise, the function clears the CBAUD bits in the c_cflag member of the termios structure
 *          and sets them to the specified speed value. It then returns 0 to indicate success.
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
 * @brief   Sets the input baud rate in a termios structure.
 * @param   tio Pointer to a struct termios where the input baud rate will be set.
 * @param   speed Input baud rate to be set.
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function sets the input baud rate in the termios structure pointed to by tio.
 *          The speed parameter specifies the input baud rate to be set.
 *          If the speed parameter is non-zero, indicating a valid baud rate, the function calls
 *          cfsetospeed() to set both the input and output baud rates to the specified value.
 *          If speed is zero, indicating that no baud rate needs to be set for input, the function returns 0
 *          without making any changes to the termios structure.
 */
int cfsetispeed(struct termios *tio, speed_t speed)
{
    return speed ? cfsetospeed(tio, speed) : 0;
}

/**
 * @brief   Sends a break signal on a terminal.
 * @param   fd File descriptor of the terminal device.
 * @param   dur Duration of the break signal (ignored).
 * @return  Always returns 0.
 *
 * @note    This function is a stub and does not send an actual break signal.
 *          Sending a break signal with a nonzero duration is implementation-defined,
 *          so this function ignores the duration parameter and always returns 0.
 */
int tcsendbreak(int fd, int dur)
{
    /* nonzero duration is implementation-defined, so ignore it */
    return 0;
}

/**
 * @brief   Flushes data from a terminal input or output queue.
 * @param   fd File descriptor of the terminal device.
 * @param   queue Queue to be flushed (TCIFLUSH, TCOFLUSH, or TCIOFLUSH).
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function flushes data from the input or output queue of the terminal device specified by the file descriptor fd.
 *          The queue parameter specifies which queue to flush:
 *          - TCIFLUSH: Flushes data from the input queue.
 *          - TCOFLUSH: Flushes data from the output queue.
 *          - TCIOFLUSH: Flushes data from both the input and output queues.
 *          The ioctl system call is used with the TCFLSH command to perform the flush operation.
 *          If the ioctl operation fails, errno is set to indicate the error, and the function returns -1.
 */
int tcflush(int fd, int queue)
{
    return ioctl(fd, TCFLSH, (void*)(rt_ubase_t)queue);
}

/**
 * @brief   Controls the terminal flow control.
 * @param   fd File descriptor of the terminal device.
 * @param   action Action to be taken for flow control (TCOOFF, TCOON, TCIOFF, or TCION).
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function controls the flow of data on the terminal device specified by the file descriptor fd.
 *          The action parameter determines the flow control action to be taken:
 *          - TCOOFF: Suspends output transmission.
 *          - TCOON: Restarts output transmission.
 *          - TCIOFF: Suspends input transmission.
 *          - TCION: Restarts input transmission.
 *          The ioctl system call is used with the TCXONC command to perform the flow control operation.
 *          If the ioctl operation fails, errno is set to indicate the error, and the function returns -1.
 */
int tcflow(int fd, int action)
{
    return ioctl(fd, TCXONC, (void*)(rt_ubase_t)action);
}

/**
 * @brief   Waits until all output written to the terminal is transmitted.
 * @param   fd File descriptor of the terminal device.
 * @return  Always returns 0.
 *
 * @note    This function is a stub and does not perform any action.
 *          In POSIX systems, tcdrain() is used to wait until all output written to the terminal
 *          is transmitted, but this function does not provide this functionality and simply returns 0 as a placeholder.
 */
int tcdrain(int fd)
{
    return 0;
}

/**
 * @brief   Sets the terminal attributes to raw mode.
 * @param   t Pointer to a struct termios where the terminal attributes will be set.
 *
 * @note    This function sets the terminal attributes pointed to by t to raw mode.
 *          Raw mode disables special input and output processing features, making the terminal behave more like a data stream.
 *          The following modifications are made to the termios structure:
 *          - Input flags (c_iflag) are cleared of various processing flags.
 *          - Output flags (c_oflag) are cleared to disable output processing.
 *          - Local flags (c_lflag) are cleared to disable canonical mode, echoing, and signal handling.
 *          - Control flags (c_cflag) are modified to set character size to 8 bits and disable parity.
 *          - The VMIN and VTIME control characters are set to 1 and 0, respectively, for non-blocking read behavior.
 */
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

/**
 * @brief   Sets the input and output baud rates in a termios structure.
 * @param   tio Pointer to a struct termios where the input and output baud rates will be set.
 * @param   speed Baud rate to be set for both input and output.
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function is a wrapper for the cfsetospeed() function.
 *          It sets both the input and output baud rates in the termios structure pointed to by tio to the specified speed.
 *          The function returns the result of cfsetospeed(), which sets the baud rate for both input and output.
 */
int cfsetspeed(struct termios *tio, speed_t speed)
{
    return cfsetospeed(tio, speed);
}
