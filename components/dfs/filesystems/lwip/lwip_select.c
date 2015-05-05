#include <rtthread.h>
#include <sys/select.h>

#ifdef RT_USING_LWIP

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
        if (readset && FD_ISSET(index, readset))
        {
            sock = dfs_lwip_getsocket(index);
            if (sock > maxfd) maxfd = sock;
            FD_SET(sock, &sock_readset);
        }
        
        if (writeset && FD_ISSET(index, writeset))
        {
            sock = dfs_lwip_getsocket(index);
            if (sock > maxfd) maxfd = sock;
            FD_SET(sock, &sock_writeset);
        }
        
        if (exceptset && FD_ISSET(index, exceptset))
        {
            sock = dfs_lwip_getsocket(index);
            if (sock > maxfd) maxfd = sock;
            FD_SET(sock, &sock_exceptset);
        }
    }

    if (maxfd == 0) return -EBADF;
    maxfd += 1;
    
    result = lwip_selscan(maxfd, &sock_readset, &sock_writeset, &sock_exceptset, timeout);
    
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

#endif
