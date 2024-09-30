/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_rndis.h"
#include "rndis_protocol.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_rndis"
#include "usb_log.h"

#define DEV_FORMAT "/dev/rndis"

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_rndis_buf[4096];

#define CONFIG_USBHOST_RNDIS_ETH_MAX_FRAME_SIZE 1514
#define CONFIG_USBHOST_RNDIS_ETH_MSG_SIZE       (CONFIG_USBHOST_RNDIS_ETH_MAX_FRAME_SIZE + 44)

static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_rndis_rx_buffer[CONFIG_USBHOST_RNDIS_ETH_MAX_RX_SIZE];
static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_rndis_tx_buffer[CONFIG_USBHOST_RNDIS_ETH_MAX_TX_SIZE];
// static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_rndis_inttx_buffer[16];

static struct usbh_rndis g_rndis_class;

static int usbh_rndis_get_notification(struct usbh_rndis *rndis_class)
{
    (void)rndis_class;
    // int ret;
    // struct usbh_urb *urb = &rndis_class->intin_urb;

    // usbh_int_urb_fill(urb, rndis_class->hport, rndis_class->intin, g_rndis_inttx_buffer, rndis_class->intin->wMaxPacketSize, USB_OSAL_WAITING_FOREVER, NULL, NULL);
    // ret = usbh_submit_urb(urb);
    // if (ret == 0) {
    //     ret = urb->actual_length;
    // }
    // return ret;
    return 0;
}

