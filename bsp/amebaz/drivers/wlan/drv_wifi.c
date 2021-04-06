/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-5-30      Bernard      the first version
 * 2018-5-30      flyingcys    add amebaz wifi driver
 */
#include <skbuff.h>
#include "board.h"
#include <string.h>
#include "drv_wlan.h"
#include "drv_wifi.h"

#define DBG_LVL DBG_INFO
#define DBG_TAG "WIFI"
#include <rtdbg.h>

#define MAX_ADDR_LEN          (6)
#define RT_WLAN_SSID_MAX_LEN  (32)

#define WIFI_INIT_FLAG        (0x1 << 0)
#define WIFI_MAC_FLAG         (0x1 << 1)
#define WIFI_TYPE_STA         (0)
#define WIFI_TYPE_AP          (1)

struct ameba_wifi
{
    struct rt_wlan_device *wlan;
    rt_uint8_t dev_addr[MAX_ADDR_LEN];
    rt_uint8_t flag;
    int connected;
    int type;
};

extern unsigned char rltk_wlan_running(unsigned char idx);
extern struct sk_buff * rltk_wlan_get_recv_skb(int idx);
extern unsigned char rltk_wlan_check_isup(int idx);
extern void rltk_wlan_tx_inc(int idx);
extern struct sk_buff * rltk_wlan_alloc_skb(unsigned int total_len);
extern void rltk_wlan_send_skb(int idx, struct sk_buff *skb);
extern void rltk_wlan_tx_dec(int idx);
extern void rtw_event_register(int event, void (*fun)(char *buf, int len, int flags, void *user_data) , void *user_data);

static const struct rt_wlan_dev_ops ops;

static struct ameba_wifi wifi_sta;
static struct ameba_wifi wifi_ap;

rt_inline struct ameba_wifi *rthw_wifi_get_dev(int idx)
{
    int mode = rthw_wifi_mode_get();

    if (mode == 1) return &wifi_sta;
    if (mode == 2) return &wifi_ap;
    if (idx == 0) return &wifi_sta;
    if (idx == 1) return &wifi_ap;
    return RT_NULL;
}

rt_inline int rthw_wifi_get_idx(struct ameba_wifi *wifi)
{
    int mode = rthw_wifi_mode_get();

    if (mode == 1) return 0;
    if (mode == 2) return 0;
    return wifi->type;
}

int rthw_wifi_register(struct ameba_wifi *wifi)
{
    struct rt_wlan_device *wlan = RT_NULL;

    if ((wifi->flag & WIFI_INIT_FLAG) == 0)
    {
        wlan = rt_malloc(sizeof(struct rt_wlan_device));
        RT_ASSERT(wlan != RT_NULL);
        if (wifi->type == WIFI_TYPE_STA)
        {
            rt_wlan_dev_register(wlan, RT_WLAN_DEVICE_STA_NAME, &ops, 0, wifi);
        }
        if (wifi->type == WIFI_TYPE_AP)
        {
            rt_wlan_dev_register(wlan, RT_WLAN_DEVICE_AP_NAME, &ops, 0, wifi);
        }
        wifi->flag |= WIFI_INIT_FLAG;
        wifi->wlan = wlan;
        LOG_D("F:%s L:%d wifi:0x%08x wlan:0x%08x\n", __FUNCTION__, __LINE__, wifi, wlan);
    }
    return RT_EOK;
}

void netif_post_sleep_processing(void)
{
}

void netif_pre_sleep_processing(void)
{
}

unsigned char *rltk_wlan_get_ip(int idx)
{
    struct ameba_wifi *wifi;

    wifi = rthw_wifi_get_dev(idx);
    if (wifi == RT_NULL)
        return RT_NULL;

    LOG_D("F:%s L:%d is run", __FUNCTION__, __LINE__);

    /* 这里留空了，会不会炸未知 */
    return RT_NULL;
}

int netif_is_valid_IP(int idx, unsigned char *ip_dest)
{
    LOG_D("F:%s L:%d is run ip: %d:%d:%d:%d", __FUNCTION__, __LINE__,
        ip_dest[0], ip_dest[1], ip_dest[2], ip_dest[3]);
    return 1;
}

