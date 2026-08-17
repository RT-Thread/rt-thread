/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TC_AF_UNIX_H__
#define TC_AF_UNIX_H__

#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#include <dfs.h>
#include <dfs_file.h>
#include <rtthread.h>
#include <utest.h>

#ifndef RT_UTEST_DFS_V2_AF_UNIX_DIR
#define RT_UTEST_DFS_V2_AF_UNIX_DIR "/dev"
#endif

#define TC_AF_UNIX_PATH_MAX 64

void tc_af_unix_path(char *buf, rt_size_t size, const char *name);
void tc_af_unix_make_address(struct sockaddr_un *address, const char *path);
void tc_af_unix_closesocket(int *fd);
void tc_af_unix_close(int *fd);
int tc_af_unix_send_rights(int socket_fd, const int *fds, size_t fd_count,
                           char payload);
int tc_af_unix_receive_rights(int socket_fd, int flags, size_t control_length,
                              int *fds, size_t *fd_count, int *message_flags,
                              char *payload);

#endif /* TC_AF_UNIX_H__ */