static int usbh_rndis_init_msg_transfer(struct usbh_rndis *rndis_class)
{
    struct usb_setup_packet *setup;
    int ret = 0;
    rndis_initialize_msg_t *cmd;
    rndis_initialize_cmplt_t *resp;

    if (!rndis_class || !rndis_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = rndis_class->hport->setup;

    cmd = (rndis_initialize_msg_t *)g_rndis_buf;

    cmd->MessageType = REMOTE_NDIS_INITIALIZE_MSG;
    cmd->MessageLength = sizeof(rndis_initialize_msg_t);
    cmd->RequestId = rndis_class->request_id++;
    cmd->MajorVersion = 1;
    cmd->MinorVersion = 0;
    cmd->MaxTransferSize = 0x4000;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_SEND_ENCAPSULATED_COMMAND;
    setup->wValue = 0;
    setup->wIndex = 0;
    setup->wLength = sizeof(rndis_initialize_msg_t);

    ret = usbh_control_transfer(rndis_class->hport, setup, (uint8_t *)cmd);
    if (ret < 0) {
        USB_LOG_ERR("rndis_initialize_msg_t send error, ret: %d\r\n", ret);
        return ret;
    }

    usbh_rndis_get_notification(rndis_class);

    resp = (rndis_initialize_cmplt_t *)g_rndis_buf;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_GET_ENCAPSULATED_RESPONSE;
    setup->wValue = 0;
    setup->wIndex = 0;
    setup->wLength = 4096;

    ret = usbh_control_transfer(rndis_class->hport, setup, (uint8_t *)resp);
    if (ret < 0) {
        USB_LOG_ERR("rndis_initialize_cmplt_t recv error, ret: %d\r\n", ret);
        return ret;
    }

    rndis_class->max_transfer_pkts = resp->MaxPacketsPerTransfer;
    rndis_class->max_transfer_size = resp->MaxTransferSize;
    USB_LOG_INFO("MaxPacketsPerTransfer:%d\r\n", resp->MaxPacketsPerTransfer);
    USB_LOG_INFO("MaxTransferSize:%d\r\n", resp->MaxTransferSize);

    return ret;
}

int usbh_rndis_query_msg_transfer(struct usbh_rndis *rndis_class, uint32_t oid, uint32_t query_len, uint8_t *info, uint32_t *info_len)
{
    struct usb_setup_packet *setup;
    int ret = 0;
    rndis_query_msg_t *cmd;
    rndis_query_cmplt_t *resp;

    if (!rndis_class || !rndis_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = rndis_class->hport->setup;

    cmd = (rndis_query_msg_t *)g_rndis_buf;

    cmd->MessageType = REMOTE_NDIS_QUERY_MSG;
    cmd->MessageLength = query_len + sizeof(rndis_query_msg_t);
    cmd->RequestId = rndis_class->request_id++;
    cmd->Oid = oid;
    cmd->InformationBufferLength = query_len;
    cmd->InformationBufferOffset = 20;
    cmd->DeviceVcHandle = 0;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_SEND_ENCAPSULATED_COMMAND;
    setup->wValue = 0;
    setup->wIndex = 0;
    setup->wLength = query_len + sizeof(rndis_query_msg_t);

    ret = usbh_control_transfer(rndis_class->hport, setup, (uint8_t *)cmd);
    if (ret < 0) {
        USB_LOG_ERR("oid:%08x send error, ret: %d\r\n", (unsigned int)oid, ret);
        return ret;
    }

    usbh_rndis_get_notification(rndis_class);

    resp = (rndis_query_cmplt_t *)g_rndis_buf;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_GET_ENCAPSULATED_RESPONSE;
    setup->wValue = 0;
    setup->wIndex = 0;
    setup->wLength = 4096;

    ret = usbh_control_transfer(rndis_class->hport, setup, (uint8_t *)resp);
    if (ret < 0) {
        USB_LOG_ERR("oid:%08x recv error, ret: %d\r\n", (unsigned int)oid, ret);
        return ret;
    }

    memcpy(info, ((uint8_t *)resp + sizeof(rndis_query_cmplt_t)), resp->InformationBufferLength);
    *info_len = resp->InformationBufferLength;

    return ret;
}

static int usbh_rndis_set_msg_transfer(struct usbh_rndis *rndis_class, uint32_t oid, uint8_t *info, uint32_t info_len)
{
    struct usb_setup_packet *setup;
    int ret = 0;
    rndis_set_msg_t *cmd;
    rndis_set_cmplt_t *resp;

    if (!rndis_class || !rndis_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = rndis_class->hport->setup;

    cmd = (rndis_set_msg_t *)g_rndis_buf;

    cmd->MessageType = REMOTE_NDIS_SET_MSG;
    cmd->MessageLength = info_len + sizeof(rndis_set_msg_t);
    cmd->RequestId = rndis_class->request_id++;
    cmd->Oid = oid;
    cmd->InformationBufferLength = info_len;
    cmd->InformationBufferOffset = 20;
    cmd->DeviceVcHandle = 0;

    memcpy(((uint8_t *)cmd + sizeof(rndis_set_msg_t)), info, info_len);
    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_SEND_ENCAPSULATED_COMMAND;
    setup->wValue = 0;
    setup->wIndex = 0;
    setup->wLength = info_len + sizeof(rndis_set_msg_t);

    ret = usbh_control_transfer(rndis_class->hport, setup, (uint8_t *)cmd);
    if (ret < 0) {
        USB_LOG_ERR("oid:%08x send error, ret: %d\r\n", (unsigned int)oid, ret);
        return ret;
    }

    usbh_rndis_get_notification(rndis_class);

    resp = (rndis_set_cmplt_t *)g_rndis_buf;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_GET_ENCAPSULATED_RESPONSE;
    setup->wValue = 0;
    setup->wIndex = 0;
    setup->wLength = 4096;

    ret = usbh_control_transfer(rndis_class->hport, setup, (uint8_t *)resp);
    if (ret < 0) {
        USB_LOG_ERR("oid:%08x recv error, ret: %d\r\n", (unsigned int)oid, ret);
        return ret;
    }

    return ret;
}

int usbh_rndis_get_connect_status(struct usbh_rndis *rndis_class)
{
    int ret;
    uint8_t data[32];
    uint32_t data_len;

    ret = usbh_rndis_query_msg_transfer(rndis_class, OID_GEN_MEDIA_CONNECT_STATUS, 4, data, &data_len);
    if (ret < 0) {
        return ret;
    }
    if (NDIS_MEDIA_STATE_CONNECTED == data[0]) {
        rndis_class->connect_status = true;
    } else {
        rndis_class->connect_status = false;
    }
    return 0;
}

int usbh_rndis_keepalive(struct usbh_rndis *rndis_class)
{
    struct usb_setup_packet *setup;
    int ret = 0;
    rndis_keepalive_msg_t *cmd;
    rndis_keepalive_cmplt_t *resp;

    if (!rndis_class || !rndis_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = rndis_class->hport->setup;

    cmd = (rndis_keepalive_msg_t *)g_rndis_buf;

    cmd->MessageType = REMOTE_NDIS_KEEPALIVE_MSG;
    cmd->MessageLength = sizeof(rndis_keepalive_msg_t);
    cmd->RequestId = rndis_class->request_id++;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_SEND_ENCAPSULATED_COMMAND;
    setup->wValue = 0;
    setup->wIndex = 0;
    setup->wLength = sizeof(rndis_keepalive_msg_t);

    ret = usbh_control_transfer(rndis_class->hport, setup, (uint8_t *)cmd);
    if (ret < 0) {
        USB_LOG_ERR("keepalive send error, ret: %d\r\n", ret);
        return ret;
    }

    usbh_rndis_get_notification(rndis_class);

    resp = (rndis_keepalive_cmplt_t *)g_rndis_buf;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_GET_ENCAPSULATED_RESPONSE;
    setup->wValue = 0;
    setup->wIndex = 0;
    setup->wLength = 4096;

    ret = usbh_control_transfer(rndis_class->hport, setup, (uint8_t *)resp);
    if (ret < 0) {
        USB_LOG_ERR("keepalive recv error, ret: %d\r\n", ret);
        return ret;
    }

    return ret;
}

static int usbh_rndis_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    int ret;
    uint32_t *oid_support_list;
    unsigned int oid = 0;
    unsigned int oid_num = 0;
    uint32_t data_len;
    uint8_t tmp_buffer[512];
    uint8_t data[32];

    struct usbh_rndis *rndis_class = &g_rndis_class;

    memset(rndis_class, 0, sizeof(struct usbh_rndis));

    rndis_class->hport = hport;
    rndis_class->ctrl_intf = intf;
    rndis_class->data_intf = intf + 1;

    hport->config.intf[intf].priv = rndis_class;
    hport->config.intf[intf + 1].priv = NULL;

    // ep_desc = &hport->config.intf[intf].altsetting[0].ep[0].ep_desc;
    // USBH_EP_INIT(rndis_class->intin, ep_desc);

    for (uint8_t i = 0; i < hport->config.intf[intf + 1].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &hport->config.intf[intf + 1].altsetting[0].ep[i].ep_desc;

        if (ep_desc->bEndpointAddress & 0x80) {
            USBH_EP_INIT(rndis_class->bulkin, ep_desc);
        } else {
            USBH_EP_INIT(rndis_class->bulkout, ep_desc);
        }
    }

    ret = usbh_rndis_init_msg_transfer(rndis_class);
    if (ret < 0) {
        return ret;
    }
    USB_LOG_INFO("rndis init success\r\n");

    ret = usbh_rndis_query_msg_transfer(rndis_class, OID_GEN_SUPPORTED_LIST, 0, tmp_buffer, &data_len);
    if (ret < 0) {
        return ret;
    }
    oid_num = (data_len / 4);
    USB_LOG_INFO("rndis query OID_GEN_SUPPORTED_LIST success,oid num :%d\r\n", oid_num);

    oid_support_list = (uint32_t *)tmp_buffer;

    for (uint8_t i = 0; i < oid_num; i++) {
        oid = oid_support_list[i];
        switch (oid) {
            case OID_GEN_PHYSICAL_MEDIUM:
                ret = usbh_rndis_query_msg_transfer(rndis_class, OID_GEN_PHYSICAL_MEDIUM, 4, data, &data_len);
                if (ret < 0) {
                    goto query_errorout;
                }
                break;
            case OID_GEN_MAXIMUM_FRAME_SIZE:
                ret = usbh_rndis_query_msg_transfer(rndis_class, OID_GEN_MAXIMUM_FRAME_SIZE, 4, data, &data_len);
                if (ret < 0) {
                    goto query_errorout;
                }
                break;
            case OID_GEN_LINK_SPEED:
                ret = usbh_rndis_query_msg_transfer(rndis_class, OID_GEN_LINK_SPEED, 4, data, &data_len);
                if (ret < 0) {
                    goto query_errorout;
                }

                memcpy(&rndis_class->link_speed, data, 4);
                break;
            case OID_GEN_MEDIA_CONNECT_STATUS:
                ret = usbh_rndis_query_msg_transfer(rndis_class, OID_GEN_MEDIA_CONNECT_STATUS, 4, data, &data_len);
                if (ret < 0) {
                    goto query_errorout;
                }
                if (NDIS_MEDIA_STATE_CONNECTED == data[0]) {
                    rndis_class->connect_status = true;
                } else {
                    rndis_class->connect_status = false;
                }
                break;
            case OID_802_3_MAXIMUM_LIST_SIZE:
                ret = usbh_rndis_query_msg_transfer(rndis_class, OID_802_3_MAXIMUM_LIST_SIZE, 4, data, &data_len);
                if (ret < 0) {
                    goto query_errorout;
                }
                break;
            case OID_802_3_CURRENT_ADDRESS:
                ret = usbh_rndis_query_msg_transfer(rndis_class, OID_802_3_CURRENT_ADDRESS, 6, data, &data_len);
                if (ret < 0) {
                    goto query_errorout;
                }

                for (uint8_t j = 0; j < 6; j++) {
                    rndis_class->mac[j] = data[j];
                }
                break;
            case OID_802_3_PERMANENT_ADDRESS:
                ret = usbh_rndis_query_msg_transfer(rndis_class, OID_802_3_PERMANENT_ADDRESS, 6, data, &data_len);
                if (ret < 0) {
                    goto query_errorout;
                }
                break;
            default:
                USB_LOG_WRN("Ignore rndis query iod:%08x\r\n", oid);
                continue;
        }
        USB_LOG_INFO("rndis query iod:%08x success\r\n", oid);
    }

    uint32_t packet_filter = 0x0f;
    usbh_rndis_set_msg_transfer(rndis_class, OID_GEN_CURRENT_PACKET_FILTER, (uint8_t *)&packet_filter, 4);
    if (ret < 0) {
        return ret;
    }
    USB_LOG_INFO("rndis set OID_GEN_CURRENT_PACKET_FILTER success\r\n");

    uint8_t multicast_list[6] = { 0x01, 0x00, 0x5E, 0x00, 0x00, 0x01 };
    usbh_rndis_set_msg_transfer(rndis_class, OID_802_3_MULTICAST_LIST, multicast_list, 6);
    if (ret < 0) {
        return ret;
    }
    USB_LOG_INFO("rndis set OID_802_3_MULTICAST_LIST success\r\n");

    USB_LOG_INFO("rndis MAC address %02x:%02x:%02x:%02x:%02x:%02x\r\n",
                 rndis_class->mac[0],
                 rndis_class->mac[1],
                 rndis_class->mac[2],
                 rndis_class->mac[3],
                 rndis_class->mac[4],
                 rndis_class->mac[5]);

    strncpy(hport->config.intf[intf].devname, DEV_FORMAT, CONFIG_USBHOST_DEV_NAMELEN);

    USB_LOG_INFO("Register RNDIS Class:%s\r\n", hport->config.intf[intf].devname);
    usbh_rndis_run(rndis_class);
    return ret;
query_errorout:
    USB_LOG_ERR("rndis query iod:%08x error\r\n", oid);
    return ret;
}

static int usbh_rndis_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_rndis *rndis_class = (struct usbh_rndis *)hport->config.intf[intf].priv;

    if (rndis_class) {
        if (rndis_class->bulkin) {
            usbh_kill_urb(&rndis_class->bulkin_urb);
        }

        if (rndis_class->bulkout) {
            usbh_kill_urb(&rndis_class->bulkout_urb);
        }

        // if (rndis_class->intin) {
        //     usbh_kill_urb(&rndis_class->intin_urb);
        // }

        if (hport->config.intf[intf].devname[0] != '\0') {
            USB_LOG_INFO("Unregister RNDIS Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_rndis_stop(rndis_class);
        }

        memset(rndis_class, 0, sizeof(struct usbh_rndis));
    }

    return ret;
}

void usbh_rndis_rx_thread(void *argument)
{
    uint32_t g_rndis_rx_length;
    int ret;
    uint32_t pmg_offset;
    rndis_data_packet_t *pmsg;
    rndis_data_packet_t temp;
#if CONFIG_USBHOST_RNDIS_ETH_MAX_RX_SIZE <= (16 * 1024)
    uint32_t transfer_size = CONFIG_USBHOST_RNDIS_ETH_MAX_RX_SIZE;
#else
    uint32_t transfer_size = (16 * 1024);
#endif

    (void)argument;

    USB_LOG_INFO("Create rndis rx thread\r\n");
    // clang-format off
find_class:
    // clang-format on
    g_rndis_class.connect_status = false;
    if (usbh_find_class_instance("/dev/rndis") == NULL) {
        goto delete;
    }

    while (g_rndis_class.connect_status == false) {
        ret = usbh_rndis_get_connect_status(&g_rndis_class);
        if (ret < 0) {
            usb_osal_msleep(100);
            goto find_class;
        }
        usb_osal_msleep(128);
    }

    g_rndis_rx_length = 0;
    while (1) {
        usbh_bulk_urb_fill(&g_rndis_class.bulkin_urb, g_rndis_class.hport, g_rndis_class.bulkin, &g_rndis_rx_buffer[g_rndis_rx_length], transfer_size, USB_OSAL_WAITING_FOREVER, NULL, NULL);
        ret = usbh_submit_urb(&g_rndis_class.bulkin_urb);
        if (ret < 0) {
            goto find_class;
        }

        g_rndis_rx_length += g_rndis_class.bulkin_urb.actual_length;

        /* A transfer is complete because last packet is a short packet.
         * Short packet is not zero, match g_rndis_rx_length % USB_GET_MAXPACKETSIZE(g_rndis_class.bulkin->wMaxPacketSize).
         * Short packet cannot be zero.
        */
        if (g_rndis_rx_length % USB_GET_MAXPACKETSIZE(g_rndis_class.bulkin->wMaxPacketSize)) {
            pmg_offset = 0;

            uint32_t total_len = g_rndis_rx_length;

            while (g_rndis_rx_length > 0) {
                USB_LOG_DBG("rxlen:%d\r\n", g_rndis_rx_length);

                pmsg = (rndis_data_packet_t *)(g_rndis_rx_buffer + pmg_offset);

                /* Not word-aligned case */
                if (pmg_offset & 0x3) {
                    usb_memcpy(&temp, pmsg, sizeof(rndis_data_packet_t));
                    pmsg = &temp;
                }

                if (pmsg->MessageType == REMOTE_NDIS_PACKET_MSG) {
                    uint8_t *buf = (uint8_t *)(g_rndis_rx_buffer + pmg_offset + sizeof(rndis_generic_msg_t) + pmsg->DataOffset);

                    usbh_rndis_eth_input(buf, pmsg->DataLength);
                    pmg_offset += pmsg->MessageLength;
                    g_rndis_rx_length -= pmsg->MessageLength;

                    /* drop the last dummy byte, it is a short packet to tell us we have received a multiple of wMaxPacketSize */
                    if (g_rndis_rx_length < 4) {
                        g_rndis_rx_length = 0;
                    }
                } else {
                    USB_LOG_ERR("offset:%d,remain:%d,total:%d\r\n", pmg_offset, g_rndis_rx_length, total_len);
                    g_rndis_rx_length = 0;
                    USB_LOG_ERR("Error rndis packet message\r\n");
                }
            }
        } else {
#if CONFIG_USBHOST_RNDIS_ETH_MAX_RX_SIZE <= (16 * 1024)
            if (g_rndis_rx_length == CONFIG_USBHOST_RNDIS_ETH_MAX_RX_SIZE) {
#else
            if ((g_rndis_rx_length + (16 * 1024)) > CONFIG_USBHOST_RNDIS_ETH_MAX_RX_SIZE) {
#endif
                USB_LOG_ERR("Rx packet is overflow, please reduce tcp window size or increase CONFIG_USBHOST_RNDIS_ETH_MAX_RX_SIZE\r\n");
                while (1) {
                }
            }
        }
    }

    // clang-format off
delete:
    USB_LOG_INFO("Delete rndis rx thread\r\n");
    usb_osal_thread_delete(NULL);
    // clang-format on
}

uint8_t *usbh_rndis_get_eth_txbuf(void)
{
    return (g_rndis_tx_buffer + sizeof(rndis_data_packet_t));
}

int usbh_rndis_eth_output(uint32_t buflen)
{
    rndis_data_packet_t *hdr;
    uint32_t len;

    if (g_rndis_class.connect_status == false) {
        return -USB_ERR_NOTCONN;
    }

    hdr = (rndis_data_packet_t *)g_rndis_tx_buffer;
    memset(hdr, 0, sizeof(rndis_data_packet_t));

    hdr->MessageType = REMOTE_NDIS_PACKET_MSG;
    hdr->MessageLength = sizeof(rndis_data_packet_t) + buflen;
    hdr->DataOffset = sizeof(rndis_data_packet_t) - sizeof(rndis_generic_msg_t);
    hdr->DataLength = buflen;

    len = hdr->MessageLength;
    /* if message length is the multiple of wMaxPacketSize, we should add a short packet to tell device transfer is over. */
    if (!(len % g_rndis_class.bulkout->wMaxPacketSize)) {
        len += 1;
    }

    USB_LOG_DBG("txlen:%d\r\n", len);

    usbh_bulk_urb_fill(&g_rndis_class.bulkout_urb, g_rndis_class.hport, g_rndis_class.bulkout, g_rndis_tx_buffer, len, USB_OSAL_WAITING_FOREVER, NULL, NULL);
    return usbh_submit_urb(&g_rndis_class.bulkout_urb);
}

__WEAK void usbh_rndis_run(struct usbh_rndis *rndis_class)
{
    (void)rndis_class;
}

__WEAK void usbh_rndis_stop(struct usbh_rndis *rndis_class)
{
    (void)rndis_class;
}

static const struct usbh_class_driver rndis_class_driver = {
    .driver_name = "rndis",
    .connect = usbh_rndis_connect,
    .disconnect = usbh_rndis_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info rndis_class_info = {
    .match_flags = USB_CLASS_MATCH_INTF_CLASS | USB_CLASS_MATCH_INTF_SUBCLASS | USB_CLASS_MATCH_INTF_PROTOCOL,
    .class = USB_DEVICE_CLASS_WIRELESS,
    .subclass = 0x01,
    .protocol = 0x03,
    .id_table = NULL,
    .class_driver = &rndis_class_driver
};
