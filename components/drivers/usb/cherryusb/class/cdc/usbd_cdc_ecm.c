/*
 * Copyright (c) 2023, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_cdc_ecm.h"

#define CDC_ECM_OUT_EP_IDX 0
#define CDC_ECM_IN_EP_IDX   1
#define CDC_ECM_INT_EP_IDX  2

/* Describe EndPoints configuration */
static struct usbd_endpoint cdc_ecm_ep_data[3];

static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_cdc_ecm_rx_buffer[CONFIG_CDC_ECM_ETH_MAX_SEGSZE];
static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_cdc_ecm_tx_buffer[CONFIG_CDC_ECM_ETH_MAX_SEGSZE];
static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_cdc_ecm_notify_buf[16];

volatile uint8_t *g_cdc_ecm_rx_data_buffer = NULL;
volatile uint32_t g_cdc_ecm_rx_data_length = 0;
volatile uint32_t g_cdc_ecm_tx_data_length = 0;

static volatile uint8_t g_current_net_status = 0;
static volatile uint8_t g_cmd_intf = 0;

static uint32_t g_connect_speed_table[2] = { CDC_ECM_CONNECT_SPEED_UPSTREAM,
                                             CDC_ECM_CONNECT_SPEED_DOWNSTREAM };

void usbd_cdc_ecm_send_notify(uint8_t notifycode, uint8_t value, uint32_t *speed)
{
    struct cdc_eth_notification *notify = (struct cdc_eth_notification *)g_cdc_ecm_notify_buf;
    uint8_t bytes2send = 0;

    notify->bmRequestType = CDC_ECM_BMREQUEST_TYPE_ECM;
    notify->bNotificationType = notifycode;

    switch (notifycode) {
        case CDC_ECM_NOTIFY_CODE_NETWORK_CONNECTION:
            notify->wValue = value;
            notify->wIndex = g_cmd_intf;
            notify->wLength = 0U;

            for (uint8_t i = 0U; i < 8U; i++) {
                notify->data[i] = 0U;
            }
            bytes2send = 8U;
            break;
        case CDC_ECM_NOTIFY_CODE_RESPONSE_AVAILABLE:
            notify->wValue = 0U;
            notify->wIndex = g_cmd_intf;
            notify->wLength = 0U;
            for (uint8_t i = 0U; i < 8U; i++) {
                notify->data[i] = 0U;
            }
            bytes2send = 8U;
            break;
        case CDC_ECM_NOTIFY_CODE_CONNECTION_SPEED_CHANGE:
            notify->wValue = 0U;
            notify->wIndex = g_cmd_intf;
            notify->wLength = 0x0008U;
            bytes2send = 16U;

            memcpy(notify->data, speed, 8);
            break;

        default:
            break;
    }

    if (bytes2send) {
        usbd_ep_start_write(0, cdc_ecm_ep_data[CDC_ECM_INT_EP_IDX].ep_addr, g_cdc_ecm_notify_buf, bytes2send);
    }
}

static int cdc_ecm_class_interface_request_handler(uint8_t busid, struct usb_setup_packet *setup, uint8_t **data, uint32_t *len)
{
    USB_LOG_DBG("CDC ECM Class request: "
                "bRequest 0x%02x\r\n",
                setup->bRequest);

    (void)busid;
    (void)data;
    (void)len;

    g_cmd_intf = LO_BYTE(setup->wIndex);

    switch (setup->bRequest) {
        case CDC_REQUEST_SET_ETHERNET_PACKET_FILTER:
            /* bit0 Promiscuous
             * bit1 ALL Multicast
             * bit2 Directed
             * bit3 Broadcast
             * bit4 Multicast
            */
            if (g_current_net_status == 0) {
                g_current_net_status = 1;
                usbd_cdc_ecm_send_notify(CDC_ECM_NOTIFY_CODE_NETWORK_CONNECTION, CDC_ECM_NET_CONNECTED, NULL);
            }

            break;
        default:
            USB_LOG_WRN("Unhandled CDC ECM Class bRequest 0x%02x\r\n", setup->bRequest);
            return -1;
    }

    return 0;
}

void cdc_ecm_notify_handler(uint8_t busid, uint8_t event, void *arg)
{
    (void)busid;
    (void)arg;

    switch (event) {
        case USBD_EVENT_RESET:
            g_current_net_status = 0;
            g_cdc_ecm_rx_data_length = 0;
            g_cdc_ecm_tx_data_length = 0;
            g_cdc_ecm_rx_data_buffer = NULL;
            break;
        case USBD_EVENT_CONFIGURED:
            usbd_ep_start_read(0, cdc_ecm_ep_data[CDC_ECM_OUT_EP_IDX].ep_addr, &g_cdc_ecm_rx_buffer[g_cdc_ecm_rx_data_length], usbd_get_ep_mps(busid, cdc_ecm_ep_data[CDC_ECM_OUT_EP_IDX].ep_addr));
            break;

        default:
            break;
    }
}

void cdc_ecm_bulk_out(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    (void)busid;

    g_cdc_ecm_rx_data_length += nbytes;

    if (nbytes < usbd_get_ep_mps(0, ep)) {
        g_cdc_ecm_rx_data_buffer = g_cdc_ecm_rx_buffer;
        usbd_cdc_ecm_data_recv_done(g_cdc_ecm_rx_buffer, g_cdc_ecm_rx_data_length);
    } else {
        usbd_ep_start_read(0, ep, &g_cdc_ecm_rx_buffer[g_cdc_ecm_rx_data_length], usbd_get_ep_mps(0, ep));
    }
}

