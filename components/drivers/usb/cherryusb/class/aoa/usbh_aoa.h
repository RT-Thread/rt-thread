/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_AOA_H
#define USBH_AOA_H

#include "usb_aoa.h"

struct usbh_aoa {
    struct usbh_hubport *hport;
    struct usb_endpoint_descriptor *bulkin;  /* Bulk IN endpoint */
    struct usb_endpoint_descriptor *bulkout; /* Bulk OUT endpoint */

    struct usbh_urb bulkout_urb;
    struct usbh_urb bulkin_urb;

    uint8_t intf;
    uint8_t minor;

    void *user_data;
};

#ifdef __cplusplus
extern "C" {
#endif

int usbh_aoa_switch(struct usbh_hubport *hport, struct aoa_string_info *info);
int usbh_aoa_register_hid(struct usbh_aoa *aoa_class, uint16_t id, uint8_t *report, uint32_t report_len);
int usbh_aoa_send_hid_event(struct usbh_aoa *aoa_class, uint16_t id, uint8_t *event, uint32_t event_len);

void usbh_aoa_run(struct usbh_aoa *aoa_class);
void usbh_aoa_stop(struct usbh_aoa *aoa_class);

#ifdef __cplusplus
}
#endif

#endif /* USBH_AOA_H */