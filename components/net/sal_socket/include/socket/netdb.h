/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-02-17     Bernard      First version
 * 2108-05-24     ChenYong     Add socket abstraction layer
 */

#ifndef NETDB_H__
#define NETDB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <sal_netdb.h>

struct hostent *gethostbyname(const char *name);

int gethostbyname_r(const char *name, struct hostent *ret, char *buf,
                size_t buflen, struct hostent **result, int *h_errnop);
void freeaddrinfo(struct addrinfo *ai);
int getaddrinfo(const char *nodename,
       const char *servname,
       const struct addrinfo *hints,
       struct addrinfo **res);

#ifdef __cplusplus
}
#endif

#endif
