/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-7-10      tyx          the first version
 */

#include "wifi_structures.h"
#include "wifi_constants.h"
#include <wifi/wifi_util.h>
#include <wifi/wifi_conf.h>
#include "board.h"
#include "drv_wlan.h"

// #define SCAN_WAIT_TIME       (10000)

struct scan_user_data
{
    struct rt_completion done;
    scan_callback_fn fun;
    void *data;
};

extern rthw_mode_t wifi_mode;

rthw_mode_t rthw_wifi_mode_get(void)
{
    return wifi_mode;
}

int rthw_wifi_stop(void)
{
    return wifi_off();
}

int rthw_wifi_start(rthw_mode_t mode)
{
    if(wifi_on(mode) < 0)
    {
        rt_kprintf("ERROR: wifi_on failed\n");
        return -1;
    }
    return 0;
}

int rthw_wifi_connect(char *ssid, int ssid_len, char *password, int pass_len, rthw_security_t security_type)
{
    int mode;
    rtw_wifi_setting_t setting;

    mode = rthw_wifi_mode_get();
    if ((mode != RTHW_MODE_STA) && (mode != RTHW_MODE_STA_AP))
    {
        return -1;
    }
    if(wext_get_mode(WLAN0_NAME, &mode) < 0)
    {
        rt_kprintf("L:%d wifi get mode err\n", __LINE__);
        return -1;
    }
    if(wifi_connect(ssid, security_type, password, ssid_len, pass_len, -1, NULL) != RTW_SUCCESS)
    {
        rt_kprintf("wifi connect fail\n");
        return -1;
    }
    rt_kprintf("wifi connect success\n");
    rt_kprintf("Show Wi-Fi information\n");
    wifi_get_setting(WLAN0_NAME,&setting);
    wifi_show_setting(WLAN0_NAME,&setting);
    return 0;
}

int rthw_wifi_connect_bssid(char *bssid, char *ssid, int ssid_len, char *password, int pass_len, rthw_security_t security_type)
{
    int mode;
    rtw_wifi_setting_t setting;

    mode = rthw_wifi_mode_get();
    if ((mode != RTHW_MODE_STA) && (mode != RTHW_MODE_STA_AP))
    {
        return -1;
    }
    if(wext_get_mode(WLAN0_NAME, &mode) < 0)
    {
        rt_kprintf("L:%d wifi get mode err\n", __LINE__);
        return -1;
    }

    if(wifi_connect_bssid(bssid, ssid, security_type, password, 6, ssid_len, pass_len, -1, NULL) != RTW_SUCCESS)
    {
        rt_kprintf("wifi connect fail\n");
        return -1;
    }
    rt_kprintf("wifi connect success\n");
    rt_kprintf("Show Wi-Fi information\n");
    wifi_get_setting(WLAN0_NAME,&setting);
    wifi_show_setting(WLAN0_NAME,&setting);
    return 0;
}

int rthw_wifi_ap_start(char *ssid, char *password, int channel)
{
    int mode = 0, timeout = 20;
    rtw_security_t security_type = RTW_SECURITY_WPA2_AES_PSK;
    char *name = RT_NULL;

    mode = rthw_wifi_mode_get();
    if (mode == RTHW_MODE_AP)
    {
        name = WLAN0_NAME;
    }
    else if (mode == RTHW_MODE_STA_AP)
    {
        name = WLAN1_NAME;
    }
    else
    {
        return -1;
    }

    if(wext_get_mode(name, &mode) < 0)
    {
        rt_kprintf("L:%d wifi get mode err\n", __LINE__);
        return -1;
    }
    if (password == RT_NULL)
    {
        security_type = RTW_SECURITY_OPEN;
    }

    if(wifi_start_ap(ssid, security_type, password, rt_strlen(ssid), rt_strlen(password), 6) != 0)
    {
        rt_kprintf("ERROR: wifi_start_ap failed\n");
        return -1;
    }

    while(1)
    {
        char essid[33];
        if(wext_get_ssid(name, (unsigned char *) essid) > 0)
        {
            if(strcmp((const char *) essid, (const char *)ssid) == 0)
            {
                rt_kprintf("%s started\n", ssid);
                break;
            }
        }
        if(timeout == 0)
        {
            rt_kprintf("Start AP timeout\n");
            return -1;
        }
        rt_thread_delay(1 * RT_TICK_PER_SECOND);
        timeout --;
    }

    return 0;
}

