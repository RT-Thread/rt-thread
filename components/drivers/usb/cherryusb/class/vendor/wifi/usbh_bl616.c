/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_bl616.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_bl616"
#include "usb_log.h"

#define DEV_FORMAT "/dev/wifi/bl616"

#define MAC_FMT      "%02X:%02X:%02X:%02X:%02X:%02X"
#define ARR_ELE_6(e) (e)[0], (e)[1], (e)[2], (e)[3], (e)[4], (e)[5]

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_bl616_tx_buffer[2048 + 512];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_bl616_rx_buffer[2048 + 512];

static struct usbh_bl616 g_bl616_class;

static const char *auth_to_str(uint8_t auth)
{
    const char *table[RNM_WIFI_AUTH_MAX] = {
        [RNM_WIFI_AUTH_UNKNOWN] = "UNKNOWN",
        [RNM_WIFI_AUTH_OPEN] = "OPEN",
        [RNM_WIFI_AUTH_WEP] = "WEP",
        [RNM_WIFI_AUTH_WPA_PSK] = "WPA-PSK",
        [RNM_WIFI_AUTH_WPA2_PSK] = "WPA2-PSK",
        [RNM_WIFI_AUTH_WPA_WPA2_PSK] = "WPA2-PSK/WPA-PSK",
        [RNM_WIFI_AUTH_WPA_ENTERPRISE] = "WPA-ENT",
        [RNM_WIFI_AUTH_WPA3_SAE] = "WPA3-SAE",
        [RNM_WIFI_AUTH_WPA2_PSK_WPA3_SAE] = "WPA2-PSK/WPA3-SAE",
    };
    if (auth < RNM_WIFI_AUTH_MAX)
        return table[auth];
    else
        return table[RNM_WIFI_AUTH_UNKNOWN];
}

static const char *cipher_to_str(uint8_t cipher)
{
    const char *table[RNM_WIFI_CIPHER_MAX] = {
        [RNM_WIFI_CIPHER_UNKNOWN] = "UNKNOWN",
        [RNM_WIFI_CIPHER_NONE] = "NONE",
        [RNM_WIFI_CIPHER_WEP] = "WEP",
        [RNM_WIFI_CIPHER_AES] = "AES",
        [RNM_WIFI_CIPHER_TKIP] = "TKIP",
        [RNM_WIFI_CIPHER_TKIP_AES] = "TKIP/AES",
    };
    if (cipher < RNM_WIFI_CIPHER_MAX)
        return table[cipher];
    else
        return table[RNM_WIFI_CIPHER_UNKNOWN];
}

static int parse_get_mac_rsp_msg(struct usbh_bl616 *bl616_class, void *buf, int buf_len)
{
    usb_data_t *usb_hdr = buf;
    rnm_mac_addr_ind_msg_t *rsp = buf + sizeof(usb_data_t);

    if (buf_len != sizeof(usb_data_t) + sizeof(rnm_mac_addr_ind_msg_t)) {
        return -1;
    }
    if (usb_hdr->type != USBWIFI_DATA_TYPE_CMD || usb_hdr->length != sizeof(rnm_mac_addr_ind_msg_t)) {
        return -1;
    }
    if (rsp->hdr.cmd != BFLB_CMD_GET_MAC_ADDR || !(rsp->hdr.flags & RNM_MSG_FLAG_ACK)) {
        return -1;
    }
    memcpy(bl616_class->sta_mac, rsp->sta_mac, 6);
    memcpy(bl616_class->ap_mac, rsp->ap_mac, 6);

    return 0;
}

static int usbh_bl616_bulk_in_transfer(struct usbh_bl616 *bl616_class, uint8_t *buffer, uint32_t buflen, uint32_t timeout)
{
    int ret;
    struct usbh_urb *urb = &bl616_class->bulkin_urb;

    usbh_bulk_urb_fill(urb, bl616_class->hport, bl616_class->bulkin, buffer, buflen, timeout, NULL, NULL);
    ret = usbh_submit_urb(urb);
    if (ret == 0) {
        ret = urb->actual_length;
    }
    return ret;
}

static int usbh_bl616_bulk_out_transfer(struct usbh_bl616 *bl616_class, uint8_t *buffer, uint32_t buflen, uint32_t timeout)
{
    int ret;
    struct usbh_urb *urb = &bl616_class->bulkout_urb;

    usbh_bulk_urb_fill(urb, bl616_class->hport, bl616_class->bulkout, buffer, buflen, timeout, NULL, NULL);
    ret = usbh_submit_urb(urb);
    if (ret == 0) {
        ret = urb->actual_length;
    }
    return ret;
}

