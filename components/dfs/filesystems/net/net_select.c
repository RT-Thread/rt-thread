/*
 * File      : lwip_select.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
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
 * 2015-05-05     Bernard      First version
 */

#include <rtthread.h>
#include <sys/select.h>

#ifdef RT_USING_LWIP

#include "dfs_net.h"

int
select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset,
            struct timeval *timeout)
{
    int index, result;
    int sock, maxfd;

    fd_set sock_readset;
    fd_set sock_writeset;
    fd_set sock_exceptset;

    FD_ZERO(&sock_readset);
    FD_ZERO(&sock_writeset);
    FD_ZERO(&sock_exceptset);

    maxfd = 0;
    for (index = 0; index < maxfdp1; index ++)
    {
        /* convert fd to sock */
        sock = dfs_net_getsocket(index);
        if (sock == -1) continue;

        if (sock > maxfd) maxfd = sock;

        /* if FD is set, set the socket set */
        if (readset && FD_ISSET(index, readset))
        {
            FD_SET(sock, &sock_readset);
        }
        if (writeset && FD_ISSET(index, writeset))
        {
            FD_SET(sock, &sock_writeset);
        }
        if (exceptset && FD_ISSET(index, exceptset))
        {
            FD_SET(sock, &sock_exceptset);
        }
    }

    /* no socket found, return bad file descriptor */
    if (maxfd == 0) return -EBADF;
    maxfd += 1;
    
    result = lwip_select(maxfd, &sock_readset, &sock_writeset, &sock_exceptset, timeout);
    
    if (readset)   FD_ZERO(readset);
    if (writeset)  FD_ZERO(writeset);
    if (exceptset) FD_ZERO(exceptset);

    if (result != -1)
    {
        for (index = 0; index < maxfd; index ++)
        {
            /* check each socket */
            if ((FD_ISSET(index, &sock_readset))  ||
                (FD_ISSET(index, &sock_writeset)) ||
                (FD_ISSET(index, &sock_exceptset)))
            {
                int fd_index;
                
                /* Because we can not get the corresponding fd, we have to search it one by one */
                for (fd_index = 0; fd_index < maxfdp1; fd_index ++)
                {
                    sock = dfs_lwip_getsocket(fd_index);
                    if (sock == index) /* found it */
                    {
                        if (readset && FD_ISSET(index, &sock_readset))
                        {
                            FD_SET(sock, readset);
                        }
                        if (writeset && FD_ISSET(index, &sock_writeset))
                        {
                            FD_SET(sock, writeset);
                        }
                        if (exceptset && FD_ISSET(index, &sock_exceptset))
                        {
                            FD_SET(sock, exceptset);
                        }
                        
                        /* end of search */
                        break;
                    }
                }
            }
        }
    }
    
    return result;
}
RTM_EXPORT(select);

#endif