void rltk_wlan_set_netif_info(int idx, void *dev, rt_uint8_t *dev_addr)
{
    struct ameba_wifi *wifi = RT_NULL;

    wifi = rthw_wifi_get_dev(idx);
    if (wifi == RT_NULL)
        return;
    LOG_D("F:%s L:%d wifi:0x%08x  type:0x%x", __FUNCTION__, __LINE__, wifi, wifi->flag);
    rt_memcpy(wifi->dev_addr, dev_addr, 6);
    wifi->flag |= WIFI_MAC_FLAG;
    rthw_wifi_register(wifi);
    LOG_D("wifi type:%d", wifi->type);
    LOG_D("idx:%d MAC %02x:%02x:%02x:%02x:%02x:%02x", idx, dev_addr[0], dev_addr[1], dev_addr[2], dev_addr[3], dev_addr[4], dev_addr[5]);
}

static void rtw_connect_callbackfn(char *buf, int len, int flags, void *user_data)
{
    struct ameba_wifi *wifi = user_data;

    LOG_D("L:%d wifi connect callback flags:%d user_data:%08x", __LINE__, flags, user_data);
    if( wifi_is_connected_to_ap() == 0)
    {
        wifi->connected = 1;
        rt_wlan_dev_indicate_event_handle(wifi->wlan, RT_WLAN_DEV_EVT_CONNECT, RT_NULL);
    }
}

static void rtw_connect_fail_callbackfn(char *buf, int len, int flags, void *user_data)
{
    struct ameba_wifi *wifi = user_data;

    LOG_D("L:%d wifi connect callback flags:%d", __LINE__, flags);
    wifi->connected = 0;
    rt_wlan_dev_indicate_event_handle(wifi->wlan, RT_WLAN_DEV_EVT_CONNECT_FAIL, RT_NULL);
}

static void rtw_disconnect_callbackfn(char *buf, int len, int flags, void *user_data)
{
    struct ameba_wifi *wifi = user_data;

    LOG_D("L:%d wifi disconnect callback flags:%d", __LINE__, flags);
    wifi->connected = 0;
    rt_wlan_dev_indicate_event_handle(wifi->wlan, RT_WLAN_DEV_EVT_DISCONNECT, RT_NULL);
}

static void rtw_sta_assoc_callbackfn(char *buf, int len, int flags, void *user_data)
{
    LOG_D("L:%d wifi sta assoc callback flags:%d", __LINE__, flags);
}

static void rtw_sta_disassoc_callbackfn(char *buf, int len, int flags, void *user_data)
{
    LOG_D("L:%d wifi sta assoc callback flags:%d buf:%08x %08x", __LINE__, flags, *((rt_uint32_t*)buf), *((rt_uint32_t*)buf + 4));
}

void netif_rx(int idx, unsigned int len)
{
    struct ameba_wifi *wifi = RT_NULL;
    struct sk_buff *skb = RT_NULL;

    wifi = rthw_wifi_get_dev(idx);
    if (wifi == RT_NULL)
        return;

    LOG_D("F:%s L:%d idx:%d len:%d", __FUNCTION__, __LINE__, idx, len);
    if((!wifi->connected) || (!rltk_wlan_running(idx)))
        return;

    skb = (struct sk_buff *)rltk_wlan_get_recv_skb(idx);
    if(!skb)
    {
        LOG_D("netif_rx rltk_wlan_get_recv_skb NULL.");
        return;
    }
    rt_wlan_dev_report_data(wifi->wlan, skb->data, len);
}

static rt_wlan_security_t security_map_from_ameba(rthw_security_t security)
{
    rt_wlan_security_t result = SECURITY_OPEN;

    switch (security)
    {
    case RTHW_SECURITY_OPEN: result = SECURITY_OPEN; break;
    case RTHW_SECURITY_WEP_PSK: result = SECURITY_WEP_PSK; break;
    case RTHW_SECURITY_WEP_SHARED: result = SECURITY_WEP_SHARED; break;
    case RTHW_SECURITY_WPA_TKIP_PSK: result = SECURITY_WPA_TKIP_PSK; break;
    case RTHW_SECURITY_WPA_AES_PSK: result = SECURITY_WPA_AES_PSK; break;
    case RTHW_SECURITY_WPA2_AES_PSK: result = SECURITY_WPA2_AES_PSK; break;
    case RTHW_SECURITY_WPA2_TKIP_PSK: result = SECURITY_WPA2_TKIP_PSK; break;
    case RTHW_SECURITY_WPA2_MIXED_PSK: result = SECURITY_WPA2_MIXED_PSK; break;
    case RTHW_SECURITY_WPA_WPA2_MIXED: result = SECURITY_WPA2_AES_PSK; break;
    case RTHW_SECURITY_WPS_OPEN: result = SECURITY_WPS_OPEN; break;
    case RTHW_SECURITY_WPS_SECURE: result = SECURITY_WPS_SECURE; break;
    default: result = -1; break;
    }

    return result;
}

