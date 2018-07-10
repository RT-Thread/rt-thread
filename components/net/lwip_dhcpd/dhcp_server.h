/*
 * File      : dhcp_server.h
 *             A simple DHCP server implementation
 *
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013-2015, Shanghai Real-Thread Technology Co., Ltd
 * http://www.rt-thread.com
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
 * 2013-01-30     aozima       the first version
 * 2013-08-08     aozima       support different network segments.
 * 2015-01-30     bernard      release to RT-Thread RTOS.
 * 2017-12-27     aozima       add [mac-ip] table support.
 */

#ifndef DHCPV4_SERVER_H__
#define DHCPV4_SERVER_H__

#ifdef __cplusplus
extern "C" {
#endif

void dhcpd_start(const char *netif_name);

#ifdef __cplusplus
}
#endif

#endif

