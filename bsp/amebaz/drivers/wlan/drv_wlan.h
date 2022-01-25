/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-7-10      tyx          the first version
 */

#ifndef __DRV_WLAN_H__
#define __DRV_WLAN_H__

typedef enum
{
    RTHW_MODE_NONE = 0,
    RTHW_MODE_STA,
    RTHW_MODE_AP,
    RTHW_MODE_STA_AP,
    RTHW_MODE_PROMISC,
    RTHW_MODE_P2P
}rthw_mode_t;

#define SHARED_ENABLED  0x00008000
#define WPA_SECURITY    0x00200000
#define WPA2_SECURITY   0x00400000
#define WPS_ENABLED     0x10000000
#define WEP_ENABLED     0x0001
#define TKIP_ENABLED    0x0002
#define AES_ENABLED     0x0004
#define WSEC_SWFLAG     0x0008

typedef enum {
    RTHW_SECURITY_OPEN           = 0,                                                /**< Open security                           */
    RTHW_SECURITY_WEP_PSK        = WEP_ENABLED,                                      /**< WEP Security with open authentication   */
    RTHW_SECURITY_WEP_SHARED     = ( WEP_ENABLED | SHARED_ENABLED ),                 /**< WEP Security with shared authentication */
    RTHW_SECURITY_WPA_TKIP_PSK   = ( WPA_SECURITY  | TKIP_ENABLED ),                 /**< WPA Security with TKIP                  */
    RTHW_SECURITY_WPA_AES_PSK    = ( WPA_SECURITY  | AES_ENABLED ),                  /**< WPA Security with AES                   */
    RTHW_SECURITY_WPA2_AES_PSK   = ( WPA2_SECURITY | AES_ENABLED ),                  /**< WPA2 Security with AES                  */
    RTHW_SECURITY_WPA2_TKIP_PSK  = ( WPA2_SECURITY | TKIP_ENABLED ),                 /**< WPA2 Security with TKIP                 */
    RTHW_SECURITY_WPA2_MIXED_PSK = ( WPA2_SECURITY | AES_ENABLED | TKIP_ENABLED ),   /**< WPA2 Security with AES & TKIP           */
    RTHW_SECURITY_WPA_WPA2_MIXED = ( WPA_SECURITY  | WPA2_SECURITY ),                /**< WPA/WPA2 Security                       */

    RTHW_SECURITY_WPS_OPEN       = WPS_ENABLED,                                      /**< WPS with open security                  */
    RTHW_SECURITY_WPS_SECURE     = (WPS_ENABLED | AES_ENABLED),                      /**< WPS with AES security                   */

    RTHW_SECURITY_UNKNOWN        = -1,                                               /**< May be returned by scan function if security is unknown. Do not pass this to the join function! */

    RTHW_SECURITY_FORCE_32_BIT   = 0x7fffffff                                        /**< Exists only to force rtw_security_t type to 32 bits */
} rthw_security_t;

typedef enum {
    RTHW_WIFI_EVENT_CONNECT = 0,
    RTHW_WIFI_EVENT_DISCONNECT = 1,
    RTHW_WIFI_EVENT_FOURWAY_HANDSHAKE_DONE = 2,
    RTHW_WIFI_EVENT_SCAN_RESULT_REPORT = 3,
    RTHW_WIFI_EVENT_SCAN_DONE = 4,
    RTHW_WIFI_EVENT_RECONNECTION_FAIL = 5,
    RTHW_WIFI_EVENT_SEND_ACTION_DONE = 6,
    RTHW_WIFI_EVENT_RX_MGNT = 7,
    RTHW_WIFI_EVENT_STA_ASSOC = 8,
    RTHW_WIFI_EVENT_STA_DISASSOC = 9,
    RTHW_WIFI_EVENT_STA_WPS_START = 10,
    RTHW_WIFI_EVENT_WPS_FINISH = 11,
    RTHW_WIFI_EVENT_EAPOL_START = 12,
    RTHW_WIFI_EVENT_EAPOL_RECVD = 13,
    RTHW_WIFI_EVENT_NO_NETWORK = 14,
    RTHW_WIFI_EVENT_BEACON_AFTER_DHCP = 15,
    RTHW_WIFI_EVENT_MAX,
}rthw_event_indicate_t;

typedef enum {
    RTHW_802_11_BAND_5GHZ   = 0, /**< Denotes 5GHz radio band   */
    RTHW_802_11_BAND_2_4GHZ = 1  /**< Denotes 2.4GHz radio band */
} rthw_802_11_band_t;

struct rthw_wlan_info
{
    char *ssid;
    rt_uint8_t *bssid;
    rthw_802_11_band_t band;
    rt_uint32_t datarate;
    rt_uint16_t channel;
    rt_int16_t  rssi;
    rthw_security_t security;
};

typedef void (*scan_callback_fn)(struct rthw_wlan_info *info, void *user_data);
typedef void (*rthw_wlan_monitor_callback_t)(rt_uint8_t *data, int len, void *user_data);

rthw_mode_t rthw_wifi_mode_get(void);
int rthw_wifi_stop(void);
int rthw_wifi_start(rthw_mode_t mode);
int rthw_wifi_connect(char *ssid, int ssid_len, char *password, int pass_len, rthw_security_t security_type);
int rthw_wifi_connect_bssid(char *bssid, char *ssid, int ssid_len, char *password, int pass_len, rthw_security_t security_type);
int rthw_wifi_ap_start(char *ssid, char *password, int channel);
int rthw_wifi_rssi_get(void);
void rthw_wifi_channel_set(int channel);
int rthw_wifi_channel_get(void);
int rthw_wifi_sta_disconnect(void);
int rthw_wifi_ap_disconnect(void);
int rthw_wifi_scan(scan_callback_fn fun, void *data);
void rthw_wifi_monitor_enable(int enable);
void rthw_wifi_monitor_callback_set(rthw_wlan_monitor_callback_t callback);
#endif