static int usbh_bl616_get_wifi_mac(struct usbh_bl616 *bl616_class)
{
    int ret;
    uint32_t msg_len;
    usb_data_t *usb_hdr = (usb_data_t *)g_bl616_tx_buffer;
    rnm_base_msg_t *rnm_msg = (rnm_base_msg_t *)(g_bl616_tx_buffer + sizeof(usb_data_t));

    memset(usb_hdr, 0, sizeof(usb_data_t));
    memset(rnm_msg, 0, sizeof(rnm_base_msg_t));

    usb_hdr->type = USBWIFI_DATA_TYPE_CMD;
    usb_hdr->length = sizeof(rnm_base_msg_t);
    usb_hdr->payload_offset = sizeof(usb_data_t);

    rnm_msg->cmd = BFLB_CMD_GET_MAC_ADDR;

    msg_len = sizeof(usb_data_t) + sizeof(rnm_base_msg_t);

    ret = usbh_bl616_bulk_out_transfer(bl616_class, g_bl616_tx_buffer, msg_len, 500);
    if (ret < 0) {
        return ret;
    }
    ret = usbh_bl616_bulk_in_transfer(bl616_class, g_bl616_rx_buffer, sizeof(g_bl616_rx_buffer), 500);
    if (ret < 0) {
        return ret;
    }

    ret = parse_get_mac_rsp_msg(bl616_class, g_bl616_rx_buffer, ret);
    return ret;
}

static int usbh_bl616_wifi_open(struct usbh_bl616 *bl616_class)
{
    uint32_t msg_len;
    usb_data_t *usb_hdr = (usb_data_t *)g_bl616_tx_buffer;
    rnm_base_msg_t *msg = (rnm_base_msg_t *)(g_bl616_tx_buffer + sizeof(usb_data_t));

    memset(usb_hdr, 0, sizeof(usb_data_t));
    memset(msg, 0, sizeof(rnm_base_msg_t));

    usb_hdr->type = USBWIFI_DATA_TYPE_CMD;
    usb_hdr->length = sizeof(rnm_base_msg_t);
    usb_hdr->payload_offset = sizeof(usb_data_t);

    msg->cmd = BFLB_CMD_HELLO;

    msg_len = sizeof(usb_data_t) + sizeof(rnm_base_msg_t);

    return usbh_bl616_bulk_out_transfer(bl616_class, g_bl616_tx_buffer, msg_len, 500);
}

static int usbh_bl616_wifi_close(struct usbh_bl616 *bl616_class)
{
    uint32_t msg_len;
    usb_data_t *usb_hdr = (usb_data_t *)g_bl616_tx_buffer;
    rnm_base_msg_t *msg = (rnm_base_msg_t *)(g_bl616_tx_buffer + sizeof(usb_data_t));

    memset(usb_hdr, 0, sizeof(usb_data_t));
    memset(msg, 0, sizeof(rnm_base_msg_t));

    usb_hdr->type = USBWIFI_DATA_TYPE_CMD;
    usb_hdr->length = sizeof(rnm_base_msg_t);
    usb_hdr->payload_offset = sizeof(usb_data_t);

    msg->cmd = BFLB_CMD_UNLOAD_DRV;

    msg_len = sizeof(usb_data_t) + sizeof(rnm_base_msg_t);

    return usbh_bl616_bulk_out_transfer(bl616_class, g_bl616_tx_buffer, msg_len, 500);
}

int usbh_bl616_wifi_sta_connect(const char *ssid,
                                const int ssid_len,
                                const char *password,
                                const int pwd_len)
{
    uint32_t msg_len;
    usb_data_t *usb_hdr = (usb_data_t *)g_bl616_tx_buffer;
    rnm_sta_connect_msg_t *msg = (rnm_sta_connect_msg_t *)(g_bl616_tx_buffer + sizeof(usb_data_t));

    memset(usb_hdr, 0, sizeof(usb_data_t));
    memset(msg, 0, sizeof(rnm_sta_connect_msg_t));

    usb_hdr->type = USBWIFI_DATA_TYPE_CMD;
    usb_hdr->length = sizeof(rnm_sta_connect_msg_t);
    usb_hdr->payload_offset = sizeof(usb_data_t);

    msg->hdr.cmd = BFLB_CMD_STA_CONNECT;
    msg->hdr.msg_id = 0x0001;
    msg->hdr.session_id = 0x0002;
    msg->ssid_len = ssid_len;
    memcpy(msg->ssid, ssid, ssid_len);
    if (password) {
        memcpy(msg->password, password, pwd_len);
    }

    msg_len = sizeof(usb_data_t) + sizeof(rnm_sta_connect_msg_t);

    return usbh_bl616_bulk_out_transfer(&g_bl616_class, g_bl616_tx_buffer, msg_len, 500);
}

