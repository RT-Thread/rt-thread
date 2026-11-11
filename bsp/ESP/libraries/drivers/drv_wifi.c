/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2023-07-25     WCX1024979076   1st version
 */

#include <rtthread.h>
#include <string.h>
#include <rtdevice.h>

#ifdef RT_USING_WIFI
#include "drv_wifi.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "nvs_flash.h"
#include "esp_private/wifi.h"

#define DBG_LEVEL DBG_LOG
#define LOG_TAG  "DRV.WIFI"
#include <rtdbg.h>

#define MAX_ADDR_LEN        (6)

struct drv_wifi
{
    struct rt_wlan_device *wlan;
    wifi_interface_t wifi_if;
    rt_uint8_t dev_addr[MAX_ADDR_LEN];
};

static const struct rt_wlan_dev_ops ops;
static struct drv_wifi wifi_sta;
static struct drv_wifi wifi_ap;

#define EXAMPLE_ESP_MAXIMUM_RETRY 5
#define DEFAULT_SCAN_LIST_SIZE 3
static int s_retry_num = 0;

wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];

static rt_err_t drv_wlan_scan_stop(struct rt_wlan_device *wlan);

static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_START) {
        rt_wlan_dev_indicate_event_handle(wifi_ap.wlan, RT_WLAN_DEV_EVT_AP_START, RT_NULL);
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STOP) {
        rt_wlan_dev_indicate_event_handle(wifi_ap.wlan, RT_WLAN_DEV_EVT_AP_STOP, RT_NULL);
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *) event_data;
        rt_wlan_dev_indicate_event_handle(wifi_ap.wlan, RT_WLAN_DEV_EVT_AP_ASSOCIATED, RT_NULL);
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *) event_data;
        rt_wlan_dev_indicate_event_handle(wifi_ap.wlan, RT_WLAN_DEV_EVT_AP_DISASSOCIATED, RT_NULL);
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_CONNECTED) {
        rt_wlan_dev_indicate_event_handle(wifi_sta.wlan, RT_WLAN_DEV_EVT_CONNECT, RT_NULL);
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
        } else {
            rt_wlan_dev_indicate_event_handle(wifi_sta.wlan, RT_WLAN_DEV_EVT_CONNECT_FAIL, RT_NULL);
        }
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_SCAN_DONE) {
        drv_wlan_scan_stop(RT_NULL);
    }
}

static esp_err_t wifi_sta_receive(void *buffer, uint16_t len, void *eb)
{
    rt_wlan_dev_report_data(wifi_sta.wlan, buffer, len);
    return RT_EOK;
}

static esp_err_t wifi_ap_receive(void *buffer, uint16_t len, void *eb)
{
    rt_wlan_dev_report_data(wifi_ap.wlan, buffer, len);
    return RT_EOK;
}

void wifi_init_sta(void)
{
}

void wifi_init_softap(void)
{
}

/* Initialize Wi-Fi as sta and set scan method */
static rt_err_t drv_wlan_scan(struct rt_wlan_device *wlan, struct rt_scan_info *scan_info)
{
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    esp_wifi_scan_start(NULL, false);
}

static rt_err_t drv_wlan_init(struct rt_wlan_device *wlan)
{
    // 初始化时钟以及事件处理
    esp_timer_init();
    esp_event_loop_create_default();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        &instance_any_id));

    // 注册收到内容回调
    ESP_ERROR_CHECK(esp_wifi_internal_reg_rxcb(WIFI_IF_STA,  wifi_sta_receive));
    ESP_ERROR_CHECK(esp_wifi_internal_reg_rxcb(WIFI_IF_AP,  wifi_ap_receive));

    return RT_EOK;
}

static rt_err_t drv_wlan_mode(struct rt_wlan_device *wlan, rt_wlan_mode_t mode)
{
    if (mode == RT_WLAN_STATION) {
        wifi_init_sta();
    } else {
        wifi_init_softap();
    }
    return RT_EOK;
}


static rt_err_t drv_wlan_join(struct rt_wlan_device *wlan, struct rt_sta_info *sta_info)
{
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "",
            .password = "",
            /* Authmode threshold resets to WPA2 as default if password matches WPA2 standards (pasword len => 8).
             * If you want to connect the device to deprecated WEP/WPA networks, Please set the threshold value
             * to WIFI_AUTH_WEP/WIFI_AUTH_WPA_PSK and set the password with length and format matching to
             * WIFI_AUTH_WEP/WIFI_AUTH_WPA_PSK standards.
             */
            .threshold.authmode = WIFI_AUTH_WPA_WPA2_PSK,
            .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
        },
    };
    rt_memcpy(wifi_config.sta.ssid, sta_info->ssid.val, sta_info->ssid.len);
    rt_memcpy(wifi_config.sta.password, sta_info->key.val, sta_info->key.len);
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    return RT_EOK;
}

