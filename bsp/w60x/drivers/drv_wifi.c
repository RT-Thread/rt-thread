/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-15     flyingcys    1st version
 */

#include <rtthread.h>
#include <wlan_dev.h>
#include "wm_type_def.h"
#include "wm_wifi.h"
#include "drv_wifi.h"

#define DBG_ENABLE
#define DBG_LEVEL DBG_INFO
#define DBG_SECTION_NAME  "WIFI"
#define DBG_COLOR
#include <rtdbg.h>

#include "wm_ram_config.h"
#include "wm_efuse.h"
#include "wm_params.h"
#include "wm_debug.h"
#include "tls_ieee80211.h"

//#define ETH_RX_DUMP
//#define ETH_TX_DUMP
//#define MINI_DUMP

#define MAX_ADDR_LEN        (6)

struct drv_wifi
{
    struct rt_wlan_device *wlan;
    rt_uint8_t dev_addr[MAX_ADDR_LEN];
};

static const struct rt_wlan_dev_ops ops;
static struct drv_wifi wifi_sta;
static struct drv_wifi wifi_ap;

extern int hed_rf_current_channel;

extern u8 *wpa_supplicant_get_mac(void);
extern u8 *hostapd_get_mac(void);
extern uint8_t* tls_wifi_buffer_acquire(int total_len);
extern void *tls_wl_init(u8 *tx_gain, u8* mac_addr, u8 *hwver);
extern int wpa_supplicant_init(u8 *mac_addr);
extern void wpa_supplicant_set_mac(u8 *mac);
extern void tls_wifi_buffer_release(rt_bool_t is_apsta, rt_uint8_t* buffer);

#if defined(ETH_RX_DUMP) ||  defined(ETH_TX_DUMP)
static void packet_dump(const char *msg, const void *ptr, rt_uint32_t len)
{
    rt_uint32_t j;
    rt_uint8_t *p = (rt_uint8_t *)ptr;
    rt_kprintf("%s %d byte\n", msg, len);

#ifdef MINI_DUMP
    return;
#endif

    for (j = 0; j < len; j++)
    {
        if ((j % 8) == 0)
        {
            rt_kprintf("  ");
        }

        if ((j % 16) == 0)
        {
            rt_kprintf("\r\n");
        }
        rt_kprintf("%02x ", *p ++);
    }

    rt_kprintf("\n\n");
}
#endif /* dump */

err_t tls_netif_set_addr(void *ipaddr, void *netmask, void *gw)
{
    LOG_D("%s %d\r\n", __FUNCTION__, __LINE__);
    return 0;
}

static int wm_ethernetif_input(const rt_uint8_t *bssid, rt_uint8_t *buf, rt_uint32_t buf_len)
{
    rt_err_t err = -RT_ERROR;

    if (0 == compare_ether_addr(bssid, wifi_ap.dev_addr))
        err = rt_wlan_dev_report_data(wifi_ap.wlan, (void *)buf, buf_len);
    else
        err = rt_wlan_dev_report_data(wifi_sta.wlan, (void *)buf, buf_len);

    return err ? -1 : 0;
}

static void wm_wlan_client_event(u8 *mac, enum tls_wifi_client_event_type event)
{
    struct rt_wlan_buff buff;
    struct rt_wlan_info sta;
    rt_memcpy(sta.bssid, mac, MAX_ADDR_LEN);
    buff.data = &sta;
    buff.len = sizeof(sta);
    if (WM_WIFI_CLIENT_EVENT_ONLINE == event)
    {
        rt_wlan_dev_indicate_event_handle(wifi_ap.wlan, RT_WLAN_DEV_EVT_AP_ASSOCIATED, &buff);
    }
    else
    {
        rt_wlan_dev_indicate_event_handle(wifi_ap.wlan, RT_WLAN_DEV_EVT_AP_DISASSOCIATED, &buff);
    }
}

