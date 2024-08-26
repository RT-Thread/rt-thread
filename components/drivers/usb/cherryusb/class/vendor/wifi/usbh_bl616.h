/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_BL616_H
#define USBH_BL616_H

#define USBWIFI_DATA_TYPE_CMD 0xA55A
#define USBWIFI_DATA_TYPE_PKT 0x6996

#define USB_DATA_FLAG_AP_PKT (1u << 0)

typedef enum {
    BFLB_CMD_REBOOT = 0,
    BFLB_CMD_RESET,
    BFLB_CMD_HELLO,
    BFLB_CMD_PING,

    BFLB_CMD_GET_MAC_ADDR,

    // Scan
    BFLB_CMD_SCAN,
    BFLB_CMD_SCAN_RESULTS,

    // STA
    BFLB_CMD_STA_CONNECT,
    BFLB_CMD_STA_DISCONNECT,
    BFLB_CMD_STA_CONNECTED_IND,
    BFLB_CMD_STA_DISCONNECTED_IND,
    BFLB_CMD_STA_IP_UPDATE_IND,
    BFLB_CMD_STA_SET_AUTO_RECONNECT,
    BFLB_CMD_STA_GET_LINK_STATUS,

    // AP
    BFLB_CMD_AP_START,
    BFLB_CMD_AP_STOP,
    BFLB_CMD_AP_STARTED_IND,
    BFLB_CMD_AP_STOPPED_IND,
    BFLB_CMD_AP_GET_STA_LIST,

    // Monitor
    BFLB_CMD_MONITOR_START,
    BFLB_CMD_MONITOR_STOP,
    BFLB_CMD_MONITOR_SET_CHANNEL,
    BFLB_CMD_MONITOR_GET_CHANNEL,

    BFLB_CMD_SET_LPM_MODE,

    // OTA
    BFLB_CMD_GET_DEV_VERSION,
    BFLB_CMD_OTA,

    BFLB_CMD_EXT,

    BFLB_CMD_USER_EXT,
    BFLB_CMD_UNLOAD_DRV,

    BFLB_CMD_MAX,
} bflb_cmd_t;

typedef enum {
    STATUS_OK,
    STATUS_NOMEM = 128,
    STATUS_INVALID_INPUT,
    STATUS_INVALID_MODE,
    STATUS_ERR_UNSPECIFIED,
    STATUS_NOT_IMPLEMENTED,
} cmd_status_t;

typedef enum {
    RNM_WIFI_AUTH_UNKNOWN = 0,
    RNM_WIFI_AUTH_OPEN,
    RNM_WIFI_AUTH_WEP,
    RNM_WIFI_AUTH_WPA_PSK,
    RNM_WIFI_AUTH_WPA2_PSK,
    RNM_WIFI_AUTH_WPA_WPA2_PSK,
    RNM_WIFI_AUTH_WPA_ENTERPRISE,
    RNM_WIFI_AUTH_WPA3_SAE,
    RNM_WIFI_AUTH_WPA2_PSK_WPA3_SAE,
    RNM_WIFI_AUTH_MAX,
} rnm_wifi_auth_mode_t;

typedef enum {
    RNM_WIFI_CIPHER_UNKNOWN = 0,
    RNM_WIFI_CIPHER_NONE,
    RNM_WIFI_CIPHER_WEP,
    RNM_WIFI_CIPHER_AES,
    RNM_WIFI_CIPHER_TKIP,
    RNM_WIFI_CIPHER_TKIP_AES,
    RNM_WIFI_CIPHER_MAX,
} rnm_wifi_cipher_t;

/* common header */
typedef struct {
    uint16_t cmd;
    // flag ACK is used by server to indicate a response to client
#define RNM_MSG_FLAG_ACK         (1 << 0)
    // flag TRANSPARENT is never transfered to peer but used locally
#define RNM_MSG_FLAG_TRANSPARENT (1 << 1)
    // flag ASYNC is used by server to notify client events such as STA_CONNECTED
#define RNM_MSG_FLAG_ASYNC       (1 << 2)
    uint16_t flags;
    uint16_t status;
    uint16_t msg_id;
    uint16_t session_id;
    uint16_t msg_id_replying;
} rnm_base_msg_t;

typedef struct {
    rnm_base_msg_t hdr;
} rnm_ack_msg_t;

typedef struct {
    rnm_base_msg_t hdr;
    uint8_t sta_mac[6];
    uint8_t ap_mac[6];
} rnm_mac_addr_ind_msg_t;

typedef struct {
    rnm_base_msg_t hdr;
    uint16_t ssid_len;
    uint8_t ssid[32];
    uint8_t password[64];
} rnm_sta_connect_msg_t;

typedef struct {
    rnm_base_msg_t hdr;
    uint8_t ip4_addr[4];
    uint8_t ip4_mask[4];
    uint8_t ip4_gw[4];
    uint8_t ip4_dns1[4];
    uint8_t ip4_dns2[4];
    uint8_t gw_mac[6];
} rnm_sta_ip_update_ind_msg_t;

struct bf1b_wifi_scan_record {
    uint8_t bssid[6];
    // TODO use compressed SSID encoding to save room
    uint8_t ssid[32 + 1];
    uint16_t channel;
    int8_t rssi;
    uint8_t auth_mode;
    uint8_t cipher;
} __PACKED;

typedef struct {
    rnm_base_msg_t hdr;
    uint16_t num;
    struct bf1b_wifi_scan_record records[];
} rnm_scan_ind_msg_t;

typedef enum {
    BL_MODE_NONE,
    BL_MODE_STA,      // card is STA
    BL_MODE_AP,       // card is AP
    BL_MODE_STA_AP,   // card is STA&AP
    BL_MODE_SNIFFER,  // card is sniffer
    BL_MODE_MAX,
} bl_wifi_mode_t;

typedef struct {
    uint16_t type;
    uint16_t length;
    uint16_t flags;
    uint16_t payload_offset;
    uint32_t rsvd[8];
    uint8_t payload[];
} __attribute__((aligned(4))) usb_data_t;

struct usbh_bl616 {
    struct usbh_hubport *hport;
    struct usb_endpoint_descriptor *bulkin;  /* Bulk IN endpoint */
    struct usb_endpoint_descriptor *bulkout; /* Bulk OUT endpoint */

    struct usbh_urb bulkout_urb;
    struct usbh_urb bulkin_urb;

    uint8_t intf;

    uint8_t sta_mac[6];
    uint8_t ap_mac[6];
    uint8_t mode;
    bool connect_status;

    void *user_data;
};

#ifdef __cplusplus
extern "C" {
#endif

int usbh_bl616_wifi_sta_connect(const char *ssid,
                                const int ssid_len,
                                const char *password,
                                const int pwd_len);

int usbh_bl616_wifi_sta_disconnect(void);
int usbh_bl616_wifi_scan(void);

void usbh_bl616_sta_connect_callback(void);
void usbh_bl616_sta_disconnect_callback(void);
void usbh_bl616_sta_update_ip(uint8_t ip4_addr[4], uint8_t ip4_mask[4], uint8_t ip4_gw[4]);

uint8_t *usbh_bl616_get_eth_txbuf(void);
int usbh_bl616_eth_output(uint32_t buflen);
void usbh_bl616_eth_input(uint8_t *buf, uint32_t buflen);
void usbh_bl616_rx_thread(void *argument);

void usbh_bl616_run(struct usbh_bl616 *bl616_class);
void usbh_bl616_stop(struct usbh_bl616 *bl616_class);

int wifi_sta_connect(int argc, char **argv);
int wifi_scan(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif /* USBH_BL616_H */
