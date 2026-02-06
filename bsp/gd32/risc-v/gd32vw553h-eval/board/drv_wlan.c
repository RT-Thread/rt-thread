/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-12-25     RT-Thread    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#ifdef RT_USING_WIFI
#include "drv_wlan.h"
#include "gd32vw55x_platform.h"
#include "wifi_management.h"
#include "wifi_init.h"

#define DBG_TAG "drv.wlan"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

enum {
    WIFI_VIF_STA = 0,
    WIFI_VIF_AP,
    WIFI_VIF_MAX
};

/* GD32VW553H WiFi device structure */
struct gd32_wlan_device
{
    struct rt_wlan_device *wlan;
    rt_uint8_t if_idx;      /* Interface index: 0 - STA, 1 - AP */
    rt_uint8_t dev_addr[MAC_ADDR_LEN];  /* MAC address */
};

static struct gd32_wlan_device wlan_sta_device;
static struct gd32_wlan_device wlan_ap_device;

/**
 * @brief WiFi initialization callback
 */
static rt_err_t gd32_wlan_init(struct rt_wlan_device *wlan)
{
    LOG_D("WiFi device init: %s", wlan->name);

    return RT_EOK;
}

/**
 * @brief WiFi mode configuration
 */
static rt_err_t gd32_wlan_mode(struct rt_wlan_device *wlan, rt_wlan_mode_t mode)
{
    LOG_D("Set WiFi mode: %d", mode);

    /* TODO: Set WiFi mode (STA/AP/STA+AP) */

    return RT_EOK;
}

static inline int wifi_freq_to_channel(uint16_t freq)
{
    if ((freq >= 2412) && (freq <= 2484)) {
        if (freq == 2484)
            return 14;
        else
            return (freq - 2407) / 5;
    }
    return 0;
}

static void scan_done_callback(void *eloop_data, void *user_ctx)
{
    int idx;
    struct macif_scan_results *results = RT_NULL;
    struct mac_scan_result *bss_info = RT_NULL;
    struct rt_wlan_info wlan_info;
    struct rt_wlan_buff buff;

    results = (struct macif_scan_results *)rt_malloc(sizeof(struct macif_scan_results));
    if (RT_NULL == results) {
        LOG_E("Failed to allocate memory for scan results\r\n");
        return;
    }

    if (wifi_netlink_scan_results_get(WIFI_VIF_STA, results)) {
        rt_free(results);
        rt_kprintf("WIFI scan results get failed\r\n");
        return;
    }

    for (idx = 0; idx < results->result_cnt; idx++) {
        bss_info = &results->result[idx];

        rt_memset(&wlan_info, 0, sizeof(wlan_info));

        rt_memcpy(&wlan_info.bssid[0], (char *)bss_info->bssid.array, MAC_ADDR_LEN);
        rt_memcpy(wlan_info.ssid.val, (char *)bss_info->ssid.array, bss_info->ssid.length);
        wlan_info.ssid.len = bss_info->ssid.length;
        wlan_info.hidden = bss_info->ssid.length > 0 ? 0 : 1;

        wlan_info.channel = wifi_freq_to_channel(bss_info->chan->freq);
        wlan_info.rssi = bss_info->rssi;
        wlan_info.band = RT_802_11_BAND_2_4GHZ;

        wlan_info.security = SECURITY_UNKNOWN;

        if (bss_info->akm & CO_BIT(MAC_AKM_NONE)) {
            wlan_info.security = SECURITY_OPEN;
        } else if (bss_info->akm == CO_BIT(MAC_AKM_PRE_RSN)) {
            wlan_info.security = SECURITY_WEP_PSK;
        } else if (bss_info->akm & CO_BIT(MAC_AKM_PRE_RSN)) {  // WPA
            if (bss_info->pairwise_cipher & CO_BIT(MAC_CIPHER_TKIP)) {
                wlan_info.security = SECURITY_WPA_TKIP_PSK;
            } else if (bss_info->pairwise_cipher & CO_BIT(MAC_CIPHER_CCMP)) {
                wlan_info.security = SECURITY_WPA_AES_PSK;
            }
        } else {  // WPA2
            if ((bss_info->pairwise_cipher & CO_BIT(MAC_CIPHER_TKIP)) &&
                (bss_info->pairwise_cipher & CO_BIT(MAC_CIPHER_CCMP))) {
                wlan_info.security = SECURITY_WPA2_MIXED_PSK;
            } else if (bss_info->pairwise_cipher & CO_BIT(MAC_CIPHER_TKIP)) {
                wlan_info.security = SECURITY_WPA2_TKIP_PSK;
            } else if (bss_info->pairwise_cipher & CO_BIT(MAC_CIPHER_CCMP)) {
                wlan_info.security = SECURITY_WPA2_AES_PSK;
            }
        }

        buff.data = &wlan_info;
        buff.len = sizeof(wlan_info);
        rt_wlan_dev_indicate_event_handle(wlan_sta_device.wlan, RT_WLAN_DEV_EVT_SCAN_REPORT, &buff);
    }

    rt_free(results);
    rt_wlan_dev_indicate_event_handle(wlan_sta_device.wlan, RT_WLAN_DEV_EVT_SCAN_DONE, RT_NULL);

    eloop_event_unregister(WIFI_MGMT_EVENT_SCAN_DONE);
    eloop_event_unregister(WIFI_MGMT_EVENT_SCAN_FAIL);
}