static void wm_wlan_status_changed(rt_uint8_t status)
{
    LOG_D("status:%d", status);
    switch (status)
    {
    case WIFI_JOIN_SUCCESS:
        LOG_D("NETIF_WIFI_JOIN_SUCCESS");
        rt_wlan_dev_indicate_event_handle(wifi_sta.wlan, RT_WLAN_DEV_EVT_CONNECT, RT_NULL);
        break;

    case WIFI_JOIN_FAILED:
        LOG_D("NETIF_WIFI_JOIN_FAILED");
        rt_wlan_dev_indicate_event_handle(wifi_sta.wlan, RT_WLAN_DEV_EVT_CONNECT_FAIL, RT_NULL);
        break;

    case WIFI_DISCONNECTED:
        LOG_D("NETIF_WIFI_DISCONNECTED");
        rt_wlan_dev_indicate_event_handle(wifi_sta.wlan, RT_WLAN_DEV_EVT_DISCONNECT, RT_NULL);
        break;

    case WIFI_SOFTAP_SUCCESS:
        LOG_D("WIFI_SOFTAP_SUCCESS");
        rt_wlan_dev_indicate_event_handle(wifi_ap.wlan, RT_WLAN_DEV_EVT_AP_START, RT_NULL);
        break;

    case WIFI_SOFTAP_CLOSED:
        LOG_D("WIFI_SOFTAP_CLOSED");
        rt_wlan_dev_indicate_event_handle(wifi_ap.wlan, RT_WLAN_DEV_EVT_AP_STOP, RT_NULL);
        break;

    default:
        break;
    }
}

static rt_err_t wm_wlan_init(void)
{
    extern rt_uint8_t tx_gain_group[];
    rt_uint8_t mac_addr[6] = {0x00, 0x25, 0x08, 0x09, 0x01, 0x0F};

    /*PARAM GAIN,MAC default*/
    tls_ft_param_init();
    tls_param_load_factory_default();
    tls_param_init(); /*add param to init sysparam_lock sem*/

    tls_get_tx_gain(&tx_gain_group[0]);
    TLS_DBGPRT_INFO("tx gain ");
    TLS_DBGPRT_DUMP((char *)(&tx_gain_group[0]), 12);

    if (tls_wifi_mem_cfg(WIFI_MEM_START_ADDR, 7, 7)) /*wifi tx&rx mem customized interface*/
    {
        LOG_E("wl mem initial failured\n");
    }

    tls_get_mac_addr(&mac_addr[0]);
    TLS_DBGPRT_INFO("mac addr ");
    TLS_DBGPRT_DUMP((char *)(&mac_addr[0]), 6);

    if (tls_wl_init(NULL, &mac_addr[0], NULL) == NULL)
    {
        LOG_I("wl driver initial failured\n");
    }
    if (wpa_supplicant_init(mac_addr))
    {
        LOG_I("supplicant initial failured\n");
    }
    rt_memcpy(wifi_sta.dev_addr, wpa_supplicant_get_mac(), MAX_ADDR_LEN);
    LOG_D("sta_mac:%02x-%02x-%02x-%02x-%02x-%02x\r\n", wifi_sta.dev_addr[0], wifi_sta.dev_addr[1], wifi_sta.dev_addr[2], wifi_sta.dev_addr[3], wifi_sta.dev_addr[4], wifi_sta.dev_addr[5]);
    rt_memcpy(wifi_ap.dev_addr, hostapd_get_mac(), MAX_ADDR_LEN);
    LOG_D("ap_mac:%02x-%02x-%02x-%02x-%02x-%02x\r\n", wifi_ap.dev_addr[0], wifi_ap.dev_addr[1], wifi_ap.dev_addr[2], wifi_ap.dev_addr[3], wifi_ap.dev_addr[4], wifi_ap.dev_addr[5]);
    return RT_EOK;
}

static void wm_wlan_promisc_dataframe_callback(u8 *data, u32 data_len)
{
    rt_wlan_dev_promisc_handler(wifi_sta.wlan, data, data_len);
}

static rt_err_t drv_wlan_init(struct rt_wlan_device *wlan)
{
    static int inited = 0;
    if (inited)
        return RT_EOK;

    wm_wlan_init();

    tls_ethernet_data_rx_callback(wm_ethernetif_input);
    tls_wifi_status_change_cb_register(wm_wlan_status_changed);
    tls_wifi_softap_client_event_register(wm_wlan_client_event);
    inited = 1;
    return RT_EOK;
}