static rthw_security_t security_map_from_rtthread(rt_wlan_security_t security)
{
    rt_wlan_security_t result = RTHW_SECURITY_OPEN;

    switch (security)
    {
    case SECURITY_OPEN:                result = RTHW_SECURITY_OPEN;             break;
    case SECURITY_WEP_PSK:             result = RTHW_SECURITY_WEP_PSK;          break;
    case SECURITY_WEP_SHARED:          result = RTHW_SECURITY_WEP_SHARED;       break;
    case SECURITY_WPA_TKIP_PSK:        result = RTHW_SECURITY_WPA_TKIP_PSK;     break;
    case SECURITY_WPA_AES_PSK:         result = RTHW_SECURITY_WPA_AES_PSK;      break;
    case SECURITY_WPA2_AES_PSK:        result = RTHW_SECURITY_WPA2_AES_PSK;     break;
    case SECURITY_WPA2_TKIP_PSK:       result = RTHW_SECURITY_WPA2_TKIP_PSK;    break;
    case SECURITY_WPA2_MIXED_PSK:      result = RTHW_SECURITY_WPA2_MIXED_PSK;   break;
    case SECURITY_WPS_OPEN:            result = RTHW_SECURITY_WPS_OPEN;         break;
    case SECURITY_WPS_SECURE:          result = RTHW_SECURITY_WPS_SECURE;       break;
    default: result = -1; break;
    }

    return result;
}

static void rt_ameba_wifi_scan_callback(struct rthw_wlan_info *info, void *user_data)
{
    struct rt_wlan_info wlan_info = { 0 };
    struct rt_wlan_buff buff;
    struct ameba_wifi *wifi = user_data;

    if (info == RT_NULL)
    {
        rt_wlan_dev_indicate_event_handle(wifi->wlan, RT_WLAN_DEV_EVT_SCAN_DONE, RT_NULL);
        return;
    }
    memcpy(&wlan_info.bssid[0], info->bssid, 6);
    strncpy(&wlan_info.ssid.val[0], info->ssid, RT_WLAN_SSID_MAX_LEN);
    wlan_info.ssid.len = strlen(&wlan_info.ssid.val[0]);
    wlan_info.band = info->band == RTHW_802_11_BAND_2_4GHZ ? RTHW_802_11_BAND_2_4GHZ : RTHW_802_11_BAND_5GHZ;
    wlan_info.channel = info->channel;
    wlan_info.datarate = info->datarate * 1000;
    wlan_info.security = security_map_from_ameba(info->security);
    wlan_info.rssi = info->rssi;

    buff.data = &wlan_info;
    buff.len = sizeof(wlan_info);
    rt_wlan_dev_indicate_event_handle(wifi->wlan, RT_WLAN_DEV_EVT_SCAN_REPORT, &buff);
}

static void rthw_wlan_monitor_callback(rt_uint8_t *data, int len, void *user_data)
{
    rt_wlan_dev_promisc_handler(wifi_sta.wlan, data, len);
}

static rt_err_t rthw_wlan_init                 (struct rt_wlan_device *wlan)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return RT_EOK;
}