static void scan_fail_callback(void *eloop_data, void *user_ctx)
{
    rt_kprintf("WIFI_SCAN: failed\r\n");
    eloop_event_unregister(WIFI_MGMT_EVENT_SCAN_DONE);
    eloop_event_unregister(WIFI_MGMT_EVENT_SCAN_FAIL);
}

/**
 * @brief WiFi scan
 */
static rt_err_t gd32_wlan_scan(struct rt_wlan_device *wlan, struct rt_scan_info *scan_info)
{
    // rt_kprintf("WiFi scan start\r\n");

    eloop_event_register(WIFI_MGMT_EVENT_SCAN_DONE, scan_done_callback, NULL, NULL);
    eloop_event_register(WIFI_MGMT_EVENT_SCAN_FAIL, scan_fail_callback, NULL, NULL);

    if (wifi_management_scan(false, NULL)) {
        eloop_event_unregister(WIFI_MGMT_EVENT_SCAN_DONE);
        eloop_event_unregister(WIFI_MGMT_EVENT_SCAN_FAIL);
        rt_kprintf("Wifi scan failed\r\n");
    }

    return RT_EOK;
}

static void sta_conn_success_cb(void *eloop_data, void *user_ctx)
{
    LOG_D("WIFI_JOIN_SUCCESS");
    rt_kprintf("WiFi connected successfully\r\n");

    eloop_event_unregister(WIFI_MGMT_EVENT_CONNECT_SUCCESS);
    eloop_event_unregister(WIFI_MGMT_EVENT_CONNECT_FAIL);

    rt_wlan_dev_indicate_event_handle(wlan_sta_device.wlan, RT_WLAN_DEV_EVT_CONNECT, RT_NULL);
}

static void sta_conn_fail_cb(void *eloop_data, void *user_ctx)
{
    LOG_D("WIFI_JOIN_FAILED");
    rt_kprintf("WiFi connection failed\r\n");

    eloop_event_unregister(WIFI_MGMT_EVENT_CONNECT_SUCCESS);
    eloop_event_unregister(WIFI_MGMT_EVENT_CONNECT_FAIL);

    rt_wlan_dev_indicate_event_handle(wlan_sta_device.wlan, RT_WLAN_DEV_EVT_CONNECT_FAIL, RT_NULL);
}

/**
 * @brief WiFi join (connect to AP)
 */
static rt_err_t gd32_wlan_join(struct rt_wlan_device *wlan, struct rt_sta_info *sta_info)
{
    LOG_D("WiFi join SSID: %s", sta_info->ssid.val);
    // rt_kprintf("WiFi join start\r\n");

    // 先注销可能存在的旧回调
    eloop_event_unregister(WIFI_MGMT_EVENT_CONNECT_SUCCESS);
    eloop_event_unregister(WIFI_MGMT_EVENT_CONNECT_FAIL);

    if (wifi_management_connect(sta_info->ssid.val, sta_info->key.val, 0) < 0) {
        rt_kprintf("WiFi join failed\r\n");
        return -RT_ERROR;
    }

    eloop_event_register(WIFI_MGMT_EVENT_CONNECT_SUCCESS, sta_conn_success_cb, NULL, NULL);
    eloop_event_register(WIFI_MGMT_EVENT_CONNECT_FAIL, sta_conn_fail_cb, NULL, NULL);

    return RT_EOK;
}

/**
 * @brief WiFi softap start
 */
