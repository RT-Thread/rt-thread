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

/* Ethernet Maximum Segment size, typically 1514 bytes */
#define CONFIG_CDC_ECM_ETH_MAX_SEGSZE 1514U

/* Init cdc ecm interface driver */
struct usbd_interface *usbd_cdc_ecm_init_intf(struct usbd_interface *intf, const uint8_t int_ep, const uint8_t out_ep, const uint8_t in_ep);

/* Setup request command callback api */
void usbd_cdc_ecm_set_connect_speed(uint32_t speed[2]);

/* Api for eth only without any net stack */
uint8_t *usbd_cdc_ecm_get_tx_buffer(void);
void usbd_cdc_ecm_send_done(void);
int usbd_cdc_ecm_start_write(uint8_t *buf, uint32_t len);
void usbd_cdc_ecm_data_recv_done(uint8_t *buf, uint32_t len);
void usbd_cdc_ecm_start_read_next(void);

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