static rt_err_t rthw_wlan_mode                 (struct rt_wlan_device *wlan, rt_wlan_mode_t mode)
{
    struct ameba_wifi *wifi = (struct ameba_wifi *)(wlan->user_data);

    LOG_D("F:%s L:%d mode:%d", __FUNCTION__, __LINE__, mode);

    if (mode == RT_WLAN_STATION)
    {
        if (wifi->type != WIFI_TYPE_STA)
        {
            LOG_D("this wlan not support sta mode");
            return -RT_ERROR;
        }
    }
    else if (mode == RT_WLAN_AP)
    {
        if (wifi->type != WIFI_TYPE_AP)
        {
            LOG_D("this wlan not support ap mode");
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}

static rt_err_t rthw_wlan_scan                 (struct rt_wlan_device *wlan, struct rt_scan_info *scan_info)
{
    struct ameba_wifi *wifi = (struct ameba_wifi *)(wlan->user_data);

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    LOG_D("F:%s L:%d wifi:0x%08x type:0x%x", __FUNCTION__, __LINE__, wifi, wifi->type);

    if (wifi->type != WIFI_TYPE_STA)
    {
        LOG_D("this wlan not support scan mode");
        return -RT_ERROR;
    }
    if (rthw_wifi_mode_get() == RTHW_MODE_NONE)
    {
        if(rthw_wifi_start(RTHW_MODE_STA_AP) != RT_EOK)
        {
            LOG_D("L:%d wifistart failed...", __LINE__);
            return -1;
        }
    }
    rthw_wifi_scan(rt_ameba_wifi_scan_callback, wifi);
    return RT_EOK;
}

static rt_err_t rthw_wlan_join                 (struct rt_wlan_device *wlan, struct rt_sta_info *sta_info)
{
    struct ameba_wifi *wifi = (struct ameba_wifi *)(wlan->user_data);
    int result = 0, i;
    char *ssid = RT_NULL, *key = RT_NULL;

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    if (wifi->type != WIFI_TYPE_STA)
    {
        LOG_E("this wlan not support sta mode");
        return -RT_ERROR;
    }
    if ((rthw_wifi_mode_get() != RTHW_MODE_STA) && (rthw_wifi_mode_get() != RTHW_MODE_STA_AP))
    {
        rthw_wifi_stop();
        rt_thread_delay(RT_TICK_PER_SECOND / 10);
        if (rthw_wifi_start(RTHW_MODE_STA_AP) != RT_EOK)
        {
            LOG_E("wifi on failed, join fail");
            return -RT_ERROR;
        }
    }
    for (i = 0; i < RT_WLAN_BSSID_MAX_LENGTH; i++)
    {
        if (sta_info->bssid[i] != 0xff || sta_info->bssid[i] != 0x00)
            break;
    }
    if (i < RT_WLAN_BSSID_MAX_LENGTH)
    {
        if (sta_info->ssid.len > 0)
            ssid = &sta_info->ssid.val[0];
        if (sta_info->key.len > 0)
            key = &sta_info->key.val[0];
            LOG_D("bssid connect bssid: %02x:%02x:%02x:%02x:%02x:%02x ssid:%s ssid_len:%d key:%s key_len%d",
            sta_info->bssid[0],sta_info->bssid[1],sta_info->bssid[2],sta_info->bssid[3],sta_info->bssid[4],sta_info->bssid[5],
            ssid,
            sta_info->ssid.len,
            key,
            sta_info->key.len
            );
        result = rthw_wifi_connect_bssid(sta_info->bssid, ssid, sta_info->ssid.len, key, sta_info->key.len, security_map_from_rtthread(sta_info->security));
    }
    else
    {
        result = rthw_wifi_connect(sta_info->ssid.val, sta_info->ssid.len, sta_info->key.val, sta_info->key.len, security_map_from_rtthread(sta_info->security));
    }
    if (result != 0)
    {
        LOG_E("amebaz_wifi_connect failed...");
        return -RT_ERROR;
    }
    // netif_set_connected((struct ameba_wifi *)wlan, 1);
    LOG_D("amebaz_wifi_connect do");
    return RT_EOK;
}

static rt_err_t rthw_wlan_softap               (struct rt_wlan_device *wlan, struct rt_ap_info *ap_info)
{
    struct ameba_wifi *wifi = (struct ameba_wifi *)(wlan->user_data);

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    if (wifi->type != WIFI_TYPE_AP)
    {
        LOG_E("this wlan not support ap mode");
        return -RT_ERROR;
    }
    if (rthw_wifi_ap_start(&ap_info->ssid.val[0], &ap_info->key.val[0], ap_info->channel) != 0)
    {
        rt_wlan_dev_indicate_event_handle(wifi->wlan, RT_WLAN_DEV_EVT_AP_STOP, RT_NULL);
        wifi->connected = 0;
        return -RT_ERROR;
    }
    rt_wlan_dev_indicate_event_handle(wifi->wlan, RT_WLAN_DEV_EVT_AP_START, RT_NULL);
    wifi->connected = 1;
    return RT_EOK;
}

static rt_err_t rthw_wlan_disconnect           (struct rt_wlan_device *wlan)
{
    struct ameba_wifi *wifi = (struct ameba_wifi *)(wlan->user_data);

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    if (wifi->type != WIFI_TYPE_STA)
    {
        LOG_E("this wlan not support sta mode");
        return -RT_ERROR;
    }
    wifi->connected = 0;
    rthw_wifi_sta_disconnect();
    rt_wlan_dev_indicate_event_handle(wifi->wlan, RT_WLAN_DEV_EVT_AP_STOP, RT_NULL);
    return RT_EOK;
}

static rt_err_t rthw_wlan_ap_stop              (struct rt_wlan_device *wlan)
{
    struct ameba_wifi *wifi = (struct ameba_wifi *)(wlan->user_data);

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    if (wifi->type != WIFI_TYPE_AP)
    {
        LOG_E("this wlan not support ap mode");
        return -RT_ERROR;
    }

    rthw_wifi_ap_disconnect();
    return RT_EOK;
}

static rt_err_t rthw_wlan_ap_deauth            (struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return RT_EOK;
}

static rt_err_t rthw_wlan_scan_stop            (struct rt_wlan_device *wlan)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return RT_EOK;
}

static int rthw_wlan_get_rssi                  (struct rt_wlan_device *wlan)
{
    struct ameba_wifi *wifi = (struct ameba_wifi *)(wlan->user_data);

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    if (wifi->type != WIFI_TYPE_STA)
    {
        LOG_E("this wlan not support sta mode");
        return -RT_ERROR;
    }

    return rthw_wifi_rssi_get();
}

static rt_err_t rthw_wlan_set_powersave            (struct rt_wlan_device *wlan, int level)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return RT_EOK;
}

