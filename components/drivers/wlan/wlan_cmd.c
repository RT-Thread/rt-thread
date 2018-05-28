/*
 * File      : wlan_cmd.c
 *             Wi-Fi common commands
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2016, RT-Thread Development Team
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
 * 2016-03-12     Bernard      first version
 */

#include <rtthread.h>
#include <wlan_dev.h>

#include <finsh.h>

#include <lwip/dhcp.h>
#include "wlan_cmd.h"

#ifdef LWIP_USING_DHCPD
#include <dhcp_server.h>
#endif

struct rt_wlan_info info;
static char wifi_ssid[32]    = {0};
static char wifi_key[32]     = {0};
static int network_mode      = WIFI_STATION;

#ifndef WIFI_SETTING_FN
#define WIFI_SETTING_FN     "/appfs/setting.json"
#endif

#ifndef WIFI_DEVICE_STA_NAME
#define WIFI_DEVICE_STA_NAME    "w0"
#endif
#ifndef WIFI_DEVICE_AP_NAME
#define WIFI_DEVICE_AP_NAME    "ap"
#endif

#ifdef RT_USING_DFS
#include <dfs_posix.h>
#ifdef PKG_USING_CJSON
#include <cJSON_util.h>
#endif

int wifi_get_mode(void)
{
    return network_mode;
}

int wifi_set_mode(int mode)
{
    network_mode = mode;

    return network_mode;
}

int wifi_set_setting(const char* ssid, const char* pwd)
{
    if (!ssid) return -1;

    strncpy(wifi_ssid, ssid, sizeof(wifi_ssid));
    wifi_ssid[sizeof(wifi_ssid) - 1] = '\0';

    if (pwd)
    {
        strncpy(wifi_key, pwd, sizeof(wifi_key));
        wifi_key[sizeof(wifi_key) - 1] = '\0';
    }
    else wifi_key[0] = '\0';

    return 0;
}

#ifdef PKG_USING_CJSON
int wifi_read_cfg(const char* filename)
{
    int fd;
    cJSON *json = RT_NULL;

    fd = open(filename,O_RDONLY, 0);
    if(fd < 0)
    {
        /* no setting file */
        return -1;
    }

    if (fd >= 0)
    {
        int length;

        length = lseek(fd, 0, SEEK_END);
        if (length)
        {
            char *json_str = (char *) rt_malloc (length);
            if (json_str)
            {
                lseek(fd, 0, SEEK_SET);
                read(fd, json_str, length);

                json = cJSON_Parse(json_str);
                rt_free(json_str);
            }
        }
        close(fd);
    }

    if (json)
    {
        cJSON *wifi = cJSON_GetObjectItem(json, "wifi");
        cJSON *ssid = cJSON_GetObjectItem(wifi, "SSID");
        cJSON *key  = cJSON_GetObjectItem(wifi, "Key");
        cJSON *mode = cJSON_GetObjectItem(wifi, "Mode");

        if (ssid)
        {
            memset(wifi_ssid, 0x0, sizeof(wifi_ssid));
            rt_strncpy(wifi_ssid, ssid->valuestring, sizeof(wifi_ssid) - 1);
        }

        if (key)
        {
            memset(wifi_key, 0x0, sizeof(wifi_key));
            rt_strncpy(wifi_key, key->valuestring, sizeof(wifi_key) - 1);
        }

        if (mode)
        {
            network_mode = mode->valueint;
        }

        cJSON_Delete(json);
    }

    return 0;
}

int wifi_save_cfg(const char* filename)
{
    int fd;
    cJSON *json = RT_NULL;

    fd = open(filename, O_RDONLY, 0);
    if (fd >= 0)
    {
        int length;

        length = lseek(fd, 0, SEEK_END);
        if (length)
        {
            char *json_str = (char *) rt_malloc (length);
            if (json_str)
            {
                lseek(fd, 0, SEEK_SET);
                read(fd, json_str, length);

                json = cJSON_Parse(json_str);
                rt_free(json_str);
            }
        }
        close(fd);
    }
    else
    {
        /* create a new setting.json */
        fd = open(filename, O_WRONLY | O_TRUNC, 0);
        if (fd >= 0)
        {
            json = cJSON_CreateObject();
            if (json)
            {
                cJSON *wifi = cJSON_CreateObject();

                if (wifi)
                {
                    char *json_str;

                    cJSON_AddItemToObject(json, "wifi", wifi);
                    cJSON_AddStringToObject(wifi, "SSID", wifi_ssid);
                    cJSON_AddStringToObject(wifi, "Key", wifi_key);
                    cJSON_AddNumberToObject(wifi, "Mode", network_mode);

                    json_str = cJSON_Print(json);
                    if (json_str)
                    {
                        write(fd, json_str, rt_strlen(json_str));
                        cJSON_free(json_str);
                    }
                }
            }
        }
        close(fd);

        return 0;
    }

    if (json)
    {
        cJSON *wifi = cJSON_GetObjectItem(json, "wifi");
        if (!wifi)
        {
            wifi = cJSON_CreateObject();
            cJSON_AddItemToObject(json, "wifi", wifi);
        }

        if (cJSON_GetObjectItem(wifi, "SSID"))cJSON_ReplaceItemInObject(wifi, "SSID", cJSON_CreateString(wifi_ssid));
        else cJSON_AddStringToObject(wifi, "SSID", wifi_ssid);
        if (cJSON_GetObjectItem(wifi, "Key")) cJSON_ReplaceItemInObject(wifi, "Key", cJSON_CreateString(wifi_key));
        else cJSON_AddStringToObject(wifi, "Key", wifi_key);
        if (cJSON_GetObjectItem(wifi, "Mode")) cJSON_ReplaceItemInObject(wifi, "Mode", cJSON_CreateNumber(network_mode));
        else cJSON_AddNumberToObject(wifi, "Mode", network_mode);

        fd = open(filename, O_WRONLY | O_TRUNC, 0);
        if (fd >= 0)
        {
            char *json_str = cJSON_Print(json);
            if (json_str)
            {
                write(fd, json_str, rt_strlen(json_str));
                cJSON_free(json_str);
            }
            close(fd);
        }
        cJSON_Delete(json);
    }

    return 0;
}
#endif

