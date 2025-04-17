/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/11/23     flyingcys    first version
 */

#include <rtthread.h>
#include "dev_wlan.h"

#define DBG_TAG     "drv.wifi"
#define DBG_LVL     DBG_LOG
#include <rtdbg.h>

#include "drv_wifi.h"

#define MAX_ADDR_LEN    6

struct _bl_wifi
{
    struct rt_wlan_device *wlan;
    rt_uint8_t dev_addr[MAX_ADDR_LEN];
};

static struct _bl_wifi wifi_sta;
static struct _bl_wifi wifi_ap;

extern err_t bl_wifi_tx(uint8_t idx, struct pbuf* p);

void event_cb_wifi_event(input_event_t *event, void *private_data)
{
    switch (event->code)
    {
        case CODE_WIFI_ON_INIT_DONE:
        {
        }
        break;

        case CODE_WIFI_ON_MGMR_DONE:
        {
        }
        break;

        case CODE_WIFI_ON_CONNECTED:
        {
            rt_wlan_dev_indicate_event_handle(wifi_sta.wlan, RT_WLAN_DEV_EVT_CONNECT, RT_NULL);
            wifi_mgmr_api_ip_got();
        }
        break;

        case CODE_WIFI_ON_DISCONNECT:
        {
            rt_wlan_dev_indicate_event_handle(wifi_sta.wlan, RT_WLAN_DEV_EVT_DISCONNECT, RT_NULL);
        }
        break;

        case CODE_WIFI_ON_SCAN_DONE:
        {
        }
        break;

        case CODE_WIFI_ON_PRE_GOT_IP:
        {
            wifi_mgmr_api_ip_got();
        }
        break;

        case CODE_WIFI_ON_AP_STARTED:
        {
            rt_wlan_dev_indicate_event_handle(wifi_ap.wlan, RT_WLAN_DEV_EVT_AP_START, RT_NULL);
        }
        break;

        case CODE_WIFI_ON_AP_STOPPED:
        {
            rt_wlan_dev_indicate_event_handle(wifi_ap.wlan, RT_WLAN_DEV_EVT_AP_STOP, RT_NULL);
        }
        break;

        default:
        {
            LOG_D(" unknow event code %d\r\n", event->code);
        }
        break;
    }
}

static rt_err_t drv_wlan_init(struct rt_wlan_device *wlan)
{
    static rt_bool_t init = RT_FALSE;

    if (init == RT_TRUE)
    {
        return RT_EOK;
    }

    bl808_wifi_init(event_cb_wifi_event);

    init = RT_TRUE;

    return RT_EOK;
}

static rt_err_t drv_wlan_mode(struct rt_wlan_device *wlan, rt_wlan_mode_t mode)
{
    LOG_D("set wlan mode: %d", mode);

    return RT_EOK;
}

static void wifi_scan_complete_callback(uint32_t scan_total, void *scan_buffer, void *param)
{
    struct rt_wlan_device *wlan = (struct rt_wlan_device *)param;
    struct wifi_mgmr_scan_item *scan_item = (struct wifi_mgmr_scan_item *)scan_buffer;

    struct rt_wlan_info wlan_info;
    struct rt_wlan_buff buff = {0};

    rt_uint32_t i;
    for (i = 0; i < scan_total; i ++)
    {
        memset(&wlan_info, 0, sizeof(wlan_info));

        wlan_info.security = SECURITY_OPEN;
        switch (scan_item[i].auth)
        {
            case WIFI_EVENT_BEACON_IND_AUTH_WPA3_SAE:
            {
            }
            break;
            case WIFI_EVENT_BEACON_IND_AUTH_WPA2_PSK_WPA3_SAE:
            {
            }
            break;
            case WIFI_EVENT_BEACON_IND_AUTH_OPEN:
            {
                wlan_info.security = SECURITY_OPEN;
            }
            break;
            case WIFI_EVENT_BEACON_IND_AUTH_WEP:
            {
                wlan_info.security = WEP_ENABLED;
            }
            break;
            case WIFI_EVENT_BEACON_IND_AUTH_WPA_PSK:
            {
                wlan_info.security = SECURITY_WPA_TKIP_PSK;
            }
            break;
            case WIFI_EVENT_BEACON_IND_AUTH_WPA2_PSK:
            {
                wlan_info.security = SECURITY_WPA2_TKIP_PSK;
            }
            break;
            case WIFI_EVENT_BEACON_IND_AUTH_WPA_WPA2_PSK:
            {
                wlan_info.security = SECURITY_WPA2_MIXED_PSK;
            }
            break;
            case WIFI_EVENT_BEACON_IND_AUTH_WPA_ENT:
            {
            }
            break;
            case WIFI_EVENT_BEACON_IND_AUTH_UNKNOWN:
            {
            }
            break;
            default:
            {
                wlan_info.security = SECURITY_OPEN;
            }
            break;
        }
        wlan_info.band = RT_802_11_BAND_2_4GHZ;
        wlan_info.channel = scan_item[i].channel;
        wlan_info.rssi = scan_item[i].rssi;

        memcpy(wlan_info.bssid, scan_item[i].bssid, 6);
        if (scan_item[i].ssid_len)
        {
            wlan_info.hidden == 0;
            memcpy(wlan_info.ssid.val, scan_item[i].ssid, strlen(scan_item[i].ssid));
            wlan_info.ssid.len = strlen(scan_item[i].ssid);
        }
        buff.data = &wlan_info;
        buff.len = sizeof(wlan_info);
        rt_wlan_dev_indicate_event_handle(wifi_sta.wlan, RT_WLAN_DEV_EVT_SCAN_REPORT, &buff);
    }

    rt_wlan_dev_indicate_event_handle(wlan, RT_WLAN_DEV_EVT_SCAN_DONE, RT_NULL);
}

