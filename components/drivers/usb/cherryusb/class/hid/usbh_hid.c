/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_hid.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_hid"
#include "usb_log.h"

#define DEV_FORMAT "/dev/input%d"

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_hid_buf[128];

static struct usbh_hid g_hid_class[CONFIG_USBHOST_MAX_HID_CLASS];
static uint32_t g_devinuse = 0;

static struct usbh_hid *usbh_hid_class_alloc(void)
{
    int devno;

    for (devno = 0; devno < CONFIG_USBHOST_MAX_HID_CLASS; devno++) {
        if ((g_devinuse & (1 << devno)) == 0) {
            g_devinuse |= (1 << devno);
            memset(&g_hid_class[devno], 0, sizeof(struct usbh_hid));
            g_hid_class[devno].minor = devno;
            return &g_hid_class[devno];
        }
    }
    return NULL;
}

static void usbh_hid_class_free(struct usbh_hid *hid_class)
{
    int devno = hid_class->minor;

    if (devno >= 0 && devno < 32) {
        g_devinuse &= ~(1 << devno);
    }
    memset(hid_class, 0, sizeof(struct usbh_hid));
}

static int usbh_hid_get_report_descriptor(struct usbh_hid *hid_class, uint8_t *buffer)
{
    struct usb_setup_packet *setup = hid_class->hport->setup;
    int ret;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_STANDARD | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = USB_REQUEST_GET_DESCRIPTOR;
    setup->wValue = HID_DESCRIPTOR_TYPE_HID_REPORT << 8;
    setup->wIndex = hid_class->intf;
    setup->wLength = 128;

    ret = usbh_control_transfer(hid_class->hport, setup, g_hid_buf);
    if (ret < 0) {
        return ret;
    }
    memcpy(buffer, g_hid_buf, ret - 8);
    return ret;
}

int usbh_hid_set_idle(struct usbh_hid *hid_class, uint8_t report_id, uint8_t duration)
{
    struct usb_setup_packet *setup = hid_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = HID_REQUEST_SET_IDLE;
    setup->wValue = (duration << 8) | report_id;
    setup->wIndex = hid_class->intf;
    setup->wLength = 0;

    return usbh_control_transfer(hid_class->hport, setup, NULL);
}

int usbh_hid_get_idle(struct usbh_hid *hid_class, uint8_t *buffer)
{
    struct usb_setup_packet *setup = hid_class->hport->setup;
    int ret;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = HID_REQUEST_GET_IDLE;
    setup->wValue = 0;
    setup->wIndex = hid_class->intf;
    setup->wLength = 1;

    ret = usbh_control_transfer(hid_class->hport, setup, g_hid_buf);
    if (ret < 0) {
        return ret;
    }
    memcpy(buffer, g_hid_buf, 1);
    return ret;
}

int usbh_hid_set_protocol(struct usbh_hid *hid_class, uint8_t protocol)
{
    struct usb_setup_packet *setup = hid_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = HID_REQUEST_SET_PROTOCOL;
    setup->wValue = protocol;
    setup->wIndex = 0;
    setup->wLength = 0;

    return usbh_control_transfer(hid_class->hport, setup, NULL);
}

int usbh_hid_set_report(struct usbh_hid *hid_class, uint8_t report_type, uint8_t report_id, uint8_t *buffer, uint32_t buflen)
{
    struct usb_setup_packet *setup = hid_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = HID_REQUEST_SET_REPORT;
    setup->wValue = (uint16_t)(((uint32_t)report_type << 8U) | (uint32_t)report_id);
    setup->wIndex = 0;
    setup->wLength = buflen;

    return usbh_control_transfer(hid_class->hport, setup, buffer);
}

int usbh_hid_get_report(struct usbh_hid *hid_class, uint8_t report_type, uint8_t report_id, uint8_t *buffer, uint32_t buflen)
{
    struct usb_setup_packet *setup = hid_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = HID_REQUEST_GET_REPORT;
    setup->wValue = (uint16_t)(((uint32_t)report_type << 8U) | (uint32_t)report_id);
    setup->wIndex = 0;
    setup->wLength = buflen;

    return usbh_control_transfer(hid_class->hport, setup, buffer);
}

int usbh_hid_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    int ret;

    struct usbh_hid *hid_class = usbh_hid_class_alloc();
    if (hid_class == NULL) {
        USB_LOG_ERR("Fail to alloc hid_class\r\n");
        return -USB_ERR_NOMEM;
    }

    hid_class->hport = hport;
    hid_class->intf = intf;

    hport->config.intf[intf].priv = hid_class;

    // /* 0x0 = boot protocol, 0x1 = report protocol */
    // ret = usbh_hid_set_protocol(hid_class, 0x1);
    // if (ret < 0) {
    //     return ret;
    // }

    ret = usbh_hid_set_idle(hid_class, 0, 0);
    if (ret < 0) {
        USB_LOG_WRN("Do not support set idle\r\n");
    }

    ret = usbh_hid_get_report_descriptor(hid_class, hid_class->report_desc);
    if (ret < 0) {
        return ret;
    }

    for (uint8_t i = 0; i < hport->config.intf[intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &hport->config.intf[intf].altsetting[0].ep[i].ep_desc;
        if (ep_desc->bEndpointAddress & 0x80) {
            USBH_EP_INIT(hid_class->intin, ep_desc);
        } else {
            USBH_EP_INIT(hid_class->intout, ep_desc);
        }
    }

    snprintf(hport->config.intf[intf].devname, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT, hid_class->minor);

    USB_LOG_INFO("Register HID Class:%s\r\n", hport->config.intf[intf].devname);

    usbh_hid_run(hid_class);
    return ret;
}

int usbh_hid_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_hid *hid_class = (struct usbh_hid *)hport->config.intf[intf].priv;

    if (hid_class) {
        if (hid_class->intin) {
            usbh_kill_urb(&hid_class->intin_urb);
        }

        if (hid_class->intout) {
            usbh_kill_urb(&hid_class->intout_urb);
        }

        if (hport->config.intf[intf].devname[0] != '\0') {
            USB_LOG_INFO("Unregister HID Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_hid_stop(hid_class);
        }

        usbh_hid_class_free(hid_class);
    }

    return ret;
}

__WEAK void usbh_hid_run(struct usbh_hid *hid_class)
{
}

__WEAK void usbh_hid_stop(struct usbh_hid *hid_class)
{
}

const struct usbh_class_driver hid_class_driver = {
    .driver_name = "hid",
    .connect = usbh_hid_connect,
    .disconnect = usbh_hid_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info hid_custom_class_info = {
    .match_flags = USB_CLASS_MATCH_INTF_CLASS,
    .class = USB_DEVICE_CLASS_HID,
    .subclass = 0x00,
    .protocol = 0x00,
    .id_table = NULL,
    .class_driver = &hid_class_driver
};