static rt_err_t gd32_wlan_softap(struct rt_wlan_device *wlan, struct rt_ap_info *ap_info)
{
    LOG_D("WiFi softap start SSID: %s", ap_info->ssid.val);

    wifi_ap_auth_mode_t auth_mode;
    char *ssid = ap_info->ssid.val;
    char *passwd = ap_info->key.val;
    uint32_t channel = ap_info->channel;
    uint32_t hidden = ap_info->hidden;

    if (wifi_management_concurrent_get() == 0) {
        wifi_management_concurrent_set(1);
    }

    switch (ap_info->security)
    {
        case SECURITY_OPEN:
            passwd = RT_NULL;
            auth_mode = AUTH_MODE_OPEN;
            break;

        case SECURITY_WEP_PSK:
        case SECURITY_WEP_SHARED:
            auth_mode = AUTH_MODE_WEP;
            break;

        case SECURITY_WPA_TKIP_PSK:
        case SECURITY_WPA_AES_PSK:
            auth_mode = AUTH_MODE_WPA;
            break;

        case SECURITY_WPA2_TKIP_PSK:
        case SECURITY_WPA2_AES_PSK:
            auth_mode = AUTH_MODE_WPA2;
            break;

        case SECURITY_WPA2_MIXED_PSK:
            auth_mode = AUTH_MODE_WPA_WPA2;
            break;

        case SECURITY_UNKNOWN:
            auth_mode = AUTH_MODE_UNKNOWN;
            break;

        default:
            rt_kprintf("Unsupported AP security mode %d, set to OPEN\r\n", ap_info->security);
            auth_mode = AUTH_MODE_OPEN;
            break;
    }

    if (wifi_management_ap_start(ssid, passwd, channel, auth_mode, hidden) < 0) {
        rt_kprintf("WiFi softap start failed\r\n");
        return -RT_ERROR;
    }

    rt_wlan_dev_indicate_event_handle(wlan_ap_device.wlan, RT_WLAN_DEV_EVT_AP_START, RT_NULL);

    return RT_EOK;
}

/**
 * @brief WiFi disconnect
 */
static rt_err_t gd32_wlan_disconnect(struct rt_wlan_device *wlan)
{
    LOG_D("WiFi disconnect");

    wifi_management_disconnect();

    rt_wlan_dev_indicate_event_handle(wlan_sta_device.wlan, RT_WLAN_DEV_EVT_DISCONNECT, RT_NULL);

    return RT_EOK;
}

/**
 * @brief WiFi AP disconnect station
 */
static rt_err_t gd32_wlan_ap_stop(struct rt_wlan_device *wlan)
{
    LOG_D("WiFi AP stop");

    if (wifi_management_concurrent_get() == 0) {
        wifi_management_concurrent_set(1);
    }

    if (wifi_management_ap_stop() < 0) {
        rt_kprintf("WiFi AP stop failed\r\n");
        return -RT_ERROR;
    }

    rt_wlan_dev_indicate_event_handle(wlan_ap_device.wlan, RT_WLAN_DEV_EVT_AP_STOP, RT_NULL);
    return RT_EOK;
}

/**
 * @brief WiFi AP deauthenticate station
 */