int usbh_bl616_wifi_sta_disconnect(void)
{
    uint32_t msg_len;
    usb_data_t *usb_hdr = (usb_data_t *)g_bl616_tx_buffer;
    rnm_base_msg_t *msg = (rnm_base_msg_t *)(g_bl616_tx_buffer + sizeof(usb_data_t));

    memset(usb_hdr, 0, sizeof(usb_data_t));
    memset(msg, 0, sizeof(rnm_base_msg_t));

    usb_hdr->type = USBWIFI_DATA_TYPE_CMD;
    usb_hdr->length = sizeof(rnm_base_msg_t);
    usb_hdr->payload_offset = sizeof(usb_data_t);

    msg->cmd = BFLB_CMD_STA_DISCONNECT;

    msg_len = sizeof(usb_data_t) + sizeof(rnm_base_msg_t);

    return usbh_bl616_bulk_out_transfer(&g_bl616_class, g_bl616_tx_buffer, msg_len, 500);
}

int usbh_bl616_get_wifi_scan_result(void)
{
    uint32_t msg_len;
    usb_data_t *usb_hdr = (usb_data_t *)g_bl616_tx_buffer;
    rnm_base_msg_t *msg = (rnm_base_msg_t *)(g_bl616_tx_buffer + sizeof(usb_data_t));

    memset(usb_hdr, 0, sizeof(usb_data_t));
    memset(msg, 0, sizeof(rnm_base_msg_t));

    usb_hdr->type = USBWIFI_DATA_TYPE_CMD;
    usb_hdr->length = sizeof(rnm_base_msg_t);
    usb_hdr->payload_offset = sizeof(usb_data_t);

    msg->cmd = BFLB_CMD_SCAN_RESULTS;

    msg_len = sizeof(usb_data_t) + sizeof(rnm_base_msg_t);

    return usbh_bl616_bulk_out_transfer(&g_bl616_class, g_bl616_tx_buffer, msg_len, 500);
}

int usbh_bl616_wifi_scan(void)
{
    int ret;
    uint32_t msg_len;
    usb_data_t *usb_hdr = (usb_data_t *)g_bl616_tx_buffer;
    rnm_base_msg_t *msg = (rnm_base_msg_t *)(g_bl616_tx_buffer + sizeof(usb_data_t));

    memset(usb_hdr, 0, sizeof(usb_data_t));
    memset(msg, 0, sizeof(rnm_base_msg_t));

    usb_hdr->type = USBWIFI_DATA_TYPE_CMD;
    usb_hdr->length = sizeof(rnm_base_msg_t);
    usb_hdr->payload_offset = sizeof(usb_data_t);

    msg->cmd = BFLB_CMD_SCAN;

    msg_len = sizeof(usb_data_t) + sizeof(rnm_base_msg_t);

    ret = usbh_bl616_bulk_out_transfer(&g_bl616_class, g_bl616_tx_buffer, msg_len, 500);
    if (ret < 0) {
        return ret;
    }

    usb_osal_msleep(500);
    return usbh_bl616_get_wifi_scan_result();
}

