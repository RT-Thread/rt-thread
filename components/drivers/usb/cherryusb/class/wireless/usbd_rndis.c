/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_rndis.h"
#include "rndis_protocol.h"

#define RNDIS_OUT_EP_IDX 0
#define RNDIS_IN_EP_IDX  1
#define RNDIS_INT_EP_IDX 2

/* Describe EndPoints configuration */
static struct usbd_endpoint rndis_ep_data[3];

#define RNDIS_INQUIRY_PUT(src, len)   (memcpy(infomation_buffer, src, len))
#define RNDIS_INQUIRY_PUT_LE32(value) (*(uint32_t *)infomation_buffer = (value))

/* Device data structure */
struct usbd_rndis_priv {
    uint32_t drv_version;
    uint32_t link_status;
    uint32_t net_filter;
    usb_eth_stat_t eth_state;
    rndis_state_t init_state;
    uint8_t mac[6];
} g_usbd_rndis;

#if CONFIG_USBDEV_RNDIS_RESP_BUFFER_SIZE < 140
#undef CONFIG_USBDEV_RNDIS_RESP_BUFFER_SIZE
#define CONFIG_USBDEV_RNDIS_RESP_BUFFER_SIZE 156
#endif

#if CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE < 1580
#undef CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE
#define CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE 1580
#endif

static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_rndis_rx_buffer[CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE];
static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_rndis_tx_buffer[CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE];

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t rndis_encapsulated_resp_buffer[CONFIG_USBDEV_RNDIS_RESP_BUFFER_SIZE];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t NOTIFY_RESPONSE_AVAILABLE[8];

volatile uint8_t *g_rndis_rx_data_buffer;
volatile uint32_t g_rndis_rx_data_length;
volatile uint32_t g_rndis_tx_data_length;

/* RNDIS options list */
const uint32_t oid_supported_list[] = {
    /* General OIDs */
    OID_GEN_SUPPORTED_LIST,
    OID_GEN_HARDWARE_STATUS,
    OID_GEN_MEDIA_SUPPORTED,
    OID_GEN_MEDIA_IN_USE,
    OID_GEN_MAXIMUM_FRAME_SIZE,
    OID_GEN_LINK_SPEED,
    OID_GEN_TRANSMIT_BLOCK_SIZE,
    OID_GEN_RECEIVE_BLOCK_SIZE,
    OID_GEN_VENDOR_ID,
    OID_GEN_VENDOR_DESCRIPTION,
    OID_GEN_VENDOR_DRIVER_VERSION,
    OID_GEN_CURRENT_PACKET_FILTER,
    OID_GEN_MAXIMUM_TOTAL_SIZE,
    OID_GEN_MEDIA_CONNECT_STATUS,

    OID_GEN_PHYSICAL_MEDIUM,

    /* General Statistic OIDs */
    OID_GEN_XMIT_OK,
    OID_GEN_RCV_OK,
    OID_GEN_XMIT_ERROR,
    OID_GEN_RCV_ERROR,
    OID_GEN_RCV_NO_BUFFER,

    /* Please configure us */
    OID_GEN_RNDIS_CONFIG_PARAMETER,

    /* 802.3 OIDs */
    OID_802_3_PERMANENT_ADDRESS,
    OID_802_3_CURRENT_ADDRESS,
    OID_802_3_MULTICAST_LIST,
    OID_802_3_MAXIMUM_LIST_SIZE,

    /* 802.3 Statistic OIDs */
    OID_802_3_RCV_ERROR_ALIGNMENT,
    OID_802_3_XMIT_ONE_COLLISION,
    OID_802_3_XMIT_MORE_COLLISIONS,

    OID_802_3_MAC_OPTIONS,
};

static int rndis_encapsulated_cmd_handler(uint8_t *data, uint32_t len);

static void rndis_notify_rsp(void)
{
    memset(NOTIFY_RESPONSE_AVAILABLE, 0, 8);
    NOTIFY_RESPONSE_AVAILABLE[0] = 0x01;
    usbd_ep_start_write(0, rndis_ep_data[RNDIS_INT_EP_IDX].ep_addr, NOTIFY_RESPONSE_AVAILABLE, 8);
}

