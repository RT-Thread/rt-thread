/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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