static rt_err_t drv_wlan_mode(struct rt_wlan_device *wlan, rt_wlan_mode_t mode)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    u8 wmode = IEEE80211_MODE_INFRA;
    if (mode == RT_WLAN_AP)
        wmode = IEEE80211_MODE_AP;
    tls_param_set(TLS_PARAM_ID_WPROTOCOL, (void *)&wmode, TRUE);

    return RT_EOK;
}

static void wm_wlan_scan_callback(void)
{
    int buflen = 2000;
    char *buf = RT_NULL;
    int err;

    struct rt_wlan_info wlan_info;
    struct rt_wlan_buff buff;

    buf = rt_malloc(buflen);
    if (RT_NULL == buf)
    {
        LOG_E("rt_malloc failed...\r\n");
        return;
    }

    err = tls_wifi_get_scan_rslt((u8 *)buf, buflen);
    if (err != WM_SUCCESS)
    {
        rt_free(buf);
        return;
    }

    struct tls_scan_bss_t *scan_res = (struct tls_scan_bss_t *)buf;
    struct tls_bss_info_t *bss_info = (struct tls_bss_info_t *)scan_res->bss;
    if (scan_res->count <= 0)
    {
        rt_free(buf);
        return;
    }

    int i;
    for (i = 0; i < scan_res->count; i ++)
    {
        rt_memset(&wlan_info, 0, sizeof(wlan_info));

        rt_memcpy(&wlan_info.bssid[0], bss_info->bssid, 6);
        rt_memcpy(wlan_info.ssid.val, bss_info->ssid, bss_info->ssid_len);
        wlan_info.ssid.len = bss_info->ssid_len;
        if (bss_info->ssid_len)
            wlan_info.hidden = 0;
        else
            wlan_info.hidden = 1;

        wlan_info.channel = (rt_int16_t)bss_info->channel;
        wlan_info.rssi = -(char)(0x100 - bss_info->rssi);

        wlan_info.datarate = bss_info->max_data_rate * 1000000;

        wlan_info.band = RT_802_11_BAND_2_4GHZ;

        wlan_info.security = SECURITY_OPEN;
        if (WM_WIFI_AUTH_MODE_WEP_AUTO & bss_info->privacy)
            wlan_info.security |= WEP_ENABLED;
        if (WM_WIFI_AUTH_MODE_WPA_PSK_TKIP & bss_info->privacy)
            wlan_info.security |= WPA_SECURITY  | TKIP_ENABLED;
        if (WM_WIFI_AUTH_MODE_WPA_PSK_CCMP & bss_info->privacy)
            wlan_info.security |= WPA_SECURITY  | AES_ENABLED;
        if (WM_WIFI_AUTH_MODE_WPA2_PSK_CCMP & bss_info->privacy)
            wlan_info.security |= WPA2_SECURITY | AES_ENABLED;
        if (WM_WIFI_AUTH_MODE_WPA2_PSK_TKIP & bss_info->privacy)
            wlan_info.security |= WPA2_SECURITY | TKIP_ENABLED;
        if (bss_info->wps_support)
            wlan_info.security |= WPS_ENABLED;
        if (WM_WIFI_AUTH_MODE_UNKNOWN == bss_info->privacy)
            wlan_info.security = SECURITY_UNKNOWN;

        /* rtt incompleted... */
        if (wlan_info.security & SECURITY_WPA2_MIXED_PSK)
            wlan_info.security = SECURITY_WPA2_MIXED_PSK;
        else if (wlan_info.security & SECURITY_WPA2_TKIP_PSK)
            wlan_info.security = SECURITY_WPA2_TKIP_PSK;
        else if (wlan_info.security & SECURITY_WPA2_AES_PSK)
            wlan_info.security = SECURITY_WPA2_AES_PSK;
        else if (wlan_info.security & SECURITY_WPA_AES_PSK)
            wlan_info.security = SECURITY_WPA_AES_PSK;
        else if (wlan_info.security & SECURITY_WPA_TKIP_PSK)
            wlan_info.security = SECURITY_WPA_TKIP_PSK;
        else if (wlan_info.security & SECURITY_WEP_PSK)
            wlan_info.security = SECURITY_WEP_PSK;
        else if ((SECURITY_UNKNOWN == wlan_info.security) && bss_info->wps_support)
            wlan_info.security = SECURITY_WPS_SECURE;

        LOG_D("%s-%x", wlan_info.ssid.val, wlan_info.security);

        bss_info ++;

        buff.data = &wlan_info;
        buff.len = sizeof(wlan_info);
        rt_wlan_dev_indicate_event_handle(wifi_sta.wlan, RT_WLAN_DEV_EVT_SCAN_REPORT, &buff);

    }
    rt_free(buf);
    rt_wlan_dev_indicate_event_handle(wifi_sta.wlan, RT_WLAN_DEV_EVT_SCAN_DONE, RT_NULL);
}