static int rndis_class_interface_request_handler(uint8_t busid, struct usb_setup_packet *setup, uint8_t **data, uint32_t *len)
{
    (void)busid;

    switch (setup->bRequest) {
        case CDC_REQUEST_SEND_ENCAPSULATED_COMMAND:
            rndis_encapsulated_cmd_handler(*data, setup->wLength);
            break;
        case CDC_REQUEST_GET_ENCAPSULATED_RESPONSE:
            *data = rndis_encapsulated_resp_buffer;
            *len = ((rndis_generic_msg_t *)rndis_encapsulated_resp_buffer)->MessageLength;
            break;

        default:
            return -1;
    }

    return 0;
}

static int rndis_init_cmd_handler(uint8_t *data, uint32_t len);
static int rndis_halt_cmd_handler(uint8_t *data, uint32_t len);
static int rndis_query_cmd_handler(uint8_t *data, uint32_t len);
static int rndis_set_cmd_handler(uint8_t *data, uint32_t len);
static int rndis_reset_cmd_handler(uint8_t *data, uint32_t len);
static int rndis_keepalive_cmd_handler(uint8_t *data, uint32_t len);

static int rndis_encapsulated_cmd_handler(uint8_t *data, uint32_t len)
{
    switch (((rndis_generic_msg_t *)data)->MessageType) {
        case REMOTE_NDIS_INITIALIZE_MSG:
            return rndis_init_cmd_handler(data, len);
        case REMOTE_NDIS_HALT_MSG:
            return rndis_halt_cmd_handler(data, len);
        case REMOTE_NDIS_QUERY_MSG:
            return rndis_query_cmd_handler(data, len);
        case REMOTE_NDIS_SET_MSG:
            return rndis_set_cmd_handler(data, len);
        case REMOTE_NDIS_RESET_MSG:
            return rndis_reset_cmd_handler(data, len);
        case REMOTE_NDIS_KEEPALIVE_MSG:
            return rndis_keepalive_cmd_handler(data, len);

        default:
            break;
    }
    return -1;
}

static int rndis_init_cmd_handler(uint8_t *data, uint32_t len)
{
    rndis_initialize_msg_t *cmd = (rndis_initialize_msg_t *)data;
    rndis_initialize_cmplt_t *resp;

    (void)len;

    resp = ((rndis_initialize_cmplt_t *)rndis_encapsulated_resp_buffer);
    resp->RequestId = cmd->RequestId;
    resp->MessageType = REMOTE_NDIS_INITIALIZE_CMPLT;
    resp->MessageLength = sizeof(rndis_initialize_cmplt_t);
    resp->MajorVersion = RNDIS_MAJOR_VERSION;
    resp->MinorVersion = RNDIS_MINOR_VERSION;
    resp->Status = RNDIS_STATUS_SUCCESS;
    resp->DeviceFlags = RNDIS_DF_CONNECTIONLESS;
    resp->Medium = RNDIS_MEDIUM_802_3;
    resp->MaxPacketsPerTransfer = CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE / 1580;
    resp->MaxTransferSize = CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE;
    resp->PacketAlignmentFactor = 0;
    resp->AfListOffset = 0;
    resp->AfListSize = 0;

    g_usbd_rndis.init_state = rndis_initialized;

    rndis_notify_rsp();
    return 0;
}

static int rndis_halt_cmd_handler(uint8_t *data, uint32_t len)
{
    rndis_halt_msg_t *resp;

    (void)data;
    (void)len;

    resp = ((rndis_halt_msg_t *)rndis_encapsulated_resp_buffer);
    resp->MessageLength = 0;

    g_usbd_rndis.init_state = rndis_uninitialized;

    return 0;
}

