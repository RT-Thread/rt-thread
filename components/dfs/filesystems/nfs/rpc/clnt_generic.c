/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
/* @(#)clnt_generic.c   2.2 88/08/01 4.0 RPCSRC */
/*
 * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
 * unrestricted use provided that this legend is included on all tape
 * media and as a part of the software program in whole or part.  Users
 * may copy or modify Sun RPC without charge, but are not authorized
 * to license or distribute it to anyone else except as part of a product or
 * program developed by the user.
 *
 * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
 * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 *
 * Sun RPC is provided with no support and without any obligation on the
 * part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 *
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
 * OR ANY PART THEREOF.
 *
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 *
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043
 */
#if !defined(lint) && defined(SCCSIDS)
static char sccsid[] = "@(#)clnt_generic.c 1.4 87/08/11 (C) 1987 SMI";
#endif
/*
 * Copyright (C) 1987, Sun Microsystems, Inc.
 */
#include <rpc/rpc.h>
#include <string.h>

/*
 * Generic client creation: takes (hostname, program-number, protocol) and
 * returns client handle. Default options are set, which the user can
 * change using the rpc equivalent of ioctl()'s.
 */
CLIENT *clnt_create(const char *hostname, const unsigned long prog,
                    const unsigned long vers, const char *proto)
{
    int sock;
    struct sockaddr_in server;
    struct addrinfo hint, *res = NULL;
    struct timeval tv;
    CLIENT *client;
    int ret;

    memset(&hint, 0, sizeof(hint));
    ret = getaddrinfo(hostname, NULL, &hint, &res);
    if (ret != 0)
    {
        rt_kprintf("getaddrinfo err: %d '%s'\n", ret, hostname);
        return NULL;
    }

    memcpy(&server, res->ai_addr, sizeof(struct sockaddr_in));
    freeaddrinfo(res);

    sock = -1;
    if (strcmp(proto, "udp") == 0)
    {
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        client = clntudp_create(&server, prog, vers, tv, &sock);
        if (client == NULL) return NULL;
        tv.tv_sec = 1;
        clnt_control(client, CLSET_TIMEOUT, (char *)&tv);
    }
    else
    {
        rt_kprintf("unknow protocol\n");
        return NULL;
    }

    return (client);
}

void clnt_perror(CLIENT *rpch, const char *s)
{
    rt_kprintf("rpc client error:%s\n", s);
}
