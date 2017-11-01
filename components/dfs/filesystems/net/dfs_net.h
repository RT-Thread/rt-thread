/*
 * File      : dfs_net.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015-2016, RT-Thread Development Team
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
 * 2016-05-05     Bernard      rename dfs_lwip to dfs_net.
 */

#ifndef DFS_NET_H__
#define DFS_NET_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <lwip/sockets.h>

const struct dfs_file_ops* dfs_net_get_fops(void);
int dfs_net_getsocket(int fd);

#ifdef __cplusplus
}
#endif

#endif