static int rndis_query_cmd_handler(uint8_t *data, uint32_t len)
{
    rndis_query_msg_t *cmd = (rndis_query_msg_t *)data;
    rndis_query_cmplt_t *resp;
    uint8_t *infomation_buffer;
    uint32_t infomation_len = 0;

    (void)len;

    resp = ((rndis_query_cmplt_t *)rndis_encapsulated_resp_buffer);
    resp->MessageType = REMOTE_NDIS_QUERY_CMPLT;
    resp->RequestId = cmd->RequestId;
    resp->InformationBufferOffset = sizeof(rndis_query_cmplt_t) - sizeof(rndis_generic_msg_t);
    resp->Status = RNDIS_STATUS_SUCCESS;

    infomation_buffer = (uint8_t *)resp + sizeof(rndis_query_cmplt_t);

    switch (cmd->Oid) {
        case OID_GEN_SUPPORTED_LIST:
            RNDIS_INQUIRY_PUT(oid_supported_list, sizeof(oid_supported_list));
            infomation_len = sizeof(oid_supported_list);
            break;
        case OID_GEN_HARDWARE_STATUS:
            RNDIS_INQUIRY_PUT_LE32(NDIS_HW_STS_READY);
            infomation_len = 4;
            break;
        case OID_GEN_MEDIA_SUPPORTED:
        case OID_GEN_MEDIA_IN_USE:
            RNDIS_INQUIRY_PUT_LE32(NDIS_MEDIUM_802_3);
            infomation_len = 4;
            break;
        case OID_GEN_MAXIMUM_FRAME_SIZE:
        case OID_GEN_TRANSMIT_BLOCK_SIZE:
        case OID_GEN_RECEIVE_BLOCK_SIZE:
            RNDIS_INQUIRY_PUT_LE32(0x05DC); /* mtu 1500 */
            infomation_len = 4;
            break;
        case OID_GEN_VENDOR_ID:
            RNDIS_INQUIRY_PUT_LE32(CONFIG_USBDEV_RNDIS_VENDOR_ID);
            infomation_len = 4;
            break;
        case OID_GEN_VENDOR_DRIVER_VERSION:
            RNDIS_INQUIRY_PUT_LE32(0x0001);
            infomation_len = 4;
            break;
        case OID_GEN_VENDOR_DESCRIPTION:
            RNDIS_INQUIRY_PUT(CONFIG_USBDEV_RNDIS_VENDOR_DESC, strlen(CONFIG_USBDEV_RNDIS_VENDOR_DESC));
            infomation_len = (strlen(CONFIG_USBDEV_RNDIS_VENDOR_DESC) + 1);
            break;
        case OID_802_3_CURRENT_ADDRESS:
        case OID_802_3_PERMANENT_ADDRESS:
            RNDIS_INQUIRY_PUT(g_usbd_rndis.mac, 6);
            infomation_len = 6;
            break;
        case OID_GEN_PHYSICAL_MEDIUM:
            RNDIS_INQUIRY_PUT_LE32(NDIS_MEDIUM_802_3);
            infomation_len = 4;
            break;
        case OID_GEN_LINK_SPEED:
            if (usbd_get_ep_mps(0, rndis_ep_data[RNDIS_OUT_EP_IDX].ep_addr) > 64) {
                RNDIS_INQUIRY_PUT_LE32(480000000 / 100);
            } else {
                RNDIS_INQUIRY_PUT_LE32(12000000 / 100);
            }

            infomation_len = 4;
            break;
        case OID_GEN_CURRENT_PACKET_FILTER:
            RNDIS_INQUIRY_PUT_LE32(g_usbd_rndis.net_filter);
            infomation_len = 4;
            break;
        case OID_GEN_MAXIMUM_TOTAL_SIZE:
            RNDIS_INQUIRY_PUT_LE32(0x0616); /* 1514 + 44 */
            infomation_len = 4;
            break;
        case OID_GEN_MEDIA_CONNECT_STATUS:
            RNDIS_INQUIRY_PUT_LE32(g_usbd_rndis.link_status);
            infomation_len = 4;
            break;
        case OID_GEN_RNDIS_CONFIG_PARAMETER:
            RNDIS_INQUIRY_PUT_LE32(0);
            infomation_len = 4;
            break;
        case OID_802_3_MAXIMUM_LIST_SIZE:
            RNDIS_INQUIRY_PUT_LE32(1); /* one address */
            infomation_len = 4;
            break;
        case OID_802_3_MULTICAST_LIST:
            //RNDIS_INQUIRY_PUT_LE32(0xE0000000); /* 224.0.0.0 */
            resp->Status = RNDIS_STATUS_NOT_SUPPORTED;
            RNDIS_INQUIRY_PUT_LE32(0);
            infomation_len = 4;
            break;
        case OID_802_3_MAC_OPTIONS:
            // infomation_len = 0;
            resp->Status = RNDIS_STATUS_NOT_SUPPORTED;
            RNDIS_INQUIRY_PUT_LE32(0);
            infomation_len = 4;
            break;
        case OID_GEN_MAC_OPTIONS:
            RNDIS_INQUIRY_PUT_LE32(0);
            infomation_len = 4;
            break;
        case OID_802_3_RCV_ERROR_ALIGNMENT:
            RNDIS_INQUIRY_PUT_LE32(0);
            infomation_len = 4;
            break;
        case OID_802_3_XMIT_ONE_COLLISION:
            RNDIS_INQUIRY_PUT_LE32(0);
            infomation_len = 4;
            break;
        case OID_802_3_XMIT_MORE_COLLISIONS:
            RNDIS_INQUIRY_PUT_LE32(0);
            infomation_len = 4;
            break;
        case OID_GEN_XMIT_OK:
            RNDIS_INQUIRY_PUT_LE32(g_usbd_rndis.eth_state.txok);
            infomation_len = 4;
            break;
        case OID_GEN_RCV_OK:
            RNDIS_INQUIRY_PUT_LE32(g_usbd_rndis.eth_state.rxok);
            infomation_len = 4;
            break;
        case OID_GEN_RCV_ERROR:
            RNDIS_INQUIRY_PUT_LE32(g_usbd_rndis.eth_state.rxbad);
            infomation_len = 4;
            break;
        case OID_GEN_XMIT_ERROR:
            RNDIS_INQUIRY_PUT_LE32(g_usbd_rndis.eth_state.txbad);
            infomation_len = 4;
            break;
        case OID_GEN_RCV_NO_BUFFER:
            RNDIS_INQUIRY_PUT_LE32(0);
            infomation_len = 4;
            break;
        default:
            resp->Status = RNDIS_STATUS_FAILURE;
            infomation_len = 0;
            USB_LOG_WRN("Unhandled query for Object ID 0x%x\r\n", cmd->Oid);
            break;
    }

    resp->MessageLength = sizeof(rndis_query_cmplt_t) + infomation_len;
    resp->InformationBufferLength = infomation_len;

    rndis_notify_rsp();
    return 0;
}