static rt_err_t gd32_wlan_ap_deauth(struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    LOG_D("WiFi AP deauth station");

    if (wifi_management_concurrent_get() == 0) {
        wifi_management_concurrent_set(1);
    }

    if (wifi_management_ap_delete_client(mac) < 0) {
        rt_kprintf("WiFi AP deauth station failed\r\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * @brief Get WiFi RSSI
 */
static rt_err_t gd32_wlan_scan_stop(struct rt_wlan_device *wlan)
{
    LOG_D("WiFi scan stop");

    /* TODO: Stop WiFi scan */

    return RT_EOK;
}

/**
 * @brief Get WiFi channel
 */
static int gd32_wlan_get_rssi(struct rt_wlan_device *wlan)
{
    int rssi = 0;

    /* TODO: Get current RSSI value */

    return rssi;
}

/**
 * @brief Set WiFi channel
 */
static rt_err_t gd32_wlan_set_channel(struct rt_wlan_device *wlan, int channel)
{
    LOG_D("Set WiFi channel: %d", channel);

    /* TODO: Set WiFi channel */

    return RT_EOK;
}

/**
 * @brief Get WiFi channel
 */
static int gd32_wlan_get_channel(struct rt_wlan_device *wlan)
{
    int channel = 1;

    /* TODO: Get current WiFi channel */

    return channel;
}

/**
 * @brief Set WiFi country code
 */
static rt_err_t gd32_wlan_set_country(struct rt_wlan_device *wlan, rt_country_code_t country_code)
{
    LOG_D("Set WiFi country code: %d", country_code);

    /* TODO: Set WiFi country code */

    return RT_EOK;
}

/**
 * @brief Get WiFi country code
 */
static rt_country_code_t gd32_wlan_get_country(struct rt_wlan_device *wlan)
{
    /* TODO: Get WiFi country code */

    return RT_COUNTRY_CHINA;
}

/**
 * @brief Set WiFi MAC address
 */
static rt_err_t gd32_wlan_set_mac(struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    LOG_D("Set WiFi MAC: %02x:%02x:%02x:%02x:%02x:%02x",
          mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    /* TODO: Set WiFi MAC address */

    return RT_EOK;
}

/**
 * @brief Get WiFi MAC address
 */
static rt_err_t gd32_wlan_get_mac(struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    return RT_EOK;
}

/**
 * @brief WiFi receive callback
 */
static int gd32_wlan_recv(struct rt_wlan_device *wlan, void *buff, int len)
{
    /* 不需要实现 - GD32 SDK LwIP 内部处理数据接收 */
    /* 数据接收流程：*/
    /* 硬件中断 -> MAC层 -> net_if_input() -> lwip tcpip_input() -> 协议栈处理 */

    return RT_EOK;
}

/**
 * @brief WiFi send
 */
static int gd32_wlan_send(struct rt_wlan_device *wlan, void *buff, int len)
{
    /* 不需要实现 - GD32 SDK LwIP 内部处理数据发送 */
    /* 数据发送流程：*/
    /* 应用层 -> lwIP协议栈 -> netif->linkoutput() -> net_if_output() -> MAC层 */

    return len;
}

/* WiFi operations */
static const struct rt_wlan_dev_ops gd32_wlan_ops =
{
    .wlan_init            = gd32_wlan_init,
    .wlan_mode            = gd32_wlan_mode,
    .wlan_scan            = gd32_wlan_scan,
    .wlan_join            = gd32_wlan_join,
    .wlan_softap          = gd32_wlan_softap,
    .wlan_disconnect      = gd32_wlan_disconnect,
    .wlan_ap_stop         = gd32_wlan_ap_stop,
    .wlan_ap_deauth       = gd32_wlan_ap_deauth,
    .wlan_scan_stop       = gd32_wlan_scan_stop,
    .wlan_get_rssi        = gd32_wlan_get_rssi,
    .wlan_set_powersave   = RT_NULL,
    .wlan_get_powersave   = RT_NULL,
    .wlan_cfg_promisc     = RT_NULL,
    .wlan_cfg_filter      = RT_NULL,
    .wlan_set_channel     = gd32_wlan_set_channel,
    .wlan_get_channel     = gd32_wlan_get_channel,
    .wlan_set_country     = gd32_wlan_set_country,
    .wlan_get_country     = gd32_wlan_get_country,
    .wlan_set_mac         = gd32_wlan_set_mac,
    .wlan_get_mac         = gd32_wlan_get_mac,
    .wlan_recv            = gd32_wlan_recv,
    .wlan_send            = gd32_wlan_send,
};

/**
 * @brief Initialize WiFi driver
 */
int rt_hw_wlan_init(void)
{
    static rt_bool_t init_flag = RT_FALSE;

    if (init_flag)
    {
        return RT_EOK;
    }

    platform_init();

    /* Initialize WiFi device structure */
    rt_memset(&wlan_sta_device, 0, sizeof(struct gd32_wlan_device));
    rt_memset(&wlan_ap_device, 0, sizeof(struct gd32_wlan_device));

    // 向系统注册
    static struct rt_wlan_device wlan_sta;
    static struct rt_wlan_device wlan_ap;

    /* Register WiFi STA device */
    wlan_sta_device.if_idx = WIFI_VIF_STA; /* STA interface */
    rt_err_t ret = rt_wlan_dev_register(&wlan_sta, RT_WLAN_DEVICE_STA_NAME, &gd32_wlan_ops, 0, &wlan_sta_device);
    wlan_sta_device.wlan = &wlan_sta;


    /* Register WiFi AP device */
    wlan_ap_device.if_idx = WIFI_VIF_AP; /* AP interface */
    ret |= rt_wlan_dev_register(&wlan_ap, RT_WLAN_DEVICE_AP_NAME, &gd32_wlan_ops, 0, &wlan_ap_device);
    wlan_ap_device.wlan = &wlan_ap;

    init_flag = RT_TRUE;

    LOG_I("GD32 WiFi driver initialized");

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_wlan_init);
#endif