void cdc_ecm_bulk_in(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    (void)busid;

    if ((nbytes % usbd_get_ep_mps(0, ep)) == 0 && nbytes) {
        /* send zlp */
        usbd_ep_start_write(0, ep, NULL, 0);
    } else {
        g_cdc_ecm_tx_data_length = 0;
    }
}

void cdc_ecm_int_in(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    (void)busid;
    (void)ep;
    (void)nbytes;

    if (g_current_net_status == 1) {
        g_current_net_status = 2;
        usbd_cdc_ecm_send_notify(CDC_ECM_NOTIFY_CODE_NETWORK_CONNECTION, CDC_ECM_NET_CONNECTED, g_connect_speed_table);
    }
}

int usbd_cdc_ecm_start_write(uint8_t *buf, uint32_t len)
{
    if (g_cdc_ecm_tx_data_length > 0) {
        return -USB_ERR_BUSY;
    }

    g_cdc_ecm_tx_data_length = len;

    USB_LOG_DBG("txlen:%d\r\n", g_cdc_ecm_tx_data_length);
    return usbd_ep_start_write(0, cdc_ecm_ep_data[CDC_ECM_IN_EP_IDX].ep_addr, buf, g_cdc_ecm_tx_data_length);
}

void usbd_cdc_ecm_start_read_next(void)
{
    g_cdc_ecm_rx_data_length = 0;
    g_cdc_ecm_rx_data_buffer = NULL;
    usbd_ep_start_read(0, cdc_ecm_ep_data[CDC_ECM_OUT_EP_IDX].ep_addr, g_cdc_ecm_rx_buffer, usbd_get_ep_mps(0, cdc_ecm_ep_data[CDC_ECM_OUT_EP_IDX].ep_addr));
}

#ifdef CONFIG_USBDEV_CDC_ECM_USING_LWIP
struct pbuf *usbd_cdc_ecm_eth_rx(void)
{
    struct pbuf *p;

    if (g_cdc_ecm_rx_data_buffer == NULL) {
        return NULL;
    }
    p = pbuf_alloc(PBUF_RAW, g_cdc_ecm_rx_data_length, PBUF_POOL);
    if (p == NULL) {
        usbd_cdc_ecm_start_read_next();
        return NULL;
    }
    usb_memcpy(p->payload, (uint8_t *)g_cdc_ecm_rx_buffer, g_cdc_ecm_rx_data_length);
    p->len = g_cdc_ecm_rx_data_length;

    USB_LOG_DBG("rxlen:%d\r\n", g_cdc_ecm_rx_data_length);
    usbd_cdc_ecm_start_read_next();
    return p;
}

int usbd_cdc_ecm_eth_tx(struct pbuf *p)
{
    struct pbuf *q;
    uint8_t *buffer;

    if (g_cdc_ecm_tx_data_length > 0) {
        return -USB_ERR_BUSY;
    }

    if (p->tot_len > sizeof(g_cdc_ecm_tx_buffer)) {
        p->tot_len = sizeof(g_cdc_ecm_tx_buffer);
    }

    buffer = g_cdc_ecm_tx_buffer;
    for (q = p; q != NULL; q = q->next) {
        usb_memcpy(buffer, q->payload, q->len);
        buffer += q->len;
    }

    return usbd_cdc_ecm_start_write(g_cdc_ecm_tx_buffer, p->tot_len);
}
#endif

struct usbd_interface *usbd_cdc_ecm_init_intf(struct usbd_interface *intf, const uint8_t int_ep, const uint8_t out_ep, const uint8_t in_ep)
{
    intf->class_interface_handler = cdc_ecm_class_interface_request_handler;
    intf->class_endpoint_handler = NULL;
    intf->vendor_handler = NULL;
    intf->notify_handler = cdc_ecm_notify_handler;

    cdc_ecm_ep_data[CDC_ECM_OUT_EP_IDX].ep_addr = out_ep;
    cdc_ecm_ep_data[CDC_ECM_OUT_EP_IDX].ep_cb = cdc_ecm_bulk_out;
    cdc_ecm_ep_data[CDC_ECM_IN_EP_IDX].ep_addr = in_ep;
    cdc_ecm_ep_data[CDC_ECM_IN_EP_IDX].ep_cb = cdc_ecm_bulk_in;
    cdc_ecm_ep_data[CDC_ECM_INT_EP_IDX].ep_addr = int_ep;
    cdc_ecm_ep_data[CDC_ECM_INT_EP_IDX].ep_cb = cdc_ecm_int_in;

    usbd_add_endpoint(0, &cdc_ecm_ep_data[CDC_ECM_OUT_EP_IDX]);
    usbd_add_endpoint(0, &cdc_ecm_ep_data[CDC_ECM_IN_EP_IDX]);
    usbd_add_endpoint(0, &cdc_ecm_ep_data[CDC_ECM_INT_EP_IDX]);

    return intf;
}

void usbd_cdc_ecm_set_connect_speed(uint32_t speed[2])
{
    memcpy(g_connect_speed_table, speed, 8);
}

__WEAK void usbd_cdc_ecm_data_recv_done(uint8_t *buf, uint32_t len)
{
    (void)buf;
    (void)len;
}