static int rndis_set_cmd_handler(uint8_t *data, uint32_t len)
{
    rndis_set_msg_t *cmd = (rndis_set_msg_t *)data;
    rndis_set_cmplt_t *resp;
    rndis_config_parameter_t *param;

    (void)len;

    resp = ((rndis_set_cmplt_t *)rndis_encapsulated_resp_buffer);
    resp->RequestId = cmd->RequestId;
    resp->MessageType = REMOTE_NDIS_SET_CMPLT;
    resp->MessageLength = sizeof(rndis_set_cmplt_t);
    resp->Status = RNDIS_STATUS_SUCCESS;

    switch (cmd->Oid) {
        case OID_GEN_RNDIS_CONFIG_PARAMETER:
            param = (rndis_config_parameter_t *)((uint8_t *)&(cmd->RequestId) + cmd->InformationBufferOffset);
            USB_LOG_WRN("RNDIS cfg param: NameOfs=%d, NameLen=%d, ValueOfs=%d, ValueLen=%d\r\n",
                        param->ParameterNameOffset, param->ParameterNameLength,
                        param->ParameterValueOffset, param->ParameterValueLength);
            break;
        case OID_GEN_CURRENT_PACKET_FILTER:
            if (cmd->InformationBufferLength < sizeof(g_usbd_rndis.net_filter)) {
                USB_LOG_WRN("PACKET_FILTER!\r\n");
                resp->Status = RNDIS_STATUS_INVALID_DATA;
            } else {
                uint32_t *filter;
                /* Parameter starts at offset buf_offset of the req_id field */
                filter = (uint32_t *)((uint8_t *)&(cmd->RequestId) + cmd->InformationBufferOffset);

                //g_usbd_rndis.net_filter = param->ParameterNameOffset;
                g_usbd_rndis.net_filter = *(uint32_t *)filter;
                if (g_usbd_rndis.net_filter) {
                    g_usbd_rndis.init_state = rndis_data_initialized;
                } else {
                    g_usbd_rndis.init_state = rndis_initialized;
                }
            }
            break;
        case OID_GEN_CURRENT_LOOKAHEAD:
            break;
        case OID_GEN_PROTOCOL_OPTIONS:
            break;
        case OID_802_3_MULTICAST_LIST:
            break;
        case OID_PNP_ADD_WAKE_UP_PATTERN:
        case OID_PNP_REMOVE_WAKE_UP_PATTERN:
        case OID_PNP_ENABLE_WAKE_UP:
        default:
            resp->Status = RNDIS_STATUS_FAILURE;
            USB_LOG_WRN("Unhandled query for Object ID 0x%x\r\n", cmd->Oid);
            break;
    }

    rndis_notify_rsp();

    return 0;
}

