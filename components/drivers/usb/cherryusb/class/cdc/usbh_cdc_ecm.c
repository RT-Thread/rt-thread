/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_cdc_ecm.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_cdc_ecm"
#include "usb_log.h"

#define DEV_FORMAT "/dev/cdc_ether"

/* general descriptor field offsets */
#define DESC_bLength            0 /** Length offset */
#define DESC_bDescriptorType    1 /** Descriptor type offset */
#define DESC_bDescriptorSubType 2 /** Descriptor subtype offset */

/* interface descriptor field offsets */
#define INTF_DESC_bInterfaceNumber  2 /** Interface number offset */
#define INTF_DESC_bAlternateSetting 3 /** Alternate setting offset */

#define CONFIG_USBHOST_CDC_ECM_PKT_FILTER     0x000C
#define CONFIG_USBHOST_CDC_ECM_ETH_MAX_SEGSZE 1514U

static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_cdc_ecm_rx_buffer[CONFIG_USBHOST_CDC_ECM_ETH_MAX_SEGSZE];
static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_cdc_ecm_tx_buffer[CONFIG_USBHOST_CDC_ECM_ETH_MAX_SEGSZE];
static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_cdc_ecm_inttx_buffer[16];

static struct usbh_cdc_ecm g_cdc_ecm_class;

static int usbh_cdc_ecm_set_eth_packet_filter(struct usbh_cdc_ecm *cdc_ecm_class, uint16_t filter_value)
{
    struct usb_setup_packet *setup = cdc_ecm_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_SET_ETHERNET_PACKET_FILTER;
    setup->wValue = filter_value;
    setup->wIndex = cdc_ecm_class->ctrl_intf;
    setup->wLength = 0;

    return usbh_control_transfer(cdc_ecm_class->hport, setup, NULL);
}

int usbh_cdc_ecm_get_connect_status(struct usbh_cdc_ecm *cdc_ecm_class)
{
    int ret;

    usbh_int_urb_fill(&cdc_ecm_class->intin_urb, cdc_ecm_class->hport, cdc_ecm_class->intin, g_cdc_ecm_inttx_buffer, 16, USB_OSAL_WAITING_FOREVER, NULL, NULL);
    ret = usbh_submit_urb(&cdc_ecm_class->intin_urb);
    if (ret < 0) {
        return ret;
    }

    if (g_cdc_ecm_inttx_buffer[1] == CDC_ECM_NOTIFY_CODE_NETWORK_CONNECTION) {
        if (g_cdc_ecm_inttx_buffer[2] == CDC_ECM_NET_CONNECTED) {
            cdc_ecm_class->connect_status = true;
        } else {
            cdc_ecm_class->connect_status = false;
        }
    } else if (g_cdc_ecm_inttx_buffer[1] == CDC_ECM_NOTIFY_CODE_CONNECTION_SPEED_CHANGE) {
        memcpy(cdc_ecm_class->speed, &g_cdc_ecm_inttx_buffer[8], 8);
    }
    return 0;
}

static int usbh_cdc_ecm_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    int ret;
    uint8_t altsetting = 0;
    char mac_buffer[12];
    uint8_t *p;
    uint8_t cur_iface = 0xff;
    uint8_t mac_str_idx = 0xff;

    struct usbh_cdc_ecm *cdc_ecm_class = &g_cdc_ecm_class;

    memset(cdc_ecm_class, 0, sizeof(struct usbh_cdc_ecm));

    cdc_ecm_class->hport = hport;
    cdc_ecm_class->ctrl_intf = intf;
    cdc_ecm_class->data_intf = intf + 1;

    hport->config.intf[intf].priv = cdc_ecm_class;
    hport->config.intf[intf + 1].priv = NULL;

    p = hport->raw_config_desc;
    while (p[DESC_bLength]) {
        switch (p[DESC_bDescriptorType]) {
            case USB_DESCRIPTOR_TYPE_INTERFACE:
                cur_iface = p[INTF_DESC_bInterfaceNumber];
                //cur_alt_setting = p[INTF_DESC_bAlternateSetting];
                break;
            case CDC_CS_INTERFACE:
                if ((cur_iface == cdc_ecm_class->ctrl_intf) && p[DESC_bDescriptorSubType] == CDC_FUNC_DESC_ETHERNET_NETWORKING) {
                    struct cdc_eth_descriptor *desc = (struct cdc_eth_descriptor *)p;
                    mac_str_idx = desc->iMACAddress;
                    cdc_ecm_class->max_segment_size = desc->wMaxSegmentSize;
                    goto get_mac;
                }
                break;

            default:
                break;
        }
        /* skip to next descriptor */
        p += p[DESC_bLength];
    }

