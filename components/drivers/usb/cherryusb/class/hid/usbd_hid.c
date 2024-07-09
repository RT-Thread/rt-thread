/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_hid.h"

static int hid_class_interface_request_handler(uint8_t busid, struct usb_setup_packet *setup, uint8_t **data, uint32_t *len)
{
    USB_LOG_DBG("HID Class request: "
                "bRequest 0x%02x\r\n",
                setup->bRequest);

    uint8_t intf_num = LO_BYTE(setup->wIndex);

    switch (setup->bRequest) {
        case HID_REQUEST_GET_REPORT:
            /* report id ,report type */
            usbd_hid_get_report(busid, intf_num, LO_BYTE(setup->wValue), HI_BYTE(setup->wValue), data, len);
            break;
        case HID_REQUEST_GET_IDLE:
            (*data)[0] = usbd_hid_get_idle(busid, intf_num, LO_BYTE(setup->wValue));
            *len = 1;
            break;
        case HID_REQUEST_GET_PROTOCOL:
            (*data)[0] = usbd_hid_get_protocol(busid, intf_num);
            *len = 1;
            break;
        case HID_REQUEST_SET_REPORT:
            /* report id ,report type, report, report len */
            usbd_hid_set_report(busid, intf_num, LO_BYTE(setup->wValue), HI_BYTE(setup->wValue), *data, *len);
            break;
        case HID_REQUEST_SET_IDLE:
            /* report id, duration */
            usbd_hid_set_idle(busid, intf_num, LO_BYTE(setup->wValue), HI_BYTE(setup->wValue));
            break;
        case HID_REQUEST_SET_PROTOCOL:
            /* protocol */
            usbd_hid_set_protocol(busid, intf_num, LO_BYTE(setup->wValue));
            break;

        default:
            USB_LOG_WRN("Unhandled HID Class bRequest 0x%02x\r\n", setup->bRequest);
            return -1;
    }

    return 0;
}

struct usbd_interface *usbd_hid_init_intf(uint8_t busid, struct usbd_interface *intf, const uint8_t *desc, uint32_t desc_len)
{
    intf->class_interface_handler = hid_class_interface_request_handler;
    intf->class_endpoint_handler = NULL;
    intf->vendor_handler = NULL;
    intf->notify_handler = NULL;

    intf->hid_report_descriptor = desc;
    intf->hid_report_descriptor_len = desc_len;
    return intf;
}

__WEAK void usbd_hid_get_report(uint8_t busid, uint8_t intf, uint8_t report_id, uint8_t report_type, uint8_t **data, uint32_t *len)
{
    (*data[0]) = 0;
    *len = 1;
}

__WEAK uint8_t usbd_hid_get_idle(uint8_t busid, uint8_t intf, uint8_t report_id)
{
    return 0;
}

__WEAK uint8_t usbd_hid_get_protocol(uint8_t busid, uint8_t intf)
{
    return 0;
}

__WEAK void usbd_hid_set_report(uint8_t busid, uint8_t intf, uint8_t report_id, uint8_t report_type, uint8_t *report, uint32_t report_len)
{
}

__WEAK void usbd_hid_set_idle(uint8_t busid, uint8_t intf, uint8_t report_id, uint8_t duration)
{
}

__WEAK void usbd_hid_set_protocol(uint8_t busid, uint8_t intf, uint8_t protocol)
{
}