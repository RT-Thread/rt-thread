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

int usbd_rndis_set_connect(bool connect);

void usbd_rndis_data_recv_done(uint32_t len);
void usbd_rndis_data_send_done(uint32_t len);
int usbd_rndis_start_write(uint8_t *buf, uint32_t len);
int usbd_rndis_start_read(uint8_t *buf, uint32_t len);

#ifdef CONFIG_USBDEV_RNDIS_USING_LWIP
struct pbuf *usbd_rndis_eth_rx(void);
int usbd_rndis_eth_tx(struct pbuf *p);
#endif

#ifdef __cplusplus
}
#endif

#endif /* USBD_RNDIS_H */