int wifi_save_setting(void)
{
    #ifdef PKG_USING_CJSON
    wifi_save_cfg(WIFI_SETTING_FN);
    #endif

    return 0;
}
#endif

int wifi_softap_setup_netif(struct netif *netif)
{
    if (netif)
    {
#ifdef RT_LWIP_DHCP
        /* Stop DHCP Client */
        dhcp_stop(netif);
#endif

#ifdef LWIP_USING_DHCPD
        {
            char name[8];
            memset(name, 0, sizeof(name));
            strncpy(name, netif->name, sizeof(name)>sizeof(netif->name)? sizeof(netif->name) : sizeof(name));
            dhcpd_start(name);
        }
#endif
    }

    return 0;
}

int wifi_default(void)
{
    int result = 0;
    struct rt_wlan_device *wlan;

    #ifdef PKG_USING_CJSON
    /* read default setting for wifi */
    wifi_read_cfg(WIFI_SETTING_FN);
    #endif

    if (network_mode == WIFI_STATION)
    {
        /* get wlan device */
        wlan = (struct rt_wlan_device*)rt_device_find(WIFI_DEVICE_STA_NAME);
        if (!wlan)
        {
            rt_kprintf("no wlan:%s device\n", WIFI_DEVICE_STA_NAME);
            return -1;
        }

        /* wifi station */
        rt_wlan_info_init(&info, WIFI_STATION, SECURITY_WPA2_MIXED_PSK, wifi_ssid);
        result =rt_wlan_init(wlan, WIFI_STATION);
        if (result == RT_EOK)
        {
            result = rt_wlan_connect(wlan, &info, wifi_key);
        }
    }
    else
    {
        /* wifi AP */
        /* get wlan device */
        wlan = (struct rt_wlan_device*)rt_device_find(WIFI_DEVICE_AP_NAME);
        if (!wlan)
        {
            rt_kprintf("no wlan:%s device\n", WIFI_DEVICE_AP_NAME);
            return -1;
        }

        rt_wlan_info_init(&info, WIFI_AP, SECURITY_WPA2_AES_PSK, wifi_ssid);
        info.channel = 11;

        /* wifi soft-AP */
        result =rt_wlan_init(wlan, WIFI_AP);
        if (result == RT_EOK)
        {
            result = rt_wlan_softap(wlan, &info, wifi_key);
        }
    }

    return result;
}

static void wifi_usage(void)
{
    rt_kprintf("wifi help     - Help information\n");
    rt_kprintf("wifi cfg SSID PASSWORD - Setting your router AP ssid and pwd\n");
    rt_kprintf("wifi          - Do the default wifi action\n");
    rt_kprintf("wifi wlan_dev scan\n");
    rt_kprintf("wifi wlan_dev join SSID PASSWORD\n");
    rt_kprintf("wifi wlan_dev ap SSID [PASSWORD]\n");    
    rt_kprintf("wifi wlan_dev up\n");
    rt_kprintf("wifi wlan_dev down\n");
    rt_kprintf("wifi wlan_dev rssi\n");
    rt_kprintf("wifi wlan_dev status\n");
}

