/*
 *  RT-Thread Wi-Fi Device
 *
 * COPYRIGHT (C) 2014 - 2018, Shanghai Real-Thread Technology Co., Ltd
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

#ifndef WIFI_DEVICE_H__
#define WIFI_DEVICE_H__

#include <stdint.h>
#include <netif/ethernetif.h>

typedef enum
{
    WIFI_NONE,
    WIFI_STATION,
    WIFI_AP,
} rt_wlan_mode_t;

typedef enum
{
    WIFI_INIT = 0x10,
    WIFI_SCAN,              /* trigger scanning (list cells) */
    WIFI_JOIN,
    WIFI_EASYJOIN,          /* join network with less information */
    WIFI_SOFTAP,            /* start soft-AP */
    WIFI_DISCONNECT,
    WIFI_GET_RSSI,          /* get sensitivity (dBm) */
    WIFI_ENTER_POWERSAVE,
    WIFI_CFG_MONITOR,       /* start/stop minitor */
    WIFI_SET_CHANNEL,
    WIFI_GET_CHANNEL,
    WIFI_SET_MONITOR_CALLBACK,
} rt_wlan_cmd_t;

typedef enum
{
    WIFI_PWR_OFF,
    WIFI_PWR_SLEEP,
    WIFI_PWR_NORMAL
} rt_wlan_powersave_t;

typedef enum
{
    WIFI_MONITOR_START,
    WIFI_MONITOR_STOP
} rt_wlan_monitor_opition_t;

#define SHARED_ENABLED  0x00008000
#define WPA_SECURITY    0x00200000
#define WPA2_SECURITY   0x00400000
#define WPS_ENABLED     0x10000000
#define WEP_ENABLED     0x0001
#define TKIP_ENABLED    0x0002
#define AES_ENABLED     0x0004
#define WSEC_SWFLAG     0x0008

#define KEY_ARRAY_SIZE  32
#define SSID_LENGTH_MAX_SIZE  32 + 1
/**
 * Enumeration of Wi-Fi security modes
 */
typedef enum
{
    SECURITY_OPEN           = 0,                                                /**< Open security                           */
    SECURITY_WEP_PSK        = WEP_ENABLED,                                      /**< WEP Security with open authentication   */
    SECURITY_WEP_SHARED     = (WEP_ENABLED | SHARED_ENABLED),                   /**< WEP Security with shared authentication */
    SECURITY_WPA_TKIP_PSK   = (WPA_SECURITY  | TKIP_ENABLED),                   /**< WPA Security with TKIP                  */
    SECURITY_WPA_AES_PSK    = (WPA_SECURITY  | AES_ENABLED),                    /**< WPA Security with AES                   */
    SECURITY_WPA2_AES_PSK   = (WPA2_SECURITY | AES_ENABLED),                    /**< WPA2 Security with AES                  */
    SECURITY_WPA2_TKIP_PSK  = (WPA2_SECURITY | TKIP_ENABLED),                   /**< WPA2 Security with TKIP                 */
    SECURITY_WPA2_MIXED_PSK = (WPA2_SECURITY | AES_ENABLED | TKIP_ENABLED),     /**< WPA2 Security with AES & TKIP           */
    SECURITY_WPS_OPEN       = WPS_ENABLED,                                      /**< WPS with open security                  */
    SECURITY_WPS_SECURE     = (WPS_ENABLED | AES_ENABLED),                      /**< WPS with AES security                   */
    SECURITY_UNKNOWN        = -1,                                               /**< May be returned by scan function if security is unknown.
                                                                                     Do not pass this to the join function! */
} rt_wlan_security_t;

typedef enum
{
    WIFI_EVT_INIT_DONE = 0,
    WIFI_EVT_LINK_DOWN,
    WIFI_EVT_LINK_UP,
    WIFI_EVT_CONNECT,
    WIFI_EVT_DISCONNECT,
    WIFI_EVT_AP_START,
    WIFI_EVT_AP_STOP,
    WIFI_EVENT_STA_ASSOC,
    WIFI_EVENT_STA_DISASSOC,
    WIFI_EVT_SCAN_DONE,
    WIFI_EVT_MAX,
} rt_wlan_event_t;

