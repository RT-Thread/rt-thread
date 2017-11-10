/*
 *  RT-Thread Wi-Fi Device
 *
 * COPYRIGHT (C) 2014 - 2015, Shanghai Real-Thread Technology Co., Ltd
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *
 *  All rights reserved.
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
 * 2014-09-11     Bernard      the first verion
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <lwip/netifapi.h>

#include "wlan_dev.h"
#include "wlan_cmd.h"

#define NIOCTL_SADDR    0x02

void rt_wlan_info_init(struct rt_wlan_info* info, rt_wlan_mode_t mode, rt_wlan_security_t security, 
    char *ssid)
{
    if (info == RT_NULL) return ;

    memset(info, 0x0, sizeof(struct rt_wlan_info));
    info->mode = mode;
    info->security = security;
    if (ssid)
    {
        info->ssid = rt_malloc(strlen((char*)ssid) + 1);
        if (info->ssid)
        {
            strncpy((char*)info->ssid, (char*)ssid, strlen((char*)ssid) + 1);
        }
    }
}

void rt_wlan_info_deinit(struct rt_wlan_info* info)
{
    if (info->ssid)
    {
        rt_free(info->ssid);
        info->ssid = RT_NULL;
    }

    memset(info, 0x0, sizeof(struct rt_wlan_info));
}

int rt_wlan_init(struct rt_wlan_device* device, rt_wlan_mode_t mode)
{
    int result;

    if (device == RT_NULL) return 0;

    result = rt_device_control(RT_DEVICE(device), WIFI_INIT, (void*)&mode);

    return result;
}

int rt_wlan_connect(struct rt_wlan_device* device, struct rt_wlan_info* info, char *password)
{
    int result = 0;

    if (device == RT_NULL) return -RT_EIO;

    if (info != RT_NULL)
    {
        rt_wlan_set_info(device, info);
    }

    result = rt_device_control(RT_DEVICE(device), WIFI_EASYJOIN, (void*)password);
    if (result == RT_EOK)
    {
        struct netif *netif = device->parent.netif;

        netifapi_netif_set_up(netif);
        eth_device_linkchange(&(device->parent), RT_TRUE);

#ifdef RT_LWIP_DHCP
        /* set DHCP flags */
        // netif->flags |= NETIF_FLAG_DHCP;
        /* start DHCP */
        dhcp_start(netif);
#endif

        rt_strncpy((char*)device->key, (char*)password, sizeof(device->key) - 1);
    }

    return result;
}

int rt_wlan_softap(struct rt_wlan_device* device, struct rt_wlan_info* info, char *password)
{
    int result = RT_EOK;

    if (device == RT_NULL) return -RT_EIO;

    if (info != RT_NULL)
    {
        rt_wlan_set_info(device, info);
    }

    result = rt_device_control(RT_DEVICE(device), WIFI_SOFTAP, (void*)password);
    if (result == RT_EOK)
    {
        rt_strncpy((char*)device->key, (char*)password, sizeof(device->key) - 1);

        netifapi_netif_set_up(device->parent.netif);
        eth_device_linkchange(&(device->parent), RT_TRUE);

        wifi_softap_setup_netif(device->parent.netif);
    }

    return result;
}

int rt_wlan_disconnect(struct rt_wlan_device* device)
{
    int result = 0;

    if (device == RT_NULL) return -RT_EIO;

    /* save event handler */
    result = rt_device_control(RT_DEVICE(device), WIFI_DISCONNECT, RT_NULL);
    if (result == RT_EOK)
    {
        netifapi_netif_set_down(device->parent.netif);
        eth_device_linkchange(&(device->parent), RT_FALSE);
    }

    return result;
}

int rt_wlan_set_info(struct rt_wlan_device* device, struct rt_wlan_info* info)
{
    if (device->info == info) return RT_EOK; /* same info */

    if (device->info != RT_NULL)
    {
        rt_wlan_info_deinit(device->info);
        rt_free(device->info);
    }

    device->info = info;

    return RT_EOK;
}

struct rt_wlan_info *rt_wlan_get_info(struct rt_wlan_device* device)
{
    struct rt_wlan_info* info = RT_NULL;

    if (device != RT_NULL)
    {
        info = device->info;
    }

    return info;
}

int rt_wlan_scan(struct rt_wlan_device* device, struct rt_wlan_info *infos, int item_sz)
{
    int result;
    struct rt_wlan_info_request request;

    if (device == RT_NULL) return 0;

    request.req_number = item_sz;
    request.rsp_number = 0;
    request.infos = infos;

    result = rt_device_control(RT_DEVICE(device), WIFI_SCAN, (void*)&request);
    result = result; /* skip warning */

    return request.rsp_number;
}

int rt_wlan_get_rssi(struct rt_wlan_device* device)
{
    int rssi;
    int result;

    if (device == RT_NULL) return 0;
    result = rt_device_control(RT_DEVICE(device), WIFI_GET_RSSI, (void*)&rssi);

    if (result == RT_EOK) return rssi;

    return result;
}

int rt_wlan_get_mac(struct rt_wlan_device* device, rt_uint8_t hwaddr[6])
{
    int result;
    if (device == RT_NULL) return 0;
    result = rt_device_control(RT_DEVICE(device), NIOCTL_GADDR, (void*)hwaddr);
    return result;
}

int rt_wlan_set_mac(struct rt_wlan_device* device, rt_uint8_t hwaddr[6])
{
    int result;
    if (device == RT_NULL) return 0;
    result = rt_device_control(RT_DEVICE(device), NIOCTL_SADDR, (void*)hwaddr);
    return result;
}

int rt_wlan_enter_powersave(struct rt_wlan_device* device, int level)
{
    int result = 0;

    if (device == RT_NULL) return -RT_EIO;

    result = rt_device_control(RT_DEVICE(device), WIFI_ENTER_POWERSAVE, (void*)&level);

    return result;
}

void rt_wlan_set_event_callback(struct rt_wlan_device* device, rt_wlan_event_handler handler, 
    void *user_data)
{
    if (device == RT_NULL) return ;

    device->handler = handler;
    device->user_data = user_data;

    return ;
}
