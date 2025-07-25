/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBD_CDC_ECM_H
#define USBD_CDC_ECM_H

#include "usb_cdc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Init cdc ecm interface driver */
struct usbd_interface *usbd_cdc_ecm_init_intf(struct usbd_interface *intf, const uint8_t int_ep, const uint8_t out_ep, const uint8_t in_ep);

int usbd_cdc_ecm_set_connect(bool connect, uint32_t speed[2]);

void usbd_cdc_ecm_data_recv_done(uint32_t len);
void usbd_cdc_ecm_data_send_done(uint32_t len);
int usbd_cdc_ecm_start_write(uint8_t *buf, uint32_t len);
int usbd_cdc_ecm_start_read(uint8_t *buf, uint32_t len);

#ifdef CONFIG_USBDEV_CDC_ECM_USING_LWIP
#include "lwip/netif.h"
#include "lwip/pbuf.h"
struct pbuf *usbd_cdc_ecm_eth_rx(void);
int usbd_cdc_ecm_eth_tx(struct pbuf *p);
#endif

#ifdef __cplusplus
}
#endif

#endif /* USBD_CDC_ECM_H */