static int rthw_wifi_disconnect(char *name)
{
    char essid[33];
    int timeout = 20;
    const rt_uint8_t null_bssid[ETH_ALEN + 2] = {0, 0, 0, 0, 0, 1, 0, 0};

    if (name == RT_NULL)
        return -1;

    if (wext_get_ssid(name, (unsigned char *) essid) < 0)
    {
        rt_kprintf("\nWIFI disconnected!\n");
        return -1;
    }

    if (wext_set_bssid(name, null_bssid) < 0)
    {
        rt_kprintf("Failed to set bogus BSSID to disconnect");
        return -1;
    }

    while (1)
    {
        if(wext_get_ssid(name, (unsigned char *) essid) < 0)
        {
            rt_kprintf("WIFI disconnected!\n");
            break;
        }

        if(timeout == 0)
        {
            rt_kprintf("ERROR: Deassoc timeout!\n");
            return -1;
        }

        rt_thread_delay(10);
        timeout --;
    }
    return 0;
}

int rthw_wifi_sta_disconnect(void)
{
    int mode = 0;
    char *name = RT_NULL;

    mode = rthw_wifi_mode_get();
    if (mode == RTHW_MODE_STA)
    {
        name = WLAN0_NAME;
    }
    else if (mode == RTHW_MODE_STA_AP)
    {
        name = WLAN0_NAME;
    }
    else
    {
        return -1;
    }
    return rthw_wifi_disconnect(name);
}

int rthw_wifi_ap_disconnect(void)
{
    int mode = 0;
    char *name = RT_NULL;

    mode = rthw_wifi_mode_get();
    if (mode == RTHW_MODE_AP)
    {
        name = WLAN0_NAME;
    }
    else if (mode == RTHW_MODE_STA_AP)
    {
        name = WLAN1_NAME;
    }
    else
    {
        return -1;
    }
    return rthw_wifi_disconnect(name);
}

int rthw_wifi_rssi_get(void)
{
    int rssi = 0;
    wifi_get_rssi(&rssi);
    return rssi;
}

void rthw_wifi_channel_set(int channel)
{
    wifi_set_channel(channel);
}

int rthw_wifi_channel_get(void)
{
    int channel;
    wifi_get_channel(&channel);
    return channel;
}

static rtw_result_t rthw_wifi_scan_result_handler( rtw_scan_handler_result_t* malloced_scan_result)
{
    struct scan_user_data* user_data = malloced_scan_result->user_data;
    struct rthw_wlan_info info = { 0 };

    if (malloced_scan_result->scan_complete != RTW_TRUE)
    {
        rtw_scan_result_t* record = &malloced_scan_result->ap_details;

        if (user_data->fun != RT_NULL)
        {
            record->SSID.val[record->SSID.len] = 0; /* Ensure the SSID is null terminated */
            info.ssid = record->SSID.val;
            info.bssid = record->BSSID.octet;
            info.band = record->band;
            info.datarate = 0;
            info.channel = record->channel;
            info.rssi = record->signal_strength;
            info.security = record->security;
            user_data->fun(&info, user_data->data);
        }
    }
    else
    {
        user_data->fun(RT_NULL, user_data->data);
        rt_free(user_data);
        rt_kprintf("scan ap down\n");
    }

    return RTW_SUCCESS;
}

int rthw_wifi_scan(scan_callback_fn fun, void *data)
{
    struct scan_user_data *user_data;

    if (fun == RT_NULL)
    {
        rt_kprintf("scan callback fun is null\n");
        return -1;
    }
    user_data = rt_malloc(sizeof(struct scan_user_data));
    if (user_data == RT_NULL)
    {
        rt_kprintf("wifi scan malloc fail\n");
        return -1;
    }
    user_data->fun = fun;
    user_data->data = data;

    if (wifi_scan_networks(rthw_wifi_scan_result_handler, user_data) != RTW_SUCCESS)
    {
        rt_kprintf("ERROR: wifi scan failed\n\r");
        return -1;
    }

    return 0;
}

static rthw_wlan_monitor_callback_t monitor_callback;

static void rthw_wifi_promisc_callback(unsigned char *buf, unsigned int len, void* userdata)
{
    if (monitor_callback)
    {
        monitor_callback(userdata, len, RT_NULL);
    }
}

void rthw_wifi_monitor_callback_set(rthw_wlan_monitor_callback_t callback)
{
    monitor_callback = callback;
}

void rthw_wifi_monitor_enable(int enable)
{
    if (enable)
    {
        wifi_enter_promisc_mode();
        wifi_set_promisc(RTW_PROMISC_ENABLE, rthw_wifi_promisc_callback, 1);
        rt_kprintf("%s run \n", __FUNCTION__);
    }
    else
    {
        wifi_set_promisc(RTW_PROMISC_DISABLE, RT_NULL, 0);
        rthw_wifi_stop();
    }
}