static rt_err_t drv_wlan_softap(struct rt_wlan_device *wlan, struct rt_ap_info *ap_info)
{
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = "",
            .ssid_len = 0,
            .channel = 3,
            .password = "",
            .max_connection = 3,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK,
            .pmf_cfg = {
                .required = false,
            },
        },
    };
    rt_memcpy(wifi_config.ap.ssid, ap_info->ssid.val, ap_info->ssid.len);
    rt_memcpy(wifi_config.ap.password, ap_info->key.val, ap_info->key.len);
    wifi_config.ap.ssid_len = ap_info->ssid.len;
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    drv_wlan_scan_stop(RT_NULL);
    return RT_EOK;
}

static rt_err_t drv_wlan_disconnect(struct rt_wlan_device *wlan)
{
    ESP_ERROR_CHECK(esp_wifi_disconnect());
    return RT_EOK;
}

static rt_err_t drv_wlan_ap_stop(struct rt_wlan_device *wlan)
{
    return RT_EOK;
}

static rt_err_t drv_wlan_ap_deauth(struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    return RT_EOK;
}

static rt_err_t drv_wlan_scan_stop(struct rt_wlan_device *wlan)
{
    struct rt_wlan_info wlan_info;
    struct rt_wlan_buff buff;
    uint16_t number = DEFAULT_SCAN_LIST_SIZE;
    uint16_t ap_count = 0;

    memset(ap_info, 0, sizeof(ap_info));

    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    for (int i = 0; (i < DEFAULT_SCAN_LIST_SIZE) && (i < ap_count); i++) {
        rt_memset(&wlan_info, 0, sizeof(wlan_info));
        rt_memcpy(&wlan_info.bssid[0], ap_info[i].bssid, 6);
        rt_memcpy(wlan_info.ssid.val, ap_info[i].ssid , strlen(ap_info[i].ssid));

        wlan_info.ssid.len = strlen(ap_info[i].ssid);
        wlan_info.hidden = 0;
        wlan_info.channel = (rt_int16_t)ap_info[i].primary;
        wlan_info.rssi = -(char)(0x100 - ap_info[i].rssi);
        wlan_info.band = RT_802_11_BAND_2_4GHZ;
        wlan_info.security = SECURITY_UNKNOWN;

        buff.data = &wlan_info;
        buff.len = sizeof(wlan_info);
        rt_wlan_dev_indicate_event_handle(wifi_sta.wlan, RT_WLAN_DEV_EVT_SCAN_REPORT, &buff);
    }
    esp_wifi_scan_stop();
    return RT_EOK;
}

static int drv_wlan_get_rssi(struct rt_wlan_device *wlan)
{
    return 0;
}

static rt_err_t drv_wlan_set_powersave(struct rt_wlan_device *wlan, int level)
{
    return RT_EOK;
}

static int drv_wlan_get_powersave(struct rt_wlan_device *wlan)
{
    return 0;
}

static rt_err_t drv_wlan_cfg_promisc(struct rt_wlan_device *wlan, rt_bool_t start)
{
    return RT_EOK;
}

static rt_err_t drv_wlan_cfg_filter(struct rt_wlan_device *wlan, struct rt_wlan_filter *filter)
{
    return -RT_EINVAL;/* not support */
}

static rt_err_t drv_wlan_set_channel(struct rt_wlan_device *wlan, int channel)
{
    return RT_EOK;
}

static int drv_wlan_get_channel(struct rt_wlan_device *wlan)
{
    return 0;
}

static rt_err_t drv_wlan_set_country(struct rt_wlan_device *wlan, rt_country_code_t country_code)
{
    return RT_EOK;
}

static rt_country_code_t drv_wlan_get_country(struct rt_wlan_device *wlan)
{
    return 0;   //RT_EOK;
}

static rt_err_t drv_wlan_set_mac(struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    return RT_EOK;
}

static rt_err_t drv_wlan_get_mac(struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    return RT_EOK;
}

static int drv_wlan_recv(struct rt_wlan_device *wlan, void *buff, int len)
{
    return RT_EOK;
}

static int drv_wlan_send(struct rt_wlan_device *wlan, void *buff, int len)
{
    struct drv_wifi* wifi = wlan->user_data;
    esp_wifi_internal_tx(wifi->wifi_if, buff, len);
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

int rt_hw_wifi_init(void)
{
    // 初始化nvs_flash
    esp_err_t esp_ret = nvs_flash_init();

    if (esp_ret == ESP_ERR_NVS_NO_FREE_PAGES || esp_ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        esp_ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(esp_ret);

    // 向系统注册
    static struct rt_wlan_device wlan;
    static struct rt_wlan_device wlan2;

    rt_memset(&wifi_sta, 0, sizeof(wifi_sta));
    wifi_sta.wifi_if = WIFI_IF_STA;
    rt_err_t ret = rt_wlan_dev_register(&wlan, RT_WLAN_DEVICE_STA_NAME, &ops, 0, &wifi_sta);
    wifi_sta.wlan = &wlan;

    rt_memset(&wifi_ap, 0, sizeof(wifi_ap));
    wifi_ap.wifi_if = WIFI_IF_AP;
    ret |= rt_wlan_dev_register(&wlan2, RT_WLAN_DEVICE_AP_NAME, &ops, 0, &wifi_ap);
    wifi_ap.wlan = &wlan2;

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_wifi_init);

#endif /* RT_USING_WIFI */