static rt_err_t drv_wlan_scan(struct rt_wlan_device *wlan, struct rt_scan_info *scan_info)
{
    int  channel_input_num = 0;
    uint8_t channel_input[MAX_FIXED_CHANNELS_LIMIT] = {0};
    const char *ssid = NULL;
    uint8_t bssid[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    uint8_t scan_mode = SCAN_ACTIVE;
    uint32_t duration_scan_us = 0;

    if (scan_info != NULL && scan_info->ssid.len > 0)
    {
        ssid = scan_info->ssid.val;
    }

    if (wifi_mgmr_scan_adv(wlan, wifi_scan_complete_callback, channel_input, channel_input_num, bssid, ssid, scan_mode, duration_scan_us) != 0)
        return -RT_ERROR;

    return RT_EOK;
}

static rt_err_t drv_wlan_join(struct rt_wlan_device *wlan, struct rt_sta_info *sta_info)
{
    uint8_t channel_index = 0;
    int bssid_set_flag = 0;
    int quick_connect = 0;
    uint32_t flags = 0;
    int pci_en = 0;
    int scan_mode = 0;
    uint8_t pmf_flag = WIFI_MGMR_CONNECT_PMF_CAPABLE_BIT;

    if (sta_info->bssid != NULL)
    {
        bssid_set_flag = 1;
    }

    if (quick_connect > 0)
    {
        flags |= WIFI_CONNECT_STOP_SCAN_CURRENT_CHANNEL_IF_TARGET_AP_FOUND;
    }

    if (scan_mode)
    {
        flags |= WIFI_CONNECT_STOP_SCAN_ALL_CHANNEL_IF_TARGET_AP_FOUND;
    }

    if (pci_en)
    {
        flags |= WIFI_CONNECT_PCI_EN;
    }

    if (pmf_flag & WIFI_MGMR_CONNECT_PMF_CAPABLE_BIT)
    {
        flags |= WIFI_CONNECT_PMF_CAPABLE;
    } else
    {
        flags &= ~WIFI_CONNECT_PMF_CAPABLE;
    }

    if (pmf_flag & WIFI_MGMR_CONNECT_PMF_REQUIRED_BIT)
     {
        flags |= WIFI_CONNECT_PMF_REQUIRED;
    } else {
        flags &= ~WIFI_CONNECT_PMF_REQUIRED;
    }

    wifi_mgmr_mode_set(0);
    wifi_mgmr_sta_connect_mid(RT_NULL, sta_info->ssid.val, (sta_info->key.len == 0) ? NULL : sta_info->key.val, NULL, bssid_set_flag ? sta_info->bssid : NULL, 0, channel_index, 1, flags);

    return RT_EOK;
}

static rt_err_t drv_wlan_softap(struct rt_wlan_device *wlan, struct rt_ap_info *ap_info)
{
    int ret;
    uint8_t mac[6];
    uint8_t hidden_ssid = 0;
    char ssid_name[32 + 1];
    char passwd[64 + 1];
    int channel;
    int max_sta_supported = -1;

    memset(mac, 0, sizeof(mac));
    bl_wifi_mac_addr_get(mac);

    memset(ssid_name, 0, sizeof(ssid_name));
    memset(passwd, 0, sizeof(passwd));

    memcpy(ssid_name, ap_info->ssid.val, (ap_info->ssid.len > 32)? 32 : ap_info->ssid.len);

    if (ap_info->hidden)
        hidden_ssid = 1;

    channel = ap_info->channel;

    wifi_mgmr_mode_set(1);

    //TODO：未知原因导致 ap 有密码的情况下会crash
#if 0
    if (ap_info->key.len > 0)
    {
        memcpy(passwd, ap_info->key.val, (ap_info->key.len > 64)? 64 : ap_info->key.len);
        ret = wifi_mgmr_api_ap_start(ssid_name, passwd, channel, hidden_ssid, max_sta_supported, 1);
    }
    else
#endif
    {
        ret = wifi_mgmr_api_ap_start(ssid_name, NULL, channel, hidden_ssid, max_sta_supported, 1);
    }

    if (ret < 0)
        return -RT_ERROR;

    return RT_EOK;
}

static rt_err_t drv_wlan_disconnect(struct rt_wlan_device *wlan)
{
    wifi_mgmr_sta_disconnect();

    rt_thread_mdelay(WIFI_MGMR_STA_DISCONNECT_DELAY);
    wifi_mgmr_sta_disable(NULL);

    return RT_EOK;
}

static rt_err_t drv_wlan_ap_stop(struct rt_wlan_device *wlan)
{
    LOG_D("%s %d", __FUNCTION__, __LINE__);
    wifi_mgmr_api_ap_stop();
    return RT_EOK;
}

static rt_err_t drv_wlan_ap_deauth(struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    LOG_D("%s %d", __FUNCTION__, __LINE__);

    return RT_EOK;
}

static rt_err_t drv_wlan_scan_stop(struct rt_wlan_device *wlan)
{
    LOG_D("%s %d", __FUNCTION__, __LINE__);

    return RT_EOK;
}

static int drv_wlan_get_rssi(struct rt_wlan_device *wlan)
{
    int rssi;

    wifi_mgmr_rssi_get(&rssi);

    return rssi;
}

static rt_err_t drv_wlan_set_powersave(struct rt_wlan_device *wlan, int level)
{
    LOG_D("%s %d", __FUNCTION__, __LINE__);

    return RT_EOK;
}

static int drv_wlan_get_powersave(struct rt_wlan_device *wlan)
{
    LOG_D("%s %d", __FUNCTION__, __LINE__);

    return RT_EOK;
}

static void sniffer_cb(void *env, uint8_t *pkt, int len, struct bl_rx_info *info)
{
    static unsigned int sniffer_counter, sniffer_last;
    static unsigned int last_tick;

    (void)sniffer_last;
    (void)sniffer_counter;

    sniffer_counter++;
    if ((int)bl_os_get_tick() - (int)last_tick > 10 * 1000) {
        bl_os_log_info("[SNIFFER] PKT Number is %d\r\n",
                (int)sniffer_counter - (int)sniffer_last
        );
        last_tick = bl_os_get_tick();
        sniffer_last = sniffer_counter;
    }
}

static rt_err_t drv_wlan_cfg_promisc(struct rt_wlan_device *wlan, rt_bool_t start)
{
    LOG_D("%s %d", __FUNCTION__, __LINE__);
    if (start)
    {
        wifi_mgmr_sniffer_register(RT_NULL, sniffer_cb);
        wifi_mgmr_sniffer_enable();
    }
    else
    {
        wifi_mgmr_sniffer_disable();
        wifi_mgmr_sniffer_register(RT_NULL, RT_NULL);
    }

    return RT_EOK;
}

static rt_err_t drv_wlan_cfg_filter(struct rt_wlan_device *wlan, struct rt_wlan_filter *filter)
{
    LOG_D("%s %d", __FUNCTION__, __LINE__);

    return RT_EOK;
}

static rt_err_t drv_wlan_cfg_mgnt_filter(struct rt_wlan_device *wlan, rt_bool_t start)
{
    LOG_D("%s %d", __FUNCTION__, __LINE__);

    return RT_EOK;
}

static rt_err_t drv_wlan_set_channel(struct rt_wlan_device *wlan, int channel)
{
    wifi_mgmr_channel_set(channel, 0);

    return RT_EOK;
}

static int drv_wlan_get_channel(struct rt_wlan_device *wlan)
{
    int channel;

    wifi_mgmr_channel_get(&channel);

    return channel;
}

static rt_err_t drv_wlan_set_country(struct rt_wlan_device *wlan, rt_country_code_t country_code)
{
    LOG_D("%s %d", __FUNCTION__, __LINE__);

    wifi_mgmr_set_country_code("CN");

    return RT_EOK;
}

static rt_country_code_t drv_wlan_get_country(struct rt_wlan_device *wlan)
{
    LOG_D("%s %d", __FUNCTION__, __LINE__);

    return RT_EOK;
}

static rt_err_t drv_wlan_set_mac(struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    wifi_mgmr_sta_mac_set(mac);

    return RT_EOK;
}

static rt_err_t drv_wlan_get_mac(struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    wifi_mgmr_sta_mac_get(mac);

    return RT_EOK;
}

int bl_wifi_rx(uint8_t idx, struct pbuf *p)
{
    rt_err_t ret = RT_EOK;
    if (idx == 0)
        ret = rt_wlan_dev_report_data(wifi_sta.wlan, p, p->tot_len);
    else
        ret = rt_wlan_dev_report_data(wifi_ap.wlan, p, p->tot_len);

    return ret;
}

static int drv_wlan_recv(struct rt_wlan_device *wlan, void *buff, int len)
{
    LOG_D("%s %d", __FUNCTION__, __LINE__);

    return RT_EOK;
}

static int drv_wlan_send(struct rt_wlan_device *wlan, void *buff, int len)
{
    if (wlan->user_data == &wifi_sta)
        bl_wifi_tx(0, (struct pbuf *)buff);
    else
        bl_wifi_tx(1, (struct pbuf *)buff);

    return RT_EOK;
}

static const struct rt_wlan_dev_ops ops =
{
    .wlan_init = drv_wlan_init,
    .wlan_mode = drv_wlan_mode,
    .wlan_scan = drv_wlan_scan,
    .wlan_join = drv_wlan_join,
    .wlan_softap = drv_wlan_softap,
    .wlan_disconnect = drv_wlan_disconnect,
    .wlan_ap_stop = drv_wlan_ap_stop,
    .wlan_ap_deauth = drv_wlan_ap_deauth,
    .wlan_scan_stop = drv_wlan_scan_stop,
    .wlan_get_rssi = drv_wlan_get_rssi,
    .wlan_set_powersave = drv_wlan_set_powersave,
    .wlan_get_powersave = drv_wlan_get_powersave,
    .wlan_cfg_promisc = drv_wlan_cfg_promisc,
    .wlan_cfg_filter = drv_wlan_cfg_filter,
    .wlan_cfg_mgnt_filter = drv_wlan_cfg_mgnt_filter,
    .wlan_set_channel = drv_wlan_set_channel,
    .wlan_get_channel = drv_wlan_get_channel,
    .wlan_set_country = drv_wlan_set_country,
    .wlan_get_country = drv_wlan_get_country,
    .wlan_set_mac = drv_wlan_set_mac,
    .wlan_get_mac = drv_wlan_get_mac,
    .wlan_recv = drv_wlan_recv,
    .wlan_send = drv_wlan_send,
};

int rt_hw_wifi_init(void)
{
    rt_err_t ret = RT_EOK;

    static struct rt_wlan_device wlan0;
    static struct rt_wlan_device wlan1;

    memset(&wifi_sta, 0, sizeof(wifi_sta));
    ret = rt_wlan_dev_register(&wlan0, RT_WLAN_DEVICE_STA_NAME, &ops, 0, &wifi_sta);
    wifi_sta.wlan = &wlan0;

    memset(&wifi_ap, 0, sizeof(wifi_ap));
    ret |= rt_wlan_dev_register(&wlan1, RT_WLAN_DEVICE_AP_NAME, &ops, 0, &wifi_ap);
    wifi_ap.wlan = &wlan1;

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_wifi_init);