get_mac:
    if (mac_str_idx == 0xff) {
        USB_LOG_ERR("Do not find cdc ecm mac string\r\n");
        return -1;
    }

    memset(mac_buffer, 0, 12);
    ret = usbh_get_string_desc(cdc_ecm_class->hport, mac_str_idx, (uint8_t *)mac_buffer);
    if (ret < 0) {
        return ret;
    }

    for (int i = 0, j = 0; i < 12; i += 2, j++) {
        char byte_str[3];
        byte_str[0] = mac_buffer[i];
        byte_str[1] = mac_buffer[i + 1];
        byte_str[2] = '\0';

        uint32_t byte = strtoul(byte_str, NULL, 16);
        cdc_ecm_class->mac[j] = (unsigned char)byte;
    }

    USB_LOG_INFO("CDC ECM MAC address %02x:%02x:%02x:%02x:%02x:%02x\r\n",
                 cdc_ecm_class->mac[0],
                 cdc_ecm_class->mac[1],
                 cdc_ecm_class->mac[2],
                 cdc_ecm_class->mac[3],
                 cdc_ecm_class->mac[4],
                 cdc_ecm_class->mac[5]);

    if (cdc_ecm_class->max_segment_size > CONFIG_USBHOST_CDC_ECM_ETH_MAX_SEGSZE) {
        USB_LOG_ERR("CDC ECM Max Segment Size is overflow, default is %u, but now %u\r\n", CONFIG_USBHOST_CDC_ECM_ETH_MAX_SEGSZE, cdc_ecm_class->max_segment_size);
    } else {
        USB_LOG_INFO("CDC ECM Max Segment Size:%u\r\n", cdc_ecm_class->max_segment_size);
    }

    /* enable int ep */
    ep_desc = &hport->config.intf[intf].altsetting[0].ep[0].ep_desc;
    USBH_EP_INIT(cdc_ecm_class->intin, ep_desc);

    if (hport->config.intf[intf + 1].altsetting_num > 1) {
        altsetting = hport->config.intf[intf + 1].altsetting_num - 1;

        for (uint8_t i = 0; i < hport->config.intf[intf + 1].altsetting[altsetting].intf_desc.bNumEndpoints; i++) {
            ep_desc = &hport->config.intf[intf + 1].altsetting[altsetting].ep[i].ep_desc;

            if (ep_desc->bEndpointAddress & 0x80) {
                USBH_EP_INIT(cdc_ecm_class->bulkin, ep_desc);
            } else {
                USBH_EP_INIT(cdc_ecm_class->bulkout, ep_desc);
            }
        }

        USB_LOG_INFO("Select cdc ecm altsetting: %d\r\n", altsetting);
        usbh_set_interface(cdc_ecm_class->hport, cdc_ecm_class->data_intf, altsetting);
    } else {
        for (uint8_t i = 0; i < hport->config.intf[intf + 1].altsetting[0].intf_desc.bNumEndpoints; i++) {
            ep_desc = &hport->config.intf[intf + 1].altsetting[0].ep[i].ep_desc;

            if (ep_desc->bEndpointAddress & 0x80) {
                USBH_EP_INIT(cdc_ecm_class->bulkin, ep_desc);
            } else {
                USBH_EP_INIT(cdc_ecm_class->bulkout, ep_desc);
            }
        }
    }

    /* bit0 Promiscuous 
    * bit1 ALL Multicast
    * bit2 Directed
    * bit3 Broadcast
    * bit4 Multicast
    */
    ret = usbh_cdc_ecm_set_eth_packet_filter(cdc_ecm_class, CONFIG_USBHOST_CDC_ECM_PKT_FILTER);
    if (ret < 0) {
        return ret;
    }
    USB_LOG_INFO("Set CDC ECM packet filter:%04x\r\n", CONFIG_USBHOST_CDC_ECM_PKT_FILTER);

    memcpy(hport->config.intf[intf].devname, DEV_FORMAT, CONFIG_USBHOST_DEV_NAMELEN);

    USB_LOG_INFO("Register CDC ECM Class:%s\r\n", hport->config.intf[intf].devname);

    usbh_cdc_ecm_run(cdc_ecm_class);
    return ret;
}

static int usbh_cdc_ecm_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_cdc_ecm *cdc_ecm_class = (struct usbh_cdc_ecm *)hport->config.intf[intf].priv;

    if (cdc_ecm_class) {
        if (cdc_ecm_class->bulkin) {
            usbh_kill_urb(&cdc_ecm_class->bulkin_urb);
        }

        if (cdc_ecm_class->bulkout) {
            usbh_kill_urb(&cdc_ecm_class->bulkout_urb);
        }

        if (cdc_ecm_class->intin) {
            usbh_kill_urb(&cdc_ecm_class->intin_urb);
        }

        if (hport->config.intf[intf].devname[0] != '\0') {
            USB_LOG_INFO("Unregister CDC ECM Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_cdc_ecm_stop(cdc_ecm_class);
        }

        memset(cdc_ecm_class, 0, sizeof(struct usbh_cdc_ecm));
    }

    return ret;
}

