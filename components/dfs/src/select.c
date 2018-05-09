/*
 * File      : select.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-12-28     Bernard      first version
 */
#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_posix.h>

#include <dfs_poll.h>
#include <dfs_select.h>

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
    int fd;
    int npfds;
    int msec;
    int ndx;
    int ret;
    struct pollfd *pollset = RT_NULL;

    /* How many pollfd structures do we need to allocate? */
    for (fd = 0, npfds = 0; fd < nfds; fd++)
    {
        /* Check if any monitor operation is requested on this fd */
        if ((readfds   && FD_ISSET(fd, readfds))  ||
            (writefds  && FD_ISSET(fd, writefds)) ||
            (exceptfds && FD_ISSET(fd, exceptfds)))
        {
            npfds++;
        }
    }

    /* Allocate the descriptor list for poll() */
    if (npfds > 0)
    {
        pollset = (struct pollfd *)rt_calloc(npfds, sizeof(struct pollfd));
        if (!pollset)
        {
            return -1;
        }
    }

    /* Initialize the descriptor list for poll() */
    for (fd = 0, ndx = 0; fd < nfds; fd++)
    {
        int incr = 0;

        /* The readfs set holds the set of FDs that the caller can be assured
         * of reading from without blocking.  Note that POLLHUP is included as
         * a read-able condition.  POLLHUP will be reported at the end-of-file
         * or when a connection is lost.  In either case, the read() can then
         * be performed without blocking.
         */

        if (readfds && FD_ISSET(fd, readfds))
        {
            pollset[ndx].fd         = fd;
            pollset[ndx].events |= POLLIN;
            incr = 1;
        }

        if (writefds && FD_ISSET(fd, writefds))
        {
            pollset[ndx].fd      = fd;
            pollset[ndx].events |= POLLOUT;
            incr = 1;
        }

        if (exceptfds && FD_ISSET(fd, exceptfds))
        {
            pollset[ndx].fd = fd;
            incr = 1;
        }

        ndx += incr;
    }

    RT_ASSERT(ndx == npfds);

    /* Convert the timeout to milliseconds */
    if (timeout)
    {
        msec = timeout->tv_sec * 1000 + timeout->tv_usec / 1000;
    }
    else
    {
        msec = -1;
    }

    /* Then let poll do all of the real work. */

    ret = poll(pollset, npfds, msec);

    /* Now set up the return values */
    if (readfds)
    {
        memset(readfds, 0, sizeof(fd_set));
    }

    if (writefds)
    {
        memset(writefds, 0, sizeof(fd_set));
    }

    if (exceptfds)
    {
        memset(exceptfds, 0, sizeof(fd_set));
    }

    /* Convert the poll descriptor list back into selects 3 bitsets */

    if (ret > 0)
    {
        ret = 0;
        for (ndx = 0; ndx < npfds; ndx++)
        {
            /* Check for read conditions.  Note that POLLHUP is included as a
             * read condition.  POLLHUP will be reported when no more data will
             * be available (such as when a connection is lost).  In either
             * case, the read() can then be performed without blocking.
             */

            if (readfds)
            {
                if (pollset[ndx].revents & (POLLIN | POLLHUP))
                {
                    FD_SET(pollset[ndx].fd, readfds);
                    ret++;
                }
            }

            /* Check for write conditions */
            if (writefds)
            {
                if (pollset[ndx].revents & POLLOUT)
                {
                    FD_SET(pollset[ndx].fd, writefds);
                    ret++;
                }
            }

            /* Check for exceptions */
            if (exceptfds)
            {
                if (pollset[ndx].revents & POLLERR)
                {
                    FD_SET(pollset[ndx].fd, exceptfds);
                    ret++;
                }
            }
        }
    }

    if (pollset) rt_free(pollset);

    return ret;
}