static rt_err_t drv_wlan_scan(struct rt_wlan_device *wlan, struct rt_scan_info *scan_info)
{
    int ret;

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    /* register scan complt callback*/
    tls_wifi_scan_result_cb_register(wm_wlan_scan_callback);

    /* trigger the scan */
    ret = tls_wifi_scan();
    if ((ret == WM_WIFI_SCANNING_BUSY) || (ret == WM_FAILED))
        return -RT_ERROR;

    return RT_EOK;
}

static rt_err_t drv_wlan_join(struct rt_wlan_device *wlan, struct rt_sta_info *sta_info)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    tls_wifi_disconnect();

    tls_wifi_connect((u8 *)sta_info->ssid.val, sta_info->ssid.len, (u8 *)sta_info->key.val, sta_info->key.len);

    return RT_EOK;
}

static rt_err_t drv_wlan_softap(struct rt_wlan_device *wlan, struct rt_ap_info *ap_info)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    struct tls_softap_info_t apinfo;
    struct tls_ip_info_t ipinfo;
    rt_memset(&apinfo, 0, sizeof(apinfo));
    rt_memcpy(apinfo.ssid, ap_info->ssid.val, ap_info->ssid.len);
    apinfo.channel = ap_info->channel;
    switch (ap_info->security)  /* only support wpa2-psk and open */
    {
    case SECURITY_WEP_PSK:
        apinfo.encrypt = IEEE80211_ENCRYT_WEP40;
        break;
    case SECURITY_WPA_TKIP_PSK:
        apinfo.encrypt = IEEE80211_ENCRYT_TKIP_WPA;
        break;
    case SECURITY_WPA_AES_PSK:
        apinfo.encrypt = IEEE80211_ENCRYT_CCMP_WPA;
        break;
    case SECURITY_WPA2_TKIP_PSK:
        apinfo.encrypt = IEEE80211_ENCRYT_TKIP_WPA2;
        break;
    case SECURITY_WPA2_AES_PSK:
    case SECURITY_WPA2_MIXED_PSK:
        apinfo.encrypt = IEEE80211_ENCRYT_CCMP_WPA2;
        break;
    default:
        apinfo.encrypt = IEEE80211_ENCRYT_NONE;
        break;
    }
    apinfo.keyinfo.format = 1; /* ascii */
    apinfo.keyinfo.index = 1;  /* index */
    apinfo.keyinfo.key_len = ap_info->key.len;
    rt_memcpy(apinfo.keyinfo.key, ap_info->key.val, ap_info->key.len);
    LOG_D("ch=%d, hd=%d, key=%s, sec=%x, ssid=%s", ap_info->channel, ap_info->hidden, ap_info->key.val, ap_info->security, ap_info->ssid.val);
    rt_memset(&ipinfo, 0, sizeof(ipinfo));
    ipinfo.ip_addr[0] = 192;
    ipinfo.ip_addr[1] = 168;
    ipinfo.ip_addr[2] = 48;
    ipinfo.ip_addr[3] = 1;
    ipinfo.netmask[0] = 255;
    ipinfo.netmask[1] = 255;
    ipinfo.netmask[2] = 255;
    ipinfo.netmask[3] = 0;
    u8 ssid_set = ap_info->hidden ? 0 : 1;
    tls_param_set(TLS_PARAM_ID_BRDSSID, (void *)&ssid_set, FALSE);
    rt_memcpy(ipinfo.dnsname, "local.w60x", sizeof("local.w60x"));
    int ret = tls_wifi_softap_create(&apinfo, &ipinfo);

    return (ret == WM_SUCCESS) ? RT_EOK : RT_ERROR;
}

