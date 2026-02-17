/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_HID_H
#define USBH_HID_H

#include "usb_hid.h"

/* local items */
#define HID_REPORT_FLAG_USAGE_MIN (1 << 0)
#define HID_REPORT_FLAG_USAGE_MAX (1 << 1)

/* global items */
#define HID_REPORT_FLAG_REPORT_ID    (1 << 2)
#define HID_REPORT_FLAG_REPORT_COUNT (1 << 3)
#define HID_REPORT_FLAG_REPORT_SIZE  (1 << 4)
#define HID_REPORT_FLAG_LOGICAL_MIN  (1 << 5)
#define HID_REPORT_FLAG_LOGICAL_MAX  (1 << 6)
#define HID_REPORT_FLAG_USAGE_PAGE   (1 << 7)

/* main items */
#define HID_REPORT_FLAG_INPUT   (1 << 8)
#define HID_REPORT_FLAG_OUTPUT  (1 << 9)
#define HID_REPORT_FLAG_FEATURE (1 << 10)

#define HID_REPORT_FLAG_EXTENDED_USAGE (1 << 11)

/* masks */

#define HID_REPORT_FLAG_GLOBAL_MASK (HID_REPORT_FLAG_REPORT_ID |    \
                                     HID_REPORT_FLAG_REPORT_COUNT | \
                                     HID_REPORT_FLAG_REPORT_SIZE |  \
                                     HID_REPORT_FLAG_LOGICAL_MIN |  \
                                     HID_REPORT_FLAG_LOGICAL_MAX |  \
                                     HID_REPORT_FLAG_USAGE_PAGE)

#define HID_REPORT_FLAG_REQUIRED_MASK (HID_REPORT_FLAG_REPORT_COUNT | \
                                       HID_REPORT_FLAG_REPORT_SIZE |  \
                                       HID_REPORT_FLAG_LOGICAL_MIN |  \
                                       HID_REPORT_FLAG_LOGICAL_MAX)

#define USAGE_ID(usage)   (usage & 0x0000FFFF)
#define USAGE_PAGE(usage) ((usage & 0xFFFF0000) >> 16)

#ifndef CONFIG_USBHOST_HID_MAX_INPUT
#define CONFIG_USBHOST_HID_MAX_INPUT 16
#endif

#ifndef CONFIG_USBHOST_HID_MAX_OUTPUT
#define CONFIG_USBHOST_HID_MAX_OUTPUT 16
#endif

#ifndef CONFIG_USBHOST_HID_MAX_FEATURE
#define CONFIG_USBHOST_HID_MAX_FEATURE 16
#endif

struct hid_report_field {
    uint32_t *usages; /* usage page + usage */
    uint32_t usage_count;
    uint32_t usage_page;

    uint32_t report_id; /* optional */
    uint32_t report_count;
    uint32_t report_size;
    int32_t logical_min;
    int32_t logical_max;
    uint32_t properties;

    uint32_t usage_min;
    uint32_t usage_max;

    uint32_t flags;
};

struct hid_report {
    bool uses_report_id;
    uint32_t input_count;
    struct hid_report_field input_fields[CONFIG_USBHOST_HID_MAX_INPUT];
    uint32_t output_count;
    struct hid_report_field output_fields[CONFIG_USBHOST_HID_MAX_OUTPUT];
    uint32_t feature_count;
    struct hid_report_field feature_fields[CONFIG_USBHOST_HID_MAX_FEATURE];
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

struct hid_report *usbh_hid_report_parse(const uint8_t *data, uint32_t report_len, uint32_t max_usages);
void usbh_hid_report_free(struct hid_report *hid_report);

void usbh_hid_run(struct usbh_hid *hid_class);
void usbh_hid_stop(struct usbh_hid *hid_class);

int lshid(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif /* USBH_HID_H */
