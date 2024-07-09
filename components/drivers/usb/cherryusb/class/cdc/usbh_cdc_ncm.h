/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_CDC_NCM_H
#define USBH_CDC_NCM_H

#include "usb_cdc.h"

struct usbh_cdc_ncm {
    struct usbh_hubport *hport;
    struct usb_endpoint_descriptor *bulkin;  /* Bulk IN endpoint */
    struct usb_endpoint_descriptor *bulkout; /* Bulk OUT endpoint */
    struct usb_endpoint_descriptor *intin;   /* Interrupt IN endpoint */
    struct usbh_urb bulkout_urb;             /* Bulk out endpoint */
    struct usbh_urb bulkin_urb;              /* Bulk IN endpoint */
    struct usbh_urb intin_urb;               /* Interrupt IN endpoint */

    uint8_t ctrl_intf; /* Control interface number */
    uint8_t data_intf; /* Data interface number */
    uint8_t minor;

    struct cdc_ncm_ntb_parameters ntb_param;
    uint16_t bulkin_sequence;
    uint16_t bulkout_sequence;

    uint8_t mac[6];
    bool connect_status;
    uint16_t max_segment_size;
    uint32_t speed[2];

    void *user_data;
};

#ifdef __cplusplus
extern "C" {
#endif

int usbh_cdc_ncm_get_connect_status(struct usbh_cdc_ncm *cdc_ncm_class);

void usbh_cdc_ncm_run(struct usbh_cdc_ncm *cdc_ncm_class);
void usbh_cdc_ncm_stop(struct usbh_cdc_ncm *cdc_ncm_class);

uint8_t *usbh_cdc_ncm_get_eth_txbuf(void);
int usbh_cdc_ncm_eth_output(uint32_t buflen);
void usbh_cdc_ncm_eth_input(uint8_t *buf, uint32_t buflen);
void usbh_cdc_ncm_rx_thread(void *argument);

#ifdef __cplusplus
}
#endif

#endif /* USBH_CDC_NCM_H */
