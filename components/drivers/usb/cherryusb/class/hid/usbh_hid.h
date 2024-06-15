/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_HID_H
#define USBH_HID_H

#include "usb_hid.h"

struct usbh_hid {
    struct usbh_hubport *hport;
    struct usb_endpoint_descriptor *intin;  /* INTR IN endpoint */
    struct usb_endpoint_descriptor *intout; /* INTR OUT endpoint */
    struct usbh_urb intin_urb;              /* INTR IN urb */
    struct usbh_urb intout_urb;             /* INTR OUT urb */

    uint8_t report_desc[256];
    uint8_t intf; /* interface number */
    uint8_t minor;

    void *user_data;
};

#ifdef __cplusplus
extern "C" {
#endif

int usbh_hid_set_idle(struct usbh_hid *hid_class, uint8_t report_id, uint8_t duration);
int usbh_hid_get_idle(struct usbh_hid *hid_class, uint8_t *buffer);
int usbh_hid_set_report(struct usbh_hid *hid_class, uint8_t report_type, uint8_t report_id, uint8_t *buffer, uint32_t buflen);
int usbh_hid_get_report(struct usbh_hid *hid_class, uint8_t report_type, uint8_t report_id, uint8_t *buffer, uint32_t buflen);

void usbh_hid_run(struct usbh_hid *hid_class);
void usbh_hid_stop(struct usbh_hid *hid_class);

#ifdef __cplusplus
}
#endif

#endif /* USBH_HID_H */