static int usbh_bl616_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    int ret = 0;

    struct usbh_bl616 *bl616_class = &g_bl616_class;

    memset(bl616_class, 0, sizeof(struct usbh_bl616));

    bl616_class->hport = hport;
    bl616_class->intf = intf;

    hport->config.intf[intf].priv = bl616_class;

    for (uint8_t i = 0; i < hport->config.intf[intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &hport->config.intf[intf].altsetting[0].ep[i].ep_desc;

        if (ep_desc->bEndpointAddress & 0x80) {
            USBH_EP_INIT(bl616_class->bulkin, ep_desc);
        } else {
            USBH_EP_INIT(bl616_class->bulkout, ep_desc);
        }
    }

    usbh_bl616_get_wifi_mac(bl616_class);
    usbh_bl616_wifi_close(bl616_class);
    usbh_bl616_wifi_open(bl616_class);

    USB_LOG_INFO("BL616 WIFI STA MAC address %02x:%02x:%02x:%02x:%02x:%02x\r\n",
                 bl616_class->sta_mac[0],
                 bl616_class->sta_mac[1],
                 bl616_class->sta_mac[2],
                 bl616_class->sta_mac[3],
                 bl616_class->sta_mac[4],
                 bl616_class->sta_mac[5]);

    USB_LOG_INFO("BL616 WIFI AP MAC address %02x:%02x:%02x:%02x:%02x:%02x\r\n",
                 bl616_class->ap_mac[0],
                 bl616_class->ap_mac[1],
                 bl616_class->ap_mac[2],
                 bl616_class->ap_mac[3],
                 bl616_class->ap_mac[4],
                 bl616_class->ap_mac[5]);

    strncpy(hport->config.intf[intf].devname, DEV_FORMAT, CONFIG_USBHOST_DEV_NAMELEN);

    USB_LOG_INFO("Register BL616 WIFI Class:%s\r\n", hport->config.intf[intf].devname);

    usbh_bl616_run(bl616_class);
    return ret;
}

static int usbh_bl616_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_bl616 *bl616_class = (struct usbh_bl616 *)hport->config.intf[intf].priv;

    if (bl616_class) {
        if (bl616_class->bulkin) {
            usbh_kill_urb(&bl616_class->bulkin_urb);
        }

        if (bl616_class->bulkout) {
            usbh_kill_urb(&bl616_class->bulkout_urb);
        }

        if (hport->config.intf[intf].devname[0] != '\0') {
            USB_LOG_INFO("Unregister BL616 WIFI Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_bl616_stop(bl616_class);
        }

        memset(bl616_class, 0, sizeof(struct usbh_bl616));
    }

    return ret;
}

void usbh_bl616_rx_thread(void *argument)
{
    int ret;
    usb_data_t *usb_hdr;
    rnm_base_msg_t *msg;
    rnm_sta_ip_update_ind_msg_t *ipmsg;
    rnm_scan_ind_msg_t *scanmsg;
    uint8_t *data;

    (void)argument;
    USB_LOG_INFO("Create bl616 wifi rx thread\r\n");

    while (1) {
        ret = usbh_bl616_bulk_in_transfer(&g_bl616_class, g_bl616_rx_buffer, sizeof(g_bl616_rx_buffer), USB_OSAL_WAITING_FOREVER);
        if (ret < 0) {
            break;
        }

        usb_hdr = (usb_data_t *)g_bl616_rx_buffer;

        if (usb_hdr->type == USBWIFI_DATA_TYPE_CMD) {
            msg = (rnm_base_msg_t *)(g_bl616_rx_buffer + usb_hdr->payload_offset);

            switch (msg->cmd) {
                case BFLB_CMD_STA_CONNECTED_IND:
                    USB_LOG_INFO("AP connected\n");
                    g_bl616_class.connect_status = true;
                    usbh_bl616_sta_connect_callback();

                    break;
                case BFLB_CMD_STA_DISCONNECTED_IND:
                    if (g_bl616_class.connect_status == true) {
                        g_bl616_class.connect_status = false;
                        USB_LOG_INFO("AP disconnected\n");
                        usbh_bl616_sta_disconnect_callback();
                    }
                    break;
                case BFLB_CMD_STA_IP_UPDATE_IND:
                    ipmsg = (rnm_sta_ip_update_ind_msg_t *)(g_bl616_rx_buffer + usb_hdr->payload_offset);

                    USB_LOG_INFO("WIFI IP update\r\n");
                    USB_LOG_INFO("WIFI IPv4 Address     : %d:%d:%d:%d\r\n",
                                 ipmsg->ip4_addr[0],
                                 ipmsg->ip4_addr[1],
                                 ipmsg->ip4_addr[2],
                                 ipmsg->ip4_addr[3]);
                    USB_LOG_INFO("WIFI IPv4 Mask        : %d:%d:%d:%d\r\n",
                                 ipmsg->ip4_mask[0],
                                 ipmsg->ip4_mask[1],
                                 ipmsg->ip4_mask[2],
                                 ipmsg->ip4_mask[3]);
                    USB_LOG_INFO("WIFI IPv4 Gateway     : %d:%d:%d:%d\r\n\r\n",
                                 ipmsg->ip4_gw[0],
                                 ipmsg->ip4_gw[1],
                                 ipmsg->ip4_gw[2],
                                 ipmsg->ip4_gw[3]);

                    g_bl616_class.mode = BL_MODE_STA;
                    usbh_bl616_sta_update_ip(ipmsg->ip4_addr, ipmsg->ip4_mask, ipmsg->ip4_gw);
                    break;
                case BFLB_CMD_SCAN_RESULTS:
                    scanmsg = (rnm_scan_ind_msg_t *)(g_bl616_rx_buffer + usb_hdr->payload_offset);
                    USB_LOG_INFO("WIFI scan result:\r\n");
                    for (uint32_t i = 0; i < scanmsg->num; ++i) {
                        struct bf1b_wifi_scan_record *r = &scanmsg->records[i];
                        USB_LOG_INFO("BSSID " MAC_FMT ", channel %u, rssi %d, auth %s, cipher %s, SSID %s\r\n",
                                     ARR_ELE_6(r->bssid), r->channel, r->rssi,
                                     auth_to_str(r->auth_mode), cipher_to_str(r->cipher), r->ssid);
                    }
                    break;
                default:
                    break;
            }
        } else if (usb_hdr->type == USBWIFI_DATA_TYPE_PKT) {
            data = (uint8_t *)(g_bl616_rx_buffer + usb_hdr->payload_offset);
            usbh_bl616_eth_input(data, usb_hdr->length);
        } else {
        }
    }

    USB_LOG_INFO("Delete bl616 wifi rx thread\r\n");
    usb_osal_thread_delete(NULL);
}