static int rthw_wlan_get_powersave            (struct rt_wlan_device *wlan)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return 0;
}

static rt_err_t rthw_wlan_cfg_promisc          (struct rt_wlan_device *wlan, rt_bool_t start)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    if(start)
    {
        rthw_wifi_monitor_callback_set(rthw_wlan_monitor_callback);
        rthw_wifi_monitor_enable(1);
    }
    else
    {
        rthw_wifi_monitor_callback_set(RT_NULL);
        rthw_wifi_monitor_enable(0);
    }
    return RT_EOK;
}

static rt_err_t rthw_wlan_cfg_filter           (struct rt_wlan_device *wlan, struct rt_wlan_filter *filter)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return RT_EOK;
}

static rt_err_t rthw_wlan_set_channel          (struct rt_wlan_device *wlan, int channel)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    rthw_wifi_channel_set(channel);

    return RT_EOK;
}

static int rthw_wlan_get_channel               (struct rt_wlan_device *wlan)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    return rthw_wifi_channel_get();
}

static rt_err_t rthw_wlan_set_country          (struct rt_wlan_device *wlan, rt_country_code_t country_code)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return RT_EOK;
}

static rt_country_code_t rthw_wlan_get_country (struct rt_wlan_device *wlan)
{
    LOG_D("F:%s L:%d\n", __FUNCTION__, __LINE__);
    return RT_EOK;
}

static rt_err_t rthw_wlan_set_mac              (struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return -RT_ERROR;
}

static rt_err_t rthw_wlan_get_mac              (struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    struct ameba_wifi *wifi = (struct ameba_wifi *)wlan->user_data;

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    if(mac == RT_NULL)
    {
        return -RT_ERROR;
    }
    memcpy(mac, wifi->dev_addr, MAX_ADDR_LEN);
    return RT_EOK;
}

static int rthw_wlan_recv                      (struct rt_wlan_device *wlan, void *buff, int len)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return RT_EOK;
}