static int rndis_reset_cmd_handler(uint8_t *data, uint32_t len)
{
    // rndis_reset_msg_t *cmd = (rndis_reset_msg_t *)data;
    rndis_reset_cmplt_t *resp;

    (void)data;
    (void)len;

    resp = ((rndis_reset_cmplt_t *)rndis_encapsulated_resp_buffer);
    resp->MessageType = REMOTE_NDIS_RESET_CMPLT;
    resp->MessageLength = sizeof(rndis_reset_cmplt_t);
    resp->Status = RNDIS_STATUS_SUCCESS;
    resp->AddressingReset = 1;

    g_usbd_rndis.init_state = rndis_uninitialized;

    rndis_notify_rsp();

    return 0;
}

static int rndis_keepalive_cmd_handler(uint8_t *data, uint32_t len)
{
    rndis_keepalive_msg_t *cmd = (rndis_keepalive_msg_t *)data;
    rndis_keepalive_cmplt_t *resp;

    (void)len;

    resp = ((rndis_keepalive_cmplt_t *)rndis_encapsulated_resp_buffer);
    resp->RequestId = cmd->RequestId;
    resp->MessageType = REMOTE_NDIS_KEEPALIVE_CMPLT;
    resp->MessageLength = sizeof(rndis_keepalive_cmplt_t);
    resp->Status = RNDIS_STATUS_SUCCESS;

    rndis_notify_rsp();

    return 0;
}

static void rndis_notify_handler(uint8_t busid, uint8_t event, void *arg)
{
    (void)busid;
    (void)arg;

    switch (event) {
        case USBD_EVENT_RESET:
            g_usbd_rndis.link_status = NDIS_MEDIA_STATE_DISCONNECTED;
            break;
        case USBD_EVENT_CONFIGURED:
            g_rndis_rx_data_length = 0;
            g_rndis_tx_data_length = 0;
            g_usbd_rndis.link_status = NDIS_MEDIA_STATE_CONNECTED;
            usbd_ep_start_read(0, rndis_ep_data[RNDIS_OUT_EP_IDX].ep_addr, g_rndis_rx_buffer, sizeof(g_rndis_rx_buffer));
            break;

        default:
            break;
    }
}

void rndis_bulk_out(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    rndis_data_packet_t *hdr;

    (void)busid;
    (void)ep;

    hdr = (rndis_data_packet_t *)g_rndis_rx_buffer;
    g_rndis_rx_data_buffer = g_rndis_rx_buffer;
    if ((hdr->MessageType != REMOTE_NDIS_PACKET_MSG) || (nbytes < hdr->MessageLength)) {
        usbd_ep_start_read(0, rndis_ep_data[RNDIS_OUT_EP_IDX].ep_addr, g_rndis_rx_buffer, sizeof(g_rndis_rx_buffer));
        return;
    }

    /* Point to the payload and update the message length */
    g_rndis_rx_data_buffer += hdr->DataOffset + sizeof(rndis_generic_msg_t);
    g_rndis_rx_data_length = hdr->DataLength;

    usbd_rndis_data_recv_done();
}

void rndis_bulk_in(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    (void)busid;

    if ((nbytes % usbd_get_ep_mps(0, ep)) == 0 && nbytes) {
        /* send zlp */
        usbd_ep_start_write(0, ep, NULL, 0);
    } else {
        g_rndis_tx_data_length = 0;
    }
}

void rndis_int_in(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    (void)busid;
    (void)ep;
    (void)nbytes;

    //USB_LOG_DBG("len:%d\r\n", nbytes);
}

#ifdef CONFIG_USBDEV_RNDIS_USING_LWIP
#include <lwip/pbuf.h>

