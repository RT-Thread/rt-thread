/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_RNDIS_H
#define USBH_RNDIS_H

#include "usb_cdc.h"

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
    uint32_t tx_offset;
    uint32_t max_transfer_pkts; /* max packets in one transfer */
    uint32_t max_transfer_size; /* max size in one transfer */

    uint32_t link_speed;
    bool connect_status;
    uint8_t mac[6];

    void *user_data;
};

#ifdef __cplusplus
extern "C" {
#endif

int usbh_rndis_get_connect_status(struct usbh_rndis *rndis_class);
int usbh_rndis_keepalive(struct usbh_rndis *rndis_class);

void usbh_rndis_run(struct usbh_rndis *rndis_class);
void usbh_rndis_stop(struct usbh_rndis *rndis_class);

uint8_t *usbh_rndis_get_eth_txbuf(void);
int usbh_rndis_eth_output(uint32_t buflen);
void usbh_rndis_eth_input(uint8_t *buf, uint32_t buflen);
void usbh_rndis_rx_thread(void *argument);

#ifdef __cplusplus
}
#endif

#endif /* USBH_RNDIS_H */
