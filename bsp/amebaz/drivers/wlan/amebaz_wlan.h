/*
 * File      : amebaz_wlan.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
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
 * 2017-5-30      Bernard      the first version
 * 2018-6-12      flyingcys    add amebaz wlan interface
 */
 
#ifndef __AMEBAZ_WLAN_H__
#define __AMEBAZ_WLAN_H__

int amebaz_wifi_scan();

void amebaz_wifi_info_init(void);

int amebaz_wifi_set_sta_info(char *ssid, char *passwd);

int amebaz_wifi_set_ap_info(char *ssid, char *passwd);

int amebaz_wifi_connect(char *ssid, char *passwd);

int amebaz_wifi_disconnect(void);

int amebaz_wifi_ap_start(char *ssid, char *passwd, int channel);

int amebaz_wifi_ap_stop(void);

int amebaz_wifi_get_rssi(void);

void amebaz_wifi_set_channel(int channel);

int amebaz_wifi_get_channel(void);

int amebaz_wifi_init(rt_wlan_mode_t mode);

#endif /* __AMEBAZ_WLAN_H__ */

