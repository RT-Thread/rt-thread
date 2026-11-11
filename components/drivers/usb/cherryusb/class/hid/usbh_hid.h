/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_HID_H
#define USBH_HID_H

#include "usb_hid.h"

#ifndef CONFIG_USB_HID_MAX_REPORT_ITEMS
#define CONFIG_USB_HID_MAX_REPORT_ITEMS       16
#endif

struct usbh_hid_report_item_attribute {
    uint16_t usage_page;
    uint16_t usage_min;
    uint16_t usage_max;
    int32_t logical_min;
    int32_t logical_max;
    uint32_t physical_min;
    uint32_t physical_max;
    uint32_t unit_exponent;
    uint32_t unit;
    uint32_t report_count;
    uint8_t report_size;
    uint8_t report_id;
};

struct usbh_hid_report_item {
    uint8_t report_type; /* input, output, feature */
    uint16_t report_flags;
    uint32_t report_bit_offset;

    struct usbh_hid_report_item_attribute attribute;
};

struct usbh_hid_report_info {
    struct usbh_hid_report_item report_items[CONFIG_USB_HID_MAX_REPORT_ITEMS];
    uint32_t report_item_count;
    bool using_report_id;
};

struct usbh_hid {
    struct usbh_hubport *hport;
    struct usb_endpoint_descriptor *intin;  /* INTR IN endpoint */
    struct usb_endpoint_descriptor *intout; /* INTR OUT endpoint */
    struct usbh_urb intin_urb;              /* INTR IN urb */
    struct usbh_urb intout_urb;             /* INTR OUT urb */

    uint16_t report_size;

    uint8_t protocol;
    uint8_t intf; /* interface number */
    uint8_t minor;

    void *user_data;
};

#ifdef __cplusplus
extern "C" {
#endif

int usbh_hid_get_report_descriptor(struct usbh_hid *hid_class, uint8_t *buffer, uint32_t buflen);
int usbh_hid_set_idle(struct usbh_hid *hid_class, uint8_t report_id, uint8_t duration);
int usbh_hid_get_idle(struct usbh_hid *hid_class, uint8_t *buffer);
int usbh_hid_set_protocol(struct usbh_hid *hid_class, uint8_t protocol);
int usbh_hid_get_protocol(struct usbh_hid *hid_class, uint8_t *protocol);
int usbh_hid_set_report(struct usbh_hid *hid_class, uint8_t report_type, uint8_t report_id, uint8_t *buffer, uint32_t buflen);
int usbh_hid_get_report(struct usbh_hid *hid_class, uint8_t report_type, uint8_t report_id, uint8_t *buffer, uint32_t buflen);

int usbh_hid_parse_report_descriptor(const uint8_t *report_data, uint32_t report_size, struct usbh_hid_report_info *report_info);
int usbh_hid_report_convert(struct usbh_hid_report_item *item, const uint8_t *report_buf, uint32_t *output1, uint8_t **output2, uint32_t *output_len);

void usbh_hid_run(struct usbh_hid *hid_class);
void usbh_hid_stop(struct usbh_hid *hid_class);

int lshid(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif /* USBH_HID_H */