void usbh_cdc_ecm_rx_thread(void *argument)
{
    uint32_t g_cdc_ecm_rx_length;
    int ret;
    err_t err;
    struct pbuf *p;
    struct netif *netif = (struct netif *)argument;

    USB_LOG_INFO("Create cdc ecm rx thread\r\n");
    // clang-format off
find_class:
    // clang-format on
    g_cdc_ecm_class.connect_status = false;
    if (usbh_find_class_instance("/dev/cdc_ether") == NULL) {
        goto delete;
    }

    while (g_cdc_ecm_class.connect_status == false) {
        ret = usbh_cdc_ecm_get_connect_status(&g_cdc_ecm_class);
        if (ret < 0) {
            usb_osal_msleep(100);
            goto find_class;
        }
    }

    g_cdc_ecm_rx_length = 0;
    while (1) {
        usbh_bulk_urb_fill(&g_cdc_ecm_class.bulkin_urb, g_cdc_ecm_class.hport, g_cdc_ecm_class.bulkin, &g_cdc_ecm_rx_buffer[g_cdc_ecm_rx_length], USB_GET_MAXPACKETSIZE(g_cdc_ecm_class.bulkin->wMaxPacketSize), USB_OSAL_WAITING_FOREVER, NULL, NULL);
        ret = usbh_submit_urb(&g_cdc_ecm_class.bulkin_urb);
        if (ret < 0) {
            goto find_class;
        }

        g_cdc_ecm_rx_length += g_cdc_ecm_class.bulkin_urb.actual_length;

        if (g_cdc_ecm_class.bulkin_urb.actual_length != USB_GET_MAXPACKETSIZE(g_cdc_ecm_class.bulkin->wMaxPacketSize)) {
            USB_LOG_DBG("rxlen:%d\r\n", g_cdc_ecm_rx_length);

            p = pbuf_alloc(PBUF_RAW, g_cdc_ecm_rx_length, PBUF_POOL);
            if (p != NULL) {
                memcpy(p->payload, (uint8_t *)g_cdc_ecm_rx_buffer, g_cdc_ecm_rx_length);
                g_cdc_ecm_rx_length = 0;

                err = netif->input(p, netif);
                if (err != ERR_OK) {
                    pbuf_free(p);
                }
            } else {
                g_cdc_ecm_rx_length = 0;
                USB_LOG_ERR("No memory to alloc pbuf for cdc ecm rx\r\n");
            }
        } else {
            /* read continue util read short packet */
        }
    }
    // clang-format off
delete:
    USB_LOG_INFO("Delete cdc ecm rx thread\r\n");
    usb_osal_thread_delete(NULL);
    // clang-format on
}

err_t usbh_cdc_ecm_linkoutput(struct netif *netif, struct pbuf *p)
{
    int ret;
    struct pbuf *q;
    uint8_t *buffer = g_cdc_ecm_tx_buffer;

    if (g_cdc_ecm_class.connect_status == false) {
        return ERR_BUF;
    }

    for (q = p; q != NULL; q = q->next) {
        memcpy(buffer, q->payload, q->len);
        buffer += q->len;
    }

    USB_LOG_DBG("txlen:%d\r\n", p->tot_len);

    usbh_bulk_urb_fill(&g_cdc_ecm_class.bulkout_urb, g_cdc_ecm_class.hport, g_cdc_ecm_class.bulkout, g_cdc_ecm_tx_buffer, p->tot_len, USB_OSAL_WAITING_FOREVER, NULL, NULL);
    ret = usbh_submit_urb(&g_cdc_ecm_class.bulkout_urb);
    if (ret < 0) {
        return ERR_BUF;
    }

    return ERR_OK;
}

__WEAK void usbh_cdc_ecm_run(struct usbh_cdc_ecm *cdc_ecm_class)
{
}

__WEAK void usbh_cdc_ecm_stop(struct usbh_cdc_ecm *cdc_ecm_class)
{
}

const struct usbh_class_driver cdc_ecm_class_driver = {
    .driver_name = "cdc_ecm",
    .connect = usbh_cdc_ecm_connect,
    .disconnect = usbh_cdc_ecm_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info cdc_ecm_class_info = {
    .match_flags = USB_CLASS_MATCH_INTF_CLASS | USB_CLASS_MATCH_INTF_SUBCLASS | USB_CLASS_MATCH_INTF_PROTOCOL,
    .class = USB_DEVICE_CLASS_CDC,
    .subclass = CDC_ETHERNET_NETWORKING_CONTROL_MODEL,
    .protocol = CDC_COMMON_PROTOCOL_NONE,
    .vid = 0x00,
    .pid = 0x00,
    .class_driver = &cdc_ecm_class_driver
};