static rt_err_t drv_wlan_disconnect(struct rt_wlan_device *wlan)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    tls_wifi_disconnect();

    return RT_EOK;
}

static rt_err_t drv_wlan_ap_stop(struct rt_wlan_device *wlan)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    tls_wifi_softap_destroy();

    return RT_EOK;
}

static rt_err_t drv_wlan_ap_deauth(struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    struct tls_wifi_hdr_mac_t machdr;
    struct tls_wifi_tx_rate_t tx;
    rt_memset(&machdr, 0, sizeof(machdr));
    rt_memcpy(machdr.da_addr, mac, MAX_ADDR_LEN);
    rt_memcpy(machdr.sa_addr, hostapd_get_mac(), MAX_ADDR_LEN);
    rt_memcpy(machdr.bssid, hostapd_get_mac(), MAX_ADDR_LEN);
    rt_memset(&tx, 0, sizeof(tx));
    tx.tx_rate = WM_WIFI_TX_RATEIDX_1M;
    tx.tx_gain = tls_wifi_get_tx_gain_max(WM_WIFI_TX_RATEIDX_1M);
    unsigned short reason = WLAN_REASON_UNSPECIFIED;/* htons */
    int ret = tls_wifi_send_mgmt(WM_WIFI_MGMT_TYPE_DEAUTH, &machdr, (u8 *)&reason, sizeof(reason), &tx);

    return (0 == ret) ? RT_EOK : RT_ERROR;
}

static rt_err_t drv_wlan_scan_stop(struct rt_wlan_device *wlan)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    return RT_EOK;
}

static int drv_wlan_get_rssi(struct rt_wlan_device *wlan)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    struct tls_curr_bss_t bss;
    rt_memset(&bss, 0, sizeof(bss));
    tls_wifi_get_current_bss(&bss);

    return -bss.rssi - 1;
}

static rt_err_t drv_wlan_set_powersave(struct rt_wlan_device *wlan, int level)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    tls_wifi_set_psflag(level ? TRUE : FALSE, FALSE);

    return RT_EOK;
}

static int drv_wlan_get_powersave(struct rt_wlan_device *wlan)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    return tls_wifi_get_psflag();
}

static rt_err_t drv_wlan_cfg_promisc(struct rt_wlan_device *wlan, rt_bool_t start)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    if (RT_TRUE == start)
    {
        tls_wifi_set_listen_mode(1);
        tls_wifi_data_recv_cb_register(wm_wlan_promisc_dataframe_callback);
    }
    else
    {
        tls_wifi_set_listen_mode(0);
        tls_wifi_data_recv_cb_register(RT_NULL);
    }

    return RT_EOK;
}

static rt_err_t drv_wlan_cfg_filter(struct rt_wlan_device *wlan, struct rt_wlan_filter *filter)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    return RT_EINVAL;/* not support */
}

static rt_err_t drv_wlan_set_channel(struct rt_wlan_device *wlan, int channel)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    tls_wifi_change_chanel(channel - 1);

    return RT_EOK;
}

static int drv_wlan_get_channel(struct rt_wlan_device *wlan)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    return hed_rf_current_channel;
}

static rt_err_t drv_wlan_set_country(struct rt_wlan_device *wlan, rt_country_code_t country_code)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    u8 region = (u8)country_code;
    tls_param_set(TLS_PARAM_ID_COUNTRY_REGION, (void *)&region, TRUE);

    return RT_EOK;
}