int wifi(int argc, char** argv)
{
    struct rt_wlan_device *wlan;

    if (argc == 1)
    {
        wifi_default();
        return 0;
    }

    if (strcmp(argv[1], "help") == 0)
    {
        wifi_usage();
        return 0;
    }

    if (strcmp(argv[1], "cfg") == 0)
    {
        /* configure wifi setting */
        memset(wifi_ssid, 0x0, sizeof(wifi_ssid));
        rt_strncpy(wifi_ssid, argv[2], sizeof(wifi_ssid) - 1);

        memset(wifi_key, 0x0, sizeof(wifi_key));
        rt_strncpy(wifi_key, argv[3], sizeof(wifi_key) - 1);

        network_mode = WIFI_STATION;

        #ifdef PKG_USING_CJSON
        wifi_save_cfg(WIFI_SETTING_FN);
        #endif

        return 0;
    }

    /* get wlan device */
    wlan = (struct rt_wlan_device*)rt_device_find(argv[1]);
    if (!wlan)
    {
        rt_kprintf("no wlan:%s device\n", argv[1]);
        return 0;
    }

    if (argc < 3)
    {
        wifi_usage();
        return 0;
    }

    if (strcmp(argv[2], "join") == 0)
    {
        rt_wlan_init(wlan, WIFI_STATION);
        network_mode = WIFI_STATION;

        /* TODO: use easy-join to replace */
        rt_wlan_info_init(&info, WIFI_STATION, SECURITY_WPA2_MIXED_PSK, argv[3]);
        rt_wlan_connect(wlan, &info, argv[4]);
    }
    else if (strcmp(argv[2], "up") == 0)
    {
        /* the key was saved in wlan device */
        rt_wlan_connect(wlan, RT_NULL, wlan->key);
    }
    else if (strcmp(argv[2], "down") == 0)
    {
        rt_wlan_disconnect(wlan);
    }
    else if (strcmp(argv[2], "scan") == 0)
    {
        struct rt_wlan_info *infos;

        infos = (struct rt_wlan_info*)rt_malloc(sizeof(struct rt_wlan_info) * 12);
        if (infos)
        {
            int index, num;

            memset(infos, 0x0, sizeof(struct rt_wlan_info) * 12);
            num = rt_wlan_scan(wlan, infos, 12);

            for (index = 0; index < num; index ++)
            {
                rt_kprintf("----Wi-Fi AP[%d] Information----\n", index);
                rt_kprintf("SSID: %-.32s\n", infos[index].ssid);
                rt_kprintf("rssi: %d\n", infos[index].rssi);
                rt_kprintf(" chn: %d\n", infos[index].channel);
                rt_kprintf("rate: %d\n", infos[index].datarate);
                rt_kprintf("\n");
            }

            /* de-initialize info */
            for (index = 0; index < num; index ++)
            {
                rt_wlan_info_deinit(&infos[index]);
            }
            rt_free(infos);
        }
    }
    else if (strcmp(argv[2], "rssi") == 0)
    {
        int rssi;

        rssi = rt_wlan_get_rssi(wlan);
        rt_kprintf("rssi=%d\n", rssi);
    }
    else if (strcmp(argv[2], "ap") == 0)
    {
        rt_err_t result = RT_EOK;

        if (argc == 4)
        {
            // open soft-AP
            rt_wlan_info_init(&info, WIFI_AP, SECURITY_OPEN, argv[3]);
            info.channel = 11;

            result =rt_wlan_init(wlan, WIFI_AP);
            /* start soft ap */
            result = rt_wlan_softap(wlan, &info, NULL);
            if (result == RT_EOK)
            {
                network_mode = WIFI_AP;
            }
        }
        else if (argc == 5)
        {
            // WPA2 with password
            rt_wlan_info_init(&info, WIFI_AP, SECURITY_WPA2_AES_PSK, argv[3]);
            info.channel = 11;

            result =rt_wlan_init(wlan, WIFI_AP);
            /* start soft ap */
            result = rt_wlan_softap(wlan, &info, argv[4]);
            if (result == RT_EOK)
            {
                network_mode = WIFI_AP;
            }            
        }
        else
        {
            wifi_usage();
        }
        
        if (result != RT_EOK)
        {
            rt_kprintf("wifi start failed! result=%d\n", result);
        }
    }
    else if (strcmp(argv[2], "status") == 0)
    {
        int rssi;

        if (netif_is_link_up(wlan->parent.netif))
        {
            rssi = rt_wlan_get_rssi(wlan);

            rt_kprintf("Wi-Fi AP: %-.32s\n", wlan->info->ssid);
            rt_kprintf("MAC Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", wlan->info->bssid[0],
                    wlan->info->bssid[1],
                    wlan->info->bssid[2],
                    wlan->info->bssid[3],
                    wlan->info->bssid[4],
                    wlan->info->bssid[5]);
            rt_kprintf(" Channel: %d\n", wlan->info->channel);
            rt_kprintf("DataRate: %dMbps\n", wlan->info->datarate/1000);
            rt_kprintf("    RSSI: %d\n", rssi);
        }
        else
        {
            rt_kprintf("wifi disconnected!\n");
        }

        return 0;
    }

    return 0;
}
MSH_CMD_EXPORT(wifi, wifi command);