uint8_t *usbh_bl616_get_eth_txbuf(void)
{
    return (g_bl616_tx_buffer + sizeof(usb_data_t));
}

int usbh_bl616_eth_output(uint32_t buflen)
{
    usb_data_t *usb_hdr;
    uint32_t txlen;

    if (g_bl616_class.connect_status == false) {
        return -USB_ERR_NOTCONN;
    }

    usb_hdr = (usb_data_t *)g_bl616_tx_buffer;
    memset(usb_hdr, 0, sizeof(usb_data_t));

    usb_hdr->type = USBWIFI_DATA_TYPE_PKT;
    usb_hdr->length = buflen;
    usb_hdr->payload_offset = sizeof(usb_data_t);

    txlen = buflen + sizeof(usb_data_t);
    if (!(txlen % USB_GET_MAXPACKETSIZE(g_bl616_class.bulkout->wMaxPacketSize))) {
        txlen += 1;
    }
    USB_LOG_DBG("txlen:%d\r\n", txlen);

    usbh_bulk_urb_fill(&g_bl616_class.bulkout_urb, g_bl616_class.hport, g_bl616_class.bulkout, g_bl616_tx_buffer, txlen, USB_OSAL_WAITING_FOREVER, NULL, NULL);
    return usbh_submit_urb(&g_bl616_class.bulkout_urb);
}

int wifi_sta_connect(int argc, char **argv)
{
    if (argc < 3) {
        USB_LOG_ERR("Usage: %s <ssid> <password>\r\n", argv[0]);
        return -1;
    }
    usbh_bl616_wifi_sta_connect(argv[1], strlen(argv[1]), argv[2], strlen(argv[2]));
    return 0;
}

int wifi_scan(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    usbh_bl616_wifi_scan();
    return 0;
}

__WEAK void usbh_bl616_run(struct usbh_bl616 *bl616_class)
{
    (void)bl616_class;
}

__WEAK void usbh_bl616_stop(struct usbh_bl616 *bl616_class)
{
    (void)bl616_class;
}

static const uint16_t bl616_id_table[][2] = {
    { 0x349b, 0x616f },
    { 0, 0 },
};

static const struct usbh_class_driver bl616_class_driver = {
    .driver_name = "bl616_wifi",
    .connect = usbh_bl616_connect,
    .disconnect = usbh_bl616_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info bl616_class_info = {
    .match_flags = USB_CLASS_MATCH_VID_PID | USB_CLASS_MATCH_INTF_CLASS,
    .class = 0xff,
    .subclass = 0x00,
    .protocol = 0x00,
    .id_table = bl616_id_table,
    .class_driver = &bl616_class_driver
};