static rt_country_code_t drv_wlan_get_country(struct rt_wlan_device *wlan)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    u8 region = RT_COUNTRY_CHINA;
    tls_param_get(TLS_PARAM_ID_COUNTRY_REGION, (void *)&region, FALSE);

    return (rt_country_code_t)region;   //RT_EOK;
}

static rt_err_t drv_wlan_set_mac(struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    if (wlan->user_data == &wifi_sta)   /* ap don't support */
    {
        wpa_supplicant_set_mac(mac);
        tls_set_mac_addr(mac);
    }

    return RT_EOK;
}

static rt_err_t drv_wlan_get_mac(struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    if (wlan->user_data == &wifi_sta)
        rt_memcpy(mac, wpa_supplicant_get_mac(), MAX_ADDR_LEN);
    else
        rt_memcpy(mac, hostapd_get_mac(), MAX_ADDR_LEN);

    return RT_EOK;
}

static int drv_wlan_recv(struct rt_wlan_device *wlan, void *buff, int len)
{
    return RT_EOK;
}

static int drv_wlan_send(struct rt_wlan_device *wlan, void *buff, int len)
{
    rt_uint8_t *dst = tls_wifi_buffer_acquire(len);
    if (dst == NULL)
        return -RT_ENOMEM;

#if ETH_PAD_SIZE
    pbuf_header(p, -ETH_PAD_SIZE);    /* Drop the padding word */
#endif

#if defined(ETH_TX_DUMP)
    packet_dump("Tx", buff, len);
#endif

    rt_memcpy(dst, buff, len);

#if TLS_CONFIG_AP
    if (netif != tls_get_netif())
        tls_wifi_buffer_release(true, dst);
    else
#endif
        tls_wifi_buffer_release(false, dst);

#if ETH_PAD_SIZE
    pbuf_header(p, ETH_PAD_SIZE);    /* Reclaim the padding word */
#endif

    return RT_EOK;
}

static const struct rt_wlan_dev_ops ops =
{
    .wlan_init              = drv_wlan_init,
    .wlan_mode              = drv_wlan_mode,
    .wlan_scan              = drv_wlan_scan,
    .wlan_join              = drv_wlan_join,
    .wlan_softap            = drv_wlan_softap,
    .wlan_disconnect        = drv_wlan_disconnect,
    .wlan_ap_stop           = drv_wlan_ap_stop,
    .wlan_ap_deauth         = drv_wlan_ap_deauth,
    .wlan_scan_stop         = drv_wlan_scan_stop,
    .wlan_get_rssi          = drv_wlan_get_rssi,
    .wlan_set_powersave     = drv_wlan_set_powersave,
    .wlan_get_powersave     = drv_wlan_get_powersave,
    .wlan_cfg_promisc       = drv_wlan_cfg_promisc,
    .wlan_cfg_filter        = drv_wlan_cfg_filter,
    .wlan_set_channel       = drv_wlan_set_channel,
    .wlan_get_channel       = drv_wlan_get_channel,
    .wlan_set_country       = drv_wlan_set_country,
    .wlan_get_country       = drv_wlan_get_country,
    .wlan_set_mac           = drv_wlan_set_mac,
    .wlan_get_mac           = drv_wlan_get_mac,
    .wlan_recv              = drv_wlan_recv,
    .wlan_send              = drv_wlan_send,
};

int wm_hw_wifi_init(void)
{
    static struct rt_wlan_device wlan;
    static struct rt_wlan_device wlan2;

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    rt_memset(&wifi_sta, 0, sizeof(wifi_sta));
    rt_err_t ret = rt_wlan_dev_register(&wlan, RT_WLAN_DEVICE_STA_NAME, &ops, 0, &wifi_sta);
    wifi_sta.wlan = &wlan;

    rt_memset(&wifi_ap, 0, sizeof(wifi_ap));
    ret |= rt_wlan_dev_register(&wlan2, RT_WLAN_DEVICE_AP_NAME, &ops, 0, &wifi_ap);
    wifi_ap.wlan = &wlan2;

    return ret; //RT_EOK;
}
INIT_DEVICE_EXPORT(wm_hw_wifi_init);
