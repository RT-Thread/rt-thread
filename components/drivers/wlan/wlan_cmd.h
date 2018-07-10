/*
 * File      : wlan_cmd.h
 *             Wi-Fi common commands
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
 * 2018-06-05     RT-Thread    first version
 */

#ifndef WLAN_CMD_H__
#define WLAN_CMD_H__

struct netif;

int wifi_get_mode(void);
int wifi_set_mode(int mode);

/* do the wifi default action: read wifi setting and then join or start soft-AP */
int wifi_default(void);
/* setup netif for soft-ap */
int wifi_softap_setup_netif(struct netif *netif);

int wifi_set_setting(const char *ssid, const char *pwd);

#ifdef PKG_USING_CJSON
int wifi_read_cfg(const char *filename);
int wifi_save_cfg(const char *filename);
#endif
/* save wifi setting with default storage file */
int wifi_save_setting(void);

extern struct rt_wlan_info info;

#endif
