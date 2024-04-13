/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_PL2303_H
#define USBH_PL2303_H

#include "usb_cdc.h"

#define PL2303_SET_REQUEST             0x01
#define PL2303_SET_REQUEST_PL2303HXN   0x80
#define PL2303_SET_CRTSCTS             0x41
#define PL2303_SET_CRTSCTS_PL2303X     0x61
#define PL2303_SET_CRTSCTS_PL2303HXN   0xFA
#define PL2303_CLEAR_CRTSCTS_PL2303HXN 0xFF
#define PL2303_CRTSCTS_REG_PL2303HXN   0x0A
#define PL2303_STATUS_REG_PL2303HX     0x8080

/* Different PL2303 IC types */
#define USBH_PL2303_TYPE_UNKNOWN   0
#define USBH_PL2303_TYPE_PL2303    1
#define USBH_PL2303_TYPE_PL2303HX  2
#define USBH_PL2303_TYPE_PL2303HXD 3
#define USBH_PL2303_TYPE_PL2303HXN 4

struct usbh_pl2303 {
    struct usbh_hubport *hport;
    struct usb_endpoint_descriptor *bulkin;  /* Bulk IN endpoint */
    struct usb_endpoint_descriptor *bulkout; /* Bulk OUT endpoint */

    struct usbh_urb bulkout_urb;
    struct usbh_urb bulkin_urb;

    struct cdc_line_coding linecoding;

    uint8_t intf;
    uint8_t minor;
    uint8_t chiptype;

    void *user_data;
};

#ifdef __cplusplus
extern "C" {
#endif

int usbh_pl2303_set_line_coding(struct usbh_pl2303 *pl2303_class, struct cdc_line_coding *line_coding);
int usbh_pl2303_get_line_coding(struct usbh_pl2303 *pl2303_class, struct cdc_line_coding *line_coding);
int usbh_pl2303_set_line_state(struct usbh_pl2303 *pl2303_class, bool dtr, bool rts);

int usbh_pl2303_bulk_in_transfer(struct usbh_pl2303 *pl2303_class, uint8_t *buffer, uint32_t buflen, uint32_t timeout);
int usbh_pl2303_bulk_out_transfer(struct usbh_pl2303 *pl2303_class, uint8_t *buffer, uint32_t buflen, uint32_t timeout);

void usbh_pl2303_run(struct usbh_pl2303 *pl2303_class);
void usbh_pl2303_stop(struct usbh_pl2303 *pl2303_class);

#ifdef __cplusplus
}
#endif

#endif /* USBH_PL2303_H */
