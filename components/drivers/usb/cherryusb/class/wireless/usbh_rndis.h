/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_RNDIS_H
#define USBH_RNDIS_H

#include "usb_cdc.h"

#include "lwip/netif.h"
#include "lwip/pbuf.h"

struct usbh_rndis {
    struct usbh_hubport *hport;
    struct usb_endpoint_descriptor *bulkin;  /* Bulk IN endpoint */
    struct usb_endpoint_descriptor *bulkout; /* Bulk OUT endpoint */
    struct usb_endpoint_descriptor *intin;   /* INTR endpoint */
    struct usbh_urb bulkin_urb;              /* Bulk IN urb */
    struct usbh_urb bulkout_urb;             /* Bulk OUT urb */
    struct usbh_urb intin_urb;               /* INTR IN urb */

    uint8_t ctrl_intf; /* Control interface number */
    uint8_t data_intf; /* Data interface number */
    uint8_t minor;

    uint32_t request_id;

    uint32_t link_speed;
    bool connect_status;
    uint8_t mac[6];

    ip_addr_t ipaddr;
    ip_addr_t netmask;
    ip_addr_t gateway;
};

#ifdef __cplusplus
extern "C" {
#endif

int usbh_rndis_get_connect_status(struct usbh_rndis *rndis_class);
int usbh_rndis_keepalive(struct usbh_rndis *rndis_class);

void usbh_rndis_run(struct usbh_rndis *rndis_class);
void usbh_rndis_stop(struct usbh_rndis *rndis_class);

err_t usbh_rndis_linkoutput(struct netif *netif, struct pbuf *p);
void usbh_rndis_rx_thread(void *argument);

#ifdef __cplusplus
}
#endif

#endif /* USBH_RNDIS_H */
