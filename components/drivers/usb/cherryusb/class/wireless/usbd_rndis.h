/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBD_RNDIS_H
#define USBD_RNDIS_H

#include "usb_cdc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Init rndis interface driver */
struct usbd_interface *usbd_rndis_init_intf(struct usbd_interface *intf,
                                             const uint8_t out_ep,
                                             const uint8_t in_ep,
                                             const uint8_t int_ep, uint8_t mac[6]);

void usbd_rndis_data_recv_done(void);

#ifdef CONFIG_USBDEV_RNDIS_USING_LWIP
struct pbuf *usbd_rndis_eth_rx(void);
int usbd_rndis_eth_tx(struct pbuf *p);
#endif

#ifdef __cplusplus
}
#endif

#endif /* USBD_RNDIS_H */
