/*
 * File      : netdb.c
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
 * 2015-02-17     Bernard      First version
 */

#include "netdb.h"
#include <lwip/netdb.h>

struct hostent *gethostbyname(const char *name)
{
    return lwip_gethostbyname(name);
}
RTM_EXPORT(gethostbyname);

int gethostbyname_r(const char *name, struct hostent *ret, char *buf,
                size_t buflen, struct hostent **result, int *h_errnop)
{
    return lwip_gethostbyname_r(name, ret, buf, buflen, result, h_errnop);
}

void freeaddrinfo(struct addrinfo *ai)
{
    lwip_freeaddrinfo(ai);
}
RTM_EXPORT(freeaddrinfo);

int getaddrinfo(const char *nodename,
       const char *servname,
       const struct addrinfo *hints,
       struct addrinfo **res)
{
    return lwip_getaddrinfo(nodename, servname, hints, res);
}
RTM_EXPORT(getaddrinfo);