struct pbuf *usbd_rndis_eth_rx(void)
{
    struct pbuf *p;

    if (g_rndis_rx_data_length == 0) {
        return NULL;
    }
    p = pbuf_alloc(PBUF_RAW, g_rndis_rx_data_length, PBUF_POOL);
    if (p == NULL) {
        return NULL;
    }
    usb_memcpy(p->payload, (uint8_t *)g_rndis_rx_data_buffer, g_rndis_rx_data_length);
    p->len = g_rndis_rx_data_length;

    USB_LOG_DBG("rxlen:%d\r\n", g_rndis_rx_data_length);
    g_rndis_rx_data_length = 0;
    usbd_ep_start_read(0, rndis_ep_data[RNDIS_OUT_EP_IDX].ep_addr, g_rndis_rx_buffer, sizeof(g_rndis_rx_buffer));

    return p;
}

int usbd_rndis_eth_tx(struct pbuf *p)
{
    struct pbuf *q;
    uint8_t *buffer;
    rndis_data_packet_t *hdr;

    if (g_usbd_rndis.link_status == NDIS_MEDIA_STATE_DISCONNECTED) {
        return -USB_ERR_NOTCONN;
    }

    if (g_rndis_tx_data_length > 0) {
        return -USB_ERR_BUSY;
    }

    if (p->tot_len > sizeof(g_rndis_tx_buffer)) {
        p->tot_len = sizeof(g_rndis_tx_buffer);
    }

    buffer = (uint8_t *)(g_rndis_tx_buffer + sizeof(rndis_data_packet_t));
    for (q = p; q != NULL; q = q->next) {
        usb_memcpy(buffer, q->payload, q->len);
        buffer += q->len;
    }

    hdr = (rndis_data_packet_t *)g_rndis_tx_buffer;

    memset(hdr, 0, sizeof(rndis_data_packet_t));
    hdr->MessageType = REMOTE_NDIS_PACKET_MSG;
    hdr->MessageLength = sizeof(rndis_data_packet_t) + p->tot_len;
    hdr->DataOffset = sizeof(rndis_data_packet_t) - sizeof(rndis_generic_msg_t);
    hdr->DataLength = p->tot_len;

    g_rndis_tx_data_length = sizeof(rndis_data_packet_t) + p->tot_len;

    USB_LOG_DBG("txlen:%d\r\n", g_rndis_tx_data_length);
    return usbd_ep_start_write(0, rndis_ep_data[RNDIS_IN_EP_IDX].ep_addr, g_rndis_tx_buffer, g_rndis_tx_data_length);
}
#endif
struct usbd_interface *usbd_rndis_init_intf(struct usbd_interface *intf,
                                            const uint8_t out_ep,
                                            const uint8_t in_ep,
                                            const uint8_t int_ep, uint8_t mac[6])
{
    memcpy(g_usbd_rndis.mac, mac, 6);

    g_usbd_rndis.drv_version = 0x0001;
    g_usbd_rndis.link_status = NDIS_MEDIA_STATE_DISCONNECTED;

    rndis_ep_data[RNDIS_OUT_EP_IDX].ep_addr = out_ep;
    rndis_ep_data[RNDIS_OUT_EP_IDX].ep_cb = rndis_bulk_out;
    rndis_ep_data[RNDIS_IN_EP_IDX].ep_addr = in_ep;
    rndis_ep_data[RNDIS_IN_EP_IDX].ep_cb = rndis_bulk_in;
    rndis_ep_data[RNDIS_INT_EP_IDX].ep_addr = int_ep;
    rndis_ep_data[RNDIS_INT_EP_IDX].ep_cb = rndis_int_in;

    usbd_add_endpoint(0, &rndis_ep_data[RNDIS_OUT_EP_IDX]);
    usbd_add_endpoint(0, &rndis_ep_data[RNDIS_IN_EP_IDX]);
    usbd_add_endpoint(0, &rndis_ep_data[RNDIS_INT_EP_IDX]);

    intf->class_interface_handler = rndis_class_interface_request_handler;
    intf->class_endpoint_handler = NULL;
    intf->vendor_handler = NULL;
    intf->notify_handler = rndis_notify_handler;

    return intf;
}