static int rthw_wlan_send                      (struct rt_wlan_device *wlan, void *buff, int len)
{
    struct ameba_wifi *wifi = (struct ameba_wifi *)wlan->user_data;
    int idx = rthw_wifi_get_idx(wifi);
    rt_base_t level;
    struct sk_buff *skb = RT_NULL;

    LOG_D("F:%s L:%d len:%d", __FUNCTION__, __LINE__, len);

    level = rt_hw_interrupt_disable();
    if(!wifi->connected || !rltk_wlan_check_isup(idx))
    {
        rt_hw_interrupt_enable(level);
        return -RT_ERROR;
    }
    rltk_wlan_tx_inc(idx);
    rt_hw_interrupt_enable(level);

    skb = (struct sk_buff *)rltk_wlan_alloc_skb(len);
    if (skb == RT_NULL)
    {
        LOG_W("rltk_wlan_alloc_skb NULL for WIFI TX.");
        goto exit;
    }
    /* copy buff to a whole ETH frame */
    memcpy(skb->tail, buff, len);
    skb_put(skb, len);
    rltk_wlan_send_skb(idx, skb);

exit:
    level = rt_hw_interrupt_disable();
    rltk_wlan_tx_dec(idx);
    rt_hw_interrupt_enable(level);

    LOG_D("F:%s L:%d end", __FUNCTION__, __LINE__);

    return RT_EOK;
}

static const struct rt_wlan_dev_ops ops =
{
    .wlan_init             =     rthw_wlan_init           ,
    .wlan_mode             =     rthw_wlan_mode           ,
    .wlan_scan             =     rthw_wlan_scan           ,
    .wlan_join             =     rthw_wlan_join           ,
    .wlan_softap           =     rthw_wlan_softap         ,
    .wlan_disconnect       =     rthw_wlan_disconnect     ,
    .wlan_ap_stop          =     rthw_wlan_ap_stop        ,
    .wlan_ap_deauth        =     rthw_wlan_ap_deauth      ,
    .wlan_scan_stop        =     rthw_wlan_scan_stop      ,
    .wlan_get_rssi         =     rthw_wlan_get_rssi       ,
    .wlan_set_powersave    =     rthw_wlan_set_powersave  ,
    .wlan_get_powersave    =     rthw_wlan_get_powersave  ,
    .wlan_cfg_promisc      =     rthw_wlan_cfg_promisc    ,
    .wlan_cfg_filter       =     rthw_wlan_cfg_filter     ,
    .wlan_set_channel      =     rthw_wlan_set_channel    ,
    .wlan_get_channel      =     rthw_wlan_get_channel    ,
    .wlan_set_country      =     rthw_wlan_set_country    ,
    .wlan_get_country      =     rthw_wlan_get_country    ,
    .wlan_set_mac          =     rthw_wlan_set_mac        ,
    .wlan_get_mac          =     rthw_wlan_get_mac        ,
    .wlan_recv             =     rthw_wlan_recv           ,
    .wlan_send             =     rthw_wlan_send           ,
};

int rthw_wifi_low_init(void)
{
    static rt_int8_t _init_flag = 0;

    if (_init_flag)
    {
        return 1;
    }
    rt_memset(&wifi_sta, 0, sizeof(wifi_sta));
    rt_memset(&wifi_ap, 0, sizeof(wifi_ap));
    wifi_sta.type = WIFI_TYPE_STA;
    wifi_ap.type = WIFI_TYPE_AP;
    if(rthw_wifi_start(RTHW_MODE_STA_AP) != RT_EOK)
    {
        LOG_E("amebaz_wifi_start failed...");
        return -1;
    }
    LOG_I("amebaz_wifi_start success");
    LOG_D("F:%s L:%d wifi_sta:0x%08x   wifi_ap:0x%08x", __FUNCTION__, __LINE__, &wifi_sta, &wifi_ap);

    wifi_reg_event_handler(RTHW_WIFI_EVENT_FOURWAY_HANDSHAKE_DONE, rtw_connect_callbackfn, &wifi_sta);
    wifi_reg_event_handler(RTHW_WIFI_EVENT_DISCONNECT, rtw_disconnect_callbackfn, &wifi_sta);

    _init_flag = 1;

    return 0;
}
INIT_DEVICE_EXPORT(rthw_wifi_low_init);
