/*
This file is part of UFFS, the Ultra-low-cost Flash File System.

Copyright (C) 2005-2009 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

UFFS is free software; you can redistribute it and/or modify it under
the GNU Library General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any
later version.

UFFS is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
or GNU Library General Public License, as applicable, for more details.

You should have received a copy of the GNU General Public License
and GNU Library General Public License along with UFFS; if not, write
to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA  02110-1301, USA.

As a special exception, if other files instantiate templates or use
macros or inline functions from this file, or you compile this file
and link it with other works to produce a work based on this file,
this file does not by itself cause the resulting work to be covered
by the GNU General Public License. However the source code for this
file must still be made available in accordance with section (3) of
the GNU General Public License v2.

This exception does not invalidate any other reasons why a work based
on this file might be covered by the GNU General Public License.
*/

/**
* \file api_test_client_posix.c
* \brief API test client functions
* \author Ricky Zheng, created in 20 Dec, 2011
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

#include "uffs/uffs_fd.h"
#include "api_test.h"


static int _io_read(int fd, void *buf, int len)
{
    return recv(fd, buf, len, MSG_WAITALL);
}

static int _io_write(int fd, const void *buf, int len)
{
    return send(fd, buf, len, 0);
}

static int _io_open(void *addr)
{
    int sock;
    struct hostent *host;
    struct sockaddr_in server_addr;
	int port = SRV_PORT;

    host = gethostbyname((const char *)addr);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket");
        return -1;
    }

	if (getenv("UFFS_TEST_SRV_PORT")) {
		port = atoi(getenv("UFFS_TEST_SRV_PORT"));
	}

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(server_addr.sin_zero),8);

    if (connect(sock, (struct sockaddr *)&server_addr,
                sizeof(struct sockaddr)) == -1)
    {
        perror("Connect");
        return -1;
    }

    return sock;
}

static int _io_close(int fd)
{
    return close(fd);
}

static struct uffs_ApiSrvIoSt m_io = {
    .open = _io_open,
    .read = _io_read,
    .write = _io_write,
    .close = _io_close,
    .addr = (void *)"127.0.0.1",
};

int api_client_init(const char *server_addr)
{
	static char addr[128] = {0};
	int ret = -1;
	
	if (server_addr == NULL)
		server_addr = getenv("UFFS_TEST_SRV_ADDR");

	if (server_addr && strlen(server_addr) < sizeof(addr)) {
		strcpy(addr, server_addr);
		m_io.addr = (void *)addr;
	}
	ret = apisrv_setup_io(&m_io);

	return ret;
}

