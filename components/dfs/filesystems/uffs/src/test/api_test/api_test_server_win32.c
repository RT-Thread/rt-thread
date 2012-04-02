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
 * \file api_test_server_win32.c
 * \brief uffs API test server.
 * \author Ricky Zheng
 */

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#include "api_test.h"

#pragma comment(lib, "Ws2_32.lib")

#define BACKLOGS	10

static int _io_read(int fd, void *buf, int len)
{
    return recv((SOCKET)fd, buf, len, 0);
}

static int _io_write(int fd, const void *buf, int len)
{
    return send((SOCKET)fd, buf, len, 0);
}

static int _io_close(int fd)
{
	closesocket((SOCKET)fd);

    return 0;
}

static struct uffs_ApiSrvIoSt m_io = {
	NULL,			// open
    _io_read,
    _io_write,
    _io_close,
};

static struct uffs_ApiSt m_api = {
    uffs_version,
    uffs_open,
    uffs_close,
    uffs_read,
    uffs_write,
    uffs_flush,
    uffs_seek,
    uffs_tell,
    uffs_eof,
    uffs_rename,
    uffs_remove,
    uffs_ftruncate,
    uffs_mkdir,
    uffs_rmdir,
    uffs_stat,
    uffs_lstat,
    uffs_fstat,
    uffs_opendir,
    uffs_closedir,
    uffs_readdir,
    uffs_rewinddir,
    uffs_get_error,
    uffs_set_error,
    uffs_format,
    uffs_space_total,
    uffs_space_used,
    uffs_space_free,
	uffs_flush_all,
};

int api_server_start(void)
{
	int iResult;
	int ret;
	WSADATA wsaData;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

	char port_buf[16];

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return -1;
	}

	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
	sprintf_s(port_buf, sizeof(port_buf), "%d", SRV_PORT);
    iResult = getaddrinfo("0.0.0.0", port_buf, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        ret = -1;
        goto ext;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        ret = -1;
        goto ext;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        ret = -1;
        goto ext;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        ret = -1;
        goto ext;
    }

	apisrv_setup_io(&m_io);

	ret = -1;
	do {
		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			continue;
		}
		ret = apisrv_serve((int)ClientSocket, &m_api);
		closesocket(ClientSocket);
	} while (ret >= 0);

ext:
    WSACleanup();

	return ret;
}