/* wifi network information */
struct rt_wlan_info
{
    rt_wlan_mode_t mode;   /* wifi mode */
    rt_wlan_security_t security;

    char *ssid;
    uint8_t bssid[6];

    /* maximal data rate */
    uint32_t datarate;
    /* radio channel */
    uint16_t channel;
    /* signal strength */
    int16_t  rssi;
};

struct rt_wlan_info_request
{
    uint16_t req_number;    /* the number of information item for request */
    uint16_t rsp_number;    /* the number of information item for response */

    struct rt_wlan_info *infos;/* the array of information to save response */
};

typedef struct rt_wlan_scan_result
{
    char ap_num;
    struct rt_wlan_info *ap_table;
} rt_wlan_scan_result_t;

struct rt_wlan_device;
typedef void (*rt_wlan_event_handler)(struct rt_wlan_device *device, rt_wlan_event_t event, void *user_data);
typedef void (*rt_wlan_monitor_callback_t)(uint8_t *data, int len, void *user_data);
struct rt_wlan_device
{
    struct eth_device parent;

    struct rt_wlan_info *info;
    char key[KEY_ARRAY_SIZE + 1];

    rt_wlan_event_handler handler[WIFI_EVT_MAX];
    void *user_data;
    int interface;
};

/*
 * Wi-Fi Information APIs
 */
void rt_wlan_info_init(struct rt_wlan_info *info, rt_wlan_mode_t mode, rt_wlan_security_t security,
                       char *ssid);
void rt_wlan_info_deinit(struct rt_wlan_info *info);

/*
 * Wi-Fi Manager APIs
 */
int rt_wlan_init(struct rt_wlan_device *device, rt_wlan_mode_t mode);

int rt_wlan_connect(struct rt_wlan_device *device, struct rt_wlan_info *info,
                    char *password);
int rt_wlan_disconnect(struct rt_wlan_device *device);

int rt_wlan_softap(struct rt_wlan_device *device, struct rt_wlan_info *info,
                   char *password);

/* set wifi information for AP */
int rt_wlan_set_info(struct rt_wlan_device *device, struct rt_wlan_info *info);
/* get wifi information for AP */
struct rt_wlan_info *rt_wlan_get_info(struct rt_wlan_device *device);

/* get the AP result which were scaned in station */
int rt_wlan_scan(struct rt_wlan_device *device, struct rt_wlan_scan_result **scan_result);

/* get rssi */
int rt_wlan_get_rssi(struct rt_wlan_device *device);
/* Get/Set MAC */
int rt_wlan_get_mac(struct rt_wlan_device *device, rt_uint8_t hwaddr[6]);
int rt_wlan_set_mac(struct rt_wlan_device *device, rt_uint8_t hwaddr[6]);

/* enter power save level */
int rt_wlan_enter_powersave(struct rt_wlan_device *device, int level);

/* register the event handler */
int rt_wlan_register_event_handler(struct rt_wlan_device *device, rt_wlan_event_t event,
                                   rt_wlan_event_handler handler);

/* un-register the event handler */
int rt_wlan_unregister_event_handler(struct rt_wlan_device *device, rt_wlan_event_t event);

/* wlan driver indicate event to upper layer through wifi_indication. */
int rt_wlan_indicate_event_handle(struct rt_wlan_device *device, rt_wlan_event_t event,
                                  void *user_data);

/* start or stop monitor */
int rt_wlan_cfg_monitor(struct rt_wlan_device *device, rt_wlan_monitor_opition_t opition);

/* set callback function for monitor mode*/
int rt_wlan_set_monitor_callback(struct rt_wlan_device *device, rt_wlan_monitor_callback_t callback);

/* Set the monitor channel */
int rt_wlan_set_channel(struct rt_wlan_device *device, int channel);

void rt_wlan_release_scan_result(struct rt_wlan_scan_result **scan_result);

#endif
